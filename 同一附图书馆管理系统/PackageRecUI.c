#include<Windows.h>
#include"Global.h"


static EZWND URLList, ScrollBar, ScrollLayer;//, ProgSelectBtn;

EZWNDPROC URLListHoldProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
EZWNDPROC URLScrollLayer(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
EZWNDPROC URLListShowProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
EZWNDPROC ProgListBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

EZWNDPROC PackageRecUIProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case EZWM_CREATE:
		URLList = CreateEZWindow(ezWnd, 140, 60, ezWnd->Width -  170, ezWnd->Height - 110, URLListHoldProc);
		return 0;
	case EZWM_DRAW:
		
		return 0;
	}

	return 0;
}


EZWNDPROC URLListHoldProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case EZWM_CREATE:

		ezWnd->Transparent = 70;
		
		ScrollBar = CreateEZStyleWindow(ezWnd, TEXT(""), EZS_CHILD | EZS_CHILD_VSCROLL, ezWnd->Width - 18, 0, 18, ezWnd->Height);
		ScrollLayer = CreateEZWindow(ezWnd, 0, 0, ezWnd->Width - 18, ezWnd->Height, URLScrollLayer);
		

		EZSendMessage(ScrollBar, EZWM_SETSCROLLRANGE, ScrollLayer->Height, 0);
		EZSendMessage(ScrollBar, EZWM_SETSCROLLPOS, 0, ScrollLayer->Height);

		return 0;


	case EZWM_TRANSDRAW:
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		return 0;
	case EZWM_SCROLLPOSCHANGE:
		ScrollLayer->ScrollY = -wParam;
		EZRepaint(ezWnd, 0);
		return 0;

	}
	return 0;
}



EZWNDPROC URLScrollLayer(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case EZWM_CREATE:
		URLListShow = CreateEZWindow(ezWnd, 0, 0, ezWnd->Width, ezWnd->Height, URLListShowProc);

		return 0;
	}
	return 0;
}


EZWNDPROC URLListShowProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	EZWND Child[MAX_URL_NUM];
	switch (message)
	{

	case EZWM_USER_NOTIFY:
		Child[URL_Num] = CreateEZStyleWindow(ezWnd, wParam, EZS_CHILD | EZS_BUTTON, 0, 40 * URL_Num, ezWnd->Width, 40);
		EZRepaint(URLList, 0);
		FontForm.lfHeight = 40 * (4.0 / 7.0);
		EZSendMessage(Child[URL_Num], EZWM_SETFONT, 0, &FontForm);
		EZSendMessage(Child[URL_Num], EZWM_SETCOLOR, RGB(80, 80, 80), RGB(0, 0, 0));
		EZSendMessage(Child[URL_Num], EZWM_SETTEXTALIGN,DT_VCENTER|DT_SINGLELINE|DT_LEFT| DT_END_ELLIPSIS,0);

		Child[URL_Num]->ezWndProc = ProgListBtnProc;
		SetEZWndTransparent(Child[URL_Num], 0);
		if ((URL_Num + 1) * 40 > ezWnd->Height)
		{
			MoveEZWindow(ezWnd, 0, 0, ezWnd->Width, (URL_Num + 1) * 40, 0);
			EZSendMessage(ScrollBar, EZWM_SETSCROLLRANGE, ezWnd->Height, 0);
		}
		EZRepaint(PkgRecUI, 0);
	return 0;

	}
	return 0;
}



EZWNDPROC ProgListBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	switch (message)
	{
	case EZWM_CREATE:
		SetEZWndTransparent(ezWnd, 0);
		return 0;

	case EZWM_DRAW:
		rect.left = 0;
		rect.top = 0;
		rect.right = ezWnd->Width;
		rect.bottom = ezWnd->Height;
		SetTextColor(wParam, (COLORREF)(((ezWnd->Extend))->ForeGroundColor));

		SetBkMode(wParam, TRANSPARENT);
		if (((pEZSE)ezWnd->Extend)->hFont)
		{
			SelectObject(wParam, ((pEZSE)ezWnd->Extend)->hFont);
		}

		if (CHK_ALT_STYLE(ezWnd->EZStyle, EZS_BORDER))
		{
			hPen = CreatePen(PS_SOLID, 1, ezWnd->Extend->ForeGroundColor);
			SelectPen(wParam, hPen);
			SelectBrush(wParam, GetStockObject(NULL_BRUSH));
			Rectangle(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
		}
		rect.left += 10;
		rect.right -= 20;
		DrawText(wParam, ((pEZSE)(ezWnd->Extend))->Title, -1, &rect, (ezWnd->Extend->TextAlign == 0) ? (DT_CENTER | DT_VCENTER | DT_SINGLELINE) : (ezWnd->Extend->TextAlign));

		return 0;
	case EZWM_TRANSDRAW:
		hBrush = CreateSolidBrush((COLORREF)(((ezWnd->Extend))->BackGroundColor));
		SelectObject(wParam, hBrush);
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);

		DeleteObject(hBrush);
		return 0;
	case EZWM_LBUTTONDOWN:
		if ((((ezWnd->Extend))->MouseHold) == FALSE)
		{
			EZCaptureMouse(ezWnd);

			(((ezWnd->Extend))->MouseHold) = TRUE;
			SetEZWndTransparent(ezWnd, 60);
			EZRepaint(URLList, NULL);
		}

		return 0;
	case EZWM_LBUTTONUP:
		SetEZWndTransparent(ezWnd, 30);
		EZRepaint(URLList, NULL);
		if ((((ezWnd->Extend))->MouseHold) == TRUE)
		{
			EZReleaseMouse(ezWnd);
			if ((LOWORD(lParam)>0) && (LOWORD(lParam)<ezWnd->Width) && (HIWORD(lParam)>0) && (HIWORD(lParam)<ezWnd->Height))
			{

				(((ezWnd->Extend))->MouseHold) = FALSE;
				//按钮被单击了！

				//判断按钮类型
				if (CHK_STYLE(ezWnd->EZStyle & MKDW(11111111, 00000000, 00000000, 00000000), EZBS_PUSHBUTTON))
				{
					//发送控制消息。
					EZSendMessage(ezWnd->ezParent, EZWM_COMMAND, 0, ezWnd);
				}
				else if (CHK_STYLE(ezWnd->EZStyle & MKDW(11111111, 00000000, 00000000, 00000000), EZBS_RADIOBUTTON))
				{
					//没说是AUTO哦，要听父窗口的话。
				}
			}

		}
		return 0;
	case EZWM_MOUSECOME:
		SetEZWndTransparent(ezWnd, 30);
		EZRepaint(URLList, NULL);
		return 0;

	case EZWM_RELEASEMOUSE:
		(((ezWnd->Extend))->MouseHold) = FALSE;
		return 0;

	case EZWM_MOUSELEAVE:
		SetEZWndTransparent(ezWnd, 0);
		EZRepaint(URLList, NULL);
		return 0;

	}
	return EZStyle_DefaultProc(ezWnd, message, wParam, lParam);
}

