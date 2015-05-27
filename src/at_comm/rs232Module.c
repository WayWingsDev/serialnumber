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
#include "context.h" 
#include "general.h" 

#include <cvirte.h>
#include <userint.h>
#include <cvirte.h>
#include <utility.h>    
#include <formatio.h>      

#include <ansi_c.h>
#include <rs232.h>  


#include "uipara.h"
#include "MFSetupUtil.h"
 
#include "rs232Module.h" 
#include "AtProcess.h"

extern HANDLE GetReadEvent (void);
extern HANDLE GetWriteEvent (void);  
extern HANDLE GetInProcessEvent (kal_uint8 i);
extern baudrate_struct g_Baudrate_Table [];
extern kal_bool GetBootStopFlag ( void );

extern AT_THREAD_CONTEXT g_AT;


S_RS232_QUEUE tQueue;

//------------------------------------------------------
kal_bool ComportInit (E_COM_NUMBER eComPort, UART_BAUDRATE eBaudRate )
{
	kal_uint8 strDrvieName [7];
	kal_uint32  iBaudrate;

	sprintf ( strDrvieName, "COM%d", eComPort );

      Scan ( (kal_uint8*)& g_Baudrate_Table [eBaudRate], "%s>%i", &iBaudrate );  

	switch ( OpenComConfig ( eComPort, strDrvieName, iBaudrate, 0, 8, 1, 0, 0 ) )
	{
		case 0:
			FlushInQ ( eComPort );
			FlushOutQ ( eComPort );
		    //return KAL_FALSE;
		    break;
		
		case -7:
		    MessagePopup ("COMPort Error", "Cannot open port!"); 
			break;
		case -6:
		    MessagePopup ("COMPort Error", "No serial port found!");   
			break;
	    default :
	        MessagePopup ("COMPort Error", "Open Com Port fail!"); 
	        break;
	}
	
	//SetComTime ( eComPort, 5.000 );
	return InitQueue ( &tQueue ); 
}

//------------------------------------------------------
kal_bool ComportDeInit (E_COM_NUMBER eComPort, UART_BAUDRATE eBaudRate )
{

	if ( CloseCom ( eComPort ) ){
	
	   MessagePopup ("COMPort Error", "Close Com Port fail!");   
	   return KAL_FALSE;
	}

	DeInitQueue ( &tQueue );
	
	return KAL_TRUE; 
}



//------------------------------------------------------
kal_bool WritePDU ( E_COM_NUMBER eComPort, kal_uint8* ptr, kal_uint16 length )
{

	kal_int32  nRetryCount = 0;
	kal_int32  nSentBytes = 0;
	kal_int32  iErrorCode;

	while( nSentBytes < length ) {

		int nBytes = 0;
		int nPerSend = 0;

		if( WaitForSingleObject ( GetInProcessEvent(0), 0 ) == WAIT_OBJECT_0 )
		{
			iErrorCode = FlushOutQ ( eComPort );
			FlushQueue ( &tQueue );
			break;
		}
		
		// set send bytes
		nPerSend = length - nSentBytes;
		// write to com
		nBytes = ComWrt ( eComPort, ((kal_uint8*)ptr) + nSentBytes, nPerSend );
		// check result
		if( nBytes < 0 ) {
			// Display the string.
			iErrorCode = ReturnRS232Err ();
			// Free the buffer.
			iErrorCode = FlushOutQ ( eComPort ); 

		} else if ( nBytes < nPerSend ) {
			// update the counts of sent bytes
			nSentBytes += nBytes;
			// Display the string.
			iErrorCode = ReturnRS232Err ();
			// Free the buffer.
			iErrorCode = FlushOutQ ( eComPort ); 
		}
		else {
			// update the counts of sent bytes
			nSentBytes += nBytes;
			// reset retry count and continue to skip retry
			nRetryCount = 0;
			continue;
		}
		// check retry count
		if( 1 <= nRetryCount ) {
			
		}
		// increase retry count
		nRetryCount++;
		// receiver might be in busy status, sleep awhile
		Sleep(10);
	}
	SetEvent ( GetWriteEvent () );  //write finish
	return KAL_TRUE;
}

//------------------------------------------------------
kal_bool GetDeviceData ( E_COM_NUMBER eComPort )
{

	int nBytes = 0, nBytesRead,iErrorCode;
	kal_uint8 tmpBuffer [512];
	
	while(1)
	{
		if( WaitForSingleObject ( GetInProcessEvent(0), 0 ) == WAIT_OBJECT_0 )
		{
			//iErrorCode = FlushInQ ( eComPort );
			FlushQueue ( &tQueue );
			break;
		}

		if( 0 == GetInQLen ( eComPort ) )
		{
			Sleep ( 20);
			continue;
		}

		nBytesRead = GetInQLen ( eComPort );
              if( 512 <= (int) nBytesRead ) 
                   nBytesRead = 512;
		
		nBytes = ReadPDU ( eComPort, tmpBuffer, nBytesRead );  //timerou = 2.0s
		if( nBytes < 0 ) 
		{            
                     // Display the string.
			iErrorCode = ReturnRS232Err ();
			// Free the buffer.
			iErrorCode = FlushInQ ( eComPort );
			return KAL_FALSE;
        	} 
		
		EnQueue ( &tQueue, tmpBuffer, nBytes );
		
		if ( 15 <= GetQueueLength( &tQueue ) )
		{
			//SetEvent ( GetReadEvent () );  //read finish
		}
		else
		{
			//ResetEvent ( GetReadEvent() ); 
		}
	}
	return KAL_TRUE;
}


//------------------------------------------------------
kal_int32 ReadPDU ( E_COM_NUMBER eComPort, kal_uint8* ptr, kal_uint16 length )
{
	return ComRd ( eComPort, ptr, length );
}


//------------------------------------------------------
kal_bool InitQueue ( S_RS232_QUEUE *pQueue )
{
	if ( pQueue->pRawChars = (kal_uint8*) malloc ( QUEUE_MAX_LENGTH * sizeof ( kal_uint8 )))
	{ return KAL_FALSE; }

	pQueue->iHead = 0;
	pQueue->iTail = 0;

	return KAL_TRUE;
}
//------------------------------------------------------
void DeInitQueue ( S_RS232_QUEUE *pQueue )
{
	free ( pQueue->pRawChars );
		
	pQueue->iHead = 0;
	pQueue->iTail = 0;

	return ;
}

//------------------------------------------------------
kal_bool IsQueueEmpty ( S_RS232_QUEUE *pQueue )
{
	return ( pQueue->iHead == pQueue->iTail );
}

//------------------------------------------------------
kal_bool IsQueueFull ( S_RS232_QUEUE *pQueue )
{
	return ( (pQueue->iHead + 1)%QUEUE_MAX_LENGTH == pQueue->iTail );
}

//------------------------------------------------------
kal_int32 GetQueueLength ( S_RS232_QUEUE *pQueue )
{
	if ( pQueue->iHead >= pQueue->iTail )
	{
		return ( pQueue->iHead - pQueue->iTail );
	}
	else 
	{
		return ( pQueue->iHead + QUEUE_MAX_LENGTH - pQueue->iTail );
	}
}
//-------------------------------------------------------
void EnQueue ( S_RS232_QUEUE *pQueue, kal_uint8* pData, kal_uint32 length )
{
	 kal_uint32 i;

	 if ( length > ( QUEUE_MAX_LENGTH - GetQueueLength ( pQueue )))
	 {
	 	Assert (0);
	}

	 for ( i = 0; i < length; i++ )
	 { 
		pQueue->pRawChars [ (pQueue->iHead++)%QUEUE_MAX_LENGTH ] = *( pData++ );  
	 }
} 

//-------------------------------------------------------
kal_uint32 DeQueue ( S_RS232_QUEUE *pQueue, kal_uint8* pData, kal_uint32 length )
{
	 kal_uint32 i;

	 length = ( length > GetQueueLength ( pQueue )) ? GetQueueLength( pQueue ) : length;
	
	 for ( i = 0; i < length; i++ )
	 { 
		*pData++ = pQueue->pRawChars [ (pQueue->iTail++)%QUEUE_MAX_LENGTH ];
	 }
	 return length;
}
//-------------------------------------------------------
kal_uint8 GetByteQueue ( S_RS232_QUEUE *pQueue )
{
	return pQueue->pRawChars [ ( pQueue->iTail++ )%QUEUE_MAX_LENGTH ];
}

//--------------------------------------------------------
void FlushQueue ( S_RS232_QUEUE *pQueue )
{
	pQueue->iHead = 0;
	pQueue->iTail = 0;
	return ;
}

//---------------------------------------------------------
kal_bool GetRawData( kal_uint8 *ch )
{
	if( IsQueueEmpty ( &tQueue ))
		return KAL_FALSE;
	else
		*ch = GetByteQueue ( &tQueue );

	return KAL_TRUE;
}

void ClearAllBuff ( E_COM_NUMBER eComPort )
{
	FlushInQ ( eComPort );
	FlushOutQ ( eComPort );
	FlushQueue ( &tQueue );
}

