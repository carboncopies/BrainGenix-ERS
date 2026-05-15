#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import subprocess  # nosec B404
import sys
from datetime import UTC, datetime
from pathlib import Path
from typing import Any, Iterable


ROOT = Path(__file__).resolve().parent
DEFAULT_TOPIC_NAME = "ers-management-logs"
DEFAULT_BOOTSTRAP_SERVER = "localhost:9092"
REQUIRED_FIELDS = (
    "timestamp",
    "managementChannel",
    "subsystem",
    "category",
    "severity",
    "source",
    "type",
    "id",
    "message",
)


def build_management_log_event(
    management_channel: str,
    subsystem: str,
    category: str,
    severity: str,
    source: str,
    event_type: str,
    event_id: int,
    message: str,
    project: str | None = None,
    scene: str | None = None,
    metadata: dict[str, Any] | None = None,
    timestamp: str | None = None,
) -> dict[str, Any]:
    event: dict[str, Any] = {
        "timestamp": timestamp or datetime.now(UTC).isoformat().replace("+00:00", "Z"),
        "managementChannel": management_channel,
        "subsystem": subsystem,
        "category": category,
        "severity": severity,
        "source": source,
        "type": event_type,
        "id": event_id,
        "message": message,
    }
    if project:
        event["project"] = project
    if scene:
        event["scene"] = scene
    if metadata:
        event["metadata"] = metadata
    validate_event(event)
    return event


def validate_event(event: dict[str, Any]) -> None:
    missing = [field for field in REQUIRED_FIELDS if field not in event]
    if missing:
        raise ValueError(f"management log event is missing required fields: {missing}")
    if not isinstance(event["id"], int):
        raise ValueError("management log event field 'id' must be an integer")
    if "metadata" in event and not isinstance(event["metadata"], dict):
        raise ValueError("management log event field 'metadata' must be an object")


def event_to_json(event: dict[str, Any]) -> str:
    validate_event(event)
    return json.dumps(event, separators=(",", ":"), sort_keys=True)


def load_events(path: Path) -> list[dict[str, Any]]:
    events: list[dict[str, Any]] = []
    for line_number, line in enumerate(path.read_text().splitlines(), start=1):
        if not line.strip():
            continue
        try:
            event = json.loads(line)
        except json.JSONDecodeError as exc:
            raise ValueError(f"{path}:{line_number}: invalid JSON: {exc}") from exc
        validate_event(event)
        events.append(event)
    return events


def encode_events(events: Iterable[dict[str, Any]]) -> str:
    return "\n".join(event_to_json(event) for event in events) + "\n"


def publish_events(
    events: Iterable[dict[str, Any]],
    topic: str = DEFAULT_TOPIC_NAME,
    bootstrap_server: str = DEFAULT_BOOTSTRAP_SERVER,
    compose_root: Path = ROOT,
) -> subprocess.CompletedProcess[str]:
    payload = encode_events(events)
    command = [
        "docker",
        "compose",
        "exec",
        "-T",
        "kafka",
        "kafka-console-producer.sh",
        "--topic",
        topic,
        "--bootstrap-server",
        bootstrap_server,
    ]
    return subprocess.run(  # nosec B603
        command,
        cwd=compose_root,
        text=True,
        input=payload,
        capture_output=True,
        check=True,
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Publish ERS management log events to the Kafka sandbox.")
    parser.add_argument(
        "--input",
        type=Path,
        default=ROOT / "messages" / "01_sample_management_logs.jsonl",
        help="JSONL management log event file to publish.",
    )
    parser.add_argument("--topic", default=DEFAULT_TOPIC_NAME, help="Kafka topic name.")
    parser.add_argument("--bootstrap-server", default=DEFAULT_BOOTSTRAP_SERVER, help="Kafka bootstrap server.")
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Validate and print the events without publishing to Kafka.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        events = load_events(args.input)
        payload = encode_events(events)
        if args.dry_run:
            print(payload, end="")
            return 0
        publish_events(events, args.topic, args.bootstrap_server)
        print(f"Published {len(events)} management log event(s) to {args.topic}.")
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(str(exc), file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
