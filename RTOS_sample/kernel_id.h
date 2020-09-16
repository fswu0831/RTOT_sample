


/* ------------------------------------------------------------------------ */
/*  HOS-V4a  kernel configuration                                           */
/*    kernel object ID definition                                           */
/*                                                                          */
/* ------------------------------------------------------------------------ */


#ifndef __KERNEL__kernel_id_h__
#define __KERNEL__kernel_id_h__



/* Task object ID definetion */

#define TSK1_ID		1
#define TSK2_ID		2
#define TSK3_ID		3
#define TSK4_ID		4

#ifdef  TMAX_TSKID
#undef  TMAX_TSKID
#endif

#define TMAX_TSKID		8



/* Semaphore object ID definetion */


#ifdef  TMAX_SEMID
#undef  TMAX_SEMID
#endif

#define TMAX_SEMID		8



/* event flag ID definetion */

#ifdef  TMAX_FLGID
#undef  TMAX_FLGID
#endif

#define TMAX_FLGID		15



/* Data queue object ID definetion */


#ifdef  TMAX_DTQID
#undef  TMAX_DTQID
#endif

#define TMAX_DTQID		15



/* Mtxaphore object ID definetion */


#ifdef  TMAX_MTXID
#undef  TMAX_MTXID
#endif

#define TMAX_MTXID		15



/* time tic */
#define TIC_NUME		(10)
#define TIC_DENO		(1)


/* Semaphore object ID definetion */


#ifdef  TMAX_CYCID
#undef  TMAX_CYCID
#endif

#define TMAX_CYCID		8




#endif	/* __KERNEL__kernel_id_h__ */


/* ------------------------------------------------------------------------ */
/*  End of file                                                             */
/* ------------------------------------------------------------------------ */
