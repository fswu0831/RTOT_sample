/** 
 *  Sample program for Hyper Operating System V4 Advance
 *
 * @file  wintimer.c
 * @brief %jp{Windows�p�̃^�C�}}%en{Windows timer object}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


/** %jp{Windows �w�b�_�t�@�C���̓ǂ݂���} */
#define SIZE  WIN_SIZE
#include <windows.h>
#undef  SIZE

#include "kernel.h"
#include "wintimer.h"
#include "arch/proc/win/win32/proc.h"


static DWORD WINAPI WinTimer_Thread(LPVOID param);		/**< %jp{�^�C�}�����ݗp�X���b�h�֐�} */
static HANDLE hEventTimer;								/**< %jp{�^�C�}�n���h��} */


/** %jp{OS�p�^�C�}�̏�����} */
void WinTimer_Start(INHNO inhno, int iInterval)
{
	DWORD dwThreadId;
		
	/* %jp{�^�C�}�p�C�x���g�̍쐬} */
	hEventTimer = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	/* %jp{�}���`���f�B�A�^�C�}�̊J�n} */
	timeSetEvent(iInterval, 1, (LPTIMECALLBACK)hEventTimer, 0, TIME_PERIODIC | TIME_CALLBACK_EVENT_PULSE);
	
	/* %jp{�X���b�h����} */
	CreateThread(NULL, 0, WinTimer_Thread, (LPVOID)inhno, 0, &dwThreadId);
}


/** %jp{�^�C�}�����ݗp�X���b�h�֐�} */
DWORD WINAPI WinTimer_Thread(LPVOID param)
{
	INHNO inhno;
	
	inhno = (INHNO)param;

	for ( ; ; )
	{
		/* %jp{�^�C�}�C�x���g��҂�} */
		WaitForSingleObject(hEventTimer, INFINITE);

		/* %jp{�����݃V�O�i��������} */
		vsig_int(inhno);
	}
}


/* end of file */
