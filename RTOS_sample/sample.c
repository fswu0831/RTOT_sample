/** 
 *  Sample program for Hyper Operating System V4 Advance
 *
 * @file  sample.c
 * @brief %jp{�T���v���v���O����}%en{Sample program}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "wintimer.h"


#define LEFT(num)	((num) <= 1 ? 5 : (num) - 1)
#define RIGHT(num)	((num) >= 5 ? 1 : (num) + 1)


ID mbxid;
ID mpfid;


/** %jp{���b�Z�[�W�\����} */
typedef struct t_print_msg
{
	T_MSG msg;
	char  text[32];
} T_PRINT_MSG;


/** %jp{�������n���h��} */
void Sample_Initialize(VP_INT exinf)
{
	T_CMPF cmpf;
	T_CMBX cmbx;
	
	/* %jp{�Œ蒷�������v�[������} */
	cmpf.mpfatr = TA_TFIFO;					
	cmpf.blkcnt = 3;						
	cmpf.blksz  = sizeof(T_PRINT_MSG);		
	cmpf.mpf    = NULL;						
	mpfid = acre_mpf(&cmpf);

	/* %jp{���[���{�b�N�X����} */
	cmbx.mbxatr  = TA_TFIFO | TA_TFIFO;		
	cmbx.maxmpri = 1;						
	cmbx.mprihd  = NULL;					
	mbxid = acre_mbx(&cmbx);

	/* %jp{�^�X�N�N��} */
	act_tsk(TSKID_PRINT);
	act_tsk(TSKID_SAMPLE1);
	act_tsk(TSKID_SAMPLE2);
	act_tsk(TSKID_SAMPLE3);
	act_tsk(TSKID_SAMPLE4);
	act_tsk(TSKID_SAMPLE5);
}


/** %jp{�K���Ȏ��ԑ҂�} */
void rand_wait(void)
{
	dly_tsk(rand() % 1000 + 100);	
}


/** %jp{��ԕ\��} */
void print_state(int num, char *text)
{
	T_PRINT_MSG *msg;
	VP  mem;
	
	/* %jp{�������擾} */
	get_mpf(mpfid, &mem);
	msg = (T_PRINT_MSG *)mem;

	/* %jp{�����񐶐�} */
	sprintf(msg->text, "%d : %s", num, text);

	/* %jp{�\���^�X�N�ɑ��M} */
	snd_mbx(mbxid, (T_MSG *)msg);
}


/** %jp{�T���v���^�X�N} */
void Sample_Task(VP_INT exinf)
{
	int num;

	num = (int)exinf;

	/* %jp{������N�w�҂̐H���̖��} */
	for ( ; ; )
	{
		/* %jp{�K���Ȏ��ԍl����} */
		print_state(num, "thinking");
		rand_wait();

		/* %jp{���E�̃t�H�[�N�����܂Ń��[�v} */
		for ( ; ; )
		{
			/* %jp{�����珇�Ɏ��} */
			wai_sem(LEFT(num));
			if ( pol_sem(RIGHT(num)) == E_OK )
			{
				break;	/* %jp{������ꂽ} */
			}
			sig_sem(LEFT(num));	/* %jp{���Ȃ���Η���} */
			
			/* %jp{�K���Ȏ��ԑ҂�} */
			print_state(num, "hungry");
			rand_wait();

			/* %jp{�E���珇�Ɏ��} */
			wai_sem(RIGHT(num));
			if ( pol_sem(LEFT(num)) == E_OK )
			{
				break;	/* %jp{������ꂽ} */
			}
			sig_sem(RIGHT(num));	/* %jp{���Ȃ���Η���} */

			/* %jp{�K���Ȏ��ԑ҂�} */
			print_state(num, "hungry");
			rand_wait();
		}
		
		/* %jp{�K���Ȏ��ԁA�H�ׂ�} */
		print_state(num, "eating");
		rand_wait();
		
		/* %jp{�t�H�[�N��u��} */
		sig_sem(LEFT(num));
		sig_sem(RIGHT(num));
	}
}


/** %jp{�\���^�X�N} */
void Sample_Print(VP_INT exinf)
{
	T_PRINT_MSG *msg;

	for ( ; ; )
	{
		rcv_mbx(mbxid, (T_MSG **)&msg);
		printf("%s\n", msg->text);
		rel_mpf(mpfid, msg);
	}
}



/* end of file */
