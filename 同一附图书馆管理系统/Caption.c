#include<Windows.h>
#include"EasyWindow.h"
#include"Global.h"

EZWNDPROC CaptionProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont;//标题字体
	static EZWND CloseBtn;
	static EZWND SmallBtn;
	LOGFONT lf;
	switch (message)
	{
	case EZWM_CREATE:
		SetEZWndTransparent(ezWnd, 130);//设置透明度
		LOGFONT lf;//用于创建字体

				   //创建标题字体
		{
			lf.lfHeight = (int)(ezWnd->Height * (1 - RATIO));
			lf.lfWidth = 0;
			lf.lfEscapement = 0;
			lf.lfOrientation = 0;
			lf.lfWeight = 0;
			lf.lfItalic = 0;
			lf.lfUnderline = 0;
			lf.lfStrikeOut = 0;
			lf.lfCharSet = DEFAULT_CHARSET;
			lf.lfOutPrecision = 0;
			lf.lfClipPrecision = 0;
			lf.lfPitchAndFamily = 0;
			lstrcpy(lf.lfFaceName, TEXT("微软雅黑"));
			hFont = CreateFontIndirect(&lf);
		}




		//创建子窗口
		CloseBtn = CreateEZWindow(ezWnd,
			ezWnd->Width - ezWnd->Height + ezWnd->Height*(1 - RATIO) / 2,
			ezWnd->Height*(1 - RATIO) / 2,
			ezWnd->Height*(RATIO),
			ezWnd->Height*(RATIO), CloseProc);

		SmallBtn = CreateEZWindow(ezWnd,
			ezWnd->Width - ezWnd->Height + ezWnd->Height*(1 - RATIO) / 2 - ezWnd->Height*(RATIO),
			ezWnd->Height*(1 - RATIO) / 2,
			ezWnd->Height*(RATIO),
			ezWnd->Height*(RATIO), SmallProc);
	case EZWM_TRANSDRAW:
		//透明绘制一个黑色的边框
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, BLACKNESS);
		return 0;


	case EZWM_DRAW:
		//画标题
	{
		SetBkMode(wParam, TRANSPARENT);
		SetTextColor(wParam, RGB(255, 255, 255));
		SelectObject(wParam, hFont);
		TextOut(wParam, (int)(ezWnd->Height * RATIO / 2), (int)(ezWnd->Height* RATIO / 2), TEXT("  同一附图书馆管理系统"), lstrlen(TEXT("  同一附图书馆管理系统")));
	}

	return 0;
	case EZWM_LBUTTONDOWN:
		SendMessage(ezWnd->hParent, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);//拖动窗口。
		return 0;

	case EZWM_DESTROY:
		DeleteObject(hFont);
	}
	return 0;
}