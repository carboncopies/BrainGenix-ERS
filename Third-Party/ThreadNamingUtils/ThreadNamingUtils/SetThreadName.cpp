// Simple library to help manage thread names

#include <SetThreadName.h>



#ifdef _WIN32
#pragma pack(push,8)
    typedef struct tagTHREADNAME_INFO {
    DWORD  dwType;     // Must be 0x1000.
    LPCSTR szName;     // Pointer to name (in user addr space).
    DWORD  dwThreadID; // Thread ID (-1=caller thread).
    DWORD  dwFlags;    // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void SetThreadName(uint32_t dwThreadID, std::string ThreadName) {
    SetThreadName(dwThreadID, ThreadName.c_str());
}
void SetThreadName(std::string ThreadName) {
    SetThreadName(ThreadName.c_str());
}
void SetThreadName(const char* ThreadName) {
    DWORD dwThreadID = ::GetThreadId( static_cast<HANDLE>( t.native_handle() ) );
    SetThreadName(dwThreadID, ThreadName)
}
void SetThreadName(uint32_t dwThreadID, const char* ThreadName) {
    THREADNAME_INFO Info;
    Info.dwType     = 0x1000;
    Info.szName     = ThreadName;
    Info.dwThreadID = dwThreadID;
    Info.dwFlags    = 0;

    __try {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof(Info)/sizeof(ULONG_PTR), (ULONG_PTR*)&Info );
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
    }
}
void SetThreadName(const char* ThreadName) {
    SetThreadName(GetCurrentThreadId(),ThreadName);
}

void SetThreadName(std::thread* thread, const char* ThreadName) {
    DWORD threadId = ::GetThreadId( static_cast<HANDLE>( thread->native_handle() ) );
    SetThreadName(threadId,ThreadName);
}

#elif defined(__linux__)
void SetThreadName(std::string ThreadName) {
    SetThreadName(ThreadName.c_str());
}
void SetThreadName(const char* ThreadName) {
    prctl(PR_SET_NAME,ThreadName,0,0,0);
}
#else
void SetThreadName(std::string ThreadName) {
    SetThreadName(ThreadName.c_str());
}
void SetThreadName(std::thread* thread, const char* ThreadName) {
    auto handle = thread->native_handle();
    pthread_setname_np(handle,ThreadName);
}
#endif