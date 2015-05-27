/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
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
 *   SN_STATION.c
 *
 * Project:
 * --------
 *   SN Write Tool
 *
 * Description:
 * ------------
 *  Production Line Barcode/IMEI write use
 *
 * Author:
 * -------
 *  Ben Huang (mtk00797)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
//---------------------------------------------------------------------------

/******************************************************************************************************************************
 *																				        	
 *				MediaTek Inc.     												        	
 *				Purpose :To do the Target site write service
 *				Designer :Ben Huang 											        	
 *				First Release:2004/4/e														
 *				Release History	:	
 * SN_STATION Tool release information
 *;version history
 *
 *SN_STATION :
 *    Support IMEI and Barcode Write function
 *
 *
 *SN_STATION V1.1.0 :
 *    Support check IMEI and Barcode from target
 *    ,disable show full AT Command information
 *
 *SN_STATION V1.2.0 :
 *
 *     Add META Mode for write IMEI,Barcode and IMEI PAD ,IMEI SVN 
 *
 *
 *SN_STATION V1.2.1 :
 *
 *    When Manual Mode = 0 and then to add Dimmed Items :     
 *         Baud Rate,COM port,MS ON Delay Time,BB Chipset
 *         Write IMEI SVN&PAD, SVN ,PAD, Check final Test Status,
 *         Select NVRAM Database file,NVRAM Database file.
 *
 *    Modify Panel title to "Write_AT_COMMAND_STATION_V1.2.1"
 *
 *SN_STATION V1.2.2 :
 *    Modify MTK_WRT_SN_V122 with 3.05.0601 META_APP.dll
 *
 *SN_STATION V1.2.3 :
 *    Change MTK_WRT_SN_V122 with 3.05.0602 META_APP.dll
 *SN_STATION V1.2.4 :
 *    Change MTK_WRT_SN_V122 with 3.6.0 META_APP.dll
 *    Add Audio information write function   
 *SN_STATION V1.2.5 :
 *   Add 6217 interfance 
 *SN_STATION V1.2.6 :
 *   Add Target information display
 *SN_STATION V1.4.0 :
 *   Change META_APP.dll V3.7.01
 *SN_STATION V1.5.0 :
 *    Add Scan BD address in META mode for hand phone version.
 *SN_STATION V1.6.0 :
 *    Add Scan BD address in META mode for HCI version.			
 *SN_STATION V1.6.2 :
 *    Add Loopback1 test functions through AT Command.
 *    Add ANA Trim and BT power table scan.
 *SN_STATION V1.6.5 :
 *    Add Loopback2 test functions through AT Command.
 *    Add query BT ID function avoid old version test load fail when BD address scan
 *SN_STATION V1.6.6 :   
 *    update BT power table default value
 *    modify BT power table structure
 *SN_STATION V1.7.0:
 *    Improve IMEI writing time by AT command
 *SN_STATION V1.7.2
 *    Add AT+EMBT=5 for BT loopback 1 and loopback 2 test.
 *SN_STATION V1.8.0
 *    Change META_APP dll to V5.3.5.0 
 *    Add support MT6230/MT6225/MT6268T/MT6223/MT6227D select interface
/*----------------------------------------------------------------------------------*/
#include <Windows.h>  
#include <cvirte.h>		
#include <userint.h>
#include <inifile.h>



#include "pwctrl.h"


#include "sn_station.h" 
#include "uipara.h"
#include "thread.h"

#include "context.h"
#include <utility.h>

#include "SN_STATION.h"
#include "brom.h"

#include "AtProcess.h"
#include "com_enum.h"
#include "USBSwitchDLLibrary.h"
#include "des.h"

/*-------------------------------Define Res Handle------------------------------------*/
#define SYSTEM_ERROR (5)
#define MAX_COMPORT_COUNT 30

/*-------------------------------Define Res Handle------------------------------------*/
kal_int32 panelHandle_main;
kal_int32 panelHandle_about;
kal_int32 panelHandle_Input;
kal_int32 panelHandle_imei;
kal_int32 panelHandle_DualImei;

kal_int32 panelHandle_CodeScan;//add by mtk71596
kal_int32 panelHandle_OperateCfg;
kal_int32 menuHandle;
kal_int32 panelHandle_combine;
unsigned short ComPortArray[255];
unsigned short ComPortCount = 255;
int TempMenuID = 0;
kal_int32 MenuItemID[MAX_COMPORT_COUNT];
//---------add by mtk71596---------------
kal_char imei[4][16] = {0};
kal_char BarCode[64];
kal_char BT[13];
kal_char WIFI[13];
kal_uint32 BootROMUSBDetection ;//change6.5

//---------------------------------------
kal_bool DimmdIMEILock;
/*------------------------------------------------------------------------------------*/ 

//******************************************
//mtk71518,2013-05-30, Login check identity
kal_bool    g_IsEngineer;
kal_bool    g_bLoginByEngineer;
kal_int32   panelHandle_PanelEngin;
kal_int32   panelHandle_PanelChgpw;
kal_uint16  g_passwordICtrlID;
kal_uint16  g_oldpasswordICtrlID;
kal_uint16  g_newpasswordICtrlID;
kal_uint16  g_confirmpasswordICtrlID;

kal_char    g_passwordVal[MAX_PASSWORD_LENGTH + 1];
//kal_char    g_inputpasswordVal[MAX_PASSWORD_LENGTH + 1];
kal_char    g_oldpasswordVal[MAX_PASSWORD_LENGTH + 1];
//kal_char    g_newpasswordVal[MAX_PASSWORD_LENGTH + 1];
kal_char    g_confirmpasswordVal[MAX_PASSWORD_LENGTH + 1];
kal_bool    g_IsCheckOldpwDone;

unsigned int us_temp_MDInex;  // add for MT6582 Support
unsigned int us_temp_SWInex;  // add for MT6582 Support

//CheckOldpwStatus_E g_CheckStatus;


HeadInfo_struct     g_HeadInfo;
OptionSelect_struct *g_pWriteOption = (OptionSelect_struct*)&g_SN.tFuncMode.eFuncType ;


CheckScanData_Result_E g_eCheckDataResult;
int g_realScanIDNums;
int g_realScanOrderID[MAX_SCANDATA_NUMS];
kal_bool g_bScanItem[MAX_SCANDATA_ITEMS];	
kal_bool g_bCheckHead[MAX_SCANDATA_ITEMS];
kal_bool g_bCheckAllFirstTime;






//******************************************


extern kal_bool read_Identity( void );
extern int read_EngineerPasswd ( kal_char *strPassword );
extern void ResetDatabaseInitFlag(void);



extern void MetaContextInit ( void );
extern void MetaContextDeInit (void);
extern kal_bool AuthInit ( void ); 
extern kal_bool SpAuthInit (void);
extern kal_bool SpSecuInit (void); 

extern void SetBootStopFlag ( kal_bool enable );
extern kal_bool GetBootStopFlag ( void );

extern void SetConnectedFlag ( kal_bool enable );
extern kal_bool GetConnectedFlag ( void );

extern kal_bool NvramDatabaseInit ( void );
extern kal_bool Nvram2DatabaseInit ( void );
extern kal_bool APNvramDatabaseInit ( void );

extern void ResetNvramUpdateFlag ( void);
extern void ResetNvram2UpdateFlag ( void);
extern void ResetAPNvramUpdateFlag ( void );
//extern void UpdateUIMACHead(void);
//extern void DimUIMACHead(void); 
extern void GetDualImei(kal_bool Flag); 

extern void Sp_ModemDebugOn(void);
extern void Sp_ApDebugOn(void);

//extern kal_uint32 IsMACHeadChecked(void);  

//-----------------add by mtk71596-------------------------
extern kal_uint32 IsIMEIChecked(void); 
extern kal_uint32 IsBarCodeChecked(void);
extern kal_uint32 IsBTChecked(void);
extern kal_uint32 IsWIFIChecked(void);
extern kal_uint32 IsHDCPChecked(void);
extern kal_uint32 IsDRM_Key_InstallChecked(void);

extern void ResetHDCPUpdateFlag ( void );
extern void ResetDRMKeyUpdateFlag ( void );
extern int write_EngineerPasswd ( kal_char *strPassword );
extern void UpdateMenuSecurreUSB(kal_bool bDir);


//-------------------------------------------------------------
//add by mtk71596


void DimmedUI_StartWrite(kal_bool Dimmed );

void UpdateDualIMEISame ( kal_bool bDir );


//-------------------------------------------------------------------------------- 
int GetComPortDynamiclly(void);

char HdcpKeyFilePath[MAX_PATHNAME_LEN]="C:\\Program Files\\MTK_SN_Write_tool";  

char DRMKeyFilePath[MAX_PATHNAME_LEN]="C:\\Program Files\\MTK_SN_Write_tool";


void Enable_Timer ( kal_bool enable )
{
	SetCtrlAttribute ( panelHandle_main, panelMain_mTIMER, ATTR_ENABLED, enable );	
	ResetTimer ( panelHandle_main, panelMain_mTIMER );
}

//--------------------------------------------------------------------------------   
void SetTimerInterval ( kal_uint32 iInterval )
{

	SetCtrlAttribute ( panelHandle_main, panelMain_mTIMER, ATTR_INTERVAL, iInterval/1000.0 );		
}

//------------------------------add by mtk71596------------------------------------------
int  CVICALLBACK IMEI_Click(int panel, int control, int event, 
void *callbackData,int eventData1, int eventData2)
{
   switch (event)
    {
		case EVENT_COMMIT:
			
			UpdateIMEI ( KAL_FALSE );
			UpdateMenuIMEI(KAL_TRUE);
			if(g_pWriteOption->bWriteIMEI)
			{
			    
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI1Head, ATTR_DIMMED, KAL_FALSE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckSum, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bDualIMEI, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bFourIMEI, ATTR_DIMMED, KAL_FALSE );
				if(g_SN.tIMEI.bDualIMEI)
				{
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);				
				}
				else if(g_SN.tIMEI.bThreeIMEI)
				{
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_FALSE);
				}
				else if(g_SN.tIMEI.bFourIMEI)
				{
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_FALSE);
				}
				else
				{
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_TRUE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
				}
				
			}
			else
			{
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckSum, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bDualIMEI, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bFourIMEI, ATTR_DIMMED, KAL_TRUE );
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei1Head, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI1Head, ATTR_DIMMED, KAL_TRUE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_TRUE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
			}

			break;
    }
	return 0;
}

int  CVICALLBACK BarCode_Click(int panel, int control, int event, 
 void *callbackData, int eventData1, int eventData2)
{
   switch (event)
    {
		case EVENT_COMMIT:
			
			UpdateBarCode ( KAL_FALSE );
			UpdateMenuBarCode( KAL_TRUE );

            if(g_pWriteOption->bWriteBarcode)
            {
                SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBcHead, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBarcHead, ATTR_DIMMED, KAL_FALSE);
            }
			else
			{
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBcHead, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBarcHead, ATTR_DIMMED, KAL_TRUE);
			}


			break;
    }
	return 0;
}

int  CVICALLBACK BT_Click(int panel, int control, int event, 
	void *callbackData, int eventData1, int eventData2)
{
   switch (event)
    {
		case EVENT_COMMIT:
			
			UpdateBT( KAL_FALSE );
			UpdateMenuBT( KAL_TRUE );
			if(g_pWriteOption->bWriteBT)
            {
                SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBThead, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBTHead, ATTR_DIMMED, KAL_FALSE);
            }
			else
			{
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckBThead, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strBTHead, ATTR_DIMMED, KAL_TRUE);
			}

			break;
    }
	return 0;
}	

int  CVICALLBACK WIFIMacadr_Click(int panel, int control, int event, 
	void *callbackData, int eventData1, int eventData2)
{
   switch (event)
	{
		case EVENT_COMMIT:
			
			UpdateWIFIMacadr( KAL_FALSE );
			UpdateMenuWIFI( KAL_TRUE );
			if(g_pWriteOption->bWriteWIFI)
            {
                SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strWifiHead, ATTR_DIMMED, KAL_FALSE);				
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bWIFIEEPROMCopy, ATTR_DIMMED, KAL_TRUE);
            }
			else
			{
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckWifiHead, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strWifiHead, ATTR_DIMMED, KAL_TRUE);			
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bWIFIEEPROMCopy, ATTR_DIMMED, KAL_FALSE);
			}

			break;
	}
	return 0;
}
int  CVICALLBACK WIFIEEPROMCopy_Click(int panel, int control, int event, 
	                void *callbackData, int eventData1, int eventData2)
{
    switch (event)
	{
		case EVENT_COMMIT:	
			UpdateWIFIEEPROMCopy(KAL_FALSE);
			if(g_SN.tFuncMode.eFuncType.bWIFIEEPROMCopy)
			 {
			   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bWIFIMacadr, ATTR_DIMMED, KAL_TRUE);
			 }
			else
				{
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bWIFIMacadr, ATTR_DIMMED, KAL_FALSE);				
				}
			break;
	}
	return 0;
}


//--------------------------------------------------------------------------------   


void DimmedCfgUI_TargetSelect ( void ){

		E_TARGET_TYPE targetStype  = GetTargetType();
		
        switch(targetStype)
        {
            case PCMCIA_CARD:
            case TARGET_FEATURE_PHONE:
			
			{
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_Database_Select, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_DB_Select_2, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database_2, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_AP_Database_Select, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strAP_Database, ATTR_DIMMED, KAL_TRUE );
				break;
            }
			case RNDIS_DONGLE:
			case TARGET_SMARTPHONE:
			{
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_Database_Select, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_DB_Select_2, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database_2, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_AP_Database_Select, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strAP_Database, ATTR_DIMMED, KAL_FALSE );
/*
				SetCtrlAttribute ( panelHandle_main, panelMain_SetCleanBoot, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_main, panelMain_bFourIMEI, ATTR_DIMMED, KAL_TRUE );
			    SetCtrlAttribute ( panelHandle_main, panelMain_bThirdIMEI, ATTR_DIMMED, KAL_TRUE );
*/
				g_SN.strPath.strAuthFilePath = g_SN.strPath.strspAuthFilePath;

				break;
            }
			
			case Tablet_WIFI_ONLY:
			{
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_Database_Select, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_DB_Select_2, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database_2, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_AP_Database_Select, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strAP_Database, ATTR_DIMMED, KAL_FALSE );
/*
/*
				SetCtrlAttribute ( panelHandle_main, panelMain_SetCleanBoot, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_main, panelMain_bFourIMEI, ATTR_DIMMED, KAL_TRUE );
			    SetCtrlAttribute ( panelHandle_main, panelMain_bThirdIMEI, ATTR_DIMMED, KAL_TRUE );
*/
				break;
            }

			case SP_DUALMODEM:
			{
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_Database_Select, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_Modem_DB_Select_2, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strModem_Database_2, ATTR_DIMMED, KAL_FALSE );
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_AP_Database_Select, ATTR_DIMMED, KAL_FALSE);
			    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strAP_Database, ATTR_DIMMED, KAL_FALSE );
/*
				SetCtrlAttribute ( panelHandle_main, panelMain_SetCleanBoot, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_main, panelMain_bFourIMEI, ATTR_DIMMED, KAL_TRUE );
			    SetCtrlAttribute ( panelHandle_main, panelMain_bThirdIMEI, ATTR_DIMMED, KAL_TRUE );
				SetCtrlAttribute ( panelHandle_main, panelMain_bDualIMEI, ATTR_DIMMED, KAL_FALSE);	//ADD BY MTK71596
*/
				g_SN.strPath.strAuthFilePath = g_SN.strPath.strspAuthFilePath;

				break;
            }
			
			defaut:
				break;
        }
/*
		if(IsIMEIChecked())
		{
			SetCtrlAttribute ( panelHandle_main, panelMain_bFourIMEI, ATTR_DIMMED, KAL_FALSE );
			SetCtrlAttribute ( panelHandle_main, panelMain_bThirdIMEI, ATTR_DIMMED, KAL_FALSE );
		}
*/

}

//--------------------------------------------------------------------------------   


//--------------------------------------------------------------------------------   
void DimmedUI_StartWrite (kal_bool Dimmed) {
	if ( Dimmed )  
	{
		SetCtrlAttribute ( panelHandle_main, panelMain_START_WRITE, ATTR_LABEL_TEXT, "__STOP" );  
	    //SetCtrlAttribute ( panelHandle_main, panelMain_START_WRITE, ATTR_CMD_BUTTON_COLOR, VAL_YELLOW);
		//SetMenuBarAttribute ( panelHandle_main, panelMain_QUIT, ATTR_CMD_BUTTON_COLOR, VAL_YELLOW );
	} 
	else
	{
		SetCtrlAttribute ( panelHandle_main, panelMain_START_WRITE, ATTR_LABEL_TEXT, "__START" );
		//SetCtrlAttribute ( panelHandle_main, panelMain_START_WRITE, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
		//SetMenuBarAttribute ( panelHandle_main, panelMain_QUIT, ATTR_CMD_BUTTON_COLOR, VAL_GREEN );
	}

    SetCtrlAttribute ( panelHandle_main, panelMain_eCOMPort, ATTR_DIMMED, Dimmed );
	SetMenuBarAttribute ( menuHandle, menuMain_Identity, ATTR_DIMMED, Dimmed );
	SetMenuBarAttribute ( menuHandle, panelMain_QUIT, ATTR_DIMMED, Dimmed );
	
	if(g_IsEngineer == KAL_TRUE)
	{
	     SetCtrlAttribute ( panelHandle_main, panelMain_System_Config, ATTR_DIMMED, Dimmed );
	     SetCtrlAttribute ( panelHandle_main, panelMain_eTargetSelect, ATTR_DIMMED, Dimmed );	
	     SetMenuBarAttribute ( menuHandle, menuMain_File, ATTR_DIMMED, Dimmed);
	     SetMenuBarAttribute ( menuHandle, menuMain_Option, ATTR_DIMMED, Dimmed );
	     SetMenuBarAttribute ( menuHandle, menuMain_BTIMEI, ATTR_DIMMED, Dimmed );
	     SetMenuBarAttribute ( menuHandle, menuMain_HDCPDRMKEY, ATTR_DIMMED, Dimmed );	
	}		
}

//--------------------------------------------------------------------------------   
void UIDimmedComponent (void){


	Sp_ModemDebugOn();
	Sp_ApDebugOn();

    GetCtrlVal ( panelHandle_main, panelMain_eCOMPort, (kal_int32*) &g_SN.tCommPort.eComPort );//FOR usb AT CMD  ,so we update the com
    //SetCtrlAttribute ( panelHandle_main, panelMain_QUIT, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
	//SetCtrlAttribute ( panelHandle_main, panelMain_START_WRITE, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
	if(g_IsEngineer == KAL_TRUE)
	{
		OperatorSwitchToEngineer();
	}
	else 
	{
		EngineerSwitchToOperator();
	}

};

//--------------------------------------------------------------------------------  
int CVICALLBACK Start_Write_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:
			

			if ( KAL_TRUE == GetBootStopFlag () ) 
			{
			
				SetBootStopFlag ( KAL_FALSE );	// Enable connect
				
				DimmedUI_StartWrite ( KAL_TRUE );

			    CreateScanOrder();
				
				SNWriteThreadExec ();           //Start to connect

				SetBootStopFlag ( KAL_TRUE);
			
				DimmedUI_StartWrite ( KAL_FALSE );
			}
			else 
			{   

				SetBootStopFlag ( KAL_TRUE);
			
				DimmedUI_StartWrite ( KAL_FALSE );
			}

			break;
    }
	return 0;
}

//--------------------------------------------------------------------------------    
int CVICALLBACK Quit_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:
			
           		SetBootStopFlag ( KAL_TRUE );
				if(g_SN.bEnableSwitchDataCard)
				{
           		    disableUSBSwitch();
				}

			QuitUserInterface (0);
			
			break;
    }
	return 0;
}

//--------------------------------------------------------------------------------  
int Modem_Database_Select_Click_Shell ( void )
{

   return Modem_Database_Select_Click (panelHandle_OperateCfg, panelCfg_Modem_Database_Select, EVENT_COMMIT,

 								NULL,(int)NULL, (int)NULL);
}

int Modem2_Database_Select_Click_Shell ( void )
{

   return Modem_DB_Select_2 (panelHandle_OperateCfg, panelCfg_Modem_DB_Select_2, EVENT_COMMIT,

 								NULL,(int)NULL, (int)NULL);
}

//--------------------------------------------------------------------------------  
int AP_Database_Select_Click_Shell ( void )
{

   return AP_Database_Select_Click (panelHandle_OperateCfg, panelCfg_AP_Database_Select, EVENT_COMMIT,

 								NULL,(int)NULL, (int)NULL);
}
//--------------------------------------------------------------------------------  
int CVICALLBACK Modem_Database_Select_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int ret_val;
    switch (event)
    {
		case EVENT_COMMIT:

			 ret_val = FileSelectPopup ( g_SN.strPath.strModemDatabasePath, "*.*", "*.*",
                                   "Open Modem Database ...", VAL_OK_BUTTON,
                                    KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strModemDatabasePath ); 

			if ( VAL_NO_FILE_SELECTED != ret_val)
			{
				UpdateModemDatabasePath ( KAL_TRUE ); // update UI     
				ResetNvramUpdateFlag ();
			}
			break;
    }
	return 0;
}

int CVICALLBACK Modem_DB_Select_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    int ret_val;
	switch (event)
		{
		case EVENT_COMMIT:

            ret_val = FileSelectPopup ( g_SN.strPath.strModemDatabasePath2, "*.*", "*.*",
                                   "Open Modem Database ...", VAL_OK_BUTTON,
                                    KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strModemDatabasePath2 ); 

			if ( VAL_NO_FILE_SELECTED != ret_val)
			{
				UpdateModemDatabasePath_2 ( KAL_TRUE ); // update UI     
				ResetNvram2UpdateFlag();
			}
			break;
		}
	return 0;
}

//--------------------------------------------------------------------------------  
int CVICALLBACK AP_Database_Select_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int ret_val;
	switch (event)
    {
		case EVENT_COMMIT:

			 ret_val = FileSelectPopup ( g_SN.strPath.strAPDatabasePath, "*.*", "*.*",
                                   "Open AP Database(for TK6515 AP) ...", VAL_OK_BUTTON,
                                    KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strAPDatabasePath ); 

			if ( VAL_NO_FILE_SELECTED != ret_val)
			{
			 	UpdateAPDatabasePath ( KAL_TRUE ); // update UI    

			 	ResetAPNvramUpdateFlag ();
			}
			break;
    }
	return 0;
}


//--------------------------------------------------------------------------------  
int CVICALLBACK TargetSelect_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:

			UpdateTargetType ( KAL_FALSE );
			UpdateMenuTarget ( KAL_TRUE, 0 );
			break;
    }
	return 0;
}

//--------------------------------------------------------------------------------  
int CVICALLBACK COMPORT_Select_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:

			//GetComPortDynamiclly();
			UpdateCOMPort ( KAL_FALSE );
			//UpdateMenuCom ( KAL_TRUE, 0 );
			
			break;
    }
	return 0;
}

int CVICALLBACK CheckSum_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:
			
			UpdateCheckSum ( KAL_FALSE );
			UpdateMenuIMEICheckSum ( KAL_TRUE );
			break;
    }
	return 0;
}

//--------------------------------------------------------------------------------  
int CVICALLBACK data_call_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateDataCall(KAL_FALSE);
			   ///AccompanyActionWithDataCall();
			   
		        
                      
			break;
    }
	return 0;
}

//AMRSet_Click
//-----------------------------------------------------------------------
int CVICALLBACK AMRSet_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:

			UpdateAMR( KAL_FALSE );
			// AccompanyActionWithAMR();
			
			break;
    }
	return 0;
}

int  CVICALLBACK SDS_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    	switch (event)
    {
		case EVENT_COMMIT:

			UpdateSDS( KAL_FALSE );
			// AccompanyActionWithAMR();
			
			break;
    }
	return 0;
}






int CVICALLBACK set_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateSet(KAL_FALSE);
			   //AccompanyActionWithSet();
			   
		        
                      
			break;
    }
	return 0;
}

int CVICALLBACK clear_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateClear(KAL_FALSE);
			   AccompanyActionWithClear();
			   
		        
                      
			break;
    }
	return 0;
}

int CVICALLBACK Data_prefer_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateDataprefer(KAL_FALSE);
			   AccompanyActionWithData();
			   
		        
                      
			break;
    }
	return 0;
}

int CVICALLBACK Call_prefer_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateCallprefer(KAL_FALSE);
			   AccompanyActionWithCall();
			   
		        
                      
			break;
    }
	return 0;
}

int CVICALLBACK Set_AMR_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateSetAMR(KAL_FALSE);
			   AccompanyActionWithSetAMR();
			   
		        
                      
			break;
    }
	return 0;
}


int CVICALLBACK Clear_AMR_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_COMMIT:
			   UpdateClearAMR(KAL_FALSE);
			   AccompanyActionWithClearAMR();
			   
		        
                      
			break;
    }
	return 0;
}



int CVICALLBACK Combine_Ok_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:
			   HidePanel ( panel ); 
			  // UpdateSet(KAL_FALSE);
			   //AccompanyActionWithSet();
			   
		        
                      
			break;
    }
	return 0;
}

int CVICALLBACK Combine_Cancel_click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:
			   HidePanel ( panel ); 
			  // UpdateSet(KAL_FALSE);
			   //AccompanyActionWithSet();
			   
		        
                      
			break;
    }
	return 0;
}



//--------------------------------------------------------------------------------  
int CVICALLBACK About_Quit_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:
			HidePanel ( panel );  
			break;
    }
	return 0;
}

int CVICALLBACK TimerOut_Callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_TIMER_TICK:

			SetTimeOutFlag ( KAL_TRUE );
			break;
    }
	return 0;
}

void SetStartButton_Disable(kal_bool bEnable)
{
	SetCtrlAttribute ( panelHandle_main, panelMain_START_WRITE, ATTR_DIMMED, bEnable );  
}

void CVICALLBACK MenuCOMChanged (int menuBarHandle, int menuItemID, void *callbackData, int panelHandle)
{
	int i = 0;
	for(;i <= ComPortCount; i++)	  // the usb vcom is MenuItemID[ComPortCount]
	{
		if(MenuItemID[i] != menuItemID)
		{
			SetMenuBarAttribute( menuBarHandle, MenuItemID[i], ATTR_CHECKED, KAL_FALSE);
		}
		else
		{
			SetCtrlIndex(panelHandle_main, panelMain_eCOMPort, i);   // update UI
			SetMenuBarAttribute( menuBarHandle, menuItemID, ATTR_CHECKED, KAL_TRUE);
			GetCtrlVal( panelHandle_main, panelMain_eCOMPort, (kal_int32*) &g_SN.tCommPort.eComPort ); // must set eCOMPort first
		}
	}
}
int GetComPortDynamiclly(void)
{
	char DestString[10]; 
	int i = 0, result = 0;
	char find_ini_comport = -1;

	if(panelHandle_main < 0 || menuHandle < 0)
	{
		MessagePopup("Error","Load main panel fail");
		return SYSTEM_ERROR;
	}
	ClearListCtrl(panelHandle_main,panelMain_eCOMPort); 					 // clear the com port value
	InsertListItem(panelHandle_main,panelMain_eCOMPort,0,"USB VCOM",17);	 // insert the usb com first
	if(ComPortCount == 255)
	{
		TempMenuID = NewSubMenu(menuHandle,menuMain_Option_COMM);   // treat ComPortArray[254] as a temp menuitem id 
	}
	ComPortCount = 255;
	result = ComPortEnumerate(ComPortArray, &ComPortCount);
	if(result != COM_ENUM_OK)
	{
		if( result == COM_ENUM_NO_COM_PORT_FOUND)                            // find no COM port, some NB will have no COM.
		{
			ComPortCount = 0;
		}
		else
		{
			MessagePopup("FAIL","Get Com Port Fail");
			return result;
		}
	}
	
	if(ComPortCount < 1 || ComPortCount >= MAX_COMPORT_COUNT)
	{
		//MessagePopup("FAIL","Total Com Port Count Fail");
		char tmpStrLog[256] = {0};
		sprintf(tmpStrLog, "Warning: Current PC without any comport!");
		UpdateLog(tmpStrLog, 10);
		return COM_ENUM_ERROR;
	}
	
	for(i = 0; i < ComPortCount; i++)	// show all com port got dynamiclly
	{	 

		if(find_ini_comport < 0)
		{
			if(g_SN.tCommPort.eComPort == ComPortArray[i])
			{
				find_ini_comport = i;
			}
		}
		sprintf(DestString,"COM%d",ComPortArray[ComPortCount - i - 1]);
		InsertListItem(panelHandle_main,panelMain_eCOMPort,0,DestString,ComPortArray[ComPortCount - i - 1]);  // update UI COM list
		sprintf(DestString,"COM%d",ComPortArray[i]);
		MenuItemID[i] = NewMenuItem(menuHandle,TempMenuID,DestString,-1,0,MenuCOMChanged,0);	// update menu COM list
	}
	MenuItemID[ComPortCount] = NewMenuItem(menuHandle,TempMenuID,"USB VCOM",-1,0,MenuCOMChanged,0);  // update menu COM list

	if(ComPortCount > 0)
	{
		if(find_ini_comport <0) // if the ini defined com port doesn't exsit. display the last com port before USB vcom
		{
			SetMenuBarAttribute ( menuHandle, MenuItemID[ComPortCount - 1], ATTR_CHECKED, KAL_TRUE); // set the com port which just before USB VCOM to display 
			SetCtrlIndex(panelHandle_main, panelMain_eCOMPort, ComPortCount - 1); // set the com port which just before USB VCOM to display
		}else // if the ini defined com port already exsit, display it
		{
			SetMenuBarAttribute ( menuHandle, MenuItemID[find_ini_comport], ATTR_CHECKED, KAL_TRUE); // set the com port which just before USB VCOM to display 
			SetCtrlIndex(panelHandle_main, panelMain_eCOMPort, find_ini_comport); // set the com port which just before USB VCOM to display
		}
	}else if(ComPortCount == 0) // if no com port, then display the USB Vcom.
	{
		SetMenuBarAttribute ( menuHandle, MenuItemID[ComPortCount], ATTR_CHECKED, KAL_TRUE); // set the com port which just before USB VCOM to display 
		SetCtrlIndex(panelHandle_main, panelMain_eCOMPort, ComPortCount); // set the com port which just before USB VCOM to display
	}
	
	UpdateCOMPort (KAL_FALSE);
	return result;
}
//--------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
///////////////////////////    main()     ///////////////////////////////////
//---------------------------------------------------------------------------------
//==================================================================================
int main (int argc, char *argv[])
{
	/*-------------------------load ui-----------------------------*/
    g_IsEngineer = KAL_TRUE;
	if(read_EngineerPasswd(g_passwordVal) != S_DES_SUCCESS)
	{
		return -1;
	}
	else
	{ 
	    memcpy(g_oldpasswordVal, g_passwordVal,strlen(g_passwordVal));
	}
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	
	if (( panelHandle_main = LoadPanel (0, "SN_STATION.uir", panelMain )) < 0)
		return -1;
	
    if (( panelHandle_about = LoadPanel (0, "SN_STATION.uir", panelAbout )) < 0)
		return -1;	

	if (( panelHandle_imei = LoadPanel (0, "SN_STATION.uir", panelIMEI )) < 0)
		return -1;	
	
	if((panelHandle_combine = LoadPanel (0, "SN_STATION.uir", Combine)) < 0)
		return -1;
	
	if (( panelHandle_OperateCfg = LoadPanel (0, "SN_STATION.uir", panelCfg )) < 0)
		return -1;

	if ((panelHandle_CodeScan = LoadPanel (0, "SN_STATION.uir", PANEL)) < 0)
		return -1;

    if (( panelHandle_PanelEngin= LoadPanel (0, "SN_STATION.uir", PanelEngin)) < 0)
		return -1;

	if (( panelHandle_PanelChgpw= LoadPanel (0, "SN_STATION.uir", PanelChgpw)) < 0)
		return -1;

    g_passwordICtrlID          =       PasswordCtrl_ConvertFromString (panelHandle_PanelEngin, 
                                                        PanelEngin_Password); 
	g_oldpasswordICtrlID      =       PasswordCtrl_ConvertFromString (panelHandle_PanelChgpw, 
                                                        PanelChgpw_OldPassword);
    g_newpasswordICtrlID      =       PasswordCtrl_ConvertFromString (panelHandle_PanelChgpw, 
                                                        PanelChgpw_NewPassword);
    g_confirmpasswordICtrlID  =       PasswordCtrl_ConvertFromString (panelHandle_PanelChgpw, 
                                                        PanelChgpw_ConfirmPassword);
	
	menuHandle = GetPanelMenuBar ( panelHandle_main );
	/*-------------------------------------------------------------*/
	
	
	/*-------------------------------------------------------------*/
	//----------------------------------------------------
	ContextInit ();
		
	//Get g_SN configration from setup.txt file
	GetParaFromIni();//

	GetComPortDynamiclly();//????????????????????
	
	//Update UI from g_SN
	UpdateUIComponent ( KAL_TRUE );
			
	UIDimmedComponent ();//update UI if dimmed or not 

    DisplayPanel (panelHandle_main);
   
	
	//nit Thread pool
	InitThreadPool ( THREAD_NUM_MAX );

	MetaContextInit ();

	RunUserInterface ();
	
	MetaContextDeInit ();
	//Deinit Thread pool
	DeInitThreadPool ();  
	
	//Update g_SN from UI--->keep when next open
	UpdateUIComponent( KAL_FALSE );

	//Save to ini file
	SaveParaToIni();

	//----------------------------------------------------
	ContextDeInit ();

	/*-------------------------------------------------------------*/
	DiscardPanel ( panelHandle_main );
	DiscardPanel ( panelHandle_about );
	DiscardPanel ( panelHandle_imei );
	DiscardPanel ( panelHandle_OperateCfg);
	 
	return 0;
}

//-------------------------------------------------------------------------------- 
int  CVICALLBACK System_Config_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
//   	if (( panelHandle_OperateCfg = LoadPanel (0, "SN_STATION.uir", panelCfg )) < 0)
//		return -1;
	
	switch (event) {
		//case EVENT_COMMIT:
	   case EVENT_LEFT_CLICK:
	
       SetStartButton_Disable ( KAL_TRUE );
	   DimmedMenuItem(KAL_TRUE);
	   
		 
	   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bIMEI, ATTR_DIMMED, KAL_FALSE);
	   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bBarCode, ATTR_DIMMED, KAL_FALSE );
	   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bBT, ATTR_DIMMED, KAL_FALSE );
	   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bWIFIMacadr, ATTR_DIMMED, KAL_FALSE );
	   if(g_pWriteOption->bWriteIMEI)
	   {
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckSum, ATTR_DIMMED, KAL_FALSE);
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bDualIMEI, ATTR_DIMMED, KAL_FALSE);
		   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_FALSE);	   
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, ATTR_DIMMED, KAL_FALSE);
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bFourIMEI, ATTR_DIMMED, KAL_FALSE);
	   }
	   else
	   {
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckSum, ATTR_DIMMED, KAL_TRUE);
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bDualIMEI, ATTR_DIMMED, KAL_TRUE);
		   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
		   SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, ATTR_DIMMED, KAL_TRUE);
	       SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bFourIMEI, ATTR_DIMMED, KAL_TRUE);
	   }
	   UpdateHeadInfo(KAL_TRUE);
	   DimmedCfgUI_TargetSelect();
	   DisplayPanel ( panelHandle_OperateCfg);       
	
       break;
    }
	return 0;

}

static E_INPUTBOX_STATUS eInputBoxRun;

E_INPUTBOX_STATUS InputBoxPopup (kal_uint8* strTitle, kal_uint8* strText, kal_int8* buffer, kal_uint16 iMaxLength ){
 
	eInputBoxRun = RUN_STATUS;


	SetStartButton_Disable ( KAL_TRUE );
	
	if ((panelHandle_Input = LoadPanel (0, "SN_STATION.uir", panelInput)) < 0)
		return CANCEL_STATUS;	

			
	SetPanelAttribute ( panelHandle_Input, ATTR_TITLE, strTitle );
	
	SetActiveCtrl ( panelHandle_Input, panelInput_mInputBox );
		
	SetCtrlAttribute ( panelHandle_Input, panelInput_mInputBox, ATTR_LABEL_TEXT, strText );
	SetCtrlAttribute ( panelHandle_Input, panelInput_mInputBox, ATTR_MAX_ENTRY_LENGTH, iMaxLength );
	SetCtrlAttribute ( panelHandle_Input, panelInput_mInputBox, ATTR_CTRL_VAL, "" );

	DisplayPanel ( panelHandle_Input );

	while ( !eInputBoxRun ) {
	
          ProcessSystemEvents ();

	}
		
	GetCtrlAttribute ( panelHandle_Input, panelInput_mInputBox, ATTR_CTRL_VAL, buffer );

	HidePanel ( panelHandle_Input );
	
	DiscardPanel ( panelHandle_Input );
	
	SetStartButton_Disable ( KAL_FALSE );

	return eInputBoxRun;

};
//-------------------------------------------------------------------------------- 
int CVICALLBACK Enter_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:  
			eInputBoxRun = OK_STATUS;
			break;
    }
	return 0;
}

//-------------------------------------------------------------------------------- 
int CVICALLBACK Cancel_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:

			eInputBoxRun = CANCEL_STATUS;
			break;
    }
    
	return 0;
}
//-------------------------------------------------------------------------------- 
int CVICALLBACK InputBox_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	kal_uint16 tmp;
	switch (event) {
		case EVENT_COMMIT:
			        eInputBoxRun = OK_STATUS;
			break;
    }
	return 0;
}
//-------------------------------------------------------------------------------- 
int CVICALLBACK Imei_SvnPad_Cancel_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:
		    
                        HidePanel ( panel );  
			break;
    }
	return 0;
}






//-------------------------------------------------------------------------------- 
int CVICALLBACK Imei_SvnPad_OK_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) 
{
	switch (event)
    {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:
		
			UpdateImeiSvnPad ( KAL_FALSE );
			
		    HidePanel ( panel );  
			break;
    }
	return 0;
}
//-------------------------------------------------------------------------------- 

void CVICALLBACK menu_RefreshCOMPort_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	int i;
	for(i = 0; i <= ComPortCount; i++ )
	{
		DiscardMenuItem(menubar,MenuItemID[i]);
	}
	GetComPortDynamiclly();
}
void CVICALLBACK menu_SVNPAD_Setting_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	DisplayPanel ( panelHandle_imei );
	UpdateImeiSvnPad ( KAL_TRUE );	
}

//--------------------------------------------------------------------------------
void CVICALLBACK menu_EnableLog_Click (int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMetaLog ( KAL_FALSE );	
	UpdateMetaLog ( KAL_TRUE );
}
//--------------------------------------------------------------------------------
void CVICALLBACK menu_ClearCountLog_Click (int menubar, int menuItem, void *callbackData, int panel)
{
}

//--------------------------------------------------------------------------------  
void CVICALLBACK menu_Modem_Database_Select_Click (int menubar, int menuItem, void *callbackData, int panel)
{
	int ret_val;
	ret_val = FileSelectPopup ( g_SN.strPath.strModemDatabasePath, "*.*", "*.*",
                     "Open Modem Database ...", VAL_OK_BUTTON,
                     KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strModemDatabasePath ); 
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
		UpdateModemDatabasePath ( KAL_TRUE ); // update UI     
		//NvramDatabaseInit ();
		ResetNvramUpdateFlag();
	}
}
//-------------------------------------------------------------------------------- 

void CVICALLBACK menu_Modem2_Database_Select_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	int ret_val;
	ret_val = FileSelectPopup ( g_SN.strPath.strModemDatabasePath2, "*.*", "*.*",
						 "Open Modem Database ...", VAL_OK_BUTTON,
						 KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strModemDatabasePath2 ); 
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
			UpdateModemDatabasePath_2( KAL_TRUE ); // update UI	   
			//NvramDatabaseInit ();
			ResetNvram2UpdateFlag();
	}

}

void CVICALLBACK menu_AP_Database_Select_Click (int menubar, int menuItem, void *callbackData, int panel)
{
	int ret_val;
	ret_val = FileSelectPopup ( g_SN.strPath.strAPDatabasePath, "*.*", "*.*",
                     "Open AP Database(for TK6515 AP) ...", VAL_OK_BUTTON,
                     KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strAPDatabasePath ); 
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
		UpdateAPDatabasePath ( KAL_TRUE ); // update UI    
	    //APNvramDatabaseInit ();
	    ResetAPNvramUpdateFlag();
	}
}
//--------------------------------------------------------------------------------  
void CVICALLBACK menu_Authen_File_Select_Click (int menubar, int menuItem, void *callbackData, int panel)
{
	int ret_val;
	ret_val = FileSelectPopup ( g_SN.strPath.strAuthFilePath, "*.auth", "*.auth",
                      "Open Authentication File...", VAL_OK_BUTTON,
                      KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strAuthFilePath ); 
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
//		UpdateAuthFilePath ( KAL_TRUE ); // update UI   
		AuthInit (); 
	}
	
	BootROMUSBDetection = 1 ;//change6.5
}


void CVICALLBACK menu_SpAuthen_File_Select_Click (int menubar, int menuItem, void *callbackData, int panel)
{
	int ret_val;
	ret_val = FileSelectPopup ( g_SN.strPath.strspAuthFilePath, "*.auth", "*.auth",
                      "Open Authentication File...", VAL_OK_BUTTON,
                      KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strspAuthFilePath ); 
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
//	      UpdateAuthFilePath ( KAL_TRUE ); // update UI 
		  SpAuthInit (); 
	}
	
	BootROMUSBDetection = 1 ;//change6.5
}
void CVICALLBACK menu_SpSecuen_File_Select_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	int ret_val;
	/*
	ret_val = FileSelectPopup ( g_SN.strPath.strspSecureFilePath, "*.auth", "*.auth",
                      "Open Authentication File...", VAL_OK_BUTTON,
                      KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strspSecureFilePath); 
       
       
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
              //UpdateAuthFilePath ( KAL_TRUE ); // update UI 
		  SpSecuInit (); 
	}
	*/

	ret_val = FileSelectPopup ( g_SN.strPath.strspAuthFilePath, "*.auth", "*.auth",
                      "Open Authentication File...", VAL_OK_BUTTON,
                      KAL_FALSE, KAL_FALSE, KAL_TRUE, KAL_TRUE, g_SN.strPath.strspAuthFilePath ); 
	if ( VAL_NO_FILE_SELECTED != ret_val)
	{
//	      UpdateAuthFilePath ( KAL_TRUE ); // update UI 
		  SpAuthInit (); 
	}
	
	BootROMUSBDetection = 1 ;//change6.5
}	
void CVICALLBACK menu_Hdcp_BinFile_Select(int menubar, int menuItem, void *callbackData, int panel)
{
/*
	switch (event)
		{
		case EVENT_COMMIT:
			if (DirSelectPopup("c:\\Program Files\\MTK_SN_Write_tool", "Select HDCP Key File Directory", 1, 1, HdcpKeyFilePath) != 1)
        	{
            	return 0;
        	}
        	SetCtrlVal(panel, panelMain_strHdcp_Key, HdcpKeyFilePath);
			break;
		}
	return 0;
	*/
	if (DirSelectPopup("c:\\Program Files\\MTK_SN_Write_tool", "Select HDCP Key File Directory", 1, 1, HdcpKeyFilePath) != 1)
		{
			return ;
		}			
//		SetMenuBarAttribute ( menuHandle, menuMain_File_HdcpBinFile, ATTR_CHECKED,HdcpKeyFilePath);
//		ResetHDCPUpdateFlag();
}
void CVICALLBACK menu_DRM_Key_File_Select(int menubar, int menuItem, void *callbackData, int panel)
{
   if (DirSelectPopup("c:\\Program Files\\MTK_SN_Write_tool", "Select HDCP Key File Directory", 1, 1, DRMKeyFilePath) != 1)
		{
			return ;
		}			
//		SetMenuBarAttribute ( menuHandle, menuMain_File_DRMKeyFile, ATTR_CHECKED,DRMKeyFilePath);
//		ResetDRMKeyUpdateFlag();
}
//--------------------------------------------------------------------------------  
void CVICALLBACK menu_Exit_Click (int menubar, int menuItem, void *callbackData, int panel)
{
	SetBootStopFlag ( KAL_TRUE ); 
	QuitUserInterface (0);
}

//--------------------------------------------------------------------------------  
void CVICALLBACK menu_BBAutoDetect_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuBBChip ( KAL_FALSE );
}

void CVICALLBACK menu_COMPORT_Select_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuCom ( KAL_FALSE, menuItem );
	UpdateMenuCom ( KAL_TRUE, menuItem );
	UpdateCOMPort ( KAL_TRUE );
}
//-----------------------------------------------------------------
void CVICALLBACK menu_Baud_Rate_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuBaudRate ( KAL_FALSE, menuItem );
	UpdateMenuBaudRate ( KAL_TRUE, menuItem );
//	UpdateBaudRate ( KAL_TRUE );

}
//----------------------------------------------------------------------------------
void CVICALLBACK menu_TargetSelect_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuTarget ( KAL_FALSE, menuItem );
	UpdateMenuTarget ( KAL_TRUE, menuItem );
	UpdateTargetType ( KAL_TRUE );
}

//-------------------------------------------------------------------------------
void CVICALLBACK menu_Write_Mode_Selection_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuMode ( KAL_FALSE, menuItem );
	UpdateMenuMode ( KAL_TRUE, menuItem );
//	UpdateModeType ( KAL_TRUE );
}
//------------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void CVICALLBACK menu_BT_Chip_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuBTChip ( KAL_FALSE, menuItem );
	UpdateMenuBTChip ( KAL_TRUE, menuItem );
}
void CVICALLBACK menu_BT_Power_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuBTPowerOn ( KAL_FALSE, menuItem );
	UpdateMenuBTPowerOn ( KAL_TRUE, menuItem );
}


//--------------------------------add by mtk71596-----------------------------------------

void CVICALLBACK menu_IMEI_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuIMEI( KAL_FALSE );
	UpdateMenuIMEI ( KAL_TRUE );
	UpdateIMEI( KAL_TRUE );
}
void CVICALLBACK menu_Barcode_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuBarCode ( KAL_FALSE );
	UpdateMenuBarCode ( KAL_TRUE );
	UpdateBarCode( KAL_TRUE );

}
void CVICALLBACK menu_BTAddr_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuBT( KAL_FALSE );
	UpdateMenuBT ( KAL_TRUE );
	UpdateBT( KAL_TRUE );

}
void CVICALLBACK menu_WIFI_Mac_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuWIFI( KAL_FALSE );
	UpdateMenuWIFI ( KAL_TRUE );
	UpdateWIFIMacadr( KAL_TRUE );
	  
}
void CVICALLBACK menu_HDCP_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuHDCP ( KAL_FALSE);
	UpdateMenuHDCP ( KAL_TRUE);
//	UpdateHDCP ( KAL_TRUE );

}


void CVICALLBACK menu_DRMKey_Click(int menubar, int menuItem, void *callbackData, int panel)

{
	UpdateMenuDRM_Key_Install( KAL_FALSE );
	UpdateMenuDRM_Key_Install ( KAL_TRUE );
}

//----------------------------------------------------------------------------------------------








void CVICALLBACK Menu_Check_Sum_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuIMEICheckSum ( KAL_FALSE );
	UpdateMenuIMEICheckSum ( KAL_TRUE );
	UpdateCheckSum ( KAL_TRUE );
}

//mtk71409 by JiXiang
void  CVICALLBACK menu_NoBattery_Click(int menubar, int menuItem, void *callbackData, int panel)
{

	UpdateMenuEnMetaWithoutBattery( KAL_FALSE);
	UpdateMenuEnMetaWithoutBattery( KAL_TRUE);
	
}


//MTK71409 by JiXiang
void  CVICALLBACK menu_DualTalk_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuEnDualTalk( KAL_FALSE);	
	UpdateMenuEnDualTalk( KAL_TRUE);
}
//add by MTK71262 
void  CVICALLBACK menu_ATSDS_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	
	UpdateMenuSDS( KAL_FALSE);
	UpdateMenuSDS( KAL_TRUE);
		
}

void CVICALLBACK menu_Datacard_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{
    UpdateMenuEnDatacard(KAL_FALSE);
	UpdateMenuEnDatacard(KAL_TRUE);
}

void CVICALLBACK SP_Securre_USB_Click(int menubar, int menuItem, void *callbackData, int panel)
{
    UpdateMenuSecurreUSB(KAL_FALSE);
	UpdateMenuSecurreUSB(KAL_TRUE);
}



void CVICALLBACK menu_Dual_IMEI_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuDualIMEI ( KAL_FALSE );
	UpdateMenuDualIMEI ( KAL_TRUE );
}

void CVICALLBACK menu_ThreeIMEI_Click (int menuBar, int menuItem, void *callbackData, int panel)
{
    UpdateMenuThreeIMEI ( KAL_FALSE );
	UpdateMenuThreeIMEI ( KAL_TRUE );
}

void CVICALLBACK menu_FoutIMEI_Click (int menuBar, int menuItem, void *callbackData, int panel)
{
    UpdateMenuFourIMEI ( KAL_FALSE );
	UpdateMenuFourIMEI ( KAL_TRUE );
}

void CVICALLBACK menu_FT_Status_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuFTStatusCheck ( KAL_FALSE );
	UpdateMenuFTStatusCheck ( KAL_TRUE );
}


void CVICALLBACK menu_Lock_IMEI_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	UpdateMenuIMEILock ( KAL_FALSE );
	UpdateMenuIMEILock ( KAL_TRUE );
}

void CVICALLBACK menu_About_Click(int menubar, int menuItem, void *callbackData, int panel)
{
	DisplayPanel ( panelHandle_about );
}

int CVICALLBACK Timer2Out_Callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {

    ProcessDrawEvents ();	
	switch (event) {
		case EVENT_TIMER_TICK:
			
            UpdateProgress ();
            break;
    }
    ProcessDrawEvents ();
	return 0;
}




//------------------ panel Dual Imei input --------------------------------
E_INPUTBOX_STATUS InputBoxRun;

int  CVICALLBACK Cfg_OK_Click(int panel, int control, int event, 
	                       void *callbackData, int eventData1, int eventData2)
{
  switch (event) {
	//	case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:

            ResetDatabaseInitFlag();
			GetIMEInums();
		    UpdateHeadInfo(KAL_FALSE);
			DimmedMenuItem(KAL_FALSE);
            HidePanel ( panel );  
              
			break;
    }
    SetStartButton_Disable ( KAL_FALSE);
	return 0;
}


//-------------------add by mtk71596-----------------------------------

int  CVICALLBACK Cancel_Key_Click(int panel, int control, int event, 
                          void *callbackData, int eventData1, int eventData2)
{
	switch (event) {
		//case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:
		    
            HidePanel ( panel );  
			InputBoxRun = CANCEL_STATUS;
			break;
    }
	return 0;
}

int  CVICALLBACK OK_Key_Click(int panel, int control, int event, 
	                void *callbackData, int eventData1, int eventData2)
{
  switch (event) {
	//	case EVENT_COMMIT:
		case EVENT_LEFT_CLICK:
                     
					 if(CheckAllScanData() != DataAllCorrect)
					 {
					    InputBoxRun = RUN_STATUS;
					 }
					 else
					 {					   					   
					    HidePanel ( panel );
					   InputBoxRun = OK_STATUS;
					 }	
					 
			break;
    }
	return 0;
}


 int  CVICALLBACK ScanDataEdit_EnterKeyPress(int panel, int control, int event, 
 	                      void *callbackData, int eventData1, int eventData2)
 {
    int nextControlID = 0;
	switch (event) {
		case EVENT_COMMIT:
            
			if(InputBoxRun == CANCEL_STATUS)
			{
				//HidePanel ( panel );  
				return KAL_FALSE;
			}
		
			
		    
			if(CheckCurrentScanData(control) == DataAllCorrect)
			{
			     nextControlID = GetNextScanControlID(control);
				 SetActiveCtrl(panel, nextControlID);
			}

			
			if(nextControlID == PANEL_OK /*|| (control + 1) == PANEL_OK*/)//The last scan data
			{
			    if(CheckAllScanData() == DataAllCorrect)
			    {
				     HidePanel ( panel );  
				    InputBoxRun = OK_STATUS;
			    }
				else
				{
				    SetActiveCtrl(panel, g_realScanOrderID[0]);
				}
			}
			
			

			break;
    }
	return 0;
}
 		                         	
E_INPUTBOX_STATUS DisplayCodeScanner(void)
{
    int FirstHighLightID = 0;
	char strTmp[1024];
	
	ResetScanItem();
	
	if ((panelHandle_CodeScan = LoadPanel (0, "SN_STATION.uir", PANEL)) < 0)
		return CANCEL_STATUS;
	
	InputBoxRun = RUN_STATUS;
	SetStartButton_Disable ( KAL_TRUE );

    
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FirstIMEI, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_SecondIMEI, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_ThirdIMEI, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FourthIMEI, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_IDBarCode, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_IDBT, ATTR_DIMMED, KAL_TRUE );
	SetCtrlAttribute ( panelHandle_CodeScan, PANEL_IDWIFI, ATTR_DIMMED, KAL_TRUE );
	SetCtrlVal(panelHandle_CodeScan, PANEL_FirstIMEI, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_SecondIMEI, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_ThirdIMEI, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_FourthIMEI, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_IDBarCode, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_IDBT, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_IDWIFI, "");

	SetCtrlVal(panelHandle_CodeScan, PANEL_strBarcHead, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_strImei1Head, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_strImei2Head, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_strImei3Head, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_strImei4Head, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_strBThead, "");
	SetCtrlVal(panelHandle_CodeScan, PANEL_strWifiHead, "");

    FirstHighLightID = g_realScanOrderID[0];
    HighLightCurrentScanData(FirstHighLightID);
	
	if(g_pWriteOption->bWriteIMEI)
		{
		   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FirstIMEI, ATTR_DIMMED, KAL_FALSE);
		   if(g_HeadInfo.bCheckIMEI_1)
		   {
		       SetCtrlVal(panelHandle_CodeScan, PANEL_strImei1Head, g_HeadInfo.IMEI_1);
		   }
		   
		  if(g_SN.tIMEI.bDualIMEI == KAL_TRUE && g_SN.tIMEI.bDualIMEISame == KAL_FALSE)
		  	{
		  	   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_SecondIMEI, ATTR_DIMMED, KAL_FALSE);
			   if(g_HeadInfo.bCheckIMEI_2)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strImei2Head, g_HeadInfo.IMEI_2);
		       }
			   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_ThirdIMEI, ATTR_DIMMED, KAL_TRUE);
			   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FourthIMEI, ATTR_DIMMED, KAL_TRUE);
		  	}
		  else if(g_SN.tIMEI.bThreeIMEI == KAL_TRUE)
		  	{
		  	   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_SecondIMEI, ATTR_DIMMED, KAL_FALSE);
		  	   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_ThirdIMEI, ATTR_DIMMED, KAL_FALSE);
			   if(g_HeadInfo.bCheckIMEI_2)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strImei2Head, g_HeadInfo.IMEI_2);
		       }
			   
			   if(g_HeadInfo.bCheckIMEI_3)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strImei3Head, g_HeadInfo.IMEI_3);
		       }
			   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FourthIMEI, ATTR_DIMMED, KAL_TRUE); 
		  	}
		  else if(g_SN.tIMEI.bFourIMEI == KAL_TRUE)
		  	{
		  	   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_SecondIMEI, ATTR_DIMMED, KAL_FALSE);
		  	   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_ThirdIMEI, ATTR_DIMMED, KAL_FALSE);
			   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FourthIMEI, ATTR_DIMMED, KAL_FALSE);
			   if(g_HeadInfo.bCheckIMEI_2)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strImei2Head, g_HeadInfo.IMEI_2);
		       }
			   
			   if(g_HeadInfo.bCheckIMEI_3)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strImei3Head, g_HeadInfo.IMEI_3);
		       }

			   if(g_HeadInfo.bCheckIMEI_4)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strImei4Head, g_HeadInfo.IMEI_4);
		       }
		  	}
		  else
		  	{
		  	    SetCtrlAttribute ( panelHandle_CodeScan, PANEL_SecondIMEI, ATTR_DIMMED, KAL_TRUE);
		  	    SetCtrlAttribute ( panelHandle_CodeScan, PANEL_ThirdIMEI, ATTR_DIMMED, KAL_TRUE);
			    SetCtrlAttribute ( panelHandle_CodeScan, PANEL_FourthIMEI, ATTR_DIMMED, KAL_TRUE);
		  	}
		}
		
	if(g_pWriteOption->bWriteBarcode)
		{
		   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_IDBarCode, ATTR_DIMMED, KAL_FALSE); 
		   if(g_HeadInfo.bCheckBarcode)
		   {
		        SetCtrlVal(panelHandle_CodeScan, PANEL_strBarcHead, g_HeadInfo.Barcode);
		   }
		}
	if(g_pWriteOption->bWriteBT)
		{
		   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_IDBT, ATTR_DIMMED, KAL_FALSE); 
		   if(g_HeadInfo.bCheckBT)
		       {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strBThead, g_HeadInfo.BT);
		       }
		}
	if(g_pWriteOption->bWriteWIFI)
		{
		   
		   SetCtrlAttribute ( panelHandle_CodeScan, PANEL_IDWIFI, ATTR_DIMMED, KAL_FALSE); 
		   if(g_HeadInfo.bCheckWIFI)
		   {
		           SetCtrlVal(panelHandle_CodeScan, PANEL_strWifiHead, g_HeadInfo.WIFI);
		   }
		}
		
	DisplayPanel(panelHandle_CodeScan);

	while ( !InputBoxRun ) {
	      
          ProcessSystemEvents ();

	}
	HidePanel ( panelHandle_CodeScan );
	
	DiscardPanel ( panelHandle_CodeScan );
	
	SetStartButton_Disable ( KAL_FALSE );
	return InputBoxRun;
}

//---------------------------------------------------------------------



void CVICALLBACK menu_Operator_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{
}

void CVICALLBACK menu_Engineer_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{
}

void CVICALLBACK menu_SwitchToEngineer_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{  
      
	  SetPassword(panelHandle_PanelEngin, g_passwordICtrlID, "");
      DisplayPanel(panelHandle_PanelEngin);
	  
}

void CVICALLBACK menu_ChangePasswd_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{
    //g_CheckStatus = E_Check_Running;
    g_IsCheckOldpwDone = KAL_FALSE;
    SetPassword(panelHandle_PanelChgpw, g_oldpasswordICtrlID, "");
	SetPassword(panelHandle_PanelChgpw, g_newpasswordICtrlID, "");
	SetPassword(panelHandle_PanelChgpw, g_confirmpasswordICtrlID, "");
	SetActiveCtrl ( panelHandle_PanelChgpw, PanelChgpw_OldPassword );
    DisplayPanel(panelHandle_PanelChgpw);    
}

void CVICALLBACK menu_SwitchToOperator_Click (int menuBar, int menuItem, void *callbackData,
		int panel)
{
     EngineerSwitchToOperator();
}


int CVICALLBACK IdenttityCheckCancel_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            HidePanel(panelHandle_PanelEngin);
			break;
		}
	return 0;
}

int CVICALLBACK IdentityCheckOK_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    
	kal_char	inputpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
	switch (event)
		{
		case EVENT_LEFT_CLICK:
            GetPassword(panelHandle_PanelEngin, g_passwordICtrlID, inputpasswordVal);			
			if(CheckIdentityPasswd(inputpasswordVal))
			{
			    OperatorSwitchToEngineer();
			    HidePanel(panelHandle_PanelEngin);
			}            
			else
			{
			    SetPassword(panelHandle_PanelEngin, g_passwordICtrlID, "");
				//SetCtrlAttribute ( panelHandle_PanelEngin, PanelEngin_Password, ATTR_CTRL_VAL, "" );
				SetActiveCtrl ( panelHandle_PanelEngin, PanelEngin_Password );
				
			}
			
			break;
		}
	return 0;
}


int CVICALLBACK ChgpasswdCancel_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			memset(g_passwordVal, 0, MAX_PASSWORD_LENGTH+1);
			memcpy(g_passwordVal,g_oldpasswordVal, strlen(g_oldpasswordVal));
			write_EngineerPasswd(g_passwordVal);
            HidePanel(panelHandle_PanelChgpw);
			break;
		}
	return 0;
}

int CVICALLBACK ChgpasswdOK_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    kal_char    oldpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
    kal_char    newpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
    kal_char    confirmpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
	
	if(g_IsCheckOldpwDone == KAL_TRUE)
	{
	    g_IsCheckOldpwDone =  KAL_FALSE;
		return 0;
	}
	else
	{
		GetPassword(panelHandle_PanelChgpw, g_oldpasswordICtrlID, oldpasswordVal);
		if(strlen(oldpasswordVal) <= 0)
		{
			return 0;
		}
	}
	
	switch (event)
		{

		case EVENT_LEFT_CLICK:
					
			if(CheckIdentityPasswd(oldpasswordVal))
			{
			    GetPassword(panelHandle_PanelChgpw, g_newpasswordICtrlID, newpasswordVal);
				GetPassword(panelHandle_PanelChgpw, g_confirmpasswordICtrlID, confirmpasswordVal);
			    if(ConfirmNewPassword(newpasswordVal, confirmpasswordVal) == KAL_TRUE)
			    {	
			        memset(g_passwordVal, 0, MAX_PASSWORD_LENGTH+1);
			        memcpy(g_passwordVal,confirmpasswordVal, strlen(confirmpasswordVal));
					memcpy(g_oldpasswordVal,confirmpasswordVal, strlen(confirmpasswordVal));
			        write_EngineerPasswd(g_passwordVal);
			        HidePanel(panelHandle_PanelChgpw);
			    }
				else
				{
				    //SetPassword(panelHandle_PanelChgpw, g_oldpasswordICtrlID, "");
					SetPassword(panelHandle_PanelChgpw, g_newpasswordICtrlID, "");
					SetPassword(panelHandle_PanelChgpw, g_confirmpasswordICtrlID, "");
					SetActiveCtrl ( panelHandle_PanelChgpw, PanelChgpw_NewPassword );
				}
			}
			else
			{			    
			    SetPassword(panelHandle_PanelChgpw, g_oldpasswordICtrlID, "");
				SetPassword(panelHandle_PanelChgpw, g_newpasswordICtrlID, "");
				SetPassword(panelHandle_PanelChgpw, g_confirmpasswordICtrlID, "");
				SetActiveCtrl ( panelHandle_PanelChgpw, PanelChgpw_OldPassword );
			}
			break;
		}
	return 0;
}

int CVICALLBACK CheckBarcHead_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateCheckBarCode(KAL_FALSE);
			break;
		}
	return 0;
}



int CVICALLBACK CheckBTHead_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateCheckBT(KAL_FALSE);
			break;
		}
	return 0;
}

int CVICALLBACK CheckWifiHead_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateCheckWIFI(KAL_FALSE);
			break;
		}
	return 0;
}

int CVICALLBACK PasswordCtrl_EnterPress (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    kal_char	inputpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
	switch (event)
		{
		case EVENT_COMMIT:

			GetPasswordFromCtrl(panel, control, inputpasswordVal);
			if(CheckIdentityPasswd(inputpasswordVal))
			{
				OperatorSwitchToEngineer();
			    HidePanel(panelHandle_PanelEngin); 
			}
			else
			{
				SetPassword(panelHandle_PanelEngin, g_passwordICtrlID, "");
				SetActiveCtrl ( panelHandle_PanelEngin, PanelEngin_Password );
			}
					
			break;
		}
	return 0;
}

int CVICALLBACK ChgPasswordCtrl_EnterPress (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    kal_char    oldpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
    kal_char    newpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
    kal_char    confirmpasswordVal[MAX_PASSWORD_LENGTH + 1] = {0};
	
	switch (event)
		{
		
		case EVENT_COMMIT:
          
            switch(control)
            	{
				
				case PanelChgpw_OldPassword:
					
					GetPasswordFromCtrl(panel, g_oldpasswordICtrlID, oldpasswordVal);
					if(0 == strcmp(g_passwordVal, oldpasswordVal))
					{				    
					    memcpy(g_oldpasswordVal,oldpasswordVal, strlen(oldpasswordVal));
					}
					/*
					else
					{
					      SetPassword(panel, g_oldpasswordICtrlID, "");
				          SetActiveCtrl ( panel, PanelChgpw_OldPassword );
					}
					
					SetActiveCtrl ( panel, PanelChgpw_NewPassword );
					*/
					SetActiveCtrl ( panel, PanelChgpw_NewPassword );
					break;
					
				case PanelChgpw_NewPassword:
					
					SetActiveCtrl ( panel, PanelChgpw_ConfirmPassword );					
					break;
					
				case PanelChgpw_ConfirmPassword:

                    //ChgpasswdOK_Click(panel, PanelChgpw_ChgpasswdOK, EVENT_LEFT_CLICK, NULL, 0, 0);
                    //HidePanel(panel);	
                    GetPasswordFromCtrl(panel, g_oldpasswordICtrlID, oldpasswordVal);
                    GetPassword(panelHandle_PanelChgpw, g_newpasswordICtrlID, newpasswordVal);
                    GetPassword(panelHandle_PanelChgpw, g_confirmpasswordICtrlID, confirmpasswordVal);
					if(CheckIdentityPasswd(oldpasswordVal))
					{
					    if(ConfirmNewPassword(newpasswordVal, confirmpasswordVal) == KAL_TRUE)
					    {
					         memset(g_passwordVal, 0, MAX_PASSWORD_LENGTH+1);
			                 memcpy(g_passwordVal,confirmpasswordVal, strlen(confirmpasswordVal));
						     write_EngineerPasswd(g_passwordVal);
					         HidePanel(panel);
					    }
						else
					     {
                             SetPassword(panel, g_newpasswordICtrlID, "");
					         SetPassword(panel, g_confirmpasswordICtrlID, "");
					         SetActiveCtrl ( panel, PanelChgpw_NewPassword );
					     }
					}
					else
					{
					    SetPassword(panel, g_oldpasswordICtrlID, "");
						SetPassword(panel, g_newpasswordICtrlID, "");
					    SetPassword(panel, g_confirmpasswordICtrlID, "");
				        SetActiveCtrl ( panel, PanelChgpw_OldPassword );
						//MessagePopup("Warning", "Incorrect engineer password!\nPlease try again!");
					}
					
					g_IsCheckOldpwDone = KAL_TRUE;
					break;
				
            	}
            	

			break;
		}
	return 0;
}

int CVICALLBACK CheckImei1Head_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateCheckIMEI_1(KAL_FALSE);
			break;
		}
	return 0;
}

int CVICALLBACK CheckImei2Head_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateCheckIMEI_2(KAL_FALSE);
			break;
		}
	return 0;
}

int CVICALLBACK CheckImei3Head_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			UpdateCheckIMEI_3(KAL_FALSE);
			break;
		}
	return 0;
}

int CVICALLBACK CheckImei4Head_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			UpdateCheckIMEI_4(KAL_FALSE);
			break;
		}
	return 0;
}

int CVICALLBACK DualIMEI_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
    {
		case EVENT_COMMIT:

			UpdateDualIMEI ( KAL_FALSE );
			UpdateMenuDualIMEI ( KAL_TRUE );
			if(g_pWriteOption->bWriteIMEI)
			{
				if(g_SN.tIMEI.bDualIMEI)
				{
				    g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
					g_SN.tIMEI.bFourIMEI = KAL_FALSE;
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, KAL_FALSE);
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bFourIMEI, KAL_FALSE);
					
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_FALSE);
									
				}
				else
				{				    
				     SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			         SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);	
			         SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);		
				}
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_TRUE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_TRUE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
				SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);	
			}
			break;
    }
	return 0;
}

int  CVICALLBACK DualImei_Same_Click(int panel, int control, int event, 
	     void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
		case EVENT_COMMIT:
			UpdateDualIMEISame ( KAL_FALSE );
			break;
    }
	return 0;
}

int CVICALLBACK ThreeIMEI_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateThreeIMEI ( KAL_FALSE );
			UpdateMenuThreeIMEI ( KAL_TRUE );
			if(g_pWriteOption->bWriteIMEI)
			{
				if(g_SN.tIMEI.bThreeIMEI)
				{
				    g_SN.tIMEI.bDualIMEI = KAL_FALSE;
					g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
					g_SN.tIMEI.bFourIMEI = KAL_FALSE;	
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bDualIMEI, KAL_FALSE);
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_DualImeiSame, KAL_FALSE);
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bFourIMEI, KAL_FALSE);
					
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_FALSE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
				}
				else
				{
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);	
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_TRUE);	
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
				}
			}
			break;
		}
	return 0;
}

int CVICALLBACK FourIMEI_Click (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
            UpdateFourIMEI ( KAL_FALSE );
			UpdateMenuFourIMEI ( KAL_TRUE );
			if(g_pWriteOption->bWriteIMEI)
			{
				if(g_SN.tIMEI.bFourIMEI)
				{
				    g_SN.tIMEI.bDualIMEI = KAL_FALSE;
					g_SN.tIMEI.bDualIMEISame = KAL_FALSE;
					g_SN.tIMEI.bThreeIMEI = KAL_FALSE;	
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bDualIMEI, KAL_FALSE);
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_DualImeiSame, KAL_FALSE);
					SetCtrlVal ( panelHandle_OperateCfg, panelCfg_bThreeIMEI, KAL_FALSE);
					
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_FALSE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_FALSE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_FALSE);
				}
				else
				{
				    SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei2Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI2Head, ATTR_DIMMED, KAL_TRUE);	
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_DualImeiSame, ATTR_DIMMED, KAL_TRUE);
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei3Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI3Head, ATTR_DIMMED, KAL_TRUE);	
					SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_bCheckImei4Head, ATTR_DIMMED, KAL_TRUE);
			        SetCtrlAttribute ( panelHandle_OperateCfg, panelCfg_strIMEI4Head, ATTR_DIMMED, KAL_TRUE);
				}
			}
			break;
		}
	return 0;
}
