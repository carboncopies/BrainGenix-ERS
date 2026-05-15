USE braingenix_ers_sandbox;

INSERT INTO scene_metadata (
  scene_id,
  scene_name,
  scene_path,
  scene_format_version,
  active_scene_camera_index,
  created_at,
  updated_at
) VALUES (
  11111111-1111-1111-1111-111111111111,
  'Sandbox Scene',
  '/Sandbox/Scenes/SandboxScene.yaml',
  6,
  0,
  toTimestamp(now()),
  toTimestamp(now())
);

INSERT INTO scene_objects_by_scene (
  scene_id,
  scene_object_index,
  scene_object_id,
  object_type,
  object_label,
  object_group,
  backing_index,
  payload_json
) VALUES (
  11111111-1111-1111-1111-111111111111,
  0,
  22222222-2222-2222-2222-222222222222,
  'Model',
  '[M] TestCube',
  'Sandbox',
  0,
  '{"ModelPath":"Assets/TestCube","Position":[0.0,0.0,0.0]}'
);

INSERT INTO models_by_name (
  model_name,
  model_id,
  asset_path,
  scene_id,
  max_texture_level,
  target_texture_level_ram,
  target_texture_level_vram,
  payload_json
) VALUES (
  'TestCube',
  33333333-3333-3333-3333-333333333333,
  'Assets/TestCube',
  11111111-1111-1111-1111-111111111111,
  4,
  2,
  1,
  '{"HasTransparency":false}'
);

SELECT scene_name, scene_format_version, active_scene_camera_index
FROM scene_metadata
WHERE scene_id = 11111111-1111-1111-1111-111111111111;

SELECT scene_object_index, object_type, object_label
FROM scene_objects_by_scene
WHERE scene_id = 11111111-1111-1111-1111-111111111111;

SELECT model_name, asset_path, max_texture_level
FROM models_by_name
WHERE model_name = 'TestCube';
