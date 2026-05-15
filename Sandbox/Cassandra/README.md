# Apache Cassandra Sandbox

This directory provides a first-pass local Cassandra sandbox for BrainGenix-ERS data-model experiments.

It is intentionally separate from the current runtime engine path. The goal is to make issue `#461` reviewable without pretending that the engine already has a Cassandra-backed IOSubsystem implementation.

## Included

- `docker-compose.yml`: single-node Cassandra sandbox pinned to the official `cassandra:5.0` image
- `schema/00_braingenix_ers_sandbox.cql`: first-pass keyspace and denormalized tables for scene metadata plus per-scene objects
- `queries/01_smoke_test.cql`: sample inserts and reads that exercise the sandbox schema

## Prerequisites

- Docker Engine or Docker Desktop
- Docker Compose v2 (`docker compose ...`)

## Start The Sandbox

From this directory:

```bash
docker compose up -d
```

The official Cassandra image does not accept CQL connections until initialization completes, so wait until the container is healthy or its logs show that CQL clients are listening.

## Open `cqlsh`

```bash
docker compose exec cassandra cqlsh
```

## Load The ERS Sandbox Schema

From inside `cqlsh`:

```sql
SOURCE '/workspace/schema/00_braingenix_ers_sandbox.cql';
```

To run the sample inserts and queries afterward:

```sql
SOURCE '/workspace/queries/01_smoke_test.cql';
```

## Reset

```bash
docker compose down -v
```

## Notes

- This sandbox is for schema and connector experimentation only.
- It does not yet integrate with `bg-ers-iosubsystem`, `ERS_ProjectManager`, or the live scene loader.
- The tables are intentionally denormalized around likely read paths so follow-up connector work has a concrete starting point.

## References

- Docker Official Image for Cassandra: <https://hub.docker.com/_/cassandra>
- Apache Cassandra `cqlsh` documentation: <https://cassandra.apache.org/doc/stable/cassandra/managing/tools/cqlsh.html>
