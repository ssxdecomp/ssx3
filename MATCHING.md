# Function matching report

Auto-generated from [objdiff](tools/objdiff) by diffing every unit's `obj/target` against `obj/current`. Regenerate with a dual build (`./configure.py -c -o && ninja`) followed by `python3 scripts/matching_report.py`; see [CONTRIBUTING.md](CONTRIBUTING.md).

Snapshot as of 2026-10-01.

**Status definitions:**
- **Matching** — byte-for-byte identical to the retail binary (100%), or a near-miss where objdiff's own report considers the function matched despite a lower raw percentage (this happens for a handful of functions where the only remaining byte difference is a relocation immediate baked in at link time by the original SN toolchain, not a real code difference — see the gp-relative note in [README.md](README.md)).
- **Partial** — has a C implementation (not raw `INCLUDE_ASM`) but doesn't yet byte-match; the percentage is objdiff's fuzzy match score.
- **Not started** — still a raw `INCLUDE_ASM` stub with no C implementation attempted.

| | Count | % of total |
|---|---|---|
| Matching | 7 | 0.01% |
| Partial | 9 | 0.02% |
| Not started | 52,117 | 99.97% |
| **Total** | **52,133** | |

(Total here may differ slightly from the function count in README.md's progress table — that one comes from objdiff's own aggregate report, this one from summing every unit's individual symbol list, and the two count a handful of duplicated/weak symbols differently.)

## Per-file summary

Only files with at least one Matching or Partial function are listed here; files that are 100% Not Started are omitted from this table (see the full per-file breakdown further down for every file, including those).

| File | Matching | Partial | Not started | Total |
|---|---|---|---|---|
| `visualfx/crowdrender2d` | 1 | 5 | 7 | 13 |
| `bxrandom` | 1 | 3 | 6 | 10 |
| `hashvalue` | 3 | 1 | 2 | 6 |
| `data/vutext` | 1 | 0 | 0 | 1 |
| `dirtysock/tags` | 1 | 0 | 39 | 40 |

## Full per-file breakdown

Every unit, including ones with no progress yet. Matching and Partial functions are listed individually with their match percentage; Not Started functions are only counted (there's nothing to report per-function until an implementation is attempted).

### `1218`

0 matching, 0 partial, 10925 not started (10925 total)

### `1DCD10`

0 matching, 0 partial, 1075 not started (1075 total)

### `218AE8`

0 matching, 0 partial, 18 not started (18 total)

### `21A1C0`

0 matching, 0 partial, 79 not started (79 total)

### `21E5A8`

0 matching, 0 partial, 4481 not started (4481 total)

### `2EEF50`

0 matching, 0 partial, 1655 not started (1655 total)

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

1 matching, 0 partial, 0 not started (1 total)

| Function | Status | Match % | Size |
|---|---|---|---|
| `D_0042E590` | Matching | 100.00% | 59348 |

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
| `cCrowdRender2D__cCrowdRender2D(int *, int)` | Partial | 94.17% | 72 |
| `cCrowdRender2D_constructCrowdAnim2D(void*)` | Partial | 94.17% | 72 |
| `cCrowdAnim2D_cCrowdAnim2D(void *, void *)` | Partial | 8.75% | 64 |
| `cCrowdRender2D_purge(int*)` | Partial | 2.33% | 240 |
| `cCrowdRender2D_init()` | Partial | 1.71% | 328 |

