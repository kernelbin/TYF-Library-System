#include<windows.h>
#include"EasyWindow.h"
#include"Global.h"
#include"PaintSmall.h"

EZWNDPROC SmallProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static BOOL MouseDown;
	switch (message)
	{
	case EZWM_CREATE:
		MouseDown = FALSE;
		SetEZWndTransparent(ezWnd, 0);
		return 0;
	case EZWM_DRAW:
		//»­ËõÐ¡Í¼±ê
		PaintSmallButton(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
		return 0;
	case EZWM_MOUSECOME:
		SetEZWndTransparent(ezWnd, 90);
		EZRepaint(ezWnd,NULL);
		return 0;
	case EZWM_MOUSELEAVE:
		SetEZWndTransparent(ezWnd, 0);
		MouseDown = FALSE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_LBUTTONDOWN:
		SetEZWndTransparent(ezWnd, 120);
		MouseDown = TRUE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_LBUTTONUP:
		if (MouseDown == TRUE)
		{
			SetEZWndTransparent(ezWnd, 90);
			MouseDown = FALSE;
			EZRepaint(ezWnd, NULL);
			CloseWindow(ezWnd->hParent);
		}
		return 0;
	case EZWM_TRANSDRAW:
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		return 0;
	}
	return 0;
}