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


//  メッセージパケット定義
typedef struct
{
    T_MSG       msg;        //  メッセージヘッダ
    ID          taskID;     //  送信側タスクID
} S_MSGPK;

//------------------------------------------------
//  概  要：MAINタスク
//------------------------------------------------
void task_main(VP_INT exinf)
{
    S_MSGPK * pMsg = NULL;

    while(1)
    {
        //  メールボックス受信
        rcv_mbx(MBX1_ID, (T_MSG **)&pMsg);

        //  開封が終わったとしてタスクを起床する
        printf("a");
    }

    return;
}
//------------------------------------------------
//  概  要：メールボックス送信用処理
//------------------------------------------------
void subfunc(void)
{
    //  ローカル変数としてメッセージパケットを作成
    S_MSGPK msgpkt;

    //  自タスクID取得
    get_tid(&msgpkt.taskID);

    //  メッセージの送信
    snd_mbx(MBX1_ID, (T_MSG *)&msgpkt);

    //  受信側の開封まで眠る
    slp_tsk();
}
//------------------------------------------------
//  概  要：練習用TASK1関数
//------------------------------------------------
void TASK1(VP_INT exinf)
{
    while(1)
    {
        subfunc();
    }

    return;
}