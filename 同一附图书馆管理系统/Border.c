#include<Windows.h>
#include"EasyWindow.h"
#include"Global.h"





typedef BOOL(*BTNFUNC)();//按钮按下后调用的函数



BTNFUNC MainUIBtnProc();

BTNFUNC DataRecordBtnProc();

BTNFUNC UsingFinishBtnProc();

BTNFUNC ShutDownBtnProc();

BTNFUNC ExitTyfLibSysProc();

//左侧边框按钮相关信息的结构体
typedef struct tagBorderButton
{
	int ID;
	TCHAR BtnName[32];
	BTNFUNC BtnFunc;

} BORDERBTN, * PBORDERBTN;

BORDERBTN BorderBtn[] = {
	0,TEXT("主界面"), MainUIBtnProc,
	0,TEXT("数据记录"),DataRecordBtnProc,
	0,TEXT("退出登录"), UsingFinishBtnProc,
	0,TEXT("关机"),ShutDownBtnProc,
	0,TEXT("关闭软件"),ExitTyfLibSysProc
};




#define BDBTN_NUM (sizeof(BorderBtn) / sizeof(BorderBtn[0]))



HFONT BtnFont;
LOGFONT lf;
EZWNDPROC BorderProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static EZWND hButton[BDBTN_NUM];
	int iCount;
	
	switch (message)
	{
	case EZWM_CREATE:

		SetEZWndTransparent(ezWnd, 100);

		
		{
			lf.lfHeight = (int)(CAPTIONHEIGHT*RATIO*RATIO);
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
			BtnFont = CreateFontIndirect(&lf);
		}

		for (iCount = 0; iCount < BDBTN_NUM; iCount++)
		{
			
			hButton[iCount] = CreateEZWindow(ezWnd, 0, iCount*CAPTIONHEIGHT*RATIO+ CAPTIONHEIGHT*RATIO*(1+RATIO), ezWnd->Width, CAPTIONHEIGHT*RATIO, BorderBtnProc);

			//其实下面这个语句一点也不地道，这明明是个指针嘛~，可是我不想再开一个ID变量，干脆拿指针放ID数据拉倒2333333
			hButton[iCount]->Extend = iCount;
		}
		
		return 0;
	case EZWM_TRANSDRAW:
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, BLACKNESS);
		return 0;
	case EZWM_DESTROY:
		DeleteObject(BtnFont);
	}
}

EZWNDPROC BorderBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{

		switch (message)
		{
		case EZWM_CREATE:
			SetEZWndTransparent(ezWnd, 0);
			return 0;
		case EZWM_MOUSECOME:
			SetEZWndTransparent(ezWnd, 35);
			EZRepaint(ezWnd, NULL);
			return 0;
		case EZWM_MOUSELEAVE:
			SetEZWndTransparent(ezWnd, 0);
			EZRepaint(ezWnd, NULL);
			return 0;
		case EZWM_TRANSDRAW:
			PatBlt(wParam, 4, 0, ezWnd->Width , ezWnd->Height, BLACKNESS);
			
			//PatBlt(wParam, ezWnd->Width - 4, 0, 4, ezWnd->Height, WHITENESS);
			return 0;
		case EZWM_LBUTTONDOWN:
			//OpenLock();
			BorderBtn[(int)(ezWnd->Extend)].BtnFunc();
			return 0;
		case EZWM_DRAW:

			//当透明度不为0，就绘制
			if (ezWnd->Transparent != 0)
			{
				PatBlt(wParam, 0, 0, 4, ezWnd->Height, WHITENESS);
			}
			//画图标，写字
			SelectObject(wParam, BtnFont);
			SetBkMode(wParam, TRANSPARENT);
			SetTextColor(wParam, RGB(255, 255, 255));
			TextOut(wParam, CAPTIONHEIGHT*RATIO, CAPTIONHEIGHT*RATIO*(1 - RATIO) / 2, BorderBtn[(int)(ezWnd->Extend)].BtnName, lstrlen(BorderBtn[(int)(ezWnd->Extend)].BtnName));

			return 0;
		}
		return 0;

}

BTNFUNC MainUIBtnProc()
{
	//打开主界面
	if (UIShow == MainUI)
	{
		return 0;
	}
	
	UIShow->ShowState = 2;
	UIShow->MouseMsgRecv = 2;

	UIShow = MainUI;


	UIShow->ShowState = 1;
	UIShow->MouseMsgRecv = 1;
	EZRepaint(MainUI, 0);
}

BTNFUNC DataRecordBtnProc()
{
	//打开数据记录界面
	if (UIShow == PkgRecUI)
	{
		return 0;
	}

	UIShow->ShowState = 2;
	UIShow->MouseMsgRecv = 2;

	UIShow = PkgRecUI;

	UIShow->ShowState = 1;
	UIShow->MouseMsgRecv = 1;
	EZRepaint(PkgRecUI, 0);
	return 0;
}

BTNFUNC UsingFinishBtnProc()
{
	//使用完毕
	LogoutFunc();
	
}


BTNFUNC ShutDownBtnProc()
{
	//关机
	if (MessageBox(NULL, TEXT("真的要关机？\r\n请确保你未完成的工作已经保存！"),
		TEXT("同一附图书馆管理系统"), MB_ICONWARNING | MB_OKCANCEL | MB_TASKMODAL) == IDOK)
	{
		ExitWindowsEx(EWX_FORCE, 0);
	}


}

BTNFUNC ExitTyfLibSysProc()
{
	//退出整个程序，包括弹出DLL，子进程。

	if (pMainData->AuthorityLevelList[pMainData->UserSelect] != 1)
	{
		MessageBox(NULL, TEXT("关闭软件需要管理员权限！"),
			TEXT("同一附图书馆管理系统"), MB_ICONERROR | MB_ICONINFORMATION | MB_TASKMODAL);
	}
	else
	{
		if (MessageBox(NULL, TEXT("这将彻底退出同一附图书馆管理系统。继续吗？"),
			TEXT("同一附图书馆管理系统"), MB_ICONQUESTION | MB_OKCANCEL | MB_TASKMODAL) == IDOK)
		{
			//执行一系列步骤关闭软件
			pMainData->bExit = 1;
			if (MainWnd)
			{
				DestroyEZWindow(MainWnd);
				MainWnd = 0;
			}
			if (LockWnd)
			{
				DestroyEZWindow(LockWnd);
				LockWnd = 0;
			}
			PostQuitMessage(0);
			return 0;
		}
	}
}