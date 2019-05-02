
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *

*                EasyWindow.h

*                EasyWindow ��Դ�ļ� �汾  3.0   Copyright (c) 2017 y.h. All rights reserved.

*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */


//*********************************************************************************************************
//                ͷ�ļ���Ԥ����ָ��
//*********************************************************************************************************


#pragma once

#pragma region ͷ�ļ�

#include<Windows.h>
#include<windowsx.h>
#include<math.h>
#include<strsafe.h>

#pragma endregion


#pragma region ���ӿ�

#pragma comment(lib,"msimg32.lib")

#pragma endregion

//*********************************************************************************************************
//                �����궨��
//*********************************************************************************************************


#pragma region EasyWindow��Ϣ����
//�����Ƕ�EasyWindows��Ϣ�Ķ���

//������Ϣ
#define EZWM_CREATE 1
#define EZWM_DESTROY 2
#define EZWM_SIZE 3
#define EZWM_TIMER 4

#define EZWM_ENABLE 5
#define EZWM_DISABLE 6

#define EZWM_SETFOCUS 7
#define EZWM_KILLFOCUS 8

#define EZWM_COLSE 9


//�����й���Ϣ
#define EZWM_DRAW 101//���ƣ���͸��
#define EZWM_TRANSDRAW 102//͸�����ƣ��ôλ��ƽ���͸����ʽ���ǡ�

//�����Ϣ
#define EZWM_LBUTTONDOWN 201
#define EZWM_LBUTTONUP 202
#define EZWM_RBUTTONDOWN 203
#define EZWM_RBUTTONUP 204
#define EZWM_MOUSEMOVE 205//�����Ϣ���WPARAMΪ1���������͵�EZ�����ڣ�˵����Win���ڳ�ȥ��
#define EZWM_MOUSECOME 206
#define EZWM_MOUSELEAVE 207

#define EZWM_NCHITTEST 208//�������Ҿ������...Ҳ���Է�����ꣿ��Ȼ�ⲻ��һ����׼�������Ϣ



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

//������Ϣ
#define EZWM_CHAR 301
#define EZWM_KEYDOWN 302
#define EZWM_KEYUP 303

//��������Ϣ
#define EZWM_VSCROLL 401
#define EZWM_HSCROLL 402


//����������Ϣ

#define EZWM_SETCOLOR 501//wParam�Ǳ�����ɫ��lParam��ǰ����ɫ������Ϣ�������ػ档
#define EZWM_SETFONT 502//�������壬wParam��lParam��ѡһ�����������ø÷��Ĭ�����塣wParam��HFONT���û������ͷţ���lParam��LOGFONT��EZWnd�����ͷţ���wParam����
#define EZWM_SETTEXT 503//�����ı���wParam���ı���lParam�ǳ��ȣ�Ϊ0���Զ���ȡ����
#define EZWM_SETTEXTALIGN 504//�ı�����ѡ�wParam���ݲ�������ʱ����ΪDrawText�Ļ��Ʋ��������ڽ������Ľ�
#define EZWM_SETMAXTEXT 505//��������ı����ȣ�wParam����󳤶�,-1û�����ơ��Ѿ������˲�����д���

#define EZWM_SETSCROLLRANGE 506//���ù�������Χ��wParam����������Χ��
#define EZWM_SETSCROLLPOS 507//���ù�����λ�ã�wParam lParam�������¹���λ�á�wParam < lParam <= Max 



//������Ϣ
#define EZWM_COMMAND 601//�������岻�����ˡ���Windows��һЩ��lParam�Ǿ����wParam��֪ͨ�ĸ�����Ϣ��
#define EZWM_SCROLLPOSCHANGE 602//������λ�ö��ˣ�wParam ���Ϲ���λ�ã�lParam�Ǿ����


//֪ͨ����Ϣ
#define EZWM_USER_NOTIFY 701//����ʹ�ã��Լ�Ū�����֪ͨ��ʽ��OK
#define EZWM_WINWND_CHECKSTATE 702//Ҫ��Win���ڼ����ʾ״̬��



//��ȡ��Ϣ��Ϣ
#define EZWM_GETTEXT 801//����ı�,wParam��������lParam������



//������Ϣ
#define SEZWM_COPYDC 2001//���洢DC���Ƶ������ڡ�
#define SEZWM_REDRAW 2002//�ػ浽�ڴ�DC
#define SEZWM_MOUSECOME 2003
#define SEZWM_MOUSELEAVE 2004//�����뿪���㴰�ڣ��Ӵ��������м�顣,wP��Ҫ�ų����Ĵ���

#define SEZWM_KILLFOCUS 2005//�н���Ĵ���ʧȥ���㡣wP�ų���顣


// #define SEZWM_CAPTURE 2005//��һ���������벶�������Ѿ������˵ĸϽ��ŵ���

#pragma endregion




#pragma region EZStyle��ʽ����

#define MKDW(a,b,c,d) 0b ## a ## b ## c ## d

#define CHK_STYLE(Style,ChkStyle) (Style ^ ChkStyle)> 0 ? FALSE : TRUE
#define CHK_ALT_STYLE(Style,AltStyle) (((Style) & (AltStyle)) > 0 ? (TRUE) : (FALSE))

//*****��ѡ������ - ����

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
#define EZS_MINIMIZEBOX    MKDW(00000000,00000000,00001000,00000000)//��С����ť
#define EZS_NO_MINIMIZEBOX MKDW(00000000,00000000,00000000,00000000)

//                                                  -|-
#define EZS_MAXIMIZEBOX    MKDW(00000000,00000000,00010000,00000000)//��󻯰�ť
#define EZS_NO_MAXIMIZEBOX MKDW(00000000,00000000,00000000,00000000)

//                                                 -|-
#define EZS_CLOSEBOX       MKDW(00000000,00000000,00100000,00000000)//�رհ�ť
#define EZS_NO_CLOSEBOX    MKDW(00000000,00000000,00000000,00000000)

//                                                -|-
#define EZS_VSCROLL        MKDW(00000000,00000000,01000000,00000000)//��ֱ
#define EZS_NO_VSCROLL     MKDW(00000000,00000000,00000000,00000000)

//                                               -|-
#define EZS_HSCROLL        MKDW(00000000,00000000,10000000,00000000)//ˮƽ
#define EZS_NO_HSCROLL     MKDW(00000000,00000000,00000000,00000000)


//*****������Ҫ���� - ����
//�Ӵ���ƪ
#define EZS_STATIC         MKDW(00000000,00000000,00000000,00000001)
#define EZS_BUTTON         MKDW(00000000,00000000,00000000,00000010)
//�������ɲ��Ǵ��й����ؼ��Ĵ��ڣ����������ǹ����ؼ���
#define EZS_CHILD_VSCROLL  MKDW(00000000,00000000,00000000,00000011)//��ֱ
#define EZS_CHILD_HSCROLL  MKDW(00000000,00000000,00000000,00000100)//ˮƽ


#define EZS_EDIT           MKDW(00000000,00000000,00000000,00000101)//�༭��



//������ƪ


//*****����ϸ������ - ����
//***�Ӵ���ƪ
//��ťƪ
#define EZBS_PUSHBUTTON    MKDW(00000000,00000000,00000000,00000000)//Ĭ�ϣ�ʲô������������ͨ��ť
#define EZBS_RADIOBUTTON   MKDW(00000001,00000000,00000000,00000000)

//�༭��ƪ
//                             -|-
#define EZES_SINGLELINE    MKDW(10000000,00000000,00000000,00000000)
//                             -|-
#define EZES_MULTILINE     MKDW(00000000,00000000,00000000,00000000)//Ĭ��

#pragma endregion




#pragma region �����궨��

//���������궨��
#define CLOSE_WINDOW 0//��ӦEZWM_CLOSEʱ�����������رմ���
#define DO_NOT_CLOSE 1//��ӦEZWM_CLOSEʱ����������رմ���

//�ڲ��ı���󳤶�
#define MAX_TEXT 16384

#define GET_EXTEND(ezWnd,Extend) (((pEZSE)(ezWnd))->Extend)

#pragma endregion


#pragma region EasyWindow��������

#define EZWindowClass TEXT("EasyWindowClass")

#pragma endregion

//*******************************************************************************************
//                �ṹ������
//*******************************************************************************************


typedef struct tagEZWND * EZWND;//��EZWINDOW�ṹ��Ķ��塣EZWND��ָ��ýṹ��ָ�롣



#pragma region Extend (����Style)�ṹ�嶨��
typedef struct tagExtendStyle
{
	PBYTE Title;//ÿ�ζ�̬���룬��಻�ó��� MAX_TEXT
	int TitleLen;

	//UI���
	COLORREF BackGroundColor;
	COLORREF ForeGroundColor;

	HFONT hFont;

	DWORD TextAlign;
	int IsFontUserControl;//����˭�����ͷţ���-1 ֮ǰû���壬0 �û����ƣ�1 EZWnd����2 Ĭ�����壩


						  //������
	int MouseHold;//�����ж�����Ƿ��ţ����簴ť�ؼ��ͻ��õõ�����Ȼ������¼��갴��ʱ�䳤��Ҳû����

				  //����ʹ����չ
	int iExtend[4];//4��������չ ����������ɸ��ݿؼ�����ʹ�á�
	EZWND hExtend[8];//8��EZWND��չ ����������ɸ��ݿؼ�����ʹ�á�
	void * vExtend[4];//4��ָ����չ ����������ɸ��ݿؼ�����ʹ�á�

}EZSE, *pEZSE;
#pragma endregion


typedef INT(*EZWNDPROC)(EZWND, int, WPARAM, LPARAM);//�ص���������

#define MAX_EZ_TIMER 64//64����ʱ��


#pragma region EZWND���㴰����չ
typedef struct tagezTopWindowExtend
{
	EZWND FocusWindow;//ӵ�����뽹��Ĵ���
	EZWND CptMouseWindow;//����������
	EZWND MouseOnWnd;//����������


	HDC hdcTop;//���㴰�������ڴ�ʹ�ã��������ڶ��ԣ���ֻ��һ���յľ����

			   //	int TimerNum;//��ǰʹ���˵ļ�ʱ������

	struct ezTimer
	{
		int WinTimerID;

		EZWND ezWnd;
	} Timer[MAX_EZ_TIMER];

}TopWndExt, *pTWE;
#pragma endregion


#pragma region EZWND�ṹ�嶨��


#define WND_TIMER_NUM 8
typedef struct tagEZWND
{
	//�йش�����Ϣ
	int x;
	int y;
	int Width;
	int Height;

	//�����������������Թ����ͻ����ڵ��Ӵ��ڣ��Լ�����������ꡣ��ע�⣬���ڱ������ݲ���������������������
	int ScrollX;
	int ScrollY;

	//�йػ���״̬****************************
	BYTE Transparent;//͸���ȣ�0����ȫ͸����255��͸��

					 //�йش���״̬****************************
	int FocusState;//���뽹��״̬��0-�޽��㡣1-�н��� 
	int MouseMsgRecv;//�����Ϣ��������� 1���������ܣ�2��͸��
	int ShowState;//��ʾ״̬��������޹أ�1��������ʾ��2��͸��

				  //�й����****************************
	BOOL MouseOn;//����ڸô����ϡ�

				 //�йػ���****************************
	HDC hdc;//һ�����ƿռ䡣ʼ�մ��ڣ�ֱ�����ڱ����١����ڻ��ƾͻ�����������档
	HDC hdcCopy;//���ڼ��ٻ��ƣ���һ�����ڿ���ֱ�Ӹ��Ƶ�DC��

	BOOL Update;//��������0Ϊ������£�1Ϊ�����˸ı䣬��Ҫ���¡�

				//�йع�������****************************
	EZWNDPROC ezWndProc;//���ڹ���
	EZWND ezParent;//EZ������
	EZWND ezRootParent;//EZ���ȴ���

	BOOL IsTopWindow;//����ָʾ�Ƿ��Ƕ���EZ���ڡ�
	HWND hParent;//����Win����.

	BOOL IsWinWnd;//�Ƿ����ӵ���һ��Win�Ӵ���
	HWND hChild;//��Win����
	WNDPROC WinChildProc;

	EZWND FirstChild;//��һ���Ӵ���
	EZWND LastEZWnd;//����������ڣ����е���һ������
	EZWND NextEZWnd;//����������ڣ����е���һ������


					//���㴰��ר��
	pTWE TopWndExtend;


	//��չ****************************

	int ezID;//�û���������ʹ�ã����ڱ�ʶ����ID��
	int TimerID[WND_TIMER_NUM];//8��Ӧ�ù����ˣ���ͨ���ڿ�������ʹ�á�������ʽ�Ĵ��ڿ��ܻ��������Windows��ʱ��ID
	pEZSE Extend;//��չָ�롣���EZ�������Դ��ģ���ôEZWindow����ʹ��������������Ǽ�����������Ǻ��� EZSTYLE �Ĵ��ڣ����ָ��ᱻEZWindowʹ��

	DWORD EZStyle;//������ʽ��
	BOOL IsStyleWindow;//�Ƿ��Ǵ�����ʽ�Ĵ���

#pragma region  ������ʽ��ע
					   /*������ʽע��

					   EZStyle ������Ϊ�� DWORD Ҳ���� 4���ֽڣ�32λ��

					   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

					   ������ÿ���ֶεĺ��壺

					   ���һ���ֽ�    ��256�֣���ʾ������Ҫ���ͣ����磬�ǲ��ǰ�ť���ǲ��Ǳ༭��ȡ�
					   �����ڶ������ֽڣ�16λ����ʾ���ڵĿ�ѡ�����ԣ����細���Ƿ���б߿�
					   �������ĸ��ֽ�  ��256�֣���ʾ����Ҫ�����´��ڵ�ϸ�����ԣ����簴ť�����Ƿ��ǵ�ѡ��ť��
					   */
#pragma endregion
}EZWINDOW;

#pragma endregion

//*******************************************************************************************
//                ��������
//*******************************************************************************************

#pragma region EZWindow��������

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



//�ⲿ��ʽ
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


#pragma region ������������

static HDC GetMemDC(HDC hdc, int cx, int cy);

static BOOL DeleteMemDC(HDC hdc);

#pragma endregion

//*******************************************************************************************
//                �����궨��
//*******************************************************************************************

#pragma region EZWindow�����궨��

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
//                ����ʵ��
//*******************************************************************************************

//��ʼ������
BOOL InitEZWindow()
{
	WNDCLASS wndclass;
	//ע�ᴰ����
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



//�������ں���
EZWND CreateEZParentWindowEx(DWORD EZStyle, int x, int y, int Width, int Height, DWORD WinStyle, EZWNDPROC ezWndProc, HMENU hMenu, HWND hParent)
{
	HWND hwndParent;//����Windows����ĸ�����
	EZWND ezwndParent;//���Ǻ�Win���ڵȴ��EZ���ڣ����ظ��û����ô��ڴݻ�ʱͬʱ�ݻ�Win����


	ezwndParent = (EZWND)malloc(sizeof(EZWINDOW));


	//Create tht EZ Window With out Using "CreateEZWindow"
	if (!ezwndParent)//����ڴ�
	{
		return (EZWND)0;
	}

	ezwndParent->TopWndExtend = (pTWE)malloc(sizeof(TopWndExt));

	if (!ezwndParent->TopWndExtend)//����ڴ�
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
	ezwndParent->ezParent = NULL;//û�У��ա�
	ezwndParent->ezRootParent = ezwndParent;//���Լ�

	ezwndParent->TopWndExtend->CptMouseWindow = NULL;//û�еģ�2333
	ezwndParent->TopWndExtend->FocusWindow = NULL;
	ezwndParent->TopWndExtend->MouseOnWnd = NULL;


	ezwndParent->IsTopWindow = TRUE;//�ǵģ��Ƕ��㴰�ڡ�

	ezwndParent->FocusState = FALSE;

	ezwndParent->MouseMsgRecv = 1;

	ezwndParent->ShowState = 1;

	ezwndParent->MouseOn = FALSE;

	ezwndParent->Update = FALSE;//�տ�ʼ���϶�û�и��¹���

	ezwndParent->Transparent = 255;//��͸��

	ezwndParent->ezWndProc = ezWndProc;

	ezwndParent->TopWndExtend->FocusWindow = NULL;


	ezwndParent->IsWinWnd = 0;
	ezwndParent->hChild = 0;


	ezwndParent->IsStyleWindow = FALSE;

	//�󲿷����ݶ���ʼ������ˡ�ezwndParent����Ϊ�����ύ��WM_CREATE��Ϣ�������ڼ佫���ָ������Ϊ������չ
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

	if (!(ezWnd = (EZWND)malloc(sizeof(EZWINDOW))))//����������ڴ�
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
		ezWnd->Extend = NULL;//��Ұָ��
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
	ezWnd->IsTopWindow = FALSE;//������


	ezWnd->FocusState = 0;
	ezWnd->MouseMsgRecv = 1;
	ezWnd->ShowState = 1;

	ezWnd->MouseOn = FALSE;

	ezWnd->Update = 1;//�տ�ʼ���϶�û�и��¹���

	ezWnd->Transparent = 255;//��͸��

	ezWnd->ezParent = ezParent;
	ezWnd->ezRootParent = ezParent->ezRootParent;
	ezWnd->ezWndProc = ezWndProc;

	//��EZ���������׷������µ��Ӵ��ڡ�
	EZAddChild(ezParent, ezWnd);

	fhdc = GetDC(hParent = ezParent->hParent);
	ezWnd->hdc = GetMemDC(fhdc, Width, Height);
	ezWnd->hdcCopy = GetMemDC(fhdc, Width, Height);
	ReleaseDC(hParent, fhdc);


	ezWnd->IsWinWnd = 0;
	ezWnd->hChild = 0;


	ezWnd->IsStyleWindow = FALSE;

	EZSendMessage(ezWnd, EZWM_CREATE, 0, 0);//���ʹ�����Ϣ

											//ֻ����һ���ƶ���Ϣ
	EZSendMessage(ezWnd, EZWM_SIZE, (WPARAM)NULL, (LPARAM)MAKELPARAM(Width, Height));
	return ezWnd;

}

BOOL EZAddChild(EZWND ezParent, EZWND ezChild)
{
	EZWND ezChildLast;
	//���Ӵ���׷����ezParent���Ӵ����������
	if (!IsEZWindow(ezParent->FirstChild))
	{
		ezParent->FirstChild = ezChild;
		return TRUE;
	}

	//�Ӵ��������һ����Ϊ��
	ezChildLast = ezParent->FirstChild;

	while (1)//ѭ�����������
	{
		if (!IsEZWindow(ezChildLast->NextEZWnd))
		{
			ezChild->LastEZWnd = ezChildLast;
			ezChildLast->NextEZWnd = ezChild;
			return TRUE;
		}
		ezChildLast = ezChildLast->NextEZWnd;//�����ƶ�
	}

}


EZWND CreateEZStyleWindow(EZWND ezParent, TCHAR Title[], DWORD EZStyle, int x, int y, int Width, int Height)
{
	EZWND ezWnd;
	ezWnd = 0;
	//�������ԣ�����Ƿ��ͻ��Ȼ�󴴽����ڡ�
	if (CHK_ALT_STYLE(EZStyle, EZS_CHILD))
	{
		//�Ӵ���
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
		//������

	}


	((pEZSE)ezWnd->Extend)->hFont = NULL;
	ezWnd->Extend->Title = 0;
	EZSendMessage(ezWnd, EZWM_SETTEXT, Title, lstrlen(Title));


	((pEZSE)ezWnd->Extend)->BackGroundColor = RGB(255, 255, 255);

	((pEZSE)ezWnd->Extend)->ForeGroundColor = RGB(0, 0, 0);

	((pEZSE)ezWnd->Extend)->MouseHold = FALSE;


	((pEZSE)ezWnd->Extend)->IsFontUserControl = -1;


	//���������һ�飬��ֹ֮ǰ����Ұ���ݻ������㡣
	ezWnd->IsStyleWindow = TRUE;
	ezWnd->EZStyle = EZStyle;

	return ezWnd;
}



//���ٴ��ں���
BOOL DestroyEZWindow(EZWND ezWnd)
{
	if (ezWnd->IsTopWindow)
	{
		DestroyWindow(ezWnd->hParent);//������ˣ����ٻ���������ɡ���Ҳûʲô��˵�ģ����ù�������������ˡ�
		return TRUE;
	}

	//�ȱ�����Ϣ�����ƣ������������ﴰ��
	if (IsEZWindow(ezWnd->FirstChild))
	{
		DestroyEZWindowWithNext(ezWnd->FirstChild);
	}


	//�����Լ�������
	EZSendMessage(ezWnd, EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//����������Ϣ

	DeleteMemDC(ezWnd->hdc);//����DC

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
	//ά��һ������
	if (ezWnd->LastEZWnd)
	{
		//����һ��
		if (ezWnd->NextEZWnd)
		{
			//������һ����
			ezWnd->LastEZWnd->NextEZWnd = ezWnd->NextEZWnd;
			ezWnd->NextEZWnd->LastEZWnd = ezWnd->LastEZWnd;
			//���Ӻÿ�
		}
		else
		{
			//��һ���ǿյ�
			ezWnd->LastEZWnd->NextEZWnd = NULL;
		}
	}
	else
	{
		//û����һ�������Ƕ��㴰�ڣ����ǵ�һ����
		if (!(ezWnd->IsTopWindow))
		{
			//���Ƕ��㰡������ĳ�����ĵ�һ��
			if (ezWnd->NextEZWnd)
			{
				//������һ��
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

	//�ع���׼�������д���
	if (IsEZWindow(ezWnd->NextEZWnd))
	{
		ezChildLast = ezWnd->NextEZWnd;

		//ѭ�����������
		while (1)
		{
			if (!IsEZWindow(ezChildLast->NextEZWnd))
			{
				break;//���������
			}
			ezChildLast = ezChildLast->NextEZWnd;
		}


		//��ѭ������������ǰ��һ�߹�һ��ɾ��

		//Ϊ�����ݣ��Ȼع���Ȼ��ͨ�����µ�ָ���һ�ȥ��ɾ��
		while (IsEZWindow(ezChildLast->LastEZWnd))//��û��ͷ
		{

			ezChildLast = ezChildLast->LastEZWnd;//�ع�

												 //��ʱ��ezChildLast->NextEZWnd�������һ����DestroyEZWindow��ɾ�˸ô��ں�������ڵ��Ӵ��ڡ�
			DestroyEZWindow(ezChildLast->NextEZWnd);//ɾ��
		}
		//������ͷ�ˣ�DestroyEZWindow��ɾ�˸ô��ں�������ڵ��Ӵ��ڡ�
		DestroyEZWindow(ezChildLast);
		return TRUE;

	}
	else
	{//��������һ�����д��ڡ�
		DestroyEZWindow(ezWnd);//ɾ��
	}
	return TRUE;

}



//�������ú���
BOOL MoveEZWindow(EZWND ezWnd, int x, int y, int Width, int Height, BOOL repaint)
{
	HDC fhdc;//��ʱDC

	ezWnd->x = x;
	ezWnd->y = y;
	ezWnd->Width = Width;
	ezWnd->Height = Height;
	if (ezWnd->IsTopWindow)
	{
		MoveWindow(ezWnd->hParent, x, y, Width, Height, FALSE);
	}


	//��ʱ����DC��Ȼ�����»��һ����
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

BOOL SetEZWndTransparent(EZWND ezWnd, int Transparent)//����EZ����͸����
{
	ezWnd->Transparent = Transparent;
	return TRUE;
}

BOOL EZCaptureMouse(EZWND ezWnd)
{
	//�򶥲㸸�����ύҪ�������󡱵Ĵ��ڵľ����
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
	//�򶥲㸸�����ύ�ͷš��������롣

	ReleaseCapture();

	//��������䲻��Ҫ����Window���ڴ���WM_CAPTURECHANGE֮���Ѿ��������
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





//�봰�ڻ����йصĺ���
BOOL EZRedraw(EZWND ezWnd)//�ػ浽�ڴ�dc,�����¡�
{
	//���������Ҫ��ȷ����Ҫ�ػ�ķ�Χ

	/*
	�������󴰿���ϵ��
	�κκ͸ô����з�Χ�ظ��Ĵ���
	ȫ�������裡Ҫ���ػ棡������

	���ԣ�����Ҫ�����д��ڣ������Ӵ��ڹ㲥��Ϣ���κ����ظ��Ĵ��ڣ�ȫ����Ҫ�ػ浽�ڴ�
	Ȼ����е��Ӵ���

	����Ҫ�ػ浽Windows�����ڡ�

	*/

	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}
	RECT rect;

	int Countx = 0, County = 0;

	EZWND WndNow = ezWnd;


	//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
	while (!WndNow->IsTopWindow)
	{
		//�����ƣ�ֱ��������
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
			//�������ԣ��ȴ����Լ���
			RECT RectDst, RectAns;

			{
				RectDst.left = cx + LastChild->x + LastChild->ezParent->ScrollX;
				RectDst.right = RectDst.left + LastChild->Width;
				RectDst.top = cy + LastChild->y + LastChild->ezParent->ScrollY;
				RectDst.bottom = RectDst.top + LastChild->Height;
			}

			if (!((IntersectRect(&RectAns, &RectSrc, &RectDst) == 0) || (LastChild->ShowState == 2)))
				//��ʱ����
				//if (LastChild->ShowState == 1)
			{

				//HRGN hRgn, OldRgn;


				BroadcastProc(LastChild, SEZWM_REDRAW, wp, lp);//�����Լ�

				//hRgn = CreateRectRgn(
				//	RectAns.left - (cx + LastChild->x + LastChild->ezParent->ScrollX),
				//	RectAns.top - (cy + LastChild->y + LastChild->ezParent->ScrollY),
				//	RectAns.right - (cx + LastChild->x + LastChild->ezParent->ScrollX),
				//	RectAns.bottom - (cy + LastChild->y + LastChild->ezParent->ScrollY));

				//OldRgn = SelectObject(LastChild->hdc, hRgn);

				RedrawBroadcast(LastChild, wp, lp, cx + LastChild->x + LastChild->ezParent->ScrollX, cy + LastChild->y + LastChild->ezParent->ScrollY, RectSrc);//���Լ����Ӵ��ڷ��͸���Ϣ

				/*DeleteObject(SelectObject(LastChild->hdc, OldRgn));*/

				BroadcastProc(LastChild, SEZWM_COPYDC, wp, lp);//�����Լ�
			}


			//���¹�

		}

	}
	return TRUE;
}

BOOL EZUpdate(EZWND ezWnd, HDC hdc)//��DC���µ����壬���ػ档�ڶ���������DC���粻�ṩ���������Զ���ȡ��
{
	//�ҵ���ġ����ڡ���

	int Countx = 0, County = 0;

	EZWND WndNow = ezWnd;

	if (!IsEZWindow(ezWnd))
	{
		return FALSE;
	}

	//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
	while (!WndNow->IsTopWindow)
	{
		//�����ƣ�ֱ��������
		Countx += WndNow->x + WndNow->ScrollX;
		County += WndNow->y + WndNow->ScrollY;
		WndNow = WndNow->ezParent;
	}

	////EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_COPYDC, (WPARAM)NULL, (LPARAM)NULL);


	if (!hdc)//ûDC
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


	//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
	while (!WndNow->IsTopWindow)
	{
		//�����ƣ�ֱ�������ڡ�˳������û�и����ڲ���ʾ��
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
	else//ûDC
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






////�봰�ڻ����йصĺ���
//BOOL EZRedraw(EZWND ezWnd)//�ػ浽�ڴ�dc,�����¡�
//{
//	//���������Ҫ��ȷ����Ҫ�ػ�ķ�Χ
//
//	/*
//	�������󴰿���ϵ��
//	�κκ͸ô����з�Χ�ظ��Ĵ���
//	ȫ�������裡Ҫ���ػ棡������
//
//	���ԣ�����Ҫ�����д��ڣ������Ӵ��ڹ㲥��Ϣ���κ����ظ��Ĵ��ڣ�ȫ����Ҫ�ػ浽�ڴ�
//	Ȼ����е��Ӵ���
//
//	����Ҫ�ػ浽Windows�����ڡ�
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
//	//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
//	while (!WndNow->IsTopWindow)
//	{
//		//�����ƣ�ֱ��������
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
//			//�������ԣ��ȴ����Լ���
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
//				BroadcastProc(LastChild, SEZWM_REDRAW, wp, lp);//�����Լ�
//
//				RedrawBroadcast(LastChild, wp, lp, cx + LastChild->x + LastChild->ScrollX, cy + LastChild->y + LastChild->ScrollY, RectSrc);//���Լ����Ӵ��ڷ��͸���Ϣ
//
//				BroadcastProc(LastChild, SEZWM_COPYDC, wp, lp);//�����Լ�
//			}
//
//			if (!IsEZWindow(LastChild->NextEZWnd))//û����һ��
//			{
//				break;//û����һ����
//			}
//
//			LastChild = LastChild->NextEZWnd;//���¹�
//
//		}
//
//	}
//	return TRUE;
//}
//
//BOOL EZUpdate(EZWND ezWnd, HDC hdc)//��DC���µ����壬���ػ档�ڶ���������DC���粻�ṩ���������Զ���ȡ��
//{
//	//�ҵ���ġ����ڡ���
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
//	//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
//	while (!WndNow->IsTopWindow)
//	{
//		//�����ƣ�ֱ��������
//		Countx += WndNow->x + WndNow->ScrollX;
//		County += WndNow->y + WndNow->ScrollY;
//		WndNow = WndNow->ezParent;
//	}
//
//	////EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_COPYDC, (WPARAM)NULL, (LPARAM)NULL);
//
//	/*
//	if (!hdc)//ûDC
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
//	if (!hdc)//ûDC
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


//��ʱ������
int SetEZTimer(EZWND ezWnd, int iTimeSpace)
{
	//�����ʱ�����ڶ������ڵļ�ʱ�����ҵ�һ����λ��д����Ϣ�����ط����ID��
	int i;
	for (i = 0; i < MAX_EZ_TIMER; i++)
	{
		if (ezWnd->ezRootParent->TopWndExtend->Timer[i].ezWnd == NULL)
		{
			//д����Ϣ
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
	//ɾ����Ϣ
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




//��꺯��
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

	//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
	while (!WndNow->IsTopWindow)
	{
		//�����ƣ�ֱ��������
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



//�ڲ�����
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
		ezWnd->hParent = hwnd;//����Win������

							  //HDC fhdc;
							  //��ʵ����Ӧ�����������.���ǣ�hdc�������ڲ��������𣿣����ɴ�����Ǹ��ɣ�ʡ�ڴ�

		hdc = GetDC(hwnd);
		ezWnd->hdc = GetMemDC(hdc, ezWnd->Width, ezWnd->Height);
		ezWnd->hdcCopy = GetMemDC(hdc, ezWnd->Width, ezWnd->Height);
		ezWnd->TopWndExtend->hdcTop = GetMemDC(hdc, ezWnd->Width, ezWnd->Height);

		ReleaseDC(hwnd, hdc);

		EZSendMessage(ezWnd, EZWM_CREATE, 0, 0);//���ʹ�����Ϣ

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
		//��ʵ����Ӧ�����������.���ǣ�hdc�������ڲ��������𣿣����ɴ�����Ǹ��ɣ�ʡ�ڴ�

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
			//������������Ϲ����ҵ�������ڵ�����
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
			while (!WndNow->IsTopWindow)
			{
				//�����ƣ�ֱ��������
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
			//������������Ϲ����ҵ�������ڵ�����
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
			while (!WndNow->IsTopWindow)
			{
				//�����ƣ�ֱ��������
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
			//������������Ϲ����ҵ�������ڵ�����
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
			while (!WndNow->IsTopWindow)
			{
				//�����ƣ�ֱ��������
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
			//������������Ϲ����ҵ�������ڵ�����
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
			while (!WndNow->IsTopWindow)
			{
				//�����ƣ�ֱ��������
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
		//������������ȥ��
		if (ezWnd->MouseOn == FALSE)
		{
			//�ոս���

			//���Խ��м���ˡ�
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			tme.hwndTrack = hwnd;
			TrackMouseEvent(&tme);
		}
		if (IsEZWindow(ezWnd->TopWndExtend->CptMouseWindow))
		{
			//������������Ϲ����ҵ�������ڵ�����
			EZWND WndNow = ezWnd->TopWndExtend->CptMouseWindow;

			int Countx = 0, County = 0;
			//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
			while (!WndNow->IsTopWindow)
			{
				//�����ƣ�ֱ��������
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
		//����������У���Ϊ������������ظ�����ReleaseCapture.

		//���������������������ݿ�������һ�ľͿ�����


		if (ezWnd->TopWndExtend->CptMouseWindow)
		{
			EZSendMessage(ezWnd->TopWndExtend->CptMouseWindow, EZWM_RELEASEMOUSE, 0, 0);
			ezWnd->TopWndExtend->CptMouseWindow = NULL;

		}


		return 0;
	}

	case WM_MOUSELEAVE:
	{

		//ѽ����������~~~   �㲥һ�£���ÿ���Ӵ��ڿ����ǲ��Ǵ��Լ��������ȥ�ġ�
		//�ȼ���Լ���
		if (ezWnd->TopWndExtend->MouseOnWnd)
		{
			ezWnd->TopWndExtend->MouseOnWnd->MouseOn = FALSE;
			EZSendMessage(ezWnd->TopWndExtend->MouseOnWnd, EZWM_MOUSELEAVE, 0, 0);
			ezWnd->TopWndExtend->MouseOnWnd = NULL;
		}


		//BroadcastProc(ezWnd, SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
		//EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);

		//����һ����Ϣ˵������������Ӵ��ڳ�ȥ��.....
		//EZSendMessage(ezWnd, EZWM_MOUSELEAVE, (WPARAM)1, (LPARAM)NULL);
		return 0;
	}

	case WM_NCHITTEST:
	{
		int iHT;
		iHT = EZSendMessage(ezWnd, EZWM_NCHITTEST, wParam, lParam);//ֻ�������ڲ����յ� EZWM_NCHITTEST ��Ϣ
		if (iHT == 0)
		{
			break;
		}
		return iHT;
	}


	case WM_ERASEBKGND:
	{
		//ֱ�����ӣ��ҹ����أ����������Ļ�,��ERASE����PAINT��
		return 1;
	}

	case WM_PAINT:
	{

		//�ػ�������Ч��������
		hdc = BeginPaint(hwnd, &ps);


		//	��������Ч���ν������Ż�
		BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, ezWnd->TopWndExtend->hdcTop, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);


		EndPaint(hwnd, &ps);

		//���ˣ�������Ч�ˡ�����һ�¡�
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
		//�ȱ�����Ϣ�����ƣ������������ﴰ��
		if (IsEZWindow(ezWnd->FirstChild))
		{
			DestroyEZWindowWithNext(ezWnd->FirstChild);
		}
		//�����Լ�������
		EZSendMessage(ezWnd, EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//����������Ϣ
		DeleteMemDC(ezWnd->hdc);//����DC

		DeleteMemDC(ezWnd->TopWndExtend->hdcTop);

		free(ezWnd->TopWndExtend);



		free(ezWnd);
		SetWindowLongPtr(hwnd, 0, NULL);

		break;
	}

	case WM_SETFOCUS:
		//����Ҫ�����д��ڽ��յ�����������д���
		return 0;

	case WM_KILLFOCUS:
		//֪ͨ���㴰�ڣ�ʧȥ���㡣
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

	//���б����ҵ���Ӧ��ezWnd����ת��EZWM_TIMER��Ϣ

	int i;
	for (i = 0; i < MAX_EZ_TIMER; i++)
	{
		if (iTimerID == ((EZWND)GetWindowLongPtr(hwnd, 0))->TopWndExtend->Timer[i].WinTimerID)
		{
			//��ʱ��ID�ͼ�¼�����
			//��ô��������Ϣ��
			EZSendMessage(((EZWND)GetWindowLongPtr(hwnd, 0))->TopWndExtend->Timer[i].ezWnd, EZWM_TIMER, i, 0);


			break;
		}
	}
	return;
}

int ezInsideWndProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam)
{
	//����޸ĺ���������ö�ٷ���Ӧ�÷����������ҵ����Ȼ�󷵻���һ������顣����֤�ͻ��Ƶ�ö��˳����ͬ��
	EZWND ezChildLast;

	ezChildLast = ezWnd->FirstChild;

	if (IsEZWindow(ezChildLast))
	{

		while (ezChildLast->NextEZWnd)
		{
			ezChildLast = ezChildLast->NextEZWnd;
		}

		//������������������Ƿ����Ӵ�����
		//**************************************************
		while (ezChildLast)
		{
			//����Ƿ����Ӵ����ڣ�ע����Ļ�ƶ�
			//if (PtInEZWnd(ezChildLast, GET_X_LPARAM(lParam) - ezChildLast->ScrollX, GET_Y_LPARAM(lParam) - ezChildLast->ScrollY))
			if ((ezChildLast->MouseMsgRecv != 2) && PtInEZWnd(ezChildLast, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
			{
				//�����ˣ����������
				if (ezInsideWndProc(ezChildLast, message, wParam, MAKELPARAM(GET_X_LPARAM(lParam) - ezChildLast->x - ezChildLast->ScrollX, GET_Y_LPARAM(lParam) - ezChildLast->y - ezChildLast->ScrollY)) == TRANSPARENT)
				{
					//�ðɣ��Ӵ���˵����͸���ġ�����������

					//�ȷ�����굽��
					//���������ʱ�򣬱����˰�������ͬ��һ�����~~~~~
					if (ezWnd->MouseOn == FALSE && message == EZWM_MOUSEMOVE)
					{
						if (ezWnd->ezRootParent->TopWndExtend->MouseOnWnd)
						{
							ezWnd->ezRootParent->TopWndExtend->MouseOnWnd->MouseOn = FALSE;//���һ�¡�
							EZSendMessage(ezWnd->ezRootParent->TopWndExtend->MouseOnWnd, EZWM_MOUSELEAVE, 0, 0);
						}
						ezWnd->ezRootParent->TopWndExtend->MouseOnWnd = ezWnd;

						ezWnd->MouseOn = TRUE;//���һ�¡�
						EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//��������
					}
					else if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//��û���㣬��Ϣ�����
					{
						if (IsEZWindow(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow))
						{
							EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow->FocusState = 0;//��û�����ˡ�
							EZSendMessage(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow, EZWM_KILLFOCUS, NULL, NULL);

						}
						ezWnd->FocusState = 1;

						EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow = ezWnd;
						EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//���н����ˣ�
					}

					return EZSendMessage(ezWnd, message, wParam, lParam);
				}
				return 0;
			}

			ezChildLast = ezChildLast->LastEZWnd;
		}
		//**************************************************		

		//�Ѿ�������ˣ���ô�������������ڡ�ֱ�ӳ�ȥ������ĺϲ�

	}

	{
		//�����Ӵ��ڶ�û��������ô�������������ˡ�

		//�ȷ�����굽����Ϣ
		//���������ʱ�򣬱����˰�������ͬ��һ�����~~~~~
		if (message == EZWM_MOUSEMOVE && ezWnd->MouseOn == FALSE)
		{
			if (ezWnd->ezRootParent->TopWndExtend->MouseOnWnd)
			{
				ezWnd->ezRootParent->TopWndExtend->MouseOnWnd->MouseOn = FALSE;//���һ�¡�
				EZSendMessage(ezWnd->ezRootParent->TopWndExtend->MouseOnWnd, EZWM_MOUSELEAVE, 0, 0);
			}
			ezWnd->ezRootParent->TopWndExtend->MouseOnWnd = ezWnd;
			ezWnd->MouseOn = TRUE;//���һ�¡�
			EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//��������
		}

		else if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//��û���㣬��Ϣ�����
		{
			if (IsEZWindow(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow))
			{
				EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow->FocusState = 0;//��û�����ˡ�
				EZSendMessage(EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow, EZWM_KILLFOCUS, NULL, NULL);
			}
			ezWnd->FocusState = 1;

			EZGetTopParentWindow(ezWnd)->TopWndExtend->FocusWindow = ezWnd;
			EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//���н����ˣ�
		}
		return EZSendMessage(ezWnd, message, wParam, lParam);

	}
}



BOOL EZBroadcastToAllChildFunc(EZWND ezWnd, BOOL sequence, int message, WPARAM wp, LPARAM lp)
{
	//ע�⣬�����������������ȵķ�ʽ������Ϣ�ġ�����������дһ��������ȵģ�����Ժ���д�ˣ�ɾ����һ�仰��
	EZWND LastChild;

	LastChild = ezWnd->FirstChild;
	//��ع�����������ֱ�Ӵ������𲻴���
	for(;;)
	{
		if (sequence)//��
		{
			//�������ԣ��ȴ����Լ���
			BroadcastProc(LastChild, message, wp, lp);//�����Լ�

			EZBroadcastToAllChild(LastChild, sequence, message, wp, lp);//���Լ����Ӵ��ڷ��͸���Ϣ

		}

		if (!IsEZWindow(LastChild->NextEZWnd))//û����һ��
		{
			break;//û����һ����
		}

		LastChild = LastChild->NextEZWnd;//���¹�

	}

	//���������ô�ٹ���ȥ
	if (!sequence)
	{
		for(;;)
		{
			//���Լ����Ӵ��ڷ��͸���Ϣ
			EZBroadcastToAllChild(LastChild, sequence, message, wp, lp);

			BroadcastProc(LastChild, message, wp, lp);//�����Լ�

			if (!IsEZWindow(LastChild->LastEZWnd))//��ͷ��
			{
				break;
			}

			LastChild = LastChild->LastEZWnd;//�ع�

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
		//�����Ƿ��Ƕ���EZ���ڡ�
		if (!ezWnd->IsTopWindow)
		{
			//����
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
		//�ж��Ƿ��Ƕ��㴰��
		if (ezWnd->IsTopWindow)
		{
			//���ײ�һ��
			PatBlt(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
			//PatBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		}
		else
		{
			X_PSX = ezWnd->x + ezWnd->ezParent->ScrollX;
			Y_PSY = ezWnd->y + ezWnd->ezParent->ScrollY;
			//�����ϼ����ڵ���Ӧ���֡�
			BitBlt(ezWnd->hdc, 0, 0,
				max(ezWnd->Width, ezWnd->ezParent->Width), max(ezWnd->Height, ezWnd->ezParent->Height),
				ezWnd->ezParent->hdcCopy,
				X_PSX,
				Y_PSY,
				SRCCOPY);
		}

		EZSendMessage(ezWnd, EZWM_TRANSDRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);


		if (ezWnd->Transparent != 255)//�������255����ϡ���255����ô�������ˣ�
		{
			BLENDFUNCTION bf = {0};
			/*bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;*/ // �������ֶ�ȫ�� 0
			bf.SourceConstantAlpha = 255 - ezWnd->Transparent;

			if (!ezWnd->IsTopWindow)
			{
				//����������������������߽硣����ֻ���ֶ�ȷ��û�г����߽硣
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
				//��ɫ
				HDC hParentdc;
				HDC hdcWhite = GetMemDC(hParentdc = GetDC(ezWnd->hParent), ezWnd->Width, ezWnd->Height);

				PatBlt(hdcWhite, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);

				AlphaBlend(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, hdcWhite, 0, 0, ezWnd->Width, ezWnd->Height, bf);

				DeleteMemDC(hdcWhite);
				ReleaseDC(ezWnd->hParent, hParentdc);
			}
		}

		//��ϻ��������Բ�͸���ķ�ʽ��DC�ϣ����ڴӸ����ڸ�����255-͸���ȸ��Ƶ�hdcWC

		//������ͨ������Ϣ�����Ƶ�DC��
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
//		//IsEZWindow��������ͨ�õļ�����Ƿ���Ч
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



//�жϺ���
BOOL PtInEZWnd(EZWND ezWnd, int x, int y)
{
	return (BOOL)((x > ezWnd->x) && (x < (ezWnd->x + ezWnd->Width)) && (y > ezWnd->y) && (y < (ezWnd->y + ezWnd->Height)));
}

BOOL IsEZWindow(EZWND ezWnd)
{
	return (BOOL)(ezWnd != NULL);
}


//*********************************************************************************************************
//                ������Щ������������EZWindow����EZWindow������Щ��������Щ����Ҳ���Ե���ʹ�á�
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
//                EZWindow�����չͷ�ļ� �Լ��궨��
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
				//��ť�������ˣ�

				//�жϰ�ť����
				if (CHK_STYLE(ezWnd->EZStyle & MKDW(11111111, 00000000, 00000000, 00000000), EZBS_PUSHBUTTON))
				{
					//���Ϳ�����Ϣ��
					EZSendMessage(ezWnd->ezParent, EZWM_COMMAND, 0, ezWnd);
				}
				else if (CHK_STYLE(ezWnd->EZStyle & MKDW(11111111, 00000000, 00000000, 00000000), EZBS_RADIOBUTTON))
				{
					//û˵��AUTOŶ��Ҫ�������ڵĻ���
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
		//����3���Ӵ���
		//���ϣ��󣿣����� -- ��չ0�ſؼ� 
		//���£��ң������� -- ��չ1�ſؼ� 
		//�϶��� -- ��չ2�ſؼ� 

		ezWnd->Extend->hExtend[0] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Scroll_BtnProc);
		ezWnd->Extend->hExtend[0]->ezID = 0;

		ezWnd->Extend->hExtend[1] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Scroll_BtnProc);
		ezWnd->Extend->hExtend[1]->ezID = 1;

		ezWnd->Extend->hExtend[2] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Scroll_BarProc);
		ezWnd->Extend->hExtend[2]->ezID = 2;


		//Ϊ�����Ӵ��ڿ��Ը�������ж�Ӧ�ú������������
		//��������ť��Style���б�ʶ

		if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
		{
			//EZS_CHILD_VSCROLL����ֱ
			ezWnd->Extend->hExtend[0]->EZStyle = ezWnd->Extend->hExtend[1]->EZStyle = 0;
		}
		else
		{
			//EZS_CHILD_HSCROLL��ˮƽ
			ezWnd->Extend->hExtend[0]->EZStyle = ezWnd->Extend->hExtend[1]->EZStyle = 1;
		}


		//��ʼ��������Χ��λ��
		//�������Χ -- int��չ 0 ��
		//����λ���� -- int��չ 1 ��
		//����λ���� -- int��չ 2 ��
		ezWnd->Extend->iExtend[0] = 16;//Ĭ��16��2333������ˡ�
		ezWnd->Extend->iExtend[1] = 0;//Ĭ��0
		ezWnd->Extend->iExtend[2] = 1;//Ĭ��1

		return 0;
	case EZWM_SIZE:
	{

		if ((ezWnd->EZStyle & MKDW(00000000, 00000000, 00000000, 11111111)) == EZS_CHILD_VSCROLL)
		{	//EZS_CHILD_VSCROLL����ֱ

			//�����ֱ���򳤶��Ƿ����3��ˮƽ����ȻҲ̫�����ˡ�
			if (!(ezWnd->Height >= ezWnd->Width * 3))
			{
				//����
				MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[1], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[2], 0, 0, 0, 0, 0);
				return 0;
			}
			//����λ�ÿ�
			MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, ezWnd->Width, (ezWnd->Width * 17) / 15, 0);//�����Ǹ���ť
			MoveEZWindow(ezWnd->Extend->hExtend[1], 0, ezWnd->Height - (ezWnd->Width * 17) / 15, ezWnd->Width, (ezWnd->Width * 17) / 15, 0);//�����Ǹ���ť

																																			//���������Ϊ MAX(���ܿ�� / ��������Χ��,��С��ȣ�

																																			//�ܿ����Ҫ��ȥ���ߵİ�ť��Ŷ
			BarLen = ((ezWnd->Height - (ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
			MoveEZWindow(ezWnd->Extend->hExtend[2],
				0,
				ceil(ezWnd->Width * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
				ezWnd->Width,
				BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
				0);

		}
		else
		{	//EZS_CHILD_HSCROLL��ˮƽ

			//���ˮƽ���򳤶��Ƿ����3����ֱ����ȻҲ̫�����ˡ�
			if (!(ezWnd->Width >= ezWnd->Height * 3))
			{
				//����
				MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[1], 0, 0, 0, 0, 0);
				MoveEZWindow(ezWnd->Extend->hExtend[2], 0, 0, 0, 0, 0);
				return 0;
			}
			//����λ�ÿ�
			MoveEZWindow(ezWnd->Extend->hExtend[0], 0, 0, (ezWnd->Height * 17.0) / 15.0, ezWnd->Height, 0);//����Ǹ���ť
			MoveEZWindow(ezWnd->Extend->hExtend[1], ezWnd->Width - (ezWnd->Height * 17.0) / 15.0, 0, (ezWnd->Height * 17.0) / 15.0, ezWnd->Height, 0);//�ұ��Ǹ���ť


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
		{	//EZS_CHILD_VSCROLL����ֱ
			BarLen = ((ezWnd->Height - (ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
			MoveEZWindow(ezWnd->Extend->hExtend[2],
				0,
				ceil(ezWnd->Width * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
				ezWnd->Width,
				BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
				0);
		}
		else
		{	//EZS_CHILD_HSCROLL��ˮƽ
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
			{	//EZS_CHILD_VSCROLL����ֱ
				BarLen = ((ezWnd->Height - (ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
				MoveEZWindow(ezWnd->Extend->hExtend[2],
					0,
					ceil(ezWnd->Width * 17.0 / 15.0 + (float)BarLen * (float)ezWnd->Extend->iExtend[1]),
					ezWnd->Width,
					BarLen * (float)(ezWnd->Extend->iExtend[2] - ezWnd->Extend->iExtend[1]),
					0);
			}
			else
			{	//EZS_CHILD_HSCROLL��ˮƽ
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
			{	//EZS_CHILD_VSCROLL����ֱ
				BarLen = (((float)ezWnd->Height - (float)(ezWnd->Width) * 34.0 / 15.0) / (float)ezWnd->Extend->iExtend[0]);
				iMove = ceil((float)GET_Y_LPARAM(wParam) / BarLen);//����ͨ��wParam���͹���
			}
			else
			{
				BarLen = (((float)ezWnd->Width - (float)(ezWnd->Height) * 34.0 / 15.0) / ((float)(ezWnd->Extend->iExtend[0])));
				iMove = ceil((float)GET_X_LPARAM(wParam) / BarLen);//����ͨ��wParam���͹���
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
		//��������ֻ����ͨ���������ģ���ϧ����Ҳ������չ�����Լ����밡~
		ezWnd->Extend = malloc(sizeof(EZSE));

		((pEZSE)ezWnd->Extend)->BackGroundColor = RGB(70, 70, 70);
		((pEZSE)ezWnd->Extend)->ForeGroundColor = RGB(70, 70, 70);

		((pEZSE)ezWnd->Extend)->MouseHold = FALSE;

		((pEZSE)ezWnd->Extend)->hFont = NULL;
		((pEZSE)ezWnd->Extend)->IsFontUserControl = -1;

		ezWnd->Extend->Title = NULL;//���������ʱ��ͻ����������ˣ�����freeһ��Ұָ�롣

									//MD��������ʽ���ڣ���ð�ģ�
		ezWnd->IsStyleWindow = FALSE;
		ezWnd->EZStyle = NULL;

		ezWnd->Extend->iExtend[0] = 0;
		//����͸���� 
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
		//		//������ö�ʱ����

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
		//		//���ȡ����ʱ����
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
		//���Ƽ�ͷ
		//�͵�define.
#define SRLBTN_ARR_W 3
#define SRLBTN_ARR_H 2

		//׼�����ʣ���ˢ��
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
			//��ֱ
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
			//ˮƽ

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
		//����͸������
		SelectObject(wParam, hBrush = CreateSolidBrush(ezWnd->Extend->BackGroundColor));
		PatBlt(wParam, 0, 0, ezWnd->Width, ezWnd->Height, PATCOPY);
		DeleteObject(hBrush);
		return 0;

	case EZWM_TIMER:
		//��Ӵ���
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
		//����Ҳ������չ������
		ezWnd->Extend = malloc(sizeof(EZSE));

		//����
		//((pEZSE)ezWnd->Extend)->BackGroundColor = RGB(70, 70, 70);
		//((pEZSE)ezWnd->Extend)->ForeGroundColor = RGB(70, 70, 70);

		((pEZSE)ezWnd->Extend)->MouseHold = FALSE;

		((pEZSE)ezWnd->Extend)->hFont = NULL;
		((pEZSE)ezWnd->Extend)->IsFontUserControl = -1;

		ezWnd->Extend->Title = NULL;//���������ʱ��ͻ����������ˣ�����freeһ��Ұָ�롣

									//MD��������ʽ���ڣ���ð�ģ�
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

			//��¼��갴�µ�λ��
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
			//�����ˣ�����һ��������.
			//������ƶ���������߸�����
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
			//�û��ύ��HFONT���û������ͷš�
			((pEZSE)ezWnd->Extend)->hFont = (HFONT)wParam;
			((pEZSE)ezWnd->Extend)->IsFontUserControl = 0;
		}
		else if (lParam)
		{
			//�û��ύ��LOGFONT�����Ǵ��������١�
			((pEZSE)ezWnd->Extend)->hFont = CreateFontIndirect(lParam);
			((pEZSE)ezWnd->Extend)->IsFontUserControl = 1;
		}
		else
		{
			//��Ϊ�գ�ʹ��Ĭ�����塣
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
			lstrcpy(lf.lfFaceName, TEXT("΢���ź�"));
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
		//����ϵ������
		if (ezWnd->Extend)
		{
			//��������
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

			//�������
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
		//�����Ӵ��ڡ�
		//0����չ�����༭����
		//1����չ����ֱ������
		//2��ˮƽ������
		ezWnd->Extend->iExtend[0] = 0;
		ezWnd->Extend->iExtend[1] = 0;
		ezWnd->Extend->iExtend[2] = 0;
		ezWnd->Extend->hExtend[0] = CreateEZWindow(ezWnd, 0, 0, 0, 0, EZStyle_Edit_InputProc);//���༭����
		ezWnd->Extend->hExtend[1] = CreateEZStyleWindow(ezWnd, TEXT(""), EZS_CHILD | EZS_CHILD_VSCROLL, 0, 0, 0, 0);
		ezWnd->Extend->hExtend[2] = CreateEZStyleWindow(ezWnd, TEXT(""), EZS_CHILD | EZS_CHILD_HSCROLL, 0, 0, 0, 0);

		ezWnd->Extend->iExtend[3] = -1;//������
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
		MoveEZWindow(ezWnd->Extend->hExtend[1],//��ֱ��V
			ezWnd->Width - 15, 0,
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_VSCROLL) ? (15) : (0),
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_HSCROLL) ? (ezWnd->Height - 15) : (ezWnd->Height)
			, 0);
		MoveEZWindow(ezWnd->Extend->hExtend[2],//ˮƽ��H
			0, ezWnd->Height - 15,
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_VSCROLL) ? (ezWnd->Width - 15) : (ezWnd->Width),
			CHK_ALT_STYLE(ezWnd->EZStyle, EZS_HSCROLL) ? (15) : (0)
			, 0);
		return 0;
	}

	case EZWM_SETFONT:
		//�ٺ٣�ɧ������ֱ�ӵݽ���Ĭ�ϴ���
		EZStyle_DefaultProc(ezWnd, message, wParam, lParam);


		//��������SETTEXT�Ĳ���
	case EZWM_SETTEXT:
		//������������ô�С��Ȼ�����ύ��Ĭ�ϴ���
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
				//���Ƶ�ǰ�У����˳���
				GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				xCount = max(xCount, size.cx);
				LineCount++;

				break;
			}
			else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
			{
				//windows���б�ǣ����Ƶ�ǰ�У����¿�ʼ��
				GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				xCount = max(xCount, size.cx);
				LineCount++;

				LastMove = iMove + 2;
				iMove++;

			}
			else if (Text[iMove] == '\n')
			{
				//Linux���б�ǣ����Ƶ�ǰ�С�
				GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				xCount = max(xCount, size.cx);
				LineCount++;

				LastMove = iMove + 1;
			}
			iMove++;//����for���������Ҹ��....�ŵ�����Ͳ�����
		}

		//���ù�����
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
			//�Ѿ���Ĭ�ϴ����ύ���ˣ���ǰ�档
			return 0;
		}
		//else,EZWM_SETTEXT���ύ��Ĭ�ϴ���
		break;
	}
	break;

	case EZWM_SCROLLPOSCHANGE:
		//wParam����ƫ��������
		if (lParam == ezWnd->Extend->hExtend[1])//��ֱ
		{
			ezWnd->Extend->hExtend[0]->ScrollY = -((int)wParam);
		}
		else if (lParam == ezWnd->Extend->hExtend[2])//ˮƽ
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
		//�����ڵ���չ�˷��ˣ��ɴ�����Ҳһ���ø����ڶ������չ��
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
				//��ǰ�У����˳���
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
				//windows���б�ǣ����¿�ʼ��
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
				//Linux���б��
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
			iMove++;//����for���������Ҹ��....�ŵ�����Ͳ�����
		}

		if (IsFounded)
		{
			//���ڵ�ǰ�У�

			CaretY = yCount;
			IsFounded = FALSE;
			int LastLen, CurrLen;
			LastLen = CurrLen = 0;
			for (iMove = LastMove; iMove <= iMaxLen;)
			{

				if ((Text[iMove] == '\0') || (Text[iMove] == '\r' && Text[iMove + 1] == '\n') || (Text[iMove] == '\n'))
				{
					//û�ҵ�������ĩβ
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
					break;
				}

				LastLen = CurrLen;
				//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
				int CharWidth;
				GetCharWidth32(ezWnd->hdc, Text[iMove], Text[iMove], &CharWidth);
				//CurrLen = size.cx;
				CurrLen += CharWidth;


				//�õ���λ�ú���λ�õ�ƽ��λ��
				if (GET_X_LPARAM(lParam) <= (LastLen + CurrLen) / 2)
				{
					//�������������ַ���ǰ��һ��,Ҳ������LastCurr��λ��
					IsFounded = TRUE;
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
					break;

				}

				iMove++;//����for���������Ҹ��....�ŵ�����Ͳ�����
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
			//�ĵ�ĩβ
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
		//��ʼ���ƣ�ѭ����飬�ҵ�\r\n����\n�����У������

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
				//���Ƶ�ǰ�У����˳���
				TextOut(wParam, 0, yCount, Text + LastMove, iMove - LastMove);
				GetTextExtentPoint32(wParam, Text + LastMove, iMove - LastMove, &size);

				yCount += tm.tmHeight;
				//xCount = max(xCount, size.cx);



				break;
			}
			else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
			{
				//windows���б�ǣ����Ƶ�ǰ�У����¿�ʼ��
				TextOut(wParam, 0, yCount, Text + LastMove, iMove - LastMove);
				//GetTextExtentPoint32(wParam, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				//xCount = max(xCount, size.cx);


				LastMove = iMove + 2;
				iMove++;

			}
			else if (Text[iMove] == '\n')
			{
				//Linux���б�ǣ����Ƶ�ǰ�С�
				TextOut(wParam, 0, yCount, Text + LastMove, iMove - LastMove);
				//GetTextExtentPoint32(wParam, Text + LastMove, iMove - LastMove, &size);
				yCount += tm.tmHeight;
				//xCount = max(xCount, size.cx);


				LastMove = iMove + 1;
			}
			iMove++;//����for���������Ҹ��....�ŵ�����Ͳ�����
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
			EZSendMessage(ezWnd, EZWM_KEYDOWN, 37, 0);//ģ�ⰴ��
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
			//���з�������\r\n
			//֧�ֶ��У�
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
			EZSendMessage(ezWnd, EZWM_KEYDOWN, 39, 0);//ģ�ⰴ��
			EZRepaint(ezWnd, 0);

			wParam = '\n';//��ȥ֮���Զ�����
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
		EZSendMessage(ezWnd, EZWM_KEYDOWN, 39, 0);//ģ�ⰴ��
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
				//��
				//����ǰ���ǲ���ͷ�ˣ����� '\n' �� "\r\n"
				if (ezWnd->ezParent->ezParent->Extend->iExtend[2] == 0)
				{
					//���ˣ���ͷ�ˣ�����Ҫ�κβ���
					return 0;
				}

				//�ǲ��ǻ��У�
				if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2] - 1] == '\n')
				{
					//�����ֻ��У�
					if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2] - 2] == '\r')
					{
						ezWnd->ezParent->ezParent->Extend->iExtend[2]--;//����-1
					}
				}
				//�����ǲ��ǻ��У���Ҫ-1.
				ezWnd->ezParent->ezParent->Extend->iExtend[2]--;
			}
			else if (wParam == 39)
			{
				//��

				//���������ǲ��ǵ�β�ˣ�����'\n' �� "\r\n"
				if (ezWnd->ezParent->ezParent->Extend->iExtend[2] == ezWnd->ezParent->ezParent->Extend->TitleLen)
				{
					//���ˣ���β�ˣ�����Ҫ�κβ���
					return 0;
				}
				//�ǲ��ǻ��У�
				if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2]] == '\r')
				{
					if (Text[ezWnd->ezParent->ezParent->Extend->iExtend[2] + 1] == '\n')
					{
						ezWnd->ezParent->ezParent->Extend->iExtend[2]++;//����+1
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
					//���Ƶ�ǰ�У����˳���
					//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
					yCount += tm.tmHeight;


					break;
				}
				else if (Text[iMove] == '\r' && Text[iMove + 1] == '\n')
				{
					//windows���б�ǣ����Ƶ�ǰ�У����¿�ʼ��
					//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);
					yCount += tm.tmHeight;

					LastMove = iMove + 2;
					iMove++;

				}
				else if (Text[iMove] == '\n')
				{
					//Linux���б�ǣ����Ƶ�ǰ�С�
					//GetTextExtentPoint32(ezWnd->hdc, Text + LastMove, iMove - LastMove, &size);

					LastMove = iMove + 1;
					yCount += tm.tmHeight;
				}
				iMove++;//����for���������Ҹ��....�ŵ�����Ͳ�����
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
				//��û����һ�У�
				//��ǰ�ݹ飬���һ�����з�������ڶ������з�

				//����������Ǿ���....������ǻ��з�����������β������Ҫ�����ֶ���鲢�����������

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
							//�������ˣ�����Text[iLineBeginCount]�� '\n'������Ҫ��һ
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
					//û����һ��
					return 0;
				}
				CaretY = ezWnd->ezParent->ezParent->Extend->iExtend[1] - tm.tmHeight;


			}
			else if (wParam == 40)
			{
				//��û����һ�У�
				//����ݹ飬���һ�����з�������ڶ�������
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
					//û����һ��
					return 0;
				}
				CaretY = ezWnd->ezParent->ezParent->Extend->iExtend[1] + tm.tmHeight;

			}

			//�������У��ҵ�������λ�������λ�á�

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

				//�õ���λ�ú���λ�õ�ƽ��λ��
				if (ezWnd->ezParent->ezParent->Extend->iExtend[0] <= (LastLen + CurrLen) / 2)
				{
					//�������������ַ���ǰ��һ��,Ҳ������LastCurr��λ��
					IsFounded = TRUE;
					//��һ�����������ģ��Ǿ������ס������ף�����ֵ��Ϊ0.�����Ļ���iMove��Ӧ-1
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
					//û�ҵ�������ĩβ
					ezWnd->ezParent->ezParent->Extend->iExtend[2] = iMove;
					break;
				}


				iMove++;//����for���������Ҹ��....�ŵ�����Ͳ�����
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



