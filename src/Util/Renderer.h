#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);
void DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3);
