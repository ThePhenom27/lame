// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// jlame.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
#ifndef _WIN32

// version
#define _RS_TOSTRING(x)	#x
#define RS_TOSTRING(x)	_RS_TOSTRING(x)

#ifdef TARGET_LBE
#define RS_ENDIAN		"Little-Endian "
#else
#define RS_ENDIAN		"Big-Endian "
#endif

#ifdef TARGET_64BIT
#define RS_BITS			"x64 "
#else
#define RS_BITS			"x86 "
#endif

#define RS_LAME_VERSION	"version: " RS_ENDIAN RS_BITS RS_TOSTRING(RS_FILEVERSION) " " RS_TOSTRING(RS_DATE) "\n"

const char* version = "\nlibjlame.so " RS_LAME_VERSION;

#endif
