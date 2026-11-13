# OEIS A001419: reference for holey polyominoes (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted** (lab registry, 14 Nov 2026).

- [A001419](https://oeis.org/A001419), Madras, Ann. Comb. 3 (1999): **candidate** (2026-11-13: repository built (core c6)). Certificate: complete.

Rules and the full registry: [athanor-oeis](https://github.com/iwasborninbali/athanor-oeis/blob/main/REGISTRY.md).
<!-- oeis-status:end -->

## Definition

For n≥1, a(n) counts free n-cell polyominoes with at least one hole, up to translations, rotations and reflections. A polyomino is a finite edge-connected union of unit squares; a hole is a bounded component of its complement. The offset is 1.

## Terms / result

The live [A001419](https://oeis.org/A001419), read 2026-11-13, states: `Conjecture: Almost all polyominoes are holey. In other words, a(n)/A000105(n) tends to 1 for increasing n.` The block is attributed to John Mason, Sep 06 2022. No term changes; the result is a missing reference for this conjecture.

## How it was obtained

Neal Madras, *A pattern theorem for lattice clusters*, Annals of Combinatorics 3 (1999), 357–384, [doi:10.1007/BF01608793](https://doi.org/10.1007/BF01608793), [arXiv:math/9902161](https://arxiv.org/abs/math/9902161). Read 2026-11-13: the [abstract](https://arxiv.org/abs/math/9902161) and [preprint PDF](https://arxiv.org/pdf/math/9902161), introduction p. 5. The abstract says patterns occurring in large clusters occur “at least cN times in most clusters”. The introduction describes the exceptional proportion as exponentially small. A local eight-cell ring surrounding a vacant cell forces a hole and can occur in arbitrarily large site animals; the pattern theorem therefore gives the indicated limit. Passing from translation classes to free polyominoes changes counts by at most a factor of eight.

## Verification

The source and its described pattern theorem were read directly. The applicability to polyominoes uses the ring argument above; the paper's own proof was not reverified. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

Madras proved the pattern theorem; Johann Peters recorded its consequence in A000105 in 2024. The lab's research identified the missing connection in A001419. See [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Open the linked abstract and PDF and compare the introduction with the ring argument above; reading takes approximately 10 minutes. No paper is bundled.

## Provenance

Source: `projects/science/athanor-oeis`, commit `11b7ea9cc6f4c0057731d8e36c023f8b36e7c27f`, `tasks/2026-11-12-A001419-holey-polyominoes/answers/2026-11-12-chatgpt.md`.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
