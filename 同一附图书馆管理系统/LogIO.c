
#include<Windows.h>
#include"Global.h"


BOOL WriteLog(int LogID,int Value,TCHAR Comment[])
{
	char Buffer[512];
	WideCharToMultiByte(CP_UTF8, 0, Comment, -1, Buffer, 512, NULL, NULL);
	WriteLogA(LogID, Value, Buffer);
	return 0;
}


BOOL WriteLogA(int LogID, int Value, char Comment[])
{
	HFILE hFile;
	int iFileLength;
	PBYTE  pBuffer;
	DWORD  dwBytesRead;
	char ModuleName[128], DriveName[128], DirName[128], FileName[128], ExtName[128];
	char LogName[128];
	char LogText[256];


	//��־

	SYSTEMTIME st;
	GetLocalTime(&st);//�õ�����ʱ��
	sprintf(LogText, "%04d-%02d-%02d %02d:%02d:%02d ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	switch (LogID)
	{
	case LOG_EVENT:
		if (Value == LOG_EVENT_START)
		{
			sprintf(LogText,"%s ͬһ��ͼ��ݹ���������� %s\r\n", LogText, Comment);
		}
		else if (Value == LOG_EVENT_END)
		{
			sprintf(LogText,"%s ͬһ��ͼ��ݹ�������ر� %s\r\n", LogText, Comment);
		}
		else if (Value == LOG_EVENT_LOGIN)
		{
			sprintf(LogText,"%s �û� %s ��¼\r\n", LogText, Comment);
		}
		else if (Value == LOG_EVENT_LOGOUT)
		{
			sprintf(LogText,"%s �û� %s �˳�\r\n", LogText, Comment);
		}

		break;
	case LOG_PROTECT:

		if (Value == LOG_PROTECT_MAIN_KILLED)
		{
			sprintf(LogText, "%s �����̱��쳣��ֹ�����Ѿ��������� %s\r\n", LogText, Comment);
		}
		else if (Value == LOG_PROTECT_PROTECT_KILLED)
		{
			sprintf(LogText, "%s �������̱��쳣��ֹ�����Ѿ��������� %s\r\n", LogText, Comment);
		}
		else
		{

		}

		break;
	case LOG_ERROR:
	{
		char ErrName[2][32] =
		{
			"",
			"����"
		};
		sprintf(LogText, "%s ����Ԥ��֮��%s�Ĵ��� %s\r\n", LogText, ErrName[Value], Comment);
		break;
	}
		
	}

	GetModuleFileNameA(NULL, ModuleName, 128);


	_splitpath_s(ModuleName, DriveName, 128, DirName, 128, FileName, 128, ExtName, 128);


	sprintf(LogName, "%s%sLog\\Log.txt", DriveName, DirName);



	if (INVALID_HANDLE_VALUE ==
		(hFile = CreateFileA(LogName, GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, 0, NULL)))
	{
		return FALSE;
	}


	SetFilePointer(hFile, NULL, NULL, FILE_END);

	DWORD Written;
	WriteFile(hFile, LogText, strlen(LogText), &Written, NULL);

	CloseHandle(hFile);
	return TRUE;
}


