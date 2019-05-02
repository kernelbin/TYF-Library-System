#pragma once

#include<windows.h>
#include"Global.h"


POINT GetStrtechPt(double x, double y)
{
	POINT pt;
	pt.x = (int)(STRETCH * x);
	pt.y = (int)(STRETCH * y);
	return pt;
}
BOOL PaintCloseButton(HDC hdc, int x,int y,int cx, int cy)
{
	double i = 1;
	HDC hdcMem;
	POINT pt1[7];
	POINT pt2[7];

	//ÉèÖÃµã×ø±ê
	{
		pt1[0] = GetStrtechPt(cx*RATIO / 2, cy* RATIO / 2 + i);
		pt1[1] = GetStrtechPt(cx*RATIO / 2, cy* RATIO / 2);
		pt1[2] = GetStrtechPt((cx*    RATIO / 2) + i, cy* RATIO / 2);
		pt1[3] = GetStrtechPt((cx*(2 - RATIO) / 2), (cy*(2 - RATIO) / 2) - i);
		pt1[4] = GetStrtechPt((cx*(2 - RATIO) / 2), (cy*(2 - RATIO) / 2));
		pt1[5] = GetStrtechPt((cx*(2 - RATIO) / 2) - i, (cy*(2 - RATIO) / 2));

	}
	{
		pt2[0] = GetStrtechPt((cx*(2 - RATIO) / 2) - i, cy* RATIO / 2);
		pt2[1] = GetStrtechPt((cx*(2 - RATIO) / 2), cy* RATIO / 2);
		pt2[2] = GetStrtechPt((cx*(2 - RATIO) / 2), cy* RATIO / 2 + i);
		pt2[3] = GetStrtechPt((cx * RATIO / 2) + i, (cy*(2 - RATIO) / 2));
		pt2[4] = GetStrtechPt((cx * RATIO / 2), (cy*(2 - RATIO) / 2));
		pt2[5] = GetStrtechPt((cx * RATIO / 2), (cy*(2 - RATIO) / 2) - i);
	}

	hdcMem = GetMemDC(hdc, cx * STRETCH, cy * STRETCH);

	SetStretchBltMode(hdcMem, HALFTONE);
	SetStretchBltMode(hdc, HALFTONE);
	StretchBlt(hdcMem, 0, 0, cx * STRETCH, cy * STRETCH, hdc, x, y, cx, cy, SRCCOPY);
	SelectObject(hdcMem, GetStockObject(WHITE_PEN));
	SelectObject(hdcMem, GetStockObject(WHITE_BRUSH));
	Polygon(hdcMem, pt1, 6);
	Polygon(hdcMem, pt2, 6);
	StretchBlt(hdc, x, y, cx, cy, hdcMem, 0, 0, cx * STRETCH, cy * STRETCH, SRCCOPY);
	DeleteDC(hdcMem);
	return TRUE;
}
