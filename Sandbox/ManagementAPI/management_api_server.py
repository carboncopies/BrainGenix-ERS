#!/usr/bin/env python3

"""Stdlib-only mock management API server for BrainGenix-ERS."""

from __future__ import annotations

import argparse
import json
from datetime import datetime, timezone
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from typing import Any
from urllib.parse import urlparse
from uuid import uuid4


HEALTH_STATUS = {"status": "ok", "apiVersion": "0.1.0-sandbox"}
RUNTIME_INFO = {
    "application": "BrainGenix-ERS",
    "apiVersion": "0.1.0-sandbox",
    "mode": "sandbox",
    "features": [
        "runtime-summary",
        "project-summary",
        "scene-summary",
        "opengl-log-readback",
        "shadow-refresh-action",
        "project-export-action",
    ],
}
PROJECT_SUMMARY = {
    "name": "Example Project",
    "root": "/tmp/BrainGenix-ERS-Example",
    "exportDirectory": "/tmp/BrainGenix-ERS-Export",
    "includeBinary": True,
    "includeConfig": True,
}
SCENE_SUMMARY = {
    "sceneName": "Example Scene",
    "selectedObject": 0,
    "counts": {
        "models": 12,
        "pointLights": 3,
        "directionalLights": 1,
        "spotLights": 2,
    },
}
OPENGL_LOG_ITEMS = {
    "items": [
        {
            "id": 131185,
            "severity": "NOTIFICATION",
            "source": "APPLICATION",
            "type": "OTHER",
            "message": "Sandbox OpenGL log routing initialized.",
        },
        {
            "id": 1,
            "severity": "LOW",
            "source": "WINDOW SYSTEM",
            "type": "PERFORMANCE",
            "message": "Mock management API is serving canned diagnostics.",
        },
    ]
}


def _now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def _accepted_action(action_name: str) -> dict[str, str]:
    return {
        "actionId": f"{action_name}-{uuid4()}",
        "status": "accepted",
        "acceptedAt": _now_iso(),
    }


class ManagementAPIHandler(BaseHTTPRequestHandler):
    server_version = "BrainGenixERSManagementAPISandbox/0.1"

    def log_message(self, fmt: str, *args: Any) -> None:
        return

    def _write_json(self, status_code: int, payload: dict[str, Any]) -> None:
        encoded = json.dumps(payload, indent=2).encode("utf-8")
        self.send_response(status_code)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(encoded)))
        self.end_headers()
        self.wfile.write(encoded)

    def _read_json_body(self) -> dict[str, Any]:
        content_length = int(self.headers.get("Content-Length", "0"))
        if content_length <= 0:
            return {}
        raw = self.rfile.read(content_length)
        if not raw:
            return {}
        return json.loads(raw.decode("utf-8"))

    def _not_found(self) -> None:
        self._write_json(404, {"error": "not_found", "path": self.path})

    def do_GET(self) -> None:  # noqa: N802
        path = urlparse(self.path).path
        if path == "/healthz":
            self._write_json(200, HEALTH_STATUS)
        elif path == "/v1/runtime":
            self._write_json(200, RUNTIME_INFO)
        elif path == "/v1/projects/current":
            self._write_json(200, PROJECT_SUMMARY)
        elif path == "/v1/scenes/current/summary":
            self._write_json(200, SCENE_SUMMARY)
        elif path == "/v1/logs/opengl":
            self._write_json(200, OPENGL_LOG_ITEMS)
        else:
            self._not_found()

    def do_POST(self) -> None:  # noqa: N802
        path = urlparse(self.path).path
        try:
            self._read_json_body()
        except json.JSONDecodeError:
            self._write_json(400, {"error": "invalid_json", "path": path})
            return

        if path == "/v1/rendering/shadow-maps/refresh":
            self._write_json(202, _accepted_action("shadow-refresh"))
        elif path == "/v1/projects/export":
            self._write_json(202, _accepted_action("project-export"))
        else:
            self._not_found()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run the BrainGenix-ERS management API sandbox server.")
    parser.add_argument("--host", default="127.0.0.1", help="Bind host.")
    parser.add_argument("--port", default=8765, type=int, help="Bind port.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    server = ThreadingHTTPServer((args.host, args.port), ManagementAPIHandler)
    host, port = server.server_address
    print(f"Listening on http://{host}:{port}", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
