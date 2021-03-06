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
#include "pwctrl.h"

#include <userint.h>
#include <utility.h>   
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>  
//#include <pwctrl.h>



#include "uipara.h"  

#include "SN_STATION.h"
#include "context.h"
#include "MfSetupUtil.h"
#include "USBSwitchDLLibrary.h"
 
#define MAX_COMPORT_COUNT 30       
extern kal_int32 panelHandle_main;
extern kal_int32 panelHandle_imei;
extern kal_int32 menuHandle;
extern kal_int32 panelHandle_DualImei;
extern kal_int32 panelHandle_CodeScan;//add by mtk71596
extern kal_int32 panelHandle_OperateCfg;
extern kal_int32 panelHandle_combine;
extern unsigned short ComPortArray[255];
extern unsigned short ComPortCount;
extern kal_int32 MenuItemID[MAX_COMPORT_COUNT];
SN_Context_struct g_SN;
extern kal_bool DimmdIMEILock;
extern kal_char imei[4][16];
extern kal_char BarCode[64];
extern kal_char BT[13];
extern kal_char WIFI[13];

//******************************************
extern kal_bool    g_IsEngineer;
extern kal_bool    g_bLoginByEngineer;
extern kal_int32   panelHandle_PanelEngin;
extern kal_int32   panelHandle_PanelChgpw;
extern kal_uint16  g_passwordICtrlID;
extern kal_uint16  g_oldpasswordICtrlID;
extern kal_uint16  g_newpasswordICtrlID;
extern kal_uint16  g_confirmpasswordICtrlID;

extern kal_char    g_passwordVal[16 + 1];
extern kal_char    g_oldpasswordVal[16 + 1];
extern kal_char    g_newpasswordVal[16 + 1];
extern kal_char    g_confirmpasswordVal[16 + 1];
extern HeadInfo_struct    g_HeadInfo;
extern OptionSelect_struct *g_pWriteOption;

extern int g_realScanOrderID[MAX_SCANDATA_NUMS];
extern kal_bool g_bScanItem[MAX_SCANDATA_ITEMS];
extern kal_bool g_bCheckHead[MAX_SCANDATA_ITEMS];
extern int g_realScanIDNums;
extern unsigned int us_temp_MDInex;  // add for MT6582 Support
extern unsigned int us_temp_SWInex;  // add for MT6582 Support


//extern CheckOldpwStatus_E g_CheckStatus;




//***************************************************

extern void Sp_ModemDebugOn(void);
extern void Sp_ApDebugOn(void);

extern void ResetDatabaseInitFlag(void);

char sp_wifi_nvram_path[512];
//#define FOUR_IMEI 3

//-------------------------------------------------------------------------------
IMEISV_struct_T GetSVNPAD ( void )
{

  	return g_SN.tIMEI.tImei_Svn_Pad;
}
//-------------------------------------------------------------------------------
kal_bool GetIsImeiCheckSum ( void )
{

  	return g_SN.tIMEI.bCheckSum;
}
//-------------------------------------------------------------------------------
kal_bool GetIsAutoCheckSum ( void )
{

  	return g_SN.tIMEI.bAutoCheckSum;
}
//-------------------------------------------------------------------------------
kal_bool GetIsEnableMetaLog ( void )
{

  	return g_SN.bEnableMetaLog;
}

//-------------------------------------------------------------------------------
kal_bool GetIsCheckFTStatus ( void )
{

  	return g_SN.tIMEI.bCheckFTStatus;
}

//-------------------------------------------------------------------------------
kal_bool GetIsswitchtool ( void )
{

  	return g_SN.bEnableSwitchDataCard;
}


kal_bool GetIsImeiLock ( void )
{

  	return g_SN.tIMEI.bLockIMEI;
}

//-------------------------------------------------------------------------------
kal_bool GetIsDualImei ( void )
{
	if(g_SN.tIMEI.bFourIMEI)
	{
		if(GetTargetType() != TARGET_SMARTPHONE)
			return FOUR_IMEI;
	}
	else if(g_SN.tIMEI.eImeiNum == THREE_IMEI)
	{
		return THREE_IMEI;
	}
	else
	  	return g_SN.tIMEI.bDualIMEI;
}

//-------------------------------------------------------------------------------
kal_bool GetIsSVNPAD_Enable ( void )
{

  	return g_SN.tIMEI.bSVNPAD_Enable;
}

//-------------------------------------------------------------------------------
E_TARGET_TYPE GetTargetType ( void )
{

  	return g_SN.tTargetInfo.eTargetType;
}

//-------------------------------------------------------------------------------
BBCHIP_TYPE GetBBChip ( void )
{

  	return g_SN.tTargetInfo.eBBChip;
}

//-------------------------------------------------------------------------------
UART_BAUDRATE GetBaudRate ( void )
{

  	return g_SN.tCommPort.eBaudRate;
}

//-------------------------------------------------------------------------------
kal_int32 GetPowerOnDelayTime ( void )
{
	g_SN.tTargetInfo.mPowerOnDelayTime = 4000;//4s
   return g_SN.tTargetInfo.mPowerOnDelayTime;

}

//-------------------------------------------------------------------------------
E_COM_NUMBER GetCOMPort ( void )
{

  	return g_SN.tCommPort.eComPort;
}

//-------------------------------------------------------------------------------
kal_bool IsUSBCOMPort ( void )
{

  	 return ( USB_VCOM == g_SN.tCommPort.eComPort )? KAL_TRUE : KAL_FALSE;
}

kal_bool GetIs6276M(void)
{
       return  g_SN.is6276M;
}

kal_bool GetIsCDrom ( void )
{

  	return g_SN.bEnableCDrom;
}

kal_bool GetIsDataCall ( void )
{

  	return g_SN.tCombine.bDataCall;
}

kal_bool GetIsSDS ( void )
{

  	return g_SN.tCombine.SDS;
}




kal_bool GetIsDataprefer( void )
{

  	return g_SN.tCombine.Dataprefer;
}
kal_bool GetIsSetAMR( void )
{

  	return g_SN.tCombine.SetAMR;
}

kal_bool GetIsSet( void )
{

  	return g_SN.tCombine.bset;
}

kal_bool GetIsClear( void )
{

  	return g_SN.tCombine.bclear;
}

kal_bool GetIsAMR( void )
{

  	return g_SN.tCombine.AMR;
}


//-------------------------------------------------------------------------------
kal_uint8* GetModemDatabasePath ( void )
{

    kal_uint8 strPath [ MAX_PATHNAME_LEN ];
 
	/* set up the pathName for the .ini file */ 
    GetProjectDir( strPath );
	MakePathname ( strPath, "BP", strPath ); 

	if (GetTargetType () == Tablet_WIFI_ONLY) 
	{
	    //Default modem database
	    strcpy(g_SN.strPath.strModemDatabasePath, strPath);
	}
	
  	return g_SN.strPath.strModemDatabasePath;
}

kal_uint8* GetModem2DatabasePath ( void )
{
  	return g_SN.strPath.strModemDatabasePath2;
}


//-------------------------------------------------------------------------------
kal_uint8* GetAPDatabasePath ( void )
{

  	return g_SN.strPath.strAPDatabasePath;
}

//-------------------------------------------------------------------------------
kal_uint8* GetAuthFilePath ( void )
{

  	return g_SN.strPath.strAuthFilePath;
}
kal_uint8* SpGetAuthFilePath ( void )
{

  	return g_SN.strPath.strspAuthFilePath;
}
kal_uint8* SpGetSecuFilePath ( void )
{

  	return g_SN.strPath.strspSecureFilePath;
}

//-------------------------------------------------------------------------------
E_OPERATE_MODE GetOperMode ( void )
{

  	return g_SN.tFuncMode.eOperateMode;
}

//-------------------------------------------------------------------------------
E_FUNCTION_TYPE GetFuncMode ( void )
{

  	return g_SN.tFuncMode.eFuncType;
}

//-------------------------------------------------------------------------------
kal_bool GetBTPowerOn ( void )
{

  	return g_SN.tBTSetting.bBTPower;
}

//----------------------------------------------------------------------------
void UpdateLog ( kal_uint8 *pBuf, kal_uint16 iStep )
{
	sprintf ( g_SN.tLogBuffer.pStrLog, pBuf );
	g_SN.tLogBuffer.iProgressStep = iStep;
	UpdateLog_Display ( KAL_TRUE );
}
//----------------------------------------------------------------------------
void UpdateProgress ( void )
{
    kal_uint32 iStep = 0;
	
	GetCtrlVal ( panelHandle_main, panelMain_mProgressBar, &iStep );

	iStep = (iStep+2)%100;
	
	SetCtrlVal ( panelHandle_main, panelMain_mProgressBar, iStep );
	
}


//---------------------------------------------------------------------------
void EnableTimer2 ( kal_bool bEnable )
{
	ResetTimer ( panelHandle_main, panelMain_mTIMER_2 );
	SetCtrlAttribute ( panelHandle_main, panelMain_mTIMER_2, ATTR_ENABLED,  bEnable );
}
//---------------------------------------------------------------------------
void ClearLog ()
{
	ResetTextBox ( panelHandle_main, panelMain_strLog_Display, "");
	SetCtrlVal ( panelHandle_main, panelMain_mProgressBar, 0);
}
//--------------------------------------------------------------------------
void UpdateCount( kal_bool bPass)
{
	kal_uint8 pBuf[64];
	
	g_SN.tLogBuffer.iTotalNum++;

	if ( bPass )
	{
		g_SN.tLogBuffer.iPassNum++;
	}
	else
	{
        	g_SN.tLogBuffer.iFailNum++;
	}

	sprintf ( pBuf, "%d",  g_SN.tLogBuffer.iTotalNum );
	SetCtrlVal ( panelHandle_main, panelMain_mTotal, pBuf );

	sprintf ( pBuf,  "%d",  g_SN.tLogBuffer.iPassNum );
	SetCtrlVal ( panelHandle_main, panelMain_mPass, pBuf );

	sprintf ( pBuf,  "%d",  g_SN.tLogBuffer.iFailNum );
	SetCtrlVal ( panelHandle_main, panelMain_mFail, pBuf );
	
}
//--------------------------------------------------------------------------
void ResetCount ()
{ 
	g_SN.tLogBuffer.iTotalNum = 0;
	g_SN.tLogBuffer.iPassNum= 0;
	g_SN.tLogBuffer.iPassNum = 0;
}

//-------------------------------------------------------------------------------
void GetLogData(Log_struct *pData)
{

  	pData->pStrLog = g_SN.tLogBuffer.pStrLog;

	pData->iProgressStep = g_SN.tLogBuffer.iProgressStep;
}
//-----------------------------------------------------------------------------
void UpdateIndicator ( kal_bool bOK )
{
	kal_uint32 result;

	result = bOK ? VAL_GREEN : VAL_RED;
	
	SetCtrlAttribute ( panelHandle_main, panelMain_ResultIndicator, ATTR_OFF_COLOR, result );

	UpdateCount ( bOK );
}
//---------------------------------------------------------------------------------
void ResetIndicator ( void )
{
	SetCtrlAttribute ( panelHandle_main, panelMain_ResultIndicator, ATTR_OFF_COLOR, VAL_BLACK );
}
//-----------------------------------------------------------
void UpdateLog_Display ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_strLog_Display, g_SN.tLogBuffer.pStrLog );
		SetCtrlVal ( panelHandle_main, panelMain_mProgressBar, g_SN.tLogBuffer.iProgressStep);
		
	
	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_strLog_Display, (kal_int32*) &g_SN.tLogBuffer.pStrLog );
		GetCtrlVal ( panelHandle_main, panelMain_mProgressBar, &g_SN.tLogBuffer.pStrLog );
	
	}
};

//-----------------------------------------------add by mtk71596--------------------------------------
void UpdateIMEI( kal_bool bDir ){
	
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bIMEI, g_SN.tFuncMode.eFuncType.bIMEI );

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bIMEI, (kal_int32*) &g_SN.tFuncMode.eFuncType.bIMEI );
	}
};
void UpdateBarCode( kal_bool bDir ){
	
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bBarCode, g_SN.tFuncMode.eFuncType.bBarCode );

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bBarCode, (kal_int32*) &g_SN.tFuncMode.eFuncType.bBarCode );
	}
};
void UpdateBT( kal_bool bDir ){
	
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bBT, g_SN.tFuncMode.eFuncType.bBT );

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bBT, (kal_int32*) &g_SN.tFuncMode.eFuncType.bBT );
	}
};
void UpdateWIFIMacadr( kal_bool bDir ){
	
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bWIFIMacadr, g_SN.tFuncMode.eFuncType.bWIFIMacadr );

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bWIFIMacadr, (kal_int32*) &g_SN.tFuncMode.eFuncType.bWIFIMacadr );
	}
};
void UpdateWIFIEEPROMCopy( kal_bool bDir ){
	
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bWIFIEEPROMCopy, g_SN.tFuncMode.eFuncType.bWIFIEEPROMCopy );

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bWIFIEEPROMCopy, (kal_int32*) &g_SN.tFuncMode.eFuncType.bWIFIEEPROMCopy );
	}
};

//-----------------------------------------------------------

void UpdateCheckSum ( kal_bool bDir ){
	
	if ( KAL_TRUE == bDir )
	{		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckSum, g_SN.tIMEI.bCheckSum );		
//		SetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, g_SN.tIMEI.bCheckSum );
	} 
	else
	{		
//		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckSum, (kal_int32*) &g_SN.tIMEI.bCheckSum );
	    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckSum, (kal_int32*) &g_SN.tIMEI.bCheckSum);
	    if(g_SN.tIMEI.bCheckSum == KAL_FALSE)
		{
		  g_SN.tIMEI.bAutoCheckSum = KAL_FALSE; 		  
		  SetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, g_SN.tIMEI.bAutoCheckSum );
		}
		else
		{			  
		  g_SN.tIMEI.bAutoCheckSum = KAL_TRUE; 				  
		  SetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, g_SN.tIMEI.bAutoCheckSum );
		}

	}

	
};
//-----------------------------------------------------------
void UpdateDualIMEI ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bDualIMEI, g_SN.tIMEI.bDualIMEI);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bDualIMEI, (kal_int32*) &g_SN.tIMEI.bDualIMEI );
	}
};

void UpdateDualIMEISame ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_DualImeiSame, g_SN.tIMEI.bDualIMEISame);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_DualImeiSame, (kal_int32*) &g_SN.tIMEI.bDualIMEISame );
		if(g_SN.tIMEI.bDualIMEISame)
			{		  
			  SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);  
			  SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			  if(g_HeadInfo.bCheckIMEI_1)
			  	{
			  	  g_HeadInfo.bCheckIMEI_2 = KAL_TRUE;				  
				  SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, g_HeadInfo.bCheckIMEI_2);
			  	}
			  else
			  	{				  	
				  g_HeadInfo.bCheckIMEI_2 = KAL_FALSE; 				
				   SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, g_HeadInfo.bCheckIMEI_2);
			  	}
			}
		else
			{
			
			  SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			  if(g_HeadInfo.bCheckIMEI_2 == KAL_TRUE)
			  	{
			      SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
			  	}
			  else
			  	{
			  	  
			      SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);
			  	}
			}
	}
};

void UpdateThreeIMEI ( kal_bool bDir )
{
    if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, g_SN.tIMEI.bThreeIMEI);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, (kal_int32*) &g_SN.tIMEI.bThreeIMEI );
	}
}

void UpdateFourIMEI ( kal_bool bDir )
{
    if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bFourIMEI, g_SN.tIMEI.bFourIMEI);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bFourIMEI, (kal_int32*) &g_SN.tIMEI.bFourIMEI );
	}
}


//-----------------------------------------------------------

void disableUSBSwitch(void)
{
	 if(hprocess)
	 {
	   DisableUSBSwitch(hprocess);
	   hprocess = 0;
	 }
}

 void * enableUSBSwitch(void)
{
    void *handle = 0;
   
       if(hprocess == 0)
       {
        handle = EnableUSBSwitch("-m");
        if(handle)
        {
            hprocess = handle;
        }
    }
    return handle;
}

/*
void UpdateCDrom ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_BINARYSWITCH, g_SN.bEnableCDrom);

	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_BINARYSWITCH, (kal_int32*) &g_SN.bEnableCDrom );
		
	}
};

*/

void UpdateDataCall ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_data_call, g_SN.tCombine.bDataCall);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_data_call, (kal_int32*) &g_SN.tCombine.bDataCall );
	}
};

void UpdateAMR( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_AMR, g_SN.tCombine.AMR);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_AMR, (kal_int32*) &g_SN.tCombine.AMR);
	}
};

void UpdateSDS( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_SDS, g_SN.tCombine.SDS);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_SDS, (kal_int32*) &g_SN.tCombine.SDS);
	}
};



void UpdateSet ( kal_bool bDir ){
	 /*
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_set, g_SN.tCombine.bset);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_set, (kal_int32*) &g_SN.tCombine.bset);
	}
	*/
};

void UpdateClear ( kal_bool bDir ){
	/*
	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_clear, g_SN.tCombine.bclear);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_clear, (kal_int32*) &g_SN.tCombine.bclear);
	} */
};

void UpdateDataprefer ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_Data_prefer, g_SN.tCombine.Dataprefer);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_Data_prefer, (kal_int32*) &g_SN.tCombine.Dataprefer);
	}
};

void UpdateCallprefer ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_Call_prefer, g_SN.tCombine.Callprefer);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_Call_prefer, (kal_int32*) &g_SN.tCombine.Callprefer);
	}
};

void UpdateSetAMR( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_SetAMR, g_SN.tCombine.SetAMR);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_SetAMR, (kal_int32*) &g_SN.tCombine.SetAMR);
	}
};


void UpdateClearAMR( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_combine, Combine_ClearAMR, g_SN.tCombine.ClearAMR);

	} else{
		
		GetCtrlVal ( panelHandle_combine, Combine_ClearAMR, (kal_int32*) &g_SN.tCombine.ClearAMR);
	}
};


/*
//-----------------------------------------------------------
void UpdatePowerONDelayTime ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_mPowerON_Delay_Time, g_SN.tTargetInfo.mPowerOnDelayTime);

	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_mPowerON_Delay_Time, (kal_int32*) &g_SN.tTargetInfo.mPowerOnDelayTime );
	}
};
*/
//-----------------------------------------------------------
void UpdateCOMPort ( kal_bool bDir ){

	int i = 0, ItemIndex = -1;   
	if ( KAL_TRUE == bDir ){
	
		SetCtrlVal ( panelHandle_main, panelMain_eCOMPort, g_SN.tCommPort.eComPort );
		
	} else{
		GetCtrlVal ( panelHandle_main, panelMain_eCOMPort, (kal_int32*) &g_SN.tCommPort.eComPort );
		GetCtrlIndex ( panelHandle_main, panelMain_eCOMPort, &ItemIndex);
		for(; i <= ComPortCount; i++)
		{
			if(i != ItemIndex)
			{
				SetMenuBarAttribute( menuHandle, MenuItemID[i], ATTR_CHECKED, KAL_FALSE);
			}else
			{
				SetMenuBarAttribute( menuHandle, MenuItemID[i], ATTR_CHECKED, KAL_TRUE);
			}
		}
	}
};

//-----------------------------------------------------------
/*
void UpdateBaudRate ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_eBaud_Rate, g_SN.tCommPort.eBaudRate);

	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_eBaud_Rate, (kal_int32*) &g_SN.tCommPort.eBaudRate );
	}
};

*/
//-----------------------------------------------------------
void UpdateTargetType ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_eTargetSelect, g_SN.tTargetInfo.eTargetType );

	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_eTargetSelect, (kal_int32*) &g_SN.tTargetInfo.eTargetType );
	}
};

//-----------------------------------------------------------
/*
void UpdateModeType ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_eMode, g_SN.tFuncMode.eOperateMode);

	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_eMode, (kal_int32*) &g_SN.tFuncMode.eOperateMode );
	}
};
*/
//-----------------------------------------------------------
void UpdateModemDatabasePath ( kal_bool bDir ){

	if ( KAL_TRUE == bDir )
	{		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strModem_Database, g_SN.strPath.strModemDatabasePath );
	} else
	{		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strModem_Database, g_SN.strPath.strModemDatabasePath );
	}
};

void UpdateModemDatabasePath_2 ( kal_bool bDir ){

	if ( KAL_TRUE == bDir )
	{		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strModem_Database_2, g_SN.strPath.strModemDatabasePath2 );
	} else
	{		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strModem_Database_2, g_SN.strPath.strModemDatabasePath2 );
	}
};

//-----------------------------------------------------------
void UpdateAPDatabasePath ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strAP_Database, g_SN.strPath.strAPDatabasePath );

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strAP_Database, g_SN.strPath.strAPDatabasePath );
	}
};

//-----------------------------------------------------------
/*
void UpdateAuthFilePath ( kal_bool bDir ){

	if ( KAL_TRUE == bDir ){
		
		SetCtrlVal ( panelHandle_main, panelMain_strAuthen_File, g_SN.strPath.strAuthFilePath );

	} else{
		
		GetCtrlVal ( panelHandle_main, panelMain_strAuthen_File, g_SN.strPath.strAuthFilePath );
	}
};
*/
//-------------------------------------------------------------------------------
void UpdateMetaLog ( kal_bool bDir )
{

	if ( KAL_TRUE == bDir )
	{
		SetMenuBarAttribute ( menuHandle, menuMain_Option_LogOption_Enable, ATTR_CHECKED,  g_SN.bEnableMetaLog );
	}
	else
	{
		GetMenuBarAttribute ( menuHandle, menuMain_Option_LogOption_Enable, ATTR_CHECKED, (kal_uint32*) &g_SN.bEnableMetaLog );
		g_SN.bEnableMetaLog = !g_SN.bEnableMetaLog;
	}	
}

//-------------------------------------------------------------------------------
void UpdateMenuBBChip ( kal_bool bDir )
{
	kal_bool bBBChecked;

	if ( KAL_TRUE == bDir )
	{
		bBBChecked = ( g_SN.tTargetInfo.eBBChip == 254 ) ? KAL_TRUE : KAL_FALSE;
		SetMenuBarAttribute ( menuHandle, menuMain_Option_BB_AutoDetect, ATTR_CHECKED,  bBBChecked );
		
	} 
	else
	{

		GetMenuBarAttribute ( menuHandle, menuMain_Option_BB_AutoDetect, ATTR_CHECKED, (kal_uint32*) &bBBChecked );
		if ( bBBChecked )
		{
				g_SN.tCommPort.eComPort = 254 ;
		}
	}	
}
//-------------------------------------------------------------------------------
void UpdateMenuCom ( kal_bool bDir, int menuItem )
{
	kal_bool bComChecked;
	kal_uint32 i;
	
	if ( KAL_TRUE == bDir )
	{
		/*for ( i = menuMain_Option_COMM_COM1; i <= menuMain_Option_COMM_USBVCOM; i++ )
		{
			bComChecked = ( g_SN.tCommPort.eComPort == i - menuMain_Option_COMM_COM1 + 1 ) ? KAL_TRUE : KAL_FALSE;
			SetMenuBarAttribute ( menuHandle, i, ATTR_CHECKED,  bComChecked );
		}*/
		//GetCtrlIndex(panelHandle_main,panelMain_eCOMPort,&i);
		//SetMenuBarAttribute ( menuHandle, i, ATTR_CHECKED,  bComChecked );
	} 
	else
	{
		//g_SN.tCommPort.eComPort = menuItem- menuMain_Option_COMM_COM1 + 1;
	}	
}
//-------------------------------------------------------------------------------
void UpdateMenuBaudRate ( kal_bool bDir, int menuItem )
{
	kal_bool bBaudRateChecked;
	kal_uint32 i;

	if ( KAL_TRUE == bDir )
	{
		for ( i = menuMain_Option_Baud_Baud961200; i <= menuMain_Option_Baud_Baud57600; i++ )
		{
			bBaudRateChecked = ( g_SN.tCommPort.eBaudRate == i - menuMain_Option_Baud_Baud961200 + 1 ) ? KAL_TRUE : KAL_FALSE;
			SetMenuBarAttribute ( menuHandle, i, ATTR_CHECKED,  bBaudRateChecked );
		}
	} 
	else
	{
		g_SN.tCommPort.eBaudRate = menuItem- menuMain_Option_Baud_Baud961200 + 1;
	}	
	
}

//-------------------------------------------------------------------------------
void UpdateMenuTarget ( kal_bool bDir, int menuItem ) 
{
	kal_bool bTargetChecked;
	kal_uint32 i;
	
	if ( KAL_TRUE == bDir )
	{
		for ( i = menuMain_Option_Target_Phone; i <= menuMain_Option_Target_RndisDong; i++ )
		{
			bTargetChecked = ( g_SN.tTargetInfo.eTargetType == i - menuMain_Option_Target_Phone ) ? KAL_TRUE : KAL_FALSE;
			SetMenuBarAttribute ( menuHandle, i, ATTR_CHECKED,  bTargetChecked );
		}
		
	} 
	else
	{
		g_SN.tTargetInfo.eTargetType = menuItem - menuMain_Option_Target_Phone;
	}	
}
//-------------------------------------------------------------------------------
void UpdateMenuMode ( kal_bool bDir, int menuItem ) 
{
	kal_bool bModeChecked;
	kal_uint32 i;
	
	if ( KAL_TRUE == bDir )
	{
		for ( i = menuMain_Option_OperMode_Meta; i <= menuMain_Option_OperMode_AT; i++ )
		{
			bModeChecked = ( g_SN.tFuncMode.eOperateMode == i - menuMain_Option_OperMode_Meta ) ? KAL_TRUE : KAL_FALSE;
			SetMenuBarAttribute ( menuHandle, i, ATTR_CHECKED,  bModeChecked );
		}
		
	}
	else
	{

		g_SN.tFuncMode.eOperateMode = menuItem - menuMain_Option_OperMode_Meta;
		
	}	
}

//-------------------------------------------------------------------------------


void UpdateMenuBTPowerOn ( kal_bool bDir, int menuItem )
{
	if ( KAL_TRUE == bDir )
	{
		SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_BTPower_On, ATTR_CHECKED, g_SN.tBTSetting.bBTPower);
		SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_BTPower_Off, ATTR_CHECKED, !g_SN.tBTSetting.bBTPower );

	}
	else
	{
		g_SN.tBTSetting.bBTPower = ( menuItem == menuMain_BTIMEI_BTPower_On ) ? KAL_TRUE : KAL_FALSE;
		
	}
}

//-------------------------------------------------------------------------------
void UpdateMenuBTChip ( kal_bool bDir, int menuItem )
{
	kal_bool b_Checked;
	int i;
	
	if ( KAL_TRUE == bDir )
	{
		for ( i = menuMain_BTIMEI_Chip_MT6601; i <= menuMain_BTIMEI_Chip_RFMD3500; i++ )
		{
			b_Checked = ( g_SN.tBTSetting.eBTChip == i - menuMain_BTIMEI_Chip_MT6601 ) ? KAL_TRUE : KAL_FALSE;
			SetMenuBarAttribute ( menuHandle, i, ATTR_CHECKED,  b_Checked );
		}
	} 
	else
	{
		g_SN.tBTSetting.eBTChip = menuItem- menuMain_BTIMEI_Chip_MT6601;
	}	
}

//----------------------------------------------------------------------------

//-------------------add by mtk71596--------------------------------------------

void UpdateMenuIMEI( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
		{
			SetMenuBarAttribute ( menuHandle, menuMain_Option_Func_IMEI, ATTR_CHECKED, g_SN.tFuncMode.eFuncType.bIMEI);
	
		} else{
			
			GetMenuBarAttribute ( menuHandle, menuMain_Option_Func_IMEI, ATTR_CHECKED, (kal_uint32*)&g_SN.tFuncMode.eFuncType.bIMEI );
			g_SN.tFuncMode.eFuncType.bIMEI = !g_SN.tFuncMode.eFuncType.bIMEI;
		}
}

void UpdateMenuBarCode( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
		{
			SetMenuBarAttribute ( menuHandle, menuMain_Option_Func_Barcode, ATTR_CHECKED, g_SN.tFuncMode.eFuncType.bBarCode );
	
		} else{
			
			GetMenuBarAttribute ( menuHandle, menuMain_Option_Func_Barcode, ATTR_CHECKED, (kal_uint32*)&g_SN.tFuncMode.eFuncType.bBarCode );
			g_SN.tFuncMode.eFuncType.bBarCode  = !g_SN.tFuncMode.eFuncType.bBarCode ;
		}
}
void UpdateMenuBT( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
		{
			SetMenuBarAttribute ( menuHandle, menuMain_Option_Func_BTAddr, ATTR_CHECKED, g_SN.tFuncMode.eFuncType.bBT);
	
		} else{
			
			GetMenuBarAttribute ( menuHandle, menuMain_Option_Func_BTAddr, ATTR_CHECKED, (kal_uint32*)&g_SN.tFuncMode.eFuncType.bBT );
			g_SN.tFuncMode.eFuncType.bBT = !g_SN.tFuncMode.eFuncType.bBT;
		}
}
void UpdateMenuWIFI( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
		{
			SetMenuBarAttribute ( menuHandle, menuMain_Option_Func_WIFIMac, ATTR_CHECKED, g_SN.tFuncMode.eFuncType.bWIFIMacadr );
	
		} else{
			
			GetMenuBarAttribute ( menuHandle, menuMain_Option_Func_WIFIMac, ATTR_CHECKED, (kal_uint32*)&g_SN.tFuncMode.eFuncType.bWIFIMacadr  );
			g_SN.tFuncMode.eFuncType.bWIFIMacadr  = !g_SN.tFuncMode.eFuncType.bWIFIMacadr ;
		}
}

void UpdateMenuHDCP( kal_bool bDir)
{
	if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY_HDCP, ATTR_CHECKED, g_SN.tFuncMode.eFuncType.bHDCP);
    }
	else
	{
	   GetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY_HDCP, ATTR_CHECKED, (kal_uint32*)&g_SN.tFuncMode.eFuncType.bHDCP);
	   g_SN.tFuncMode.eFuncType.bHDCP =!g_SN.tFuncMode.eFuncType.bHDCP;
	}
	
}
void UpdateMenuDRM_Key_Install( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
		{
			SetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY_DRMKeyInstal, ATTR_CHECKED, g_SN.tFuncMode.eFuncType.bDRMKeyInstall);
	
		} else{
			
			GetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY_DRMKeyInstal, ATTR_CHECKED, (kal_uint32*)&g_SN.tFuncMode.eFuncType.bDRMKeyInstall);
			g_SN.tFuncMode.eFuncType.bDRMKeyInstall = !g_SN.tFuncMode.eFuncType.bDRMKeyInstall;
		}
}

//-------------------------------------------------------------------------------
void UpdateMenuIMEICheckSum ( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
	{
		SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_CheckSum, ATTR_CHECKED, g_SN.tIMEI.bCheckSum );

	} 
	else
	{
		
		GetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_CheckSum, ATTR_CHECKED, (kal_uint32*)&g_SN.tIMEI.bCheckSum );
		g_SN.tIMEI.bCheckSum = !g_SN.tIMEI.bCheckSum;
		if(g_SN.tIMEI.bCheckSum)
		{
		  	g_SN.tIMEI.bAutoCheckSum = KAL_TRUE; 		  
	        SetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, g_SN.tIMEI.bAutoCheckSum );
		}
		else
		{
			g_SN.tIMEI.bAutoCheckSum = KAL_FALSE; 		  
	        SetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, g_SN.tIMEI.bAutoCheckSum );
		}
	}
}

//mtk71409
void UpdateMenuEnMetaWithoutBattery ( kal_bool bDir )
{
	if ( KAL_TRUE == bDir )
	{
		SetMenuBarAttribute ( menuHandle, menuMain_Option_FpOption_MetaNoB, ATTR_CHECKED, g_SN.isEntryMetaWithoutBattery);

	} else{
		
		GetMenuBarAttribute ( menuHandle, menuMain_Option_FpOption_MetaNoB, ATTR_CHECKED, (kal_uint32*)&g_SN.isEntryMetaWithoutBattery);
		g_SN.isEntryMetaWithoutBattery= !g_SN.isEntryMetaWithoutBattery;
	}
}

//mtk71518  2013-0702

void UpdateMenuEnDatacard(kal_bool bDir)
{
    if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_Option_Datacard, ATTR_CHECKED, g_SN.bEnableSwitchDataCard);
	   if(g_SN.bEnableSwitchDataCard == KAL_TRUE)
	   {
	      g_SN.isEntryDualTalk = KAL_FALSE;
	      SetMenuBarAttribute ( menuHandle, menuMain_Option_DualTalk, ATTR_CHECKED, KAL_FALSE);
		  SetMenuBarAttribute ( menuHandle, menuMain_Option_DualTalk, ATTR_DIMMED, KAL_TRUE);
	   }
	   else
	   {
	      SetMenuBarAttribute ( menuHandle, menuMain_Option_DualTalk, ATTR_DIMMED, KAL_FALSE);
	   }
    }
	else
	{
       GetMenuBarAttribute ( menuHandle, menuMain_Option_Datacard, ATTR_CHECKED, (kal_uint32*)&g_SN.bEnableSwitchDataCard);
	   g_SN.bEnableSwitchDataCard = !g_SN.bEnableSwitchDataCard;
	
	  
	}
}

void UpdateMenuSecurreUSB(kal_bool bDir)
{
    if ( KAL_TRUE == bDir )
	{
		SetMenuBarAttribute ( menuHandle, menuMain_Option_SPSecurreUSB, ATTR_CHECKED, g_SN.SpSecurreUSB);

	} else{
		
		GetMenuBarAttribute ( menuHandle, menuMain_Option_SPSecurreUSB, ATTR_CHECKED, (kal_uint32*)&g_SN.SpSecurreUSB);
		g_SN.SpSecurreUSB = !g_SN.SpSecurreUSB;
	}
}

void UpdateMenuEnDualTalk(kal_bool bDir)
{
    if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_Option_DualTalk, ATTR_CHECKED, g_SN.isEntryDualTalk);
	   if(g_SN.isEntryDualTalk == KAL_TRUE)
	  {
	     g_SN.bEnableSwitchDataCard = KAL_FALSE;
		 SetMenuBarAttribute ( menuHandle, menuMain_Option_Datacard, ATTR_CHECKED, KAL_FALSE);
	     SetMenuBarAttribute ( menuHandle, menuMain_Option_Datacard, ATTR_DIMMED, KAL_TRUE);
	  }
	  else
	  {
	     SetMenuBarAttribute ( menuHandle, menuMain_Option_Datacard, ATTR_DIMMED, KAL_FALSE);
	  }
    }
	else
	{
	   GetMenuBarAttribute ( menuHandle, menuMain_Option_DualTalk, ATTR_CHECKED, (kal_uint32*)&g_SN.isEntryDualTalk);
	   g_SN.isEntryDualTalk= !g_SN.isEntryDualTalk;
	
	  
	}
	
	

}
	
//add by mtk71262
 void UpdateMenuSDS(kal_bool bDir)
{		
    if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_Option_FpOption_SDS, ATTR_CHECKED, g_SN.isEntrySDS);
    }
	else
	{
	   GetMenuBarAttribute ( menuHandle, menuMain_Option_FpOption_SDS, ATTR_CHECKED, (kal_uint32*)&g_SN.isEntrySDS);
	   g_SN.isEntrySDS= !g_SN.isEntrySDS;
	}	
}   


//-------------------------------------------------------------------------------
void UpdateMenuIMEILock ( kal_bool bDir )
{
    if(bDir == KAL_TRUE)
    {
        SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_LockIMEI, ATTR_CHECKED, g_SN.tIMEI.bLockIMEI );
    }
	else
	{
	    GetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_LockIMEI, ATTR_CHECKED, (kal_uint32*)&g_SN.tIMEI.bLockIMEI );
	    g_SN.tIMEI.bLockIMEI = !g_SN.tIMEI.bLockIMEI;
	}
	
	
}
//-------------------------------------------------------------------------------
void UpdateMenuDualIMEI ( kal_bool bDir )
{		
    if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_DualIMEI, ATTR_CHECKED, g_SN.tIMEI.bDualIMEI);
	   if(g_SN.tIMEI.bDualIMEI == KAL_TRUE)
	  {
	     g_SN.tIMEI.eImeiNum = DUAL_IMEI;
	     g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
	     g_SN.tIMEI.bFourIMEI = KAL_FALSE;
		 SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_ThreeIMEI, ATTR_CHECKED, KAL_FALSE);
		 SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_FourIMEI, ATTR_CHECKED, KAL_FALSE);
	  }
    }
	else
	{
	   GetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_DualIMEI, ATTR_CHECKED, (kal_uint32*)&g_SN.tIMEI.bDualIMEI );
	   g_SN.tIMEI.bDualIMEI =!g_SN.tIMEI.bDualIMEI ;
	  
	}
	
}
void UpdateMenuThreeIMEI ( kal_bool bDir )
{
	if(bDir == KAL_TRUE)
	{
		  SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_ThreeIMEI, ATTR_CHECKED, g_SN.tIMEI.bThreeIMEI);
		  if(g_SN.tIMEI.bThreeIMEI == KAL_TRUE)
	      {
	         g_SN.tIMEI.eImeiNum = THREE_IMEI;
	         g_SN.tIMEI.bDualIMEI = KAL_FALSE;
		     g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
	         g_SN.tIMEI.bFourIMEI = KAL_FALSE;
		     SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_DualIMEI, ATTR_CHECKED, KAL_FALSE);
		     SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_FourIMEI, ATTR_CHECKED, KAL_FALSE);
	      }
	}
	else
	{
		  GetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_ThreeIMEI, ATTR_CHECKED, (kal_uint32*)&g_SN.tIMEI.bThreeIMEI );
		  g_SN.tIMEI.bThreeIMEI =!g_SN.tIMEI.bThreeIMEI ;
		  
	}		
}

void UpdateMenuFourIMEI ( kal_bool bDir )
{
   if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_FourIMEI, ATTR_CHECKED, g_SN.tIMEI.bFourIMEI);
	   if(g_SN.tIMEI.bFourIMEI == KAL_TRUE)
	   {
	      g_SN.tIMEI.eImeiNum = FOUR_IMEI;
	      g_SN.tIMEI.bDualIMEI = KAL_FALSE;
		  g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
	      g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
		  SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_DualIMEI, ATTR_CHECKED, KAL_FALSE);
		  SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_ThreeIMEI, ATTR_CHECKED, KAL_FALSE);
	   }
    }
	else
	{
	   GetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_FourIMEI, ATTR_CHECKED, (kal_uint32*)&g_SN.tIMEI.bFourIMEI );
	   g_SN.tIMEI.bFourIMEI =!g_SN.tIMEI.bFourIMEI ;
	   
	}
	
}

//-------------------------------------------------------------------------------
void UpdateMenuFTStatusCheck( kal_bool bDir )
{	
    if(bDir == KAL_TRUE)
    {
       SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_FTStatus, ATTR_CHECKED, g_SN.tIMEI.bCheckFTStatus );
    }
	else
	{
	   GetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_FTStatus, ATTR_CHECKED, (kal_uint32*)&g_SN.tIMEI.bCheckFTStatus );
	  g_SN.tIMEI.bCheckFTStatus = !g_SN.tIMEI.bCheckFTStatus;
	}
	
}

void swap_c ( kal_uint8* x, kal_uint8* y )
{
	kal_uint8 z;
	z = *x;
	*x = *y;
	*y = z;

}
//-----------------------------------------------------------
void UpdateImeiSvnPad ( kal_bool bDir ){

	kal_uint8 strPad [4], strSvn [4];
	kal_uint32 tmp;

	if ( KAL_TRUE == bDir )
	{
		Fmt ( strSvn, "%s<%x", g_SN.tIMEI.tImei_Svn_Pad.svn ); 
		Fmt ( strPad, "%s<%x", g_SN.tIMEI.tImei_Svn_Pad.pad ); 
		if ( g_SN.tIMEI.tImei_Svn_Pad.svn < 10)
		{  strSvn[1] = strSvn[0]; strSvn[0] = '0';strSvn[2] = '\0';}
			  
		swap_c ( &strSvn[0], &strSvn[1] );  
		
		SetCtrlVal ( panelHandle_imei, panelIMEI_IMEISVN, strSvn);
		SetCtrlVal ( panelHandle_imei, panelIMEI_IMEIPAD, strPad );
		
		SetCtrlVal ( panelHandle_imei, panelIMEI_SvnPadEnable_2, g_SN.tIMEI.bSVNPAD_Enable );
		SetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, g_SN.tIMEI.bAutoCheckSum );

	} else{
	
		GetCtrlVal ( panelHandle_imei, panelIMEI_IMEISVN, strSvn );
		GetCtrlVal ( panelHandle_imei, panelIMEI_IMEIPAD, strPad );
		GetCtrlVal ( panelHandle_imei, panelIMEI_SvnPadEnable_2, (kal_int32*)&g_SN.tIMEI.bSVNPAD_Enable );
		GetCtrlVal ( panelHandle_imei, panelIMEI_AutoCheckSum, (kal_int32*)&g_SN.tIMEI.bAutoCheckSum );
		if(g_SN.tIMEI.bAutoCheckSum)
		{	
		    g_SN.tIMEI.bCheckSum = KAL_TRUE;
		    SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckSum, g_SN.tIMEI.bCheckSum );			
			SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_CheckSum, ATTR_CHECKED, g_SN.tIMEI.bCheckSum );
		}
		else
		{
		    g_SN.tIMEI.bCheckSum = KAL_FALSE;
		    SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckSum, g_SN.tIMEI.bCheckSum );		
			SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI_CheckSum, ATTR_CHECKED, g_SN.tIMEI.bCheckSum );
		}

		swap_c ( &strSvn[0], &strSvn[1] );
		
		Scan ( strSvn, "%s>%2x", (kal_uint32*) &tmp );
		g_SN.tIMEI.tImei_Svn_Pad.svn = tmp;
			
		Scan ( strPad, "%s>%x", (kal_uint32*) &tmp );
		g_SN.tIMEI.tImei_Svn_Pad.pad = tmp;
	}
};

//------------------------------------------------------

/*
void UpdateUIMACHead(void){
	SetCtrlAttribute ( panelHandle_main, panelMain_sMACHeader, ATTR_MAX_ENTRY_LENGTH, 12 );
	SetCtrlAttribute ( panelHandle_main, panelMain_sMACHeader, ATTR_CTRL_VAL, "" );
}
*/
//-------------------------add by mtk71596---------------------------------------
kal_uint32 IsIMEIChecked(void)
{
	kal_uint32 bIMEISelected = KAL_FALSE;
	GetCtrlAttribute (panelHandle_OperateCfg, panelCfg_bIMEI,ATTR_CTRL_VAL,&bIMEISelected);
	return bIMEISelected;
}
kal_uint32 IsBarCodeChecked(void)
{
	kal_uint32 bBarCodeSelected = KAL_FALSE;
	GetCtrlAttribute (panelHandle_OperateCfg, panelCfg_bBarCode,ATTR_CTRL_VAL,&bBarCodeSelected);
	return bBarCodeSelected;
}
kal_uint32 IsBTChecked(void)
{
	kal_uint32 bBTSelected = KAL_FALSE;
	GetCtrlAttribute (panelHandle_OperateCfg, panelCfg_bBT,ATTR_CTRL_VAL,&bBTSelected);
	return bBTSelected;
}
kal_uint32 IsWIFIChecked(void)
{
	kal_uint32 bWIFISelected = KAL_FALSE;
	GetCtrlAttribute (panelHandle_OperateCfg, panelCfg_bWIFIMacadr,ATTR_CTRL_VAL,&bWIFISelected);
	return bWIFISelected;
}
void GetUILegacyUSBautodetection(kal_bool flag, kal_uint32* checked)
{
	//int* check = checked;
	if(flag == KAL_TRUE)
		GetCtrlVal(panelHandle_main, menuMain_Option_SPSecurreUSB, checked);
	else
		SetCtrlVal(panelHandle_main, menuMain_Option_SPSecurreUSB, *checked);
}


//add by mtk71596--------------------------------------------------------------
/*
void GetCodeScan(kal_bool Flag)
{
	if(Flag) // true means get result
	{   
	    if(g_pWriteOption->bWriteIMEI)
	    {
	      GetCtrlVal( panelHandle_CodeScan, PANEL_FirstIMEI, imei[0]);
		   if(g_SN.tIMEI.bDualIMEI == KAL_TRUE)
			{
			  GetCtrlVal( panelHandle_CodeScan, PANEL_SecondIMEI, imei[1]);
			}
	    }
		if(g_pWriteOption->bWriteBarcode)
		{
		  GetCtrlVal( panelHandle_CodeScan, PANEL_IDBarCode, BarCode);
		}
		if(g_pWriteOption->bWriteBT)
		{
		  GetCtrlVal( panelHandle_CodeScan, PANEL_IDBT, BT);
		}
		if(g_pWriteOption->bWriteWIFI)
		{
		  GetCtrlVal( panelHandle_CodeScan, PANEL_IDWIFI, WIFI);
		}
		
	}
	else // else means set result
	{
	  if(IsIMEIChecked())
		{
			if(strlen(imei[0]) != 15)
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_FirstIMEI, "");
			}
			else
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_FirstIMEI, imei[0]);
			}
			if(g_SN.tIMEI.bDualIMEI == KAL_TRUE)
			{
			    if(g_SN.tIMEI.bDualIMEISame)
			    	{
			    	  if(strcmp(imei[0],imei[1]))
			    	  	{
					       SetCtrlVal(panelHandle_CodeScan, PANEL_SecondIMEI, "");
			    	  	}
					  else
					  	{
					  	
						SetCtrlVal(panelHandle_CodeScan, PANEL_SecondIMEI, imei[1]);
					  	}
					}
				else
				{
				  	if(strlen(imei[1]) != 15)
					{
						SetCtrlVal(panelHandle_CodeScan, PANEL_SecondIMEI, "");
					}
					else
					{
						SetCtrlVal(panelHandle_CodeScan, PANEL_SecondIMEI, imei[1]);
					} 
				}
			}	
	  	}
	  if(IsBarCodeChecked())
	  	{
	  	  if((strlen(BarCode) == 0) || (strlen(BarCode) > 63))
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_IDBarCode, "");
			}
			else
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_IDBarCode, BarCode);
			}
	  	}
	 if(IsBTChecked())
	  	{
	  	  if(strlen(BT) != 12)
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_IDBT, "");
			}
			else
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_IDBT, BT);
			}
	  	}
	  if(IsWIFIChecked())
	  	{
	  	  if(strlen(WIFI) != 12)
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_IDWIFI, "");
			}
			else
			{
				SetCtrlVal(panelHandle_CodeScan, PANEL_IDWIFI, WIFI);
			}
	  	}
	}
}
*/
//---------------------------------------------------------------------------



void ContextInit (void){

	g_SN.strPath.strAPDatabasePath = (kal_uint8*) malloc ( MAX_PATHNAME_LEN  );
	g_SN.strPath.strModemDatabasePath = (kal_uint8*)  malloc ( MAX_PATHNAME_LEN  );
	g_SN.strPath.strModemDatabasePath2 = (kal_uint8*)  malloc ( MAX_PATHNAME_LEN  );
	g_SN.strPath.strAuthFilePath = (kal_uint8*) malloc ( MAX_PATHNAME_LEN );
	g_SN.strPath.strspAuthFilePath = (kal_uint8*) malloc ( MAX_PATHNAME_LEN );
    g_SN.strPath.strspSecureFilePath = (kal_uint8*) malloc ( MAX_PATHNAME_LEN );
	g_SN.strPath.strHDCPKeyPath = (kal_uint8*) malloc ( MAX_PATHNAME_LEN );
    g_SN.strPath.strDRMKeyPath = (kal_uint8*) malloc ( MAX_PATHNAME_LEN );
	g_SN.tLogBuffer.pStrLog = (kal_uint8*) malloc ( MAX_LOG_LEN );

	memset(&g_HeadInfo, 0, sizeof(g_HeadInfo));
	memset(g_pWriteOption, 0, sizeof(g_pWriteOption));
	

	if ( NULL == g_SN.strPath.strAPDatabasePath || 
		 NULL == g_SN.strPath.strModemDatabasePath ||
		 NULL == g_SN.strPath.strModemDatabasePath2 ||
	 	 NULL == g_SN.strPath.strAuthFilePath||
	 	 NULL ==g_SN.strPath.strspSecureFilePath||
	 	 NULL ==g_SN.strPath.strspAuthFilePath ||
	 	 NULL ==g_SN.strPath.strHDCPKeyPath ||
	 	 NULL == g_SN.strPath.strDRMKeyPath ||
	 	 NULL == g_SN.tLogBuffer.pStrLog)
	{	 
	     MessagePopup ("WARNING", "Allocate memory fail!");
	}
     
}

//------------------------------------------------------
void ContextDeInit (void){

	free ( g_SN.strPath.strAPDatabasePath );
    free ( g_SN.strPath.strModemDatabasePath );
	free ( g_SN.strPath.strModemDatabasePath2 );
	free ( g_SN.strPath.strAuthFilePath );
	free ( g_SN.strPath.strspSecureFilePath );
	free ( g_SN.strPath.strspAuthFilePath );
	free ( g_SN.strPath.strHDCPKeyPath );
	free ( g_SN.strPath.strDRMKeyPath );
	free ( g_SN.tLogBuffer.pStrLog );

 	g_SN.strPath.strAPDatabasePath = NULL; 
	g_SN.strPath.strModemDatabasePath = NULL;
	g_SN.strPath.strModemDatabasePath2 = NULL;
	g_SN.strPath.strAuthFilePath = NULL;
	g_SN.strPath.strspSecureFilePath = NULL;
	g_SN.strPath.strspAuthFilePath = NULL;
	g_SN.strPath.strHDCPKeyPath = NULL;
	g_SN.strPath.strDRMKeyPath = NULL;
	g_SN.tLogBuffer.pStrLog = NULL;
}


//-----Get g_SN configration from setup.txt file--------
void GetParaFromIni(){

	kal_uint32 temp = 0;
	char  tmpStr[1024] = {0};

    read_SP_WIFI_NVRAM_Path(sp_wifi_nvram_path);
	g_SN.tCommPort.eBaudRate = read_BaudRate ();
	

	//Add mtk71518 begin, 2013-07-05
	g_SN.tTargetInfo.eBBChip= read_IntValueFromSetupFile ("System Setup", "BB Chip");
	g_SN.tBTSetting.eBTChip = read_IntValueFromSetupFile ("System Setup", "BT Chip");
	g_SN.tCommPort.eComPort = read_IntValueFromSetupFile ("System Setup", "COM PORT");
	
	g_SN.tTargetInfo.mPowerOnDelayTime = 5000;
	g_SN.tTargetInfo.mPowerOnDelayTime = read_IntValueFromSetupFile ("System Setup", "MS ON Delay Time");
	
	g_SN.tFuncMode.eFuncType.bIMEI = read_BoolValueFromSetupFile("System Setup", "Write IMEI");
	g_SN.tFuncMode.eFuncType.bBarCode= read_BoolValueFromSetupFile("System Setup", "Write Barcode");
	g_SN.tFuncMode.eFuncType.bBT= read_BoolValueFromSetupFile("System Setup","Write BT");
	g_SN.tFuncMode.eFuncType.bWIFIMacadr= read_BoolValueFromSetupFile("System Setup", "Write WIFI");
	g_SN.tFuncMode.eFuncType.bHDCP= read_BoolValueFromSetupFile("System Setup", "Write HDCP");
	g_SN.tFuncMode.eFuncType.bDRMKeyInstall= read_BoolValueFromSetupFile("System Setup", "Write DRAM Key Install");
	
	g_SN.tIMEI.bCheckSum = read_BoolValueFromSetupFile("System Setup", "IMEI Check Sum");
    g_SN.tIMEI.bAutoCheckSum = read_BoolValueFromSetupFile("System Setup", "Auto Check Sum");
	g_SN.tIMEI.eImeiNum = read_IntValueFromSetupFile("System Setup", "IMEI nums");
	GetIMEIConfig();
	
	g_SN.bEnableMetaLog = KAL_TRUE;
	g_SN.tIMEI.bDualIMEISame = read_BoolValueFromSetupFile("System Setup", "IMEI DUAL SAME");
	g_SN.tIMEI.bLockIMEI = read_BoolValueFromSetupFile("System Setup", "IMEI Lock");
	g_SN.tIMEI.bLockIMEI_Enable = read_BoolValueFromSetupFile("System Setup", "IMEI Lock Dimmd ENABLE");
	g_SN.tIMEI.bCheckFTStatus = read_BoolValueFromSetupFile("System Setup", "IMEI Check FinalTest Status");
	g_SN.bEnableCDrom = read_BoolValueFromSetupFile("System Setup", "CDrom");
	g_SN.is6276M = read_BoolValueFromSetupFile("System Setup", "Is76M");
	g_SN.tIMEI.bSVNPAD_Enable = read_BoolValueFromSetupFile("System Setup", "IMEI SVNPAD ENABLE");	
	g_SN.bEnableSwitchDataCard = read_BoolValueFromSetupFile("System Setup", "Enable Switchtool");
	g_SN.isEntryDualTalk = read_BoolValueFromSetupFile("System Setup", "Enable DualTalk");
	read_Imei_SvnPad ( &g_SN.tIMEI.tImei_Svn_Pad );
	
	g_SN.tTargetInfo.eTargetType = read_IntValueFromSetupFile ("System Setup", "Target Type");
	g_SN.tFuncMode.eOperateMode = read_IntValueFromSetupFile ("System Setup", "Mode Type");

	temp = read_BackupFlag();

	read_StringValueFromSetupFile ( "System Setup", "Modem Database Path",g_SN.strPath.strModemDatabasePath );	
	read_StringValueFromSetupFile ( "System Setup", "AP Database Path",g_SN.strPath.strAPDatabasePath );
	read_StringValueFromSetupFile ("System Setup", "Authentication File Path", g_SN.strPath.strAuthFilePath );
	read_StringValueFromSetupFile("System Setup", "SP Authentication file",g_SN.strPath.strspAuthFilePath);
	read_StringValueFromSetupFile("System Setup", "SP Authentication file",g_SN.strPath.strspSecureFilePath);
	read_StringValueFromSetupFile("System Setup", "HDCP Key Path", g_SN.strPath.strHDCPKeyPath);
	read_StringValueFromSetupFile("System Setup", "DRM Key Path",g_SN.strPath.strDRMKeyPath);
	read_StringValueFromSetupFile ( "System Setup", "Modem2 Database Path",g_SN.strPath.strModemDatabasePath2 );

	g_SN.tTargetInfo.bWorldPhone = read_BoolValueFromSetupFile("System Setup", "Is MT6582 World Phone");
	us_temp_MDInex = read_spMD_Index();
	us_temp_SWInex = read_spSW_Version();
	
	if(us_temp_MDInex>2 || us_temp_MDInex <= 0)
	{
	    us_temp_MDInex = 1;
	}

	/*
	sprintf ( tmpStr, "GetParaFromIni : us_temp_SWInex = %d.\n", us_temp_SWInex);
	UpdateLog ( tmpStr, 0);
	*/
	
	if(us_temp_SWInex != 3 && us_temp_SWInex != 5)
	{
	     us_temp_SWInex = 5; //default value
	}
	
	read_HeadInfo(&g_HeadInfo);

	//Add mtk71518 end, 2013-07-05
	DimmdIMEILock=g_SN.tIMEI.bLockIMEI_Enable;//just for dimmd the IMEI LOCK Option 
	
}

//-----------------------Save to ini file--------------------
void SaveParaToIni(){
    
      
	write_BaudRate ( g_SN.tCommPort.eBaudRate );
	write_IntValueToSetupFile ("System Setup", "BB Chip", g_SN.tTargetInfo.eBBChip );
	write_IntValueToSetupFile ("System Setup", "BT Chip", g_SN.tBTSetting.eBTChip  );
	write_IntValueToSetupFile ("System Setup", "COM PORT", g_SN.tCommPort.eComPort );
	write_IntValueToSetupFile ("System Setup", "MS ON Delay Time",g_SN.tTargetInfo.mPowerOnDelayTime );
	write_IntValueToSetupFile("System Setup", "Target Type",g_SN.tTargetInfo.eTargetType);
	write_IntValueToSetupFile("System Setup", "Mode Type",g_SN.tFuncMode.eOperateMode);
	write_IntValueToSetupFile("System Setup", "IMEI nums",g_SN.tIMEI.eImeiNum);
	write_Imei_SvnPad ( g_SN.tIMEI.tImei_Svn_Pad  );

	write_BoolValueToSetupFile("System Setup", "Write IMEI",g_SN.tFuncMode.eFuncType.bIMEI);
	write_BoolValueToSetupFile("System Setup", "Write Barcode",g_SN.tFuncMode.eFuncType.bBarCode);
	write_BoolValueToSetupFile("System Setup", "Write BT",g_SN.tFuncMode.eFuncType.bBT);
	write_BoolValueToSetupFile("System Setup", "Write WIFI", g_SN.tFuncMode.eFuncType.bWIFIMacadr);
	write_BoolValueToSetupFile("System Setup", "Write HDCP",g_SN.tFuncMode.eFuncType.bHDCP);
	write_BoolValueToSetupFile("System Setup", "Write DRAM Key Install",g_SN.tFuncMode.eFuncType.bDRMKeyInstall);
	write_BoolValueToSetupFile ("System Setup", "IMEI Check Sum",g_SN.tIMEI.bCheckSum );
	write_BoolValueToSetupFile ("System Setup", "Auto Check Sum",g_SN.tIMEI.bAutoCheckSum);	
	

	write_BoolValueToSetupFile ("System Setup", "IMEI Lock",g_SN.tIMEI.bLockIMEI );
	write_BoolValueToSetupFile("System Setup", "IMEI DUAL SAME",g_SN.tIMEI.bDualIMEISame);
	write_BoolValueToSetupFile ("System Setup", "IMEI Check FinalTest Status",g_SN.tIMEI.bCheckFTStatus );
	write_BoolValueToSetupFile ("System Setup", "IMEI SVNPAD ENABLE",g_SN.tIMEI.bSVNPAD_Enable );
    write_BoolValueToSetupFile ("System Setup", "CDrom",g_SN.bEnableCDrom);
	write_BoolValueToSetupFile("System Setup", "Enable Switchtool",g_SN.bEnableSwitchDataCard);
	write_BoolValueToSetupFile("System Setup", "Enable DualTalk", g_SN.isEntryDualTalk);
	write_BoolValueToSetupFile("System Setup", "Is MT6582 World Phone", g_SN.tTargetInfo.bWorldPhone);
	
	write_StringValueToSetupFile("System Setup", "Modem Database Path", g_SN.strPath.strModemDatabasePath );
	write_StringValueToSetupFile("System Setup", "Modem2 Database Path", g_SN.strPath.strModemDatabasePath2);
	write_StringValueToSetupFile("System Setup", "AP Database Path", g_SN.strPath.strAPDatabasePath );
	write_StringValueToSetupFile("System Setup", "Authentication File Path",  g_SN.strPath.strAuthFilePath);
	write_StringValueToSetupFile("System Setup", "HDCP Key Path", g_SN.strPath.strHDCPKeyPath);
	write_StringValueToSetupFile("System Setup", "DRM Key Path", g_SN.strPath.strDRMKeyPath);
	
	write_HeadInfo(g_HeadInfo);
	write_EngineerPasswd(g_passwordVal);
	
	write_SetCleanBoot_Flag();

};


//------------------Update  <<->> g_SN--------------------
// bDir = TRUE  ==> g_SN->UI 
// bDir = FALSE ==> g_SN<-UI 
void UpdateUIComponent(kal_bool bDir){

    //-----------------------add by mtk71596-----------
    
    UpdateIMEI( bDir );
	UpdateBarCode( bDir );
	UpdateBT( bDir );
	UpdateWIFIMacadr( bDir );
	UpdateWIFIEEPROMCopy( bDir );
	UpdateCOMPort ( bDir ); 
	UpdateTargetType ( bDir );

	
	UpdateCheckSum ( bDir );
	UpdateDualIMEI ( bDir );
    UpdateDualIMEISame(bDir);	
	UpdateThreeIMEI(bDir);
	UpdateFourIMEI( bDir );
	
    //UpdateHDCP( bDir );
	//UpdateDRMKeyInstall( bDir );
	//UpdateLockIMEI ( bDir );
	//UpdateLockIMEI_Enable(g_SN.tIMEI.bLockIMEI_Enable);
	//UpdateCheckFTStatus ( bDir );	
	//UpdatePowerONDelayTime ( bDir );   
	//UpdateBaudRate ( bDir );
	//UpdateModeType ( bDir );



	UpdateModemDatabasePath ( bDir );
	UpdateModemDatabasePath_2( bDir );
	UpdateAPDatabasePath ( bDir );	
//	UpdateAuthFilePath ( bDir );

	UpdateMenuBBChip ( KAL_TRUE );
	UpdateMenuCom ( KAL_TRUE, 0 );
	UpdateMenuBaudRate ( KAL_TRUE, 0 );
	UpdateMenuTarget ( KAL_TRUE, 0 );
	UpdateMenuMode ( KAL_TRUE, 0 );
	UpdateMetaLog ( KAL_TRUE );	
	
	UpdateMenuBTPowerOn ( KAL_TRUE, 0 );
	UpdateMenuBTChip ( KAL_TRUE, 0 );

	UpdateMenuIMEI( KAL_TRUE );
	UpdateMenuBarCode( KAL_TRUE );
	UpdateMenuBT( KAL_TRUE );
	UpdateMenuWIFI ( KAL_TRUE );
	UpdateMenuHDCP( KAL_TRUE);
	UpdateMenuDRM_Key_Install( KAL_TRUE);
	//---------------------------------------


	UpdateMenuIMEICheckSum ( KAL_TRUE );
	UpdateMenuIMEILock ( KAL_TRUE );
	UpdateMenuDualIMEI ( KAL_TRUE );
	UpdateMenuThreeIMEI(KAL_TRUE);
	UpdateMenuFourIMEI ( KAL_TRUE );
	UpdateMenuFTStatusCheck( KAL_TRUE );
	UpdateImeiSvnPad ( bDir );

	UpdateMenuEnDatacard(KAL_TRUE);
	UpdateMenuEnDualTalk(KAL_TRUE);
	
}

void AccompanyActionWithDualIMEI()
{
	if(g_SN.tIMEI.eImeiNum == THREE_IMEI)
	{
		g_SN.tIMEI.eImeiNum = ONE_IMEI;
//		UpdateThirdIMEI(KAL_TRUE);
	}

	if(g_SN.tIMEI.bFourIMEI)
	{
		g_SN.tIMEI.bFourIMEI = KAL_FALSE;
//		UpdateFourIMEI(KAL_TRUE);
	}

}

void AccompanyActionWithThirdIMEI()
{
	if((g_SN.tIMEI.eImeiNum == THREE_IMEI) && (g_SN.tTargetInfo.eTargetType != TARGET_FEATURE_PHONE))
	{
		SetCtrlVal ( panelHandle_main, panelMain_eTargetSelect, TARGET_FEATURE_PHONE );
		//UpdateTargetType(KAL_FALSE);
		TargetSelect_Click(0,0,EVENT_COMMIT,NULL,0,0);
	}

	if(g_SN.tIMEI.bDualIMEI)
	{
		g_SN.tIMEI.bDualIMEI = KAL_FALSE;
//		UpdateDualIMEI(KAL_TRUE);
	}
	
	if(g_SN.tIMEI.bFourIMEI)
	{
		g_SN.tIMEI.bFourIMEI = KAL_FALSE;
//		UpdateFourIMEI(KAL_TRUE);
	}

	
}

void AccompanyActionWithClear()
{   

      if(g_SN.tCombine.bset)
	{
		g_SN.tCombine.bset= KAL_FALSE;
		UpdateSet(KAL_TRUE);
	}
	
}
void AccompanyActionWithData()
{   

      if(g_SN.tCombine.Callprefer)
	{
		g_SN.tCombine.Callprefer= KAL_FALSE;
		UpdateCallprefer(KAL_TRUE);
	}
	
}

void AccompanyActionWithCall()
{   

      if(g_SN.tCombine.Dataprefer)
	{
		g_SN.tCombine.Dataprefer= KAL_FALSE;
		UpdateDataprefer(KAL_TRUE);
	}
	
}
void AccompanyActionWithSetAMR()
{   

      if(g_SN.tCombine.ClearAMR)
	{
		g_SN.tCombine.ClearAMR= KAL_FALSE;
		UpdateClearAMR(KAL_TRUE);
	}
	
}


void AccompanyActionWithClearAMR()
{     	
	if(g_SN.tCombine.SetAMR)
	{
		g_SN.tCombine.SetAMR = KAL_FALSE;
		UpdateSetAMR(KAL_TRUE);
	}
		
}


void AccompanyActionWithAMR()
{    

	if(g_SN.tCombine.bDataCall)
	{
		g_SN.tCombine.bDataCall = KAL_FALSE;
		UpdateDataCall(KAL_TRUE);
	}
	
}




void AccompanyActionWithDataCall()
{  
   	if(g_SN.tCombine.AMR)
	{
		g_SN.tCombine.AMR = KAL_FALSE;
		UpdateAMR(KAL_TRUE);
	}
	
}




void AccompanyActionWithFourIMEI()
{
	if(g_SN.tIMEI.bFourIMEI && g_SN.tTargetInfo.eTargetType != TARGET_FEATURE_PHONE)
	{
		SetCtrlVal ( panelHandle_main, panelMain_eTargetSelect, TARGET_FEATURE_PHONE );
		//UpdateTargetType(KAL_FALSE);
		TargetSelect_Click(0,0,EVENT_COMMIT,NULL,0,0);
	}

	if(g_SN.tIMEI.bDualIMEI)
	{
		g_SN.tIMEI.bDualIMEI = KAL_FALSE;
//		UpdateDualIMEI(KAL_TRUE);
	}

	if(g_SN.tIMEI.eImeiNum == THREE_IMEI)
	{
		g_SN.tIMEI.eImeiNum = ONE_IMEI;
//		UpdateThirdIMEI(KAL_TRUE);
	}
	
}

void AccomanyActionWithModeSel()
{
	if(GetOperMode() == AT_MODE)
	{
//		if(GetFuncMode() != FUNC_IMEI && GetFuncMode() != FUNC_BARCODE)   changed by mtk71596
        if(!IsIMEIChecked() && !IsBarCodeChecked())//add by mtk71596
		{
//		    g_SN.tFuncMode.eFuncType = FUNC_BARCODE   changed by mtk71596
//			g_SN.tFuncMode.eFuncType = bBarCode; //add by mtk71596
//			UpdateFuncType(KAL_TRUE);		 changed by mtk71596
		}

		if(GetTargetType() != TARGET_FEATURE_PHONE)
		{
			g_SN.tTargetInfo.eTargetType = TARGET_FEATURE_PHONE;
			UpdateTargetType(KAL_TRUE);
		}
	}
}

kal_uint8* ResultToString(kal_uint8 MR)
{
	switch((META_RESULT)MR)
	{
	case META_SUCCESS:
		return M2S(META_SUCCESS);
	case META_FAILED:
		return M2S(META_FAILED);
	case META_COMM_FAIL:
		return M2S(META_COMM_FAIL);
	case META_NORESPONSE:
		return M2S(META_NORESPONSE);
	case META_BUFFER_LEN:
		return M2S(META_BUFFER_LEN); //0~4
		
	case META_FILE_BAD:
		return M2S(META_FILE_BAD);
	case META_LID_INVALID:
		return M2S(META_LID_INVALID);
	case META_INTERNAL_DB_ERR:
		return M2S(META_INTERNAL_DB_ERR);
	case META_NO_MEMORY:
		return M2S(META_NO_MEMORY);
	case META_INVALID_ARGUMENTS:
		return M2S(META_INVALID_ARGUMENTS); //5~9
		
	case META_TIMEOUT: //10
		return M2S(META_TIMEOUT);
	case META_BUSY:
		return M2S(META_BUSY);
	case META_INVALID_HANDLE:
		return M2S(META_INVALID_HANDLE);
	case META_FAT_ERROR:
		return M2S(META_FAT_ERROR);
	case META_FAT_DISK_FULL:
		return M2S(META_FAT_DISK_FULL);

	case META_FAT_ROOT_DIR_FULL:
		return M2S(META_FAT_ROOT_DIR_FULL);
	case META_FAT_INVALID_FILENAME:
		return M2S(META_FAT_INVALID_FILENAME);
	case META_FAT_INVALID_FILE_HANDLE:
		return M2S(META_FAT_INVALID_FILE_HANDLE);
	case META_FAT_FILE_NOT_FOUND:
		return M2S(META_FAT_FILE_NOT_FOUND);
	case META_FAT_DRIVE_NOT_FOUND:
		return M2S(META_FAT_DRIVE_NOT_FOUND);

	case META_FAT_PATH_NOT_FOUND:  //20
		return M2S(META_FAT_PATH_NOT_FOUND);
	case META_FAT_ACCESS_DENIED:
		return M2S(META_FAT_ACCESS_DENIED);
	case META_FAT_TOO_MANY_FILES:
		return M2S(META_FAT_TOO_MANY_FILES);
	case META_INCORRECT_TARGET_VER:
		return M2S(META_INCORRECT_TARGET_VER);
	case META_COM_ERROR:
		return M2S(META_COM_ERROR);

	case META_BROM_CMD_ERROR:
		return M2S(META_BROM_CMD_ERROR);
	case META_INCORRECT_BBCHIP_TYPE:
		return M2S(META_INCORRECT_BBCHIP_TYPE);
	case META_BROM_ERROR:
		return M2S(META_BROM_ERROR);
	case META_STOP_BOOTUP_PROCEDURE:
		return M2S(META_STOP_BOOTUP_PROCEDURE);
	case META_CANCEL:
		return M2S(META_CANCEL);
   /*
	case META_CCT_NOT_IMPORT_PROFILE: //30
		return M2S(META_CCT_NOT_IMPORT_PROFILE);
	case META_CCT_INVALID_SENSOR_ID:
		return M2S(META_CCT_INVALID_SENSOR_ID);
	case META_CCT_TGT_NO_MEM_FOR_SINGLE_SHOT:
		return M2S(META_CCT_TGT_NO_MEM_FOR_SINGLE_SHOT);
	case META_CCT_TGT_NO_MEM_FOR_MULTI_SHOT:
		return M2S(META_CCT_TGT_NO_MEM_FOR_MULTI_SHOT);
		*/
	case META_FUNC_NOT_IMPLEMENT_YET:
		return M2S(META_FUNC_NOT_IMPLEMENT_YET);
	 /*
	case META_CCT_PREVIEW_ALREADY_STARTED:
		return M2S(META_CCT_PREVIEW_ALREADY_STARTED);
	case META_CCT_PREVIEW_ALREADY_STOPPED:
		return M2S(META_CCT_PREVIEW_ALREADY_STOPPED);
	case META_CCT_READ_REG_NO_CNF:
		return M2S(META_CCT_READ_REG_NO_CNF);
	case META_CCT_WRITE_REG_NO_CNF:
		return M2S(META_CCT_WRITE_REG_NO_CNF);
	case META_CCT_TGT_ABORT_IMAGE_SENDING:
		return M2S(META_CCT_TGT_ABORT_IMAGE_SENDING);

	case META_CCT_READ_ONLY_REGISTER: //40
		return M2S(META_CCT_READ_ONLY_REGISTER);
	case META_CCT_LOAD_FROM_NVRAM_FAIL:
		return M2S(META_CCT_LOAD_FROM_NVRAM_FAIL);
	case META_CCT_SAVE_TO_NVRAM_FAIL:
		return M2S(META_CCT_SAVE_TO_NVRAM_FAIL);
	case META_CCT_AE_INVALID_EC_LEVEL:
		return M2S(META_CCT_AE_INVALID_EC_LEVEL);
	case META_CCT_AE_INVALID_EC_STEP:
		return M2S(META_CCT_AE_INVALID_EC_STEP);

	case META_CCT_AE_ALREADY_ENABLED:
		return M2S(META_CCT_AE_ALREADY_ENABLED);
	case META_CCT_AE_ALREADY_DISABLED:
		return M2S(META_CCT_AE_ALREADY_DISABLED);
	case META_CCT_WB_INVALID_INDEX:
		return M2S(META_CCT_WB_INVALID_INDEX);
	case META_CCT_NO_TGT_SENSOR_MATCH_IN_PROFILE:
		return M2S(META_CCT_NO_TGT_SENSOR_MATCH_IN_PROFILE);
	case META_CCT_IMAGE_SENDING_FAME_NUM_ERROR:
		return M2S(META_CCT_IMAGE_SENDING_FAME_NUM_ERROR);

	case META_CCT_AE_IS_NOT_DISABLED: //50
		return M2S(META_CCT_AE_IS_NOT_DISABLED);
		*/
	case META_FAT_APP_QUOTA_FULL:
		return M2S(META_FAT_APP_QUOTA_FULL);
	case META_IMEI_CD_ERROR:
		return M2S(META_IMEI_CD_ERROR);
	case META_RFID_MISMATCH:
		return M2S(META_RFID_MISMATCH);
	case META_NVRAM_DB_IS_NOT_LOADED_YET:
		return M2S(META_NVRAM_DB_IS_NOT_LOADED_YET);
	   /*
	case META_CCT_ERR_CAPTURE_WIDTH_HEIGHT_TOO_SMALL:
		return M2S(META_CCT_ERR_CAPTURE_WIDTH_HEIGHT_TOO_SMALL);
	case META_WAIT_FOR_TARGET_READY_TIMEOUT:
		return M2S(META_WAIT_FOR_TARGET_READY_TIMEOUT);
	case META_CCT_ERR_SENSOR_ENG_SET_INVALID_VALUE:
		return M2S(META_CCT_ERR_SENSOR_ENG_SET_INVALID_VALUE);
	case META_CCT_ERR_SENSOR_ENG_GROUP_NOT_EXIST:
		return M2S(META_CCT_ERR_SENSOR_ENG_GROUP_NOT_EXIST);
	case META_CCT_NO_TGT_ISP_MATCH_IN_PROFILE:
		return M2S(META_CCT_NO_TGT_ISP_MATCH_IN_PROFILE);

	case META_CCT_TGT_ISP_SUPPORT_NOT_DEFINED: //60
		return M2S(META_CCT_TGT_ISP_SUPPORT_NOT_DEFINED);
	case META_CCT_ERR_SENSOR_ENG_ITEM_NOT_EXIST:
		return M2S(META_CCT_ERR_SENSOR_ENG_ITEM_NOT_EXIST);
	case META_CCT_ERR_INVALID_COMPENSATION_MODE:
		return M2S(META_CCT_ERR_INVALID_COMPENSATION_MODE);
	case META_CCT_ERR_USB_COM_NOT_READY:
		return M2S(META_CCT_ERR_USB_COM_NOT_READY);
	case META_CCT_DEFECTPIXEL_CAL_UNDER_PROCESSING:
		return M2S(META_CCT_DEFECTPIXEL_CAL_UNDER_PROCESSING);

	case META_CCT_ERR_DEFECTPIXEL_CAL_NO_MEM:
		return M2S(META_CCT_ERR_DEFECTPIXEL_CAL_NO_MEM);
	case META_CCT_ERR_TOO_MANY_DEFECT_PIXEL:
		return M2S(META_CCT_ERR_TOO_MANY_DEFECT_PIXEL);
	case META_CCT_ERR_CAPTURE_JPEG_FAIL:
		return M2S(META_CCT_ERR_CAPTURE_JPEG_FAIL);
	case META_CCT_ERR_CAPTURE_JPEG_TIMEOUT:
		return M2S(META_CCT_ERR_CAPTURE_JPEG_TIMEOUT);
	case META_CCT_ERR_AF_FAIL:
		return M2S(META_CCT_ERR_AF_FAIL);

	case META_CCT_ERR_AF_TIMEOUT: //70
		return M2S(META_CCT_ERR_AF_TIMEOUT);
	case META_CCT_ERR_AF_LENS_OFFSET_CAL_FAIL:
		return M2S(META_CCT_ERR_AF_LENS_OFFSET_CAL_FAIL);
	case META_CCT_ERR_PREVIEW_MUST_ENABLE:
		return M2S(META_CCT_ERR_PREVIEW_MUST_ENABLE);
	case META_CCT_ERR_UNSUPPORT_CAPTURE_FORMAT:
		return M2S(META_CCT_ERR_UNSUPPORT_CAPTURE_FORMAT);
	case META_CCT_ERR_EXCEED_MAX_DEFECT_PIXEL:
		return M2S(META_CCT_ERR_EXCEED_MAX_DEFECT_PIXEL);

	case META_ERR_EXCEED_MAX_PEER_BUF_SIZE:
		return M2S(META_ERR_EXCEED_MAX_PEER_BUF_SIZE);
	case META_CCT_ERR_INVALID_WIDTH_FACTOR:
		return M2S(META_CCT_ERR_INVALID_WIDTH_FACTOR);
	case META_BROM_SECURITY_CHECK_FAIL:
		return M2S(META_BROM_SECURITY_CHECK_FAIL);
	case META_CCT_ERR_PREVIEW_MUST_DISABLE:
		return M2S(META_CCT_ERR_PREVIEW_MUST_DISABLE);
		*/
	case META_MAUI_DB_INCONSISTENT:
		return M2S(META_MAUI_DB_INCONSISTENT);

	case META_FAT_FILEPATH_TOO_LONG: //80
		return M2S(META_FAT_FILEPATH_TOO_LONG);
	case META_FAT_RESTRICTED_FILEPATH:
		return M2S(META_FAT_RESTRICTED_FILEPATH);
	case META_FAT_DIR_NOT_EXIST:
		return M2S(META_FAT_DIR_NOT_EXIST);
	case META_FAT_DISK_SPACE_IS_NOT_ENOUGH:
		return M2S(META_FAT_DISK_SPACE_IS_NOT_ENOUGH);
	case META_TDMB_ERR_BAND_NOT_EXIST:
		return M2S(META_TDMB_ERR_BAND_NOT_EXIST);

	case META_TDMB_ERR_FREQ_NOT_EXIST:
		return M2S(META_TDMB_ERR_FREQ_NOT_EXIST);
	case META_TDMB_ERR_ENSM_NOT_EXIST:
		return M2S(META_TDMB_ERR_ENSM_NOT_EXIST);
	case META_TDMB_ERR_SERV_NOT_EXIST:
		return M2S(META_TDMB_ERR_SERV_NOT_EXIST);
	case META_TDMB_ERR_SUB_CHAN_NOT_EXIST:
		return M2S(META_TDMB_ERR_SUB_CHAN_NOT_EXIST);
	case META_TDMB_ERR_DEMOD_STATE:
		return M2S(META_TDMB_ERR_DEMOD_STATE);

	case META_ENUMERATE_USB_FAIL: //90
		return M2S(META_ENUMERATE_USB_FAIL);
	case META_STOP_ENUM_USB_PROCEDURE:
		return M2S(META_STOP_ENUM_USB_PROCEDURE);
		/*
	case META_CCT_6238_AE_ALREADY_ENABLED:
		return M2S(META_CCT_6238_AE_ALREADY_ENABLED);
	case META_CCT_6238_AE_ALREADY_DISABLED:
		return M2S(META_CCT_6238_AE_ALREADY_DISABLED);
	case META_CCT_6238_AE_IS_NOT_DISABLED:
		return M2S(META_CCT_6238_AE_IS_NOT_DISABLED);

	case META_CCT_6238_ISP_FLASHLIGHT_LINEARITY_PRESTROBE_FAIL:
		return M2S(META_CCT_6238_ISP_FLASHLIGHT_LINEARITY_PRESTROBE_FAIL);
		*/
	case META_MISC_TARGET_LOAD_NEED_TO_BE_PATCHED:
		return M2S(META_MISC_TARGET_LOAD_NEED_TO_BE_PATCHED);
	case META_MISC_INI_FILE_SETTINGS_WRONG:
		return M2S(META_MISC_INI_FILE_SETTINGS_WRONG);
	case META_MISC_FAIL_TO_READ_IMEI:
		return M2S(META_MISC_FAIL_TO_READ_IMEI);
	case META_MISC_FAIL_TO_BACKUP_FILE:
		return M2S(META_MISC_FAIL_TO_BACKUP_FILE);

	case META_MISC_FAIL_TO_WRITE_BACKUP_RESULT: //100
		return M2S(META_MISC_FAIL_TO_WRITE_BACKUP_RESULT);
	case META_MISC_FAIL_TO_GET_NVRAM_FOLDER_PATH:
		return M2S(META_MISC_FAIL_TO_GET_NVRAM_FOLDER_PATH);
	case META_MISC_FAIL_TO_GET_NVRAM_MUST_LIST:
		return M2S(META_MISC_FAIL_TO_GET_NVRAM_MUST_LIST);
	case META_STOP_CURRENT_PROCEDURE:
		return M2S(META_STOP_CURRENT_PROCEDURE);
	case META_MISC_CUSTOMIZED_NVRAM_ERROR:
		return M2S(META_MISC_CUSTOMIZED_NVRAM_ERROR);

	case META_MISC_FOLDER_EMPTY_CHECKING_FAIL:
		return M2S(META_MISC_FOLDER_EMPTY_CHECKING_FAIL);
	case META_MISC_TOO_MANY_BACKUP_RESULT_FILE:
		return M2S(META_MISC_TOO_MANY_BACKUP_RESULT_FILE);
	case META_MISC_TOO_MANY_RESTORE_RESULT_FILE:
		return M2S(META_MISC_TOO_MANY_RESTORE_RESULT_FILE);
	case META_MISC_RESTORE_RESULT_FILE_NOT_EXIST:
		return M2S(META_MISC_RESTORE_RESULT_FILE_NOT_EXIST);
	case META_MISC_RESTORE_RESULT_FILE_INCOMPLETE:
		return M2S(META_MISC_RESTORE_RESULT_FILE_INCOMPLETE);

	case META_FAIL_TO_CELAR_ALL_IN_BACUP_FOLDER: //110
		return M2S(META_FAIL_TO_CELAR_ALL_IN_BACUP_FOLDER);
	case META_MISC_BACKUP_RESULT_FILE_NOT_EXIST:
		return M2S(META_MISC_BACKUP_RESULT_FILE_NOT_EXIST);
	case META_MISC_BACKUP_RESULT_FILE_INCOMPLETE:
		return M2S(META_MISC_BACKUP_RESULT_FILE_INCOMPLETE);
	case META_MISC_IMEI_MISMATCH:
		return M2S(META_MISC_IMEI_MISMATCH);
	case META_MISC_SML_FILE_VERIFY_FAIL:
		return M2S(META_MISC_SML_FILE_VERIFY_FAIL);

	case META_MISC_BACKUP_RESULT_NOT_ENOUGH_FOR_NEW_LOAD:
		return M2S(META_MISC_BACKUP_RESULT_NOT_ENOUGH_FOR_NEW_LOAD);
	case META_MISC_FAIL_TO_RESTORE_FILE:
		return M2S(META_MISC_FAIL_TO_RESTORE_FILE);
	case META_MISC_FAIL_TO_WRITE_RESTORE_RESULT:
		return M2S(META_MISC_FAIL_TO_WRITE_RESTORE_RESULT);
	case META_MISC_USE_WRONG_API_FOR_NEW_LOAD:
		return M2S(META_MISC_USE_WRONG_API_FOR_NEW_LOAD);
	case META_MISC_QUERY_TARGET_CAPABILITY_FAIL:
		return M2S(META_MISC_QUERY_TARGET_CAPABILITY_FAIL);
		

	case META_MISC_INI_SETTINGS_ERR_IN_NVRAM_SEC: //120
		return M2S(META_MISC_INI_SETTINGS_ERR_IN_NVRAM_SEC);
	case META_MISC_INI_SETTINGS_ERR_IN_TARGET_SEC:
		return M2S(META_MISC_INI_SETTINGS_ERR_IN_TARGET_SEC);
	case META_MISC_INI_SETTINGS_ERR_IN_PC_SEC:
		return M2S(META_MISC_INI_SETTINGS_ERR_IN_PC_SEC);
	case META_MISC_NO_FILES_NEED_TO_BE_UPLOAD:
		return M2S(META_MISC_NO_FILES_NEED_TO_BE_UPLOAD);
	case META_FAT_ACTION_NOT_SUPPORT:
		return M2S(META_FAT_ACTION_NOT_SUPPORT);
	 /*
	case META_CCT_DUAL_UNSOPPORT_DUAL_CAMERA_IN_TARGET:
		return M2S(META_CCT_DUAL_UNSOPPORT_DUAL_CAMERA_IN_TARGET);
	case META_CCT_DUAL_SET_MAIN_SUB_SENSOR_FAIL:
		return M2S(META_CCT_DUAL_SET_MAIN_SUB_SENSOR_FAIL);
	case META_CCT_DUAL_GET_CAMERA_PARA_TABLE_TAIL:
		return M2S(META_CCT_DUAL_GET_CAMERA_PARA_TABLE_TAIL);
	case META_CCT_DUAL_GET_SENSOR_PREFIX_NAME_TAIL:
		return M2S(META_CCT_DUAL_GET_SENSOR_PREFIX_NAME_TAIL);
	case META_CCT_DUAL_ERR_DETECT_SENSOR_ID_FAIL:
		return M2S(META_CCT_DUAL_ERR_DETECT_SENSOR_ID_FAIL);


	case META_CCT_ERR_DETECT_SENSOR_ID_FAIL: //130
		return M2S(META_CCT_ERR_DETECT_SENSOR_ID_FAIL);
	case META_CCT_ERR_YUV_SENSOR_NOT_SUPPORT:
		return M2S(META_CCT_ERR_YUV_SENSOR_NOT_SUPPORT);
	case META_CCT_DUAL_GET_LENS_PREFIX_NAME_TAIL:
	*/
		return M2S(META_CCT_DUAL_GET_LENS_PREFIX_NAME_TAIL);
	case META_MISC_EMPTY_UPLOADFILES_AND_IMEI_SEC:
		return M2S(META_MISC_EMPTY_UPLOADFILES_AND_IMEI_SEC);
	case META_MISC_INI_SETTINGS_ERR_IN_MORE_SEC:
		return M2S(META_MISC_INI_SETTINGS_ERR_IN_MORE_SEC);

	case META_MISC_INI_SETTINGS_ERR_IN_DELETE_SEC:
		return M2S(META_MISC_INI_SETTINGS_ERR_IN_DELETE_SEC);
	case META_MISC_CHECK_TARGET_NVRAM_FILES_FAIL:
		return M2S(META_MISC_CHECK_TARGET_NVRAM_FILES_FAIL);
	case META_MISC_FAIL_TO_GET_NVRAM_FOLDER_AMOUNT:
		return M2S(META_MISC_FAIL_TO_GET_NVRAM_FOLDER_AMOUNT);
	case META_AUDIO_CHECK_WAVE_FILE_FAIL:
		return M2S(META_AUDIO_CHECK_WAVE_FILE_FAIL);
	case META_LAST_RESULT:
		return M2S(META_LAST_RESULT);

	default:
		return M2S(DEFAULT_FAIL);
	}
}

kal_bool CheckIdentityPasswd(kal_char *strPasswd)
{
    if(strlen(strPasswd) <= 0 || strlen(strPasswd) > 16)
		return KAL_FALSE;

	//return KAL_TRUE;
	if(0 == strcmp(g_passwordVal, strPasswd))
	{
	   //g_CheckStatus = E_Check_CORRECT;
	   return KAL_TRUE;
	}
	else
	{
	   //g_CheckStatus = E_Check_UNCORRECT;
	   MessagePopup("Warning", "Incorrect engineer password!\nPlease try again!");
	   return KAL_FALSE;
	}
}

void GetPassword (int hpanel, kal_uint16 ctrlID, kal_char *strPasswd)
{
    PasswordCtrl_GetAttribute (hpanel, ctrlID, ATTR_PASSWORD_VAL,
                               strPasswd);  //��ȡ�༭������
	//MessagePopup("GetPassword", strPasswd);
	
}
 
void SetPassword (int hpanel, kal_uint16 ctrlID, kal_char *strPasswd)
{	
    PasswordCtrl_SetAttribute (hpanel, ctrlID, ATTR_PASSWORD_VAL,
                               strPasswd);//��ձ༭��	
    //MessagePopup("SetPassword", strPasswd);
}

void EngineerSwitchToOperator (void)
{
    g_IsEngineer = KAL_FALSE;
    SetPanelAttribute( panelHandle_main, ATTR_TITLE, "SN_Write_Tool(Operator Mode)" );
    SetCtrlAttribute ( panelHandle_main, panelMain_System_Config, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_main, panelMain_eTargetSelect, ATTR_DIMMED, KAL_TRUE );
	
	SetMenuBarAttribute ( menuHandle, menuMain_File, ATTR_DIMMED, KAL_TRUE);
	SetMenuBarAttribute ( menuHandle, menuMain_Option, ATTR_DIMMED, KAL_TRUE );
	SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI, ATTR_DIMMED, KAL_TRUE );

	SetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY, ATTR_DIMMED, KAL_TRUE );		
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Engineer, ATTR_DIMMED, KAL_TRUE );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Engineer, ATTR_CHECKED, KAL_FALSE );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Operator, ATTR_DIMMED, KAL_FALSE );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Operator, ATTR_CHECKED, KAL_TRUE);
}

void OperatorSwitchToEngineer (void)
{
	g_IsEngineer = KAL_TRUE;

    SetPanelAttribute( panelHandle_main, ATTR_TITLE, "SN_Write_Tool(Engineer Mode)" );
    SetCtrlAttribute ( panelHandle_main, panelMain_System_Config, ATTR_DIMMED, KAL_FALSE);	
    SetCtrlAttribute ( panelHandle_main, panelMain_eTargetSelect, ATTR_DIMMED, KAL_FALSE);

	SetMenuBarAttribute ( menuHandle, menuMain_File, ATTR_DIMMED, KAL_FALSE);
	SetMenuBarAttribute ( menuHandle, menuMain_Option, ATTR_DIMMED, KAL_FALSE );
	SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI, ATTR_DIMMED, KAL_FALSE );

	SetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY, ATTR_DIMMED, KAL_FALSE );		
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Engineer, ATTR_DIMMED, KAL_FALSE );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Engineer, ATTR_CHECKED, KAL_TRUE );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Operator, ATTR_DIMMED, KAL_TRUE );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity_Operator, ATTR_CHECKED, KAL_FALSE );
}

kal_bool ConfirmNewPassword(kal_char *strNewpasswd, kal_char *strConfpasswd)
{
	if(strlen(strNewpasswd) == 0 || strlen(strConfpasswd) == 0)
	{
		return KAL_FALSE;
	}
	
	if(0 == strcmp(strNewpasswd, strConfpasswd))
	{
	    return KAL_TRUE;
	}
	else
	{
	    MessagePopup("Warning", "The Confirm password is not the same the New Password!\nPlease make sure the new password and try again!");
	    return KAL_FALSE;
	}
}

void UpdateCheckBarCode( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckBcHead,  g_HeadInfo.bCheckBarcode);

	} else{

		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckBcHead, (kal_char*)&g_HeadInfo.bCheckBarcode);
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBarcHead, ATTR_DIMMED, !g_HeadInfo.bCheckBarcode);
		if(g_HeadInfo.bCheckBarcode == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strBarcHead);
	}
}

void UpdateCheckBT( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckBThead, g_HeadInfo.bCheckBT);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckBThead, (kal_char*)&g_HeadInfo.bCheckBT);
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBTHead, ATTR_DIMMED, !g_HeadInfo.bCheckBT);
		if(g_HeadInfo.bCheckBT == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strBTHead );
	}
}

void UpdateCheckWIFI( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead, g_HeadInfo.bCheckWIFI);

	} 
	else
	{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead,  (kal_char*)&g_HeadInfo.bCheckWIFI);
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strWifiHead, ATTR_DIMMED, !g_HeadInfo.bCheckWIFI);
		if(g_HeadInfo.bCheckWIFI == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strWifiHead );
	}
}

void UpdateHeadInfo( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
	    SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strBarcHead,  g_HeadInfo.Barcode);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckBcHead,  g_HeadInfo.bCheckBarcode);
		if(g_pWriteOption->bWriteBarcode == KAL_TRUE)
		{		    	    
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBarcHead, ATTR_DIMMED, KAL_FALSE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBcHead, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBarcHead, ATTR_DIMMED, KAL_TRUE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBcHead, ATTR_DIMMED, KAL_TRUE);
		}

        SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI1Head,  g_HeadInfo.IMEI_1);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head,  g_HeadInfo.bCheckIMEI_1);
		if(g_pWriteOption->bWriteIMEI == KAL_TRUE)
		{		    
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI1Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI1Head, ATTR_DIMMED, KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head, ATTR_DIMMED, KAL_TRUE);
		}
		
        SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI2Head,  g_HeadInfo.IMEI_2);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head,  g_HeadInfo.bCheckIMEI_2);
		if((g_pWriteOption->bWriteIMEI == KAL_TRUE) && (g_SN.tIMEI.bDualIMEI == KAL_TRUE))
		{		 
		    //SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bDualIMEI,  KAL_TRUE);
			if(g_SN.tIMEI.bDualIMEISame == KAL_TRUE)
				SetCtrlVal ( panelHandle_OperateCfg, panelCfg_DualImeiSame,  KAL_TRUE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
		    SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bDualIMEI,  KAL_FALSE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
		}

        SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI3Head,  g_HeadInfo.IMEI_3);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head,  g_HeadInfo.bCheckIMEI_3);
		if((g_pWriteOption->bWriteIMEI == KAL_TRUE) && (g_SN.tIMEI.bThreeIMEI == KAL_TRUE))
		{	
		    //SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bThreeIMEI,  KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_TRUE);
		}

		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI4Head,  g_HeadInfo.IMEI_4);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head,  g_HeadInfo.bCheckIMEI_4);
		if((g_pWriteOption->bWriteIMEI == KAL_TRUE) && (g_SN.tIMEI.bFourIMEI == KAL_TRUE))
		{		
		    //SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bFourIMEI,  KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_FALSE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);
		}

        SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strBTHead,  g_HeadInfo.BT);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckBThead,  g_HeadInfo.bCheckBT);
		if(g_pWriteOption->bWriteBT == KAL_TRUE)
		{		  
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBTHead, ATTR_DIMMED, KAL_FALSE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBThead, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBTHead, ATTR_DIMMED, KAL_TRUE);
		    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBThead, ATTR_DIMMED, KAL_TRUE);
		}

        SetCtrlVal ( panelHandle_OperateCfg, panelCfg_strWifiHead,  g_HeadInfo.WIFI);
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead,  g_HeadInfo.bCheckWIFI);
		if(g_pWriteOption->bWriteWIFI == KAL_TRUE)
		{		 
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strWifiHead, ATTR_DIMMED, KAL_FALSE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead, ATTR_DIMMED, KAL_FALSE);
		}
		else
		{
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strWifiHead, ATTR_DIMMED, KAL_TRUE);
			SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead, ATTR_DIMMED, KAL_TRUE);
		}

	} 
	else
	{
		if(g_HeadInfo.bCheckBarcode == KAL_TRUE)
		{
		    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strBarcHead,  (kal_char*)g_HeadInfo.Barcode);
		}

		if(g_HeadInfo.bCheckIMEI_1== KAL_TRUE)
		{
		    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI1Head,  (kal_char*)g_HeadInfo.IMEI_1);
		}

		if(g_HeadInfo.bCheckIMEI_2 == KAL_TRUE)
		{
			if(g_SN.tIMEI.bDualIMEISame)
	    	{
			    strcpy(g_HeadInfo.IMEI_2,g_HeadInfo.IMEI_1);				
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);
	    	}
			else
			{
		        GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI2Head,  (kal_char*)g_HeadInfo.IMEI_2);
			}
		}

		if(g_HeadInfo.bCheckIMEI_3 == KAL_TRUE)
		{
		    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI3Head,  (kal_char*)g_HeadInfo.IMEI_3);
		}

		if(g_HeadInfo.bCheckIMEI_4 == KAL_TRUE)
		{
		    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strIMEI4Head,  (kal_char*)g_HeadInfo.IMEI_4);
		}

		if(g_HeadInfo.bCheckBT == KAL_TRUE)
		{
		    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strBTHead,  (kal_char*)g_HeadInfo.BT);
		}

		if(g_HeadInfo.bCheckWIFI == KAL_TRUE)
		{
		    GetCtrlVal ( panelHandle_OperateCfg, panelCfg_strWifiHead,  (kal_char*)g_HeadInfo.WIFI);
		}
	}
}


int GetIMEInums(void)
{  
    if(g_pWriteOption->bWriteIMEI == KAL_TRUE) 
    {
       if(g_SN.tIMEI.bDualIMEI == KAL_TRUE)
       {
          g_SN.tIMEI.eImeiNum = DUAL_IMEI;
       }
       else if(g_SN.tIMEI.bThreeIMEI == KAL_TRUE)
       {
          g_SN.tIMEI.eImeiNum = THREE_IMEI;
       }
       else if(g_SN.tIMEI.bFourIMEI == KAL_TRUE)
       {
          g_SN.tIMEI.eImeiNum = FOUR_IMEI;
       }
	   else
	   	  g_SN.tIMEI.eImeiNum = ONE_IMEI;
   }
   else
   {
       g_SN.tIMEI.eImeiNum = IMEI_NONE;
   }

   return g_SN.tIMEI.eImeiNum;
}


void HighLightCurrentScanData(int controlID)
{
    SetActiveCtrl(panelHandle_CodeScan, controlID);
	SetCtrlVal(panelHandle_CodeScan, controlID, "");
	SetCtrlAttribute(panelHandle_CodeScan, controlID, ATTR_TEXT_BGCOLOR , VAL_CYAN);			  
	SetCtrlAttribute(panelHandle_CodeScan, controlID, ATTR_TEXT_COLOR , VAL_RED);
}

void ResetCurrentScanID(int controlID)
{
	SetCtrlAttribute(panelHandle_CodeScan, controlID, ATTR_TEXT_BGCOLOR , VAL_WHITE);			  
	SetCtrlAttribute(panelHandle_CodeScan, controlID, ATTR_TEXT_COLOR , VAL_BLACK);
}

CheckScanData_Result_E CheckAllScanData(void)
{
    int i = 0;
    int j = 0;  // currenScanOrderItem index
	int k = 0;  // newScanOrderItem index
	kal_char strScanData[65];
    kal_char strHead[65];
	kal_bool bDataAllCorrect = KAL_TRUE;
	
	for(i = E_BARCODE_INDEX; i < MAX_SCANDATA_ITEMS; i++)
	{
	    if(g_bScanItem[i])
		{
			GetCurrentScanData(g_realScanOrderID[j], strScanData, strHead);
			switch(i)
		    {
		       case E_BARCODE_INDEX:
			   	   if((strlen(strScanData) == 0 || strlen(strScanData) > 64 ))
			       {	
				       HighLightCurrentScanData(g_realScanOrderID[j]);
					   g_realScanOrderID[k] = g_realScanOrderID[j];
					   k += 1;
				       bDataAllCorrect = KAL_FALSE;
			       }
			       else
				   {
			           if(g_bCheckHead[i])
			           {
				           if(CheckScanDataHead(strScanData, strHead) != 0)
				           {
				               HighLightCurrentScanData(g_realScanOrderID[j]);
					           g_realScanOrderID[k] = g_realScanOrderID[j];
					           k += 1;
					           bDataAllCorrect = KAL_FALSE;
				           }
				           else
				           {
					           g_bScanItem[i] = KAL_FALSE;
				           }
			            }				   
                        else
                        {
						    g_bScanItem[i] = KAL_FALSE;	
                        }
				   }
			   	   break;
				   
			   case E_IMEI1_INDEX:				   
			   case E_IMEI2_INDEX:
			   case E_IMEI3_INDEX:				   
			   case E_IMEI4_INDEX:
			   	   if(strlen(strScanData) != 15)
			       {	
				       HighLightCurrentScanData(g_realScanOrderID[j]);
					   g_realScanOrderID[k] = g_realScanOrderID[j];
					   k += 1;
				       bDataAllCorrect = KAL_FALSE;
			       }
				   else
				   {
				        if(g_bCheckHead[i])
			            {
				            if((CheckScanDataHead(strScanData, strHead) != 0) || CheckIMEIData(strScanData) == KAL_FALSE)
				            {
				                HighLightCurrentScanData(g_realScanOrderID[j]);
					            g_realScanOrderID[k] = g_realScanOrderID[j];
					            k += 1;
					            bDataAllCorrect = KAL_FALSE;
				            }
							else
                            {
						        g_bScanItem[i] = KAL_FALSE;
								if(g_SN.tIMEI.bDualIMEI == KAL_TRUE && g_SN.tIMEI.bDualIMEISame == KAL_TRUE)
							    {
							        strncpy(imei[1], imei[0], strlen(imei[0]));
							    }
                            }
			            }
                        else 
                        {
                            if(CheckIMEIData(strScanData) == KAL_TRUE)
                            {
						       g_bScanItem[i] = KAL_FALSE;
							   if(g_SN.tIMEI.bDualIMEI == KAL_TRUE && g_SN.tIMEI.bDualIMEISame == KAL_TRUE)
							   {
							      strncpy(imei[1], imei[0], strlen(imei[0]));
							   }
                            }
							else
							{
							    HighLightCurrentScanData(g_realScanOrderID[j]);
					            g_realScanOrderID[k] = g_realScanOrderID[j];
					            k += 1;
					            bDataAllCorrect = KAL_FALSE;
							}
                        }
				   }
			   	   break;
				   
			   case E_BT_INDEX:				   
			   case E_WIFI_INDEX:
			   	   if(strlen(strScanData) != 12)
			       {	
				       HighLightCurrentScanData(g_realScanOrderID[j]);
					   g_realScanOrderID[k] = g_realScanOrderID[j];
					   k += 1;
				       bDataAllCorrect = KAL_FALSE;
			       }
				   else
				   {
				        if(g_bCheckHead[i])
			            {
				            if(CheckScanDataHead(strScanData, strHead) != 0 || CheckBT_WIFIData(strScanData) == KAL_FALSE )
				            {
				                HighLightCurrentScanData(g_realScanOrderID[j]);
					            g_realScanOrderID[k] = g_realScanOrderID[j];
					            k += 1;
					            bDataAllCorrect = KAL_FALSE;
				            }
							else
                            {
						        g_bScanItem[i] = KAL_FALSE;	
                            }
			            }
                        else
                        {
                            if(CheckBT_WIFIData(strScanData) == KAL_TRUE )
                            {
                                g_bScanItem[i] = KAL_FALSE; 
                            }
							else
							{						        	
								HighLightCurrentScanData(g_realScanOrderID[j]);
					            g_realScanOrderID[k] = g_realScanOrderID[j];
					            k += 1;
					            bDataAllCorrect = KAL_FALSE;
							}
                        }
				   }
			   	   break;				
		    }
			
			j += 1;
		}
	}

	g_realScanOrderID[k] = PANEL_OK;			
	if(bDataAllCorrect)
	{
		return DataAllCorrect;
	}
	else
	{
		return DataCheckFail;
	}
}


CheckScanData_Result_E CheckCurrentScanData(int controlID)
{
   
   int nextControlID = 0;
   /*
   int i = 0;
   int j = 0;
   kal_char strScanData[65];
   kal_char strHead[65];
   kal_bool bDataAllCorrect = KAL_TRUE;
   */
   switch(controlID)
	{
	   case PANEL_IDBarCode:
	   	
	   	if(g_bScanItem[E_BARCODE_INDEX])
	   	{
	   	    GetCtrlVal( panelHandle_CodeScan, controlID, BarCode);
	   	    if((strlen(BarCode) == 0 || strlen(BarCode) > 63 ))
			{	
				  HighLightCurrentScanData(PANEL_IDBarCode);
				  return CheckBarcodeFail;
			}
			else
			{
			      if(g_HeadInfo.bCheckBarcode)
				   {
				      if(CheckScanDataHead(BarCode, g_HeadInfo.Barcode) != 0)
				      {
				
						 HighLightCurrentScanData(PANEL_IDBarCode);
				         return CheckBarcodeFail;
				      }
					  /*
					  else
					  {
					      //GetCtrlAttribute (panelHandle_CodeScan, PANEL_IDBarCode, ATTR_NEXT_CTRL, (int*)&nextControlID);
					      nextControlID = GetNextScanControlID(PANEL_IDBarCode);
						 SetActiveCtrl(panelHandle_CodeScan, nextControlID);
					  }
					  */
				   }
				
			 }
	   	 }
	   	 break;
		 
	   case PANEL_FirstIMEI:
        
		if(g_bScanItem[E_IMEI1_INDEX])
		{
		    GetCtrlVal( panelHandle_CodeScan, controlID, imei[0]);
	   	    if(strlen(imei[0]) != 15)
		    {
			   HighLightCurrentScanData(PANEL_FirstIMEI);
		       return CheckIMEI1Fail;
		    }
			else 
			{
				   if(g_HeadInfo.bCheckIMEI_1)
				   {
				      if((CheckScanDataHead(imei[0], g_HeadInfo.IMEI_1) != 0))
				      {
				         HighLightCurrentScanData(PANEL_FirstIMEI);
				         return CheckIMEI1Fail;
				      }										  
				   }
				   
				   if(CheckIMEIData(imei[0]) == KAL_TRUE)
				   {
				       if(g_SN.tIMEI.bDualIMEI == KAL_TRUE && g_SN.tIMEI.bDualIMEISame == KAL_TRUE)
				       {
				           strncpy(imei[1], imei[0], strlen(imei[0]));
				       }
				   }
				   else
				   {
					   HighLightCurrentScanData(PANEL_FirstIMEI);
				       return CheckIMEI1Fail;
				   }
		 	}
		}
	   	 break;
		 
	   case PANEL_SecondIMEI:

		if(g_bScanItem[E_IMEI2_INDEX])
		{
		      GetCtrlVal( panelHandle_CodeScan, controlID, imei[1]);
			  if(strlen(imei[1]) != 15) 
			   {
			      HighLightCurrentScanData(PANEL_SecondIMEI);
				  return CheckIMEI2Fail;
			   }
			   else
			   {
				   if(g_HeadInfo.bCheckIMEI_2)
				   {
				      if((CheckScanDataHead(imei[1], g_HeadInfo.IMEI_2) != 0))
				      {
				         HighLightCurrentScanData(PANEL_SecondIMEI);
				         return CheckIMEI2Fail;
				      }	
					  
				   }
				  
				   if(CheckIMEIData(imei[1]) == KAL_FALSE)
				   {
				       HighLightCurrentScanData(PANEL_SecondIMEI);
				       return CheckIMEI2Fail;
				   }
				  
			   }
		}
	   	 break;

		 case PANEL_ThirdIMEI:

		if(g_bScanItem[E_IMEI3_INDEX])
		{
		      GetCtrlVal( panelHandle_CodeScan, controlID, imei[2]);
			  if(strlen(imei[2]) != 15) 
			   {
			      HighLightCurrentScanData(PANEL_ThirdIMEI);
				  return CheckIMEI3Fail;
			   }
			   else
			   {
				   if(g_HeadInfo.bCheckIMEI_3)
				   {
				      if(CheckScanDataHead(imei[2], g_HeadInfo.IMEI_3) != 0)
				      {
				         HighLightCurrentScanData(PANEL_ThirdIMEI);
				         return CheckIMEI3Fail;
				      }						  
				   }

				   if(CheckIMEIData(imei[2]) == KAL_FALSE)
				   {
				       HighLightCurrentScanData(PANEL_ThirdIMEI);
				       return CheckIMEI3Fail;
				   }
			   }
		}
	   	 break;

		 case PANEL_FourthIMEI:

		if(g_bScanItem[E_IMEI4_INDEX])
		{
		      GetCtrlVal( panelHandle_CodeScan, controlID, imei[3]);
			  if(strlen(imei[3]) != 15) 
			   {
			      HighLightCurrentScanData(PANEL_FourthIMEI);
				  return CheckIMEI4Fail;
			   }
			   else
			   {
				   if(g_HeadInfo.bCheckIMEI_4)
				   {
				      if((CheckScanDataHead(imei[3], g_HeadInfo.IMEI_4) != 0) || CheckIMEIData(imei[3]) == KAL_FALSE)
				      {
				         HighLightCurrentScanData(PANEL_FourthIMEI);
				         return CheckIMEI4Fail;
				      }	
				   }

				   if(CheckIMEIData(imei[3]) == KAL_FALSE)
				   {
				       HighLightCurrentScanData(PANEL_FourthIMEI);
				       return CheckIMEI4Fail;
				   }
				  
			   }
		}
	   	 break;
		 
	   case PANEL_IDBT:
	   	if(g_bScanItem[E_BT_INDEX])
	   	{
	   	 GetCtrlVal( panelHandle_CodeScan, controlID, BT);
	   	 if(strlen(BT) != 12)
			   {
			      HighLightCurrentScanData(PANEL_IDBT);
				  return CheckBTFail;
			   }
			   else
			   {
			        if(g_HeadInfo.bCheckBT)
				   {
				      if(CheckScanDataHead(BT, g_HeadInfo.BT) != 0 || CheckBT_WIFIData(BT) == KAL_FALSE )
				      {
				         HighLightCurrentScanData(PANEL_IDBT);
				         return CheckBTFail;
				      }	
					 
				   }
				   else
				   {
				        if(CheckBT_WIFIData(BT) == KAL_FALSE )
                        {
                            HighLightCurrentScanData(PANEL_IDBT);
				            return CheckBTFail; 
                        }
							
				   }
			   }
	   		}
	   	 break;
		 
	   case PANEL_IDWIFI:
	   	if(g_bScanItem[E_WIFI_INDEX])
	   	{
	   	 GetCtrlVal( panelHandle_CodeScan, controlID, WIFI);
	   	 if(strlen(WIFI) != 12)
			   {
			      HighLightCurrentScanData(PANEL_IDWIFI);
				  return CheckWIFIFail;
			   }
			   else
			   {
			       if(g_HeadInfo.bCheckWIFI)
				   {
				      if(CheckScanDataHead(WIFI, g_HeadInfo.WIFI) != 0 || CheckBT_WIFIData(WIFI) == KAL_FALSE)
				      {
				         HighLightCurrentScanData(PANEL_IDWIFI);
				         return CheckWIFIFail;
				      }	
					 
				   }
				   else
				   {
				  	   if(CheckBT_WIFIData(WIFI) == KAL_FALSE )
                        {
                            HighLightCurrentScanData(PANEL_IDWIFI);
				            return CheckWIFIFail; 
                        }
				   }
			   }
	   		}
	   	 break;
		 
	}
   
	return DataAllCorrect;
}

kal_bool CheckScanDataHead(const kal_char *strScanData, const kal_char *strHead)
{
    int length = strlen(strHead);   
	return(strncmp(strHead, strScanData, length));			
}

kal_bool CheckBT_WIFIData(const kal_char *strScanData)
{
    int dataLenght = 0;
	int i = 0;
	char msgStr[256] = {0};
	dataLenght = strlen(strScanData);
	
	for(i = 0; i < dataLenght; i++)
	{
	    if ( !((strScanData[i] <= '9' && strScanData[i] >= '0') 
			   || (strScanData[i] <= 'F' && strScanData[i] >= 'A') 
               || (strScanData[i] <= 'f' && strScanData[i] >= 'a')))
	    {
	        sprintf(msgStr, "The Data = \"%s\" have some characters is illegal!!", strScanData);
	        MessagePopup("Data Error", msgStr);
			return KAL_FALSE;
	    }
	}

	return KAL_TRUE;
}

kal_bool CheckIMEIData(const kal_char *strScanData)
{
    int imeiLenght = 0;
	int index = 0;
	char msgStr[256] = {0};
	imeiLenght = strlen(strScanData);
	
	for(index = 0; index < imeiLenght; index++)
	{
	    if(strScanData[index] >'9' || strScanData[index] < '0')
	    {
	        sprintf(msgStr, "The IMEI = \"%s\" have some characters is no digit!!", strScanData);
	        MessagePopup("IMEI Error", msgStr);
			return KAL_FALSE;
	    }
	}

	return KAL_TRUE;
}


void ResetScanItem(void)
{
    CreateScanOrder();
}


void CreateScanOrder(void)
{
    int initScanOrderID[MAX_SCANDATA_NUMS];
	int i = 0;
	int j = 0;
	
	g_bScanItem[E_BARCODE_INDEX] = g_pWriteOption->bWriteBarcode;
	g_bScanItem[E_IMEI1_INDEX] = g_pWriteOption->bWriteIMEI;
	g_bScanItem[E_IMEI2_INDEX] = (g_pWriteOption->bWriteIMEI &&((g_SN.tIMEI.bDualIMEI== KAL_TRUE && g_SN.tIMEI.bDualIMEISame == KAL_FALSE) || g_SN.tIMEI.bThreeIMEI== KAL_TRUE || g_SN.tIMEI.bFourIMEI== KAL_TRUE));
	g_bScanItem[E_IMEI3_INDEX] = (g_pWriteOption->bWriteIMEI &&(g_SN.tIMEI.bThreeIMEI== KAL_TRUE || g_SN.tIMEI.bFourIMEI== KAL_TRUE));
	g_bScanItem[E_IMEI4_INDEX] = (g_pWriteOption->bWriteIMEI &&( g_SN.tIMEI.bFourIMEI== KAL_TRUE));
	g_bScanItem[E_BT_INDEX] = g_pWriteOption->bWriteBT;
	g_bScanItem[E_WIFI_INDEX] = g_pWriteOption->bWriteWIFI;

	g_bCheckHead[E_BARCODE_INDEX] = g_HeadInfo.bCheckBarcode;
	g_bCheckHead[E_IMEI1_INDEX] = g_HeadInfo.bCheckIMEI_1;
	g_bCheckHead[E_IMEI2_INDEX] = g_HeadInfo.bCheckIMEI_2;
	g_bCheckHead[E_IMEI3_INDEX] = g_HeadInfo.bCheckIMEI_3;
	g_bCheckHead[E_IMEI4_INDEX] = g_HeadInfo.bCheckIMEI_4;
	g_bCheckHead[E_BT_INDEX] = g_HeadInfo.bCheckBT;
	g_bCheckHead[E_WIFI_INDEX] = g_HeadInfo.bCheckWIFI;

    initScanOrderID[0] = PANEL_IDBarCode;
	initScanOrderID[1] = PANEL_FirstIMEI;
	initScanOrderID[2] = PANEL_SecondIMEI;
	initScanOrderID[3] = PANEL_ThirdIMEI;
	initScanOrderID[4] = PANEL_FourthIMEI;
	initScanOrderID[5] = PANEL_IDBT;
	initScanOrderID[6] = PANEL_IDWIFI;
	initScanOrderID[7] = PANEL_OK;
	
    j = 0;
	for(i = E_BARCODE_INDEX; i < MAX_SCANDATA_ITEMS; i++)
	{
	   if(g_bScanItem[i])
	   {
	      g_realScanOrderID[j] = initScanOrderID[i];
		  j += 1;
	   }
	}
    g_realScanIDNums = j;
	g_realScanOrderID[j] = PANEL_OK;
	
}

int GetNextScanControlID(int currentID)
{
   int nextID;
   int i = 0;
   
   ResetCurrentScanID(currentID);
   
   for(i = 0; i < MAX_SCANDATA_NUMS; i++)
	{
	   if(g_realScanOrderID[i] == currentID)
	   {
	      nextID = g_realScanOrderID[i+1];
		  break;
	   }
	}

   HighLightCurrentScanData(nextID);
   return nextID;
}

void GetCurrentScanData(int currentID, kal_char* strScanData, kal_char* strHead)
{
    GetCtrlVal( panelHandle_CodeScan, currentID, (kal_char*)strScanData);

	switch(currentID)
	{
	    case PANEL_IDBarCode:
			strcpy(strHead,g_HeadInfo.Barcode);
			break;

		case PANEL_FirstIMEI:
			strcpy(strHead,g_HeadInfo.IMEI_1);			
			break;

		case PANEL_SecondIMEI:
			strcpy(strHead,g_HeadInfo.IMEI_2);
			break;

		case PANEL_ThirdIMEI:
			strcpy(strHead,g_HeadInfo.IMEI_3);
			break;

		case PANEL_FourthIMEI:
			strcpy(strHead,g_HeadInfo.IMEI_4);
			break;

		case PANEL_IDBT:
			strcpy(strHead,g_HeadInfo.BT);
			break;

		case PANEL_IDWIFI:
			strcpy(strHead,g_HeadInfo.WIFI);
			break;
	}
}

void GetPasswordFromCtrl(kal_int32 panelID, int currentID, kal_char* strPassword)
{
    //GetCtrlVal ( panelID, currentID,  (kal_char*)strPassword);
	PasswordCtrl_GetAttribute (panelID, currentID, ATTR_PASSWORD_VAL,
                               strPassword);  //��ȡ�༭������
}

void GetIMEIConfig(void)
{
    switch(g_SN.tIMEI.eImeiNum)
	{
	   case ONE_IMEI:
	   	  g_SN.tIMEI.bDualIMEI = KAL_FALSE;
		  g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
		  g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
		  g_SN.tIMEI.bFourIMEI = KAL_FALSE;
	   	  break;

	   case DUAL_IMEI:
	   	  g_SN.tIMEI.bDualIMEI = KAL_TRUE;
		  g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
		  g_SN.tIMEI.bFourIMEI = KAL_FALSE;
	   	  break;

	   case THREE_IMEI:
	   	  g_SN.tIMEI.bDualIMEI = KAL_FALSE;
		  g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
		  g_SN.tIMEI.bThreeIMEI = KAL_TRUE;
		  g_SN.tIMEI.bFourIMEI = KAL_FALSE;
	   	  break;

	   case FOUR_IMEI:
	   	  g_SN.tIMEI.bDualIMEI = KAL_FALSE;
		  g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
		  g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
		  g_SN.tIMEI.bFourIMEI = KAL_TRUE;
	   	  break;
	   	  
	   default:
	   	  g_SN.tFuncMode.eFuncType.bIMEI = KAL_FALSE;
	   	  g_SN.tIMEI.bDualIMEI = KAL_FALSE;
		  g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
		  g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
		  g_SN.tIMEI.bFourIMEI = KAL_FALSE;
	   	  break;
	}
}


void UpdateCheckIMEI_1( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head,  g_HeadInfo.bCheckIMEI_1);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head, (kal_char*)&g_HeadInfo.bCheckIMEI_1);
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI1Head, ATTR_DIMMED, !g_HeadInfo.bCheckIMEI_1);
		if(g_HeadInfo.bCheckIMEI_1 == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strIMEI1Head );
	}
}

void UpdateCheckIMEI_2( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head,  g_HeadInfo.bCheckIMEI_2);
	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head,  (kal_char*)&g_HeadInfo.bCheckIMEI_2);	
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, !g_HeadInfo.bCheckIMEI_2);	
		if(g_HeadInfo.bCheckIMEI_2 == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strIMEI2Head );
		
	}
}

void UpdateCheckIMEI_3( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head,  g_HeadInfo.bCheckIMEI_3);

	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, (kal_char*)&g_HeadInfo.bCheckIMEI_3);
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, !g_HeadInfo.bCheckIMEI_3);
		if(g_HeadInfo.bCheckIMEI_3 == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strIMEI3Head );
	}
}

void UpdateCheckIMEI_4( kal_bool bDir )
{
    if ( KAL_TRUE == bDir )
	{
		SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head,  g_HeadInfo.bCheckIMEI_4);
	} else{
		
		GetCtrlVal ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head,  (kal_char*)&g_HeadInfo.bCheckIMEI_4);	
		SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, !g_HeadInfo.bCheckIMEI_4);	
		if(g_HeadInfo.bCheckIMEI_4 == KAL_TRUE)
		   SetActiveCtrl ( panelHandle_OperateCfg, panelCfg_strIMEI4Head );
		
	}
}

void DimmedMenuItem(kal_bool bDimmed)
{    
	SetMenuBarAttribute ( menuHandle, panelMain_QUIT, ATTR_DIMMED, bDimmed );
	SetMenuBarAttribute ( menuHandle, menuMain_File, ATTR_DIMMED, bDimmed);
	SetMenuBarAttribute ( menuHandle, menuMain_Option, ATTR_DIMMED, bDimmed );
	SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI, ATTR_DIMMED, bDimmed );	
	SetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY, ATTR_DIMMED, bDimmed );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity, ATTR_DIMMED, bDimmed );
}

