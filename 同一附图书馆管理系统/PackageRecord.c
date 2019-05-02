#include<Windows.h>
#include"Global.h"
//我第一次尝试使用关键段
SRWLOCK SLock_Package;



int InitRecord()
{
	InitializeSRWLock(&SLock_Package);
	URL_Num = 0;
	return 0;
}
int RecordURL(char URL[])
{
	AcquireSRWLockExclusive(&SLock_Package);
	__try
	{
		if (URL_Num == MAX_URL_NUM)
		{
			__leave;
		}
		URL_Rec[URL_Num] = malloc(sizeof(char) * 512);
		strcpy_s(URL_Rec[URL_Num], 512, URL);

#if defined(UNICODE)
		//转换编码
		int Wide_Len;
		Wide_Len = MultiByteToWideChar(CP_ACP, 0, URL, strlen(URL), 0, 0);
		WCHAR *WideURLStr;
		WideURLStr = malloc((Wide_Len + 1) * sizeof(WCHAR));
		MultiByteToWideChar(CP_ACP, 0, URL, strlen(URL), WideURLStr, Wide_Len);
		WideURLStr[Wide_Len] = '\0';
		if (URLListShow)
		{
			EZSendMessage(URLListShow, EZWM_USER_NOTIFY, WideURLStr, 0);
		}
		free(WideURLStr);
#else
		EZSendMessage(URLListShow, EZWM_USER_NOTIFY, URL, 0);
#endif
		//转换编码
		//通知界面
		

		URL_Num++;
	}
	__finally
	{
		ReleaseSRWLockExclusive(&SLock_Package);
	}
	return 0;
}
int CleanRecord()
{
	AcquireSRWLockExclusive(&SLock_Package);
	__try
	{
		URL_Num--;
		for (; URL_Num >= 0; URL_Num--)
		{
			free(URL_Rec[URL_Num]);
		}
	}
	__finally
	{
		ReleaseSRWLockExclusive(&SLock_Package);
	}
	return 0;
}