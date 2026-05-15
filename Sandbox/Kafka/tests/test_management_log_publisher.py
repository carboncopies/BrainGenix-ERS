#!/usr/bin/env python3

from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path

import sys


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from management_log_publisher import (  # noqa: E402
    build_management_log_event,
    encode_events,
    load_events,
    validate_event,
)


class ManagementLogPublisherTests(unittest.TestCase):
    def test_build_event_validates_required_fields(self) -> None:
        event = build_management_log_event(
            management_channel="opengl-log-item",
            subsystem="OpenGLLoggingSystem",
            category="opengl-debug",
            severity="INFO",
            source="APPLICATION",
            event_type="OTHER",
            event_id=42,
            message="test event",
            project="Example Project",
            scene="Example Scene",
            metadata={"topicVersion": 1},
            timestamp="2026-04-22T00:00:00Z",
        )

        self.assertEqual(event["id"], 42)
        self.assertEqual(event["metadata"]["topicVersion"], 1)

    def test_validate_rejects_missing_field(self) -> None:
        with self.assertRaises(ValueError):
            validate_event({"id": 1, "message": "missing envelope"})

    def test_load_and_encode_jsonl_events(self) -> None:
        event = build_management_log_event(
            management_channel="management-action",
            subsystem="ManagementAPI",
            category="management-action",
            severity="INFO",
            source="APPLICATION",
            event_type="OTHER",
            event_id=100,
            message="action accepted",
            timestamp="2026-04-22T00:00:00Z",
        )

        with tempfile.TemporaryDirectory() as temporary_directory:
            path = Path(temporary_directory) / "events.jsonl"
            path.write_text(json.dumps(event) + "\n")

            events = load_events(path)
            payload = encode_events(events)

        self.assertEqual(len(events), 1)
        self.assertIn("\"managementChannel\":\"management-action\"", payload)
        self.assertTrue(payload.endswith("\n"))


if __name__ == "__main__":
    unittest.main()
