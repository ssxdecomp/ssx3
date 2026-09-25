<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: Not yet split (asm/ catch-alls)

Functions that fall inside the `asm` catch-all segments of `config/ssx3_us.yaml` (not yet assigned to a
source file). The heading is the segment's splat name (file offset); vram = offset + 0xFF000.

## `asm:sce/crt0`

Segment `0x00100000`-`0x00100218`.

- **`0x00100008`** - ELF entry point of SLUS_207.72 (32-bit little-endian MIPS ELF, no symbol table). Single load segment at VA `0x00100000`: 3,820,532 file bytes, 4,451,036 memory bytes; main .text is 3,334,176 bytes, .vutext 59,360 bytes. *[static]*

## `asm/1218.s`

Segment `0x00100218`-`0x0010C4F8`.

- **`0x00100680`** - NPC ground behavior 'Cruise' (used by all five NPCs at race-ready). *[PS2]*
- **`0x001009E0`** - NPC ground behavior 'Jump' (glide slots 1/3/4). *[PS2]*
- **`0x00100B90`** - NPC ground behavior 'Designated'. *[static]*
- **`0x00100F88`** - NPC ground behavior 'Peer' (glide slots 2/5). *[PS2]*
- **`0x001013A8`** - Rider-manager pass run after the section pass, just before the tick counter increments. *[static]*
- **`0x00101B60`** - Course section activation pass for streamed locations, run in the world pass after all riders: for instances entering the activation octree cells (one octree holds every resident location) runs slot-1/3 programs via `0x0030A3A0` -> `0x0030A298`, in section order. Instances enter the octree on read completion; rescan on 6->1 / 8->2, 5->7 drops the list. In free ride slot-1 programs kill challenge reset planes, mode fences and start-mode colliders (builtin43 kind mismatch -> DeadNode). Visual-RNG draws: flag grid builds (4 per new flag slot), set-piece emitter seeds (`0x0036CCB8`, `0x00370DC8`), builtin3 key8/key6; also starts LiveComps. *[PS2]*
- **`0x001032C0`** - Adds an entity to the renderer dynamic list and sets instance flag 0x100 (0x200 is renderer bookkeeping). *[static]*
- **`0x00103308`** - Drops a location's instances from the section activation list without running leave handlers; tears down stage programs and entities. *[static]*
- **`0x00103578`** - Contains the kind-8 animation driver entry below. *[static]*
  - `0x001037E0`: Kind-8 animation driver entry block (dispatch table `0x00456950`[8]); calls `0x001045D8`. *[static]*
- **`0x001036A0`** - Per-sequence animation driver dispatch: driver kind from state table +4, jump table `0x00456950`[16] to the per-kind driver (e.g. kind 11 -> air-adjust driver `0x001043F8`). *[static]*
  - `0x00103700`: Base of the driver-kind case blocks: case = `0x00103700` + 0x1C*kind. *[static]*
- **`0x00103918`** - Animation completion dispatch: completion kind from state table +8, jumps via `0x00456990`; the result is stored in the channel's requested slot. Remove (kind 0), keep (kind 2 when the semantic is outside table `0x004569E0`), replace via `0x00312B18` (kinds 1,2,3,7,8), play via `0x00312BD0` (kinds 4,5,6,9,10). *[PS2]*
  - `0x00103978`: First case target of the completion jump table `0x00456990`. *[static]*
  - `0x00103990`: Second case target of the completion jump table `0x00456990`. *[static]*
  - `0x00103A68`: Last case target of the completion jump table `0x00456990`. *[static]*
- **`0x00103AA0`** - Animation sequence event latch: latches every newly reached sequence event with the clip id. *[static]*
- **`0x00103BE0`** - Two-way seek-by-magnitude animation driver helper: amount < 0 -> slot 0 = clip t0 at -amount*duration, else clip a3 at amount*duration; no clock advance. Used by driver kinds 9 and 10. *[static]*
- **`0x00103CC8`** - Three-way weight-blend animation driver helper (animator, sequencer, seq, f12 timeScale, f13 amount, a3 neg, t0 centre, t1 pos): centre clip in slot 0 (weight 1-side, loop 1), positive/negative side clip in slot 1 weighted by |amount| and phase-locked (slot 1 time = slot 0 normalized*dur via `0x00313CF0`). Slot 0 clock via `0x003135B0` by rate*seqRate*timeScale/60; fade `0x00313800`; `0x003145F8` on stop fade. Used by the rail cycle driver kind 5 (`0x00104238`) and driver kind 15. *[static]*
- **`0x00103E28`** - Five-way cycle selection/blend helper used by animation driver kind 4 (`0x00104178`). *[static]*
- **`0x00104110`** - Animation driver kind 3. *[static]*
- **`0x00104178`** - Animation driver kind 4: normal-ground five-way cycle selection (HS2, HS1, fwd, TS1, TS2) via `0x00103E28`, driven by the +0x1FC animation-turn filter (not +0x1F0). Switching the primary preserves normalized phase; the secondary clock is synced after the advance. *[static]*
- **`0x00104238`** - Animation driver kind 5: rail balance cycle, three-way weight blend via `0x00103CC8` of RS[_FS|_BS]_BAL_R_CYC / _FWD_CYC / _BAL_L_CYC by rider+0x238 (rider = animator+0x60), negated when rider+0x320 (switch stance) is set. Semantic 18 -> leaves 65 RS_BAL_R / 63 RS_FWD / 64 RS_BAL_L; 19 -> 68/66/67 (RSFS); else 71/69/70 (RSBS). *[static]*
  - `0x00104250`: Negates the balance amount (neg.s) when rider+0x320 (switch/reverse stance) is set. *[static]*
- **`0x001042A8`** - Animation driver kind 6. *[static]*
- **`0x001042E0`** - Animation driver kind 10: rail Uber BAL_L/BAL_R seek-by-magnitude via `0x00103BE0` with amount rider+0x238 (not negated). Semantic 218 -> leaves 362/363 (GRIND1), 226 -> 371/372, 234 -> 380/381, else 389/390 (GRIND4). *[static]*
- **`0x00104358`** - Animation driver kind 7: sets slot 0 time = max(|prewindSpin|, |prewindFlip|) * slot0.duration (marked as a seek); only the fade advances. *[static]*
- **`0x001043F8`** - Air-adjust animation driver (kind 11) for air adjust clips 297..304; also runs on fading sequences. Per tick: sets slot 1 clip/duration via `0x00313C50` (secondary leaf, fallback 165), loop on; m = clamp(max(|rider+0x28C|, |rider+0x298|), 0, 1), filtered; slot 1 weight 0.75*m + 0.25, primary weight the rest, primary time m*duration with seekPending = 1. Only slot 1 advances (`0x003135B0`, dt = timeScale/60), leaving completion/marker flags alone; then one fade step, finished removal fade requests `0x003145F8`. No RNG. *[PS2]*
- **`0x001045B8`** - Animation driver kind 12. *[static]*
- **`0x001045D8`** - Animation driver kind 8 (start pose): seeks slot 0 to duration * owner+0x2A0 and only advances fades. *[static]*
- **`0x00104660`** - Animation driver kind 9: half-pipe balance seek-by-magnitude via `0x00103BE0` (semantics 40/45, amount rider+0x244). Semantic 45 -> leaves 352/353 HPHS_BAL_THROUGH/REFLECT, else 346/347 HPTS. *[static]*
- **`0x001046B0`** - Animation driver kind 15 (board-press hold clips 28/36): three-way blend via `0x00103CC8` by clamp(2*(+0x274) - 1). *[static]*
- **`0x00104728`** - Animation driver kind 14 (press clips 24/32, 25/33): seeks from +0x268 (24/32 seek +0x268, 25/33 seek clamp(1 - +0x268)) and runs only the sequence fade. *[static]*
- **`0x001047F0`** - Animation driver kind 13 (pivot clips 29/30, 37/38): sets the slot 0 clock from |+0x280| (29/30 seek |+0x280|, 37/38 seek 1 - |+0x280|) and runs only the sequence fade. *[static]*
- **`0x001048C0`** - Animation driver kind 0. *[static]*
- **`0x00104940`** - Animation driver kind 1. *[static]*
- **`0x001049C0`** - Animation driver kind 2 (looping). *[static]*
- **`0x00104A40`** - Animation completion kind 1 handler: replaces with semantic 287 via `0x00312B18`, keeping weight/fade (e.g. IntoAir -> A_CYC). *[static]*
- **`0x00104A60`** - Animation completion kind 2 handler: replacement (e.g. for release clips 289..296); keeps the sequence when the semantic is not in table `0x004569E0`. *[static]*
- **`0x00104B48`** - Animation completion kind 5 handler: plays via `0x00312BD0`, fading grabs into semantic 287 (alternate 436 when animator+0x64 is set). *[static]*
- **`0x00104B78`** - Animation completion kind 3 handler: replaces with semantic 5. *[static]*
- **`0x00104B98`** - Animation completion kind 7 handler: replaces with semantic 3 via `0x00312B18`(..., 3). *[PS2]*
- **`0x00104BB8`** - Animation completion kind 8 handler: replaces with semantic 19 (the Uber OUTOF clip) via `0x00312B18`. *[static]*
- **`0x00104BD8`** - Animation completion kind 9 handler: moves latched bit 63 into the raised flags (`0x00144670`) and plays 28 or 36 via `0x00312BD0`. *[static]*
- **`0x00104C18`** - Animation completion kind 4 handler: clears end flag 63 and plays semantic 5 with an ordinary crossfade (`0x00312BD0`). *[static]*
- **`0x00104C38`** - Animation completion kind 6 handler: plays rail cycle 20 for entry 69, 19 for 70, else 18 via `0x00312BD0`; the finished entry clip stays and fades. Used by air rail entries 68/69/70 and rail spins 49..54. Not the kind-7 handler `0x00104B98` (the two were once confused). *[PS2]*
- **`0x00104C80`** - Animation completion kind 10 handler: requests semantic 434. *[static]*
- **`0x00104CA0`** - Animation completion kind 0 handler: removes the finished sequence (requested slot -> 438). *[static]*
- **`0x00104CC8`** - Animation routine that calls the animation event sound dispatcher `0x00289B18`. *[static]*
- **`0x00104CF8`** - Semantic-to-clip resolution for an animator, filtering variants by the semantic mask of animator+0x60 rider +0x364 (or the alternate animator+0x64 actor +0xCD8). Used with `0x00311710` by generic sequence init and the duration query `0x00312790`; can consume the shared RNG for weighted variants (all observed semantics 268..313 have one variant). *[static]*
- **`0x00104E70`** - Instance contact query and selection, part of the instance-contact phase with `0x00105398`/`0x001057B8`: filter-1 body query `0x00334458`(rider+0x860 list, query, capacity 64, t0=0), contact ranking, unique instance list and priority-normal aggregation. Writes distinct instance+0x78 IDs to rider+0x5B8 (ends with 0xFFFFFFFF). Ranking: node priority (flag bit0 and value != 0), sign of dot(contact-center, normal), |distance - radius| (`0x0032F8C0`), unsigned resource ID. With >= 2 contacts sums priority normals from `0x004FF120`, normalized if length > 0.001. Calls entity vtable+0x154; returns packet +0x40 depth or -1. *[PS2]*
- **`0x00105398`** - Instance-contact phase, the collision step of the rider post stages, run before the rider pairs and skipped in control 9: hips/rail contact `0x00106F78` first, then a filter-1 instance query (`0x0032F650` mode 1 -> `0x00104E70`) and response against solid surface -1 scenery, pickups and scripted entities; stops unless depth >= 0. Normal projected off rider+0x370 when `0x001231A8` holds, else off caller a1. Node flag bit1 with !(instance+8 & 0x2000) copies hit/record to rider+0x9E0/+0xA60; flag bit0 calls the response `0x001057B8`; !(flags & 0x2000) calls contact audio `0x00296088`. Callers `0x0013F178`, `0x00139C88`, `0x00137860`, `0x00138640`, `0x0013BFA8`. *[PS2]*
- **`0x001057B8`** - Instance contact response: soft collision, rigid push/bounce, entity mass impulse, air bounce counting or land-on-top (via `0x0010E910`). Node value 0 -> soft collision `0x00108388` and return. closing = max(0, n.(hit+0x20 - v)); r = clamp(node+4, 0, 1). Static or rigid entities (entity vt+0x74, `0x00355420`): push n*(depth*1.1) via `0x00106538`, impulse = closing + clamp(r*closing, 55.5556, 1388.8889), `0x001065B0` in motion 0, then `0x0011E098`; other entities use a mass formula. Air adds (2.5 - up.n)*max(n.z, 0.2) to rider+0x3F4 below 833.33 cm/s. Then v += n*impulse, reaction `0x00105D98`(rider, record, hit+0x4C) and a predictor restart `0x001135B8`. *[PS2]*
  - `0x00105C30`: Instance contact rumble site: writes owner+0xDFC. *[PS2]*
- **`0x00105D98`** - Collision event notification (rider, contact record, surface): updates contact history and chooses the reaction: ignore, hazard reset, crash-in-crash, soft impact or hard crash. Control 9 is ignored before history. Updates rider+0x3E0 and +0x3F0 (+= 1 - max(dot(n, prev), 0)); surface +0x44 nonzero -> reset `0x00116120`; motion 2: another crash collision with optional predictor restart `0x001135B8`; soft grounded impact: semantics 55..60, may change manual spin with one shared-RNG draw, control 3; hard: crash `0x0010EB30` (control 8 / motion 2). Classifies with the pre-impact presentation frame rider+0x160..0x190. Also the reaction for hips/rail contacts and ragdoll body-vs-scenery hits. *[PS2]*
  - `0x00105E7C`: Obstacle contact rumble site: writes owner+0xDFC. *[PS2]*
  - `0x00105EA0`: Crash-air path (through `0x00105EEC`): in motion 2 with owner+0x30 == 1 calls `0x001135B8`(rider+0x788, pos, vel, rider+0x2E4), a full predictor restart, not just the `0x00113618` reseed. *[PS2]*
  - `0x00105EEC`: Air predictor restart call (`0x001135B8`). *[PS2]*
  - `0x00105F50`: Air predictor restart call (`0x001135B8`). *[PS2]*
- **`0x00106538`** - Rider translation (push) helper: moves the physical position (+0x110), secondary presentation offset, collision body spheres (cached +0xAA0 centres) and AABBs +0x400/+0x410, and accumulates the translation in rider+0x9D0 (committed later to cached bones, incl. crash-contact displacement). Posed bone arrays are not moved. Used by `0x001057B8`, `0x00106F78`, pair separation in `0x00107888` and the touchdown push (followed by `0x0013AA48`). *[PS2]*
- **`0x001065B0`** - Impact heading (orientation) correction after an obstacle bounce: rotates at most 20 degrees per call toward a 110 degree wall-facing limit (post-multiplied quaternion convention). Runs only in motion 0 from `0x001057B8` / `0x00106F78`; followed by `0x0011E098`. *[static]*
- **`0x00106828`** - Builds the rider's body spheres (+0xAA0). *[PS2]*
- **`0x00106848`** - Rail attach, tried every tick from the cruise, crouch, air and passive-air controllers (callers in controls 0-5, 11, 12). Sets v = d*min(|v|, max(|along|, 555.5555)) with v.z *= 0.1, grind style from atan2 (`0x0031C228`) of board axes vs rail (150/30 deg), rider+0x438 and audio+0x598C = surface; scores via `0x0010E910` or `0x00119D40` -> `0x0010E098`; requestMotion(4) (runs `0x0013AD20` at once), then for controls 0/4/5/11 requestControl(13), `0x00115358`, `0x001326C8`, requestControl(7); finally `0x0013ADC0`. Board-press riders stay in control 1; handplant phase 6 attaches with control 11, style 4. Applies v_before - v_after to a bound AnimTeeter (vt+0x15C). *[PS2]*
  - `0x00106D9C`: Airborne board-press arrival (+0x330 set): plays 26/34 and enters control 1 instead of 7. *[PS2]*
- **`0x00106F78`** - Hips/rail contact, first step of every `0x00105398` call: pushes the hips away from nearby grind rails the rider cannot attach to; returns 0 in motion 4. Uses the hips bone (rider+0x89C, bone 0) local Y axis and `0x00334680`(rider+0x860, hips, out, mask 1, 300). Skips if the rail is behind ((p-hips).v < -0.2*speed), > 50 cm from the clamped hips segment, or `0x00108A48` would attach. Inside 50 cm pushes e*(50-gap) via `0x00106538`, v += e*(max(0, -e.v) + 55.5556), then `0x001065B0` (motion 0), `0x0011E098` and reaction `0x00105D98`. Also snaps a bound AnimTeeter (force x60, vt+0x15C). *[PS2]*
  - `0x00107554`: Return address of the `0x00105D98` notification call; notifications with this ra identify hips/rail contacts. The result is ignored. *[PS2]*
- **`0x00107578`** - Handplant entry test and requests (control 11 + motion 5). Callers: cruise `0x00131620`, natural/passive air `0x0012F730` (optional; on failure the crouch request becomes 1), spin `0x00133308` (only when air-control +0x0C == 3). The airborne check rejects animation classes 18..20; seven reject paths; the query uses rail mask 2 within 300 cm. *[PS2]*
- **`0x00107888`** - Rider pair collision dispatcher for one initiating rider over six opponent slots, run inside each rider's `0x00121750` after `0x00105398` and before the `0x0013F358` clamp (also the contact pass of the rail post after `0x0013C140`). Caches initiator weight (`0x0011FF98`). Per slot: skip a disabled record or opponent +0x878 != 0; stamp reciprocal +0x14 checked ticks; overlap `0x00329F98`; move A by -0.55*pen and B by +0.55*pen via `0x00106538` (ground-projected in motion 0 / motion 2 submode 0); if A +0x10 < tick-3, impulses A then B (`0x00107E70`) and write +0x10 in both. The attack branch is evaluated afterwards regardless. Not the rail attach `0x00106848` (an earlier misreading). *[PS2]*
  - `0x00107BCC`: Writes the collision tick into actor+slot*0x24+0x10 (through `0x00107BD4`) after the `0x00107E70` impulses. *[PS2]*
- **`0x00107E70`** - Rider pair impulse and reaction: caps the signed impulse at +/-555.555542 cm/s, applies it to velocity, then requests a soft (`0x00108388`) or crash (`0x0010EB30`) reaction through the relationship bump/attack handlers `0x0010E228`/`0x0010E2E8`/`0x0010E3A8`/`0x0010E468`. Ignores control 10; ground-tangent projection when grounded; motion 1 / crash air reseed the predictor (`0x001135B8`); motion 2 and control 9 suppress reactions. Gate 39.995327 cm/s (uncapped); above 599.974 cm/s a crash semantic from presentation-axis dominance and the shared RNG, else soft; the knockdown cheat uses exactly the hard threshold. *[PS2]*
- **`0x00108388`** - Soft collision reaction for scenery and rider pairs: push-out, soft-collision animation semantic and entry to control 3; allowed only when the motion (`0x0011FE98`) is 0 or 4. Called by `0x001057B8` for node value 0 and by `0x00107E70` for soft pair impacts. Plays via `0x003128E8`(anim, semantic, 0, -1), an ordinary play, so `0x00311F00` inherits a fading copy of the same clip. In control 1 runs jump-out `0x00131348` first; speech via `0x002A0E70`. *[PS2]*
- **`0x001086B8`** - Board-to-rail proximity check of the rail attach test (after `0x00108A48`): builds hips/board axes, projects the hit onto the board x-axis within reach and accepts within halfWidth, else re-projects along the rail and queries again (if 1-dot^2 >= 0.001). f2 = rider+0x25C; halfWidth = 50*f2 + 30*(1-f2); reach = 170*f2 + (rider+0x330 ? 50 : 100)*(1-f2); projection clamped to +/-(reach - halfWidth). `0x00106F78` reuses its axis sequence. *[static]*
- **`0x00108A48`** - Rail attach test (would the rider grind a rail): motion must be 0 or 1; queries a rail near q = board-root bone (index at rider+0x8A0, root 22 rather than mesh bone 23) + rider+0x9D0. Rejects if dot(hit-q, v) < -0.2*|v| (|v| > 0.001); class 18 needs sequence flag bit 2 or not bit 0, classes 19/20 need bit 2 (`0x001446A0` on seq+0xB0); then the proximity check `0x001086B8`. `0x00106F78` skips its bounce when this would attach. *[static]*
  - `0x00108B1C`: Loads the -0.2 rail 'behind' tolerance from gp-0x7E34 (`0x0049B2BC`). *[static]*
  - `0x00108C28`: Code block (no own function start) that tests whether an instance resource ID (instance+0x78) is in rider+0x5B8 (up to 64 entries, stops at 0xFFFFFFFF); reached only via rider+0x6C0 vtable `0x004583A8` slot 0x1C (slot 0x18 this-adjustment). *[static]*
- **`0x0010A768`** - NPC (computer rider) input provider method, used in place of the pad provider `0x00127998`; also drives the backcountry rival. Clears the 8-byte command, runs pacing `0x0010DEF0` and time scale `0x00120090`, then dispatches per control via table `0x00456A30` (e.g. rail producer `0x0010AED8`); clears owner+0xE34 afterward when control != 5. Keeps its own state at motion owner +0xDF8, never calls the human RLE command recorder (`0x0026D178`/`0x0026D2B0`) and follows the 129 authored AI paths, separate from the 8 course-progress paths. *[PS2]*
- **`0x0010A898`** - NPC provider serialization method (common owner state, then the NPC extension); listed together with `0x0010A8E8`. *[PS2]*
- **`0x0010A8E8`** - NPC provider serialization method (common owner state, then the NPC extension); listed together with `0x0010A898`. *[PS2]*
- **`0x0010A960`** - NPC control 0 (ground) command producer: path/recovery `0x0010D1A0`, interaction decisions (`0x0010DBF0`/`0x0010DA10`), then the behavior member function at owner+0xF44: Cruise `0x00100680`, Jump `0x001009E0`, Peer `0x00100F88` or Designated `0x00100B90`. *[PS2]*
- **`0x0010AA70`** - NPC control 2 (jump) command producer. *[static]*
- **`0x0010AD78`** - NPC control 1 command producer. *[static]*
- **`0x0010AED8`** - NPC control 7 (rail) command producer, including jump-zone launches. The no-jump-zone path copies an unwritten stack word from `0x0010B980` to owner+0xE20 (observed as 0 in rail sequences). *[PS2]*
- **`0x0010B0E8`** - NPC air stop planning. *[static]*
- **`0x0010B250`** - NPC control 5 (active air) command producer; the grab release branch (remaining <= owner+0xE2C + 0.3) clears owner+0xE24. *[PS2]*
- **`0x0010B590`** - NPC control 4 (passive air) command producer. *[static]*
- **`0x0010B750`** - NPC control 8 command producer. *[static]*
- **`0x0010B790`** - NPC control 6 (start) command producer. *[static]*
- **`0x0010B980`** - NPC path/event query; does not populate its output flags on a miss. *[static]*
- **`0x0010BB18`** - NPC path/event function called by the behaviors. *[static]*
- **`0x0010BBF8`** - NPC path/event function called by the behaviors. *[static]*
- **`0x0010BD10`** - NPC path/event function called by the behaviors. *[static]*
- **`0x0010BFA8`** - NPC control/command writer called by the behaviors. *[static]*
- **`0x0010C0A8`** - NPC control/command writer called by the behaviors. *[static]*
- **`0x0010C140`** - NPC control/command writer called by the behaviors. *[static]*

## `asm/14B10.s`

Segment `0x00113B10`-`0x001172E0`.

- **`0x00113B10`** `cAI_setAIState` - Selects a new race state, retaining the previous handler; e.g. starts the race countdown (Countdown clock state). *[static]*
  - Possible mismatch with the current name: The decomp name suggests rider AI state, but our notes read this as part of the race-flow state machine (states GameInit..Shutdown, e.g. Countdown).
- **`0x00113B48`** `cAI_forceAIState` - Race state machine state selection: holds the state names and selects the enter/update handlers (GameInit..Shutdown). *[static]*
  - Possible mismatch with the current name: The decomp name suggests rider AI state, but our notes read this as part of the race-flow state machine (states GameInit..Shutdown, e.g. Countdown).
- **`0x00113C20`** - Race state update, run as the race clock pass by the rider manager `0x00128AF0`: runs the pending exit and next entry, then the selected handler; transitions requested during the update defer to the next one. *[static]*
- **`0x00113D38`** - Countdown entry code: sets the countdown tick count to 180. *[static]*
  - `0x00113D38`: Literal 180: countdown tick count set on Countdown entry. *[static]*
- **`0x00113DB0`** - Race state update that increments the game-info race ticks (+0x0C) before the rider update. *[static]*
- **`0x00113E80`** - Turn target/rate request for the control triplets (ground turn target; the board press passes a clamped CruiseTurn). *[static]*
- **`0x00113F38`** - Rail (and soft-collision) steer/balance target: rate = clamp(|input - current|*7, 0.1, 8)/60, target = input (rider+0x22C triplet). Takes RailBalance (LStickR - LStickL) unnegated, so stick left slides to screen left; the board press clamps the argument to +-0.5. Callers: control 7 `0x00131E00`, Uber `0x001365DC`, soft `0x0012E850`, prewind `0x0012EC1C`. The game has no rail balance meter. *[PS2]*
- **`0x00113F88`** - Charge (crouch) and brake target request (rider, charge, brake) with mutual exclusion. Default non-braking target is 0 or 1; rate = |target - current| * 0x3DCCCDC2 (float bits) when the gap >= 0.1, else 0x3C23D7CF. Held control 2 calls (rider, 1, 0), release (rider, 0, 0); rail control 7, Uber control 12 (after the steer target) and the board-press update call it with (0, 0). *[static]*
- **`0x00114130`** - Boost control (held, pressed): press feedback via `0x002F6AC8`(owner+0xD20, 0), meter thresholds 2/3 and 1/3 giving amount 1/0.625/0.25 in rider+0x2FC (cleared when the control word disallows boost), active drain from gp-0x7BF4 (`0x0049B4FC`), start/denied/stop callbacks (boost sounds). Control 0 (call at `0x00131844`, before animation selection `0x00131878` reads +0x2FC) passes held+pressed, control 2 held/no press, control 5 and passive air (false, false); board press feeds control-12 command bits 13/14. Paired with the meter/timer update `0x001200D0`; airborne input stops thrust while boost stays available for tweaks. *[PS2]*
- **`0x00114298`** - Jump/ground takeoff (rider, charge q): adds the launch impulse to velocity and starts motion 1 (air). q >= 0: base = speed < 972.18085 ? speed*0.35714668 + 361.203125 : 708.41425, impulse = clamp(q*q*base, 361.203125, 708.41425); q < 0 (e.g. -1 on rail loss) is a passive takeoff (impulse 0.16339834, no clamp) that sets owner+0x14 = -1 so the next landing keeps full speed. Direction: mode 4 uses rider+0x1C0, else normalize(n(+0x370) + 0.2*fwd(+0x3A0)); cap +0x2E4; half pipes (locations 11..13) skip the ground-focus launch scale. Writes/returns the camera launch value rider+0x5A4 and calls score takeoff `0x00119E38` with s1 (1 only on the ramp branch) as field +0x4. Runs before the `0x0013F358` speed clamp. *[PS2]*
  - `0x001144C4`: Rising-ramp launch branch (to `0x00114794`): slope = (n.z - cos50)/(cos70 - cos50), blend = clamp(slope*projFwd.z/sin20, 0, 0.95); blends velocity toward projected forward, then adds half the impulse along the blended direction. *[static]*
  - `0x00114660`: Ramp takeoff branch; sets s1 = 1, the score alternate flag passed to `0x00119E38`. *[PS2]*
  - `0x00114998`: Takeoff stage that stores the normalized horizontal takeoff normal into rider+0x3C0 (unconditional, +X fallback on flat surfaces); read by the chase camera for wall/launch direction. *[static]*
  - `0x00114A5C`: Vertical-wall lip launch check: a near-vertical wall takeoff (|+0x380 z| < 0.05) is scaled by 0.8 unless rider+0x2D4 patch flag 0x20 is set (BHP1 lip vert patches are authored 0x29, so keep full speed). *[PS2]*
  - `0x00114B78`: Computes (through `0x00114C6C`) the camera launch value stored at rider+0x5A4, which feeds the chase camera takeoff ramp (300..500). *[static]*
- **`0x00114CC0`** - Grounded reverse turn: when the rider travels backwards (velocity on contact forward <= -111.111 cm/s with brake 0) it pre-multiplies the physical orientation by quaternion {boardUp,0}, normalises, plays semantic 21 and flips stance together with `0x00115168`. Called at touchdown, from the normal controller at `0x001318EC`, by prewind `0x0012E9B8` (when +0x328 == 0 and +0x2DC == 0), finish phase 0 and board-press reverse; not during crouch/release, soft control, an active reverse animation or manual spin. Its result gates the ground animation selector. *[PS2]*
- **`0x00114DB8`** - Air stance-switch test, part of the in-flight switch with `0x00135BE0`: compares the board-root frame (+0x170 fwd, +0x180 up) with the predicted landing normal/heading. Needs predictor status 1/3; uses predictor +0x20/+0x10, or rider +0x180/+0x1E0 on surface 18 or table+0x44. No switch when up.n < 0, fwd.vel > 277.78, fwd.n > 0.9 or projected fwd.heading > *(0x004A0EA8). *[PS2]*
- **`0x00115168`** - Stance flip: toggles rider+0x320, rotates animation roots by pi (`0x00311B48`(anim, pi)), resets root/mirror (anim+0x30 = `0x004FF130`, anim+0x40 = sincos(-pi/2 or -0) about `0x004FF160`, anim+0x18 = +0x320), and negates contact forward/lateral +0x3A0/+0x3B0 plus the current/target pairs +0x1F0, +0x1FC, +0x208, +0x214 (turn, brake, extraLean, animationTurn) and balance +0x280. Used by the grounded reverse turn `0x00114CC0`, the air stance switch `0x00135BE0` and rail attach alignment `0x00115358`. *[PS2]*
- **`0x00115358`** - Stance alignment for a grind style, run during rail attach after the attach requests: style 2 needs switch 1, styles 1/3/4 need 0; on mismatch multiplies the quaternion by pure (up,0), calls `0x0011E098`, then stance flip `0x00115168`. Styles 3/4 also rotate by +pi/2 (4) or -pi/2 (3) via `0x0011DFE0` and `0x00311B48`, with root sincos(-pi/4) (4) / (+pi/4) (3). Ends in empty `0x00116930`. *[PS2]*
- **`0x00115640`** - Stance restoration after a temporary prewind/side stance, keyed on style +0x328 and motion: style 0 is a no-op. Motion 1: style 3 root reset + clip 282, style 4 root reset + 277, others 268. Motion 0: styles 3/4 rotate +/-pi/2 about the old physical up +0x1C0 (`0x0011DFE0`, `0x0011E098`), transform roots via `0x00311B48`, reset root and request 5; other styles just request 5. Other motions do nothing. Clears +0x328 after the request and ends with no-op `0x00116930`. Used at board-press end (return to cruise) and by rail control and uber finish before leaving the rail. *[static]*
- **`0x001158B8`** - Air input direction: applies a deadzone and angular snapping to the spin/flip input pair. *[static]*
- **`0x00115AB0`** - Attribute tilt used by the start controller: returns 75 - 90 * the resolved attribute. *[static]*
- **`0x00115B08`** - Per-player route offset lookup (offset 0 for player 0), used during route re-attach in `0x0011D390`. *[static]*
- **`0x00115B58`** - Reaction request player: plays the pending upper-body reaction rider+0x358 on animation channel 1 with the +0x8C8 bone mask when the main class is not 5/10 and channel 1 is free; drops the request after 180 ticks (due tick at +0x354). Kinds 1..3 play 315 (1/2 also trigger trick speech `0x0029FF80`), kind 4 plays get-up reaction 314, kinds 5/6 play 318 only in control 0 with |+0x1FC| < 0.75 (table `0x00456CC0`) using the animator's all-bone mask. Runs before `0x001200D0` each frame and before `0x00115D48` in board-press updates; the finish reaction plays at rate 0.75. *[PS2]*
- **`0x00115D48`** - Upper-body idle/peer reaction controller (head checks) with timers, bone mask 0x8000FFFE, six peer cooldowns and shared game RNG draws in its timer/proximity branches (conditional). Idle clock rider+0x35C += 1/60; cooldowns use the logic tick from `0x001298C8`. The peer loop over pair records tests record +0x1C (rival flag), not +0x4 (peer is human); one note also has it setting that rival flag. A second percentage test is always true but still consumes a draw. Not run in start/soft/crash-exit/landing ticks; runs after `0x00115B58` in board-press updates. *[PS2]*
  - `0x00115E4C`: RNG draw point in the timer branch; with `0x00115FA4` it accounts for the two draws of rider slot 4 (Griff) in the idle-timer case at the Snow Jam start (call site vs. helper entry unconfirmed). *[unconfirmed]*
  - `0x00115FA4`: Second RNG draw point of the idle-timer case (paired with `0x00115E4C`); call site vs. helper entry unconfirmed. *[unconfirmed]*
- **`0x00116120`** - Forced reset request (rider, a, reason): proceeds only when requested or reason != 0; enters reset control 9 via `0x0012F230` with frozen motion 3 (control 9 updates from the next tick), clears rider+0x2E8/+0x2EC, records reason > 0 at owner+0x350 and reports observers `0x0029A220`/`0x00270970`. Reasons 1 and 4 post 'Wrong Way!' (HUD message 0x33) via `0x0011A088`. Reason 1 comes from `0x0013F178` patch flag 0x2, 2 from `0x001210B0`, 4 from builtin27 effect 5; surface property +0x44 and Select warp also request it. A new request restarts progress. Also the recovery input handler (command bit 12) called first by passive-air, rail 7, soft 3 and uber 12 control updates. *[PS2]*
- **`0x001161D0`** - Board-press entry (rider, press): from cruise or rail, plays semantic 24 (nose, input > 0, +0x330 = 1) or 32 (tail, +0x330 = 2) and requests control 1. Declines a zero press, rail styles 3/4, and (grounded only, motion 0) a rider travelling against +0x3A0. Callers: cruise `0x001317D8`, rail control 7 at `0x00131E80`/`0x00131ED8`. Because rail control calls it, it can be misread as a rail transfer. Control 1 itself (with `0x0012FC80`) covers press phases, pivot, stance flip, R3 ollie, crash, landing and rail entry. *[PS2]*
- **`0x001162C8`** - Crouch/jump request (held, pressed): while board-press latch rider+0x360 is 0, a held or first-pressed jump requests control 2 (prewind/charge) via `0x0011FEC8`; a nonzero return makes the caller exit before requesting charge (first press gives no charge). Cross held through a crash exit also requests control 2. Rail control passes bit 14 held, bit 13 pressed; the control-2 request runs the control-7 exit `0x00132048`. Called at `0x00131794`. Not an upper-body/attack action as earlier notes said. *[PS2]*
  - `0x00116344`: Call to `0x0011FEC8`(control 2) that switches the rider to prewind/charge. *[static]*
- **`0x00116378`** - Requests finish control 10, only for controller slots 0..3 (the pipe finish is crossed in the air, so control 10 follows the landing); uses rider+0x470. Runs first in soft control 3 update `0x0012E778` (before recovery and rail attach) and as a cruise precondition before the handplant test; can end the board-press tick. *[PS2]*
- **`0x001163B0`** - Upper-body attack control (rider, attackLeft, attackRight): block/punch on animation channel 1; returns 1 while the channel-1 class is 3 or 13. Right only: semantic 323 (regular) or 324 (switch), rider+0x340 = rider+0x1A0; left only: 324/323 with +0x340 = -(+0x1A0); both: 322 BLOCK. On marker 2 with the button held, ch1 rate freezes at 0 and a ch0 cycle plays (325 block, 326/327 charge). Release or side switch restores ch1 rate 1 and fades ch0 over 0.1 s; re-press is ignored until marker 1. The passive-air update calls it every tick but uses the return only while the upper latch is set. *[PS2]*
- **`0x00116930`** - Empty routine (exact no-op); called at the end of stance restore `0x00115640` and every stance alignment path, by uber enter, and during hard-crash entry. *[static]*
- **`0x00116950`** `gGenTrickName` - Trick name formatter: builds the display text for a packed trick identity from 17 text-table fields, concatenated in bit order: spin degrees, flip counts/types, named combinations, grab/late transitions, rail styles and rail Ubers (Handstand, Edge Grind, Butt Stand, Foot Surf). *[static]*
- **`0x00116FB8`** - Advances each HUD slot's elapsed time (+0x8) by 1/60 per tick. *[PS2]*
- **`0x001171A8`** - Writes a HUD bank slot (type, value, a2, a3 = count). For value slots (types 5/6) writes maximum = -1 and value = -input, so value/maximum is the fraction; a3 goes to slot+0xC. The multiplier pickup calls it as (4, int(value), 0, 0). *[static]*
- **`0x00117248`** - Score object construction; sets the +0x1C4 multiplier to 1. Paired with the run reset `0x00117540`. *[PS2]*

## `asm/1137E8.s`

Segment `0x002127E8`-`0x002227D0`.

- **`0x0021CF60`** - Constructor of the finish results panel ('finishov'), vtable `0x00473D28`. After 3 s of rider +0x470 it scales/fades in '1st run'/'2nd run'/'Final run', 'Nth place' (via `0x00238B70`) and '%d pts'; shown for FINISH only. *[PS2]*
- **`0x0021D1A0`** - Boost gauge draw (widgets 4/5/6/7): submits quads through `0x00379860` with settings from `0x004768B0` and UVs from OV.LUI atlas page 4; draws 20 background quads including flash backgrounds, plus eight middle sections (owner scale observed as 1.01680672). *[static]*
- **`0x0021D9A0`** - Recover bar draw. *[static]*
- **`0x0021E1B0`** - In-race place HUD ('2ND/6') from atlas OV_1-3 (nm1w..nm6w digits, st/nd/rd/th, slash, rider count) at (20,20); number 26x42 for 1st, else 40x42; gold (1,0.8,0) for 1st, blue (0,0.494,0.7) otherwise. The change animation comes from `0x001EA930`. 1st-place glow: two `0x0021E7E0` calls, order 10, rect grown by 1.8101751 (gp-0x535C), alpha A*(0.5+0.5*tri(g)). Slope style shows '1ST/2' by score. *[PS2]*
- **`0x0021E750`** - HUD align/placement helper used by the trick HUD and by the SUPER/UBER letter draw `0x0021ED48`. *[static]*
- **`0x0021E7A8`** - HUD placement helper used by the SUPER/UBER letter draw. *[static]*
- **`0x0021E7E0`** - Glow draw around a HUD rectangle using texture 0x5F5, material order 10, vertical centre fixed. The orb glow pads by 17.00097847 per side with alpha 0.2603548765..0.4999853671 on a triangular phase; the race place HUD `0x0021E1B0` calls it twice for the 1st-place glow. *[static]*
- **`0x0021EA00`** - Glow submission (rectangle, UV, ARGB, material). *[static]*
- **`0x0021ED48`** - Draws one SUPER/UBER letter, mode in t3: 0 dim white glyph; 1 glyph + white outline; 2 descriptor blue-green glyph ARGB(1,0,0.4,0.65098) + outline, with glow when HUD state +0x64 >= 0. Inactive UBER at x 552/568/584/600 y 81, SUPER x 544..608 y 59, scale (0.6667,1), ARGB(0.4,1,1,1); descriptor 30+2*letter. Glyphs are submitted first but with material order 12, outlines with 11. *[static]*
- **`0x0021F338`** - Draws the grade stars. *[static]*
- **`0x0021F660`** - Finish banner draw: 'fini' FINISH! with the run score, or 'timeup' TIME'S UP when t0 = 1; descriptor 0x1B. Shown when HUD state +0x88 = 1/2 and +0x80 = 0xFFEFFFFF. *[PS2]*
  - `0x0021F81C`: In-race HUD clock block: formats the time as hh:mm:ss. *[static]*
- **`0x002200C0`** - Contains the race HUD speed print below. *[PS2]*
  - `0x00220260`: Race HUD speed print block: cm/s * 0.036 = km/h, or 0.621 of that for mph (options bit 19). *[PS2]*
- **`0x002204A0`** - Now Playing (EA RADIO BIG) HUD popup routine. *[static]*
- **`0x002224A0`** - LUN script VM helper next to the host entry `0x002224B8`; role not described. *[static]*
- **`0x002224A8`** - LUN script VM helper next to the host entry `0x002224B8`; role not described. *[static]*
- **`0x002224B8`** - LUN VM host entry (frame, funcref*, globals*, ret*): allocates record 0's registers (word0 and type zeroed), sets reg0 = copy of the globals table (via `0x00225068`, type forced to 4 = table) and reg1 = nil, then runs the interpreter `0x002227D0`. *[static]*
- **`0x00222648`** - LUN VM call frame for op 0x1B: like host entry `0x002224B8`, but reg0 = the caller's reg0 and reg1 = a copy of the argument register. *[static]*

## `asm/156860.s`

Segment `0x00255860`-`0x00259288`.

- **`0x00258448`** `cGameComm_syncGame` - Contains a replay path that seeds the roster generator from the restored shared RNG. *[static]*
  - `0x0025861C`: Replay path: seeds the roster generator from a draw of the restored shared RNG instead of the presentation generator. *[static]*

## `asm/184E60.s`

Segment `0x00283E60`-`0x00284BB0`.

- **`0x00284BA0`** - Returns audio duck mask 0x173 for mode 0 (MUSIC, ch5, AMBIENT, BOARD, COLLISION, ARCADESFX). *[static]*

## `asm/1BA100.s`

Segment `0x002B9100`-`0x002C03A8`.

- **`0x002BAF90`** - Painter/environment payload lookup wrapper: runs the spatial tree query `0x002C1CD8`, takes the leaf's second 32-bit word (leaf+4) as the payload index (0xFFFFFFFF = no payload) into the section's 8-byte (type, payload pointer) table and returns the selected entry. *[static]*
- **`0x002BB100`** - Painter bank-reference comparison helper. *[static]*
- **`0x002BC7C8`** - Fog world painter constructor (painter type 5); installs vtable `0x00484FE0`. *[static]*
- **`0x002BC830`** - Glare world painter constructor (painter type 6); installs vtable `0x00484DA8`. Initialises +0 = -99999, +0x08..+0x2C = 1, +0x30..+0x3C = 0. The payload is 8 floats: rate then seven values. *[PS2]*
- **`0x002BC890`** - ScreenTint world painter constructor (painter type 7); installs vtable `0x00484B70` (blend `0x002BD1B8`, defaults `0x002BE170`, compare `0x002BDC78`). Driven by `0x002C0778` like Fog, with camera X/Y from `0x002ED490`. *[static]*
- **`0x002BC910`** - Sun world painter constructor (tWPIGD_Sun, painter type 9); installs vtable `0x00484700`. Payload is 10 words: rate, elevation deg, azimuth deg, R, G, B, glow alpha, texture index (int; lerped as float then truncated), flare alpha, glow half size. The blend weight is squared like ScreenTint. *[PS2]*
- **`0x002BC9B0`** - Lighting world painter constructor (tWPIGD_Lighting, painter type 11); installs vtable `0x00484290`. Payload is 44 bytes: blend-rate float, four 8-byte named irradiance-bank references and two scalar floats (gain, rim); ARA1 payloads reference APBR1/APDK1/APTN1/AOBR1 with scalars 1 and 0.75. References 0..2 feed the bright/dark/alternate rider banks (see `0x002EDA4C`); the fourth reference's role is unknown. *[static]*
- **`0x002BCAF8`** - Environment property constructor; initialises the breath pair to 10. *[static]*
- **`0x002BCF38`** - Fog painter blend (vtable slot 0x210): squares the weight and, for density, near, far, R, G, B, sets cur = w^2*sample + (1-w^2)*prior (no clamp), then stores the sample in the pair's second slot. Painter +0 and payload+0 (rate) are untouched. Calls slot 0x218 (empty `0x002BDA48`) before and after. *[static]*
- **`0x002BD068`** - Glare painter blend (vtable slot 0x210, entry 66): w = weight^2; cur = w*payload + (1-w)*cur for seven value pairs +0x08/+0x0C .. +0x38/+0x3C. The live painter runs several driver steps ahead of the render-context copy (e.g. 9 steps at w = 0.1^2 in Metro City, 14 at 0.08^2 in The Junction). *[PS2]*
- **`0x002BD1B8`** - ScreenTint painter blend; squares the weight before blending. *[static]*
- **`0x002BD378`** - Sun painter (tWPIGD_Sun, type 9) blend. *[PS2]*
- **`0x002BD5A8`** - Lighting painter blend: copies the four current 8-byte bank references (keeping the previous-reference slots) and blends gain +0x48 and rim +0x50 as w^2*sample + (1-w^2)*prior, recording the latest samples; rate unchanged. Calls vtable slot 0x218 (empty `0x002BDA58`) before and after. Resolved references hold a bank index plus tag 0x00123400 (APBR1 = 12, APDK1 = 14). *[static]*
- **`0x002BD698`** - Environment property blend over all 19 current/target pairs: w^2 blend of current toward incoming, then stores incoming as target (no clamp). *[static]*
- **`0x002BDA48`** - Empty Fog painter method in vtable slot 0x218, called before and after the blend; other painter classes may have non-empty hooks in this slot. *[static]*
- **`0x002BDA50`** - Glare painter no-op notify (vtable entry 67, slot 0x218), called before and after the blend. *[static]*
- **`0x002BDA58`** - Empty method in the Lighting painter vtable slot 0x218, called before and after the blend; counterpart of the Fog painter's `0x002BDA48`. *[static]*
- **`0x002BDA90`** - Default before/after hook of the environment property blend (no-op). *[static]*
- **`0x002BDABC`** - Contains the Fog painter compare entry below. *[static]*
  - `0x002BDB38`: Fog painter compare entry (vtable slot 0x220): true when all six current values are equal (sample slots ignored). *[static]*
- **`0x002BDBC4`** - Contains the Glare painter compare entry below. *[static]*
  - `0x002BDBD0`: Glare painter compare entry (vtable entry 68): true when all seven values are equal. *[static]*
- **`0x002BDC78`** - ScreenTint painter compare. *[static]*
- **`0x002BDD04`** - Contains the Sun painter compare entry below. *[static]*
  - `0x002BDD38`: Sun painter compare entry. *[static]*
- **`0x002BDE30`** - Lighting painter compare: equal when all four bank references (compared via `0x002BB100`) and both scalars match. *[static]*
- **`0x002BDEE0`** - Environment property dispatch routine in the painter transition chain. *[static]*
- **`0x002BE108`** - Fog painter defaults/reset (vtable slot 0x228): replaces near/far/RGB from globals, clears travel distance and density, and keeps the six sample slots. Called by the painter driver when the region or payload is missing. *[static]*
  - `0x002BE138`: Density clear (earlier read as a 'mode' field) in the return delay slot of the Fog reset. *[static]*
  - `0x002BE140`: Glare painter reset entry (vtable entry 69): +0 = 0 and values (1,1,1,1,1,0,0). *[static]*
  - `0x002BE170`: ScreenTint painter defaults/reset entry. *[static]*
- **`0x002BE198`** - Contains the Sun and Lighting painter reset entries below. *[static]*
  - `0x002BE1A8`: Sun painter reset entry: angles 0 (then 107 and 16 deg from `0x0049F834`/`0x0049F838`, gp-0x38BC/gp-0x38B8), colour 1, alphas 1, texture 0, size 1. *[static]*
  - `0x002BE1F8`: Lighting painter reset entry: stores the empty reference `0x004A53D0` (gp+0x22E0) in all four slots and sets scalars to (1, 0.75); an empty reference falls back to the default irradiance bank `0x004A43C4` (gp+0x12D4). *[static]*
- **`0x002BE258`** - Environment property dispatch routine in the painter transition chain. *[static]*
- **`0x002BE518`** - Fog painter vtable slot 0x208: stream/serialisation interface, not the frame update. *[static]*
- **`0x002BE698`** - Glare painter serializer. *[static]*
- **`0x002BF580`** - Fog painter vtable slot 0x200: stream/serialisation interface, not the frame update. *[static]*
- **`0x002BF700`** - Glare painter serializer. *[static]*

## `asm/1DCD10.s`

Segment `0x002DBD10`-`0x002DCB88`.

- **`0x002DBF98`** - Depth-sorted fog0 sprite list draw (priority 7), called every frame by `0x0022C708`. *[static]*

## `asm/1F1548.s`

Segment `0x002F0548`-`0x002F5298`.

- **`0x002F0548`** `cPSPVisualEffectsMan_cPSPVisualEffectsMan` - Builds the environment/visual-effects object with its 17 components, each a 4-byte object holding only a vtable, in order: 0 RenderToggles, 1 VisualEffectsTest, 2 LightGlow, 3 Plants, 4 DepthFog, 5 HeightFog, 6 DetailSystem, 7 ScreenTint, 8 Shadow, 9 SnowSurface, 10 BoardTrail, 11 Flags, 12 PowerUpFXToggles, 13 SnowfallToggles, 14 SplashToggles, 15 Tube, 16 PathArrow. *[static]*
- **`0x002F0A98`** - Environment update (vtable `0x00487D28` +0x14): calls slot +0x14 of components 0..16 in order, then `0x002F00A0` for each camera. *[static]*
- **`0x002F0CD0`** - Environment render; makes no visual-RNG draws. *[static]*
- **`0x002F1148`** - Resets the fist effect FX component at +0xC70; called by `0x00111890`. *[static]*
- **`0x002F1150`** - Attack fist sparkle FX pass (effect object at rider FX +0xC70): punch-window check using attack charge rider+0x350 drives the sparkle. *[PS2]*
- **`0x002F1A00`** - Clears +0xA0 of the rider bone-emitter controller (rider+0x88C). *[static]*
- **`0x002F1A08`** - Bone-emitter controller update, called each tick from `0x00120E88`; sets +0xA0 when its type-0x19 bone emits. *[static]*
- **`0x002F2810`** - Updates the Camera Splash lens drops (count +0x14, 0x3C-byte drops at +0x1C); a dead drop is replaced by the last one. *[static]*
- **`0x002F3030`** - Updates one Camera Splash ice crystal (0x4C bytes). *[static]*
- **`0x002F3618`** - Camera Splash vtable `0x00488230` slot +0x0C method; role not described. *[static]*
- **`0x002F3640`** - Spawns an ice-crystal group on the camera lens (Camera Splash). *[static]*
- **`0x002F37A8`** - Spawns one Camera Splash lens drop; also used to spawn a drop from a crystal. *[static]*
- **`0x002F3810`** - Camera Splash spawn (lens snow splat, only when the Weather painter value exceeds 1.0): n = trunc(+0x1024), pending -= n. Per unit, three draws of the visual LCG `0x004A3AFC` (gp+0xA0C) give x = (f-1)*640, y = (f-1)*480, t = f-1; if t < 0.6 one visual-RNG draw sets group size k = 1 + r % 2 and `0x002F3640` spawns a crystal group, else `0x002F37A8` spawns a drop. No spawn occurs in ordinary races (snowfall <= 0.1). *[static]*
  - `0x002F3920`: Return address of the visual-RNG draw that picks the ice-crystal group size; never hit in traced race ticks. *[PS2]*
- **`0x002F39C8`** - Camera Splash reset; probably the vt+0x70 call the update makes when camera speed exceeds 1000 km/h (slot assignment inferred). *[unconfirmed]*
- **`0x002F39E0`** - Camera Splash update (snow drops and ice crystals on the lens), vtable `0x00488230` slot +0x14; exactly one visual-RNG draw per tick in a race. Returns early if Enable `0x004A424C` (gp+0x115C) is 0 or camera index obj+0x10 >= camera count (in single player the camera-1 object returns here). Computes camera speed (km/h), spawns via `0x002F3810`, updates drops `0x002F2810`, runs the crystal draw step, then updates crystals `0x002F3030`. Runs in the group-2 pass (`0x00230CCC`) and also in load/overlay updates. *[PS2]*
  - `0x002F3BE0`: Crystal draw step: unconditional draw u = ((r & 0x7FFFFF) | 1.0f) - 1, f = u * crystals(+0x18) / 24; if f < 0.01 and crystals > 0 a second draw picks chosen = r2 % crystals (the crystal that spawns a drop), else chosen = -1. *[static]*
  - `0x002F3BE8`: Return address of the unconditional per-tick visual-RNG draw (via `0x003177F0`) in the crystal step; exactly one per game tick. *[PS2]*
  - `0x002F3C4C`: Return address of the second crystal draw (chosen = r2 % crystals); not seen in race traces. *[PS2]*
- **`0x002F3E28`** - Camera Splash render (vtable `0x00488230` slot +0x24); makes no visual-RNG draws. *[static]*
- **`0x002F4118`** - Secondary impact effect request raised by snow impact `0x002E1598`; calls the Camera Splash impact source `0x002F4260` (lens snow splat chain `0x002E1598` -> `0x002F4118` -> `0x002F4260`). *[static]*
- **`0x002F41A8`** - Viewport render object method vt+0x74, called after a camera set-target. *[static]*
- **`0x002F4260`** - Camera Splash impact source, last step of the lens snow splat chain from `0x002F4118`: only when snowfall > 1.0 and impact distance d < 450, pending += (1 - d/450) * clamp((I*0.036 - 105)/(120 - 105), 0, 1) * 1.1; the pending count is spawned by `0x002F3810`. *[static]*
- **`0x002F4330`** - Camera Splash snowfall source: sets +0x1028 = snowfall and, when snowfall > 1.5, adds pending += snowfall * (speed + 10) * 0.015 * 0.0076923 (constant `0x0049F7FC`, gp-0x38F4). Called once per camera from the snowfall object (`0x002E5920` / `0x002E5DA0`). *[static]*
- **`0x002F43E0`** - Provides the nine-entry lens-flare sprite table used by the sun flare draw `0x002F4690` (whether it builds or returns the table is unconfirmed). *[unconfirmed]*
- **`0x002F4690`** - Sun lens-flare draw: nine sprites from the 256x256 lens atlas (FX 45: ring/soft blob/star/disc) placed along the sun-to-centre line at centre+(sun-centre)*t, half extent 300*s, A = a*vis*flareAlpha, priority 8. Sprite table from `0x002F43E0`, colours from a gp pool via `0x002F6BC0`/`0x002F7804`. Part of the sun object with `0x002F4DB8` and `0x002F4A08`. *[PS2]*
- **`0x002F4A08`** - Sun glow sprite draw: FX texture 51+index (sun1/sun2, 128x64), one sprite via `0x00377CF0` centred on the sun with half extent painter +0x48 (320 cm when +0x48 == 1); vertex ARGB trunc(128*(vis*glowAlpha, R, G, B)); blend enum 7 (0x48), MODULATE, priority 8. *[PS2]*
- **`0x002F4DB8`** - Per-camera sun placement and screen projection: texture index -1 hides it; direction (cos az cos el, sin az cos el, sin el), Z up; point = eye + dir*(far - 500 cm), far = camera+0x58 (300 m). Hidden unless outcode test `0x0037DBE8` passes; sun+0x1F0 = screen xyz from `0x0037DD20`; a 16x16 query rect at (x-8, y-8), clamped to the viewport, gives visibility from a Z readback (`0x002EC478`). The sun (glow `0x002F4A08`, nine flare sprites `0x002F4690`) draws additive at priority 8, after fog `0x0036AC00` and before ScreenTint. *[PS2]*

## `asm/1FBE38.s`

Segment `0x002FAE38`-`0x00307598`.

- **`0x002FAE38`** `checkActiveNode` - Updates an existing Debounce component for LUN builtin 1 (called from `0x002FC7D0`). *[static]*
  - Possible mismatch with the current name: The name suggests a node-activity check, but the records describe it as the update path for an existing Debounce component of builtin 1.
- **`0x002FB498`** - Stage builtin 6 handler: AnimTeeter (ctor `0x003421A0`). *[static]*
- **`0x002FBCB8`** - Stage builtin 3 handler: LiveComp animation player (ctor `0x00341AA0`); keys 6/8 draw from the gameplay RNG. *[PS2]*
- **`0x002FBEC8`** - Stage builtin 7 handler: one-way volume (Boost, entity type 8). *[PS2]*
- **`0x002FC0D0`** - LUN builtin 0 handler: constructs an Object entity (type 17) for the current instance via `0x00356DB0` (vtable `0x00490E80`); `0x0034FB00` sets instance+0xC and `0x001032C0` sets flag 0x100 and adds it to the renderer dynamic list. With default arguments turns flags&3 == 3 into bit 2. Serves as a contact gate entity with a 30-tick guard (`0x00355770`), e.g. crashbag program 49 (builtin 0, builtin 15, return); key1/key2 flag variants appear only on inert ARA1 endmode colliders. *[static]*
- **`0x002FC2C0`** - Event instance node-state fallback for LUN builtin 2, run when the instance's event-6 handler returns false: DeadNode / type-19 construction or flag restore by mode. Mode 0: keep type 6, else destroy the node and construct type 6 (DeadNode). Mode 1: keep type 6, else destroy, then restore flags from the authored high half plus retained runtime bits (read after destruction). Mode 3: keep type 6 or 19, else destroy and construct type 19 (RestoreNode). Other modes: no action. *[PS2]*
- **`0x002FC420`** - LUN builtin 2 handler: SetNodeState / instance event dispatch (DeadNode 6, authored flags, RestoreNode 19); calls the node-state fallback `0x002FC2C0` when the event-6 handler returns false. The resulting runtime flags reach collision and the renderer. *[static]*
  - `0x002FC590`: Call site of the node-state fallback `0x002FC2C0`. *[static]*
- **`0x002FC7D0`** - LUN builtin 1 handler: creates or updates a Debounce component (defaults: target -1/current, duration 1.0, restore state 1, mode -1). Updates an existing one via `0x002FAE38`, else allocates Debounce (string `0x004896E8`, ctor `0x00342C08`, methods `0x00342D88`/`0x00342E98`); sets trigger flags by mode and replaces any instance entity through `0x00355F10` (effects move, magnet frozen). Restore mode 0 = DeadNode (permanent, section dead), 3 = RestoreNode; slot 4 replaces the completion. Boost programs pass state 3, mode 0. *[PS2]*
- **`0x002FC9C8`** - Stage builtin 12 handler (flag cloth): calls `0x0034AC88` to build a flag entity. *[static]*
- **`0x002FCFF0`** - Stage builtin 13 handler: MeshAnim break pieces (construction `0x00351B40`, draw `0x00352230`, update `0x00352500`). *[PS2]*
- **`0x002FD250`** - Stage builtin 15 handler: builds a RollerModifier (crashbag) for the current instance via `0x00355DB8`. *[static]*
- **`0x002FD420`** - Stage builtin 16 handler (MakeParticleData): creates a particle emitter/burst from keyed profile fields via `0x003705E0` -> `0x0036CCB8` (9 visual-RNG seeds per static emitter). The Startfire timer program 118 creates six emitters with it; also used at a spline path end to turn the entity into a type-13 emitter. *[PS2]*
- **`0x002FDC60`** - Stage builtin 18 handler: ParentModifier. *[static]*
- **`0x002FDED0`** - Stage builtin 19 handler: SplineModifier (defaults `0x004FB778`), built via `0x00355AD0`. *[PS2]*
- **`0x002FE0C0`** - Stage builtin 20 handler: MultiSpline(self, spline, count, speed km/h, rotation) via factory `0x00355B30`. The Snow Jam chairlift (programs 69/71, splines GondolaRail_0/1) uses 3 cars at 35/-35 km/h with rotation 90 deg. *[PS2]*
- **`0x002FE2C0`** - Stage builtin 21 handler: UVScrollModifier (ctor `0x0035F6E8`). *[static]*
- **`0x002FE840`** `cViewer_addParticle` - Stage builtin 25 handler: particle add. *[PS2]*
- **`0x002FEE98`** - Stage builtin 26 handler: DynamicParticle trail (emitter seeds via `0x00370DC8`). *[PS2]*
- **`0x002FF1C8`** - Stage builtin 48 handler: RailModifier (ctor `0x0035B708`) binding rails to a node. *[static]*
- **`0x002FF850`** - Stage builtin 27 handler (player effect): parses keyed args (player or current, effect type, float amount) with defaults `0x004FBAE8` and expected types `0x00446530`, then calls the rider effect dispatch `0x0010F1C0`. Effect types: 1/2 boost, 5 reset ('Wrong Way!'), 6 points. Keyed parsing starts from defaults; stores word0 if its type matches expected[key], else CVT.S.W(word0) if the expected type is float, else word0. Player key -1 = current player *`0x004A3DD8` (gp+0xCE8). Boost programs 28 (speed, type 1) and 30 (trick, type 2) pass amount 5. *[PS2]*
  - `0x002FF95C`: Call to the rider effect dispatch `0x0010F1C0`. *[static]*
- **`0x002FFB50`** - Stage builtin 29 handler: Hide (type-16 nodes). *[static]*
- **`0x002FFD58`** - Stage builtin 58 handler: Unhide (type-16 nodes). *[static]*
- **`0x002FFF00`** - Stage builtin 30 handler: sound. *[static]*
- **`0x003000A8`** - Stage builtin 31 handler: sound. Another note links 'AnimObject builtin31 181' to the raven flap animation; the relation is unclear. *[static]*
- **`0x00300260`** - Stage builtin 73 handler: sound. *[static]*
- **`0x00300770`** - Stage builtin 34 'Teleport current player': one int key, the instance resource (types `0x004A3C40` gp+0xB50, default -1 at `0x004A5688` gp+0x2598; -1 uses ctx+0x290). Player = ctx+0; no-op if player < 0 or instance 0. Destination matrix = instance+0xC entity ? entity vt+0xC4() : instance+0x10; then calls the roster rider's vt+0x54 (`0x00123210`), which human and computer vtables share, so CPU riders teleport too. Returns nil; used by BRA2 teleport beams. *[static]*
- **`0x00300E28`** - Stage builtin 37 handler: collections (collectibles). *[static]*
- **`0x00300F50`** - Stage builtin 38 handler: collections (collectibles). *[static]*
- **`0x00301120`** - Stage builtin 39 handler: collections (collectibles). *[static]*
- **`0x003012F0`** - Stage builtin 40: mission operation; calls `0x0030A868`. *[static]*
- **`0x003019C8`** - Stage builtin 55 handler: LiveComp timer gate, true when the player time crossed key1/30 s this tick (`0x0034EBE0`). *[PS2]*
- **`0x00301D78`** - LUN builtin 0x41 (65): script instance-contact predicate. Parses keyed arguments (expected types at `0x004A3CB0`, gp+0xBC0), resolves an authored resource through the world table, gets the current rider, calls the rider's instance-contact predicate (interface rider+0x6C0 slot 0x1C, `0x00108C28`) and writes the result as a script value via `0x00226610`. Builtin table entry `0x0044203C`. *[static]*
  - `0x00301E5C`: Resolves an authored resource through the world table at `0x004A47B8` (gp+0x16C8), through `0x00301EA4`. *[static]*
  - `0x00301EAC`: Gets the current rider from the player manager / current-player index (through `0x00301EDC`). *[static]*
  - `0x00301EF0`: Indirect call of the rider instance-contact predicate (interface +0x6C0 slot 0x1C); call sequence spans `0x00301EE0`..`0x00301EF4`. *[static]*
  - `0x00301EF8`: Writes the predicate result as a script value via `0x00226610`. *[static]*
- **`0x00302048`** - Stage builtin 67 handler (RaceRideState gate), human riders only: key1 = 0, key0 goes through entry table `0x00445E40` and value 1 (FreeRideState volumes) is rejected. Ends an active Big Challenge (`0x0030B7F8`) and calls `0x0022D6C8` to start a CTM event. Peak 3 gates: ERA5 rid 989 (k0 0), ESS3 rid 1526 (k0 1), EBA3 rid 735 (k0 2), EHP3 rid 255 (k0 3); EBC3's three FreeRideState volumes (k0 4) are rejected. *[PS2]*
- **`0x00302210`** - Stage builtin 68: streaming/station trigger, human riders only; key0 map id (converted to a course by `0x00144CE0`), key1 action, key2 entry index into `0x00445E40`. Actions: 0 Unload (`0x0022CEA8`), 1 nothing, 2 Load (`0x0022D088`), 3 transport booth, 4 lodge door, 5 sky dome switch allowed. For actions 3/4 key0 is ignored and the current course is used. *[static]*
- **`0x00302490`** - LUN builtin 69 (particle stop): resolves an instance, checks its entity (instance+0xC, vtable+0x84) and toggles attached components through entity+0x1C: argument 1 -> `0x00353278` (mode 1 also deletes halos), 0 -> `0x00353228`. Boost programs call it with 1 right after the reward. *[PS2]*
- **`0x00302778`** - Stage builtin 43 handler: event-kind test, returns int(table `0x004465F8`[n] == event type `0x00535C10`) (e.g. Race on ARA1/BRA2, Half Pipe on BHP1). Mode fences and challenge reset planes use it to remove themselves in the wrong event. *[PS2]*
- **`0x00302968`** - Stage builtin 44 handler: set current instance. *[static]*
- **`0x00303130`** - Stage builtin 52 handler: has entity; guards slot-2 triggers so they launch once. *[static]*
- **`0x00303430`** - Stage builtin 61 handler: read current instance (-1 without one). *[static]*
- **`0x00303598`** - Stage builtin 77 handler: random float from the gameplay RNG. Crow's Nest program 42 (ospreytrigger) returns if the draw is < 60, else launches LiveComp + Spline. *[static]*
- **`0x003039F0`** - Contains a builtin path by which global scripts reach `0x00343C60`. *[static]*
  - `0x00303B38`: Builtin path by which global scripts reach `0x00343C60`. *[static]*
- **`0x00303BA0`** - Stage builtin 88 handler: CrowdMan2d registration (crowd texture animation and camera-flash areas). *[static]*
- **`0x00303E60`** - Stage/WScript builtin code; source notes place the scripted lightning-strike builtin code `0x00305778` inside it (unconfirmed, since builtin handlers `0x003050F0` and `0x00305478` start in between). *[static]*
  - `0x00305778`: WScript builtin code that triggers a scripted lightning strike through `0x00390EC8`. *[static]*
- **`0x00304E38`** - Stage builtin 87 handler: contact guard preset, entity+0x20 = int(60 * seconds). *[static]*
- **`0x003050F0`** - Course script builtin 91: scripted camera shake (index 0, amplitude 0.4, radius 200 m). *[static]*
- **`0x00305478`** - Stage builtin 90 handler: MagnetModifier (entity-route box answering filter 1; the first human contact acquires it and it flies to the rider). *[PS2]*
- **`0x003057C0`** - Stage builtin 97 handler: HaloModifier (spinning halo sprite). *[static]*
- **`0x003061B0`** - LUN builtin 99 handler: option-enabled test. Selectors 0/1/2 test bits 6/8/7 of global `0x005308D0` and return enabled when the bit is clear; other selectors return 1. Not an instance-collection flag. *[static]*
  - `0x00306260`: Selector test block (through `0x003062C8`): bits 6/8/7 of `0x005308D0` for selectors 0/1/2. *[static]*
- **`0x00306A90`** - Stage builtin 105 handler: MultiParticle group member add (roadflare flames). *[PS2]*
- **`0x00306CB0`** - Stage builtin 106 handler: MultiParticle group member remove (first match, via `0x003581F0`). *[PS2]*
- **`0x00307308`** - Big Challenge complete: sets status bit 3, awards cash via `0x001511B0`(peak), shows the 'MISSION SUCCESS' popup and unlocks the next challenge (own bit 4 off; next bit 0 off, bits 1 and 4 on). Observed: status 0x12 -> 0x1A and +$2,000. *[PS2]*
- **`0x003074C0`** - Big Challenge fail: sets status bit 2. *[PS2]*

## `asm/2125C8.s`

Segment `0x003115C8`-`0x003118D0`.

- **`0x00311710`** - Weighted animation variant lookup, the second stage of semantic resolution after `0x00104CF8`: a variant is eligible if (allowed & required) == required; with more than one eligible variant it makes one shared RNG draw, takes draw % sum of the uint32 weights and subtracts weights, selecting when the signed remainder <= 0. A singleton bypasses and consumes no draw. The generic init resolves the air-adjust primary leaves [157,163,160,164,158,162,159,161] for semantics 297..304. *[static]*

## `asm/21E5A8.s`

Segment `0x0031D5A8`-`0x0031D660`.

- **`0x0031D5A8`** - cCSICubicSpline routine: natural cubic spline build/evaluate used by the jump and swing cameras; one of eight related routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) whose individual roles are not separated. Coefficients match a Burden-Faires natural spline with a cache tie rule. *[static]*
- **`0x0031D5E8`** - cCSICubicSpline routine: natural cubic spline build/evaluate used by the jump and swing cameras; one of eight related routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) whose individual roles are not separated. Coefficients match a Burden-Faires natural spline with a cache tie rule. *[static]*

## `asm/2B4578.s`

Segment `0x003B3578`-`0x003EB198`.

- **`0x003B6300`** - Caller of the 48000 Hz / codec 10 PT header parser `0x003BBDA0`. *[static]*
- **`0x003B6788`** - Caller of the 48000 Hz / codec 10 PT header parser `0x003BBDA0`. *[static]*
- **`0x003B6BD0`** - SCHl chunk handler; clears the stream +0x24 'not first block' flag. Listed together with `0x003B7080`. *[static]*
- **`0x003B6EA8`** - SCDl chunk handler: builds the block descriptor and returns the block count with bit 31 set when this is not the first block of the current SCHl (stream +0x24 flag, cleared by the SCHl handler `0x003B6BD0`, set after every SCDl); channel pointer = end of offset table + offset[c]. The flag, stored in decoder ctx+0xD5C, decides between header parse and keeping decoder state. *[PS2]*
- **`0x003B7080`** - Stream chunk routine listed with the SCHl handler `0x003B6BD0`; role not described. *[unconfirmed]*
- **`0x003B76E8`** - Checks for the SCEl end chunk of a stream. *[static]*
- **`0x003B7E70`** - Stream volume setter (0..127). *[static]*
- **`0x003B7EB0`** - Stream volume fade (ms/10 ticks, target): linear in the 0..127 domain in 10 ms steps, applied as a 16.16 step per tick by `0x003B8530`. *[static]*
- **`0x003B7FB8`** - Stream pitch setter (4.12 fixed, 0x1000 = 1.0). *[static]*
- **`0x003B80A0`** - Stream filter parameter setter (stream param +0x100); LOWPASS path `0x003B80A0` -> `0x003B8978` -> `0x003C3178`. Normalised cutoff = value/(mixer rate/2) with mixer rate 36000; retail values never filter. *[static]*
- **`0x003B8160`** - Sets the sound driver master volume (0..127, master byte `0x0050AA5D`); called with ch0 volume x 127. *[static]*
- **`0x003B8530`** - Stream fade tick: 16.16 fixed-point volume step every 10 ms. *[static]*
- **`0x003B8978`** - Stream filter chain step (`0x003B80A0` -> `0x003B8978` -> `0x003C3178`). *[static]*
- **`0x003BA0B0`** - Hardware voice allocation: SPU pool of 48 voices (PS-ADPCM) and IOP-mixed pool of 8 (MicroTalk, EA-XA, PCM8). Takes a free voice first, else steals the lowest priority (patch tag 0x06) <= min(new, 100), oldest on ties, with a hard stop; a layer without voices fails the whole request. *[static]*
- **`0x003BAAC0`** - Bank patch PT header parser with defaults (rate 22050, codec 5); returns at each 0xFE (end of patch). *[static]*
  - `0x003BABC0`: Sets the default bank patch sample rate 22050. *[static]*
- **`0x003BB588`** - SND voice layer start (patch parameters, envelopes, LFOs); part of the `0x002906B8` / `0x002AC868` voice path. *[static]*
- **`0x003BB820`** - Stream PT header parser with defaults (rate 22050, codec 5); mode voice+0x30 = tag 0x80 (header struct +7), tag 0x8C lands in header struct +2. *[static]*
  - `0x003BB930`: Sets the default stream sample rate 22050. *[static]*
- **`0x003BBDA0`** - Third PT header parser, with defaults 48000 Hz and codec 10; called from `0x003B6300` and `0x003B6788`. *[static]*
- **`0x003C2A50`** - EE audio mixer: scales by gain/127 (linear amplitude). *[static]*
- **`0x003C3178`** - Stream low-pass setup: normalised cutoff = value / (mixer rate / 2); last step of the filter chain from `0x003B80A0`. *[static]*
- **`0x003C6DE0`** - Stream ring-buffer fetch used by the stream voice read `0x003C96F0`: returns the block pointer, the count with bit 31 cleared, and bit 31 separately. *[static]*
- **`0x003C7010`** - Stream ring-buffer release, used with fetch `0x003C6DE0` by the MicroTalk stream voice read `0x003C96F0`. *[static]*
- **`0x003C72F8`** - Big-endian value reader for PT header tags. *[static]*
- **`0x003C7388`** - EA PT header tag-list iterator (streams and bank patches): 0xFC padding, 0xFF end of header, 0xFD sample part follows, 0xFE end of patch (next patch follows); otherwise tag, u8 length (0xFF -> u32 BE length), big-endian value. *[static]*
- **`0x003C8D00`** - Removes the stream filter when the cutoff ratio is >= 1 (true for every retail LOWPASS value). *[static]*
- **`0x003C92F8`** - Generated function containing the code for all voice types (`0x003C92F8`..`0x003C9DA0`); the stream voice setup selects voice type 2 for stream codec 4 (MicroTalk). *[static]*
  - `0x003C9420`: SND (bank) voice MicroTalk open: opens the loop body as a fresh stream. *[static]*
  - `0x003C9520`: SND voice MicroTalk loop restart: reopens the loop body as a fresh stream. *[static]*
  - `0x003C9938`: MicroTalk stream voice close. *[static]*
- **`0x003C96F0`** - MicroTalk stream voice read (voice type 2, codec 4): decodes stream samples into the voice frame buffer ctx+0x684, fetching/releasing blocks via ring-buffer `0x003C6DE0`/`0x003C7010` and opening each block with `0x003CDDE8`(ctx, pointer + 1, ...), so the first byte of each channel block (01 in the first block, 00 after) is skipped. Lies within the voice-type code of `0x003C92F8`. *[PS2]*
- **`0x003C9960`** - MicroTalk music stream voice open (stream codec 4, voice type 2; read entry `0x003C96F0`). Parses the header only on the first block of each SCHl, otherwise keeps decoder state across blocks; with stream tag 0x80 < 3 it runs plain MicroTalk (ctx+0xD64 = 0). Lies within the voice-type code of `0x003C92F8`. *[PS2]*
- **`0x003CA8A0`** - EE filter module, enabled for cutoff values < 18000 (response not recovered; unused by retail data). *[unconfirmed]*
- **`0x003CD1F8`** - MicroTalk bit reader (LSB-first, 8-15 bits buffered, one-byte refill); paired with `0x003CD260`. *[static]*
- **`0x003CD260`** - MicroTalk bit reader, paired with `0x003CD1F8`. *[static]*
- **`0x003CD2B0`** - MicroTalk excitation decode: multipulse Huffman (codebooks `0x0044E9E8`, commands `0x0044EBE8`) with zero runs 7-70 and escape pulses >= 7; RELP mode codes 0/+-2. *[static]*
- **`0x003CD518`** - MicroTalk reduced-bandwidth interpolation (coefficients 0.5973859, -0.1145916, 0.0180327; fixed gain halved). *[static]*
- **`0x003CD590`** - MicroTalk reflection -> LPC coefficient conversion. *[static]*
- **`0x003CD6F0`** - MicroTalk init and 15-bit header parse: reduced_bw:1, threshold = 32 - read(4), gain[0] = 8(1 + read(4)), gain[i] = gain[i-1](1.04 + 0.001 read(6)) for 64 gains. *[static]*
- **`0x003CD878`** - MicroTalk frame decoder: 12 reflection indices (4x6 bits, 8x5 bits +16) into table `0x0044E8E8`, four 108-sample subframes; multipulse when the first index < threshold. Per subframe: pitch lag 8 bits, pitch gain 4 bits (/15), fixed gain index 6 bits. Constants: pitch gain = cvt(v) x float 0x3D888889; gain base = v x 0x3A83126F + 0x3F851EB8 (float bit patterns). *[static]*
- **`0x003CDDB8`** - MicroTalk decoder entry; works with block open `0x003CDDE8` and frame step `0x003CDE68`. *[PS2]*
- **`0x003CDDE8`** - MicroTalk block open (ctx, pointer, ...); EA wrapper entry when ctx+0xD64 = 1. *[PS2]*
- **`0x003CDE68`** - MicroTalk EA-wrapper frame step, including the flag byte 0xEE PCM patch writer, which writes without bounds checks: a misparsed patch (MineShaft channel 1, offset 223, count 262) overruns the 432-sample frame and clobbers ctx fields (remaining count, output pointer), losing that voice's output. *[static]*
  - `0x003CDF34`: Inter-frame byte re-alignment block (skipped in plain mode). *[static]*
- **`0x003CE0B8`** - MicroTalk block start: with ctx+0xD5C = 1 parses the header (`0x003CD6F0`) and clears decoder state; with 0 only restarts the bit reader. *[PS2]*
- **`0x003CE0D8`** - Sets the MicroTalk wrapper mode (ctx, mode); 0 = plain MicroTalk (ctx+0xD64 = 0). *[PS2]*
- **`0x003CE410`** - MicroTalk 12-tap LPC synthesis filter: 1+1+1 blocks of 12 samples with quarter-interpolated coefficients, then 33 blocks; 324-float adaptive codebook refreshed per frame. Accumulation order (ADDA.S/MADDA.S) matters: for output j >= 1, lpc[1..j-1] x older outputs, lpc[j..11] x history, lpc[0] x newest output last. *[static]*
- **`0x003CFC30`** - Pathfinder event action execution: runs actions in order, and an incomplete action blocks the rest of that event; opcode dispatch through jump table `0x00495A30` on action byte 9. *[unconfirmed]*
- **`0x003D0D70`** - Pathfinder voice intensity setter (voice+1 branch value). Called via `0x002B2120`/`0x002B3C28` with 127 for hub, podium, map and FE songs; in races `0x0028F000` writes a rising value. *[PS2]*
- **`0x003D1038`** - Pathfinder track pause/resume (track id, flag). *[static]*
- **`0x003D11B8`** - Pathfinder stream status; reports -1 once a voice has stopped and the queue has drained. *[static]*
- **`0x003D15C8`** - Pathfinder stream call used by `0x002B3C60`; meaning not recovered. *[unconfirmed]*
- **`0x003D16F0`** - Pathfinder event post (slot, event): copies the event head and actions into the slot queue (max 16) with the post time; the event number indexes the event table and values >= count are ignored. Only queues; the next service tick executes it. *[static]*
- **`0x003D1D28`** - Pathfinder event handling routine (works with `0x003D16F0`, `0x003D2068`, `0x003CFC30`). *[static]*
- **`0x003D1E80`** - Processes pending Pathfinder events (service reason 0x20). *[static]*
- **`0x003D2068`** - Pathfinder event handling routine (works with `0x003D16F0`, `0x003D1D28`, `0x003CFC30`). *[static]*
- **`0x003D2350`** - Pathfinder .mpf loader: checks magic and version, builds the table pointers ctx+0x38..+0x54 from the .mpf offsets (x4) and zeroes the slot. Slot id = 0x1000000 << mpf[0xC] | 0x10000000 << instance. *[static]*
  - `0x003D240C`: Magic check: .mpf 'PFDx' (bytes 78 44 46 50). *[static]*
  - `0x003D2420`: Version byte check (must be 4). *[static]*
  - `0x003D2474`: Start of the table-pointer setup (through `0x003D256C`): slot +0x38..+0x54 from the .mpf offsets (x4). *[static]*
- **`0x003D25F0`** - Opens a Pathfinder track voice on a stream file (track id, file, latency, queue size); the voice is 0x110 bytes at slot+0x58[track]. Game ids 0x11000001 = track 0 (MUSDATA), 0x11000002 = track 1 (LOOPDATA) of the first slot. *[static]*
- **`0x003D2DF8`** - Attaches the resident loop bank to Pathfinder track 1; called from `0x002B4620`. *[static]*
- **`0x003D3658`** - Computes the Pathfinder loop slice: (master beat index + 1) mod beats-per-measure + 1; tests the sync mode on the group head. *[static]*
- **`0x003D37A0`** - Pathfinder branch pick: first branch with lo <= v <= hi (v = voice intensity or loop counter), else the nearest bound; 0xFFFF or no branch = stop. *[PS2]*
- **`0x003D3900`** - Walks Pathfinder control nodes until an audio node. Sample 0 = part head (sets voice+0x30; w4 bits 17-19 == 1 makes the branch value random = (now_ms/23) & 0x7F, the only random source); -1 = part end (loop counter); -2 random; -3 post event (w12>>2)&0xFFF (the last two unused by songs). *[static]*
- **`0x003D3C90`** - Pathfinder router: remaps targets by the previous node (no song uses routers). *[static]*
- **`0x003D3D20`** - Pathfinder next-node selection entry (-> `0x003D37A0` -> `0x003D3900` -> `0x003D41A8`). *[static]*
- **`0x003D4050`** - Hands a target on another track to that track's voice via a synthetic event (unused by songs). *[static]*
- **`0x003D41A8`** - Queues a Pathfinder node's sample (stream offset value x 0x80, or a bank entry); handles slice sync, returning -9999 while waiting for the master beat. *[static]*
  - `0x003D4388`: Reads node +8 bits 20-31 (group head node index). *[static]*
  - `0x003D43B0`: Block reading a node sample's duration: table[sample*8 - 4] (duration of sample-1; samples are 1-based). *[static]*
  - `0x003D4400`: Block reading a node sample's value: table[(sample-1)*8]. *[static]*
  - `0x003D4440`: Tests the sync mode (node +8 bits 8-9) on the group head node. *[static]*
  - `0x003D4460`: Block deriving ms per bar (ctx+0x44 = ms / measures) and per beat (ctx+0x40 = ms / (measures x beats)) from node +4; ctx is probably the voice/segment context, not the slot's table pointers. *[unconfirmed]*
- **`0x003D4950`** - Sums the remaining ms of a voice's queued entries. *[static]*
- **`0x003D4B00`** - Finds the Pathfinder master voice (playing voice with the largest latency, track 0); reads the section as node word >> 21. *[static]*
- **`0x003D4F10`** - Pathfinder voice commit rule: queues the next node when queued audio (`0x003D4950`) <= latency and the stream has room (`0x002AEBD0`), keeping the stream one bar ahead (e.g. each 1818 ms Avalanche bar is followed by the next commit 420-490 ms before its end). *[PS2]*
- **`0x003D5128`** - Pathfinder service tick, run from callbacks `0x003D54C8`/`0x003D54E8`: processes events (reason 0x20) and voices. *[static]*
- **`0x003D54C8`** - Pathfinder service callback registered by `0x002AE048`. The two callbacks (with `0x003D54E8`) serve reasons 0x20 (margin 50 ms, events first) and 0x42 (margin 10 ms, voices only); which one handles which is not established. *[static]*
- **`0x003D54E8`** - Pathfinder service callback registered by `0x002AE048`; paired with `0x003D54C8` for service reasons 0x20/0x42 (assignment not established). *[static]*
- **`0x003D5508`** - Pathfinder track level setter (track id, level %). *[static]*
- **`0x003D5A98`** - Pathfinder volume ramp: moves the stream volume to the target over time along a curve. *[static]*
- **`0x003D62C8`** - Pathfinder volume write (through gate `0x002AF6C0`). *[static]*
- **`0x003D69F0`** - Speech .hdr line table parser. Layout: +0 u16 id/hash, +2 0xFFFF, +4 u8 bits 0-3 field count F (bit 7 played bitmap), +5 u8 lines N, +6 u8 history H, +7 u8 align mask M (offset unit 256(M+1)), +8 u32 .dat size/256 (one reading says /512, unconfirmed), +12 N x (u16 BE offset + F key bytes), pad 'p', F x u32 masks, cursor + H history bytes. A line matches when arg & (1 << tag). *[static]*
- **`0x003D7110`** - Searches the eight loaded speech event banks for a packed event ID. *[PS2]*
- **`0x003D7418`** - Speech event post body/handler, reached from `0x003D76F0`. *[static]*
- **`0x003D76F0`** - Speech event argument post entry, called through *`0x004A482C` (gp+0x173C): builds an argument packet and delegates to `0x003D7418`. *[PS2]*
- **`0x003D8008`** - EA speech engine event post start, called as (1, 0, eventId) before the argument call through *`0x004A482C` (gp+0x173C); packs a speech event resource ID (e.g. 0x010020A7). *[static]*
- **`0x003D8CB0`** - Speech line weighted pick. *[static]*
- **`0x003D95B8`** - Speech line selection with a shuffle mode. *[static]*
- **`0x003DB4D0`** - Speech engine RNG. *[static]*
- **`0x003DB5C0`** - Uniform random choice among matching speech lines with a no-repeat history: uses RNG `0x003DB4D0`; the history is a 32-entry ring at `0x00450B88` keyed by bank, and values from the last min(n/2, 10) picks are rejected. *[static]*
- **`0x003E6328`** - Knuth-gap shell sort used by the race ranking. *[static]*

## `asm/2EEF50.s`

Segment `0x003EDF50`-`0x0042E590`.

- **`0x003F42A0`** - Post-camera game-update step; makes no RNG draws in a race. *[static]*
- **`0x003FE818`** - Starts a VU0 microprogram: moves its argument (the VU0 micro-memory start address) into CMSAR0 and issues VCALLMSR in the return delay slot. About six game routines use this VCALLMSR path. *[static]*
- **`0x00402520`** - sceCdReadClock (reads the console clock). *[static]*
- **`0x0040D758`** - Math library wrapper called by the brightness curve `0x002EDF00`; probably exp (from the call order of exp(log(v)*p)). *[unconfirmed]*
- **`0x0040DA10`** - Math library wrapper called by the brightness curve `0x002EDF00`; probably log (from the call order of exp(log(v)*p)). *[unconfirmed]*
- **`0x0040E048`** - Math leaf kernel (log or exp) under the brightness curve's library calls; call order suggests exp, with `0x0040E550` as log (unconfirmed). *[unconfirmed]*
- **`0x0040E550`** - Math leaf kernel (log or exp) under the brightness curve's library calls; call order suggests log, with `0x0040E048` as exp (unconfirmed). *[unconfirmed]*
- **`0x004139F8`** - __fixsfsi (float to int conversion helper). *[static]*
- **`0x004165A8`** - strcmp; used by bone name lookup. *[static]*
- **`0x00418EF8`** - Sort routine used by the skeleton compile to order parts by file id. *[PS2]*
- **`0x0041AA88`** - Case-insensitive string compare, used for MUSIC.INF keys. *[static]*
- **`0x0042C130`** - Game routine installed as a kernel syscall handler; startup code `0x0042C1F0` finds its kernel copy via FindAddress (probably the search paired with the 0x168 subtraction; pairing inferred from order). *[static]*
- **`0x0042C168`** - Game routine installed as a kernel syscall handler; startup code `0x0042C1F0` finds its kernel copy via FindAddress (probably the search paired with the 0x20C subtraction; pairing inferred from order). *[static]*
- **`0x0042C1A8`** - Wrapper that issues EE kernel syscall 0x83 (FindAddress); called repeatedly by `0x0042C1F0` during startup. *[static]*
- **`0x0042C1F0`** - Startup kernel-table locator: loops calling FindAddress (`0x0042C1A8`) over kernel memory 0x80000000..0x80080000 for the words 0x0042C168 and 0x0042C130 (the game's own syscall handler addresses), subtracts 0x20C and 0x168 from the returned locations, and repeats until the two derived kernel table bases agree. Called from `0x0042C300`. *[static]*
- **`0x0042C300`** - Caller of the startup kernel-table locator `0x0042C1F0`. *[static]*
- **`0x0042CB78`** - Game routine registered as a kernel syscall handler entry during early startup, like `0x0042C130` and `0x0042C168`. *[static]*
