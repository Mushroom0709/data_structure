#ifndef _X_LIBRARY_COMMON_HPP_
#define _X_LIBRARY_COMMON_HPP_

#include <stdio.h>

//#define XLIBRARY_OUTPUT_DEBUG
#define XLIBRARY_OUTPUT_RELEASE
//#define XLIBRARY_OUTPUT_NONE

#ifdef XLIBRARY_OUTPUT_DEBUG

#define xPrintln(_FMT_,...) printf("[%s-%d] " _FMT_ "\n", __FILE__, __LINE__,##__VA_ARGS__)
#define xInfoPrintln(_FMT_,...) printf("[Info] [%s-%d] " _FMT_ "\n", __FILE__, __LINE__,##__VA_ARGS__)
#define xWaringPrintln(_FMT_,...) printf("[Waring] [%s-%d] " _FMT_ "\n", __FILE__, __LINE__,##__VA_ARGS__)
#define xErrorPrintln(_FMT_,...) printf("[Error] [%s-%d] " _FMT_ "\n", __FILE__, __LINE__,##__VA_ARGS__)

#define xPrint(_FMT_,...) printf("[%s-%d] " _FMT_ , __FILE__, __LINE__,##__VA_ARGS__)
#define xInfoPrint(_FMT_,...) printf("[Info] [%s-%d] " _FMT_, __FILE__, __LINE__,##__VA_ARGS__)
#define xWaringPrint(_FMT_,...) printf("[Waring] [%s-%d] " _FMT_, __FILE__, __LINE__,##__VA_ARGS__)
#define xErrorPrint(_FMT_,...) printf("[Error] [%s-%d] " _FMT_, __FILE__, __LINE__,##__VA_ARGS__)

#elif defined XLIBRARY_OUTPUT_RELEASE

#define xPrintln(_FMT_,...) printf(_FMT_ "\n",##__VA_ARGS__)
#define xInfoPrintln(_FMT_,...) printf("[Info] " _FMT_ "\n",##__VA_ARGS__)
#define xWaringPrintln(_FMT_,...) printf("[Waring] " _FMT_ "\n",##__VA_ARGS__)
#define xErrorPrintln(_FMT_,...) printf("[Error] " _FMT_ "\n",##__VA_ARGS__)

#define xPrint(_FMT_,...) printf(_FMT_,##__VA_ARGS__)
#define xInfoPrint(_FMT_,...) printf("[Info] " _FMT_,##__VA_ARGS__)
#define xWaringPrint(_FMT_,...) printf("[Waring] " _FMT_,##__VA_ARGS__)
#define xErrorPrint(_FMT_,...) printf("[Error] " _FMT_,##__VA_ARGS__)

#elif defined XLIBRARY_OUTPUT_NONE

#define xPrintln(_FMT_,...)
#define xInfoPrintln(_FMT_,...)
#define xWaringPrintln(_FMT_,...)
#define xPrintErrorln(_FMT_,...)

#define xPrint(_FMT_,...)
#define xInfoPrint(_FMT_,...)
#define xWaringPrint(_FMT_,...)
#define xErrorPrint(_FMT_,...)

#endif

#endif // !_X_LIBRARY_COMMON_HPP_