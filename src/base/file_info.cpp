/*******************************************************************************
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

#include "base/file_info.h"
#ifdef _WIN32
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#pragma comment(lib, "Version.lib")

namespace ppx {
    namespace base {
        FileInfo::FileInfo() {
            Reset();
        }

        FileInfo::~FileInfo() {

        }

        bool FileInfo::GetTranslationId(LPVOID lpData, UINT unBlockSize, WORD wLangId, DWORD &dwId, BOOL bPrimaryEnough/*= FALSE*/) {
            LPWORD lpwData;

            for (lpwData = (LPWORD)lpData; (LPBYTE)lpwData < ((LPBYTE)lpData) + unBlockSize; lpwData += 2) {
                if (*lpwData == wLangId) {
                    dwId = *((DWORD *)lpwData);
                    return true;
                }
            }

            if (!bPrimaryEnough)
                return false;

            for (lpwData = (LPWORD)lpData; (LPBYTE)lpwData < ((LPBYTE)lpData) + unBlockSize; lpwData += 2) {
                if (((*lpwData) & 0x00FF) == (wLangId & 0x00FF)) {
                    dwId = *((DWORD *)lpwData);
                    return true;
                }
            }

            return false;
        }

        bool FileInfo::Create(HMODULE hModule) {
            TCHAR szBuf[MAX_PATH + 1] = { 0 };
            GetModuleFileName(hModule, szBuf, MAX_PATH);

            return Create(szBuf);
        }

        bool FileInfo::Create(const std::wstring &strFileName) {
            Reset();

            HANDLE hFile = CreateFileW(strFileName.c_str(), GENERIC_READ, 
                FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE) {
                return false;
            }


            printf("\n�ļ��ϴ�д��ʱ��\n");
            BOOL bRet = GetFileTime(hFile, &m_ftCreationTime, &m_ftLastAccessTime, &m_ftLastWriteTime);
            if (!bRet) {
                CloseHandle(hFile);
                return false;
            }
            CloseHandle(hFile);
            hFile = INVALID_HANDLE_VALUE;

            DWORD   dwHandle;
            DWORD   dwFileVersionInfoSize = GetFileVersionInfoSize(strFileName.c_str(), &dwHandle);

            if (!dwFileVersionInfoSize)
                return false;

            LPVOID  lpData = (LPVOID)(new BYTE[dwFileVersionInfoSize]);

            if (!lpData)
                return false;

            try {
                if (!GetFileVersionInfo((LPTSTR)strFileName.c_str(), dwHandle, dwFileVersionInfoSize, lpData))
                    return false;

                LPVOID  lpInfo;
                UINT    unInfoLen;

                if (VerQueryValue(lpData, _T("\\"), &lpInfo, &unInfoLen)) {
                    if (unInfoLen == sizeof(m_FileInfo))
                        memcpy(&m_FileInfo, lpInfo, unInfoLen);
                }

                VerQueryValue(lpData, _T("\\VarFileInfo\\Translation"), &lpInfo, &unInfoLen);

                DWORD   dwLangCode = 0;

                if (!GetTranslationId(lpInfo, unInfoLen, GetUserDefaultLangID(), dwLangCode, FALSE)) {
                    if (!GetTranslationId(lpInfo, unInfoLen, GetUserDefaultLangID(), dwLangCode, TRUE)) {
                        if (!GetTranslationId(lpInfo, unInfoLen, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), dwLangCode, TRUE)) {
                            if (!GetTranslationId(lpInfo, unInfoLen, MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL), dwLangCode, TRUE))
                                // use the first one we can get
                                dwLangCode = *((DWORD *)lpInfo);
                        }
                    }
                }

                TCHAR strSubBlock[MAX_PATH * 2] = { 0 };
                ZeroMemory(strSubBlock, MAX_PATH * 2 * sizeof(TCHAR));
                _stprintf_s(strSubBlock, _T("\\StringFileInfo\\%04X%04X\\"), dwLangCode & 0x0000FFFF, (dwLangCode & 0xFFFF0000) >> 16);

                TCHAR strTmp[MAX_PATH * 2] = { 0 };
                ZeroMemory(strTmp, MAX_PATH * 2 * sizeof(TCHAR));

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("CompanyName"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strCompanyName = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("FileDescription"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strFileDescription = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("FileVersion"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strFileVersion = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("InternalName"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strInternalName = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("LegalCopyright"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strLegalCopyright = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("OriginalFileName"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strOriginalFileName = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("ProductName"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strProductName = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("ProductVersion"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strProductVersion = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("Comments"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strComments = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("LegalTrademarks"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strLegalTrademarks = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("PrivateBuild"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strPrivateBuild = (LPCTSTR)lpInfo;

                _stprintf_s(strTmp, _T("%s%s"), strSubBlock, _T("SpecialBuild"));

                if (VerQueryValue(lpData, strTmp, &lpInfo, &unInfoLen))
                    m_strSpecialBuild = (LPCTSTR)lpInfo;

                delete[] lpData;
            } catch (...) {
                delete[] lpData;
                return false;
            }

            return true;
        }

        WORD FileInfo::GetFileVersion(int nIndex) const {
            switch (nIndex) {
                case 0:
                    return (WORD)(m_FileInfo.dwFileVersionLS & 0x0000FFFF);

                case 1:
                    return (WORD)((m_FileInfo.dwFileVersionLS & 0xFFFF0000) >> 16);

                case 2:
                    return (WORD)(m_FileInfo.dwFileVersionMS & 0x0000FFFF);

                case 3:
                    return (WORD)((m_FileInfo.dwFileVersionMS & 0xFFFF0000) >> 16);

                default:
                    return 0;
            }
        }


        WORD FileInfo::GetProductVersion(int nIndex) const {
            switch (nIndex) {
                case 0:
                    return (WORD)(m_FileInfo.dwProductVersionLS & 0x0000FFFF);

                case 1:
                    return (WORD)((m_FileInfo.dwProductVersionLS & 0xFFFF0000) >> 16);

                case 2:
                    return (WORD)(m_FileInfo.dwProductVersionMS & 0x0000FFFF);

                case 3:
                    return (WORD)((m_FileInfo.dwProductVersionMS & 0xFFFF0000) >> 16);

                default:
                    return 0;
            }
        }

        DWORD FileInfo::GetFileFlagsMask() const {
            return m_FileInfo.dwFileFlagsMask;
        }

        DWORD FileInfo::GetFileFlags() const {
            return m_FileInfo.dwFileFlags;
        }

        DWORD FileInfo::GetFileOs() const {
            return m_FileInfo.dwFileOS;
        }

        DWORD FileInfo::GetFileType() const {
            return m_FileInfo.dwFileType;
        }

        DWORD FileInfo::GetFileSubtype() const {
            return m_FileInfo.dwFileSubtype;
        }

        std::wstring FileInfo::GetCompanyName() {
            return m_strCompanyName;
        }

        std::wstring FileInfo::GetFileDescription() {
            return m_strFileDescription;
        }

        std::wstring FileInfo::GetFileVersion() {
            return m_strFileVersion;
        }

        std::wstring FileInfo::GetFileVersionEx() {
            wchar_t strTemp[MAX_PATH * 2] = { 0 };

            StringCchPrintfW(strTemp, MAX_PATH * 2, L"%d.%d.%d.%d", (m_FileInfo.dwFileVersionMS & 0xFFFF0000) >> 16,
                        (m_FileInfo.dwFileVersionMS & 0x0000FFFF),
                        (m_FileInfo.dwFileVersionLS & 0xFFFF0000) >> 16,
                        m_FileInfo.dwFileVersionLS & 0x0000FFFF);

            return strTemp;
        }

        std::wstring FileInfo::GetInternalName() {
            return m_strInternalName;
        }

        std::wstring FileInfo::GetLegalCopyright() {
            return m_strLegalCopyright;
        }

        std::wstring FileInfo::GetOriginalFileName() {
            return m_strOriginalFileName;
        }

        std::wstring FileInfo::GetProductName() {
            return m_strProductName;
        }

        std::wstring FileInfo::GetProductVersion() {
            return m_strProductVersion;
        }

        std::wstring FileInfo::GetComments() {
            return m_strComments;
        }

        std::wstring FileInfo::GetLegalTrademarks() {
            return m_strLegalTrademarks;
        }

        std::wstring FileInfo::GetPrivateBuild() {
            return m_strPrivateBuild;
        }

        std::wstring FileInfo::GetSpecialBuild() {
            return m_strSpecialBuild;
        }

        FILETIME FileInfo::GetCreationTime() const {
            return m_ftCreationTime;
        }

        FILETIME FileInfo::GetLastAccessTime() const {
            return m_ftLastAccessTime;
        }

        FILETIME FileInfo::GetLastWriteTime() const {
            return m_ftLastWriteTime;
        }

        void FileInfo::Reset() {
            ZeroMemory(&m_FileInfo, sizeof(m_FileInfo));
            m_strCompanyName.clear();
            m_strFileDescription.clear();
            m_strFileVersion.clear();
            m_strInternalName.clear();
            m_strLegalCopyright.clear();
            m_strOriginalFileName.clear();
            m_strProductName.clear();
            m_strProductVersion.clear();
            m_strComments.clear();
            m_strLegalTrademarks.clear();
            m_strPrivateBuild.clear();
            m_strSpecialBuild.clear();

            m_ftCreationTime.dwHighDateTime = m_ftCreationTime.dwLowDateTime = 0;
            m_ftLastAccessTime.dwHighDateTime = m_ftLastAccessTime.dwLowDateTime = 0;
            m_ftLastWriteTime.dwHighDateTime = m_ftLastWriteTime.dwLowDateTime = 0;
        }
    }
}
#endif