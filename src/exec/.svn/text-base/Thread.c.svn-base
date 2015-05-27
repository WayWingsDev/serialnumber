/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   Thread.cpp
 *
 * Project:
 * --------
 *   Maui META APP
 *
 * Description:
 * ------------
 *   MF_Setup.txt file handler source
 *
 * Author:
 * -------
 *  Xuhua (mtk70506)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
****************************************************************************/



#include <windows.h>
#include <utility.h>

#include "general.h"
#include "thread.h"
//#include "ExecFunc.h"

extern kal_int32 CVICALLBACK SNWriteThread (void *pParaData);
extern kal_int32 CVICALLBACK EdgeCardThread (void *pParaData);
extern kal_int32 CVICALLBACK ATParseThread (void *pParaData);
extern kal_int32 CVICALLBACK ATParseThread2 (void *pParaData);
extern kal_int32 CVICALLBACK MetaThread (void *pParaData);

static kal_int32 poolThreadHandle;
static kal_int32 ThreadFuncIds [ THREAD_NUM_MAX ]; 
static HANDLE hStopATThreadEvent[2];
static HANDLE hStartATThreadEvent[2];
clock_t StartTime_g;

HANDLE GetStopATThreadEvent ( kal_uint8 i )
{
	return hStopATThreadEvent[i];
}

HANDLE GetStartATThreadEvent ( kal_uint8 i )
{
	return hStartATThreadEvent[i];
}

void SetStartATThreadEvent ( kal_uint8 i )
{
	ResetEvent ( hStartATThreadEvent[i] );
	SetEvent  ( hStartATThreadEvent [i] );
}

void InitStopATThreadEvent ( void )
{
	int i;
	for (i = 0; i<2; i++)
	{
		hStopATThreadEvent[i]= CreateEvent(NULL, FALSE, FALSE, NULL);
		ResetEvent ( hStopATThreadEvent[i] );

		hStartATThreadEvent [i]= CreateEvent(NULL, FALSE, FALSE, NULL);
		ResetEvent ( hStartATThreadEvent[i] );
	}
}

void DeInitStopATThreadEvent ( void )
{
	int i;
	for (i = 0; i<2; i++)
	{
		CloseHandle ( hStopATThreadEvent[i] );
		CloseHandle ( hStartATThreadEvent[i] );
	}
	
}

void SetStopATThreadEvent ( void  )
{
	
	int i;
	for (i = 0; i<2; i++)
	{
		ResetEvent ( hStopATThreadEvent[i] );
		SetEvent ( hStopATThreadEvent[i] ); 
		
		ResetEvent ( hStartATThreadEvent[i] );
		SetEvent  ( hStartATThreadEvent [i] );
	}
}
//---------------------------------------------------------------------------
kal_int32 InitThreadPool ( kal_int32 iThreadNumber )
{
	InitStopATThreadEvent ();
	
 	if ( CmtNewThreadPool ( iThreadNumber, &poolThreadHandle ) ){

		 MessagePopup ("WARNING", "Create Thread fail!");
	
	}
		
	ATParseThreadExec ();

    return 0;

}     

//---------------------------------------------------------------------------

kal_int32 EdgeCardThreadExec ( HANDLE hCOM ){

	if ( CmtScheduleThreadPoolFunction ( poolThreadHandle,
                    EdgeCardThread, hCOM, &ThreadFuncIds[1] ) )
       {
                    
    		MessagePopup ("WARNING", "Executive Thread fail!");
       }

	if ( CmtWaitForThreadPoolFunctionCompletion ( poolThreadHandle,
                    ThreadFuncIds[1], OPT_TP_PROCESS_EVENTS_WHILE_WAITING ) ){

		 MessagePopup ("WARNING", "Exit Thread fail!");
	}
	                       
	CmtReleaseThreadPoolFunctionID ( poolThreadHandle, ThreadFuncIds[1] ); 
    return 0;
	
}

//---------------------------------------------------------------------------
kal_int32 ATParseThreadExec ( void )
{

	if ( CmtScheduleThreadPoolFunction ( poolThreadHandle,
              ATParseThread, NULL, &ThreadFuncIds[2] ) )
      {
                    
    			MessagePopup ("WARNING", "Executive Thread fail!");
	}

       	if ( CmtScheduleThreadPoolFunction ( poolThreadHandle,
              ATParseThread2, NULL, &ThreadFuncIds[4] ) )
      {
                    
    			MessagePopup ("WARNING", "Executive Thread fail!");
	}
    return 0;
	
}

void WaitForATParseThread ( void )
{
	if ( CmtWaitForThreadPoolFunctionCompletion ( poolThreadHandle,
                    ThreadFuncIds[2], OPT_TP_PROCESS_EVENTS_WHILE_WAITING ) )
       {

		 MessagePopup ("WARNING", "Exit Thread fail!");
	}

	if ( CmtWaitForThreadPoolFunctionCompletion ( poolThreadHandle,
                    ThreadFuncIds[4], OPT_TP_PROCESS_EVENTS_WHILE_WAITING ) )
       {

		 MessagePopup ("WARNING", "Exit Thread fail!");
	}
	                       
	CmtReleaseThreadPoolFunctionID ( poolThreadHandle, ThreadFuncIds[2] ); 
	CmtReleaseThreadPoolFunctionID ( poolThreadHandle, ThreadFuncIds[4] ); 
}


//---------------------------------------------------------------------------
extern void UpdateLog ( kal_uint8 *pBuf, kal_uint16 iStep );
kal_int32 SNWriteThreadExec ( void )
{
	if ( CmtScheduleThreadPoolFunction ( poolThreadHandle,
                    SNWriteThread, NULL, &ThreadFuncIds[0] ) )
       {
                    
    		MessagePopup ("WARNING", "Executive Thread fail!");
       }

	 
	if ( CmtWaitForThreadPoolFunctionCompletion ( poolThreadHandle,
                    ThreadFuncIds[0], OPT_TP_PROCESS_EVENTS_WHILE_WAITING ) ){

		 MessagePopup ("WARNING", "Exit Thread fail!");
	}

	CmtReleaseThreadPoolFunctionID ( poolThreadHandle, ThreadFuncIds[0] );  

    	return 0;
	
}
//---------------------------------------------------------------------------
kal_int32 MetaThreadExec ( void ) {

	if ( CmtScheduleThreadPoolFunction ( poolThreadHandle,
                    MetaThread, NULL, &ThreadFuncIds[3] ) ){
                    
    	MessagePopup ("WARNING", "Executive Thread fail!");
    }

	if ( CmtWaitForThreadPoolFunctionCompletion ( poolThreadHandle,
                    ThreadFuncIds[3], OPT_TP_PROCESS_EVENTS_WHILE_WAITING ) ){

		 MessagePopup ("WARNING", "Exit Thread fail!");
	}
	                       
	CmtReleaseThreadPoolFunctionID ( poolThreadHandle, ThreadFuncIds[3] ); 
    return 0;
	
}

//---------------------------------------------------------------------------
kal_int32 DeInitThreadPool ( void )
{
		
	SetStopATThreadEvent ();
	
	WaitForATParseThread ();
	
	DeInitStopATThreadEvent ();
	
	CmtDiscardThreadPool ( poolThreadHandle );
    return 0;
    
}




