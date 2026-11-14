# Function matching report

Auto-generated from [objdiff](tools/objdiff) by diffing every unit's `obj/target` against `obj/current`. Regenerate with a dual build (`./configure.py -c -o && ninja`) followed by `python3 scripts/matching_report.py`; see [CONTRIBUTING.md](CONTRIBUTING.md).

Snapshot as of 2026-11-14.

**Status definitions:**
- **Matching** — byte-for-byte identical to the retail binary (100%), or a near-miss where objdiff's own report considers the function matched despite a lower raw percentage (this happens for a handful of functions where the only remaining byte difference is a relocation immediate baked in at link time by the original SN toolchain, not a real code difference — see the gp-relative note in [README.md](README.md)).
- **Partial** — has a C implementation (not raw `INCLUDE_ASM`) but doesn't yet byte-match; the percentage is objdiff's fuzzy match score.
- **Not started** — still a raw `INCLUDE_ASM` stub with no C implementation attempted.

| | Count | % of total |
|---|---|---|
| Matching | 471 | 0.90% |
| Partial | 9 | 0.02% |
| Not started | 51,653 | 99.08% |
| **Total** | **52,133** | |

(Total here may differ slightly from the function count in README.md's progress table — that one comes from objdiff's own aggregate report, this one from summing every unit's individual symbol list, and the two count a handful of duplicated/weak symbols differently.)

## Per-file summary

Only files with at least one Matching or Partial function are listed here; files that are 100% Not Started are omitted from this table (see the full per-file breakdown further down for every file, including those).

| File | Matching | Partial | Not started | Total |
|---|---|---|---|---|
| `visualfx/crowdrender2d` | 1 | 5 | 7 | 13 |
| `bxrandom` | 1 | 3 | 6 | 10 |
| `hashvalue` | 3 | 1 | 2 | 6 |
| `_Unknown/cExecutionMan_postpause` | 1 | 0 | 0 | 1 |
| `_Unknown/cExecutionMan_prepause` | 1 | 0 | 0 | 1 |
| `_Unknown/cGameAnimMap_testResolve` | 1 | 0 | 0 | 1 |
| `_Unknown/cReplayFramePtr_getFrameBlock` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113A98` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113CB8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113CE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113D10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113D28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113D30` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113E40` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113E48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113E70` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00113E78` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00116930` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00125AD0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0012A558` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0012E9B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00136978` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00136F28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00139A18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001406C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140708` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140710` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140718` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140720` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140728` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140730` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140C68` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140C70` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140C78` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00140C80` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00144068` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0014A078` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0014A180` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0014F100` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001547D8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001547E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001549E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00155380` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00155388` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00155AA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00155AA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015BB00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015BB08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015BB10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015BB18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015BCC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015BCC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015C6C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015C6D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015C6D8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015C6E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015C7D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015C7D8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0015FD48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00162560` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001635C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167E18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167E20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167E28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167E58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167E60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167E90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167FB8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00167FF8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00168000` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00168008` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00168010` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0016CA08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0016CA10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0016CF40` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001762A0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001762A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001762B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001762E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001762E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00176318` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001765F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00177E28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00179730` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00194980` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00195A98` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0019BFE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001A3300` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001A34A0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001A34A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001A7BB0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001A8768` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001A94D8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001D5F38` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001D93A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001D93C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001D93C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001D93D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001D9878` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DC930` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DC938` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DCCA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DD918` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDDD8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDDE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDDE8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDDF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDDF8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDE00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDE08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDE10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DDFA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE010` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE078` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE0E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE550` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE868` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE910` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE940` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DE948` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DF578` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DF5C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DFAC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001DFAC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0770` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0778` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E07B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E07B8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0948` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0BA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0C20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0C80` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0E88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E0EC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E1078` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E1080` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E1088` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E10E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E12A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E1450` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E1548` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E7920` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001E8FC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001F54A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_001F8720` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002087E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002212C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00221400` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00221D80` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002222A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002222B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002224B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00229F80` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00230E90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00232710` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00232718` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00233B88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00236AF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00237030` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00237948` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0023AC10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0023E2C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0023E4F0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002438E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002438E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243AB0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CB0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CB8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CD0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CD8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00243CE8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244230` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244238` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244528` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244538` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244540` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244550` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244558` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244620` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244628` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244860` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00244A38` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00245690` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002458B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00245B50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00245DB8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00251D00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00255668` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002557A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002557B8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00256250` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00259390` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0025FC20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002614E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00261A20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00267DC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0026ADA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0026C410` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0026C418` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0026ED88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0026F498` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002705A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00270F18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002847A8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002847B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002847B8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002847C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002847E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002847F0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284800` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284808` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284828` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284830` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284838` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284840` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284848` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284878` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00284880` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00289680` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00289AF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00291430` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00296308` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00296E18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00297430` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00297498` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0029B960` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0029C418` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0029E560` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0029E568` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0029E570` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002ADF58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002B4060` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA30` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA38` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA40` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA68` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA70` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA78` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA80` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002BDA90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002C1458` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002C2200` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002C2208` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002C3FA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002C5520` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002CA368` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002CA370` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002CAD50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002CD3F0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D2138` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D2140` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D21B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D21B8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D37C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D37C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D39E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002D39F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F0388` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F64E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F6908` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7A60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7AB0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7AD8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7B00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7B28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7B50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7B78` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7BA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7C20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7C28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7C30` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7EA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7EC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7EF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7EF8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7FC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F7FD0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F8168` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002F8FF8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_002FA5F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00303D88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0030B4B8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00316CC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00317FC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00319D08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00319D10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0031A260` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0031ABC0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0031FE28` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003200E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320518` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320520` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320528` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320530` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320538` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320540` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00320548` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00326A20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00327808` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0032B460` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00340A08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0034AF18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0035CFE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0035ED88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360720` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360728` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360730` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360738` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360778` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360780` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360788` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360790` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360938` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003609D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003609D8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003609F0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003609F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A68` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360A98` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AB0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AE8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360AF8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B30` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B38` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B40` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B70` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B78` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360B88` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360BA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360BD8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360BE8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360C00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360C58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360C60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360CF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360CF8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360D00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360D08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360D10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360D90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00360DC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003614C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003614C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003614F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00361578` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00361580` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00361588` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00361590` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003618F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00361A50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00361F90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003673D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00369FF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00375A00` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038D660` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038DC20` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038DC48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038DC50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038DC58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038DC60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038DC68` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0038F7F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00393FA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394008` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003942C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003942C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003942D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003942E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945B8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945D0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945D8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945E0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003945E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394610` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394618` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394620` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394628` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394630` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394638` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394640` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394648` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394650` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394658` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394660` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394668` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394670` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394680` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394688` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003946E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394B68` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394B78` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394B80` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394C48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394C50` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394C58` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394C60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394D30` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394D38` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394D40` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00394D48` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00395508` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00395FA0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00396190` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00396198` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003961A0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003968C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00396918` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00396920` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00396958` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0039CD90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0039CD98` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0039CE90` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0039E508` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0039ECA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A4BE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A4BE8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A4BF0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A4DD8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A4DE0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A4DE8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A5AA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A5AC8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A5AD0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A5B08` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A5B10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A5B18` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003A9180` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003AAE60` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003B11E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003B5470` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003C2438` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003C7AA8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003D16C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003D16E8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003D3010` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003DE4C8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003DE668` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003E5288` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003F5908` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003FB2F8` | 1 | 0 | 0 | 1 |
| `_Unknown/func_003FD908` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00410408` | 1 | 0 | 0 | 1 |
| `_Unknown/func_00410C10` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0042E0B0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0042E0C0` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0042E308` | 1 | 0 | 0 | 1 |
| `_Unknown/func_0042E318` | 1 | 0 | 0 | 1 |
| `dirtysock/tags` | 1 | 0 | 39 | 40 |

## Full per-file breakdown

Every unit, including ones with no progress yet. Matching and Partial functions are listed individually with their match percentage; Not Started functions are only counted (there's nothing to report per-function until an implementation is attempted).

### `1097F0`

0 matching, 0 partial, 239 not started (239 total)

### `1218`

0 matching, 0 partial, 335 not started (335 total)

### `1222C8`

0 matching, 0 partial, 3 not started (3 total)

### `122408`

0 matching, 0 partial, 29 not started (29 total)

### `122D88`

0 matching, 0 partial, 20 not started (20 total)

### `1232B8`

0 matching, 0 partial, 9 not started (9 total)

### `1234B8`

0 matching, 0 partial, 108 not started (108 total)

### `12AF88`

0 matching, 0 partial, 126 not started (126 total)

### `131E98`

0 matching, 0 partial, 95 not started (95 total)

### `133720`

0 matching, 0 partial, 35 not started (35 total)

### `134B90`

0 matching, 0 partial, 63 not started (63 total)

### `137AF8`

0 matching, 0 partial, 22 not started (22 total)

### `138038`

0 matching, 0 partial, 6 not started (6 total)

### `138950`

0 matching, 0 partial, 54 not started (54 total)

### `13BC18`

0 matching, 0 partial, 143 not started (143 total)

### `13F2C8`

0 matching, 0 partial, 5 not started (5 total)

### `13F4F8`

0 matching, 0 partial, 109 not started (109 total)

### `1448F0`

0 matching, 0 partial, 26 not started (26 total)

### `144AB8`

0 matching, 0 partial, 12 not started (12 total)

### `144CE0`

0 matching, 0 partial, 1 not started (1 total)

### `144CF0`

0 matching, 0 partial, 27 not started (27 total)

### `145240`

0 matching, 0 partial, 47 not started (47 total)

### `145530`

0 matching, 0 partial, 1 not started (1 total)

### `145548`

0 matching, 0 partial, 1 not started (1 total)

### `145560`

0 matching, 0 partial, 4 not started (4 total)

### `145630`

0 matching, 0 partial, 24 not started (24 total)

### `145868`

0 matching, 0 partial, 11 not started (11 total)

### `145A40`

0 matching, 0 partial, 17 not started (17 total)

### `146698`

0 matching, 0 partial, 3 not started (3 total)

### `1468B8`

0 matching, 0 partial, 4 not started (4 total)

### `146B58`

0 matching, 0 partial, 6 not started (6 total)

### `146DC0`

0 matching, 0 partial, 142 not started (142 total)

### `14AA0`

0 matching, 0 partial, 12 not started (12 total)

### `14CC0`

0 matching, 0 partial, 1 not started (1 total)

### `14CE8`

0 matching, 0 partial, 2 not started (2 total)

### `14D18`

0 matching, 0 partial, 1 not started (1 total)

### `14D38`

0 matching, 0 partial, 6 not started (6 total)

### `14E50`

0 matching, 0 partial, 1 not started (1 total)

### `14E80`

0 matching, 0 partial, 25 not started (25 total)

### `152D08`

0 matching, 0 partial, 69 not started (69 total)

### `156670`

0 matching, 0 partial, 7 not started (7 total)

### `1567B0`

0 matching, 0 partial, 1 not started (1 total)

### `1567C0`

0 matching, 0 partial, 37 not started (37 total)

### `157258`

0 matching, 0 partial, 119 not started (119 total)

### `15A398`

0 matching, 0 partial, 97 not started (97 total)

### `160C28`

0 matching, 0 partial, 17 not started (17 total)

### `1624E8`

0 matching, 0 partial, 6 not started (6 total)

### `162A28`

0 matching, 0 partial, 187 not started (187 total)

### `168DD0`

0 matching, 0 partial, 123 not started (123 total)

### `16BDA8`

0 matching, 0 partial, 28 not started (28 total)

### `16D420`

0 matching, 0 partial, 108 not started (108 total)

### `16FD98`

0 matching, 0 partial, 11 not started (11 total)

### `1704A0`

0 matching, 0 partial, 43 not started (43 total)

### `1715B0`

0 matching, 0 partial, 23 not started (23 total)

### `171F20`

0 matching, 0 partial, 572 not started (572 total)

### `17938`

0 matching, 0 partial, 226 not started (226 total)

### `1857C8`

0 matching, 0 partial, 3 not started (3 total)

### `1857F8`

0 matching, 0 partial, 1 not started (1 total)

### `185810`

0 matching, 0 partial, 3 not started (3 total)

### `185850`

0 matching, 0 partial, 4 not started (4 total)

### `185888`

0 matching, 0 partial, 127 not started (127 total)

### `18A688`

0 matching, 0 partial, 6 not started (6 total)

### `18AAF8`

0 matching, 0 partial, 141 not started (141 total)

### `192438`

0 matching, 0 partial, 66 not started (66 total)

### `197310`

0 matching, 0 partial, 2 not started (2 total)

### `197E20`

0 matching, 0 partial, 2 not started (2 total)

### `198438`

0 matching, 0 partial, 1 not started (1 total)

### `1984A0`

0 matching, 0 partial, 29 not started (29 total)

### `19C968`

0 matching, 0 partial, 3 not started (3 total)

### `19D420`

0 matching, 0 partial, 22 not started (22 total)

### `19F578`

0 matching, 0 partial, 386 not started (386 total)

### `1AEF60`

0 matching, 0 partial, 139 not started (139 total)

### `1B5068`

0 matching, 0 partial, 330 not started (330 total)

### `1BEA98`

0 matching, 0 partial, 81 not started (81 total)

### `1C2460`

0 matching, 0 partial, 78 not started (78 total)

### `1C3210`

0 matching, 0 partial, 38 not started (38 total)

### `1C4FA8`

0 matching, 0 partial, 78 not started (78 total)

### `1C6528`

0 matching, 0 partial, 136 not started (136 total)

### `1CB378`

0 matching, 0 partial, 21 not started (21 total)

### `1CBD58`

0 matching, 0 partial, 83 not started (83 total)

### `1CE3F8`

0 matching, 0 partial, 100 not started (100 total)

### `1D3148`

0 matching, 0 partial, 5 not started (5 total)

### `1D31C0`

0 matching, 0 partial, 23 not started (23 total)

### `1D47D0`

0 matching, 0 partial, 17 not started (17 total)

### `1D49E8`

0 matching, 0 partial, 2 not started (2 total)

### `1D4A00`

0 matching, 0 partial, 128 not started (128 total)

### `1DCD10`

0 matching, 0 partial, 224 not started (224 total)

### `1F1390`

0 matching, 0 partial, 84 not started (84 total)

### `1F74F0`

0 matching, 0 partial, 2 not started (2 total)

### `1F7910`

0 matching, 0 partial, 9 not started (9 total)

### `1F8A68`

0 matching, 0 partial, 3 not started (3 total)

### `1F8AB8`

0 matching, 0 partial, 1 not started (1 total)

### `1F8AE0`

0 matching, 0 partial, 1 not started (1 total)

### `1F8B08`

0 matching, 0 partial, 1 not started (1 total)

### `1F8B30`

0 matching, 0 partial, 1 not started (1 total)

### `1F8B58`

0 matching, 0 partial, 1 not started (1 total)

### `1F8B80`

0 matching, 0 partial, 1 not started (1 total)

### `1F8BA8`

0 matching, 0 partial, 6 not started (6 total)

### `1F8C38`

0 matching, 0 partial, 36 not started (36 total)

### `1F8EA8`

0 matching, 0 partial, 1 not started (1 total)

### `1F8ED0`

0 matching, 0 partial, 1 not started (1 total)

### `1F8F00`

0 matching, 0 partial, 5 not started (5 total)

### `1F8FD8`

0 matching, 0 partial, 11 not started (11 total)

### `1F9170`

0 matching, 0 partial, 16 not started (16 total)

### `1FA000`

0 matching, 0 partial, 4 not started (4 total)

### `1FB600`

0 matching, 0 partial, 129 not started (129 total)

### `204D90`

0 matching, 0 partial, 219 not started (219 total)

### `20C4C0`

0 matching, 0 partial, 246 not started (246 total)

### `2160B8`

0 matching, 0 partial, 28 not started (28 total)

### `217CD0`

0 matching, 0 partial, 18 not started (18 total)

### `218AE8`

0 matching, 0 partial, 16 not started (16 total)

### `218FC8`

0 matching, 0 partial, 1 not started (1 total)

### `21A1C0`

0 matching, 0 partial, 28 not started (28 total)

### `21AD18`

0 matching, 0 partial, 8 not started (8 total)

### `21B268`

0 matching, 0 partial, 13 not started (13 total)

### `21BBC8`

0 matching, 0 partial, 26 not started (26 total)

### `21E5A8`

0 matching, 0 partial, 32 not started (32 total)

### `220E30`

0 matching, 0 partial, 16 not started (16 total)

### `2210E8`

0 matching, 0 partial, 21 not started (21 total)

### `221550`

0 matching, 0 partial, 2 not started (2 total)

### `221960`

0 matching, 0 partial, 202 not started (202 total)

### `227A28`

0 matching, 0 partial, 27 not started (27 total)

### `228810`

0 matching, 0 partial, 39 not started (39 total)

### `22C468`

0 matching, 0 partial, 103 not started (103 total)

### `241A10`

0 matching, 0 partial, 164 not started (164 total)

### `24BF20`

0 matching, 0 partial, 361 not started (361 total)

### `25DFE8`

0 matching, 0 partial, 15 not started (15 total)

### `25FD90`

0 matching, 0 partial, 19 not started (19 total)

### `261740`

0 matching, 0 partial, 6 not started (6 total)

### `261798`

0 matching, 0 partial, 22 not started (22 total)

### `261940`

0 matching, 0 partial, 15 not started (15 total)

### `2619E0`

0 matching, 0 partial, 2 not started (2 total)

### `261A10`

0 matching, 0 partial, 4 not started (4 total)

### `261A70`

0 matching, 0 partial, 1 not started (1 total)

### `261AB8`

0 matching, 0 partial, 1 not started (1 total)

### `261B00`

0 matching, 0 partial, 1 not started (1 total)

### `261B50`

0 matching, 0 partial, 1 not started (1 total)

### `261B60`

0 matching, 0 partial, 2 not started (2 total)

### `261B80`

0 matching, 0 partial, 1 not started (1 total)

### `261B90`

0 matching, 0 partial, 1 not started (1 total)

### `261BA8`

0 matching, 0 partial, 6 not started (6 total)

### `261BE0`

0 matching, 0 partial, 1 not started (1 total)

### `261BF0`

0 matching, 0 partial, 2 not started (2 total)

### `261C08`

0 matching, 0 partial, 2 not started (2 total)

### `261C68`

0 matching, 0 partial, 5 not started (5 total)

### `261D18`

0 matching, 0 partial, 6 not started (6 total)

### `261D98`

0 matching, 0 partial, 2 not started (2 total)

### `261DD0`

0 matching, 0 partial, 45 not started (45 total)

### `2624D0`

0 matching, 0 partial, 1 not started (1 total)

### `262500`

0 matching, 0 partial, 7 not started (7 total)

### `262598`

0 matching, 0 partial, 15 not started (15 total)

### `262900`

0 matching, 0 partial, 18 not started (18 total)

### `262A58`

0 matching, 0 partial, 51 not started (51 total)

### `262F98`

0 matching, 0 partial, 92 not started (92 total)

### `2683D8`

0 matching, 0 partial, 74 not started (74 total)

### `26AD8`

0 matching, 0 partial, 55 not started (55 total)

### `26AFF8`

0 matching, 0 partial, 124 not started (124 total)

### `276A08`

0 matching, 0 partial, 208 not started (208 total)

### `28E668`

0 matching, 0 partial, 4 not started (4 total)

### `28EC28`

0 matching, 0 partial, 1 not started (1 total)

### `28EC70`

0 matching, 0 partial, 42 not started (42 total)

### `290800`

0 matching, 0 partial, 60 not started (60 total)

### `294FB0`

0 matching, 0 partial, 4 not started (4 total)

### `295010`

0 matching, 0 partial, 45 not started (45 total)

### `2952D8`

0 matching, 0 partial, 1 not started (1 total)

### `2952E8`

0 matching, 0 partial, 16 not started (16 total)

### `2955F0`

0 matching, 0 partial, 2 not started (2 total)

### `295678`

0 matching, 0 partial, 1 not started (1 total)

### `295690`

0 matching, 0 partial, 8 not started (8 total)

### `2956F0`

0 matching, 0 partial, 17 not started (17 total)

### `295B70`

0 matching, 0 partial, 1 not started (1 total)

### `295B88`

0 matching, 0 partial, 18 not started (18 total)

### `295C68`

0 matching, 0 partial, 6 not started (6 total)

### `295D50`

0 matching, 0 partial, 23 not started (23 total)

### `296510`

0 matching, 0 partial, 34 not started (34 total)

### `296FA8`

0 matching, 0 partial, 8 not started (8 total)

### `2971A8`

0 matching, 0 partial, 87 not started (87 total)

### `2978D0`

0 matching, 0 partial, 2 not started (2 total)

### `297928`

0 matching, 0 partial, 1 not started (1 total)

### `297960`

0 matching, 0 partial, 218 not started (218 total)

### `29DDA0`

0 matching, 0 partial, 3 not started (3 total)

### `29DE98`

0 matching, 0 partial, 36 not started (36 total)

### `29F510`

0 matching, 0 partial, 13 not started (13 total)

### `29FCB0`

0 matching, 0 partial, 198 not started (198 total)

### `2A5BF8`

0 matching, 0 partial, 14 not started (14 total)

### `2A5DF0`

0 matching, 0 partial, 103 not started (103 total)

### `2A6AB0`

0 matching, 0 partial, 3 not started (3 total)

### `2A6AD8`

0 matching, 0 partial, 6 not started (6 total)

### `2A6B20`

0 matching, 0 partial, 177 not started (177 total)

### `2AA188`

0 matching, 0 partial, 61 not started (61 total)

### `2ABE68`

0 matching, 0 partial, 181 not started (181 total)

### `2B21F0`

0 matching, 0 partial, 107 not started (107 total)

### `2B560`

0 matching, 0 partial, 150 not started (150 total)

### `2B6478`

0 matching, 0 partial, 190 not started (190 total)

### `2C3440`

0 matching, 0 partial, 138 not started (138 total)

### `2C8AB0`

0 matching, 0 partial, 224 not started (224 total)

### `2D26D0`

0 matching, 0 partial, 2 not started (2 total)

### `2D26F0`

0 matching, 0 partial, 20 not started (20 total)

### `2D4018`

0 matching, 0 partial, 242 not started (242 total)

### `2DF4D0`

0 matching, 0 partial, 1 not started (1 total)

### `2DF670`

0 matching, 0 partial, 172 not started (172 total)

### `2E6290`

0 matching, 0 partial, 109 not started (109 total)

### `2EEF50`

0 matching, 0 partial, 133 not started (133 total)

### `2F6910`

0 matching, 0 partial, 220 not started (220 total)

### `2F9B8`

0 matching, 0 partial, 85 not started (85 total)

### `2FC300`

0 matching, 0 partial, 77 not started (77 total)

### `2FE910`

0 matching, 0 partial, 377 not started (377 total)

### `311410`

0 matching, 0 partial, 16 not started (16 total)

### `311C18`

0 matching, 0 partial, 798 not started (798 total)

### `32F0B8`

0 matching, 0 partial, 1 not started (1 total)

### `32F0C8`

0 matching, 0 partial, 12 not started (12 total)

### `32F310`

0 matching, 0 partial, 1 not started (1 total)

### `32F320`

0 matching, 0 partial, 11 not started (11 total)

### `37980`

0 matching, 0 partial, 7 not started (7 total)

### `37F30`

0 matching, 0 partial, 19 not started (19 total)

### `3AA20`

0 matching, 0 partial, 37 not started (37 total)

### `416D0`

0 matching, 0 partial, 5 not started (5 total)

### `41738`

0 matching, 0 partial, 74 not started (74 total)

### `41C88`

0 matching, 0 partial, 54 not started (54 total)

### `45070`

0 matching, 0 partial, 237 not started (237 total)

### `4B080`

0 matching, 0 partial, 4 not started (4 total)

### `4B188`

0 matching, 0 partial, 129 not started (129 total)

### `50108`

0 matching, 0 partial, 188 not started (188 total)

### `557E8`

0 matching, 0 partial, 4 not started (4 total)

### `559E8`

0 matching, 0 partial, 13 not started (13 total)

### `56390`

0 matching, 0 partial, 17 not started (17 total)

### `56AB0`

0 matching, 0 partial, 237 not started (237 total)

### `5CB20`

0 matching, 0 partial, 21 not started (21 total)

### `5CCD0`

0 matching, 0 partial, 76 not started (76 total)

### `5D6E8`

0 matching, 0 partial, 8 not started (8 total)

### `5D7E0`

0 matching, 0 partial, 113 not started (113 total)

### `60D50`

0 matching, 0 partial, 61 not started (61 total)

### `63568`

0 matching, 0 partial, 11 not started (11 total)

### `645C8`

0 matching, 0 partial, 32 not started (32 total)

### `68E30`

0 matching, 0 partial, 2 not started (2 total)

### `68E68`

0 matching, 0 partial, 1 not started (1 total)

### `68E98`

0 matching, 0 partial, 13 not started (13 total)

### `68FC0`

0 matching, 0 partial, 7 not started (7 total)

### `69018`

0 matching, 0 partial, 123 not started (123 total)

### `6DA18`

0 matching, 0 partial, 8 not started (8 total)

### `6DF48`

0 matching, 0 partial, 119 not started (119 total)

### `772B8`

0 matching, 0 partial, 2 not started (2 total)

### `772F0`

0 matching, 0 partial, 1 not started (1 total)

### `77320`

0 matching, 0 partial, 18 not started (18 total)

### `77600`

0 matching, 0 partial, 37 not started (37 total)

### `78E30`

0 matching, 0 partial, 25 not started (25 total)

### `7A738`

0 matching, 0 partial, 540 not started (540 total)

### `95988`

0 matching, 0 partial, 30 not started (30 total)

### `96AA0`

0 matching, 0 partial, 104 not started (104 total)

### `9CFE8`

0 matching, 0 partial, 228 not started (228 total)

### `A4308`

0 matching, 0 partial, 2 not started (2 total)

### `A44B0`

0 matching, 0 partial, 88 not started (88 total)

### `A8BB8`

0 matching, 0 partial, 12 not started (12 total)

### `A9770`

0 matching, 0 partial, 32 not started (32 total)

### `AA4E0`

0 matching, 0 partial, 1037 not started (1037 total)

### `D6F40`

0 matching, 0 partial, 65 not started (65 total)

### `DA3B0`

0 matching, 0 partial, 1 not started (1 total)

### `DA3D8`

0 matching, 0 partial, 5 not started (5 total)

### `DA880`

0 matching, 0 partial, 53 not started (53 total)

### `DD940`

0 matching, 0 partial, 26 not started (26 total)

### `DDCB0`

0 matching, 0 partial, 49 not started (49 total)

### `DE920`

0 matching, 0 partial, 75 not started (75 total)

### `DEE18`

0 matching, 0 partial, 8 not started (8 total)

### `DEFB0`

0 matching, 0 partial, 2 not started (2 total)

### `DF018`

0 matching, 0 partial, 2 not started (2 total)

### `DF080`

0 matching, 0 partial, 2 not started (2 total)

### `DF0F0`

0 matching, 0 partial, 39 not started (39 total)

### `DF558`

0 matching, 0 partial, 14 not started (14 total)

### `DF870`

0 matching, 0 partial, 8 not started (8 total)

### `DF918`

0 matching, 0 partial, 1 not started (1 total)

### `DF950`

0 matching, 0 partial, 26 not started (26 total)

### `E0580`

0 matching, 0 partial, 1 not started (1 total)

### `E05C8`

0 matching, 0 partial, 39 not started (39 total)

### `E0AD0`

0 matching, 0 partial, 87 not started (87 total)

### `E1780`

0 matching, 0 partial, 1 not started (1 total)

### `E17C0`

0 matching, 0 partial, 9 not started (9 total)

### `E1950`

0 matching, 0 partial, 9 not started (9 total)

### `E1BA8`

0 matching, 0 partial, 4 not started (4 total)

### `E1C28`

0 matching, 0 partial, 3 not started (3 total)

### `E1C88`

0 matching, 0 partial, 13 not started (13 total)

### `E1E90`

0 matching, 0 partial, 2 not started (2 total)

### `E1EC8`

0 matching, 0 partial, 11 not started (11 total)

### `E2090`

0 matching, 0 partial, 2 not started (2 total)

### `E20F0`

0 matching, 0 partial, 47 not started (47 total)

### `E22B0`

0 matching, 0 partial, 3 not started (3 total)

### `E2458`

0 matching, 0 partial, 2 not started (2 total)

### `E2550`

0 matching, 0 partial, 143 not started (143 total)

### `E8928`

0 matching, 0 partial, 21 not started (21 total)

### `E9FC8`

0 matching, 0 partial, 112 not started (112 total)

### `F64B0`

0 matching, 0 partial, 46 not started (46 total)

### `F9728`

0 matching, 0 partial, 165 not started (165 total)

### `_Unknown/cExecutionMan_postpause`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cExecutionMan_postpause()` | Matching | 100.00% | 8 |

### `_Unknown/cExecutionMan_prepause`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cExecutionMan_prepause()` | Matching | 100.00% | 8 |

### `_Unknown/cGameAnimMap_testResolve`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cGameAnimMap_testResolve()` | Matching | 100.00% | 8 |

### `_Unknown/cReplayFramePtr_getFrameBlock`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cReplayFramePtr_getFrameBlock()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113A98`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113A98()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113CB8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113CB8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113CE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113CE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113D10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113D10()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113D28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113D28()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113D30`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113D30()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113E40`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113E40()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113E48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113E48()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113E70`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113E70()` | Matching | 100.00% | 8 |

### `_Unknown/func_00113E78`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00113E78()` | Matching | 100.00% | 8 |

### `_Unknown/func_00116930`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00116930()` | Matching | 100.00% | 8 |

### `_Unknown/func_00125AD0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00125AD0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0012A558`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0012A558()` | Matching | 100.00% | 8 |

### `_Unknown/func_0012E9B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0012E9B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00136978`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00136978()` | Matching | 100.00% | 8 |

### `_Unknown/func_00136F28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00136F28()` | Matching | 100.00% | 8 |

### `_Unknown/func_00139A18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00139A18()` | Matching | 100.00% | 8 |

### `_Unknown/func_001406C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001406C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140708`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140708()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140710`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140710()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140718`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140718()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140720`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140720()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140728`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140728()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140730`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140730()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140C68`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140C68()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140C70`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140C70()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140C78`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140C78()` | Matching | 100.00% | 8 |

### `_Unknown/func_00140C80`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00140C80()` | Matching | 100.00% | 8 |

### `_Unknown/func_00144068`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00144068()` | Matching | 100.00% | 8 |

### `_Unknown/func_0014A078`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0014A078()` | Matching | 100.00% | 8 |

### `_Unknown/func_0014A180`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0014A180()` | Matching | 100.00% | 8 |

### `_Unknown/func_0014F100`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0014F100()` | Matching | 100.00% | 8 |

### `_Unknown/func_001547D8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001547D8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001547E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001547E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001549E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001549E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00155380`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00155380()` | Matching | 100.00% | 8 |

### `_Unknown/func_00155388`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00155388()` | Matching | 100.00% | 8 |

### `_Unknown/func_00155AA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00155AA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00155AA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00155AA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015BB00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BB00()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015BB08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BB08()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015BB10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BB10()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015BB18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BB18()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015BCC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BCC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015BCC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015BCC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015C6C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015C6C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015C6D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015C6D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015C6D8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015C6D8()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015C6E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015C6E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015C7D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015C7D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015C7D8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015C7D8()` | Matching | 100.00% | 8 |

### `_Unknown/func_0015FD48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0015FD48()` | Matching | 100.00% | 8 |

### `_Unknown/func_00162560`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00162560()` | Matching | 100.00% | 8 |

### `_Unknown/func_001635C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001635C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167E18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167E18()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167E20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167E20()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167E28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167E28()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167E58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167E58()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167E60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167E60()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167E90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167E90()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167FB8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167FB8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00167FF8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00167FF8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00168000`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00168000()` | Matching | 100.00% | 8 |

### `_Unknown/func_00168008`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00168008()` | Matching | 100.00% | 8 |

### `_Unknown/func_00168010`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00168010()` | Matching | 100.00% | 8 |

### `_Unknown/func_0016CA08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0016CA08()` | Matching | 100.00% | 8 |

### `_Unknown/func_0016CA10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0016CA10()` | Matching | 100.00% | 8 |

### `_Unknown/func_0016CF40`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0016CF40()` | Matching | 100.00% | 8 |

### `_Unknown/func_001762A0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001762A0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001762A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001762A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001762B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001762B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001762E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001762E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001762E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001762E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00176318`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00176318()` | Matching | 100.00% | 8 |

### `_Unknown/func_001765F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001765F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00177E28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00177E28()` | Matching | 100.00% | 8 |

### `_Unknown/func_00179730`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00179730()` | Matching | 100.00% | 8 |

### `_Unknown/func_00194980`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00194980()` | Matching | 100.00% | 8 |

### `_Unknown/func_00195A98`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00195A98()` | Matching | 100.00% | 8 |

### `_Unknown/func_0019BFE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0019BFE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001A3300`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A3300()` | Matching | 100.00% | 8 |

### `_Unknown/func_001A34A0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A34A0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001A34A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A34A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001A7BB0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A7BB0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001A8768`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A8768()` | Matching | 100.00% | 8 |

### `_Unknown/func_001A94D8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001A94D8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001D5F38`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D5F38()` | Matching | 100.00% | 8 |

### `_Unknown/func_001D93A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D93A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001D93C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D93C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001D93C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D93C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001D93D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D93D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001D9878`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001D9878()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DC930`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DC930()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DC938`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DC938()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DCCA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DCCA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DD918`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DD918()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDDD8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDDD8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDDE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDDE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDDE8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDDE8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDDF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDDF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDDF8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDDF8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDE00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDE00()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDE08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDE08()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDE10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDE10()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DDFA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DDFA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE010`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE010()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE078`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE078()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE0E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE0E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE550`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE550()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE868`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE868()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE910`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE910()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE940`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE940()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DE948`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DE948()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DF578`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DF578()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DF5C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DF5C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DFAC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DFAC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001DFAC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001DFAC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0770`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0770()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0778`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0778()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E07B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E07B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E07B8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E07B8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0948`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0948()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0BA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0BA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0C20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0C20()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0C80`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0C80()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0E88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0E88()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E0EC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E0EC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E1078`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E1078()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E1080`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E1080()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E1088`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E1088()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E10E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E10E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E12A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E12A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E1450`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E1450()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E1548`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E1548()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E7920`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E7920()` | Matching | 100.00% | 8 |

### `_Unknown/func_001E8FC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001E8FC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_001F54A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001F54A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_001F8720`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_001F8720()` | Matching | 100.00% | 8 |

### `_Unknown/func_002087E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002087E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002212C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002212C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00221400`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00221400()` | Matching | 100.00% | 8 |

### `_Unknown/func_00221D80`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00221D80()` | Matching | 100.00% | 8 |

### `_Unknown/func_002222A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002222A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002222B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002222B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002224B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002224B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00229F80`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00229F80()` | Matching | 100.00% | 8 |

### `_Unknown/func_00230E90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00230E90()` | Matching | 100.00% | 8 |

### `_Unknown/func_00232710`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00232710()` | Matching | 100.00% | 8 |

### `_Unknown/func_00232718`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00232718()` | Matching | 100.00% | 8 |

### `_Unknown/func_00233B88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00233B88()` | Matching | 100.00% | 8 |

### `_Unknown/func_00236AF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00236AF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00237030`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00237030()` | Matching | 100.00% | 8 |

### `_Unknown/func_00237948`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00237948()` | Matching | 100.00% | 8 |

### `_Unknown/func_0023AC10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0023AC10()` | Matching | 100.00% | 8 |

### `_Unknown/func_0023E2C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0023E2C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0023E4F0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0023E4F0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002438E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002438E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002438E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002438E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243AB0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243AB0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CB0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CB0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CB8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CB8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CD0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CD0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CD8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CD8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00243CE8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00243CE8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244230`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244230()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244238`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244238()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244528`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244528()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244538`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244538()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244540`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244540()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244550`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244550()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244558`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244558()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244620`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244620()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244628`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244628()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244860`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244860()` | Matching | 100.00% | 8 |

### `_Unknown/func_00244A38`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00244A38()` | Matching | 100.00% | 8 |

### `_Unknown/func_00245690`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00245690()` | Matching | 100.00% | 8 |

### `_Unknown/func_002458B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002458B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00245B50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00245B50()` | Matching | 100.00% | 8 |

### `_Unknown/func_00245DB8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00245DB8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00251D00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00251D00()` | Matching | 100.00% | 8 |

### `_Unknown/func_00255668`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00255668()` | Matching | 100.00% | 8 |

### `_Unknown/func_002557A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002557A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002557B8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002557B8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00256250`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00256250()` | Matching | 100.00% | 8 |

### `_Unknown/func_00259390`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00259390()` | Matching | 100.00% | 8 |

### `_Unknown/func_0025FC20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0025FC20()` | Matching | 100.00% | 8 |

### `_Unknown/func_002614E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002614E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00261A20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00261A20()` | Matching | 100.00% | 8 |

### `_Unknown/func_00267DC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00267DC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_0026ADA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026ADA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0026C410`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026C410()` | Matching | 100.00% | 8 |

### `_Unknown/func_0026C418`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026C418()` | Matching | 100.00% | 8 |

### `_Unknown/func_0026ED88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026ED88()` | Matching | 100.00% | 8 |

### `_Unknown/func_0026F498`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0026F498()` | Matching | 100.00% | 8 |

### `_Unknown/func_002705A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002705A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00270F18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00270F18()` | Matching | 100.00% | 8 |

### `_Unknown/func_002847A8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002847A8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002847B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002847B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002847B8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002847B8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002847C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002847C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002847E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002847E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002847F0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002847F0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284800`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284800()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284808`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284808()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284828`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284828()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284830`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284830()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284838`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284838()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284840`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284840()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284848`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284848()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284878`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284878()` | Matching | 100.00% | 8 |

### `_Unknown/func_00284880`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00284880()` | Matching | 100.00% | 8 |

### `_Unknown/func_00289680`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00289680()` | Matching | 100.00% | 8 |

### `_Unknown/func_00289AF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00289AF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00291430`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00291430()` | Matching | 100.00% | 8 |

### `_Unknown/func_00296308`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00296308()` | Matching | 100.00% | 8 |

### `_Unknown/func_00296E18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00296E18()` | Matching | 100.00% | 8 |

### `_Unknown/func_00297430`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00297430()` | Matching | 100.00% | 8 |

### `_Unknown/func_00297498`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00297498()` | Matching | 100.00% | 8 |

### `_Unknown/func_0029B960`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0029B960()` | Matching | 100.00% | 8 |

### `_Unknown/func_0029C418`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0029C418()` | Matching | 100.00% | 8 |

### `_Unknown/func_0029E560`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0029E560()` | Matching | 100.00% | 8 |

### `_Unknown/func_0029E568`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0029E568()` | Matching | 100.00% | 8 |

### `_Unknown/func_0029E570`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0029E570()` | Matching | 100.00% | 8 |

### `_Unknown/func_002ADF58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002ADF58()` | Matching | 100.00% | 8 |

### `_Unknown/func_002B4060`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002B4060()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA28()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA30`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA30()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA38`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA38()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA40`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA40()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA48()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA50()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA58()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA60()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA68`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA68()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA70`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA70()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA78`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA78()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA80`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA80()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA88()` | Matching | 100.00% | 8 |

### `_Unknown/func_002BDA90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002BDA90()` | Matching | 100.00% | 8 |

### `_Unknown/func_002C1458`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002C1458()` | Matching | 100.00% | 8 |

### `_Unknown/func_002C2200`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002C2200()` | Matching | 100.00% | 8 |

### `_Unknown/func_002C2208`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002C2208()` | Matching | 100.00% | 8 |

### `_Unknown/func_002C3FA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002C3FA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002C5520`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002C5520()` | Matching | 100.00% | 8 |

### `_Unknown/func_002CA368`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002CA368()` | Matching | 100.00% | 8 |

### `_Unknown/func_002CA370`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002CA370()` | Matching | 100.00% | 8 |

### `_Unknown/func_002CAD50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002CAD50()` | Matching | 100.00% | 8 |

### `_Unknown/func_002CD3F0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002CD3F0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D2138`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D2138()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D2140`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D2140()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D21B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D21B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D21B8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D21B8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D37C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D37C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D37C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D37C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D39E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D39E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002D39F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002D39F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F0388`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F0388()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F64E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F64E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F6908`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F6908()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7A60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7A60()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7AB0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7AB0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7AD8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7AD8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7B00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7B00()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7B28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7B28()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7B50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7B50()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7B78`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7B78()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7BA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7BA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7C20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7C20()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7C28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7C28()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7C30`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7C30()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7EA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7EA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7EC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7EC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7EF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7EF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7EF8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7EF8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7FC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7FC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F7FD0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F7FD0()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F8168`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F8168()` | Matching | 100.00% | 8 |

### `_Unknown/func_002F8FF8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002F8FF8()` | Matching | 100.00% | 8 |

### `_Unknown/func_002FA5F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_002FA5F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00303D88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00303D88()` | Matching | 100.00% | 8 |

### `_Unknown/func_0030B4B8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0030B4B8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00316CC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00316CC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00317FC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00317FC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00319D08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00319D08()` | Matching | 100.00% | 8 |

### `_Unknown/func_00319D10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00319D10()` | Matching | 100.00% | 8 |

### `_Unknown/func_0031A260`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0031A260()` | Matching | 100.00% | 8 |

### `_Unknown/func_0031ABC0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0031ABC0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0031FE28`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0031FE28()` | Matching | 100.00% | 8 |

### `_Unknown/func_003200E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003200E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320518`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320518()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320520`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320520()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320528`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320528()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320530`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320530()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320538`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320538()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320540`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320540()` | Matching | 100.00% | 8 |

### `_Unknown/func_00320548`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00320548()` | Matching | 100.00% | 8 |

### `_Unknown/func_00326A20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00326A20()` | Matching | 100.00% | 8 |

### `_Unknown/func_00327808`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00327808()` | Matching | 100.00% | 8 |

### `_Unknown/func_0032B460`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0032B460()` | Matching | 100.00% | 8 |

### `_Unknown/func_00340A08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00340A08()` | Matching | 100.00% | 8 |

### `_Unknown/func_0034AF18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0034AF18()` | Matching | 100.00% | 8 |

### `_Unknown/func_0035CFE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0035CFE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0035ED88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0035ED88()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360720`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360720()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360728`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360728()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360730`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360730()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360738`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360738()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360778`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360778()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360780`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360780()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360788`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360788()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360790`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360790()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360938`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360938()` | Matching | 100.00% | 8 |

### `_Unknown/func_003609D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003609D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003609D8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003609D8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003609F0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003609F0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003609F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003609F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A00()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A08()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A50()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A58()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A60()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A68`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A68()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360A98`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360A98()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AB0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AB0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AE8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AE8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360AF8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360AF8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B30`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B30()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B38`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B38()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B40`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B40()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B48()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B58()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B70`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B70()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B78`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B78()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360B88`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360B88()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360BA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360BA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360BD8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360BD8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360BE8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360BE8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360C00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360C00()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360C58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360C58()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360C60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360C60()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360CF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360CF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360CF8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360CF8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360D00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360D00()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360D08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360D08()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360D10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360D10()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360D90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360D90()` | Matching | 100.00% | 8 |

### `_Unknown/func_00360DC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00360DC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003614C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003614C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003614C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003614C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003614F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003614F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00361578`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00361578()` | Matching | 100.00% | 8 |

### `_Unknown/func_00361580`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00361580()` | Matching | 100.00% | 8 |

### `_Unknown/func_00361588`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00361588()` | Matching | 100.00% | 8 |

### `_Unknown/func_00361590`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00361590()` | Matching | 100.00% | 8 |

### `_Unknown/func_003618F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003618F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00361A50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00361A50()` | Matching | 100.00% | 8 |

### `_Unknown/func_00361F90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00361F90()` | Matching | 100.00% | 8 |

### `_Unknown/func_003673D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003673D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00369FF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00369FF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00375A00`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00375A00()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038D660`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038D660()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038DC20`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038DC20()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038DC48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038DC48()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038DC50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038DC50()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038DC58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038DC58()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038DC60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038DC60()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038DC68`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038DC68()` | Matching | 100.00% | 8 |

### `_Unknown/func_0038F7F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0038F7F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00393FA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00393FA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394008`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394008()` | Matching | 100.00% | 8 |

### `_Unknown/func_003942C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003942C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003942C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003942C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003942D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003942D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003942E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003942E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945B8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945B8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945D0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945D0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945D8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945D8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945E0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945E0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003945E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003945E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394610`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394610()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394618`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394618()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394620`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394620()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394628`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394628()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394630`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394630()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394638`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394638()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394640`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394640()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394648`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394648()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394650`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394650()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394658`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394658()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394660`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394660()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394668`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394668()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394670`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394670()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394680`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394680()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394688`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394688()` | Matching | 100.00% | 8 |

### `_Unknown/func_003946E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003946E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394B68`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394B68()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394B78`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394B78()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394B80`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394B80()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394C48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394C48()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394C50`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394C50()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394C58`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394C58()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394C60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394C60()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394D30`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394D30()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394D38`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394D38()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394D40`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394D40()` | Matching | 100.00% | 8 |

### `_Unknown/func_00394D48`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00394D48()` | Matching | 100.00% | 8 |

### `_Unknown/func_00395508`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00395508()` | Matching | 100.00% | 8 |

### `_Unknown/func_00395FA0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00395FA0()` | Matching | 100.00% | 8 |

### `_Unknown/func_00396190`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00396190()` | Matching | 100.00% | 8 |

### `_Unknown/func_00396198`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00396198()` | Matching | 100.00% | 8 |

### `_Unknown/func_003961A0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003961A0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003968C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003968C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_00396918`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00396918()` | Matching | 100.00% | 8 |

### `_Unknown/func_00396920`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00396920()` | Matching | 100.00% | 8 |

### `_Unknown/func_00396958`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00396958()` | Matching | 100.00% | 8 |

### `_Unknown/func_0039CD90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039CD90()` | Matching | 100.00% | 8 |

### `_Unknown/func_0039CD98`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039CD98()` | Matching | 100.00% | 8 |

### `_Unknown/func_0039CE90`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039CE90()` | Matching | 100.00% | 8 |

### `_Unknown/func_0039E508`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039E508()` | Matching | 100.00% | 8 |

### `_Unknown/func_0039ECA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0039ECA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A4BE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4BE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A4BE8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4BE8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A4BF0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4BF0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A4DD8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4DD8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A4DE0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4DE0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A4DE8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A4DE8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A5AA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A5AA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A5AC8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A5AC8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A5AD0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A5AD0()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A5B08`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A5B08()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A5B10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A5B10()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A5B18`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A5B18()` | Matching | 100.00% | 8 |

### `_Unknown/func_003A9180`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003A9180()` | Matching | 100.00% | 8 |

### `_Unknown/func_003AAE60`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003AAE60()` | Matching | 100.00% | 8 |

### `_Unknown/func_003B11E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003B11E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003B5470`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003B5470()` | Matching | 100.00% | 8 |

### `_Unknown/func_003C2438`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003C2438()` | Matching | 100.00% | 8 |

### `_Unknown/func_003C7AA8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003C7AA8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003D16C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003D16C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003D16E8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003D16E8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003D3010`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003D3010()` | Matching | 100.00% | 8 |

### `_Unknown/func_003DE4C8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003DE4C8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003DE668`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003DE668()` | Matching | 100.00% | 8 |

### `_Unknown/func_003E5288`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003E5288()` | Matching | 100.00% | 8 |

### `_Unknown/func_003F5908`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003F5908()` | Matching | 100.00% | 8 |

### `_Unknown/func_003FB2F8`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003FB2F8()` | Matching | 100.00% | 8 |

### `_Unknown/func_003FD908`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_003FD908()` | Matching | 100.00% | 8 |

### `_Unknown/func_00410408`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00410408()` | Matching | 100.00% | 8 |

### `_Unknown/func_00410C10`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_00410C10()` | Matching | 100.00% | 8 |

### `_Unknown/func_0042E0B0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0042E0B0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0042E0C0`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0042E0C0()` | Matching | 100.00% | 8 |

### `_Unknown/func_0042E308`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0042E308()` | Matching | 100.00% | 8 |

### `_Unknown/func_0042E318`

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `func_0042E318()` | Matching | 100.00% | 8 |

### `bx/bxstring`

0 matching, 0 partial, 44 not started (44 total)

### `bxrandom`

1 matching, 3 partial, 6 not started (10 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `BXrand()` | Matching | 99.38% | 32 |
| `AIrandf(float, float)` | Partial | 98.92% | 96 |
| `func_00317890(float, float)` | Partial | 95.00% | 80 |
| `BXsrand(unsigned int)` | Partial | 89.50% | 40 |

### `data/33DE00.data`

0 matching, 0 partial, 688 not started (688 total)

### `data/357900.rodata`

0 matching, 0 partial, 6604 not started (6604 total)

### `data/39C100.lit4`

0 matching, 0 partial, 26486 not started (26486 total)

### `data/vutext`

0 matching, 0 partial, 1 not started (1 total)

### `dirtysock/tags`

1 matching, 0 partial, 39 not started (40 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cDirtysock_tag__TagFieldSetupAppend(char *, char *, char *)` | Matching | 100.00% | 72 |

### `hashvalue`

3 matching, 1 partial, 2 not started (6 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `tHashName32_getHashValue(unsigned int*, char*)` | Matching | 100.00% | 88 |
| `GetHashValue32(char*)` | Matching | 100.00% | 32 |
| `GetHashValue64(char*)` | Matching | 100.00% | 32 |
| `tHashName64_getHashValue(unsigned long*, char*)` | Partial | 20.50% | 96 |

### `md5`

0 matching, 0 partial, 4 not started (4 total)

### `sce/crt0`

0 matching, 0 partial, 4 not started (4 total)

### `visualfx/crowdrender2d`

1 matching, 5 partial, 7 not started (13 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `cCrowdRender2D_cCrowdRender2D(int)` | Matching | 100.00% | 40 |
| `cCrowdRender2D__cCrowdRender2D(int *, int)` | Partial | 94.44% | 72 |
| `cCrowdRender2D_constructCrowdAnim2D(void*)` | Partial | 94.17% | 72 |
| `cCrowdAnim2D_cCrowdAnim2D(void *, void *)` | Partial | 8.75% | 64 |
| `cCrowdRender2D_purge(int*)` | Partial | 2.33% | 240 |
| `cCrowdRender2D_init()` | Partial | 1.71% | 328 |

