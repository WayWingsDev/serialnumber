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
#include <ansi_c.h>
#include <cvirte.h> 
#include <userint.h>

#include "context.h" 
#include "general.h"

#include <formatio.h>   
#include "MFSetupUtil.h"
#include "rs232Module.h"
#include "Atprocess.h"

#include "thread.h"

#include <interface.h>
 #include <xboot.h>

extern baudrate_struct g_Baudrate_Table[];
extern kal_bool GetBootStopFlag ( void );
extern void SetBootStopFlag ( kal_bool enable );
extern HANDLE GetInProcessEvent (kal_uint8 i);
extern void Enable_Timer ( kal_bool );
extern void SetTimerInterval ( kal_uint32 iInterval );
extern E_COM_NUMBER GetCOMPort ( void );
extern UART_BAUDRATE GetBaudRate ( void );
extern void UpdateLog ( kal_uint8 *pBuf, kal_uint16 iStep );
extern void swap_c ( kal_uint8* x, kal_uint8* y );
kal_bool GetPDUToBuf ( kal_uint8* pPDUBuf, E_AT_RESULT_TYPE *pState , kal_uint16 nLF );

AT_THREAD_CONTEXT g_AT;

extern HANDLE hCOM1;

//------------------------------------------------------
kal_int32 CVICALLBACK ATParseThread ( void *pParaData )
{

	while ( 1 )
	{
		WaitForSingleObject ( GetStartATThreadEvent (0), INFINITE ); 
		if( WaitForSingleObject ( GetStopATThreadEvent(0), 0 ) == WAIT_OBJECT_0 )
		{
			break;
		}
		
		if ( g_AT.cb.FuncExec )
		{
			g_AT.cb.FuncExec ();
		}

		g_AT.cb.FuncExec = NULL;

	}
	return 0;
}

//------------------------------------------------------
kal_int32 CVICALLBACK ATParseThread2 ( void *pParaData )
{
	while ( 1 )
	{
		WaitForSingleObject ( GetStartATThreadEvent (1), INFINITE ); 
		if( WaitForSingleObject ( GetStopATThreadEvent(1), 0 ) == WAIT_OBJECT_0 )
		{
			break;
		}
		
		if ( g_AT.cb2.FuncExec )
		{
			g_AT.cb2.FuncExec ();
		}
		g_AT.cb2.FuncExec = NULL;
		
	}
	return 0;
}
//------------------------------------------------------ 
void ActiveThread_Exec ( EXEC_FUNC func )
{
	g_AT.cb.FuncExec = func;
	SetStartATThreadEvent (0);
	return;
}
//------------------------------------------------------ 
void ActiveThread_Exec2 ( EXEC_FUNC func )
{
	g_AT.cb2.FuncExec = func;
	SetStartATThreadEvent (1);
	return;
}
//------------------------------------------------------         
void SetATRequest ( kal_uint8* strATCmd, kal_uint8* strExpectedResult, kal_int32 iTimeOut )
{	
	g_AT.request.pstrATCmd = strATCmd;
	g_AT.result.pstrExpectedResult = strExpectedResult;    
	g_AT.request.iTimeOut = iTimeOut;
}



//------------------------------------------------------         
S_AT_RESULT GetATResult ()
{
	return g_AT.result;
}
//------------------------------------------------------    
HANDLE GetWriteEvent ()
{
	return g_AT.event.hWriteEvent;
}
//------------------------------------------------------    
HANDLE GetReadEvent ()
{
	return g_AT.event.hReadEvent;
}
//------------------------------------------------------    
HANDLE GetInProcessEvent (kal_uint8 i)
{
	return g_AT.event.hInProgressEvent[i];
}

//------------------------------------------------------    
kal_bool COMContextInit (E_COM_NUMBER eComPort, UART_BAUDRATE eBaudRate )
{
	g_AT.event.hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_AT.event.hReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_AT.event.hInProgressEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_AT.event.hInProgressEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if ( NULL == g_AT.event.hWriteEvent 
		|| NULL == g_AT.event.hReadEvent
		|| NULL == g_AT.event.hInProgressEvent[0] )
	{

	}
	
	ResetEvent ( GetInProcessEvent(0) );
	ResetEvent ( GetInProcessEvent(1) );
	
	return ComportInit ( eComPort, eBaudRate );
}

//------------------------------------------------------    
kal_bool COMContextDeInit (E_COM_NUMBER eComPort, UART_BAUDRATE eBaudRate )
{

	SetBootStopFlag ( KAL_TRUE );
	
	SetEvent ( g_AT.event.hInProgressEvent[0] );	
	SetEvent ( g_AT.event.hInProgressEvent[1] );	
	Sleep ( 0.4 );  //wait for com thread exit
	//CloseHandle ( g_AT.event.hWriteEvent );
	//CloseHandle ( g_AT.event.hReadEvent );
	//CloseHandle ( g_AT.event.hInProgressEvent );
	
	return ComportDeInit ( eComPort, eBaudRate );
}
//------------------------------------------------------ 
void SetCbRecArg ( E_COM_NUMBER eCom, kal_uint8* pPDU, kal_uint16 length )
{
	g_AT.cb.eCom = eCom;
	g_AT.cb.pBuf = pPDU;
	g_AT.cb.iLength = length;
}

//------------------------------------------------------ 
void SetCbGetPduArg (kal_uint8* pPDUBuf, E_AT_RSP_STATUS *pState , kal_uint16 nLF ) 
{
	g_AT.cb2.pPDUBuf = pPDUBuf;
	g_AT.cb2.pState = pState;
	g_AT.cb2.nLF = nLF;
}


//------------------------------------------------------ 
void WritePDU_Exec ( void )
{
	WritePDU ( g_AT.cb.eCom, g_AT.cb.pBuf, g_AT.cb.iLength );
}
//------------------------------------------------------ 
void GetDeviceData_Exec ( void )
{
	GetDeviceData ( g_AT.cb.eCom );
}

//------------------------------------------------------ 
void GetPDUToBuf_Exec ( void )
{
	GetPDUToBuf ( g_AT.cb2.pPDUBuf, g_AT.cb2.pState,  g_AT.cb2.nLF ); 
}

//------------------------------------------------------ 
void SetTimeOutFlag ( kal_bool bFlag )
{
	g_AT.bTimerOut = bFlag;
}

//------------------------------------------------------ 
kal_bool GetTimeOutFlag ( void )
{
	return g_AT.bTimerOut ;
}

//------------------------------------------------------ 
kal_bool WriteCommand ( E_COM_NUMBER eComPort, S_AT_REQUEST tRequest, S_AT_RESULT *ptResult )
{
	kal_int32 t_out;
	E_AT_RSP_STATUS eState;
	
	ResetEvent ( GetWriteEvent() );
	ResetEvent ( GetInProcessEvent(0) );  //start cmd
	ResetEvent ( GetInProcessEvent(1) );  
	
	ClearAllBuff ( eComPort );

	t_out = tRequest.iTimeOut;

	SetCbRecArg ( eComPort, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd) );
	//ActiveThread_Exec ( WritePDU_Exec );  //write cmd
	WritePDU_Exec ();
	
	if( WaitForSingleObject ( GetWriteEvent (), t_out ) == WAIT_TIMEOUT )
	{
		ptResult->eATResult = AT_WRITE_FAIL;
		return KAL_FALSE;
	}
	return KAL_TRUE;
	
}

//---------------------------------------------------------
kal_bool SkipComma ( kal_char *ptr, kal_int32 *ri, kal_int32 size)
{
	//*ri = 0;
	
	while( (*ri) < size && *(ptr+(*ri))!=',')
		(*ri)++;

	if (*ri == size)
	{
		( *ri )--;
		return KAL_FALSE;
	}
	else
		return KAL_TRUE;
}
//---------------------------------------------------------
kal_bool IsUnsolicited(kal_uint8* cmd, ATParamElem* lst)
{
      ATParamElem elem;

	if( strcmp(cmd, "RING" ) )
	{
		return KAL_TRUE;
	}

	if( lst == NULL)
		return KAL_FALSE;

	if( lst->type != AT_STRING )
		return KAL_FALSE;

	// Then handled unsolicited command is listed here
	// This should take care of all the unsolicited command
	// listed in spec.
	if(
	   strcmp (lst->str_value, "RING")
	|| strcmp (lst->str_value, "NO CARRIER")
	|| strcmp (lst->str_value, "+CMT")
	|| strcmp (lst->str_value, "+CBM")
	|| strcmp (lst->str_value, "+CDS")
	|| strcmp (lst->str_value, "+CMTI")
	|| strcmp (lst->str_value, "+CBMI")
	|| strcmp (lst->str_value, "+CDSI")
	|| strcmp (lst->str_value, "+CLIP")
	|| strcmp (lst->str_value, "+EADC")
	|| strcmp (lst->str_value, "+GPIOS")
	|| strcmp (lst->str_value, "+EKPDS")
	|| strcmp (lst->str_value, "+BATSR")
	)
		return KAL_TRUE;

	else
		return KAL_FALSE;
}
//---------------------------------------------------------
kal_bool IsNumber ( kal_char *ptr )
{
	
	kal_int32 len = strlen (ptr),i;

	for ( i =0; i<len; i++ )
	{
		if( (*(ptr+i) < '0')
		||  (*(ptr+i) > '9')
		)
		{
			return KAL_FALSE;
		}
	}
	return KAL_TRUE;
}

//---------------------------------------------------------
bool GetParam(char *ptr, ATParamElem* elem, bool isString)
{

	if ( isString )
	{
		elem->type = AT_STRING;
		elem->str_value = ptr;
	}
	else
	{
		if ( strlen(ptr)==0 )
			elem->type = AT_OMIT;

		
		if( IsNumber(ptr) )
		{
			elem->type = AT_INTEGER;
			elem->int_value = atoi(ptr);
		}
		else
		{
			elem->type = AT_STRING;
			elem->str_value = ptr;
		}
	}

    return KAL_TRUE;
}

//---------------------------------------------------------
kal_bool GetPDUToBuf ( kal_uint8* pPDUBuf, E_AT_RESULT_TYPE *pState , kal_uint16 nLF )
{
	kal_uint8 ch, *pBuf = pPDUBuf;
	kal_uint16 iCount = 0;
	kal_uint16 iValid = 0x0;
	E_AT_RSP_STATUS State = STATE_WAIT_1ST_CR;
	*pState = AT_TIMEOUT;

	while( 1 ) 
	{
		if( WaitForSingleObject ( GetInProcessEvent (1), 0 ) == WAIT_OBJECT_0 )
		{
			break;
		}
  		
		if ( GetRawData ( &ch ))
		{
			 if ( (ch == 'A' )  && (0 == iValid) )
			{
				iValid = 0x01;
				*pBuf++ = ch;
			}else if ( (ch == 'T' )  && (0x01 == iValid)  )
			{
				 iValid = 0x02;
				*pBuf++ = ch;
			} else if (0x02 == iValid )
			{
				*pBuf++ = ch;
			}
			
			switch ( State )
			{
			case STATE_WAIT_1ST_CR:
				if( ch == CR )
					State = STATE_WAIT_1ST_LF;
				break;

			case STATE_WAIT_1ST_LF:
				if ( ch == LR )
				{
					State = STATE_WAIT_1ST_CR;
					if ( ++iCount == nLF )
					{
						*pBuf = '\0'; 
						*pState = AT_SUCCESS;
						 SetEvent ( GetReadEvent () ); 
						return KAL_TRUE;
					}
				}
				break;

			default:
				break;
			}     
			
		} //get byte

	}
	return KAL_FALSE;  
}
				
//-----------------------------------------
kal_bool AnalyingRespString ( S_AT_RESULT *ptResult )
{

	if ( -1 == FindPattern ( ptResult->pstrReceResult, 0, -1, ptResult->pstrExpectedResult, 0, 0 ) )
	{
		ptResult->eATResult = AT_PARSE_FAIL;
		return KAL_FALSE;
	}
	
	ptResult->eATResult = AT_SUCCESS;
	return KAL_TRUE;
}
//-----------------------------------------
kal_bool GetStringToBuf (kal_uint8 *pSrc, kal_uint8 *ptr, kal_int32* wi, kal_int32* readIndex, const kal_int32 size)
{
	*wi = 0;
	
	(*readIndex)++; // Skip one "

	while ( pSrc[(*readIndex)] != '"' )
	{
		switch ( pSrc[(*readIndex)] )
		{
			case '\0':
				return KAL_FALSE;

				break;
			default:
				ptr[(*wi)++] = pSrc[(*readIndex)++];
				break;
		}

		if((*readIndex)>=size)
			return KAL_FALSE;
	}

	ptr[(*wi)]='\0';

	return KAL_TRUE;
}
//-----------------------------------------
kal_bool  GetRespContext ( S_AT_RESULT *ptResult, kal_uint8 *pContext, kal_int32* len )
{

	kal_int32 size = strlen ( ptResult->pstrReceResult );
	kal_int32 readIndex = 0, tmpWI = 0;
	
	kal_uint8 endString[256] = "";
	kal_uint8 command[256] = "";
	
	kal_bool ignoreWhiteSpace = KAL_FALSE;
	kal_bool stag = KAL_FALSE;
	kal_bool getDbQEmptyString = KAL_FALSE;
	
	while ( readIndex != (size+1) )
	{

		switch ( ptResult->pstrReceResult[readIndex] )
		{
			case '\0':

				break;

			case '"':		

				if( !GetStringToBuf (ptResult->pstrReceResult, pContext, len, &readIndex, (size+1)))
				return KAL_FALSE;

				break;
			
			default:
				break;
		}
		readIndex++;
		
	}
	
	return KAL_TRUE;
}

//---------------------------------------------------
kal_bool ParseAtResult ( E_COM_NUMBER eComPort, S_AT_RESULT *ptResult, kal_uint16 nLF )
{
	E_AT_RESULT_TYPE eState;
	DWORD wait_result;

	ResetEvent ( GetReadEvent() ); 
	ResetEvent ( GetInProcessEvent(0) );
	ResetEvent ( GetInProcessEvent(1) );
	
	SetCbRecArg ( eComPort, (void*) NULL, 0 );
	ActiveThread_Exec ( GetDeviceData_Exec ); 
	Sleep(50);
	SetCbGetPduArg (  ptResult->pstrReceResult, &eState, nLF );
	ActiveThread_Exec2 ( GetPDUToBuf_Exec );
	
  	  wait_result = WaitForSingleObject ( GetReadEvent(), ptResult->iTimeOut );  
	if ( wait_result == WAIT_TIMEOUT )
	{
		ptResult->eATResult = AT_TIMEOUT;
		return KAL_FALSE;
	}

	ptResult->eATResult = eState;
	
	SetEvent ( GetInProcessEvent(0) );
	SetEvent ( GetInProcessEvent(1) );
	
	return AnalyingRespString ( ptResult );

}

//---------------------------------------------------
kal_bool AT_Preset ( E_COM_NUMBER eComPort, kal_uint16 iTimeOut )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_uint8 strLog[128], icount = 0;

	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd = "AT+ESLP=0\r";
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = malloc ( 256*sizeof (kal_uint8) );

	while ( GetBootStopFlag() != KAL_TRUE )
	{
	
		if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
		{	
			continue; //write fail
		}
		
		if ( ParseAtResult ( eComPort, &tResult, CRLF2 ) )
		{
			if ( AT_SUCCESS == tResult.eATResult )
			{
				break;   //OK
			}
			else if ( AT_PARSE_FAIL == tResult.eATResult )
			{
				continue;  //TODO: result parse fail
			}
		}
		else						  
		{
			if ( icount ++ == 30 )
			{
				sprintf ( strLog,  "     Time Out: Disable sleep time out > 15 s. \n     Please Check uart connection and PS uart in handset!\n" );
				UpdateLog ( strLog, 20 );
				icount = 0;
			}
			continue; //TODO: AT reponse time out
		}

 	}

	free ( tResult.pstrReceResult );
	
	if ( AT_SUCCESS == tResult.eATResult )
	{
		return KAL_TRUE;
	}

	return KAL_FALSE; 	  //timer out / manul stop
}

//---------------------------------------------------
kal_bool WriteBarcodeATMode ( E_COM_NUMBER eComPort, kal_uint8* pBarcode )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;

	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=1,5,\"%s\"\r", pBarcode );
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{	
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	if ( ! ParseAtResult ( eComPort, &tResult , CRLF2) )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == tResult.eATResult )
	{
		return KAL_TRUE;
	}
	//timer out / manul stop
	return KAL_FALSE;
}
//--------------------------------------------------
kal_bool SDSATMode ( E_COM_NUMBER eComPort)
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;

	tRequest.iTimeOut = 5000;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	sprintf ( tRequest.pstrATCmd,  "AT+ESDS=0\r");
	
	tResult.iTimeOut = 5000;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{	
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	if ( ! ParseAtResult ( eComPort, &tResult , CRLF2) )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == tResult.eATResult )
	{
		return KAL_TRUE;
	}
	//timer out / manul stop
	return KAL_FALSE;
}

//---------------------------------------------------
kal_bool ReadBarcodeATMode ( E_COM_NUMBER eComPort, kal_uint8* pBarcode, kal_uint32* len )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;

	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=0,5\r" );
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{					
		//TODO: write fail
	}

	if ( !ParseAtResult ( eComPort, &tResult, CRLF4 ) )
	{
	
	}


	if ( AT_SUCCESS == tResult.eATResult )
	{
		GetRespContext ( &tResult, pBarcode, len );
	}
	else if ( AT_PARSE_FAIL == tResult.eATResult )
	{
			//TODO: result parse fail
	}

	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == tResult.eATResult )
	{
		return KAL_TRUE;
	}
	
	return KAL_FALSE; //timer out / manul stop
}
//---------------------------------------------

kal_bool WriteDataCallATMode ( E_COM_NUMBER eComPort, kal_uint16 id)
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	E_AT_RESULT_TYPE status = AT_SUCCESS;
	
	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	tResult.iTimeOut = 700;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));


	sprintf ( tRequest.pstrATCmd,  "AT+EGTP=%d\r",id);
	
	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{	
		status = tResult.eATResult;
	}
	Sleep(50);
	if ( ! ParseAtResult ( eComPort, &tResult , CRLF2) )
	{
		status = tResult.eATResult;
	}
	if ( status != AT_SUCCESS )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );
		return KAL_FALSE; 
	}
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == status )
	{
		return KAL_TRUE;
	}
	//timer out / mannul stop
	return KAL_FALSE;
}






//---------------------------------------------------
kal_bool WriteIMEIATMode ( E_COM_NUMBER eComPort, IMEISV_struct_T *pIMEI, kal_uint16 id, kal_bool bSVN )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_uint8 strSvn[4], cmd_id;
	E_AT_RESULT_TYPE status = AT_SUCCESS;
	
	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	tResult.iTimeOut = 700;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	/*-- Write imei--*/
	//cmd_id = (0 == id)? 7 : 10; 
	switch(id)
	{
	   case 0:
	   	cmd_id=7;
		break;
	   case 1:
	   	cmd_id=10;
		break;
	   case 2:
	   	cmd_id=11;
		break;
	   case 3:
	   	cmd_id=12;
		break;			
	}	
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=1,%d,\"%s\"\r",cmd_id, pIMEI->imei);
	
	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{	
		status = tResult.eATResult;
	}
	if ( ! ParseAtResult ( eComPort, &tResult , CRLF2) )
	{
		status = tResult.eATResult;
	}
	if ( status != AT_SUCCESS )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );
		return KAL_FALSE; 
	}
	/*
	if ( 0 == id &&  bSVN )
	{
		/* --Write svn--*/
	/*
		Fmt ( strSvn, "%s<%x", pIMEI->svn ); 
		if ( pIMEI->svn < 10)
		{  strSvn[1] = strSvn[0]; strSvn[0] = '0';strSvn[2] = '\0';}
		swap_c ( &strSvn[0], &strSvn[1]);
		
		sprintf ( tRequest.pstrATCmd,  "AT+EGMR=1,9,\"%s\"\r", strSvn);

		if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
		{	
			status = tResult.eATResult;
		}
		
		if (  !ParseAtResult ( eComPort, &tResult , CRLF2) )
		{
			status = tResult.eATResult;
		}
		
	}
       */
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == status )
	{
		return KAL_TRUE;
	}
	//timer out / mannul stop
	return KAL_FALSE;
}
//---------------------------------------------------
kal_bool ReadIMEIATMode ( E_COM_NUMBER eComPort, IMEISV_struct_T *pIMEI, kal_uint16 id )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_uint8 strSvn[4], cmd_id;
	kal_uint32 len;
	E_AT_RESULT_TYPE status = AT_SUCCESS;
		
	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	tResult.iTimeOut = 700;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	// Read imei
	//cmd_id = (0 == id)? 7 : 10; 
	switch(id)
	{
	   case 0:
	   	cmd_id=7;
		break;
	   case 1:
	   	cmd_id=10;
		break;
	   case 2:
	   	cmd_id=11;
		break;
	   case 3:
	   	cmd_id=12;
		break;			
	}	
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=0,%d\r",  cmd_id );
	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{					
		status = tResult.eATResult;
	}
       Sleep(50);
	if ( !ParseAtResult ( eComPort, &tResult, CRLF4 ) )
	{
		status = tResult.eATResult;
	}

	if ( AT_SUCCESS == tResult.eATResult )
	{
		GetRespContext ( &tResult, pIMEI->imei, &len );
	}
	else if ( AT_PARSE_FAIL == tResult.eATResult )
	{
		status = AT_PARSE_FAIL;
	}

	if ( status != AT_SUCCESS )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );
		return KAL_FALSE; 
	}

	/*
	// Read svn
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=0, 9\r" );
	if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
	{					
		status = tResult.eATResult;
	}

	if ( !ParseAtResult ( eComPort, &tResult, CRLF4 ) )
	{
		status = tResult.eATResult;
	}

	if ( AT_SUCCESS == tResult.eATResult )
	{
		GetRespContext ( &tResult, strSvn, &len );
		if ( 2 == len )
		{
			Scan ( strSvn, "%s>%x", (kal_uint32*) &pIMEI->svn);
		}else
		{
			status = AT_PARSE_FAIL;
		}
		
	}
	*/	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == status)
	{
		return KAL_TRUE;
	}
	
	return KAL_FALSE; //timer out / manul stop
}

kal_bool WriteIMEIATMode_r ( E_COM_NUMBER eComPort, IMEISV_struct_T *pIMEI, kal_uint16 id, kal_bool bSVN )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_uint8 strSvn[4], cmd_id;
	E_AT_RESULT_TYPE status = AT_SUCCESS;
	kal_bool xboot_result;
	XBOOT_BOOT_ARG meta_arg;
	int stop=0;
	
	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	tResult.iTimeOut = 700;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

       meta_arg.read_retry_time = 10000;
        meta_arg.read_interval_timeout = 20;
       meta_arg.m_p_stopflag = &stop;
	

	/*-- Write imei--*/
	//cmd_id = (0 == id)? 7 : 10; 
	 switch(id)
	{
	   case 0:
	   	cmd_id=7;
		break;
	   case 1:
	   	cmd_id=10;
		break;
	   case 2:
	   	cmd_id=11;
		break;
	   case 3:
	   	cmd_id=12;
		break;			
	}
	
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=1,%d,\"%s\"\r",cmd_id, pIMEI->imei);
	
	if (  KAL_TRUE!=(xboot_result =  XBOOT_SendCMD_r(&hCOM1, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd)  )) )
	{	
		status = AT_WRITE_FAIL;
	}
	if ( KAL_TRUE!=(xboot_result = XBOOT_Wait4Confirm_r (hCOM1, meta_arg, "OK\r\n")) )
	{
		status = AT_PARSE_FAIL;
	}
	if ( status != AT_SUCCESS )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );
		return KAL_FALSE; 
	}
	
	if ( 0 == id &&  bSVN )
	{
		/* --Write svn--*/
		Fmt ( strSvn, "%s<%x", pIMEI->svn ); 
		if ( pIMEI->svn < 10)
		{  strSvn[1] = strSvn[0]; strSvn[0] = '0';strSvn[2] = '\0';}
		swap_c ( &strSvn[0], &strSvn[1]);
		
		sprintf ( tRequest.pstrATCmd,  "AT+EGMR=1,9,\"%s\"\r", strSvn);

		if (KAL_TRUE!=(xboot_result =  XBOOT_SendCMD_r(&hCOM1, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd)  )) )
		{	
			status = AT_WRITE_FAIL;
		}
		
		if (  KAL_TRUE!=(xboot_result = XBOOT_Wait4Confirm_r (hCOM1, meta_arg, "OK\r\n")) )
		{
			status = AT_PARSE_FAIL;
		}
		
	}
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == status )
	{
		return KAL_TRUE;
	}
	//timer out / mannul stop
	return KAL_FALSE;
}

kal_bool WriteBarcodeATMode_r ( E_COM_NUMBER eComPort, kal_uint8* pBarcode )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_bool xboot_result;
	XBOOT_BOOT_ARG meta_arg;
	int stop=0;
	 meta_arg.read_retry_time = 10000;
        meta_arg.read_interval_timeout = 20;
       meta_arg.m_p_stopflag = &stop;

	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	sprintf ( tRequest.pstrATCmd,  "AT+EGMR=1,5,\"%s\"\r", pBarcode );
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	if ( KAL_TRUE!=(xboot_result =  XBOOT_SendCMD_r(&hCOM1, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd)  )) )
	{	
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	if (  KAL_TRUE!=(xboot_result = XBOOT_Wait4Confirm_r (hCOM1, meta_arg, "OK\r\n")) )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( KAL_TRUE == xboot_result)
	{
		return KAL_TRUE;
	}
	//timer out / manul stop
	return KAL_FALSE;
}
//---------------------------------------------------Add by mtk71262 ---------------
kal_bool SDSATMode_r ( E_COM_NUMBER eComPort)
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_bool xboot_result;
	XBOOT_BOOT_ARG meta_arg;
	int stop=0;
	 meta_arg.read_retry_time = 10000;
        meta_arg.read_interval_timeout = 20;
       meta_arg.m_p_stopflag = &stop;

	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	sprintf ( tRequest.pstrATCmd,  "AT+ESDS=0\r" );
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));

	if ( KAL_TRUE!=(xboot_result =  XBOOT_SendCMD_r(&hCOM1, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd)  )) )
	{	
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	if (  KAL_TRUE!=(xboot_result = XBOOT_Wait4Confirm_r (hCOM1, meta_arg, "OK\r\n")) )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );

		return KAL_FALSE;
	}
	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( KAL_TRUE == xboot_result)
	{
		return KAL_TRUE;
	}
	//timer out / manul stop
	return KAL_FALSE;
}

//---------------------------------------------------

kal_bool AT_Preset_rr( E_COM_NUMBER eComPort, kal_uint16 iTimeOut )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_uint8 strLog[128], icount = 0;

	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd = "AT\r";
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = malloc ( 256*sizeof (kal_uint8) );

	while ( GetBootStopFlag() != KAL_TRUE )
	{
	
		if ( !WriteCommand ( eComPort, tRequest, &tResult ) )
		{	
			continue; //write fail
		}
		Sleep(50);
		if ( ParseAtResult ( eComPort, &tResult, CRLF2 ) )
		{
			if ( AT_SUCCESS == tResult.eATResult )
			{
				break;   //OK
			}
			else if ( AT_PARSE_FAIL == tResult.eATResult )
			{
				continue;  //TODO: result parse fail
			}
		}
		else						  
		{
			if ( icount ++ == 30 )
			{
				sprintf ( strLog,  "     Time Out: Disable sleep time out > 15 s. \n     Please Check uart connection and PS uart in handset!\n" );
				UpdateLog ( strLog, 20 );
				icount = 0;
			}
			continue; //TODO: AT reponse time out
		}

 	}

	free ( tResult.pstrReceResult );
	
	if ( AT_SUCCESS == tResult.eATResult )
	{
		return KAL_TRUE;
	}

	return KAL_FALSE; 	  //timer out / manul stop
}







kal_bool AT_Preset_r (  E_COM_NUMBER eComPort, kal_uint16 iTimeOut )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;
	kal_uint8 strLog[128], icount = 0;
	kal_bool xboot_result;
	XBOOT_BOOT_ARG meta_arg;
	int stop=0;

	meta_arg.read_retry_time = 10000;
       meta_arg.read_interval_timeout = 20;
       meta_arg.m_p_stopflag = &stop;
	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd = "AT+ESLP=0\r";
	
	tResult.iTimeOut = 500;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = malloc ( 256*sizeof (kal_uint8) );

	while ( GetBootStopFlag() != KAL_TRUE )
	{
	     
		if ( KAL_TRUE!=(xboot_result =  XBOOT_SendCMD_r(&hCOM1, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd)  ))  )
		{	

              //sprintf ( strLog,  " write at cmd for sleep fail0");
		//UpdateLog ( strLog, 20 );
		
		continue; //write fail
		}
		
	      // sprintf ( strLog,  " write at cmd for sleep fail 0.5");
	       //UpdateLog ( strLog, 20 );
		
		Sleep(1000);
		if (  KAL_TRUE==(xboot_result = XBOOT_Wait4Confirm_r (hCOM1, meta_arg, "OK\r\n")) )
		{
                    //  sprintf ( strLog,  " write at cmd for sleep fail1");
		      //  UpdateLog ( strLog, 20 );
		
		       break;
		   	       
		}
		else						  
		{    


		     //  sprintf ( strLog,  " write at cmd for sleep fail 1.5");
	            // UpdateLog ( strLog, 20 );
			if ( icount ++ == 30 )
			{
				sprintf ( strLog,  "     Time Out: Disable sleep time out > 15 s. \n     Please Check uart connection and PS uart in handset!\n" );
				UpdateLog ( strLog, 20 );
				icount = 0;
			}
			continue; //TODO: AT reponse time out
		}

 	}

	free ( tResult.pstrReceResult );
	
	if ( KAL_TRUE == xboot_result )
	{
		return KAL_TRUE;
	}

	return KAL_FALSE; 	  //timer out / manul stop
}




kal_bool WriteCDROMATMode ( E_COM_NUMBER eComPort,  kal_uint8 id )
{
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult;

	E_AT_RESULT_TYPE status = AT_SUCCESS;
	kal_bool xboot_result;
	XBOOT_BOOT_ARG meta_arg;
	int stop=0;
	 meta_arg.read_retry_time = 10000;
        meta_arg.read_interval_timeout = 20;
       meta_arg.m_p_stopflag = &stop;
	
	tRequest.iTimeOut = 500;
	tRequest.pstrATCmd =  (kal_uint8*) malloc ( 128*sizeof (kal_uint8) );
	
	tResult.iTimeOut = 700;
	tResult.pstrExpectedResult = "OK";
	tResult.pstrReceResult = (kal_uint8*) malloc ( 1024*sizeof (kal_uint8));
	
	sprintf ( tRequest.pstrATCmd,  "AT+ESWM=3,%d\r\n",id);
	
	if (  KAL_TRUE!=(xboot_result =  XBOOT_SendCMD_r(&hCOM1, tRequest.pstrATCmd, strlen(tRequest.pstrATCmd)  ))  )
	{	
		status = AT_WRITE_FAIL;
	}
	if ( KAL_TRUE!=(xboot_result = XBOOT_Wait4Confirm_r (hCOM1, meta_arg, "OK\r\n")) )
	{
		status = AT_PARSE_FAIL;
	}
	if ( status != AT_SUCCESS )
	{
		free ( tResult.pstrReceResult );
		free ( tRequest.pstrATCmd );
		return KAL_FALSE; 
	}

	
	free ( tResult.pstrReceResult );
	free ( tRequest.pstrATCmd );
	
	if ( AT_SUCCESS == status )
	{
		return KAL_TRUE;
	}
	//timer out / mannul stop
	return KAL_FALSE;
}



