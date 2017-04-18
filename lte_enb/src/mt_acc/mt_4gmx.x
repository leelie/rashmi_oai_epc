/********************************************************************20**

     Name:

     Type:     C File.

     Desc:   The upper arm to lower arm and vice versa communication channel

     File:     mt_4gmx.x

     Sid:      mt_4gmx.x@@/main/1 - Mon Aug 29 22:31:39 2011

     Prg:

************************************************************************/
#ifndef __MT4GMX_X__
#define __MT4GMX_X__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SS_4GMX_UCORE

typedef struct ssRegIcpuCfg
{
   U32 Ent;                      /* Entity ID */
   U32 Inst;                     /* Instance ID */
   U32 CoreId;                   /* Core instance ID */
} SsRegIcpuCfg;

extern S16 uarmInit(void);
extern S16 uarmDrvrInit(void);
extern S16 uarmPstTsk(Pst *pst, Buffer *mbuf);
extern S16 uarmIsTsk(Inst inst);
#endif   /* SS_4GMX_UCORE */
#ifdef __cplusplus
}
#endif

#endif


/********************************************************************30**

         End of file:     mt_4gmx.x@@/main/1 - Mon Aug 29 22:31:39 2011

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

   ver        pat        init                  description
---------  ---------  ----------  -------------------------------------
/main/1      --------     ------    1. Initial release
*********************************************************************91*/