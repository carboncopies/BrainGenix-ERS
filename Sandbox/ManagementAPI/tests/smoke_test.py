#!/usr/bin/env python3

"""Smoke-test the BrainGenix-ERS management API sandbox server."""

from __future__ import annotations

import json
import socket
import subprocess
import sys
import time
from pathlib import Path
from typing import Any
from urllib.error import URLError
from urllib.request import Request, urlopen


ROOT = Path(__file__).resolve().parents[1]
SERVER = ROOT / "management_api_server.py"


def _free_port() -> int:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("127.0.0.1", 0))
    _, port = sock.getsockname()
    sock.close()
    return int(port)


def _request(url: str, method: str = "GET", body: dict[str, Any] | None = None) -> dict[str, Any]:
    data = None
    headers = {}
    if body is not None:
        data = json.dumps(body).encode("utf-8")
        headers["Content-Type"] = "application/json"
    req = Request(url, data=data, method=method, headers=headers)
    with urlopen(req, timeout=5) as response:
        return json.loads(response.read().decode("utf-8"))


def main() -> int:
    port = _free_port()
    process = subprocess.Popen(
        [sys.executable, str(SERVER), "--host", "127.0.0.1", "--port", str(port)],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    base = f"http://127.0.0.1:{port}"

    try:
        deadline = time.time() + 10
        while True:
            try:
                health = _request(f"{base}/healthz")
                if health["status"] == "ok":
                    break
            except URLError:
                if time.time() >= deadline:
                    raise
                time.sleep(0.2)

        runtime = _request(f"{base}/v1/runtime")
        project = _request(f"{base}/v1/projects/current")
        scene = _request(f"{base}/v1/scenes/current/summary")
        logs = _request(f"{base}/v1/logs/opengl")
        refresh = _request(
            f"{base}/v1/rendering/shadow-maps/refresh",
            method="POST",
            body={"reason": "smoke-test"},
        )
        export = _request(
            f"{base}/v1/projects/export",
            method="POST",
            body={"includeBinary": True, "includeConfig": True},
        )

        assert runtime["application"] == "BrainGenix-ERS"
        assert "runtime-summary" in runtime["features"]
        assert project["name"] == "Example Project"
        assert scene["counts"]["models"] >= 0
        assert len(logs["items"]) >= 1
        assert refresh["status"] == "accepted"
        assert export["status"] == "accepted"
        return 0
    finally:
        process.terminate()
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            process.kill()
            process.wait(timeout=5)


if __name__ == "__main__":
    raise SystemExit(main())
