CREATE KEYSPACE IF NOT EXISTS braingenix_ers_sandbox
WITH replication = {
  'class': 'SimpleStrategy',
  'replication_factor': 1
};

USE braingenix_ers_sandbox;

CREATE TABLE IF NOT EXISTS scene_metadata (
  scene_id uuid PRIMARY KEY,
  scene_name text,
  scene_path text,
  scene_format_version bigint,
  active_scene_camera_index int,
  created_at timestamp,
  updated_at timestamp
);

CREATE TABLE IF NOT EXISTS scene_objects_by_scene (
  scene_id uuid,
  scene_object_index bigint,
  scene_object_id uuid,
  object_type text,
  object_label text,
  object_group text,
  backing_index bigint,
  payload_json text,
  PRIMARY KEY ((scene_id), scene_object_index)
);

CREATE TABLE IF NOT EXISTS models_by_name (
  model_name text,
  model_id uuid,
  asset_path text,
  scene_id uuid,
  max_texture_level int,
  target_texture_level_ram int,
  target_texture_level_vram int,
  payload_json text,
  PRIMARY KEY ((model_name), model_id)
);
