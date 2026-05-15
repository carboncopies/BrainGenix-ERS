//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

namespace ERS::Editor::Localization {

enum class Language {
    English = 0,
    French,
    Russian,
    Chinese
};

enum class TextID {
    File,
    New,
    Open,
    Save,
    ProjectSettings,
    About,
    ImportModel,
    ImportModelsInDirectory,
    Exit,

    Window,
    Windows,
    SceneTree,
    SystemLog,
    AssetExplorer,
    ObjectProperties,
    Framerate,
    FramerateCounter,
    FramerateHistogram,
    FramerateGraph,
    FrameratePlot,
    FrameLatencyGraph,
    SystemResources,
    RAM,
    Viewport,
    AddViewport,
    RemoveViewport,
    ScriptEditor,
    ShaderEditor,

    Settings,
    ColorTheme,
    SystemFont,
    Language,
    EditorSettings,
    EditorCameraSettings,
    EngineSettings,
    RenderingSettings,
    AssetStreamingSettings,
    GameControllers,
    DetectNewControllers,
    GameControllerSettings,

    Debug,
    ImGuiDemoWindow,
    TestEditorWindow,
    InduceSegmentationFault,
    WindowManagerDebugging,
    ShowAllWindows,
    HideAllWindows,
    InvertWindowStates,
    OpenGLDebugging,
    DebuggingEnabled,
    GLSources,
    GLTypes,
    GLSeverity
};

inline Language ActiveLanguage = Language::English;

inline const char* GetLanguageName(int Index) {
    switch ((Language)Index) {
        case Language::English:
            return "English";
        case Language::French:
            return "Français";
        case Language::Russian:
            return "Русский";
        case Language::Chinese:
            return "中文";
    }
    return "English";
}

inline int GetLanguageCount() {
    return 4;
}

inline int GetActiveLanguageIndex() {
    return (int)ActiveLanguage;
}

inline void SetActiveLanguageFromIndex(int Index) {
    if (Index >= 0 && Index < GetLanguageCount()) {
        ActiveLanguage = (Language)Index;
    }
}

inline const char* GetEnglish(TextID ID) {
    switch (ID) {
        case TextID::File:                    return "File";
        case TextID::New:                     return "New";
        case TextID::Open:                    return "Open";
        case TextID::Save:                    return "Save";
        case TextID::ProjectSettings:         return "Project Settings";
        case TextID::About:                   return "About";
        case TextID::ImportModel:             return "Import Model";
        case TextID::ImportModelsInDirectory: return "Import Models In Directory";
        case TextID::Exit:                    return "Exit";

        case TextID::Window:                  return "Window";
        case TextID::Windows:                 return "Windows";
        case TextID::SceneTree:               return "Scene Tree";
        case TextID::SystemLog:               return "System Log";
        case TextID::AssetExplorer:           return "Asset Explorer";
        case TextID::ObjectProperties:        return "Object Properties";
        case TextID::Framerate:               return "Framerate";
        case TextID::FramerateCounter:        return "Framerate Counter";
        case TextID::FramerateHistogram:      return "Framerate Histogram";
        case TextID::FramerateGraph:          return "Framerate Graph";
        case TextID::FrameratePlot:           return "Framerate Plot";
        case TextID::FrameLatencyGraph:       return "Frame Latency Graph";
        case TextID::SystemResources:         return "System Resources";
        case TextID::RAM:                     return "RAM";
        case TextID::Viewport:                return "Viewport";
        case TextID::AddViewport:             return "Add Viewport";
        case TextID::RemoveViewport:          return "Remove Viewport";
        case TextID::ScriptEditor:            return "Script Editor";
        case TextID::ShaderEditor:            return "Shader Editor";

        case TextID::Settings:                return "Settings";
        case TextID::ColorTheme:              return "Color Theme";
        case TextID::SystemFont:              return "System Font";
        case TextID::Language:                return "Language";
        case TextID::EditorSettings:          return "Editor Settings";
        case TextID::EditorCameraSettings:    return "Editor Camera Settings";
        case TextID::EngineSettings:          return "Engine Settings";
        case TextID::RenderingSettings:       return "Rendering Settings";
        case TextID::AssetStreamingSettings:  return "Asset Streaming Settings";
        case TextID::GameControllers:         return "Game Controllers";
        case TextID::DetectNewControllers:    return "Detect New Controllers";
        case TextID::GameControllerSettings:  return "Game Controller Settings";

        case TextID::Debug:                   return "Debug";
        case TextID::ImGuiDemoWindow:         return "ImGui Demo Window";
        case TextID::TestEditorWindow:        return "Test Editor Window";
        case TextID::InduceSegmentationFault: return "Induce Segmentation Fault";
        case TextID::WindowManagerDebugging:  return "Window Manager Debugging";
        case TextID::ShowAllWindows:          return "Show All Windows";
        case TextID::HideAllWindows:          return "Hide All Windows";
        case TextID::InvertWindowStates:      return "Invert Window States";
        case TextID::OpenGLDebugging:         return "OpenGL Debugging";
        case TextID::DebuggingEnabled:        return "Debugging Enabled";
        case TextID::GLSources:               return "GL Sources";
        case TextID::GLTypes:                 return "GL Types";
        case TextID::GLSeverity:              return "GL Severity";
    }
    return "";
}

inline const char* GetFrench(TextID ID) {
    switch (ID) {
        case TextID::File:                    return "Fichier";
        case TextID::New:                     return "Nouveau";
        case TextID::Open:                    return "Ouvrir";
        case TextID::Save:                    return "Enregistrer";
        case TextID::ProjectSettings:         return "Paramètres du projet";
        case TextID::About:                   return "À propos";
        case TextID::ImportModel:             return "Importer un modèle";
        case TextID::ImportModelsInDirectory: return "Importer les modèles du dossier";
        case TextID::Exit:                    return "Quitter";

        case TextID::Window:                  return "Fenêtre";
        case TextID::Windows:                 return "Fenêtres";
        case TextID::SceneTree:               return "Arborescence de scène";
        case TextID::SystemLog:               return "Journal système";
        case TextID::AssetExplorer:           return "Explorateur d'actifs";
        case TextID::ObjectProperties:        return "Propriétés de l'objet";
        case TextID::Framerate:               return "Fréquence d'images";
        case TextID::FramerateCounter:        return "Compteur FPS";
        case TextID::FramerateHistogram:      return "Histogramme FPS";
        case TextID::FramerateGraph:          return "Graphique FPS";
        case TextID::FrameratePlot:           return "Courbe FPS";
        case TextID::FrameLatencyGraph:       return "Latence d'image";
        case TextID::SystemResources:         return "Ressources système";
        case TextID::RAM:                     return "RAM";
        case TextID::Viewport:                return "Vue";
        case TextID::AddViewport:             return "Ajouter une vue";
        case TextID::RemoveViewport:          return "Supprimer une vue";
        case TextID::ScriptEditor:            return "Éditeur de scripts";
        case TextID::ShaderEditor:            return "Éditeur de shaders";

        case TextID::Settings:                return "Paramètres";
        case TextID::ColorTheme:              return "Thème de couleur";
        case TextID::SystemFont:              return "Police système";
        case TextID::Language:                return "Langue";
        case TextID::EditorSettings:          return "Paramètres de l'éditeur";
        case TextID::EditorCameraSettings:    return "Paramètres de caméra";
        case TextID::EngineSettings:          return "Paramètres du moteur";
        case TextID::RenderingSettings:       return "Paramètres de rendu";
        case TextID::AssetStreamingSettings:  return "Paramètres de streaming";
        case TextID::GameControllers:         return "Manettes";
        case TextID::DetectNewControllers:    return "Détecter les manettes";
        case TextID::GameControllerSettings:  return "Paramètres des manettes";

        case TextID::Debug:                   return "Débogage";
        case TextID::ImGuiDemoWindow:         return "Fenêtre de démonstration ImGui";
        case TextID::TestEditorWindow:        return "Fenêtre d'éditeur de test";
        case TextID::InduceSegmentationFault: return "Provoquer une erreur mémoire";
        case TextID::WindowManagerDebugging:  return "Débogage du gestionnaire de fenêtres";
        case TextID::ShowAllWindows:          return "Afficher toutes les fenêtres";
        case TextID::HideAllWindows:          return "Masquer toutes les fenêtres";
        case TextID::InvertWindowStates:      return "Inverser les états";
        case TextID::OpenGLDebugging:         return "Débogage OpenGL";
        case TextID::DebuggingEnabled:        return "Débogage activé";
        case TextID::GLSources:               return "Sources GL";
        case TextID::GLTypes:                 return "Types GL";
        case TextID::GLSeverity:              return "Gravité GL";
    }
    return GetEnglish(ID);
}

inline const char* GetRussian(TextID ID) {
    switch (ID) {
        case TextID::File:                    return "Файл";
        case TextID::New:                     return "Новый";
        case TextID::Open:                    return "Открыть";
        case TextID::Save:                    return "Сохранить";
        case TextID::ProjectSettings:         return "Настройки проекта";
        case TextID::About:                   return "О программе";
        case TextID::ImportModel:             return "Импорт модели";
        case TextID::ImportModelsInDirectory: return "Импорт моделей из папки";
        case TextID::Exit:                    return "Выход";

        case TextID::Window:                  return "Окно";
        case TextID::Windows:                 return "Окна";
        case TextID::SceneTree:               return "Дерево сцены";
        case TextID::SystemLog:               return "Системный журнал";
        case TextID::AssetExplorer:           return "Обозреватель ресурсов";
        case TextID::ObjectProperties:        return "Свойства объекта";
        case TextID::Framerate:               return "Частота кадров";
        case TextID::FramerateCounter:        return "Счётчик FPS";
        case TextID::FramerateHistogram:      return "Гистограмма FPS";
        case TextID::FramerateGraph:          return "График FPS";
        case TextID::FrameratePlot:           return "Кривая FPS";
        case TextID::FrameLatencyGraph:       return "Задержка кадра";
        case TextID::SystemResources:         return "Системные ресурсы";
        case TextID::RAM:                     return "ОЗУ";
        case TextID::Viewport:                return "Область просмотра";
        case TextID::AddViewport:             return "Добавить область";
        case TextID::RemoveViewport:          return "Удалить область";
        case TextID::ScriptEditor:            return "Редактор скриптов";
        case TextID::ShaderEditor:            return "Редактор шейдеров";

        case TextID::Settings:                return "Настройки";
        case TextID::ColorTheme:              return "Цветовая тема";
        case TextID::SystemFont:              return "Системный шрифт";
        case TextID::Language:                return "Язык";
        case TextID::EditorSettings:          return "Настройки редактора";
        case TextID::EditorCameraSettings:    return "Настройки камеры";
        case TextID::EngineSettings:          return "Настройки движка";
        case TextID::RenderingSettings:       return "Настройки рендеринга";
        case TextID::AssetStreamingSettings:  return "Настройки потоковой загрузки";
        case TextID::GameControllers:         return "Игровые контроллеры";
        case TextID::DetectNewControllers:    return "Найти новые контроллеры";
        case TextID::GameControllerSettings:  return "Настройки контроллеров";

        case TextID::Debug:                   return "Отладка";
        case TextID::ImGuiDemoWindow:         return "Демо-окно ImGui";
        case TextID::TestEditorWindow:        return "Тестовое окно редактора";
        case TextID::InduceSegmentationFault: return "Вызвать ошибку сегментации";
        case TextID::WindowManagerDebugging:  return "Отладка менеджера окон";
        case TextID::ShowAllWindows:          return "Показать все окна";
        case TextID::HideAllWindows:          return "Скрыть все окна";
        case TextID::InvertWindowStates:      return "Инвертировать состояния";
        case TextID::OpenGLDebugging:         return "Отладка OpenGL";
        case TextID::DebuggingEnabled:        return "Отладка включена";
        case TextID::GLSources:               return "Источники GL";
        case TextID::GLTypes:                 return "Типы GL";
        case TextID::GLSeverity:              return "Важность GL";
    }
    return GetEnglish(ID);
}

inline const char* GetChinese(TextID ID) {
    switch (ID) {
        case TextID::File:                    return "文件";
        case TextID::New:                     return "新建";
        case TextID::Open:                    return "打开";
        case TextID::Save:                    return "保存";
        case TextID::ProjectSettings:         return "项目设置";
        case TextID::About:                   return "关于";
        case TextID::ImportModel:             return "导入模型";
        case TextID::ImportModelsInDirectory: return "导入文件夹中的模型";
        case TextID::Exit:                    return "退出";

        case TextID::Window:                  return "窗口";
        case TextID::Windows:                 return "窗口列表";
        case TextID::SceneTree:               return "场景树";
        case TextID::SystemLog:               return "系统日志";
        case TextID::AssetExplorer:           return "资源浏览器";
        case TextID::ObjectProperties:        return "对象属性";
        case TextID::Framerate:               return "帧率";
        case TextID::FramerateCounter:        return "帧率计数器";
        case TextID::FramerateHistogram:      return "帧率直方图";
        case TextID::FramerateGraph:          return "帧率图";
        case TextID::FrameratePlot:           return "帧率曲线";
        case TextID::FrameLatencyGraph:       return "帧延迟图";
        case TextID::SystemResources:         return "系统资源";
        case TextID::RAM:                     return "内存";
        case TextID::Viewport:                return "视口";
        case TextID::AddViewport:             return "添加视口";
        case TextID::RemoveViewport:          return "移除视口";
        case TextID::ScriptEditor:            return "脚本编辑器";
        case TextID::ShaderEditor:            return "着色器编辑器";

        case TextID::Settings:                return "设置";
        case TextID::ColorTheme:              return "颜色主题";
        case TextID::SystemFont:              return "系统字体";
        case TextID::Language:                return "语言";
        case TextID::EditorSettings:          return "编辑器设置";
        case TextID::EditorCameraSettings:    return "编辑器相机设置";
        case TextID::EngineSettings:          return "引擎设置";
        case TextID::RenderingSettings:       return "渲染设置";
        case TextID::AssetStreamingSettings:  return "资源流式加载设置";
        case TextID::GameControllers:         return "游戏控制器";
        case TextID::DetectNewControllers:    return "检测新控制器";
        case TextID::GameControllerSettings:  return "游戏控制器设置";

        case TextID::Debug:                   return "调试";
        case TextID::ImGuiDemoWindow:         return "ImGui 演示窗口";
        case TextID::TestEditorWindow:        return "测试编辑器窗口";
        case TextID::InduceSegmentationFault: return "触发段错误";
        case TextID::WindowManagerDebugging:  return "窗口管理器调试";
        case TextID::ShowAllWindows:          return "显示所有窗口";
        case TextID::HideAllWindows:          return "隐藏所有窗口";
        case TextID::InvertWindowStates:      return "反转窗口状态";
        case TextID::OpenGLDebugging:         return "OpenGL 调试";
        case TextID::DebuggingEnabled:        return "启用调试";
        case TextID::GLSources:               return "GL 来源";
        case TextID::GLTypes:                 return "GL 类型";
        case TextID::GLSeverity:              return "GL 严重性";
    }
    return GetEnglish(ID);
}

inline const char* Get(TextID ID) {
    switch (ActiveLanguage) {
        case Language::English:
            return GetEnglish(ID);
        case Language::French:
            return GetFrench(ID);
        case Language::Russian:
            return GetRussian(ID);
        case Language::Chinese:
            return GetChinese(ID);
    }
    return GetEnglish(ID);
}

}
