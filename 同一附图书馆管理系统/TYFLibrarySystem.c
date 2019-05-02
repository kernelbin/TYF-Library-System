#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<process.h>
#include"EasyWindow.h"
#include"Global.h"
#include"resource.h"
#include"ReplaceStr.h"
#include"jpeg.h"
#include<TlHelp32.h>
#include<math.h>
#include"../Public/Public.h"


#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"packet.lib")
#pragma comment(lib,"wpcap.lib")

#pragma comment(lib,"ws2_32.lib")

#ifdef _X86_
#pragma comment(lib,"libmysql32.lib")
#elif defined _AMD64_
#pragma comment(lib,"libmysql64.lib")
#endif




/****   函数定义   ****/

int ReplaceStr(char* sSrc, char* sMatchStr, char* sReplaceStr); 
//void GaussianBlur(unsigned char* img, unsigned  int x, unsigned int y, unsigned int w, unsigned int h, unsigned int comp, unsigned int radius);


void GaussianBlurFast(unsigned char* img, unsigned int width, unsigned int height, unsigned int channels, unsigned int radius);



static HBITMAP LoadJpegFromDataWithGauss(PBYTE pData, DWORD DataLength);

/****   宏和定义   ****/

//有关CMD
#define CMD_DEFAULT 0	//默认模式，检查是否重复打开，然后打开主界面。和服务器交换数据.

#define CMD_SAFE 1		//安全进程，后台。和DEFAULT互相检查，双进程守护


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	ReplaceStr(lpCmdLine, "/", "-");
	ReplaceStr(lpCmdLine, "\\", "-");
	hInst = hInstance;

	hMainData = NULL;
	pMainData = NULL;

	LockWnd = NULL;

	srand(time(0));


	/*MessageBox(NULL, TEXT("TEST"),
		TEXT("安全性保护"), MB_OK | MB_ICONERROR);*/
		//分析命令行
	{
		int CmdLen;
		//命令行存在lpCmdLine里，先判断长度
		CmdLen = strlen(lpCmdLine);
		if (CmdLen == 0)
		{
			Cmd_Mode = CMD_DEFAULT;
		}
		else
		{
			//反正命令行很简单，就那么几个参数。而且这些参数不允许重叠。我偷个懒，依次比较解决问题
			if ((strcmpi(lpCmdLine, ".exe -default") && strcmpi(lpCmdLine, "-default")) == 0)
			{
				Cmd_Mode = CMD_DEFAULT;
			}
			else if ((strcmpi(lpCmdLine, ".exe  -help") && strcmpi(lpCmdLine, "-help") && strcmpi(lpCmdLine, "-?") && strcmpi(lpCmdLine, ".exe  -?")) == 0)
			{
				MessageBox(NULL, TEXT("为确保程序的安全，如果您真的需要命令行参数\n请询问开发人员（高二（8）杨赫），或查阅程序源代码。"),
					TEXT("安全性保护"), MB_OK | MB_ICONINFORMATION);
				return 0;//退出程序
			}
			else if ((strcmpi(lpCmdLine, ".exe  -safe") && strcmpi(lpCmdLine, "-safe")) == 0)
			{
				Cmd_Mode = CMD_SAFE;
			}
			else
			{
				MessageBox(NULL, TEXT("命令行参数不正确！程序将自动退出！"),
					TEXT("安全性保护"), MB_OK | MB_ICONERROR);
				return 0;//退出程序
			}
		}

	}




	switch (Cmd_Mode)
	{
	case CMD_DEFAULT:
		return DefaultEntry();

	case CMD_SAFE:
		return SafeEntry();
	}

}



int DefaultEntry()
{

	MSG msg;

	InitEZWindow();

	GDIObjectCreate();
	//判断是否是唯一进程

	//检查数据

	if (MainDataLoad(FALSE))//加载数据
	{
		if (pMainData->MainKilled == 1)
		{
			//刚刚“死”了，现在“复活”了

			WriteLog(LOG_PROTECT, LOG_PROTECT_MAIN_KILLED, TEXT(""));
			pMainData->MainKilled = 0;
			pMainData->Main_PID = GetCurrentProcessId();
			_beginthreadex(0, 0, OpenProtectProcess, 0, 0, 0);

			//计时器
			SetTimer(NULL, APP_TIMER_ID, 1000, TimerProc);

			pMainData->UserCount = 0;

			pMainData->LoadState = LS_EMPTY;


			//从数据库加载数据
			_beginthreadex(0, 0, NetDataLoad, 0, 0, 0);

			//开始截获网络数据
			StartCapture();

			if (pMainData->IsLogin == FALSE)
			{
				//开锁
				OpenLock();

			}


		}
		else
		{
			//重复打开
			//通知进程，打开主界面。

			ReopenNoticeSema = NULL;
			if ((ReopenNoticeSema = OpenSemaphore(SEMAPHORE_ALL_ACCESS, 0, ReopenNoticeSemaName)) == NULL)
			{
				//奇怪，那就退出吧
				//添加错误处理。
				return 0;
			}
			else
			{
				//现在，ReopenNoticeSema就是信号量句柄。

				ReleaseSemaphore(ReopenNoticeSema, 1, NULL);

				CloseHandle(ReopenNoticeSema);
				ReopenNoticeSema = NULL;
			}
			return 0;
		}

	}
	else
	{

		WriteLog(LOG_EVENT, LOG_EVENT_START, TEXT(""));

		//创建数据
		MainDataCreate();
		MainDataOpen();


		pMainData->MainKilled = 0;
		pMainData->ProtectKilled = -1;

		pMainData->Main_PID = GetCurrentProcessId();

		pMainData->bExit = 0;

		pMainData->UserCount = 0;

		pMainData->LoadState = LS_EMPTY;

		//从数据库加载数据
		_beginthreadex(0, 0, NetDataLoad, 0, 0, 0);


		pMainData->LoadTime = 0;//既然是第一次打开，需要初始化。



		pMainData->IsLogin = FALSE;//是否登录

								   //计时器
		SetTimer(NULL, APP_TIMER_ID, 1000, TimerProc);

		//开始截获网络数据
		StartCapture();


		//启动保护进程
		_beginthreadex(0, 0, StartProtectProcess, 0, 0, 0);




		//开锁
		OpenLock();

	}

	ReopenNoticeSema = NULL;
	if ((ReopenNoticeSema = OpenSemaphore(SEMAPHORE_ALL_ACCESS, 0, ReopenNoticeSemaName)) == NULL)
	{
		//没有，那就对了！保护进程并不持有这个句柄r
		ReopenNoticeSema = CreateSemaphore(0, 0, 1, ReopenNoticeSemaName);//信号量现在为0，最大为1。
		_beginthreadex(0, 0, WaitForSem, 0, 0, 0);
	}
	else
	{
		//奇怪，那就退出吧
		CloseHandle(ReopenNoticeSema);
		//添加错误处理。
		return 0;
	}

	MainWnd = CreateEZParentWindow(0.15*GetSystemMetrics(SM_CXSCREEN),
		0.1*GetSystemMetrics(SM_CYSCREEN),
		0.7*GetSystemMetrics(SM_CXSCREEN),
		0.8*GetSystemMetrics(SM_CYSCREEN),
		WS_POPUP, MainProc, 0, NULL);

	ShowWindow(MainWnd->hParent, SW_SHOWDEFAULT);
	UpdateWindow(MainWnd->hParent);
	SetWindowText(MainWnd->hParent, TEXT("同一附图书馆管理系统"));


	//调试用

	//		CloseLock();


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//结束抓包
	EndCapture();

	MainDataDelete();//这个函数会自行检查数据，有就销毁（其实无关紧要，进程结束后，内核对象会全部被windows清理。）

	if (ReopenNoticeSema)
	{
		CloseHandle(ReopenNoticeSema);
	}
	GDIObjectClean();
	return msg.lParam;
}

int SafeEntry()
{
	//安全进程
	if (MainDataLoad(FALSE))//加载数据
	{
		//有数据

		if (pMainData->ProtectKilled == 1)
		{
			WriteLog(LOG_PROTECT, LOG_PROTECT_PROTECT_KILLED, TEXT(""));
		}

		if (pMainData->ProtectKilled == 1 || pMainData->ProtectKilled == -1)
		{
			//刚刚被关掉。

			pMainData->ProtectKilled = 0;

			pMainData->Protect_PID = GetCurrentProcessId();

			return OpenMainProcess();
		}
		else
		{
			//看来，重复打开了。
			return 0;
		}
	}
	return 0;

}



EZWNDPROC MainProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{

	static EZWND Caption;
	static EZWND LBorder;//左侧边框

	static int PicCount;
	HBITMAP hBitmap;
	static int IDTimer_Static, IDTimer_Dymanic;
	static int RefreshFrame;//当前帧数
	static HDC hdcMem, hdcMemLast;



	HDC hdcBuf;
	BITMAP bitmap;


	switch (message)
	{
	case EZWM_CREATE:

		InitMyAlphaBlend();
		//创建子窗口
		Caption = CreateEZWindow(ezWnd, 0, 0, ezWnd->Width, CAPTIONHEIGHT, CaptionProc);
		LBorder = CreateEZWindow(ezWnd, 0, CAPTIONHEIGHT, BORDERWIDTH, ezWnd->Height - CAPTIONHEIGHT, BorderProc);


		MainUI = CreateEZWindow(ezWnd, BORDERWIDTH, CAPTIONHEIGHT, ezWnd->Width - BORDERWIDTH, ezWnd->Height - CAPTIONHEIGHT, MainUIProc);
		PkgRecUI = CreateEZWindow(ezWnd, BORDERWIDTH, CAPTIONHEIGHT, ezWnd->Width - BORDERWIDTH, ezWnd->Height - CAPTIONHEIGHT, PackageRecUIProc);
		UIShow = MainUI;
		PkgRecUI->MouseMsgRecv = 2;
		PkgRecUI->ShowState = 2;

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

		hRes = LoadResource(NULL, hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_JPG1 + PicCount), TEXT("JPG")));

		/*	for (int bmpload = 0; bmpload < 20; bmpload++)
	{
			hBitmap = LoadJpegFromDataWithGauss(LockResource(hRes), SizeofResource(NULL, hRsrc));
			DeleteObject(hBitmap);
		}*/
		hBitmap = LoadJpegFromDataWithGauss(LockResource(hRes), SizeofResource(NULL, hRsrc));

		FreeResource(hRes);


		GetObject(hBitmap, sizeof(BITMAP), &bitmap);

		/*bits = malloc((bitmap.bmWidth*bitmap.bmHeight) << 2);


		GetBitmapBits(hBitmap,  (bitmap.bmWidth*bitmap.bmHeight)<< 2, bits);
		GaussianBlur(bits,bitmap.bmWidth,bitmap.bmHeight, 4, 10);
		SetBitmapBits(hBitmap, (bitmap.bmWidth*bitmap.bmHeight) << 2, bits);

		free(bits);*/
		//BytesToWrite = SizeofResource(NULL, hRsrc);


		//pData =;


		hdcMem = GetMemDC(ezWnd->hdc, ezWnd->Width, ezWnd->Height);
		hdcMemLast = GetMemDC(ezWnd->hdc, ezWnd->Width, ezWnd->Height);
		PatBlt(hdcMem, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);



		hdcBuf = CreateCompatibleDC(ezWnd->hdc);
		SelectObject(hdcBuf, hBitmap);


		SetStretchBltMode(hdcMem, HALFTONE);
		SetStretchBltMode(hdcMemLast, HALFTONE);
		StretchBlt(hdcMem,
			0, 0, ezWnd->Width, ezWnd->Height,
			hdcBuf, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


		DeleteDC(hdcBuf);
		DeleteObject(hBitmap);

		RefreshFrame = -1;
		IDTimer_Static = SetEZTimer(ezWnd, 30 * 1000);

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

			hBitmap = LoadJpegFromDataWithGauss(LockResource(hRes), SizeofResource(NULL, hRsrc));

			FreeResource(hRes);


			GetObject(hBitmap, sizeof(BITMAP), &bitmap);



			HDC hdcSwap;
			hdcSwap = hdcMem;
			hdcMem = hdcMemLast;
			hdcMemLast = hdcSwap;
			//BitBlt(hdcMemLast, 0, 0, ezWnd->Width, ezWnd->Height, hdcMem, 0, 0, SRCCOPY);

			//清空（重置hdcMem）的底色
			PatBlt(hdcMem, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);



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
				IDTimer_Static = SetEZTimer(ezWnd, 6 * 1000);
			}
		}

		EZRepaint(ezWnd, 0);
		//InvalidateRect(ezWnd->hParent, 0, 1);
		return 0;

	case EZWM_DRAW:

	{
		BLENDFUNCTION bf = { 0 };

		BitBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, hdcMem, 0, 0, SRCCOPY);

		if (RefreshFrame != -1)
		{
			/*bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER; 初始化全部为0了，而且AC_SRC_OVER == 0*/
			bf.SourceConstantAlpha = 255 - RefreshFrame * (6.375);
			AlphaBlend(wParam, 0, 0, ezWnd->Width, ezWnd->Height, hdcMemLast, 0, 0, ezWnd->Width, ezWnd->Height, bf);
			//MyAlphaBlend(wParam, 0,0,ezWnd->Width, ezWnd->Height, hdcMemLast,0,0, bf.SourceConstantAlpha);
			//Sleep(0);
		}

	}

	return 0;

	case EZWM_DESTROY:

		if (hdcMem)
		{
			DeleteDC(hdcMem);
		}
		if (hdcMemLast)
		{
			DeleteDC(hdcMemLast);
		}


	}
	return 0;
}




void __stdcall StartProtectProcess(void * var)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };
	TCHAR FileNameNow[MAX_PATH];
	GetModuleFileName(NULL, FileNameNow, MAX_PATH);
	if (CreateProcess(FileNameNow, TEXT(" -safe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0)
	{
		//创建进程失败
		//检查错误并上报服务器

	}

	switch (WaitForSingleObject(pi.hProcess, INFINITE))
	{
	case WAIT_OBJECT_0:
		//保护进程结束了，重启。
		pMainData->ProtectKilled = 1;
		pMainData->Protect_PID = NULL;
		_beginthreadex(0, 0, StartProtectProcess, 0, 0, 0);
		return;
	case WAIT_ABANDONED:
		//不应该，待改进，加入错误处理。

		return 0;
	case WAIT_FAILED:
		//出错，待处理。
		return 0;
	case WAIT_TIMEOUT:
		//明明设置的是无穷啊，错误处理
		return 0;
	}
	//这里！继续！判断CreateProcess,Waitfor……执行是否正确，并且在WaitFor 进程结束后重启保护进程。
	//保护进程可以通过OpenProcess找到主进程。
}

int OpenMainProcess()
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pMainData->Main_PID);

	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };


	TCHAR FileNameNow[MAX_PATH];
	GetModuleFileName(NULL, FileNameNow, MAX_PATH);


	for (; pMainData->bExit != 1;)
	{

		switch (WaitForSingleObject(hProcess, INFINITE))
		{
		case WAIT_OBJECT_0:
			//主进程结束了，重启。
			if (pMainData->bExit == 1)
			{
				//主进程标明了，退出。
				break;
			}
			pMainData->MainKilled = 1;
			pMainData->Main_PID = NULL;


			if (CreateProcess(FileNameNow, TEXT(""), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0)
			{
				//创建进程失败
				//检查错误并上报服务器

			}
			else
			{
				hProcess = pi.hProcess;
				break;//跳出switch进入for循环，重新开始等待
			}

		case WAIT_ABANDONED:
			//不应该，待改进，加入错误处理。

			return 0;
		case WAIT_FAILED:
			//出错，待处理。

			return 0;
		case WAIT_TIMEOUT:
			//明明设置的是无穷啊，错误处理

			return 0;
		}

	}

}

void __stdcall OpenProtectProcess(void * var)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pMainData->Protect_PID);

	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };
	//TCHAR FileNameNow[MAX_PATH];
	//GetModuleFileName(NULL, FileNameNow, MAX_PATH);
	//if (CreateProcess(FileNameNow, TEXT(" -safe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0)
	//{
	//	//创建进程失败
	//	//检查错误并上报服务器

	//}


	TCHAR FileNameNow[MAX_PATH];
	GetModuleFileName(NULL, FileNameNow, MAX_PATH);


Wait_Entry:

	switch (WaitForSingleObject(hProcess, INFINITE))
	{
	case WAIT_OBJECT_0:
		//保护进程结束了，重启。
		pMainData->ProtectKilled = 1;
		pMainData->Protect_PID = NULL;

		if (CreateProcess(FileNameNow, TEXT(" -safe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0)
		{
			//创建进程失败
			//检查错误并上报服务器
		}
		else
		{
			hProcess = pi.hProcess;
			goto Wait_Entry;
		}

		return;
	case WAIT_ABANDONED:
		//不应该，待改进，加入错误处理。

		return;
	case WAIT_FAILED:
		//出错，待处理。
		return;
	case WAIT_TIMEOUT:
		//明明设置的是无穷啊，错误处理
		return;
	}

}

void __stdcall WaitForSem(void * var)
{
	if (ReopenNoticeSema)
	{
		while (1)
		{
			switch (WaitForSingleObject(ReopenNoticeSema, INFINITE))
			{
			case WAIT_OBJECT_0:
				//收到信号！
				ShowWindow(MainWnd->hParent, SW_SHOWNORMAL);
				SetForegroundWindow(MainWnd->hParent);
				break;
			case WAIT_ABANDONED:
				//不应该，待改进，加入错误处理。

				return 0;
			case WAIT_FAILED:
				//出错，待处理。
				return;
			case WAIT_TIMEOUT:
				//明明设置的是无穷啊，错误处理
				return;
			}
		}
	}

}



BOOL OpenLock()
{
	//这里！试试CreateDesktop函数？

	if (LockWnd)
	{
		return FALSE;
	}
	LockWnd = CreateEZParentWindow(0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		WS_POPUP | WS_VISIBLE, LockProc, 0, NULL);
	SetWindowPos(LockWnd->hParent, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN), SWP_NOMOVE);
}

BOOL CloseLock()
{
	DestroyEZWindow(LockWnd);
	LockWnd = NULL;

}


BOOL NetLoadStateUpdate()//更新数据状态改变！
{
	//检查桌面锁是否打开，如果打开则refresh
	if (LockWnd)
	{
		EZRepaint(LockWnd, NULL);
	}
}


VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	DWORD TimeLeft;
	(pMainData->RunningTime)++;

	if (pMainData->RunningTime > pMainData->LoadTime + 45)
	{
		//过了45秒，定时刷新。
		BeginNetDataLoad();
	}
	if (pMainData->IsLogin == TRUE)
	{
		if (pMainData->TimeLimit != -1)//检查有没有时间限制
		{
			TimeLeft = pMainData->TimeLimit - (pMainData->RunningTime - pMainData->LoginTime);
			if (TimeLeft == 0)
			{
				//没时间了，退出！
				LogoutFunc();
			}
			else if (TimeLeft == 60)
			{
				//一分钟提醒
				MessageBox(NULL, TEXT("剩余使用时间还剩一分钟！\n请注意及时保存未完成的工作！"),
					TEXT("同一附图书馆管理系统"), MB_ICONINFORMATION | MB_SYSTEMMODAL);
			}
			else if (TimeLeft == 300)
			{
				//五分钟提醒
				MessageBox(NULL, TEXT("剩余使用时间还剩五分钟！\n请注意及时保存未完成的工作！"),
					TEXT("同一附图书馆管理系统"), MB_ICONINFORMATION | MB_SYSTEMMODAL);
			}
			else if (TimeLeft == 600)
			{
				//十分钟提醒
				MessageBox(NULL, TEXT("剩余使用时间还剩十分钟！"),
					TEXT("同一附图书馆管理系统"), MB_ICONINFORMATION | MB_SYSTEMMODAL);
			}
		}

	}
}


BOOL LoginFunc(int User)//User 是 用户列表数组的索引值
{
	//登录
	WriteLogA(LOG_EVENT, LOG_EVENT_LOGIN, pMainData->UsernameList[User]);

	pMainData->LoginTime = pMainData->RunningTime;//登录的时间
	pMainData->TimeLimit = pMainData->TimeLimitList[User];

	pMainData->IsLogin = TRUE;

	EZRepaint(MainWnd, NULL);
}

BOOL LogoutFunc()
{
	WriteLogA(LOG_EVENT, LOG_EVENT_LOGOUT, pMainData->UsernameList[pMainData->UserSelect]);
	if (pMainData->DeleteList[pMainData->UserSelect] != 0)
	{
		_beginthreadex(0, 0, LogoutDataRefresh, 0, 0, 0);
	}


	pMainData->IsLogin = FALSE;
	pMainData->LoginTime = 0;
	pMainData->TimeLimit = 0;
	OpenLock();
}




static HBITMAP LoadJpegFromDataWithGauss(PBYTE pData, DWORD DataLength)
{
	HBITMAP hBitmap;
	BYTE *picbuf;
	int info[8];
	struct DLL_STRPICENV env;
	hBitmap = 0;

	__try
	{
		if (info_JPEG(&env, info, DataLength, pData) == 0)
		{
			return 0;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}


	//info[0]保存的是类型

	picbuf = (PBYTE)malloc(info[2] * info[3] * sizeof(struct RGB));
	



	if (decode0_JPEG(&env, DataLength, pData, 4, picbuf, 0) != 0)
	{

		free(picbuf);

		return 0;
	}

	/*GaussianBlurFast(picbuf, info[2], info[3], 4, 16);
	GaussianBlurFast(picbuf, info[2], info[3], 4, 16);
	GaussianBlurFast(picbuf, info[2], info[3], 4, 16);
	GaussianBlurFast(picbuf, info[2], info[3], 4, 16);*/
	GaussianBlurFast(picbuf, info[2], info[3], 4, 32);
	
	
	hBitmap = CreateBitmap(info[2], info[3], 1, 32, picbuf);


	if (picbuf)
	{
		free(picbuf);
	}
	return hBitmap;
}





void GaussianBlurFast(unsigned char* img, unsigned int width, unsigned int height, unsigned int channels, unsigned int radius)
{
	radius = min(max(1, radius), 248);
	unsigned int kernelSize = 1 + radius << 1;
	unsigned int* kernel = (unsigned int*)malloc(kernelSize * sizeof(unsigned int));
	memset(kernel, 0, kernelSize * sizeof(unsigned int));
	int(*mult)[256] = (int(*)[256])malloc(kernelSize * sizeof(int) << 8);
	memset(mult, 0, kernelSize * sizeof(int) << 8);

	//	width += xStart - max(0, xStart);//(xStart + width) - width
	//	height += yStart - max(0, yStart);//(yStart + height) - height
	int imageSize = width * height;
	int widthstep = width * channels;

	int sqrt_rad = ceil(radius);
	if (channels == 3 || channels == 4)
	{
		unsigned char *    CacheImg = 0;
		CacheImg = (unsigned char *)malloc((sizeof(unsigned char) * imageSize << 2) + (sizeof(unsigned char) * imageSize << 1));
		if (!CacheImg) return;
		unsigned char *    rCache = CacheImg;
		unsigned char *    gCache = rCache + imageSize;
		unsigned char *    bCache = gCache + imageSize;
		unsigned char *    r2Cache = bCache + imageSize;
		unsigned char *    g2Cache = r2Cache + imageSize;
		unsigned char *    b2Cache = g2Cache + imageSize;
		

		unsigned int pow2_szi = (radius - 1) * (radius - 1);
		unsigned int RPK, RMK;
		RPK = radius + 1;
		RMK = radius - 1;
		
		for (int K = 1; K < radius; K++) 
		{
			pow2_szi += (1 - (RMK << 1));
		//	unsigned int szi = radius - K;
			
			kernel[RPK] = kernel[RMK] = pow2_szi;

			int kernelszibuf = 0;
			for (int j = 0; j < 256; j++) 
			{
				mult[RPK][j] = mult[RMK][j] = kernelszibuf;
				kernelszibuf += pow2_szi;
			}
			RPK++;
			RMK--;
		}
		kernel[radius] = radius * radius;


		int sum = 0;

		//百度出来的平方和公式，sum=1^2+2^2+3^2+4^2+.....+n^2+....+2^2+1^2 = 2(1^2+...+(n-1)^2) + n^2
		sum = (radius - 2)*(radius - 1)*((radius << 1) - 3) / 3;
		sum += kernel[radius];

		float fkernelsum = 1.0f / sum;
		for (int j = 0; j < 256; j++) 
		{
			mult[radius][j] = kernel[radius] * j;
		}
		unsigned char*     LinePS = img;// +Y * widthstep;
		unsigned char*     LinePR = rCache;// +Y * width;
		unsigned char*     LinePG = gCache;// +Y * width;
		unsigned char*     LinePB = bCache;// +Y * width;
		for (int Y = 0; Y < height; ++Y) 
		{
			int p2 = 0;
			for (int X = 0; X < width; ++X)
			{
				// = X * channels;
				LinePR[X] = LinePS[p2];
				LinePG[X] = LinePS[p2 + 1];
				LinePB[X] = LinePS[p2 + 2];
				p2 += channels;
			}
			LinePS += widthstep;
			LinePR += width;
			LinePG += width;
			LinePB += width;
		}
		
		

		int heightStep = 0;
		
		for (int Y = 0; Y < height; Y++) 
		{
			
			LinePR = rCache +heightStep;
			LinePG = gCache +heightStep;
			LinePB = bCache +heightStep;
			for (int X = 0; X < width; X++) {
				int cb = 0;
				int cg = 0;
				int cr = 0;

				for (int K = 0; K < kernelSize; K++) 
				{
					//((X - radius + K ) % width);
					int readPos = X - radius + K;
					if (readPos < 0)
					{
						//对称
						readPos = -readPos;
					}
					if (readPos >= width)
					{
						readPos = (((width - 1) << 1) - readPos);
					}
					int * pmult = mult[K];
					cr += pmult[LinePR[readPos]];
					cg += pmult[LinePG[readPos]];
					cb += pmult[LinePB[readPos]];
				}
				unsigned int p = heightStep + X;
				r2Cache[p] = cr * fkernelsum;
				g2Cache[p] = cg * fkernelsum;
				b2Cache[p] = cb * fkernelsum;
			}
			heightStep += width;
			/*LinePR += width;
			LinePG += width;
			LinePB += width;*/
		}

		LinePS = img;// +X * channels;
		LinePR = r2Cache;// +X;
		LinePG = g2Cache;// +X;
		LinePB = b2Cache;// +X;

		int WidthComp = 0;
		//int WidthStep = width * channels;
		for (int X = 0; X < width; X++) 
		{
			int    p = 0;
			for (int Y = 0; Y < height; Y++) 
			{
				int cb = 0;
				int cg = 0;
				int cr = 0;
				for (int K = 0; K < kernelSize; K++) 
				{
					int   readPos = Y - radius + K;
					if (readPos < 0)
					{
						//对称
						readPos = -readPos;
					}
					if (readPos >= height)
					{
						readPos = (((height - 1) << 1) - readPos);
					}

					readPos*= width;

					int * pmult = mult[K];
					cr += pmult[LinePR[readPos]];
					cg += pmult[LinePG[readPos]];
					cb += pmult[LinePB[readPos]];
				}
				
				LinePS[p] = (unsigned char)(cr * fkernelsum);
				LinePS[p + 1] = (unsigned char)(cg * fkernelsum);
				LinePS[p + 2] = (unsigned char)(cb* fkernelsum);

				p += widthstep;
			}

			WidthComp += channels;
			LinePS += channels;
			LinePR++;
			LinePG++;
			LinePB++;
		}
		free(CacheImg);
	}
	else if (channels == 1)
	{
		unsigned char *    CacheImg = 0;
		CacheImg = (unsigned char *)malloc(sizeof(unsigned char) * imageSize << 1);
		if (CacheImg == 0) return;
		unsigned char *    rCache = CacheImg;
		unsigned char *    r2Cache = CacheImg + imageSize;

		int sum = 0;
		for (int K = 1; K < radius; K++) {
			unsigned int szi = radius - K;
			kernel[radius + K] = kernel[szi] = szi * szi;
			sum += kernel[szi] + kernel[szi];
			for (int j = 0; j < 256; j++) {
				mult[radius + K][j] = mult[szi][j] = kernel[szi] * j;
			}
		}
		kernel[radius] = radius * radius;
		sum += kernel[radius];
		for (int j = 0; j < 256; j++) {
			mult[radius][j] = kernel[radius] * j;
		}
		for (int Y = 0; Y < height; ++Y) {
			unsigned char*     LinePS = img + Y * widthstep;
			unsigned char*     LinePR = rCache + Y * width;
			for (int X = 0; X < width; ++X) {
				LinePR[X] = LinePS[X];
			}
		}
		int kernelsum = 0;
		for (int K = 0; K < kernelSize; K++) {
			kernelsum += kernel[K];
		}
		float fkernelsum = 1.0f / kernelsum;
		for (int Y = 0; Y < height; Y++) {
			int heightStep = Y * width;
			unsigned char*     LinePR = rCache + heightStep;
			for (int X = 0; X < width; X++) {
				int cb = 0;
				int cg = 0;
				int cr = 0;
				for (int K = 0; K < kernelSize; K++) {
					unsigned    int     readPos = ((X - radius + K + width) % width);
					int * pmult = mult[K];
					cr += pmult[LinePR[readPos]];
				}
				unsigned int p = heightStep + X;
				r2Cache[p] = cr * fkernelsum;
			}
		}
		for (int X = 0; X < width; X++) {
			int WidthComp = X * channels;
			int WidthStep = width * channels;
			unsigned char*     LinePS = img + X * channels;
			unsigned char*     LinePR = r2Cache + X;
			for (int Y = 0; Y < height; Y++) {
				int cb = 0;
				int cg = 0;
				int cr = 0;
				for (int K = 0; K < kernelSize; K++) {
					unsigned int   readPos = ((Y - radius + K + height) % height) * width;
					int * pmult = mult[K];
					cr += pmult[LinePR[readPos]];
				}
				int    p = Y * WidthStep;
				LinePS[p] = (unsigned char)(cr* fkernelsum);
			}
		}
		free(CacheImg);
	}
	free(kernel);
	free(mult);
}


int MulTable[256][256];

BOOL InitMyAlphaBlend()
{
	int i, j;
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			MulTable[i][j] = i * j;
		}
	}
	return 0;
}


BOOL MyAlphaBlend(HDC hdcSrc, int x,int y,int w, int h, HDC hdcDst, int x1,int y1,BYTE t)//使用条件：hdcSrc hdcDst都与显示器兼容,一个像素4字节
{
	//HDC hdcSrcRP = CreateCompatibleDC(hdcSrc);
	//HDC hdcDstRP = CreateCompatibleDC(hdcDst);
	//HBITMAP hbSrc = CreateCompatibleBitmap(hdcSrc, w, h);
	//HBITMAP hbDst = CreateCompatibleBitmap(hdcSrc, w, h);

	//PBYTE pBSrc, pBDst;
	//long wh4 = w * h << 2;
	//SelectObject(hdcSrcRP, hbSrc);
	//SelectObject(hdcDstRP, hbDst);

	//BitBlt(hdcSrcRP, 0, 0, w, h, hdcSrc, 0, 0, SRCCOPY);
	//BitBlt(hdcDstRP, 0, 0, w, h, hdcDst, 0, 0, SRCCOPY);

	//pBSrc = malloc(w*h << 2);
	//pBDst = malloc(w*h << 2);

	//GetBitmapBits(hbSrc, wh4, pBSrc);
	//GetBitmapBits(hbDst, wh4, pBDst);

	////一次处理两个像素
	//if (w % 2 && h % 2)
	//{
	//	//w是奇数，h也是。
	//	int looptime = (wh4 - 1) >> 1;
	//	int i;
	//	for (i = 0; i < looptime; i += 8)
	//	{
	//		pBSrc[i] = (MulTable[pBSrc[i]][((~t) & 255)] + MulTable[pBDst[i]][t]) >> 8;
	//		pBSrc[i + 1] = (MulTable[pBSrc[i + 1]][((~t) & 255)] + MulTable[pBDst[i + 1]][t]) >> 8;
	//		pBSrc[i + 2] = (MulTable[pBSrc[i + 2]][((~t) & 255)] + MulTable[pBDst[i + 2]][t]) >> 8;

	//		pBSrc[i + 4] = (MulTable[pBSrc[i + 4]][((~t) & 255)] + MulTable[pBDst[i + 4]][t]) >> 8;
	//		pBSrc[i + 5] = (MulTable[pBSrc[i + 5]][((~t) & 255)] + MulTable[pBDst[i + 5]][t]) >> 8;
	//		pBSrc[i + 6] = (MulTable[pBSrc[i + 6]][((~t) & 255)] + MulTable[pBDst[i + 6]][t]) >> 8;
	//	}
	//	pBSrc[i] = (MulTable[pBSrc[i]][((~t) & 255)] + MulTable[pBDst[i]][t]) >> 8;
	//	pBSrc[i + 1] = (MulTable[pBSrc[i + 1]][((~t) & 255)] + MulTable[pBDst[i + 1]][t]) >> 8;
	//	pBSrc[i + 2] = (MulTable[pBSrc[i + 2]][((~t) & 255)] + MulTable[pBDst[i + 2]][t]) >> 8;
	//}
	//else
	//{
	//	for (int i = 0; i < wh4; i += 8)
	//	{
	//		/*pBSrc[i]     = (pBSrc[i]     * ((~t) & 255) + pBDst[i]     * t) >> 8;
	//		pBSrc[i + 1] = (pBSrc[i + 1] * ((~t) & 255) + pBDst[i + 1] * t) >> 8;
	//		pBSrc[i + 2] = (pBSrc[i + 2] * ((~t) & 255) + pBDst[i + 2] * t) >> 8;

	//		pBSrc[i + 4] = (pBSrc[i + 4] * ((~t) & 255) + pBDst[i + 4] * t) >> 8;
	//		pBSrc[i + 5] = (pBSrc[i + 5] * ((~t) & 255) + pBDst[i + 5] * t) >> 8;
	//		pBSrc[i + 6] = (pBSrc[i + 6] * ((~t) & 255) + pBDst[i + 6] * t) >> 8;*/
	//		pBSrc[i]     = ( MulTable[pBSrc[i]][((~t) & 255)]     + MulTable[pBDst[i]][t]    ) >> 8;
	//		pBSrc[i + 1] = ( MulTable[pBSrc[i + 1]][((~t) & 255)] + MulTable[pBDst[i + 1]][t]) >> 8;
	//		pBSrc[i + 2] = ( MulTable[pBSrc[i + 2]][((~t) & 255)] + MulTable[pBDst[i + 2]][t]) >> 8;

	//		pBSrc[i + 4] = ( MulTable[pBSrc[i + 4]][((~t) & 255)] + MulTable[pBDst[i + 4]][t]) >> 8;
	//		pBSrc[i + 5] = ( MulTable[pBSrc[i + 5]][((~t) & 255)] + MulTable[pBDst[i + 5]][t]) >> 8;
	//		pBSrc[i + 6] = ( MulTable[pBSrc[i + 6]][((~t) & 255)] + MulTable[pBDst[i + 6]][t]) >> 8;
	//	}
	//}
	//
	//SetBitmapBits(hbSrc, w*h << 2, pBSrc);
	////SetBitmapBits(hbDst, w*h << 2, pBSrc);
	////hbSrc = 
	//SelectObject(hdcSrcRP, hbSrc);
	////hbDst = 
	//BitBlt(hdcSrc, 0, 0, w, h, hdcSrcRP, 0, 0, SRCCOPY);
	////SelectObject(hdcDst, hbDst);
	//free(pBSrc);
	//free(pBDst);
	//DeleteObject(hbSrc);
	//DeleteObject(hbDst);
	//DeleteDC(hdcSrcRP);
	//DeleteDC(hdcDstRP);





	
	

	HBITMAP hBmpSrcRP,hBmpDstRP,hBitmapSrc,hBitmapDst;
	BITMAP bmp;
	PBYTE pBSrc, pBDst;
	int sx, dx;
	long wh4 = w * h << 2;


	hBmpSrcRP = CreateCompatibleBitmap(hdcSrc, 1, 1);
	hBmpDstRP = CreateCompatibleBitmap(hdcDst, 1, 1);

	hBitmapSrc = SelectObject(hdcSrc, hBmpSrcRP);
	hBitmapDst = SelectObject(hdcDst, hBmpDstRP);

	GetObject(hBitmapSrc, sizeof(BITMAP), &bmp);
	sx = bmp.bmWidth;
	GetObject(hBitmapDst, sizeof(BITMAP), &bmp);
	dx = bmp.bmWidth;

	pBSrc = malloc(wh4);
	pBDst = malloc(wh4);

	GetBitmapBits(hBitmapSrc, wh4, pBSrc);
	GetBitmapBits(hBitmapDst, wh4, pBDst);

	//按行来

	//一次处理两个像素
	if (w % 2)
	{
		//w是奇数
		//按行循环
		int lc;//line count
		int looptime = (w - 1) <<2;

		PBYTE pBSLine, pBDLine;
		pBSLine = pBSrc + ((y * sx + x) << 2);
		pBDLine = pBDst + ((y1 * dx + x1) << 2);
		for (lc = 0; lc < h; lc++)
		{
			int i;
			
			
			for (i = 0; i < looptime; i += 8)
			{
				pBSLine[i] = (MulTable[pBSLine[i]][((~t) & 255)] + MulTable[pBDLine[i]][t]) >> 8;
				pBSLine[i + 1] = (MulTable[pBSLine[i + 1]][((~t) & 255)] + MulTable[pBDLine[i + 1]][t]) >> 8;
				pBSLine[i + 2] = (MulTable[pBSLine[i + 2]][((~t) & 255)] + MulTable[pBDLine[i + 2]][t]) >> 8;

				pBSLine[i + 4] = (MulTable[pBSLine[i + 4]][((~t) & 255)] + MulTable[pBDLine[i + 4]][t]) >> 8;
				pBSLine[i + 5] = (MulTable[pBSLine[i + 5]][((~t) & 255)] + MulTable[pBDLine[i + 5]][t]) >> 8;
				pBSLine[i + 6] = (MulTable[pBSLine[i + 6]][((~t) & 255)] + MulTable[pBDLine[i + 6]][t]) >> 8;
			}
			pBSLine[i] = (MulTable[pBSLine[i]][((~t) & 255)] + MulTable[pBDLine[i]][t]) >> 8;
			pBSLine[i + 1] = (MulTable[pBSLine[i + 1]][((~t) & 255)] + MulTable[pBDLine[i + 1]][t]) >> 8;
			pBSLine[i + 2] = (MulTable[pBSLine[i + 2]][((~t) & 255)] + MulTable[pBDLine[i + 2]][t]) >> 8;

			pBSLine += sx << 2;
			pBDLine += dx << 2;
		}
		
		
	}
	else
	{
		//w是偶数
		//按行循环
		int lc;//line count
		int looptime = w <<2 ;

		PBYTE pBSLine, pBDLine;
		pBSLine = pBSrc + ((y * sx + x) << 2);
		pBDLine = pBDst + ((y1 * dx + x1) << 2);
		for (lc = 0; lc < h; lc++)
		{
			int i;


			for (i = 0; i < looptime; i += 8)
			{
				pBSLine[i] = (MulTable[pBSLine[i]][((~t) & 255)] + MulTable[pBDLine[i]][t]) >> 8;
				pBSLine[i + 1] = (MulTable[pBSLine[i + 1]][((~t) & 255)] + MulTable[pBDLine[i + 1]][t]) >> 8;
				pBSLine[i + 2] = (MulTable[pBSLine[i + 2]][((~t) & 255)] + MulTable[pBDLine[i + 2]][t]) >> 8;

				pBSLine[i + 4] = (MulTable[pBSLine[i + 4]][((~t) & 255)] + MulTable[pBDLine[i + 4]][t]) >> 8;
				pBSLine[i + 5] = (MulTable[pBSLine[i + 5]][((~t) & 255)] + MulTable[pBDLine[i + 5]][t]) >> 8;
				pBSLine[i + 6] = (MulTable[pBSLine[i + 6]][((~t) & 255)] + MulTable[pBDLine[i + 6]][t]) >> 8;
			}
			
			pBSLine += sx << 2;
			pBDLine += dx << 2;
		}
	}

	SetBitmapBits(hBitmapSrc, wh4, pBSrc);

	DeleteObject(SelectObject(hdcSrc, hBitmapSrc));
	DeleteObject(SelectObject(hdcDst, hBitmapDst));

	free(pBSrc);
	free(pBDst);
}