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

#ifndef PPX_BASE_PROCESS_UTIL_H_
#define PPX_BASE_PROCESS_UTIL_H_
#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include "ppx_export.h"

namespace ppx {
    namespace base {
        class PPX_API ProcessFinder {
          public:
			// If use default param, CreateToolhelp32Snapshot With dwFlags = TH32CS_SNAPALL, th32ProcessID = 0
			//
			ProcessFinder(DWORD dwFlags = 0, DWORD dwProcessID = 0);
            ~ProcessFinder();
            BOOL CreateSnapShot(DWORD dwFlag, DWORD dwProcessID);
            BOOL ProcessFirst(PPROCESSENTRY32 ppe) const;
            BOOL ProcessNext(PPROCESSENTRY32 ppe) const;
            // Don't forgot pe.dwSize = sizeof(PROCESSENTRY32);
            BOOL ProcessFind(DWORD dwProcessId, PPROCESSENTRY32 ppe) const;
            BOOL ProcessFind(PCTSTR pszExeName, PPROCESSENTRY32 ppe, BOOL bExceptSelf = false) const;
            BOOL ModuleFirst(PMODULEENTRY32 pme) const;
            BOOL ModuleNext(PMODULEENTRY32 pme) const;
            BOOL ModuleFind(PVOID pvBaseAddr, PMODULEENTRY32 pme) const;
            BOOL ModuleFind(PTSTR pszModName, PMODULEENTRY32 pme) const;
          private:
            HANDLE m_hSnapShot;
        };

        PPX_API BOOL RunAsAdministrator(LPCTSTR szCommand, LPCTSTR szArgs, BOOL bWaitProcess);
        PPX_API BOOL EnablePrivilege(LPCTSTR szPrivilege, BOOL fEnable);
        PPX_API BOOL CheckProcessUserIsAdmin(BOOL *pIsAdmin);
        PPX_API BOOL TerminateProcess(DWORD dwProcessId, DWORD dwExitCode);
        PPX_API BOOL TerminateProcess(LPCTSTR pszExeName, DWORD dwExitCode);

        // terminate all process that EXE file in szAppDir directory.
        PPX_API void RecursiveTerminateProcess(LPCTSTR szAppDir, bool exclude_self);

        PPX_API std::wstring GetCurrentProcessDirectoryW();
        PPX_API std::string GetCurrentProcessDirectoryA();
#if defined(UNICODE) || defined(_UNICODE)
#define GetCurrentProcessDirectory ppx::base::GetCurrentProcessDirectoryW
#else
#define GetCurrentProcessDirectory ppx::base::GetCurrentProcessDirectoryA
#endif

        PPX_API BOOL MakesureProcessSingleInstance(LPCTSTR pszUniqueName);

        // ���·���к��пո񣬱���ʹ��˫��������
        //
        PPX_API BOOL EasyCreateProcess(LPCTSTR szCmdLine, LPPROCESS_INFORMATION lpProcessInfo, BOOL bInheritHandles = FALSE);

        PPX_API BOOL CreateProcessInCurrentSession(PCTSTR pszFilePath);
    }
}

#endif

#endif // PPX_BASE_WIN_PROCESS_H_
