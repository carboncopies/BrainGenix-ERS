# ERS Goal Progress Ledger

Living work-queue for the "realize project goals" mission. Status values:
`verified` (works as documented) · `fixed` (was broken, now fixed + rebuilt) ·
`blocked` (environment/external blocker, reason recorded) ·
`not-implemented` (documented/aspirational, recorded with reason) · `pending`

Legend note: builds are verified per change; "fixed" implies the build was re-run and passes.

## Environment / Build

| Item | Status | Notes |
|---|---|---|
| System deps (apt list from Tools/Setup.sh) | verified | All 22 packages already installed; sudo unavailable but not needed |
| vcpkg bootstrap | verified | `ThirdParty/vcpkg/vcpkg` present |
| cmake configure (vcpkg manifest: assimp, freeimage, lua, glfw3, …) | verified | Configured in ~20s (deps pre-provisioned in ThirdParty) |
| Full compile (`cmake --build -j6`, Debug) | verified | All targets built, `Binaries/ERS` linked at 100% |
| Binary launches | verified | Full editor init on display :0 / RTX 3070, ran 30s, killed by `timeout` (exit 124) — viewed viewport/FBO/render-texture/motion-blur history creation; no crash |

### Runtime observations

- VRAM auto-detection fails on this NVIDIA laptop GPU; falls back to config value 10 GiB (graceful). Improve detection later.
- Unattended-run flags are parsed but unused; app always opens a window.

## Phase 1 — Renderer defects (make the code do what it intends)

Queue from code-inventory sweep (Source/, Overlays/, Sandbox/):

| # | Item | Status | Notes |
|---|---|---|---|
| P1.1 | `ERS_STRUCT_Project` copy/dtor UB (`Project.h:42,47-50`) — root cause of documented Game Controller Settings crash (`GUI_Window_ControllerSettings.cpp:156` derefs dangling `ControllerSettings` vector) | fixed | Converted to value member `std::vector<ERS_STRUCT_ControllerSettings>` across 5 files (loader/manager/writer/window/struct); window now null-safe with graceful fallback and bounds guard; build 100% clean |
| P1.2 | `FindShaderByName.cpp:8-20` silent fallback returns shader index 0 on name miss | fixed | Optional `Logger*` param added (default nullptr); miss logs severity-8 with name, once per distinct name (static cache prevents per-frame spam — caller at `VisualRenderer.cpp:334-335` runs every frame); contract documented in header |
| P1.3 | `DepthMaps.cpp:69-75` glTextureStorage3D segfault workaround (unresolved) | fixed | Root-caused: original call passed the GL_TEXTURE_2D_ARRAY **target** instead of the texture **name**, levels=0 (invalid), and DSA requires GL 4.5 which isn't guaranteed — the glTexImage3D path is correct; comment now explains accurately |
| P1.4 | Light-icon billboard temp-disabled "Doesn't Work ATM" (`VisualRenderer.cpp:970`) | fixed | **Premise corrected**: icons are NOT disabled — `IconRenderer->Draw()` runs every frame gated by `Viewport->LightIcons` (default true, menu-toggleable); `_LightIcon` shader compiles (GL program 4); blend state set by Grid's ctor. Stale comment replaced with accurate note; no code change needed |
| P1.5 | Dead/debug leftovers in renderer main loop (`VisualRenderer.cpp:352` preview-shader-as-depth line, `:369` commented SetSystemInfoData, `:233` hardcoded "CHANGE THIS LATER" mode) | fixed | dead debug bind removed; uncompilable commented call removed; "CHANGE THIS LATER" replaced with neutral comment (editor-mode default kept) |
| P1.6 | Redundant local LuaJIT test interpreter at startup (`Main.cpp:112-120`, runs `Test_Script()` every launch) | fixed | removed; SystemUtils instance is the live one; smoke log confirms "Hello from LuaJIT!" gone. Note: `Test_Script()` method itself still exists unused (future cleanup) |
| P1.7 | `MeshRenderer.cpp:134` transparency "completely bypassed" in no-textures pass | fixed | **Premise corrected**: that pass is called ONLY from depth/shadow sites (`DepthMaps.cpp:397,443,486`) — blending/sort irrelevant there; comment replaced with accurate NOTE incl. alpha-cutout caveat |
| P1.8 | Mouse-scroll callback path broken (`InputProcessor.h:79` "DOESN'T WORK RIGHT NOW"); wheel speed adjust works via `InputProcessor.cpp:306-309` | fixed | Premise updated: no GLFW callback exists — working per-frame ImGui path IS `ScrollCallback`; stale docstring rewritten, dead `MouseWheelH` remnant removed. No new callback added (per-frame path is the documented/working one) |
| P1.9 | `Main.h` dead file referencing ~16 non-existent headers | fixed | Deleted file + removed `${SRC_DIR}/Main.h` from root `CMakeLists.txt` source list; relinked clean |
| P1.10 | `DrawMeshNoTextures.cpp:12-111` ~100 lines commented-out texture code | fixed | deleted; file now 19 lines with NOTE that the pass is depth-map-only by design |

## Phase 2 — README Feature List vs. code

Code-mapping sweep completed. Verdicts: **backed** unless noted below — every editor window, monitoring tool, viewport behavior, scene tree, system log, asset explorer, object properties, script/shader editor, theme/font/camera/rendering/streaming settings, viewport menu, run menu (F5/Esc), gizmo/WASD keybinds exist and are implemented.

Gaps found (queue):

| # | Item | Status | Notes |
|---|---|---|---|
| P2.1 | Keybind mismatch: README says [left shift] moves camera while gizmo active; code binds LEFT CTRL (`VisualRenderer.cpp:652`, key 341) | fixed | key 340 (GLFW_KEY_LEFT_SHIFT) now; comment updated; build+smoke pass |
| P2.2 | Grid-snapping "0.025" item actually sets 0.205 (`ViewportMenu.cpp:523`) | fixed | sets 0.025f now; build+smoke pass |
| P2.3 | Scripting section stale: README says Python; actual scripting is LuaJIT (Python migration) — README must be corrected | fixed | README intro now says Lua executed by embedded LuaJIT |
| P2.4 | Point light `RolloffConstant/Linear/Quadratic` documented in README but NOT exposed to scripts | fixed | See P3.15 — implemented end-to-end including Lua globals (bidirectional) |
| P2.5 | Camera `ScaleX/Y/Z` documented but not exposed; spot `CutOff` vs README `Cutoff`; directional light names unprefixed in code vs `DirectionalLight*` in README | fixed | README corrected: camera Scale entries removed (no scale concept exists), `FOV`+`Priority` added; directional-light names now actual unprefixed API; `CutOff` case fixed; model LOD/texture vars documented |
| P2.6 | Scene-camera context menu commented out (`GUI_Window_SceneTree.cpp:661-673`) — inconsistent with other object types | not-implemented | **Cannot restore**: it references `Subwindow_SceneCameraRenameModal_` and `Subwindow_DeleteSceneCamera_` classes that DO NOT EXIST anywhere in the repo. Queued as P3.16 (mechanical clone of SpotLight modal pair) |
| P2.7 | Framerate target unlock/sync settings are `#ifdef __linux__`-gated (degraded elsewhere) | noted | Linux is the primary platform; acceptable, recorded |
| P2.8 | "Repair asset index" only repairs models in scenes (not textures/scripts/shaders) | noted | partial; record as P3 aspiration |
| P2.9 | Asset Explorer advanced tabs gated on hardwired `AdvancedMode_=true` with no UI toggle (`GUI_Window_AssetExplorer.h:48`) | noted | record as P3 aspiration |
| P2.10 | README says Game Controller Settings "seems to crash" — root cause fixed under P1.1; remove the caveat from README after runtime confirm | fixed | README now describes the real feature (profile list view/add/remove; inline editing not yet implemented). Crash verified-by-construction (no pointer indirection remains); interactive confirmation pending open session |

Noise: README typos ("Shder Editor", "Fornt Selector", "doens't") — fix opportunistically with P2.3/P2.5 docs pass.

## Phase 3 — Aspirations / roadmap items (TODO, "doesn't do anything yet", stubs, Sandbox)

| # | Item | Status | Notes |
|---|---|---|---|
| P3.1 | Sandbox/ (Cassandra, Kafka, ManagementAPI) scaffolding-only | verified-triaged | Zero references from Source/ or build; issue #461/#472/#473 experiments, not integrated — stay as scaffolding (noted, not implemented) |
| P3.2 | "Casts Static Shadows — doesn't do anything yet" (README model settings; prebaked shadows don't exist) | not-implemented | Requires a full prebake pipeline (offline lightmap/baked-shadow asset generation, storage, and render-path wiring). Dynamic shadow maps now exist for point/directional/spot lights with filtering + update modes; prebaking is a new subsystem, triaged here rather than half-built |
| P3.3 | RendererSettings NOT serialized into project (`RendererSettings.h:1` ToDo; `Project.h` has no member) | fixed | 22-key YAML `RendererSettings` section; tolerant read (missing section/keys → defaults + warning); writer syncs live settings on save; loader applies settings before renderer construction (budgets copied only when non-zero so hardware auto-detect survives); smoke log shows "Applying Project Renderer Settings" |
| P3.4 | `AssetStreamingManager::PreloadScene` "Not yet implemented" (`AssetStreamingManager.h:188`) | not-implemented | Declared function, no implementation. Real implementation needs scene-swap coordination (which assets to stage before switch, memory double-occupancy policy). Functionally unverifiable headlessly; triaged with reason |
| P3.5 | Controller profile consumption (`ControllerInputManager.h:55`) — loaded profiles never matched to controllers; settings-edit UI stub (`GUI_Window_ControllerSettings.cpp:158-163,211-220`) | not-implemented | Blocked by design on the missing input-remapping system (the TODO is explicitly "once we have input remapping"); window became crash-free and functional as a profile list manager under P1.1; deeper consumption matches no shipped infrastructure |
| P3.6 | Python→LuaJIT migration residue: `ERS_CLASS_PythonInterpreterIntegration` sources remain, uncompiled; cleanup plan in its Notes.md | fixed | Entire Python dir deleted (12 files + Notes.md); commented refs removed from Main.cpp / SystemUtils.h / CMakeLists; `Test_Script()` + "JuaJIT" typo removed; Script.h doc comments say Lua. Migration plan step 2 complete. Build+headless smoke green |
| P3.17 | (dead rule) `Tools/AuditCppFileNames.py:16-17` has a dead `legacy_pybind` classifier after P3.6 | fixed | Removed with the rest of the PyBind residue; no PyBind files remain to classify |
| P3.7 | Main.cpp:58-62 FIXME aspirations: proper lighting/shadow maps, animations/deformations, offscreen rendering, audio, ray tracing | fixed | Stale FIXME card replaced with NOTE: dynamic shadow-mapped lighting exists; `-Headless true` exists; animation/deformations, offscreen targets, audio, ray tracing remain long-horizon (recorded with reason, tracked here) |
| P3.8 | Headless/offscreen run mode — binary always opens a GLFW window; no arg consumer | fixed | `-Headless true` or `ERS_HEADLESS=1` → `glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE)` before window creation (`RendererManager.cpp:199-215`, consumed from `SystemUtils_->Arguments_` with env fallback); render loop runs fully; smoke + regression pass, documented in README |
| P3.9 | `SceneLoader.cpp:5-6`/`SceneWriter.cpp:5-6` FIXMEs: template-texture reuse map; dynamic/static model transforms | fixed | Replaced with accurate NOTEs: texture dedup verified present at model-loader level (loaded-textures map); models already have runtime transforms via editor+scripts; residual ideas recoded as future-optimization notes, not defects |
| P3.12 | OpenGL logging items not surfaced in main log (`OpenGLLoggingSystem/README.md:5`) | fixed | **Premise corrected**: forwarding to the main log already existed, gated behind collection-enabled (opt-in, off by default). Fixed real problems: severity map (GL HIGH no longer logs as "Fatal" → now 8/7/6/4), `"GL: [id] [source] [type] [severity]"` prefix, `DebugEnabled_` default false so the menu checkbox matches reality, subsystem README updated. Smoke: 0 GL lines as expected (collection off by default) |
| P3.10 | OIT (order-independent transparency) aspiration (`MeshRenderer.cpp:104-112`) | not-implemented | Full transparency architecture (weighted-blend/linked-list OIT) + the listed refactor wish-list ("finish moving mesh draw stuff", remove model draw call) is a renderer-wide refactor; current two-pass transparency sort works for typical scenes. Out of safe autonomous scope; recorded with reason |
| P3.11 | `AssetStreamingManager.cpp:232` todo: unload high-LOD textures over RAM/VRAM thresholds | not-implemented | Auto-downsize mechanism absent. Floor is covered: new loads are budget-gated (`TextureFitsInVRAMBudget`), `QueuePanic()` triggers under critical RAM, and manual Purge RAM/VRAM/All exists in the UI. Fill-rate behavior unverifiable headlessly; recorded with reason |

| P3.13 | `LuaJITInterpreterIntegration/build.log` committed build debris (42 bytes) | fixed | Deleted |
| P3.14 | Unattended run mode: arguments parsed but unused (`Main.cpp:87-91`); add documented flags | fixed | `-Headless true` is now the first consumed flag (see P3.8); README "Running Headless (Hidden Window)" documents usage |
| P3.15 | Point-light attenuation (`RolloffConstant/Linear/Quadratic`) documented in README but has no implementation anywhere (struct, shader uniforms, loaders, writers, editor UI) — implement end-to-end so code matches docs (from P2.4) | fixed | Full pipeline: struct defaults 1/0/0 (visually neutral) → ShaderUniformData → VisualRenderer population → GLSL struct + `1/(Kc+Kl·d+Kq·d²)` factor in all 13 `10041.ERS` project shaders (PBRPointLight only) → SceneWriter v7 + new SceneDecoderV7 (conditional keys, V1–V6 untouched) → ObjectProperties DragFloats → Lua globals. Build + headless smoke green, scene round-trip intact |
| P3.15a | (finding) Legacy `10037.ERS` Blinn-Phong shader already had `ConstantRolloff`/`LinearRolloff`/`QuadraticRolloff` but uniform push never sets them and sets fields it doesn't have — inert, unused by any project's default | noted | triage-only: not bound anywhere; left untouched |
| P3.18 | `SceneDecoderV6.cpp` logs "With Decoder Version 3" (wrong number, pre-existing) | fixed | now logs 6 |
| P3.19 | Vulkan renderer migration (user-requested) | not-implemented | Design-first effort: port GLSL (incl. 13 project shader copies), ImGui backend, FBO/depth-array pipeline, ImGuizmo to Vulkan. Weeks-scale; autonomous half-ports are fakes. Start with a scoping document if pursued |
| P3.20 | Distributed multi-GPU rendering (user-requested; second machine available at 192.168.1.153) | not-implemented | Needs an architecture first: frame/partition strategy, sync protocol, lossless transport, failure modes. Design document before any code |
| P3.16 | SceneCamera rename/delete modals missing — clone `SpotLightRenameModal`+`DeleteSpotLight` file pairs into camera versions and un-comment the context menu (`GUI_Window_SceneTree.cpp:661-673`) (from P2.6) | fixed | New `Subwindow_SceneCameraRenameModal` + `Subwindow_DeleteSceneCamera` (members, Draw calls, CMake entries); context menu live: right-click camera → Rename/Delete. Build + headless smoke + regression all green |

## Phase 4 — Offscreen rendering + asset streaming completion (goal 2)

| # | Item | Status | Notes |
|---|---|---|---|
| P4.1 | Null-window crash on missing display: `InitializeGLFW` doesn't return after failed `glfwCreateWindow` → segfault (exit 139 confirmed with DISPLAY unset) | fixed | `InitializeGLFW` now fatals cleanly (level-10 log, exit 1, no segfault) — verified: no-display no-flag run exits 1 with clear message. NULL-window guards also added to UpdateLoop/LoadEditorData, glfw input calls in VisualRenderer/InputProcessor |
| P4.2 | True display-free offscreen mode via EGL surfaceless/pbuffer context (`-Headless offscreen`); current `-Headless true` still needs a display; leftover `OffscreenRendering`/`OffscreenContextAPI` config scaffolding noted | fixed (with driver caveat) | `eglQueryDevicesEXT` + `EGL_EXT_platform_device` pbuffer (GL4.x core, descending 4.6→4.1), GLAD via eglGetProcAddress; shared EGL worker contexts for texture-upload threads (NVIDIA quirk worked around: share-context creation must be main-thread); ImGui runs without GLFW backend; some GL-ext probing guarded (glGetStringi fallback). **Display-free main loop verified** (EXIT=124, own confirmation run). **Found + worked around NVIDIA driver bug**: project Viewport shader fails to link ONLY under NVIDIA EGL device platform (`C6020 constant register limit` — works under GLX, same driver; standalone repros in /tmp). Ship mitigation: `-EGLDeviceIndex`/`ERS_EGL_DEVICE_INDEX` → Intel iGPU/Mesa device 2 renders with 0 GL errors. README "Running Headless (Display-Free Offscreen Rendering)" documents semantics, requirements, device selection, driver caveat |
| P4.3 | `AssetStreamingManager::PreloadScene` declared-only (`AssetStreamingManager.h:188`) — background stage next scene's assets | fixed | Implemented: RAM-only staging of inactive scene's models at baseline LOD (level 0 with MinLOD user caps; never touches VRAM targets), budget-gated (`TextureFitsInRAMBudget`), skips already-satisfied models, new tiny public wrapper `AsyncTextureUpdater::QueueRAMOnlyUpdate` reusing the proven queue machinery (512-limit, dedupe). Doxygen rewritten. Caller wiring honest + limited: no "about to switch" signal exists in the codebase — wired to scene-combo hover in SceneTree (`GUI_Window_SceneTree.cpp:70-73`), documented as opportunistic. Follow-up: a SceneManager "predicted next scene" API is the right extension point (SceneManager currently has no ModelLoader dependency — not abused) |
| P4.4 | High-LOD texture auto-unload over RAM/VRAM thresholds (`AssetStreamingManager.cpp:232` todo) integrated with ResourceMonitor budgets | fixed | `ReduceTextureTargetsUnderMemoryPressure` at end of `CheckHardwareLimitations`( replaces `// todo`): warning-threshold trigger, far-from-camera-first one-level-at-a-time target lowering to LOD floors until deficit covered; hysteresis (enter at warning, exit at 1.25× warning; shrink-only, distance sizing re-raises naturally — no ping-pong); one `SortModels` call actuates the proven downward `SetLevel*}_{RAM,VRAM}` passes same-frame; edge-triggered logs. Inert under normal memory (0 hits in smoke logs, as designed) |

## Final verification

- [x] Clean build after last change — **passed** (from-scratch: `rm -rf Build`, fresh cmake configure + Debug build of target ERS, exit 0, 132 s, `[100%] Built target ERS`)
- [x] This ledger has no `pending` entries without a reason — all rows are fixed / verified / noted / not-implemented-with-reason
- [x] Final headless run on the clean binary — `DISPLAY=:0 timeout -k 8 30 ./ERS -Headless true` → alive full 30 s (EXIT=124 by timeout), "Headless Mode Enabled", "Starting BrainGenix-ERS Instance" main loop reached, "Finished Decoding Scene", zero segfault/fatal/assert matches in log

**Disposition — goal closed.** Total: ~50 files changed, ~20 new files (modals, SceneDecoderV7, docs), −1633 net lines (Python residue), 38 ledger items across Phase 1/2/3 each with build evidence or a written reason.

## Goal 2 (Phase 4) final verification

- [x] Fresh clean from-scratch build (new empty `Build/`, Debug, target ERS) — exit 0, 132 s
- [x] `-Headless true` on display — EXIT=124, main loop reached
- [x] **Display-free offscreen** (`env -u DISPLAY ./ERS -Headless offscreen`) — EXIT=124, main loop reached, "Selected EGL Platform For Offscreen Rendering: EGL_EXT_platform_device, device 0, EGL 1.5"
- [x] Graceful failure — no display, no flags → EXIT=1 with fatal log, no segfault (baseline was exit 139)
- [x]driver caveat recorded: NVIDIA EGL device-platform shader-link defect (C6020) with `-EGLDeviceIndex` mitigation; Intel iGPU/Mesa device fully clean (0 GL errors); standalone repro in /tmp/egl-*

**Disposition — goal 2 closed.** P4.1–P4.4 all fixed (P4.2 with documented driver caveat; P4.3 with honest limited-wiring note). README "Running Headless (Display-Free Offscreen Rendering)" documents the modes.
