# Independent verification — OEIS A001419 (2026-11-15)

Repository input: archive of `iwasborninbali/oeis-A001419-unsubmitted` at `7e6717a`. The archive contains `README.md`, `CERTIFICATE.md`, and `PRIOR-ART.md`, but no `verification/` directory. No prior agent's proof or computational log was available. This audit is independent of the certificate. **Verdict: partial** (qualified below).

## Claim

> Madras's pattern theorem supplies a reference for the limiting assertion in A001419.

This is the entire assertion under `CERTIFICATE.md` / `Claim`. A001419 says that the number of *free* n-cell polyominoes having at least one hole, divided by the number of all free n-cell polyominoes (`A000105(n)`), tends to one. Its offset is 1. The certificate explicitly does **not** reprove Madras's theorem or independently enumerate OEIS terms.

## Source check

**Primary source opened:** Neal Madras, *A Pattern Theorem for Lattice Clusters*, arXiv:math/9902161v1 (1999), https://arxiv.org/pdf/math/9902161 ; journal version *Annals of Combinatorics* **3** (1999), 357–384, https://doi.org/10.1007/BF01608793 .

* **Printed p. 5 (PDF page index 4), Introduction:** Madras explicitly illustrates a pattern consisting of a square-lattice loop with the centre site absent and says the fraction of n-site **bond animals** having fewer than `epsilon*n` occurrences is at most `exp(-alpha*n)` for sufficiently large n. Short quotation: “the center site (and its four incident bonds) absent”. This is a motivating example, **not** yet a verbatim assertion about OEIS A001419.
* **Printed pp. 9–10 (PDF indices 8–9), §§2.3–2.4:** a *proper pattern* `(P1,P2)` requires finitely specified present and absent sites/bonds and occurrence in arbitrarily large clusters. **Theorem 2.1, printed p. 10, equation (16)** gives, for a suitable `epsilon > 0`, `limsup_{n→∞} (G_n[≤epsilon*n; P])^(1/n) < lambda`, assuming cluster axioms CA1, CA2, CA4. It is a strict growth-rate inequality for exceptional translation classes; the exponential-fraction interpretation also needs the known existence of the total growth constant (CA3).
* **Printed pp. 2, 14–16 (PDF indices 1, 13–15), §§1, 3.2–3.3:** the paper defines **site animals** as finite edge-connected occupied lattice sites with all induced nearest-neighbour bonds; §3.2(c) counts them by **number of sites**. **Proposition 3.1 (printed p. 15)** verifies CA4 for site animals on the square lattice; weights identically one satisfy CA2. Theorem 2.1 therefore applies to them, not just to the bond-animal example on p. 5.

**Application, supplied explicitly by this verifier:** Set `P1` to the four sites immediately N, E, S, W of `(0,0)` and `P2={(0,0)}`. A site animal containing the pattern has a missing central square, sealed off from infinity by its four occupied neighbours, hence a hole. The pattern is proper: the eight squares in a 3-by-3 ring around the missing centre can be extended by an arbitrarily long connected exterior tail. With translation-class counts `T_n` (all) and `B_n` (no holes), the pattern theorem gives `limsup B_n^(1/n) < lambda = lim T_n^(1/n)`; hence `B_n/T_n -> 0` exponentially. This also follows if one uses the full eight-site ring as `P1`.

**Convention transfer:** Madras counts up to **translations** and uses site count `n`. OEIS A001419 and A000105 count **free** objects (translations, rotations, reflections). Every free orbit has from 1 to 8 translation classes and holes are symmetry-invariant. Thus `B_n^free / T_n^free <= 8 * B_n^fixed / T_n^fixed -> 0`. OEIS A001419 starts at `n=1`; A000105 includes `n=0`. For `n>=1`, `A001419(n)=A000105(n)-A000104(n)`. No offset or hole convention mismatch is detected (holes are bounded complementary components of unions of **closed** occupied unit squares; this explains a first holey free 7-omino).

**Support assessment:** The cited paper **directly states the relevant general theorem and gives a missing-centre pattern example**, but **does not literally state** `A001419(n)/A000105(n)->1` or count free polyominoes. The inference above is required. The paper's proof was not independently audited, so this is verification of the source statement and of its applicability, not a reproof of its theorem.

**Better direct source located:** Érika B. Roldán Roa, *Topological, geometric and combinatorial properties of random polyominoes*, CIMAT doctoral thesis, May 2018, https://www.cimat.mx/~pabreu/TesisErikaRoldan.pdf , **Chapter 3, §3.2, Theorem 4 (printed p. 35), Corollaries 3 and 4 (printed p. 40; PDF index 51)**. Corollary 3 explicitly says “The number of polyominoes with holes grows exponentially faster than the number of polyominoes without holes”; Corollary 4 asserts that the probability of more than `epsilon*n` holes tends to 1. Chapter 2, §2.2.1, printed pp. 9–10, defines edge-connected unions of **closed** squares and distinguishes free/fixed equivalence; §3.3, printed p. 43, states the asymptotic construction using translation classes. This thesis is a *more direct*, though later, citation; it credits Madras's theorem and explains its specialized application. The change from fixed to free classes is bounded by factor 8.

## Independent computation

The Madras paper does not provide numeric A001419 terms, a numerical value of the limiting ratio, or explicit `epsilon/alpha/lambda` constants to reproduce. I instead checked finite OEIS terms independently; this **cannot establish the asymptotic limit**.

Program: `enumerate.cpp` (standalone C++17, no external libraries). Starting from one cell, add an edge-adjacent cell to each previously generated shape. Canonicalize each under all eight rotations/reflections plus translation, and deduplicate. Detect holes by flood-filling **unoccupied cells with four-neighbour moves** in a bounding rectangle with an exterior margin; an unreachable empty cell certifies a bounded complementary component of the union of closed squares. The OEIS integers used as controls are kept separate from generation and hole detection. Compile `g++ -O3 -std=c++17 -Wall -Wextra -pedantic enumerate.cpp -o enumerate`; run `./enumerate 14 > OUTPUT.log`.

**Range:** n = 1..14 inclusive, **all 14 sizes PASS** against A000105 (total) and A001419 (holey). At n=7: 108 total / 1 holey / 107 without holes. At n=14: **901,971 total / 96,496 holey / 805,475 without holes**. Exact per-size results are in `OUTPUT.log`. Instrumented program wall runtime: **10.1072 seconds** for this execution (external `time -p`: **10.18s real, 10.00s user, 0.15s sys**). Machine/compiler variations affect runtime only.

SHA-256 of local source: `b07b137168ae87ad3e8fc094faf1d4056a80dcb5cb6380d5d05d63dd5385b53f` (`enumerate.cpp`).

SHA-256 of local output: `c4df1cccd5b818d91110fbcdc65705ed3a7677e3ae90d7800786a6c40d0ca9d5` (`OUTPUT.log`, includes the runtime line). All data are UTF-8 with LF newlines.

## Entry check

Consulted OEIS https://oeis.org/A001419 , https://oeis.org/A001419/internal , https://oeis.org/A000105 and indexed public copies on **2026-11-15**. An indexed A001419 internal record labelled **revision #77, 2026-10-19** still says “Conjecture: Almost all polyominoes are holey” in `%C`, retains `%F a(n)=A000105(n)-A000104(n)`, and includes **no Madras** in `%D` or `%H`. Another openable, older cached internal copy showed **#72, 2026-05-30** with the same relevant lines and `%O 1,8`. These cache dates disagree because they are distinct snapshots. The direct OEIS normal-page and history endpoints returned HTTP 403 or were inaccessible; **the full edit history and live as-of-this-minute state could not be independently checked**. History-related dates visible in the entry are John Mason's conjecture, 2022-09-06, and the OEIS internal revision metadata. Do not mistake a cached snapshot for proof about changes after 2026-10-19.

**Already present elsewhere in OEIS:** https://oeis.org/A000105 (free polyominoes; offset 0) contains the *equivalent* `A000104(n)/A000105(n)->0` assertion and the explicit parenthetic correction **“This is true, a consequence of Madras's 1999 pattern theorem.” — Johann Peters, 2024-01-06**. A000105 also cites Madras's paper in its links and cross-references A001419. Therefore the source connection and the proof status are **not new to OEIS as a whole**, regardless of whether A001419 has a direct reference in its most recent inaccessible revision.

**Other prior art:** The 2018 Roldán Roa thesis states the holey assertion more directly; it is older than the 2024 OEIS A000105 note but newer than Madras. Neither novelty of the mathematical theorem nor priority of its application should be attributed to this repository. The modest candidate contribution is to fix the *outdated A001419 wording* and add/propagate references already known in related OEIS material.

## Verdict

**PARTIAL** under the requested conservative evidence rule, not a refutation of the mathematics. The source theorem is real, covers square-lattice site animals, and rigorously implies the asserted limit via a proper vacant-centre pattern and an at-most-eight symmetry factor. The independent finite enumeration confirms `n=1..14`. **But** (1) the exact limit is a derived consequence, not a verbatim Madras statement, (2) the attribution and equivalent correction are **already on A000105** (2024), (3) a more explicit thesis source exists (2018), and (4) OEIS's full history and freshest 2026-11-15 state could not be accessed, so absence from the actual current A001419 cannot be certified beyond the indexed 2026-10-19 snapshot. The certificate's unqualified `complete` verdict and novelty implication are too strong. **No submission or change to OEIS itself was made.**
