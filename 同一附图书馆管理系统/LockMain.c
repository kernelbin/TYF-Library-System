#include<windows.h>
#include<TCHAR.H>
#include"EasyWindow.h"
#include"Global.h"

#include"PaintShutDown.h"
#include"PaintRefresh.h"
#include"PaintExit.h"
#include"jpeg.h"


EZWNDPROC UsernameProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

VOID CALLBACK CaretTimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);

EZWNDPROC PasswordProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);


EZWNDPROC LogOnBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);


EZWNDPROC PicCopyrightProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

EZWNDPROC ShutDownProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

EZWNDPROC RefreshBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);


EZWNDPROC ExitBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);



#define TIMER_CARET 1




static EZWND UsernameWnd;
static EZWND PasswordWnd;
static EZWND LogOnBtn;
static EZWND PicCopyright;




static char Password[64];
static int CaretPos;//在第0个字符前，就为0。


static BOOL IsCaretTimer;//插入符号计时器是否打开



HFONT ListFont;


EZWNDPROC LockProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{

	static EZWND ShowIMG;//显示登录头像圆形窗口。
	static EZWND UserListBox[MAX_USER_COUNT];
	static EZWND RefreshBtn;
	static EZWND ShutDownBtn;
	static EZWND ExitBtn;
	LOGFONT lf;
	int iCount;


	static int PicCount;
	HBITMAP hBitmap;
	static int IDTimer_Static, IDTimer_Dymanic;
	static int RefreshFrame;//当前帧数
	static HDC hdcMem = 0, hdcMemLast = 0;
	HDC hdcBuf;
	BITMAP bitmap;


	switch (message)
	{
	case EZWM_CREATE:

		LockWnd = ezWnd;
		pMainData->UserSelect = -1;//用户？不存在的！加载了再说！


		//创建子窗口
		ShowIMG = CreateEZWindow(ezWnd, (ezWnd->Width - ezWnd->Height / 4) / 2, (1.6 * ezWnd->Height / 4) / 2, ezWnd->Height / 4, ezWnd->Height / 4, ShowImgProc);

		UsernameWnd = CreateEZWindow(ezWnd, (ezWnd->Width - ezWnd->Height / 1.6) / 2, (3.6 * ezWnd->Height / 4) / 2, ezWnd->Height / 1.6, ezWnd->Height / 10, UsernameProc);

		PasswordWnd = CreateEZWindow(ezWnd, (ezWnd->Width - ezWnd->Height / 2.6) / 2, (4.6 * ezWnd->Height / 4) / 2, ezWnd->Height / 2.6, ezWnd->Height / 21, PasswordProc);

		LogOnBtn = CreateEZWindow(ezWnd, (ezWnd->Width - ezWnd->Height / 4.8) / 2, (5.1 * ezWnd->Height / 4) / 2, ezWnd->Height / 4.8, ezWnd->Height / 21, LogOnBtnProc);

		PicCopyright = CreateEZWindow(ezWnd, ezWnd->Width*0.05, ezWnd->Height*0.92, ezWnd->Width *0.16, ezWnd->Height *0.04, PicCopyrightProc);

		RefreshBtn = CreateEZWindow(ezWnd, ezWnd->Width - ezWnd->Height*0.18, ezWnd->Height*0.88, ezWnd->Height *0.06, ezWnd->Height *0.06, RefreshBtnProc);

		ShutDownBtn = CreateEZWindow(ezWnd, ezWnd->Width - ezWnd->Height*0.12, ezWnd->Height*0.88, ezWnd->Height *0.06, ezWnd->Height *0.06, ShutDownProc);

		ExitBtn = CreateEZWindow(ezWnd, ezWnd->Width - ezWnd->Height*0.24, ezWnd->Height*0.88, ezWnd->Height *0.06, ezWnd->Height *0.06, ExitBtnProc);

		
		{
			lf.lfHeight = (int)(ezWnd->Width*0.03*RATIO);
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
			ListFont = CreateFontIndirect(&lf);
		}


		for (iCount = 0; iCount < MAX_USER_COUNT; iCount++)
		{

			UserListBox[iCount] = CreateEZWindow(ezWnd, ezWnd->Width*0.07, ezWnd->Height*0.80 - iCount*ezWnd->Width*0.03, ezWnd->Width*0.20, ezWnd->Width*0.03, UserListBoxProc);

			//其实下面这个语句一点也不地道，这明明是个指针嘛~，可是我不想再开一个ID变量，干脆拿指针放ID数据拉倒2333333
			UserListBox[iCount]->Extend = iCount;

		}

		//准备背景图片
		hBitmap = 0;

		if (wParam == 1)
		{
			if (IDTimer_Static)
			{
				KillEZTimer(ezWnd, IDTimer_Static);
			}
			if (IDTimer_Dymanic)
			{
				KillEZTimer(ezWnd, IDTimer_Dymanic);
			}
		}
		else
		{
			IDTimer_Static = -1;
			IDTimer_Dymanic = -1;
		}

		/*IDTimer_Dymanic = -1;
		IDTimer_Static = -1;*/

		
		//加载图片到hBitmap

		HGLOBAL hRes;
		HRSRC hRsrc;

		PicCount = 0;

		hRes = LoadResource(NULL, hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_JPG1+ PicCount), TEXT("JPG")));

		hBitmap = LoadJpegFromData(LockResource(hRes), SizeofResource(NULL, hRsrc));
		FreeResource(hRes);
		//BytesToWrite = SizeofResource(NULL, hRsrc);


		//pData =;


		hdcMem = GetMemDC(ezWnd->hdc, ezWnd->Width, ezWnd->Height);
		hdcMemLast = GetMemDC(ezWnd->hdc, ezWnd->Width, ezWnd->Height);
		PatBlt(hdcMem, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);

		SetStretchBltMode(hdcMem, HALFTONE);
		SetStretchBltMode(hdcMemLast, HALFTONE);

		GetObject(hBitmap, sizeof(BITMAP), &bitmap);

		hdcBuf = CreateCompatibleDC(ezWnd->hdc);
		SelectObject(hdcBuf, hBitmap);

		
		StretchBlt(hdcMem,
			0,0,ezWnd->Width,ezWnd->Height,
			hdcBuf, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		


		DeleteDC(hdcBuf);
		DeleteObject(hBitmap);

		RefreshFrame = -1;
		IDTimer_Static = SetEZTimer(ezWnd, 60 * 1000);

		return 0;

	case EZWM_TIMER:
		if (wParam == IDTimer_Static)
		{
			hBitmap = NULL;

			//切换图片并加载到hBitmap

			PicCount++;
			if (PicCount == PIC_NUM)
			{
				PicCount = 0;
			}

			hRes = LoadResource(NULL, hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_JPG1 + PicCount), TEXT("JPG")));

			hBitmap = LoadJpegFromData(LockResource(hRes), SizeofResource(NULL, hRsrc));
			FreeResource(hRes);

			HDC hdcSwap;
			hdcSwap = hdcMem;
			hdcMem = hdcMemLast;
			hdcMemLast = hdcSwap;
			//BitBlt(hdcMemLast, 0, 0, ezWnd->Width, ezWnd->Height, hdcMem, 0, 0, SRCCOPY);

			//清空（重置hdcMem）的底色
			PatBlt(hdcMem, 0, 0, ezWnd->Width , ezWnd->Height , WHITENESS);

			GetObject(hBitmap, sizeof(BITMAP), &bitmap);

			hdcBuf = CreateCompatibleDC(ezWnd->hdc);
			SelectObject(hdcBuf, hBitmap);

			
			StretchBlt(hdcMem,
				0, 0, ezWnd->Width, ezWnd->Height,
				hdcBuf, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			DeleteDC(hdcBuf);


			DeleteObject(hBitmap);

			//关闭这个计时器，切换当前图片，切换到动态

			KillEZTimer(ezWnd, IDTimer_Static);
			IDTimer_Static = -1;

			//切换至动态
			RefreshFrame = 0;
			IDTimer_Dymanic = SetEZTimer(ezWnd, 50);

		}
		else if (wParam == IDTimer_Dymanic)
		{

			RefreshFrame++;
			if (RefreshFrame >= 40)

			{

				//关闭动态
				KillEZTimer(ezWnd, IDTimer_Dymanic);
				IDTimer_Dymanic = -1;
				RefreshFrame = -1;


				//打开静态
				IDTimer_Static = SetEZTimer(ezWnd, 60 * 1000);
			}
		}

		EZRepaint(ezWnd, 0);

		return 0;

	case EZWM_DRAW:

	{
		BLENDFUNCTION bf = {0};

		//Rectangle(wParam, ezWnd->Width * (1 - PIC_WIDTH) / 2 - 1, (ezWnd->Height - ezWnd->Width * PIC_WIDTH* PIC_HW_RATIO) / 2 - 1, ezWnd->Width * (1 + PIC_WIDTH) / 2 + 1, (ezWnd->Height + ezWnd->Width * PIC_WIDTH* PIC_HW_RATIO) / 2 + 1);
		BitBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, hdcMem, 0, 0, SRCCOPY);
		if (RefreshFrame != -1)
		{
			/*bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER; 初始化全部为0了，而且AC_SRC_OVER == 0*/
			bf.SourceConstantAlpha = 255 - RefreshFrame * (6.375);
			AlphaBlend(wParam, 0, 0, ezWnd->Width, ezWnd->Height, hdcMemLast, 0, 0 , ezWnd->Width, ezWnd->Height, bf);
		}

	}

		return 0;

	case EZWM_TRANSDRAW:
		return 0;
	case EZWM_COLSE:
		return DO_NOT_CLOSE;

	case EZWM_DESTROY:

		/*DeleteDC(hdcMem);*/
		DeleteObject(ListFont);
		if (hdcMem)
		{
			DeleteDC(hdcMem);
		}
		if (hdcMemLast)
		{
			DeleteDC(hdcMemLast);
		}
		return 0;
	}
	return 0;
}




EZWNDPROC ShowImgProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
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

EZWNDPROC UsernameProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static RECT rect;
	static HFONT hFont;
	switch (message)
	{
	case EZWM_CREATE:
		rect.left = 0;
		rect.top = 0;
		rect.right = ezWnd->Width;
		rect.bottom = ezWnd->Height;
		hFont = CreateFont(
			5 * ezWnd->Height / 7,
			0, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("微软雅黑")
		);
		return 0;
	case EZWM_DRAW:


		SetTextColor(wParam, RGB(255, 255, 255));
		SetBkMode(wParam, TRANSPARENT);
		SelectFont(wParam, hFont);
		if (pMainData->LoadState == LS_REFRESHING)
		{
			//刷新数据库ing
			DrawText(wParam, TEXT("正在刷新数据库"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (pMainData->LoadState == LS_LOADFAILED)
		{
			//访问数据库失败
			DrawText(wParam, TEXT("访问数据库失败"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (pMainData->LoadState == LS_REFRESHFAILED)
		{
			//刷新数据库失败
			DrawText(wParam, TEXT("刷新数据库失败"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		else if (pMainData->LoadState == LS_EMPTY ||
			(pMainData->UserCount == 0))
		{
			//用户不存在hhh，用户列表为空
			DrawText(wParam, TEXT("用户列表为空"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (pMainData->UserSelect == -1)
		{
			//没选择
			DrawText(wParam, TEXT("请选择用户"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else
		{
			DrawTextA(wParam, pMainData->UsernameList[pMainData->UserSelect], -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

	case EZWM_DESTROY:
		DeleteFont(hFont);
	}
}


EZWNDPROC PasswordProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static BOOL Focus;
	static BOOL Mouse;

	static BOOL ShowCaret;

	static RECT rect;
	static HFONT hFont;





	static TCHAR ShowDot[67] = TEXT("  ●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●");

	int LenCount;//长度
	switch (message)
	{
	case EZWM_CREATE:
		Focus = FALSE;
		Mouse = FALSE;

		ShowCaret = 0;

		CaretPos = 0;

		IsCaretTimer = 1;

		rect.left = 0;
		rect.top = 0;
		rect.right = ezWnd->Width;
		rect.bottom = ezWnd->Height;
		hFont = CreateFont(
			4 * ezWnd->Height / 7,
			0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("微软雅黑"));

		SetEZWndTransparent(ezWnd, 80);

		strcpy(Password, "");

		//设置时间
		SetTimer(NULL, TIMER_CARET, 600, CaretTimerProc);
		return 0;
	case EZWM_SETFOCUS:
		Focus = TRUE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_KILLFOCUS:
		Focus = FALSE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_MOUSECOME:
		Mouse = TRUE;
		SetEZWndTransparent(ezWnd, 120);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_MOUSELEAVE:
		Mouse = FALSE;
		SetEZWndTransparent(ezWnd, 80);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_DRAW:
		if (pMainData->UserSelect == -1 || pMainData->UserCount == 0)
		{
			return 0;
		}
		if (Focus)
		{
			SelectPen(wParam, GetStockPen(NULL_PEN));
			SelectBrush(wParam, GetStockBrush(WHITE_BRUSH));
			Rectangle(wParam, 2, 2, ezWnd->Width - 1, ezWnd->Height - 1);
			SetTextColor(wParam, RGB(0, 0, 0));
		}
		else
		{

			SetTextColor(wParam, RGB(255, 255, 255));
		}
		//绘制密码点。
		SelectFont(wParam, hFont);

		SetBkMode(wParam, TRANSPARENT);
		DrawText(wParam, ShowDot, CaretPos + 2, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

		//绘制光标
		if (Focus && ShowCaret)
		{
			SIZE Size;
			GetTextExtentPoint32(wParam, ShowDot, CaretPos + 2, &Size);
			SelectPen(wParam, GetStockPen(BLACK_PEN));
			MoveToEx(wParam, Size.cx + 0.1 * ezWnd->Height, 0.2 * ezWnd->Height, NULL);
			LineTo(wParam, Size.cx + 0.1 * ezWnd->Height, 0.8 * ezWnd->Height);
		}
		return 0;
	case EZWM_TRANSDRAW:
		SelectPen(wParam, CreatePen(PS_INSIDEFRAME, 2, RGB(255, 255, 255)));
		SelectBrush(wParam, GetStockBrush(BLACK_BRUSH));
		Rectangle(wParam, 0, 0, ezWnd->Width, ezWnd->Height);



		if (CaretPos == 0)
		{
			SelectFont(wParam, hFont);
			SetTextColor(wParam, RGB(255, 255, 255));
			SetBkMode(wParam, TRANSPARENT);
			DrawText(wParam, TEXT("  Password :"), -1, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}

		DeletePen(SelectObject(wParam, GetStockObject(NULL_PEN)));
		return 0;

	case EZWM_CHAR:
		if (pMainData->UserSelect == -1 || pMainData->UserCount == 0)
		{
			return 0;
		}

		//strncpy_s(Password[CaretPos + 1], 64, Password[CaretPos], 64 - CaretPos - 1);
		if (wParam == '\b')
		{
			if (CaretPos == 0)
			{
				//不能再减了
				return 0;
			}
			CaretPos--;
			Password[CaretPos] = '\0';

			ShowCaret = 1;
		}
		else if ((('a' <= wParam) && (wParam <= 'z')) || (('A' <= wParam) && (wParam <= 'Z')) || (('0' <= wParam) && (wParam <= '9')))
		{
			Password[CaretPos] = wParam;
			CaretPos++;

			ShowCaret = 1;
		}
		else if (wParam == '\r')
		{
			if (strcmp(Password, pMainData->PasswordList[pMainData->UserSelect]) == 0)
			{
				//登录成功！
				//做好登录准备，然后关界面锁。
				LoginFunc(pMainData->UserSelect);
				CloseLock();
				return 0;
			}
		}


		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_TIMER:
		if (wParam == 1)
		{
			//光标计时器
			ShowCaret = !ShowCaret;
			EZRepaint(ezWnd, NULL);
		}
		return 0;
	case EZWM_DESTROY:
		DeleteFont(hFont);
		KillTimer(NULL, TIMER_CARET);
		IsCaretTimer = 0;
	}

}



EZWNDPROC LogOnBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static BOOL MouseDown;
	static HFONT hFont;
	static RECT rect;

	switch (message)
	{
	case EZWM_CREATE:
		MouseDown = FALSE;
		SetEZWndTransparent(ezWnd, 100);
		hFont = CreateFont(
			4 * ezWnd->Height / 7,
			0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("微软雅黑"));
		rect.left = 0;
		rect.top = 0;
		rect.right = ezWnd->Width;
		rect.bottom = ezWnd->Height;
		return 0;
	case EZWM_TRANSDRAW:

		SelectPen(wParam, CreatePen(PS_INSIDEFRAME, 2, RGB(255, 255, 255)));
		SelectBrush(wParam, CreateSolidBrush(RGB(50, 50, 50)));
		Rectangle(wParam, 0, 0, ezWnd->Width, ezWnd->Height);




		SelectFont(wParam, hFont);
		SetTextColor(wParam, RGB(255, 255, 255));
		SetBkMode(wParam, TRANSPARENT);
		DrawText(wParam, TEXT("登录"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		DeletePen(SelectObject(wParam, GetStockObject(NULL_PEN)));
		DeletePen(SelectObject(wParam, GetStockObject(NULL_BRUSH)));
		return 0;
	case EZWM_MOUSECOME:
		SetEZWndTransparent(ezWnd, 180);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_MOUSELEAVE:
		SetEZWndTransparent(ezWnd, 100);
		MouseDown = FALSE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_LBUTTONDOWN:
		SetEZWndTransparent(ezWnd, 180);
		MouseDown = TRUE;
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_LBUTTONUP:
		if (MouseDown == TRUE)
		{
			SetEZWndTransparent(ezWnd, 90);
			MouseDown = FALSE;
			EZRepaint(ezWnd, NULL);


			//登录


			if (pMainData->UserSelect == -1 || pMainData->UserCount == 0)
			{
				return 0;
			}

			if (strcmp(Password, pMainData->PasswordList[pMainData->UserSelect]) == 0)
			{
				//登录成功！
				//做好登录准备，然后关界面锁。
				LoginFunc(pMainData->UserSelect);
				CloseLock();
				return 0;
			}
		}
		return 0;

	case EZWM_DESTROY:
		DeleteObject(hFont);
		return 0;
	}
	return 0;
}



EZWNDPROC ShutDownProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hRedBrush;
	static BOOL MouseDown;

	switch (message)
	{
	case EZWM_CREATE:
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		MouseDown = FALSE;
		SetEZWndTransparent(ezWnd, 0);
		return 0;
	case EZWM_DRAW:
		//画关机图标
		PaintShutDownButton(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
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
			//ShowWindow(ezWnd->hParent, SW_HIDE);
			ExitWindowsEx(EWX_FORCE, 0);
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

VOID CALLBACK CaretTimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	if (IsCaretTimer == 1)
	{
		EZSendMessage(PasswordWnd, EZWM_TIMER, 1, 0);
	}

}

EZWNDPROC UserListBoxProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	int iCount;
	switch (message)
	{
	case EZWM_CREATE:
		SetEZWndTransparent(ezWnd, 0);
		return 0;
	case EZWM_MOUSECOME:

		SetEZWndTransparent(ezWnd, 50);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_MOUSELEAVE:
		SetEZWndTransparent(ezWnd, 0);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_TRANSDRAW:
		if ((!(ezWnd->Extend > (pMainData->UserCount - 1))) && (pMainData->UserCount != 0))
		{

			PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, BLACKNESS);
		}
		return 0;
	case EZWM_SETFOCUS:
		if (!(ezWnd->Extend > (pMainData->UserCount - 1)))
		{
			pMainData->UserSelect = (int)ezWnd->Extend;
			EZRepaint(ezWnd->ezParent, NULL);
			for (iCount = 0; iCount < sizeof(Password) / sizeof(Password[0]); iCount++)
			{
				Password[iCount] = '\0';
			}
		}
		CaretPos = 0;
		return 0;
	case EZWM_DRAW:
		SelectObject(wParam, ListFont);
		SetBkMode(wParam, TRANSPARENT);
		SetTextColor(wParam, RGB(255, 255, 255));
		//TextOut(wParam, CAPTIONHEIGHT*RATIO, CAPTIONHEIGHT*RATIO*(1 - RATIO) / 2, BorderBtn[(int)(ezWnd->Extend)].BtnName, lstrlen(BorderBtn[(int)(ezWnd->Extend)].BtnName));
		if ((!(ezWnd->Extend > (pMainData->UserCount - 1))) && pMainData->UserCount != 0)
		{
			TextOutA(wParam, ezWnd->Height*RATIO, ezWnd->Height*(1 - RATIO) / 2, pMainData->UsernameList[(int)ezWnd->Extend], strlen(pMainData->UsernameList[(int)ezWnd->Extend]));
		}
		return 0;
	}
	return 0;
}

EZWNDPROC PicCopyrightProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static RECT rect;
	static HFONT hFont;
	switch (message)
	{
	case EZWM_CREATE:
		rect.left = 0;
		rect.top = 0;
		rect.right = ezWnd->Width;
		rect.bottom = ezWnd->Height;
		hFont = CreateFont(
			5 * ezWnd->Height / 7,
			0, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("微软雅黑")
		);
		SetEZWndTransparent(ezWnd, 130);
		return 0;
	case EZWM_TRANSDRAW:
		SetTextColor(wParam, RGB(255, 255, 255));
		SetBkMode(wParam, TRANSPARENT);
		SelectFont(wParam, hFont);
		DrawText(wParam, TEXT("图片由高一（3）叶思齐 提供"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	case EZWM_DESTROY:
		DeleteFont(hFont);
	}
}




EZWNDPROC ExitBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static BOOL MouseDown;
	switch (message)
	{
	case EZWM_CREATE:
		MouseDown = FALSE;
		SetEZWndTransparent(ezWnd, 0);
		return 0;
	case EZWM_DRAW:

		PaintExitButton(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
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
			//准备验证管理员身份，然后退出整个程序

			/*这里开始！
			现在需要添加这几个功能：

			2：本地管理员登录，内置密码，无需网络连接
			3：退出程序功能（验证管理员后）*/


		}
		return 0;
	case EZWM_TRANSDRAW:
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		return 0;
	}
	return 0;
}



EZWNDPROC RefreshBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static BOOL MouseDown;
	switch (message)
	{
	case EZWM_CREATE:
		MouseDown = FALSE;
		SetEZWndTransparent(ezWnd, 0);
		return 0;
	case EZWM_DRAW:

		PaintRefreshButton(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
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
			BeginNetDataLoad();
		}
		return 0;
	case EZWM_TRANSDRAW:
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		return 0;
	}
	return 0;
}