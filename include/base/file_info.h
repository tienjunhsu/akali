/*******************************************************************************
* Copyright (C) 2018 - 2020, Jeffery Jiang, <china_jeffery@163.com>.
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


#ifndef __FILE_INFO_SDFSDR54_H__
#define __FILE_INFO_SDFSDR54_H__
#pragma once

#ifdef _WIN32
#ifndef _INC_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif
#include <string>
#include "base/timeutils.h"
#include "ppx_export.h"

namespace ppx
{
    namespace base {
        class PPX_API FileInfo {
        public:
            FileInfo();
            ~FileInfo();

            bool Create(HMODULE hModule = NULL);
            bool Create(const std::wstring &strFileName);

        public:
            WORD GetFileVersion(int nIndex) const;
            WORD GetProductVersion(int nIndex) const;
            DWORD GetFileFlagsMask() const;
            DWORD GetFileFlags() const;
            DWORD GetFileOs() const;
            DWORD GetFileType() const;
            DWORD GetFileSubtype() const;

            std::wstring GetCompanyName();
            std::wstring GetFileDescription();
            std::wstring GetFileVersion();
            std::wstring GetFileVersionEx();
            std::wstring GetInternalName();
            std::wstring GetLegalCopyright();
            std::wstring GetOriginalFileName();
            std::wstring GetProductName();
            std::wstring GetProductVersion();
            std::wstring GetComments();
            std::wstring GetLegalTrademarks();
            std::wstring GetPrivateBuild();
            std::wstring GetSpecialBuild();

            // Windows���ļ�ʱ��Ϊһ��64λ��������FILETIME�ṹ��洢��,����¼��1601-1-1 00:00:00����ǰ��������ʱ�䣨UTC����������100����(ns)��
            // See: https ://blog.csdn.net/china_jeffery/article/details/78409614 
            //
            FILETIME GetCreationTime() const;
            FILETIME GetLastAccessTime() const;
            FILETIME GetLastWriteTime() const;

        private:
            virtual void Reset();
            bool GetTranslationId(LPVOID lpData, UINT unBlockSize, WORD wLangId, DWORD &dwId, BOOL bPrimaryEnough = FALSE);

        private:
            VS_FIXEDFILEINFO m_FileInfo;

            std::wstring m_strCompanyName;
            std::wstring m_strFileDescription;
            std::wstring m_strFileVersion;
            std::wstring m_strInternalName;
            std::wstring m_strLegalCopyright;
            std::wstring m_strOriginalFileName;
            std::wstring m_strProductName;
            std::wstring m_strProductVersion;
            std::wstring m_strComments;
            std::wstring m_strLegalTrademarks;
            std::wstring m_strPrivateBuild;
            std::wstring m_strSpecialBuild;

            FILETIME     m_ftCreationTime;
            FILETIME     m_ftLastAccessTime;
            FILETIME     m_ftLastWriteTime;
        };
    }
}
#endif

#endif // ! __FILE_INFO_SDFSDR54_H__