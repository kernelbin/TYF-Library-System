#pragma once
#include<windows.h>
#include"resource.h"
#include"EasyWindow.h"
#include"../Public/Public.h"

/****   �����С   ****/
#define CAPTIONHEIGHT 60

#define BORDERWIDTH 210

/****   ��������   ****/
#define RATIO 0.618

#define STRETCH 4.0


/****   ��¼�й�   ****/

#define MAX_USER_COUNT 16
//����û�����


/****   Ӧ�ó���   ****/

#define EXE_FILENAME TEXT("ͬһ��ͼ��ݹ���ϵͳ.exe")


/****   �ں˶���   ****/



HANDLE hMainData;//������ �����ڴ���

HANDLE ReopenNoticeSema;//����ظ��� �ź������

/****   ���ݸ�ʽ   ****/
typedef struct tagMainDataStruct
{
	int WindowsLock;//������״̬

	//����PID
	DWORD Main_PID;
	DWORD Protect_PID;

	//���ڱ���Ƿ���̱��������ڡ����ʱ�����жϡ�
	BOOL MainKilled;
	int ProtectKilled;

	//���ڽ����˳���ǣ�ȫ�����˳���
	BOOL bExit;

	//��¼���
	int UserCount;

	char UsernameList[MAX_USER_COUNT][256];
	char PasswordList[MAX_USER_COUNT][256];
	int UserID[MAX_USER_COUNT];//���ݿ��е��û�ID��-1�����ع���Ա
	DWORD TimeLimitList[MAX_USER_COUNT];//ʱ������,-1����û��ʱ������
	int AuthorityLevelList[MAX_USER_COUNT];//Ȩ�޼���Ŀǰ��0��ͨ�û���1����Ա
	int DeleteList[MAX_USER_COUNT];//�Ƿ�ʹ�����ɾ����0��ɾ����1ɾ����

	int UserSelect;

	BOOL IsLogin;//�Ƿ��¼
	


	//�����������
	DWORD LoadTime;//���ϴΣ�����ʱ�䣨���룬������˰ɣ�2^32�η�=100���� hhhhh233333��
	int LoadState;//��ǰ����״̬


	//ʱ��
	DWORD RunningTime;//��������ʱ�䣬�롣���˼�ʱ���������LoadTime����ͬ����

	DWORD TimeLimit;//��ǰ�û���ʱ������
	DWORD LoginTime;//��ǰ�û���¼��ʱ��

} MAINDATASTRUCT, *PMAINDATASTRUCT;




//LOADSTATE����
#define LS_EMPTY 0 //��δ���ع�
#define LS_LOADED 1 //���ع�������ʱ���� LoadTime
#define LS_LOADFAILED 2 //����ʧ�ܣ���δ���سɹ���
#define LS_REFRESHFAILED 3//ˢ��ʧ�ܣ�֮ǰ�����ɹ�������ˢ��ʱʧ���ˣ�
#define LS_REFRESHING 4 // ����ˢ��


//��ʱ��ID

#define APP_TIMER_ID 100//Ӧ�ò����ظ��ɣ�

/****   ����ͼƬ   ****/



//����ͼƬ����
#define PIC_NUM 6




static HBITMAP LoadJpegFromData(PBYTE pData, DWORD DataLength);//����JPEG



/****   ��������   ****/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow);

EZWNDPROC ShowImgProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

EZWNDPROC MainProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

EZWNDPROC CaptionProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

	EZWNDPROC CloseProc(EZWND, int, WPARAM, LPARAM);

	EZWNDPROC SmallProc(EZWND, int, WPARAM, LPARAM);

	

EZWNDPROC BorderProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

	EZWNDPROC BorderBtnProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);


EZWNDPROC MainUIProc(EZWND ezWnd, int message, WPARAM wPaeam, LPARAM lParam);

EZWNDPROC PackageRecUIProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);



EZWNDPROC LockProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);

	EZWNDPROC UserListBoxProc(EZWND ezWnd, int message, WPARAM wParam, LPARAM lParam);




VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);



BOOL LoginFunc(int User);

BOOL LogoutFunc();









BOOL MainDataLoad(BOOL CheckOnly);

BOOL MainDataOpen();

BOOL MainDataCreate();

BOOL MainDataDelete();

PMAINDATASTRUCT MakeMainDataStruct();





BOOL BeginNetDataLoad();

void __stdcall NetDataLoad(void * var);

BOOL BeginNetDataUserDelete(int UserID);

void __stdcall NetDataUserDelete(int UserID);

void __stdcall LogoutDataRefresh();



BOOL NetLoadStateUpdate();



//�����������̺���
void __stdcall StartProtectProcess(void * var);



//�������̺���
int OpenMainProcess();


//�򿪱������̺���
void __stdcall OpenProtectProcess(void * var);


//�ȴ��ź�������
void __stdcall WaitForSem(void * var);





//����������

BOOL OpenLock();

BOOL CloseLock();



/****   ȫ�ֱ���   ****/

int Cmd_Mode;

PMAINDATASTRUCT pMainData;

EZWND MainWnd;


EZWND MainUI;//������
EZWND PkgRecUI;//���ݼ�¼�����������վ�ȣ�����
EZWND URLListShow;
EZWND UIShow;//����չʾ��UI����


EZWND LockWnd;

HINSTANCE hInst;//ʵ�����

int WndLock;//���ڴ�ӳ���ļ��е��Ǹ�����ͬ���������ݴ򲻿�ʱ�������Ϊ׼��


//�������
LOGFONT FontForm;


BOOL GDIObjectCreate();
BOOL GDIObjectClean();



//��¼��־���
#define LOG_EVENT 1 //�����¼��������������֮���
#define LOG_PROTECT 2 //�������쳣������������ر�
#define LOG_ERROR 3 //����ڲ�����

#define LOG_EVENT_START  1//�����������
#define LOG_EVENT_END    2//�����������
#define LOG_EVENT_LOGIN  3//�û���¼��Comment���û���
#define LOG_EVENT_LOGOUT 4//�û��˳���¼��Comment���û���


#define LOG_PROTECT_MAIN_KILLED 1//�����̱�����
#define LOG_PROTECT_PROTECT_KILLED 2//�������̱�����

#define LOG_ERROR_WEB 1//�������

BOOL WriteLog(int LogID, int Value, TCHAR Comment[]);

BOOL WriteLogA(int LogID, int Value, char Comment[]);








int StartCapture();



//����URL��¼���
int InitRecord();
int RecordURL(char URL[]);

#define MAX_URL_NUM 2048
int URL_Num;
char * URL_Rec[MAX_URL_NUM];


