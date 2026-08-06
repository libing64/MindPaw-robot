# MindPaw — Affective-VLA (NeurIPS Template)

Emotion-Conditioned Vision-Language-Action Generation for a Low-Cost Companion Robot.

## Files

| File | Purpose |
|------|---------|
| `neurips_2024.tex` | **Main paper source** |
| `neurips_2024.sty` | NeurIPS 2024 style file |
| `refs.bib` | Bibliography |

## How to Compile

**On Overleaf:**
1. Upload `neurips_2024.tex`, `neurips_2024.sty`, `refs.bib`
2. Set compiler to **XeLaTeX** (or pdfLaTeX)
3. Set bibliography to `refs.bib`

**Locally:**
```bash
pdflatex neurips_2024.tex
bibtex neurips_2024
pdflatex neurips_2024.tex
pdflatex neurips_2024.tex
```

## Paper Outline

- **Abstract** — closed affective loop on a \$8 MCU, three contributions, headline numbers.
- **1 Introduction** — the VLA vs. companion-robot gap; emotion as a first-class conditioning channel; four contributions (incl. the MAID dataset).
- **2 Related Work** — VLA, affective computing/social robots, **affective interaction datasets (SEMAINE/RECOLA/MERCI/HRI-SENSE/SEMIAC)**, TinyML distillation, LLM-as-judge.
- **3 Method**
  - 3.1 Overview (closed affective loop)
  - 3.2 PAD Emotion Engine (Eq. 1–2, <100 B RAM)
  - 3.3 Multi-modal Affective Fusion (MAF)
  - 3.4 Emotion-Conditioned VLA (EC-VLA) + coherence proposition
  - 3.5 Affective Edge Distillation (Eq. 4–5, int8 MLP, parametric motion)
  - 3.6 **MAID corpus** — collection + continuous-PAD annotation protocol (SEMAINE/RECOLA-style), statistics, ethics
- **4 Experiments**
  - LLM-judged affective consistency (Table 3)
  - PAD trajectory quality (Table 4)
  - Edge distillation (Table 5)
  - Ablation (Table 7)
  - **MAID-supervised affect estimation (Table 8)** — CCC vs. annotator ceiling, single-modality, and hand-set heuristics; cross-modal conflict detection; PAD calibration effect
  - 30-subject user study with SAM + **implicit behaviour signals (voice prosody, gesture frequency)** (Table 9)
  - Threats to validity
- **5 Conclusion** + Broader Impact

## ⚠️ IMPORTANT — Before You Submit

The quantitative results in this draft (Tables 3–9) are **plausible
placeholders** written to make the architecture concrete. They are **not**
measured. Before any submission you MUST:

1. **Train the gesture student.** Run `tools/distill_gesture.py` from the repo
   root to generate real int8 weights; report the real accuracy (Table 6).
2. **Collect the MAID corpus.** The dataset (Sec. 3.6, Table 3) is the paper's
   fourth contribution and currently exists only as a protocol. You must
   actually collect it: IRB/consent, 3 continuous-PAD annotators, the 20-session
   pilot, run the cross-modal-conflict labeling, and release on a data host with
   a research-only license. The CCC numbers in Table 8 and the conflict-detection
   numbers in Sec. 4.6 are placeholders.
3. **Run the LLM-judge experiment.** Replay the 300-turn dialogue corpus with
   real teacher calls and re-measure Table 4.
4. **Run the user study (IRB).** 30 subjects, SAM + Likert, paired t-tests,
   plus the MAID-protocol recordings for the implicit-signal rows in Table 9.
5. **Measure PAD trajectories** on the real device and re-check Table 5.
6. **Calibrate the PAD gains.** Run the MAID-calibrated update (Sec. 4.6) and
   report real MAE / total-variation reductions.
7. **Fix the author block.** Replace `First Author / Second Author` and the
   placeholder affiliation/email.

The paper is written so that these are *replacements*, not rewrites: the
method and structure stay; the numbers get swapped in.

## Figures Still Needed

| Figure | Where | Status |
|--------|-------|--------|
| Pipeline diagram (closed affective loop) | Figure 1 | **Placeholder box** — replace with TikZ/png |
| Robot photo / BOM photo | Appendix | Not present |
| User-study photos or session snapshots | Appendix | Not present |

The legacy `demo_*.jpg` files in this folder belong to the old YOLOv14 draft
and should be **deleted or replaced** before submission.

## How to Change the Venue Template

This uses `neurips_2024.sty`. To target **RO-MAN / ICRA / IROS / HRI**, swap
the style file and adjust: abstract placement, section caps, and the
references style. The content is venue-agnostic.
