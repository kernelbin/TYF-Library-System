#include<Windows.h>
#include"EasyWindow.h"
#include"Global.h"





typedef BOOL(*BTNFUNC)();//��ť���º���õĺ���



BTNFUNC MainUIBtnProc();

BTNFUNC DataRecordBtnProc();

BTNFUNC UsingFinishBtnProc();

BTNFUNC ShutDownBtnProc();

BTNFUNC ExitTyfLibSysProc();

//���߿�ť�����Ϣ�Ľṹ��
typedef struct tagBorderButton
{
	int ID;
	TCHAR BtnName[32];
	BTNFUNC BtnFunc;

} BORDERBTN, * PBORDERBTN;

BORDERBTN BorderBtn[] = {
	0,TEXT("������"), MainUIBtnProc,
	0,TEXT("���ݼ�¼"),DataRecordBtnProc,
	0,TEXT("�˳���¼"), UsingFinishBtnProc,
	0,TEXT("�ػ�"),ShutDownBtnProc,
	0,TEXT("�ر����"),ExitTyfLibSysProc
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
			lstrcpy(lf.lfFaceName, TEXT("΢���ź�"));
			BtnFont = CreateFontIndirect(&lf);
		}

		for (iCount = 0; iCount < BDBTN_NUM; iCount++)
		{
			
			hButton[iCount] = CreateEZWindow(ezWnd, 0, iCount*CAPTIONHEIGHT*RATIO+ CAPTIONHEIGHT*RATIO*(1+RATIO), ezWnd->Width, CAPTIONHEIGHT*RATIO, BorderBtnProc);

			//��ʵ����������һ��Ҳ���ص����������Ǹ�ָ����~�������Ҳ����ٿ�һ��ID�������ɴ���ָ���ID��������2333333
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

			//��͸���Ȳ�Ϊ0���ͻ���
			if (ezWnd->Transparent != 0)
			{
				PatBlt(wParam, 0, 0, 4, ezWnd->Height, WHITENESS);
			}
			//��ͼ�꣬д��
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
	//��������
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
	//�����ݼ�¼����
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
	//ʹ�����
	LogoutFunc();
	
}


BTNFUNC ShutDownBtnProc()
{
	//�ػ�
	if (MessageBox(NULL, TEXT("���Ҫ�ػ���\r\n��ȷ����δ��ɵĹ����Ѿ����棡"),
		TEXT("ͬһ��ͼ��ݹ���ϵͳ"), MB_ICONWARNING | MB_OKCANCEL | MB_TASKMODAL) == IDOK)
	{
		ExitWindowsEx(EWX_FORCE, 0);
	}


}

BTNFUNC ExitTyfLibSysProc()
{
	//�˳��������򣬰�������DLL���ӽ��̡�

	if (pMainData->AuthorityLevelList[pMainData->UserSelect] != 1)
	{
		MessageBox(NULL, TEXT("�ر������Ҫ����ԱȨ�ޣ�"),
			TEXT("ͬһ��ͼ��ݹ���ϵͳ"), MB_ICONERROR | MB_ICONINFORMATION | MB_TASKMODAL);
	}
	else
	{
		if (MessageBox(NULL, TEXT("�⽫�����˳�ͬһ��ͼ��ݹ���ϵͳ��������"),
			TEXT("ͬһ��ͼ��ݹ���ϵͳ"), MB_ICONQUESTION | MB_OKCANCEL | MB_TASKMODAL) == IDOK)
		{
			//ִ��һϵ�в���ر����
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