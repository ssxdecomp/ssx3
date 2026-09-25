# Rider animation

Every rider carries an animation model (the compiled skeleton built from its outfit's model parts) and an
animator that plays compressed clips on six prioritised channels. Each tick the rider's controller picks a
*semantic* (an abstract animation state such as "cruise", "brake", "air adjust left"), the animator resolves it
to a clip, blends it with the sequences already playing, samples a local pose, and the rider code builds the
world pose from the physical root with lean, lift, board alignment and leg IK. The same cached pose feeds
rendering and the body collision spheres.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a
PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Translation units per the current splits:

- `src/animation/animmodel.cpp`: model assembly and compile (`0x0030D8B8` `cAnimModel_addModelPartLOD`,
  `0x0030DBD0` `cAnimModel_compile`), part-active query `0x0030EBC0`, single-bone sampling `0x0030ECD8`, the
  local-pose sampler `0x0030F2B0`, forward kinematics `0x00310200`, late translation `0x00310530`, bone
  world-position query `0x00310C48`, mask helper `0x00310CE8` (bone lists to masks, unconfirmed), 30 Hz segment
  lookup `0x00311318`.
- `src/animation/rideranimbase.cpp`: the rider animator (`0x003118D0` `cRiderAnimBase_cRiderAnimBase`,
  `0x003128E8` `cRiderAnimBase_play`, `0x00311B48` `cRiderAnimBase_changeHeadingOffset`, `0x00311BF0`
  `cRiderAnimBase_changeOrientationOffset`), sequence creation `0x00311F00`, channel queries
  `0x00311AE8`/`0x00311B20`/`0x00312AA0`/`0x00312AE8`, replace/crossfade `0x00312B18`/`0x00312BD0`, duration query
  `0x00312790`, completion dispatch `0x00312490`, scalar sampler `0x00312C20`, slot advance and events
  `0x003135B0`..`0x003139A8`, fade advance `0x00313800`.
- `src/animation/animsequencer.cpp`: sequences and sequencers (`0x00313A10` `cAnimSequence_fadeWeight`,
  `0x00314760` `cAnimSequencer_getSequence`), slot clip setter `0x00313C50`, slot seek `0x00313CF0`, fade weights
  `0x00313D70`, descriptor emission `0x00314418`, sequence init `0x00314518`, sequence removal `0x003145F8`.
- `src/animation/gameanimmap.cpp`: pending-rate setter `0x003158E0`.
- `asm/2125C8.s` (unsplit): weighted variant lookup `0x00311710`.
- `asm/1218.s` (unsplit): driver dispatch `0x001036A0`, completion callbacks `0x00103918`, ground cycle selection
  `0x00103E28`/`0x00104178`, prewind driver `0x00104358`, air-adjust driver `0x001043F8`, grab-completion
  helper `0x00104B48`, variant-mask source `0x00104CF8`, soft-reaction selection `0x00108388`.
- `asm/14B10.s` (unsplit): reverse turn `0x00114CC0`, in-flight switch test `0x00114DB8`, stance reversal
  `0x00115168`, reaction request playback `0x00115B58`, upper-body reactions `0x00115D48`.
- `src/ai/rider.cpp`: outfit collection and part adding `0x0011BBE8`/`0x0011C138`, rider init with bone masks
  `0x0011C298`, pose phases `0x00121700`/`0x00121728`/`0x00121750`, local phase `0x0011EB60`, world pose
  `0x0011EB98`, leg IK `0x0011F3D8`, `0x0011FA10` (`cRider_doLeanPoseAdjust`), grab rate `0x00120038`,
  secondary motion `0x00120378`, control approach `0x001211F8`.
- `src/ai/ai.cpp`: the controllers that choose animations (ground `0x00131620`, prewind `0x0012E9B8`, air
  `0x00133308`, grab lifecycle `0x001352A8`, in-flight switch `0x00135BE0`), airborne root `0x00134DD0`,
  direction classifier `0x0012EE30`, release rate `0x00133128`.
- `src/ai/control/handplantcontrol.cpp` (current range, which also covers ground/air motion and landing):
  lift target inside `0x0013D818`, board-normal filter inside `0x0013F178`, landing `0x00139C88`,
  `0x0013A8F8`/`0x0013A968`.

## Per-tick order

1. The active controller runs (ground `0x00131620`, prewind `0x0012E9B8`, air `0x00133308`, ...). It writes
   control targets and makes play/fade/rate requests immediately. The ground, prewind and air selections read
   the *filtered current* control values from before this tick's approach pass; for the ground controller this
   is the step-start turn, brake, crouch, velocity, lateral vector and boost **(PS2)**.
2. `0x001211F8` approaches the control triplets (current value toward target at a rate), including the
   animation-turn filter, lift, air-adjust and prewind pairs. Local animation preparation reads the approached
   values.
3. `0x00121700` calls `0x0011EB60`: advance (sequences with a kind driver are advanced by that driver), local
   sampling, then completion dispatch.
   `0x0011EB60` calls `0x003123C0` and `0x00312598` and then `0x00312490` (completion dispatch).
4. `0x00121728` calls `0x0011EB98`: root presentation, world FK, board alignment and leg IK.
5. After contact, `0x00121750` calls `0x00310530`, which commits the translation accumulated by `0x00106538` in
   rider `+0x9D0` to the cached bones and skin matrices. The pose is not resampled: landing/impact handling in
   `0x0013AA48` reuses the cached pose of the tick.

Other ordering facts:

- The ground selector runs before the function at `0x0013D818`, whose lift target (`0x0013E144`..`0x0013E228`)
  and board-alignment target read the animation class; they therefore see the class chosen this tick **(PS2)**.
- On a charged release (control 2), the first control-5 step (grab, adjust spin, air selection) runs on the
  *next* tick, not the release tick **(PS2)**.
- Passive departure (riding off an edge): the ground controller has already run on the departure tick; the next
  tick (control 0 still running, now airborne) requests control 4 (entry `0x0012F730`); the tick after is the
  first passive-air step. A passive-to-control-5 transition does not also step the air controller on that tick
  **(PS2)**. Inside `0x0013F178` the rider stays in ground mode through the final body-pose query and only then
  starts the airborne predictor after final clamping (sites `0x0013F194`, `0x0013F264`, `0x0013F2B0`).
- Control-2 entry `0x0012E980` sets `+0x204` = 0 and `+0x200` = 1/30 before that tick's approach pass, so the
  fading ground cycle keeps blending toward 0 **(PS2)**.
- Whether `+0x1FC` is approached on the tick after a passive departure is stated both ways in the source notes:
  one says the departure tick advances it and the following control-0-in-air tick does not; a later note says
  that following tick does approach it (at least with tuck held). Unresolved.

## Data layout

### Rider fields used by animation

Offsets are into the rider actor.

| Offset | Meaning |
| --- | --- |
| `+0x110` / `+0x120` | Physical position / quaternion: the normal pose root. |
| `+0x130` / `+0x140` | Optional second root, used only when `+0x150` is nonzero. |
| `+0x170` / `+0x180` | Board-root forward / up of the last pose. |
| `+0x1E0` | Velocity (post-controller value is used by secondary motion). |
| `+0x1F0` | Physical turn triplet. |
| `+0x1FC` | Animation-turn triplet, a separate filter used by the ground cycle blend (not `+0x1F0`). |
| `+0x238` | Rail balance (input of the rail cycle blend). |
| `+0x28C` / `+0x298` | Air-adjust triplets (targets written by the air selector). |
| `+0x2BC` | Board-alignment weight. |
| `+0x2C8`/`+0x2CC`/`+0x2D0` | Presentation-lift triplet (body root only). |
| `+0x318` | Leg-IK gate. |
| `+0x31C` | Board lift from a cosine oscillator (not the `+0x758` contact compression). |
| `+0x320` | Stance (toggled by stance reversal). |
| `+0x328`, `+0x2DC` | Both zero enables prewind branch 3 (reverse turn). |
| `+0x354` / `+0x358` | Pending reaction: due logic tick / kind. |
| `+0x35C` | Idle clock, +1/60 per tick; zeroed by control-0 entry `0x00131608`. |
| `+0x360` | Board-press latch, cleared by control-0 entry. |
| `+0x364` | Variant eligibility flags for the rider animator. |
| `+0x370` | Contact normal. |
| `+0x390` | Filtered board-plane normal. |
| `+0x3A0` / `+0x3B0` | Tangent basis; the turn offset is applied along `+0x3B0`. |
| `+0x780` | Animation model ("geometry"). |
| `+0x784` | Animator. |
| `+0x86C` | Secondary-motion phase (compared with logic tick mod 6). |
| `+0x89C` | Animated bone used as the air pivot (Zoe: bone 0). |
| `+0x8A8` | Cached bone used for the secondary-motion wind. |
| `+0x8C0` / `+0x8C8` / `+0x8D0` | Channel-1 bone masks (64-bit). |
| `+0x8E0` / `+0x910` | Leg-IK bindings, one per leg. |
| `+0x950` / `+0x960` | Secondary-motion wind factors. |
| `+0x9D0` | Accumulated contact translation. |
| `+0xB1C` | Nonzero enables the reduced-bone mask. |

Several controls are triplets of floats advanced by `0x001211F8`. The order inside a triplet is not fixed by
these notes; for `+0x1FC`, `+0x204` behaves as the target and `+0x200` as the rate (unconfirmed).

### Animation model (`rider+0x780`)

| Offset | Meaning |
| --- | --- |
| `+0x08` | Part count. |
| `+0x0C` | Model-part records, stride 0x58. |
| `+0x24` / `+0x28` | Local position / quaternion arrays, one float4 per bone. |
| `+0x2C` | World transforms, 32 bytes per bone (position, then quaternion). |
| `+0x38` | Bind bank. |
| `+0x140` | The three body scale factors. |
| `+0x150` | 64-bit bone mask intersected with each sequence's mask. |
| `+0x158` | Reduced-bone mask, also intersected when rider `+0xB1C` is nonzero. |

Model-part record (0x58 bytes):

| Offset | Meaning |
| --- | --- |
| `+0x00` | File ID (the part slot). |
| `+0x04` | Compiled bone base (first bone slot). |
| `+0x18` | Active. |
| `+0x1C` | LOD/variant table of 16-byte entries {model header, material names, flags, ...}. |
| `+0x38` | Original bone records. |
| `+0x44` | Bone count. |
| `+0x50` | Selects the live entry of the `+0x1C` table; it is not always entry 0 (reading of the source wording, unconfirmed). |

Zoe's `TopB`/`BottomB`/`HandsB_NIS`/`DummyB_NIS` and Nate's `TopC` use variant entries 1..5 **(PS2)**. The live
model header of each part is byte-identical to its `MDLPS2.BIG` LOD0 header except for three loader-patched
pointer words at header bytes 56..67 **(PS2)**.

### Animator (`rider+0x784`)

| Offset | Meaning |
| --- | --- |
| `+0x00`..`+0x14` | The six *requested* semantics, one word per channel. |
| `+0x1C` | Pending rate for the next play request (setter `0x003158E0`). |
| `+0x50` | Pointer to six 8-byte sequencers {count, linked-list head}, one per channel. |
| `+0x60` / `+0x64` | Owner references for the normal and alternate variant-mask paths of `0x00104CF8`; `+0x64` is 0 for race riders (reading of the source wording, unconfirmed). |

Channel priorities come from the table at `0x0048D808` = {3, 2, 1, 0, 0, 0}, indexed by channel;
`0x003128E8` gives each new sequence the priority of its channel **(PS2)**. The observed channel uses are:

| Channel | Priority | Use |
| --- | --- | --- |
| 0 | 3 | Not identified in these notes. |
| 1 | 2 | Upper body: head checks and reactions, with the rider's channel-1 masks. |
| 2 | 1 | Main body (ground cycles, air clips such as 288 and 297..304). |
| 3..5 | 0 | Secondary motion (`SH_*` clips). |

### Sequence node

| Offset | Meaning |
| --- | --- |
| `+0x00` | Semantic state ID (not a bank index). |
| `+0x04` | Slot 0 packed clip ID: low 8 bits bank, remaining bits animation index. |
| `+0x08` | Slot 0 time (seconds). |
| `+0x0C` | Slot 0 rate. |
| `+0x10` | Slot 0 duration. |
| `+0x14` | Slot 0 weight. |
| `+0x18` | Slot 0 enabled. |
| `+0x60` / `+0x70` | Per-sequence root offsets (rotated on stance reversal). |
| `+0x80` | Mirror flag. |
| `+0x84` | Priority. |
| `+0x88` | 64-bit bone mask. |
| `+0x90` | Sequence playback rate. |
| `+0xB0` / `+0xB8` | Latched / newly raised event flags. |
| `+0xC0` | Completion flag (returned by `0x00312AE8`). |
| `+0xC4` | Seek pending. |
| `+0xC8` | Next sequence in the channel list. |

A sequence has three playback slots with stride 0x1C; slot n's fields are at the slot-0 offsets plus n x 0x1C.
The packed clip ID for bank 0 (the basic bank) is `index << 8`.

Example: the Snow Jam glide state (Zoe) **(PS2)**

| Channel | Packed clip | Clip name | Priority / mask |
| --- | --- | --- | --- |
| 1 | 0x1D00 | `HEADCHECK_TS` | 2 / 0x870 (bones 4, 5, 6, 11: neck, head, clavicles) |
| 2 | 0x2300 | `RNORM_FWD_CYC` | 1 / all bones |
| 2, second slot | 0x2400 | `RNORM_TURN_HS_1_CYC` | weight 0 |
| 3 | 0x1E000 | `SH_RIGHT_CYC` | 0 / secondary model parts (hair; includes part 19, no body bones) |

### Semantic definitions

Each semantic has a definition with: class, driver kind, completion kind, channel, blend time, first fade-in
and end fade-out. A field at `+0x8` of the definition/descriptor selects the completion callback in
`0x00103918` (that this is the same record is unconfirmed). Semantics resolve to clips through a lookup of
*leaves* (`0x00104CF8` then `0x00311710`); a leaf gives a packed clip ID, an integer weight and flags.

Classes referenced by the code in these notes:

| Class | Where it matters |
| --- | --- |
| 1 | Air-adjust definitions 297..304. |
| 2 | Checked by the phase-1 extension gate of the air selector. |
| 4, 5, 10 | Suppress the presentation-lift target (as does semantic 22). |
| 5 | Steep-slope bob 16/17; ground selection keeps a class-5 semantic. Blocks reaction playback (with 10). |
| 6 | Soft collision reactions 55..60. |
| 7 | Ordinary ground cycles. |
| 9 | Charged-release entry clips. |
| 10 | Landing; ground selection keeps it. |
| 18..20 | Grab active. |

Driver kinds (dispatched by `0x001036A0` through the function table at `0x00456950`, indexed by kind):

| Kind | Driver |
| --- | --- |
| 0, 1, 2 | Other kinds (not detailed in these notes). |
| 4 | Ground cycle blend; reads `+0x1FC`. |
| 5 | Rail balance blend on rider `+0x238`. |
| 7 | Prewind, `0x00104358`. |
| 11 | Air adjust, `0x001043F8`. |

Completion kinds (callbacks dispatched from `0x00312490`):

| Kind | Effect |
| --- | --- |
| 0 | None. |
| 1 | Removes the finished clip (e.g. `A_INTO_AIR`, switch 288) and creates 287, keeping its weight/fade (`0x00312B18`). |
| 2 | Charged-release clips are replaced by 289..296. |
| 3 | Like kind 1 but returns to 5. |
| 4 | Clears end event 63 and requests 5 with an ordinary crossfade (`0x00312BD0`). |
| 5 | Grab end: `0x00104B48`/`0x00312BD0` fade into 287 when animator `+0x64` is 0, else request 436. |

## Model assembly and skeleton compile

- Outfit collection `0x0011BBE8` gathers the equipped item entries of the base rider (a cheat skin takes every
  entry of its own bucket). `0x0011C138` adds each entry's four LOD models by name at its part slot through
  `0x0030D8B8` (`cAnimModel_addModelPartLOD`); the first model added for a file ID creates the part.
- Rider init (`0x0011C298`) hides slots 5, 6, 8, 9 and 11 (cinematic head, eyes, cinematic hands, cinematic
  right hand, PDA) at `0x0011C61C`.
- `0x0030DBD0` (`cAnimModel_compile`):
  - Sorts the parts by file ID (sort routine `0x00418EF8`).
  - A part's bone base is the running bone count over all parts, hidden parts included (the eye part holds two
    slots). In Zoe's race model the body is compiled bones 0..21, the board 22/23, the hidden eyes 24/25 and the
    hair 26..28 **(PS2)**.
  - Each part with morphs takes the next morph index.
  - Inverse binds: local at `0x0030E560`, world = parent x local at `0x0030E5F4`, rigid inverse at `0x0030E748`
    (locations inside `0x0030DBD0`). The VU0 multiplies and adds round toward zero with denormals flushed, e.g.
    Zoe's hips term 2 x 7.1e-20 x 7.1e-20 becomes 0. Bind translations are float centimetres **(PS2)**.
- Channel-1 masks, built in `0x0011C298` with `0x00310CE8` from bone lists:
  - `+0x8C0` = bones of list `0x00457A90`, plus the file-7 hands morph bit at (slot count + morph index).
  - `+0x8C8` = list `0x00457B38` plus the same bit.
  - `+0x8D0` = list `0x00457BC8` = 0x870 (the head-check bones).
  - Bits above the bone slots therefore address morph channels. Live `+0x8C0` values are bones 1..15 plus one
    high bit, e.g. bit 31 for Zoe, bit 30 for Psymon, bit 33 for Moby **(PS2)**.
- The air pivot, the secondary-motion bones [5, 2, 0], the contact legs and the board bones are named bones of
  files 0/1, so they do not change with the outfit.
- Secondary-motion enables (block `0x0011CF70`..`0x0011D1B8` inside `0x0011C298`, using `0x0030EBC0` "part is
  active"):
  - secondary channel 0: any active part in slots 0x0F..0x1D except 0x12 (hair and hats);
  - secondary channel 1: slots 0x1E, 0x1F, 0x20, 0x22 (hoodie, necklace, wings, backpack);
  - secondary channel 2: slots 0x24, 0x26, 0x27, 0x2A (T-shirt, tail, suspenders).
- Body scale: the three factors at geometry `+0x140`. A rider's live scale equals its CHARDB model size x 0.01
  (Zoe 0.85) **(PS2)**.

## Clip data and local sampling

- Clips are compressed packets; rotations are stored as spherical coordinates and converted to quaternions
  (block `0x0030FC7C`..`0x0030FD9C` inside `0x0030F2B0`, and a copy at `0x0030EFE0` inside the single-bone path
  `0x0030ECD8`).
- `0x00311318` finds the 30 Hz segment for a time; `0x00312C20` samples a scalar channel.
- Duration = (u16 frame count - 1) x float(1/30), a multiplication (with EE toward-zero rounding), not a
  division by 30.
- `0x00314418` emits the model's sampling descriptors (clip, time, priority, mask per active sequence);
  `0x00313D70` computes the fade weights.
- The local sampler `0x0030F2B0` intersects geometry `+0x150` with each sequence's mask; at `0x0030F4F4` it also
  intersects geometry `+0x158` when rider `+0xB1C` is nonzero. This explains Psymon's antenna staying in bind
  pose at the race start **(PS2)**.
- Time step: slots advance by dt = timeScale x float(1/60), scaled by slot rate x sequence rate in that order.
- `0x0030ECD8` samples a single bone of a clip; the hard-crash entry `0x0010EB30` uses it to bake the new clip's
  root.

## World pose (`0x0011EB98`)

`0x00310200` scales each local translation by body scale and composes quaternion and position with the parent.
World FK runs from the physical root (rider `+0x110`/`+0x120`) in world space, with world-space lateral and
contact vectors **(PS2)**.

### Root presentation (`0x0011FA10`, `cRider_doLeanPoseAdjust`)

- Cancels lean against twice the brake magnitude.
- Rotates around the board-local pivot and applies roll.
- Offsets along rider `+0x3B0` by 45 cm x turn x body scale.
- In `0x0011EB98` the presentation lift `+0x2C8` is added to the body root only; the board root keeps the
  unlifted presentation.

### Airborne and crash roots

- In the air (control 5), `0x00134DD0` runs first with the current animated local bone selected by rider
  `+0x89C`, times body scale, then `0x0011FA10` and the body lift. The pivot add/subtract is always performed,
  even with zero angular input.
- The air-motion code at `0x00139A70` (inside `0x00139A20`) copies the retained board-root up (`+0x180`) into
  `+0x370` before air motion; the airborne board lift uses it. Departure ticks still use the ground normal and
  the board normal from before the `0x0013F2E4` update, and the air keeps the last ground `+0x3B0` **(PS2)**.
- During a crash there is no `0x00134DD0` root; the crash-contact displacement from `0x00106538` is committed to
  the cached bones through `0x00310530`, like body/landing translation **(PS2)**.

### Board alignment, lift and leg IK

- The block `0x0011ED80`..`0x0011F148` inside `0x0011EB98` aligns the board: `+0x2BC` weight, `+0x390` desired
  board-plane normal, `+0x31C` lift, `+0x370` contact normal; the board child is rebuilt after the adjustment.
- `+0x390` is a separately filtered normal (not the temporary force-leaning normal). The pose uses the old
  value; afterwards the site at `0x0013F2E4` inside `0x0013F178` updates it:
  `n390 = normalize(n390 + 0.5 * n370)`.
- Leg IK is gated by `+0x318`. The bindings at `+0x8E0` and `+0x910` hold thigh/shin/foot bone indices and the
  board-relative foot translation and quaternion; `0x0011F3D8` solves the two links. Partial IK weights (partial
  quaternion blending) exist; their behaviour is not covered here.
- Presentation-lift target (block `0x0013E144`..`0x0013E228` inside `0x0013D818`): driven by the old/new position
  projected onto the previous filtered board normal, clamped by crouch, multiplied by body scale; animation
  classes 10/4/5 or semantic 22 suppress it. The current value is advanced by `0x001211F8`.
- `+0x31C` is an independent oscillator: a phase/amplitude update and the cosine polynomial `0x0031C040`.

## Playing, fading and querying

### `0x003128E8` (`cRiderAnimBase_play`)

- Resolves the semantic through `0x00104CF8`/`0x00311710` (may draw from the shared RNG), then creates or
  revives a sequence with `0x00311F00` on the definition's channel, with the channel priority from
  `0x0048D808`.
- Leaf 519 is the no-play sentinel: `0x003128E8` returns 438 and leaves the requested channel unchanged.
- The landing calls in `0x0013A968`/`0x0013A8F8` pass `a2` = 0, so `0x00311F00` revives a still-fading copy of
  the same clip, keeping its time and weight, instead of restarting it **(PS2)**. (That a nonzero `a2` forces a
  restart is unconfirmed.)
- `0x00311F00` gives every new sequence the pending rate at animator `+0x1C`; `0x00311F00` -> `0x00314518`
  initialises one enabled, non-looping primary slot with time 0, slot rate 1 and weight 1, plus the usual
  fade/root/mirror setup.
- `0x00311F00` converts each authored event's first 16-bit word (a frame number) to time with x float(1/30);
  the event's ordinal gives its flag bit, the second word does not. Completion uses event bit 63; no implicit
  bit-63 end event is installed for driver kind 11 with completion kind 0 (whether the rule depends on the kind,
  the completion kind or both is unconfirmed).

### Pending rate (animator `+0x1C`)

- It is the rate for the *next* request, not the current sequence's rate. A new play request consumes it and
  resets it to 1; if the selected semantic does not change, a newly computed value survives to a later request.
- `0x00311A50` (placement) resets it to 1. The air selector sets it and then plays with the default argument;
  the in-flight switch passes it on.
- The finish reaction plays at 0.75 inside a transient `0x0012C678` window, after which the rate returns to 1.
- The charged-release rate is -1 when there is neither spin nor flip (meaning of -1 unconfirmed).

### Requested versus playing

- `0x00312AA0` and `0x00311AE8` read the requested semantic words (animator `+0x00`..`+0x14`).
- `0x00311B20` and `0x00312AE8` look at the *first playback sequence* of a channel, which differs from the
  request while fading. `0x00311B20` calls `0x00314760` (`cAnimSequencer_getSequence`) with list index 0 and
  gets the first sequence even when it is fading out. `0x00312AE8` returns its `+0xC0` completion flag.
- Grab control writes a rate at `0x00135480`/`0x00135488` and `0x00135554`/`0x0013555C` (inside `0x001352A8`)
  into that one sequence's `+0x90` only; outgoing crossfade sequences keep their rates.

### Duration query (`0x00312790`)

Resolves the semantic through `0x00104CF8` and `0x00311710` first (so it can consume an RNG draw for weighted
semantics), then returns (frame count - 1) x float(1/30). Leaf 519 returns +0.

### Weighted variant lookup (`0x00311710`)

- One leaf: returned directly, with no eligibility test, no weight and no RNG draw.
- Several leaves: exactly one shared RNG draw, even if only one leaf is eligible.
- A leaf is eligible when `(allowed & required) == required`. Weights are uint32.
- Selection: `r = draw % sum`; for each eligible leaf `r -= weight`; pick the first leaf where the signed `r <= 0`.
  The boundary is inclusive, so a zero-weight first leaf is picked when the draw is 0.
- The allowed mask comes from `0x00104CF8`: on the normal path (animator `+0x60`) rider `+0x364`; on the
  alternate path (animator `+0x64`) `+0xCD8` of that owner (the front-end preview slot keeps its variant mask
  there).
- The draw happens at request time, before the sequence is created or faded; choices are not cached per
  semantic.
- The shared generator's state is at `0x004FF030`. Computer riders draw from the same generator between the
  human's controller-phase draws and its motion-phase draws, so the random variants (landing 62, crash landings,
  bob, head checks) depend on the whole field **(PS2)**.

### Events, markers and seek

- `0x003135B0` advances a slot and processes its events: `0x00313868` detects interval crossings, `0x00313938`
  tests seek-time equality and `0x003139A8` handles completion. Reverse playback and multiple wraps per step are
  handled. Advancing a slot other than the primary does not change the sequence's completion, marker or
  raised-event flags.
- Setting a time directly (drivers) marks a seek (`+0xC4`).

### Completion dispatch (`0x00312490`)

Traverses the six channel lists and collects every node flagged with event 63 (`0x00312500`..`0x00312510`),
then dispatches callbacks for that fixed set (`0x00312540`..`0x00312568`). A node created by a callback is not
dispatched in the same pass, and clearing a flag after collection does not cancel an already collected callback.
What happens when a callback destroys another pending node is not established.

### Fades and removal

`0x00313800` advances a sequence fade; when a removal fade completes, `0x003145F8` removes the sequence.
`0x00312BD0` starts an ordinary crossfade; `0x00312B18` replaces a sequence while keeping its weight/fade. The
front-end idle change observed on the PS2 is consistent with a linear 0.23 s crossfade **(PS2)**, the same as
the 0.23 s blend time of the air-adjust definitions. `0x00313A10` (`cAnimSequence_fadeWeight`) is in the same
file; its relation to `0x00313D70` is not covered by these notes.

### Stance reversal, heading offsets and mirroring

- Each sequence keeps its own root offsets (`+0x60`/`+0x70`) and mirror flag (`+0x80`). Mirrored playback uses a
  per-bone mirror source mapping from the model data and signed quaternion/translation component selectors.
- `0x00115168` (stance reversal): toggles `+0x320`; rotates existing sequences with `0x00311B48`
  (`cRiderAnimBase_changeHeadingOffset`, called with pi) / `0x00311BF0`
  (`cRiderAnimBase_changeOrientationOffset`); sets the published default root rotation (sin/cos of -pi/2 or -0)
  and mirror flag used by new sequences; negates `+0x3A0`/`+0x3B0` and the turn, animation-turn, lean, brake and
  `+0x280` values.
- `0x00311B48` applies the rotation to the roots with the angle negated.

## Drivers

### Ground cycle (kind 4) and five-way turn selection

The cruise cycle blends five clips, HS2, HS1, forward, TS1, TS2 (heel-side/toe-side), through
`0x00104178`/`0x00103E28`. The input is the animation-turn filter `+0x1FC`, not the physical turn `+0x1F0`.
Switching the primary clip keeps the normalised phase; the second slot's clock is synchronised to the primary
after it advances. (That these two functions are the kind-4 driver is unconfirmed.)

### Rail balance (kind 5)

Rail cycle semantics 18/19/20 blend `RS[_FS|_BS]_BAL_R`, `_FWD` and `_BAL_L_CYC` by weight on rider `+0x238`.

### Prewind (kind 7, `0x00104358`)

Writes `slot0.time = max(|prewindSpin|, |prewindFlip|) * slot0.duration`, marks a seek, then advances only the
sequence fade. Elapsed time and playback rate are not used.

### Air adjust (kind 11, `0x001043F8`)

`0x001036A0` reaches it through entry 11 of `0x00456950`. It handles semantics 297..304 with two slots and does
not free-run the primary clip. Clips (basic-bank indices):

| Semantic | Primary `AADJ_INTO_ROT_*` | Secondary `AADJ_ROT_*_CYC` | Direction |
| --- | --- | --- | --- |
| 297 | 135 | 143 | L |
| 298 | 141 | 149 | FWDL |
| 299 | 138 | 146 | FWD |
| 300 | 142 | 150 | FWDR |
| 301 | 136 | 144 | R |
| 302 | 140 | 148 | BWDR |
| 303 | 137 | 145 | BWD |
| 304 | 139 | 147 | BWDL |

- Definitions 297..304: class 1, kind 11, completion kind 0, channel 2, blend 0.23 s (float 0.230000004),
  first fade-in 0, end fade-out 0. The 16 clips have no events.
- The generic path resolves the primary leaves [157, 163, 160, 164, 158, 162, 159, 161]. The driver reads its own
  secondary leaves [165, 171, 168, 172, 166, 170, 167, 169] directly from the loaded lookup, without an RNG
  draw; for any other semantic it falls back to leaf 165.
- Each tick: `0x00313C50` assigns slot 1's clip and duration. If slot 1 was disabled it is initialised (time 0,
  rate 1, weight 1, enabled); an enabled slot keeps its time and rate even when the clip changes. Slot 1 is set
  looping. Slot 1 is created by the first driver update, not at sequence creation.
- With `m = clamp(max(|+0x28C|, |+0x298|), 0, 1)` from the filtered current values:

  ```
  w1 = 0.75*m + 0.25        // secondary weight
  w0 = 1 - w1               // primary weight
  slot0.time = m * slot0.duration   (seek via 0x00313CF0, seek pending set)
  ```

- Only slot 1 is advanced (`0x003135B0`, dt = timeScale x 1/60, looping), so the sequence's completion, marker
  and event flags are untouched. The primary is not advanced afterwards.
- The fade is advanced once with the same dt (`0x00313800`); a finished removal fade requests `0x003145F8`.
- The driver keeps running on a fading 297..304 sequence during landing, reading `+0x28C`/`+0x298` as they
  approach the landing's zero targets at 1/60 per tick **(PS2)**.

## Ground selection (control 0)

The selector is the block `0x00131878`..`0x00131C04` inside the ground controller `0x00131620`. It runs before
`0x001211F8`, so it uses the old filtered controls; turn and crouch are the effective raw requests (after any
handplant override). The physical reversal `0x00114CC0` is done by its caller. Priority:

1. Semantic 22 stays selected; animation-turn, brake and crouch targets are zeroed.
2. Semantic 21 or a successful eligible reversal: animation-turn and brake targets zeroed.
3. Class 10 keeps its landing semantic; animation-turn target zeroed.
4. Class 5 keeps its semantic, follows the filtered physical turn, brake target zeroed.
5. Otherwise pick the ordinary unbraked or braking cycle.

All these target rates are float(1/30). Animation turn follows the old filtered turn while unbraked and targets 0
while braking. Speed thresholds (cm/s; they are round km/h values):

- Below 833.333374 (30 km/h): positive raw crouch or |raw turn| > 0.2 selects 22; a neutral request continues
  normally. The crouch input here is the command crouch axis, which is 1 while jump is held, not the jump charge
  **(PS2)**.
- Surface 4 (ice) selects 14/15; boost 8 only when tucked and |filtered turn| < 0.3.
- Other surfaces: if |animation turn| > 0.6 and |lateral z| > 0.7, a steep-slope bob is tried with exactly one RNG
  draw: an even word selects 16/17 by stance-adjusted lean sign, an odd word falls through.
- Tuck boundary `0.5 * (1 - |filtered turn|)`: below it 5; above it 8 while boosting, otherwise 7 below
  1666.666748 (60 km/h) or on surfaces 2/3, else 6.
- Braking with hysteresis: a current 12/13 stays eligible for the stopped pose up to 972.222229 (35 km/h), other
  semantics up to 694.444458 (25 km/h). Above the threshold, or with |brake| < 0.8, select 11; otherwise 12/13
  by brake sign and reverse stance.
- 16/17 are class 5; the other ordinary cycles are class 7.

### Reaction requests (`0x00115B58`) and upper-body reactions (`0x00115D48`)

Inside `0x00131620`: turn/crouch targets, then `0x00115B58` (called at `0x00131868`), then `0x00115D48` (at
`0x00131870`), then the main selection.

- A request is rider `+0x358` (kind) / `+0x354` (due logic tick), made by `0x0010E028`. `0x00115B58` plays it on
  channel 1 with the `+0x8C8` mask when the main class is not 5 or 10 and channel 1 is free, and drops it after
  180 ticks. Table `0x00456CC0`: kinds 1-3 -> 315, 4 -> 314, 5/6 -> 318 if |`+0x1FC`| < 0.75 **(PS2)**.
- Requesters: crash-control exit `0x0012E690` (kind 4 on even logic ticks; a voice query at `+0x6C0` is involved,
  unconfirmed), `0x0010E098` (kind 5), `0x001200D0` (kind 6), `0x0010E910` (kinds 1-3, race position),
  `0x0012C678`.
- `0x00115D48` (head checks and idle): updates its timer, draws shared RNG words, selects a semantic and bone
  mask, and stamps six peer cooldown timestamps (one per rider in the race, unconfirmed). Its second
  percentage test is always true but still consumes a draw. Cooldowns count logic ticks of `0x001298C8`
  (600 means 600 ticks) **(PS2)**; the idle clock `+0x35C` advances by float(1/60). Head checks 316/317 map
  to single leaves; 319..321 have weighted variants.
- `0x00115D48` does not run on start, soft-reaction (control 3), crash-exit or landing ticks **(PS2)**.

### Soft collision reactions

Soft scenery impacts enter control 3 through `0x00105D98` -> `0x00108388`, which selects the reaction clip;
control 3 (`0x0012E778`) sets its targets and transition requests and waits for the primary sequence's `+0xC0`
completion. Clips 55..60 keep class 6 through the recovery tick; then control 0 selects its ordinary cycle.

## Charge, prewind and release

- Prewind controller `0x0012E9B8`: branch 1 handles class 10, branch 2 semantic 21; when `+0x328` and `+0x2DC`
  are both 0, branch 3 runs the reverse turn `0x00114CC0`, which plays 21 and flips the stance. The index-21
  turn/brake targets are skipped while the prewind is held.
- Prewind direction: the classifier `0x0012EE30` and the five-style table `0x0043D788` select the prewind, for
  both stances; the 23 prewind definitions are semantics 245..267. Selection uses the retained (pre-approach)
  currents; `0x001211F8` approaches the prewind pair once per tick, also while fading **(PS2)**.
- Riding off an edge while holding jump keeps control 2 and its prewind. Releasing in the air enters control 5
  without another launch impulse or predictor reset; landing while still holding keeps control 2 and uses the
  impact gate for the landing animation. Held-air ticks also run the crouch/brake, prewind and turn targets.
- A crash from control 5 zeroes the prewind triplets (`0x00134CB0`); crashes from controls 3/4 keep the
  `0x0012F620` rates.
- Charged release: the table `0x0043D840` with the same `0x0012EE30` classifier picks one of five styles; release
  semantics are 269..286 (class 9), with completion-kind-2 replacements 289..296. `0x00133128` computes the
  release playback rate into sequence `+0x90`.

## Air selection (control 5)

The selector is the block `0x0013437C`..`0x00134C6C` inside `0x00133308`, after the angular and scoring updates
and before timers, control filters and pose sampling. It uses the phase value held from `0x0013364C` (before the
angular update) and the *effective* spin/flip controls (after mode substitution, direction snapping and phase
handling, kept on the caller's stack). Current semantic and class are read after the grab lifecycle has applied
its requests.

First, each call writes the `+0x298` and `+0x28C` targets from adjust spin and adjust flip divided by 1.7453294
(100 degrees in radians), with rate float(1/6); the current values change only in `0x001211F8`. Then, in order:

1. An active grab or semantic 288 keeps the current animation.
2. Nonzero angular adjustment chooses 297..304 from the filtered adjustment direction and stance, unless a
   class-9 entry clip is still current.
3. A phase 3 -> 0/1 start chooses 269..276 from the effective input direction, with a playback rate derived
   from the stat and angular rate.
4. Phase 0 with both targets 0 selects 287.
5. Phase 1 keeps its clip unless the extension, class-2, unfinished-rotation and sequence-completion gates allow
   293..296. A failed phase-1 gate returns directly, without the landing-duration query.
6. A new phase 2 maps the current directional semantic through `0x004581A0` to 306..313 or 287, with a rate
   from the remaining rotation and the clip duration.
7. Otherwise the trajectory-based 287 <-> 305 landing transition is evaluated (prediction-driven branch
   `0x00134B80`..`0x00134C3C`). This path can query 305's duration even when the semantic stays unchanged.

"Main completed" is the sequence `+0xC0` flag from `0x00312AE8`, not an event marker. The selector itself draws
no random numbers; all observed mappings 268..313 have a single leaf, but the duration queries keep their order.

### In-flight stance switch (`0x00135BE0`) **(PS2)**

- `0x00133308` calls `0x00135BE0` in phase 3 (before the D-pad input, which a switch then skips) and in an
  unfinished phase 2, when no grab is active and the channel-2 request is not 288.
- The test `0x00114DB8` needs predictor status 1 or 3. It compares the last pose's board-root frame (`+0x170`
  forward, `+0x180` up) with the landing normal `n` and heading (predictor `+0x20`/`+0x10`, or rider
  `+0x180`/`+0x1E0` on surface 18 or per a table `+0x44` field). No switch when `up.n < 0`, `forward.velocity >
  277.78`, `forward.n > 0.9`, or projected forward . projected heading > the constant at `0x004A0EA8` (-0.0).
  The air-adjust spin (up to 100 degrees) is what turns the frame past 90 degrees.
- On a switch: `+0x110` moves by `rotate(q, 2 * (scaled pivot xy, 0))`; then `0x0011E098`
  (`cRider_updateOrientationImplicit`), `0x00115168` (stance reversal) and `0x001135B8`
  (`cAirPredictor_startLaunchIntoAir`, a new flight; the predictor status is 0 for a few ticks, pausing landing
  alignment). `0x00135BE0` then wraps the total spin by pi into [-pi, pi), negates the four flip fields and plays
  288 (clip 0x7500, 0.3 s, completion kind 1 -> 287). While 288 is requested the selector keeps the adjust clips
  off.

### Grab lifecycle (`0x001352A8`)

- Runs before angular control; its requests apply immediately, and its active flag (class 18..20) gates the
  angular grab logic. States 0, 1, 2 and 5 are the ordinary grab; tweak/uber states 3/4 are not covered here.
- Normal grab semantics 71..85, upper-body cycles 86..91. A grab begins through marker 0, holds at marker 1 with
  main-sequence rate 0, resumes on input release, and resets through marker 3. The checks are sequential, so
  several state changes can happen in one tick.
- Playback speed (`0x00120038`): `1 + grabStat * 0.29988324642181396`.
- It issues scoring begin/end requests in a fixed order; the caller carries out the scoring and boost effects
  (`0x00119708`/`0x001197D8`, `0x0010E098`).
- Completion kind 5 ends the grab (see the completion table).

### Landing

- Landing semantics are 61..67 (plus switch 21); 62 has three weighted variants.
- The landing crash variant 351/352/353 is chosen from an RNG word `& 3` at `0x0013A14C` inside `0x00139C88`.
- Landing requests are not forced (see `0x003128E8`).

## Secondary motion (`0x00120378`) **(PS2)**

- Runs after the controller; velocity (`+0x1E0`) and stance (`+0x320`) are the post-controller values read in
  the `0x001211F8` pass.
- Every tick the first sequence of channels 3..5 gets rate
  `clamp(|v - surfaceV| / 1666.67, 0.5, 2.0)` from the pre-motion velocity.
- When `logicTick % 6 == rider+0x86C`, each enabled channel picks one of seven `SH_*` semantics from the wind
  (computed with the cached bone at `+0x8A8` and the factors `+0x950`/`+0x960`): still if speed <= 138.9 cm/s,
  up/down if |z| > 888.9, side if |x| > 416.7, else fore/aft.
- The still semantic is 0x19B + 7c (c = secondary channel, unconfirmed) and does not need the cached bone, so it
  can be requested on logic tick 0 (411 for channel 0).
- Secondary channel c appears to play on animator channel 3 + c (unconfirmed; `SH_RIGHT_CYC` with hair part 19
  is on channel 3).

## Front-end preview animation

- Preview slots: `*(*(0x004A28A8)+0x7C)` (gp-0x848) + 0xB0 + 0xCE0 x player. Slot fields: `+0x0` character,
  `+0x8` geometry, `+0xC` animator, `+0xC30`/`+0xC40` root position/quaternion, `+0xCC8` model shown,
  `+0xCD8` variant mask. Every bone slot is active, the binds equal the race binds for shared bones, and the
  geometry is unscaled **(PS2)**.
- The preview adds the cinematic parts: head (file 5, 36 morphs), eyes (file 6, bones `eye_r`/`eye_l`), left
  hand (file 8, 27 morphs) and right hand (file 9, 27 morphs). Front-end clips carry one stream per part file:
  file 5 has 36 channels, files 8/9 have 27 morph channels, file 6 drives the eye bones. Morph weights act
  linearly and unclamped on vertex positions before skinning (unconfirmed for the PS2 renderer code).
- PS2 model morph data: VIF `UNPACK V4-8` packets after each vertex chunk, {count, 0, 0, 0} then
  {dx, dy, dz, slot} with slot = 3 x chunk vertex; vertex positions are V3-32 floats in cm. A fit against the
  GameCube twins gives about 4 mm per PS2 unit (fitted, unconfirmed).
- Timing **(PS2)**: the clip plays on the sequence reached from the list head at animator-side `+0x14` (with
  8-byte {count, head} sequencers this would be channel 2's head, unconfirmed), with clip at `+0x4` and time at
  `+0x8`. Cross starts the cheer (435) at t = 0; it is held while the model is hidden (`+0xCC8` = 0) and its
  clock runs from the frame the model appears. At the cheer's end the idle restarts at t = 0; the sequence list
  during the change is consistent with a linear 0.23 s crossfade. Rider Details and the return to Setup
  Character restart the cheer. The idle is `FE_GEAR_<X>_CYC` (`FE_GEAR_MAC_CYC` has no face stream).
- `FE_A_CYC` (436) is played by `0x00184C60` in the Ubertrick Setup state (vtable `0x0046CCC8`), with the model at
  (-228, -205, 63).

## Semantic reference

| Semantic | Meaning |
| --- | --- |
| 5 | Ordinary cruise cycle (also the target of completion kinds 3/4). |
| 6, 7, 8 | Tucked cycles: 6 fast, 7 slow or surfaces 2/3, 8 boosting. |
| 11 | Braking while moving. |
| 12, 13 | Stopped brake pose (brake sign, stance). |
| 14, 15 | Ice. |
| 16, 17 | Steep-slope bob (class 5, RNG). |
| 18, 19, 20 | Rail balance cycles (kind 5). |
| 21 | Reverse turn / switch landing. |
| 22 | Slow crouch or low-speed turn. |
| 55..60 | Soft collision reactions (class 6). |
| 61..67 | Landings (62 weighted). |
| 71..85, 86..91 | Grabs, grab upper-body cycles. |
| 245..267 | Prewinds. |
| 268 | `A_INTO_AIR`. |
| 269..286 | Charged releases (269..276 chosen by the air selector). |
| 287 | `A_CYC_1`/`A_CYC_2`, neutral air cycle. |
| 288 | In-flight stance switch. |
| 289..296 | Release completion replacements (293..296 are the phase-1 extensions). |
| 297..304 | Air adjust. |
| 305 | `A_OUTOF_AIR`. |
| 306..313 | Phase-2 directional clips (via `0x004581A0`). |
| 314, 315, 318 | Requested reactions (314 also the get-up reaction). |
| 316, 317, 319..321 | Head checks. |
| 351..353 | Landing crashes. |
| 411 | Secondary-motion still, channel 0. |
| 435, 436 | Front-end cheer, `FE_A_CYC`. |
| leaf 519 | No-play sentinel (`0x003128E8` returns 438). |
