#pragma once

#include<Windows.h>
#include<windowsx.h>
#include"GetMemDC.h"



//*********************************************************************************************************

//*********************************************************************************************************

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



//�����й���Ϣ
#define EZWM_DRAW 101//���ƣ���͸��
#define EZWM_TRANSDRAW 102//͸�����ƣ��ôλ��ƽ���͸����ʽ���ǡ�

//�����Ϣ
#define EZWM_LBUTTONDOWN 201
#define EZWM_LBUTTONUP 202
#define EZWM_MOUSEMOVE 203//�����Ϣ���WPARAMΪ1���������͵�EZ�����ڣ�˵����Win���ڳ�ȥ��
#define EZWM_MOUSECOME 204
#define EZWM_MOUSELEAVE 205


//������Ϣ
#define EZWM_CHAR 301
#define EZWM_KEYDOWN 302
#define EZWM_KEYUP 303

//������Ϣ
#define SEZWM_COPYDC 1001//���洢DC���ơ�
#define SEZWM_REDRAW 1002//�ػ浽�ڴ�DC
#define SEZWM_MOUSECOME 1003
#define SEZWM_MOUSELEAVE 1004//�����뿪���㴰�ڣ��Ӵ��������м�顣,wP��Ҫ�ų����Ĵ���

#define SEZWM_KILLFOCUS 1005//�н���Ĵ���ʧȥ���㡣wP�ų���顣


// #define SEZWM_CAPTURE 1005//��һ���������벶�������Ѿ������˵ĸϽ��ŵ���



HINSTANCE ezhInst;




//�ȶ����ִ��ڽṹ��


#define EZWindowClass TEXT("EZWindowClass")

typedef struct tagEZWND * EZWND;
typedef int(*EZWNDPROC)(EZWND, int, WPARAM, LPARAM);


//����Ƕ�EZWINDOW�ṹ��Ķ��塣EZWND��ָ��ýṹ��ָ�롣
typedef struct tagEZWND
{
	//�йش�����Ϣ
	int x;
	int y;
	int Width;
	int Height;

	//�йػ���״̬****************************
	BYTE Transparent;//͸���ȣ�0����ȫ͸����255��͸��

					//�йش���״̬****************************
	int FocusState;//���뽹��״̬��0-�޽��㡣1-�н��� 
	int Show;//�Ƿ���ʾ���Լ���ʾ��״̬��


			 //�й����****************************
	BOOL MouseOn;//����ڸô����ϡ�


				 //�йػ���****************************
	HDC hdc;//һ�����ƿռ䡣ʼ�մ��ڣ�ֱ�����ڱ����١����ڻ��ƾͻ�����������档
	HDC hdcWC;//hdcWithChild���Ӵ��ڽ������ǻ���������
	BOOL Update;//��������0Ϊ������£�1Ϊ�����˸ı䣬��Ҫ���¡�


				//�йع�������****************************
	EZWNDPROC ezWndProc;//���ڹ���
	struct tagEZWND * ezParent;//EZ������
	struct tagEZWND * ezRootParent;//EZ���ȴ���

	BOOL IsTopWindow;//����ָʾ�Ƿ��Ƕ���EZ���ڡ�
	HWND hParent;//����Win����.

	struct tagEZWND * FirstChild;//��һ���Ӵ���
	struct tagEZWND * LastEZWnd;//����������ڣ����е���һ������
	struct tagEZWND * NextEZWnd;//����������ڣ����е���һ������

	//��������ʹ�ã����ڱ�ݹ���******
	EZWND FocusWindow;//ӵ�����뽹��Ĵ���

}EZWINDOW;



//*******************************************************************************************
//                ��������
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

//�����궨��
#define CreateEZParetntWindow(x, y, Width, Height,  ezWndProc, hMenu, hParent) CreateEZParetntWindowEx(x, y, Width, Height,  WS_CHILD|WS_VISIBLE, ezWndProc, hMenu, hParent) 

//#define IsEZWindow(ezWnd) (ezWnd)?TRUE:FALSE

//��ʼ��EasyWindow�⺯��
BOOL InitEZWindow(HINSTANCE hInstance)
{
	WNDCLASS wndclass;
	//����ʵ�����********���ļۣ����Ӽ���Ƿ���Ч
	ezhInst = hInstance;

	//ע�ᴰ����
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
	//���Ľ�������Ƿ�ע��ɹ���
}



//�������ں���
EZWND CreateEZParetntWindowEx(int x, int y, int Width, int Height, DWORD Style, EZWNDPROC ezWndProc, HMENU hMenu, HWND hParent)
{
	HWND hwndParent;//����Windows����ĸ�����
	EZWND ezwndParent;//���Ǻ�Win���ڵȴ��EZ���ڣ����ظ��û����ô��ڴݻ�ʱͬʱ�ݻ�Win����
	HDC fhdc;

	ezwndParent = (EZWND)malloc(sizeof(EZWINDOW));

	

	//Create tht EZ Window With out Using "CreateEZWindow"
	
	if (!ezwndParent)//����ڴ�
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
	ezwndParent->ezParent = NULL;//û�У��ա�
	ezwndParent->ezRootParent = ezwndParent;//���Լ�
	ezwndParent->IsTopWindow = TRUE;//�ǵģ��Ƕ��㴰�ڡ�

	ezwndParent->FocusState = FALSE;

	ezwndParent->MouseOn = FALSE;

	ezwndParent->Update = FALSE;//�տ�ʼ���϶�û�и��¹���

	ezwndParent->Transparent = 255;//��͸��

	ezwndParent->ezWndProc = ezWndProc;

	ezwndParent->FocusWindow = NULL;


	//�󲿷����ݶ���ʼ������ˡ�ezwndParent����Ϊ�����ύ��WM_CREATE��Ϣ�������ڼ佫���ָ������Ϊ������չ
	hwndParent = CreateWindow(EZWindowClass, TEXT(""), Style, x, y, Width, Height, hParent, hMenu, ezhInst, ezwndParent);


									  //���ݸ���Win�����ڻ��һ��DC
	fhdc = GetDC(hwndParent);
	ezwndParent->hdc = GetMemDC(fhdc, Width, Height);
	ezwndParent->hdcWC = GetMemDC(fhdc, Width, Height);
	ReleaseDC(hwndParent, fhdc);



	//��Win��������չָ��EZ����
	//SetWindowLong(hwndParent, 0, (LONG)ezwndParent);
	//���ڣ����ǽ��л��ơ���������WM_PAINT������ʱ��Ϳ���ֱ��Bitblt�ˡ��������.....�Ӵ���ò�Ʋ���Ҫ
	
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
	

	if (!(ezWnd = (EZWND)malloc(sizeof(EZWINDOW))))//����������ڴ�
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
	ezWnd->IsTopWindow = FALSE;//������


	ezWnd->FocusState = 0;

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
	ezWnd->hdcWC = GetMemDC(fhdc, Width, Height);
	ReleaseDC(hParent, fhdc);

	
	EZSendMessage(ezWnd, EZWM_CREATE, 0, 0);//���ʹ�����Ϣ
	MoveEZWindow(ezWnd, x, y, Width, Height, 0);
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


	for (;;)//ѭ�����������
	{
		if (IsEZWindow(ezChildLast->NextEZWnd))
		{
			ezChildLast = ezChildLast->NextEZWnd;//�����ƶ�
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




//���ٴ��ں���
BOOL DestroyEZWindow(EZWND ezWnd)
{
	if (ezWnd->IsTopWindow)
	{
		DestroyWindow(ezWnd->hParent);//������ˣ����ٻ����������
		return TRUE;
	}

	//�ȱ�����Ϣ�����ƣ������������ﴰ��
	if (IsEZWindow(ezWnd->FirstChild))
	{
		DestroyEZWindowWithNext(ezWnd->FirstChild);
	}
	//�����Լ�������
	EZSendMessage(ezWnd, EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//����������Ϣ
	DeleteDC(ezWnd->hdc);//����DC
	DeleteDC(ezWnd->hdcWC);//����DCWC
						   
	
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
		while(1)
		{
			if (!IsEZWindow(ezChildLast->NextEZWnd))
			{
				break;
				//���������
			}

			ezChildLast = ezChildLast->NextEZWnd;
		}


		//��ѭ������������ǰ��һ�߹�һ��ɾ��
		while (1)
		{
			//Ϊ�����ݣ��Ȼع���Ȼ��ͨ�����µ�ָ���һ�ȥ��ɾ��
			if (IsEZWindow(ezChildLast->LastEZWnd))//��û��ͷ
			{
				ezChildLast = ezChildLast->LastEZWnd;//�ع�

													 //��ʱ��ezChildLast->NextEZWnd�������һ����DestroyEZWindow��ɾ�˸ô��ں�������ڵ��Ӵ��ڡ�
				DestroyEZWindow(ezChildLast->NextEZWnd);//ɾ��
				continue;
			}
			
			//û��continue��Ҳ����else.
			//������ͷ�ˣ�DestroyEZWindow��ɾ�˸ô��ں�������ڵ��Ӵ��ڡ�
			DestroyEZWindow(ezChildLast);

			return TRUE;
		}
		
	}
	else
	{//��������һ�����д��ڡ�
		DestroyEZWindow(ezWnd);//ɾ��
	}
	return TRUE;
}



//�Դ��ڽ��е������жϣ��ĺ���
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



//�봰�ڻ����йصĺ���
BOOL EZRedraw(EZWND ezWnd)//�ػ浽�ڴ�dc,�����¡�
{
	BroadcastProc(ezWnd, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);

	EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_REDRAW, (WPARAM)NULL, (LPARAM)NULL);

	return TRUE;
}

BOOL EZUpdate(EZWND ezWnd, HDC hdc)//��DC���µ����壬���ػ档�ڶ���������DC���粻�ṩ���������Զ���ȡ��
{
	//�ҵ���ġ����ڡ���
	EZWND ezRootWnd;
	HDC hdcg;

	ezRootWnd = EZGetTopParentWindow(ezWnd);//�õ����㴰��







		if (!hdc)//ûDC
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

		//ֻ��Ҫ��������ڣ�����Ҫȫ��BitBlt��,�õ���Ը����ڵ�λ��
		EZWND WndNow = ezWnd;

		while(1)
		{
			//�����ƣ�ֱ��������
			if (!WndNow->IsTopWindow)
			{
				Countx += WndNow->x;
				County += WndNow->y;
				WndNow = WndNow->ezParent;
				continue;
			}
			
			break;
			
		}
		
		
		if (!hdc)//ûDC
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

BOOL EZRepaint(EZWND ezWnd, HDC hdc)//�ػ沢�Ҹ���
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
		((EZWND)((LPCREATESTRUCT)lParam)->lpCreateParams)->hParent = hwnd;//����Win������
		EZSendMessage((EZWND)((LPCREATESTRUCT)lParam)->lpCreateParams, EZWM_CREATE, 0, 0);//���ʹ�����Ϣ
		

		return 0;
	case WM_SIZE:

		
		((EZWND)(GetWindowLong(hwnd, 0)))->Width = 1;
		((EZWND)(GetWindowLong(hwnd, 0)))->Width = LOWORD(lParam);
		((EZWND)(GetWindowLong(hwnd, 0)))->Height = GET_Y_LPARAM(lParam);

		DeleteDC(((EZWND)(GetWindowLong(hwnd, 0)))->hdc);
		DeleteDC(((EZWND)(GetWindowLong(hwnd, 0)))->hdcWC);

		//HDC fhdc;
		//��ʵ����Ӧ�����������.���ǣ�hdc�������ڲ��������𣿣����ɴ�����Ǹ��ɣ�ʡ�ڴ�


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
		//������������ȥ��
		if (((EZWND)GetWindowLong(hwnd, 0))->MouseOn == FALSE)
		{
			//�ոս���


			//���Խ��м���ˡ�
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			tme.hwndTrack = hwnd;
			TrackMouseEvent(&tme);
		}
		ezInsideWndProc((EZWND)GetWindowLong(hwnd, 0), EZWM_MOUSEMOVE, wParam, lParam);
		return 0;


	case WM_MOUSELEAVE:
		//ѽ����������~~~   �㲥һ�£���ÿ���Ӵ��ڿ����ǲ��Ǵ��Լ��������ȥ�ġ�
		//�ȼ���Լ���

		BroadcastProc(((EZWND)(GetWindowLong(hwnd, 0))), SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
		EZBroadcastToAllChild(((EZWND)(GetWindowLong(hwnd, 0))), TRUE, SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);

		//����һ����Ϣ˵������������Ӵ��ڳ�ȥ��.....
		EZSendMessage(((EZWND)(GetWindowLong(hwnd, 0))), EZWM_MOUSELEAVE, (WPARAM)1, (LPARAM)NULL);
		return 0;
	case WM_ERASEBKGND:
		//ֱ�����ӣ��ҹ����أ����������Ļ�,��ERASE����PAINT��
		return 1;

	case WM_PAINT:
		
			//�ػ�������Ч��������
			hdc = BeginPaint(hwnd, &ps);

		
			BitBlt(hdc, 0, 0, ((EZWND)GetWindowLong(hwnd, 0))->Width, ((EZWND)GetWindowLong(hwnd, 0))->Height, ((EZWND)GetWindowLong(hwnd, 0))->hdcWC, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
		

		//���ˣ�������Ч�ˡ�����һ�¡�
		((EZWND)GetWindowLong(hwnd, 0))->Update = 0;
		return 0;

	case WM_DESTROY:
		
		
		//�ȱ�����Ϣ�����ƣ������������ﴰ��
		if (IsEZWindow(((EZWND)GetWindowLong(hwnd, 0))->FirstChild))
		{
			DestroyEZWindowWithNext(((EZWND)GetWindowLong(hwnd, 0))->FirstChild);
		}
		//�����Լ�������
		EZSendMessage(((EZWND)GetWindowLong(hwnd, 0)), EZWM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);//����������Ϣ
		DeleteDC(((EZWND)GetWindowLong(hwnd, 0))->hdc);//����DC
		DeleteDC(((EZWND)GetWindowLong(hwnd, 0))->hdcWC);//����DCWC
		
		
		free(((EZWND)GetWindowLong(hwnd, 0)));
		SetWindowLong(hwnd, 0, 0);

		break;
	case WM_SETFOCUS:
		//����Ҫ�����д��ڽ��յ�����������д���
		return 0;

	case WM_KILLFOCUS:
		//֪ͨ���㴰�ڣ�ʧȥ���㡣
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
		//��Щ���������Ϣ��
	{



		if (IsEZWindow(ezWnd->FirstChild))
		{
			ezChildLast = ezWnd->FirstChild;
			for (;;)//����������ײ�������Ƿ����Ӵ�����
					//**************************************************
			{
				//����Ƿ����Ӵ�����
				if (PtInEZWnd(ezChildLast, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
				{
					//�����ˣ����������
					if (ezInsideWndProc(ezChildLast, message, wParam, MAKELPARAM(GET_X_LPARAM(lParam) - ezChildLast->x, GET_Y_LPARAM(lParam) - ezChildLast->y)) == TRANSPARENT)
					{
						//�ðɣ��Ӵ���˵����͸���ġ�����������

						if (ezWnd->FocusState == 0&&message == EZWM_LBUTTONDOWN)//��û���㣬��Ϣ�����
						{
							if (IsEZWindow(EZGetTopParentWindow(ezWnd)->FocusWindow))
							{
								BroadcastProc(EZGetTopParentWindow(ezWnd)->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
							}
							ezWnd->FocusState = 1;

							EZGetTopParentWindow(ezWnd)->FocusWindow = ezWnd;
							EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//���н����ˣ�
						}

						return EZSendMessage(ezWnd, message, wParam, lParam);
					}
					break;
				}
				else if (IsEZWindow(ezChildLast->NextEZWnd))
				{
					ezChildLast = ezChildLast->NextEZWnd;//��һ���Ӵ��ڣ�
				}
				else
				{
					//�Ѿ�������ˣ���ô�������������ڡ�

					//�ȷ�����굽��
					//���������ʱ�򣬱����˰�����һ����ͬ��һ�����~~~~~
					if (message == EZWM_MOUSEMOVE)
					{
						if (ezWnd->MouseOn == FALSE)
						{

							//��ô����һ���ӱ�ĵط�����
							BroadcastProc(EZGetTopParentWindow(ezWnd), SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
							EZBroadcastToAllChild(EZGetTopParentWindow(ezWnd), TRUE, SEZWM_MOUSELEAVE, NULL, NULL);

							EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//��������
							ezWnd->MouseOn = TRUE;//���һ�¡�


						}
					}

					//������Ϣ

					if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//��û���㣬��Ϣ�����
					{
						//BroadcastProc(EZGetTopParentWindow(ezWnd), SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
						//EZBroadcastToAllChild(ezWnd, TRUE, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
						if (IsEZWindow(EZGetTopParentWindow(ezWnd)->FocusWindow))
						{
							BroadcastProc(EZGetTopParentWindow(ezWnd)->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
						}
						ezWnd->FocusState = 1;

						EZGetTopParentWindow(ezWnd)->FocusWindow = ezWnd;
						EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//���н����ˣ�

					}

					return EZSendMessage(ezWnd, message, wParam, lParam);

				}
			}
			//**************************************************
		}
		else
		{
			//�����Ӵ��ڶ�û��������ô�������������ˡ�

			//�ȷ�����굽����Ϣ
			//���������ʱ�򣬱����˰�����һ����ͬ��һ�����~~~~~
			if (message == EZWM_MOUSEMOVE)
			{
				if (ezWnd->MouseOn == FALSE)
				{
					//��ô����һ���ӱ�ĵط�����
					BroadcastProc(EZGetTopParentWindow(ezWnd), SEZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);
					EZBroadcastToAllChild(EZGetTopParentWindow(ezWnd), TRUE, SEZWM_MOUSELEAVE, NULL, NULL);

					EZSendMessage(ezWnd, EZWM_MOUSECOME, (WPARAM)NULL, (LPARAM)NULL);//��������
					ezWnd->MouseOn = TRUE;//���һ�¡�


				}
			}

			if (ezWnd->FocusState == 0 && message == EZWM_LBUTTONDOWN)//��û���㣬��Ϣ�����
			{
				if (IsEZWindow(EZGetTopParentWindow(ezWnd)->FocusWindow))
				{
					BroadcastProc(EZGetTopParentWindow(ezWnd)->FocusWindow, SEZWM_KILLFOCUS, (WPARAM)NULL, (LPARAM)NULL);
				}
				ezWnd->FocusState = 1;

				EZGetTopParentWindow(ezWnd)->FocusWindow = ezWnd;
				EZSendMessage(ezWnd, EZWM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);//���н����ˣ�
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
	//ע�⣬�����������������ȵķ�ʽ������Ϣ�ġ�����������дһ��������ȵģ�����Ժ���д�ˣ�ɾ����һ�仰��
	EZWND LastChild;


	if (IsEZWindow(ezWnd->FirstChild))
	{

		LastChild = ezWnd->FirstChild;
		//��ع�����������ֱ�Ӵ������𲻴���
		while(1)
		{
			if (sequence)//��
			{
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
			while(1)
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
		//�����Ƿ��Ƕ���EZ���ڡ�
		if (!ezWnd->IsTopWindow)
		{
			//����
			BitBlt(ezWnd->ezParent->hdcWC, ezWnd->x, ezWnd->y, ezWnd->Width, ezWnd->Height, ezWnd->hdcWC, 0, 0, SRCCOPY);
			
		}
		
		//������㣬û���ϼ�EZ���ڡ����Ƶ�Win���ڲ��ɱ�ģ�鸺��
		return 0;
	}
	case SEZWM_REDRAW:
	{
		//�ж��Ƿ��Ƕ��㴰��
		if (ezWnd->IsTopWindow)
		{
			//���ײ�һ��
			PatBlt(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
			//PatBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, WHITENESS);
		}
		else
		{
			//�����ϼ����ڵ���Ӧ���֡�
			BitBlt(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->ezParent->hdcWC, ezWnd->x, ezWnd->y, SRCCOPY);
			//BitBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->ezParent->hdcWC, ezWnd->x, ezWnd->y, SRCCOPY);
		}

		EZSendMessage(ezWnd, EZWM_TRANSDRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);


		if (ezWnd->Transparent != 255)//�������255����ϡ���255����ô�������ˣ�
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
				//��ɫ
				HDC hParentdc;
				HDC hdcWhite = GetMemDC(hParentdc = GetDC(ezWnd->hParent), ezWnd->Width, ezWnd->Height);


				AlphaBlend(ezWnd->hdc, 0, 0, ezWnd->Width, ezWnd->Height, hdcWhite, 0, 0, ezWnd->Width, ezWnd->Height, bf);

				DeleteDC(hdcWhite);
				ReleaseDC(ezWnd->hParent, hParentdc);
			}
		}

		
		
		
		//��ϻ��������Բ�͸���ķ�ʽ��DC�ϣ����ڴӸ����ڸ�����255-͸���ȸ��Ƶ�hdcWC
		
		//������ͨ������Ϣ�����Ƶ�DC��
		EZSendMessage(ezWnd, EZWM_DRAW, (WPARAM)(ezWnd->hdc), (LPARAM)NULL);
		BitBlt(ezWnd->hdcWC, 0, 0, ezWnd->Width, ezWnd->Height, ezWnd->hdc, 0, 0, SRCCOPY);


		return 0;
	}
	case SEZWM_MOUSELEAVE:
	{
		//��������
		if ((ezWnd != (EZWND)wP)&&(ezWnd->MouseOn == TRUE))
		{
			
			//�������ȥ�ģ�

			ezWnd->MouseOn = FALSE;
			EZSendMessage(ezWnd, EZWM_MOUSELEAVE, (WPARAM)NULL, (LPARAM)NULL);

		}
		return 0;
	}
	case SEZWM_KILLFOCUS:
	{
		//����Ƿ��ų����Ƿ���н��㣬����У�ȥ�����㣬����KILLFOCUS��
		if ((ezWnd->FocusState == 1)&&(ezWnd != (EZWND)wP))//�н���
		{
			//���ų�
			ezWnd->FocusState = 0;//��û�����ˡ�
			EZSendMessage(ezWnd, EZWM_KILLFOCUS, NULL, NULL);
			
		}
		
	}
	}
}



EZWND EZGetTopParentWindow(EZWND ezWnd)//�õ�����EZ����
{
	return ezWnd->ezRootParent;
}


BOOL SetEZWndTransparent(EZWND ezWnd, int Transparent)//����EZ����͸����
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