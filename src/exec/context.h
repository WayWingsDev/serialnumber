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
/****************************************************************************/
#ifndef _CONTEXT_H___
#define _CONTEXT_H___

#include "download.h"
#include "mtk_mcu.h"
#include "meta.h"

#include <userint.h>

#define MAX_LOG_LEN 1024*20
#define MAX_WRITE_OPTION  10

//---------------------------changed by mtk71596-------------------------------------------
/*
typedef enum {
	FUNC_BARCODE = 0,
	FUNC_IMEI,
	FUNC_BT_ADDRESS,
	FUNC_MAC_ADDRESS,
	FUNC_MAC_ADDRESS_EX,
	FUNC_BT_TEST_BY_CHIP,
	FUNC_BT_TEST_BY_EARPHONE,
	FUNC_FOUR_IN_ONE,
	FUNC_IMEI_WM_ONLY,
	FUNC_COMBINE,
	
	FUNC_NUMBER_MAX,
	
} E_FUNCTION_TYPE;
*/
//add by mtk71596
typedef struct 
{
	kal_bool bIMEI;
	kal_bool bBarCode;   
	kal_bool bBT;
	kal_bool bWIFIMacadr;
	kal_bool bHDCP;
	kal_bool bDRMKeyInstall;
	kal_bool bWIFIEEPROMCopy;
}E_FUNCTION_TYPE;

typedef enum
{
 	HDCP = 0,
	DRMKEYINSTALL,
	UNDO,
}HDCP_DRMKEY;
//-----------------------------
typedef enum {
	TARGET_FEATURE_PHONE = 0,
	TARGET_SMARTPHONE,
	PCMCIA_CARD,
	Tablet_WIFI_ONLY,
	SP_DUALMODEM,
    RNDIS_DONGLE,
} E_TARGET_TYPE;
//---------------------------
typedef enum {
	META_MODE = 0,
	AT_MODE,
	
	OPERATE_MODE_MAX
	
} E_OPERATE_MODE;
//----------------------------
typedef enum {
	MT6601 = 0,
	MT6611,
	RFMD3500,
	
} E_BT_CHIP;
//-----------------------------
typedef enum {
	COM1 = 1,
	COM2,
	COM3,
	COM4,
	COM5,
	COM6,
	COM7,
	COM8,
	COM9,
	COM10,
	COM11,
	COM12,
	COM13,
	COM14,
	COM15,
	COM16,
	USB_VCOM,
} E_COM_NUMBER;
//------------------------------------------------------------------------------
typedef void (*FUNCTION_MODE_ARRAY)(void);

//------------------------------------------------------------------------------
//add by mtk71596
typedef struct 
{
	E_FUNCTION_TYPE eFuncType;
	E_OPERATE_MODE  eOperateMode;
	const FUNCTION_MODE_ARRAY func_ft_callback;
} Func_Mode_struct;



//----------------------------------------
typedef struct 
{
	E_COM_NUMBER    eComPort;
	UART_BAUDRATE   eBaudRate;

} Comm_Port_struct;

//----------------------------------------
typedef struct 
{
	BBCHIP_TYPE eBBChip;
	BBCHIP_TYPE eBBChip_AP;   //for 6516_AP
	E_TARGET_TYPE eTargetType;
	kal_int32 mPowerOnDelayTime;
	kal_bool bLogging;
	kal_bool bWorldPhone;

} Target_Info_struct;

//----------------------------------------
typedef struct 
{
	E_BT_CHIP eBTChip;
	kal_bool  bBTPower;   

} BT_Setting_struct;

//-----------------------------------------

typedef enum
{
	IMEI_NONE = 0,
	ONE_IMEI = 1,
	DUAL_IMEI = 2,
	THREE_IMEI = 3,
	FOUR_IMEI = 4,
	IMEI_MAX
}IMEI_Option;

typedef struct 
{
	kal_bool bCheckSum;
	kal_bool bDualIMEI;   // need save this item in eImeiNum
	kal_bool bLockIMEI;
	kal_bool bLockIMEI_Enable;
	kal_bool bCheckFTStatus;
	kal_bool bFourIMEI;   // need save this item in eImeiNum
	kal_bool bSVNPAD_Enable;
	kal_bool bAutoCheckSum;
	IMEISV_struct_T tImei_Svn_Pad;
	IMEI_Option eImeiNum; // add by guanxian 20101215 for third IMEI request.
	kal_bool bDualIMEISame;
	kal_bool bThreeIMEI;

} IMEI_Setting_struct;

typedef struct
{
   kal_bool bDataCall;
   kal_bool bset;
   kal_bool bclear;
   kal_bool AMR;
   kal_bool Dataprefer;
   kal_bool Callprefer;
   kal_bool SetAMR;
   kal_bool ClearAMR;
   kal_bool SDS;
}Combine_struct;

//-----------------------------------------
typedef struct 
{
	kal_uint8 *strModemDatabasePath;
	kal_uint8 *strModemDatabasePath2;
	kal_uint8 *strAPDatabasePath;
	kal_uint8 *strAuthFilePath;
	kal_uint8 *strspAuthFilePath;
	kal_uint8 *strspSecureFilePath;
	kal_uint8 *strHDCPKeyPath;
	kal_uint8 *strDRMKeyPath;
} Config_File_struct;


//-----------------------------------------
typedef struct 
{
	kal_uint16 iProgressStep;
	kal_uint32 iTotalNum;
	kal_uint32 iPassNum;
	kal_uint32 iFailNum;
	kal_uint8  *pStrLog;
	
} Log_struct;

//=============================================================================
typedef struct 
{
	Func_Mode_struct tFuncMode;
	Comm_Port_struct tCommPort;
	Target_Info_struct tTargetInfo;
	BT_Setting_struct tBTSetting;
	IMEI_Setting_struct tIMEI;
	Combine_struct tCombine;
	Config_File_struct strPath;
	Log_struct tLogBuffer;
	kal_bool bEnableMetaLog;
	kal_bool bEnableSwitchDataCard;
	kal_bool SpSecurreUSB;
	kal_bool bEnableCDrom;
	kal_bool is6276M;
	//mtk71409
	kal_bool isEntryMetaWithoutBattery;
	kal_bool isEntryDualTalk;
	kal_bool isEntrySDS;
} SN_Context_struct;


typedef enum {
	RUN_STATUS = 0,
	OK_STATUS,
	CANCEL_STATUS,
	
} E_INPUTBOX_STATUS;

typedef struct
{
   kal_char Barcode[64];
   kal_char IMEI_1[15];
   kal_char IMEI_2[15];
   kal_char IMEI_3[15];
   kal_char IMEI_4[15];
   kal_char BT[12];
   kal_char WIFI[12];

   kal_bool bCheckBarcode;
   kal_bool bCheckIMEI_1;
   kal_bool bCheckIMEI_2;
   kal_bool bCheckIMEI_3;
   kal_bool bCheckIMEI_4;
   kal_bool bCheckBT;
   kal_bool bCheckWIFI;
}HeadInfo_struct;

typedef struct
{
   kal_bool bWriteIMEI;
   kal_bool bWriteBarcode;  
   kal_bool bWriteBT;
   kal_bool bWriteWIFI;
   kal_bool bWriteHDCP;
   kal_bool bWriteDRMKeyInstall;
   kal_bool bWIFIEEPROMCopy;
}OptionSelect_struct;

typedef enum
{
   E_BARCODE_INDEX = 0,
   E_IMEI1_INDEX = 1,
   E_IMEI2_INDEX = 2,
   E_IMEI3_INDEX = 3,
   E_IMEI4_INDEX = 4,
   E_BT_INDEX = 5,
   E_WIFI_INDEX = 6   
}ScanOrder_E;

typedef enum
{
   E_Check_Running = 0,
   E_Check_CORRECT = 1,
   E_Check_UNCORRECT = 2
}CheckOldpwStatus_E;


#define MAX_SCANDATA_ITEMS 7
#define MAX_SCANDATA_NUMS 8
#define MAX_PASSWORD_LENGTH 16



//mtk71518 2013-05-13
//static unsigned int us_temp_MDInex = 1;  // add for MT6582 Support
//static unsigned int us_temp_SWInex = 5;  // add for MT6582 Support

//=============================================================================                    

#endif
