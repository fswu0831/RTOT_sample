#include "kernel.h"
#include "kernel_id.h"
#include "HelloWorld.h"
#include "stdafx.h"
#include "itron.h"
#include "ostimer.h"
#include "wintimer.h"
#include "targetver.h"
#include <stdlib.h>
#include <stdio.h>

void Task1(void);
void task_main(INT stacd);


//  ���b�Z�[�W�p�P�b�g��`
typedef struct
{
    T_MSG       msg;        //  ���b�Z�[�W�w�b�_
    ID          taskID;     //  ���M���^�X�NID
} S_MSGPK;

//------------------------------------------------
//  �T  �v�FMAIN�^�X�N
//------------------------------------------------
void task_main(VP_INT exinf)
{
    S_MSGPK * pMsg = NULL;

    while(1)
    {
        //  ���[���{�b�N�X��M
        rcv_mbx(MBX1_ID, (T_MSG **)&pMsg);

        //  �J�����I������Ƃ��ă^�X�N���N������
        printf("a");
    }

    return;
}
//------------------------------------------------
//  �T  �v�F���[���{�b�N�X���M�p����
//------------------------------------------------
void subfunc(void)
{
    //  ���[�J���ϐ��Ƃ��ă��b�Z�[�W�p�P�b�g���쐬
    S_MSGPK msgpkt;

    //  ���^�X�NID�擾
    get_tid(&msgpkt.taskID);

    //  ���b�Z�[�W�̑��M
    snd_mbx(MBX1_ID, (T_MSG *)&msgpkt);

    //  ��M���̊J���܂Ŗ���
    slp_tsk();
}
//------------------------------------------------
//  �T  �v�F���K�pTASK1�֐�
//------------------------------------------------
void TASK1(VP_INT exinf)
{
    while(1)
    {
        subfunc();
    }

    return;
}