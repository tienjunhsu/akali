#include "akali/trace.h"
#include <memory>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <strsafe.h>
#else
#include <string>
#include <stdarg.h>
#endif

namespace akali {

void TraceMsgW(const wchar_t *lpFormat, ...) {
  if (!lpFormat)
    return;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  wchar_t *pMsgBuffer = NULL;
  unsigned int iMsgBufCount = 0;

  va_list arglist;
  va_start(arglist, lpFormat);
  HRESULT hr = STRSAFE_E_INSUFFICIENT_BUFFER;

  while (hr == STRSAFE_E_INSUFFICIENT_BUFFER) {
    iMsgBufCount += 1024;

    if (pMsgBuffer) {
      free(pMsgBuffer);
      pMsgBuffer = NULL;
    }

    pMsgBuffer = (wchar_t *)malloc(iMsgBufCount * sizeof(wchar_t));

    if (!pMsgBuffer) {
      break;
    }

    hr = StringCchVPrintfW(pMsgBuffer, iMsgBufCount, lpFormat, arglist);
  }

  va_end(arglist);

  if (hr == S_OK) {
    if (pMsgBuffer)
      OutputDebugStringW(pMsgBuffer);
  }

  if (pMsgBuffer) {
    free(pMsgBuffer);
    pMsgBuffer = NULL;
  }
#else
  wchar_t msgBuf[1024] = {0};
  va_list arglist;
  va_start(arglist, lpFormat);
  int err = vswprintf(msgBuf, 1024, lpFormat, arglist);
  va_end(arglist);
  printf("%ls\n", msgBuf);
#endif
}

void TraceMsgA(const char *lpFormat, ...) {
  if (!lpFormat)
    return;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  char *pMsgBuffer = NULL;
  unsigned int iMsgBufCount = 0;

  va_list arglist;
  va_start(arglist, lpFormat);
  HRESULT hr = STRSAFE_E_INSUFFICIENT_BUFFER;

  while (hr == STRSAFE_E_INSUFFICIENT_BUFFER) {
    iMsgBufCount += 1024;

    if (pMsgBuffer) {
      free(pMsgBuffer);
      pMsgBuffer = NULL;
    }

    pMsgBuffer = (char *)malloc(iMsgBufCount * sizeof(char));

    if (!pMsgBuffer) {
      break;
    }

    hr = StringCchVPrintfA(pMsgBuffer, iMsgBufCount, lpFormat, arglist);
  }

  va_end(arglist);

  if (hr == S_OK) {
    if (pMsgBuffer)
      OutputDebugStringA(pMsgBuffer);
  }

  if (pMsgBuffer) {
    free(pMsgBuffer);
    pMsgBuffer = NULL;
  }
#else
  char msgBuf[1024] = {0};
  va_list arglist;
  va_start(arglist, lpFormat);
  int err = vsnprintf(msgBuf, 1024, lpFormat, arglist);
  va_end(arglist);
  printf("%s\n", msgBuf);
#endif
}
} // namespace akali