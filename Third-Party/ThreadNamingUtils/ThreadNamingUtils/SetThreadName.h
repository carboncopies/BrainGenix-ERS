// Simple library to help manage thread names

#pragma once

#include <string>



// Based off of: https://stackoverflow.com/questions/10121560/stdthread-naming-your-thread
#ifdef _WIN32
#include <windows.h>
const DWORD MS_VC_EXCEPTION=0x406D1388;

void SetThreadName(uint32_t dwThreadID, std::string ThreadName);
void SetThreadName(std::string ThreadName);
void SetThreadName(const char* ThreadName);
void SetThreadName(uint32_t dwThreadID, const char* ThreadName);
void SetThreadName(const char* ThreadName);
void SetThreadName(std::thread* thread, const char* ThreadName);

#elif defined(__linux__)
#include <sys/prctl.h>

void SetThreadName(std::string ThreadName);
void SetThreadName(const char* ThreadName);

#else
void SetThreadName(std::string ThreadName);
void SetThreadName(std::thread* thread, const char* ThreadName);
#endif