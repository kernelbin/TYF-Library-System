#include<windows.h>
#include "Global.h"



//下面是主数据操作函数。

BOOL MainDataLoad(BOOL CheckOnly)
{
	DWORD ErrorCode;
	hMainData = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, MainDataName);
	ErrorCode = GetLastError();
	if (hMainData)
	{
		//有数据
		if (CheckOnly)
		{
			CloseHandle(hMainData);
			hMainData = NULL;
			return TRUE;
		}
		else
		{
			return MainDataOpen();
		}
	}
	else
	{
		//加载失败
		if (ErrorCode == 2)//系统说，找不到指定文件。那么就是之前没有咯
		{
			return FALSE;
			//可以创建
		}
		else
		{
			//其他原因导致打不开。
			return FALSE;
		}
	}

}

BOOL MainDataOpen()
{
	if (pMainData)
	{
		return FALSE;
	}
	pMainData = MapViewOfFile(hMainData, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pMainData)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MainDataCreate()
{
	hMainData = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		sizeof(MAINDATASTRUCT),//数据区大小
		MainDataName);
	if (hMainData)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL MainDataDelete()
{
	if (pMainData)
	{
		UnmapViewOfFile(pMainData);
		pMainData = NULL;
	}
	if (hMainData)
	{
		CloseHandle(hMainData);
		hMainData = NULL;
		
	}

	return TRUE;
	
}

PMAINDATASTRUCT MakeMainDataStruct()
{
	return (PMAINDATASTRUCT)malloc(sizeof(MAINDATASTRUCT));
}
