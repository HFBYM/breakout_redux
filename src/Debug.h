#pragma once
#if defined(_MSC_VER)
    #define MDEBUG() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #define MDEBUG() __builtin_trap()
#else
    #error "ERROR::COMPILER: unsupported compiler"
#endif
#define Check()	check(__FILE__,__LINE__)	//check if any error before this line
#define ASSERT(x) if(!(x)) MDEBUG()
void check(const char* file, int line);
void clearError();
