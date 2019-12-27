﻿/*******************************************************************************
 * Copyright (C) 2018 - 2020, winsoft666, <winsoft666@outlook.com>.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Expect bugs
 *
 * Please use and enjoy. Please let me know of any bugs/improvements
 * that you have found/implemented and I will fix/incorporate them into this
 * file.
 *******************************************************************************/

#ifndef AKALI_STRINGENCODE_H_
#define AKALI_STRINGENCODE_H_
#include <assert.h>
#include <sstream>
#include <string>
#include <vector>
#include "akali_export.h"

namespace akali {

AKALI_API size_t UrlDecode(char *buffer, size_t buflen, const char *source, size_t srclen);
AKALI_API std::string UrlDecode(const std::string &source);
AKALI_API std::string UrlEncode(const std::string &str);

// Convert an unsigned value from 0 to 15 to the hex character equivalent...
AKALI_API char HexEncode(unsigned char val);
// ...and vice-versa.
AKALI_API bool HexDecode(char ch, unsigned char *val);

// hex_encode, but separate each byte representation with a delimiter.
// delimiter == 0 means no delimiter. If the buffer is too short, we return 0
AKALI_API size_t HexEncodeWithDelimiter(char *buffer, size_t buflen, const char *source,
                                          size_t srclen, char delimiter);

AKALI_API std::string HexEncode(const std::string &str);
AKALI_API std::string HexEncode(const char *source, size_t srclen);
AKALI_API std::string HexEncodeWithDelimiter(const char *source, size_t srclen, char delimiter);

// hex_decode, assuming that there is a delimiter between every byte pair.
// delimiter == 0 means no delimiter. If the buffer is too short or the data is invalid, we return 0.
AKALI_API size_t HexDecodeWithDelimiter(char *buffer, size_t buflen, const char *source,
                                          size_t srclen, char delimiter);

AKALI_API size_t HexDecode(char *buffer, size_t buflen, const std::string &source);
AKALI_API size_t HexDecodeWithDelimiter(char *buffer, size_t buflen, const std::string &source,
                                          char delimiter);

#if (defined _WIN32 || defined WIN32)
// About code_page, see
// https://docs.microsoft.com/zh-cn/windows/desktop/Intl/code-page-identifiers
//
AKALI_API std::string UnicodeToAnsi(const std::wstring &str, unsigned int code_page = 0);
AKALI_API std::wstring AnsiToUnicode(const std::string &str, unsigned int code_page = 0);
AKALI_API std::string UnicodeToUtf8(const std::wstring &str);
AKALI_API std::wstring Utf8ToUnicode(const std::string &str);
AKALI_API std::string AnsiToUtf8(const std::string &str, unsigned int code_page = 0);
AKALI_API std::string Utf8ToAnsi(const std::string &str, unsigned int code_page = 0);

AKALI_API std::string UnicodeToUtf8BOM(const std::wstring &str);
AKALI_API std::string AnsiToUtf8BOM(const std::string &str, unsigned int code_page = 0);

#if (defined UNICODE || defined _UNICODE)
#define TCHARToAnsi(str) akali::UnicodeToAnsi((str), 0)
#define TCHARToUtf8(str) akali::UnicodeToUtf8((str))
#define AnsiToTCHAR(str) akali::AnsiToUnicode((str), 0)
#define Utf8ToTCHAR(str) akali::Utf8ToUnicode((str))
#define TCHARToUnicode(str) ((std::wstring)(str))
#define UnicodeToTCHAR(str) ((std::wstring)(str))
#else
#define TCHARToAnsi(str) ((std::string)(str))
#define TCHARToUtf8 akali::AnsiToUtf8((str), 0)
#define AnsiToTCHAR(str) ((std::string)(str))
#define Utf8ToTCHAR(str) akali::Utf8ToAnsi((str), 0)
#define TCHARToUnicode(str) akali::AnsiToUnicode((str), 0)
#define UnicodeToTCHAR(str) akali::UnicodeToAnsi((str), 0)
#endif

#endif
} // namespace akali
#endif // AKALI_STRINGENCODE_H_
