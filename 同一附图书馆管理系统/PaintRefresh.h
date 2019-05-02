#pragma once
#include<windows.h>
#include"Global.h"


BOOL PaintRefreshButton(HDC hdc, int x, int y, int cx, int cy)
{
	POINT pt;
	HPEN hPen = CreatePen(PS_SOLID, 1.41*STRETCH, RGB(255, 255, 255));
	HDC hdcMem = GetMemDC(hdc, cx*STRETCH, cy*STRETCH);


	SetStretchBltMode(hdc, HALFTONE);
	SetStretchBltMode(hdcMem, HALFTONE);
	StretchBlt(hdcMem, 0, 0, cx*STRETCH, cy*STRETCH, hdc, x, y, cx, cy, SRCCOPY);


	/*
	对连续调用2次AngleArc的说明

	AngleArc函数有个缺陷，会从当前画笔处拉一条直线到圆弧开始处。
	网上给出的方案是，先MoveTo到圆弧开始处。
	但是————我更懒
	我们事先用透明画笔调用一次AngleArc函数，旋转角度为0，就可以直接定位到位置了，免去计算的麻烦
	*/
	
	
		SelectObject(hdcMem, GetStockObject(NULL_PEN));
		AngleArc(hdcMem, (cx*STRETCH) / 2, (cy*STRETCH) / 2, (cy*STRETCH) *(0.5) / 2, 90, 0);//见说明

		SelectObject(hdcMem, hPen);
		AngleArc(hdcMem, (cx*STRETCH) / 2, (cy*STRETCH) / 2, (cy*STRETCH) *(0.5) / 2, 90, -330);
		GetCurrentPositionEx(hdcMem, &pt);

		LineTo(hdcMem, pt.x - STRETCH * cx / 10, pt.y);
		MoveToEx(hdcMem, pt.x, pt.y, NULL);
		LineTo(hdcMem, pt.x, pt.y + STRETCH * cy / 10);

		
	StretchBlt(hdc, x, y, cx, cy, hdcMem, 0, 0, cx*STRETCH, cy*STRETCH, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hPen);
}