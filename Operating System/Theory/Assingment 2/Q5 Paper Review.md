# Paper Review

## Parallel Processing of E-Atheer Algorithm Using Pthread Paradigm

| Field | Details |
|-------|---------|
| **Journal** | Indonesian Journal of Electrical Engineering and Computer Science |
| **Volume / Issue** | Vol. 30, No. 3, June 2023 |
| **Pages** | pp. 1624–1633 |
| **ISSN** | 2502-4752 |
| **DOI** | [10.11591/ijeecs.v30.i3.pp1624-1633](https://doi.org/10.11591/ijeecs.v30.i3.pp1624-1633) |
| **Authors** | Atheer Akram AbdulRazzaq, Mohammed A. Fadhel, Laith Alzubaidi, Omran Al-Shamma |

---

## Overview

This paper tackles a genuine bottleneck in string matching: sequential execution times that don't scale well as databases grow. The authors' choice to parallelize the E-Atheer algorithm using POSIX threads is technically sound, and the five-step Pthread implementation they describe is clear enough to follow.

---

## Methodology

The experimental setup, however, has some real limitations worth naming. The Khawarizmi cluster they used tops out at 8 cores, which means the study says almost nothing about how the algorithm behaves beyond that threshold. That's a fairly narrow window for conclusions about scalability. The test was also run on a single hardware configuration, so it's hard to know how much the results reflect the algorithm versus the specific machine.

---

## Results and Analysis

The findings are a mixed bag. Parallel execution time beats sequential time across the board, which is expected. What's more interesting is the variation between database types:

- **Pitch** — performs well consistently across both short and long pattern lengths.
- **DNA** — drags behind on execution time but achieves the best speedup numbers (up to **7.19×** with 8 cores on short patterns). The authors attribute this to the small DNA alphabet forcing more hash collisions and repeated character checks — a reasonable explanation, though more analysis would have been welcome.
- **XML and Protein** — plateau early and drop off noticeably with long patterns. The paper doesn't dig deeply into why.

---

## Strengths

- Technically sound parallelization strategy using a well-established threading model
- Clear, reproducible five-step Pthread implementation
- Tested across four meaningfully different database types (DNA, Protein, XML, Pitch)
- Results are real and the methodology is replicable

---

## Weaknesses

- Hardware ceiling of 8 cores limits what can be said about scalability
- Single hardware configuration makes it difficult to isolate algorithm performance from machine-specific factors
- Writing is technically dense and occasionally repetitive
- Conclusion is thin — it restates results and gestures toward GPU/MPI work without much specificity

---

## Verdict

A solid contribution to a fairly niche area. The speedup gains are real and the database-type comparisons are genuinely informative. The work would benefit from broader hardware testing and deeper analysis of why certain database types underperform. Worth reading for anyone working in parallel string matching or multicore algorithm design.

---
