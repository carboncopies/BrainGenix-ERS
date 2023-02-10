# About

This document aims to discuss the potential ways we can proceed with ERS Scripting - it discusses the various methods including extending the python API versus removing the python API and replacing it with a C++ API and a JIT (just in time compiler) for dynamic compilation.

Either way, the plan outlined here will only be complete when a fully-functional scripting system has been developed that allows the user to build a fully-functional script (moving camera based on user input, altering scene, changing engine behavior, etc.)


## Extending Python API

This section discusses rewriting the python integration to expand the ERS API and enable more functionality including scene modification and modifying assets not directly attached to the script.

### Challenges

    