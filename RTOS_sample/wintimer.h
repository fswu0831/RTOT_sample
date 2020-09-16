/** 
 *  Sample program for Hyper Operating System V4 Advance
 *
 * @file  wintimer.h
 * @brief %jp{Windows�p�̃^�C�}}%en{Windows timer object}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef __wintimer_h__
#define __wintimer_h__


#ifdef __cplusplus
extern "C" {
#endif

void WinTimer_Start(int inhno, int iInterval);	/** %jp{�^�C�}����J�n} */
//INHNO����int�ɕϊ�

#ifdef __cplusplus
}
#endif



#endif	/* __wintimer_h__ */



/* end of file */
