#pragma once

#include<windows.h>
#include"Global.h"


BOOL PaintShutDownButton(HDC hdc, int x, int y, int cx, int cy)
{
	HDC hdcMem;
	HPEN hPen = CreatePen(PS_SOLID, 1.414*STRETCH, RGB(255, 255, 255));

	hdcMem = GetMemDC(hdc, cx * STRETCH, cy * STRETCH);
	SetStretchBltMode(hdcMem, HALFTONE);
	SetStretchBltMode(hdc, HALFTONE);
	StretchBlt(hdcMem, 0, 0, cx * STRETCH, cy * STRETCH, hdc, x, y, cx, cy, SRCCOPY);

	//绘制关机图标
	SelectPen(hdcMem, GetStockPen(NULL_PEN));
	AngleArc(hdcMem, cx*STRETCH / 2, cy*STRETCH / 2, cx * STRETCH / 4, 60, 0);

	SelectPen(hdcMem, hPen);
	AngleArc(hdcMem, cx*STRETCH / 2, cy*STRETCH / 2, cx * STRETCH / 4, 60, -300);

	MoveToEx(hdcMem, cx * STRETCH / 2, cy * STRETCH *(1 - RATIO) / 2, NULL);
	LineTo(hdcMem, cx * STRETCH / 2, cy * STRETCH / 2);

	StretchBlt(hdc, x, y, cx, cy, hdcMem, 0, 0, cx * STRETCH, cy * STRETCH, SRCCOPY);
	DeleteDC(hdcMem);
	DeletePen(hPen);
	return TRUE;
}
