// CustomID.h: interface for the CCustomID class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMID_H__E1D9CABA_BE37_4202_9BDA_E84B7CFC4C5E__INCLUDED_)
#define AFX_CUSTOMID_H__E1D9CABA_BE37_4202_9BDA_E84B7CFC4C5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
//						客户ID                                             //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Demo
#define CUST_ID_DEMO				3
#define CUST_NAME_DEMO 				0x1a,0x07,0x97,0xc4,0xde,0x5a,0x2e,0x3d,0xd6,0xf0,0x60,0x67,0x83,0xcd,0x40,0xcc
// 01 E7 D6 DB 15 ED D3 30    AA B2 89 F6 4A 2A 1C 4A
// 98 96 8E 01 AD 02 41 2D    3F A0 DA CC BC EE AE A5
// 79 24 52 43 2D 42 AC E5    AE 41 03 01

/////////////////////////////////////////////////////////////////////////////
// Foxconn(CMMSG)
#define	CUST_ID_FOXCONN_CMMSG		4	// 富士康CMMSG(GT)
#define CUST_NAME_FOXCONN_CMMSG		0x2e,0x9a,0x85,0x09,0x56,0x59,0xff,0xe8,0xba,0xbd,0x08,0x9e,0x5d,0x69,0x8f,0x67
// 02 8B AC A1 8E 9F 04 55    48 E6 57 A5 90 11 17 65
// 46 5B 51 C3 AF 03 3C EE    99 69 CC 5E ED 36 30 AF
// D2 12 DB 96 D1 95 17 1D    D5 23 04 01

/////////////////////////////////////////////////////////////////////////////
// Multek
#define CUST_ID_MULTEK			    5  // 超毅
#define CUST_NAME_MULTEK			0x72,0xdb,0x16,0xf6,0xbf,0xa9,0x5d,0x53,0x19,0xf6,0xec,0x9f,0x27,0xcc,0x0c,0x93
// 01 4F C0 A2 60 75 98 64    5E E8 86 63 E7 F6 8A 04
// 2E 4B 05 CD 9D 00 A6 EF    DF 5C 3C 32 EB B3 39 15
// 90 A6 6D 62 1F 80 A9 52    D8 36 05 01

/////////////////////////////////////////////////////////////////////////////
// EleceltekGZ
#define CUST_ID_ELECELTEK_GZ	    6  // 广州依利
#define CUST_NAME_ELECELTEK_GZ		0x11,0xa0,0xa7,0x47,0x50,0x9b,0x90,0x24,0x47,0x25,0xe4,0xcb,0x84,0x39,0xcd,0xac
// 01 AB F2 6A BC AA 81 57    9E F7 CA A4 1E F3 77 4D
// 53 E9 BF 66 4C 03 A6 28    29 FB 73 86 20 2B A2 C2
// 8E 83 4B 5B 57 55 79 2A    9E 47 06 01

/////////////////////////////////////////////////////////////////////////////
// EleceltekNJ
#define CUST_ID_ELECELTEK_NJ	    7  // 南京依利
#define CUST_NAME_ELECELTEK_NJ		0xbe,0xa6,0x1d,0xbd,0xa3,0x7b,0x90,0x0f,0x4e,0x6e,0x0b,0x2c,0xd6,0xc2,0xfb,0xcd
// 03 41 22 C6 8D 64 E9 62    8F FE 16 4A 99 8C A5 19
// C5 CD E6 51 C0 02 F1 7A    08 24 3E 73 8E A6 EE 45
// 0E 43 8A 27 CA 9B BB 65    03 38 07 01

/////////////////////////////////////////////////////////////////////////////
// KuaiJie
#define CUST_ID_KUAI_JIE		    8  // 快捷
#define CUST_NAME_KUAI_JIE			0x6c,0x9f,0x40,0x01,0xc5,0xc9,0xdd,0x87,0xfe,0x2c,0x7f,0x10,0x3c,0x08,0xff,0xcf
// 01 E1 12 17 34 F3 18 1E    24 69 60 6E FC E7 35 A5
// 89 22 50 D8 9E 02 A5 BA    8A DA 65 30 9C DF B2 79
// 6B B9 43 FE E2 A4 C6 3C    D7 35 08 01

/////////////////////////////////////////////////////////////////////////////
// ChuanYi
#define CUST_ID_CHUAN_YI		    9  // 川亿
#define CUST_NAME_CHUAN_YI			0x82,0xf6,0x5f,0x1a,0x76,0x55,0xd9,0x0b,0x02,0x6e,0x74,0x9a,0xf3,0x45,0x62,0x95
// 01 5D CE 93 01 EA 7F BF    55 43 4A 3E AC 6B C8 13
// 4B D3 23 2D E6 03 BA D8    C4 47 D2 DC 27 72 10 08
// CF 5D 2D B2 AC F2 86 B1    29 EA 09 01

/////////////////////////////////////////////////////////////////////////////
// JinXiang
#define CUST_ID_JIN_XIANG		    11  // 金相
#define CUST_NAME_JIN_XIANG			0xaf,0xd8,0x70,0xca,0x92,0xad,0xd9,0x42,0x72,0x30,0x67,0xb8,0xa5,0xe4,0x5b,0x3c
// 03 79 0F 78 5B 14 5E 1F    F2 87 08 1A 51 7F 71 3F
// 99 B2 B9 3A AA 03 AD A1    0B EF 13 A0 8C 5F 5C DC
// 36 1D E1 3D 0B D4 C6 E1    50 1A 0B 01

/////////////////////////////////////////////////////////////////////////////
// JingWang
#define CUST_ID_JING_WANG		    12  // 景旺
#define CUST_NAME_JING_WANG			0x67,0x1e,0x64,0x47,0x40,0xa5,0x62,0xb9,0x85,0x3a,0x61,0x51,0xd3,0xe3,0x9c,0x31
// 00 34 B5 AD 48 5C 73 EA    23 2B A2 7B 75 A4 94 E8
// 7B 76 17 E3 45 00 4B A5    82 81 A8 11 67 43 C7 CF
// 8C 03 FE 65 7A 14 2C 07    AF F9 0C 01

/////////////////////////////////////////////////////////////////////////////
// ZhongFu
#define CUST_ID_ZHONG_FU		    14  // 中富
#define CUST_NAME_ZHONG_FU			0xaf,0x2e,0xdd,0x1a,0xf5,0xcf,0xce,0xfd,0x26,0xb2,0x12,0x0c,0x0e,0x72,0x6e,0x35
// 03 AD 4C 3D 02 08 D1 1F    D6 09 F4 C7 55 BB 8F CD
// F6 E7 2A 00 B9 00 E9 AB    70 9B 7F 07 7A F7 42 5D
// FA 52 FA D7 B8 C2 F5 F8    F0 A2 0D 01

/////////////////////////////////////////////////////////////////////////////
// ShenNan
#define CUST_ID_SHEN_NAN		    15  // 深南
#define CUST_NAME_SHEN_NAN			0xff,0x06,0x02,0x5a,0x57,0x7c,0x84,0x1a,0xab,0x0c,0x8c,0x5e,0x7f,0x6c,0x07,0x22
// 00 01 3D 4A 48 2F 31 66    22 41 41 8B 7B CF 3E 09
// B2 F9 E1 4A CE 01 E2 81    CF 23 30 FA DE 33 86 5E
// 66 AF 7A FB B1 57 6E 49    B4 78 0F 01

/////////////////////////////////////////////////////////////////////////////
// RedBoard
#define CUST_ID_RED_BOARD		    16  // 红板
#define CUST_NAME_RED_BOARD			0x8d,0x0f,0xb0,0xa5,0x85,0x25,0xf2,0x61,0xd1,0xa4,0xc6,0x5c,0x31,0x48,0x1b,0x0d
// 00 9F 92 C6 91 46 23 79    A6 92 91 B9 52 50 CB BE
// 83 2C C4 57 61 02 C3 2F    08 AE 92 1A 9A E8 A5 40
// 56 89 7A 13 1B 6B 7D F4    F9 FB 10 01

/////////////////////////////////////////////////////////////////////////////
// EleceltekKS
#define CUST_ID_ELECELTEK_KS	    17  // 昆山依利
#define CUST_NAME_ELECELTEK_KS		0x82,0x7f,0x35,0x6c,0x33,0x83,0xc3,0x79,0xe8,0x4e,0x99,0x69,0x4c,0x09,0x94,0x74
// 02 E2 16 DB 9E FC CB 4F    DA C4 7E 3D 9A C5 32 6F
// 16 6D FE C3 A8 03 47 8C    CE 98 FC A6 02 0C F0 47
// F5 9E 60 CA AF 0F AD FC    F6 D3 11 01

/////////////////////////////////////////////////////////////////////////////
// WuZhou
#define CUST_ID_WU_ZHOU			    18  // 五洲
#define CUST_NAME_WU_ZHOU			0x14,0x42,0x14,0xbe,0xb5,0xce,0xf8,0x2d,0x0d,0xf9,0x4e,0x11,0xda,0x55,0x6e,0x8e
// 01 5C D4 97 FB 08 70 18    B3 34 81 8E 8B A3 C8 66
// EF 1B 75 38 A8 03 74 60    C5 7D 99 F0 55 11 E2 0F
// B2 78 15 FE 0E CB 97 E3    CA 5F 12 01

/////////////////////////////////////////////////////////////////////////////
// Topsearch
#define CUST_ID_TOPSEARCH		    19  // 至卓
#define CUST_NAME_TOPSEARCH			0xc4,0x1d,0x6a,0x47,0x3c,0xa8,0xc1,0x8a,0xd1,0x63,0x6a,0x62,0xbd,0x78,0x2e,0x92
// 00 57 0E 97 7B 99 F3 3F    B6 31 6B D7 30 B8 5F 43
// 32 4E 96 52 07 03 1E AE    0B 9B D4 5E F7 CF D9 16
// 3F E8 7D 90 84 A7 C9 74    24 3D 13 01

/////////////////////////////////////////////////////////////////////////////
// KoreaDemo
#define CUST_ID_KOREA_DEMO		    20  // 韩国Demo
#define CUST_NAME_KOREA_DEMO		0x8c,0xa8,0x26,0xbd,0xa7,0x28,0xcf,0xb1,0x37,0x16,0xc0,0x03,0x4e,0x88,0xff,0xec
// 00 8E 8B 46 5D 6B 16 94    FD 53 6F 98 83 2D 81 F3
// EF F2 33 19 C9 00 7D CC    90 79 4F 20 5A 7B 8A 4C
// 51 1D 51 AB BB 7F 07 2E    6B A1 14 01

/////////////////////////////////////////////////////////////////////////////
// HuaTong
#define CUST_ID_HUA_TONG		    21  // 华通
#define CUST_NAME_HUA_TONG			0xef,0xa9,0xcc,0x8e,0x56,0x4f,0xaf,0x3c,0x15,0xe5,0xe1,0x71,0xe7,0x19,0x9d,0x11
// 02 0C AE 9E 8B 7B 5A D0    6F CE F7 A5 A8 D0 BA 36
// C2 23 CA 6F 42 00 04 52    94 F5 89 15 47 21 A4 17
// DA 5E B7 5D 02 8E F1 26    F2 1F 15 01

/////////////////////////////////////////////////////////////////////////////
// ViasystemZS
#define CUST_ID_VIASYSTEM_ZS	    22  // 中山惠亚
#define CUST_NAME_VIASYSTEM_ZS		0x04,0xd8,0x59,0xf6,0x0c,0xc5,0x5b,0x19,0xd0,0xc0,0xad,0x35,0x3f,0xca,0xe5,0x02
// 01 1B 85 1F B7 48 F4 26    20 B0 29 19 3C 76 7F D4
// 42 D6 FD D7 53 00 28 C8    FE D2 0B 3D 2E 70 17 EF
// 12 DA 0C 1D F7 BC 04 BA    4E D9 16 01

/////////////////////////////////////////////////////////////////////////////
// YueHu
#define CUST_ID_YUE_HU			    23  // 跃虎
#define CUST_NAME_YUE_HU			0x60,0x53,0x25,0xb6,0x5e,0x5c,0xdd,0xbe,0xc1,0x8e,0xb3,0x13,0x8d,0xb4,0x6b,0xdd
// 03 8B 7B C8 E2 D3 1F D0    8D 39 75 C7 68 4E 72 27
// F7 97 6B 0C 01 02 A5 A8    10 3D CB 5A 02 53 BC DB
// CC 9C 7D A7 13 FE D8 FD    EF B5 17 01

/////////////////////////////////////////////////////////////////////////////
// HuShi
#define CUST_ID_HU_SHI			    24  // 护士
#define CUST_NAME_HU_SHI			0x07,0x8f,0x57,0xa3,0x64,0x58,0x68,0x1a,0x54,0x69,0xf7,0xe9,0x2d,0x35,0x86,0x0c
// 03 8D 8D 74 54 6A 61 2B    BD 87 03 17 C4 C3 A9 40
// 05 D3 9E 67 C1 03 82 E7    C1 B3 2F F1 F4 BB A0 C0
// DE D1 AD CB 43 58 2E E0    DF 30 18 01

/////////////////////////////////////////////////////////////////////////////
// JingCheng
#define CUST_ID_JING_CHENG		    25  // 精诚
#define CUST_NAME_JING_CHENG		0x37,0xe8,0x6b,0xdf,0x76,0x49,0x73,0x4f,0xd8,0x3a,0xcf,0x0b,0x51,0x55,0x04,0xf3
// 02 93 F9 55 CC 47 2C 2B    CC CD 8F 3E DE E5 B9 DD
// 68 AF A4 55 31 02 56 B3    96 D6 FF 3B 50 94 AF DB
// E8 E3 1B 77 24 63 2B E9    1D 2B 19 01

/////////////////////////////////////////////////////////////////////////////
// YiJie
#define CUST_ID_YI_JIE			    26  // 宜捷
#define CUST_NAME_YI_JIE			0x12,0x5a,0x12,0x6e,0xc0,0xf7,0x95,0x80,0x6e,0x5d,0xb5,0xa9,0xc4,0x27,0x6b,0x58
// 00 47 B7 80 50 BA 8A 6C    CF D2 3C EF B7 78 BC 49
// 92 85 DD 41 C5 02 88 E1    04 0E DD 0C BC 70 8A DC
// 88 96 6E F6 67 95 44 89    EE 96 1A 01

/////////////////////////////////////////////////////////////////////////////
// JianYe
#define CUST_ID_JIAN_YE			    27  // 建业
#define CUST_NAME_JIAN_YE			0x21,0xa1,0x3d,0x68,0x11,0xf8,0x35,0xc1,0x1d,0x0b,0x29,0x5e,0x40,0xff,0xc0,0xc2
// 03 82 D5 39 A8 52 7C 7A    BC 54 1E 34 AA 8D 92 AE
// 6C 37 AC 27 1C 01 1C D2    F3 80 11 97 0C 60 33 BB
// 8B E6 99 9A D1 52 46 97    D2 6E 1B 01

/////////////////////////////////////////////////////////////////////////////
// QingQiang
#define CUST_ID_QING_QIANG		    28  // 欣强
#define CUST_NAME_QING_QIANG		0x8b,0x41,0x4f,0x60,0x33,0x08,0xb8,0x94,0x59,0x3b,0x6c,0x5a,0x77,0xd4,0x60,0x99
// 00 F6 A9 7C 67 F6 DB 67    EF 30 7B A1 F3 8F 53 4A
// DB 19 1F 0B 78 02 43 BA    74 A5 18 1F BD A8 5F 33
// FB 4E 0C 88 88 A8 A9 4A    D5 7C 1C 01

/////////////////////////////////////////////////////////////////////////////
// AoShiKang
#define CUST_ID_AO_SHI_KANG		    29  // 奥士康
#define CUST_NAME_AO_SHI_KANG		0xdd,0x40,0x23,0x7d,0xb7,0xd7,0xae,0x40,0x36,0x90,0x09,0xcf,0x99,0x33,0x1b,0x93
// 03 1E CD 0C 34 D0 54 02    55 F6 B3 DB CC FC 85 23
// 73 DD 9C 98 83 03 5B 1C    34 75 30 87 C7 FE 8B E0
// C4 08 2B 55 38 68 85 70    4F 87 1D 01

/////////////////////////////////////////////////////////////////////////////
// FuChangFa
#define CUST_ID_FU_CHANG_FA		    30  // 福昌发
#define CUST_NAME_FU_CHANG_FA		0x9e,0xcc,0x0d,0xa6,0x7b,0x9f,0xfa,0x8a,0xa5,0x4e,0x8c,0xe7,0xc3,0x53,0x0a,0xa2
// 03 5D C4 06 66 9A 57 17    61 B3 37 A3 9B C3 1D 37
// 4E 1C 13 77 D8 01 53 C8    E1 C2 FA 23 04 23 CC A6
// 01 89 A5 68 53 DD 18 50    3D A7 1E 01

/////////////////////////////////////////////////////////////////////////////
// BoMin
#define CUST_ID_BO_MIN			    31  // 博敏
#define CUST_NAME_BO_MIN			0x23,0x05,0x87,0x2d,0x00,0xda,0x8d,0xe9,0xec,0x14,0xe7,0x6d,0x1b,0xeb,0x44,0xe2
// 01 06 CB B9 74 2C 52 D3    A8 01 FB 34 35 BF 30 7D
// 19 9B 9D A7 E7 01 8A 11    62 40 D5 1A 7F 5E 61 A8
// 74 FE 7D A0 78 1D E6 94    C9 E8 1F 01

/////////////////////////////////////////////////////////////////////////////
// ViasystemGZ
#define CUST_ID_VIASYSTEM_GZ	    32  // 广州惠亚
#define CUST_NAME_VIASYSTEM_GZ		0xa0,0x54,0xe4,0x03,0x34,0xcc,0x5b,0x55,0x3f,0x7f,0x06,0x74,0x0b,0x3f,0x59,0xd9
// 03 74 2B F6 DB 3F 3F 2D    E5 B3 DE 75 F1 7D F7 9A
// 33 D4 8A 71 B4 03 26 5A    26 E2 D2 7C 6A 80 38 0B
// 4B 13 FE 57 C7 04 52 C7    BF 6C 20 01

/////////////////////////////////////////////////////////////////////////////
// ChongDa
#define CUST_ID_CHONG_DA		    33  // 崇达
#define CUST_NAME_CHONG_DA			0x7a,0x7f,0x3f,0x5f,0x1f,0xa1,0xf7,0xb6,0x82,0x2d,0xb8,0x32,0xad,0x0e,0x3f,0x70
// 01 A1 18 BF 45 26 BC 83    5B 15 F4 EA 9E CE A4 25
// 25 48 D4 A6 4B 01 90 E2    D0 EE 73 08 5F A4 AC 96
// 1C DC 50 C4 1C FF 42 82    99 82 21 01

/////////////////////////////////////////////////////////////////////////////
// EleceltekHK
#define CUST_ID_ELECELTEK_HK	    34  // 香港依利
#define CUST_NAME_ELECELTEK_HK		0x1a,0x3a,0xd0,0x71,0x42,0x67,0xf3,0x8d,0x56,0x3b,0x1e,0x81,0xa8,0x51,0xa2,0xf4
// 01 E4 83 58 1E 7C 1A 7F    4F D8 B4 E6 8A 93 CA 11
// 71 A3 F5 98 04 00 F8 C0    FD 94 44 52 0C 50 47 EE
// DC 77 2E D3 5B BE 4F 81    B3 8D 22 01

/////////////////////////////////////////////////////////////////////////////
// Meiko
#define CUST_ID_MEIKO			    35  // 名幸电子
#define CUST_NAME_MEIKO				0xdd,0x1a,0xf9,0x2e,0xe1,0xb3,0xa9,0x4b,0x33,0xa7,0x2f,0x99,0xe5,0xcc,0x86,0xad
// 03 CF 6F DD 7D 64 81 8D    01 E4 6D B2 94 78 98 EA
// 95 0F C5 2A 75 03 48 59    D8 B6 8E 40 16 92 AE FB
// BC 8A 6B B8 2C 3C E3 A8    23 05 23 01

/////////////////////////////////////////////////////////////////////////////
// DongYang
#define CUST_ID_DONG_YANG		    36  // 东阳
#define CUST_NAME_DONG_YANG			0x5c,0x4a,0xe2,0x3c,0xfd,0x9d,0xb6,0xd9,0x96,0x94,0x89,0x97,0x9f,0x7c,0x77,0xde
// 02 66 3D 2C 5A 66 C9 6F    F5 A7 72 6B 1F 50 EA BE
// BD 22 37 92 73 00 9B B1    79 3C 86 C5 96 3C 95 24
// 7F A7 0B 25 13 CC 2F 7F    1C 48 24 01

/////////////////////////////////////////////////////////////////////////////
// JinLu
#define CUST_ID_JIN_LU			    37  // 精路
#define CUST_NAME_JIN_LU			0x0e,0xda,0x4c,0xd2,0xdf,0x47,0x17,0x15,0x3a,0xc6,0x1f,0x47,0x5c,0x8b,0x17,0xad
// 01 43 04 4A 6F D5 1E 44    BE F6 CA F6 25 21 67 AD
// DF 69 F7 9A 27 03 A3 74    C4 EE ED 31 75 F3 53 8D
// 0C 49 51 78 5F 6B F6 24    93 DE 25 01

/////////////////////////////////////////////////////////////////////////////
// KunYing
#define CUST_ID_KUN_YING		    38  // 昆颖
#define CUST_NAME_KUN_YING			0x68,0x49,0x8e,0x63,0x7a,0xb6,0x25,0xaa,0x7f,0xc3,0xdf,0xb4,0x0d,0x32,0xdc,0x0b
// 03 F9 95 9B 92 13 78 08    BB 6C 93 2A 14 2B DC 5D
// B2 57 85 03 A8 00 34 81    75 F1 4C 53 D8 B8 B5 62
// 7F 40 D2 56 82 A0 BA 31    21 90 26 01

/////////////////////////////////////////////////////////////////////////////
// GuangYuan
#define CUST_ID_GUANG_YUAN		    39  // 广元
#define CUST_NAME_GUANG_YUAN		0x21,0x92,0x36,0x2e,0x4a,0xbf,0xd2,0xb0,0xc2,0x2f,0xb3,0x42,0x7f,0xdf,0x72,0x46
// 02 CC FC 8E 16 95 C7 1E    5B 9A 8E 43 8B E7 E3 18
// 41 C9 24 54 A0 00 B4 04    42 60 78 CD F7 24 07 1A
// 8C B4 6E 69 E5 49 DD 65    9E 9D 27 01

/////////////////////////////////////////////////////////////////////////////
// RongXin
#define CUST_ID_RONG_XIN		    40  // 荣信
#define CUST_NAME_RONG_XIN			0x02,0x93,0x2e,0x7f,0x2e,0x6b,0x18,0x26,0xc6,0xc7,0x9c,0xb9,0x42,0x21,0x5c,0xfa
// 01 A5 CD B2 23 15 1E B9    52 76 79 67 42 46 99 AB
// A1 C2 94 B7 FA 03 B8 E4    36 0F 13 38 01 10 C2 BA
// B0 8E D5 6B 37 7A 76 F3    A8 9B 28 01

/////////////////////////////////////////////////////////////////////////////
// WeiSheng
#define CUST_ID_WEI_SHENG		    41  // 湖南维胜
#define CUST_NAME_WEI_SHENG			0x7b,0xf9,0x5e,0x42,0x3d,0x4b,0x30,0x07,0x3b,0x1d,0xbe,0x0b,0x1e,0xf7,0x9f,0x8e
// 03 59 50 07 DF 67 1E 63    26 5E D2 E7 F5 33 1D 87
// 6C 94 42 95 43 03 EC 82    1A 16 29 F3 5B 64 F2 8F
// B0 B2 45 B2 BA 04 B9 96    8E AD 29 01

/////////////////////////////////////////////////////////////////////////////
// ShengYi
#define CUST_ID_SHENG_YI		    42  // 生益
#define CUST_NAME_SHENG_YI			0x1e,0xae,0xed,0x55,0x95,0xf5,0x8e,0x79,0x69,0x1b,0x72,0xcf,0x13,0x9c,0x79,0x9a
// 00 80 66 7E 9B 05 F9 45    6C 22 FF 73 6C 6B 41 4F
// AB 8B C2 4A B2 02 BB 24    7B 80 45 3F 3A D1 F6 08
// E0 FC C9 7B 1F AF E9 75    99 DA 2A 01

/////////////////////////////////////////////////////////////////////////////
// Legend
#define CUST_ID_LEGEND			    43  // 科惠
#define CUST_NAME_LEGEND			0x87,0xc8,0xc6,0xe1,0xfc,0x98,0x7c,0xe2,0xc7,0xd7,0x60,0x6c,0x03,0x18,0x5b,0x57
// 02 F3 50 25 E7 D1 95 FB    AF 50 F0 F9 2E ED 97 4A
// D8 BD 96 71 E4 02 99 9E    D5 A2 F1 92 44 80 8F 1E
// 03 51 F0 7B 0B 6B 0C 9A    81 AF 2B 01

/////////////////////////////////////////////////////////////////////////////
// ShouFu
#define CUST_ID_SHOU_FU			    44  // 首富
#define CUST_NAME_SHOU_FU			0xe8,0x78,0xb1,0xde,0x2b,0x05,0xfe,0xad,0xf5,0x21,0x5a,0x72,0xdd,0x5a,0xfa,0x70
// 02 84 8C B4 47 E9 59 F9    24 1F EE 04 8B 6E 08 71
// 4C 58 4D F1 99 00 87 BB    83 BB 81 76 BB 67 5F AB
// B8 A9 F1 49 1B 1A 5E 17    96 51 2C 01

/////////////////////////////////////////////////////////////////////////////
// YuHua
#define CUST_ID_YU_HUA			    45  // 裕华
#define CUST_NAME_YU_HUA			0xa3,0x93,0x6c,0xdc,0xc3,0x50,0x6f,0x8e,0x2d,0x67,0xe1,0x23,0xc5,0x99,0x0b,0x2d
// 00 AC 32 15 87 DA 2B DB    A4 E0 33 E1 20 11 C7 D2
// 94 F9 24 A4 68 01 B1 11    F2 02 ED 3D B7 BF E1 08
// 19 2B 78 72 A4 A5 E4 5A    DE 3B 2D 01

/////////////////////////////////////////////////////////////////////////////
// Foxconn
#define CUST_ID_FOXCONN			    46  // 富士康
#define CUST_NAME_FOXCONN			0x46,0xcd,0x65,0xe7,0x93,0x39,0xaf,0x11,0xeb,0x5f,0xb4,0xe9,0x32,0x03,0x61,0x52
// 00 6D AD 27 18 71 CE 8A    A8 1D F8 D1 AE 60 61 3A
// DF 50 C9 4F F0 01 13 6C    FD E4 97 53 17 2A 82 B4
// 41 0B 78 03 54 CC 74 8A    A7 7F 2E 01

/////////////////////////////////////////////////////////////////////////////
// YuanMao
#define CUST_ID_YUAN_MAO			47  // 元茂
#define CUST_NAME_YUAN_MAO			0x57,0x3a,0xf9,0xb5,0xea,0x10,0xf6,0xcd,0x40,0x03,0x28,0x2e,0xe1,0x3f,0x2d,0x77
// 02 D3 04 63 26 37 6D CF    5E 6B B3 CB 4B 72 02 DF
// 02 F7 FF 3F F8 01 EB 4E    9C 87 DD AA 03 DF AA 47
// 07 5D 78 F3 DB 44 A2 3E    F0 9F 2F 01

/////////////////////////////////////////////////////////////////////////////
// TeChuang
#define CUST_ID_TE_CHUANG			48  // 特创
#define CUST_NAME_TE_CHUANG			0x5a,0x64,0xac,0xfd,0x8c,0x43,0x4d,0x82,0x6e,0x90,0x46,0x54,0xb1,0x8d,0x4a,0x54
// 00 C4 68 A5 4D 27 83 F7    D6 74 CC B9 59 A6 AC 75
// B2 3A A4 1A 3F 03 92 CD    4D 08 AF 74 25 97 32 FA
// AF C3 55 90 6D 7B CE 4A    E7 B4 30 01

/////////////////////////////////////////////////////////////////////////////
// HuaShen
#define CUST_ID_HUA_SHEN			49  // 华神
#define CUST_NAME_HUA_SHEN			0xbd,0xd4,0x09,0x1c,0x8d,0x39,0xb2,0x43,0x76,0x19,0xc1,0x9a,0x69,0x00,0x86,0x6a
// 00 3E CC EE B8 B3 6A 98    AA C6 17 75 B1 B2 0C 9C
// 45 00 BF D4 AF 03 BC 63    F9 88 43 6C 37 E4 3B 47
// E2 54 4C 98 11 A6 69 8C    70 BE 31 01

/////////////////////////////////////////////////////////////////////////////
// ChangDian
#define CUST_ID_CHANG_DIAN			50  // 江阴长电
#define CUST_NAME_CHANG_DIAN		0x31,0x8d,0xe3,0x68,0xbc,0x44,0x07,0x6d,0x46,0x1d,0x95,0x79,0x37,0x92,0x13,0xe4
// 01 70 3C 5A 0F 7E F5 86    34 D5 B3 54 3E 82 47 B1
// F6 3C 9B 8A FE 02 67 48    25 4C 1B 90 6F 4B A8 88
// 79 73 B4 02 FE 60 90 D3    76 39 32 01

/////////////////////////////////////////////////////////////////////////////
// LianQiao
#define CUST_ID_LIAN_QIAO			51  // 联桥
#define CUST_NAME_LIAN_QIAO			0xe8,0xd8,0x37,0x6f,0xf8,0x48,0x33,0x65,0x64,0xaa,0xe0,0xda,0xc9,0xd4,0x5e,0x40
// 01 A3 7F B8 57 DF 7A F0    F3 7E 75 61 F9 14 73 D0
// 8C 72 E2 41 53 00 8F D7    99 E7 F2 AE E5 8F B7 23
// E2 C5 57 83 65 FA B0 43    D3 CB 33 01

/////////////////////////////////////////////////////////////////////////////
// MingYang
#define CUST_ID_MING_YANG			52  // 明阳
#define CUST_NAME_MING_YANG			0x4e,0x16,0xb8,0x15,0x3e,0x57,0x30,0x39,0xb6,0xa2,0xef,0x2f,0x4d,0xe9,0x5c,0xd0
// 02 B5 7D 53 54 F5 B9 9E    49 6A 97 EF 71 C7 64 CC
// FE DD 30 BF 25 02 71 AF    7F 27 1C 3A 4A CC 9D 8F
// EF 5B D8 3E C3 39 9F AA    44 1D 34 01

/////////////////////////////////////////////////////////////////////////////
// AoHong
#define CUST_ID_AO_HONG				53  // 奥鸿
#define CUST_NAME_AO_HONG			0x34,0x04,0x7a,0x81,0xde,0xa2,0x4a,0x02,0x3b,0xbf,0xb1,0xed,0x44,0x20,0x60,0x7d
// 01 8D 53 E3 8E 4F C6 7C    40 4A 2D 1D F0 49 DE 4F
// FC 96 19 65 B0 01 C0 13    AF 11 D7 04 7A A9 DD 0F
// B1 BF 2B 70 5F B6 86 4D    77 E8 35 01

/////////////////////////////////////////////////////////////////////////////
// EleceltekTG
#define CUST_ID_ELECELTEK_TG		54  // 泰国依利
#define CUST_NAME_ELECELTEK_TG		0x94,0x5f,0xad,0x47,0xec,0x9f,0x0c,0x5c,0x76,0x73,0xbe,0xc3,0x8c,0x59,0xab,0x49
// 03 D6 43 C3 72 2E 04 94    89 7B D1 96 48 E1 F0 66
// 4A F1 C2 E1 6D 01 36 F8    77 3A 13 85 9C 63 B0 8C
// DF 96 5A D9 C1 5B AE EC    ED FE 36 01

/////////////////////////////////////////////////////////////////////////////
// ManKun
#define CUST_ID_MAN_KUN				55  // 满坤
#define CUST_NAME_MAN_KUN			0xb7,0xca,0xb9,0x80,0x7b,0x48,0x35,0xa9,0x46,0x32,0x39,0x43,0x00,0xd3,0x51,0x58
// 00 D5 F8 3E F6 65 17 81    10 29 CC D6 FE 67 7C 5C
// 53 4D 28 F7 06 03 5F 85    32 0C F5 C1 19 39 AE 91
// 22 03 55 79 1C 9E 73 44    6E D3 37 01

/////////////////////////////////////////////////////////////////////////////
// ChengRan
#define CUST_ID_CHENG_RAN			56  // 晟然
#define CUST_NAME_CHENG_RAN			0x67,0x7b,0x78,0x62,0x43,0x34,0x5d,0xea,0xdd,0x57,0x79,0x0d,0x49,0x99,0x8c,0xfc
// 02 55 69 15 2E 59 C2 B5    73 BC 47 34 5C C4 A5 98
// F6 A5 EB B9 12 01 6B 7D    1E 84 C9 45 C2 BC 8C 9B
// 06 56 78 61 3A FA F1 32    DE 11 38 01

/////////////////////////////////////////////////////////////////////////////
// JingXie
#define CUST_ID_JING_XIE			57  // 京写
#define CUST_NAME_JING_XIE			0x34,0x37,0xc3,0xdb,0x2a,0x98,0xc0,0xc1,0xaf,0x61,0xe3,0xf3,0x0b,0x42,0x07,0xb4
// 00 F8 9A 56 8A 24 91 12    68 99 12 5C 50 1E 29 6D
// 6F C6 79 2D 94 00 74 68    C2 26 CE CF 8C D9 C9 D0
// E9 01 B2 35 46 7B 3A E0    B0 90 39 01

/////////////////////////////////////////////////////////////////////////////
// FuYing
#define CUST_ID_FU_YING				58  // 富盈
#define CUST_NAME_FU_YING			0xcb,0xf4,0xdb,0x60,0xab,0x08,0xf5,0x80,0xc7,0xd9,0xb6,0x86,0x36,0xeb,0x12,0xb0
// 00 B8 B6 9F E7 22 B0 46    A8 88 07 65 B0 3B 65 E0
// 19 C3 36 07 5A 03 7E 5A    80 28 FF A6 A3 3C BC 23
// E5 87 50 BE 4B 7E C6 5D    8A F9 3A 01

/////////////////////////////////////////////////////////////////////////////
// JunYa
#define CUST_ID_JUN_YA				59  // 骏亚（惠州）
#define CUST_NAME_JUN_YA			0xb3,0xcf,0xcf,0xa7,0x41,0x48,0xa4,0xf4,0xb1,0x6b,0xeb,0x82,0xd3,0x09,0x94,0x6c
// 01 FE A2 61 FF D7 33 BB    91 E0 DE F9 DB EF A4 DC
// 78 43 88 29 33 00 5C 76    71 22 61 DE A5 04 54 E6
// 90 B0 33 E4 31 87 B1 5F    85 35 3B 01

/////////////////////////////////////////////////////////////////////////////
// YangXuan
#define CUST_ID_YANG_XUAN			60  // 扬宣
#define CUST_NAME_YANG_XUAN			0x6d,0x52,0x06,0x5e,0x78,0x9c,0xbd,0x7c,0x3c,0xc3,0x86,0xee,0x68,0x77,0x74,0x48
// 00 D9 52 38 43 5A 41 55    19 4A E3 B7 33 B6 CF 3A
// 40 11 3F 47 DC 02 C3 47    C8 26 0F 53 16 93 9C 54
// D2 0F 21 5C 1B B7 3C 36    E1 4C 3C 01

/////////////////////////////////////////////////////////////////////////////
// EleceltekKP
#define CUST_ID_ELECELTEK_KP		61  // 开平依利
#define CUST_NAME_ELECELTEK_KP		0x40,0x0f,0xda,0xc5,0x29,0xe5,0x38,0x16,0x0e,0x4b,0xd0,0xb0,0xf8,0xbb,0xae,0xe6
// 02 DC DC FE EE 9E 6A 6B    35 39 B1 D2 E4 A8 FA C5
// E5 1B EA 16 88 03 81 6C    85 3E 67 73 97 DC 56 9A
// D5 CB 81 10 5A 95 84 15    14 E2 3D 01

/////////////////////////////////////////////////////////////////////////////
// Oumulong
#define CUST_ID_OU_MU_LONG			62  // 欧姆龙
#define CUST_NAME_OU_MU_LONG		0x5e,0x4d,0x6b,0x1c,0xd1,0xbe,0x91,0x92,0xd8,0x1b,0x5f,0x79,0x0c,0xc5,0x48,0xfc
// 01 27 6F 06 30 4D BF 88    C3 37 E9 60 12 68 AE 2A
// 74 63 AB EE 3B 03 41 38    91 AA A4 32 CA 36 FD 7D
// 1A 5C 1A 77 01 22 CE D6    3B AB 3E 01

/////////////////////////////////////////////////////////////////////////////
// BangJi
#define CUST_ID_BANG_JI				63  // 邦基
#define CUST_NAME_BANG_JI			0xd6,0x96,0x43,0xc5,0x7a,0x7a,0xfb,0xff,0x09,0xbc,0xfe,0x98,0x44,0xdf,0x05,0xb5
// 03 66 A8 B0 84 C5 18 2C    D0 97 AA 79 50 62 42 CA
// 94 5B EA 9A 5E 03 C0 12    9C CA DC CA 1C 5E 67 5F
// FA 41 9C 56 03 50 67 2F    AD 7F 3F 01

/////////////////////////////////////////////////////////////////////////////
// PuLin
#define CUST_ID_PU_LIN				64  // 天津普林
#define CUST_NAME_PU_LIN			0x26,0xdc,0xdd,0xa2,0xbd,0xe5,0xd9,0x92,0x9d,0x39,0x7e,0x05,0x33,0xfb,0x9c,0x1a
// 01 E5 A1 BE 41 4A 63 C5    9D BA A0 26 B5 9A 02 BD
// A5 D0 D4 F1 8F 03 F7 42    EA 99 1C C2 DA 21 64 37
// A0 D7 13 62 32 40 A0 A8    A8 9D 40 01

/////////////////////////////////////////////////////////////////////////////
// XiangGuo
#define CUST_ID_XIANG_GUO			65  // 东莞翔国
#define CUST_NAME_XIANG_GUO			0x89,0xd8,0xa5,0xbf,0x7e,0x0b,0x63,0xc9,0xfd,0xc7,0x6a,0x7a,0xa2,0x9c,0x95,0x5e
// 03 C0 CE 45 9C 00 C6 7D    3D EA BA 44 72 F8 C1 53
// 59 03 22 D2 99 03 7A 5F    C7 CD D6 75 72 37 BD BB
// D6 F8 A6 7A DD 2D FB FD    83 53 41 01

/////////////////////////////////////////////////////////////////////////////
// ChaoYue
#define CUST_ID_CHAO_YUE			66  // 超跃
#define CUST_NAME_CHAO_YUE			0x04,0x85,0xc6,0xa9,0x3e,0x2a,0x56,0x62,0x5a,0xf8,0x6d,0xae,0xb2,0x93,0x8c,0x39
// 00 05 86 F2 1C 3F 79 1A    97 72 9A 1D A0 20 30 2D
// DE 1F 3C 55 9C 02 8B E1    2B 94 B6 89 89 87 AC 7B
// 81 3D 5A 10 A5 FE B1 CC    92 CA 42 01

/////////////////////////////////////////////////////////////////////////////
// XingHua
#define CUST_ID_XING_HUA			67  // 星华
#define CUST_NAME_XING_HUA			0xc1,0xfc,0xfd,0x61,0xa7,0xb0,0x50,0x72,0x21,0xb9,0xf9,0xaf,0x94,0xcf,0x57,0x2e
// 03 A7 8F B5 D9 81 08 B5    15 60 61 38 53 C0 CA 5B
// 04 7B D3 ED 3C 00 66 1C    70 E4 6E 93 C5 E9 48 8E
// 31 43 37 C7 33 2F 95 C4    F0 F9 43 01

/////////////////////////////////////////////////////////////////////////////
// GuangTian
#define CUST_ID_GUANG_TIAN			68  // 广天
#define CUST_NAME_GUANG_TIAN		0xd2,0xcb,0xb3,0x9c,0xdc,0x59,0x8f,0xb1,0xf6,0xaf,0xb4,0xe9,0xf8,0xbc,0xe8,0x3f
// 02 D4 D5 24 1D 6F 7B 43    9E 88 60 ED 92 55 FE A2
// FC A6 E4 81 91 01 9D 1A    60 CE 86 6A ED 0C 2B 6F
// 93 E7 D9 C2 AB 47 95 25    1A 40 44 01

/////////////////////////////////////////////////////////////////////////////
// ShenLian
#define CUST_ID_SHEN_LIAN			69  // 深联
#define CUST_NAME_SHEN_LIAN			0x67,0x86,0xaf,0xf1,0x06,0xe1,0xe8,0x3b,0x14,0xc2,0x63,0x51,0xe7,0x74,0x7c,0x74
// 00 B2 9B E7 AB 48 A6 D1    25 EE AA 1F 4D F1 8D 4F
// F3 7A 7F 8B 51 02 96 37    D8 83 4B E0 33 FB 91 8C
// 71 1D F8 24 87 DE 5B 64    59 51 45 01

/////////////////////////////////////////////////////////////////////////////
// ChuangHong
#define CUST_ID_CHUANG_HONG			70  // 创弘
#define CUST_NAME_CHUANG_HONG		0xdf,0x7d,0x0a,0x3f,0x8a,0x91,0x37,0xb7,0x84,0x02,0x4f,0x46,0xd8,0x06,0xd2,0x1e
// 02 AD 1B D7 9B B5 D3 2F    E9 A8 B0 E8 92 95 90 B9
// EB 59 71 9B 84 03 C9 27    C6 5D AC E2 39 99 64 44
// 4C EC 05 A0 E0 55 D1 6B    2D 77 46 01

/////////////////////////////////////////////////////////////////////////////
// ShiJi
#define CUST_ID_SHI_JI				71  // 世纪
#define CUST_NAME_SHI_JI			0x91,0x9c,0x3b,0x5f,0xab,0xf4,0xef,0xd0,0xe1,0x5f,0x69,0xe6,0xc0,0x75,0x53,0xc0
// 02 BE 7B 13 4A 8C 9D 69    F4 D3 38 3E 5C 37 F7 BA
// B2 D4 35 8A 79 02 53 E3    A1 0E 44 10 03 C6 44 DB
// C6 CC 2E 55 74 9E F2 E1    F9 2A 47 01

/////////////////////////////////////////////////////////////////////////////
// LiangDa
#define CUST_ID_LIANG_DA			72  // 良达
#define CUST_NAME_LIANG_DA			0x5c,0xd3,0xd0,0xd7,0xf0,0x9a,0xa6,0xcd,0xde,0x36,0xd8,0x8c,0xc9,0x0d,0xbf,0x7f
// 00 38 D7 70 66 CB BE B7    B8 F6 B3 01 A8 CD F3 4D
// 17 3A 5C 07 4E 03 F3 78    4B 66 F0 ED 46 4A 60 5B
// 7B 1F A5 E2 88 6D 34 DC    41 C6 48 01

/////////////////////////////////////////////////////////////////////////////
// SanQiang
#define CUST_ID_SAN_QIANG			73  // 三强
#define CUST_NAME_SAN_QIANG			0x1a,0x7d,0x4c,0x36,0x4a,0x15,0x1d,0xf3,0x26,0xda,0x61,0xdb,0xfa,0xf5,0x2b,0x0c
// 00 26 9E 21 64 2B EE 7C    EF 6F F7 00 20 95 A3 48
// 83 CA BB 29 52 01 02 E2    FD 55 D5 69 6A C7 12 D6
// C5 80 C4 4D 75 D8 A9 8D    C6 4A 49 01

/////////////////////////////////////////////////////////////////////////////
// BiYaDi
#define CUST_ID_BI_YA_DI			74  // 比亚迪
#define CUST_NAME_BI_YA_DI			0x57,0xbf,0xb0,0x08,0xf7,0x8e,0x05,0x14,0xa2,0x04,0xad,0xf0,0x27,0xee,0x09,0x0b
// 01 C7 48 B9 3E 82 31 A0    C2 26 00 1A AF 69 E8 62
// 3E F3 D0 71 64 03 F6 43    A5 3A 2B 7A 9A 2E 23 51
// D9 7E 25 D1 58 AA 29 91    58 98 4A 01

/////////////////////////////////////////////////////////////////////////////
// JianDing
#define CUST_ID_JIAN_DING			75  // 健鼎
#define CUST_NAME_JIAN_DING			0xa8,0xa0,0x03,0x33,0x26,0xaf,0x53,0x12,0xe7,0x9f,0x04,0xe4,0xed,0x0e,0xcd,0xe4
// 00 1A 73 35 EA 48 D2 4F    38 24 6D 60 7C CE DE 46
// 2D 20 B9 49 6E 00 04 97    D1 D9 D1 C8 9A AB C8 2B
// 5D 82 AA C3 7A 3C 8A FA    72 C1 4B 01

/////////////////////////////////////////////////////////////////////////////
// JiaLiEn
#define CUST_ID_JIA_LI_EN			76  // 嘉利恩
#define CUST_NAME_JIA_LI_EN			0x8c,0x65,0xb4,0x0c,0x05,0x4c,0x3b,0xc3,0x16,0xa3,0x81,0xd8,0x42,0xc7,0x8e,0x5c
// 00 9D D6 DA D3 C2 54 BF    A2 87 74 38 37 98 7D E5
// 9C 24 BB 10 48 01 A3 39    28 88 FA 74 E4 51 79 33
// E9 98 0C 6C B1 3A AD 1D    8A BC 4C 01

/////////////////////////////////////////////////////////////////////////////
// JunYaLN
#define CUST_ID_JUN_YA_LN			77  // 骏亚（龙南）
#define CUST_NAME_JUN_YA_LN			0xa5,0xa2,0x60,0xc3,0x86,0xb3,0x53,0x6a,0xe2,0xc6,0x34,0xef,0xc9,0xcc,0xf7,0x81
// 03 30 26 13 6E 4E 3F 86    4E FE 86 93 E0 92 5B AD
// DC D8 C2 1D B2 01 C5 49    19 20 1F B5 AD 3C CD A3
// A4 93 A9 F1 C6 DB 3E 6B    B8 EC 4D 01

/////////////////////////////////////////////////////////////////////////////
// LingChuang
#define CUST_ID_LING_CHUANG			78  // 领创
#define CUST_NAME_LING_CHUANG		0x1a,0x4a,0x8a,0x60,0xd1,0x49,0x10,0xb2,0x96,0x74,0xb1,0x0c,0xa2,0xf5,0xec,0x9d
// 00 ED B6 84 1E B0 3D 24    F2 4D C9 65 B2 FF 2C 78
// 1D C5 5C 35 23 01 28 56    DA DF CF 8D AA 56 F4 8C
// 2F 80 78 D5 94 4D 62 7D    C1 67 4E 01

/////////////////////////////////////////////////////////////////////////////
// JunJie
#define CUST_ID_JUN_JIE				79  // 俊杰
#define CUST_NAME_JUN_JIE			0x55,0xea,0xfe,0x16,0xf8,0xeb,0x57,0x9a,0x6b,0x6d,0xcb,0x67,0x19,0xe3,0x67,0x04
// 01 97 11 48 4A 24 BA FB    C9 CD E0 31 76 90 DA D4
// 14 69 9A B4 E6 03 68 80    82 AB CF 2F 71 23 EA AB
// 98 E3 22 EB 84 B8 B7 F9    97 20 4F 01

/////////////////////////////////////////////////////////////////////////////
// XingYing
#define CUST_ID_XING_YING			80  // 兴英
#define CUST_NAME_XING_YING			0xc6,0xa0,0x43,0x61,0xf2,0x7c,0x1e,0x98,0xe5,0x04,0xcf,0xab,0xc1,0x4b,0xc8,0xa4
// 01 64 E2 AA A3 5D 3B 63    52 C9 C2 CE E6 E4 AF 32
// 44 A9 44 59 B3 02 ED E1    68 E2 9B 44 50 50 D0 F3
// 9A 62 4A 34 6E E5 15 34    B1 D5 50 01

/////////////////////////////////////////////////////////////////////////////
// SongWei
#define CUST_ID_SONG_WEI			81  // 松维
#define CUST_NAME_SONG_WEI			0x3f,0xb5,0x37,0xc1,0x92,0x57,0xab,0xc0,0x7d,0x72,0x83,0xbb,0xd9,0x83,0x5a,0x12
// 03 88 2D C2 AF 63 A6 62    82 95 EF 4C 2E 87 06 59
// 14 5C DD 79 CB 02 3E FA    01 B4 67 BB A1 30 98 3E
// B5 14 05 8A 5F 68 99 1A    D3 B3 51 01

/////////////////////////////////////////////////////////////////////////////
// RuoMei
#define CUST_ID_RUO_MEI				82  // 若美
#define CUST_NAME_RUO_MEI			0x29,0x1b,0x9b,0xe2,0xc3,0xdd,0x0d,0xa1,0xc8,0xc7,0x96,0xdc,0x05,0xe7,0x0a,0x3d
// 00 58 36 E5 97 B7 F7 85    47 74 06 F6 6D 79 06 DA
// 8D B0 80 51 A7 01 44 63    F0 C5 8F 4D 25 38 7F FD
// 3F 20 FC 29 B0 8A B5 8A    05 2F 52 01

/////////////////////////////////////////////////////////////////////////////
// ZhongJing
#define CUST_ID_ZHONG_JING			83  // 中京
#define CUST_NAME_ZHONG_JING		0xbf,0x5d,0x8b,0xf2,0xe7,0x82,0x3b,0x46,0x10,0x78,0x62,0x38,0xa3,0x10,0x0f,0xa7
// 02 CF 9A D0 53 46 3A CA    78 75 03 64 25 20 8B E9
// 76 5A 9C B9 2A 03 FF C5    32 5F 25 1C A3 64 63 25
// C9 E7 FD CC EF AB 13 BA    5D 72 53 01

/////////////////////////////////////////////////////////////////////////////
// QuanChengXin
#define CUST_ID_QUAN_CHENG_XIN		84  // 全成信
#define CUST_NAME_QUAN_CHENG_XIN	0x3d,0x66,0xd9,0xaa,0x52,0xaf,0x86,0x85,0xd1,0x4c,0xc5,0xe9,0x30,0xf4,0x6d,0x47
// 01 6C FB 3A E5 5F 81 92    16 1B DA E7 3C 3E 06 27
// 42 31 FB 5F 94 01 8E C9    68 9F 4A 7C E5 60 01 1B
// F0 5A E9 57 C1 AC 41 84    11 72 54 01

/////////////////////////////////////////////////////////////////////////////
// NanChe
#define CUST_ID_NAN_CHE				85  // 南车
#define CUST_NAME_NAN_CHE			0x9b,0x51,0x7d,0x58,0x7d,0x30,0x67,0x35,0xef,0x53,0xea,0xf9,0xc2,0x52,0xa1,0x91
// 03 B1 AB D4 B0 1F 33 C9    D1 D3 E5 3A 47 2B 7D D4
// 7F B3 00 93 3A 02 E4 47    D3 5D ED 65 D6 8D 0B 0B
// 22 F4 C8 76 04 77 7F 12    C0 96 55 01

/////////////////////////////////////////////////////////////////////////////
// SuHang
#define CUST_ID_SU_HANG				86  // 苏杭
#define CUST_NAME_SU_HANG			0x2e,0x6e,0x1d,0x0a,0x99,0xa7,0x66,0x74,0xc1,0x14,0xeb,0xfc,0xcf,0x48,0xed,0x52
// 01 06 21 77 92 CB AC 85    05 66 0E AC 23 77 84 04
// 7F 84 AE 14 7A 00 26 65    8D BE 2B EA D7 00 CB 93
// 53 63 A4 14 34 EC C4 77    EF 74 56 01

/////////////////////////////////////////////////////////////////////////////
// ZhiEn
#define CUST_ID_ZHI_EN				87  // 智恩
#define CUST_NAME_ZHI_EN			0x5f,0x73,0xf7,0x3c,0x44,0x51,0x01,0xa6,0x86,0x27,0x3e,0xe8,0xb2,0xc5,0xd4,0xf4
// 01 EA 4C B9 24 91 11 04    01 01 3D FA C8 48 6A 57
// 8D 13 E1 8F 5A 00 ED 03    D4 9F 6D D3 99 2B C0 F2
// 23 7C CB 42 17 03 57 CA    27 64 57 01

/////////////////////////////////////////////////////////////////////////////
// DaTong
#define CUST_ID_DA_TONG				88  // 大通
#define CUST_NAME_DA_TONG			0x25,0x0e,0x7c,0xcc,0x70,0x48,0x88,0xff,0x52,0xa4,0xf7,0x34,0x73,0xd5,0x12,0x48
// 00 82 2E F4 23 90 20 38    34 06 E5 E9 AC 80 59 AE
// 51 97 7B 7F 23 02 5B 44    E6 56 99 70 90 D5 61 D6
// 37 BD 88 51 56 4C E8 75    DC BB 58 01

/////////////////////////////////////////////////////////////////////////////
// WuHan709
#define CUST_ID_WH_709				89  // 武汉709
#define CUST_NAME_WH_709			0xf7,0x2f,0x8f,0x19,0x7e,0xcb,0x5c,0x32,0x92,0xcc,0x40,0x6c,0x0b,0xb0,0xe7,0x55
// 02 A4 7E DA 05 4E 61 0E    32 64 02 C5 55 6A D9 11
// 80 E5 4B F9 F5 03 02 91    49 3F 1F BE 55 AF F6 69
// 2E 41 6C BA 1C 5A E1 0E    B6 6C 59 01

/////////////////////////////////////////////////////////////////////////////
// BanXin
#define CUST_ID_BAN_XIN				90  // 班信
#define CUST_NAME_BAN_XIN			0xad,0x73,0xbe,0xe7,0x90,0xa6,0x07,0xf6,0xd3,0x56,0x16,0xe8,0xee,0xf9,0x75,0x8b
// 02 67 71 42 63 37 F6 BC    A1 CD 7A C5 BC DA 5D 7B
// E4 20 76 89 E2 02 BE E5    C0 23 68 62 17 BA 69 EA
// EE CA AC 75 80 A3 A2 9B    6D 0E 5A 01

/////////////////////////////////////////////////////////////////////////////
// OuLong
#define CUST_ID_OU_LONG				91  // 欧珑
#define CUST_NAME_OU_LONG			0x19,0xa7,0x15,0x02,0x02,0xb2,0x14,0x64,0x5b,0xab,0xe6,0x49,0xfb,0xe4,0xf9,0xc8
// 03 20 88 46 37 28 50 BA    65 DE 25 FC 32 DA FF 6F
// F0 DD 8E 49 EF 01 1C F6    DA FB B9 C8 97 71 43 77
// 2C DC 66 3B 1E 03 C3 FB    32 4A 5B 01

/////////////////////////////////////////////////////////////////////////////
// KangJia
#define CUST_ID_KANG_JIA			92  // 康佳
#define CUST_NAME_KANG_JIA			0xe5,0x0f,0xc3,0xc8,0x78,0x24,0x72,0x39,0xc4,0xb7,0x20,0x3a,0xcc,0x40,0x3e,0xed
// 02 BB 67 8D 33 36 79 DA    D2 4A CF BB 9B CB B8 74
// D8 B7 A0 2D 3A 02 CD EC    50 0C B2 4A CA CC B1 08
// 0F CF 95 CD 37 94 68 BE    D5 45 5C 01

/////////////////////////////////////////////////////////////////////////////
// XieHe
#define CUST_ID_XIE_HE				93  // 协和
#define CUST_NAME_XIE_HE			0x27,0x52,0x5e,0xd3,0xc4,0x91,0x86,0x47,0x86,0xf9,0x98,0xa7,0xbf,0x8f,0x41,0x00
// 02 A2 B4 53 C7 AA 59 FF    7D 42 20 25 5E 0C 96 BA
// D1 C0 B6 4D 41 02 5B 4C    CE A1 3E 6F 8B AE 95 7A
// 75 9D B0 3C 26 36 8E 79    17 62 5D 01

/////////////////////////////////////////////////////////////////////////////
// ShangDa
#define CUST_ID_SHANG_DA			94  // 上达
#define CUST_NAME_SHANG_DA			0xda,0x2b,0xcb,0x27,0x06,0x9b,0xf3,0x59,0x7f,0x8d,0x5c,0xd5,0x83,0xee,0x46,0xf3
// 01 25 C5 DB F7 16 F6 61    8F 29 AE 5D F0 77 DD 5A
// AC D0 3D FE 8B 01 61 BB    1B 46 31 2F 14 47 01 F4
// 57 1E 8C 41 54 49 6A F8    2B 96 5E 01

/////////////////////////////////////////////////////////////////////////////
// HangTianHuoJian
#define CUST_ID_HANG_TIAN_HUO_JIAN			95  // 北京航天火箭
#define CUST_NAME_HANG_TIAN_HUO_JIAN		0x34,0x3c,0x94,0xdb,0x03,0xa1,0xd0,0xf9,0xb9,0x39,0x79,0x2d,0xee,0x5f,0x8b,0xf8
// 01 D6 1F 6A A1 FD EF 8B    A9 C5 5A 9A 06 29 EC 8B
// E1 87 77 8D B6 02 13 8E    2A D7 51 A4 6B F4 59 B6
// EF AB 53 D6 A0 02 43 57    9D 77 5F 01

/////////////////////////////////////////////////////////////////////////////
// WanJun
#define CUST_ID_WAN_JUN				96  // 东莞万钧
#define CUST_NAME_WAN_JUN			0x65,0xd1,0xe5,0x03,0x44,0xfb,0x62,0x40,0xbe,0xd9,0x6f,0x6e,0x9b,0x55,0xcd,0xa9
// 02 76 1E BF F7 B0 7B D5    D9 B3 CF C1 D2 1D 44 AC
// BD CF 4E 87 1A 03 79 56    2A BD AE 3E 11 14 ED E7
// BD F5 10 A4 0C 23 04 4C    00 55 60 01

/////////////////////////////////////////////////////////////////////////////
// XinTai
#define CUST_ID_XIN_TAI				97  // 珠海欣泰
#define CUST_NAME_XIN_TAI			0x3b,0xc4,0x58,0x8b,0x13,0x72,0x6c,0xef,0xb8,0x05,0x41,0x43,0xe6,0x33,0x14,0x24
// 02 BD D0 C1 18 F7 A6 1D    6E AA C5 4C D4 17 67 CB
// 98 A4 84 D0 C6 01 FA 54    71 AE 1E 0E 92 72 5C B7
// 47 13 13 D8 D6 FA 7C 27    2C 72 61 01

/////////////////////////////////////////////////////////////////////////////
// GuangHe
#define CUST_ID_GUANG_HE			98  // 广合
#define CUST_NAME_GUANG_HE			0x86,0xd7,0x13,0xe0,0xb7,0xf0,0xcc,0xd8,0x29,0x03,0x8a,0x36,0x83,0xce,0x57,0x75
// 00 A5 1A 46 CA A8 C1 E3    73 2D 19 A6 2A B9 2B AB
// 21 EC E6 B1 72 03 64 F3    05 25 6B C1 6A 98 7D F6
// BF EA 63 E5 9D 23 8B 40    2A 03 62 01

/////////////////////////////////////////////////////////////////////////////
// ShuangJin
#define CUST_ID_SHUANG_JIN			99  // 双进
#define CUST_NAME_SHUANG_JIN		0x6d,0xa3,0x8f,0x86,0x53,0x1c,0x06,0x47,0xac,0x56,0x05,0x18,0x5f,0x11,0x91,0x05
// 01 84 3A B3 84 DC 6A A7    E6 8E 72 4F C7 6D A6 AA
// 50 11 0C 4E 71 01 5D 84    81 D2 13 24 C9 38 D4 A9
// F5 B4 24 5F 79 CA BC 10    38 68 63 01

/////////////////////////////////////////////////////////////////////////////
// YuanSheng
#define CUST_ID_YUAN_SHENG			100  // 元盛
#define CUST_NAME_YUAN_SHENG		0x87,0x6f,0x7a,0xf3,0x7a,0x09,0xe2,0xb9,0xd5,0x06,0x1c,0x99,0x68,0x86,0xff,0x4a
// 00 11 D2 0C BD D9 5A 5A    02 DA 50 1C 21 81 C2 08
// 19 1D 17 49 35 02 5E 97    A4 54 80 8D 41 2A 18 8F
// F2 76 13 2A CE B2 1A B8    91 1D 64 01

/////////////////////////////////////////////////////////////////////////////
// ChengYi
#define CUST_ID_CHENG_YI			101  // 诚亿（嘉兴）
#define CUST_NAME_CHENG_YI			0x23,0x0c,0x44,0xc8,0x30,0x86,0x4f,0x79,0xde,0xca,0x25,0x8a,0x1b,0xd9,0x49,0x98
// 00 93 10 37 0B 29 1B C6    E7 C8 47 0B B1 D0 83 B9
// AF 3C BD 33 C3 00 56 33    5A AE 87 E5 EA 6D 5C 88
// 07 55 2C D0 7E E9 AB 9D    2E 6A 65 01

/////////////////////////////////////////////////////////////////////////////
// HuaXingYu
#define CUST_ID_HUA_XING_YU			102  // 华兴宇
#define CUST_NAME_HUA_XING_YU		0x1a,0xe4,0x7e,0xbb,0xe0,0x55,0x4d,0x24,0xe4,0x2d,0xcf,0x13,0x83,0xfe,0xdd,0x05
// 00 66 BB 47 CB 64 5F 8E    CE 5F F3 49 69 13 DC 7A
// EC 4E 45 C5 68 03 94 6E    E9 43 8B 16 43 94 6C 3C
// 16 DA 9C FF FA 47 E3 06    D4 B0 66 01

/////////////////////////////////////////////////////////////////////////////
// LianMeng
#define CUST_ID_LIAN_MENG			103  // 连盟
#define CUST_NAME_LIAN_MENG			0x47,0xf6,0x7d,0x70,0x0f,0x09,0x95,0x61,0xb7,0xd7,0x67,0xe9,0xc7,0xf7,0x32,0xac
// 00 5B C8 ED 69 81 23 4C    D6 C9 BB FF 7C 78 A1 44
// 49 B7 D6 B7 F3 00 D3 A7    88 16 21 2A 36 AD 8F 89
// 24 75 B4 21 FD 16 42 04    56 F6 67 01

/////////////////////////////////////////////////////////////////////////////
// XinDaHui
#define CUST_ID_XIN_DA_HUI			104  // 鑫达辉
#define CUST_NAME_XIN_DA_HUI		0x7b,0x1a,0xf6,0x4e,0x83,0x76,0x12,0x36,0xf9,0xc2,0xb6,0x00,0xff,0x42,0x87,0xa0
// 03 B7 2D A6 F7 84 F9 6F    6D 4E 87 B6 B8 45 4C 7D
// 49 86 C5 66 3F 02 33 DE    B2 EE 41 B1 9F 56 12 5C
// 31 8D 92 FE 69 18 AF 5E    E8 EF 68 01

/////////////////////////////////////////////////////////////////////////////
// XunJieXing
#define CUST_ID_XUN_JIE_XING		105  // 迅捷兴
#define CUST_NAME_XUN_JIE_XING		0xef,0x22,0x22,0xb2,0xb7,0x92,0xd4,0x53,0xe9,0xff,0x9d,0xc7,0xf2,0x68,0x51,0xa8
// 00 D0 32 2C E8 34 EC 85    2B 9E A5 65 54 38 AA 46
// 6F 21 2D 4C F3 03 9D 38    6F 83 46 E8 F3 56 28 3F
// 68 EA 0C 6D 6A 69 9E 5E    83 D9 69 01

/////////////////////////////////////////////////////////////////////////////
// BenLiDa
#define CUST_ID_BEN_LI_DA			106  // 奔力达
#define CUST_NAME_BEN_LI_DA			0x22,0xd3,0xaf,0x3a,0x91,0x09,0xc5,0x9c,0xae,0x71,0x56,0x15,0x93,0xe5,0xff,0xdf
// 03 61 38 9D 24 A8 DE 1A    C3 B3 06 56 3E CE 06 A0
// 10 AE AC 7C 4A 01 87 E5    B7 4D 0B 8B D0 22 87 BE
// 04 B0 ED DC 1D 21 77 AC    DF 6C 6A 01

/////////////////////////////////////////////////////////////////////////////
// XinAn
#define CUST_ID_XIN_AN				107  // 鑫岸
#define CUST_NAME_XIN_AN			0xed,0xdc,0xee,0x5a,0xd0,0xd6,0xc5,0x73,0xe3,0x32,0x71,0x69,0x59,0x76,0x2a,0xa1
// 03 7E 8F 6C B2 35 0F E6    C4 0E BA 87 4E AF 36 E5
// D9 0F FD 10 97 01 34 8E    C8 20 E9 2B 98 2D FE 4B
// EB EA 27 F3 6E 85 62 5C    3C 53 6B 01

/////////////////////////////////////////////////////////////////////////////
// GuangQian
#define CUST_ID_GUANG_QIAN			108  // 广谦
#define CUST_NAME_GUANG_QIAN		0xc7,0x42,0xef,0xcc,0x7d,0x41,0x0a,0x5c,0xa3,0x0a,0x7c,0x1b,0x6d,0x2f,0x1e,0x96
// 03 7C B5 AA E9 27 57 3E    F7 2B B2 6D 4B 4C 8F 91
// F4 AD A6 52 93 01 F0 F9    8C E1 C5 3F B4 38 26 0C
// B6 8D 53 5B E5 A4 BF F8    65 13 6C 01

/////////////////////////////////////////////////////////////////////////////
// XinLi
#define CUST_ID_XIN_LI				109  // 信利
#define CUST_NAME_XIN_LI			0x21,0xae,0x0d,0x4f,0x28,0x9c,0x84,0x9a,0xf9,0xc4,0x04,0xaf,0x87,0x49,0xf1,0x40
// 03 02 A2 05 CE 7B 9C F2    9F 98 D4 C1 10 A1 5B CA
// 85 B7 70 36 A6 02 B0 69    3F 97 FC CD 60 87 44 8F
// 02 EF 03 85 16 AB 8C 91    40 4D 6D 01

/////////////////////////////////////////////////////////////////////////////
// LianTai
#define CUST_ID_LIAN_TAI			110  // 联泰
#define CUST_NAME_LIAN_TAI			0x51,0xe2,0x37,0x2d,0xd9,0xc6,0xeb,0xe8,0xf3,0x7d,0xa5,0x8e,0x5f,0x10,0xa5,0xb0
// 01 23 72 3E BF 24 05 81    1D EC 80 B9 83 87 BE E0
// EC 6C 00 3F 64 03 DE 78    D0 93 22 95 75 A3 AB 68
// F0 97 78 12 3D 9A 33 F8    75 C7 6E 01

/////////////////////////////////////////////////////////////////////////////
// KangYuan
#define CUST_ID_KANG_YUAN			111  // 康源
#define CUST_NAME_KANG_YUAN			0x18,0x0f,0xbd,0xae,0x11,0x50,0xb3,0x58,0x84,0x1f,0x34,0xc8,0x86,0x6f,0xd0,0x07
// 02 4B 36 81 DC FD 61 79    18 96 0F 21 71 9C EA B9
// C2 BC CD BC 5C 01 21 F5    04 31 D3 31 DB 3A DF 93
// 9C 23 31 94 74 EC 8D CB    B4 38 6F 01

/////////////////////////////////////////////////////////////////////////////
// DaYang
#define CUST_ID_DA_YANG				112  // 大洋
#define CUST_NAME_DA_YANG			0xb2,0x79,0xf5,0x7c,0x9e,0x65,0x02,0xe7,0xd2,0x8d,0x19,0xc9,0xb1,0xd3,0xae,0xfb
// 03 01 8C 66 38 B5 75 23    69 23 E2 7A F8 F6 96 43
// 9C 04 ED 6F 6B 03 7B EF    74 35 83 88 27 9C AF 97
// 84 B1 AF 82 2F CD 1D 9C    92 42 70 01

/////////////////////////////////////////////////////////////////////////////
// KaiNuoWei
#define CUST_ID_KAI_NUO_WEI			113  // 凯诺微
#define CUST_NAME_KAI_NUO_WEI		0xfc,0x44,0xa5,0xce,0x2b,0xe0,0xe4,0xfa,0xa2,0x71,0x8a,0x28,0x12,0x8a,0x95,0x71
// 01 9A EB BA 7A EB E4 AE    88 C0 CF 14 F1 B0 51 41
// 5C 70 69 B3 2B 00 A0 6E    03 E3 CF D9 3D 2E 6A F3
// 37 8A 92 8D 8F FD 40 54    AC 51 71 01

/////////////////////////////////////////////////////////////////////////////
// AiSheng
#define CUST_ID_AI_SHENG			114  // 爱升
#define CUST_NAME_AI_SHENG			0x1e,0xd5,0x77,0x63,0x81,0x2f,0xaa,0x5c,0x16,0x17,0xd2,0x31,0x39,0x5b,0x26,0xbc
// 03 5A FA 8B DD CF F6 72    67 CD C6 B5 7E 62 16 18
// 28 7B 7D 96 68 03 49 50    56 AD BF 88 DA 07 DA 62
// A9 25 57 51 9E 92 27 F2    60 1D 72 01

class CCustomID  
{
public:
	CCustomID();
	virtual ~CCustomID();

};

#endif // !defined(AFX_CUSTOMID_H__E1D9CABA_BE37_4202_9BDA_E84B7CFC4C5E__INCLUDED_)