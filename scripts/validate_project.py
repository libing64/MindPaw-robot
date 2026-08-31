#!/usr/bin/env python3
"""Validate the cross-domain files that make a MindPaw checkout reproducible."""

import json
import pathlib
import re
import sys


ROOT = pathlib.Path(__file__).resolve().parents[1]


def main() -> None:
    manifest = ROOT / "hardware-manifest.json"
    data = json.loads(manifest.read_text(encoding="utf-8"))
    if data.get("schema_version") != 1:
        raise SystemExit("hardware-manifest.json must use schema_version 1")
    for raw_path in data.get("required_paths", []):
        path = ROOT / raw_path
        if not path.exists():
            raise SystemExit(f"missing required project path: {raw_path}")

    platformio = (ROOT / "MindPaw_main/platformio.ini").read_text(encoding="utf-8")
    if "[env:nodemcuv2]" not in platformio or "framework = arduino" not in platformio:
        raise SystemExit("PlatformIO project is missing the expected ESP8266 environment")

    for env_file in [ROOT / "ai-infra/.env.example"]:
        if re.search(r"(?i)(api[_-]?key|token)\s*=\s*(sk-|ghp_|github_pat_|[A-Za-z0-9]{24,})", env_file.read_text(encoding="utf-8")):
            raise SystemExit(f"possible real secret in {env_file}")
    print("MindPaw project manifest ok")


if __name__ == "__main__":
    main()
