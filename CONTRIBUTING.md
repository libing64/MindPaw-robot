# Contributing to MindPaw

MindPaw is a physical robot project. Contributions must be reproducible on
real hardware or in a clearly identified simulation, and must preserve a safe
fallback when a sensor, network, or model fails.

## Before opening an Issue

Choose the most specific Issue Form and search existing reports first. Include
the board/module revision, firmware or Gateway commit, power supply, exact
commands or wiring, expected and observed results, and logs or measurements.
Never include API keys, Wi-Fi passwords, or personal data.

AI may assist with search, translation, or formatting, but AI-only or
unverifiable reports are not accepted. The author must personally reproduce the
problem and answer maintainer follow-up questions. Reports without evidence may
be labelled `needs-more-info` and closed after a reasonable response window.

## Pull requests

1. Keep a PR focused on firmware, hardware, documentation, 3D assets, or AI Infra.
2. Explain compatibility impact and the safe rollback or power-off procedure.
3. Do not commit `.env`, provider keys, build artifacts, or personal logs.
4. Update the affected beginner tutorial and `hardware-manifest.json` when paths change.
5. Run the checks below before submitting:

```bash
python3 scripts/validate_project.py
python3 -m compileall -q ai-infra MindPaw_main/tools
(cd ai-infra && python3 -m unittest discover -s tests -v)
git diff --check
```

For firmware changes, also run `pio run --project-dir MindPaw_main` when
PlatformIO is available. For motion or power changes, test with servos
disconnected first and include the measured voltage/current in the PR.

## Ownership boundaries

- `MindPaw_main/`: ESP8266 firmware and device protocol.
- `ai-infra/`: optional Gateway, provider adapters, and research experiments.
- `SCH&PCB/` and `3Dmodel/`: electrical and mechanical source files.
- `Docs/`: beginner reproduction, safety, and troubleshooting procedures.

See [`MAINTAINERS.md`](MAINTAINERS.md), [`SECURITY.md`](SECURITY.md), and
[`CONTENT-LICENSE.md`](CONTENT-LICENSE.md) for review and licensing boundaries.
