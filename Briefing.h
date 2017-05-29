#pragma once

#define WIN32_LEAN_AND_MEAN

#include "resource.h"
#include "odasl\odasl.h"
#include <richedit.h>
#include <windows.h>

void ShowBriefing();
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);