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
 *   MfSetupUtil.cpp
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
//--add by mtk71596
#include <windows.h>
#include<winbase.h>
#include <stdio.h>
#include "stdlib.h"//add by mtk71596

//------------------

#include <userint.h>
#include <ansi_c.h>   

#include "interface.h"  
#include "brom.h"
#include <formatio.h>
#include <utility.h>
#include "SLA.h"
#include "thread.h"
#include "execfunc.h"

#include "wmexec.h"
#include "spmeta.h"
//#include "Uipara.h"

 #include"AUTH.h"

 #include"SCERT.h"
#include "HdcpEncryption.h"





extern kal_char * m_exist_symbolic_set[20];
extern kal_char *m_exist_port_set[20];
extern kal_char  s_com_symbol[100];
extern kal_char s_com_port[100];
extern int usb_port;
char *buff;

LPWIN32_FIND_DATA files_data;

extern int CVICALLBACK search_kernel_port(void *functionData);
extern int CVICALLBACK Connect_with_preloader(void *functionData);


//DEFINE_GUID(Guid_ANDROID_USB2Ser,0xA5DCBF10L,0x6530,0x11D2,0x90,0x1F,0x00,0xC0,0x4F,0xB9,0x51,0xED);
static const GUID  Guid_ANDROID_USB2Ser={0xA5DCBF10L,0x6530,0x11D2,{0x90,0x1F,0x00,0xC0,0x4F,0xB9,0x51,0xED}};
#define  PID_ANDROID       "2000"
#define  VID_ANDROID       "0E8D"
#define  InterfaceClassGuidConstant  Guid_ANDROID_USB2Ser
#define  PID                      PID_ANDROID
#define  VID                      VID_ANDROID
#define  PreloaderUSB  1
#define  BootROMUSB   0
extern void scan_exist_com_port_str(
kal_char *exist_symbolic_str[] /*out*/,
kal_char *exist_port_str[] /*out*/,
char * PID_Scan,char * VID_Scan,GUID guid, kal_uint32*  device_num);

extern bool get_new_created_com_port_str(kal_char *symbolic_return_value, kal_char *port_return_value,
                                           kal_char * exist_symbolic_str[],
                                           kal_char * exist_port_str[],
                                           char * PID_Scan,char * VID_Scan,GUID guid);
extern BBCHIP_TYPE GetBBChip ( void );
extern E_COM_NUMBER GetCOMPort ( void );
extern UART_BAUDRATE GetBaudRate ( void );
extern kal_bool GetIsEnableMetaLog ( void );
extern void  EnableTimer2 ( kal_bool );
extern kal_bool GetIsAutoCheckSum ( void );
extern kal_bool IsUSBCOMPort ( void );

extern MetaCommon_struct g_Meta;
extern kal_bool GetBootStopFlag ( void );
extern kal_uint8* GetAPDatabasePath ( void );
extern void UpdateLog ( kal_uint8 *pBuf, kal_uint16 iStep );
extern void ResetIndicator ( void );
extern void UpdateIndicator ( kal_bool bOK );
extern void ClearLog  ( void );
extern void read_SpPreloaderPortFilter ( kal_uint8 *strPath );
extern kal_bool read_Is_Composite_Device_Enable( void );
extern void read_SpBromPortFilter ( kal_uint8 *strPath );
extern void read_Kernel_COMPort_Filter ( kal_uint8 *strPath );
extern kal_uint16 read_Search_Kernel_Port_Time( void );
extern E_INPUTBOX_STATUS InputBoxPopup (kal_uint8* strTitle, kal_uint8* strText, kal_int8* buffer, kal_uint16 iMaxLength );

extern kal_bool MetaModemHandleInit(void);
extern void MetaModemHandleDeInit (void);
extern kal_bool MetaAPHandleInit (void);
extern void	MetaAPHandleDeInit (void);

//static MetaAP_struct g_MetaAP;
MetaAP_struct g_MetaAP;


META_ConnectByUSB_Req usbRequest;
unsigned short us_com_port;  

extern kal_int8 Ascii2BCD ( kal_uint8 iAscii );

extern kal_char imei[4][16];

extern E_INPUTBOX_STATUS DisplayCodeScanner(void);//add by mtk71596
extern void GetUILegacyUSBautodetection(kal_bool flag, kal_uint32* checked);

extern SP_BOOT_ARG_S m_stModeArg;
char asBROMPortFilter[100];
char asPreloaderPortFilter[100];
char asKernelPortFilter[100];
extern  kal_bool search_preloader_port_success;
extern kal_bool search_kernel_port_success;
extern char HdcpKeyFilePath[MAX_PATHNAME_LEN];
extern char DRMKeyFilePath[MAX_PATHNAME_LEN];

FILE_CUSTOM_HDCP_KEY_STRUCT m_sHDCPNvramStruct;
FILE_CUSTOM_HDCP_KEY_STRUCT m_sReadBackHdcp;

char HdcpFileName[1024];
 char DRMFileName[1024];



int functionId;
 
static kal_uint8 strLog [1024];
COMM_BAUDRATE BaudMap [] = 
			{	
				BAUD1500000,
				BAUD921600,
				BAUD460800,
				BAUD230400,
				BAUD115200,
				BAUD57600,
				BAUD57600,  //repeat
				BAUD19200,
				BAUD9600,
				BAUD4800,
				BAUD4800
			};

extern char sp_wifi_nvram_path[512];

static const GUID  GUID_PORT_CLASS_USB2SER ={0x4D36E978L,0xE325,0x11CE,{0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18}};


//For EEPROM Checksum
#define  EEPROM_NIC_CHKSUM_ADD_BYTE                0x13F
#define  EEPROM_NIC_CHKSUM_START_ADD_BYTE          0x1A/* EEPROM offset for HIF section checksum */
#define  EEPROM_NIC_CHKSUM_ADD_DW                0x9F
#define  EEPROM_NIC_CHKSUM_START_ADD_DW          0x0D

//------------------------------------------------------
kal_int32 CVICALLBACK MetaThread ( void *pParaData )
{

	while ( !GetBootStopFlag () )
	{
		if ( g_MetaAP.cb == NULL )
		{
			g_MetaAP.cb();
		}

		g_MetaAP.cb = NULL;
	}
	return 0;
}

void ESetActiveFunction ( EXEC_FUNC_ext func )
{
	g_MetaAP.cb = func;
	return;
}

static void cbMETA_Init ( META_CNF_ERR_CODE  mr )
{
	return;
}


//-------------------------------------------------------------------------
kal_bool MetaAPHandleInit () {

	if ( SP_META_GetAvailableHandle ( &g_Meta.iMetaAP_handle ) ){
	
		MessagePopup ("WARNING", "Get Meta handle fail!");
		return KAL_TRUE;
	} 
	

	if ( SP_META_Init_r ( g_Meta.iMetaAP_handle , (META_Error_CallBack) cbMETA_Init )){

		MessagePopup ("WARNING", "Init Meta handle fail!");
		return KAL_TRUE;
	};
	
	return KAL_FALSE;

}

//--------------------------------------------------- -------------------
void MetaAPHandleDeInit ( void ) 
{
	SP_META_Deinit_r( &g_Meta.iMetaAP_handle );
}

void ResetAPNvramUpdateFlag ( void )
{
	g_Meta.bIsDatabaseInitialized [1] = KAL_FALSE;  
}
void ResetHDCPUpdateFlag ( void )
{
	g_Meta.bhdcpenable = KAL_FALSE;
}
void ResetDRMKeyUpdateFlag ( void )
{
    g_Meta.bdrmenable = KAL_FALSE;
}

//--------------------------------------------------------------------------
kal_bool APNvramDatabaseInit () 
{
	kal_uint32 db;
	META_RESULT result;
	kal_uint8 msgStr[1024] = {'\0'};

	EnableTimer2 ( KAL_TRUE );
	
	if ( result = SP_META_NVRAM_Init_r ( g_Meta.iMetaAP_handle, GetAPDatabasePath(), &db) )
	{
		sprintf(msgStr, "Initial AP Database fail: %s!, Please reselect a database.", ResultToString(result));
		MessagePopup ("WARNING", msgStr);
		return KAL_TRUE;
	}

	g_Meta.bIsDatabaseInitialized [1] = KAL_TRUE;  

	EnableTimer2 ( KAL_FALSE );
	
	return KAL_FALSE;
}
//--------------------------------------------------------------------------
kal_bool IsAPNvramDatabaseInit ()
{

	extern int AP_Database_Select_Click_Shell ( void );
	
	if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [1] ) {

		if ( APNvramDatabaseInit () )
		{
			AP_Database_Select_Click_Shell ();
			return APNvramDatabaseInit ();
		}	
		
	} 
	
	return KAL_FALSE;
}

//---------------------------------------------------
void Seg_MetaAPConnectReq ( void ) {

//******************************************************************************** 
//*************************************************************************************** 
//-------------------Baseband chipset select----------------------------  
//*****************************************************************************************
//*************************************************************************** 
//  -----------Boot ROM and Sync with Target ----------------------
//***************************************************************************
	
    g_MetaAP.tMETA_Connect_Req.com_port = GetCOMPort();
	
    g_MetaAP.tMETA_Connect_Req.baudrate[0] = META_BAUD115200;
    g_MetaAP.tMETA_Connect_Req.baudrate[1] = META_BAUD230400;
    g_MetaAP.tMETA_Connect_Req.baudrate[2] = META_BAUD460800;
    g_MetaAP.tMETA_Connect_Req.baudrate[2] = META_BAUD921600;
    g_MetaAP.tMETA_Connect_Req.baudrate[3] = META_BAUD_END;	
	
    g_MetaAP.tMETA_Connect_Req.flowctrl = META_NO_FLOWCTRL;    //for Modem side SW_FLOWCTRL
    g_MetaAP.tMETA_Connect_Req.ms_connect_timeout = META_CONNECT_TIME_OUT;
     memset (&m_stModeArg, 0x0, sizeof(SP_BOOT_ARG_S));
     m_stModeArg.m_bbchip_type=SP_AUTO_DETECT_BBCHIP;
    m_stModeArg.m_ext_clock=SP_AUTO_DETECT_EXT_CLOCK;
    m_stModeArg.m_ms_boot_timeout=SP_BOOT_INFINITE;
    m_stModeArg.m_uBaudrate=CBR_115200;
    m_stModeArg.m_uTimeout=20000;
    m_stModeArg.m_uRetryTime=2000;
    m_stModeArg.m_uInterval=10;

	
    m_stModeArg.m_auth_handle=SPATE_Get_AuthHandle();
    m_stModeArg.m_scert_handle=SPATE_Get_ScertHandle();
    m_stModeArg.m_cb_sla_challenge=SLA_Challenge;
    m_stModeArg.m_cb_sla_challenge_arg=NULL;
    m_stModeArg.m_cb_sla_challenge_end=SLA_Challenge_END;
    m_stModeArg.m_cb_sla_challenge_end_arg=NULL;
	



	
}

//----------------------------------------------------------------------
kal_bool Exit_MetaAPMode ( void )
{
	//return WM_META_ShutDownTarget_r( g_Meta.iMetaAP_handle );
	//MetaModemHandleDeInit ();
	//MetaAPHandleDeInit ();
	SP_META_DisconnectWithTarget_r ( g_Meta.iMetaAP_handle );
	//MetaModemHandleDeInit ();
	//MetaAPHandleDeInit ();

	return META_SUCCESS;
	
};

void Sp_ApDebugOn(void)
{

	if ( GetIsEnableMetaLog() )
	{
		Eboot_DebugOn ();
		SP_META_DebugOn ();
		SP_Brom_DebugOn();
	}
	else
	{
		Eboot_DebugOff ();
		SP_META_DebugOff ();
		SP_Brom_DebugOff();
	}
}





//----------------------------------------------------------------------
//return KAL_FALSE -> OK
//return KAL_TURE  -> ERROR
kal_bool EnterMetaAPMode ( void )
{
    	Meta_Boot_Arg meta_arg;
	    EBOOT_RESULT Eboot_Result;

	
       META_ConnectByUSB_Report usbReport;
	   kal_int32 device_num=0;

        int iRet;
        kal_uint32  BootStop;

        /*
		MetaModemHandleInit();
		MetaAPHandleInit();
		*/

       sprintf ( strLog,  " COM port searching and preloader handshake\n");	
        UpdateLog ( strLog, 10 );
	   // ***********************************************
	   // Search  preloader or brom COM port for META connection  and handshake with preloader
	   // *********************************************** 	
	   Connect_with_preloader(NULL);		
	   if(search_preloader_port_success == 0)  
	   {
             sprintf ( strLog,  " COM port searching and preloader handshake  fail\n");	
             UpdateLog ( strLog, 10 );	
	         return KAL_TRUE;	
	   }	
	   sprintf ( strLog,  " COM port searching and preloader handshake ok\n");	
       UpdateLog ( strLog, 10 );

	
	   sprintf ( strLog,  "COM port searching and Kernel handshake\n");	
       UpdateLog ( strLog, 10 );

         // ***********************************************
		 // ***kernel  COM port searching and Kernel handshake ***
		 // ***********************************************
	     Sleep(1);
		 search_kernel_port(NULL);	 
         if(search_kernel_port_success==0)
		 {
             sprintf ( strLog,  " COM port searching and Kernel handshake  fail\n");	
             UpdateLog ( strLog, 10 );	
	         return KAL_TRUE;	
		 }
		 sprintf ( strLog,  "COM port searching and Kernel handshake OK\n");	
         UpdateLog ( strLog, 10 );
		 
         Sleep(0.3);
         if(IsUSBCOMPort())
         {
             Delay(1.0);  
	         g_MetaAP.tMETA_Connect_Req.com_port = usb_port;
             g_MetaAP.eMetaAP_Result = SP_META_ConnectInMetaMode_r (g_Meta.iMetaAP_handle, &g_MetaAP.tMETA_Connect_Req, &g_Meta.bootstop, &g_MetaAP.tMETA_Connect_Report); 
   	 	
         }
         else
         {
	          g_MetaAP.eMetaAP_Result = SP_META_ConnectInMetaMode_r (g_Meta.iMetaAP_handle, &g_MetaAP.tMETA_Connect_Req, &g_Meta.bootstop, &g_MetaAP.tMETA_Connect_Report);  
         }

    if(g_MetaAP.eMetaAP_Result != META_SUCCESS)
    {
	    sprintf ( strLog, "SP_META_ConnectInMetaMode_r Error: maybe is %s cause...\n", ResultToString(g_MetaAP.eMetaAP_Result));
	    UpdateLog ( strLog, 30 );

	    return KAL_TRUE;
	}
	else
	{
	    return KAL_FALSE;
	}

};

#if 0
//===========================================================================
kal_bool Compose_IMEI ( kal_bool check_checksum, IMEISV_struct_T tIMEI, kal_uint8* m_PIMEIBuf, kal_int32 len )
{
    g_MetaAP.eMetaAP_Result = META_NVRAM_Compose_IMEISV_ex(&tIMEI, m_PIMEIBuf, len, check_checksum);
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        return KAL_FALSE;
    }
    return KAL_TRUE;
}

//===========================================================================
kal_bool Decompose_IMEI ( IMEISV_struct_T *tIMEI, kal_uint8* m_pIMEIBuf, kal_int16 len )
{
    g_MetaAP.eMetaAP_Result = META_NVRAM_Decompose_IMEISV ( tIMEI, m_pIMEIBuf, len );
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        return KAL_FALSE;
    }
    
    return KAL_TRUE;
}
#endif
#if 0
//===========================================================================
kal_bool Compose_BTAddr_MT6611 (const ap_nvram_btradio_mt6610_struct  *tBT6611, kal_uint8 *buf, kal_int16 buf_len)
{
	g_MetaAP.eMetaAP_Result = META_NVRAM_SetRecFieldValue("AP_CFG_RDEB_FILE_BT_ADDR_LID",
                                                "ap_nvram_btradio_mt6610_struct.addr",
                                                buf,
                                                buf_len,
                                                tBT6611.addr,
                                                sizeof(m_sL1CalTxIq.bbtx_common_mode_voltage) );

	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
		ConfirmCallback ( META_FAILED );
		return KAL_FALSE;
    }

	g_MetaAP.eMetaAP_Result = META_NVRAM_SetRecFieldValue("AP_CFG_RDEB_FILE_BT_ADDR_LID",
                                                "ap_nvram_btradio_mt6610_struct.CapId",
                                                buf,
                                                buf_len,
                                                tBT6611.CapId,
                                                sizeof(tBT6611.CapId[]) );

	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
		ConfirmCallback ( META_FAILED );
		return KAL_FALSE;
    }

	g_MetaAP.eMetaAP_Result = META_NVRAM_SGetRecFieldValue("AP_CFG_RDEB_FILE_BT_ADDR_LID",
                                                "ap_nvram_btradio_mt6610_struct.Codec",
                                                buf,
                                                buf_len,
                                                tBT6611.Codec,
                                                sizeof(tBT6611.Codec[]) );

	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
		ConfirmCallback ( META_FAILED );
		return KAL_FALSE;
    }
    return KAL_TRUE;
}

//===========================================================================
kal_bool Decompose_BTAddr ( ap_nvram_btradio_mt6610_struct *tBT6611, const kal_uint8* buf, kal_int16 buf_len )
{
   g_MetaAP.eMetaAP_Result = META_NVRAM_GetRecFieldValue("AP_CFG_RDEB_FILE_BT_ADDR_LID",
                                                "ap_nvram_btradio_mt6610_struct.addr",
                                                buf,
                                                buf_len,
                                                tBT6611.addr,
                                                sizeof(tBT6611.addr[]) );

	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
		ConfirmCallback ( META_FAILED );
		return KAL_FALSE;
    }
	
    g_MetaAP.eMetaAP_Result = META_NVRAM_GetRecFieldValue("AP_CFG_RDEB_FILE_BT_ADDR_LID",
                                                "ap_nvram_btradio_mt6610_struct.CapId",
                                                buf,
                                                buf_len,
                                                tBT6611.CapId,
                                                sizeof(tBT6611.CapId[]) );

	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
		ConfirmCallback ( META_FAILED );
		return KAL_FALSE;
    }

	g_MetaAP.eMetaAP_Result = META_NVRAM_GetRecFieldValue("AP_CFG_RDEB_FILE_BT_ADDR_LID",
                                                "ap_nvram_btradio_mt6610_struct.Codec",
                                                buf,
                                                buf_len,
                                                tBT6611.Codec,
                                                sizeof(tBT6611.Codec[]) );

	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
		ConfirmCallback ( META_FAILED );
		return KAL_FALSE;
    }
	
    return KAL_TRUE;
}
#endif
//--------------------------------------------------
static void ConfirmCallback (META_RESULT state)
{
    
    switch (state)
    {
        case META_SUCCESS:
        {
        }
        break;

        case META_FAILED:
        {
           
        }
        break;

        case META_TIMEOUT:
        {
        }
        break;
		default: break;
    }
}


//-------------------------------------
void __stdcall CNF_WMReadFromNVRAM(const FT_NVRAM_READ_CNF *cnf, const short token, void *usrData)
{
     if (cnf->status != META_SUCCESS)
    {  
       	ConfirmCallback (META_FAILED);  
		return; 
	}
	
	SetEvent (g_MetaAP.m_ReadFromNVRAMEvent);   
}
//-----------------------------------------------
void __stdcall CNF_WMWriteNVRAM ( const FT_NVRAM_WRITE_CNF *cnf, const short token, void *usrData)
{
    if (cnf->status != META_SUCCESS)
    {  
    	 ConfirmCallback (META_FAILED);  
		return; 
	}
	SetEvent (g_MetaAP.m_WriteToNVRAMEvent);   

}

//-----------------------------------------------
META_RESULT REQ_Write2NVRAM(void)
{
       kal_int16 m_sNVRAM_OPID;
	DWORD wait_result;
	
	
   
    g_MetaAP.m_WriteToNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

    ResetEvent ( g_MetaAP.m_WriteToNVRAMEvent );

    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_Write_r ( g_Meta.iMetaAP_handle,
                                                   &g_MetaAP.tNVRAM_WriteReq,
                                                   CNF_WMWriteNVRAM,
                                                   &m_sNVRAM_OPID,
                                                   NULL);


    wait_result = WaitForSingleObject ( g_MetaAP.m_WriteToNVRAMEvent, 15000 );
	
    //CloseHandle ( g_MetaAP.m_WriteToNVRAMEvent );
	
    if (WAIT_TIMEOUT == wait_result)
    {
        ConfirmCallback (META_TIMEOUT);
        return META_TIMEOUT;
    }

    if (g_MetaAP.eMetaAP_Result != META_SUCCESS)
    {
        return g_MetaAP.eMetaAP_Result;
    }
    return META_SUCCESS;
}


//-----------------------------------------------
static META_RESULT REQ_ReadFromNVRAM ( void )
{
    DWORD wait_result;
	kal_int16 m_sNVRAM_OPID;
	 
    g_MetaAP.m_ReadFromNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	
    ResetEvent ( g_MetaAP.m_ReadFromNVRAMEvent );

    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_Read_r ( g_Meta.iMetaAP_handle,
                                	          &g_MetaAP.tNVRAM_ReadReq,
                                              &g_MetaAP.tNVRAM_ReadCnf,
                                              CNF_WMReadFromNVRAM,
                                              &m_sNVRAM_OPID,
                                              NULL );

    wait_result = WaitForSingleObject ( g_MetaAP.m_ReadFromNVRAMEvent, 15000 );

    //CloseHandle ( g_MetaAP.m_ReadFromNVRAMEvent );
    if ( WAIT_TIMEOUT == wait_result )
    {
        ConfirmCallback ( META_TIMEOUT );
        return META_TIMEOUT;
    }

    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        return g_MetaAP.eMetaAP_Result;
    }

    return META_SUCCESS;
}
//===========================================================================
META_RESULT REQ_ReadBTAddrFromNVRAM_Start ( kal_uint32 iBTId, kal_uint8* pBTAddress )
{
       kal_int32 m_usRID = 1, m_iBTBufSize;
	kal_uint8 *pLID;
	//nvram_ef_btradio_mt6611_struct  tBT;
       kal_uint32 pBTv;
	NVRAM_BTRADIO_MT6611_S  tBT;
       NVRAM_BTRADIO_MT6620_S  tBT1;
	NVRAM_BTRADIO_MT6626_S  tBT2;
       BT_CHIP_ID_E  Chip_id;
	
	switch ( iBTId )	
	{
		case BTMODULE_MT6601:  //6601
		case BTMODULE_MT6611:
			if (!SP_META_NVRAM_GetRecLen ( "AP_CFG_RDCL_FILE_BT_ADDR_LID", &m_iBTBufSize )) // to Test LID exist
			{
				pLID = "AP_CFG_RDCL_FILE_BT_ADDR_LID";  //after DUMA 1004
			} else if (!SP_META_NVRAM_GetRecLen ( "AP_CFG_RDEB_FILE_BT_ADDR_LID", &m_iBTBufSize ))
			{
				pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";  //before DUMA 1004
			} else
			{
				return META_LID_INVALID;
			}
			break;
			
		case BTMODULE_RFMD3500:  //RFMD
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		case BTMODULE_RFMD4020:
			
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		default:
			break;
	}

    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen( pLID, &m_iBTBufSize);
    if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
    {
    	return g_MetaAP.eMetaAP_Result;
    }

	if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaAP.tNVRAM_ReadCnf.buf );
		g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
		
	}

	g_MetaAP.tNVRAM_ReadReq.LID = pLID;
       g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
       g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
       g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );

	g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
	if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
    {
    	return g_MetaAP.eMetaAP_Result;
    }

    g_MetaAP.eMetaAP_Result=SP_META_BT_GetChipID_r(g_Meta.iMetaAP_handle, 10000, &pBTv);//2012-8-8 dongck modify for tinno 6622 BT Initial time is too long
  
     if(pBTv==BT_CHIP_ID_MT6622||pBTv==BT_CHIP_ID_MT6626)
     {
         g_MetaAP.eMetaAP_Result= SP_META_NVRAM_BT_Decompose_MT6626Radio(&tBT2,g_MetaAP.tNVRAM_ReadCnf.buf,m_iBTBufSize); 
		
     }
	 else
     {
       #if 0
       g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_QueryChipByStructSize(&Chip_id);
       if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
       {
          //TODO: LOG
          return g_MetaAP.eMetaAP_Result;
       }
	   #endif 
	 
	    //if(Chip_id==BT_CHIP_ID_MT6611) 
		if(pBTv == BT_CHIP_ID_MT6611)
        {
            g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Decompose_MT6611Radio ( &tBT, g_MetaAP.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	    }
        else 
        {
            g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Decompose_MT6620Radio( &tBT1, g_MetaAP.tNVRAM_ReadCnf.buf, m_iBTBufSize);
        }
	   
   }


	//g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Decompose_MT6611Radio ( &tBT, g_MetaAP.tNVRAM_ReadCnf.buf, m_iBTBufSize );
	if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
    {
    	return g_MetaAP.eMetaAP_Result;
    }

     if(pBTv==BT_CHIP_ID_MT6622||pBTv==BT_CHIP_ID_MT6626)
     {
         memcpy ( pBTAddress, tBT2.addr, BD_ADDR_LEN ); 
     }
     else
     {
	       //if(Chip_id==BT_CHIP_ID_MT6611) 
	      if(pBTv == BT_CHIP_ID_MT6611)
	      {
	          memcpy ( pBTAddress, tBT.addr, BD_ADDR_LEN ); 
	      }
	      else
          {
	          memcpy ( pBTAddress, tBT1.addr, BD_ADDR_LEN ); 	
	       }
     }
	 
	 if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
	 {
		   free ( g_MetaAP.tNVRAM_ReadCnf.buf );
		   g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
		
	 }
	
	return g_MetaAP.eMetaAP_Result;
}

//===========================================================================
/*
typedef struct{   
     unsigned char imei[8];   
     unsigned char svn;   
     unsigned char pad;
 } nvram_ef_imei_imeisv_struct;
 
 typedef struct{		
     unsigned char barcode[64];		
     nvram_ef_imei_imeisv_struct IMEI[4];		
     unsigned char reserved[1024-40-64];
 }PRODUCT_INFO;
 
 #define CFG_FILE_PRODUCT_INFO_SIZE    sizeof(PRODUCT_INFO)
 #define CFG_FILE_PRODUCT_INFO_TOTAL   1
*/

// add mtk71518 begin, write imei to product_info, 2013-07-09
int REQ_ReadImeiFromNVRAM_Start(kal_char (*pImei)[16], int imeiNums)
{
		   kal_int32 m_usRID = 1;
		   kal_int32 iProdInfoBufSize;
		   int index = 0;
		   int imeiIndex = 0;
		   int beginIndex = 0;
		   kal_uint32  tmpCh;	
		   kal_uint8 *pLID = "AP_CFG_REEB_PRODUCT_INFO_LID";
		   
		   g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &iProdInfoBufSize );
		   if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
		   {
			   //TODO: LOG
			   return g_MetaAP.eMetaAP_Result;
		   }
		
		   if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
		   {
			   free ( g_MetaAP.tNVRAM_ReadCnf.buf );   
			   g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
		   }
		
		   g_MetaAP.tNVRAM_ReadReq.LID = pLID;
		   g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
		   g_MetaAP.tNVRAM_ReadCnf.len = iProdInfoBufSize;
		   g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (iProdInfoBufSize*sizeof(kal_uint8));
		
		   
		   g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
		   if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
		   {
			   return g_MetaAP.eMetaAP_Result;
		   }

		   beginIndex = 64;				   
		   for(imeiIndex = 0; imeiIndex < imeiNums; imeiIndex++)
		   {
	         for (index = 0; index <7; index++)
		     {		  
		         tmpCh = (g_MetaAP.tNVRAM_ReadCnf.buf[beginIndex+index] & 15); //15-->00001111
				 pImei[imeiIndex][index*2] = tmpCh + '0';
				 
			     tmpCh = (g_MetaAP.tNVRAM_ReadCnf.buf[beginIndex+index] & 240);//240-->11110000
				 tmpCh = tmpCh >> 4;
				 pImei[imeiIndex][index*2+1] = tmpCh + '0';
							 
		     }
			 
		     tmpCh = (g_MetaAP.tNVRAM_ReadCnf.buf[beginIndex+7] & 15);	
			 pImei[imeiIndex][14] = tmpCh + '0';//checkSum bit

		     beginIndex += 10;  //next IMEI field
		  }
	
		   if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
		   {
			  free ( g_MetaAP.tNVRAM_ReadCnf.buf ); 
			  g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
		   }
		
		   return META_SUCCESS;
	
	}
	
int REQ_WriteImei2NVRAM_Start (kal_char (*pImei)[16], int imeiNums)
{
		kal_int32 m_usRID = 1;
		kal_int32 iProdInfoBufSize;
		int index = 0;
		int imeiIndex = 0;
		int beginIndex = 0;
		kal_uint32  tmpCh;	
		kal_uint8 *pLID = "AP_CFG_REEB_PRODUCT_INFO_LID";

		/* Debug use
		
            kal_char imei_1[] = "123456789012345";
		kal_char imei_2[] = "987654321054321";
            imeiNums = 2;
	      strncpy(pImei[0], imei_1, 15);
		strncpy(pImei[1], imei_2, 15);
		
		*/
		
		g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &iProdInfoBufSize );
		if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
		{
			return g_MetaAP.eMetaAP_Result;
		}
	
		if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
		{
			free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
			g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
		}
	
		g_MetaAP.tNVRAM_ReadReq.LID = pLID;
		g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
		g_MetaAP.tNVRAM_ReadCnf.len = iProdInfoBufSize;
		g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (iProdInfoBufSize * sizeof(kal_uint8));
		
		g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
		if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
		{
			return g_MetaAP.eMetaAP_Result;
		}
		
		//Modify IMEI  Part
		beginIndex = 64;	//64Bytes storage barcode string	
		for(imeiIndex = 0; imeiIndex < imeiNums; imeiIndex++)
		{
	       for (index = 0; index <7; index++)
		   {
		      tmpCh = pImei[imeiIndex][index*2 + 1] - '0';
			  tmpCh = ((tmpCh << 4) & 240);//240 -->11110000	
			  
			  //sprintf(strLog, "2:pImei[%d] = %d, temCH = %d\n", index, pImei[imeiIndex][index*2 + 1], tmpCh);
			  //UpdateLog(strLog, 10);
				  
			  tmpCh += pImei[imeiIndex][index*2] - '0';
			  g_MetaAP.tNVRAM_ReadCnf.buf[beginIndex+index] = tmpCh;		  
		   }
		   
		   tmpCh = 15;         //        15 --> 00001111
		   tmpCh = tmpCh << 4; //15 <<4  --> 11110000
		   tmpCh += pImei[imeiIndex][14] - '0'; //checkSum bit
		   g_MetaAP.tNVRAM_ReadCnf.buf[beginIndex+7] = tmpCh;

		   beginIndex += 10;  //next IMEI field
		}
		
		m_usRID = 1;
		g_MetaAP.tNVRAM_WriteReq.LID = pLID;
		g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
		g_MetaAP.tNVRAM_WriteReq.len = iProdInfoBufSize;
		g_MetaAP.tNVRAM_WriteReq.buf = g_MetaAP.tNVRAM_ReadCnf.buf;
			   
		g_MetaAP.eMetaAP_Result = REQ_Write2NVRAM ();
			
		if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
		{
			 return g_MetaAP.eMetaAP_Result;
		}
		
		if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
		{
			 free ( g_MetaAP.tNVRAM_ReadCnf.buf );
			 g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
			 g_MetaAP.tNVRAM_WriteReq.buf = NULL;
		}
	
		return META_SUCCESS;
	
}
// add mtk71518 end, write imei to product_info


int REQ_ReadBarcodeFromNVRAM_Start(kal_uint8 *strBarcode)
{
	   kal_int32 m_usRID = 1;
	   kal_int32 iProdInfoBufSize;
	   kal_uint8 *pLID = "AP_CFG_REEB_PRODUCT_INFO_LID";
	   
	   g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &iProdInfoBufSize );
	   if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
	   {
		   //TODO: LOG
		   return g_MetaAP.eMetaAP_Result;
	   }
	
	   if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
	   {
		   free ( g_MetaAP.tNVRAM_ReadCnf.buf );   
		   g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
	   }
	
	   g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	   g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	   g_MetaAP.tNVRAM_ReadCnf.len = iProdInfoBufSize;
	   g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (iProdInfoBufSize*sizeof(kal_uint8));
	
	   
	   g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
	   if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
	   {
		   return g_MetaAP.eMetaAP_Result;
	   }
	   memcpy(strBarcode, g_MetaAP.tNVRAM_ReadCnf.buf, (strlen(g_MetaAP.tNVRAM_ReadCnf.buf)+1));

	   if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
	   {
		  free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
		  g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
	   }
	
	   return META_SUCCESS;

}

int REQ_WriteBarcode2NVRAM_Start (kal_uint8 *strBarcode)
{
    kal_int32 m_usRID = 1;
	kal_int32 iProdInfoBufSize;
    kal_uint8 *pLID = "AP_CFG_REEB_PRODUCT_INFO_LID";

    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &iProdInfoBufSize );
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        //TODO: LOG
        return g_MetaAP.eMetaAP_Result;
    }

    if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
    {
	    free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
	    g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
    }

    g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	g_MetaAP.tNVRAM_ReadCnf.len = iProdInfoBufSize;
	g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (iProdInfoBufSize * sizeof(kal_uint8));

	
    g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
    if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
	{
	    return g_MetaAP.eMetaAP_Result;
	}
	memcpy(g_MetaAP.tNVRAM_ReadCnf.buf, strBarcode, 64);
	
    m_usRID = 1;
    g_MetaAP.tNVRAM_WriteReq.LID = pLID;
	g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
	g_MetaAP.tNVRAM_WriteReq.len = iProdInfoBufSize;
	g_MetaAP.tNVRAM_WriteReq.buf = g_MetaAP.tNVRAM_ReadCnf.buf;
	       
    g_MetaAP.eMetaAP_Result = REQ_Write2NVRAM ();
	    
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
    	 return g_MetaAP.eMetaAP_Result;
    }
    
	if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
    {
	     free ( g_MetaAP.tNVRAM_ReadCnf.buf );
		 g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
		 g_MetaAP.tNVRAM_WriteReq.buf = NULL;
	}

    return META_SUCCESS;

}

int REQ_WriteBTAddr2NVRAM_Start (kal_uint32 iBTId, kal_uint8* pBTAddress)
{
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID;
	kal_uint32 pBTv;
    NVRAM_BTRADIO_MT6611_S  tBT;
    NVRAM_BTRADIO_MT6620_S  tBT1;
    NVRAM_BTRADIO_MT6626_S  tBT2;
    BT_CHIP_ID_E  Chip_id;
	
	switch ( iBTId )	
	{
		case BTMODULE_MT6601:  //6601
		case BTMODULE_MT6611:
		//case BTMODULE_MT6612:
			if (!SP_META_NVRAM_GetRecLen ( "AP_CFG_RDCL_FILE_BT_ADDR_LID", &m_iBTBufSize )) // to Test LID exist
			{
				pLID = "AP_CFG_RDCL_FILE_BT_ADDR_LID";  //after DUMA 1004
			} else if (!SP_META_NVRAM_GetRecLen ( "AP_CFG_RDEB_FILE_BT_ADDR_LID", &m_iBTBufSize ))
			{
				pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";  //before DUMA 1004
			} else
			{
				return META_LID_INVALID;
			}
			break;
			
		case BTMODULE_RFMD3500:  //RFMD
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		case BTMODULE_RFMD4020:
			
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		default:
			break;
	}

	g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        //TODO: LOG
        return g_MetaAP.eMetaAP_Result;
    }

    if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
    {
		free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
		g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
	}

	g_MetaAP.tNVRAM_ReadReq.LID = pLID;
    g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
    g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
    g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

	g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
	if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
    {
    	return g_MetaAP.eMetaAP_Result;
    }

     g_MetaAP.eMetaAP_Result=SP_META_BT_GetChipID_r(g_Meta.iMetaAP_handle, 10000, &pBTv);//1012-8-8 dongck modify for tinno 6622 BT Initial time is too long
     if(pBTv == BT_CHIP_ID_MT6622 || pBTv == BT_CHIP_ID_MT6626)
     {
         g_MetaAP.eMetaAP_Result= SP_META_NVRAM_BT_Decompose_MT6626Radio(&tBT2, g_MetaAP.tNVRAM_ReadCnf.buf,m_iBTBufSize); 		
     }
	 else
     {
        #if 0
        g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_QueryChipByStructSize(&Chip_id);
        if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
        {
           //TODO: LOG
           return g_MetaAP.eMetaAP_Result;
        }
		#endif
		
	    //if(Chip_id==BT_CHIP_ID_MT6611) 
	    if(pBTv == BT_CHIP_ID_MT6611)
        {
            g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Decompose_MT6611Radio ( &tBT, g_MetaAP.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	    }
        else 
        {
            g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Decompose_MT6620Radio( &tBT1, g_MetaAP.tNVRAM_ReadCnf.buf, m_iBTBufSize);
        }
    }  
	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
    	return g_MetaAP.eMetaAP_Result;
    }

    if(pBTv==BT_CHIP_ID_MT6622||pBTv==BT_CHIP_ID_MT6626)
    {     
        memcpy(tBT2.addr,pBTAddress,BD_ADDR_LEN);		
    }
	else
	{
	   //if(Chip_id==BT_CHIP_ID_MT6611) 
	   if(pBTv == BT_CHIP_ID_MT6611)
       {
	       memcpy ( tBT.addr, pBTAddress, BD_ADDR_LEN ); 
	   }
	   else
	   {
	       memcpy ( tBT1.addr, pBTAddress, BD_ADDR_LEN ); 
	   }
    }
	
	if (NULL != g_MetaAP.tNVRAM_WriteReq.buf)
	{
		free (g_MetaAP.tNVRAM_WriteReq.buf);	
		g_MetaAP.tNVRAM_WriteReq.buf = NULL;
	}
	
	switch ( iBTId )	
	{
		case BTMODULE_MT6601:  //6601
		case BTMODULE_MT6611:
		//case BTMODULE_MT6612:
			if (!SP_META_NVRAM_GetRecLen ( "AP_CFG_RDCL_FILE_BT_ADDR_LID", &m_iBTBufSize )) // to Test LID exist
			{
				pLID = "AP_CFG_RDCL_FILE_BT_ADDR_LID";  //after DUMA 1004
			} else if (!SP_META_NVRAM_GetRecLen ( "AP_CFG_RDEB_FILE_BT_ADDR_LID", &m_iBTBufSize ))
			{
				pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";  //before DUMA 1004
			} else
			{
				return META_LID_INVALID;
			}
			break;
			
		case BTMODULE_RFMD3500:  //RFMD
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		case BTMODULE_RFMD4020:
			
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		default:
			break;
	}

	g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );
    	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
      {
         //TODO: LOG
        return g_MetaAP.eMetaAP_Result;
      }
		
	m_usRID = 1;
	g_MetaAP.tNVRAM_WriteReq.LID = pLID;
       g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
       g_MetaAP.tNVRAM_WriteReq.len = m_iBTBufSize;
       g_MetaAP.tNVRAM_WriteReq.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );


 g_MetaAP.eMetaAP_Result=SP_META_BT_GetChipID_r(g_Meta.iMetaAP_handle, 10000, &pBTv);//1012-8-8 dongck modify for tinno 6622 BT Initial time is too long

 if(pBTv==BT_CHIP_ID_MT6622||pBTv==BT_CHIP_ID_MT6626)
{
     g_MetaAP.eMetaAP_Result= SP_META_NVRAM_BT_Compose_MT6626Radio(&tBT2, g_MetaAP.tNVRAM_WriteReq.buf,m_iBTBufSize); 		
}
else
{
    #if 0
    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_QueryChipByStructSize(&Chip_id);
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        //TODO: LOG
        return g_MetaAP.eMetaAP_Result;
    }
    #endif
	 
	//if(Chip_id==BT_CHIP_ID_MT6611) 
	if(pBTv == BT_CHIP_ID_MT6611)
    {
        g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Compose_MT6611Radio( &tBT,  g_MetaAP.tNVRAM_WriteReq.buf,  m_iBTBufSize );
	}
    else 
    {
         g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Compose_MT6620Radio( &tBT1,  g_MetaAP.tNVRAM_WriteReq.buf,  m_iBTBufSize );
    }

 }
	   
 if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
 {
     return g_MetaAP.eMetaAP_Result;
 }
	   
	//g_MetaAP.eMetaAP_Result = SP_META_NVRAM_BT_Compose_MT6611Radio ( &tBT, 
	  //                                     g_MetaAP.tNVRAM_WriteReq.buf, 
		//                                   m_iBTBufSize );

	g_MetaAP.eMetaAP_Result = REQ_Write2NVRAM ();
    
	if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
       {
    	    return g_MetaAP.eMetaAP_Result;
       }

       if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaAP.tNVRAM_ReadCnf.buf );
		g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
	}

	if (NULL != g_MetaAP.tNVRAM_WriteReq.buf)
	{
		free (g_MetaAP.tNVRAM_WriteReq.buf);	
		g_MetaAP.tNVRAM_WriteReq.buf = NULL;
	}
	
    return META_SUCCESS;
}

//----------------------------------------------------------------------
int func_bt_address_meta_hdlr_smart_phone ( void )
{
	kal_uint8 strTip [256] , i, iBCD_L, iBCD_H;
	
	BT_ModuleID_S BT_ID;
	
	S_HANDSET_BT_ADRRESS tBtAddress_W, tBtAddress_R;
		
//	kal_uint8 strBtAddress_W [ BT_ADDRESS_MAX_LENGTH + 1 ];
	extern kal_char BT[13];
	kal_uint8 strBtAddress_R [ BT_ADDRESS_MAX_LENGTH + 1 ];
	kal_uint16 iLoop = 0;
	kal_uint32 BackupSecondImei;
	extern int ret_statue;
	int ret = 0;
	BT_ID.id = BTMODULE_MT6611;
	sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
    sprintf ( strLog, "\n>>Step: Enter func_BT_meta_hdlr_smart_phone();\n");
	strcat ( strLog,  "        Write BT to smartphone nvram\n");
	UpdateLog ( strLog, 100 );

 

			for ( i = 0; i < BT_ADDRESS_MAX_LENGTH; i += 2 )
			{
				 
				 iBCD_H = Ascii2BCD( BT [i] );
				 iBCD_L = Ascii2BCD( BT [i + 1] );

				 tBtAddress_W.bd_addr [i/2] = iBCD_H<<4 | iBCD_L;
				
			}

			switch ( BT_ID.id )	
			{
				case BTMODULE_MT6601:  //6601
				case BTMODULE_MT6611:
				//case BTMODULE_MT6612:
					if ( g_MetaAP.eMetaAP_Result  = REQ_WriteBTAddr2NVRAM_Start ( BT_ID.id, tBtAddress_W.bd_addr) )
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", g_MetaAP.eMetaAP_Result );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						Exit_MetaAPMode ();  
						
						MessagePopup ("BT Address Error", "BD Address write fail");  
											
						ret = 1;
						goto err;
					}
					break;
				case BTMODULE_RFMD3500:  //RFMD
				case BTMODULE_RFMD4020:
					if ( g_MetaAP.eMetaAP_Result  = REQ_WriteBTAddr2NVRAM_Start ( BT_ID.id, tBtAddress_W.bd_addr ) )
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", g_MetaAP.eMetaAP_Result );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						
						MessagePopup ("BT Address Error", "BD Address write fail");
						Exit_MetaAPMode ();
						ret = 2;
						goto err;
					}
					
					break;
				default:
					break;
			}

			sprintf ( strLog, "   OK: Write BT Address successfully.\n"  );
			UpdateLog ( strLog, 70 );	

			if ( REQ_ReadBTAddrFromNVRAM_Start ( BT_ID.id, tBtAddress_R.bd_addr) )
			{
				//TODO
			}

			sprintf ( strLog, "   Step: Check BT Address.\n"  );
			UpdateLog ( strLog, 80 );	
			
			if ( memcmp ( tBtAddress_W.bd_addr, tBtAddress_R.bd_addr, BD_ADDR_LEN )) {

				
				sprintf ( strLog, "   Error: Check BT Address fail. BT Address = \"%x %x %x %x %x %x\".\n",  tBtAddress_R.bd_addr[0],
																											 tBtAddress_R.bd_addr[1],
																											 tBtAddress_R.bd_addr[2],
																											 tBtAddress_R.bd_addr[3],
																											 tBtAddress_R.bd_addr[4],
																											 tBtAddress_R.bd_addr[5]);

				UpdateLog ( strLog, 100 );
				
				UpdateIndicator ( KAL_FALSE );
				MessagePopup ("BT Address Error", " Read/Write BT Address inconsist");
				
				
			}
			else
			{
				sprintf ( strLog, "   OK: Check BT Address. BT Address  = \"%x %x %x %x %x %x\".\n.", tBtAddress_R.bd_addr[0],
																		    					      tBtAddress_R.bd_addr[1],
																		  					          tBtAddress_R.bd_addr[2],
																		   					          tBtAddress_R.bd_addr[3],
																		   					          tBtAddress_R.bd_addr[4],
																		   					          tBtAddress_R.bd_addr[5]);
				UpdateLog ( strLog, 90 );
//				UpdateIndicator ( KAL_TRUE );
			}
	err:
		return ret;
}

//---------------------------------------------------------------------------------------------------
int func_wifi_mac_meta_hdlr_smart_phone_Ex ( void )
{

	kal_uint8 eeprom_buf [EEPROM_SIZE], check_buf[EEPROM_SIZE];
	int m_usRID = 1, m_iBTBufSize;
	short token;
	char LID_Name[100];
	META_RESULT metaResult = 0;
	int ret;
	unsigned short value = 0;

     extern int sp_nv_to_nvram;
       char barcode[90];
       char filename[500];
	   extern int ret_statue;

       ////
	kal_uint8 strTip [256] , i, iBCD_L, iBCD_H, strMacHeader[13],strTemp[20];
	
	WiFi_MacAddress_S tWifiMac_W, tWifiMac_R;
	kal_uint8 strWifiMac_W [ WIFI_MAC_MAX_LENGTH + 1 ];
	kal_uint8 srtWifiMac_R [ WIFI_MAC_MAX_LENGTH + 1 ];
	kal_uint16 iLoop = 0;
	extern kal_uint32 iMacHeaderLen,BackupSecondImei;

	META_RESULT MR = META_SUCCESS;
	/////
	extern kal_char WIFI[13];
	kal_char WIFI_r[13];
    int rett = 0;
    sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
	strcat ( strLog, "\n>>Step: Enter func_wifi_mac_meta_hdlr_smart_phone_Ex();\n");
	strcat ( strLog,  "        Write Wifi MAC  to smart phone nvram\n");
	UpdateLog ( strLog, 0 );





			sprintf ( strLog,  ">>Step: Start to write Wifi MAC.\n" );
			UpdateLog ( strLog, 50 );

			for ( i = 0; i < WIFI_MAC_MAX_LENGTH; i+=2 )
			{
				 
				 iBCD_H = Ascii2BCD( WIFI [i] );
				 iBCD_L = Ascii2BCD( WIFI [i+1] );

                             if ( (i/2)%2 == 0 )
                             {
                                tWifiMac_W.mac_addr [i/2+1] = iBCD_H<<4 | iBCD_L;
                             }
                             else
                             {
                                tWifiMac_W.mac_addr [i/2-1] = iBCD_H<<4 | iBCD_L;
                             }
			}


			//if ( MR = METAAPP_WiFi_writeWiFiMacAddressToNVRAM ( g_Meta.iMeta_handle, 5000, &tWifiMac_W ))

            if ( MR = REQ_WriteWifiMAC2NVRAM_Start (&tWifiMac_W) )
			{
				sprintf ( strLog, "   Error: Write Wifi MAC  fail. Meta Result = %d\n", MR );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );
				MessagePopup ("Wifi MAC Error", "Wifi MAC write fail");

				Exit_MetaAPMode ();
				rett = 1;
				goto err;
			}   
			
			sprintf ( strLog, "    OK: Write Wifi MACsuccessfully.\n"  );
			UpdateLog ( strLog, 70 );	

			sprintf ( strLog, " >>Step: Start to check Wifi MAC.\n"  );
			UpdateLog ( strLog, 80 );	
			
			//if ( MR = METAAPP_WiFi_readWiFiMacAddressFromNVRAM ( g_Meta.iMeta_handle,5000,&tWifiMac_R))
            if ( MR = REQ_ReadWifiMACFromNVRAM_Start (&tWifiMac_R) )
			{
				sprintf ( strLog, "    Error: Read Wifi MAC  fail. Meta Result = %d\n", MR );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );
				Exit_MetaAPMode ();   

				MessagePopup ("Meta  API Error", "Wifi Address read fail");  
			rett = 2;
				goto err;
			}
			
                        
	        if ( memcmp  ( tWifiMac_W.mac_addr, tWifiMac_R.mac_addr, MAC_ADDR_LEN))
			{
				sprintf ( strLog, "    Error: Check Wifi MAC fail.Wifi MAC [write] = \"%x %x %x %x %x %x\".\n",  tWifiMac_W.mac_addr[0],
																					  tWifiMac_W.mac_addr[1],
																					  tWifiMac_W.mac_addr[2],
																					  tWifiMac_W.mac_addr[3],
																					  tWifiMac_W.mac_addr[4],
																					  tWifiMac_W.mac_addr[5]);

				UpdateLog ( strLog, 100 );
				sprintf ( strLog, "    Wifi MAC [read] = \"%x %x %x %x %x %x\".\n",  tWifiMac_R.mac_addr[0],
																					  tWifiMac_R.mac_addr[1],
																					  tWifiMac_R.mac_addr[2],
																					  tWifiMac_R.mac_addr[3],
																					  tWifiMac_R.mac_addr[4],
																					  tWifiMac_R.mac_addr[5]);
				UpdateLog ( strLog, 100 );
                            MR = META_FAILED;
							rett = 3;
				goto err;
			}
			else
			{
				sprintf ( strLog, "    OK: Check Wifi MAC Pass. Wifi MAC = \"%x %x %x %x %x %x\".\n",  tWifiMac_R.mac_addr[0],
																					      tWifiMac_R.mac_addr[1],
																					      tWifiMac_R.mac_addr[2],
																					      tWifiMac_R.mac_addr[3],
																					      tWifiMac_R.mac_addr[4],
																					      tWifiMac_R.mac_addr[5]);
				UpdateLog ( strLog, 100 );	
                            MR = META_SUCCESS;
			}

              if (sp_nv_to_nvram == 1 && MR == META_SUCCESS)
              {
                sprintf ( strLog, ">>Step: NV To File.\n");
                UpdateLog ( strLog, 100 );

                MR = ApMetaToModemMeta();
                if (MR != 0 )
                {
                    	sprintf ( strLog, ">>Step: ApMetaToModemMeta fail.\n");
                        UpdateLog ( strLog, 100 );
                }
                else
                {
                    sprintf ( strLog, "    OK: ApMetaToModemMeta.\n");
                        UpdateLog ( strLog,  100);
                }
                
                MR = FP_METAAPP_readBarcodefromNVRAM( g_Meta.iMeta_handle, 5000, barcode );
                if (MR != 0 )
                {
                    	sprintf ( strLog, ">>Step: FP_METAAPP_readBarcodefromNVRAM fail.\n");
                        UpdateLog ( strLog, 100 );
						rett = 4;
				goto err;
                }
                else
                {
                    sprintf ( strLog, "    OK: Read Barcode.\n");
                        UpdateLog ( strLog,  100);
                }
                sprintf (filename, "%s_%s.txt", barcode, WIFI);

                MR = ModemMetaToAPMeta();
                if (MR != 0 )
                {
                    	sprintf ( strLog, ">>Step: ModemMetaToAPMeta fail.\n");
                        UpdateLog ( strLog, 100 );
						rett = 5;
				goto err;
                }
                else
                {
                    sprintf ( strLog, "    OK: ModemMetaToAPMeta.\n");
                        UpdateLog ( strLog,  100);
                }


                //MR = SP_WIFI_Save_NVRAM_To_File(g_Meta.iMetaAP_handle, "C:\\WIFI\\", filename);
                MR = SP_WIFI_Save_NVRAM_To_File(g_Meta.iMetaAP_handle, sp_wifi_nvram_path, filename);
                if (MR != 0 )
                {
                    	sprintf ( strLog, ">>Step: SP_WIFI_Save_NVRAM_To_File fail.\n");
                     UpdateLog ( strLog, 100 );
					 rett = 6;
				goto err;
                }
                else
                {
                    sprintf ( strLog, "    OK: Write NV To File.\n");
                        UpdateLog ( strLog,  100);
                }
                
              }
        
//		sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
//		UpdateLog ( strLog, 100 );
				
//		Exit_MetaAPMode ();

              if (MR == META_SUCCESS)
              {
//                UpdateIndicator ( KAL_TRUE );
              }
              else
              {
                UpdateIndicator ( KAL_FALSE );
              }
			  err:
			  	return rett;

}


//----------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
int func_wifi_mac_meta_hdlr_smart_phone ( void )
{

	kal_uint8 eeprom_buf [EEPROM_SIZE], check_buf[EEPROM_SIZE];
	int m_usRID = 1, m_iBTBufSize;
	short token;
	char LID_Name[100];
	META_RESULT metaResult = 0;
	int ret;
	int rett = 0;
	unsigned short value = 0;
	kal_uint32 BackupSecondImei = 0;
	sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
    sprintf ( strLog, ">>Step: Enter func_wifi_meta_hdlr_smart_phone();\n");
	strcat ( strLog,  "        Copy Wifi Paranmenter from EEPROM to NVRAM.\n\n");
	UpdateLog ( strLog, 100 );
	/********************************************************************
	sprintf ( strLog, ">> Step: Enter func_wifi_mac_meta_hdlr_smart_phone();\n");
	strcat ( strLog,  "      Copy Wifi Paranmenter from EEPROM to NVRAM.\n\n");
	UpdateLog ( strLog, 0 );
	
	sprintf ( strLog, ">> Step: Start to Init AP Nvram Database...\n");
	UpdateLog ( strLog, 20 );

	if ( IsAPNvramDatabaseInit() ) 

	{ 
		sprintf ( strLog, "   Error: Init AP Nvram Database failed.\n\n");
		UpdateLog ( strLog, 100);
		return;
	}

	sprintf ( strLog, "   OK: Init AP Nvram Database successfully.\n\n");
	UpdateLog ( strLog, 100 );
	
	Seg_MetaAPConnectReq ();
	GetUISetCleanBootFlag(KAL_TRUE, &BackupSecondImei);

	g_MetaAP.eRunStatus = RUN_STATUS;

	sprintf ( strLog, ">> Step: Start to Enter Meta mode, Please Powe On phone\n" );
	
	UpdateLog ( strLog, 0 );	

	ResetIndicator ();

	if ( EnterMetaAPMode () ) 
	{
		Exit_MetaAPMode ();
		
		sprintf ( strLog, "       Error: Connect failed, Exit Meta Mode and turn to next phone.\n\n" );
		UpdateLog ( strLog, 100 );
		UpdateIndicator ( KAL_FALSE );
	 }
	
	sprintf ( strLog,  "       OK: Connect to target successfully.\n\n" );
	UpdateLog ( strLog, 30 );
******************************************************************************/
// if ( OK_STATUS == g_MetaAP.eRunStatus ) 
if(1)
 {
	sprintf(strLog, ">> Step:  Start to Read TX From EEPROM \n");
	UpdateLog ( strLog, 40 );
    if ( SP_Read_Wifi_Para_From_EEPROM (eeprom_buf) )
    {
		sprintf(strLog, "       Error: Read TX From EEPROM fail \n\n");
		UpdateLog ( strLog, 100 );
		Exit_MetaAPMode ();   
		UpdateIndicator ( KAL_FALSE );
		rett = 1;
		goto err;

	}

	sprintf(strLog, "       OK: Read TX From EEPROM Successfully.\n \n");
	UpdateLog ( strLog, 40 );

	sprintf(strLog, ">> Step:  Start to Write to NVRAM. \n");
	UpdateLog ( strLog, 50 );
	//Write to Nvram
	strcpy (LID_Name, "AP_CFG_RDEB_FILE_WIFI_LID");

	if ( SP_META_NVRAM_GetRecLen ( LID_Name, &m_iBTBufSize ))
	{
		 //TODO: LOG
		 sprintf(strLog, "Error: SP_META_NVRAM_GetRecLen\n\n");
		UpdateLog ( strLog, 60 );
		UpdateIndicator ( KAL_FALSE );
	 	rett = 2;
		goto err;
	//	return ;
	    
	}
	
	if (EEPROM_SIZE != m_iBTBufSize)
	{
	//	return ;
	 sprintf(strLog, "Error:SP_META_NVRAM_GetRecLen Get Size not equal to EEPROM_SIZE \n\n");
		UpdateLog ( strLog, 60 );
		UpdateIndicator ( KAL_FALSE );
	 	rett = 3;
		goto err;
	}

	g_MetaAP.tNVRAM_WriteReq.LID = LID_Name;
	g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
	g_MetaAP.tNVRAM_WriteReq.len = m_iBTBufSize;
	g_MetaAP.tNVRAM_WriteReq.buf = eeprom_buf;

	if(  REQ_Write2NVRAM ())
	{

		sprintf(strLog, "       Error: Write to NVRAM Fail\n\n");
		UpdateLog ( strLog, 60 );
		UpdateIndicator ( KAL_FALSE );
	 	rett = 4;
		goto err;
	}
	sprintf(strLog, "        OK: Write to NVRAM Successfully.\n\n");
	UpdateLog ( strLog, 60 );
	Sleep(200);

	sprintf(strLog, ">> Step:  start to Check  NVRAM data...\n");
	UpdateLog ( strLog, 70 );
	g_MetaAP.tNVRAM_ReadReq.LID = LID_Name;
       g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
       g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
       g_MetaAP.tNVRAM_ReadCnf.buf = check_buf;

	g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
	if ( REQ_ReadFromNVRAM ()!=META_SUCCESS )
       {
           sprintf(strLog, "      Error: Read  NVRAM data Fail....\n\n");
	    UpdateLog ( strLog, 70 );
	    UpdateIndicator ( KAL_FALSE );	
    	rett = 5;
		goto err;
       }

	if ( memcmp ( check_buf, eeprom_buf, EEPROM_SIZE ) )
	{
		sprintf(strLog, "    Error:  Check  NVRAM data Fail.\n\n");
	       UpdateLog ( strLog, 80 );
		UpdateIndicator ( KAL_FALSE );
		rett = 6;
		goto err;
	}
	else
	{
		sprintf(strLog, "      OK: Check  NVRAM data OK!.\n\n");
	       UpdateLog ( strLog, 80 );
	}
	err:
		return rett;
 }
/**************************************************************************************
	if(BackupSecondImei)
	{
		sprintf ( strLog, "\n>>Step: To Backup NVRAM to Bin Region, and Set Clean Boot Flag\n" );
		UpdateLog ( strLog, 90 );
		Delay (0.5);
		if ( META_SUCCESS != WM_META_SetCleanBootFlag_Customize ( g_Meta.iMeta_handle ) )   ///// Clean boot is very Importnant for Customer.
		{
			sprintf ( strLog, "    Error:!!!!! Fail to Backup NVRAM and WM_META_SetCleanBootFlag_Customize()\n" );
			UpdateLog ( strLog, 100 );	
			UpdateIndicator ( KAL_FALSE );
			return;
		}
		else
		{
			sprintf ( strLog, "    OK: Backup NVRAM and WM_META_SetCleanBootFlag_Customize() \n" );
			UpdateLog ( strLog, 95 );	
			UpdateIndicator ( KAL_TRUE );
		}
	}
	
	sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
	UpdateLog ( strLog, 100 );

	Exit_MetaAPMode ( );   
*******************************************************************/	
}

//---------------------------------------------------------------------------------------------------
kal_bool Switch2WM_META_Mode ( const int meta_handle )
{

       unsigned short us_com_port;


	if ( GetIsEnableMetaLog() )
	{
		Eboot_DebugOn ();
		SP_META_DebugOn ();
	}
	else
	{
		Eboot_DebugOff ();
		SP_META_DebugOff ();
	}
	
	Seg_MetaAPConnectReq ();

     
       if(IsUSBCOMPort())
        {
            g_MetaAP.tMETA_Connect_Req.com_port = usb_port;
        }
      
	 g_MetaAP.eMetaAP_Result = SP_META_ConnectInMetaMode_r ( g_Meta.iMetaAP_handle, &g_MetaAP.tMETA_Connect_Req, &g_Meta.bootstop, &g_MetaAP.tMETA_Connect_Report); 
	
        switch ( g_MetaAP.eMetaAP_Result )
       {
		case META_SUCCESS:

			 return KAL_FALSE; 
			 break;

		case META_INCORRECT_TARGET_VER:
			
		 	MessagePopup ("Meta Warning", "Modem NVRAM database inconsistent with target...");
			break;

		case META_COMM_FAIL:

			MessagePopup ("Meta Error", "Open COM port fail...");
			break;

		case META_COM_ERROR:

			MessagePopup ("Meta Error", "COM port doesn't exist...");
			break;

		case META_TIMEOUT:	

			MessagePopup ("Meta Error", "Connecting timeout...");
			break;

		case META_FAILED:
			MessagePopup ("Meta Error", "Can't connect to target.\nPlease Enable Meta Dll.Log to get detail cause... ");
			break;

		default: 
			break;
    }	

     return KAL_TRUE;
     
}




kal_bool WM_META_SetCleanBootFlag_Customize ( const int meta_handle, int writeOption )
{
	
	SetCleanBootFlag_REQ req;
	SetCleanBootFlag_CNF cnf;

	req.Notused = writeOption;
    return SP_META_SetCleanBootFlag_r ( g_Meta.iMetaAP_handle, 5000, &req, &cnf );
}

//===========================================================================
META_RESULT REQ_ReadWifiMACFromNVRAM_Start ( WiFi_MacAddress_S *MACAddress )
{
  kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID = "AP_CFG_RDEB_FILE_WIFI_LID";
    int index = 0;
    kal_uint8 FieldName[20];
    kal_uint8 *uBTbuffer;
    unsigned long ChipVersion;
	unsigned long m_wifiChipVersion;
	unsigned int offset = 0;
    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        //TODO: LOG
          return g_MetaAP.eMetaAP_Result;
    }

    if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
    {
	  free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
	  g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
    }
	
      /*g_MetaAP.tNVRAM_ReadReq.LID = pLID;
      g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
      g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
      g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));
	g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
	if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
       {
    	    return g_MetaAP.eMetaAP_Result;
       }

      for (index=0; index < 6; index=index+2)
      {
        MACAddress->mac_addr[index] = g_MetaAP.tNVRAM_ReadCnf.buf[0x26+index+1];
        MACAddress->mac_addr[index+1] = g_MetaAP.tNVRAM_ReadCnf.buf[0x26+index];
      }*/

	  
 /*************************************
      g_MetaAP.eMetaAP_Result = SP_META_WiFi_GetChipVersion_r(g_Meta.iMetaAP_handle, 5000, &ChipVersion);
      if(g_MetaAP.eMetaAP_Result != META_SUCCESS)
      {
	    return g_MetaAP.eMetaAP_Result;
      }
  ******************************************/
	  g_MetaAP.eMetaAP_Result = SP_META_WiFi_readMCR32_r(g_Meta.iMetaAP_handle, 20000,offset, &m_wifiChipVersion);
	  if(META_SUCCESS != g_MetaAP.eMetaAP_Result)
	  {
		  return g_MetaAP.eMetaAP_Result;
	  }
	  ChipVersion = m_wifiChipVersion & 0xFFFF;
	
      if(ChipVersion == MT6620 || ChipVersion == MT6628 || ChipVersion == MT6572 || ChipVersion == MT6582 || ChipVersion == MT5931) 
    	{
    	
		/*uBTbuffer = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));
		for(index=0; index < 3; index++)
		{
		  	sprintf(FieldName, "usMacAddr[%d]", index);
			SP_META_NVRAM_GetRecFieldValue(pLID, FieldName, uBTbuffer, m_iBTBufSize, &MACAddress->mac_addr[index*2], sizeof(kal_uint16));
		}

		if(uBTbuffer != NULL)
		{
			free(uBTbuffer);
		}*/
			g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	       	g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	       	g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
	      	g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));
			g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
			if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
	       	{
	    	    return g_MetaAP.eMetaAP_Result;
	       	}

	       	for (index=0; index < 6; index=index+2)
	      	{
	        	MACAddress->mac_addr[index] = g_MetaAP.tNVRAM_ReadCnf.buf[0x4+index+1];
	        	MACAddress->mac_addr[index+1] = g_MetaAP.tNVRAM_ReadCnf.buf[0x4+index];
	      	}
			
	  }
	  else if(MT5921 == ChipVersion /*|| MT5931 == ChipVersion*/)
	  {
			g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	       	g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	       	g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
	      	g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));
			g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
			if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
	       	{
	    	    return g_MetaAP.eMetaAP_Result;
	       	}

	       	for (index=0; index < 6; index=index+2)
	       	{
	        	MACAddress->mac_addr[index] = g_MetaAP.tNVRAM_ReadCnf.buf[0x26+index+1];
	        	MACAddress->mac_addr[index+1] = g_MetaAP.tNVRAM_ReadCnf.buf[0x26+index];
	       	}
	  }
	 else
	  {
	       sprintf ( strLog, " SP_META_WiFi_GetChipVersion_r return success, but get the Wifi ChipVersion failed.\n");
		   UpdateLog ( strLog, 100);
		   return META_FAILED;
	  }
      if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
      {
      		free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
			g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
      }

    return META_SUCCESS;
}

//===========================================================================
META_RESULT REQ_WriteWifiMAC2NVRAM_Start (WiFi_MacAddress_S *MACAddress)
{
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID = "AP_CFG_RDEB_FILE_WIFI_LID";
    //nvram_ef_btradio_mt6611_struct  tBT;
    int index = 0;
    kal_uint16 tempValue = 0;
    kal_uint8* tBTbuffer;
    char FiledName[20];
    unsigned long ChipVersion;
  	unsigned int u4Addr = 0;
    unsigned long u4Value = 0;
  

    g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );
    if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
    {
        //TODO: LOG
        return g_MetaAP.eMetaAP_Result;
    }

    if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
    {
	    free ( g_MetaAP.tNVRAM_ReadCnf.buf );	
	    g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
    }

	g_MetaAP.eMetaAP_Result = SP_META_WiFi_readMCR32_r(g_Meta.iMetaAP_handle, 20000, u4Addr, &u4Value);
    //g_MetaAP.eMetaAP_Result = SP_META_WiFi_GetChipVersion_r(g_Meta.iMetaAP_handle, 20000, &ChipVersion);
    if(g_MetaAP.eMetaAP_Result != META_SUCCESS)
    {
	    return g_MetaAP.eMetaAP_Result;
    }

    ChipVersion = u4Value & 0xFFFF;
//	sprintf ( strLog, "readMCR: wifi chip version is %s.\n",ChipVersion);
    if(ChipVersion == MT6620 || ChipVersion == MT6628 || ChipVersion == MT6572 || ChipVersion == MT6582 || ChipVersion == MT5931)
    {	
		g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	   	g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	    g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
	    g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

		g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
		if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
       	{
    	    return g_MetaAP.eMetaAP_Result;
       	}

	    //Modify MAC Address Part
       	for (index = 0; index <6; index=index+2)
       	{
            g_MetaAP.tNVRAM_ReadCnf.buf[0x4+index+1] = MACAddress->mac_addr[index];
            g_MetaAP.tNVRAM_ReadCnf.buf[0x4+index] = MACAddress->mac_addr[index+1];
       	}

	    Checksum_Generation (g_MetaAP.tNVRAM_ReadCnf.buf);
			
		m_usRID = 1;
		g_MetaAP.tNVRAM_WriteReq.LID = pLID;
       	g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
       	g_MetaAP.tNVRAM_WriteReq.len = m_iBTBufSize;
       	g_MetaAP.tNVRAM_WriteReq.buf = g_MetaAP.tNVRAM_ReadCnf.buf;
	       
		g_MetaAP.eMetaAP_Result = REQ_Write2NVRAM ();
	    
		if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
       	{
    	    return g_MetaAP.eMetaAP_Result;
       	}

	    if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
		{
			free ( g_MetaAP.tNVRAM_ReadCnf.buf );
			g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
			g_MetaAP.tNVRAM_WriteReq.buf = NULL;
		}
        // change by MTK71518
        /* already free by g_MetaAP.tNVRAM_ReadCnf.buf
		if (NULL != g_MetaAP.tNVRAM_WriteReq.buf)
		{
			free (g_MetaAP.tNVRAM_WriteReq.buf);	
			g_MetaAP.tNVRAM_WriteReq.buf = NULL;
		}
		*/
    }
	else if(ChipVersion == MT5921 /*|| ChipVersion == MT5931*/)
	{
	      g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	      g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	      g_MetaAP.tNVRAM_ReadCnf.len = m_iBTBufSize;
	      g_MetaAP.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

		g_MetaAP.eMetaAP_Result =  REQ_ReadFromNVRAM ();
		if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
	       {
	    	    return g_MetaAP.eMetaAP_Result;
	       }

	       //Modify MAC Address Part
	       
	       for (index = 0; index <6; index=index+2)
	       {
	            g_MetaAP.tNVRAM_ReadCnf.buf[0x26+index+1] = MACAddress->mac_addr[index];
	            g_MetaAP.tNVRAM_ReadCnf.buf[0x26+index] = MACAddress->mac_addr[index+1];
	       }

	       Checksum_Generation (g_MetaAP.tNVRAM_ReadCnf.buf);
			
		m_usRID = 1;
		g_MetaAP.tNVRAM_WriteReq.LID = pLID;
	    g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
	    g_MetaAP.tNVRAM_WriteReq.len = m_iBTBufSize;
	    g_MetaAP.tNVRAM_WriteReq.buf = g_MetaAP.tNVRAM_ReadCnf.buf;
	       
		g_MetaAP.eMetaAP_Result = REQ_Write2NVRAM ();
	    
		if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
       	{
    	    return g_MetaAP.eMetaAP_Result;
       	}

	    if ( NULL != g_MetaAP.tNVRAM_ReadCnf.buf )
		{
			free ( g_MetaAP.tNVRAM_ReadCnf.buf );
			g_MetaAP.tNVRAM_ReadCnf.buf = NULL;
			g_MetaAP.tNVRAM_WriteReq.buf = NULL;
		}
        // change by MTK71518
        /* already free by g_MetaAP.tNVRAM_ReadCnf.buf
		if (NULL != g_MetaAP.tNVRAM_WriteReq.buf)
		{
			free (g_MetaAP.tNVRAM_WriteReq.buf);	
			g_MetaAP.tNVRAM_WriteReq.buf = NULL;
		}
		*/
    }
	else
	{
	    sprintf ( strLog, " SP_META_WiFi_GetChipVersion_r return success, but get the Wifi ChipVersion failed.\n");
		UpdateLog ( strLog, 100);
		return META_FAILED;
	}
    return META_SUCCESS;
}

/*
//----------------------------------------------------------------------
void func_bt_address_meta_hdlr_smart_phone ( void )
{
	kal_uint8 strTip [256] , i, iBCD_L, iBCD_H;
	
	BT_ModuleID_S BT_ID;
	
	S_HANDSET_BT_ADRRESS tBtAddress_W, tBtAddress_R;
		
	kal_uint8 strBtAddress_W [ BT_ADDRESS_MAX_LENGTH + 1 ];
	kal_uint8 strBtAddress_R [ BT_ADDRESS_MAX_LENGTH + 1 ];
	kal_uint16 iLoop = 0;
	
	BT_ID.id = BTMODULE_MT6611;

	sprintf ( strLog, ">>Step: Enter func_bt_address_meta_hdlr_smart_phone();\n");
	strcat ( strLog,  "        Write BT Address to smartphone AP nvram.\n");
	UpdateLog ( strLog, 0 );
	
	sprintf ( strLog, ">>Step: Start to Init AP Nvram Database...\n");
	UpdateLog ( strLog, 20 );

	if ( IsAPNvramDatabaseInit() ) 

	{ 
		sprintf ( strLog, "   Error: Init Modem Nvram Database failed.\n");
		UpdateLog ( strLog, 100);
		return;
	}

	sprintf ( strLog, "   OK: Init Modem Nvram Database successfully.\n");
	UpdateLog ( strLog, 100 );
	
	Seg_MetaAPConnectReq ();

	g_MetaAP.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_MetaAP.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{
		sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );	

		sprintf ( strLog, ">>Step: Scan Smartphone BT Address.\n");
		UpdateLog ( strLog, 10 );

		
		
		sprintf ( strTip, "Please scan SmartPhone BT address, then Power On phone..." );
		g_MetaAP.eRunStatus = InputBoxPopup ("BT Address (12 Bytes)", strTip, (kal_int8*) strBtAddress_W, BT_ADDRESS_MAX_LENGTH );

		ResetIndicator ();
		if ( iLoop++ == 50)
		{
			ClearLog ();
			iLoop = 0;
		}
		
		if ( OK_STATUS == g_MetaAP.eRunStatus ) 
		{

		    sprintf ( strLog, "    OK: BT Address = \"%s\".\n", strBtAddress_W );
			UpdateLog ( strLog, 20 );

			sprintf ( strLog, ">>Step: Start to Connect with target.\n" );
			UpdateLog ( strLog, 30 );
					
		    if ( EnterMetaAPMode () ) 
		    {
				Exit_MetaAPMode ();
				
				sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode and turn to next phone.\n" );
				UpdateLog ( strLog, 100 );
				
				UpdateIndicator ( KAL_FALSE );
				continue; 
		     }
			sprintf ( strLog,  "   OK: Connect to target successfully.\n" );
			UpdateLog ( strLog, 50 );
			
			sprintf ( strLog,  ">>Step: Start to write BT Address.\n" );
			UpdateLog ( strLog, 50 );
			
			//-------------------------------------------------------------------/
			// Not support the meta function yet
			//if ( META_QueryIfFunctionSupportedByTarget_r ( g_Meta.iMeta_handle, 5000, "META_BT_QueryModuleID_r" ))
			//{
			//	if ( META_BT_QueryModuleID_r (g_Meta.iMeta_handle, 5000, &BT_ID ))
			//	{
			//		MessagePopup ("BT Address Error", " Query BT Module fail!");
			//	}

			//}

			for ( i = 0; i < BT_ADDRESS_MAX_LENGTH; i += 2 )
			{
				 
				 iBCD_H = Ascii2BCD( strBtAddress_W [i] );
				 iBCD_L = Ascii2BCD( strBtAddress_W [i + 1] );

				tBtAddress_W.bd_addr [i/2] = iBCD_H<<4 | iBCD_L;
				
			}

			switch ( BT_ID.id )	
			{
				case BTMODULE_MT6601:  //6601
				case BTMODULE_MT6611:
				//case BTMODULE_MT6612:
					if ( g_MetaAP.eMetaAP_Result  = REQ_WriteBTAddr2NVRAM_Start ( BT_ID.id, tBtAddress_W.bd_addr) )
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", g_MetaAP.eMetaAP_Result );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						Exit_MetaAPMode ();  
						
						MessagePopup ("BT Address Error", "BD Address write fail");  
											
						continue;
					}
					break;
				case BTMODULE_RFMD3500:  //RFMD
				case BTMODULE_RFMD4020:
					if ( g_MetaAP.eMetaAP_Result  = REQ_WriteBTAddr2NVRAM_Start ( BT_ID.id, tBtAddress_W.bd_addr ) )
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", g_MetaAP.eMetaAP_Result );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						
						MessagePopup ("BT Address Error", "BD Address write fail");
						Exit_MetaAPMode ();
						continue;
					}
					
					break;
				default:
					break;
			}

			sprintf ( strLog, "   OK: Write BT Address successfully.\n"  );
			UpdateLog ( strLog, 70 );	

			if ( REQ_ReadBTAddrFromNVRAM_Start ( BT_ID.id, tBtAddress_R.bd_addr) )
			{
				//TODO
			}

			sprintf ( strLog, "   Step: Check BT Address.\n"  );
			UpdateLog ( strLog, 80 );	
			
			if ( memcmp ( tBtAddress_W.bd_addr, tBtAddress_R.bd_addr, BD_ADDR_LEN )) {

				
				sprintf ( strLog, "   Error: Check BT Address fail. BT Address = \"%x %x %x %x %x %x\".\n",  tBtAddress_R.bd_addr[0],
																											 tBtAddress_R.bd_addr[1],
																											 tBtAddress_R.bd_addr[2],
																											 tBtAddress_R.bd_addr[3],
																											 tBtAddress_R.bd_addr[4],
																											 tBtAddress_R.bd_addr[5]);

				UpdateLog ( strLog, 100 );
				
				UpdateIndicator ( KAL_FALSE );
				MessagePopup ("BT Address Error", " Read/Write BT Address inconsist");
				;
				
			}
			else
			{
				sprintf ( strLog, "   OK: Check BT Address. BT Address  = \"%x %x %x %x %x %x\".\n.", tBtAddress_R.bd_addr[0],
																		    					      tBtAddress_R.bd_addr[1],
																		  					          tBtAddress_R.bd_addr[2],
																		   					          tBtAddress_R.bd_addr[3],
																		   					          tBtAddress_R.bd_addr[4],
																		   					          tBtAddress_R.bd_addr[5]);
				UpdateLog ( strLog, 90 );
				UpdateIndicator ( KAL_TRUE );
			}
	
		}
		else
		{

			sprintf ( strLog, ">>Step:: Cancel scan BT Address DiagBox.\n");
			UpdateLog ( strLog, 100 );
			
			break;

		}

		sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
		UpdateLog ( strLog, 100 );
		
		Exit_MetaAPMode ();   
		
	}//while ()          
}
*/

//------------------------------------for Smartphone wifi para copy from Module to NVRAM ------------------
META_RESULT SP_Read_Wifi_Para_From_EEPROM ( kal_uint8* eepromInByte )
{
	unsigned char lowbyte = 0;
	unsigned char highbyte = 0;
	unsigned long oneWord = 0;
	unsigned int offset = 0; // unit : word
	int index = 0, m_usRID = 1, m_iBTBufSize;
	short token;
	char LID_Name[100];
	META_RESULT metaResult = 0;
	int ret;
	unsigned short value = 0;

       //Read from EEPROM word by word
	index = 0;
	sprintf (strLog, "\r\n\r\n");
	UpdateLog ( strLog, 50 );
	for(offset = 0; offset < EEPROM_SIZE/2; offset ++)
	{
	
		metaResult = SP_META_WiFi_readEEPRom16_r (g_Meta.iMetaAP_handle, 5000, offset, &oneWord);
		if(META_SUCCESS != metaResult)
		{
		       return metaResult;
		}

               value = (unsigned short) oneWord;
		lowbyte = value & 0x00FF;
		highbyte = (value >> 8) & 0x00FF;
		eepromInByte[index ++] = lowbyte;
		eepromInByte[index ++] = highbyte;

              //print eeprom data
		sprintf(strLog, "%02x %02x ", eepromInByte[index-2],eepromInByte[index-1]);
		UpdateLog ( strLog, 50 );
		if(index % 16 == 0)
		{
			sprintf(strLog, "\r\n");
			UpdateLog ( strLog, 50 );
		}
	}
	
	return META_SUCCESS;

}


void Checksum_Generation(unsigned char StorageBuf[])
{
	int u2Len = (EEPROM_NIC_CHKSUM_ADD_DW - EEPROM_NIC_CHKSUM_START_ADD_DW + 1) * 2;

	/* 5921 Start NIC EEPROM Checksum from 0x0D ~ 0x9F */
	int StartIndex = EEPROM_NIC_CHKSUM_START_ADD_DW * 2;	//from word to byte
	int EndIndex = EEPROM_NIC_CHKSUM_ADD_DW * 2;
	int LoopIndex = 0;
	unsigned char Chksum = 0;
	unsigned char New_Chksum = 0;
	unsigned char Old_Chksum = 0;
	
       //for (LoopIndex = StartIndex; LoopIndex <= EndIndex; LoopIndex++)
       for (LoopIndex = 0; LoopIndex < u2Len - 1; LoopIndex++)//not count 0x13F
       {
              Chksum = (Chksum + StorageBuf[LoopIndex + StartIndex]) & 0x00FF;
       }
       Old_Chksum = StorageBuf[0x13F];
	New_Chksum = (0x01FF - Chksum) & 0x00FF;
    
       StorageBuf[0x13F] = (0x01FF - Chksum) & 0x00FF;
}

int AP_META_DisconnectInMetaMode_r(const int meta_handle)
{
    META_RESULT meta_result = META_SUCCESS;

    meta_result = SP_META_DisconnectInMetaMode_r(meta_handle);
    return meta_result;
}


int ModemMetaToAPMeta (void)
{
	META_RESULT MetaResult = 0;
    WM_META_ConnectInMETA_Req BootRequest;
	int BootStop = 0;
	WM_META_ConnectInMETA_Report BootReport;

    //MetaResult = META_DisconnectInMetaMode_r (g_Meta.iMeta_handle);
    MetaResult = FP_META_DisconnectInMetaMode_r (g_Meta.iMeta_handle);
	if (META_SUCCESS != MetaResult)
	{
		return MetaResult;
	}

    BootRequest.com_port = GetCOMPort();
	BootRequest.baudrate[0] = META_BAUD115200;
	BootRequest.baudrate[1] = META_BAUD230400;
	BootRequest.baudrate[2] = META_BAUD460800;
	BootRequest.baudrate[3] = META_BAUD921600;
	BootRequest.baudrate[4] = META_BAUD57600;
	BootRequest.baudrate[5] = META_BAUD_END;

	BootRequest.flowctrl = META_NO_FLOWCTRL;//META_SW_FLOWCTRL;
	BootRequest.ms_connect_timeout = 80000;

	if(IsUSBCOMPort())
    {
       BootRequest.com_port = usb_port;
    }

	MetaResult = SP_META_ConnectInMetaMode_r(g_Meta.iMetaAP_handle, &BootRequest, &BootStop, &BootReport);
	Sleep(200);
	if (META_SUCCESS != MetaResult)
	{
		return MetaResult;
	}

	return MetaResult;
}

static void  __stdcall CNF_ReadNVRAM( const FT_NVRAM_READ_CNF *cnf, const short token, void *usrData)
{
//    g_nvram_ptr->CNF_ReadNVRAM( cnf, token, usrData);
	int check = 0;
	check = 1;

       SetEvent (g_MetaAP.m_ReadFromNVRAMEvent);   
}

 META_RESULT SP_WIFI_Save_NVRAM_To_File (int meta_handle, char file_path[], char file_name[])
 {
        META_RESULT meta_result = META_SUCCESS;
        unsigned char *m_pcAdcBuf = NULL;
    	 int m_uiAdcBufSize = 0;
    	 FT_NVRAM_READ_REQ NVRAM_ReadReq;
    	 FT_NVRAM_READ_CNF NVRAM_ReadCnf;
    	 char LID_Name[100];
        short token = 0;
    	 int file_path_len = 0;
        char abs_file_name[300];
        int file_handle = 0;

        unsigned char buf[1024];
        unsigned char tempBuf[2];
        int i = 0;
        int returnValue = 0;

    	 strcpy(LID_Name, "AP_CFG_RDEB_FILE_WIFI_LID");

        // Check file path and file name
        file_path_len = strlen (file_path);
        if ('\\' == file_path[file_path_len-1])
        {
            sprintf (abs_file_name, "%s%s", file_path, file_name);
        }
        else
        {
            sprintf (abs_file_name, "%s\\%s", file_path, file_name);
        }

        //Get WIFI Nvram Length (512bytes)
    	 meta_result = SP_META_NVRAM_GetRecLen(LID_Name, (int *) &m_uiAdcBufSize);
    	 if (META_SUCCESS != meta_result)
    	 {
    	    goto Error;
    	 }

    	 m_pcAdcBuf = calloc (m_uiAdcBufSize, sizeof(char));

    	 // Read WIFI nvram value
        NVRAM_ReadReq.LID = LID_Name;
        NVRAM_ReadReq.RID = 1;
        NVRAM_ReadCnf.len = m_uiAdcBufSize;
        NVRAM_ReadCnf.buf = m_pcAdcBuf;

        //WM_META_NVRAM_Read_r(meta_handle, const FT_NVRAM_READ_REQ * req, FT_NVRAM_READ_CNF * cnf, const META_NVRAM_Read_CNF cb, short * token, void * usrData);
        
        //meta_result = ApMeta_NVRAM_Read_r (meta_handle, &NVRAM_ReadReq, m_pcAdcBuf, m_uiAdcBufSize, &token, NULL);

        ResetEvent ( g_MetaAP.m_ReadFromNVRAMEvent );

    	 meta_result = SP_META_NVRAM_Read_r(meta_handle,
    										   &NVRAM_ReadReq,
    										   &NVRAM_ReadCnf,
    										   CNF_ReadNVRAM,
    										   &token,
    										   NULL);
    	 if(META_SUCCESS != meta_result)
    	 {
          goto Error;
    	 }
    	 Sleep(200);

        WaitForSingleObject ( g_MetaAP.m_ReadFromNVRAMEvent, 25000 );

        strcpy (buf, "");
        for (i = 0; i < m_uiAdcBufSize; i = i + 2)
        {
            sprintf (tempBuf, "%02x", m_pcAdcBuf[i+1]);
            sprintf (buf, "%s%s", buf, tempBuf);

            sprintf (tempBuf, "%02x", m_pcAdcBuf[i]);
            sprintf (buf, "%s%s", buf, tempBuf);
        }

        for (i=0; i < m_uiAdcBufSize; i ++)
        {
            if ('a' <= buf[i] && 'z' >= buf[i])
            {
                buf[i] = buf[i] - 32;
            }
        }

        // Write NVRAM data to file
        file_handle= OpenFile (abs_file_name, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
        if (file_handle < 0)
        {
            meta_result = -1;
            goto Error;
        }
      	 returnValue = WriteFile (file_handle, buf, 2*m_uiAdcBufSize);  
        Sleep (50);
        if (returnValue < 0)
        {
            meta_result = -1;
            goto Error;
        }
        CloseFile (file_handle);
         
        free (m_pcAdcBuf);
        return meta_result;

 Error:
        if (NULL != m_pcAdcBuf)
        {
            free (m_pcAdcBuf);
            m_pcAdcBuf = NULL;
        }
        if (file_handle > 0)
        {
            CloseFile (file_handle);
            file_handle = 0;
        }
        return meta_result;
 }
 int  func_hdcp_key_meta_hdlr_smart_phone ( void )
  {
  
	  kal_uint8 eeprom_buf [EEPROM_SIZE], check_buf[EEPROM_SIZE];
	  int m_usRID = 1, m_iBTBufSize;
	  short token;
	  char LID_Name[100];
	  META_RESULT metaResult = 0;
	  int ret;
	  unsigned short value = 0;
	  kal_uint32 BackupSecondImei = 0;
	  char curHdcpFilePatch[1024]={0};
	  int returnvalue;
	  int i;
	  int rett = 0;
	   extern int ret_statue;
	  
	/*************************************************************************  
	  sprintf ( strLog, ">> Step: Enter func_hdcp_key_meta_hdlr_smart_phone();\n");
	  strcat ( strLog,	"	   Copy Wifi Paranmenter from EEPROM to NVRAM.\n\n");
	  UpdateLog ( strLog, 0 );
	  
	  sprintf ( strLog, ">> Step: Start to Init AP Nvram Database...\n");
	  UpdateLog ( strLog, 20 );
  
	  if ( IsAPNvramDatabaseInit() ) 
  
	  { 
		  sprintf ( strLog, "	Error: Init AP Nvram Database failed.\n\n");
		  UpdateLog ( strLog, 100);
		  return;
	  }
  
	  sprintf ( strLog, "	OK: Init AP Nvram Database successfully.\n\n");
	  UpdateLog ( strLog, 100 );
	  
	  Seg_MetaAPConnectReq ();
	  GetUISetCleanBootFlag(KAL_TRUE, &BackupSecondImei);
  
	  g_MetaAP.eRunStatus = RUN_STATUS;
  
	  sprintf ( strLog, ">> Step: Start to Enter Meta mode, Please Powe On phone\n" );
	  
	  UpdateLog ( strLog, 0 );	  
  
	  ResetIndicator ();
  
	  if ( EnterMetaAPMode () ) 
	  {
		  Exit_MetaAPMode ();
		  
		  sprintf ( strLog, "		Error: Connect failed, Exit Meta Mode and turn to next phone.\n\n" );
		  UpdateLog ( strLog, 100 );
		  UpdateIndicator ( KAL_FALSE );
		  return;
	  }
	  
	  sprintf ( strLog,  "		 OK: Connect to target successfully.\n\n" );
	  UpdateLog ( strLog, 30 );
****************************************************************************************************/
  //load key file
	  returnvalue = Load_HDCP_Key_File(HdcpKeyFilePath);
	  if(returnvalue<0)
	  {
		 sprintf ( strLog,	 "		 FAIL: Load_HDCP_Key_File.\n\n" );
		 UpdateLog ( strLog, 100 );
		 UpdateIndicator ( KAL_FALSE );
		 Exit_MetaAPMode ( );
		 rett = 1;
		 goto err;
	  }
  //write hdcpkey to nvram
	  returnvalue = REQ_WriteHdcpKey2NVRAM_Start();
  
	  if(returnvalue != 0)
	  {
		 sprintf ( strLog,	 "		 FAIL: REQ_WriteHdcpKey2NVRAM_Start.\n\n" );
		 UpdateLog ( strLog, 100 );
		 UpdateIndicator ( KAL_FALSE );
		 Exit_MetaAPMode ( );
		  rett = 2;
		 goto err;
	  }
  //readback hdcp key
	  returnvalue = REQ_ReadHdcpKeyFromNVRAM_Start();
	  if(returnvalue != 0)
	  {
		 sprintf ( strLog,	 "		 FAIL: REQ_ReadHdcpKeyFromNVRAM_Start.\n\n" );
		 UpdateLog ( strLog, 100 );
		 UpdateIndicator ( KAL_FALSE );
		 Exit_MetaAPMode ( );
		  rett = 3;
		 goto err;
	  }
 //if the write is the same as the read, remove the HDCP Key file
	 for(i=0;i<287;i++)
	 {
		 //printf("%x, %x\n",m_sHDCPNvramStruct.HdcpKeyArray[i],m_sReadBackHdcp.HdcpKeyArray[i]);
		 if(m_sHDCPNvramStruct.HdcpKeyArray[i]!=m_sReadBackHdcp.HdcpKeyArray[i])
		 {
			 sprintf ( strLog, " FAIL:The Key Read back is not the same as the write \n" );
			 UpdateLog ( strLog, 100 );   
			 UpdateIndicator ( KAL_FALSE );
			 Exit_MetaAPMode( );
			  rett = 4;
		 goto err;
			 
		 }
		 
	 }
	 
	 remove(HdcpFileName);
	 sprintf ( strLog, " OK: Write HDCP Key File\n" );
	 UpdateLog ( strLog, 95 );	  
//	 UpdateIndicator ( KAL_TRUE );
	  err:
	  	return rett;
 	}
/*****************************************************************************************	  
	  if(BackupSecondImei)
	  {
		  sprintf ( strLog, "\n>>Step: To Backup NVRAM to Bin Region, and Set Clean Boot Flag\n" );
		  UpdateLog ( strLog, 90 );
		  Delay (0.5);
		  if ( META_SUCCESS != WM_META_SetCleanBootFlag_Customize ( g_Meta.iMeta_handle ) )   ///// Clean boot is very Importnant for Customer.
		  {
			  sprintf ( strLog, "	 Error:!!!!! Fail to Backup NVRAM and WM_META_SetCleanBootFlag_Customize()\n" );
			  UpdateLog ( strLog, 100 );  
			  UpdateIndicator ( KAL_FALSE );
			  return;
		  }
		  else
		  {
			  sprintf ( strLog, "	 OK: Backup NVRAM and WM_META_SetCleanBootFlag_Customize() \n" );
			  UpdateLog ( strLog, 95 );   
			  UpdateIndicator ( KAL_TRUE );
		  }
	  }
	  Exit_MetaAPMode ( );
	  sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
	  UpdateLog ( strLog, 100 );  
*****************************************************************************************/
 
 
  META_RESULT REQ_WriteHdcpKey2NVRAM_Start (void)
  {
	  kal_int32 m_usRID = 1;
	  kal_int32 m_iHDCPBufSize;
	  kal_uint8 *pLID = "AP_CFG_RDCL_FILE_HDCP_KEY_LID";
	  //nvram_ef_btradio_mt6611_struct	tBT;
	  int index = 0;
	  kal_uint16 tempValue = 0;
	  kal_uint8* m_pcHDCPBuf;
	  char FiledName[20];
	  unsigned long ChipVersion;
	
  
	  g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &m_iHDCPBufSize );
	  if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
	  {
		  //TODO: LOG
		  return g_MetaAP.eMetaAP_Result;
	  }
  
	 m_pcHDCPBuf = (kal_uint8*) malloc (m_iHDCPBufSize*sizeof(kal_uint8));
	  
	  g_MetaAP.eMetaAP_Result = SP_META_NVRAM_Compose_HDCP(&m_sHDCPNvramStruct, m_pcHDCPBuf, m_iHDCPBufSize);
 
	  if (g_MetaAP.eMetaAP_Result != META_SUCCESS)
	  {
		 //Confirm(META_FAILED);
		 return META_FAILED;
	  }
  
	 g_MetaAP.tNVRAM_WriteReq.LID = pLID;
	 g_MetaAP.tNVRAM_WriteReq.RID = m_usRID;
	 g_MetaAP.tNVRAM_WriteReq.len = m_iHDCPBufSize;
	 g_MetaAP.tNVRAM_WriteReq.buf = m_pcHDCPBuf;
		  
	 g_MetaAP.eMetaAP_Result = REQ_Write2NVRAM ();
		  
	 if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
	 {
		 return g_MetaAP.eMetaAP_Result;
	 }
  
	 if(NULL != m_pcHDCPBuf)
	 {
		 free ( m_pcHDCPBuf);
		 m_pcHDCPBuf = NULL;
	 }
	 return META_SUCCESS;
  }
 
  META_RESULT REQ_ReadHdcpKeyFromNVRAM_Start ( void )
  {
	kal_int32 m_usRID = 1;
	  kal_int32 m_iHDCPBufSize;
	  kal_uint8 *pLID = "AP_CFG_RDCL_FILE_HDCP_KEY_LID";
	  int index = 0;
	  kal_uint8 FieldName[20];
	  kal_uint8 *m_pcHDCPBuf;
	  unsigned long ChipVersion;
	  META_RESULT mr;
	  
	  g_MetaAP.eMetaAP_Result = SP_META_NVRAM_GetRecLen ( pLID, &m_iHDCPBufSize );
	  if ( g_MetaAP.eMetaAP_Result != META_SUCCESS )
	  {
		  //TODO: LOG
			return g_MetaAP.eMetaAP_Result;
	  }
  
	 m_pcHDCPBuf = (kal_uint8*) malloc (m_iHDCPBufSize*sizeof(kal_uint8));
	   
		 
	 g_MetaAP.tNVRAM_ReadReq.LID = pLID;
	 g_MetaAP.tNVRAM_ReadReq.RID = m_usRID;
	 g_MetaAP.tNVRAM_ReadCnf.len = m_iHDCPBufSize;
	 g_MetaAP.tNVRAM_ReadCnf.buf = m_pcHDCPBuf;
	 g_MetaAP.eMetaAP_Result =	 REQ_ReadFromNVRAM ();
	 if ( g_MetaAP.eMetaAP_Result!=META_SUCCESS )
	 {
		 return g_MetaAP.eMetaAP_Result;
	 }
  
	 
	 mr = SP_META_NVRAM_Decompose_HDCP(&m_sReadBackHdcp, m_pcHDCPBuf, m_iHDCPBufSize);
	 if(mr != META_SUCCESS)
		 return META_FAILED;
			  
	 return META_SUCCESS;
  }
 
 int Load_HDCP_Key_File(char *filepath)
 {
	 int count = 0;
	 char bufNoEncrypt[HDCP_KEY_ARRAY_NUMBER_FILE] = {0};
	 char bufEncrypt[HDCP_KEY_ARRAY_NUMBER] = {0};
	 char* chCurPath;
	 char* chNewPath;
	 int ret;
	 //struct _finddata_t data;  
	 HANDLE hnd;
	 int file_size;
	 FILE *fp;
	 EN_HDCP_RET retHdcp;
	 LPWIN32_FIND_DATA file_data;
	 int i;
	 char tempfile[1024]; 
	 char logbuffer[100];
	 
	 file_data = malloc(sizeof(WIN32_FIND_DATA));
	 sprintf(strLog, ">> Step:	 Read key file \n");
	 UpdateLog ( strLog, 40 );

	 sprintf(tempfile,"%s\\*.bin",HdcpKeyFilePath);
	 hnd = FindFirstFile(tempfile,file_data);
	 //hnd = _findfirst( "*.bin", &data ); 
	 if(hnd == INVALID_HANDLE_VALUE)
	 {
		 sprintf ( strLog,	 "FAIL: Key File is not found\n\n");
//		 UpdateIndicator ( KAL_FALSE );
		 UpdateLog ( strLog, 100 );
		 return -1;
	 }
	 sprintf ( strLog,	 "Find a key file: %s\n\n", file_data->cFileName);
	 UpdateLog ( strLog, 50 );
	 //memcpy(HdcpFileName,0,1024);
	 sprintf(HdcpFileName,"%s\\%s",HdcpKeyFilePath,file_data->cFileName);
	 
	 fp = fopen(HdcpFileName,"rb");
	 if(fp == NULL)
	 {
		 sprintf ( strLog,	 "FAIL: Open Key File\n\n");
//		 UpdateIndicator ( KAL_FALSE );
		 UpdateLog ( strLog, 100 );
		 return -1;
	 }
	 fseek(fp,0,SEEK_SET);
	 fread(bufNoEncrypt,sizeof(char),308,fp);
	 fseek(fp,0,SEEK_END);
	 file_size = ftell(fp);  
  
	 for( i = 0; i < HDCP_KEY_ARRAY_NUMBER_FILE; i++)
	 {
		 sprintf(strLog,"HDCP: HdcpProcess input bufNoEncrypt[%d]: 0x%2.2X.\n", i, bufNoEncrypt[i]&0xFF);
		 //strcat(strLog, logbuffer);
	 }
	 UpdateLog ( strLog, 60 );
 
	 retHdcp = HdcpProcess((unsigned char *)bufNoEncrypt, (unsigned char *)bufEncrypt);
 
	 if(R_OK != retHdcp)
	 {
		 sprintf (strLog,"FAIL: HdcpProcess return value is: %d\n\n",retHdcp);
//		 UpdateIndicator ( KAL_FALSE );
		 UpdateLog ( strLog, 100 );
		 return  -1;
	 }
	 
	 for( i = 0; i < HDCP_KEY_ARRAY_NUMBER; i++)
	 {
		 sprintf(strLog,"HDCP: HdcpProcess output bufEncrypt[%d]: 0x%2.2X.\n", i, bufEncrypt[i]&0xFF);
	 }
	 UpdateLog ( strLog, 60 );
	 fclose(fp);
 
	 
	 FindClose( hnd );		

	 memcpy((char*)&m_sHDCPNvramStruct, bufEncrypt, sizeof(bufEncrypt));
	 free (file_data);
	 return 0;
 }

void backup(void);

//DRM Key Install

 int  func_drm_key_meta_hdlr_smart_phone ( void )
  {
	  int returnvalue;
//	  const int meta_handle;
	  extern int ret_statue;
	  int ret = 0;
	  

	  DRMKEY_INSTALL_QUERY_REQ Req;
      DRMKEY_INSTALL_SET_CNF pCnf;
      DRMKEY_INSTALL_QUERY_CNF QueCnf;
	  memset(&Req,0,sizeof(DRMKEY_INSTALL_QUERY_REQ));
	  memset(&QueCnf,0,sizeof(DRMKEY_INSTALL_QUERY_CNF));
	  memset(&pCnf,0,sizeof(DRMKEY_INSTALL_SET_CNF));
 //     const char * filename;
  //load key file
	  returnvalue = Load_DRM_Key_File(DRMKeyFilePath);
	  if(returnvalue<0)
	  {
		 sprintf ( strLog,	 "FAIL: Load_DRM_Key_File.\n" );
		 UpdateLog ( strLog, 100 );
//		 UpdateIndicator ( KAL_FALSE );
		 Exit_MetaAPMode ( );
		 ret = 1;
		 goto err;
	  }
  //send to platform	 
//       filename = DRMFileName.c_str();
      g_MetaAP.eMetaAP_Result = SP_META_DRMKey_Install_Set_r(g_Meta.iMetaAP_handle,10000,(const char *)&DRMFileName,&pCnf);
	  if (g_MetaAP.eMetaAP_Result != META_SUCCESS)
	  {
	     sprintf ( strLog,	 "FAIL: Install DRM key.\n" );
		 UpdateLog ( strLog, 100 );
		 ret = 2;
		 goto err;
	  }
  //query form platform

     g_MetaAP.eMetaAP_Result = SP_META_DRMKey_Install_Query_r(g_Meta.iMetaAP_handle,5000, &Req, &QueCnf);
      if (g_MetaAP.eMetaAP_Result != META_SUCCESS)
	  {
	     sprintf ( strLog,	 "FAIL: Query Install DRM key.\n" );
		 UpdateLog ( strLog, 100 );
		 ret = 3;
		 goto err;
	  } 
	 if(QueCnf.keycount == 0)
	 {
  	   sprintf ( strLog,	 "FAIL: QueCnf.keycount = 0,Install DRM key fail .\n" );
	   UpdateLog ( strLog, 100 );
	   ret = 4;
	   goto err;
	 }

	 CreateDirectory("C:\\Program Files\\MTK_SN_Write_tool\\Delete\\",NULL);

	 CopyFile(DRMFileName,"C:\\Program Files\\MTK_SN_Write_tool\\Delete\\");



	 remove(DRMFileName);
	 sprintf ( strLog, " OK: Write DRM Key File\n" );
	 UpdateLog ( strLog, 95 );	  
	 UpdateIndicator ( KAL_TRUE );
	 err:
	 	return ret;
}




int Load_DRM_Key_File(char *filepath)
{
	HANDLE hnd;
	char tempfile[1024]; 
	int ret = 0;

	FILE *fp;

	char loadbuf[2052] = {0};

	files_data = malloc(sizeof(WIN32_FIND_DATA));
	sprintf(strLog, ">> Step:	Read key file \n");
	UpdateLog ( strLog, 40 );


//	sprintf(tempfile,"%s\\*file*",DRMKeyFilePath);

	sprintf(tempfile,"%s\\*.*",DRMKeyFilePath);

	hnd = FindFirstFile(tempfile,files_data);
    if (INVALID_HANDLE_VALUE == hnd) 
		{
		   ret = -1; 
		   goto err;
    	}
	while (1)
	{
	    if(files_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	       	FindNextFile(hnd, files_data);
		else 
			break;
	}
	sprintf ( strLog,	"Find a key file: %s\n\n", files_data->cFileName);
	UpdateLog ( strLog, 50 );

	sprintf(DRMFileName,"%s\\%s",DRMKeyFilePath,files_data->cFileName);
	
err:	
	free (files_data);
	FindClose( hnd );	
	return ret;
}




	
