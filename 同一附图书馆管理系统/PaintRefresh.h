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
	����������2��AngleArc��˵��

	AngleArc�����и�ȱ�ݣ���ӵ�ǰ���ʴ���һ��ֱ�ߵ�Բ����ʼ����
	���ϸ����ķ����ǣ���MoveTo��Բ����ʼ����
	���ǡ��������Ҹ���
	����������͸�����ʵ���һ��AngleArc��������ת�Ƕ�Ϊ0���Ϳ���ֱ�Ӷ�λ��λ���ˣ���ȥ������鷳
	*/
	
	
		SelectObject(hdcMem, GetStockObject(NULL_PEN));
		AngleArc(hdcMem, (cx*STRETCH) / 2, (cy*STRETCH) / 2, (cy*STRETCH) *(0.5) / 2, 90, 0);//��˵��

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