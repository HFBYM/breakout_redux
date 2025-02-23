/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-22 21:35:57
 * @FilePath: \breakout_redux\src\utils\debug.h
 * Copyright (c) 2025 by Clare, All Rights Reserved. 
 */

#pragma once
#if defined(_MSC_VER)
    #define MDEBUG() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #define MDEBUG() __builtin_trap()
#else
    #error "ERROR::COMPILER: unsupported compiler"
#endif
#define Check()	check(__FILE__, __LINE__)    // check if any error before this line
#define ASSERT(x) if ( !( x ) ) MDEBUG()
namespace debug{
    void check(const char* file, int line);
    void clearError();
} // namespace debug
