<!-- markdownlint-disable MD013 MD043 -->

# Apache Kafka Management Logging Sandbox

This directory provides a first-pass local Kafka sandbox for BrainGenix-ERS management logging work.

It is intentionally separate from the current runtime engine path. The goal is to make issue `#473` reviewable without pretending that the engine already has a live Kafka-backed management plane.

## Included

- `docker-compose.yml`: single-node Kafka sandbox pinned to the official `apache/kafka:4.2.0` image
- `schemas/ers_management_log_event.schema.json`: first-pass JSON schema for management log events
- `messages/01_sample_management_logs.jsonl`: newline-delimited sample events shaped around the current OpenGL log item fields plus a management envelope
- `management_log_publisher.py`: reusable management log event builder, validator, and sandbox publisher
- `tests/run_kafka_smoke_test.py`: repeatable smoke harness for topic creation, sample publish, and sample consume

## Prerequisites

- Docker Engine or Docker Desktop
- Docker Compose v2 (`docker compose ...`)

## Start The Sandbox

From this directory:

```bash
docker compose up -d
```

Wait until the container is healthy or until topic commands succeed.

## Create The Topic

```bash
docker compose exec kafka kafka-topics.sh \
  --create \
  --if-not-exists \
  --topic ers-management-logs \
  --bootstrap-server localhost:9092 \
  --partitions 1 \
  --replication-factor 1
```

## Publish Sample Management Log Events

```bash
python3 management_log_publisher.py \
  --input messages/01_sample_management_logs.jsonl
```

To validate and print the event payload without requiring Docker:

```bash
python3 management_log_publisher.py --dry-run
```

## Consume The Topic

```bash
docker compose exec -T kafka kafka-console-consumer.sh \
  --topic ers-management-logs \
  --from-beginning \
  --max-messages 2 \
  --bootstrap-server localhost:9092
```

## Reset

```bash
docker compose down -v
```

## Run The Smoke Test Harness

The first-pass sandbox test for issue `#473` lives in `tests/run_kafka_smoke_test.py`.

To start the sandbox, create the topic, publish the sample management log events, consume them back, and tear everything down in one pass:

```bash
python3 tests/run_kafka_smoke_test.py --start --teardown
```

If the sandbox is already running, omit `--start`. If you want to inspect the broker afterward, omit `--teardown`.

## Notes

- This sandbox is for management-logging experimentation only.
- It does not yet integrate with the live `ERS_OpenGLLoggingSystem`, the current C++ logger, or the `#472` management API server at runtime.
- The sample event schema intentionally carries the current `ERS_OpenGLLogItem` fields (`id`, `source`, `type`, `severity`, `message`) inside a larger management envelope so later runtime plumbing has a concrete event target.

## References

- Apache Kafka Quickstart: <https://kafka.apache.org/quickstart/>
- Apache Kafka Docker docs: <https://kafka.apache.org/41/getting-started/docker/>
