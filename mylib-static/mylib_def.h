#ifndef MYLIB_DEF_H_
#define MYLIB_DEF_H_
#include <inttypes.h>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>

#include "pch.h"

#define MYLIB_SPACE_NAME mylib
#define MYLIB_SPACE_BEGIN namespace MYLIB_SPACE_NAME {
#define MYLIB_SPACE_END }

//#define MYLIB_STATIC static
//#define MYLIB_THREAD thread_local
//#define MYLIB_CONST const;
//#define MYLIB_CONST_STATIC static const
// #define MYLIB_STATIC_THREAD MYLIB_STATIC MYLIB_THREAD

#ifdef _MSC_VER
#define MYLIB_MSVC _MSC_VER
#elif __GNUC__
#define MYLIB_GUN __GNUC__
#elif Clang
#define MYLIB_CLANG
#endif// _MSC_VER

MYLIB_SPACE_BEGIN

using int8 = signed char;
using int16 = signed short int;
using int32 = signed int;
using int64 = signed long long int;

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long int;

using float32 = float;
using float64 = double;
using CString = const char *;

using cid_t = uint32;//协程id类型
using size_t = uint64;
using weight_t = float32;

using String = std::string;
using SString = std::stringstream;

using time_t = ::time_t;//时间戳类型

MYLIB_SPACE_END

#endif// MYLIB_DEF_H_