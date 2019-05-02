#include<windows.h>
#include"EasyWindow.h"
#include"Global.h"
#include"PaintClose.h"

EZWNDPROC CloseProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hRedBrush;
	static BOOL MouseDown;
	switch (message)
	{
	case EZWM_CREATE:
		hRedBrush = CreateSolidBrush(RGB(214,71,74));
		MouseDown = FALSE;
		SetEZWndTransparent(ezWnd, 0);
		return 0;
	case EZWM_DRAW:
		//»­¹Ø±ÕÍ¼±ê
		PaintCloseButton(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
		return 0;
	case EZWM_MOUSECOME:
		SetEZWndTransparent(ezWnd, 90);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_MOUSELEAVE:
		SetEZWndTransparent(ezWnd, 0);
		MouseDown = FALSE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_LBUTTONDOWN:
		SetEZWndTransparent(ezWnd, 255);
		MouseDown = TRUE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_LBUTTONUP:
		if (MouseDown == TRUE)
		{
			SetEZWndTransparent(ezWnd, 90);
			MouseDown = FALSE;
			EZRepaint(ezWnd, NULL);
			ShowWindow(ezWnd->hParent,SW_HIDE);
		}
		return 0;
	case EZWM_TRANSDRAW:
		if (MouseDown == TRUE)
		{
			SelectObject(wParam, hRedBrush);
			PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);
		}
		else
		{
			PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		}
		
		return 0;
	case EZWM_DESTROY:
		DeleteObject(hRedBrush);
		return 0;
	}
	return 0;
}