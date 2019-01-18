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

#ifndef __MD5_MAKER_34DFDR7_H__
#define __MD5_MAKER_34DFDR7_H__
#pragma once

#include <string>
#include "ppx_export.h"

namespace ppx
{
    namespace base {
        namespace libmd5_internal {
            typedef unsigned int UWORD32;
            typedef unsigned char md5byte;

            struct MD5Context {
                UWORD32 buf[4];
                UWORD32 bytes[2];
                UWORD32 in[16];
            };

            PPX_API void MD5Init(struct MD5Context *context);
            PPX_API void MD5Update(struct MD5Context *context, md5byte const *buf, unsigned len);
            PPX_API void MD5Final(md5byte digest[16], struct MD5Context *context);
            PPX_API void MD5Buffer(const unsigned char *buf, unsigned int len, unsigned char sig[16]);
            PPX_API void MD5SigToString(unsigned char sig[16], char *str, int len);
        }

		// Helper function.
        PPX_API std::string GetStringMd5(const std::string &str);
        PPX_API std::string GetStringMd5(const void *buffer, unsigned int buffer_size);
        PPX_API std::string GetFileMd5(const std::string &file_path);
    }
}

#endif