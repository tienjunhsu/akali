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

#include "base/criticalsection.h"

#ifdef _WIN32
namespace ppx {
    namespace base {
        CriticalSection::CriticalSection() {
            InitializeCriticalSection(&crit_);
        }
        CriticalSection::~CriticalSection() {
            DeleteCriticalSection(&crit_);
        }
        void CriticalSection::Enter() const {
            EnterCriticalSection(&crit_);
        }
        void CriticalSection::Leave() const {
            LeaveCriticalSection(&crit_);
        }

        bool CriticalSection::TryEnter() const {
            return TryEnterCriticalSection(&crit_) != FALSE;
        }

        CritScope::CritScope(const CriticalSection *pCS) : crit_(pCS) {
            crit_->Enter();
        }

        CritScope::~CritScope() {
            crit_->Leave();
        }
    }
}

#endif