<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/animation/

## `src/animation/animmodel.cpp`

Segment `0x0030D8B8`-`0x003115C8`.

- **`0x0030D8B8`** `cAnimModel_addModelPartLOD` - Adds a model by name at a geometry part slot. *[PS2]*
- **`0x0030DBD0`** `cAnimModel_compile` - Compiles the rider skeleton: sorts parts by file id, gives each part a base slot equal to the running bone count (hidden parts included; Eyes_NIS holds 2 slots), assigns each part with morphs the next morph index, and builds inverse binds (local bind, world = parent x local, rigid inverse) with VU0 ops that round toward zero with DaZ/FtZ. *[PS2]*
  - `0x0030E560`: Block building a bone's local bind matrix (VU0, round toward zero). *[PS2]*
  - `0x0030E5F4`: Block building a bone's world bind matrix = parent x local. *[PS2]*
  - `0x0030E748`: Block computing the rigid inverse of a bind matrix (inverse bind). *[PS2]*
- **`0x0030EBC0`** - Tests whether a geometry part is active. *[PS2]*
- **`0x0030ECD8`** - Animation preview: samples a clip at time zero with sequence/root/mirror settings; probably draws from the animation variant RNG. Crash entry `0x0010EB30` uses it to bake the new crash clip's preview root. *[PS2]*
  - `0x0030EFE0`: Quaternion conversion in the single-bone sampling path. *[static]*
- **`0x0030F2B0`** - Animation local-pose sampler; contains the bone-mask and spherical-to-quaternion blocks below. *[PS2]*
  - `0x0030F4F4`: Local sampler bone-mask block: intersects geometry+0x158 when rider+0xB1C is nonzero (with geometry+0x150 and the sequence mask). *[PS2]*
  - `0x0030FC7C`: Spherical-coordinate to quaternion conversion block (through `0x0030FD9C`). *[static]*
- **`0x00310120`** - Builds per-bone pose matrices from posed position and (unnormalised) quaternion: reads geometry+0x2C, writes the unscaled cache geometry+0x30, then scales every column by geometry+0x140 XYZW into geometry+0x34 (W is 1, so the position column is unchanged). First skin-palette stage, before the bind product at `0x003106CC` and weighted sum `0x00386BD0`. *[PS2]*
- **`0x00310200`** - Forward kinematics: scales each local translation and composes quaternion/position with the parent. *[static]*
- **`0x003103F0`** - Animation step called in the tail of `0x0011D660`. *[static]*
- **`0x00310530`** - Late geometry translation: adds an accumulated contact displacement to the pose and to both cached translation columns (unscaled geometry+0x30 and scaled +0x34, not only the scaled one), moving cached bones and skin matrices without resampling. Used with `0x00121750` to move bones and head after contact. *[static]*
- **`0x00310640`** - Geometry draw: multiplies the scaled pose (geometry+0x34) by the inverse binds (geometry+0x38) into the skin palette at `0x004FC420` (`0x003106B8`..`0x00310778`), then calls renderer slots 0x37C (`0x00386BD0`, weighted skin sum) and 0x31C (`0x0037A610`) for active model parts. *[PS2]*
  - `0x003106CC`: Pose x inverse-bind loop (through `0x00310778`) writing palette matrices to `0x004FC420`; the skin stage between `0x00310120` and `0x00386BD0`. *[static]*
- **`0x00310C48`** - Skeleton bone lookup by name (skeleton, part, name): linear strcmp over the part's bones, returns part.firstIndex+i or -1. Used by FE lighting for the hips bone; another note describes it as returning a bone's world position. *[PS2]*
- **`0x00310CE8`** - Builds a bone mask from a bone-name list; `0x0011C298` uses it to build the channel-1 masks from lists `0x00457A90`, `0x00457B38` and `0x004A1090`. *[PS2]*
- **`0x00311318`** - Compressed animation curve sampling with 30 Hz segment lookup; where consecutive packets overlap at a segment boundary, the sample comes from the next packet's first row. *[static]*

## `src/animation/rideranimbase.cpp`

Segment `0x003118D0`-`0x00313A10`.

- **`0x00311A50`** - Animation placement routine; after its play it resets the pending next rate animator+0x1C to 1. *[PS2]*
- **`0x00311AE8`** - Returns the animation class (not the semantic) of a channel's requested semantic, called as (anim, channel). Attack control tests classes 3/13; the handplant airborne entry test rejects channel-2 classes 18..20; the breath emitter treats channel-2 class 30 as effort. *[static]*
- **`0x00311B20`** - Returns a channel's first playback sequence via `0x00314760` (list index 0), even while fading. Used to change the rate of only that sequence and with `0x001446A0`/`0x001446B8` to read its marker bits. *[static]*
- **`0x00311B48`** `cRiderAnimBase_changeHeadingOffset` - Rotates all existing animation sequence roots on the six channels by -angle about Z (quaternion from sincos(-angle/2) about `0x004FF160`, applied via `0x00311BF0`); the rotation is by -angle, not +angle. Leaves the default root and mirror flags unchanged. Used by rail attach, stance flip `0x00115168` (pi), stance alignment and crash compensation. *[PS2]*
- **`0x00311BF0`** `cRiderAnimBase_changeOrientationOffset` - Applies a root rotation quaternion to existing animation sequence roots; called by `0x00311B48`, and after crash/reset bakes with the inverse root delta. Also runs on the stance-restore path. *[static]*
- **`0x00311E88`** - Fades an animation channel (anim, channel, time): removes completion marker 63 (`0x00314718`), fades the channel list (`0x003146D0`) and sets the requested semantic slot to 438 (neutral, class 0); fading poses and ordinary markers are kept. Uber enter fades channels 1 and 0 over 0.33. *[static]*
  - `0x00311EE0`: Writes 438 (neutral) into the channel's requested-semantic slot. *[static]*
- **`0x00311F00`** - Creates or revives an animation sequence: new sequences take the animator pending rate +0x1C, event time = first 16-bit event word * (1/30), and `0x00314518` sets up the primary slot. With a2=0 it revives a fading sequence with the same clip, root, mask and mirror, keeping its clock and weight (target 1, fade = blend*(1-weight)). For kind 11: one enabled non-looping primary slot (time 0, rate 1, weight 1), no implicit completion event 63 for completionKind 0. *[PS2]*
- **`0x003123C0`** - Animation step called by `0x0011EB60` before completion dispatch. *[static]*
- **`0x00312490`** - Animation completion batch: traverses the six channel lists, collects flag-63 sequence nodes, then dispatches that fixed set. Nodes flagged during callbacks wait for the next pass; already-collected callbacks still run if their flag is cancelled. Runs after local-pose sampling (with `0x0011EB60`). *[static]*
  - `0x00312500`: Collects flag-63 sequence nodes (through `0x00312510`). *[static]*
  - `0x00312540`: Dispatches the collected completion set (through `0x00312568`). *[static]*
- **`0x00312598`** - Animation semantic request helper; called by `0x0011EB60` before completion dispatch `0x00312490` and in the `0x0011D660` tail. *[static]*
- **`0x00312790`** - Animation duration query: resolves the semantic via `0x00104CF8`/`0x00311710` and returns (AFL frameCount-1)/30; basic ID 519 returns +0. May consume the shared RNG through weighted-variant lookup, so call order matters (the air selector can query semantic 305's duration even when the semantic stays unchanged). *[static]*
- **`0x00312820`** - Animation marker time getter (authored AFL marker 1/2 times); may consume RNG for multi-variant semantics. *[static]*
- **`0x003128E8`** `cRiderAnimBase_play` - Plays an animation semantic (anim, semantic, blend, force): resolves the variant, creates or revives a sequence via `0x00311F00` and sets channel priority from table `0x0048D808`. Blend -1 uses the state-table crossfade; (anim, sem, 0, -1) is an ordinary non-forced play, and with a2=0 (landings `0x0013A968`/`0x0013A8F8`) a fading copy is revived. Leaf 519 is a no-play sentinel returning 438 without changing the channel. Honours a bone mask in animator+0x20 (attack control writes rider+0x8C0 there, then restores -1). *[PS2]*
- **`0x00312AA0`** - Returns the animator's requested semantic for a channel (from the requested-semantic slots). During fades this differs from the first playback sequence, which `0x00311B20`/`0x00312AE8` inspect instead. *[static]*
- **`0x00312AB0`** - Animation channel progress: elapsed / duration using scalar DIV.S (round to nearest). *[static]*
- **`0x00312AE8`** - Tests whether a channel's primary (first) sequence is complete by returning its completed flag seq+0xC0 (not an AFL marker flag). Used as mainCompleted by the air animation selector and as (anim, 2) in uber phase 0. *[static]*
- **`0x00312B18`** - Completion replacement: removes the sequence (`0x003145F8`), plays a semantic with blend -1, copies +0x94/+0x98 and calls `0x00313A10` if +0x9C != 0, preserving the replaced sequence's weight/fade. Returns its semantic. *[static]*
- **`0x00312BD0`** - Completion play: moves flag bit 63 to the raised word via `0x00144670`, then plays via `0x003128E8` with the state blend so the finished clip fades out; returns the play result. Used by completion kind 6 for the rail cycles and probably by the kind-9 handler `0x00104BD8`. *[PS2]*
- **`0x00312C20`** - Compressed animation scalar sampler. *[static]*
- **`0x003135B0`** - Advances a sequence's primary slot clock (dt * slot rate * sequence rate) with loop wrap and authored event flags, setting completion seq+0xC0. Uses `0x00313868` (event interval boundaries), `0x00313938` (seek-time equality) and `0x003139A8` (completion); flag words seq+0xB0 latched, +0xB8 new, +0xC4 seek. Handles reverse play and multiple wraps per step. *[static]*
- **`0x00313800`** - Per-tick animation sequence fade advance. *[static]*
- **`0x00313868`** - Event interval boundary test used by the clock/event advance `0x003135B0`. *[static]*
- **`0x00313938`** - Seek-time equality event test used by `0x003135B0`. *[static]*
- **`0x003139A8`** - Completion event handling used by `0x003135B0`. *[static]*

## `src/animation/animsequencer.cpp`

Segment `0x00313A10`-`0x00314CB0`.

- **`0x00313A10`** `cAnimSequence_fadeWeight__FP13cAnimSequenceff` - Sequence fade-to helper; used by attack control and by completion replacement `0x00312B18` when the source sequence's +0x9C is nonzero. *[static]*
- **`0x00313C50`** - Assigns a clip to a sequence playback slot: +4 clip, +0x10 duration = (u16 frames-1)*(1/30), sets the seq+0xC4 seek; if the slot was disabled (+0x18 == 0) initializes time 0, rate 1, weight 1, enabled and loop. An already-enabled slot keeps its time and rate when the clip changes. Called every tick by `0x001043F8` for slot 1. *[static]*
- **`0x00313CF0`** - Seeks a playback slot: sets its time and the seek flag. *[static]*
- **`0x00313D28`** - Sets a playback slot's weight. *[static]*
- **`0x00313D40`** - Sets a playback slot's loop flag. *[static]*
- **`0x00313D70`** - Computes sequence fade weights. *[static]*
- **`0x00314418`** - Emits the model's animation descriptors. *[static]*
- **`0x00314518`** - Initializes a sequence's primary playback slot; called from sequence creation `0x00311F00`. *[static]*
- **`0x003145F8`** - Removes an animation sequence (the owning sequence container performs the removal); used by completion replacement `0x00312B18` and when a stop/removal fade completes. *[static]*
- **`0x003146D0`** - Fades a channel's sequence list; called by channel fade `0x00311E88`. *[static]*
- **`0x00314718`** - Removes completion marker/flag 63 from a channel's sequences; called by channel fade `0x00311E88`. *[static]*
- **`0x00314760`** `cAnimSequencer_getSequence__FP14cAnimSequenceri` - Sequence list accessor; `0x00311B20` calls it with list index 0 to get a channel's first playback sequence (used for set-rate). Also on the stance-restore path. *[static]*

## `src/animation/gameanimmap.cpp`

Segment `0x003150B0`-`0x00316898`.

- **`0x003158E0`** - Setter for the animator's pending next rate animator+0x1C, which the next new sequence takes as its rate. *[PS2]*
