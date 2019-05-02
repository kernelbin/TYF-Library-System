#pragma once

#include<windows.h>
#include"EasyWindow.h"
#include"Global.h"

BOOL PaintSmallButton(HDC hdc,int x,int y, int cx, int cy)
{
	HDC hdcMem;
	double i = 1.41;

	hdcMem = GetMemDC(hdc, cx * STRETCH, cy * STRETCH);
	SetStretchBltMode(hdcMem, HALFTONE);
	SetStretchBltMode(hdc, HALFTONE);
	StretchBlt(hdcMem, 0, 0, cx * STRETCH, cy * STRETCH, hdc, x, y, cx, cy, SRCCOPY);
	SelectObject(hdcMem, GetStockObject(WHITE_PEN));
	SelectObject(hdcMem, GetStockObject(WHITE_BRUSH));
	Rectangle(hdcMem, (int)(STRETCH * ((cx / 2)*RATIO)), (int)(STRETCH * ((cy*(2 - RATIO) / 2) - i / 2)), (int)(STRETCH * (cx - (cx / 2)*RATIO)), (int)(STRETCH * ((cy*(2 - RATIO) / 2) + i / 2)));
	StretchBlt(hdc, x, y, cx, cy, hdcMem, 0, 0, cx * STRETCH, cy * STRETCH, SRCCOPY);
	DeleteDC(hdcMem);
	return TRUE;
}