# About
This document aims to discuss the potential ways we can proceed with ERS Scripting - it discusses the various methods including extending the python API versus removing the python API and replacing it with a C++ API and a JIT (just in time compiler) for dynamic compilation.

Either way, the plan outlined here will only be complete when a fully-functional scripting system has been developed that allows the user to build a fully-functional script (moving camera based on user input, altering scene, changing engine behavior, etc.)


## Extending Python API
This section discusses rewriting the python integration to expand the ERS API and enable more functionality including scene modification and modifying assets not directly attached to the script.

### Challenges
Some of the challenges that would potentially be faced are listed below:
- Performance
 - Expanding the API could lead to issues where the entire scene needs to be iterated through for every script, (to allow the script to access other objects in the scene), creating performance issues for large scenes
 - This would be made worse by python's GIL which prevents true multithreading. The only foreseeable solution to this would be running multiple python interpreters, however the binding library pybind11 doesn't officially support this (to my knowledge)
- Installation Issues
 - As it is already, many times the editor will crash or have issues with python binding if the user doesn't have the exactly right version of python or some slight configuration change.

### Benefits
Some of the benefits are discussed below:
- Large talent pool
 - Many people already know python, so the available number of people who could use it would be large
 - Additionally, python is easy to learn so people could pick it up quickly
- Less error-prone
 - Since python is a higher-level language, users would be less-likely to make mistakes leading to time wasted debugging


## Replacing Python with C++/JIT
This section discusses replacing the python API with a C++ API and compiling the code with a Just In Time compiler (JIT).

### Challenges
Some of the challenges that would potentially be faced are listed below:
- Finding a JIT
 - It seems that there are not very many C++ JITs so the options for this are limited
- JIT Dependencies
 - In addition to the poor selection of JITs, the issue is further exacerbated by the dependency hell that normally accompanies JITs
 - Many JITs require the user to install a regular compiler that the JIT uses on the backend.
 - Those that don't require this, aren't able to support the full C++ API.
- Cross Platform
 - It also seems that many of the JIT libraries are platform dependent (Windows only, Linux only, etc.)
 - This seems to be due to how JITs would have to work (dynamically loading compiled executables), which is an inherantly platform-specific task. For example, windows has DLL formats, and linux cannot use these.
- Poor documentation/Ease of integration
 - Since C++ JITs are a rather niche thing, we would potentially have a difficult time finding documentation for our use case, leading to extended development time.

### Benefits
Some of the benefits are discussed below:
- Performance
 - Due to C++'s design, there are no issues with multithreading, allowing scripts to be run in paralell on multiple cores. We would need to find a way to create multiple change lists to the scene that would be sync'd later on in the frame rendering process. The only potential issues here involve race conditions to this system which would cause issues where the system struggles with applying these changes in a timely manner. That issue however is outside the scope of this specific issue.
- Simplicity to extend API
 - Since the Engine is already implemented in C++, there would be minimal effort expanding the API to the rest of these systems as the code is already in C++



## Replacing Python with a C++ like Scripting Language
This section discusses replacing the python API with a c++ (like) API that has been specifically designed for scripting.

### Challenges
Some of the challenges that would potentially be faced are listed below:

### Benefits
Some of the benefits are discussed below: