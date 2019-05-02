#pragma once
#include<Windows.h>

#define MainDataName TEXT("TYF_LIBSYS_MAIN_SHAREMEMORY")//�������ڴ�ӳ���ļ����ں˶�������

#define ReopenNoticeSemaName TEXT("TYF_LIBSYS_SEM_OPEN")//����ظ����ź������ں˶�������

#define DLLInjectModeDataName TEXT("TYF_LIBSYS_DLL_INJECT_MODE_SHAREMEMORY")//DLL ����/ע�� ��ʶ �����ڴ���ں˶�������

#define SetInjectDataMutexName TEXT("TYF_LIBSYS_DLL_SET_INJECT_DATA_MUTEX")//���� д��DLL����/ע�� ��ʶʱ����ȷ����Դ���ʵĻ���������

#define ReadDLLInjSemaName TEXT("TYF_LIBSYS_READ_DLL_INJ_SEMA_NAME")//��ȡ ����ע�����ݶ�ȡ��� �ź�������

#define StartInjEventName32 TEXT("TYF_LIBSYS_START_INJ_EVEVT_NAME32")//����֪ͨע����̿�ʼ��ȡ�����ڴ����ݣ�����ʼע����¼� ������
#define StartInjEventName64 TEXT("TYF_LIBSYS_START_INJ_EVEVT_NAME64")//����֪ͨע����̿�ʼ��ȡ�����ڴ����ݣ�����ʼע����¼� ������


#define FinDataLoadEventName TEXT("TYF_LIBSYS_FIN_DATALOAD_EVEVT_NAME")//����֪ͨ�����̹����ڴ����ݶ�ȡ��ϵ��¼� ������



typedef struct tagInjectDLLDataStruct
{
	int reserve;
} INJDLLDATASTRUCT, *PINJDLLDATASTRUCT;



//DLLע��/������ʶ
#define DLL_MODE_UNDEF 0
#define DLL_MODE_INJECT 1
#define DLL_MODE_EJECT 2
#define DLL_MODE_INJECT_SINGLE 3
#define DLL_MODE_INJECT_SINGLE_SUSPEND 4