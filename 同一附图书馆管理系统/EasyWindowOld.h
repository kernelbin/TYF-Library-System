#pragma once

#include<Windows.h>
#include<windowsx.h>
#include"GetMemDC.h"



//*********************************************************************************************************

//*********************************************************************************************************

//下面是对EasyWindows消息的定义

//常规消息
#define EZWM_CREATE 1
#define EZWM_DESTROY 2
#define EZWM_SIZE 3
#define EZWM_TIMER 4

#define EZWM_ENABLE 5
#define EZWM_DISABLE 6

#define EZWM_SETFOCUS 7
#define EZWM_KILLFOCUS 8



//绘制有关消息
#define EZWM_DRAW 101//绘制，不透明
#define EZWM_TRANSDRAW 102//透明绘制，该次绘制将以透明形式覆盖。

//鼠标消息
#define EZWM_LBUTTONDOWN 201
#define EZWM_LBUTTONUP 202
#define EZWM_MOUSEMOVE 203//这个消息如果WPARAM为1，（仅发送到EZ主窗口）说明从Win窗口出去了
#define EZWM_MOUSECOME 204
#define EZWM_MOUSELEAVE 205


//键盘消息
#define EZWM_CHAR 301
#define EZWM_KEYDOWN 302
#define EZWM_KEYUP 303

//内置消息
#define SEZWM_COPYDC 1001//将存储DC复制。
#define SEZWM_REDRAW 1002//重绘到内存DC
#define SEZWM_MOUSECOME 1003
#define SEZWM_MOUSELEAVE 1004//老鼠离开顶层窗口，子窗口们自行检查。,wP是要排除检查的窗口

#define SEZWM_KILLFOCUS 1005//有焦点的窗口失去焦点。wP排除检查。


// #define SEZWM_CAPTURE 1005//有一个窗口申请捕获老鼠。已经捕获了的赶紧放掉！



HINSTANCE ezhInst;




//先定义字窗口结构体


#define EZWindowClass TEXT("EZWindowClass")

typedef struct tagEZWND * EZWND;
typedef int(*EZWNDPROC)(EZWND, int, WPARAM, LPARAM);


//这个是对EZWINDOW结构体的定义。EZWND是指向该结构的指针。
typedef struct tagEZWND
{
	//有关窗口信息
	int x;
	int y;
	int Width;
	int Height;

	//有关绘制状态****************************
	BYTE Transparent;//透明度，0是完全透明，255不透明

					//有关窗口状态****************************
	int FocusState;//输入焦点状态。0-无焦点。1-有焦点 
	int Show;//是否显示，以及显示的状态。


			 //有关鼠标****************************
	BOOL MouseOn;//鼠标在该窗口上。


				 //有关绘制****************************
	HDC hdc;//一个绘制空间。始终存在，直到窗口被销毁。窗口绘制就绘制在这个上面。
	HDC hdcWC;//hdcWithChild。子窗口将被覆盖绘制在这里
	BOOL Update;//更新区域，0为无需更新，1为发生了改变，需要更新。


				//有关关联窗口****************************
	EZWNDPROC ezWndProc;//窗口过程
	struct tagEZWND * ezParent;//EZ父窗口
	struct tagEZWND * ezRootParent;//EZ祖先窗口

	BOOL IsTopWindow;//用于指示是否是顶层EZ窗口。
	HWND hParent;//祖先Win窗口.

	struct tagEZWND * FirstChild;//第一个子窗口
	struct tagEZWND * LastEZWnd;//（和这个窗口）并列的上一个窗口
	struct tagEZWND * NextEZWnd;//（和这个窗口）并列的下一个窗口

	//仅父窗口使用，用于便捷管理。******
	EZWND FocusWindow;//拥有输入焦点的窗口

}EZWINDOW;



//*******************************************************************************************
//                函数声明
//*******************************************************************************************

static BOOL InitEZWindow(HINSTANCE hInstance);
static EZWND CreateEZParetntWindowEx(int x, int y, int Width, int Height, DWORD Style, EZWNDPROC ezWndProc, HMENU hMenu, HWND hParent);
static EZWND CreateEZWindow(EZWND ezParent, int x, int y, int Width, int Height, EZWNDPROC ezWndProc);
static BOOL DestroyEZWindow(EZWND ezWnd);
static BOOL DestroyEZWindowWithNext(EZWND ezWnd);
static BOOL MoveEZWindow(EZWND ezWnd, int x, int y, int Width, int Height, BOOL repaint);
static BOOL EZRedraw(EZWND ezWnd);
static BOOL EZUpdate(EZWND ezWnd, HDC hdc);
static BOOL EZRepaint(EZWND ezWnd, HDC hdc);
static BOOL EZAddChild(EZWND ezParent, EZWND ezChild);
static int EZSendMessage(EZWND ezwnd, int message, WPARAM wparam, LPARAM lparam);
static LRESULT CALLBACK EZParentWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
static int ezInsideWndProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static BOOL PtInEZWnd(EZWND ezWnd, int x, int y);
static BOOL EZBroadcastToAllChild(EZWND ezWnd, BOOL sequence, int message, WPARAM wp, LPARAM lp);
static BOOL BroadcastProc(EZWND ezWnd, int Param, WPARAM wP, LPARAM lP);
static EZWND EZGetTopParentWindow(EZWND ezWnd);
static BOOL SetEZWndTransparent(EZWND ezWnd, int Transparent);
static BOOL IsEZWindow(EZWND ezWnd);

//函数宏定义
#define CreateEZParetntWindow(x, y, Width, Height,  ezWndProc, hMenu, hParent) CreateEZParetntWindowEx(x, y, Width, Height,  WS_CHILD|WS_VISIBLE, ezWndProc, hMenu, hParent) 

//#define IsEZWindow(ezWnd) (ezWnd)?TRUE:FALSE

//初始化EasyWindow库函数
BOOL InitEZWindow(HINSTANCE hInstance)
{
	WNDCLASS wndclass;
	//复制实例句柄********待改价，增加检查是否有效
	ezhInst = hInstance;

	//注册窗口类
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = EZParentWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(EZWND);
	wndclass.hInstance = ezhInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = EZWindowClass;
	RegisterClass(&wndclass);
	return TRUE;
	//待改进，检查是否注册成功。
}



//创建窗口函数
EZWND CreateEZParetntWindowEx(int x, int y, int Width, int Height, DWORD Style, EZWNDPROC ezWndProc, HMENU hMenu, HWND hParent)
{
	HWND hwndParent;//这是Windows句柄的父窗口
	EZWND ezwndParent;//这是和Win窗口等大的EZ窗口，返回给用户。该窗口摧毁时同时摧毁Win窗口
	HDC fhdc;

	ezwndParent = (EZWND)malloc(sizeof(EZWINDOW));

	

	//Create tht EZ Window With out Using "CreateEZWindow"
	
	if (!ezwndParent)//检查内存
	{
		return (EZWND)0;
	}
	ezwndParent->x = x;
	ezwndParent->y = y;
	ezwndParent->Width = Width;
	ezwndParent->Height = Height;


	ezwndParent->FirstChild = NULL;
	ezwndParent->LastEZWnd = NULL;
	ezwndParent->NextEZWnd = NULL;
	ezwndParent->ezParent = NULL;//没有，空。
	ezwndParent->ezRootParent = ezwndParent;//你自己
	ezwndParent->IsTopWindow = TRUE;//是的，是顶层窗口。

	ezwndParent->FocusState = FALSE;

	ezwndParent->MouseOn = FALSE;

	ezwndParent->Update = FALSE;//刚开始，肯定没有更新过。

	ezwndParent->Transparent = 255;//不透明

	ezwndParent->ezWndProc = ezWndProc;

	ezwndParent->FocusWindow = NULL;


	//大部分内容都初始化完毕了。ezwndParent被作为参数提交给WM_CREATE消息，并在期间将这个指针设置为窗口扩展
	hwndParent = CreateWindow(EZWindowClass, TEXT(""), Style, x, y, Width, Height, hParent, hMenu, ezhInst, ezwndParent);


									  //根据父（Win）窗口获得一个DC
	fhdc = GetDC(hwndParent);
	ezwndParent->hdc = GetMemDC(fhdc, Width, Height);
	ezwndParent->hdcWC = GetMemDC(fhdc, Width, Height);
	ReleaseDC(hwndParent, fhdc);



	//将Win父窗口扩展指向EZ窗口
	//SetWindowLong(hwndParent, 0, (LONG)ezwndParent);
	//现在，我们进行绘制。这样，在WM_PAINT到来的时候就可以直接Bitblt了。这个步骤.....子窗口貌似不需要
	
	EZRepaint(ezwndParent, NULL);
	
	return ezwndParent;


}

EZWND CreateEZWindow(EZWND ezParent, int x, int y, int Width, int Height, EZWNDPROC ezWndProc)
{
	HWND hParent;
	EZWND ezWnd;
	HDC fhdc;
	if (!IsEZWindow(ezParent))
	{
		return (EZWND)0;
	}
	

	if (!(ezWnd = (EZWND)malloc(sizeof(EZWINDOW))))//创建并检查内存
	{
		return (EZWND)0;
	}


	ezWnd->x = x;
	ezWnd->y = y;
	ezWnd->Width = Width;
	ezWnd->Height = Height;
	ezWnd->FirstChild = NULL;
	ezWnd->LastEZWnd = NULL;
	ezWnd->NextEZWnd = NULL;
	ezWnd->hParent = ezParent->hParent;
	ezWnd->IsTopWindow = FALSE;//并不是


	ezWnd->FocusState = 0;

	ezWnd->MouseOn = FALSE;


	ezWnd->Update = 1;//刚开始，肯定没有更新过。

	ezWnd->Transparent = 255;//不透明

	ezWnd->ezParent = ezParent;
	ezWnd->ezRootParent = ezParent->ezRootParent;
	ezWnd->ezWndProc = ezWndProc;

	//在EZ父窗口最后追加这个新的子窗口。
	EZAddChild(ezParent, ezWnd);

	fhdc = GetDC(hParent = ezParent->hParent);
	ezWnd->hdc = GetMemDC(fhdc, Width, Height);
	ezWnd->hdcWC = GetMemDC(fhdc, Width, Height);
	ReleaseDC(hParent, fhdc);

	
	EZSendMessage(ezWnd, EZWM_CREATE, 0, 0);//发送创建消息
	MoveEZWindow(ezWnd, x, y, Width, Height, 0);
	return ezWnd;

}

BOOL EZAddChild(EZWND ezParent, EZWND ezChild)
{
	EZWND ezChildLast;
	//将子窗口追加在ezParent的子窗口链表最后
	if (!IsEZWindow(ezParent->FirstChild))
	{
		ezParent->FirstChild = ezChild;
		return TRUE;
	}

	
	
	//子窗口链表第一个不为空

	ezChildLast = ezParent->FirstChild;


	for (;;)//循环到链表最后
	{
		if (IsEZWindow(ezChildLast->NextEZWnd))
		{
			ezChildLast = ezChildLast->NextEZWnd;//向下移动
		}
		else
		{
			ezChild->LastEZWnd = ezChildLast;
			ezChildLast->NextEZWnd = ezChild;
			break;
		}
	}

	
	
	return TRUE;
}




//销毁窗口函数
BOOL DestroyEZWindow(EZWND ezWnd)
{
	if (ezWnd->IsTopWindow)
	{
		DestroyWindow(ezWnd->hParent);//这就行了，销毁会在这里完成
		return TRUE;
	}

	//先保存信息，倒推，消除所有子孙窗口
	if (IsEZWindow(ezWnd->FirstChild))
	{
		DestroyEZWindowWithNext(ezWnd->FirstChild);
	}
	//把你自己清理了
	EZSendMessage(ezWnd, EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//发送销毁信息
	DeleteDC(ezWnd->hdc);//清理DC
	DeleteDC(ezWnd->hdcWC);//清理DCWC
						   
	
	free(ezWnd);
	ezWnd = NULL;
	return TRUE;

}

BOOL DestroyEZWindowWithNext(EZWND ezWnd)
{
	EZWND ezChildLast;

	//回滚，准备清理并列窗口
	if (IsEZWindow(ezWnd->NextEZWnd))
	{
		ezChildLast = ezWnd->NextEZWnd;

		//循环到链表最后
		while(1)
		{
			if (!IsEZWindow(ezChildLast->NextEZWnd))
			{
				break;
				//最后，跳出。
			}

			ezChildLast = ezChildLast->NextEZWnd;
		}


		//再循环滚回链表最前（一边滚一边删）
		while (1)
		{
			//为了数据，先回滚，然后通过向下的指针找回去，删了
			if (IsEZWindow(ezChildLast->LastEZWnd))//还没到头
			{
				ezChildLast = ezChildLast->LastEZWnd;//回滚

													 //这时，ezChildLast->NextEZWnd就是最后一个。DestroyEZWindow会删了该窗口和这个窗口的子窗口。
				DestroyEZWindow(ezChildLast->NextEZWnd);//删了
				continue;
			}
			
			//没有continue，也就是else.
			//滚动到头了，DestroyEZWindow会删了该窗口和这个窗口的子窗口。
			DestroyEZWindow(ezChildLast);

			return TRUE;
		}
		
	}
	else
	{//你就是最后一个并列窗口。
		DestroyEZWindow(ezWnd);//删了
	}
	return TRUE;
}



//对窗口进行调整（判断）的函数
//BOOL IsEZWindow(EZWND ezWnd)
//{
//	if (!ezWnd)
//	{
//		return FALSE;
//	}
//	else
//	{
//		return TRUE;
//	}
//}

BOOL MoveEZWindow(EZWND ezWnd, int x, int y, int Width, int Height, BOOL repaint)
{
	HDC fhdc;//临时DC

	ezWnd->x = x;
	ezWnd->y = y;
	ezWnd->Width = Width;
	ezWnd->Height = Height;
	if (ezWnd->IsTopWindow)
	{
		MoveWindow(ezWnd->hParent, x, y, Width, Height, FALSE);
	}


	//暂时清理DC，然后重新获得一个。
	DeleteDC(ezWnd->hdc);
	DeleteDC(ezWnd->hdcWC);

	fhdc = GetDC(ezWnd->hParent);
	ezWnd->hdc = GetMemDC(fhdc, Width, Height);
	ezWnd->hdcWC = GetMemDC(fhdc, Width, Height);
	ReleaseDC(ezWnd->hParent, fhdc);

	EZSendMessage(ezWnd, EZWM_SIZE, (WPARAM)NULL, (LPARAM)MAKELPARAM(Width, Height));
	if (repaint)
	{
		
		EZRepaint(ezWnd, NULL);
	}

	return TRUE;
}



//与窗口绘制有关的函数
BOOL EZRedraw(EZWND ezWnd)//重绘到内存dc,不更新。
{
	BroadcastProc(ezWnd, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);

	EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);

	return TRUE;
}

BOOL EZUpdate(EZWND ezWnd, HDC hdc)//将DC更新到窗体，不重绘。第二个参数是DC，如不提供，函数将自动获取。
{
	//找到你的“祖宗”、
	EZWND ezRootWnd;
	HDC hdcg;

	ezRootWnd = EZGetTopParentWindow(ezWnd);//得到顶层窗口







		if (!hdc)//没DC
		{
			hdcg = GetDC(ezRootWnd->hParent);
		}
		else
		{
			hdcg = NULL;
		}
		int Countx = 0, County = 0;

		EZBroadcastToAllChild(ezWnd, FALSE, SEZWM_COPYDC, (WPARAM)NULL, (LPARAM)NULL);
		//BitBlt(hdcg, 0, 0, ezRootWnd->Width, ezRootWnd->Height, ezRootWnd->hdcWC, 0, 0, SRCCOPY);

		//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
		EZWND WndNow = ezWnd;

		while(1)
		{
			//向上推，直到父窗口
			if (!WndNow->IsTopWindow)
			{
				Countx += WndNow->x;
				County += WndNow->y;
				WndNow = WndNow->ezParent;
				continue;
			}
			
			break;
			
		}
		
		
		if (!hdc)//没DC
		{
			BitBlt(hdcg, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->hdcWC, 0, 0, SRCCOPY);
			ReleaseDC(ezRootWnd->hParent, hdcg);
		}
		else
		{
			BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->hdcWC, 0, 0, SRCCOPY);
		}


	return 0;
}

BOOL EZRepaint(EZWND ezWnd, HDC hdc)//重绘并且更新
{
	EZRedraw(ezWnd);
	EZUpdate(ezWnd, hdc);
	return TRUE;
}






int EZSendMessage(EZWND ezwnd, int message, WPARAM wparam, LPARAM lparam)
{
	return ezwnd->ezWndProc(ezwnd, message, wparam, lparam);
}


LRESULT CALLBACK EZParentWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TRACKMOUSEEVENT tme;

	switch (message)
	{
	case WM_CREATE:
		
		SetWindowLong(hwnd, 0, (((LPCREATESTRUCT)lParam)->lpCreateParams));
		((EZWND)((LPCREATESTRUCT)lParam)->lpCreateParams)->hParent = hwnd;//设置Win父窗口
		EZSendMessage((EZWND)((LPCREATESTRUCT)lParam)->lpCreateParams, EZWM_CREATE, 0, 0);//发送创建消息
		

		return 0;
	case WM_SIZE:

		
		((EZWND)(GetWindowLong(hwnd, 0)))->Width = 1;
		((EZWND)(GetWindowLong(hwnd, 0)))->Width = LOWORD(lParam);
		((EZWND)(GetWindowLong(hwnd, 0)))->Height = GET_Y_LPARAM(lParam);

		DeleteDC(((EZWND)(GetWindowLong(hwnd, 0)))->hdc);
		DeleteDC(((EZWND)(GetWindowLong(hwnd, 0)))->hdcWC);

		//HDC fhdc;
		//其实，本应该用这个变量.但是？hdc变量现在不正闲着吗？？？干脆就用那个吧，省内存


		hdc = GetDC(((EZWND)(GetWindowLong(hwnd, 0)))->hParent);
		((EZWND)(GetWindowLong(hwnd, 0)))->hdc = GetMemDC(hdc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		((EZWND)(GetWindowLong(hwnd, 0)))->hdcWC = GetMemDC(hdc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		ReleaseDC(((EZWND)(GetWindowLong(hwnd, 0)))->hParent, hdc);

		EZSendMessage(((EZWND)(GetWindowLong(hwnd, 0))), EZWM_SIZE, wParam, lParam);
		
		EZRepaint(((EZWND)(GetWindowLong(hwnd, 0))), 0);
		return 0;
	case WM_LBUTTONDOWN:
		ezInsideWndProc((EZWND)(GetWindowLong(hwnd, 0)), EZWM_LBUTTONDOWN, wParam, lParam);
		return 0;

	case WM_LBUTTONUP:
		ezInsideWndProc((EZWND)(GetWindowLong(hwnd, 0)), EZWM_LBUTTONUP, wParam, lParam);
		return 0;

	case WM_MOUSEMOVE:
		//老鼠在跑来跑去。
		if (((EZWND)GetWindowLong(hwnd, 0))->MouseOn == FALSE)
		{
			//刚刚进来


			//可以进行监测了。
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			tme.hwndTrack = hwnd;
			TrackMouseEvent(&tme);
		}
		ezInsideWndProc((EZWND)GetWindowLong(hwnd, 0), EZWM_MOUSEMOVE, wParam, lParam);
		return 0;


	case WM_MOUSELEAVE:
		//呀，老鼠跑了~~~   广播一下，让每个子窗口看看是不是从自己那里溜出去的。
		//先检查自己。

		BroadcastProc(((EZWND)(GetWindowLong(hwnd, 0))), SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
		EZBroadcastToAllChild(((EZWND)(GetWindowLong(hwnd, 0))), TRUE, SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);

		//发送一个消息说明鼠标是整个从窗口出去了.....
		EZSendMessage(((EZWND)(GetWindowLong(hwnd, 0))), EZWM_MOUSELEAVE, (WPARAM)1, (LPARAM)NULL);
		return 0;
	case WM_ERASEBKGND:
		//直接无视（我管你呢，反正正常的话,有ERASE就有PAINT）
		return 1;

	case WM_PAINT:
		
			//重绘区域无效啦！！！
			hdc = BeginPaint(hwnd, &ps);

		
			BitBlt(hdc, 0, 0, ((EZWND)GetWindowLong(hwnd, 0))->Width, ((EZWND)GetWindowLong(hwnd, 0))->Height, ((EZWND)GetWindowLong(hwnd, 0))->hdcWC, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
		

		//好了，现在有效了。设置一下。
		((EZWND)GetWindowLong(hwnd, 0))->Update = 0;
		return 0;

	case WM_DESTROY:
		
		
		//先保存信息，倒推，消除所有子孙窗口
		if (IsEZWindow(((EZWND)GetWindowLong(hwnd, 0))->FirstChild))
		{
			DestroyEZWindowWithNext(((EZWND)GetWindowLong(hwnd, 0))->FirstChild);
		}
		//把你自己清理了
		EZSendMessage(((EZWND)GetWindowLong(hwnd, 0)), EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//发送销毁信息
		DeleteDC(((EZWND)GetWindowLong(hwnd, 0))->hdc);//清理DC
		DeleteDC(((EZWND)GetWindowLong(hwnd, 0))->hdcWC);//清理DCWC
		
		
		free(((EZWND)GetWindowLong(hwnd, 0)));
		SetWindowLong(hwnd, 0, 0);

		break;
	case WM_SETFOCUS:
		//不需要处理，有窗口接收到单击后会自行处理。
		return 0;

	case WM_KILLFOCUS:
		//通知焦点窗口，失去焦点。
		if (IsEZWindow(((EZWND)GetWindowLong(hwnd, 0))->FocusWindow))
		{
			BroadcastProc(((EZWND)GetWindowLong(hwnd, 0))->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		}
		
		//EZBroadcastToAllChild(((EZWND)(GetWindowLong(hwnd, 0))), TRUE, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);

		
		return 0;
	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
		if (((EZWND)GetWindowLong(hwnd, 0))->FocusWindow != NULL)
		{
			switch (message)
			{
			case WM_CHAR:
				EZSendMessage(((EZWND)GetWindowLong(hwnd, 0))->FocusWindow, EZWM_CHAR, wParam, lParam);
				return 0;
			case WM_KEYDOWN:
				EZSendMessage(((EZWND)GetWindowLong(hwnd, 0))->FocusWindow, EZWM_KEYDOWN, wParam, lParam);
				return 0;
			case WM_KEYUP:
				EZSendMessage(((EZWND)GetWindowLong(hwnd, 0))->FocusWindow, EZWM_KEYUP, wParam, lParam);
				return 0;
			}
			
		}
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);

}


int ezInsideWndProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	EZWND ezChildLast;

	switch (message)
	{
	case EZWM_LBUTTONDOWN:
	case EZWM_LBUTTONUP:
	case EZWM_MOUSEMOVE:
		//这些都是鼠标消息。
	{



		if (IsEZWindow(ezWnd->FirstChild))
		{
			ezChildLast = ezWnd->FirstChild;
			for (;;)//滚动到链表底部，检查是否在子窗口内
					//**************************************************
			{
				//检查是否在子窗口内
				if (PtInEZWnd(ezChildLast, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
				{
					//可以了，在这个窗口
					if (ezInsideWndProc(ezChildLast, message, wParam, MAKELPARAM(GET_X_LPARAM(lParam) - ezChildLast->x, GET_Y_LPARAM(lParam) - ezChildLast->y)) == TRANSPARENT)
					{
						//好吧，子窗口说他是透明的》。。。。。

						if (ezWnd->FocusState == 0&&message == EZWM_LBUTTONDOWN)//你没焦点，消息是左键
						{
							if (IsEZWindow(EZGetTopParentWindow(ezWnd)->FocusWindow))
							{
								BroadcastProc(EZGetTopParentWindow(ezWnd)->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
							}
							ezWnd->FocusState = 1;

							EZGetTopParentWindow(ezWnd)->FocusWindow = ezWnd;
							EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//你有焦点了！
						}

						return EZSendMessage(ezWnd, message, wParam, lParam);
					}
					break;
				}
				else if (IsEZWindow(ezChildLast->NextEZWnd))
				{
					ezChildLast = ezChildLast->NextEZWnd;//下一个子窗口！
				}
				else
				{
					//已经到最后了，那么，就是在主窗口。

					//先发送鼠标到来
					//更改这里的时候，别忘了把下面一段相同的一起改了~~~~~
					if (message == EZWM_MOUSEMOVE)
					{
						if (ezWnd->MouseOn == FALSE)
						{

							//那么老鼠一定从别的地方跑了
							BroadcastProc(EZGetTopParentWindow(ezWnd), SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
							EZBroadcastToAllChild(EZGetTopParentWindow(ezWnd), TRUE, SEZWM_MOUSELEAVE, NULL, NULL);

							EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//老鼠来了
							ezWnd->MouseOn = TRUE;//标记一下。


						}
					}

					//发送消息

					if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//你没焦点，消息是左键
					{
						//BroadcastProc(EZGetTopParentWindow(ezWnd), SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
						//EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
						if (IsEZWindow(EZGetTopParentWindow(ezWnd)->FocusWindow))
						{
							BroadcastProc(EZGetTopParentWindow(ezWnd)->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
						}
						ezWnd->FocusState = 1;

						EZGetTopParentWindow(ezWnd)->FocusWindow = ezWnd;
						EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//你有焦点了！

					}

					return EZSendMessage(ezWnd, message, wParam, lParam);

				}
			}
			//**************************************************
		}
		else
		{
			//连个子窗口都没。。。那么，就在你这里了。

			//先发送鼠标到来消息
			//更改这里的时候，别忘了把上面一段相同的一起改了~~~~~
			if (message == EZWM_MOUSEMOVE)
			{
				if (ezWnd->MouseOn == FALSE)
				{
					//那么老鼠一定从别的地方跑了
					BroadcastProc(EZGetTopParentWindow(ezWnd), SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
					EZBroadcastToAllChild(EZGetTopParentWindow(ezWnd), TRUE, SEZWM_MOUSELEAVE, NULL, NULL);

					EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//老鼠来了
					ezWnd->MouseOn = TRUE;//标记一下。


				}
			}

			if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//你没焦点，消息是左键
			{
				if (IsEZWindow(EZGetTopParentWindow(ezWnd)->FocusWindow))
				{
					BroadcastProc(EZGetTopParentWindow(ezWnd)->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
				}
				ezWnd->FocusState = 1;

				EZGetTopParentWindow(ezWnd)->FocusWindow = ezWnd;
				EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//你有焦点了！
			}
			
			return EZSendMessage(ezWnd, message, wParam, lParam);

		}
	}

	}
}


BOOL PtInEZWnd(EZWND ezWnd, int x, int y)
{
	if ((x>ezWnd->x) && (y>ezWnd->y) && (x<(ezWnd->x + ezWnd->Width)) && (y<(ezWnd->y + ezWnd->Height)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL EZBroadcastToAllChild(EZWND ezWnd, BOOL sequence, int message, WPARAM wp, LPARAM lp)
{
	//注意，这个函数是以深度优先的方式发送消息的。（我懒得再写一个广度优先的，如果以后我写了，删掉这一句话）
	EZWND LastChild;


	if (IsEZWindow(ezWnd->FirstChild))
	{

		LastChild = ezWnd->FirstChild;
		//向回滚，如正序则直接处理，倒叙不处理。
		while(1)
		{
			if (sequence)//正
			{
				BroadcastProc(LastChild, message, wp, lp);//处理自己

				EZBroadcastToAllChild(LastChild, sequence, message, wp, lp);//给自己的子窗口发送该消息

			}

			if (!IsEZWindow(LastChild->NextEZWnd))//没有下一个
			{
				break;//没有下一个了
			}

			LastChild = LastChild->NextEZWnd;//向下滚
			
		}

		//如果倒，那么再滚回去
		if (!sequence)
		{
			while(1)
			{
				//给自己的子窗口发送该消息
				EZBroadcastToAllChild(LastChild, sequence, message, wp, lp);

				BroadcastProc(LastChild, message, wp, lp);//处理自己

				if (!IsEZWindow(LastChild->LastEZWnd))//到头了
				{
					break;
				}

				LastChild = LastChild->LastEZWnd;//回滚
				
			}
		}
	}
	return TRUE;
}


BOOL BroadcastProc(EZWND ezWnd, int Param, WPARAM wP, LPARAM lP)
{
	BLENDFUNCTION bf;
	switch (Param)
	{
	case SEZWM_COPYDC:
	{
		//看看是否是顶层EZ窗口。
		if (!ezWnd->IsTopWindow)
		{
			//不是
			BitBlt(ezWnd->ezParent->hdcWC, ezWnd->x, ezWnd->y, ezWnd->Width, ezWnd->Height, ezWnd->hdcWC, 0, 0, SRCCOPY);
			
		}
		
		//如果顶层，没有上级EZ窗口。绘制到Win窗口不由本模块负责。
		return 0;
	}
	case SEZWM_REDRAW:
	{
		//判断是否是顶层窗口
		if (ezWnd->IsTopWindow)
		{
			//画白布一块
			PatBlt(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
			//PatBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		}
		else
		{
			//复制上级窗口的相应部分。
			BitBlt(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->ezParent->hdcWC, ezWnd->x, ezWnd->y, SRCCOPY);
			//BitBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->ezParent->hdcWC, ezWnd->x, ezWnd->y, SRCCOPY);
		}

		EZSendMessage(ezWnd, EZWM_TRANSDRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);


		if (ezWnd->Transparent != 255)//如果不是255，混合。是255，那么，别混合了！
		{
			
			bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = 255 - ezWnd->Transparent;

			if (!ezWnd->IsTopWindow)
			{

				AlphaBlend(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->ezParent->hdc, ezWnd->x, ezWnd->y, ezWnd->Width, ezWnd->Height, bf);
			}
			else
			{
				//白色
				HDC hParentdc;
				HDC hdcWhite = GetMemDC(hParentdc = GetDC(ezWnd->hParent), ezWnd->Width, ezWnd->Height);


				AlphaBlend(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, hdcWhite, 0, 0, ezWnd->Width, ezWnd->Height, bf);

				DeleteDC(hdcWhite);
				ReleaseDC(ezWnd->hParent, hParentdc);
			}
		}

		
		
		
		//混合绘制现在以不透明的方式在DC上，现在从父窗口复制以255-透明度复制到hdcWC
		
		//发送普通绘制消息，绘制到DC。
		EZSendMessage(ezWnd, EZWM_DRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);
		BitBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);


		return 0;
	}
	case SEZWM_MOUSELEAVE:
	{
		//老鼠跑了
		if ((ezWnd != (EZWND)wP)&&(ezWnd->MouseOn == TRUE))
		{
			
			//这里溜出去的！

			ezWnd->MouseOn = FALSE;
			EZSendMessage(ezWnd, EZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);

		}
		return 0;
	}
	case SEZWM_KILLFOCUS:
	{
		//检查是否排除，是否具有焦点，如果有，去掉焦点，发送KILLFOCUS。
		if ((ezWnd->FocusState == 1)&&(ezWnd != (EZWND)wP))//有焦点
		{
			//不排除
			ezWnd->FocusState = 0;//你没焦点了。
			EZSendMessage(ezWnd, EZWM_KILLFOCUS, NULL, NULL);
			
		}
		
	}
	}
}



EZWND EZGetTopParentWindow(EZWND ezWnd)//得到顶层EZ窗口
{
	return ezWnd->ezRootParent;
}


BOOL SetEZWndTransparent(EZWND ezWnd, int Transparent)//设置EZ窗口透明度
{
	ezWnd->Transparent = Transparent;
	return TRUE;
}

BOOL IsEZWindow(EZWND ezWnd)
{
	if (ezWnd)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}