#pragma once

/*
typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
*/

typedef char int8;
typedef short int16;
typedef long int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

#include <string>

typedef uint32 UnicodeChar;

typedef std::basic_string<UnicodeChar> UnicodeString;
typedef std::basic_string_view<UnicodeChar> UnicodeStringView;

typedef std::string UTF8String;
typedef std::string_view UTF8StringView;