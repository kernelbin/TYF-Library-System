#include<windows.h>
#include<stdio.h>
#include <mysql.h> //包含MySQL所需要的头文件  
#include<process.h>

#include"Global.h"
//#include <WinSock.h>

char Server[] = "127.0.0.1";
char DataBaseUser[] = "root";
char DataBasePassword[] = "SQLPassword";
const char DataBase[] = "testonly";


BOOL IsOperating=FALSE;


BOOL BeginNetDataLoad()
{
	if (IsOperating)
	{
		//已有线程在刷新
		return FALSE;
	}
	IsOperating = TRUE;
	_beginthreadex(0,0,NetDataLoad,0 ,0, 0);
	
	return TRUE;
}


void __stdcall NetDataLoad(void * var)
{
	//测试连接SQL数据库

	MYSQL SQLConnect = { 0 };
	MYSQL_RES *Result = 0;
	MYSQL_ROW Row = 0;
	MYSQL_FIELD *Field = 0;
	int iCount = 0;
	int ListID, ListName, ListPassword, ListTimeLimit, ListAuthorityLevel, ListDelete;
	char sql[1024] = "select * from testonly.table_test;";

	int OldState;
	BOOL bSuccess = TRUE;
	

	__try
	{
		//无论成功与否，都记下来时间。
		pMainData->LoadTime = pMainData->RunningTime;

		//开始连接！
		OldState = pMainData->LoadState;
		pMainData->LoadState = LS_REFRESHING;
		NetLoadStateUpdate();

		mysql_init(&SQLConnect);

		if (!mysql_real_connect(&SQLConnect, Server, DataBaseUser, DataBasePassword, DataBase, 0, NULL, 0))
		{
			//出错，进入__finally模块
			bSuccess = FALSE;
			__leave;
		}

		if (mysql_set_character_set(&SQLConnect, "utf8"))
		{
			//出错，进入__finally模块
			bSuccess = FALSE;
			__leave;
		}

		//解决字符集乱码问题。为什么？？我也不知道hhhh，网上这么说的。
		//按照我的理解，设置utf8应该就够啦？
		mysql_query(&SQLConnect, "set names gbk");

		if (mysql_query(&SQLConnect, sql))
		{
			//出错，进入__finally模块
			bSuccess = FALSE;
			__leave;
		}

		Result = mysql_use_result(&SQLConnect);

		for (iCount = 0; Field = mysql_fetch_field(Result); iCount++)
		{
			//ListID = ListName = ListPassword = -1;
			if (strcmp(Field->name, "ID") == 0)
			{
				ListID = iCount;
			}
			if (strcmp(Field->name, "Name") == 0)
			{
				ListName = iCount;
			}
			if (strcmp(Field->name, "Password") == 0)
			{
				ListPassword = iCount;
			}
			if (strcmp(Field->name, "TimeLimit") == 0)
			{
				ListTimeLimit = iCount;
			}
			if (strcmp(Field->name, "AuthorityLevel") == 0)
			{
				ListAuthorityLevel = iCount;
			}
			if (strcmp(Field->name, "Delete") == 0)
			{
				ListDelete = iCount;
			}
		}

		//这里！继续！mysql_fetch_row读取数据分行判断！

		iCount = 0;


		while (((Row = mysql_fetch_row(Result)) != NULL) && (iCount < MAX_USER_COUNT - 1))//减一产生的空位是预留给本地管理员用户的
		{
			//例：ID信息存在row[ListID]中，以此类推。
			if (pMainData)
			{
				strcpy(pMainData->UsernameList[iCount], Row[ListName]);
				strcpy(pMainData->PasswordList[iCount], Row[ListPassword]);
				pMainData->TimeLimitList[iCount] = atoi(Row[ListTimeLimit]);
				pMainData->UserID[iCount] = atoi(Row[ListID]);
				pMainData->AuthorityLevelList[iCount] = atoi(Row[ListAuthorityLevel]);
				pMainData->DeleteList[iCount] = atoi(Row[ListDelete]);
			}
			iCount++;
		}

		//诶，加载成功！美滋滋！

	}
	__finally 
	{
		//执行退出
		if (Result)
		{
			mysql_free_result(Result);
		}
		//if (SQLConnect == 0) 这个初始化函数好像不怎么会出错
		//{
			mysql_close(&SQLConnect);
		//}
		
		if (!bSuccess)
		{
			//记录错误状态
			switch (OldState)
			{
			case LS_EMPTY:
			case LS_LOADFAILED:
				pMainData->LoadState = LS_LOADFAILED;
				break;
			case LS_LOADED:
			case LS_REFRESHFAILED:
				pMainData->LoadState = LS_REFRESHFAILED;
				break;
			}

			iCount = 0;//跳出if后接补齐本地管理员用户
			return;
		}
		else
		{
			pMainData->LoadState = LS_LOADED;

		}

		//添加本地管理员用户
		if (pMainData)
		{
			strcpy(pMainData->UsernameList[iCount], "本地管理员");
			strcpy(pMainData->PasswordList[iCount], "123456");
			pMainData->TimeLimitList[iCount] = -1;
			pMainData->UserID[iCount] = -1;
			pMainData->AuthorityLevelList[iCount] = 1;
			pMainData->DeleteList[iCount] = 0;
		}

		iCount++;

		pMainData->UserCount = iCount;

		NetLoadStateUpdate();
		IsOperating = FALSE;
	}
	return;

	
}


BOOL BeginNetDataUserDelete(int UserID)
{
	if (IsOperating)
	{
		//已有线程在刷新
		return FALSE;
	}
	IsOperating = TRUE;
	_beginthreadex(0, 0, NetDataUserDelete, pMainData->UserID[UserID], 0, 0);
	//_beginthread(NetDataUserDelete, 0, );
	return TRUE;
}


void __stdcall NetDataUserDelete(int UserID)
{
	MYSQL SQLConnect;
	MYSQL_RES *Result;
	MYSQL_ROW Row;
	MYSQL_FIELD *Field;

	char sql[1024];

	__try
	{
		mysql_init(&SQLConnect);

		if (!mysql_real_connect(&SQLConnect, Server, DataBaseUser, DataBasePassword, DataBase, 0, NULL, 0))
		{
			//出错
			__leave;
		}

		sprintf(sql, "DELETE FROM testonly.table_test WHERE ID=%d", UserID);

		if (mysql_query(&SQLConnect, sql)) 
		{
			//出错
			__leave;
		}
	}
	__finally
	{
		mysql_close(&SQLConnect);
		IsOperating = FALSE;
	}
	return;
	
}


void __stdcall LogoutDataRefresh()
{
	NetDataUserDelete(pMainData->UserID[pMainData->UserSelect]);
	NetDataLoad(0);
}
