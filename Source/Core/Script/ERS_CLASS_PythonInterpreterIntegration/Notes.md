# About
This document aims to discuss the potential ways we can proceed with ERS Scripting - it discusses the various methods including extending the python API versus removing the python API and replacing it with a C++ API and a JIT (just in time compiler) for dynamic compilation.

Either way, the plan outlined here will only be complete when a fully-functional scripting system has been developed that allows the user to build a fully-functional script (moving camera based on user input, altering scene, changing engine behavior, etc.)


# Main Paths

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



## Replacing Python with a C++ like Scripting Language (Selected)
This section discusses replacing the python API with a c++ (like) API that has been specifically designed for scripting.

### Challenges
Some of the challenges that would potentially be faced are listed below:

- Selecting a scripting API
 - There are a *lot* of scripting APIs, so finding the best one is challenging.
 - Kind of a double-edged issue, as this also means there are a lot of options, so we could pick one that very closely matches our needs.
- User base
 - Since there are so many scirpting APIs, users will likely have to learn the language from scratch
 - However, we can pick one that's super easy to pick up, mostly eliminating this issue.
- Unknown variables
 - Given that we have not yet selected one scripting API, the performance and limitations are as of yet unknown.
 - We would need to be careful to pick a system that is going to meet our needs for performance.


### Benefits
Some of the benefits are discussed below:
- Ease of integration
 - The language has been designed to be used as a scripting platform, so it's going to be pretty good at it's job (hopefully)
 - No messing around with JITs or the Python interpreter.
 - Hopefully easy to expose ERS functionality
- Platform Consitency
 - Since the code to compile/run or just run the scripts is included in the ERS codebase, the user should not have to install anything.


# Analysis On Selected Approach
Given the significant and non-trivial issues with the other two systems, it indicates that the preferred solution is a scripting language. Now, the challenge is to identify the best language to use for the job. Currently, that language seems to be AngelScript, as it has been designed to be used in real-time rendering applications.


According to it's website, the language has the following features:

## Script language

    - Familiar syntax - The script syntax is similar to that of C or C++, with only a few differences.
    - Statically typed - Unlike most scripting languages that are dynamically typed this one uses the same static types as C++, and applications can register additional types.
    - Object oriented - The script language allows for declaration of classes, with support for single inheritance and polymorphism through interfaces.
    - Object handles - Pointers are not safe in a scripted environment, so AngelScript uses object handles instead. Object handles are almost like smart pointers, that control the life time of the object they hold.
    - Sandboxing - The library provides a secure environment for the scripts, i.e. the scripts can only access what the application explicitly exposes, and any built-in script objects are completely secure.
    - International support - The script files can be encoded in ASCII or UTF-8. String constants can include UTF-8 encoded characters directly or can use escape sequences to add specific unicode code points. UTF-16 encoded string literals is also supported. 

## Engine

    - Run-time compiled - The library compiles the scripts into byte code and executes the byte code through a virtual machine.
    - Step by step execution - The scripts may be executed line by line, for controlled execution and debugging.
    - Detailed exceptions - When an exception occurs information about why and where can easily be obtained.
    - Line interpretation - The engine can interpret separate script lines using the currently compiled script. Useful for in-game consoles.
    - Saving/loading byte code - The compiled bytecode can be saved and reloaded at a later time. The bytecode is platform independent.
    - Modular - Scripts can be compiled into modules that can be dynamically linked with each other.
    - Concurrent scripts - Several scripts can be executed in parallel, by suspending and resuming them one by one. This allows for easy implementation of multi-tasking schemes, or even co-routines.
    - Debugging support - The application can examine the call stack and the value of local variables while running the scripts. The line callback feature allows the application to use breakpoints, do profiling, etc.
    - Real-time capable - The execution time is deterministic and doesn't vary. 

## Integration

    - Direct access - The script engine can directly access and use registered functions, objects, and object members without the need to write proxy functions (where native calling conventions are supported).
    - C++ interface - The standard application interface is C++, but a C interface can easily be written that can be used by languages that don't interact well with C++ interfaces. It has for example successfully been used in Delphi projects.
    - Multithreading - The library can be used in a multithreaded environment.
    - Memory management - Objects are reference counted for easy management of objects that pass between script and application. An iterative garbage collector is used where circular references can occur. The application can also completely control the library's memory usage. 

## Portability

    - Cross platform - It has been confirmed to work on Windows, Linux, MacOS X, XBox, XBox 360, XBox One, PS2, PSP, PS3, PS4, PS Vita, Dreamcast, Nintendo DS, Windows Mobile, iPhone, BSD, and Android.
    - CPU independent - Both 32bit and 64bit platforms are supported. Both big endian and little endian CPUs are supported. Confirmed CPUs: x86, amd64, sh4, mips, ppc, ppc64, arm, s390x.
    - Compiler support - It works with MSVC++, GNUC, MinGW, DJGPP, Borland C++ Builder. Other compilers haven't been formally tested but are likely to work as well.
    - Native calling conventions - The library support native calling conventions, i.e. without the need for wrappers on the following configurations and other compatible ones:
        - Win32 - MSVC - x86
        - Win32 - MinGW - x86
        - Win32 CE - MSVC - arm
        - Win64 - MSVC - x86/64
        - Win64 - MinGW - x86/64
        - Linux - GNUC - x86
        - Linux - GNUC - x86/64
        - Linux - GNUC - arm/arm64
        - Linux - GNUC - mips
        - MacOS X - GNUC - x86
        - MacOS X - GNUC - x86/64
        - MacOS X - GNUC - ppc
        - iOS - GNUC - arm
        - BSD - GNUC - x86
        - BSD - GNUC - x86/64
        - Dreamcast - GNUC - sh4
        - PSP - GNUC - mips
        - PS2 - GNUC - mips
        - PS3 - GNUC - ppc/64
        - PS4 - GNUC - x86/64
        - PS Vita - GNUC - arm
        - XBox - MSVC - x86
        - XBox 360 - MSVC - ppc/64
        - XBox One - MSVC - x86/64
        - Android - GNUC - arm/arm64
        - Android - GNUC - mips
        - Haiku - GNUC - x86 
    - Maximum portability mode - When the library is compiled in this mode it should work on just about any compiler/platform that can compile standard compliant C++ code. Some features like native calling conventions are not available in this mode.
    - Cross language - With the flat C interface, other languages, such as Delphi, are also able to use the library. The library has also been successfully integrated in .NET based applications through the C++ interface. It is has even been used in web applications by compiling it with emscripten and Chome PNaCl. 

## Other

    - No costs - The scripting library is completely free for all use, though donations are appreciated.
    - Well documented - Both the script language and library is fully documented. 

## Analysis on language/features
LuaJIT seems to be the best platform for this task. Given it's performance according to various benchmarks, it vastly exceeds that of AngelScript, and in addtion, it has a much larger userbase given that of the Lua Community.

~~Other scripting languages do have some of the same features, and their own benefits, however this language seems to be well-tested in industry and has extensive documentation. Additionally, it's syntax is so similar to C++ that the learning curve should be very small for existing C++/C developers.

In addition to that, the system seems to support multithreading well, which is very critical given the design goals of ERS (very heavily threaded, should scale well on servers with 256 cores, very minimal single-threaded performance requirements).

In conclusion, I feel that the most efficent way forwards will be using AngelScript with ERS, and replacing the Python API in favor of this.~~




# Plan

The development plan is broken into the following sections:

### 1. Sandbox Test
Create a test sandbox with the LuaJIT system, allowing us to have a minimal working example with cmake.

### 2. Remove Python System
Remove the python scripting system, and all associated code to simplify everything.

### 3. Integrate LuaJIT
Create a new directory in the interface system, and create the associated system components to add the new scripting system.