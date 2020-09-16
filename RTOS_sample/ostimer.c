/** 
 *  Sample program for Hyper Operating System V4 Advance
 *
 * @file  ostimer.c
 * @brief %jp{OS�^�C�}}%en{OS timer}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#include "kernel.h"
#include "ostimer.h"
#include "wintimer.h"


#define OSTIMER_TIMER_INHNO		1			/**< %jp{�����݃n���h���ԍ�} */


static void OsTimer_IrqHandler(void);		/**< %jp{�^�C�}�����݃n���h��} */


/** %jp{OS�p�^�C�}���������[�`��} */
void OsTimer_Initialize(VP_INT exinf)
{
	T_DINH dfinh;
	
	/* %jp{�����݃n���h����`} */
	dfinh.inthdr = (FP)OsTimer_IrqHandler;
	def_inh(OSTIMER_TIMER_INHNO, &dfinh);
	
	/* %jp{�^�C�}����J�n} */
	WinTimer_Start(OSTIMER_TIMER_INHNO, 10);
}


/** %jp{�^�C�}�����݃n���h��} */
void OsTimer_IrqHandler(void)
{
	isig_tim();
}


/* end of file */
