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

#ifndef AKALI_H__
#define AKALI_H__
#pragma once

#include "akali/assert.h"
#include "akali/base64.h"
#include "akali/scoped_variant.h"
#include "akali/scoped_propvariant.h"
#include "akali/scoped_com_initializer.h"
#include "akali/buffer_queue.h"
#include "akali/byteorder.h"
#include "akali/cmdline_parse.h"
#include "akali/constructormagic.h"
#include "akali/criticalsection.h"
#include "akali/deprecation.h"
#include "akali/driver_info.h"
#include "akali/endianess_detect.h"
#include "akali/flags.h"
#include "akali/file_info.h"
#include "akali/file_util.h"
#include "akali/ini.h"
#include "akali/logging.h"
#include "akali/logging_file_sink_win.h"
#include "akali/md5.h"
#include "akali/memory_pool.hpp"
#include "akali/module_safe_string.h"
#include "akali/os_ver.h"
#include "akali/pc_info.h"
#include "akali/process_util.h"
#include "akali/process.hpp"
#include "akali/random.h"
#include "akali/registry.h"
#include "akali/string_helper.h"
#include "akali/safe_release_macro.h"
#include "akali/noncopyable.h"
#include "akali/singleton.h"
#include "akali/stringencode.h"
#include "akali/timer.h"
#include "akali/timeutils.h"
#include "akali/win_main.h"
#include "akali/win_service_base.h"
#include "akali/win_service_installer.h"
#include "akali/display_monitors.h"
#include "akali/schedule_task.h"
#include "akali/ipc.h"
#include "akali/miscellaneous.h"
#include "akali/shortcut.h"
#include "akali/host_resolve.h"
#include "akali/ipaddress.h"
#include "akali/networkprotocoldef.h"
#include "akali/ping.h"
#include "akali/socket.h"
#include "akali/socketaddress.h"
#include "akali/overlappedsocket.h"
#include "akali/iocp_socket.h"
#include "akali/iocpserver.h"
#include "akali/internet_availability_checker.h"
#include "akali/stack_walker.h"
#include "akali/directory_monitor.h"
#include "akali/thread.hpp"
#include "akali/thread_pool.hpp"

#if (defined WIN32 || defined _WIN32)
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "UserEnv.lib")
#pragma comment(lib, "DbgHelp.lib")
#endif

#endif // !AKALI_H__