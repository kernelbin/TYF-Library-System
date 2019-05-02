#include<Windows.h>
#include"EasyWindow.h"
#include"Global.h"


EZWNDPROC MainUIImgProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
EZWNDPROC MainUITextProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

EZWNDPROC MainUIProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static EZWND ShowIMG, ShowName;

	switch (message)
	{
	case EZWM_CREATE:

		
		ShowIMG = CreateEZWindow(ezWnd, ezWnd->Width / 18, ezWnd->Width / 18, ezWnd->Width / 4, ezWnd->Width / 4, MainUIImgProc);
		ShowName = CreateEZWindow(ezWnd, ezWnd->Width * 13 / 36, ezWnd->Width * 5 / 36, ezWnd->Width * 2 / 3, ezWnd->Width / 12, MainUITextProc);
		return 0;
	case EZWM_DRAW:
		//if (pData)
		//{
		//	if (pData->UserSelect != -1)
		//	{
		//		SelectObject(wParam, hFont);
		//		SetTextColor(wParam, RGB(255, 255, 255));
		//		SetBkMode(wParam, TRANSPARENT);
		//		//TextOutA(wParam, ezWnd->Height / 24, ezWnd->Height / 24, pData->UsernameList[pData->UserSelect], strlen(pData->UsernameList[pData->UserSelect]));
		//	}
		//}

		return 0;

	case EZWM_TRANSDRAW:
		return 0;

	case EZWM_DESTROY:

		return 0;
	}
}



EZWNDPROC MainUIImgProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	HDC hdcWin;
	static HDC hdcMem;
	static HPEN hPen;
	int ws, hs;
	switch (message)
	{
	case EZWM_CREATE:
		SetEZWndTransparent(ezWnd, 140);


		hdcWin = GetDC(ezWnd->hParent);
		hdcMem = GetMemDC(hdcWin, ezWnd->Width*STRETCH, ezWnd->Height*STRETCH);
		ReleaseDC(ezWnd->hParent, hdcWin);

		hPen = CreatePen(PS_SOLID, 7 * STRETCH, RGB(255, 255, 255));

		return 0;
	case EZWM_TRANSDRAW:

		ws = ezWnd->Width*STRETCH;
		hs = ezWnd->Height*STRETCH;
		StretchBlt(hdcMem, 0, 0, ws, hs, wParam, 0, 0, ezWnd->Width, ezWnd->Height, SRCCOPY);
		SelectPen(hdcMem, GetStockPen(NULL_PEN));
		SelectBrush(hdcMem, GetStockBrush(WHITE_BRUSH));
		Ellipse(hdcMem, 0, 0, ws, hs);

		SetStretchBltMode(wParam, HALFTONE);

		StretchBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, hdcMem, 0, 0, ws, hs, SRCCOPY);

		return 0;
	case EZWM_DRAW:
	{
		//int ws0_75;
		ws = ezWnd->Width*STRETCH;
		hs = ezWnd->Height*STRETCH;
		//ws0_75 = 3 * (ws >> 2);
		StretchBlt(hdcMem, 0, 0, ws, hs, wParam, 0, 0, ezWnd->Width, ezWnd->Height, SRCCOPY);

		SelectPen(hdcMem, hPen);
		SelectBrush(hdcMem, GetStockObject(NULL_BRUSH));

		Ellipse(hdcMem, ws*0.35, ws*0.2, ws*0.65, ws >> 1);

		//SetStretchBltMode(wParam, HALFTONE);  因为EZWM_TRANSDRAW是先调用的，已经设置过，这个就可以去掉了。
		MoveToEx(hdcMem, (ws >> 2) + (ws >> 1), (ws >> 2) + (ws >> 1), 0);
		AngleArc(hdcMem, ws >> 1, (ws >> 2) + (ws >> 1), ws >> 2, 0, 180);
		StretchBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, hdcMem, 0, 0, ws, hs, SRCCOPY);
	}
		


		return 0;
	case EZWM_DESTROY:
		DeleteDC(hdcMem);
		DeletePen(hPen);
	}
}

EZWNDPROC MainUITextProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont;
	switch (message)
	{
	case EZWM_CREATE:
		hFont = CreateFont(
			5 * ezWnd->Height / 7,
			0, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("微软雅黑"));
		return 0;

	case EZWM_DRAW:
		if (pMainData)
		{
			if (pMainData->UserSelect != -1)
			{
				SelectObject(wParam, hFont);
				SetTextColor(wParam, RGB(255, 255, 255));
				SetBkMode(wParam, TRANSPARENT);
				TextOutA(wParam, 0, 0, pMainData->UsernameList[pMainData->UserSelect], strlen(pMainData->UsernameList[pMainData->UserSelect]));

			}
		}
		return 0;

	case EZWM_RBUTTONUP:

		return 0;
	case EZWM_DESTROY:
		DeleteObject(hFont);
		return 0;
	}
}