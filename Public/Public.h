#pragma once
#include<Windows.h>

#define MainDataName TEXT("TYF_LIBSYS_MAIN_SHAREMEMORY")//主数据内存映射文件的内核对象名称

#define ReopenNoticeSemaName TEXT("TYF_LIBSYS_SEM_OPEN")//软件重复打开信号量的内核对象名称

#define DLLInjectModeDataName TEXT("TYF_LIBSYS_DLL_INJECT_MODE_SHAREMEMORY")//DLL 弹出/注入 标识 共享内存的内核对象名称

#define SetInjectDataMutexName TEXT("TYF_LIBSYS_DLL_SET_INJECT_DATA_MUTEX")//设置 写入DLL弹出/注入 标识时用于确保资源访问的互斥量名称

#define ReadDLLInjSemaName TEXT("TYF_LIBSYS_READ_DLL_INJ_SEMA_NAME")//读取 弹出注入数据读取完毕 信号量名称

#define StartInjEventName32 TEXT("TYF_LIBSYS_START_INJ_EVEVT_NAME32")//用于通知注入进程开始读取共享内存数据，并开始注入的事件 的名称
#define StartInjEventName64 TEXT("TYF_LIBSYS_START_INJ_EVEVT_NAME64")//用于通知注入进程开始读取共享内存数据，并开始注入的事件 的名称


#define FinDataLoadEventName TEXT("TYF_LIBSYS_FIN_DATALOAD_EVEVT_NAME")//用于通知主进程共享内存数据读取完毕的事件 的名称



typedef struct tagInjectDLLDataStruct
{
	int reserve;
} INJDLLDATASTRUCT, *PINJDLLDATASTRUCT;



//DLL注入/弹出标识
#define DLL_MODE_UNDEF 0
#define DLL_MODE_INJECT 1
#define DLL_MODE_EJECT 2
#define DLL_MODE_INJECT_SINGLE 3
#define DLL_MODE_INJECT_SINGLE_SUSPEND 4