#define  HAVE_REMOTE
#define WIN32
#include<pcap.h>
#include<windows.h>
#include<winsock2.h>
#include"Global.h"
#ifdef _X86_
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"Packet.lib")

#else
#pragma comment(lib,"wpcap64.lib")
#pragma comment(lib,"Packet64.lib")

#endif


#define MAX_PACKAGE_LEN 2048

struct ether_header
{
	u_int8_t ether_dhost[6]; //Ŀ��Mac��ַ   
	u_int8_t ether_shost[6]; //ԴMac��ַ   
	u_int16_t ether_type;    //Э������   
};


struct ip_header
{
#if defined(WORDS_BIENDIAN)   
	u_int8_t   ip_version : 4,
		ip_header_length : 4;
#else   
	u_int8_t   ip_header_length : 4,
		ip_version : 4;
#endif   
	u_int8_t    ip_tos;
	u_int16_t   ip_length;
	u_int16_t   ip_id;
	u_int16_t   ip_off;
	u_int8_t    ip_ttl;
	u_int8_t    ip_protocol;
	u_int16_t   ip_checksum;
	struct in_addr ip_souce_address;
	struct in_addr ip_destination_address;
};


struct tcp_header
{
	short m_sSourPort;         // Դ�˿ں�16bit
	short m_sDestPort;         // Ŀ�Ķ˿ں�16bit
	unsigned int m_uiSequNum;        // ���к�32bit
	unsigned int m_uiAcknowledgeNum;  // ȷ�Ϻ�32bit
	//short m_sHeaderLenAndFlag;       // ǰ4λ��TCPͷ���ȣ���6λ����������6λ����־λ

	u_int8_t m_sHeaderLen;
	u_int8_t m_sFlag;

	short m_sWindowSize;        // ���ڴ�С16bit
	short m_sCheckSum;         // �����16bit
	short m_surgentPointer;       // ��������ƫ����16bit
};

void __stdcall CaptureData(pcap_t *ADHandle);


int StartCapture()
{
	pcap_if_t *AllDevices = 0, *EnumDevices = 0;
	char ErrBuf[PCAP_ERRBUF_SIZE];

	pcap_t *ADHandle;

	//��ʼ����¼�ã���Ҫ�ǳ�ʼ��SRWLock��
	InitRecord();

	/* ��ȡ�����豸�б� */

	__try
	{
		if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &AllDevices, ErrBuf) == -1)
		{
			//������
			WriteLogA(LOG_ERROR, LOG_ERROR_WEB, ErrBuf);
			__leave;
		}

		for (EnumDevices = AllDevices; EnumDevices; EnumDevices = EnumDevices->next)
		{
			if ((ADHandle = pcap_open(EnumDevices->name,          // �豸��
				MAX_PACKAGE_LEN,            // Ҫ��׽�����ݰ��Ĳ��� 
								  // 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
				PCAP_OPENFLAG_PROMISCUOUS,   // ����ģʽ
				1000,             // ��ȡ��ʱʱ��
				NULL,             // Զ�̻�����֤
				ErrBuf            // ���󻺳��
			)) == NULL)
			{
				sprintf_s(ErrBuf, PCAP_ERRBUF_SIZE, "\n���� WinPcap ��֧�֣��޷�������������������%s ��\n", EnumDevices->name);
				WriteLogA(LOG_ERROR, LOG_ERROR_WEB, ErrBuf);
			}
			else
			{
				//����һ���̣߳�����ADHandle
				_beginthreadex(0, 0, CaptureData, ADHandle, 0, 0);
			}

		}
	}
	__finally
	{
		if (AllDevices)
		{
			pcap_freealldevs(AllDevices);
		}
	}


	return 0;
}

void __stdcall CaptureData(pcap_t *ADHandle)
{
	int res;
	const u_char *pkt_data;
	struct pcap_pkthdr *header;
	struct ether_header *ethernet_protocol;



	while ((res = pcap_next_ex(ADHandle, &header, &pkt_data)) >= 0)
	{

		if (res == 0)
		{
			/* ��ʱʱ�䵽 */
			continue;
		}
		ethernet_protocol = (struct ether_header*)pkt_data;//������ݰ�����
		if (ntohs(ethernet_protocol->ether_type) != 0x0800)
		{
			//�ϲ�Э�鲻��IPЭ��
			continue;
		}

		//MAC�ײ���14λ�ģ�����14λ�õ�IPЭ���ײ� 
		struct ip_header *IP_Header;
		IP_Header = pkt_data + 14;

		if (IP_Header->ip_protocol == 6)
		{
			struct tcp_header *TCP_Header;
			int IPData_MaxLen = min(IP_Header->ip_length, MAX_PACKAGE_LEN - 14);//
			int TCPData_MaxLen = IPData_MaxLen - (IP_Header->ip_header_length << 2);
			TCP_Header = (BYTE*)IP_Header + (IP_Header->ip_header_length << 2);

			u_int8_t LenMask;
			if (ntohs(TCP_Header->m_sDestPort) == 80)
			{
				char *HttpInfo;
				if (TCP_Header->m_sFlag == 24)
				{
					int HTTPData_MaxLen = TCPData_MaxLen - ((TCP_Header->m_sHeaderLen & 0xF0) >> 2);
					HttpInfo = ((BYTE *)TCP_Header) + ((TCP_Header->m_sHeaderLen & 0xF0) >> 2);//ԭ��������12λ���ٳ�4���ͼ򻯳�����10λ��
																							   //����ǲ���GET��POST��ͷ
					char *pURL_Search, *pHost_Search;
					int SearchLen = 0;
					int bFindURL = 0;
					char URL_Buffer[512] = { 0 };
					char HostName[512] = { 0 };
					char FullURL[512] = { 0 };
					if (strnicmp(HttpInfo, "GET", 3) == 0)
					{
						//HTTP GET
						HttpInfo += 4;//�������Ҿ�����GET����POSTò��ûɶ��
						pURL_Search = HttpInfo;
						HTTPData_MaxLen -= 4;
					}
					else if (strnicmp(HttpInfo, "POST", 4) == 0)
					{
						//HTTP POST
						HttpInfo += 5;//�������Ҿ�����GET����POSTò��ûɶ��
						pURL_Search = HttpInfo;
						HTTPData_MaxLen -= 5;
					}
					else
					{
						//ע�⣬���ڻ���������Ǹ����PCAPץ���� while ѭ��֮�ڡ�
						continue;//��һ����
					}

					for (SearchLen = 0; SearchLen < min(512, HTTPData_MaxLen); SearchLen++)
					{
						if ((*pURL_Search) == ' ')
						{
							//����θ��Ƶ�URL������
							strncpy_s(URL_Buffer, 512, HttpInfo, min(HTTPData_MaxLen, SearchLen));
							HTTPData_MaxLen -= SearchLen + 1;
							pURL_Search++;
							pHost_Search = pURL_Search;
							break;//����for
						}
						pURL_Search++;
					}

					if (!(*URL_Buffer))
					{
						//û�ҵ�URL��
						continue;
					}

					//ѭ��Ѱ��\r\n��ֱ�������ҵ�����\r\nΪֹ��
					int bHostHeadFinded = 0;
					int HostHeadStart = 0, HostHeadLen = 0;
					for (SearchLen = 0; SearchLen < min(1024, HTTPData_MaxLen); SearchLen++)
					{
						if (pHost_Search[0] == '\r' && pHost_Search[1] == '\n')
						{
							if (bHostHeadFinded)
							{
								//�����ǽ�����
								HostHeadLen = SearchLen - HostHeadStart;
								break;
							}
							if (pHost_Search[2] == '\r' && pHost_Search[3] == '\n')
							{
								//������
								break;
							}
							//�����ǲ���Host
							if (strnicmp(pHost_Search + 2, "Host", 4) == 0)
							{
								//�ǵģ�
								bHostHeadFinded = 1;
								HostHeadStart = SearchLen + 2;


							}
							pHost_Search++;//�����ƽ�һ���ֽ�

							SearchLen++;
						}
						pHost_Search++;
					}


					if (HostHeadStart)
					{
						pHost_Search = pURL_Search + HostHeadStart;
						//��ð�ţ����ո�
						pHost_Search += 4;
						HostHeadLen -= 4;
						int bColonFinded = 0;
						for (;; )
						{
							if (*pHost_Search != ' ')//����֮���ǿո�Ϳ�ѭ��
							{
								if (*pHost_Search == ':' && bColonFinded == 0)//��һ���ҵ���ð��
								{
									bColonFinded = 1;
								}
								else
								{
									if (bColonFinded)
									{
										//������
										strncpy(HostName, pHost_Search, HostHeadLen);
										break;
									}
									else
									{
										//ûð�Ż�����������
										break;
									}
								}
							}
							pHost_Search++;
							HostHeadLen--;
						}

						if (!(*HostName))
						{
							//û�ҵ�URL��
							continue;
						}

						sprintf(FullURL, "%s%s", HostName, URL_Buffer);
						RecordURL(FullURL);
						//ͨ���ں˶���д�����ݡ�
					}
				}



			}

			//�������TCPЭ�飬�����ǲ���HTTP(S)
		}

	}

	if (res == -1) {
		char ErrBuf[PCAP_ERRBUF_SIZE];

		sprintf_s(ErrBuf, PCAP_ERRBUF_SIZE, "��ȡ���ݰ�����: %s��", pcap_geterr(ADHandle));
		WriteLogA(LOG_ERROR, LOG_ERROR_WEB, ErrBuf);
		return -1;
	}
}

int EndCapture()
{
	//����Ľ�,����ץ���߳�
	CleanRecord();
	return 0;
}