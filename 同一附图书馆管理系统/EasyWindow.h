
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *

*                EasyWindow.h

*                EasyWindow 库源文件 版本  3.0   Copyright (c) 2017 y.h. All rights reserved.

*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */


//*********************************************************************************************************
//                头文件等预编译指令
//*********************************************************************************************************


#pragma once

#pragma region 头文件

#include<Windows.h>
#include<windowsx.h>
#include<math.h>
#include<strsafe.h>

#pragma endregion


#pragma region 链接库

#pragma comment(lib,"msimg32.lib")

#pragma endregion

//*********************************************************************************************************
//                常量宏定义
//*********************************************************************************************************


#pragma region EasyWindow消息定义
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

#define EZWM_COLSE 9


//绘制有关消息
#define EZWM_DRAW 101//绘制，不透明
#define EZWM_TRANSDRAW 102//透明绘制，该次绘制将以透明形式覆盖。

//鼠标消息
#define EZWM_LBUTTONDOWN 201
#define EZWM_LBUTTONUP 202
#define EZWM_RBUTTONDOWN 203
#define EZWM_RBUTTONUP 204
#define EZWM_MOUSEMOVE 205//这个消息如果WPARAM为1，（仅发送到EZ主窗口）说明从Win窗口出去了
#define EZWM_MOUSECOME 206
#define EZWM_MOUSELEAVE 207

#define EZWM_NCHITTEST 208//讲道理我觉得这个...也可以放在鼠标？虽然这不是一个标准的鼠标消息



#define EZHTERROR             (-3)
#define EZHTTRANSPARENT       (-2)
#define EZHTNOWHERE           -1
#define EZHTCLIENT            1
#define EZHTCAPTION           2
#define EZHTSYSMENU           3
#define EZHTGROWBOX           4
#define EZHTSIZE              HTGROWBOX
#define EZHTMENU              5
#define EZHTHSCROLL           6
#define EZHTVSCROLL           7
#define EZHTMINBUTTON         8
#define EZHTMAXBUTTON         9
#define EZHTLEFT              10
#define EZHTRIGHT             11
#define EZHTTOP               12
#define EZHTTOPLEFT           13
#define EZHTTOPRIGHT          14
#define EZHTBOTTOM            15
#define EZHTBOTTOMLEFT        16
#define EZHTBOTTOMRIGHT       17
#define EZHTBORDER            18
#define EZHTREDUCE            HTMINBUTTON
#define EZHTZOOM              HTMAXBUTTON
#define EZHTSIZEFIRST         HTLEFT
#define EZHTSIZELAST          HTBOTTOMRIGHT
#if(WINVER >= 0x0400)
#define EZHTOBJECT            19
#define EZHTCLOSE             20
#define EZHTHELP              21
#endif




#define EZWM_CAPTUREMOUSE 251
#define EZWM_RELEASEMOUSE 252

//键盘消息
#define EZWM_CHAR 301
#define EZWM_KEYDOWN 302
#define EZWM_KEYUP 303

//滚动条消息
#define EZWM_VSCROLL 401
#define EZWM_HSCROLL 402


//各类设置消息

#define EZWM_SETCOLOR 501//wParam是背景颜色，lParam是前景颜色。该消息会引起重绘。
#define EZWM_SETFONT 502//设置字体，wParam和lParam二选一，都空则设置该风格默认字体。wParam是HFONT（用户申请释放），lParam是LOGFONT（EZWnd申请释放）。wParam优先
#define EZWM_SETTEXT 503//设置文本，wParam是文本。lParam是长度，为0则自动获取长度
#define EZWM_SETTEXTALIGN 504//文本对齐选项，wParam传递参数。临时设置为DrawText的绘制参数。后期将继续改进
#define EZWM_SETMAXTEXT 505//设置最大文本长度，wParam是最大长度,-1没有限制。已经超过了不会进行处理。

#define EZWM_SETSCROLLRANGE 506//设置滚动条范围，wParam是最大滚动范围。
#define EZWM_SETSCROLLPOS 507//设置滚动条位置，wParam lParam，是上下滚动位置。wParam < lParam <= Max 



//控制消息
#define EZWM_COMMAND 601//恩，含义不解释了。比Windows简单一些，lParam是句柄，wParam是通知的附加信息。
#define EZWM_SCROLLPOSCHANGE 602//滚动条位置动了，wParam 是上滚动位置，lParam是句柄。


//通知类消息
#define EZWM_USER_NOTIFY 701//自由使用，自己弄得清楚通知形式就OK
#define EZWM_WINWND_CHECKSTATE 702//要求Win窗口检查显示状态。



//获取信息消息
#define EZWM_GETTEXT 801//获得文本,wParam缓冲区，lParam最大计数



//内置消息
#define SEZWM_COPYDC 2001//将存储DC复制到父窗口。
#define SEZWM_REDRAW 2002//重绘到内存DC
#define SEZWM_MOUSECOME 2003
#define SEZWM_MOUSELEAVE 2004//老鼠离开顶层窗口，子窗口们自行检查。,wP是要排除检查的窗口

#define SEZWM_KILLFOCUS 2005//有焦点的窗口失去焦点。wP排除检查。


// #define SEZWM_CAPTURE 2005//有一个窗口申请捕获老鼠。已经捕获了的赶紧放掉！

#pragma endregion




#pragma region EZStyle样式定义

#define MKDW(a,b,c,d) 0b ## a ## b ## c ## d

#define CHK_STYLE(Style,ChkStyle) (Style ^ ChkStyle)> 0 ? FALSE : TRUE
#define CHK_ALT_STYLE(Style,AltStyle) (((Style) & (AltStyle)) > 0 ? (TRUE) : (FALSE))

//*****可选择属性 - 定义

//                                                      -|-
#define EZS_CHILD          MKDW(00000000,00000000,00000001,00000000)
#define EZS_PARENT         MKDW(00000000,00000000,00000000,00000000)

//                                                     -|-
#define EZS_BORDER         MKDW(00000000,00000000,00000010,00000000)
#define EZS_NO_BORDER      MKDW(00000000,00000000,00000000,00000000)

//                                                    -|-
#define EZS_CAPTION        MKDW(00000000,00000000,00000100,00000000)
#define EZS_NO_CAPTION     MKDW(00000000,00000000,00000000,00000000)



//                                                   -|-
#define EZS_MINIMIZEBOX    MKDW(00000000,00000000,00001000,00000000)//最小化按钮
#define EZS_NO_MINIMIZEBOX MKDW(00000000,00000000,00000000,00000000)

//                                                  -|-
#define EZS_MAXIMIZEBOX    MKDW(00000000,00000000,00010000,00000000)//最大化按钮
#define EZS_NO_MAXIMIZEBOX MKDW(00000000,00000000,00000000,00000000)

//                                                 -|-
#define EZS_CLOSEBOX       MKDW(00000000,00000000,00100000,00000000)//关闭按钮
#define EZS_NO_CLOSEBOX    MKDW(00000000,00000000,00000000,00000000)

//                                                -|-
#define EZS_VSCROLL        MKDW(00000000,00000000,01000000,00000000)//竖直
#define EZS_NO_VSCROLL     MKDW(00000000,00000000,00000000,00000000)

//                                               -|-
#define EZS_HSCROLL        MKDW(00000000,00000000,10000000,00000000)//水平
#define EZS_NO_HSCROLL     MKDW(00000000,00000000,00000000,00000000)


//*****窗口主要属性 - 定义
//子窗口篇
#define EZS_STATIC         MKDW(00000000,00000000,00000000,00000001)
#define EZS_BUTTON         MKDW(00000000,00000000,00000000,00000010)
//这两个可不是带有滚动控件的窗口，这两个就是滚动控件。
#define EZS_CHILD_VSCROLL  MKDW(00000000,00000000,00000000,00000011)//竖直
#define EZS_CHILD_HSCROLL  MKDW(00000000,00000000,00000000,00000100)//水平


#define EZS_EDIT           MKDW(00000000,00000000,00000000,00000101)//编辑框



//父窗口篇


//*****窗口细分属性 - 定义
//***子窗口篇
//按钮篇
#define EZBS_PUSHBUTTON    MKDW(00000000,00000000,00000000,00000000)//默认，什么都不带就是普通按钮
#define EZBS_RADIOBUTTON   MKDW(00000001,00000000,00000000,00000000)

//编辑框篇
//                             -|-
#define EZES_SINGLELINE    MKDW(10000000,00000000,00000000,00000000)
//                             -|-
#define EZES_MULTILINE     MKDW(00000000,00000000,00000000,00000000)//默认

#pragma endregion




#pragma region 其他宏定义

//各种其他宏定义
#define CLOSE_WINDOW 0//响应EZWM_CLOSE时，用于声明关闭窗口
#define DO_NOT_CLOSE 1//响应EZWM_CLOSE时，声明请勿关闭窗口

//内部文本最大长度
#define MAX_TEXT 16384

#define GET_EXTEND(ezWnd,Extend) (((pEZSE)(ezWnd))->Extend)

#pragma endregion


#pragma region EasyWindow窗口类名

#define EZWindowClass TEXT("EasyWindowClass")

#pragma endregion

//*******************************************************************************************
//                结构体声明
//*******************************************************************************************


typedef struct tagEZWND * EZWND;//对EZWINDOW结构体的定义。EZWND是指向该结构的指针。



#pragma region Extend (用于Style)结构体定义
typedef struct tagExtendStyle
{
	PBYTE Title;//每次动态申请，最多不得超过 MAX_TEXT
	int TitleLen;

	//UI相关
	COLORREF BackGroundColor;
	COLORREF ForeGroundColor;

	HFONT hFont;

	DWORD TextAlign;
	int IsFontUserControl;//字体谁负责释放？（-1 之前没字体，0 用户控制，1 EZWnd负责，2 默认字体）


						  //鼠标相关
	int MouseHold;//用于判断鼠标是否按着，比如按钮控件就会用得到。当然用来记录鼠标按的时间长短也没问题

				  //自由使用扩展
	int iExtend[4];//4个整型扩展 程序可以自由根据控件类型使用。
	EZWND hExtend[8];//8个EZWND扩展 程序可以自由根据控件类型使用。
	void * vExtend[4];//4个指针扩展 程序可以自由根据控件类型使用。

}EZSE, *pEZSE;
#pragma endregion


typedef INT(*EZWNDPROC)(EZWND, int, WPARAM, LPARAM);//回调函数定义

#define MAX_EZ_TIMER 64//64个计时器


#pragma region EZWND顶层窗口扩展
typedef struct tagezTopWindowExtend
{
	EZWND FocusWindow;//拥有输入焦点的窗口
	EZWND CptMouseWindow;//捕获了鼠标的
	EZWND MouseOnWnd;//鼠标在上面的


	HDC hdcTop;//顶层窗口申请内存使用，其他窗口而言，这只是一个空的句柄。

			   //	int TimerNum;//当前使用了的计时器数量

	struct ezTimer
	{
		int WinTimerID;

		EZWND ezWnd;
	} Timer[MAX_EZ_TIMER];

}TopWndExt, *pTWE;
#pragma endregion


#pragma region EZWND结构体定义


#define WND_TIMER_NUM 8
typedef struct tagEZWND
{
	//有关窗口信息
	int x;
	int y;
	int Width;
	int Height;

	//设置这两个变量可以滚动客户区内的子窗口，以及鼠标输入坐标。（注意，窗口本身内容并！不！被！滚！动！）
	int ScrollX;
	int ScrollY;

	//有关绘制状态****************************
	BYTE Transparent;//透明度，0是完全透明，255不透明

					 //有关窗口状态****************************
	int FocusState;//输入焦点状态。0-无焦点。1-有焦点 
	int MouseMsgRecv;//鼠标消息接受情况。 1：正常接受，2：透明
	int ShowState;//显示状态（和鼠标无关）1：正常显示，2：透明

				  //有关鼠标****************************
	BOOL MouseOn;//鼠标在该窗口上。

				 //有关绘制****************************
	HDC hdc;//一个绘制空间。始终存在，直到窗口被销毁。窗口绘制就绘制在这个上面。
	HDC hdcCopy;//用于加速绘制，下一个窗口可以直接复制的DC。

	BOOL Update;//更新区域，0为无需更新，1为发生了改变，需要更新。

				//有关关联窗口****************************
	EZWNDPROC ezWndProc;//窗口过程
	EZWND ezParent;//EZ父窗口
	EZWND ezRootParent;//EZ祖先窗口

	BOOL IsTopWindow;//用于指示是否是顶层EZ窗口。
	HWND hParent;//祖先Win窗口.

	BOOL IsWinWnd;//是否链接到了一个Win子窗口
	HWND hChild;//子Win窗口
	WNDPROC WinChildProc;

	EZWND FirstChild;//第一个子窗口
	EZWND LastEZWnd;//（和这个窗口）并列的上一个窗口
	EZWND NextEZWnd;//（和这个窗口）并列的下一个窗口


					//顶层窗口专属
	pTWE TopWndExtend;


	//扩展****************************

	int ezID;//用户可以自由使用，用于标识窗口ID。
	int TimerID[WND_TIMER_NUM];//8个应该够用了，普通窗口可以自由使用。带有样式的窗口可能会用来存放Windows计时器ID
	pEZSE Extend;//扩展指针。如果EZ窗口是自创的，那么EZWindow不会使用这个变量。但是假如这个窗口是含有 EZSTYLE 的窗口，这个指针会被EZWindow使用

	DWORD EZStyle;//窗口样式。
	BOOL IsStyleWindow;//是否是带有样式的窗口

#pragma region  窗口样式详注
					   /*窗口样式注释

					   EZStyle 被定义为了 DWORD 也就是 4个字节，32位。

					   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

					   这里是每个字段的含义：

					   最后一个字节    ：256种，表示窗口主要类型，比如，是不是按钮，是不是编辑框等。
					   倒数第二三个字节：16位，表示窗口的可选择属性，比如窗口是否带有边框。
					   倒数第四个字节  ：256种，表示在主要类型下窗口的细分属性，比如按钮窗口是否是单选按钮。
					   */
#pragma endregion
}EZWINDOW;

#pragma endregion

//*******************************************************************************************
//                函数声明
//*******************************************************************************************

#pragma region EZWindow函数声明

static BOOL InitEZWindow();
static EZWND CreateEZParentWindowEx(DWORD EZStyle, int x, int y, int Width, int Height, DWORD WinStyle, EZWNDPROC ezWndProc, HMENU hMenu, HWND hParent);
static EZWND CreateEZWindowEx(EZWND ezParent, DWORD EZStyle, int x, int y, int Width, int Height, EZWNDPROC ezWndProc);
static BOOL DestroyEZWindow(EZWND ezWnd);
static BOOL DestroyEZWindowWithNext(EZWND ezWnd);
static BOOL MoveEZWindow(EZWND ezWnd, int x, int y, int Width, int Height, BOOL repaint);
static BOOL EZCaptureMouse(EZWND ezWnd);
static BOOL EZReleaseMouse(EZWND ezWnd);
static BOOL SetMouseMsgRecvMode(EZWND ezWnd, int Mode);
static BOOL SetShowState(EZWND ezWnd, int State);
static BOOL EZRedraw(EZWND ezWnd);
static BOOL EZUpdate(EZWND ezWnd, HDC hdc);
static BOOL EZRepaint(EZWND ezWnd, HDC hdc);
static BOOL EZAddChild(EZWND ezParent, EZWND ezChild);
static EZWND CreateEZStyleWindow(EZWND ezParent, TCHAR Title[], DWORD EZStyle, int x, int y, int Width, int Height);
static int SetEZTimer(EZWND ezWnd, int iTimeSpace);
static BOOL KillEZTimer(EZWND ezWnd, int TimerID);
static BOOL EZCreateCaret(EZWND ezWnd, HBITMAP hBitmap, int nWidth, int nHeight);
static BOOL EZSetCaretPos(EZWND ezWnd, int x, int y);
static BOOL EZShowCaret(EZWND ezWnd);
static BOOL EZHideCaret(EZWND ezWnd);
static BOOL EZDestroyCaret();
static LRESULT CALLBACK EZParentWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
static VOID CALLBACK ezInsideTimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);
static int ezInsideWndProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static BOOL PtInEZWnd(EZWND ezWnd, int x, int y);
static BOOL IsEZWindow(EZWND ezWnd);
static BOOL EZBroadcastToAllChildFunc(EZWND ezWnd, BOOL sequence, int message, WPARAM wp, LPARAM lp);
static BOOL BroadcastProc(EZWND ezWnd, int Param, WPARAM wP, LPARAM lP);
//static int EZSendMessage(EZWND ezWnd, int message, WPARAM wP, LPARAM lP);
static BOOL SetEZWndTransparent(EZWND ezWnd, int Transparent);

static BOOL RedrawBroadcast(EZWND ezWnd, WPARAM wp, LPARAM lp, int cx, int cy, RECT RectSrc);
static int EZWndMessageLoop();



//外部样式
static EZWNDPROC EZStyle_ButtonProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_StaticProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_ScrollChildProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_Scroll_BtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_Scroll_BarProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_DefaultProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_EditProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_Edit_InputProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);
static EZWNDPROC EZStyle_Edit_InputChildProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);



#pragma endregion


#pragma region 其他函数声明

static HDC GetMemDC(HDC hdc, int cx, int cy);

static BOOL DeleteMemDC(HDC hdc);

#pragma endregion

//*******************************************************************************************
//                函数宏定义
//*******************************************************************************************

#pragma region EZWindow函数宏定义

//#define CreateEZParentWindow(x, y, Width, Height,  ezWndProc, hMenu, hParent) CreateEZParentWindow(x, y, Width, Height,  WS_CHILD|WS_VISIBLE, ezWndProc, hMenu, hParent) 

#define CreateEZWindow(ezParent, x,y, Width, Height, ezWndProc) CreateEZWindowEx(ezParent,0L, x,y, Width, Height, ezWndProc)

#define CreateEZParentWindow(x, y, Width, Height,WinStyle, ezWndProc, hMenu, hParent) CreateEZParentWindowEx(0L, x, y, Width, Height,WinStyle, ezWndProc, hMenu, hParent)



#define EZBroadcastToAllChild(ezWnd, sequence, message, wp,lp) if(IsEZWindow(ezWnd->FirstChild)){ EZBroadcastToAllChildFunc(ezWnd, sequence, message, wp,lp); }

//#define EZRepaint(ezWnd,hdc) {  EZRedraw(ezWnd);   EZUpdate(ezWnd, hdc);}

#define EZGetTopParentWindow(ezWnd) (ezWnd->ezRootParent)


#define EZSendMessage(ezWnd, message, wP, lP) (ezWnd)->ezWndProc(ezWnd, message, wP, lP)


//#define EZRepaint(ezWnd,hdc) {  EZRedraw(ezWnd);   EZUpdate(ezWnd, hdc);}

#pragma endregion

//*******************************************************************************************
//                函数实体
//*******************************************************************************************

//初始化函数
BOOL InitEZWindow()
{
	WNDCLASS wndclass;
	//注册窗口类
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = EZParentWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(LONG_PTR);
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = EZWindowClass;
	if (!RegisterClass(&wndclass))
	{
		return  FALSE;
	}


	return TRUE;
}



//创建窗口函数
EZWND CreateEZParentWindowEx(DWORD EZStyle, int x, int y, int Width, int Height, DWORD WinStyle, EZWNDPROC ezWndProc, HMENU hMenu, HWND hParent)
{
	HWND hwndParent;//这是Windows句柄的父窗口
	EZWND ezwndParent;//这是和Win窗口等大的EZ窗口，返回给用户。该窗口摧毁时同时摧毁Win窗口


	ezwndParent = (EZWND)malloc(sizeof(EZWINDOW));


	//Create tht EZ Window With out Using "CreateEZWindow"
	if (!ezwndParent)//检查内存
	{
		return (EZWND)0;
	}

	ezwndParent->TopWndExtend = (pTWE)malloc(sizeof(TopWndExt));

	if (!ezwndParent->TopWndExtend)//检查内存
	{
		free(ezwndParent);
		return (EZWND)0;
	}


	ezwndParent->Extend = 0;


	int i;
	for (i = 0; i < MAX_EZ_TIMER; i++)
	{
		ezwndParent->TopWndExtend->Timer[i].ezWnd = NULL;
		ezwndParent->TopWndExtend->Timer[i].WinTimerID = 0;
	}




	ezwndParent->x = x;
	ezwndParent->y = y;
	ezwndParent->Width = Width;
	ezwndParent->Height = Height;


	ezwndParent->ScrollX = 0;
	ezwndParent->ScrollY = 0;


	ezwndParent->FirstChild = NULL;
	ezwndParent->LastEZWnd = NULL;
	ezwndParent->NextEZWnd = NULL;
	ezwndParent->ezParent = NULL;//没有，空。
	ezwndParent->ezRootParent = ezwndParent;//你自己

	ezwndParent->TopWndExtend->CptMouseWindow = NULL;//没有的，2333
	ezwndParent->TopWndExtend->FocusWindow = NULL;
	ezwndParent->TopWndExtend->MouseOnWnd = NULL;


	ezwndParent->IsTopWindow = TRUE;//是的，是顶层窗口。

	ezwndParent->FocusState = FALSE;

	ezwndParent->MouseMsgRecv = 1;

	ezwndParent->ShowState = 1;

	ezwndParent->MouseOn = FALSE;

	ezwndParent->Update = FALSE;//刚开始，肯定没有更新过。

	ezwndParent->Transparent = 255;//不透明

	ezwndParent->ezWndProc = ezWndProc;

	ezwndParent->TopWndExtend->FocusWindow = NULL;


	ezwndParent->IsWinWnd = 0;
	ezwndParent->hChild = 0;


	ezwndParent->IsStyleWindow = FALSE;

	//大部分内容都初始化完毕了。ezwndParent被作为参数提交给WM_CREATE消息，并在期间将这个指针设置为窗口扩展
	hwndParent = CreateWindow(EZWindowClass, TEXT(""), WinStyle, x, y, Width, Height, hParent, hMenu, GetModuleHandle(NULL), ezwndParent);

	//	EZRepaint(ezwndParent, NULL);

	return ezwndParent;
}

EZWND CreateEZWindowEx(EZWND ezParent, DWORD EZStyle, int x, int y, int Width, int Height, EZWNDPROC ezWndProc)
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

	ezWnd->EZStyle = EZStyle;

	if (EZStyle != 0L)
	{
		ezWnd->Extend = (pEZSE)malloc(sizeof(EZSE));
		ezWnd->Extend->TextAlign = 0;
	}
	else
	{
		ezWnd->Extend = NULL;//防野指针
	}

	ezWnd->TopWndExtend = NULL;

	ezWnd->x = x;
	ezWnd->y = y;
	ezWnd->Width = Width;
	ezWnd->Height = Height;

	ezWnd->ScrollX = 0;
	ezWnd->ScrollY = 0;

	ezWnd->FirstChild = NULL;
	ezWnd->LastEZWnd = NULL;
	ezWnd->NextEZWnd = NULL;

	ezWnd->hParent = ezParent->hParent;
	ezWnd->IsTopWindow = FALSE;//并不是


	ezWnd->FocusState = 0;
	ezWnd->MouseMsgRecv = 1;
	ezWnd->ShowState = 1;

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
	ezWnd->hdcCopy = GetMemDC(fhdc, Width, Height);
	ReleaseDC(hParent, fhdc);


	ezWnd->IsWinWnd = 0;
	ezWnd->hChild = 0;


	ezWnd->IsStyleWindow = FALSE;

	EZSendMessage(ezWnd, EZWM_CREATE, 0, 0);//发送创建消息

											//只发送一个移动消息
	EZSendMessage(ezWnd, EZWM_SIZE, (WPARAM)NULL, (LPARAM)MAKELPARAM(Width, Height));
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

	while (1)//循环到链表最后
	{
		if (!IsEZWindow(ezChildLast->NextEZWnd))
		{
			ezChild->LastEZWnd = ezChildLast;
			ezChildLast->NextEZWnd = ezChild;
			return TRUE;
		}
		ezChildLast = ezChildLast->NextEZWnd;//向下移动
	}

}


EZWND CreateEZStyleWindow(EZWND ezParent, TCHAR Title[], DWORD EZStyle, int x, int y, int Width, int Height)
{
	EZWND ezWnd;
	ezWnd = 0;
	//解析属性，检测是否冲突，然后创建窗口。
	if (CHK_ALT_STYLE(EZStyle, EZS_CHILD))
	{
		//子窗口
		switch (EZStyle & MKDW(00000000, 00000000, 00000000, 11111111))
		{
		case EZS_STATIC:
			ezWnd = CreateEZWindowEx(ezParent, EZStyle, x, y, Width, Height, EZStyle_StaticProc);

			break;
		case EZS_BUTTON:
			ezWnd = CreateEZWindowEx(ezParent, EZStyle, x, y, Width, Height, EZStyle_ButtonProc);
			break;
		case EZS_CHILD_HSCROLL:
		case EZS_CHILD_VSCROLL:
			ezWnd = CreateEZWindowEx(ezParent, EZStyle, x, y, Width, Height, EZStyle_ScrollChildProc);
			break;
		case EZS_EDIT:
			ezWnd = CreateEZWindowEx(ezParent, EZStyle, x, y, Width, Height, EZStyle_EditProc);
			break;
		}

	}
	else
	{
		//主窗口

	}


	((pEZSE)ezWnd->Extend)->hFont = NULL;
	ezWnd->Extend->Title = 0;
	EZSendMessage(ezWnd, EZWM_SETTEXT, Title, lstrlen(Title));


	((pEZSE)ezWnd->Extend)->BackGroundColor = RGB(255, 255, 255);

	((pEZSE)ezWnd->Extend)->ForeGroundColor = RGB(0, 0, 0);

	((pEZSE)ezWnd->Extend)->MouseHold = FALSE;


	((pEZSE)ezWnd->Extend)->IsFontUserControl = -1;


	//最后再设置一遍，防止之前被防野数据机制清零。
	ezWnd->IsStyleWindow = TRUE;
	ezWnd->EZStyle = EZStyle;

	return ezWnd;
}



//销毁窗口函数
BOOL DestroyEZWindow(EZWND ezWnd)
{
	if (ezWnd->IsTopWindow)
	{
		DestroyWindow(ezWnd->hParent);//这就行了，销毁会在这里完成。这也没什么好说的，不用管链表，清理就是了。
		return TRUE;
	}

	//先保存信息，倒推，消除所有子孙窗口
	if (IsEZWindow(ezWnd->FirstChild))
	{
		DestroyEZWindowWithNext(ezWnd->FirstChild);
	}


	//把你自己清理了
	EZSendMessage(ezWnd, EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//发送销毁信息

	DeleteMemDC(ezWnd->hdc);//清理DC

	if (ezWnd->ezRootParent->TopWndExtend->MouseOnWnd == ezWnd)
	{
		ezWnd->ezRootParent->TopWndExtend->MouseOnWnd = NULL;
	}
	if (ezWnd->ezRootParent->TopWndExtend->FocusWindow == ezWnd)
	{
		ezWnd->ezRootParent->TopWndExtend->FocusWindow = NULL;
	}
	if (ezWnd->ezRootParent->TopWndExtend->CptMouseWindow == ezWnd)
	{
		ezWnd->ezRootParent->TopWndExtend->CptMouseWindow = NULL;
	}


	if (ezWnd->IsTopWindow)
	{
		DeleteMemDC(ezWnd->TopWndExtend->hdcTop);
		free(ezWnd->TopWndExtend);
	}


	if (ezWnd->IsStyleWindow)
	{
		free(ezWnd->Extend);
	}
	//维护一下链表？
	if (ezWnd->LastEZWnd)
	{
		//有上一个
		if (ezWnd->NextEZWnd)
		{
			//还有下一个。
			ezWnd->LastEZWnd->NextEZWnd = ezWnd->NextEZWnd;
			ezWnd->NextEZWnd->LastEZWnd = ezWnd->LastEZWnd;
			//链接好咯
		}
		else
		{
			//下一个是空的
			ezWnd->LastEZWnd->NextEZWnd = NULL;
		}
	}
	else
	{
		//没有上一个？你是顶层窗口？还是第一个？
		if (!(ezWnd->IsTopWindow))
		{
			//不是顶层啊，你是某个链的第一个
			if (ezWnd->NextEZWnd)
			{
				//还有下一个
				ezWnd->ezParent->FirstChild = ezWnd->NextEZWnd;
				ezWnd->NextEZWnd->LastEZWnd = NULL;
			}
		}
	}



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
		while (1)
		{
			if (!IsEZWindow(ezChildLast->NextEZWnd))
			{
				break;//最后，跳出。
			}
			ezChildLast = ezChildLast->NextEZWnd;
		}


		//再循环滚回链表最前（一边滚一边删）

		//为了数据，先回滚，然后通过向下的指针找回去，删了
		while (IsEZWindow(ezChildLast->LastEZWnd))//还没到头
		{

			ezChildLast = ezChildLast->LastEZWnd;//回滚

												 //这时，ezChildLast->NextEZWnd就是最后一个。DestroyEZWindow会删了该窗口和这个窗口的子窗口。
			DestroyEZWindow(ezChildLast->NextEZWnd);//删了
		}
		//滚动到头了，DestroyEZWindow会删了该窗口和这个窗口的子窗口。
		DestroyEZWindow(ezChildLast);
		return TRUE;

	}
	else
	{//你就是最后一个并列窗口。
		DestroyEZWindow(ezWnd);//删了
	}
	return TRUE;

}



//窗口设置函数
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
	DeleteMemDC(ezWnd->hdc);
	DeleteMemDC(ezWnd->hdcCopy);

	fhdc = GetDC(ezWnd->hParent);
	ezWnd->hdc = GetMemDC(fhdc, Width, Height);
	ezWnd->hdcCopy = GetMemDC(fhdc, Width, Height);

	if (ezWnd->IsTopWindow)
	{
		DeleteMemDC(ezWnd->TopWndExtend->hdcTop);
		ezWnd->TopWndExtend->hdcTop = GetMemDC(fhdc, Width, Height);
	}

	ReleaseDC(ezWnd->hParent, fhdc);

	EZSendMessage(ezWnd, EZWM_SIZE, (WPARAM)NULL, (LPARAM)MAKELPARAM(Width, Height));

	if (repaint)
	{
		if (ezWnd->ezParent)
		{
			EZRepaint(ezWnd->ezParent, NULL);
		}
		else
		{
			EZRepaint(ezWnd, NULL);
		}
	}

	return TRUE;
}

BOOL SetEZWndTransparent(EZWND ezWnd, int Transparent)//设置EZ窗口透明度
{
	ezWnd->Transparent = Transparent;
	return TRUE;
}

BOOL EZCaptureMouse(EZWND ezWnd)
{
	//向顶层父窗口提交要捕获“老鼠”的窗口的句柄。
	if (ezWnd->ezRootParent->TopWndExtend->CptMouseWindow)
	{
		EZSendMessage(ezWnd->ezRootParent->TopWndExtend->CptMouseWindow, EZWM_RELEASEMOUSE, 0, 0);

	}
	ezWnd->ezRootParent->TopWndExtend->CptMouseWindow = ezWnd;
	EZSendMessage(ezWnd->ezRootParent->TopWndExtend->CptMouseWindow, EZWM_CAPTUREMOUSE, 0, 0);
	SetCapture(ezWnd->hParent);
	return TRUE;
}

BOOL EZReleaseMouse(EZWND ezWnd)
{
	//向顶层父窗口提交释放“老鼠”申请。

	ReleaseCapture();

	//下面两这句不需要，在Window窗口处理WM_CAPTURECHANGE之间已经处理好了
	//EZSendMessage(ezWnd->ezRootParent->CptMouseWindow, EZWM_RELEASEMOUSE, 0, 0);
	//ezWnd->ezRootParent->CptMouseWindow = NULL;

	return TRUE;
}

BOOL SetMouseMsgRecvMode(EZWND ezWnd, int Mode)
{
	ezWnd->MouseMsgRecv = Mode;
	return TRUE;
}

BOOL SetShowState(EZWND ezWnd, int State)
{
	ezWnd->ShowState = State;
	return TRUE;
}





//与窗口绘制有关的函数
BOOL EZRedraw(EZWND ezWnd)//重绘到内存dc,不更新。
{
	//这里，我们需要先确定需要重绘的范围

	/*
	在整个大窗口体系下
	任何和该窗口有范围重复的窗口
	全！部！需！要！重绘！！！！

	所以，我们要向所有窗口，包括子窗口广播消息。任何有重复的窗口，全部需要重绘到内存
	然后进行叠加处理。

	不需要重绘到Windows父窗口。

	*/

	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}
	RECT rect;

	int Countx = 0, County = 0;

	EZWND WndNow = ezWnd;


	//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
	while (!WndNow->IsTopWindow)
	{
		//向上推，直到父窗口
		Countx += WndNow->x + WndNow->ScrollX;
		County += WndNow->y + WndNow->ScrollY;
		WndNow = WndNow->ezParent;

	}

	rect.left = Countx;
	rect.right = Countx + ezWnd->Width;
	rect.top = County;
	rect.bottom = County + ezWnd->Height;



	BroadcastProc(ezWnd, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);
	RedrawBroadcast(ezWnd, 0, 0, Countx, County, rect);


	BitBlt(ezWnd->ezRootParent->TopWndExtend->hdcTop,
		Countx,
		County,
		ezWnd->Width, ezWnd->Height,
		ezWnd->hdc,
		0,
		0, SRCCOPY);

	return TRUE;
}

BOOL RedrawBroadcast(EZWND ezWnd, WPARAM wp, LPARAM lp, int cx, int cy, RECT RectSrc)
{

	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}

	if (IsEZWindow(ezWnd->FirstChild))
	{

		EZWND LastChild;

		

		for (LastChild = ezWnd->FirstChild; LastChild; LastChild = LastChild->NextEZWnd)
		{
			//正序，所以，先处理自己。
			RECT RectDst, RectAns;

			{
				RectDst.left = cx + LastChild->x + LastChild->ezParent->ScrollX;
				RectDst.right = RectDst.left + LastChild->Width;
				RectDst.top = cy + LastChild->y + LastChild->ezParent->ScrollY;
				RectDst.bottom = RectDst.top + LastChild->Height;
			}

			if (!((IntersectRect(&RectAns, &RectSrc, &RectDst) == 0) || (LastChild->ShowState == 2)))
				//临时处理
				//if (LastChild->ShowState == 1)
			{

				//HRGN hRgn, OldRgn;


				BroadcastProc(LastChild, SEZWM_REDRAW, wp, lp);//处理自己

				//hRgn = CreateRectRgn(
				//	RectAns.left - (cx + LastChild->x + LastChild->ezParent->ScrollX),
				//	RectAns.top - (cy + LastChild->y + LastChild->ezParent->ScrollY),
				//	RectAns.right - (cx + LastChild->x + LastChild->ezParent->ScrollX),
				//	RectAns.bottom - (cy + LastChild->y + LastChild->ezParent->ScrollY));

				//OldRgn = SelectObject(LastChild->hdc, hRgn);

				RedrawBroadcast(LastChild, wp, lp, cx + LastChild->x + LastChild->ezParent->ScrollX, cy + LastChild->y + LastChild->ezParent->ScrollY, RectSrc);//给自己的子窗口发送该消息

				/*DeleteObject(SelectObject(LastChild->hdc, OldRgn));*/

				BroadcastProc(LastChild, SEZWM_COPYDC, wp, lp);//处理自己
			}


			//向下滚

		}

	}
	return TRUE;
}

BOOL EZUpdate(EZWND ezWnd, HDC hdc)//将DC更新到窗体，不重绘。第二个参数是DC，如不提供，函数将自动获取。
{
	//找到你的“祖宗”、

	int Countx = 0, County = 0;

	EZWND WndNow = ezWnd;

	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}

	//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
	while (!WndNow->IsTopWindow)
	{
		//向上推，直到父窗口
		Countx += WndNow->x + WndNow->ScrollX;
		County += WndNow->y + WndNow->ScrollY;
		WndNow = WndNow->ezParent;
	}

	////EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_COPYDC, (WPARAM)NULL, (LPARAM)NULL);


	if (!hdc)//没DC
	{

		hdc = GetDC(EZGetTopParentWindow(ezWnd)->hParent);
		//BitBlt(hdcg, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->hdc, Countx, County, SRCCOPY);
		BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);
		ReleaseDC(EZGetTopParentWindow(ezWnd)->hParent, hdc);
		hdc = NULL;
	}
	else
	{
		//BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->hdc, Countx, County, SRCCOPY);
		BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);
	}



	/*
	RECT rect;
	rect.left = Countx;
	rect.right = Countx + ezWnd->Width;
	rect.top = County;
	rect.bottom = County + ezWnd->Height;

	InvalidateRect(ezWnd->hParent, &rect, 0);
	*/
	return 0;
}

BOOL EZRepaint(EZWND ezWnd, HDC hdc)
{
	if (!ezWnd)
	{
		return FALSE;
	}
	if (ezWnd->ShowState == 2)
	{
		return TRUE;
	}
	RECT rect;

	int Countx = 0, County = 0;

	EZWND WndNow = ezWnd;


	//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
	while (!WndNow->IsTopWindow)
	{
		//向上推，直到父窗口。顺便检查有没有父窗口不显示的
		if (WndNow->ShowState == 2)
		{
			return 0;
		}
		Countx += WndNow->x + WndNow->ScrollX;
		County += WndNow->y + WndNow->ScrollY;
		WndNow = WndNow->ezParent;

	}

	rect.left = Countx;
	rect.right = Countx + ezWnd->Width;
	rect.top = County;
	rect.bottom = County + ezWnd->Height;

	BroadcastProc(ezWnd, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);
	RedrawBroadcast(ezWnd, 0, 0, Countx, County, rect);

	if (hdc)
	{
		BitBlt(hdc, Countx - ezWnd->ScrollX, County - ezWnd->ScrollY, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);
	}
	else//没DC
	{

		hdc = GetDC(ezWnd->hParent);
		BitBlt(hdc, Countx - ezWnd->ScrollX, County - ezWnd->ScrollY, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);
		ReleaseDC(ezWnd->hParent, hdc);
	}


	BitBlt(ezWnd->ezRootParent->TopWndExtend->hdcTop,
		Countx - ezWnd->ScrollX,
		County - ezWnd->ScrollY,
		ezWnd->Width, ezWnd->Height,
		ezWnd->hdc,
		0,
		0, SRCCOPY);


	return 0;
}






////与窗口绘制有关的函数
//BOOL EZRedraw(EZWND ezWnd)//重绘到内存dc,不更新。
//{
//	//这里，我们需要先确定需要重绘的范围
//
//	/*
//	在整个大窗口体系下
//	任何和该窗口有范围重复的窗口
//	全！部！需！要！重绘！！！！
//
//	所以，我们要向所有窗口，包括子窗口广播消息。任何有重复的窗口，全部需要重绘到内存
//	然后进行叠加处理。
//
//	不需要重绘到Windows父窗口。
//
//	*/
//
//	if (!IsEZWindow(ezWnd))
//	{
//		return FALSE;
//	}
//	RECT rect;
//
//	int Countx = 0, County = 0;
//
//	EZWND WndNow = ezWnd;
//
//
//	//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
//	while (!WndNow->IsTopWindow)
//	{
//		//向上推，直到父窗口
//		Countx += WndNow->x + WndNow->ScrollX;
//		County += WndNow->y + WndNow->ScrollY;
//		WndNow = WndNow->ezParent;
//
//	}
//
//	rect.left = Countx;
//	rect.right = Countx + ezWnd->Width;
//	rect.top = County;
//	rect.bottom = County + ezWnd->Height;
//
//
//	//BroadcastProc(ezWnd->ezRootParent, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);
//	//RedrawBroadcast(ezWnd->ezRootParent, 0, 0, 0, 0, rect);
//	BroadcastProc(ezWnd, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);
//	RedrawBroadcast(ezWnd, 0, 0, 0, 0, rect);
//
//	/*BitBlt(ezWnd->ezRootParent->TopWndExtend->hdcTop,
//		Countx,
//		County,
//		ezWnd->Width, ezWnd->Height,
//		ezWnd->ezRootParent->hdc,
//		Countx,
//		County, SRCCOPY);*/
//
//
//
//	BitBlt(ezWnd->ezRootParent->TopWndExtend->hdcTop,
//				Countx - ezWnd->ScrollX,
//				County - ezWnd->ScrollY,
//				ezWnd->Width, ezWnd->Height,
//				ezWnd->hdc,
//				0,
//				0, SRCCOPY);
//
//	//	BroadcastProc(ezWnd->ezRootParent, SEZWM_COPYDC, (WPARAM)NULL, (LPARAM)NULL);
//
//
//	return TRUE;
//}
//
//BOOL RedrawBroadcast(EZWND ezWnd, WPARAM wp, LPARAM lp, int cx, int cy, RECT RectSrc)
//{
//
//	if (!IsEZWindow(ezWnd))
//	{
//		return FALSE;
//	}
//
//	if (IsEZWindow(ezWnd->FirstChild))
//	{
//
//		EZWND LastChild;
//
//		LastChild = (ezWnd)->FirstChild;
//
//		while (1)
//		{
//			//正序，所以，先处理自己。
//			RECT RectDst, RectAns;
//
//			{
//				RectDst.left = cx + LastChild->x;
//				RectDst.right = RectDst.left + LastChild->Width;
//				RectDst.top = cy + LastChild->y;
//				RectDst.bottom = RectDst.top + LastChild->Height;
//			}
//
//			if ((IntersectRect(&RectAns, &RectSrc, &RectDst) != 0) && (LastChild->ShowState != 2))
//			{
//				BroadcastProc(LastChild, SEZWM_REDRAW, wp, lp);//处理自己
//
//				RedrawBroadcast(LastChild, wp, lp, cx + LastChild->x + LastChild->ScrollX, cy + LastChild->y + LastChild->ScrollY, RectSrc);//给自己的子窗口发送该消息
//
//				BroadcastProc(LastChild, SEZWM_COPYDC, wp, lp);//处理自己
//			}
//
//			if (!IsEZWindow(LastChild->NextEZWnd))//没有下一个
//			{
//				break;//没有下一个了
//			}
//
//			LastChild = LastChild->NextEZWnd;//向下滚
//
//		}
//
//	}
//	return TRUE;
//}
//
//BOOL EZUpdate(EZWND ezWnd, HDC hdc)//将DC更新到窗体，不重绘。第二个参数是DC，如不提供，函数将自动获取。
//{
//	//找到你的“祖宗”、
//
//	int Countx = 0, County = 0;
//
//	EZWND WndNow = ezWnd;
//
//	if (!IsEZWindow(ezWnd))
//	{
//		return FALSE;
//	}
//
//	//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
//	while (!WndNow->IsTopWindow)
//	{
//		//向上推，直到父窗口
//		Countx += WndNow->x + WndNow->ScrollX;
//		County += WndNow->y + WndNow->ScrollY;
//		WndNow = WndNow->ezParent;
//	}
//
//	////EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_COPYDC, (WPARAM)NULL, (LPARAM)NULL);
//
//	/*
//	if (!hdc)//没DC
//	{
//	HDC hdcg;
//	hdcg = GetDC(EZGetTopParentWindow(ezWnd)->hParent);
//	//BitBlt(hdcg, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->hdc, Countx, County, SRCCOPY);
//	BitBlt(hdcg, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->TopWndExtend->hdcTop, Countx, County, SRCCOPY);
//	ReleaseDC(EZGetTopParentWindow(ezWnd)->hParent, hdcg);
//	}
//	else
//	{
//	//BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->hdc, Countx, County, SRCCOPY);
//	BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->TopWndExtend->hdcTop, Countx, County, SRCCOPY);
//	}
//
//	*/
//
//
//	if (!hdc)//没DC
//	{
//
//		hdc = GetDC(EZGetTopParentWindow(ezWnd)->hParent);
//		//BitBlt(hdcg, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->hdc, Countx, County, SRCCOPY);
//		BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);
//		ReleaseDC(EZGetTopParentWindow(ezWnd)->hParent, hdc);
//		hdc = NULL;
//	}
//	else
//	{
//		//BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->ezRootParent->hdc, Countx, County, SRCCOPY);
//		BitBlt(hdc, Countx, County, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);
//	}
//
//	//RECT rect;
//	//rect.left = Countx;
//	//rect.right = Countx + ezWnd->Width;
//	//rect.top = County;
//	//rect.bottom = County + ezWnd->Height;
//
//	//InvalidateRect(ezWnd->hParent, &rect, 0);
//	return 0;
//}


//计时器函数
int SetEZTimer(EZWND ezWnd, int iTimeSpace)
{
	//申请计时器，在顶部窗口的计时器中找到一个空位，写入信息，返回分配的ID。
	int i;
	for (i = 0; i < MAX_EZ_TIMER; i++)
	{
		if (ezWnd->ezRootParent->TopWndExtend->Timer[i].ezWnd == NULL)
		{
			//写入信息
			ezWnd->ezRootParent->TopWndExtend->Timer[i].ezWnd = ezWnd;

			int IDGet = SetTimer(NULL, 0, iTimeSpace, ezInsideTimerProc);
			KillTimer(0, IDGet);

			ezWnd->ezRootParent->TopWndExtend->Timer[i].WinTimerID = SetTimer(ezWnd->hParent, IDGet, iTimeSpace, ezInsideTimerProc);
			return i;
		}
	}
	return -1;

}

BOOL KillEZTimer(EZWND ezWnd, int TimerID)
{
	//删除信息
	if (ezWnd->ezRootParent->TopWndExtend->Timer[TimerID].ezWnd != NULL)
	{
		KillTimer(ezWnd->hParent, ezWnd->ezRootParent->TopWndExtend->Timer[TimerID].WinTimerID);
		ezWnd->ezRootParent->TopWndExtend->Timer[TimerID].ezWnd = NULL;
		ezWnd->ezRootParent->TopWndExtend->Timer[TimerID].WinTimerID = 0;
		return 0;
	}
	else
	{
		return -1;
	}
}




//光标函数
BOOL EZCreateCaret(EZWND ezWnd, HBITMAP hBitmap, int nWidth, int nHeight)
{
	return CreateCaret(ezWnd->hParent, hBitmap, nWidth, nHeight);
}

BOOL EZSetCaretPos(EZWND ezWnd, int x, int y)
{
	int Countx = 0, County = 0;
	EZWND WndNow = ezWnd;

	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}

	//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
	while (!WndNow->IsTopWindow)
	{
		//向上推，直到父窗口
		Countx += WndNow->x + WndNow->ScrollX;
		County += WndNow->y + WndNow->ScrollY;
		WndNow = WndNow->ezParent;
	}

	return SetCaretPos(Countx + x, County + y);
}

BOOL EZShowCaret(EZWND ezWnd)
{
	return ShowCaret(ezWnd->hParent);
}

BOOL EZHideCaret(EZWND ezWnd)
{
	return HideCaret(ezWnd->hParent);
}

BOOL EZDestroyCaret()
{
	DestroyCaret();
}



//内部函数
LRESULT CALLBACK EZParentWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TRACKMOUSEEVENT tme;

	EZWND ezWnd;

	if (message != WM_CREATE)
	{
		ezWnd = ((EZWND)GetWindowLongPtr(hwnd, 0));
		if (ezWnd == NULL)
		{
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	else
	{
		ezWnd = NULL;
	}
	switch (message)
	{
	case WM_CREATE:
	{
		ezWnd = (EZWND)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		SetWindowLongPtr(hwnd, 0, (LONG_PTR)ezWnd);
		ezWnd->hParent = hwnd;//设置Win父窗口

							  //HDC fhdc;
							  //其实，本应该用这个变量.但是？hdc变量现在不正闲着吗？？？干脆就用那个吧，省内存

		hdc = GetDC(hwnd);
		ezWnd->hdc = GetMemDC(hdc, ezWnd->Width, ezWnd->Height);
		ezWnd->hdcCopy = GetMemDC(hdc, ezWnd->Width, ezWnd->Height);
		ezWnd->TopWndExtend->hdcTop = GetMemDC(hdc, ezWnd->Width, ezWnd->Height);

		ReleaseDC(hwnd, hdc);

		EZSendMessage(ezWnd, EZWM_CREATE, 0, 0);//发送创建消息

		return 0;

	}


	case WM_SIZE:
	{

		ezWnd->Width = GET_X_LPARAM(lParam);
		ezWnd->Height = GET_Y_LPARAM(lParam);

		DeleteMemDC(ezWnd->hdc);
		DeleteMemDC(ezWnd->hdcCopy);
		DeleteMemDC(ezWnd->TopWndExtend->hdcTop);

		//HDC fhdc;
		//其实，本应该用这个变量.但是？hdc变量现在不正闲着吗？？？干脆就用那个吧，省内存

		hdc = GetDC(hwnd);
		ezWnd->hdc = GetMemDC(hdc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		ezWnd->hdcCopy = GetMemDC(hdc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		ezWnd->TopWndExtend->hdcTop = GetMemDC(hdc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		ReleaseDC(hwnd, hdc);

		EZSendMessage(ezWnd, EZWM_SIZE, wParam, lParam);

		EZRepaint(ezWnd, NULL);

		return 0;

	}


	case WM_LBUTTONDOWN:
	{
		if (IsEZWindow(ezWnd->TopWndExtend->CptMouseWindow))
		{
			//从这个窗口向上滚，找到这个窗口的坐标
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
			while (!WndNow->IsTopWindow)
			{
				//向上推，直到父窗口
				Countx += WndNow->x + WndNow->ScrollX;
				County += WndNow->y + WndNow->ScrollY;
				WndNow = WndNow->ezParent;
			}
			ezInsideWndProc(ezWnd->TopWndExtend->CptMouseWindow, EZWM_LBUTTONDOWN, wParam,
				MAKELPARAM(LOWORD(lParam) - Countx, HIWORD(lParam) - County));
			return 0;
		}
		ezInsideWndProc(ezWnd, EZWM_LBUTTONDOWN, wParam,
			MAKELPARAM(LOWORD(lParam) - ezWnd->ScrollX, HIWORD(lParam) - ezWnd->ScrollY));
		return 0;

	}

	case WM_LBUTTONUP:
	{
		if (IsEZWindow(ezWnd->TopWndExtend->CptMouseWindow))
		{
			//从这个窗口向上滚，找到这个窗口的坐标
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
			while (!WndNow->IsTopWindow)
			{
				//向上推，直到父窗口
				Countx += WndNow->x + WndNow->ScrollX;
				County += WndNow->y + WndNow->ScrollY;
				WndNow = WndNow->ezParent;
			}
			ezInsideWndProc(ezWnd->TopWndExtend->CptMouseWindow, EZWM_LBUTTONUP, wParam,
				MAKELPARAM(LOWORD(lParam) - Countx, HIWORD(lParam) - County));
			return 0;
		}
		ezInsideWndProc(ezWnd, EZWM_LBUTTONUP, wParam,
			MAKELPARAM(LOWORD(lParam) - ezWnd->ScrollX, HIWORD(lParam) - ezWnd->ScrollY));
		return 0;
	}

	case WM_RBUTTONDOWN:
	{
		if (IsEZWindow(ezWnd->TopWndExtend->CptMouseWindow))
		{
			//从这个窗口向上滚，找到这个窗口的坐标
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
			while (!WndNow->IsTopWindow)
			{
				//向上推，直到父窗口
				Countx += WndNow->x + WndNow->ScrollX;
				County += WndNow->y + WndNow->ScrollY;
				WndNow = WndNow->ezParent;
			}
			ezInsideWndProc(ezWnd->TopWndExtend->CptMouseWindow, EZWM_RBUTTONDOWN, wParam,
				MAKELPARAM(LOWORD(lParam) - Countx, HIWORD(lParam) - County));
			return 0;
		}
		ezInsideWndProc(ezWnd, EZWM_RBUTTONDOWN, wParam,
			MAKELPARAM(LOWORD(lParam) - ezWnd->ScrollX, HIWORD(lParam) - ezWnd->ScrollY));
		return 0;

	}

	case WM_RBUTTONUP:
	{
		if (IsEZWindow(ezWnd->TopWndExtend->CptMouseWindow))
		{
			//从这个窗口向上滚，找到这个窗口的坐标
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
			while (!WndNow->IsTopWindow)
			{
				//向上推，直到父窗口
				Countx += WndNow->x + WndNow->ScrollX;
				County += WndNow->y + WndNow->ScrollY;
				WndNow = WndNow->ezParent;
			}
			ezInsideWndProc(ezWnd->TopWndExtend->CptMouseWindow, EZWM_RBUTTONUP, wParam,
				MAKELPARAM(LOWORD(lParam) - Countx, HIWORD(lParam) - County));
			return 0;
		}
		ezInsideWndProc(ezWnd, EZWM_RBUTTONUP, wParam,
			MAKELPARAM(LOWORD(lParam) - ezWnd->ScrollX, HIWORD(lParam) - ezWnd->ScrollY));
		return 0;

	}

	case WM_MOUSEMOVE:
	{
		//老鼠在跑来跑去。
		if (ezWnd->MouseOn == FALSE)
		{
			//刚刚进来

			//可以进行监测了。
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			tme.hwndTrack = hwnd;
			TrackMouseEvent(&tme);
		}
		if (IsEZWindow(ezWnd->TopWndExtend->CptMouseWindow))
		{
			//从这个窗口向上滚，找到这个窗口的坐标
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//只需要把这个窗口（不需要全屏BitBlt）,得到相对父窗口的位置
			while (!WndNow->IsTopWindow)
			{
				//向上推，直到父窗口
				Countx += WndNow->x + WndNow->ScrollX;
				County += WndNow->y + WndNow->ScrollY;
				WndNow = WndNow->ezParent;
			}
			ezInsideWndProc(ezWnd->TopWndExtend->CptMouseWindow, EZWM_MOUSEMOVE, wParam,
				MAKELPARAM(LOWORD(lParam) - Countx, HIWORD(lParam) - County));
			return 0;
		}
		ezInsideWndProc(ezWnd, EZWM_MOUSEMOVE, wParam,
			MAKELPARAM(LOWORD(lParam) - ezWnd->ScrollX, HIWORD(lParam) - ezWnd->ScrollY));
		return 0;

	}

	case WM_CAPTURECHANGED:
	{
		//EZReleaseMouse(((EZWND)GetWindowLongPtr(hwnd, 0))->CptMouseWindow);
		//上面这个不行，因为这个函数还会重复调用ReleaseCapture.

		//把上面这个函数里面的内容拷下来改一改就可以了


		if (ezWnd->TopWndExtend->CptMouseWindow)
		{
			EZSendMessage(ezWnd->TopWndExtend->CptMouseWindow, EZWM_RELEASEMOUSE, 0, 0);
			ezWnd->TopWndExtend->CptMouseWindow = NULL;

		}


		return 0;
	}

	case WM_MOUSELEAVE:
	{

		//呀，老鼠跑了~~~   广播一下，让每个子窗口看看是不是从自己那里溜出去的。
		//先检查自己。
		if (ezWnd->TopWndExtend->MouseOnWnd)
		{
			ezWnd->TopWndExtend->MouseOnWnd->MouseOn = FALSE;
			EZSendMessage(ezWnd->TopWndExtend->MouseOnWnd, EZWM_MOUSELEAVE, 0, 0);
			ezWnd->TopWndExtend->MouseOnWnd = NULL;
		}


		//BroadcastProc(ezWnd, SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
		//EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);

		//发送一个消息说明鼠标是整个从窗口出去了.....
		//EZSendMessage(ezWnd, EZWM_MOUSELEAVE, (WPARAM)1, (LPARAM)NULL);
		return 0;
	}

	case WM_NCHITTEST:
	{
		int iHT;
		iHT = EZSendMessage(ezWnd, EZWM_NCHITTEST, wParam, lParam);//只有主窗口才能收到 EZWM_NCHITTEST 消息
		if (iHT == 0)
		{
			break;
		}
		return iHT;
	}


	case WM_ERASEBKGND:
	{
		//直接无视（我管你呢，反正正常的话,有ERASE就有PAINT）
		return 1;
	}

	case WM_PAINT:
	{

		//重绘区域无效啦！！！
		hdc = BeginPaint(hwnd, &ps);


		//	这里用无效矩形进行了优化
		BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, ezWnd->TopWndExtend->hdcTop, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);


		EndPaint(hwnd, &ps);

		//好了，现在有效了。设置一下。
		ezWnd->Update = 0;
		return 0;
	}

	case WM_CLOSE:
		if (EZSendMessage(ezWnd, EZWM_COLSE, 0, 0) != DO_NOT_CLOSE)
		{
			break;
		}
		return 0;

	case WM_DESTROY:
	{
		//先保存信息，倒推，消除所有子孙窗口
		if (IsEZWindow(ezWnd->FirstChild))
		{
			DestroyEZWindowWithNext(ezWnd->FirstChild);
		}
		//把你自己清理了
		EZSendMessage(ezWnd, EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//发送销毁信息
		DeleteMemDC(ezWnd->hdc);//清理DC

		DeleteMemDC(ezWnd->TopWndExtend->hdcTop);

		free(ezWnd->TopWndExtend);



		free(ezWnd);
		SetWindowLongPtr(hwnd, 0, NULL);

		break;
	}

	case WM_SETFOCUS:
		//不需要处理，有窗口接收到单击后会自行处理。
		return 0;

	case WM_KILLFOCUS:
		//通知焦点窗口，失去焦点。
		if (IsEZWindow(ezWnd->TopWndExtend->FocusWindow))
		{
			ezWnd->ezRootParent->TopWndExtend->FocusWindow->FocusState = 0;

			EZSendMessage(ezWnd->ezRootParent->TopWndExtend->FocusWindow, EZWM_KILLFOCUS, 0, 0);
			ezWnd->ezRootParent->TopWndExtend->FocusWindow = NULL;
		}
		return 0;

	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
		if (ezWnd->TopWndExtend->FocusWindow != NULL)
		{
			switch (message)
			{
			case WM_CHAR:
				EZSendMessage(ezWnd->TopWndExtend->FocusWindow, EZWM_CHAR, wParam, lParam);
				return 0;
			case WM_KEYDOWN:
				EZSendMessage(ezWnd->TopWndExtend->FocusWindow, EZWM_KEYDOWN, wParam, lParam);
				return 0;
			case WM_KEYUP:
				EZSendMessage(ezWnd->TopWndExtend->FocusWindow, EZWM_KEYUP, wParam, lParam);
				return 0;
			}

		}
		return 0;

	}

	return DefWindowProc(hwnd, message, wParam, lParam);

}

VOID CALLBACK ezInsideTimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{

	//在列表里找到对应的ezWnd，并转发EZWM_TIMER消息

	int i;
	for (i = 0; i < MAX_EZ_TIMER; i++)
	{
		if (iTimerID == ((EZWND)GetWindowLongPtr(hwnd, 0))->TopWndExtend->Timer[i].WinTimerID)
		{
			//计时器ID和记录的相符
			//那么，发送消息啊
			EZSendMessage(((EZWND)GetWindowLongPtr(hwnd, 0))->TopWndExtend->Timer[i].ezWnd, EZWM_TIMER, i, 0);


			break;
		}
	}
	return;
}

int ezInsideWndProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	//这里！修改函数，链表枚举方向应该反过来，先找到最后，然后返回来一个个检查。（保证和绘制的枚举顺序相同）
	EZWND ezChildLast;

	ezChildLast = ezWnd->FirstChild;

	if (IsEZWindow(ezChildLast))
	{

		while (ezChildLast->NextEZWnd)
		{
			ezChildLast = ezChildLast->NextEZWnd;
		}

		//滚动到链表顶部，检查是否在子窗口内
		//**************************************************
		while (ezChildLast)
		{
			//检查是否在子窗口内，注意屏幕移动
			//if (PtInEZWnd(ezChildLast, GET_X_LPARAM(lParam) - ezChildLast->ScrollX, GET_Y_LPARAM(lParam) - ezChildLast->ScrollY))
			if ((ezChildLast->MouseMsgRecv != 2) && PtInEZWnd(ezChildLast, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
			{
				//可以了，在这个窗口
				if (ezInsideWndProc(ezChildLast, message, wParam, MAKELPARAM(GET_X_LPARAM(lParam) - ezChildLast->x - ezChildLast->ScrollX, GET_Y_LPARAM(lParam) - ezChildLast->y - ezChildLast->ScrollY)) == TRANSPARENT)
				{
					//好吧，子窗口说他是透明的》。。。。。

					//先发送鼠标到来
					//更改这里的时候，别忘了把下面相同的一起改了~~~~~
					if (ezWnd->MouseOn == FALSE && message == EZWM_MOUSEMOVE)
					{
						if (ezWnd->ezRootParent->TopWndExtend->MouseOnWnd)
						{
							ezWnd->ezRootParent->TopWndExtend->MouseOnWnd->MouseOn = FALSE;//标记一下。
							EZSendMessage(ezWnd->ezRootParent->TopWndExtend->MouseOnWnd, EZWM_MOUSELEAVE, 0, 0);
						}
						ezWnd->ezRootParent->TopWndExtend->MouseOnWnd = ezWnd;

						ezWnd->MouseOn = TRUE;//标记一下。
						EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//老鼠来了
					}
					else if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//你没焦点，消息是左键
					{
						if (IsEZWindow(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow))
						{
							EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow->FocusState = 0;//你没焦点了。
							EZSendMessage(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow, EZWM_KILLFOCUS, NULL, NULL);

						}
						ezWnd->FocusState = 1;

						EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow = ezWnd;
						EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//你有焦点了！
					}

					return EZSendMessage(ezWnd, message, wParam, lParam);
				}
				return 0;
			}

			ezChildLast = ezChildLast->LastEZWnd;
		}
		//**************************************************		

		//已经到最后了，那么，就是在主窗口。直接出去和外面的合并

	}

	{
		//连个子窗口都没。。。那么，就在你这里了。

		//先发送鼠标到来消息
		//更改这里的时候，别忘了把上面相同的一起改了~~~~~
		if (message == EZWM_MOUSEMOVE && ezWnd->MouseOn == FALSE)
		{
			if (ezWnd->ezRootParent->TopWndExtend->MouseOnWnd)
			{
				ezWnd->ezRootParent->TopWndExtend->MouseOnWnd->MouseOn = FALSE;//标记一下。
				EZSendMessage(ezWnd->ezRootParent->TopWndExtend->MouseOnWnd, EZWM_MOUSELEAVE, 0, 0);
			}
			ezWnd->ezRootParent->TopWndExtend->MouseOnWnd = ezWnd;
			ezWnd->MouseOn = TRUE;//标记一下。
			EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//老鼠来了
		}

		else if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//你没焦点，消息是左键
		{
			if (IsEZWindow(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow))
			{
				EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow->FocusState = 0;//你没焦点了。
				EZSendMessage(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow, EZWM_KILLFOCUS, NULL, NULL);
			}
			ezWnd->FocusState = 1;

			EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow = ezWnd;
			EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//你有焦点了！
		}
		return EZSendMessage(ezWnd, message, wParam, lParam);

	}
}



BOOL EZBroadcastToAllChildFunc(EZWND ezWnd, BOOL sequence, int message, WPARAM wp, LPARAM lp)
{
	//注意，这个函数是以深度优先的方式发送消息的。（我懒得再写一个广度优先的，如果以后我写了，删掉这一句话）
	EZWND LastChild;

	LastChild = ezWnd->FirstChild;
	//向回滚，如正序则直接处理，倒叙不处理。
	for(;;)
	{
		if (sequence)//正
		{
			//正序，所以，先处理自己。
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
		for(;;)
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
	return TRUE;
}

BOOL BroadcastProc(EZWND ezWnd, int Param, WPARAM wP, LPARAM lP)
{
	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}

	switch (Param)
	{


	case SEZWM_COPYDC:
	{
		//看看是否是顶层EZ窗口。
		if (!ezWnd->IsTopWindow)
		{
			//不是
			BitBlt(ezWnd->ezParent->hdc,
				ezWnd->x + ezWnd->ezParent->ScrollX,
				ezWnd->y + ezWnd->ezParent->ScrollY,
				ezWnd->Width, ezWnd->Height,
				ezWnd->hdc,
				0, 0,
				SRCCOPY);
		}

		return 0;
	}
	case SEZWM_REDRAW:
	{
	
		int X_PSX;
		int Y_PSY;
		//判断是否是顶层窗口
		if (ezWnd->IsTopWindow)
		{
			//画白布一块
			PatBlt(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
			//PatBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		}
		else
		{
			X_PSX = ezWnd->x + ezWnd->ezParent->ScrollX;
			Y_PSY = ezWnd->y + ezWnd->ezParent->ScrollY;
			//复制上级窗口的相应部分。
			BitBlt(ezWnd->hdc, 0, 0,
				max(ezWnd->Width, ezWnd->ezParent->Width), max(ezWnd->Height, ezWnd->ezParent->Height),
				ezWnd->ezParent->hdcCopy,
				X_PSX,
				Y_PSY,
				SRCCOPY);
		}

		EZSendMessage(ezWnd, EZWM_TRANSDRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);


		if (ezWnd->Transparent != 255)//如果不是255，混合。是255，那么，别混合了！
		{
			BLENDFUNCTION bf = {0};
			/*bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;*/ // 这三个字段全是 0
			bf.SourceConstantAlpha = 255 - ezWnd->Transparent;

			if (!ezWnd->IsTopWindow)
			{
				//这个蠢货函数，不允许超出边界。我们只能手动确保没有超出边界。
				int ab_Width,ab_Height;
				ab_Width = min((ezWnd->Width), (ezWnd->ezParent->Width - (X_PSX)));
				ab_Height = min((ezWnd->Height), (ezWnd->ezParent->Height - (Y_PSY)));

				AlphaBlend(ezWnd->hdc,
					0, 0,
					ab_Width,
					ab_Height,
					ezWnd->ezParent->hdcCopy,
					X_PSX,
					Y_PSY,
					ab_Width,
					ab_Height,
					bf);
			}
			else
			{
				//白色
				HDC hParentdc;
				HDC hdcWhite = GetMemDC(hParentdc = GetDC(ezWnd->hParent), ezWnd->Width, ezWnd->Height);

				PatBlt(hdcWhite, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);

				AlphaBlend(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, hdcWhite, 0, 0, ezWnd->Width, ezWnd->Height, bf);

				DeleteMemDC(hdcWhite);
				ReleaseDC(ezWnd->hParent, hParentdc);
			}
		}

		//混合绘制现在以不透明的方式在DC上，现在从父窗口复制以255-透明度复制到hdcWC

		//发送普通绘制消息，绘制到DC。
		EZSendMessage(ezWnd, EZWM_DRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);
		BitBlt(ezWnd->hdcCopy, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);

		/*if (!ezWnd->IsTopWindow)
		{
		BitBlt(ezWnd->ezParent->hdc,
		ezWnd->x + ezWnd->ezParent->ScrollX,
		ezWnd->y + ezWnd->ezParent->ScrollY,
		ezWnd->Width, ezWnd->Height,
		ezWnd->hdc, 0, 0, SRCCOPY);
		}*/



		return 0;
	}


	}
}

//int EZSendMessage(EZWND ezWnd, int message, WPARAM wP, LPARAM lP)
//{
//	//if (IsEZWindow(ezWnd)/* && IsEZWindow((EZWND)(ezWnd->ezWndProc))*/)
//	{
//		//IsEZWindow函数可以通用的检查句柄是否有效
//		return ezWnd->ezWndProc(ezWnd, message, wP, lP);
//
//	}
//}

int EZWndMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



//判断函数
BOOL PtInEZWnd(EZWND ezWnd, int x, int y)
{
	return (BOOL)((x > ezWnd->x) && (x < (ezWnd->x + ezWnd->Width)) && (y > ezWnd->y) && (y < (ezWnd->y + ezWnd->Height)));
}

BOOL IsEZWindow(EZWND ezWnd)
{
	return (BOOL)(ezWnd != NULL);
}


//*********************************************************************************************************
//                下面这些函数本不属于EZWindow，但EZWindow基于这些函数。这些函数也可以单独使用。
//*********************************************************************************************************

HDC GetMemDC(HDC hdc, int cx, int cy)
{
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, cx, cy);
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, hBitmap);
	DeleteObject(hBitmap);
	return hdcMem;
}


BOOL DeleteMemDC(HDC hdc) 
{
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 1, 1);
	DeleteObject(SelectObject(hdc, hBitmap));
	DeleteDC(hdc);
	DeleteObject(hBitmap);
	return TRUE;
}


//*********************************************************************************************************
//                EZWindow风格扩展头文件 以及宏定义
//*********************************************************************************************************




EZWNDPROC EZStyle_ButtonProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	switch (message)
	{
	case EZWM_CREATE:
		SetEZWndTransparent(ezWnd, 30);
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
			SetEZWndTransparent(ezWnd, 90);
			EZRepaint(ezWnd, NULL);
		}

		return 0;
	case EZWM_LBUTTONUP:
		SetEZWndTransparent(ezWnd, 60);
		EZRepaint(ezWnd, NULL);
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
		SetEZWndTransparent(ezWnd, 60);
		EZRepaint(ezWnd, NULL);
		return 0;

	case EZWM_RELEASEMOUSE:
		(((ezWnd->Extend))->MouseHold) = FALSE;
		return 0;

	case EZWM_MOUSELEAVE:
		SetEZWndTransparent(ezWnd, 30);
		EZRepaint(ezWnd, NULL);
		return 0;

	}
	return EZStyle_DefaultProc(ezWnd, message, wParam, lParam);
}


EZWNDPROC EZStyle_StaticProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	switch (message)
	{
	case EZWM_CREATE:
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
		DrawText(wParam, ezWnd->Extend->Title, -1, &rect, (ezWnd->Extend->TextAlign == 0) ? (DT_WORDBREAK | DT_EDITCONTROL | DT_NOCLIP) : (ezWnd->Extend->TextAlign));

		return 0;
	case EZWM_TRANSDRAW:
		hPen = CreatePen(PS_INSIDEFRAME, 1, (COLORREF)(((ezWnd->Extend))->ForeGroundColor));
		SelectObject(wParam, hPen);


		hBrush = CreateSolidBrush((COLORREF)(((ezWnd->Extend))->BackGroundColor));
		SelectObject(wParam, hBrush);
		if (CHK_ALT_STYLE(ezWnd->EZStyle, EZS_BORDER))
		{
			Rectangle(wParam, 0, 0, ezWnd->Width, ezWnd->Height);
		}
		else
		{
			PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);
		}
		DeleteObject(hBrush);

		DeleteObject(hPen);
		return 0;
	}
	return EZStyle_DefaultProc(ezWnd, message, wParam, lParam);
}


EZWNDPROC EZStyle_ScrollChildProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{

	double BarLen;
	switch (message)
	{
	case EZWM_CREATE:
		//创建3个子窗口
		//向上（左？）滚动 -- 扩展0号控件 
		//向下（右？）滚动 -- 扩展1号控件 
		//拖动条 -- 扩展2号控件 

		ezWnd->Extend->hExtend[0] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Scroll_BtnProc);
		ezWnd->Extend->hExtend[0]->ezID = 0;

		ezWnd->Extend->hExtend[1] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Scroll_BtnProc);
		ezWnd->Extend->hExtend[1]->ezID = 1;

		ezWnd->Extend->hExtend[2] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Scroll_BarProc);
		ezWnd->Extend->hExtend[2]->ezID = 2;


		//为了让子窗口可以更方便的判断应该横向还是纵向绘制
		//用两个按钮的Style进行标识

		if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
		{
			//EZS_CHILD_VSCROLL，竖直
			ezWnd->Extend->hExtend[0]->EZStyle = ezWnd->Extend->hExtend[1]->EZStyle = 0;
		}
		else
		{
			//EZS_CHILD_HSCROLL，水平
			ezWnd->Extend->hExtend[0]->EZStyle = ezWnd->Extend->hExtend[1]->EZStyle = 1;
		}


		//初始化滚动范围，位置
		//滚动最大范围 -- int扩展 0 号
		//滚动位置上 -- int扩展 1 号
		//滚动位置下 -- int扩展 2 号
		ezWnd->Extend->iExtend[0] = 16;//默认16？2333，随便了。
		ezWnd->Extend->iExtend[1] = 0;//默认0
		ezWnd->Extend->iExtend[2] = 1;//默认1

		return 0;
	case EZWM_SIZE:
	{

		if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
		{	//EZS_CHILD_VSCROLL，竖直

			//检测竖直方向长度是否大于3倍水平，不然也太不像话了。
			if (!(ezWnd->Height >= ezWnd->Width * 3))
			{
				//滚吧
				MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[1], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[2], 0, 0, 0, 0, 0);
				return 0;
			}
			//调整位置咯
			MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, ezWnd->Width, (ezWnd->Width * 17) / 15, 0);//上面那个按钮
			MoveEZWindow(ezWnd->Extend->hExtend[1], 0, ezWnd->Height - (ezWnd->Width * 17) / 15, ezWnd->Width, (ezWnd->Width * 17) / 15, 0);//下面那个按钮

																																			//滚动条宽度为 MAX(（总宽度 / 最大滚动范围）,最小宽度）

																																			//总宽度是要扣去两边的按钮的哦
			BarLen = ((ezWnd->Height - (ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
			MoveEZWindow(ezWnd->Extend->hExtend[2],
				0,
				ceil(ezWnd->Width * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
				ezWnd->Width,
				BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
				0);

		}
		else
		{	//EZS_CHILD_HSCROLL，水平

			//检测水平方向长度是否大于3倍竖直，不然也太不像话了。
			if (!(ezWnd->Width >= ezWnd->Height * 3))
			{
				//滚吧
				MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[1], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[2], 0, 0, 0, 0, 0);
				return 0;
			}
			//调整位置咯
			MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, (ezWnd->Height * 17.0) / 15.0, ezWnd->Height, 0);//左边那个按钮
			MoveEZWindow(ezWnd->Extend->hExtend[1], ezWnd->Width - (ezWnd->Height * 17.0) / 15.0, 0, (ezWnd->Height * 17.0) / 15.0, ezWnd->Height, 0);//右边那个按钮


			BarLen = (((float)ezWnd->Width - (float)(ezWnd->Height) * 34.0 / 15.0) / ((float)(ezWnd->Extend->iExtend[0])));

			MoveEZWindow(ezWnd->Extend->hExtend[2],
				ceil(ezWnd->Height * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
				0,
				BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
				ezWnd->Height,
				0);


		}
		return 0;
	}

	case EZWM_SETSCROLLRANGE:
		ezWnd->Extend->iExtend[0] = wParam;
		if (ezWnd->Extend->iExtend[2] > wParam)
		{
			ezWnd->Extend->iExtend[1] = 0;
			ezWnd->Extend->iExtend[2] = 1;
		}
		if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
		{	//EZS_CHILD_VSCROLL，竖直
			BarLen = ((ezWnd->Height - (ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
			MoveEZWindow(ezWnd->Extend->hExtend[2],
				0,
				ceil(ezWnd->Width * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
				ezWnd->Width,
				BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
				0);
		}
		else
		{	//EZS_CHILD_HSCROLL，水平
			BarLen = (((float)ezWnd->Width - (float)(ezWnd->Height) * 34.0 / 15.0) / ((float)(ezWnd->Extend->iExtend[0])));

			MoveEZWindow(ezWnd->Extend->hExtend[2],
				ceil(ezWnd->Height * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
				0,
				BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
				ezWnd->Height,
				0);
		}

		return 0;

	case EZWM_SETSCROLLPOS:

		if (wParam < lParam)
		{
			ezWnd->Extend->iExtend[1] = wParam;
			ezWnd->Extend->iExtend[2] = lParam;
			if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
			{	//EZS_CHILD_VSCROLL，竖直
				BarLen = ((ezWnd->Height - (ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
				MoveEZWindow(ezWnd->Extend->hExtend[2],
					0,
					ceil(ezWnd->Width * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
					ezWnd->Width,
					BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
					0);
			}
			else
			{	//EZS_CHILD_HSCROLL，水平
				BarLen = (((float)ezWnd->Width - (float)(ezWnd->Height) * 34.0 / 15.0) / ((float)(ezWnd->Extend->iExtend[0])));

				MoveEZWindow(ezWnd->Extend->hExtend[2],
					ceil(ezWnd->Height * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
					0,
					BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
					ezWnd->Height,
					0);
			}
			EZSendMessage(ezWnd->ezParent, EZWM_SCROLLPOSCHANGE, wParam, ezWnd);
		}
		EZRepaint(ezWnd, NULL);
		return 0;

	case EZWM_COMMAND:
		if (lParam == ezWnd->Extend->hExtend[0])
		{
			if (ezWnd->Extend->iExtend[1] - (int)(ezWnd->Extend->iExtend[0] / 10) >= 0)
			{
				EZSendMessage(ezWnd, EZWM_SETSCROLLPOS,
					ezWnd->Extend->iExtend[1] - (int)(ezWnd->Extend->iExtend[0] / 10),
					ezWnd->Extend->iExtend[2] - (int)(ezWnd->Extend->iExtend[0] / 10));
			}
			else
			{
				EZSendMessage(ezWnd, EZWM_SETSCROLLPOS,
					0,
					ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]);
			}
		}
		if (lParam == ezWnd->Extend->hExtend[1])
		{
			if (ezWnd->Extend->iExtend[2] + (int)(ezWnd->Extend->iExtend[0] / 10) <= ezWnd->Extend->iExtend[0])
			{
				EZSendMessage(ezWnd, EZWM_SETSCROLLPOS,
					ezWnd->Extend->iExtend[1] + (int)(ezWnd->Extend->iExtend[0] / 10),
					ezWnd->Extend->iExtend[2] + (int)(ezWnd->Extend->iExtend[0] / 10));
			}
			else
			{
				EZSendMessage(ezWnd, EZWM_SETSCROLLPOS,
					ezWnd->Extend->iExtend[0] - (ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
					ezWnd->Extend->iExtend[0]);
			}
		}
		if (lParam == ezWnd->Extend->hExtend[2])
		{
			int iMove;
			if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
			{	//EZS_CHILD_VSCROLL，竖直
				BarLen = (((float)ezWnd->Height - (float)(ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
				iMove = ceil((float)GET_Y_LPARAM(wParam) / BarLen);//参数通过wParam传送过来
			}
			else
			{
				BarLen = (((float)ezWnd->Width - (float)(ezWnd->Height) * 34.0 / 15.0) / ((float)(ezWnd->Extend->iExtend[0])));
				iMove = ceil((float)GET_X_LPARAM(wParam) / BarLen);//参数通过wParam传送过来
			}
			if (-iMove > ezWnd->Extend->iExtend[1])
			{
				iMove = -ezWnd->Extend->iExtend[1];
			}
			if (iMove + ezWnd->Extend->iExtend[2] > ezWnd->Extend->iExtend[0])
			{
				iMove = ezWnd->Extend->iExtend[0] - ezWnd->Extend->iExtend[2];
			}

			EZSendMessage(ezWnd, EZWM_SETSCROLLPOS, ezWnd->Extend->iExtend[1] + iMove, ezWnd->Extend->iExtend[2] + iMove);

		}
		return 0;
	}
	return EZStyle_DefaultProc(ezWnd, message, wParam, lParam);
}

EZWNDPROC EZStyle_Scroll_BtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrush;
	HPEN hPen;
	POINT pt[7];
	switch (message)
	{
	case EZWM_CREATE:
		//这个窗口嘛，只是普通创建出来的，可惜我们也想用扩展，那自己申请啊~
		ezWnd->Extend = malloc(sizeof(EZSE));

		((pEZSE)ezWnd->Extend)->BackGroundColor = RGB(70, 70, 70);
		((pEZSE)ezWnd->Extend)->ForeGroundColor = RGB(70, 70, 70);

		((pEZSE)ezWnd->Extend)->MouseHold = FALSE;

		((pEZSE)ezWnd->Extend)->hFont = NULL;
		((pEZSE)ezWnd->Extend)->IsFontUserControl = -1;

		ezWnd->Extend->Title = NULL;//这样清理的时候就会跳过清理了，免着free一个野指针。

									//MD，不是样式窗口（假冒的）
		ezWnd->IsStyleWindow = FALSE;
		ezWnd->EZStyle = NULL;

		ezWnd->Extend->iExtend[0] = 0;
		//设置透明度 
		SetEZWndTransparent(ezWnd, 20);
		EZRepaint(ezWnd, NULL);
		return 0;




	case EZWM_LBUTTONDOWN:
		if ((((ezWnd->Extend))->MouseHold) == FALSE)
		{
			EZCaptureMouse(ezWnd);

			(((ezWnd->Extend))->MouseHold) = TRUE;
			SetEZWndTransparent(ezWnd, 200);
			EZRepaint(ezWnd, NULL);
			EZSendMessage(ezWnd->ezParent, EZWM_COMMAND, 0, ezWnd);
			ezWnd->TimerID[0] = SetEZTimer(ezWnd, 80);
		}

		return 0;
	case EZWM_LBUTTONUP:
		SetEZWndTransparent(ezWnd, 40);
		EZRepaint(ezWnd, NULL);
		if ((((ezWnd->Extend))->MouseHold) == TRUE)
		{
			EZReleaseMouse(ezWnd);
			KillEZTimer(ezWnd, ezWnd->TimerID[0]);
			ezWnd->Extend->iExtend[0] = 0;
		}
		return 0;
	case EZWM_MOUSECOME:
		SetEZWndTransparent(ezWnd, 40);
		EZRepaint(ezWnd, NULL);
		return 0;

	case EZWM_RELEASEMOUSE:
		(((ezWnd->Extend))->MouseHold) = FALSE;
		return 0;

	case EZWM_MOUSELEAVE:
		if ((((ezWnd->Extend))->MouseHold) == TRUE)
		{
			ezWnd->Extend->MouseHold = FALSE;
			KillEZTimer(ezWnd, ezWnd->TimerID[0]);
			ezWnd->Extend->iExtend[0] = 0;
		}

		SetEZWndTransparent(ezWnd, 20);
		EZRepaint(ezWnd, NULL);
		return 0;


		//case EZWM_LBUTTONDOWN:
		//	if ((((ezWnd->Extend))->MouseHold) == FALSE)
		//	{
		//		EZCaptureMouse(ezWnd);
		//		(((ezWnd->Extend))->MouseHold) = TRUE;
		//		//ezWnd->TimerID[0] = SetTimer(NULL, 0, 100, ScrollBtnTimerProc);
		//		//这里！设置定时器！

		//		EZSendMessage(ezWnd->ezParent, EZWM_COMMAND, 0, ezWnd);
		//		ezWnd->TimerID[0] = SetEZTimer(ezWnd, 80);

		//		SetEZWndTransparent(ezWnd, 200);
		//		EZRepaint(ezWnd, NULL);
		//	}
		//	return 0;

		//case EZWM_LBUTTONUP:
		//	if ((((ezWnd->Extend))->MouseHold) == TRUE)
		//	{
		//		
		//		(((ezWnd->Extend))->MouseHold) = FALSE;
		//		//这里！取消定时器！
		//		KillEZTimer(ezWnd, ezWnd->TimerID[0]);
		//		ezWnd->Extend->iExtend[0] = 0;

		//		SetEZWndTransparent(ezWnd, 40);
		//		EZReleaseMouse(ezWnd);
		//		EZRepaint(ezWnd, NULL);
		//	}
		//	return 0;

		//case EZWM_MOUSECOME:
		//	SetEZWndTransparent(ezWnd, 40);
		//	EZRepaint(ezWnd, NULL);
		//	return 0;

		//case EZWM_MOUSELEAVE:
		//	if ((((ezWnd->Extend))->MouseHold) == TRUE)
		//	{
		//		ezWnd->Extend->MouseHold = FALSE;
		//		KillEZTimer(ezWnd, ezWnd->TimerID[0]);
		//		ezWnd->Extend->iExtend[0] = 0;
		//	}
		//	SetEZWndTransparent(ezWnd, 20);
		//	EZRepaint(ezWnd, NULL);
		//	return 0;

	case EZWM_DRAW:
		//绘制箭头
		//就地define.
#define SRLBTN_ARR_W 3
#define SRLBTN_ARR_H 2

		//准备画笔，画刷。
		hPen = NULL;
		hBrush = NULL;
		if ((((ezWnd->Extend))->MouseHold) == TRUE)
		{
			SelectObject(wParam, GetStockObject(WHITE_PEN));
			SelectObject(wParam, GetStockObject(WHITE_BRUSH));
		}
		else
		{
			SelectObject(wParam, hPen = CreatePen(PS_SOLID, 1, ezWnd->Extend->ForeGroundColor));
			SelectObject(wParam, hBrush = CreateSolidBrush(ezWnd->Extend->ForeGroundColor));
		}

		if (ezWnd->EZStyle == 0)
		{
			//竖直
			pt[0].x = ezWnd->Width / 2;
			pt[1].x = ezWnd->Width / 2 + SRLBTN_ARR_W;
			pt[2].x = ezWnd->Width / 2 + SRLBTN_ARR_W;
			pt[3].x = ezWnd->Width / 2;
			pt[4].x = ezWnd->Width / 2 - SRLBTN_ARR_W;
			pt[5].x = ezWnd->Width / 2 - SRLBTN_ARR_W;
			pt[6].x = ezWnd->Width / 2;
			if (ezWnd->ezID == 0)
			{

				pt[0].y = ezWnd->Height / 2 - SRLBTN_ARR_H;

				pt[1].y = ezWnd->Height / 2 - SRLBTN_ARR_H + SRLBTN_ARR_W;

				pt[2].y = ezWnd->Height / 2 + SRLBTN_ARR_W;

				pt[3].y = ezWnd->Height / 2;

				pt[4].y = ezWnd->Height / 2 + SRLBTN_ARR_W;

				pt[5].y = ezWnd->Height / 2 - SRLBTN_ARR_H + SRLBTN_ARR_W;

				pt[6].y = ezWnd->Height / 2 - SRLBTN_ARR_H;
			}
			else
			{

				pt[0].y = ezWnd->Height / 2 + SRLBTN_ARR_H;

				pt[1].y = ezWnd->Height / 2 + SRLBTN_ARR_H - SRLBTN_ARR_W;

				pt[2].y = ezWnd->Height / 2 - SRLBTN_ARR_W;

				pt[3].y = ezWnd->Height / 2;

				pt[4].y = ezWnd->Height / 2 - SRLBTN_ARR_W;

				pt[5].y = ezWnd->Height / 2 + SRLBTN_ARR_H - SRLBTN_ARR_W;

				pt[6].y = ezWnd->Height / 2 + SRLBTN_ARR_H;
			}


		}
		else
		{
			//水平

			pt[0].y = ezWnd->Height / 2;
			pt[1].y = ezWnd->Height / 2 + SRLBTN_ARR_W;
			pt[2].y = ezWnd->Height / 2 + SRLBTN_ARR_W;
			pt[3].y = ezWnd->Height / 2;
			pt[4].y = ezWnd->Height / 2 - SRLBTN_ARR_W;
			pt[5].y = ezWnd->Height / 2 - SRLBTN_ARR_W;
			pt[6].y = ezWnd->Height / 2;
			if (ezWnd->ezID == 0)
			{

				pt[0].x = ezWnd->Width / 2 - SRLBTN_ARR_H;

				pt[1].x = ezWnd->Width / 2 - SRLBTN_ARR_H + SRLBTN_ARR_W;

				pt[2].x = ezWnd->Width / 2 + SRLBTN_ARR_W;

				pt[3].x = ezWnd->Width / 2;

				pt[4].x = ezWnd->Width / 2 + SRLBTN_ARR_W;

				pt[5].x = ezWnd->Width / 2 - SRLBTN_ARR_H + SRLBTN_ARR_W;

				pt[6].x = ezWnd->Width / 2 - SRLBTN_ARR_H;
			}
			else
			{

				pt[0].x = ezWnd->Width / 2 + SRLBTN_ARR_H;

				pt[1].x = ezWnd->Width / 2 + SRLBTN_ARR_H - SRLBTN_ARR_W;

				pt[2].x = ezWnd->Width / 2 - SRLBTN_ARR_W;

				pt[3].x = ezWnd->Width / 2;

				pt[4].x = ezWnd->Width / 2 - SRLBTN_ARR_W;

				pt[5].x = ezWnd->Width / 2 + SRLBTN_ARR_H - SRLBTN_ARR_W;

				pt[6].x = ezWnd->Width / 2 + SRLBTN_ARR_H;
			}

		}

		Polygon((HDC)wParam, &pt, 6);


		if ((((ezWnd->Extend))->MouseHold) == FALSE)
		{
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
		return 0;

	case EZWM_TRANSDRAW:
		//绘制透明背景
		SelectObject(wParam, hBrush = CreateSolidBrush(ezWnd->Extend->BackGroundColor));
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);
		DeleteObject(hBrush);
		return 0;

	case EZWM_TIMER:
		//添加处理
		if (ezWnd->Extend->iExtend[0] < 3)
		{
			ezWnd->Extend->iExtend[0]++;
		}
		else
		{
			EZSendMessage(ezWnd->ezParent, EZWM_COMMAND, 0, ezWnd);
		}

		return 0;

	case EZWM_DESTROY:
		free(ezWnd->Extend);
		return 0;

	}
	return EZStyle_DefaultProc(ezWnd, message, wParam, lParam);
}

EZWNDPROC EZStyle_Scroll_BarProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrush;
	switch (message)
	{
	case EZWM_CREATE:
		//我们也想用扩展！！！
		ezWnd->Extend = malloc(sizeof(EZSE));

		//不用
		//((pEZSE)ezWnd->Extend)->BackGroundColor = RGB(70, 70, 70);
		//((pEZSE)ezWnd->Extend)->ForeGroundColor = RGB(70, 70, 70);

		((pEZSE)ezWnd->Extend)->MouseHold = FALSE;

		((pEZSE)ezWnd->Extend)->hFont = NULL;
		((pEZSE)ezWnd->Extend)->IsFontUserControl = -1;

		ezWnd->Extend->Title = NULL;//这样清理的时候就会跳过清理了，免着free一个野指针。

									//MD，不是样式窗口（假冒的）
		ezWnd->IsStyleWindow = FALSE;
		ezWnd->EZStyle = NULL;



		SetEZWndTransparent(ezWnd, 50);
		return 0;

	case EZWM_TRANSDRAW:
		hBrush = CreateSolidBrush(RGB(36, 36, 36));

		SelectObject(wParam, hBrush);
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);

		DeleteObject(hBrush);
		return 0;
	case EZWM_LBUTTONDOWN:
		if (ezWnd->Extend->MouseHold == FALSE)
		{
			ezWnd->Extend->MouseHold = TRUE;

			EZCaptureMouse(ezWnd);

			//记录鼠标按下的位置
			ezWnd->Extend->iExtend[0] = GET_X_LPARAM(lParam);
			ezWnd->Extend->iExtend[1] = GET_Y_LPARAM(lParam);

			SetEZWndTransparent(ezWnd, 180);
			EZRepaint(ezWnd, NULL);
		}
		return 0;
	case EZWM_LBUTTONUP:
		if (ezWnd->Extend->MouseHold == TRUE)
		{
			ezWnd->Extend->MouseHold = FALSE;
			EZReleaseMouse(ezWnd);
			SetEZWndTransparent(ezWnd, 95);
			EZRepaint(ezWnd, NULL);
		}

	case EZWM_MOUSEMOVE:
		if (ezWnd->Extend->MouseHold == TRUE)
		{
			//别忘了，这是一个滚动条.
			//将鼠标移动的情况告诉父窗口
			EZSendMessage(ezWnd->ezParent, EZWM_COMMAND,
				MAKELPARAM(GET_X_LPARAM(lParam) - ezWnd->Extend->iExtend[0], GET_Y_LPARAM(lParam) - ezWnd->Extend->iExtend[1]),
				ezWnd);
			EZRepaint(ezWnd, NULL);
		}
		return 0;
	case EZWM_MOUSECOME:
		SetEZWndTransparent(ezWnd, 95);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_MOUSELEAVE:
		/*if (ezWnd->Extend->MouseHold == TRUE)
		{
		EZReleaseMouse(ezWnd);
		}*/

		SetEZWndTransparent(ezWnd, 50);
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_RELEASEMOUSE:
		(((ezWnd->Extend))->MouseHold) = FALSE;
		return 0;

	case EZWM_DESTROY:
		free(ezWnd->Extend);
		return 0;
	}
}



EZWNDPROC EZStyle_DefaultProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case EZWM_SETCOLOR:
	{
		if (ezWnd->Extend)
		{
			ezWnd->Extend->BackGroundColor = (COLORREF)wParam;
			ezWnd->Extend->ForeGroundColor = (COLORREF)lParam;

			EZRepaint(ezWnd, NULL);

		}
	}
	return 0;
	case EZWM_SETFONT:
	{

		if (((pEZSE)ezWnd->Extend)->hFont)
		{
			switch (((pEZSE)ezWnd->Extend)->IsFontUserControl)
			{
			case 1:
			case 2:
				DeleteObject(((pEZSE)ezWnd->Extend)->hFont);
				break;
			}
			((pEZSE)ezWnd->Extend)->hFont = NULL;
		}

		if (wParam)
		{
			//用户提交了HFONT，用户负责释放。
			((pEZSE)ezWnd->Extend)->hFont = (HFONT)wParam;
			((pEZSE)ezWnd->Extend)->IsFontUserControl = 0;
		}
		else if (lParam)
		{
			//用户提交了LOGFONT，我们创建并销毁。
			((pEZSE)ezWnd->Extend)->hFont = CreateFontIndirect(lParam);
			((pEZSE)ezWnd->Extend)->IsFontUserControl = 1;
		}
		else
		{
			//都为空，使用默认字体。
			LOGFONT lf;
			lf.lfHeight = 19;
			lf.lfWidth = 0;
			lf.lfEscapement = 0;
			lf.lfOrientation = 0;
			lf.lfWeight = 0;//1
			lf.lfItalic = 0;//1
			lf.lfUnderline = 0;//1
			lf.lfStrikeOut = 0;//1
			lf.lfCharSet = DEFAULT_CHARSET;
			lf.lfOutPrecision = 0;
			lf.lfClipPrecision = 0;
			lf.lfQuality = 0;
			lf.lfPitchAndFamily = 0;
			lstrcpy(lf.lfFaceName, TEXT("微软雅黑"));
			((pEZSE)ezWnd->Extend)->hFont = CreateFontIndirect(&lf);
			((pEZSE)ezWnd->Extend)->IsFontUserControl = 2;
		}
		return 0;
	}

	case EZWM_SETTEXT:
	{
		int TitleLen;
		if (lParam == 0)
		{
			TitleLen = lstrlen(wParam);
		}
		else
		{
			TitleLen = lParam;
		}

		if ((TitleLen) > MAX_TEXT - 2)
		{
			return FALSE;
		}
		if (ezWnd->Extend)
		{
			if (((pEZSE)(ezWnd->Extend))->Title)
			{
				free(((pEZSE)(ezWnd->Extend))->Title);
			}
#ifdef UNICODE
			((pEZSE)ezWnd->Extend)->Title = malloc(TitleLen * 2 + 4);
			ezWnd->Extend->TitleLen = TitleLen;
			lstrcpyn(((pEZSE)ezWnd->Extend)->Title, wParam, TitleLen + 1);
			((pEZSE)ezWnd->Extend)->Title[TitleLen * 2 + 2] = '\0';
			((pEZSE)ezWnd->Extend)->Title[TitleLen * 2 + 3] = '\0';
#else
			((pEZSE)ezWnd->Extend)->Title = (PBYTE)malloc(TitleLen + 2);
			strcpy((char *)((pEZSE)ezWnd->Extend)->Title, wParam);
			((pEZSE)ezWnd->Extend)->Title[TitleLen] = '\0';
			((pEZSE)ezWnd->Extend)->Title[TitleLen + 1] = '\0';
#endif

			return TRUE;

		}

	}
	break;
	case EZWM_DESTROY:
	{
		//清理系列内容
		if (ezWnd->Extend)
		{
			//清理字体
			if (((pEZSE)ezWnd->Extend)->hFont)
			{
				switch (((pEZSE)ezWnd->Extend)->IsFontUserControl)
				{
				case 1:
				case 2:
					DeleteObject(((pEZSE)ezWnd->Extend)->hFont);
					break;
				}
				((pEZSE)ezWnd->Extend)->hFont = NULL;
			}

			//清理标题
			if (((pEZSE)ezWnd->Extend)->Title)
			{
				free(((pEZSE)(ezWnd->Extend))->Title);
			}
		}
		return 0;
	}

	case EZWM_SETTEXTALIGN:
	{
		ezWnd->Extend->TextAlign = wParam;
		return 0;
	}

	}
	return 0;
}




EZWNDPROC EZStyle_EditProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	int iMove, LastMove;
	int iMaxLen;
	int LineCount;
	int xCount, yCount;
	SIZE size;
	TCHAR *Text;

	switch (message)
	{
	case EZWM_CREATE:
		//创建子窗口。
		//0号扩展放主编辑窗口
		//1号扩展放竖直滚动条
		//2号水平滚动条
		ezWnd->Extend->iExtend[0] = 0;
		ezWnd->Extend->iExtend[1] = 0;
		ezWnd->Extend->iExtend[2] = 0;
		ezWnd->Extend->hExtend[0] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Edit_InputProc);//主编辑窗口
		ezWnd->Extend->hExtend[1] = CreateEZStyleWindow(ezWnd, TEXT(""), EZS_CHILD | EZS_CHILD_VSCROLL, 0, 0, 0, 0);
		ezWnd->Extend->hExtend[2] = CreateEZStyleWindow(ezWnd, TEXT(""), EZS_CHILD | EZS_CHILD_HSCROLL, 0, 0, 0, 0);

		ezWnd->Extend->iExtend[3] = -1;//无限制
		ezWnd->Extend->BackGroundColor = RGB(255, 255, 255);
		SetEZWndTransparent(ezWnd, 0);

		return 0;

	case EZWM_SETMAXTEXT:
		ezWnd->Extend->iExtend[3] = wParam;
		return 0;

	case EZWM_SIZE:
	{
		MoveEZWindow(ezWnd->Extend->hExtend[0],
			0, 0,
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_VSCROLL) ? ezWnd->Width - 15 : ezWnd->Width,
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_HSCROLL) ? ezWnd->Height - 15 : ezWnd->Height,
			0);
		MoveEZWindow(ezWnd->Extend->hExtend[1],//竖直，V
			ezWnd->Width - 15, 0,
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_VSCROLL) ? (15) : (0),
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_HSCROLL) ? (ezWnd->Height - 15) : (ezWnd->Height)
			, 0);
		MoveEZWindow(ezWnd->Extend->hExtend[2],//水平，H
			0, ezWnd->Height - 15,
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_VSCROLL) ? (ezWnd->Width - 15) : (ezWnd->Width),
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_HSCROLL) ? (15) : (0)
			, 0);
		return 0;
	}

	case EZWM_SETFONT:
		//嘿嘿，骚操作。直接递交给默认处理。
		EZStyle_DefaultProc(ezWnd, message, wParam, lParam);


		//并入下面SETTEXT的部分
	case EZWM_SETTEXT:
		//截下来，计算好大小，然后再提交给默认处理
	{

		if (message == EZWM_SETTEXT)
		{
			Text = (TCHAR *)wParam;
			if (lParam == 0)
			{
				iMaxLen = lstrlen(Text);
			}
			else
			{
				iMaxLen = lParam;
			}

		}
		else
		{//EZWM_SETFONT
			Text = ezWnd->Extend->Title;
			iMaxLen = ezWnd->Extend->TitleLen;
		}

		LastMove = 0;
		xCount = yCount = 0;
		LineCount = 0;

		if (ezWnd->Extend->hFont)
		{
			SelectObject(ezWnd->hdc, ezWnd->Extend->hFont);
		}


		TEXTMETRIC tm;
		GetTextMetrics(ezWnd->hdc, &tm);

		for (iMove = 0; iMove <= iMaxLen;)
		{

			if (Text[iMove] == '\0')
			{
				//绘制当前行，并退出。
				GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				xCount = max(xCount, size.cx);
				LineCount++;

				break;
			}
			else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
			{
				//windows换行标记，绘制当前行，重新开始。
				GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				xCount = max(xCount, size.cx);
				LineCount++;

				LastMove = iMove + 2;
				iMove++;

			}
			else if (Text[iMove] == '\n')
			{
				//Linux换行标记，绘制当前行。
				GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				xCount = max(xCount, size.cx);
				LineCount++;

				LastMove = iMove + 1;
			}
			iMove++;//放在for里面我怕我搞混....放到这里就不会了
		}

		//设置滚动条
		MoveEZWindow(ezWnd->Extend->hExtend[3], 0, 0, max(ezWnd->Extend->hExtend[0]->Width, xCount), max(ezWnd->Extend->hExtend[0]->Height, yCount), 0);





		EZSendMessage(ezWnd->Extend->hExtend[1], EZWM_SETSCROLLRANGE, max(ezWnd->Extend->hExtend[0]->Height, yCount), 0);
		EZSendMessage(ezWnd->Extend->hExtend[2], EZWM_SETSCROLLRANGE, max(ezWnd->Extend->hExtend[0]->Width, xCount), 0);


		if (ezWnd->Extend->iExtend[1] > ezWnd->Extend->hExtend[0]->Height)
		{
			EZSendMessage(ezWnd->Extend->hExtend[1], EZWM_SETSCROLLPOS, ezWnd->Extend->hExtend[0]->Height - ezWnd->Extend->iExtend[0],
				ezWnd->Extend->hExtend[0]->Height);
		}
		else
		{
			EZSendMessage(ezWnd->Extend->hExtend[1], EZWM_SETSCROLLPOS, 0,
				ezWnd->Extend->hExtend[0]->Height);
		}
		if (ezWnd->Extend->iExtend[0] > ezWnd->Extend->hExtend[0]->Width)
		{
			EZSendMessage(ezWnd->Extend->hExtend[2], EZWM_SETSCROLLPOS, ezWnd->Extend->iExtend[0] - ezWnd->Extend->hExtend[0]->Width,
				ezWnd->Extend->iExtend[0]);
		}
		else
		{
			EZSendMessage(ezWnd->Extend->hExtend[2], EZWM_SETSCROLLPOS, 0, ezWnd->Extend->hExtend[0]->Width);
		}



		if (message == EZWM_SETFONT)
		{
			//已经给默认处理提交过了，在前面。
			return 0;
		}
		//else,EZWM_SETTEXT，提交给默认处理。
		break;
	}
	break;

	case EZWM_SCROLLPOSCHANGE:
		//wParam就是偏移像素数
		if (lParam == ezWnd->Extend->hExtend[1])//竖直
		{
			ezWnd->Extend->hExtend[0]->ScrollY = -((int)wParam);
		}
		else if (lParam == ezWnd->Extend->hExtend[2])//水平
		{
			ezWnd->Extend->hExtend[0]->ScrollX = -((int)wParam);
		}
		EZRepaint(ezWnd, NULL);
		return 0;
	case EZWM_TRANSDRAW:
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(ezWnd->Extend->BackGroundColor);
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);
		DeleteObject(hBrush);
	}
	return 0;

	}
	return EZStyle_DefaultProc(ezWnd, message, wParam, lParam);
}

EZWNDPROC EZStyle_Edit_InputProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case EZWM_CREATE:
		//父窗口的扩展浪费了，干脆我们也一起用父窗口多余的扩展吧
		ezWnd->ezParent->Extend->hExtend[3] = CreateEZWindow(ezWnd, 0, 0, 100, 100, EZStyle_Edit_InputChildProc);
		return 0;
		//case EZWM_SIZE:
		//	MoveEZWindow(ezWnd->ezParent->Extend->hExtend[3], 0, 0, ezWnd->Width, ezWnd->Height, 1);
		//	return 0;
	}
}

EZWNDPROC EZStyle_Edit_InputChildProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	int iMove, LastMove;
	int iMaxLen;
	int xCount, yCount;
	int CaretX, CaretY;
	SIZE size;
	TCHAR *Text;
	TEXTMETRIC tm;
	TCHAR TextBuffer[MAX_TEXT];
	switch (message)
	{
	case EZWM_CREATE:
		return 0;
	case EZWM_LBUTTONDOWN:
	{

		int LineCount;
		Text = ezWnd->ezParent->ezParent->Extend->Title;
		iMaxLen = ezWnd->ezParent->ezParent->Extend->TitleLen;

		LineCount = 0;
		LastMove = 0;
		xCount = yCount = 0;


		BOOL IsFounded;
		IsFounded = FALSE;
		if (ezWnd->ezParent->ezParent->Extend->hFont)
		{
			SelectObject(ezWnd->hdc, ezWnd->ezParent->ezParent->Extend->hFont);
		}
		GetTextMetrics(ezWnd->hdc, &tm);

		for (iMove = 0; iMove <= iMaxLen;)
		{
			if (Text[iMove] == '\0')
			{
				//当前行，并退出。
				//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				if (yCount >= GET_Y_LPARAM(lParam))
				{
					IsFounded = TRUE;
					yCount -= tm.tmHeight;
					break;
				}
				break;
			}
			else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
			{
				//windows换行标记，重新开始。
				//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				if (yCount >= GET_Y_LPARAM(lParam))
				{
					IsFounded = TRUE;
					yCount -= tm.tmHeight;
					break;
				}
				LineCount++;
				LastMove = iMove + 2;
				iMove++;

			}
			if (Text[iMove] == '\n')
			{
				//Linux换行标记
				//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				if (yCount >= GET_Y_LPARAM(lParam))
				{
					IsFounded = TRUE;
					yCount -= tm.tmHeight;
					break;

				}
				LineCount++;
				LastMove = iMove + 1;
			}
			iMove++;//放在for里面我怕我搞混....放到这里就不会了
		}

		if (IsFounded)
		{
			//就在当前行！

			CaretY = yCount;
			IsFounded = FALSE;
			int LastLen, CurrLen;
			LastLen = CurrLen = 0;
			for (iMove = LastMove; iMove <= iMaxLen;)
			{

				if ((Text[iMove] == '\0') || (Text[iMove] == '\r' && Text[iMove + 1] == '\n') || (Text[iMove] == '\n'))
				{
					//没找到，在行末尾
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
					break;
				}

				LastLen = CurrLen;
				//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				int CharWidth;
				GetCharWidth32(ezWnd->hdc, Text[iMove], Text[iMove], &CharWidth);
				//CurrLen = size.cx;
				CurrLen += CharWidth;


				//得到旧位置和新位置的平均位置
				if (GET_X_LPARAM(lParam) <= (LastLen + CurrLen) / 2)
				{
					//插入符号在这个字符往前推一个,也就是在LastCurr的位置
					IsFounded = TRUE;
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
					break;

				}

				iMove++;//放在for里面我怕我搞混....放到这里就不会了
			}

			if (IsFounded)
			{
				CaretX = LastLen;
			}
			else
			{
				CaretX = CurrLen;
			}
		}
		else
		{
			//文档末尾
			CaretY = yCount;
		}

		ezWnd->ezParent->ezParent->Extend->iExtend[0] = CaretX;

		ezWnd->ezParent->ezParent->Extend->iExtend[1] = CaretY;

		EZHideCaret(ezWnd);
		EZSetCaretPos(ezWnd, ezWnd->ezParent->ezParent->Extend->iExtend[0], ezWnd->ezParent->ezParent->Extend->iExtend[1]);
		EZRepaint(ezWnd, NULL);
		EZShowCaret(ezWnd);
	}
	return 0;
	case EZWM_DRAW:
	{
		EZHideCaret(ezWnd);
		//开始绘制，循环检查，找到\r\n，或\n，掐行，输出。

		Text = ezWnd->ezParent->ezParent->Extend->Title;
		if (!Text)
		{
			return 0;
		}
		iMaxLen = ezWnd->ezParent->ezParent->Extend->TitleLen;
		LastMove = 0;
		xCount = yCount = 0;

		if (ezWnd->ezParent->ezParent->Extend->hFont)
		{
			SelectObject(wParam, ezWnd->ezParent->ezParent->Extend->hFont);
		}
		SetBkMode(wParam, TRANSPARENT);
		SetTextColor(wParam, ezWnd->ezParent->ezParent->Extend->ForeGroundColor);
		GetTextMetrics(wParam, &tm);
		for (iMove = 0; iMove <= iMaxLen;)
		{

			if (Text[iMove] == '\0')
			{
				//绘制当前行，并退出。
				TextOut(wParam, 0, yCount, Text + LastMove, iMove - LastMove);
				GetTextExtentPoint32(wParam, Text + LastMove, iMove - LastMove, &size);

				yCount += tm.tmHeight;
				//xCount = max(xCount, size.cx);



				break;
			}
			else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
			{
				//windows换行标记，绘制当前行，重新开始。
				TextOut(wParam, 0, yCount, Text + LastMove, iMove - LastMove);
				//GetTextExtentPoint32(wParam, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				//xCount = max(xCount, size.cx);


				LastMove = iMove + 2;
				iMove++;

			}
			else if (Text[iMove] == '\n')
			{
				//Linux换行标记，绘制当前行。
				TextOut(wParam, 0, yCount, Text + LastMove, iMove - LastMove);
				//GetTextExtentPoint32(wParam, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				//xCount = max(xCount, size.cx);


				LastMove = iMove + 1;
			}
			iMove++;//放在for里面我怕我搞混....放到这里就不会了
		}

	}
	EZShowCaret(ezWnd);
	//SetPixel(wParam, ezWnd->ezParent->ezParent->Extend->iExtend[0], ezWnd->ezParent->ezParent->Extend->iExtend[1], RGB(255, 0, 0));
	return 0;

	case EZWM_CHAR:
		EZHideCaret(ezWnd);
		if (wParam == '\b')
		{
			if (ezWnd->ezParent->ezParent->Extend->iExtend[2] == 0)
			{
				EZShowCaret(ezWnd);
				return 0;
			}
			lstrcpyn(TextBuffer, (TCHAR *)ezWnd->ezParent->ezParent->Extend->Title, ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1);

			lstrcpyn(TextBuffer + ezWnd->ezParent->ezParent->Extend->iExtend[2] - 1,
				(TCHAR *)(ezWnd->ezParent->ezParent->Extend->Title) + ezWnd->ezParent->ezParent->Extend->iExtend[2],
				ezWnd->ezParent->ezParent->Extend->TitleLen - ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1);
			EZSendMessage(ezWnd->ezParent->ezParent, EZWM_SETTEXT, TextBuffer, 0);
			EZSendMessage(ezWnd, EZWM_KEYDOWN, 37, 0);//模拟按键
			EZRepaint(ezWnd, 0);
			EZShowCaret(ezWnd);
			return 0;
		}
		if (wParam == '\r')
		{
			if (ezWnd->ezParent->ezParent->Extend->iExtend[3] != -1)
			{
				if (ezWnd->ezParent->ezParent->Extend->TitleLen + 2 > ezWnd->ezParent->ezParent->Extend->iExtend[3])
				{
					EZShowCaret(ezWnd);
					return 0;
				}
			}
			//换行符，插入\r\n
			//支持多行？
			if (CHK_ALT_STYLE(ezWnd->ezParent->ezParent->EZStyle, EZES_SINGLELINE))
			{
				EZSendMessage(ezWnd->ezParent->ezParent->ezParent, EZWM_COMMAND, 0, ezWnd->ezParent->ezParent);
				EZShowCaret(ezWnd);
				return 0;
			}
			lstrcpyn(TextBuffer, (TCHAR *)ezWnd->ezParent->ezParent->Extend->Title, ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1);

			TextBuffer[ezWnd->ezParent->ezParent->Extend->iExtend[2]] = wParam;

			lstrcpyn(TextBuffer + ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1,
				(TCHAR *)(ezWnd->ezParent->ezParent->Extend->Title) + ezWnd->ezParent->ezParent->Extend->iExtend[2],
				ezWnd->ezParent->ezParent->Extend->TitleLen - ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1);
			//ezWnd->ezParent->ezParent->Extend->iExtend[2]++;
			EZSendMessage(ezWnd->ezParent->ezParent, EZWM_SETTEXT, TextBuffer, 0);
			EZSendMessage(ezWnd, EZWM_KEYDOWN, 39, 0);//模拟按键
			EZRepaint(ezWnd, 0);

			wParam = '\n';//出去之后自动插入
		}

		if (ezWnd->ezParent->ezParent->Extend->iExtend[3] != -1)
		{
			if (ezWnd->ezParent->ezParent->Extend->TitleLen + 1 > ezWnd->ezParent->ezParent->Extend->iExtend[3])
			{
				EZShowCaret(ezWnd);
				return 0;
			}
		}

		lstrcpyn(TextBuffer, (TCHAR *)ezWnd->ezParent->ezParent->Extend->Title, ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1);

		TextBuffer[ezWnd->ezParent->ezParent->Extend->iExtend[2]] = wParam;

		lstrcpyn(TextBuffer + ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1,
			(TCHAR *)(ezWnd->ezParent->ezParent->Extend->Title) + ezWnd->ezParent->ezParent->Extend->iExtend[2],
			ezWnd->ezParent->ezParent->Extend->TitleLen - ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1);
		//ezWnd->ezParent->ezParent->Extend->iExtend[2]++;
		EZSendMessage(ezWnd->ezParent->ezParent, EZWM_SETTEXT, TextBuffer, 0);
		EZSendMessage(ezWnd, EZWM_KEYDOWN, 39, 0);//模拟按键
		EZRepaint(ezWnd, 0);
		EZShowCaret(ezWnd);
		return 0;
	case EZWM_KEYDOWN:


		Text = ezWnd->ezParent->ezParent->Extend->Title;
		iMaxLen = ezWnd->ezParent->ezParent->Extend->TitleLen;
		LastMove = 0;
		xCount = yCount = 0;
		if (ezWnd->ezParent->ezParent->Extend->hFont)
		{
			SelectObject(ezWnd->hdc, ezWnd->ezParent->ezParent->Extend->hFont);
		}

		GetTextMetrics(ezWnd->hdc, &tm);

		if (wParam == 37 || wParam == 39)
		{
			if (wParam == 37)
			{
				//左
				//看看前面是不到头了，或是 '\n' 或 "\r\n"
				if (ezWnd->ezParent->ezParent->Extend->iExtend[2] == 0)
				{
					//别动了，到头了，不需要任何操作
					return 0;
				}

				//是不是换行？
				if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2] - 1] == '\n')
				{
					//是哪种换行？
					if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2] - 2] == '\r')
					{
						ezWnd->ezParent->ezParent->Extend->iExtend[2]--;//额外-1
					}
				}
				//无论是不是换行，都要-1.
				ezWnd->ezParent->ezParent->Extend->iExtend[2]--;
			}
			else if (wParam == 39)
			{
				//右

				//看看后面是不是到尾了，或是'\n' 或 "\r\n"
				if (ezWnd->ezParent->ezParent->Extend->iExtend[2] == ezWnd->ezParent->ezParent->Extend->TitleLen)
				{
					//别动了，到尾了，不需要任何操作
					return 0;
				}
				//是不是换行？
				if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2]] == '\r')
				{
					if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1] == '\n')
					{
						ezWnd->ezParent->ezParent->Extend->iExtend[2]++;//额外+1
					}
				}
				ezWnd->ezParent->ezParent->Extend->iExtend[2]++;
			}

			for (iMove = 0; iMove <= iMaxLen;)
			{
				if (iMove == ezWnd->ezParent->ezParent->Extend->iExtend[2])
				{

					GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
					//yCount += size.cy;

					break;
				}
				if (Text[iMove] == '\0')
				{
					//绘制当前行，并退出。
					//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
					yCount += tm.tmHeight;


					break;
				}
				else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
				{
					//windows换行标记，绘制当前行，重新开始。
					//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
					yCount += tm.tmHeight;

					LastMove = iMove + 2;
					iMove++;

				}
				else if (Text[iMove] == '\n')
				{
					//Linux换行标记，绘制当前行。
					//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);

					LastMove = iMove + 1;
					yCount += tm.tmHeight;
				}
				iMove++;//放在for里面我怕我搞混....放到这里就不会了
			}

			//if (ezWnd->FocusState == 1)
			{
				ezWnd->ezParent->ezParent->Extend->iExtend[0] = size.cx;
				ezWnd->ezParent->ezParent->Extend->iExtend[1] = yCount;


				EZHideCaret(ezWnd);
				EZSetCaretPos(ezWnd, ezWnd->ezParent->ezParent->Extend->iExtend[0], ezWnd->ezParent->ezParent->Extend->iExtend[1]);

				EZRepaint(ezWnd, 0);
				EZShowCaret(ezWnd);
			}


		}
		else if (wParam == 38 || wParam == 40)
		{
			int iLineBeginCount;
			int iLineCross;
			iLineCross = 0;
			iLineBeginCount = ezWnd->ezParent->ezParent->Extend->iExtend[2];

			if (wParam == 38)
			{
				//有没有上一行？
				//往前递归，跨过一个换行符，到达第二个换行符

				//有种情况，那就是....这个就是换行符（现在在行尾。）需要我们手动检查并避免这种情况

				if (Text[iLineBeginCount] == '\n')
				{

					if (Text[iLineBeginCount - 1] == '\r')
					{
						iLineBeginCount--;
					}
					iLineBeginCount--;
				}

				for (; iLineBeginCount > 0; iLineBeginCount--)
				{
					if (Text[iLineBeginCount] == '\n')
					{
						if (iLineCross == 1)
						{
							//两个齐了！现在Text[iLineBeginCount]是 '\n'，所以要加一
							iLineBeginCount++;
							iLineCross++;
							break;
						}

						if (Text[iLineBeginCount - 1] == '\r')
						{
							iLineBeginCount--;
						}
						iLineCross++;
					}
				}
				if (iLineCross == 0)
				{
					//没有上一行
					return 0;
				}
				CaretY = ezWnd->ezParent->ezParent->Extend->iExtend[1] - tm.tmHeight;


			}
			else if (wParam == 40)
			{
				//有没有下一行？
				//往后递归，跨过一个换行符，到达第二行行首
				int LineCrossRec;
				for (; iLineBeginCount < iMaxLen; iLineBeginCount++)
				{
					if (Text[iLineBeginCount] == '\n')
					{
						iLineBeginCount++;
						iLineCross++;
						break;

					}
					else if ((Text[iLineBeginCount] == '\r') && (Text[iLineBeginCount + 1] == '\n'))
					{

						iLineBeginCount += 2;
						iLineCross++;
						break;
					}
				}
				if (iLineCross == 0)
				{
					//没有下一行
					return 0;
				}
				CaretY = ezWnd->ezParent->ezParent->Extend->iExtend[1] + tm.tmHeight;

			}

			//在新行中，找到与现在位置最近的位置。

			int iFindCount;

			int LastLen, CurrLen;
			LastLen = CurrLen = 0;




			BOOL IsFounded;
			IsFounded = FALSE;

			for (iMove = iLineBeginCount; iMove <= iMaxLen;)
			{

				LastLen = CurrLen;
				GetTextExtentPoint32(ezWnd->hdc, Text + iLineBeginCount, iMove - iLineBeginCount, &size);
				CurrLen = size.cx;

				//得到旧位置和新位置的平均位置
				if (ezWnd->ezParent->ezParent->Extend->iExtend[0] <= (LastLen + CurrLen) / 2)
				{
					//插入符号在这个字符往前推一个,也就是在LastCurr的位置
					IsFounded = TRUE;
					//有一种情况是特殊的，那就是行首。在行首，两个值都为0.这样的话，iMove不应-1
					if (iMove == iLineBeginCount)
					{
						ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
						break;
					}
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove - 1;
					break;

				}

				if ((Text[iMove] == '\0') || (Text[iMove] == '\r' && Text[iMove + 1] == '\n') || (Text[iMove] == '\n'))
				{
					//没找到，在行末尾
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
					break;
				}


				iMove++;//放在for里面我怕我搞混....放到这里就不会了
			}

			GetTextExtentPoint32(ezWnd->hdc, Text + iLineBeginCount, iMove - iLineBeginCount, &size);
			CurrLen = size.cx;
			if (IsFounded)
			{
				CaretX = LastLen;
			}
			else
			{
				CaretX = CurrLen;
			}





			ezWnd->ezParent->ezParent->Extend->iExtend[0] = CaretX;

			ezWnd->ezParent->ezParent->Extend->iExtend[1] = CaretY;

			if (ezWnd->FocusState == 1)
			{
				//EZHideCaret(ezWnd);
				EZSetCaretPos(ezWnd, ezWnd->ezParent->ezParent->Extend->iExtend[0], ezWnd->ezParent->ezParent->Extend->iExtend[1]);
				//EZShowCaret(ezWnd);
			}
			EZRepaint(ezWnd, NULL);




		}


		return 0;

	case EZWM_SETFOCUS:

		if (ezWnd->ezParent->ezParent->Extend->hFont)
		{
			SelectObject(ezWnd->hdc, ezWnd->ezParent->ezParent->Extend->hFont);
		}

		GetTextMetrics(ezWnd->hdc, &tm);

		EZCreateCaret(ezWnd, NULL, 2, tm.tmHeight);

		EZShowCaret(ezWnd);
		return 0;

	case EZWM_KILLFOCUS:
		if (CHK_ALT_STYLE(ezWnd->ezParent->ezParent->EZStyle, EZES_SINGLELINE))
		{
			EZSendMessage(ezWnd->ezParent->ezParent->ezParent, EZWM_COMMAND, 0, ezWnd->ezParent->ezParent);
		}
		EZHideCaret(ezWnd);
		EZDestroyCaret();
		EZRepaint(ezWnd, NULL);
		return 0;

	}

}



