#include "SN_STATION.h"

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
#include <Windows.h>
#include "MfSetupUtil.h"   


#include <userint.h>
#include <utility.h>   
#include <formatio.h>
 
#include "Download.h"
#include "string.h"
#include "general.h"
#include "context.h"
#include "des.h"

extern kal_bool g_IsEngineer;

  



IniText g_IniSetupFile = 0;

baudrate_struct g_Baudrate_Table [UART_BAUD_110] = {
	"xxxxxx",
	"921600",
	"460800",
	"230400",
	"115200",
	"57600",
};

//------------------------------------------------------------------------------
///////////////////////////    General Setting     ///////////////////////////////////
//------------------------------------------------------------------------------
//==============================================================================
void read_item(kal_uint8* strSetupFile, kal_uint8* strSecName, kal_uint8* strFieldName, ini_item_struct *sIniData)
{
    kal_uint8 strPath [ MAX_PATHNAME_LEN ];
 
	/* set up the pathName for the .ini file */ 
    GetProjectDir( strPath );
	MakePathname ( strPath, strSetupFile, strPath ); 
    

	/* create object for holding the value/tag pairs */ 
	g_IniSetupFile = Ini_New ( FALSE );  /* TRUE for automatic sorting */ 

	/* read in the tag/value pairs */ 
	Ini_ReadFromFile ( g_IniSetupFile, strPath ); 

	if(! Ini_ItemExists ( g_IniSetupFile, strSecName, strFieldName ) ){

		switch( sIniData->eType )
		{
		case INI_BOOLEAN:
			Ini_PutBoolean ( g_IniSetupFile, strSecName, strFieldName, sIniData->uData.bData ); 
			break;

		case INI_INTEGER:
		    Ini_PutInt ( g_IniSetupFile, strSecName, strFieldName, sIniData->uData.mData ); 
			break;

		case INI_STRING:
			Ini_PutString ( g_IniSetupFile, strSecName, strFieldName, sIniData->uData.pData ); 
			break;

		default:
			break;
		}
	}

	switch( sIniData->eType )
	{
		case INI_BOOLEAN:
			Ini_GetBoolean (g_IniSetupFile, strSecName, strFieldName, &(sIniData->uData.bData)	); 
			break;

		case INI_INTEGER:
		    Ini_GetInt (g_IniSetupFile, strSecName, strFieldName, &(sIniData->uData.mData) ); 
			break;

		case INI_STRING:
			Ini_GetStringIntoBuffer (g_IniSetupFile, strSecName, strFieldName, sIniData->uData.pData, MAX_PATHNAME_LEN ); 
			break;

		default:
			break;
	}

	/* dispose of the in-memory tag/value pairs */ 
	Ini_Dispose (g_IniSetupFile);
		
    return ;
}

//---------------------------------------------------------------------------
void write_item(kal_uint8* strSetupFile, kal_uint8* strSecName, kal_uint8* strFieldName, ini_item_struct *sIniData)
{
    kal_uint8 strPath[MAX_PATHNAME_LEN];

	/* set up the pathName for the .ini file */ 
    GetProjectDir(strPath);
	MakePathname (strPath, strSetupFile, strPath); 
    

	/* create object for holding the value/tag pairs */ 
	g_IniSetupFile = Ini_New ( FALSE );  /* TRUE for automatic sorting */ 

	/* read in the tag/value pairs */ 
	Ini_ReadFromFile (g_IniSetupFile, strPath); 


	switch( sIniData->eType )
	{
		case INI_BOOLEAN:
			Ini_PutBoolean (g_IniSetupFile, strSecName, strFieldName, sIniData->uData.bData); 
			break;

		case INI_INTEGER:
		    Ini_PutInt (g_IniSetupFile, strSecName, strFieldName, sIniData->uData.mData); 
			break;

		case INI_STRING:
			Ini_PutString (g_IniSetupFile, strSecName, strFieldName, sIniData->uData.pData); 
			break;

		default:
			break;
	}
    Ini_WriteToFile (g_IniSetupFile, strPath);
	/* dispose of the in-memory tag/value pairs */ 
	Ini_Dispose (g_IniSetupFile);
		
    return ;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

void read_HeadInfo( HeadInfo_struct *ptHeadInfo )
{
	ini_item_struct sIniData;
	
	sIniData.eType = INI_BOOLEAN;   
    
	read_item( SETUP_FILE, "System Setup", "Check Barcode Head", &sIniData);
	ptHeadInfo->bCheckBarcode = sIniData.uData.bData;

	read_item( SETUP_FILE, "System Setup", "Check IMEI_1 Head", &sIniData);
	ptHeadInfo->bCheckIMEI_1 = sIniData.uData.bData;

	read_item( SETUP_FILE, "System Setup", "Check IMEI_2 Head", &sIniData);
	ptHeadInfo->bCheckIMEI_2 = sIniData.uData.bData;

	read_item( SETUP_FILE, "System Setup", "Check IMEI_3 Head", &sIniData);
	ptHeadInfo->bCheckIMEI_3 = sIniData.uData.bData;

	read_item( SETUP_FILE, "System Setup", "Check IMEI_4 Head", &sIniData);
	ptHeadInfo->bCheckIMEI_4 = sIniData.uData.bData;

	read_item( SETUP_FILE, "System Setup", "Check BT Head", &sIniData);
	ptHeadInfo->bCheckBT = sIniData.uData.bData;

	read_item( SETUP_FILE, "System Setup", "Check Wifi Head", &sIniData);
	ptHeadInfo->bCheckWIFI = sIniData.uData.bData;
	
    
	sIniData.eType = INI_STRING;
	sIniData.uData.pData = ptHeadInfo->Barcode;
	read_item( SETUP_FILE, "System Setup", "Barcode HeadString", &sIniData);
		
    sIniData.uData.pData = ptHeadInfo->IMEI_1;
	read_item( SETUP_FILE, "System Setup", "IMEI_1 HeadString", &sIniData);

	sIniData.uData.pData = ptHeadInfo->IMEI_2;
	read_item( SETUP_FILE, "System Setup", "IMEI_2 HeadString", &sIniData);
		
    sIniData.uData.pData = ptHeadInfo->IMEI_3;
	read_item( SETUP_FILE, "System Setup", "IMEI_3 HeadString", &sIniData);

	sIniData.uData.pData = ptHeadInfo->IMEI_4;
	read_item( SETUP_FILE, "System Setup", "IMEI_4 HeadString", &sIniData);

	sIniData.uData.pData = ptHeadInfo->BT;
	read_item( SETUP_FILE, "System Setup", "BT Addr HeadString", &sIniData);

	sIniData.uData.pData = ptHeadInfo->WIFI;
	read_item( SETUP_FILE, "System Setup", "Wifi Addr HeadString", &sIniData);
	
	return;
}

void write_HeadInfo( HeadInfo_struct tHeadInfo )
{
	ini_item_struct sIniData;

	sIniData.eType = INI_BOOLEAN; 
	
	sIniData.uData.bData = tHeadInfo.bCheckBarcode;   	
	write_item( SETUP_FILE, "System Setup", "Check Barcode Head", &sIniData);

	sIniData.uData.bData = tHeadInfo.bCheckIMEI_1;   	
	write_item( SETUP_FILE, "System Setup", "Check IMEI_1 Head", &sIniData);

	sIniData.uData.bData = tHeadInfo.bCheckIMEI_2;   	
	write_item( SETUP_FILE, "System Setup", "Check IMEI_2 Head", &sIniData);

	sIniData.uData.bData = tHeadInfo.bCheckIMEI_3;   	
	write_item( SETUP_FILE, "System Setup", "Check IMEI_3 Head", &sIniData);

	sIniData.uData.bData = tHeadInfo.bCheckIMEI_4;   	
	write_item( SETUP_FILE, "System Setup", "Check IMEI_4 Head", &sIniData);

	sIniData.uData.bData = tHeadInfo.bCheckBT;   	
	write_item( SETUP_FILE, "System Setup", "Check BT Head", &sIniData);

	sIniData.uData.bData = tHeadInfo.bCheckWIFI;   	
	write_item( SETUP_FILE, "System Setup", "Check Wifi Head", &sIniData);

	
	
	sIniData.eType = INI_STRING; 
	
	sIniData.uData.pData = tHeadInfo.Barcode;   
	write_item( SETUP_FILE, "System Setup", "Barcode HeadString", &sIniData);

	sIniData.uData.pData = tHeadInfo.IMEI_1;   
	write_item( SETUP_FILE, "System Setup", "IMEI_1 HeadString", &sIniData);

	sIniData.uData.pData = tHeadInfo.IMEI_2;   
	write_item( SETUP_FILE, "System Setup", "IMEI_2 HeadString", &sIniData);

	sIniData.uData.pData = tHeadInfo.IMEI_3;   
	write_item( SETUP_FILE, "System Setup", "IMEI_3 HeadString", &sIniData);

	sIniData.uData.pData = tHeadInfo.IMEI_4;   
	write_item( SETUP_FILE, "System Setup", "IMEI_4 HeadString", &sIniData);

	sIniData.uData.pData = tHeadInfo.BT;   
	write_item( SETUP_FILE, "System Setup", "BT Addr HeadString", &sIniData);

	sIniData.uData.pData = tHeadInfo.WIFI;   
	write_item( SETUP_FILE, "System Setup", "Wifi Addr HeadString", &sIniData);
    
	return;
}

int read_EngineerPasswd ( kal_char *strPassword )
{
	kal_char key[10]="03055030";
	kal_uint8 strPath[MAX_PATHNAME_LEN] = {0};
	STATUS_DES desStatus;
	kal_uint16 pwdLength = 0;
	kal_char strPasswd_Mode[64] = {0};

	//ini_item_struct sIniData;
	//sIniData.eType = INI_STRING;
	//sIniData.uData.pData = strPassword;
	//read_item( SETUP_FILE, "System Setup", "Engineer Password", &sIniData);
	GetProjectDir( strPath );
	MakePathname ( strPath, "SNDATA", strPath ); 	
	
	desStatus = ReadDataFromFile(strPasswd_Mode, 64, key, strPath);	
	switch(desStatus)
	{
	  case S_DES_SUCCESS:
	  	   pwdLength = strlen(strPasswd_Mode);
	       strncpy(strPassword, (strPasswd_Mode+2), (pwdLength - 2));
	  	   if(strPasswd_Mode[0]== '0' && strPasswd_Mode[1] == '1')
	  	   {
	  	      g_IsEngineer = KAL_TRUE;
	  	   }
		   else if(strPasswd_Mode[0]== '0' && strPasswd_Mode[1] == '0')
		   {
		      g_IsEngineer = KAL_FALSE;
		   }
	   	   break;
		  
	  case S_DES_FAIL:
	  	  MessagePopup("Error", "Can`t encrypt the password!!");
	   	  break;
		  
	  case S_DES_DATALEN_TOO_BIG:
	  	  MessagePopup("Error", "The password length is overflow!!");
	   	  break;
		  
	  case S_DES_KEYLEN_TOO_BIG:
	  	  MessagePopup("Error", "The password deskey is overflow!!");
	   	  break;
		  
	  case S_DES_OPEN_FILE_ERROR:
	  	  MessagePopup("Error", "Open file error!!");
	   	  break;
		  
	  default:
	   	  MessagePopup("Error", "Write File cause unknow error!!");
		  break;
	}
	
	return desStatus;
}

void read_StringValueFromSetupFile(kal_uint8* strSecName, kal_uint8* strFieldName, kal_uint8 * strValue)
{
    ini_item_struct sIniData;
    sIniData.eType = INI_STRING;
    sIniData.uData.pData = strValue;

	read_item( SETUP_FILE, strSecName, strFieldName, &sIniData);
    return;
}

void write_StringValueToSetupFile (kal_uint8* strSecName, kal_uint8* strFieldName,  kal_uint8 *strValue )
{
    ini_item_struct sIniData;
    sIniData.eType = INI_STRING;
    sIniData.uData.pData = strValue;

	write_item( SETUP_FILE, strSecName, strFieldName, &sIniData);
    return;
}


int read_IntValueFromSetupFile( kal_uint8* strSecName, kal_uint8* strFieldName)
{
   ini_item_struct sIniData;
   sIniData.eType = INI_INTEGER;
   sIniData.uData.mData = 0;

   read_item( SETUP_FILE, strSecName, strFieldName, &sIniData);
   return sIniData.uData.mData;
}

void write_IntValueToSetupFile(  kal_uint8* strSecName, kal_uint8* strFieldName, int intValue )
{
   ini_item_struct sIniData;
   sIniData.eType = INI_INTEGER;
   sIniData.uData.mData = intValue;
	
   write_item( SETUP_FILE, strSecName, strFieldName, &sIniData);
   return;
}


kal_bool read_BoolValueFromSetupFile( kal_uint8* strSecName, kal_uint8* strFieldName)
{
    ini_item_struct sIniData;
	sIniData.eType = INI_BOOLEAN;
	sIniData.uData.bData = KAL_FALSE;

	read_item( SETUP_FILE, strSecName, strFieldName, &sIniData);
	return sIniData.uData.bData;
}

void write_BoolValueToSetupFile(  kal_uint8* strSecName, kal_uint8* strFieldName, kal_bool boolValue )
{
    ini_item_struct sIniData;
	sIniData.eType = INI_BOOLEAN;
	sIniData.uData.bData = boolValue;
	
	write_item( SETUP_FILE, strSecName, strFieldName, &sIniData);
	return;
}


int write_EngineerPasswd ( kal_char *strPassword )
{
    kal_char key[10]="03055030";
	kal_char strPath[261];
	STATUS_DES desStatus;
	kal_uint16 pwdLength = 64;
	kal_char strPasswd_Mode[64]= {0};
	
	GetProjectDir( strPath );
	MakePathname ( strPath, "SNDATA", strPath ); 

	
	strncpy(strPasswd_Mode+2, strPassword, strlen(strPassword));
	if(g_IsEngineer)
	{
	   strPasswd_Mode[0] = '0';
	   strPasswd_Mode[1] = '1';
	}
	else
	{
	   strPasswd_Mode[0] = '0';
	   strPasswd_Mode[1] = '0';
	}
	
	desStatus = WriteDataToFile(strPasswd_Mode, pwdLength, key, strPath);
	
	switch(desStatus)
	{
	  case S_DES_SUCCESS:
	   	  break;
		  
	  case S_DDES_FAIL:
	  	  MessagePopup("Error", "Can`t decrypt the password!!");
	   	  break;
		  
	  case S_DES_DATALEN_TOO_BIG:
	  	  MessagePopup("Error", "The password length is overflow!!");
	   	  break;
		  
	  case S_DES_KEYLEN_TOO_BIG:
	  	  MessagePopup("Error", "The password deskey is overflow!!");
	   	  break;
		  
	  case S_DES_OPEN_FILE_ERROR:
	  	  MessagePopup("Error", "Open file error!!");
	   	  break;
		  
	  default:
	   	  MessagePopup("Error", "Write File cause unknow error!!");
	}
	

	return desStatus;
}


void read_SP_WIFI_NVRAM_Path( char path[] )
{	
       ini_item_struct sIniData;
	
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = path;
	
	read_item( SETUP_FILE, "System Setup", "SP WIFI NVRAM Path", &sIniData );
}

UART_BAUDRATE read_BaudRate( void )
{
	ini_item_struct sIniData;
	UART_BAUDRATE i;
	
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = malloc ( sizeof ( ini_item_struct ) );
	
	if ( NULL == sIniData.uData.pData ){
	     MessagePopup ("WARNING", "Allocate memory fail!");
	}
	
	read_item( SETUP_FILE, "System Setup", "Baud Rate", &sIniData );
		
	for ( i = UART_BAUD_921600; i < UART_BAUD_57600; i++ ) {
		
		if( !strcmp( (kal_char*) &g_Baudrate_Table[i], sIniData.uData.pData )){
			break;
		}
	} 

	free ( sIniData.uData.pData );
	sIniData.uData.pData = NULL;

	if ( i>= UART_BAUD_921600 && i<= UART_BAUD_57600 ) {
		return i;
	} else {
		return UART_BAUD_115200;
	}
		
}

void write_BaudRate(UART_BAUDRATE mBaudrate )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = malloc ( sizeof ( ini_item_struct ) );
	
	if ( NULL == sIniData.uData.pData ){
	     MessagePopup ("WARNING", "Allocate memory fail!");
	}

	sIniData.uData.pData = (kal_char*) &g_Baudrate_Table[ mBaudrate ]; 

	write_item( SETUP_FILE, "System Setup", "Baud Rate", &sIniData);
	return;
}

void read_PidFilter ( kal_uint8 *strPath )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = strPath;   
	
	read_item( SETUP_FILE, "System Setup", "Com port filter", &sIniData);

	return ;
}

void read_SpBromPortFilter ( kal_uint8 *strPath )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = strPath;   
	
	read_item( SETUP_FILE, "System Setup", "BROM Port Filter", &sIniData);

	return ;
}
void read_SpPreloaderPortFilter ( kal_uint8 *strPath )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = strPath;   
	
	read_item( SETUP_FILE, "System Setup", "Preloader Port Filter", &sIniData);

	return ;
}

kal_bool read_Is_Composite_Device_Enable( void )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_BOOLEAN;  
	sIniData.uData.bData = KAL_FALSE ; 
	
	read_item( SETUP_FILE, "System Setup", "IS Composite Device Enable", &sIniData);

	return sIniData.uData.bData;
}

void read_Kernel_COMPort_Filter ( kal_uint8 *strPath )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_STRING;  
	sIniData.uData.pData = strPath;   
	
	read_item( SETUP_FILE, "System Setup", "Kernel Port Filter", &sIniData);

	return ;
}

void read_Imei_SvnPad ( IMEISV_struct_T *ptSvnPad )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_INTEGER;
	
	read_item( SETUP_FILE, "System Setup", "IMEI SVN", &sIniData);
	ptSvnPad->svn = sIniData.uData.mData;

	read_item( SETUP_FILE, "System Setup", "IMEI PAD", &sIniData);
	ptSvnPad->pad = sIniData.uData.mData;
	
	return;
}

void write_Imei_SvnPad ( IMEISV_struct_T tSvnPad )
{
	ini_item_struct sIniData;
	
	sIniData.eType = INI_INTEGER; 
	sIniData.uData.mData = tSvnPad.svn;   
	write_item( SETUP_FILE, "System Setup", "IMEI SVN", &sIniData);

	sIniData.eType = INI_INTEGER; 
	sIniData.uData.mData = tSvnPad.pad;   
	write_item( SETUP_FILE, "System Setup", "IMEI PAD", &sIniData);

	return;
}

kal_uint32 read_BackupFlag(void)
{
	ini_item_struct sIniData;
	
	sIniData.eType = INI_INTEGER;  
	sIniData.uData.pData = 0x0;

	read_item( SETUP_FILE, "System Setup", "Backup Second Imei", &sIniData);

	return sIniData.uData.mData;
}

void write_SetCleanBoot_Flag()
{
	ini_item_struct sIniData;
	sIniData.eType = INI_INTEGER;  
//	GetUISetCleanBootFlag(KAL_TRUE, &sIniData.uData.mData);   
	
	write_item( SETUP_FILE, "System Setup", "Backup Second Imei", &sIniData);

	return;
}

kal_uint32 read_spMD_Index(void)
{
    ini_item_struct sIniData;
	sIniData.eType = INI_INTEGER;  
	sIniData.uData.mData = 1;
	
	read_item( SETUP_FILE, "System Setup", "World Phone MD Index", &sIniData);

	return sIniData.uData.mData;
}

kal_uint32 read_spSW_Version(void)
{
    ini_item_struct sIniData;
	sIniData.eType = INI_INTEGER;  
	sIniData.uData.mData = 5;
	
	read_item( SETUP_FILE, "System Setup", "World Phone SW Version", &sIniData);

	return sIniData.uData.mData;
}


kal_uint16 read_Search_Kernel_Port_Time( void )
{
	ini_item_struct sIniData;
	sIniData.eType = INI_INTEGER;  
	sIniData.uData.mData = 5000;   //default 5000ms
	
	read_item( SETUP_FILE, "System Setup", "Search Kernel Port Time", &sIniData);

	return sIniData.uData.mData;
}

