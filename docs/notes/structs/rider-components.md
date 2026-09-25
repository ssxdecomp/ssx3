# Rider component layouts

Partial layouts of the objects owned by or attached to an SSX 3 rider (PS2 executable SLUS_207.72): the motion owner and its controllers, the score object, geometry, animator, air predictor, collision body, rider FX components, computer-rider state and a few related records. They were gathered from reading the code and checking the running game; only identified fields are listed, and gaps are unknown, not padding. **(PS2)** marks fields whose meaning was checked against the game running on a PS2 emulator; **(unconfirmed)** marks inferences.

Offsets are relative to the start of each object. Rider offsets (`rider+0x...`) refer to the rider object described in "Rider object layout".

## Score object

0x1CC bytes. Reached as *(rider+0x790); owning rider at +0x1AC, HUD message bank at +0x1B0. Passed to the landing/commit boundary 0x00119D40, the takeoff boundary 0x00119E38 and the scoring calls 0x00119918, 0x00119938, 0x00119958. The records named score object, trick score object/state and grab-score object all describe this object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Stance flag: set at landing (0x00119D40) to (rider+0x320 XOR rider+0x324) != 0 | PS2 |
| +0x4 | int | Alternate-table flag: landing sets ground normal.z < 0.7; takeoff 0x00119E38 sets it from the ramp branch (at 0x00114660) | PS2 |
| +0x8 | int | Multi-trick flag; nonzero skips repeat matching and insertion | PS2 |
| +0xC | | Style value | PS2 |
| +0x10 | int | Flag copied from rider+0x330 (board-press style) at landing by 0x00119D40 | PS2 |
| +0x14 | float | Pending trick reward (points / 10000 before multiplier): begin adds points x 1e-4, held ticks add +0x3C, rails add distance x 0.00005; divided by repeats + 1; 0x00117948 converts it to points | PS2 |
| +0x18 | | Multiplier; a multiplier icon pickup (0x00119448) raises it to the icon value when lower and posts HUD slot 4 | PS2 |
| +0x1C | float | Inverted-points accumulator: += distance x 0.0002 while the board up z is negative on rails, plus the stall bonus (b/1200 per tick); 0x00117908 converts it (INVERTED! message) | PS2 |
| +0x20 | int | Trick style value: seeded by 0x00119D40, updated by rail rotation scoring 0x00119918; nonzero (special records with +0x28) skips repeat history | |
| +0x24 | float | Rail (grind) distance in cm, not seconds: advances by speed x 1/60 (scaled); -1 when inactive (0x00117838), started by 0x00119D40 on rail entry; restored by Uber score end | PS2 |
| +0x28 | int | Flag field of special records; nonzero skips repeat history | |
| +0x2C | | Manual timer, accrued per tick by 0x00117C28; reset to -1 by 0x00117838, started by 0x00119D40 when applicable | PS2 |
| +0x30 | float | Air time accumulator (seconds); restored by Uber score end | PS2 |
| +0x34 | float | Spin amount of the current trick; sign-adjusted in place by the identity builder | PS2 |
| +0x38 | float | Flip amount of the current trick; sign-adjusted in place by the identity builder | PS2 |
| +0x3C | float | Hold increment added to +0x14 each held tick (hold points / 600000); start of the hold block +0x3C..+0x48 | PS2 |
| +0x40 | float | Current hold seconds, -1 when inactive; + time scale / 60 per held tick; begin sets 0 if negative, end adds it to +0x44 and sets -1 | PS2 |
| +0x44 | float | Total hold seconds, added by score end 0x001197D8 | PS2 |
| +0x48 | float | Longest hold seconds, updated by score end 0x001197D8 | PS2 |
| +0x4C | int | Normal trick count (score IDs below 19), incremented by 0x001197D8 | PS2 |
| +0x50 | int | Tweak trick count (score IDs 19..34) | PS2 |
| +0x54 | int | Uber count for the current air (score IDs 35+); all commit at landing and advance the tier by this count; read by the pending-letter widget (at 0x00118AF8) | PS2 |
| +0x58 | int | Super-Uber count. Tier notes: Ubers done at tier 10; grab-scoring notes: Uber end with rider tier (rider+0x2F4) >= 6; unresolved | PS2 |
| +0x5C | | Active Uber flag/identity: set by begin for IDs >= 35, cleared by end, preserved across the 0x00119D40 reset; the pending-letter widget adds 1 when nonzero | PS2 |
| +0x60 | | Grabs array [3] | PS2 |
| +0x6C | float | Active seconds timer (negative = inactive), restored after the 0x00119D40 commit/reset | |
| +0x70 | int | Active flag, saved before the commit callback and restored by 0x00119D40; nonzero skips repeat history | |
| +0x74 | | Counter incremented together with the Uber count | |
| +0x7C | int | Identity field; nonzero skips repeat history | |
| +0x84 | int | Trick bonus points from hold/distance threshold bonuses (separate from the pending points) | PS2 |
| +0x88 | | Threshold indices (+0x88..+0x98), updated by 0x00119210 from the per-tick update | PS2 |
| +0x8C | int | Hold threshold index into the authored 3/6/9 s bonus list; advances once per crossing; not cleared by 0x001176F8 | |
| +0x9C | int | Combo trick count; combo multiplier = clamp((count + 10) x 0.05, 0.5, 2) in 0x00117638 | PS2 |
| +0xA0 | | Combo points | PS2 |
| +0xA4 | float | Combo clock (timeout): counts down on the ground, payout 0x00117718 at expiry; -1 suspends it (0x001176F8); kept by score end and by the landing reset 0x00117838 | PS2 |
| +0xA8 | | Repeat history: 10 trick identities of 8 bytes (+0xA8..+0xF7), maintained by 0x001190F0; a monster trick stores {0, id << 27} | PS2 |
| +0xF8 | int | Repeat history cursor (mod 10) | PS2 |
| +0xFC | | Start of the run statistics block (+0xFC..+0x1A8), recorded per character by 0x00155420 at the end of each Conquer the Mountain run | PS2 |
| +0x110 | int | Run trick count | PS2 |
| +0x114 | int | Run (cumulative) Uber count; drives Uber tier progression at landing (checked against the committed increment in 0x0010E910); personal best for Ubers | PS2 |
| +0x118 | int | Run super-Uber count (personal best DoSupUber) | PS2 |
| +0x11C | int | Run Uber-grind count (personal best DoUberGrind) | |
| +0x120 | int | Reset count (incremented by 0x00119368) | |
| +0x128 | int | Knockout count, incremented by 0x00119400 on the attacker (personal best KOPeopleRace) | PS2 |
| +0x130 | int | Multiplier icon pickup count (incremented by 0x00119448) | PS2 |
| +0x134 | int | Run combo trick count | PS2 |
| +0x14C | float | Run air statistic (StayInAir personal best, stored rounded) | |
| +0x154 | float | Run rail statistic (StayOnRail personal best, stored rounded) | |
| +0x158 | float | Run handplant statistic (HoldHandplant personal best, stored rounded) | |
| +0x16C | | Run grade statistics | PS2 |
| +0x184 | | Best combo, first word (personal best DoXCombo) | PS2 |
| +0x188 | | Best combo, second word | PS2 |
| +0x18C | | Best trick | PS2 |
| +0x198 | int | Total score: trick commits add to it, finish payout 0x001193E0 adds the open combo; freestyle heat score (0x00239230), rank key in rank mode 2 (0x0010F998), HUD slot 7 | PS2 |
| +0x1A0 | | Lost points, first word | PS2 |
| +0x1A4 | int | Lost points, second word: accumulated lost points (adds the 0x0011A7A8 result on a score reset) | PS2 |
| +0x1AC | ptr | Owning rider | PS2 |
| +0x1B0 | ptr | HUD message bank (44 slots of 0x9C bytes) | PS2 |
| +0x1B8 | | Renderer bitmask | PS2 |
| +0x1C4 | float | Score multiplier: 1 after construction; kept by the landing reset 0x00117838 | PS2 |

## Motion owner and rider FX container

Reached as *(rider+0x77C). Holds the motion receivers, control objects, input provider and the rider FX components (components reset by 0x00111890 and updated in order at 0x00128F20..0x001290F0). On computer riders +0xDF0..+0xF3F is a 0x150-byte NPC extension, serialized after the common owner. The records named motion owner, motion/control owner, owner, active motion owner, RFX and rider effects object all describe this object; a few more fields reported as rider offsets are listed in "Rider object layout".

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | int | Tick at which the ground gained focus (takeoff and landing timers) | PS2 |
| +0x14 | | Set to -1 by takeoff 0x00114298 (after a passive takeoff the next landing keeps full speed); stamped by the ground motion exit 0x0013F410; 0 at event start | PS2 |
| +0x20 | struct | Air motion receiver (mode 1); its first word is a flag set when entering air from handplant motion 5, read by the air orientation tail | PS2 |
| +0x30 | struct | Wipeout (crash) motion receiver (mode 2); first word = submode: 0 grounded/sliding ragdoll (0x00137D18), else airborne ragdoll (0x00137750); read by 0x001231A8, 0x001057B8, 0x00105D98, 0x001210B0 | PS2 |
| +0xA0 | struct | Mode-3 motion receiver | PS2 |
| +0xB0 | struct | Rail motion receiver (mode 4); see "Rail motion state" | |
| +0x110 | struct | Handplant motion receiver (mode 5); its +0x10 is set once the launch has been computed | |
| +0x1D0 | struct | Board-press control object (control 1); see its section | PS2 |
| +0x200 | | Region +0x200..+0x2FF holding the air-control state (as logged by a capture hook) | unconfirmed |
| +0x210 | struct | Passive-air controller state; see its section | |
| +0x230 | struct | Air control object; its +0x58 is the rider pointer | |
| +0x2B0 | struct | Rail control state (control 7); see its section | |
| +0x350 | | Reset flag: records whether the reset reason was > 0 | |
| +0x390 | struct | Rail Uber control object (control 12); see its section | |
| +0x394 | int | Held rail Uber identity 0..3 (+0x4 of the control-12 object), set by 0x00132620; indexes table 0x00458230 on control-12 rail loss | |
| +0x3B0 | struct | Wake FX component; its first word is the wake ring cache pointer | |
| +0x3B4 | int | Wake ring row count | |
| +0x470 | struct | Board sparks FX component (sparks, glints, grind chunks; emitter 0x002DABC8); reacts to contacts | PS2 |
| +0x520 | struct | Board track FX component | |
| +0x610 | struct | Boost FX component | |
| +0x9C0 | struct | Power-up aura FX component | |
| +0xAD0 | struct | Air streamers FX component | |
| +0xAF0 | struct | Rival indicator (relationship icon '!') component: update 0x002D4C08, draw 0x002D5048, reset 0x002D4BE0 | |
| +0xB00 | struct | Rival locator beam component: update 0x002E39D8, draw 0x002E3AF8, reset 0x002E3930 | |
| +0xB40 | struct | Snow FX component (rider snow FX state), passed to 0x002E23E0 by 0x00111AA0; reacts to contacts | |
| +0xC70 | struct | Attack fist sparkle component (emitter 0x002F1150); reacts to contacts | PS2 |
| +0xD20 | struct | Unresolved: cheat toggle component (component list) or boost/pad feedback object passed to 0x002F6AC8 (boost notes) | |
| +0xD27 | u8 | Flags byte of the +0xD20 object: 0x002F6AC8 ORs in 0x10 on press feedback; bit 6 is the handplant attempt flag | |
| +0xD30 | struct | Light list component (first in the update order): ambient RGB plus a counted set of directional RGB/vector pairs, read by 0x001220D8 via 0x00389558, 0x00389520, 0x00389308 | |
| +0xDE0 | int | Motion mode: 0 ground (cruise), 1 air, 2 crash (wipeout), 3, 4 rail, 5 handplant | PS2 |
| +0xDE4 | int | Control state id (0..13) | PS2 |
| +0xDE8 | ptr | Input provider interface (see its section); computer riders point to vtable 0x004585F0 | PS2 |
| +0xDF0 | | Human: pad input context pointer. Computer: first word of the NPC extension, the start steering amount, drawn with its sign by the start command (two RNG draws at the first countdown pass) | PS2 |
| +0xDF8 | | Human: accepted command recorder pointer (RLE of the input commands actually consumed, whose tick can differ from pad input). Computer: NPC float parameter | PS2 |
| +0xDFC | float | Human: rumble impact strength; crash, landing (0x0010EAD8), obstacle (0x00105E7C) and instance (0x00105C30) hits store max(current, a); decayed and sent to the motors by 0x00125B18 | PS2 |
| +0xE00 | | Human: rumble slide / get-up level, set directly (crash phase 2 at 0x0012D23C, get-up slide event at 0x0012D8E8), decayed by 0x00125B18. Computer: route score context role (0 race rival, 2 trick-planning jam rival) | PS2 |
| +0xE04 | int | Computer: route score context allow flag | unconfirmed |
| +0xE08 | int | Computer: route score context randomize flag | unconfirmed |
| +0xE20 | int | Computer: rail output word copied from an unwritten 0x0010B980 stack slot on the no-jump-zone path (0 in captures) | PS2 |
| +0xE24 | int | Computer: air state cleared by the 0x0010B250 grab-release branch | |
| +0xE2C | float | Computer: grab-release threshold; release when the remaining time <= value + 0.3 | |
| +0xE34 | int | Computer: state cleared by 0x0010A768 when the current control is not 5 | |
| +0xF44 | struct | Computer: behavior member-function descriptor (s16 this-adjust, s16 virtual index, u32 target), not a command cache | PS2 |

## Rider geometry

Reached as *(rider+0x780); a front-end preview holds one at its slot +0x8. Bone indices used with it come from rider+0x89C..+0x8A8. The records named rider geometry, geometry/pose object and bone geometry record (board bone 23) all describe this object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | int | Part count | PS2 |
| +0xC | ptr | Model-part records, 0x58 bytes each | PS2 |
| +0x24 | vec4[] | Local bone positions, one float4 per bone (current scaled local root data, read before world FK/IK) | PS2 |
| +0x28 | quat[] | Local bone quaternions | PS2 |
| +0x2C | ptr | World bone transforms, 32 bytes each (position then quaternion); input to the pose matrix build 0x00310120 | PS2 |
| +0x30 | ptr | World bone matrices, 64 bytes each (unit axes, row 3 = translation in cm), written by 0x00310120; bone 23 gives the unscaled board frame used by snow; indexed by rider+0x8A8 | PS2 |
| +0x34 | ptr | Scaled bone matrices (axes scaled by +0x140): board tracks and the wake (scaled board axis) use them; also cited as a skinning input with +0x38 | PS2 |
| +0x38 | ptr | Static inverse bind matrices (29 slots, constant across captures), multiplied with the scaled pose by 0x00310640 | PS2 |
| +0x140 | vec4 | Body (pose) scale XYZW applied per column by 0x00310120: model size x 0.01, e.g. (0.85,0.85,0.85,1); 1.0 on the front-end preview; grid spot, normals and lift follow it | PS2 |
| +0x150 | u64 | Bone mask intersected with the sequence mask by the local sampler | PS2 |
| +0x158 | u64 | Reduced bone mask used when rider+0xB1C is nonzero (at 0x0030F4F4) | PS2 |

## Rider animator

Reached as *(rider+0x784).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int[6] | Requested semantic per channel (+0x00..+0x14), read by 0x00312AA0 and 0x00311AE8 | PS2 |
| +0x18 | int | Mirror flag (= rider+0x320 after a stance flip) | |
| +0x1C | float | Pending playback rate for new sequences: applied by 0x00311F00, set by 0x003158E0, reset to 1 by 0x00311A50 and the air selector; 0x0012C678 sets 0.75 around the finish reaction, then 1 | PS2 |
| +0x20 | int | Bone mask for the play call; normally -1, set from rider+0x8C0 during upper-body plays | |
| +0x30 | vec4 | Default root translation for new sequences (set from 0x004FF130) | |
| +0x40 | quat | Default root quaternion for new sequences (sincos about 0x004FF160) | |
| +0x50 | ptr | Six 8-byte sequencers (count, linked-list head), one per channel | PS2 |
| +0x60 | ptr | Owning rider (normal variant filter source rider+0x364) | |
| +0x64 | ptr | Alternate actor (variant filter at actor+0xCD8); 0 in the checked Snow Jam starts | |

## Air trajectory predictor

Reached as *(rider+0x788); seeded and restarted by 0x001135B8. The records named air predictor, air trajectory predictor and air landing predictor all describe this object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | vec4 | Predicted landing heading; used by the air stance-switch test and the camera landing angle | PS2 |
| +0x20 | vec4 | Predicted landing normal ((0,0,1,0) in savestates); camera landing angle input | PS2 |
| +0x98 | float | Predicted flight time T (s); camera slot 0x60; cleared on landing | PS2 |
| +0x9C | float | Predicted landing time | |
| +0xA0 | float | Elapsed air time | |
| +0xA8 | float | Speed cap for air integration (3333.33 cm/s) | PS2 |
| +0xAC | int | Prediction status 0..3; 1 or 3 = in flight (camera and big-air logic) | PS2 |

## Rider collision body

Reached as *(rider+0xAA0): a broad-phase sphere plus up to 20 bone-attached spheres, built at pose time.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | vec4 | Broad-phase sphere centre | |
| +0x20 | float | Broad-phase sphere radius (cm; 78.2 for Zoe) | PS2 |
| +0x28 | u32 | Active sphere mask: 3 (spheres 0/1, lower spine and head) around obstacle queries 0x0013F488/0x0013AA48, all bits set before instance contact 0x00105398; ignored by pair overlap 0x00329F98 | PS2 |
| +0x2C | u32 | Number of spheres in use (10 for riders) | PS2 |
| +0x30 | struct[20] | Sphere slots, 32 bytes each: +0x0 centre float4, +0x10 radius, +0x14 bone index, +0x18/+0x1C two aux words; riders use bones 1,5,7,9,12,14,16,17,19,20 | PS2 |

## Rider snow FX state

FX component at motion owner +0xB40 (snow emitters, BodySnow and the breath emitter); passed to 0x002E23E0 by 0x00111AA0. The breath emitter fields (+0x14..+0x24, +0xBC) are reported relative to the same parent+0xB40 object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | float | Impact buildup: raised up to 2.0 by crash impacts; BodySnow active while > 0; decays 1/60 per tick outside motion 2 | |
| +0x10 | float | Kicker carry-off buildup (1.37 captured) | |
| +0x14 | float | Breath emission accumulator | PS2 |
| +0x18 | int | Breath phase, toggled when the phase clock expires | PS2 |
| +0x1C | float | Breath effort: snaps up to the target, decays by 1/600 per call | PS2 |
| +0x20 | float | Breath phase clock (+1/60 per call) | PS2 |
| +0x24 | float | Breath phase duration: 0.4 when active, else (1 - effort) x 0.6 + 0.4 | PS2 |
| +0x2C | struct | Emitter profile parameters; +0x2C+0x900 is emitter 9 VelScale (0.8) | |
| +0x60 | int | Deactivate-all request (cleared by 0x002DF448) | |
| +0x78 | int | BodySnow bone cursor (0..29) | |
| +0x7C | ptr | 30-word BodySnow bone index table (heap) | |
| +0x80 | int | BodySnow bones-bound flag | |
| +0x90 | vec4 | Emitter colour (2R, 2G, 2B, 1) from the environment colour; reset to (1,1,1,1) | |
| +0xB0 | int | Ground emission flag (false in motion 2, disabling trail, cloud and carve chunks) | |
| +0xB8 | float | Cached rider speed (length of rider+0x1E0) | |
| +0xBC | float | Absolute cached speed; above 1111.11 cm/s disables breath | |
| +0xD4 | int | Cached motion mode (from 0x0011FE98) | |
| +0xE0 | float | Retained snow impact strength (one note writes it as FX+0xE0 and reports it bit-exact against PS2 captures) | |
| +0x120 | float | Impact alpha (reset 0.5) | |
| +0x12C | float | Edge bias, usually 0; derived from rider+0x330 (board-press style), animation and stance, not from turn input | |

## Rail motion state

Motion 4 receiver at motion owner +0xB0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | vec4 | Rail direction (tangent oriented along travel); 0x00105398 uses plus or minus it as the contact normal when no other projection applies | |
| +0x10 | float | Rail lean angle (rad) | |
| +0x14 | float | Time on rail | |
| +0x18 | float | Rail balance -1..1: lateral offset / 70 (styles 3/4) or / 30 (styles 1/2) | |
| +0x1C | float | Heading offset, clamped to +/-45 deg by 0x0013ADC0 | |
| +0x20 | int | Lost-rail flag | |
| +0x24 | u32 | Current rail packed id (from the rail header +0x00) | |
| +0x30 | vec4 | Rail entry position, used as the previous contact position by the stuck test | |
| +0x40 | float | Stationary timer; zeroed on rail enter | |

## Board-press control (control 1)

At motion owner +0x1D0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Phase: 0 press in, 1 hold, 2 pivot finish, 3 release | PS2 |
| +0x4 | float | Time in the press | PS2 |
| +0x8 | float | Time at full depth; over 1 s triggers the crash | PS2 |
| +0xC | float | Idle (no input) time; 0.5 s releases the press | PS2 |
| +0x10 | | R3 latch for the ollie | PS2 |

## Passive-air controller state

At motion owner +0x210.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Entry angle atan2(current crouch, current turn) | |
| +0x4 | float | Entry magnitude max(abs(turn), crouch); set to -1 once identity/direction releases | |
| +0x8 | | Upper latch (starts 1); while set, the upper-action return is checked | |
| +0xC | | Identity latch (starts 1); tracks a continuously held grab identity | |
| +0x10 | int | Signed last grab identity (-1 = none at entry) | |
| +0x14 | ptr | Actor (rider) backlink | |

## Rail control state (control 7)

At motion owner +0x2B0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Accumulated rail spin (+/- pi/2 per rotation) | |
| +0x4 | s8 | Last rail identity byte (-1 = none) | |
| +0x8 | ptr | Rider | |

## Rail Uber control (control 12)

At motion owner +0x390.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Control-12 state | |
| +0x4 | int | Requested Uber identity 0..3 (motion owner +0x394) | |
| +0x8 | ptr | Rider | |

## Crash control (control 8)

Location inside the motion owner not recorded. The ragdoll crash control of the snow/crash notes is taken to be this object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x54 | | Unresolved: integer impact flag (crash notes), or the start of the ragdoll body-vs-scenery collision event slot from 0x00105D98, spanning +0x54/+0x60 (snow/crash notes) | |
| +0x60 | | Impact velocity | |
| +0x70 | float | Recovery meter | |

## Air control state

Base object not named; may be the air control object at motion owner +0x230.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x28 | float | Air-adjust spin (up to 100 degrees) | PS2 |
| +0x30 | float | Scored rotation field used by trick commit (with +0x34) | |
| +0x34 | float | Scored rotation field used by trick commit | |

## Air/spin control (control 5)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | int | Air control mode; 3 (spin) allows handplant entry | |

## Natural air control (control 4)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | | Attack latch, consulted before calling the attack control | |

## Grab lifecycle state owner

Object used by the grab lifecycle 0x001352A8; owner not identified. Rail notes use rider+0x238 as the rail balance triplet, so the owner may be the rider with controller-specific reuse of that area.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x234 | | Grab lifecycle phase (states 0..5) | |
| +0x238 | | Grab index for the lifecycle; set to -1 on the state-5 reset | |

## Cruise ground controller (mode-0 motion receiver)

Location inside the motion owner not recorded.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | float | Smoothed powder depth, approaching the scaled target at up to 100 cm/s (with +0x8) | PS2 |
| +0x8 | float | Second smoothed powder depth | PS2 |

## Input provider interface

At *(motion owner +0xDE8).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | ptr | Provider routine/object (human: 0x00127998) | PS2 |

## Pad input context (human riders)

At *(motion owner +0xDF0).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | ptr | Pad object; button records at pad+4+i*0x1C | PS2 |
| +0x4 | ptr | Compiled input mapping (INPUT.MAP) | PS2 |

## Accepted command recorder (human riders)

At *(motion owner +0xDF8).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Record count | PS2 |
| +0xC | ptr | Record buffer (8-byte RLE records) | PS2 |

## Crash motion object (motion 2)

These offsets equal the rider's detached-board fields rider+0x130..+0x150, and the wipeout receiver at motion owner +0x30 is too small to contain them, so they may be rider fields.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x130 | vec4 | Detached board position | |
| +0x140 | vec4 | Detached board quaternion | |
| +0x150 | | Detached flag; board position and quaternion evolve independently when set | |

## Crash collision event

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | vec4 | Contact point (reported by crash entry) | |
| +0x20 | vec4 | Contact normal | |
| +0x30 | float | Closing speed | |

## Landing contact record

Record handled by 0x0010E910.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | vec4 | Landing point | |
| +0x10 | vec4 | Landing normal | |
| +0x4C | int | Landing surface | |

## Rider camera-target interface

Virtual slot offsets of the interface the camera uses to read its target rider.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | vfunc | Head position (0x0011FF48; bone rider+0x89C) | |
| +0x18 | vfunc | Velocity (rider+0x1E0, w = 0) | |
| +0x20 | vfunc | Rider forward (re-read by set-target 0x00166C60) | |
| +0x48 | vfunc | Previous contact normal (rider+0x380) | |
| +0x60 | vfunc | Predicted air time, *(rider+0x788)+0x98 | |
| +0x80 | vfunc | Wall normal rider+0x3C0 (set when contact normal z < 0.05) | |
| +0x88 | vfunc | Boost level rider+0x2FC (0/0.25/0.625/1) | |
| +0x90 | vfunc | Filtered crouch rider+0x220 (0x0015F710) | |
| +0x98 | vfunc | Trajectory active: *(rider+0x788)+0xAC is 1 or 3 | |
| +0xA0 | vfunc | Surface id rider+0x438 | |
| +0xA8 | vfunc | Launch value rider+0x5A4 | |
| +0xB8 | vfunc | Landing angle (getter 0x0015F780) | |
| +0xC0 | vfunc | Proximity flag rider+0x5AC | |

## Rider interface vtable, rumble slots

Vtables 0x004583A8 (human) and 0x00458660 (computer); the other known slots are listed in "Rider object layout".

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x88 | vfunc | Rumble impact: motion owner +0xDFC = max(current, amount) | PS2 |
| +0x90 | vfunc | Rumble slide: motion owner +0xE00 = amount | PS2 |

## Rider pair record

0x24 bytes, six per rider (one per opponent slot); the rider notes place the +0x10 field at rider+0x10+slot*0x24. Initialised by 0x0010F3B8 and refreshed by the rider-manager pass 0x0010F560. The records named rider pair record and rider-manager pair proximity record describe this record.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | | Peer-is-human flag | |
| +0x8 | float | Initialised to 1e10 by 0x0010F3B8; probably a cached planar distance refreshed by 0x0010F560 | unconfirmed |
| +0x10 | int | Last-contact tick; impulses only when it is older than the current tick - 3; written for both actors after both responses | |
| +0x14 | int | Last-checked tick; when older than the current tick, both records are stamped before the query | |
| +0x18 | int | Attack cooldown timestamp of the reciprocal record | |
| +0x1C | | Rival flag, set by 0x0010F560 when the relationship level is >= 2 | PS2 |

## Score HUD message slot

0x9C bytes; 44 slots in the bank at score object +0x1B0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Slot type (0x34 = free); a type below 0x22 owns slot [type]; 0x00117A58 allocates a slot for types 0x23 and above | PS2 |
| +0x4 | float | Maximum; -1 marks a persistent value slot | PS2 |
| +0x8 | float | Value: elapsed time (0x00116FB8 adds 1/60 per tick); value slots store -input, so value / maximum gives the fraction | PS2 |
| +0xC | | Argument (count/tier passed as a3 of 0x001171A8); read by the renderer at 0x001ECC74/0x001ECC84; for slot 9 it selects the flash palette tier | PS2 |
| +0x10 | | Auxiliary word; the game never clears stale front-end words here in slots 5, 6, 7 and 0x19 | PS2 |
| +0x14 | | Points | PS2 |
| +0x18 | ptr | Text pointer (a trick name or '%d') | PS2 |

## Character table row (CHARDB)

Table at 0x00530970, 0x88 bytes per rider.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | Long name string | |
| +0x20 | | First name string; used to build text keys such as kT_FULLBIO1<Name> and kT_DNA1..8<Name> | |
| +0x30 | | Nickname string | |
| +0x40 | | Rider weight; feeds the rider-pair collision inputs through 0x0011FF98 (a cheat skin keeps its base rider's weight) | |
| +0x44 | | Stance: 1 = goofy (Moby, Psymon, Elise, Allegra) | |
| +0x48 | | Model size; model scale = size x 0.01 (Elise 96 gives 0.96) | |
| +0x4C | | Blood type (bio field) | |
| +0x5C | | Female flag | |
| +0x60 | | Age (bio field) | |
| +0x64 | | Height (bio field) | |
| +0x74 | | Nationality (bio field) | |

## Rider attribute bytes

Seven bytes per character at 0x00535538 + player*70 + character*7. Raw values are shown in the game as raw x 0.2.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u8 | Speed attribute | |
| +0x1 | u8 | Acceleration attribute | |
| +0x2 | u8 | Tricks attribute | |
| +0x3 | u8 | Edging attribute | |
| +0x4 | u8 | Spin attribute | |
| +0x5 | u8 | Toughness attribute | |
| +0x6 | u8 | Stability attribute | |

## Rail query result

Output record of the rail query 0x00334680.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | vec4 | Closest rail point | |
| +0x10 | vec4 | Unit tangent | |
| +0x20 | vec4 | Normal (zero for splines) | |
| +0x30 | vec4 | Velocity (zero for splines) | |
| +0x44 | int | Hit kind (2 for rails) | |
| +0x4C | int | Surface id (copied to rider+0x438) | |
| +0x50 | ptr | Instance (0 for static splines) | |
| +0x58 | ptr | Rail descriptor (record header) | |
| +0x68 | float | Curve parameter t | |

## Rail Uber record

Table at 0x0045A038, 0x24 bytes per record; record k (0-based) holds the semantics of Uber tier k + 1.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | INTO semantic for style 4 (RSBS_INTO_FS_GRINDn, 213 + 8k) | |
| +0x4 | int | INTO semantic for style 3 (RSFS_INTO_FS_GRINDn, 214 + 8k) | |
| +0x8 | int | INTO semantic for style 2 (RSFAKIE_INTO_FS_GRINDn, 215 + 8k) | |
| +0xC | int | INTO semantic for style 1 (RSREG_INTO_FS_GRINDn, 216 + 8k) | |
| +0x10 | int | CYC semantic (RSFS_GRINDn_CYC, 217 + 8k, driver kind 2) | |
| +0x14 | int | BAL_L semantic (218 + 8k, kind 10) | |
| +0x18 | int | LAND semantic (219 + 8k, kind 1) | |
| +0x1C | int | OUTOF semantic (220 + 8k, completion 8) | |
| +0x20 | int | Tier n (= k + 1) passed to the entry score 0x00119938 | |

## Animation channel sequence

Per-channel sequence data reached through the rider animator.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x84 | | Channel priority array, initialised from table 0x0048D808 = {3,2,1,0,0,0} | PS2 |
| +0x90 | float | Playback rate (the attack control writes 0 to freeze channel 1 and 1 to restore it) | |
| +0x94 | float | Blend weight (attack strength is copied here for class 13) | |
| +0x98 | float | Blend weight target | |
| +0x9C | float | Fade value/time | |
| +0xC0 | | Completion pulse flags; the crash semantics' pulses drive the control-8 phase machine | |

## Front-end / rider animator

Described in the character notes. Its +0x8 and +0x14 fall on the requested-semantic slots of the rider animator above, so this may be a different object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | | Current animation semantic; the Ubertrick preview writes the Uber's trick id here (0x7B Indian, 0x9E Pommel Me seen) | PS2 |
| +0x14 | ptr | Head of the playing sequence list (two entries during a crossfade) | PS2 |

## Alternate animation actor

Object at animator+0x64, used on the alternate (non-rider) path of 0x00104CF8.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xCD8 | u32 | Variant filter (semantic mask) flags read by 0x00104CF8 when animator+0x64 is set | |

## Rider snow emitter

0x210-byte class, vtable 0x004930D0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | int | Base texture id | PS2 |
| +0xC | int | Flipbook frame count | PS2 |
| +0x10 | float | Flipbook phase (1.5 / 4.5 / 3.0 for chunks 1/2/3, others 0.6667) | PS2 |
| +0x14 | float | Flipbook rate (LargeChunky 30, SmallChunky 45, Rock 45) | PS2 |
| +0x1F8 | ptr | Vtable pointer (0x004930D0) | PS2 |
| +0x200 | int | VU program / colour mode select; 0 selects the A00 program (all ten human emitters) | PS2 |

## Wake controller state

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x60 | vec4 | Fan coefficient | |
| +0x70 | vec4 | Fan coefficient | |
| +0x80 | vec4 | Drag coefficient | |
| +0x90 | float | Amplitude | |
| +0x94 | float | Alpha | |

## Wake physics row

0x70-byte stride.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | vec4[] | Column vectors (+0x00..+0x40) | |
| +0x50 | vec4 | Drag vector | |
| +0x60 | float | Caller value (drives the initial growth term) | |
| +0x64 | float | Zero-initialised value, probably the row age | unconfirmed |

## Boost effect object

Rider FX boost ribbon state; the boost effect parameter block records give the same fields.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | int | Primary ribbon row count | |
| +0x18 | float | Primary ribbon distance | |
| +0x3A0 | int | Side history count | |

## Rider query scope (nearby-object cache)

Reached as *(rider+0x860); rebuilt from the rider query bounds.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x210 | int | Nearby layer count (the lighting notes give +0x210/+0x214 as the light candidate list without the split) | PS2 |
| +0x214 | array | Nearby layer entries iterated by the rail query 0x00334680; light candidates (extra nodes) consumed by selector 0x002F5B68 | PS2 |

## Rider environment record

Record at 0x004FA370 + slot*0xF0. The rider notes index 0x004FA398 (this table + 0x28) with the same stride.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x28 | u32 | ARGB environment colour (board trails; snow doubles the RGB) | |
| +0x38 | vec4 | Lighting ratio (target / base) | |

## Rider environment irradiance slot

Slot structure used at 0x002ED92C; its base is not identified.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x24 | float | Alternate irradiance bank selector (> 0.1 blends toward the third bank); updated at 0x002ED5B4 (x 0.9, + 0.1 while rider+0x3FC is set); starts 0 | unconfirmed |

## Rider manager / race clock

Reached as world+0x0C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Race clock phase (3 PreRace, 4 Countdown, 5 Race, 6 EndRace) | |
| +0x8 | int | Total game ticks, incremented at the end of the rider-manager update 0x00128AF0 (0x00129134..0x00129144) | PS2 |
| +0xC | int | Race ticks (the race timer), cleared on PreRace entry | |

## Rider manager (ranking)

Object refreshed by 0x0010F560; may be the same object as the rider manager / race clock above.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xEC | | Ranking storage written by 0x0010F998 (only the offset is given) | unconfirmed |

## AI / reset path record

Table at 0x004D33A8, 64-byte stride, 129 records.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x38 | | Path flags | |
| +0x3C | | Reset eligibility: must be nonzero for reset candidates (117 of 129 records) | PS2 |

## AI path runtime header

64 bytes, interface 0x00481478. Same size and field offsets as the AI / reset path record; may be the same record.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x38 | u32 | Authored flags (not the course remaining-distance float) | PS2 |
| +0x3C | u32 | Separate authored field | PS2 |

## Rail record

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1C | u32 | Runtime query flags | |
| +0x28 | u32 | Runtime surface | |

## Type-2 object rail (layer object)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x30 | u32 | Packed rail descriptor id, resolved via 0x002D1BD8 | |
| +0x34 | ptr | Transform input for 0x0034FED8 (with +0x40) | |
| +0x40 | ptr | Transform input for 0x0034FED8 (with +0x34) | |
| +0x50 | matrix | Transform composed with the instance/binding transform by 0x0035C5A0 | |

## Type-3 object rail (layer object)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x18 | ptr | Instance returned in the query result | |
| +0x20 | int | Segment count plus one (the loop runs count - 1) | |
| +0x24 | u32 | Flags checked before searching | |
| +0x50 | matrix[] | 64-byte cubic coefficient matrices, one per segment | |

## Rider model part header

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x20 | | Locator of the 20-byte material records in the part data | |
| +0x48 | int | Signed material (batch) count | |

## Rider bone-emitter controller

Vtable 0x004881D0; embedded at rider+0x88C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xA0 | int | Emit flag, set when its type-0x19 bone emits; cleared by 0x002F1A00 | |

## Rival locator beam component

At motion owner +0xB00.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x28 | vec4 | Beam colour (initial r 1, g 0, b 0, a 0.5) | |

## Career rider profile record

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xF70 | | Per-rider song ownership state | |

## UIPair

Vtable 0x00494868 (front-end UI element, not rider-owned).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x7C | ptr | Embedded control (list box or slider) | |

## LUN script function record

16 bytes per function in the program trailer (script VM, not rider-owned).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Byte offset back to the header, -(code end + 16 x index); not used by the VM | |
| +0x4 | int | Start pc of the function | |
| +0x8 | int | Register count; frame setup only reads record 0's count, even when entering another record | |
| +0xC | int | Argument-stack capacity; 0x002227D0 allocates capacity x 16 + 16 bytes when > 0 | |
