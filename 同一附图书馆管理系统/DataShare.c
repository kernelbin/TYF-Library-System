#include<windows.h>
#include "Global.h"



//�����������ݲ���������

BOOL MainDataLoad(BOOL CheckOnly)
{
	DWORD ErrorCode;
	hMainData = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, MainDataName);
	ErrorCode = GetLastError();
	if (hMainData)
	{
		//������
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
		//����ʧ��
		if (ErrorCode == 2)//ϵͳ˵���Ҳ���ָ���ļ�����ô����֮ǰû�п�
		{
			return FALSE;
			//���Դ���
		}
		else
		{
			//����ԭ���´򲻿���
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
		sizeof(MAINDATASTRUCT),//��������С
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
