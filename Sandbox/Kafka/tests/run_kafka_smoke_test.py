#!/usr/bin/env python3

from __future__ import annotations

import argparse
import subprocess  # nosec B404
import sys
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from management_log_publisher import load_events, publish_events  # noqa: E402

TOPIC_NAME = "ers-management-logs"
MESSAGE_FILE = ROOT / "messages" / "01_sample_management_logs.jsonl"
EXPECTED_OUTPUT = [
    "opengl-log-item",
    "shadow-refresh-requested",
    "Sandbox OpenGL log routing initialized.",
]


def run_compose(args: list[str], check: bool = True, stdin_text: str | None = None) -> subprocess.CompletedProcess[str]:
    command = ["docker", "compose", *args]
    return subprocess.run(  # nosec B603
        command,
        cwd=ROOT,
        text=True,
        input=stdin_text,
        capture_output=True,
        check=check,
    )


def wait_for_kafka(max_attempts: int, delay_seconds: float) -> None:
    for attempt in range(1, max_attempts + 1):
        result = run_compose(
            ["exec", "-T", "kafka", "kafka-topics.sh", "--bootstrap-server", "localhost:9092", "--list"],
            check=False,
        )
        if result.returncode == 0:
            return
        if attempt == max_attempts:
            raise RuntimeError(
                "Kafka did not become ready in time.\n"
                f"stdout:\n{result.stdout}\n"
                f"stderr:\n{result.stderr}"
            )
        time.sleep(delay_seconds)


def create_topic() -> None:
    run_compose(
        [
            "exec",
            "-T",
            "kafka",
            "kafka-topics.sh",
            "--create",
            "--if-not-exists",
            "--topic",
            TOPIC_NAME,
            "--bootstrap-server",
            "localhost:9092",
            "--partitions",
            "1",
            "--replication-factor",
            "1",
        ],
        check=True,
    )


def produce_messages() -> None:
    publish_events(load_events(MESSAGE_FILE), topic=TOPIC_NAME)


def consume_messages() -> str:
    result = run_compose(
        [
            "exec",
            "-T",
            "kafka",
            "kafka-console-consumer.sh",
            "--topic",
            TOPIC_NAME,
            "--from-beginning",
            "--max-messages",
            "2",
            "--bootstrap-server",
            "localhost:9092",
        ],
        check=True,
    )
    return result.stdout


def ensure_expected_output(output: str) -> None:
    missing = [token for token in EXPECTED_OUTPUT if token not in output]
    if missing:
        raise RuntimeError(
            "Kafka smoke test output did not include all expected markers.\n"
            f"Missing: {missing}\n"
            f"stdout:\n{output}"
        )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Run the BrainGenix-ERS Kafka sandbox smoke test."
    )
    parser.add_argument(
        "--start",
        action="store_true",
        help="Start the sandbox with `docker compose up -d` before running the test.",
    )
    parser.add_argument(
        "--teardown",
        action="store_true",
        help="Run `docker compose down -v` after the smoke test completes.",
    )
    parser.add_argument(
        "--max-attempts",
        type=int,
        default=20,
        help="Maximum number of readiness checks before failing.",
    )
    parser.add_argument(
        "--delay-seconds",
        type=float,
        default=3.0,
        help="Delay between readiness checks.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        if args.start:
            run_compose(["up", "-d"])

        wait_for_kafka(args.max_attempts, args.delay_seconds)
        create_topic()
        produce_messages()
        output = consume_messages()
        ensure_expected_output(output)

        print("Kafka sandbox smoke test passed.")
        print(output.strip())
        return 0
    except (subprocess.CalledProcessError, RuntimeError) as exc:
        print(str(exc), file=sys.stderr)
        return 1
    finally:
        if args.teardown:
            teardown_result = run_compose(["down", "-v"], check=False)
            if teardown_result.returncode != 0:
                print(teardown_result.stderr, file=sys.stderr)


if __name__ == "__main__":
    raise SystemExit(main())
