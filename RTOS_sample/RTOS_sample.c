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

#pragma comment(lib, "winmm.lib")   // winmm.lib‚ðŽg—p‚·‚é

void create_object(void);
void task_main(INT stacd);
void task_sub(INT stacd);
void task_rcv(INT stacd);


struct{
	ID tskid;
	T_CTSK info;
} tsk_info[]={
	{TSK1_ID,{0,TA_HLNG,TA_HLNG,1,256}},
	{TSK2_ID,{0,TA_HLNG,TA_HLNG,2,256}},
	{TSK3_ID,{0,TA_HLNG,TA_HLNG,3,256}},
	{TSK4_ID,{0,TA_HLNG,TA_HLNG,4,256}}

};
#define TSKID_MAX 4


struct {
	ID polid;
	T_CMPF info;
} pol_info[]={
	{POL1_ID, {0,TA_TFIFO,4,80}}, //80
	{POL2_ID, {0,TA_TFIFO,4,128}},//128
	{POL3_ID, {0,TA_TFIFO,4,256}}//256
};

#define POLID_MAX 3

struct{
	ID mbxid;
	T_CMBX info;
} mbx_info[]={
	{MBX1_ID,  {0,TA_TFIFO, 4}},//4
	{MBX2_ID,  {0,TA_TFIFO, 4}},
	{MBX3_ID,  {0,TA_TFIFO, 4}}
};

#define MBXID_MAX 3


void create_object(void) {
	ER ercd;
	INT i;
	for(i=0;i<TSKID_MAX;i++){
		ercd=cre_tsk(tsk_info[i].tskid,&tsk_info[i].info);
		
		if(ercd!=E_OK){
			printf("creat task");
		}
	}

	for(i=0;i<POLID_MAX;i++){
		//ercd=cre_mpf(pol_info[i].polid,&pol_info[i].info); 
		ercd=acre_mpf(&pol_info[i].info);
		if(ercd!=E_OK){

		}
	}

	for(i=0;i<MBXID_MAX;i++){
		//ercd=cre_mbx(pol_info[i].polid,&pol_info[i].info);
		ercd=acre_mbx(&mbx_info[i].info);
		if(ercd!=E_OK){

		}
	}

	ercd=sta_tsk(TSK1_ID,0);
	if(ercd!=E_OK){
	}

}

void task_main(INT stacd)
{
	ER ercd;
	INT loop;
	INT i;
	VP mba;
	B *pt;
	//printf("1");
	ercd=sta_tsk(TSK2_ID,0);
	if(ercd=E_OK){
		
	}
	ercd=sta_tsk(TSK3_ID,1);
	if(ercd=E_OK){
	}
	ercd=sta_tsk(TSK4_ID,0);
	if(ercd=E_OK){
	}

	for(loop=0;;loop++){
		if(loop>9)
			loop=0;
		dly_tsk(1000);
		ercd=get_mpf(POL1_ID,&mba);
		if(ercd!=E_OK){
	}
	pt=(B *)mba+sizeof(T_MSG);
	for(i=0;i<=loop;i++)
		*pt++='0'+loop;
	*pt=0;
	ercd=snd_mbx(MBX1_ID,(T_MSG *) mba);
	}
}

B set_char[2]={
	'@',
	'#'
};

ID get_polid[2]={
	POL2_ID,
	POL3_ID
};

ID rel_polid[2]={
	POL1_ID,
	POL2_ID
};

ID rcv_mbxid[2]={
	MBX1_ID,
	MBX2_ID
};

ID snd_mbxid[2]={
	MBX2_ID,
	MBX3_ID
};

void task_sub(INT stacd)
{
ER ercd;
VP rcv_blk;
B *pt;
VP snd_blk;
B *pt2;
B c;
	//c=putchar(stacd);
	c=set_char[stacd];

	for(;;){
		ercd=rcv_mbx(rcv_mbxid[stacd],(T_MSG **) &rcv_blk);
		if(ercd!=E_OK){
		}
		pt=(B *)rcv_blk+sizeof(T_MSG);
		ercd=get_mpf(get_polid[stacd],&snd_blk);
		if(ercd!=E_OK){
		}
		pt2=(B *)snd_blk+sizeof(T_MSG);
		for(;;){
			if(*pt==0){
				*pt=0;
				break;
			}
			*pt2++=*pt++;
			*pt2++=c;
		}

		ercd=rel_mpf(rel_polid[stacd],rcv_blk);
		if(ercd!=E_OK){
		}
		ercd=snd_mbx(snd_mbxid[stacd],(T_MSG *) snd_blk);
		if(ercd!=E_OK){
		}
	}
}
 
void task_rcv(INT stacd)
{
	ER ercd;
	VP mba;
	for(;;){
		ercd=rcv_mbx(MBX3_ID,(T_MSG **) &mba);
		if(ercd!=E_OK){
			printf("%lf",mba);
		}

		ercd=rel_mpf(POL3_ID,mba);
		if(ercd!=E_OK){
			
		}
	}
}


