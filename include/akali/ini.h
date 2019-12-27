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

#ifndef AKALI_INI_H_
#define AKALI_INI_H_
#pragma once

#if (defined _WIN32 || defined WIN32)
#include <tchar.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "akali/stringencode.h"
#include "akali_export.h"

namespace akali {
class AKALI_API Ini {
public:
  Ini();
  virtual ~Ini();

public:
  void SetIniFilePath(LPCWSTR pszIniFile);
  LPCWSTR GetIniFilePath();

public:
  bool ReadRect(LPCWSTR pszItem, LPCWSTR pszSubItem, RECT &ValueRect);
  bool ReadSize(LPCWSTR pszItem, LPCWSTR pszSubItem, SIZE &ValueSize);
  bool ReadPoint(LPCWSTR pszItem, LPCWSTR pszSubItem, POINT &ValuePoint);
  bool ReadColor(LPCWSTR pszItem, LPCWSTR pszSubItem, COLORREF &ValueColor);
  bool ReadInt(LPCWSTR pszItem, LPCWSTR pszSubItem, UINT &ValueInt);
  LPCWSTR ReadString(LPCWSTR pszItem, LPCWSTR pszSubItem, LPCWSTR pszDefault, LPTSTR pszString,
                     WORD wMaxCount);
  bool ReadString(LPCWSTR pszItem, LPCWSTR pszSubItem, std::wstring &strString);
  bool WriteString(LPCWSTR pszItem, LPCWSTR pszSubItem, LPCWSTR ValueString);
  bool WriteString(LPCWSTR pszItem, LPCWSTR pszSubItem, const std::wstring &ValueString);
  bool WriteInt(LPCWSTR pszItem, LPCWSTR pszSubItem, LONG ValueInt);
  bool WriteRGBColor(LPCWSTR pszItem, LPCWSTR pszSubItem, COLORREF ValueColor);
  bool WritePoint(LPCWSTR pszItem, LPCWSTR pszSubItem, POINT ValuePoint);
  bool WriteSize(LPCWSTR pszItem, LPCWSTR pszSubItem, SIZE ValueSize);
  bool WriteRect(LPCWSTR pszItem, LPCWSTR pszSubItem, RECT ValueRect);

protected:
  LONG SwitchStringToValue(LPCWSTR &pszSring);

protected:
  WCHAR m_szIniFile[MAX_PATH];
};
} // namespace akali
#endif
#endif // !AKALI_INI_H_
