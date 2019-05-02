#pragma once
#include<windows.h>
#include"resource.h"
#include"EasyWindow.h"
#include"../Public/Public.h"

/****   界面大小   ****/
#define CAPTIONHEIGHT 60

#define BORDERWIDTH 210

/****   比例定义   ****/
#define RATIO 0.618

#define STRETCH 4.0


/****   登录有关   ****/

#define MAX_USER_COUNT 16
//最大用户数量


/****   应用程序   ****/

#define EXE_FILENAME TEXT("同一附图书馆管理系统.exe")


/****   内核对象   ****/



HANDLE hMainData;//主数据 共享内存句柄

HANDLE ReopenNoticeSema;//软件重复打开 信号量句柄

/****   数据格式   ****/
typedef struct tagMainDataStruct
{
	int WindowsLock;//桌面锁状态

	//进程PID
	DWORD Main_PID;
	DWORD Protect_PID;

	//用于标记是否进程被结束，在“复活”时用来判断。
	BOOL MainKilled;
	int ProtectKilled;

	//用于进程退出标记（全程序退出）
	BOOL bExit;

	//登录相关
	int UserCount;

	char UsernameList[MAX_USER_COUNT][256];
	char PasswordList[MAX_USER_COUNT][256];
	int UserID[MAX_USER_COUNT];//数据库中的用户ID。-1代表本地管理员
	DWORD TimeLimitList[MAX_USER_COUNT];//时间限制,-1代表没有时间限制
	int AuthorityLevelList[MAX_USER_COUNT];//权限级别。目前，0普通用户，1管理员
	int DeleteList[MAX_USER_COUNT];//是否使用完后删除。0不删除，1删除。

	int UserSelect;

	BOOL IsLogin;//是否登录
	


	//加载数据相关
	DWORD LoadTime;//（上次）加载时间（我想，这个够了吧？2^32次方=100多年 hhhhh233333）
	int LoadState;//当前加载状态


	//时间
	DWORD RunningTime;//程序运行时间，秒。除了计时还给上面的LoadTime用于同步。

	DWORD TimeLimit;//当前用户的时间限制
	DWORD LoginTime;//当前用户登录的时间

} MAINDATASTRUCT, *PMAINDATASTRUCT;




//LOADSTATE定义
#define LS_EMPTY 0 //从未加载过
#define LS_LOADED 1 //加载过，加载时间是 LoadTime
#define LS_LOADFAILED 2 //加载失败（从未加载成功）
#define LS_REFRESHFAILED 3//刷新失败（之前曾经成功过，但刷新时失败了）
#define LS_REFRESHING 4 // 正在刷新


//计时器ID

#define APP_TIMER_ID 100//应该不会重复吧？

/****   背景图片   ****/



//背景图片个数
#define PIC_NUM 6




static HBITMAP LoadJpegFromData(PBYTE pData, DWORD DataLength);//加载JPEG



/****   函数定义   ****/

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



//创建保护进程函数
void __stdcall StartProtectProcess(void * var);



//打开主进程函数
int OpenMainProcess();


//打开保护进程函数
void __stdcall OpenProtectProcess(void * var);


//等待信号量函数
void __stdcall WaitForSem(void * var);





//开关桌面锁

BOOL OpenLock();

BOOL CloseLock();



/****   全局变量   ****/

int Cmd_Mode;

PMAINDATASTRUCT pMainData;

EZWND MainWnd;


EZWND MainUI;//主界面
EZWND PkgRecUI;//数据记录（浏览过的网站等）界面
EZWND URLListShow;
EZWND UIShow;//正在展示的UI界面


EZWND LockWnd;

HINSTANCE hInst;//实例句柄

int WndLock;//和内存映射文件中的那个变量同步。当数据打不开时，以这个为准。


//界面相关
LOGFONT FontForm;


BOOL GDIObjectCreate();
BOOL GDIObjectClean();



//记录日志相关
#define LOG_EVENT 1 //常规事件，比如软件启动之类的
#define LOG_PROTECT 2 //保护性异常，比如软件被关闭
#define LOG_ERROR 3 //软件内部错误

#define LOG_EVENT_START  1//软件正常启动
#define LOG_EVENT_END    2//软件正常结束
#define LOG_EVENT_LOGIN  3//用户登录，Comment是用户名
#define LOG_EVENT_LOGOUT 4//用户退出登录，Comment是用户名


#define LOG_PROTECT_MAIN_KILLED 1//主进程被结束
#define LOG_PROTECT_PROTECT_KILLED 2//保护进程被结束

#define LOG_ERROR_WEB 1//网络错误

BOOL WriteLog(int LogID, int Value, TCHAR Comment[]);

BOOL WriteLogA(int LogID, int Value, char Comment[]);








int StartCapture();



//包和URL记录相关
int InitRecord();
int RecordURL(char URL[]);

#define MAX_URL_NUM 2048
int URL_Num;
char * URL_Rec[MAX_URL_NUM];


