# ERS Internal Library: OpenGLLoggingSystem

## Description

The OpenGLLoggingSystem Collects user configurable information from the driver and logs it when needed. If there are errors or other issues, this subsystem records them. Collected items that pass the configured source/type/severity filters are also forwarded into the main log via the logging system, prefixed with "GL:" so they can be identified as OpenGL-originated; GL severities map to log levels (HIGH -> 8, MEDIUM -> 7, LOW -> 6, NOTIFICATION -> 4). Collection is off by default at startup and is enabled/disabled (along with the filters) from the editor's Debug menu. Modules using this subsystem may also get a list containing the log items collected here.