<!-- markdownlint-disable MD013 MD043 -->

# BrainGenix-ERS Management API Sandbox

This directory contains a first-pass management API sandbox for `BrainGenix-ERS#472`.

The goal is narrow:

- define a concrete HTTP management contract that later ERS runtime work can implement
- provide a local mock server with no third-party Python dependencies
- provide a smoke-test harness that exercises the first-pass endpoints

This is not wired into the C++ runtime yet. It is a sandbox seam and contract, not a production control plane.

## Files

- `openapi.yaml`: OpenAPI 3.0 contract for the first-pass management surface
- `management_api_server.py`: stdlib-only mock server that serves the contract with canned responses
- `tests/smoke_test.py`: local smoke harness for the mock server

## Endpoints

- `GET /healthz`
- `GET /v1/runtime`
- `GET /v1/projects/current`
- `GET /v1/scenes/current/summary`
- `GET /v1/logs/opengl`
- `POST /v1/rendering/shadow-maps/refresh`
- `POST /v1/projects/export`

## Local Usage

Start the mock server:

```bash
python3 Sandbox/ManagementAPI/management_api_server.py --host 127.0.0.1 --port 8765
```

Run the smoke test:

```bash
python3 Sandbox/ManagementAPI/tests/smoke_test.py
```

## Intentional Gaps

- no integration with the ERS C++ runtime or editor process yet
- no authentication, authorization, or TLS yet
- no persistent job store or cluster-management behavior yet
- no Kafka-backed transport or management-log pipeline yet
