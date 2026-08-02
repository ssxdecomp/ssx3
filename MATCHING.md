# Function matching report

Auto-generated from [objdiff](tools/objdiff) by diffing every unit's `obj/target` against `obj/current`. Regenerate with a dual build (`./configure.py -c -o && ninja`) followed by `python3 scripts/matching_report.py`; see [CONTRIBUTING.md](CONTRIBUTING.md).

Snapshot as of 2026-08-02.

**Status definitions:**
- **Matching** — byte-for-byte identical to the retail binary (100%), or a near-miss where objdiff's own report considers the function matched despite a lower raw percentage (this happens for a handful of functions where the only remaining byte difference is a relocation immediate baked in at link time by the original SN toolchain, not a real code difference — see the gp-relative note in [README.md](README.md)).
- **Partial** — has a C implementation (not raw `INCLUDE_ASM`) but doesn't yet byte-match; the percentage is objdiff's fuzzy match score.
- **Not started** — still a raw `INCLUDE_ASM` stub with no C implementation attempted.

| | Count | % of total |
|---|---|---|
| Matching | 1,159 | 8.96% |
| Partial | 105 | 0.81% |
| Not started | 11,676 | 90.23% |
| **Total** | **12,940** | |

(Total here may differ slightly from the function count in README.md's progress table — that one comes from objdiff's own aggregate report, this one from summing every unit's individual symbol list, and the two count a handful of duplicated/weak symbols differently.)

## Per-file summary

Only files with at least one Matching or Partial function are listed here; files that are 100% Not Started are omitted from this table (see the full per-file breakdown further down for every file, including those).

| File | Matching | Partial | Not started | Total |
|---|---|---|---|---|
| `object/railmodifier` | 170 | 1 | 144 | 315 |
| `fe/fepopupmisc` | 122 | 0 | 168 | 290 |
| `render/font` | 81 | 1 | 61 | 143 |
| `worldpainter/worldpaintermanquery` | 65 | 1 | 4 | 70 |
| `main/debugmenu` | 42 | 0 | 49 | 91 |
| `camera/camera` | 41 | 0 | 144 | 185 |
| `bx/cubicspline` | 32 | 6 | 16 | 54 |
| `replay/replaycache` | 34 | 2 | 121 | 157 |
| `fe/feasyncfile` | 30 | 1 | 492 | 523 |
| `ui/uivector` | 30 | 0 | 48 | 78 |
| `main/ssxappdtor` | 29 | 0 | 61 | 90 |
| `ai/control/handplantcontrol` | 25 | 0 | 78 | 103 |
| `scripter/ssxscriptengine` | 17 | 4 | 144 | 165 |
| `dirtysock/tagsunk` | 14 | 6 | 272 | 292 |
| `util/menu` | 16 | 4 | 141 | 161 |
| `main/gamestate` | 19 | 0 | 54 | 73 |
| `be/bedbreward` | 13 | 0 | 11 | 24 |
| `worldpainter/quadtree` | 11 | 2 | 111 | 124 |
| `bx/appman` | 9 | 3 | 4 | 16 |
| `camera/trigger/cameratriggerfactory` | 12 | 0 | 102 | 114 |
| `visualfx/worldlightman` | 11 | 0 | 49 | 60 |
| `be/beintreward` | 9 | 1 | 87 | 97 |
| `wscript/wscriptman` | 6 | 4 | 85 | 95 |
| `ai/rider` | 7 | 2 | 97 | 106 |
| `sound/bankmonitor` | 7 | 2 | 154 | 163 |
| `fe/fememcardcallbacks` | 5 | 3 | 49 | 57 |
| `mem/memstd` | 7 | 1 | 41 | 49 |
| `ui/uiscreen` | 7 | 1 | 39 | 47 |
| `world/wscriptcache` | 8 | 0 | 108 | 116 |
| `movie/movieplayer` | 7 | 0 | 107 | 114 |
| `render/lightman` | 7 | 0 | 37 | 44 |
| `replay/frameptr` | 7 | 0 | 32 | 39 |
| `be/beintplayer` | 5 | 1 | 75 | 81 |
| `bx/bxstringctor` | 5 | 1 | 81 | 87 |
| `input/inputparse` | 6 | 0 | 53 | 59 |
| `scripter/bxscriptengine` | 5 | 1 | 51 | 57 |
| `sound/soundsys` | 4 | 2 | 262 | 268 |
| `visualfx/crowdrender2d` | 3 | 3 | 2 | 8 |
| `ai/ai` | 2 | 3 | 156 | 161 |
| `ai/ridermetrix` | 4 | 1 | 62 | 67 |
| `be/beintscore` | 3 | 2 | 16 | 21 |
| `bx/bigfile` | 4 | 1 | 2 | 7 |
| `bx/bxrandom` | 4 | 1 | 5 | 10 |
| `bx/memman` | 5 | 0 | 1 | 6 |
| `fe/festateloadscreen` | 5 | 0 | 23 | 28 |
| `fe/ovstatehud` | 2 | 3 | 30 | 35 |
| `object/modifierblock` | 4 | 1 | 31 | 36 |
| `object/movenode` | 5 | 0 | 91 | 96 |
| `render/particle` | 3 | 2 | 183 | 188 |
| `util/list` | 4 | 1 | 9 | 14 |
| `ai/computer` | 4 | 0 | 67 | 71 |
| `animation/animsequencer` | 3 | 1 | 29 | 33 |
| `bx/execman` | 4 | 0 | 6 | 10 |
| `bx/memblockman` | 4 | 0 | 32 | 36 |
| `camera/trigger/cameratriggerlist` | 3 | 1 | 5 | 9 |
| `camera/trigger/cameratriggerman` | 4 | 0 | 20 | 24 |
| `hashvalue` | 3 | 1 | 2 | 6 |
| `luno/lunovm` | 3 | 1 | 22 | 26 |
| `main/loadscreens_prestart` | 4 | 0 | 30 | 34 |
| `main/ssxapp` | 4 | 0 | 44 | 48 |
| `scripter/datamanager` | 1 | 3 | 44 | 48 |
| `sound/bankmanager` | 3 | 1 | 62 | 66 |
| `sound/ssxAudio` | 3 | 1 | 75 | 79 |
| `util/objectinterface` | 4 | 0 | 4 | 8 |
| `world/worldcache` | 2 | 2 | 46 | 50 |
| `world/worldview` | 4 | 0 | 41 | 45 |
| `be/beintaggression` | 3 | 0 | 6 | 9 |
| `be/beintmission` | 3 | 0 | 39 | 42 |
| `be/beintnewrace` | 2 | 1 | 33 | 36 |
| `be/belibrary` | 3 | 0 | 46 | 49 |
| `camera/script/scriptcontroller` | 3 | 0 | 28 | 31 |
| `fe/festateloadhint` | 3 | 0 | 24 | 27 |
| `fe/festateoptions` | 3 | 0 | 55 | 58 |
| `fe/ovstatemission` | 3 | 0 | 6 | 9 |
| `intersect/riderspheretree` | 2 | 1 | 66 | 69 |
| `intersect/worldsphtree` | 3 | 0 | 73 | 76 |
| `object/bucketman` | 1 | 2 | 15 | 18 |
| `object/deadfadenode` | 3 | 0 | 10 | 13 |
| `object/splinemodifier` | 3 | 0 | 32 | 35 |
| `render/bezierman` | 2 | 1 | 15 | 18 |
| `replay/replay` | 2 | 1 | 19 | 22 |
| `sound/icepick/worldtriggermanager` | 2 | 1 | 51 | 54 |
| `sound/streamsys` | 1 | 2 | 56 | 59 |
| `ui/uiengine` | 2 | 1 | 31 | 34 |
| `visualfx/boardwakefx` | 2 | 1 | 79 | 82 |
| `ai/airpredictor` | 1 | 1 | 7 | 9 |
| `be/beintecon` | 2 | 0 | 22 | 24 |
| `be/beintnetwork` | 2 | 0 | 16 | 18 |
| `be/beintoption` | 1 | 1 | 15 | 17 |
| `be/beintsavefile` | 2 | 0 | 10 | 12 |
| `be/beprepoststate` | 2 | 0 | 11 | 13 |
| `bx/bxstring` | 2 | 0 | 25 | 27 |
| `camera/trigger/cameratriggervolumes` | 2 | 0 | 1 | 3 |
| `fe/fepopup` | 2 | 0 | 117 | 119 |
| `fe/festatebigradio` | 2 | 0 | 15 | 17 |
| `fe/festatenethelppopup` | 2 | 0 | 19 | 21 |
| `fe/festateruleselect` | 2 | 0 | 16 | 18 |
| `fe/festatetrophyroom` | 2 | 0 | 34 | 36 |
| `fe/ovstatepause` | 2 | 0 | 58 | 60 |
| `fe/ovtemplatepausemenu` | 2 | 0 | 14 | 16 |
| `fe/uitemplatemap` | 2 | 0 | 36 | 38 |
| `main/gameload` | 2 | 0 | 33 | 35 |
| `main/gamemode` | 2 | 0 | 48 | 50 |
| `main/sectionman` | 1 | 1 | 5 | 7 |
| `object/debouncenode` | 2 | 0 | 41 | 43 |
| `object/effectlink` | 1 | 1 | 28 | 30 |
| `object/flexrailnode` | 2 | 0 | 32 | 34 |
| `object/instanceman` | 2 | 0 | 18 | 20 |
| `object/objnode` | 2 | 0 | 9 | 11 |
| `path/pathsys` | 2 | 0 | 14 | 16 |
| `render/graphicsman` | 2 | 0 | 48 | 50 |
| `render/ps2graphicsman` | 2 | 0 | 30 | 32 |
| `replay/playbackman` | 1 | 1 | 34 | 36 |
| `scripter/videngine` | 1 | 1 | 13 | 15 |
| `sound/asyncsys` | 1 | 1 | 18 | 20 |
| `ui/uitext` | 2 | 0 | 29 | 31 |
| `visualfx/lensfx` | 2 | 0 | 47 | 49 |
| `world/world` | 2 | 0 | 17 | 19 |
| `ai/motion/wipeoutmotion` | 1 | 0 | 15 | 16 |
| `animation/gameanimmap` | 1 | 0 | 4 | 5 |
| `be/be` | 0 | 1 | 9 | 10 |
| `be/bedbprofile` | 0 | 1 | 4 | 5 |
| `be/beintbagt` | 0 | 1 | 21 | 22 |
| `be/beintcharacter` | 0 | 1 | 2 | 3 |
| `be/bestate` | 1 | 0 | 3 | 4 |
| `camera/trigger/triggeralgorithms` | 1 | 0 | 9 | 10 |
| `fe/debugfe` | 1 | 0 | 85 | 86 |
| `fe/fememcard` | 1 | 0 | 19 | 20 |
| `fe/festatebonusmaterial` | 1 | 0 | 4 | 5 |
| `fe/festatecharselect` | 1 | 0 | 17 | 18 |
| `fe/festateload` | 1 | 0 | 12 | 13 |
| `fe/festateprofile` | 1 | 0 | 20 | 21 |
| `fe/festateriderbio` | 1 | 0 | 10 | 11 |
| `fe/messagecenter` | 1 | 0 | 22 | 23 |
| `fe/ovstatelodge` | 1 | 0 | 21 | 22 |
| `fe/ovstatemap` | 1 | 0 | 23 | 24 |
| `fe/ovstateprofile` | 1 | 0 | 19 | 20 |
| `fe/ovstatereplay` | 1 | 0 | 7 | 8 |
| `fe/ovstates` | 1 | 0 | 15 | 16 |
| `main/streampause` | 1 | 0 | 2 | 3 |
| `md5` | 1 | 0 | 3 | 4 |
| `object/floatingnode` | 0 | 1 | 9 | 10 |
| `object/spline3d` | 0 | 1 | 3 | 4 |
| `render/ps2bezierman` | 0 | 1 | 1 | 2 |
| `render/ps2lightman` | 1 | 0 | 1 | 2 |
| `ui/uianimation` | 1 | 0 | 8 | 9 |
| `ui/uimenu` | 1 | 0 | 22 | 23 |
| `ui/uistate` | 1 | 0 | 9 | 10 |
| `ui/uistatestack` | 1 | 0 | 21 | 22 |
| `ui/uithing` | 1 | 0 | 11 | 12 |
| `visualfx/boardtrailfx` | 0 | 1 | 28 | 29 |
| `worldpainter/worldpainterman` | 1 | 0 | 0 | 1 |
| `wscript/wscriptcompile` | 1 | 0 | 4 | 5 |
| `wscript/wscriptprocess` | 1 | 0 | 61 | 62 |

## Full per-file breakdown

Every unit, including ones with no progress yet. Matching and Partial functions are listed individually with their match percentage; Not Started functions are only counted (there's nothing to report per-function until an implementation is attempted).

### `1137E8`

0 matching, 0 partial, 154 not started (154 total)

### `1218`

0 matching, 0 partial, 110 not started (110 total)

### `14B10`

0 matching, 0 partial, 56 not started (56 total)

### `156860`

0 matching, 0 partial, 101 not started (101 total)

### `184E60`

0 matching, 0 partial, 70 not started (70 total)

### `1BA100`

0 matching, 0 partial, 299 not started (299 total)

### `1C9348`

0 matching, 0 partial, 18 not started (18 total)

### `1D3510`

0 matching, 0 partial, 113 not started (113 total)

### `1DCD10`

0 matching, 0 partial, 7 not started (7 total)

### `1F1548`

0 matching, 0 partial, 56 not started (56 total)

### `1FBE38`

0 matching, 0 partial, 125 not started (125 total)

### `2125C8`

0 matching, 0 partial, 6 not started (6 total)

### `218AE8`

0 matching, 0 partial, 5 not started (5 total)

### `218F38`

0 matching, 0 partial, 5 not started (5 total)

### `21A1C0`

0 matching, 0 partial, 16 not started (16 total)

### `21E5A8`

0 matching, 0 partial, 3 not started (3 total)

### `2B4578`

0 matching, 0 partial, 1046 not started (1046 total)

### `2EEF50`

0 matching, 0 partial, 1428 not started (1428 total)

### `6D428`

0 matching, 0 partial, 4 not started (4 total)

### `CF758`

0 matching, 0 partial, 4 not started (4 total)

### `DC148`

0 matching, 0 partial, 280 not started (280 total)

### `ai/ai`

2 matching, 3 partial, 156 not started (161 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0012E9B0(void*)` | Matching | 100.00% | 8 |
| `func_00136978(void*)` | Matching | 100.00% | 8 |
| `func_0012FC60(void*)` | Partial | 87.50% | 32 |
| `func_00131608(void*)` | Partial | 68.00% | 20 |
| `func_001304D0(void*)` | Partial | 63.33% | 12 |

### `ai/airpredictor`

1 matching, 1 partial, 7 not started (9 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113998(void*)` | Matching | 100.00% | 8 |
| `cAirPredictor_initLaunch(char *, sQuad *, sQuad *)` | Partial | 0.00% | 48 |

### `ai/computer`

4 matching, 0 partial, 67 not started (71 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0010F398(void*)` | Matching | 100.00% | 28 |
| `func_001125B8(void*)` | Matching | 100.00% | 8 |
| `func_00113128(void*)` | Matching | 100.00% | 8 |
| `func_00113130(void*)` | Matching | 100.00% | 8 |

### `ai/control/handplantcontrol`

25 matching, 0 partial, 78 not started (103 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00139A18(void*)` | Matching | 100.00% | 8 |
| `func_001406C0(void*)` | Matching | 100.00% | 8 |
| `func_001406C8(void*)` | Matching | 100.00% | 8 |
| `func_001406F0(void*)` | Matching | 100.00% | 8 |
| `func_001406F8(void*)` | Matching | 100.00% | 8 |
| `func_00140700(void*)` | Matching | 100.00% | 8 |
| `func_00140708(void*)` | Matching | 100.00% | 8 |
| `func_00140710(void*)` | Matching | 100.00% | 8 |
| `func_00140718(void*)` | Matching | 100.00% | 8 |
| `func_00140720(void*)` | Matching | 100.00% | 8 |
| `func_00140728(void*)` | Matching | 100.00% | 8 |
| `func_00140730(void*)` | Matching | 100.00% | 8 |
| `func_001408F0(void*)` | Matching | 100.00% | 8 |
| `func_00140910(void*)` | Matching | 100.00% | 8 |
| `func_00140B80(void*)` | Matching | 100.00% | 8 |
| `func_00140BC0(void*)` | Matching | 100.00% | 8 |
| `func_00140C68(void*)` | Matching | 100.00% | 8 |
| `func_00140C70(void*)` | Matching | 100.00% | 8 |
| `func_00140C78(void*)` | Matching | 100.00% | 8 |
| `func_00140C80(void*)` | Matching | 100.00% | 8 |
| `func_00140CE0(void*)` | Matching | 100.00% | 8 |
| `func_00144068(void*)` | Matching | 100.00% | 8 |
| `func_001441A0(void *, void *)` | Matching | 100.00% | 24 |
| `func_00144610(void*)` | Matching | 100.00% | 28 |
| `func_001446E8(void*)` | Matching | 100.00% | 12 |

### `ai/motion/wipeoutmotion`

1 matching, 0 partial, 15 not started (16 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00136F28(void*)` | Matching | 100.00% | 8 |

### `ai/rider`

7 matching, 2 partial, 97 not started (106 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0011FE98(void*)` | Matching | 100.00% | 12 |
| `func_0011FEE8(void*)` | Matching | 100.00% | 12 |
| `func_00122CD0(void*)` | Matching | 100.00% | 28 |
| `func_00125AD0(void*)` | Matching | 100.00% | 8 |
| `func_001278E0(void*, float)` | Matching | 100.00% | 8 |
| `func_00128660(void*)` | Matching | 100.00% | 28 |
| `func_00128680(void*)` | Matching | 100.00% | 28 |
| `func_001278C0(void*)` | Partial | 99.33% | 12 |
| `cRider_addRiderMetrix(cRider*)` | Partial | 95.00% | 80 |

### `ai/ridermetrix`

4 matching, 1 partial, 62 not started (67 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00117900(void*)` | Matching | 100.00% | 8 |
| `func_0011A0C0(void*)` | Matching | 100.00% | 12 |
| `func_0011B678(void*)` | Matching | 100.00% | 28 |
| `cRiderMetrix_evAutoResetSurface(void*)` | Matching | 99.62% | 52 |
| `func_00119938(void*, int, int)` | Partial | 97.62% | 32 |

### `animation/animmodel`

0 matching, 0 partial, 32 not started (32 total)

### `animation/animsequencer`

3 matching, 1 partial, 29 not started (33 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cAnimSequence_fadeWeight(cAnimSequence*, float, float)` | Matching | 100.00% | 16 |
| `cAnimSequencer_getSequence(cAnimSequencer*, int)` | Matching | 100.00% | 36 |
| `func_00314978(void*)` | Matching | 100.00% | 12 |
| `func_003142E8(void*)` | Partial | 99.33% | 12 |

### `animation/gameanimmap`

1 matching, 0 partial, 4 not started (5 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cGameAnimMap_testResolve()` | Matching | 100.00% | 8 |

### `animation/mdfarchive`

0 matching, 0 partial, 8 not started (8 total)

### `animation/rideranimbase`

0 matching, 0 partial, 30 not started (30 total)

### `be/be`

0 matching, 1 partial, 9 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBE_getInterface()` | Partial | 95.88% | 64 |

### `be/bedbprofile`

0 matching, 1 partial, 4 not started (5 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBECharProfileDB_getScoreStats(void*, int, int)` | Partial | 93.68% | 76 |

### `be/bedbreward`

13 matching, 0 partial, 11 not started (24 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BB00(void*)` | Matching | 100.00% | 8 |
| `func_0015BB08(void*)` | Matching | 100.00% | 8 |
| `func_0015BB10(void*)` | Matching | 100.00% | 8 |
| `func_0015BB18(void*)` | Matching | 100.00% | 8 |
| `func_0015BCC0(void*)` | Matching | 100.00% | 8 |
| `func_0015BCC8(void*)` | Matching | 100.00% | 8 |
| `func_0015C6C8(void*)` | Matching | 100.00% | 8 |
| `func_0015C6D0(void*)` | Matching | 100.00% | 8 |
| `func_0015C6D8(void*)` | Matching | 100.00% | 8 |
| `func_0015C6E0(void*)` | Matching | 100.00% | 8 |
| `func_0015C7D0(void*)` | Matching | 100.00% | 8 |
| `func_0015C7D8(void*)` | Matching | 100.00% | 8 |
| `func_0015C930(void*)` | Matching | 100.00% | 16 |

### `be/beintaggression`

3 matching, 0 partial, 6 not started (9 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00155AA0(void*)` | Matching | 100.00% | 8 |
| `func_00155AA8(void*)` | Matching | 100.00% | 8 |
| `cBEAggressionInterface_getThis()` | Matching | 99.84% | 76 |

### `be/beintbagt`

0 matching, 1 partial, 21 not started (22 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBEBAGTInterface_getThis()` | Partial | 83.17% | 96 |

### `be/beintcharacter`

0 matching, 1 partial, 2 not started (3 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBECharacterInterface_getWeight(void*, int)` | Partial | 98.67% | 60 |

### `be/beintecon`

2 matching, 0 partial, 22 not started (24 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBEEconInterface_getTotalMoneyEarned(void*, int, int)` | Matching | 100.00% | 56 |
| `cBEEconInterface_getThis()` | Matching | 99.84% | 76 |

### `be/beintmission`

3 matching, 0 partial, 39 not started (42 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001547D8(void*)` | Matching | 100.00% | 8 |
| `func_001547E0(void*)` | Matching | 100.00% | 8 |
| `cBEMissionInterface_getThis()` | Matching | 99.84% | 76 |

### `be/beintnetwork`

2 matching, 0 partial, 16 not started (18 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0014E2C0(void*)` | Matching | 100.00% | 8 |
| `cBENetworkInterface_getThis()` | Matching | 99.84% | 76 |

### `be/beintnewrace`

2 matching, 1 partial, 33 not started (36 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBENewRaceInterface_setNumberMission(void*, int)` | Matching | 100.00% | 36 |
| `cBENewRaceInterface_getThis()` | Matching | 99.84% | 76 |
| `cBENewRaceInterface_setNumberHumans(void*, int)` | Partial | 63.16% | 76 |

### `be/beintoption`

1 matching, 1 partial, 15 not started (17 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBEOptionInterface_getDefaultQuickKeyMessageHashValue(void*, int)` | Matching | 99.58% | 48 |
| `cBEOptionInterface_getThis()` | Partial | 92.24% | 84 |

### `be/beintplayer`

5 matching, 1 partial, 75 not started (81 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBENewPlayerInterface_cBENewPlayerInterface(cBENewPlayerInterfaceCtor*)` | Matching | 100.00% | 64 |
| `cBENewPlayerInterface_getRiderCharID(void*, int)` | Matching | 100.00% | 52 |
| `cBENewPlayerInterface_getPlayerCharID(void*, int)` | Matching | 100.00% | 28 |
| `cBENewPlayerInterface_getPlayerID(int)` | Matching | 100.00% | 24 |
| `cBENewPlayerInterface_getThis()` | Matching | 99.82% | 68 |
| `cBENewPlayerInterface_isMissionMan(int)` | Partial | 96.00% | 60 |

### `be/beintreward`

9 matching, 1 partial, 87 not started (97 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBERewardInterface_isBetterMedal(void*, int, int)` | Matching | 100.00% | 44 |
| `func_001572B0(void*)` | Matching | 100.00% | 32 |
| `func_001572D0(void*)` | Matching | 100.00% | 32 |
| `func_001572F0(void*)` | Matching | 100.00% | 32 |
| `func_00157310(void*)` | Matching | 100.00% | 32 |
| `func_00157330(void*)` | Matching | 100.00% | 32 |
| `func_00157350(void*)` | Matching | 100.00% | 32 |
| `func_00157370(void*)` | Matching | 100.00% | 32 |
| `cBERewardInterface_getThis()` | Matching | 99.84% | 76 |
| `cBERewardInterface_getTrackMedal(void*, int, int, int, int)` | Partial | 88.68% | 76 |

### `be/beintsavefile`

2 matching, 0 partial, 10 not started (12 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00152948(void*)` | Matching | 100.00% | 8 |
| `cBESaveInterface_getThis()` | Matching | 99.80% | 80 |

### `be/beintscore`

3 matching, 2 partial, 16 not started (21 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001549E0(void*)` | Matching | 100.00% | 8 |
| `func_00155380(void*)` | Matching | 100.00% | 8 |
| `func_00155388(void*)` | Matching | 100.00% | 8 |
| `cBEScoreInterface_getCurrentHighlightLevel(void*, int)` | Partial | 97.94% | 68 |
| `cBEScoreInterface_getThis()` | Partial | 86.17% | 92 |

### `be/beintstat`

0 matching, 0 partial, 13 not started (13 total)

### `be/belibrary`

3 matching, 0 partial, 46 not started (49 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBELibrary_getCharacterID(int)` | Matching | 100.00% | 48 |
| `cBELibrary_getProfileIndex(int)` | Matching | 100.00% | 76 |
| `cBELibrary_getRiderIndex(int)` | Matching | 100.00% | 80 |

### `be/beprepoststate`

2 matching, 0 partial, 11 not started (13 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBEPostRaceState_getState(void*)` | Matching | 99.86% | 88 |
| `cBEPreRaceState_getState(void*)` | Matching | 99.86% | 88 |

### `be/bestate`

1 matching, 0 partial, 3 not started (4 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBERaceState_getState(void*)` | Matching | 99.86% | 88 |

### `bx/appman`

9 matching, 3 partial, 4 not started (16 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cAppMan_setNextModule(cAppMan*, unsigned int)` | Matching | 100.00% | 8 |
| `cAppMan_checkHalt(cAppMan*)` | Matching | 100.00% | 32 |
| `cExecutionMan_halt(cExecutionMan*)` | Matching | 100.00% | 28 |
| `cExecutionMan_checkHalt(void*, int)` | Matching | 100.00% | 88 |
| `func_003175A0(void*)` | Matching | 99.96% | 96 |
| `cAppMan__cAppMan(void *, int)` | Matching | 99.92% | 52 |
| `func_00317550(void*, float)` | Matching | 99.90% | 80 |
| `func_00317520()` | Matching | 99.67% | 12 |
| `func_00317600(void*)` | Matching | 99.67% | 24 |
| `func_00317530(void*, float)` | Partial | 99.29% | 28 |
| `func_00317500()` | Partial | 99.25% | 32 |
| `func_00317348(void*)` | Partial | 93.78% | 180 |

### `bx/bigfile`

4 matching, 1 partial, 2 not started (7 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBigFile_cBigFile(cBigFile*)` | Matching | 100.00% | 20 |
| `cBigFile_cBigFile1(cBigFile*)` | Matching | 100.00% | 52 |
| `cBigFile__cBigFile(cBigFile *, int)` | Matching | 100.00% | 68 |
| `func_00316A00(void*)` | Matching | 100.00% | 32 |
| `cBigFile_close(cBigFile*)` | Partial | 90.59% | 68 |

### `bx/blockman`

0 matching, 0 partial, 1 not started (1 total)

### `bx/bxrandom`

4 matching, 1 partial, 5 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00317890(float, float)` | Matching | 100.00% | 76 |
| `BXsrand(unsigned int)` | Matching | 99.44% | 36 |
| `BXrand()` | Matching | 99.38% | 32 |
| `AIrand()` | Matching | 99.38% | 32 |
| `AIrandf(float, float)` | Partial | 99.12% | 96 |

### `bx/bxstring`

2 matching, 0 partial, 25 not started (27 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBXString_FindLastOf(cBXString*, char, int)` | Matching | 100.00% | 72 |
| `cBXString_FindFirstOf(cBXString*, char)` | Matching | 100.00% | 68 |

### `bx/bxstringctor`

5 matching, 1 partial, 81 not started (87 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00269DA0(void*)` | Matching | 100.00% | 28 |
| `func_00269E20(void*)` | Matching | 100.00% | 28 |
| `func_00269EC0(void*)` | Matching | 100.00% | 20 |
| `func_0026A068(void*)` | Matching | 100.00% | 8 |
| `func_0026ADA0(void*)` | Matching | 100.00% | 8 |
| `cBXString_cBXString(cBXString2*)` | Partial | 85.05% | 76 |

### `bx/cubicspline`

32 matching, 6 partial, 16 not started (54 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0031D790(void*)` | Matching | 100.00% | 80 |
| `func_0031FF20(void*)` | Matching | 100.00% | 24 |
| `func_0031FF38(void*, int)` | Matching | 100.00% | 36 |
| `func_003200C0(void*)` | Matching | 100.00% | 28 |
| `func_003200E8(void*)` | Matching | 100.00% | 56 |
| `func_00320120(void*)` | Matching | 100.00% | 56 |
| `func_00320158(void*)` | Matching | 100.00% | 56 |
| `func_00320190(void*)` | Matching | 100.00% | 72 |
| `func_003201D8(void*)` | Matching | 100.00% | 72 |
| `func_00320220(void*)` | Matching | 100.00% | 76 |
| `func_00320270(void*)` | Matching | 100.00% | 76 |
| `func_003202C0(void*)` | Matching | 100.00% | 52 |
| `func_003202F8(void*)` | Matching | 100.00% | 52 |
| `func_00320330(void*)` | Matching | 100.00% | 52 |
| `func_00320488(void*, void**)` | Matching | 100.00% | 16 |
| `func_00320498(void*, void**)` | Matching | 100.00% | 16 |
| `func_003204A8(void*, void**)` | Matching | 100.00% | 16 |
| `func_003204B8(void*, void**)` | Matching | 100.00% | 24 |
| `func_003204D0(void*, void**)` | Matching | 100.00% | 24 |
| `func_003204E8(void*, void**)` | Matching | 100.00% | 24 |
| `func_00320500(void*, void**)` | Matching | 100.00% | 24 |
| `func_00320518()` | Matching | 100.00% | 8 |
| `func_00320520()` | Matching | 100.00% | 8 |
| `func_00320528()` | Matching | 100.00% | 8 |
| `func_00320530()` | Matching | 100.00% | 8 |
| `func_00320538()` | Matching | 100.00% | 8 |
| `func_00320540()` | Matching | 100.00% | 8 |
| `func_00320548()` | Matching | 100.00% | 8 |
| `func_0031D738(void*, float, float)` | Matching | 99.76% | 84 |
| `func_0031D700(void*)` | Matching | 99.62% | 52 |
| `func_00320058(void*)` | Matching | 99.29% | 28 |
| `func_00320078(void*)` | Matching | 99.29% | 28 |
| `func_00320408(void*)` | Partial | 92.50% | 64 |
| `func_00320448(void*)` | Partial | 92.50% | 64 |
| `func_0031E260(void*)` | Partial | 86.24% | 116 |
| `func_00320368(void*)` | Partial | 71.26% | 76 |
| `func_003203B8(void*)` | Partial | 71.26% | 76 |
| `func_0031FBB8(void *, void *)` | Partial | 48.00% | 104 |

### `bx/execman`

4 matching, 0 partial, 6 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cExecutionMan__cExecutionMan(cExecutionMan *, int)` | Matching | 100.00% | 48 |
| `cExecutionMan_prepause()` | Matching | 100.00% | 8 |
| `cExecutionMan_postpause()` | Matching | 100.00% | 8 |
| `func_00320B08(void*)` | Matching | 100.00% | 28 |

### `bx/memblockman`

4 matching, 0 partial, 32 not started (36 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00319D10(void*)` | Matching | 100.00% | 8 |
| `func_00319D18(void*)` | Matching | 100.00% | 8 |
| `func_0031ABC0(void*)` | Matching | 100.00% | 8 |
| `func_0031ABC8(void*)` | Matching | 100.00% | 8 |

### `bx/memman`

5 matching, 0 partial, 1 not started (6 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `operator_delete(int*)` | Matching | 100.00% | 72 |
| `cMemMan_free(void*)` | Matching | 100.00% | 72 |
| `operator_new1(int)` | Matching | 99.90% | 40 |
| `operator_new2(int)` | Matching | 99.90% | 40 |
| `operator_new(unsigned int)` | Matching | 99.29% | 28 |

### `bx/ps2main`

0 matching, 0 partial, 17 not started (17 total)

### `camera/camera`

41 matching, 0 partial, 144 not started (185 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015F640(void*)` | Matching | 100.00% | 12 |
| `func_0015F680(void*)` | Matching | 100.00% | 16 |
| `func_0015F690(void*)` | Matching | 100.00% | 16 |
| `func_0015F6A0(void*)` | Matching | 100.00% | 16 |
| `func_0015F6E0(void*)` | Matching | 100.00% | 16 |
| `func_0015F6F0(void*)` | Matching | 100.00% | 12 |
| `func_0015F700(void*)` | Matching | 100.00% | 12 |
| `func_0015F710(void*)` | Matching | 100.00% | 12 |
| `func_0015F750(void*)` | Matching | 100.00% | 12 |
| `func_0015F760(void*)` | Matching | 100.00% | 12 |
| `func_0015F770(void*)` | Matching | 100.00% | 12 |
| `func_0015F908(void*)` | Matching | 100.00% | 12 |
| `func_0015F918(void*)` | Matching | 100.00% | 16 |
| `func_0015F928(void*)` | Matching | 100.00% | 16 |
| `func_0015FD48(void*)` | Matching | 100.00% | 8 |
| `func_001604A0(void*)` | Matching | 100.00% | 12 |
| `func_001604B0(void *, void *)` | Matching | 100.00% | 8 |
| `func_001607C8(void*)` | Matching | 100.00% | 12 |
| `func_001607D8(void *, void *)` | Matching | 100.00% | 8 |
| `func_00160BE0(void*)` | Matching | 100.00% | 12 |
| `func_00160BF0(void *, void *)` | Matching | 100.00% | 8 |
| `func_001613D8(void*)` | Matching | 100.00% | 12 |
| `func_001613E8(void *, void *)` | Matching | 100.00% | 8 |
| `func_00161710(void*)` | Matching | 100.00% | 12 |
| `func_00161720(void *, void *)` | Matching | 100.00% | 8 |
| `func_00162310(void*, int)` | Matching | 100.00% | 8 |
| `func_00166530(void*)` | Matching | 100.00% | 28 |
| `func_00167E18(void*)` | Matching | 100.00% | 8 |
| `func_00167E20(void*)` | Matching | 100.00% | 8 |
| `func_00167E28(void*)` | Matching | 100.00% | 8 |
| `func_00167E58(void*)` | Matching | 100.00% | 8 |
| `func_00167E60(void*)` | Matching | 100.00% | 8 |
| `func_00167E90(void*)` | Matching | 100.00% | 8 |
| `func_00167E98(void*)` | Matching | 100.00% | 8 |
| `func_00167FB0(void*)` | Matching | 100.00% | 8 |
| `func_00167FB8(void*)` | Matching | 100.00% | 8 |
| `func_00168060(void*)` | Matching | 100.00% | 28 |
| `func_00168320(void*)` | Matching | 100.00% | 12 |
| `func_00168330(void *, void *)` | Matching | 100.00% | 8 |
| `func_001686B8(void*)` | Matching | 100.00% | 12 |
| `func_001686C8(void *, void *)` | Matching | 100.00% | 8 |

### `camera/cameraalgolist`

0 matching, 0 partial, 3 not started (3 total)

### `camera/cameraalgorithms`

0 matching, 0 partial, 6 not started (6 total)

### `camera/cameracontroller`

0 matching, 0 partial, 14 not started (14 total)

### `camera/script/scriptcontroller`

3 matching, 0 partial, 28 not started (31 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001694A8(void*, int)` | Matching | 100.00% | 8 |
| `func_001694B0(void*)` | Matching | 100.00% | 8 |
| `func_0016BEE8(void*)` | Matching | 100.00% | 12 |

### `camera/trigger/cameratriggerfactory`

12 matching, 0 partial, 102 not started (114 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `get_cCTActionNone(void*, int*)` | Matching | 100.00% | 16 |
| `get_cCTBoundObjPoint(void*, sBoundObjPoint*)` | Matching | 100.00% | 72 |
| `func_00176440(void*)` | Matching | 100.00% | 8 |
| `func_00176448(void*)` | Matching | 100.00% | 8 |
| `func_00176450(void*)` | Matching | 100.00% | 8 |
| `func_00176458(void*)` | Matching | 100.00% | 8 |
| `func_00176460(void*)` | Matching | 100.00% | 8 |
| `func_001765F8(void*)` | Matching | 100.00% | 8 |
| `func_00177548(void*)` | Matching | 100.00% | 12 |
| `func_00178B98(void*)` | Matching | 100.00% | 12 |
| `func_00178BA8(void *, void *)` | Matching | 100.00% | 8 |
| `func_0017ABC8(void*)` | Matching | 100.00% | 24 |

### `camera/trigger/cameratriggerlist`

3 matching, 1 partial, 5 not started (9 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cCameraTriggerList_init(cCameraTriggerList*)` | Matching | 100.00% | 32 |
| `cCameraTriggerList_initHeader(cCameraTriggerList*)` | Matching | 100.00% | 24 |
| `cCameraTriggerList_readCookie(cCameraTriggerList*, void*)` | Matching | 99.44% | 36 |
| `cCameraTriggerList_insert(cCameraTriggerList2*, void*, int)` | Partial | 27.25% | 80 |

### `camera/trigger/cameratriggerman`

4 matching, 0 partial, 20 not started (24 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0016CA10(void*)` | Matching | 100.00% | 8 |
| `func_0016CF40(void*)` | Matching | 100.00% | 8 |
| `cCameraTriggerStack_init(cCameraTriggerStack*)` | Matching | 100.00% | 12 |
| `cCameraTriggerMan_setInGameTriggers(void*)` | Matching | 99.29% | 28 |

### `camera/trigger/cameratriggervolumes`

2 matching, 0 partial, 1 not started (3 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `tCameraTrigger__tCameraTrigger__FPvi` | Matching | 100.00% | 36 |
| `func_0016C5D0(void*)` | Matching | 100.00% | 12 |

### `camera/trigger/triggeralgorithms`

1 matching, 0 partial, 9 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cActiveTriggerList_purge(cActiveTriggerList*)` | Matching | 100.00% | 80 |

### `data/vutext`

0 matching, 0 partial, 1 not started (1 total)

### `dirtysock/tags`

0 matching, 0 partial, 25 not started (25 total)

### `dirtysock/tagsunk`

14 matching, 6 partial, 272 not started (292 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00259390(void*)` | Matching | 100.00% | 8 |
| `func_0025FC20(void*)` | Matching | 100.00% | 8 |
| `func_00261A20(void*)` | Matching | 100.00% | 8 |
| `func_00262390(void*)` | Matching | 100.00% | 32 |
| `func_002623E0(void*)` | Matching | 100.00% | 32 |
| `func_00266D00(void*)` | Matching | 100.00% | 16 |
| `func_00266F38(void*)` | Matching | 100.00% | 28 |
| `func_00267DA8(void*)` | Matching | 100.00% | 28 |
| `func_00267DC8(void*)` | Matching | 100.00% | 8 |
| `func_00267DD0(void*)` | Matching | 100.00% | 8 |
| `func_00267DE8(void*)` | Matching | 100.00% | 8 |
| `func_00267DF0(void*)` | Matching | 100.00% | 8 |
| `func_00267DF8(void*)` | Matching | 100.00% | 8 |
| `func_00267E10(void*)` | Matching | 100.00% | 8 |
| `func_00261058(void*)` | Partial | 99.50% | 24 |
| `func_00265DF0(void*)` | Partial | 63.33% | 12 |
| `func_00265E00(void*)` | Partial | 63.33% | 12 |
| `func_00265E10(void*)` | Partial | 63.33% | 12 |
| `func_00265E20(void*)` | Partial | 63.33% | 12 |
| `func_00265E30(void*)` | Partial | 63.33% | 12 |

### `fe/debugfe`

1 matching, 0 partial, 85 not started (86 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0017FAB0(void*)` | Matching | 100.00% | 32 |

### `fe/feasyncfile`

30 matching, 1 partial, 492 not started (523 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cFEAsyncManager_GetFileStatus(cFEAsyncManager*, int)` | Matching | 100.00% | 20 |
| `cFEAsyncManager_SetFileStatus(cFEAsyncManager*, int, int)` | Matching | 100.00% | 20 |
| `func_001A7B20(void*)` | Matching | 100.00% | 28 |
| `func_001A7BB0(void*)` | Matching | 100.00% | 8 |
| `func_001A8768(void*)` | Matching | 100.00% | 8 |
| `func_001A8828(void*)` | Matching | 100.00% | 8 |
| `func_001A94D8(void*)` | Matching | 100.00% | 8 |
| `func_001A98B0(void*)` | Matching | 100.00% | 8 |
| `func_001AC150(void*)` | Matching | 100.00% | 28 |
| `func_001AD1E8(void*)` | Matching | 100.00% | 28 |
| `func_001AE0E0(void*)` | Matching | 100.00% | 28 |
| `func_001B0130(void*)` | Matching | 100.00% | 28 |
| `func_001B1048(void*)` | Matching | 100.00% | 28 |
| `func_001B6078(void*)` | Matching | 100.00% | 8 |
| `func_001B89E8(void*)` | Matching | 100.00% | 28 |
| `func_001BA4E0(void*)` | Matching | 100.00% | 28 |
| `func_001BBAA8(void*)` | Matching | 100.00% | 32 |
| `func_001BBDE0(void*)` | Matching | 100.00% | 28 |
| `func_001BCE18(void*)` | Matching | 100.00% | 28 |
| `func_001BE890(void*)` | Matching | 100.00% | 28 |
| `func_001BEA30(void*)` | Matching | 100.00% | 8 |
| `func_001BEF40(void*)` | Matching | 100.00% | 28 |
| `func_001BFCA0(void*)` | Matching | 100.00% | 28 |
| `func_001C0E88(void*)` | Matching | 100.00% | 28 |
| `func_001C17D8(void*)` | Matching | 100.00% | 8 |
| `func_001C1D10(void*)` | Matching | 100.00% | 28 |
| `func_001C21A0(void*)` | Matching | 100.00% | 28 |
| `func_001C2EE0(void*)` | Matching | 100.00% | 28 |
| `func_001C5178(void*)` | Matching | 100.00% | 28 |
| `func_001B7088(void*)` | Matching | 99.29% | 28 |
| `func_001B4198(void*)` | Partial | 63.33% | 12 |

### `fe/feflowstate`

0 matching, 0 partial, 4 not started (4 total)

### `fe/fememcard`

1 matching, 0 partial, 19 not started (20 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00187C10(void*)` | Matching | 100.00% | 8 |

### `fe/fememcardcallbacks`

5 matching, 3 partial, 49 not started (57 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D93A8(void*)` | Matching | 100.00% | 8 |
| `func_001D93C0(void*)` | Matching | 100.00% | 8 |
| `func_001D93C8(void*)` | Matching | 100.00% | 8 |
| `func_001D93D0(void*)` | Matching | 100.00% | 8 |
| `func_001D9878(void*)` | Matching | 100.00% | 8 |
| `func_001D8C38(void*)` | Partial | 99.60% | 20 |
| `func_001D86A0(void*)` | Partial | 63.33% | 12 |
| `func_001D93B0(void*)` | Partial | 63.33% | 12 |

### `fe/fepopup`

2 matching, 0 partial, 117 not started (119 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001C5DD0(void*)` | Matching | 100.00% | 8 |
| `func_001CA578(void*)` | Matching | 100.00% | 28 |

### `fe/fepopupmisc`

122 matching, 0 partial, 168 not started (290 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DF378(void*)` | Matching | 100.00% | 8 |
| `func_001DF578(void*)` | Matching | 100.00% | 8 |
| `func_001DF5C0(void*)` | Matching | 100.00% | 8 |
| `func_001DF630(void*)` | Matching | 100.00% | 8 |
| `func_001DF6A0(void*)` | Matching | 100.00% | 8 |
| `func_001DF8E0(void*)` | Matching | 100.00% | 8 |
| `func_001DF988(void*)` | Matching | 100.00% | 8 |
| `func_001DFA88(void*)` | Matching | 100.00% | 8 |
| `func_001DFAA0(void*)` | Matching | 100.00% | 8 |
| `func_001DFAA8(void*)` | Matching | 100.00% | 8 |
| `func_001DFAC0(void*)` | Matching | 100.00% | 8 |
| `func_001DFAC8(void*)` | Matching | 100.00% | 8 |
| `func_001DFAD0(void*)` | Matching | 100.00% | 8 |
| `func_001DFAD8(void*)` | Matching | 100.00% | 8 |
| `func_001DFAE0(void*)` | Matching | 100.00% | 8 |
| `func_001DFAE8(void*)` | Matching | 100.00% | 8 |
| `func_001DFBB0(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFBB8(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFC80(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFC88(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFD50(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFD58(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFE20(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFE28(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFEF0(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFEF8(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFFC0(void *, void *)` | Matching | 100.00% | 8 |
| `func_001DFFC8(void *, void *)` | Matching | 100.00% | 8 |
| `func_001E0020(void*)` | Matching | 100.00% | 8 |
| `func_001E0028(void*)` | Matching | 100.00% | 8 |
| `func_001E04F8(void*)` | Matching | 100.00% | 8 |
| `func_001E0500(void*)` | Matching | 100.00% | 8 |
| `func_001E0508(void*)` | Matching | 100.00% | 8 |
| `func_001E0770(void*)` | Matching | 100.00% | 8 |
| `func_001E0778(void*)` | Matching | 100.00% | 8 |
| `func_001E07B0(void*)` | Matching | 100.00% | 8 |
| `func_001E07B8(void*)` | Matching | 100.00% | 8 |
| `func_001E08D0(void*)` | Matching | 100.00% | 8 |
| `func_001E0940(void*)` | Matching | 100.00% | 8 |
| `func_001E0948(void*)` | Matching | 100.00% | 8 |
| `func_001E0A00(void*)` | Matching | 100.00% | 8 |
| `func_001E0AB8(void*)` | Matching | 100.00% | 8 |
| `func_001E0BA0(void*)` | Matching | 100.00% | 8 |
| `func_001E0BA8(void*)` | Matching | 100.00% | 8 |
| `func_001E0C10(void*)` | Matching | 100.00% | 8 |
| `func_001E0C18(void*)` | Matching | 100.00% | 8 |
| `func_001E0C20(void*)` | Matching | 100.00% | 8 |
| `func_001E0C28(void*)` | Matching | 100.00% | 8 |
| `func_001E0C78(void*)` | Matching | 100.00% | 8 |
| `func_001E0C80(void*)` | Matching | 100.00% | 8 |
| `func_001E0C88(void*)` | Matching | 100.00% | 8 |
| `func_001E0C90(void*)` | Matching | 100.00% | 8 |
| `func_001E0C98(void*)` | Matching | 100.00% | 8 |
| `func_001E0D60(void*)` | Matching | 100.00% | 8 |
| `func_001E0DD0(void*)` | Matching | 100.00% | 8 |
| `func_001E0E40(void*)` | Matching | 100.00% | 8 |
| `func_001E0E88(void*)` | Matching | 100.00% | 8 |
| `func_001E0E90(void*)` | Matching | 100.00% | 8 |
| `func_001E0EC0(void*)` | Matching | 100.00% | 8 |
| `func_001E0EF0(void*)` | Matching | 100.00% | 8 |
| `func_001E0F58(void*)` | Matching | 100.00% | 8 |
| `func_001E0FB8(void*)` | Matching | 100.00% | 8 |
| `func_001E1040(void*)` | Matching | 100.00% | 8 |
| `func_001E1078(void*)` | Matching | 100.00% | 8 |
| `func_001E1080(void*)` | Matching | 100.00% | 8 |
| `func_001E1088(void*)` | Matching | 100.00% | 8 |
| `func_001E10E8(void*)` | Matching | 100.00% | 8 |
| `func_001E10F0(void*)` | Matching | 100.00% | 8 |
| `func_001E10F8(void*)` | Matching | 100.00% | 8 |
| `func_001E1100(void*)` | Matching | 100.00% | 8 |
| `func_001E1138(void*)` | Matching | 100.00% | 8 |
| `func_001E1140(void*)` | Matching | 100.00% | 8 |
| `func_001E1148(void*)` | Matching | 100.00% | 8 |
| `func_001E1150(void*)` | Matching | 100.00% | 8 |
| `func_001E1158(void*)` | Matching | 100.00% | 8 |
| `func_001E1160(void*)` | Matching | 100.00% | 8 |
| `func_001E1168(void*)` | Matching | 100.00% | 8 |
| `func_001E1170(void*)` | Matching | 100.00% | 8 |
| `func_001E1178(void*)` | Matching | 100.00% | 8 |
| `func_001E1180(void*)` | Matching | 100.00% | 8 |
| `func_001E1188(void*)` | Matching | 100.00% | 8 |
| `func_001E1190(void*)` | Matching | 100.00% | 8 |
| `func_001E1198(void*)` | Matching | 100.00% | 8 |
| `func_001E11A0(void*)` | Matching | 100.00% | 8 |
| `func_001E11A8(void*)` | Matching | 100.00% | 8 |
| `func_001E11B0(void*)` | Matching | 100.00% | 8 |
| `func_001E11B8(void*)` | Matching | 100.00% | 8 |
| `func_001E11C0(void*)` | Matching | 100.00% | 8 |
| `func_001E11C8(void*)` | Matching | 100.00% | 8 |
| `func_001E11D0(void*)` | Matching | 100.00% | 8 |
| `func_001E11D8(void*)` | Matching | 100.00% | 8 |
| `func_001E11E0(void*)` | Matching | 100.00% | 8 |
| `func_001E11E8(void*)` | Matching | 100.00% | 8 |
| `func_001E11F0(void*)` | Matching | 100.00% | 8 |
| `func_001E11F8(void*)` | Matching | 100.00% | 8 |
| `func_001E1200(void*)` | Matching | 100.00% | 8 |
| `func_001E1208(void*)` | Matching | 100.00% | 8 |
| `func_001E1210(void*)` | Matching | 100.00% | 8 |
| `func_001E1218(void*)` | Matching | 100.00% | 8 |
| `func_001E1220(void*)` | Matching | 100.00% | 8 |
| `func_001E1228(void*)` | Matching | 100.00% | 8 |
| `func_001E1230(void*)` | Matching | 100.00% | 8 |
| `func_001E1238(void*)` | Matching | 100.00% | 8 |
| `func_001E1240(void*)` | Matching | 100.00% | 8 |
| `func_001E1248(void*)` | Matching | 100.00% | 12 |
| `func_001E1258(void*)` | Matching | 100.00% | 12 |
| `func_001E1268(void*)` | Matching | 100.00% | 12 |
| `func_001E1278(void*)` | Matching | 100.00% | 8 |
| `func_001E1280(void*)` | Matching | 100.00% | 8 |
| `func_001E1288(void*)` | Matching | 100.00% | 8 |
| `func_001E1290(void*)` | Matching | 100.00% | 8 |
| `func_001E1298(void*, int)` | Matching | 100.00% | 8 |
| `func_001E12A0(void*)` | Matching | 100.00% | 8 |
| `func_001E12A8(void*)` | Matching | 100.00% | 8 |
| `func_001E1548(void*)` | Matching | 100.00% | 8 |
| `func_001E33E8(void*)` | Matching | 100.00% | 32 |
| `func_001E52B0(void*)` | Matching | 100.00% | 28 |
| `func_001E64A8(void*)` | Matching | 100.00% | 28 |
| `func_001E7920(void*)` | Matching | 100.00% | 8 |
| `func_001E8E70(void*)` | Matching | 100.00% | 28 |
| `func_001E8E90(void*)` | Matching | 100.00% | 8 |
| `func_001E8FC0(void*)` | Matching | 100.00% | 8 |

### `fe/fereal`

0 matching, 0 partial, 21 not started (21 total)

### `fe/feridermanager`

0 matching, 0 partial, 30 not started (30 total)

### `fe/festateaudiooptions`

0 matching, 0 partial, 8 not started (8 total)

### `fe/festatebigradio`

2 matching, 0 partial, 15 not started (17 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00193310(void*)` | Matching | 100.00% | 8 |
| `func_00193318(void*)` | Matching | 100.00% | 28 |

### `fe/festatebonusmaterial`

1 matching, 0 partial, 4 not started (5 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001955E0(void*)` | Matching | 100.00% | 28 |

### `fe/festatebuyattrib`

0 matching, 0 partial, 29 not started (29 total)

### `fe/festatecharequip`

0 matching, 0 partial, 5 not started (5 total)

### `fe/festatecharequipdetail`

0 matching, 0 partial, 78 not started (78 total)

### `fe/festatecharselect`

1 matching, 0 partial, 17 not started (18 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00181400(void*)` | Matching | 100.00% | 28 |

### `fe/festatecharsetup`

0 matching, 0 partial, 9 not started (9 total)

### `fe/festatecredits`

0 matching, 0 partial, 10 not started (10 total)

### `fe/festatedebug`

0 matching, 0 partial, 3 not started (3 total)

### `fe/festatelegal`

0 matching, 0 partial, 4 not started (4 total)

### `fe/festateload`

1 matching, 0 partial, 12 not started (13 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00186B48(void*)` | Matching | 100.00% | 8 |

### `fe/festateloadhint`

3 matching, 0 partial, 24 not started (27 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00245B50(void*)` | Matching | 100.00% | 8 |
| `func_00245DB8(void*)` | Matching | 100.00% | 8 |
| `func_00245F30(void*)` | Matching | 100.00% | 28 |

### `fe/festateloadscreen`

5 matching, 0 partial, 23 not started (28 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00233B88(void*)` | Matching | 100.00% | 8 |
| `func_00233B90(void*)` | Matching | 99.29% | 28 |
| `func_00233BB0(void*)` | Matching | 99.29% | 28 |
| `func_00233BD0(void*)` | Matching | 99.29% | 28 |
| `func_00233BF0(void*)` | Matching | 99.29% | 28 |

### `fe/festatelodge`

0 matching, 0 partial, 13 not started (13 total)

### `fe/festatenethelppopup`

2 matching, 0 partial, 19 not started (21 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D9F30(void*)` | Matching | 100.00% | 8 |
| `func_001DA528(void*, int)` | Matching | 100.00% | 8 |

### `fe/festateoptions`

3 matching, 0 partial, 55 not started (58 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001895F0(void*)` | Matching | 100.00% | 28 |
| `func_0018A870(void*)` | Matching | 100.00% | 28 |
| `func_0018C198(void*)` | Matching | 100.00% | 28 |

### `fe/festateprofile`

1 matching, 0 partial, 20 not started (21 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0018EE98(void*)` | Matching | 100.00% | 28 |

### `fe/festaterewards`

0 matching, 0 partial, 75 not started (75 total)

### `fe/festateriderbio`

1 matching, 0 partial, 10 not started (11 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001835A8(void*)` | Matching | 100.00% | 28 |

### `fe/festateriderbiodetail`

0 matching, 0 partial, 9 not started (9 total)

### `fe/festateruleselect`

2 matching, 0 partial, 16 not started (18 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00191C48(void*)` | Matching | 100.00% | 28 |
| `func_00192968(void*, int)` | Matching | 100.00% | 8 |

### `fe/festateselectmp`

0 matching, 0 partial, 4 not started (4 total)

### `fe/festatestore`

0 matching, 0 partial, 14 not started (14 total)

### `fe/festatetransition`

0 matching, 0 partial, 5 not started (5 total)

### `fe/festatetrophyroom`

2 matching, 0 partial, 34 not started (36 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D43D0(void*)` | Matching | 100.00% | 28 |
| `func_001D5F38(void*)` | Matching | 100.00% | 8 |

### `fe/messagecenter`

1 matching, 0 partial, 22 not started (23 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00198AE8(void*)` | Matching | 100.00% | 8 |

### `fe/ovstateenterlodge`

0 matching, 0 partial, 22 not started (22 total)

### `fe/ovstatehud`

2 matching, 3 partial, 30 not started (35 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E9290(void *, void *)` | Matching | 100.00% | 20 |
| `func_001F30C0(void*)` | Matching | 100.00% | 24 |
| `func_001F3170(void*)` | Partial | 99.20% | 20 |
| `func_001E91A8(void *, void *)` | Partial | 64.67% | 36 |
| `func_001E91D0(void *, void *)` | Partial | 64.67% | 36 |

### `fe/ovstatelodge`

1 matching, 0 partial, 21 not started (22 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D3C60(void*)` | Matching | 100.00% | 28 |

### `fe/ovstatemap`

1 matching, 0 partial, 23 not started (24 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002087E8(void*)` | Matching | 100.00% | 8 |

### `fe/ovstatemission`

3 matching, 0 partial, 6 not started (9 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A3300(void*)` | Matching | 100.00% | 8 |
| `func_001A34A0(void*)` | Matching | 100.00% | 8 |
| `func_001A34A8(void*)` | Matching | 100.00% | 8 |

### `fe/ovstatepause`

2 matching, 0 partial, 58 not started (60 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001FAF08(void*)` | Matching | 100.00% | 8 |
| `func_001FEC40(void*)` | Matching | 100.00% | 28 |

### `fe/ovstateprofile`

1 matching, 0 partial, 19 not started (20 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002122E0(void*)` | Matching | 100.00% | 8 |

### `fe/ovstatereplay`

1 matching, 0 partial, 7 not started (8 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0020E8E0(void*)` | Matching | 100.00% | 28 |

### `fe/ovstaterewardslist`

0 matching, 0 partial, 4 not started (4 total)

### `fe/ovstates`

1 matching, 0 partial, 15 not started (16 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00194980(void*)` | Matching | 100.00% | 8 |

### `fe/ovstatetrophy`

0 matching, 0 partial, 24 not started (24 total)

### `fe/ovtemplatedialog`

0 matching, 0 partial, 21 not started (21 total)

### `fe/ovtemplatepausemenu`

2 matching, 0 partial, 14 not started (16 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001F8720(void*)` | Matching | 100.00% | 8 |
| `func_001F8DF0(void*)` | Matching | 100.00% | 8 |

### `fe/uitemplatemap`

2 matching, 0 partial, 36 not started (38 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00202768(void*)` | Matching | 100.00% | 8 |
| `cUITemplate_MAP_setupEventUnlock(cUITemplate_MAP*)` | Matching | 99.91% | 44 |

### `hashvalue`

3 matching, 1 partial, 2 not started (6 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `tHashName32_getHashValue(unsigned int*, char*)` | Matching | 100.00% | 88 |
| `GetHashValue32(char*)` | Matching | 100.00% | 32 |
| `GetHashValue64(char*)` | Matching | 100.00% | 32 |
| `tHashName64_getHashValue(unsigned long*, char*)` | Partial | 20.50% | 96 |

### `input/inputmap`

0 matching, 0 partial, 13 not started (13 total)

### `input/inputparse`

6 matching, 0 partial, 53 not started (59 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00325250(void*)` | Matching | 100.00% | 12 |
| `func_00326A20(void*)` | Matching | 100.00% | 8 |
| `func_00327738(void*)` | Matching | 100.00% | 8 |
| `func_00327800(void*)` | Matching | 100.00% | 8 |
| `func_00327808(void*)` | Matching | 100.00% | 8 |
| `func_00327810(void*)` | Matching | 100.00% | 24 |

### `intersect/aifwddiff`

0 matching, 0 partial, 19 not started (19 total)

### `intersect/riderspheretree`

2 matching, 1 partial, 66 not started (69 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0032E688(void*)` | Matching | 100.00% | 8 |
| `func_0032F8B0(void*)` | Matching | 100.00% | 16 |
| `cRiderSphereTree_cRiderSphereTree(cRiderSphereTree*)` | Partial | 0.00% | 36 |

### `intersect/worldsphtree`

3 matching, 0 partial, 73 not started (76 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00330778(void*)` | Matching | 100.00% | 16 |
| `func_00340A08(void*)` | Matching | 100.00% | 8 |
| `func_00340A10(void*)` | Matching | 100.00% | 8 |

### `luno/lunovm`

3 matching, 1 partial, 22 not started (26 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00226610(void*)` | Matching | 100.00% | 8 |
| `func_00226618(void*)` | Matching | 100.00% | 8 |
| `func_00226620(void*)` | Matching | 100.00% | 8 |
| `func_00226600(void*, int, int)` | Partial | 96.00% | 12 |

### `main/debugmenu`

42 matching, 0 partial, 49 not started (91 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0024D690(void*)` | Matching | 100.00% | 28 |
| `func_0024D6B0(void*)` | Matching | 100.00% | 28 |
| `func_0024F7E0(void*)` | Matching | 100.00% | 28 |
| `func_0024F800(void*)` | Matching | 100.00% | 28 |
| `func_0024F820(void*)` | Matching | 100.00% | 28 |
| `func_0024F840(void*)` | Matching | 100.00% | 28 |
| `func_0024F940(void*)` | Matching | 100.00% | 28 |
| `func_0024F960(void*)` | Matching | 100.00% | 28 |
| `func_0024F980(void*)` | Matching | 100.00% | 28 |
| `func_0024F9A0(void*)` | Matching | 100.00% | 28 |
| `func_0024F9C0(void*)` | Matching | 100.00% | 28 |
| `func_0024F9E0(void*)` | Matching | 100.00% | 28 |
| `func_0024FA78(void*)` | Matching | 100.00% | 28 |
| `func_0024FA98(void*)` | Matching | 100.00% | 28 |
| `func_0024FB80(void*)` | Matching | 100.00% | 28 |
| `func_0024FBA0(void*)` | Matching | 100.00% | 28 |
| `func_0024FC80(void*)` | Matching | 100.00% | 28 |
| `func_0024FCA0(void*)` | Matching | 100.00% | 28 |
| `func_0024FCC0(void*)` | Matching | 100.00% | 28 |
| `func_0024FCE0(void*)` | Matching | 100.00% | 28 |
| `func_0024FDC0(void*)` | Matching | 100.00% | 28 |
| `func_0024FDE0(void*)` | Matching | 100.00% | 28 |
| `func_0024FEA8(void*)` | Matching | 100.00% | 28 |
| `func_0024FEC8(void*)` | Matching | 100.00% | 28 |
| `func_0024FEE8(void*)` | Matching | 100.00% | 28 |
| `func_0024FF08(void*)` | Matching | 100.00% | 28 |
| `func_0024FF90(void*)` | Matching | 100.00% | 28 |
| `func_0024FFB0(void*)` | Matching | 100.00% | 28 |
| `func_0024FFD0(void*)` | Matching | 100.00% | 28 |
| `func_0024FFF0(void*)` | Matching | 100.00% | 28 |
| `func_00250010(void*)` | Matching | 100.00% | 28 |
| `func_00250030(void*)` | Matching | 100.00% | 28 |
| `func_00250050(void*)` | Matching | 100.00% | 28 |
| `func_00250070(void*)` | Matching | 100.00% | 28 |
| `func_00250128(void*)` | Matching | 100.00% | 28 |
| `func_00250148(void*)` | Matching | 100.00% | 28 |
| `func_00250168(void*)` | Matching | 100.00% | 28 |
| `func_00250188(void*)` | Matching | 100.00% | 28 |
| `func_00250A60(void*)` | Matching | 100.00% | 28 |
| `func_00250A80(void*)` | Matching | 100.00% | 28 |
| `func_002515F0(void*)` | Matching | 100.00% | 28 |
| `func_00251610(void*)` | Matching | 100.00% | 28 |

### `main/game`

0 matching, 0 partial, 31 not started (31 total)

### `main/gameload`

2 matching, 0 partial, 33 not started (35 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00231278(void*, int)` | Matching | 100.00% | 8 |
| `func_00231CB0(void*)` | Matching | 100.00% | 28 |

### `main/gamemode`

2 matching, 0 partial, 48 not started (50 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00238348(void*)` | Matching | 100.00% | 12 |
| `func_0023AC10(void*)` | Matching | 100.00% | 8 |

### `main/gamerender`

0 matching, 0 partial, 8 not started (8 total)

### `main/gamestate`

19 matching, 0 partial, 54 not started (73 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00234DE0(void*)` | Matching | 100.00% | 28 |
| `func_00234E00(void*)` | Matching | 100.00% | 28 |
| `func_00234EB8(void*)` | Matching | 100.00% | 28 |
| `func_00234ED8(void*)` | Matching | 100.00% | 28 |
| `func_002361C8(void*)` | Matching | 100.00% | 28 |
| `func_002361E8(void*)` | Matching | 100.00% | 28 |
| `func_00236AF0(void*)` | Matching | 100.00% | 8 |
| `func_00236AF8(void*)` | Matching | 100.00% | 28 |
| `func_00236B18(void*)` | Matching | 100.00% | 28 |
| `func_00236B70(void*)` | Matching | 100.00% | 28 |
| `func_00236B90(void*)` | Matching | 100.00% | 28 |
| `func_00236D60(void*)` | Matching | 100.00% | 28 |
| `func_00236D80(void*)` | Matching | 100.00% | 28 |
| `func_00236EC8(void*)` | Matching | 100.00% | 28 |
| `func_00236EE8(void*)` | Matching | 100.00% | 28 |
| `func_00236FA8(void*)` | Matching | 100.00% | 28 |
| `func_00236FC8(void*)` | Matching | 100.00% | 28 |
| `func_00237030(void*)` | Matching | 100.00% | 8 |
| `func_00237948(void*)` | Matching | 100.00% | 8 |

### `main/loadscreens`

0 matching, 0 partial, 4 not started (4 total)

### `main/loadscreens_prestart`

4 matching, 0 partial, 30 not started (34 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00232710(void*)` | Matching | 100.00% | 8 |
| `func_00232718(void*)` | Matching | 100.00% | 8 |
| `func_00232CF8(void*)` | Matching | 100.00% | 28 |
| `func_002332C8(void*)` | Matching | 100.00% | 32 |

### `main/sectionman`

1 matching, 1 partial, 5 not started (7 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0022E288(void *, void *)` | Matching | 100.00% | 16 |
| `func_0022E278(void*)` | Partial | 95.00% | 16 |

### `main/ssxapp`

4 matching, 0 partial, 44 not started (48 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00229F80(void*)` | Matching | 100.00% | 8 |
| `cSSXApp_loadexecpurge(void*)` | Matching | 99.95% | 76 |
| `cSSXApp_flush()` | Matching | 99.91% | 44 |
| `cSSXApp_timerCallback()` | Matching | 99.89% | 36 |

### `main/ssxappdtor`

29 matching, 0 partial, 61 not started (90 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243AB0(void*)` | Matching | 100.00% | 8 |
| `func_00243CB0(void*)` | Matching | 100.00% | 8 |
| `func_00243CB8(void*)` | Matching | 100.00% | 8 |
| `func_00243CC0(void*)` | Matching | 100.00% | 8 |
| `func_00243CC8(void*)` | Matching | 100.00% | 8 |
| `func_00243CD0(void*)` | Matching | 100.00% | 8 |
| `func_00243CD8(void*)` | Matching | 100.00% | 8 |
| `func_00243CE0(void*)` | Matching | 100.00% | 8 |
| `func_00243CE8(void*)` | Matching | 100.00% | 8 |
| `func_002443F8(void*)` | Matching | 100.00% | 8 |
| `func_00244400(void*, int)` | Matching | 100.00% | 8 |
| `func_00244408(void*, int)` | Matching | 100.00% | 8 |
| `func_00244528(void*)` | Matching | 100.00% | 8 |
| `func_00244530(void*)` | Matching | 100.00% | 8 |
| `func_00244538(void*)` | Matching | 100.00% | 8 |
| `func_00244540(void*)` | Matching | 100.00% | 8 |
| `func_00244548(void*)` | Matching | 100.00% | 8 |
| `func_00244550(void*)` | Matching | 100.00% | 8 |
| `func_00244558(void*)` | Matching | 100.00% | 8 |
| `func_00244620(void*)` | Matching | 100.00% | 8 |
| `func_00244628(void*)` | Matching | 100.00% | 8 |
| `func_00244860(void*)` | Matching | 100.00% | 8 |
| `func_00244868(void*)` | Matching | 100.00% | 8 |
| `func_00244870(void*)` | Matching | 100.00% | 8 |
| `func_00244878(void*)` | Matching | 100.00% | 8 |
| `func_00244880(void*)` | Matching | 100.00% | 8 |
| `func_00245228(void*)` | Matching | 100.00% | 28 |
| `func_00245690(void*)` | Matching | 100.00% | 8 |
| `func_002458B0(void*)` | Matching | 100.00% | 8 |

### `main/streampause`

1 matching, 0 partial, 2 not started (3 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cStreamPause_construct()` | Matching | 100.00% | 60 |

### `md5`

1 matching, 0 partial, 3 not started (4 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `md5_init(md5_ctx*)` | Matching | 100.00% | 60 |

### `mem/memstd`

7 matching, 1 partial, 41 not started (49 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00252658(void*)` | Matching | 100.00% | 8 |
| `func_00255668(void*)` | Matching | 100.00% | 8 |
| `func_00255830(void*)` | Matching | 100.00% | 16 |
| `func_00253AF8(void*)` | Matching | 99.29% | 28 |
| `func_00254DA0(void*)` | Matching | 99.29% | 28 |
| `MEM_print()` | Matching | 99.25% | 32 |
| `MEM_printclass(void*)` | Matching | 98.50% | 40 |
| `func_00254400(void*, float, float)` | Partial | 96.00% | 12 |

### `movie/movieplayer`

7 matching, 0 partial, 107 not started (114 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0023E2C0(void*)` | Matching | 100.00% | 8 |
| `func_0023E4F0(void*)` | Matching | 100.00% | 8 |
| `func_0023FB18(void*, int)` | Matching | 100.00% | 8 |
| `func_00242500(void*)` | Matching | 100.00% | 24 |
| `cMCOverlayManager_getManager()` | Matching | 99.82% | 68 |
| `func_0023CC58(void*)` | Matching | 99.29% | 28 |
| `func_00240F10(void*)` | Matching | 99.29% | 28 |

### `object/animnode`

0 matching, 0 partial, 9 not started (9 total)

### `object/bucketman`

1 matching, 2 partial, 15 not started (18 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBucketMan_next(cBucketMan*, void*, int)` | Matching | 100.00% | 36 |
| `cBucketMan_first(cBucketMan*, int)` | Partial | 95.00% | 36 |
| `cBucketMan_addfirst(cBucketMan*, int)` | Partial | 95.00% | 36 |

### `object/deadfadenode`

3 matching, 0 partial, 10 not started (13 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00350E70(void*)` | Matching | 100.00% | 28 |
| `func_00350F40(void*)` | Matching | 100.00% | 28 |
| `func_00351010(void*)` | Matching | 100.00% | 28 |

### `object/debouncenode`

2 matching, 0 partial, 41 not started (43 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00342E78(void*)` | Matching | 100.00% | 28 |
| `func_00344348(void*)` | Matching | 100.00% | 28 |

### `object/effectlink`

1 matching, 1 partial, 28 not started (30 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cEffectLink_add(cEffectLink *, cEffectLink *)` | Matching | 100.00% | 32 |
| `func_00346060(void*)` | Partial | 63.33% | 12 |

### `object/flagset`

0 matching, 0 partial, 35 not started (35 total)

### `object/flexbridgenode`

0 matching, 0 partial, 17 not started (17 total)

### `object/flexrailnode`

2 matching, 0 partial, 32 not started (34 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0034AEF8(void*)` | Matching | 100.00% | 28 |
| `func_0034AF18(void*)` | Matching | 100.00% | 8 |

### `object/floatingnode`

0 matching, 1 partial, 9 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cFloatingNode_initInfo(cFloatingNode*)` | Partial | 93.68% | 76 |

### `object/instanceman`

2 matching, 0 partial, 18 not started (20 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cInstanceMan_copyInstance(void *, sInstanceStruct *, void *)` | Matching | 100.00% | 76 |
| `func_00351A60(void*)` | Matching | 99.29% | 28 |

### `object/instancenode`

0 matching, 0 partial, 16 not started (16 total)

### `object/modifierblock`

4 matching, 1 partial, 31 not started (36 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `tModifierBlock_tModifierBlock(tModifierBlock*)` | Matching | 100.00% | 64 |
| `tModifierBlock_setRadius(tModifierBlock*)` | Matching | 100.00% | 52 |
| `func_00353D98(void*)` | Matching | 100.00% | 16 |
| `func_00353DA8(void*)` | Matching | 100.00% | 12 |
| `tModifierBlock_setBoundBox(tModifierBlock*)` | Partial | 98.46% | 52 |

### `object/movenode`

5 matching, 0 partial, 91 not started (96 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cMoveNode_addModifierBlock(cMoveNode*)` | Matching | 100.00% | 68 |
| `func_00355878(void *, void *)` | Matching | 100.00% | 12 |
| `cMoveNode_addEffectModifier(cMoveNode*, void*)` | Matching | 99.74% | 76 |
| `func_00356E98(void*)` | Matching | 99.29% | 28 |
| `func_003579A8(void*)` | Matching | 99.29% | 28 |

### `object/multiparticle`

0 matching, 0 partial, 32 not started (32 total)

### `object/objnode`

2 matching, 0 partial, 9 not started (11 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003549D0(void*)` | Matching | 100.00% | 16 |
| `cObjNode_cObjNode(cObjNode*, void*)` | Matching | 99.94% | 64 |

### `object/railmodifier`

170 matching, 1 partial, 144 not started (315 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0035CFE0(void*)` | Matching | 100.00% | 8 |
| `func_0035CFE8(void*)` | Matching | 100.00% | 8 |
| `func_0035ED88(void*)` | Matching | 100.00% | 8 |
| `func_00360720(void*)` | Matching | 100.00% | 8 |
| `func_00360728(void*)` | Matching | 100.00% | 8 |
| `func_00360730(void*)` | Matching | 100.00% | 8 |
| `func_00360738(void*)` | Matching | 100.00% | 8 |
| `func_00360740(void*)` | Matching | 100.00% | 8 |
| `func_00360748(void*)` | Matching | 100.00% | 8 |
| `func_00360750(void*)` | Matching | 100.00% | 8 |
| `func_00360758(void*)` | Matching | 100.00% | 8 |
| `func_00360760(void*)` | Matching | 100.00% | 8 |
| `func_00360778(void*)` | Matching | 100.00% | 8 |
| `func_00360780(void*)` | Matching | 100.00% | 8 |
| `func_00360788(void*)` | Matching | 100.00% | 8 |
| `func_00360790(void*)` | Matching | 100.00% | 8 |
| `func_00360798(void*)` | Matching | 100.00% | 8 |
| `func_00360880(void*)` | Matching | 100.00% | 8 |
| `func_00360910(void*)` | Matching | 100.00% | 8 |
| `func_00360918(void*)` | Matching | 100.00% | 8 |
| `func_00360920(void*)` | Matching | 100.00% | 12 |
| `func_00360930(void*)` | Matching | 100.00% | 8 |
| `func_00360938(void*)` | Matching | 100.00% | 8 |
| `func_00360940(void*)` | Matching | 100.00% | 8 |
| `func_00360948(void*)` | Matching | 100.00% | 8 |
| `func_00360950(void*)` | Matching | 100.00% | 8 |
| `func_00360958(void*)` | Matching | 100.00% | 8 |
| `func_00360960(void*)` | Matching | 100.00% | 8 |
| `func_00360970(void*)` | Matching | 100.00% | 12 |
| `func_00360980(void*)` | Matching | 100.00% | 12 |
| `func_00360990(void*)` | Matching | 100.00% | 8 |
| `func_00360998(void*)` | Matching | 100.00% | 8 |
| `func_003609A0(void*)` | Matching | 100.00% | 8 |
| `func_003609A8(void*)` | Matching | 100.00% | 8 |
| `func_003609B0(void*)` | Matching | 100.00% | 12 |
| `func_003609C0(void*)` | Matching | 100.00% | 8 |
| `func_003609C8(void*)` | Matching | 100.00% | 8 |
| `func_003609D0(void*)` | Matching | 100.00% | 8 |
| `func_003609D8(void*)` | Matching | 100.00% | 8 |
| `func_003609E0(void*)` | Matching | 100.00% | 8 |
| `func_003609E8(void*)` | Matching | 100.00% | 8 |
| `func_003609F0(void*)` | Matching | 100.00% | 8 |
| `func_003609F8(void*)` | Matching | 100.00% | 8 |
| `func_00360A00(void*)` | Matching | 100.00% | 8 |
| `func_00360A08(void*)` | Matching | 100.00% | 8 |
| `func_00360A10(void*)` | Matching | 100.00% | 8 |
| `func_00360A18(void*)` | Matching | 100.00% | 8 |
| `func_00360A20(void*)` | Matching | 100.00% | 8 |
| `func_00360A50(void*)` | Matching | 100.00% | 8 |
| `func_00360A58(void*)` | Matching | 100.00% | 8 |
| `func_00360A60(void*)` | Matching | 100.00% | 8 |
| `func_00360A68(void*)` | Matching | 100.00% | 8 |
| `func_00360A98(void*)` | Matching | 100.00% | 8 |
| `func_00360AA0(void*)` | Matching | 100.00% | 8 |
| `func_00360AA8(void*)` | Matching | 100.00% | 8 |
| `func_00360AB0(void*)` | Matching | 100.00% | 8 |
| `func_00360AE0(void*)` | Matching | 100.00% | 8 |
| `func_00360AE8(void*)` | Matching | 100.00% | 8 |
| `func_00360AF0(void*)` | Matching | 100.00% | 8 |
| `func_00360AF8(void*)` | Matching | 100.00% | 8 |
| `func_00360B30(void*)` | Matching | 100.00% | 8 |
| `func_00360B38(void*)` | Matching | 100.00% | 8 |
| `func_00360B40(void*)` | Matching | 100.00% | 8 |
| `func_00360B48(void*)` | Matching | 100.00% | 8 |
| `func_00360B50(void*)` | Matching | 100.00% | 8 |
| `func_00360B58(void*)` | Matching | 100.00% | 8 |
| `func_00360B60(void*)` | Matching | 100.00% | 8 |
| `func_00360B68(void*)` | Matching | 100.00% | 8 |
| `func_00360B70(void*)` | Matching | 100.00% | 8 |
| `func_00360B78(void*)` | Matching | 100.00% | 8 |
| `func_00360B80(void*)` | Matching | 100.00% | 8 |
| `func_00360B88(void*)` | Matching | 100.00% | 8 |
| `func_00360B90(void*)` | Matching | 100.00% | 12 |
| `func_00360BA0(void*)` | Matching | 100.00% | 8 |
| `func_00360BA8(void*)` | Matching | 100.00% | 8 |
| `func_00360BB0(void*)` | Matching | 100.00% | 8 |
| `func_00360BB8(void*)` | Matching | 100.00% | 8 |
| `func_00360BC0(void*)` | Matching | 100.00% | 8 |
| `func_00360BC8(void*)` | Matching | 100.00% | 8 |
| `func_00360BD0(void*)` | Matching | 100.00% | 8 |
| `func_00360BD8(void*)` | Matching | 100.00% | 8 |
| `func_00360BE0(void*)` | Matching | 100.00% | 8 |
| `func_00360BE8(void*)` | Matching | 100.00% | 8 |
| `func_00360BF0(void*)` | Matching | 100.00% | 8 |
| `func_00360BF8(void*)` | Matching | 100.00% | 8 |
| `func_00360C00(void*)` | Matching | 100.00% | 8 |
| `func_00360C58(void*)` | Matching | 100.00% | 8 |
| `func_00360C60(void*)` | Matching | 100.00% | 8 |
| `func_00360C68(void*)` | Matching | 100.00% | 8 |
| `func_00360C70(void*)` | Matching | 100.00% | 8 |
| `func_00360C78(void*)` | Matching | 100.00% | 28 |
| `func_00360CE8(void*)` | Matching | 100.00% | 8 |
| `func_00360CF0(void*)` | Matching | 100.00% | 8 |
| `func_00360CF8(void*)` | Matching | 100.00% | 8 |
| `func_00360D00(void*)` | Matching | 100.00% | 8 |
| `func_00360D08(void*)` | Matching | 100.00% | 8 |
| `func_00360D10(void*)` | Matching | 100.00% | 8 |
| `func_00360D20(void*)` | Matching | 100.00% | 8 |
| `func_00360D28(void*)` | Matching | 100.00% | 8 |
| `func_00360D38(void*)` | Matching | 100.00% | 8 |
| `func_00360D90(void*)` | Matching | 100.00% | 8 |
| `func_00360DC8(void*)` | Matching | 100.00% | 8 |
| `func_00360DD0(void*)` | Matching | 100.00% | 8 |
| `func_00361060(void*)` | Matching | 100.00% | 8 |
| `func_00361080(void*)` | Matching | 100.00% | 12 |
| `func_00361090(void*)` | Matching | 100.00% | 8 |
| `func_00361150(void*)` | Matching | 100.00% | 8 |
| `func_00361198(void*)` | Matching | 100.00% | 8 |
| `func_00361458(void*)` | Matching | 100.00% | 8 |
| `func_003614B8(void*)` | Matching | 100.00% | 8 |
| `func_003614C0(void*)` | Matching | 100.00% | 8 |
| `func_003614C8(void*)` | Matching | 100.00% | 8 |
| `func_003614F8(void*)` | Matching | 100.00% | 8 |
| `func_00361528(void*)` | Matching | 100.00% | 8 |
| `func_00361558(void*)` | Matching | 100.00% | 8 |
| `func_00361560(void*)` | Matching | 100.00% | 8 |
| `func_00361568(void*)` | Matching | 100.00% | 8 |
| `func_00361570(void*)` | Matching | 100.00% | 8 |
| `func_00361578(void*)` | Matching | 100.00% | 8 |
| `func_00361580(void*)` | Matching | 100.00% | 8 |
| `func_00361588(void*)` | Matching | 100.00% | 8 |
| `func_00361590(void*)` | Matching | 100.00% | 8 |
| `func_00361598(void*)` | Matching | 100.00% | 8 |
| `func_003615A0(void*)` | Matching | 100.00% | 8 |
| `func_00361768(void*)` | Matching | 100.00% | 8 |
| `func_00361770(void*)` | Matching | 100.00% | 8 |
| `func_003617B0(void*)` | Matching | 100.00% | 8 |
| `func_003618F8(void*)` | Matching | 100.00% | 8 |
| `func_00361900(void*)` | Matching | 100.00% | 8 |
| `func_00361908(void*)` | Matching | 100.00% | 8 |
| `func_00361910(void*)` | Matching | 100.00% | 8 |
| `func_00361930(void*)` | Matching | 100.00% | 8 |
| `func_00361938(void*, float)` | Matching | 100.00% | 8 |
| `func_003619C8(void*)` | Matching | 100.00% | 8 |
| `func_003619D0(void*)` | Matching | 100.00% | 8 |
| `func_00361A10(void*)` | Matching | 100.00% | 12 |
| `func_00361A20(void*)` | Matching | 100.00% | 8 |
| `func_00361A28(void*)` | Matching | 100.00% | 8 |
| `func_00361A48(void*)` | Matching | 100.00% | 8 |
| `func_00361A50(void*)` | Matching | 100.00% | 8 |
| `func_00361A58(void*)` | Matching | 100.00% | 8 |
| `func_00361AD8(void*)` | Matching | 100.00% | 8 |
| `func_00361AF8(void*)` | Matching | 100.00% | 8 |
| `func_00361B00(void*, float)` | Matching | 100.00% | 8 |
| `func_00361B08(void*)` | Matching | 100.00% | 8 |
| `func_00361B10(void*)` | Matching | 100.00% | 8 |
| `func_00361B48(void*)` | Matching | 100.00% | 8 |
| `func_00361B50(void*)` | Matching | 100.00% | 8 |
| `func_00361B58(void*)` | Matching | 100.00% | 8 |
| `func_00361B78(void*)` | Matching | 100.00% | 8 |
| `func_00361B80(void*, float)` | Matching | 100.00% | 8 |
| `func_00361B88(void*)` | Matching | 100.00% | 8 |
| `func_00361BD8(void*)` | Matching | 100.00% | 8 |
| `func_00361BE0(void*)` | Matching | 100.00% | 12 |
| `func_00361C10(void*)` | Matching | 100.00% | 8 |
| `func_00361C18(void*, float)` | Matching | 100.00% | 8 |
| `func_00361C70(void*)` | Matching | 100.00% | 8 |
| `func_00361CA8(void*)` | Matching | 100.00% | 8 |
| `func_00361CF8(void*)` | Matching | 100.00% | 8 |
| `func_00361D18(void*)` | Matching | 100.00% | 8 |
| `func_00361D20(void*)` | Matching | 100.00% | 8 |
| `func_00361D28(void*, float)` | Matching | 100.00% | 8 |
| `func_00361D30(void*)` | Matching | 100.00% | 8 |
| `func_00361D38(void*)` | Matching | 100.00% | 8 |
| `func_00361D40(void*)` | Matching | 100.00% | 8 |
| `func_00361D88(void*)` | Matching | 100.00% | 8 |
| `func_00361E08(void*)` | Matching | 100.00% | 8 |
| `func_00361F90(void*)` | Matching | 100.00% | 8 |
| `func_00366FE0(void*, int)` | Matching | 100.00% | 8 |
| `func_00361F40(void*)` | Matching | 99.29% | 28 |
| `func_003619B8(void*)` | Partial | 63.33% | 12 |

### `object/spline3d`

0 matching, 1 partial, 3 not started (4 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cSpline_calcLength(cSpline*)` | Partial | 81.47% | 76 |

### `object/splinemodifier`

3 matching, 0 partial, 32 not started (35 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0035A5D8(void*)` | Matching | 100.00% | 28 |
| `func_0035AAD0(void*)` | Matching | 100.00% | 16 |
| `func_0035AAE0(void*)` | Matching | 100.00% | 16 |

### `object/spring`

0 matching, 0 partial, 4 not started (4 total)

### `path/pathsys`

2 matching, 0 partial, 14 not started (16 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026C410(void*)` | Matching | 100.00% | 8 |
| `func_0026C418(void*)` | Matching | 100.00% | 8 |

### `render/bezierman`

2 matching, 1 partial, 15 not started (18 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cBezierMan_construct()` | Matching | 100.00% | 52 |
| `func_0038D660(void*)` | Matching | 100.00% | 8 |
| `func_0038B178(void*)` | Partial | 99.20% | 20 |

### `render/font`

81 matching, 1 partial, 61 not started (143 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00392DE8(void*, int)` | Matching | 100.00% | 8 |
| `func_00393FA8(void*)` | Matching | 100.00% | 8 |
| `func_00393FB0(void*)` | Matching | 100.00% | 8 |
| `func_00394008(void*)` | Matching | 100.00% | 8 |
| `func_00394010(void*)` | Matching | 100.00% | 8 |
| `func_00394018(void*)` | Matching | 100.00% | 8 |
| `func_003942C0(void*)` | Matching | 100.00% | 8 |
| `func_003942C8(void*)` | Matching | 100.00% | 8 |
| `func_003942D0(void*)` | Matching | 100.00% | 8 |
| `func_003942D8(void*)` | Matching | 100.00% | 8 |
| `func_003942E0(void*)` | Matching | 100.00% | 8 |
| `func_003945B8(void*)` | Matching | 100.00% | 8 |
| `func_003945C0(void*)` | Matching | 100.00% | 8 |
| `func_003945C8(void*)` | Matching | 100.00% | 8 |
| `func_003945D0(void*)` | Matching | 100.00% | 8 |
| `func_003945D8(void*)` | Matching | 100.00% | 8 |
| `func_003945E0(void*)` | Matching | 100.00% | 8 |
| `func_003945E8(void*)` | Matching | 100.00% | 8 |
| `func_00394610(void*)` | Matching | 100.00% | 8 |
| `func_00394618(void*)` | Matching | 100.00% | 8 |
| `func_00394620(void*)` | Matching | 100.00% | 8 |
| `func_00394628(void*)` | Matching | 100.00% | 8 |
| `func_00394630(void*)` | Matching | 100.00% | 8 |
| `func_00394638(void*)` | Matching | 100.00% | 8 |
| `func_00394640(void*)` | Matching | 100.00% | 8 |
| `func_00394648(void*)` | Matching | 100.00% | 8 |
| `func_00394650(void*)` | Matching | 100.00% | 8 |
| `func_00394658(void*)` | Matching | 100.00% | 8 |
| `func_00394660(void*)` | Matching | 100.00% | 8 |
| `func_00394668(void*)` | Matching | 100.00% | 8 |
| `func_00394670(void*)` | Matching | 100.00% | 8 |
| `func_00394678(void*)` | Matching | 100.00% | 8 |
| `func_00394680(void*)` | Matching | 100.00% | 8 |
| `func_00394688(void*)` | Matching | 100.00% | 8 |
| `func_003946E8(void*)` | Matching | 100.00% | 8 |
| `func_00394B68(void*)` | Matching | 100.00% | 8 |
| `func_00394B78(void*)` | Matching | 100.00% | 8 |
| `func_00394B80(void*)` | Matching | 100.00% | 8 |
| `func_00394B88(void*, float)` | Matching | 100.00% | 8 |
| `func_00394B90(void*)` | Matching | 100.00% | 8 |
| `func_00394BC0(void*, float)` | Matching | 100.00% | 8 |
| `func_00394BC8(void*, float)` | Matching | 100.00% | 8 |
| `func_00394BD0(void*)` | Matching | 100.00% | 8 |
| `func_00394BD8(void*)` | Matching | 100.00% | 8 |
| `func_00394BE0(void*, int)` | Matching | 100.00% | 8 |
| `func_00394BE8(void*, int)` | Matching | 100.00% | 8 |
| `func_00394BF0(void*, int)` | Matching | 100.00% | 8 |
| `func_00394BF8(void*, int)` | Matching | 100.00% | 8 |
| `func_00394C00(void*)` | Matching | 100.00% | 8 |
| `func_00394C08(void*)` | Matching | 100.00% | 8 |
| `func_00394C10(void*)` | Matching | 100.00% | 8 |
| `func_00394C48(void*)` | Matching | 100.00% | 8 |
| `func_00394C50(void*)` | Matching | 100.00% | 8 |
| `func_00394C58(void*)` | Matching | 100.00% | 8 |
| `func_00394C60(void*)` | Matching | 100.00% | 8 |
| `func_00394C68(void*)` | Matching | 100.00% | 28 |
| `func_00394D10(void*)` | Matching | 100.00% | 8 |
| `func_00394D30(void*)` | Matching | 100.00% | 8 |
| `func_00394D38(void*)` | Matching | 100.00% | 8 |
| `func_00394D40(void*)` | Matching | 100.00% | 8 |
| `func_00394D48(void*)` | Matching | 100.00% | 8 |
| `func_00395268(void*)` | Matching | 100.00% | 28 |
| `func_00395318(void*)` | Matching | 100.00% | 8 |
| `func_00395320(void*)` | Matching | 100.00% | 8 |
| `func_00395328(void*)` | Matching | 100.00% | 8 |
| `func_003953B0(void*)` | Matching | 100.00% | 8 |
| `func_00395420(void*)` | Matching | 100.00% | 8 |
| `func_00395500(void*)` | Matching | 100.00% | 8 |
| `func_00395508(void*)` | Matching | 100.00% | 8 |
| `func_00395510(void*)` | Matching | 100.00% | 8 |
| `func_003956E0(void*, int)` | Matching | 100.00% | 8 |
| `func_00395C68(void*)` | Matching | 100.00% | 8 |
| `func_00395F60(void*)` | Matching | 100.00% | 28 |
| `func_00395F80(void*)` | Matching | 100.00% | 28 |
| `func_00395FA0(void*)` | Matching | 100.00% | 8 |
| `func_00396108(void*)` | Matching | 100.00% | 8 |
| `func_003968C8(void*)` | Matching | 100.00% | 8 |
| `func_00396918(void*)` | Matching | 100.00% | 8 |
| `func_00396920(void*)` | Matching | 100.00% | 8 |
| `func_00396958(void*)` | Matching | 100.00% | 8 |
| `func_00397138(void*, int)` | Matching | 100.00% | 8 |
| `func_00395730(void*)` | Partial | 84.12% | 32 |

### `render/graphicsman`

2 matching, 0 partial, 48 not started (50 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00369FF0(void*)` | Matching | 100.00% | 8 |
| `func_0036A1B0(void *, void *)` | Matching | 100.00% | 16 |

### `render/irradiance`

0 matching, 0 partial, 2 not started (2 total)

### `render/lightman`

7 matching, 0 partial, 37 not started (44 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cLightMan_construct()` | Matching | 100.00% | 80 |
| `func_0038DC50(void*)` | Matching | 100.00% | 8 |
| `func_0038DC58(void*)` | Matching | 100.00% | 8 |
| `func_0038DC60(void*)` | Matching | 100.00% | 8 |
| `func_0038DC68(void*)` | Matching | 100.00% | 8 |
| `func_0038F7F8(void*)` | Matching | 100.00% | 8 |
| `func_0038F800(void*)` | Matching | 100.00% | 28 |

### `render/particle`

3 matching, 2 partial, 183 not started (188 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00372500(void*)` | Matching | 100.00% | 28 |
| `func_00375A00(void*)` | Matching | 100.00% | 8 |
| `func_00382740(void*)` | Matching | 100.00% | 28 |
| `func_003758F8(void*)` | Partial | 99.71% | 28 |
| `func_003866E0(void*, int, int)` | Partial | 96.00% | 12 |

### `render/ps2bezierman`

0 matching, 1 partial, 1 not started (2 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cPSPBezierMan_cPSPBezierMan(void*)` | Partial | 88.42% | 76 |

### `render/ps2graphicsman`

2 matching, 0 partial, 30 not started (32 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003673D0(void*)` | Matching | 100.00% | 8 |
| `func_00369890(void*, int, int)` | Matching | 100.00% | 16 |

### `render/ps2lightman`

1 matching, 0 partial, 1 not started (2 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cPSPLightMan_cPSPLightMan(cPSPLightMan*)` | Matching | 99.83% | 24 |

### `replay/frameptr`

7 matching, 0 partial, 32 not started (39 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cReplayFramePtr_readRewind(cReplayFramePtr*)` | Matching | 100.00% | 12 |
| `func_0026E9C0(void*)` | Matching | 100.00% | 16 |
| `func_0026ED88(void*)` | Matching | 100.00% | 8 |
| `cReplayFramePtr_getFrameBlock()` | Matching | 100.00% | 8 |
| `func_0026F498(void*)` | Matching | 100.00% | 8 |
| `func_0026F4A0(void*, int)` | Matching | 100.00% | 8 |
| `func_0026F898(void*, int)` | Matching | 100.00% | 8 |

### `replay/playbackman`

1 matching, 1 partial, 34 not started (36 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026CBB0(void*)` | Matching | 100.00% | 8 |
| `func_0026D168(void*)` | Partial | 99.25% | 16 |

### `replay/replay`

2 matching, 1 partial, 19 not started (22 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026E5A8(void*)` | Matching | 100.00% | 20 |
| `func_0026E7F8(void*)` | Matching | 100.00% | 8 |
| `func_0026E5C0(void*)` | Partial | 99.25% | 16 |

### `replay/replaycache`

34 matching, 2 partial, 121 not started (157 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002705A8(void*)` | Matching | 100.00% | 8 |
| `func_00270ED8(void*)` | Matching | 100.00% | 28 |
| `func_00270EF8(void*)` | Matching | 100.00% | 28 |
| `func_00270F18(void*)` | Matching | 100.00% | 8 |
| `func_002716F0(void*)` | Matching | 100.00% | 24 |
| `func_002722E0(void *, void *, void *)` | Matching | 100.00% | 36 |
| `func_00274348(void*)` | Matching | 100.00% | 12 |
| `func_00274388(void*)` | Matching | 100.00% | 12 |
| `func_002743C8(void*)` | Matching | 100.00% | 12 |
| `func_00274808(void*, float)` | Matching | 100.00% | 8 |
| `func_002752F0(void*)` | Matching | 100.00% | 8 |
| `func_002752F8(void*)` | Matching | 100.00% | 8 |
| `func_00275300(void*)` | Matching | 100.00% | 8 |
| `func_00275308(void*)` | Matching | 100.00% | 8 |
| `func_00275310(void*)` | Matching | 100.00% | 8 |
| `func_00275318(void*)` | Matching | 100.00% | 12 |
| `func_00275328(void*)` | Matching | 100.00% | 8 |
| `func_00275330(void*)` | Matching | 100.00% | 8 |
| `func_00275338(void*)` | Matching | 100.00% | 8 |
| `func_00275340(void*)` | Matching | 100.00% | 8 |
| `func_00275348(void*)` | Matching | 100.00% | 12 |
| `func_00275358(void*)` | Matching | 100.00% | 8 |
| `func_00275360(void*)` | Matching | 100.00% | 8 |
| `func_00275368(void*)` | Matching | 100.00% | 8 |
| `func_00275370(void*)` | Matching | 100.00% | 8 |
| `func_00275378(void*)` | Matching | 100.00% | 12 |
| `func_00275388(void*)` | Matching | 100.00% | 8 |
| `func_00275390(void*)` | Matching | 100.00% | 8 |
| `func_00275398(void*)` | Matching | 100.00% | 8 |
| `func_002753A0(void*)` | Matching | 100.00% | 8 |
| `func_002753A8(void*)` | Matching | 100.00% | 12 |
| `cReplay_stopAutoReplay(void*)` | Matching | 99.69% | 64 |
| `func_002724C8(void*)` | Matching | 99.29% | 28 |
| `func_00272510(void*)` | Matching | 99.29% | 28 |
| `func_00272680(void*)` | Partial | 99.11% | 36 |
| `func_00274C10(void*, int)` | Partial | 78.33% | 12 |

### `sce/crt0`

0 matching, 0 partial, 4 not started (4 total)

### `scripter/bxscriptengine`

5 matching, 1 partial, 51 not started (57 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00282BE0(void *, void *)` | Matching | 100.00% | 12 |
| `func_00282DA8(void*, int)` | Matching | 100.00% | 8 |
| `func_00282F80(void*)` | Matching | 100.00% | 12 |
| `func_00283430(void*)` | Matching | 100.00% | 16 |
| `func_00283440(void*)` | Matching | 100.00% | 16 |
| `func_00282C88(void *, void *)` | Partial | 87.50% | 40 |

### `scripter/datamanager`

1 matching, 3 partial, 44 not started (48 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002772B8(void*)` | Matching | 100.00% | 8 |
| `func_00277F08(void*)` | Partial | 99.50% | 24 |
| `func_00275CF8(void*)` | Partial | 53.33% | 24 |
| `func_00275CD0(void *, void *)` | Partial | 0.00% | 36 |

### `scripter/scanimmgr`

0 matching, 0 partial, 8 not started (8 total)

### `scripter/scsndmgr`

0 matching, 0 partial, 11 not started (11 total)

### `scripter/ssxscriptengine`

17 matching, 4 partial, 144 not started (165 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00278710(void*)` | Matching | 100.00% | 8 |
| `func_00278718(void*)` | Matching | 100.00% | 8 |
| `func_00278DE8(void*, int)` | Matching | 100.00% | 8 |
| `func_0027A668(void*)` | Matching | 100.00% | 28 |
| `func_0027C070(void*)` | Matching | 100.00% | 8 |
| `func_0027C078(void*)` | Matching | 100.00% | 28 |
| `func_0027C098(void*)` | Matching | 100.00% | 8 |
| `func_0027C2A8(void*)` | Matching | 100.00% | 8 |
| `func_0027C4B8(void*)` | Matching | 100.00% | 8 |
| `func_0027C6A0(void*)` | Matching | 100.00% | 8 |
| `func_0027C888(void*)` | Matching | 100.00% | 8 |
| `func_0027C958(void*)` | Matching | 100.00% | 8 |
| `func_0027C960(void*)` | Matching | 100.00% | 28 |
| `func_0027D680(void*, int)` | Matching | 100.00% | 8 |
| `func_0027D788(void*, float)` | Matching | 100.00% | 8 |
| `func_00281160(void*, int)` | Matching | 100.00% | 8 |
| `func_00281168(void*)` | Matching | 100.00% | 8 |
| `func_00280548(void *, int, void *, void *)` | Partial | 68.00% | 20 |
| `func_00281000(void *, int, void *, void *)` | Partial | 68.00% | 20 |
| `func_0027BD78(void*)` | Partial | 53.33% | 24 |
| `func_0027BD90(void *, void *)` | Partial | 41.78% | 36 |

### `scripter/videngine`

1 matching, 1 partial, 13 not started (15 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00283C58(void*)` | Matching | 100.00% | 8 |
| `func_00283C20(void*)` | Partial | 99.25% | 16 |

### `sound/asyncsys`

1 matching, 1 partial, 18 not started (20 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0028B240(void*)` | Matching | 100.00% | 8 |
| `cAsyncSys_ASYNCSYS_Init(cAsyncSys*, unsigned int)` | Partial | 63.76% | 68 |

### `sound/bankmanager`

3 matching, 1 partial, 62 not started (66 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0028B928(void*)` | Matching | 100.00% | 8 |
| `func_0028C8C0(void*, int)` | Matching | 100.00% | 8 |
| `func_0028D898(void*)` | Matching | 100.00% | 8 |
| `func_0028DF08(void*)` | Partial | 63.33% | 12 |

### `sound/bankmonitor`

7 matching, 2 partial, 154 not started (163 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002AD848(void*)` | Matching | 100.00% | 20 |
| `func_002AD990(void*)` | Matching | 100.00% | 8 |
| `func_002AE000(void*)` | Matching | 100.00% | 28 |
| `func_002AF8E0(void*)` | Matching | 100.00% | 28 |
| `func_002B4060(void*)` | Matching | 100.00% | 8 |
| `func_002B4868(void*)` | Matching | 100.00% | 12 |
| `func_002B4AE8(void*)` | Matching | 100.00% | 8 |
| `func_002AD970(void*, int)` | Partial | 99.33% | 12 |
| `func_002AD980(void*)` | Partial | 63.33% | 12 |

### `sound/icepick/worldtriggermanager`

2 matching, 1 partial, 51 not started (54 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002B6628(void*)` | Matching | 100.00% | 8 |
| `WORLDTRIGGERMANAGER_Init()` | Matching | 99.88% | 64 |
| `func_002B6900(void*)` | Partial | 78.50% | 24 |

### `sound/ps2soundman`

0 matching, 0 partial, 3 not started (3 total)

### `sound/soundsys`

4 matching, 2 partial, 262 not started (268 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0029B960(void*)` | Matching | 100.00% | 8 |
| `func_0029C418(void*)` | Matching | 100.00% | 8 |
| `func_0029E560(void*)` | Matching | 100.00% | 8 |
| `func_002A1BD0(void*)` | Matching | 100.00% | 8 |
| `func_0029D6D0(void*)` | Partial | 63.33% | 12 |
| `func_002A78E0(void*)` | Partial | 47.00% | 20 |

### `sound/ssxAudio`

3 matching, 1 partial, 75 not started (79 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00289680(void*)` | Matching | 100.00% | 8 |
| `func_00289AF0(void*)` | Matching | 100.00% | 8 |
| `func_00289AF8(void*)` | Matching | 100.00% | 28 |
| `func_00289DE0(void*)` | Partial | 60.00% | 12 |

### `sound/streamsys`

1 matching, 2 partial, 56 not started (59 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002A9F30(void*, int)` | Matching | 100.00% | 8 |
| `func_002ABCE8(void*, int, int)` | Partial | 96.00% | 12 |
| `func_002ABD38(void*, int, int)` | Partial | 96.00% | 12 |

### `ui/uianimation`

1 matching, 0 partial, 8 not started (9 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00397298(void*, int)` | Matching | 100.00% | 8 |

### `ui/uiengine`

2 matching, 1 partial, 31 not started (34 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `UIAsciiToUnicode(unsigned short*, const char*)` | Matching | 100.00% | 48 |
| `func_00398618(void*)` | Matching | 100.00% | 28 |
| `func_00398A60(void *, void *)` | Partial | 58.00% | 20 |

### `ui/uilistbox`

0 matching, 0 partial, 15 not started (15 total)

### `ui/uimenu`

1 matching, 0 partial, 22 not started (23 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039BAB0(void*)` | Matching | 100.00% | 28 |

### `ui/uiscreen`

7 matching, 1 partial, 39 not started (47 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cUIThread_deleteThread(void*)` | Matching | 100.00% | 64 |
| `func_0039CD90(void*)` | Matching | 100.00% | 8 |
| `func_0039CD98(void*)` | Matching | 100.00% | 8 |
| `func_0039CE90(void*)` | Matching | 100.00% | 8 |
| `func_0039D948(void*)` | Matching | 100.00% | 28 |
| `func_0039E508(void*)` | Matching | 100.00% | 8 |
| `cUIScreen_jumpToFrame(void*, unsigned short)` | Matching | 99.75% | 80 |
| `cUIScreen_getFrameByLabel(cUIScreen*, int)` | Partial | 44.71% | 68 |

### `ui/uistate`

1 matching, 0 partial, 9 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039ECA8(void*)` | Matching | 100.00% | 8 |

### `ui/uistatestack`

1 matching, 0 partial, 21 not started (22 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039FF50(void*)` | Matching | 100.00% | 16 |

### `ui/uitext`

2 matching, 0 partial, 29 not started (31 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cUIText_setUnicodeStringByID(cUIText*, int)` | Matching | 100.00% | 48 |
| `cUIText_setAsciiString(cUIText*, const char*)` | Matching | 99.38% | 32 |

### `ui/uithing`

1 matching, 0 partial, 11 not started (12 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cUIThing_getKeyframerEvent(cUIThing*, int)` | Matching | 100.00% | 40 |

### `ui/uivector`

30 matching, 0 partial, 48 not started (78 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4BD8(void*)` | Matching | 100.00% | 8 |
| `func_003A4BE0(void*)` | Matching | 100.00% | 8 |
| `func_003A4BE8(void*)` | Matching | 100.00% | 8 |
| `func_003A4BF0(void*)` | Matching | 100.00% | 8 |
| `func_003A4EA8(void*)` | Matching | 100.00% | 8 |
| `func_003A50F8(void*)` | Matching | 100.00% | 8 |
| `func_003A5330(void*)` | Matching | 100.00% | 8 |
| `func_003A5500(void*)` | Matching | 100.00% | 8 |
| `func_003A56A0(void*)` | Matching | 100.00% | 8 |
| `func_003A5AA8(void*)` | Matching | 100.00% | 8 |
| `func_003A5AB0(void*)` | Matching | 100.00% | 8 |
| `func_003A5AB8(void*)` | Matching | 100.00% | 8 |
| `func_003A5AC0(void*)` | Matching | 100.00% | 8 |
| `func_003A5AC8(void*)` | Matching | 100.00% | 8 |
| `func_003A5AD0(void*)` | Matching | 100.00% | 8 |
| `func_003A5AD8(void*)` | Matching | 100.00% | 8 |
| `func_003A5B08(void*)` | Matching | 100.00% | 8 |
| `func_003A5B10(void*)` | Matching | 100.00% | 8 |
| `func_003A5B18(void*)` | Matching | 100.00% | 8 |
| `func_003A5B20(void*)` | Matching | 100.00% | 8 |
| `func_003A5B28(void*)` | Matching | 100.00% | 8 |
| `func_003A5B30(void*)` | Matching | 100.00% | 8 |
| `func_003A5B38(void*)` | Matching | 100.00% | 8 |
| `func_003A5B40(void*)` | Matching | 100.00% | 8 |
| `func_003A5DF0(void*)` | Matching | 100.00% | 8 |
| `func_003A6000(void*)` | Matching | 100.00% | 8 |
| `func_003A6168(void*)` | Matching | 100.00% | 8 |
| `func_003A6220(void*)` | Matching | 100.00% | 8 |
| `func_003A6330(void*)` | Matching | 100.00% | 8 |
| `func_003A6540(void*)` | Matching | 100.00% | 8 |

### `util/list`

4 matching, 1 partial, 9 not started (14 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cListNode_isSentinel(cListNode*)` | Matching | 100.00% | 36 |
| `cList_first(cList*)` | Matching | 100.00% | 20 |
| `cList_addToFront(cList*, cListNode*)` | Matching | 100.00% | 28 |
| `cList_addToEnd(cList*, cListNode*)` | Matching | 100.00% | 28 |
| `func_00397930(void*)` | Partial | 79.33% | 24 |

### `util/locale`

0 matching, 0 partial, 15 not started (15 total)

### `util/menu`

16 matching, 4 partial, 141 not started (161 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002CA368(void*)` | Matching | 100.00% | 8 |
| `func_002CA370(void*)` | Matching | 100.00% | 8 |
| `func_002CAD48(void*)` | Matching | 100.00% | 8 |
| `func_002CAD50(void*)` | Matching | 100.00% | 8 |
| `func_002CC0B8(void*, int)` | Matching | 100.00% | 8 |
| `func_002CC248(void*)` | Matching | 100.00% | 8 |
| `func_002CC250(void*)` | Matching | 100.00% | 8 |
| `func_002CC258(void*)` | Matching | 100.00% | 8 |
| `func_002CD2E8(void*)` | Matching | 100.00% | 8 |
| `func_002CD398(void*)` | Matching | 100.00% | 8 |
| `func_002CD3F0(void*)` | Matching | 100.00% | 8 |
| `func_002CFF80(void*)` | Matching | 100.00% | 8 |
| `func_002D0448(void*)` | Matching | 100.00% | 8 |
| `func_002D1CC0(void*)` | Matching | 100.00% | 28 |
| `cExpandMenuItem_addItem(void *, void *)` | Matching | 99.29% | 28 |
| `func_002D03D0(void*)` | Matching | 99.29% | 28 |
| `func_002CC070(void*)` | Partial | 98.40% | 40 |
| `cNullMenuItem_cNullMenuItem(cNullMenuItem*, void*)` | Partial | 89.33% | 72 |
| `cSpaceMenuItem_cSpaceMenuItem(cSpaceMenuItem*, void*)` | Partial | 89.33% | 72 |
| `cMenuItem_cMenuItem(cMenuItem*, void*)` | Partial | 53.56% | 36 |

### `util/objectinterface`

4 matching, 0 partial, 4 not started (8 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D1CF0(void*)` | Matching | 100.00% | 28 |
| `func_002D21B0(void*)` | Matching | 100.00% | 8 |
| `func_002D21B8(void*)` | Matching | 100.00% | 8 |
| `cObjectInterface_getInstanceMan()` | Matching | 99.75% | 16 |

### `util/statemachine`

0 matching, 0 partial, 4 not started (4 total)

### `visualfx/angerfx`

0 matching, 0 partial, 11 not started (11 total)

### `visualfx/avalanche`

0 matching, 0 partial, 33 not started (33 total)

### `visualfx/boardsparkfx`

0 matching, 0 partial, 5 not started (5 total)

### `visualfx/boardtrailfx`

0 matching, 1 partial, 28 not started (29 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002EADC0(void*)` | Partial | 99.33% | 12 |

### `visualfx/boardwakefx`

2 matching, 1 partial, 79 not started (82 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002E2860(void*)` | Matching | 100.00% | 8 |
| `func_002E3110(void*)` | Matching | 100.00% | 28 |
| `func_002E4F10(void*)` | Partial | 99.60% | 20 |

### `visualfx/crowdrender2d`

3 matching, 3 partial, 2 not started (8 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cCrowdRender2D_cCrowdRender2D(int)` | Matching | 100.00% | 40 |
| `cCrowdRender2D__cCrowdRender2D(int *, int)` | Matching | 100.00% | 68 |
| `cCrowdRender2D_constructCrowdAnim2D(void*)` | Matching | 99.71% | 68 |
| `cCrowdAnim2D_cCrowdAnim2D(void *, void *)` | Partial | 8.75% | 64 |
| `cCrowdRender2D_purge(int*)` | Partial | 2.37% | 236 |
| `cCrowdRender2D_init()` | Partial | 1.71% | 328 |

### `visualfx/lensfx`

2 matching, 0 partial, 47 not started (49 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002EC9D0(void*)` | Matching | 100.00% | 16 |
| `cLensFxMan_construct()` | Matching | 99.62% | 52 |

### `visualfx/renderstateman`

0 matching, 0 partial, 51 not started (51 total)

### `visualfx/worldlightman`

11 matching, 0 partial, 49 not started (60 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F64E8(void*)` | Matching | 100.00% | 8 |
| `func_002F6908(void*)` | Matching | 100.00% | 8 |
| `func_002F7A68(void*)` | Matching | 100.00% | 8 |
| `func_002F7C20(void*)` | Matching | 100.00% | 8 |
| `func_002F7C28(void*)` | Matching | 100.00% | 8 |
| `func_002F7C30(void*)` | Matching | 100.00% | 8 |
| `func_002F7FF0(void*)` | Matching | 100.00% | 8 |
| `func_002F8168(void*)` | Matching | 100.00% | 8 |
| `func_002F81B8(void*)` | Matching | 100.00% | 28 |
| `func_002F8FF8(void*)` | Matching | 100.00% | 8 |
| `func_002FA5F8(void*)` | Matching | 100.00% | 8 |

### `world/streamman`

0 matching, 0 partial, 11 not started (11 total)

### `world/world`

2 matching, 0 partial, 17 not started (19 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A6CC8(void *, void *)` | Matching | 100.00% | 16 |
| `func_003A6CD8(void *, void *)` | Matching | 100.00% | 16 |

### `world/worldcache`

2 matching, 2 partial, 46 not started (50 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A77B0(void*, int, int)` | Matching | 100.00% | 28 |
| `func_003A9180(void*)` | Matching | 100.00% | 8 |
| `func_003A7768(void*)` | Partial | 51.20% | 40 |
| `func_003A7790(void *, void *)` | Partial | 9.12% | 32 |

### `world/worldview`

4 matching, 0 partial, 41 not started (45 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cWorldView_getNumSections(cWorldView*)` | Matching | 100.00% | 28 |
| `cWorldView_isSectionLoaded(cWorldView*, int)` | Matching | 100.00% | 56 |
| `func_003A9AB0(void*)` | Matching | 100.00% | 12 |
| `func_003AAE60(void*)` | Matching | 100.00% | 8 |

### `world/wscriptcache`

8 matching, 0 partial, 108 not started (116 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003ACA50(void*)` | Matching | 100.00% | 28 |
| `func_003AD230(void*)` | Matching | 100.00% | 28 |
| `func_003ADC48(void*)` | Matching | 100.00% | 8 |
| `func_003B0720(void*)` | Matching | 100.00% | 20 |
| `func_003B0738(void*)` | Matching | 100.00% | 28 |
| `func_003B0FA0(void*)` | Matching | 100.00% | 8 |
| `func_003B11E8(void*)` | Matching | 100.00% | 8 |
| `func_003B2380(void*)` | Matching | 100.00% | 28 |

### `worldpainter/quadtree`

11 matching, 2 partial, 111 not started (124 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002C3FA0(void*)` | Matching | 100.00% | 8 |
| `func_002C4400(void*)` | Matching | 100.00% | 8 |
| `func_002C4408(void*, int)` | Matching | 100.00% | 8 |
| `func_002C5520(void*)` | Matching | 100.00% | 8 |
| `func_002C6700(void*)` | Matching | 100.00% | 8 |
| `func_002C6708(void*)` | Matching | 100.00% | 8 |
| `func_002C6710(void*)` | Matching | 100.00% | 8 |
| `func_002C6748(void*)` | Matching | 100.00% | 8 |
| `func_002C6750(void*)` | Matching | 100.00% | 8 |
| `func_002C67A8(void*)` | Matching | 100.00% | 8 |
| `func_002C67E0(void*)` | Matching | 100.00% | 8 |
| `func_002C4758(void*)` | Partial | 63.33% | 12 |
| `func_002C4890(void*)` | Partial | 63.33% | 12 |

### `worldpainter/worldpainterman`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cWorldPainterMan_reset(void*)` | Matching | 99.29% | 28 |

### `worldpainter/worldpaintermanquery`

65 matching, 1 partial, 4 not started (70 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cWorldPainterMan_getQuery(void*, cWorldPainterManArg*)` | Matching | 100.00% | 68 |
| `func_002C1458(void*)` | Matching | 100.00% | 8 |
| `func_002C1490(void*)` | Matching | 100.00% | 8 |
| `func_002C1498(void*)` | Matching | 100.00% | 8 |
| `func_002C14A0(void*)` | Matching | 100.00% | 8 |
| `func_002C14A8(void*)` | Matching | 100.00% | 8 |
| `func_002C14B0(void*)` | Matching | 100.00% | 8 |
| `func_002C14B8(void*)` | Matching | 100.00% | 8 |
| `func_002C14C0(void*)` | Matching | 100.00% | 8 |
| `func_002C14C8(void*)` | Matching | 100.00% | 8 |
| `func_002C14D0(void*)` | Matching | 100.00% | 8 |
| `func_002C14D8(void*)` | Matching | 100.00% | 8 |
| `func_002C14E0(void*)` | Matching | 100.00% | 8 |
| `func_002C14E8(void*)` | Matching | 100.00% | 8 |
| `func_002C14F0(void*)` | Matching | 100.00% | 8 |
| `func_002C14F8(void*)` | Matching | 100.00% | 8 |
| `func_002C1500(void*)` | Matching | 100.00% | 8 |
| `func_002C1508(void*)` | Matching | 100.00% | 8 |
| `func_002C1510(void*)` | Matching | 100.00% | 8 |
| `func_002C1518(void*)` | Matching | 100.00% | 8 |
| `func_002C1520(void*)` | Matching | 100.00% | 8 |
| `func_002C1528(void*)` | Matching | 100.00% | 8 |
| `func_002C1530(void*)` | Matching | 100.00% | 8 |
| `func_002C1538(void*)` | Matching | 100.00% | 8 |
| `func_002C1540(void*)` | Matching | 100.00% | 8 |
| `func_002C1548(void*)` | Matching | 100.00% | 8 |
| `func_002C1550(void*)` | Matching | 100.00% | 8 |
| `func_002C1558(void*)` | Matching | 100.00% | 8 |
| `func_002C1560(void*)` | Matching | 100.00% | 8 |
| `func_002C1568(void*)` | Matching | 100.00% | 8 |
| `func_002C1570(void*)` | Matching | 100.00% | 8 |
| `func_002C1578(void*)` | Matching | 100.00% | 8 |
| `func_002C1580(void*)` | Matching | 100.00% | 8 |
| `func_002C1588(void*)` | Matching | 100.00% | 8 |
| `func_002C1590(void*)` | Matching | 100.00% | 8 |
| `func_002C1598(void*)` | Matching | 100.00% | 8 |
| `func_002C15A0(void*)` | Matching | 100.00% | 8 |
| `func_002C15A8(void*)` | Matching | 100.00% | 8 |
| `func_002C15B0(void*)` | Matching | 100.00% | 8 |
| `func_002C15B8(void*)` | Matching | 100.00% | 8 |
| `func_002C15C0(void*)` | Matching | 100.00% | 8 |
| `func_002C15C8(void*)` | Matching | 100.00% | 8 |
| `func_002C15D0(void*)` | Matching | 100.00% | 8 |
| `func_002C15D8(void*)` | Matching | 100.00% | 8 |
| `func_002C15E0(void*)` | Matching | 100.00% | 8 |
| `func_002C15E8(void*)` | Matching | 100.00% | 8 |
| `func_002C15F0(void*)` | Matching | 100.00% | 8 |
| `func_002C15F8(void*)` | Matching | 100.00% | 8 |
| `func_002C1600(void*)` | Matching | 100.00% | 8 |
| `func_002C1608(void*)` | Matching | 100.00% | 8 |
| `func_002C1610(void*)` | Matching | 100.00% | 8 |
| `func_002C1618(void*)` | Matching | 100.00% | 8 |
| `func_002C1620(void*)` | Matching | 100.00% | 8 |
| `func_002C1628(void*)` | Matching | 100.00% | 8 |
| `func_002C1630(void*)` | Matching | 100.00% | 8 |
| `func_002C1638(void*)` | Matching | 100.00% | 8 |
| `func_002C1640(void*)` | Matching | 100.00% | 8 |
| `func_002C1648(void*)` | Matching | 100.00% | 8 |
| `func_002C1650(void*)` | Matching | 100.00% | 8 |
| `func_002C1658(void*)` | Matching | 100.00% | 8 |
| `func_002C1660(void*)` | Matching | 100.00% | 8 |
| `func_002C1668(void*)` | Matching | 100.00% | 8 |
| `func_002C1670(void*)` | Matching | 100.00% | 8 |
| `func_002C1678(void*)` | Matching | 100.00% | 8 |
| `func_002C1680(void*)` | Matching | 100.00% | 8 |
| `func_002C17C0(void*)` | Partial | 70.75% | 16 |

### `worldpainter/worldpainterquery`

0 matching, 0 partial, 1 not started (1 total)

### `worldpainter/worldpainterqueryctor`

0 matching, 0 partial, 4 not started (4 total)

### `wscript/wscriptcompile`

1 matching, 0 partial, 4 not started (5 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00351260(void *, void *)` | Matching | 100.00% | 16 |

### `wscript/wscriptman`

6 matching, 4 partial, 85 not started (95 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0030B058(void*)` | Matching | 100.00% | 12 |
| `func_0030B260(void *, void *)` | Matching | 100.00% | 16 |
| `func_0030B2C0(void *, void *)` | Matching | 100.00% | 16 |
| `func_0030B4B8(void*)` | Matching | 100.00% | 8 |
| `func_0030D3D8(void*)` | Matching | 100.00% | 8 |
| `func_0030D480(void*)` | Matching | 100.00% | 8 |
| `func_0030B4C0(void*, int, int)` | Partial | 75.40% | 20 |
| `func_0030B4D8(void*, int, int)` | Partial | 75.40% | 20 |
| `func_0030B4F0(void*, int, int)` | Partial | 75.40% | 20 |
| `func_0030B508(void *, int, void *)` | Partial | 70.50% | 24 |

### `wscript/wscriptmission`

0 matching, 0 partial, 2 not started (2 total)

### `wscript/wscriptprocess`

1 matching, 0 partial, 61 not started (62 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00308B58(void*)` | Matching | 100.00% | 28 |

