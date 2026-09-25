# Rider object layout

Partial layout of the SSX 3 rider object (PS2 executable SLUS_207.72), gathered from reading the code and checking the running game. Only fields that were identified are listed; gaps are unknown, not padding. Offsets are relative to the start of the object and field descriptions are plain-language, not decomp names. **(PS2)** marks fields whose meaning was checked against the game running on a PS2 emulator; **(unconfirmed)** marks inferences.

Notes on the table:

- The block +0x1F0..+0x2D3 holds 19 filter triplets of three floats each (current, rate, target), reset by 0x0011D660; several are approached every tick by 0x001211F8. Rows marked `float[3]` are triplet starts.
- Objects reached through the pointers at +0x77C (motion owner / FX container), +0x780 (geometry), +0x784 (animator), +0x788 (air predictor), +0x790 (score object), +0x860 (query scope) and +0xAA0 (collision body) are described in "Rider component layouts".

## Rider object (cRider)

Vtables 0x004583A8 (human) and 0x00458660 (computer), stored in the interface subobject at +0x6C0 (its methods adjust `this` by -0x6C0). Size and constructor not recorded; identified fields reach +0xB34.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 + 0x24*i | int | Last-contact tick in per-opponent pair record i, written at 0x00107BCC; consistent with six 0x24-byte rider pair records whose +0x10 is the last-contact tick | PS2 |
| +0x98 | | Per-rider object or field updated in the post-camera part of the game update (from 0x00230DC0); makes no RNG draws | unconfirmed |
| +0xE8 | | Place at the last checkpoint (copied from +0xEC by 0x0010E558) | |
| +0xEC | | Current place (copied to +0xE8 at a checkpoint) | |
| +0x100 | int | Celebrate flag: 1 on a rival win; cleared at 0-based place >= 3 (race) or > 0 (freestyle); control 10 phase 1 picks finish reaction 1 when set, 4 when clear | PS2 |
| +0x110 | vec4 | Physical position (cm, Z-up), normally the first pose root; sound position; source of the query bounds (0x0011E150); passed with +0x1E0 to the flight seed 0x001135B8 | PS2 |
| +0x120 | quat | Physical orientation quaternion (XYZW); spins are not written here (presentation is separate) | PS2 |
| +0x130 | vec4 | Detached board position (optional second pose root, used only when +0x150 is nonzero); set to the posed bone 22 at the Uber crash | PS2 |
| +0x140 | quat | Detached board quaternion (second pose root rotation) | PS2 |
| +0x150 | int | Detached board flag: enables the second pose root +0x130/+0x140; cleared by 0x0011D660 | PS2 |
| +0x160 | matrix | Pre-impact presentation frame (rows +0x160..+0x190) used by reaction classification 0x00105D98; taken before the body-only presentation lift | |
| +0x170 | vec4 | Last pose's board-root frame forward (row of the +0x160 frame), read by the air stance-switch test 0x00114DB8 | PS2 |
| +0x180 | vec4 | Retained presentation up (previous board-root up); the landing probe 0x0013A7B0 casts along it; copied into +0x370 each air tick (0x00139A70..0x00139A80, in 0x00139A20) | PS2 |
| +0x1A0 | vec4 | Physical right axis (basis column rebuilt by 0x0011E098); source of the attack facing +0x340 | |
| +0x1B0 | vec4 | Physical forward axis (from 0x0011E098); the camera's rider forward; used for the placement exit velocity | PS2 |
| +0x1C0 | vec4 | Physical up axis: shadow-fit normal; stance restore rotates about its old value; takeoff impulse direction in motion mode 4 | PS2 |
| +0x1E0 | vec4 | Velocity (cm/s, Z-up): cruise integration moves position by the old velocity / 60; camera slot 0x18; read for board trail edges (0x002E8F24); its size before the landing response is the snow-impact strength | PS2 |
| +0x1F0 | float[3] | First filter triplet: physical (effective) turn; zeroed on rail enter and crash entry, negated on stance flip; negated and passed to the lateral ground term 0x0013D028 | |
| +0x1FC | float[3] | Animation-turn triplet (+0x200 rate, +0x204 target) driving the five-way ground cycle; control 2 enter 0x0012E980 sets rate 1/30, target 0; control 7 enter rate 1/15, target 0; negated on stance flip | PS2 |
| +0x208 | float[3] | Extra-lean triplet (wake input); zeroed on rail enter and crash entry, negated on stance flip; ground exit 0x0013F410 zeroes its target (with +0x2BC, +0x2C8) | |
| +0x20C | float | Rate word of the +0x208 triplet by position; seen to differ on a crash tick when the motion-0 exit is skipped | unconfirmed |
| +0x214 | float[3] | Brake triplet (wake input); negated on stance flip | |
| +0x220 | float[3] | Crouch / jump-charge triplet (+0x224 rate, +0x228 target); filtered crouch from 0x0015F710 that the camera reads (slot 0x90) instead of the raw charge; takeoff uses the previous tick's value | PS2 |
| +0x22C | float[3] | Rail steer triplet written by 0x00113F38 (negative target with the stick left) | PS2 |
| +0x238 | float[3] | Rail balance triplet (+0x23C rate, +0x240 target) weighting the rail cycle blend (semantics 18/19/20), negated by the switch flag; control 7: target clamp(1.2 x balance) to +/-1, rate 1/15; Uber: rate 3.5/60 | PS2 |
| +0x244 | float[3] | Half-pipe / handplant balance triplet (control 11): written by 0x00132A30, zeroed by 0x00132F98; drives animation driver kind 9 (seek amount) | |
| +0x250 | float[3] | Presentation roll triplet read by 0x0011FA10; zeroed on rail enter and crash entry; control 11 reuses it as the handplant balance, and its phase-2 exit leans the rider by it before zeroing. See +0x274 | |
| +0x25C | float[3] | Rail attach-tolerance triplet: -0.25 on leaving a rail, then +1/30 per tick (0x001211F8); 2 while time on rail < 0.6; widens board half-width (30 vs 50 cm in 0x001086B8); reset sets current and rate to 1 | PS2 |
| +0x268 | float | Board-press depth 0..1 (triplet start); drives seeks of animation semantics 24/25/32/33 | PS2 |
| +0x274 | float[3] | Unresolved: board-depth triplet (kind-15 blend weight, the 1 s full-depth lock, the crash) per the board-press notes; the snow/wake notes call it presentation roll, which other notes place at +0x250 | unconfirmed |
| +0x280 | float[3] | Board pivot amount -1..1 (times pi gives the angle); balance control value negated by the stance toggle 0x00115168 | PS2 |
| +0x28C | float[3] | Air-adjust triplet: target = flip adjust input / 1.7453 (100 deg), rate 1/6; landing targets 0 at 1/60; driver kind 11 (0x001043F8 uses the larger of +0x28C/+0x298); fading adjust clips 297..304 keep reading it | PS2 |
| +0x298 | float[3] | Second air-adjust triplet: target = spin adjust input / 1.7453, rate 1/6 (spin/flip pairing unconfirmed); read by driver kind 11; also approached during board press | PS2 |
| +0x2A4 | float[3] | Prewind triplet (filtered); passive-air entry sets rate 1/30 and target 0; consumed by air-control entry 0x00133128 | |
| +0x2B0 | float[3] | Second prewind triplet (same handling as +0x2A4) | |
| +0x2BC | float[3] | Board-alignment weight triplet used by board correction; the ground (motion 0) exit 0x0013F410 zeroes its target and re-arms its decay | |
| +0x2C8 | float[3] | Presentation lift triplet (+0x2CC rate, +0x2D0 target): body-root lift applied in 0x0011EB98, target set at 0x0013E144; last of the 19 triplets | |
| +0x2D4 | u32 | Runtime flags of the contacted terrain patch (patch+0xA OR 0x40), written by ground contact 0x0013D1B8: 0x20 full-speed lip launch (0x00114298), 0x10 heading boost (0x0013C948), 0x2 ground reset (0x0013F178) | PS2 |
| +0x2DC | float | Retained manual spin rate: kept through passive flight and soft-collision landings, read by landing 0x0013A968; zero gates the prewind reverse turn. Motion notes read it as a cruise heading angle; unresolved | PS2 |
| +0x2E4 | float | Speed limit (3333.33 from 0x0011B3F8 in motion 1): cruise cap, takeoff and predictor speed cap (0x001135B8), rail speed clamp; carried over by arrivals | PS2 |
| +0x2E8 | float | Speed-boost pickup window (a pickup adds 5; enables the boost ribbon); zeroed with +0x2EC..+0x2F4 by the arrival tail 0x0011D390 and by a forced reset; not the stored meter | PS2 |
| +0x2EC | float | Boost / air-control modifier counter (a trick boost pickup adds 5); cleared by 0x0010E910 when the landing award is positive, and by a forced reset | PS2 |
| +0x2F0 | float | Tricky / Super Uber timer (s): > 0 allows Ubers, including rail Ubers; full meter sets max(value, 20); tier 10 sets 60; on expiry (0x001200D0) tier 5 with 20 s; drives HUD slot 9 | PS2 |
| +0x2F4 | int | Uber tier 0..10 (10 = Super Uber): 0 to 1 when Tricky starts, +1 per committed Uber up to 10; >= 5 selects the Uber tier variant; grab scoring counts super-Ubers at >= 6; 0 removes HUD slot 8 | PS2 |
| +0x2F8 | float | Stored boost meter 0..1: full (1.0 via 0x0010E098) starts Tricky; locked at 1 in Super Uber; not written by pickups; set from the finishing place in 0x00239230; carried over by arrivals | PS2 |
| +0x2FC | float | Boost amount 0/0.25/0.625/1 (0.25 while boosting in control 0): boost ribbon while > 0; collision weight x (1 + 10 x value) in 0x0011FF98; rail accel 2450 x value; camera slot 0x88; zeroed by 0x0011D660 | PS2 |
| +0x300 | float | Time scale (rubber band), dt = value / 60; written only by the pacing routine 0x00120090; 1 after 0x0011D660; boost timers use it | PS2 |
| +0x304 | int | Boost meter policy: 0 forces full, 1 normal decay, 2 fast decay, 3 awards return early, other values retain | |
| +0x308 | int | Contact / sticking branch flags; nonzero plus distance above surface+0x10 triggers a passive takeoff | unconfirmed |
| +0x310 | float | Weight of the late velocity-toward-board-forward blend in 0x002F6518 (0.18 observed) | PS2 |
| +0x318 | float | Leg IK weight (gate), moved by 0x00120D90 toward 0 (animation classes 20..26) or 1; 1 after 0x0011D660 | |
| +0x31C | float | Board lift: a separate cosine oscillator (not the +0x758 contact compression) | |
| +0x320 | int | Switch/reverse stance flag: toggled by 0x00115168, mirrored into animator+0x18, negates rail balance for driver kind 5; restored from +0x324 on reset; not changed by stance restore 0x00115640 | |
| +0x324 | int | Default (reference) stance, copied back into +0x320 by the reset tail 0x0011D660; landing stance for scoring = (+0x320 XOR +0x324) != 0 | |
| +0x328 | int | Grind / temporary stance style: 0 none, 1 50-50, 2 backward, 3 frontside, 4 backside; Uber enter forces 3; cleared by air release 0x0012E9B8 and by 0x00115640; board-press entry declines 3/4 | PS2 |
| +0x330 | int | Board-press (manual) style: 0 none, 1 nose, 2 tail; written by control 5, 1/2 after a rail transfer; nonzero at landing re-enters control 1; copied to score +0x10; cleared by crash entry | PS2 |
| +0x340 | vec4 | Attack facing: copy of +0x1A0 (right punch) or its negation (left); read with +0x350 by the rider-pair attack branch | |
| +0x350 | float | Attack strength: approaches 1 by time scale x 0.0111111 while channel-0 class is 13, copied to channel-0 weight and target; scales the attack stat in pair attacks; fist sparkle while > 0 | PS2 |
| +0x354 | int | Pending reaction due tick (logic tick) | PS2 |
| +0x358 | int | Pending reaction kind (1-3 race position, 4, 5 award, 6 boost) | PS2 |
| +0x35C | float | Upper-body idle clock (+1/60 per tick), zeroed by control 0 entry 0x00131608, by 0x0011D660 and by active upper-body animations | PS2 |
| +0x360 | int | Jump / board-press latch: a press always requests control 2, a hold alone only when the latch is 0 (checked by 0x001162C8); cleared by control 0 entry (landing) and control 7 entry | |
| +0x364 | int | Animation variant filter mask, read through animator+0x60 by 0x00104CF8 | |
| +0x370 | vec4 | Current contact normal: copied to +0x380 by 0x0013D1B8 before the terrain query; rail normal on rails (0x0013BD80); air ticks copy +0x180 in; (0,0,1) from 0x0011D660 in the transport limbo state | PS2 |
| +0x380 | vec4 | Previous contact normal (copy of +0x370 made before every terrain query, also failed ones); takeoff normal, abs(z) < 0.05 marks a wall takeoff; camera slot 0x48; not written by crash motion | PS2 |
| +0x390 | vec4 | Filtered board (lean) normal: sampled before collision, filtered after, updated after the pose at 0x0013F2E4 for the next tick; keeps the old +0x370 on reset (0x0013C7A8 runs before 0x0011D660) | PS2 |
| +0x3A0 | vec4 | Ground forward tangent of the contact frame (with +0x3B0); kept in the air from the departure tick; negated on stance flip; board-press entry rejects travel against it; used by the transfer gate | PS2 |
| +0x3B0 | vec4 | Ground lateral tangent recomputed by the terrain query (the old value offsets the next query centre); 0x0011FA10 offsets along it; negated on stance flip; kept in the air; read by the pose root | PS2 |
| +0x3C0 | vec4 | Wall normal: normalized horizontal takeoff normal written at 0x00114998 (in takeoff 0x00114298) when contact normal z < 0.05; camera slot 0x80 | |
| +0x3D0 | vec4 | Contact surface velocity (subtracted from velocity); zeroed each air tick and on rails | PS2 |
| +0x3E0 | vec4 | Previous collision normal (history), decayed x 0.98 per tick in 0x001210B0 | |
| +0x3F0 | float | Direction-change accumulator: + (1 - max(dot(n, prev), 0)) per contact, x 0.956 per tick; above 4.5 requests reset reason 2 | PS2 |
| +0x3F4 | float | Air bounce counter: 0x001057B8 adds (2.5 - dot(up, n)) x max(n.z, 0.2) in the air below 833.33 cm/s; 0x001210B0 requests a reset above 5 in the air | PS2 |
| +0x3FC | | Flag that raises the alternate irradiance-bank selector by 0.1 per update; cleared by 0x00120F20; getter 0x00140C28, setter 0x00140C30; 0 in all captures | unconfirmed |
| +0x400 | vec4 | Rider query bounds (body AABB) minimum; refreshed by 0x0011E150, moved by 0x00106538; used by 0x00332DB8 and the scope rebuild 0x00120E50 | PS2 |
| +0x410 | vec4 | Query bounds maximum; the bounds span -50..+250 cm along the physical up | PS2 |
| +0x430 | u32 | Contacted patch resource: (RID << 8) OR track (from patch+0x150) | PS2 |
| +0x434 | int | Location id of the contacted patch (0x001218D0 -> 0x0022E0E0 on the track byte of +0x430); 0x31 before contact; 11..13 half pipes, >= 17 hubs/connectors. Also read as a rider type (0 for all riders); unresolved | PS2 |
| +0x438 | int | Current surface id (patch+0x8, none -> 0); rail surface on rails (10 metal, 9 wood), kept in the air; board sound class, snow FX, camera slot 0xA0; 4th argument of hard-crash entry 0x0010EB30 | PS2 |
| +0x454 | float | Signed contact distance (cm) = dot(query centre - surface point, surface normal); the query centre includes the steering offset | PS2 |
| +0x460 | vec4 | Ground contact point (X +0x460, Y +0x464): board-spark origin, sample point of the Lighting painter 0x002C0778, environment and boost anchors. One note calls it the lighting bank set by that painter; unresolved | PS2 |
| +0x470 | float | Finish timer: < 0 unfinished, 0 starts the finish, then +1/60 per tick; >= 0 requests control 10 and mutes rider SFX; stop clip end sets 10 (0x0012C964); results after 3 s; read by 0x002A3B18, 0x00116378 | PS2 |
| +0x478 | int | Finish ticks = race ticks at the finish + penalty ticks (+0x47C) | PS2 |
| +0x47C | int | Penalty ticks added to the finish ticks | |
| +0x480 | int | DNF / time-up / give-up flag; set by 0x00125228 (time limit) and 0x001253D0 (Give Up, cRider_quitEvent); selects the 288- vs 408-tick results delay | PS2 |
| +0x490 | vec4 | Start of the retained route block (+0x490..+0x4CF): route sample at the adjusted distance +0x4C4; seeded from the countdown anchor at race start | PS2 |
| +0x498 | float | Height reference (z lane of the +0x490 sample by position): the obstacle phase may be skipped when abs(position.z - value) < 50 cm | |
| +0x4A0 | vec4 | Route lookahead sample at the adjusted distance + 796 cm | |
| +0x4B0 | float | AI progress lookahead (796 cm) copy written by 0x001125C0 | |
| +0x4C0 | float | Previous route / AI path distance (copied from +0x4C4 by 0x001125C0; receives the adjusted distance) | |
| +0x4C4 | float | Current route / AI path distance along the retained path (about 2990.4 cm captured on Snow Jam) | PS2 |
| +0x4C8 | float | Obstacle-phase gate: a skip requires it below 50 (meaning not identified) | |
| +0x4CC | float | Route heading (fall line) from route progress 0x001125C0, recomputed after route changes; read by the ground drive 0x0013C948; taking it from the wrong region row (0x00112180) gives a velocity step | PS2 |
| +0x4D0 | float | Remaining course distance to the finish (cm; 353496.16 at the Snow Jam countdown grid); set with +0x4D4 by 0x00112180; NPC pacing input | PS2 |
| +0x4D4 | float | Best (minimum) remaining distance reached; checkpoint crossings compare it with list 0x004D33B8; never moves back | PS2 |
| +0x4D8 | float | Progress origin (copy of +0x4D0 at the start) that normalises the progress gauge | PS2 |
| +0x5A4 | float | Jump camera launch value written at takeoff (0x00114298, 0x00114B78..0x00114C6C); drives the DEFAULT_3 chase camera takeoff ramp (300..500); camera slot 0xA8 | PS2 |
| +0x5AC | int | Rail proximity flag, reset and set each rail-motion tick by 0x0013AF28 when a hit within 300 cm of the board bone belongs to an entity whose vtable +0x170 predicate is true; camera push input | |
| +0x5B8 | u32[] | Distinct contacted instance resource IDs from 0x00104E70 (up to 64, ended by -1): one-way volume list; searched at 0x00108C28 (in 0x00108A48); read by script builtin 65 | PS2 |
| +0x5FC | u32 | Checkpoint bitmask (one bit set per checkpoint by 0x00270AB0). Falls inside the +0x5B8 list if that list really holds 64 entries; unresolved | |
| +0x6C0 | ptr | Interface subobject vtable pointer: 0x004583A8 human, 0x00458660 computer (see the vtable section); has a voice query used by control 8 exit | PS2 |
| +0x6D0 | | NIS actor handler (drives the rider as a cutscene actor) | |
| +0x750 | float | Board sound brake input | |
| +0x754 | float | Board sound turn input | |
| +0x758 | float | Contact compression ratio (>= 0) written by 0x0013C878; board sound compression input; distinct from board lift +0x31C | |
| +0x75C | float | Board sound speed = clamp(speed / 3333.33, 0, 1) | PS2 |
| +0x770 | float | Landing impact speed (landing sound level input); values such as 220.8 and 519.0 seen at landings | |
| +0x774 | | Crash slide loop voice handle 1 | |
| +0x778 | | Crash slide loop voice handle 2 | |
| +0x77C | ptr | Motion owner, which is also the rider FX container: +0xDE0 selects the motion mode, +0xD30 is the light list; passed to 0x001112B8, 0x00111538 and 0x00111890 (component reset) | PS2 |
| +0x780 | ptr | Geometry / rig: parts at +0x0C (0x58 bytes each), world bones at +0x2C, bone matrices | PS2 |
| +0x784 | ptr | Animator (animation player) | PS2 |
| +0x788 | ptr | Air trajectory (landing) predictor, seeded and restarted by 0x001135B8; its status is also read by the environment colour air branch | PS2 |
| +0x790 | ptr | Score / trick score object (0x1CC bytes, 44-slot HUD message bank, total at +0x198); passed to 0x00119D40, 0x00119918, 0x00119938, 0x00119958 | PS2 |
| +0x794 | ptr[8] | Eight selected local-light pointers (null allowed), visited in order during lighting assembly; the words at +0x79C, +0x7A0 and +0x7AC change only on scope refresh | PS2 |
| +0x7C0 | float[40] | Irradiance coefficient bank (ten RGBA rows, 160 bytes) built by 0x001220D8 | |
| +0x860 | ptr | Query scope / nearby-object cache (count +0x210, entries +0x214): rebuilt every third tick by 0x00120E50 via 0x00332DB8 from +0x400/+0x410; used by 0x00104E70, 0x00106F78, rail query 0x00334680, light selection | PS2 |
| +0x864 | ptr | Coarse ground contact cache (kind 2 for all riders), shared by ground contact, landing and air probes, body queries and the crash probe 0x00138960 | PS2 |
| +0x868 | ptr | Body collision cache: kind 1 (detailed) for humans, kind 0 (coarse) for computer riders; used by 0x0013F488, 0x0013AA48 and crash queries (0x00137860); kept on control 8 entry | PS2 |
| +0x86C | int | Unresolved: roster/grid slot (0 human, 1..5 computer; selects the teleport offset; hair schedule uses tick % 6 == slot), race place, or environment index (accessor 0x00140B80, table 0x004FA398, stride 0xF0) | PS2 |
| +0x870 | int | Controller device / player index (-1 for computer riders); sound request player; crash camera shake needs >= 0 | |
| +0x874 | int | Human (local player) flag: gates 0x00125228, human-only reactions (0x0010E910 kinds 1-3, get-up) and SFX (with +0x87C); zero lets computer riders skip the obstacle query 0x0013F488 | PS2 |
| +0x878 | int | Nonzero excludes the actor as a pair-collision opponent; also makes rank mode 2 use a constant key instead of the score (meaning not identified) | |
| +0x87C | int | Controller enabled flag: crash camera shake and SFX gates need it nonzero | |
| +0x880 | int | Actor kind/state; pair records are enabled only when it equals 7 | |
| +0x88C | struct | Bone-emitter controller (vtable 0x004881D0) | |
| +0x89C | int | Root/hips bone index (0 for Zoe): air presentation pivot, 0x00106F78, BodySnow inactive position. Camera notes call it the head bone (head position 0x0011FF48); unresolved | PS2 |
| +0x8A0 | int | Board-root bone index (22 for Zoe): bone = *(geometry+0x2C) + index*32 (position +0, quaternion +0x10); rail queries 0x00108A48/0x001086B8, landing probe | PS2 |
| +0x8A4 | int | Board bone index (23); its geometry+0x30 matrix is the snow board frame; detached-board spheres lie along its X axis | |
| +0x8A8 | int | Head bone index into the bone matrix bank (5 captured): handplant setup, breath emitter point (-3,0,4,1), hair wind (with +0x950/+0x960) | PS2 |
| +0x8C0 | u64 | Channel-1 upper-body bone mask A (Zoe: bits 1-15 and 31): bone list 0x00457A90 plus the hands morph bit (31 Zoe/Sam/Griff, 30 Psymon/Luther, 33 Allegra/Moby); built by 0x0011C298 via 0x00310CE8 | PS2 |
| +0x8C8 | u64 | Channel-1 bone mask B: bone list 0x00457B38 plus the same morph bit (Zoe: bits 3-15 and 31); used when playing reactions on channel 1 | PS2 |
| +0x8D0 | u64 | Morph mask from bone list 0x00457BC8 (0x870 for all riders), ORed into +0x8C0 and +0x8C8 | PS2 |
| +0x8E0 | struct | Leg IK binding 1: thigh/shin/foot bone indices, board-relative foot translation and quaternion | |
| +0x910 | struct | Leg IK binding 2 (same layout) | |
| +0x950 | vec4 | Hair wind term (with +0x960), applied with cached bone +0x8A8 | PS2 |
| +0x960 | vec4 | Hair wind term (with +0x950) | PS2 |
| +0x9D0 | vec4 | Accumulated collision-body translation (board query offset): added by 0x00106538 and rail contact response 0x0013C140, committed to cached bones by 0x00310530, cleared on the next motion tick (at 0x00121020) | |
| +0x9E0 | struct | Copy of the selected instance contact packet (0x00334888 packet) made by 0x00105398: packet +0x48 node collider, +0x50 instance; passed to entity contact and the RollerModifier constructor | |
| +0xA30 | ptr | Selected contact instance (packet +0x50 inside the +0x9E0 copy); non-null triggers the collection/contact dispatch 0x00121818 | |
| +0xA60 | struct | Copy of the 0x00105398 contact record (point, direction, normal, closing speed); passed to entity contact handlers and the RollerModifier kick | |
| +0xAA0 | ptr | Collision body (broad sphere plus bone spheres): built at pose time (0x0011EB98 -> 0x00106828), translated by 0x00106538 and 0x0013C140, used by 0x0032F650 and 0x0013AA48 | PS2 |
| +0xAAC | float | Solved patch U (with +0xAB0) | PS2 |
| +0xAB0 | float | Solved patch V | PS2 |
| +0xAB4 | ptr | Current route path (path array + 3 x 0x3C for ARA1's region row); course progress tracking with +0xAC0 | PS2 |
| +0xAB8 | | Unresolved: selected AI path index (int), retained route pointer (a missing route stays missing), or a route progress word (float) | PS2 |
| +0xABC | struct | Route / AI path projection cache (horizontal), invalidated on route refresh | PS2 |
| +0xAC0 | int | Course progress tracking field (with +0xAB4) | PS2 |
| +0xAC4 | | Unresolved: playback-rider ground re-probe data (strength source for the fifth 0x00111AA0 caller), or a course-progress inhibition field (progress allowed when clear) | unconfirmed |
| +0xB18 | | Visibility flag gating the per-tick shadow build | |
| +0xB1C | int | When nonzero, the local animation sampler also applies the geometry+0x158 reduced bone mask | PS2 |
| +0xB20 | int | Rider category | unconfirmed |
| +0xB28 | u32 | Meter award category eligibility mask tested by 0x0010E098 | |
| +0xB2C | u32 | Ability flags (3 in the starting profile): bit 0 needed for the initial Uber selection, bit 1 for rail Uber entry 0x00132620; also enables the full-meter notification | PS2 |
| +0xB30 | | Start delay (from the countdown grid) | PS2 |
| +0xB34 | | Rider stat level; 11 = maxed stats | PS2 |

## Rider interface vtable (0x004583A8 human, 0x00458660 computer)

Vtable of the interface subobject at rider+0x6C0 (methods adjust `this` by -0x6C0). Offsets are slot offsets within the vtable.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x38 | vfunc | Environment getter 0x00140B80 | |
| +0x40 | vfunc | Reset end permission | |
| +0x44 | vfunc | Gates the checkpoint trick bonus | |
| +0x78 | vfunc | Multiplier icon pickup handler (0x0010E830) | PS2 |
| +0x80 | vfunc | Feedback hooks +0x80..+0x9C: human versions write motion owner +0xDFC/+0xE00 (rumble), computer versions are no-ops | |
| +0xA4 | vfunc | Route score: 0x001446E8 (human) or 0x0010D410 (computer) | |

## Motion owner and rider FX container (*(rider+0x77C))

Reached as *(rider+0x77C). These records were written as rider offsets, but the offsets match components and fields of the motion owner (full layout in "Rider component layouts").

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x290 | struct | Start-grid controller state: phase, steady time, low/high and pose (the source notes correct its location to owner+0x290, not +0x250) | |
| +0x2A0 | float | Start-pose fraction: the kind-8 driver seeks slot 0 to duration times this value; reported as rider+0x2A0, placed here as the pose field of the +0x290 control | unconfirmed |
| +0x3B0 | struct | Wake FX component (pass 0x002DD0B8); snow reads the newest wake row's final vector from it instead of a fresh world query | |
| +0x470 | struct | Board sparks FX component (pass 0x002DABC8) | |
| +0x520 | struct | FX component updated by pass 0x002E8938: the component list calls it the board track; one note labels it the grind-chunk emitter; unresolved | unconfirmed |
| +0x610 | struct | FX component updated by pass 0x002E66B8 (boost component in the component list) | |
| +0x9C0 | struct | FX component updated by pass 0x002EADD0 (power-up aura in the component list) | |
| +0xAD0 | struct | FX component updated by pass 0x002EF6D0 (air streamers in the component list) | |
| +0xAF0 | struct | FX component updated by pass 0x002D4C08 (rival indicator) | |
| +0xB00 | struct | FX component updated by pass 0x002E39D8 (locator beam) | |
| +0xB40 | struct | Snow FX component (particle emitters, breath and other emitters), pass 0x002DF920 | PS2 |
| +0xC70 | struct | Fist sparkle FX component, pass 0x002F1150 | |
| +0xD20 | struct | FX component updated by pass 0x002F6518 | |
| +0xDE0 | int | Current motion (index into the motion exit table 0x00456B10) | |
| +0xDE4 | int | Current control (index into the control exit table 0x00456B90) | |
| +0xDF0 | struct | Computer riders: NPC extension block +0xDF0..+0xF40 (trick-plan words) | PS2 |
| +0xDFC | | Written by the human feedback hooks (with +0xE00); holds NPC state on a computer rider | |
| +0xE24 | | Word cleared by 0x0010B250 on grab release | PS2 |

## Score object (*(rider+0x790))

One record was written as a rider offset but matches the score object's multiplier (full layout in "Rider component layouts").

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1C4 | float | Trick score multiplier used by bonus rounding and the pending-points getter; survives the 0x00119D40 reset | |
