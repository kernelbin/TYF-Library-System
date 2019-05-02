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
	u_int8_t ether_dhost[6]; //目的Mac地址   
	u_int8_t ether_shost[6]; //源Mac地址   
	u_int16_t ether_type;    //协议类型   
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
	short m_sSourPort;         // 源端口号16bit
	short m_sDestPort;         // 目的端口号16bit
	unsigned int m_uiSequNum;        // 序列号32bit
	unsigned int m_uiAcknowledgeNum;  // 确认号32bit
	//short m_sHeaderLenAndFlag;       // 前4位：TCP头长度；中6位：保留；后6位：标志位

	u_int8_t m_sHeaderLen;
	u_int8_t m_sFlag;

	short m_sWindowSize;        // 窗口大小16bit
	short m_sCheckSum;         // 检验和16bit
	short m_surgentPointer;       // 紧急数据偏移量16bit
};

void __stdcall CaptureData(pcap_t *ADHandle);


int StartCapture()
{
	pcap_if_t *AllDevices = 0, *EnumDevices = 0;
	char ErrBuf[PCAP_ERRBUF_SIZE];

	pcap_t *ADHandle;

	//初始化记录用（主要是初始化SRWLock）
	InitRecord();

	/* 获取本机设备列表 */

	__try
	{
		if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &AllDevices, ErrBuf) == -1)
		{
			//错误处理。
			WriteLogA(LOG_ERROR, LOG_ERROR_WEB, ErrBuf);
			__leave;
		}

		for (EnumDevices = AllDevices; EnumDevices; EnumDevices = EnumDevices->next)
		{
			if ((ADHandle = pcap_open(EnumDevices->name,          // 设备名
				MAX_PACKAGE_LEN,            // 要捕捉的数据包的部分 
								  // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
				PCAP_OPENFLAG_PROMISCUOUS,   // 混杂模式
				1000,             // 读取超时时间
				NULL,             // 远程机器验证
				ErrBuf            // 错误缓冲池
			)) == NULL)
			{
				sprintf_s(ErrBuf, PCAP_ERRBUF_SIZE, "\n由于 WinPcap 不支持，无法打开以下网络适配器：%s 。\n", EnumDevices->name);
				WriteLogA(LOG_ERROR, LOG_ERROR_WEB, ErrBuf);
			}
			else
			{
				//启动一个线程，传入ADHandle
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
			/* 超时时间到 */
			continue;
		}
		ethernet_protocol = (struct ether_header*)pkt_data;//获得数据包内容
		if (ntohs(ethernet_protocol->ether_type) != 0x0800)
		{
			//上层协议不是IP协议
			continue;
		}

		//MAC首部是14位的，加上14位得到IP协议首部 
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
					HttpInfo = ((BYTE *)TCP_Header) + ((TCP_Header->m_sHeaderLen & 0xF0) >> 2);//原本是向右12位，再乘4。就简化成向右10位了
																							   //检查是不是GET，POST开头
					char *pURL_Search, *pHost_Search;
					int SearchLen = 0;
					int bFindURL = 0;
					char URL_Buffer[512] = { 0 };
					char HostName[512] = { 0 };
					char FullURL[512] = { 0 };
					if (strnicmp(HttpInfo, "GET", 3) == 0)
					{
						//HTTP GET
						HttpInfo += 4;//讲道理，我觉得是GET还是POST貌似没啥用
						pURL_Search = HttpInfo;
						HTTPData_MaxLen -= 4;
					}
					else if (strnicmp(HttpInfo, "POST", 4) == 0)
					{
						//HTTP POST
						HttpInfo += 5;//讲道理，我觉得是GET还是POST貌似没啥用
						pURL_Search = HttpInfo;
						HTTPData_MaxLen -= 5;
					}
					else
					{
						//注意，现在还在最外层那个大的PCAP抓包的 while 循环之内。
						continue;//下一个包
					}

					for (SearchLen = 0; SearchLen < min(512, HTTPData_MaxLen); SearchLen++)
					{
						if ((*pURL_Search) == ' ')
						{
							//把这段复制到URL缓存里
							strncpy_s(URL_Buffer, 512, HttpInfo, min(HTTPData_MaxLen, SearchLen));
							HTTPData_MaxLen -= SearchLen + 1;
							pURL_Search++;
							pHost_Search = pURL_Search;
							break;//跳出for
						}
						pURL_Search++;
					}

					if (!(*URL_Buffer))
					{
						//没找到URL？
						continue;
					}

					//循环寻找\r\n，直到连续找到两个\r\n为止。
					int bHostHeadFinded = 0;
					int HostHeadStart = 0, HostHeadLen = 0;
					for (SearchLen = 0; SearchLen < min(1024, HTTPData_MaxLen); SearchLen++)
					{
						if (pHost_Search[0] == '\r' && pHost_Search[1] == '\n')
						{
							if (bHostHeadFinded)
							{
								//这里是结束点
								HostHeadLen = SearchLen - HostHeadStart;
								break;
							}
							if (pHost_Search[2] == '\r' && pHost_Search[3] == '\n')
							{
								//结束了
								break;
							}
							//看看是不是Host
							if (strnicmp(pHost_Search + 2, "Host", 4) == 0)
							{
								//是的！
								bHostHeadFinded = 1;
								HostHeadStart = SearchLen + 2;


							}
							pHost_Search++;//额外推进一个字节

							SearchLen++;
						}
						pHost_Search++;
					}


					if (HostHeadStart)
					{
						pHost_Search = pURL_Search + HostHeadStart;
						//找冒号，丢空格
						pHost_Search += 4;
						HostHeadLen -= 4;
						int bColonFinded = 0;
						for (;; )
						{
							if (*pHost_Search != ' ')//换言之，是空格就空循环
							{
								if (*pHost_Search == ':' && bColonFinded == 0)//第一个找到的冒号
								{
									bColonFinded = 1;
								}
								else
								{
									if (bColonFinded)
									{
										//主机名
										strncpy(HostName, pHost_Search, HostHeadLen);
										break;
									}
									else
									{
										//没冒号还有其他东西
										break;
									}
								}
							}
							pHost_Search++;
							HostHeadLen--;
						}

						if (!(*HostName))
						{
							//没找到URL？
							continue;
						}

						sprintf(FullURL, "%s%s", HostName, URL_Buffer);
						RecordURL(FullURL);
						//通过内核对象写入数据。
					}
				}



			}

			//这里解析TCP协议，看看是不是HTTP(S)
		}

	}

	if (res == -1) {
		char ErrBuf[PCAP_ERRBUF_SIZE];

		sprintf_s(ErrBuf, PCAP_ERRBUF_SIZE, "读取数据包出错: %s。", pcap_geterr(ADHandle));
		WriteLogA(LOG_ERROR, LOG_ERROR_WEB, ErrBuf);
		return -1;
	}
}

int EndCapture()
{
	//这里！改进,结束抓包线程
	CleanRecord();
	return 0;
}