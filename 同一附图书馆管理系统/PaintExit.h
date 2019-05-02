#pragma once
#include<windows.h>
#include"Global.h"

BOOL PaintExitButton(HDC hdc, int x, int y, int cx, int cy)
{
	POINT pt;
	HPEN hPen = CreatePen(PS_SOLID, 1.41*STRETCH, RGB(255, 255, 255));
	HDC hdcMem = GetMemDC(hdc, cx*STRETCH, cy*STRETCH);


	SetStretchBltMode(hdc, HALFTONE);
	SetStretchBltMode(hdcMem, HALFTONE);
	StretchBlt(hdcMem, 0, 0, cx*STRETCH, cy*STRETCH, hdc, x, y, cx, cy, SRCCOPY);


	SelectObject(hdcMem, hPen);
	
	MoveToEx(hdcMem, cx*STRETCH * 7 / 16, cy*STRETCH * 1 / 4, NULL);
	LineTo(hdcMem, cx*STRETCH * 1 / 4, cy*STRETCH * 1 / 4);
	LineTo(hdcMem, cx*STRETCH * 1 / 4, cy*STRETCH * 3 / 4);
	LineTo(hdcMem, cx*STRETCH * 7 / 16, cy*STRETCH * 3 / 4);

	MoveToEx(hdcMem, cx*STRETCH * 3 / 8, cy*STRETCH * 1 / 2, NULL);
	LineTo(hdcMem, cx*STRETCH * 3 / 4, cy*STRETCH * 1 / 2);

	LineTo(hdcMem, cx*STRETCH * 5 / 8, cy*STRETCH * 3 / 8);

	MoveToEx(hdcMem, cx*STRETCH * 3 / 4, cy*STRETCH * 1 / 2, NULL);

	LineTo(hdcMem, cx*STRETCH * 5 / 8, cy*STRETCH * 5 / 8);

	StretchBlt(hdc, x, y, cx, cy, hdcMem, 0, 0, cx*STRETCH, cy*STRETCH, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hPen);
}