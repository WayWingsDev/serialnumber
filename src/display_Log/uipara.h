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
#ifndef _UIPARA_H_
#define _UIPARA_H_

#include "general.h"
#include "context.h"

/*
typedef struct
{
   kal_char Barcode[64];
   kal_char IMEI_1[15];
   kal_char IMEI_2[15];
   kal_char BT[12];
   kal_char WIFI[12];

   kal_bool bCheckBarcode;
   kal_bool bCheckIMEI_1;
   kal_bool bCheckIMEI_2;
   kal_bool bCheckBT;
   kal_bool bCheckWIFI;
}HeadInfo_struct;
*/

typedef enum
{
   DataAllCorrect = 0,
   CheckBarcodeFail = -1,
   CheckIMEI1Fail = -2,
   CheckIMEI2Fail = -3,
   CheckIMEI3Fail = -4,
   CheckIMEI4Fail = -5,
   CheckBTFail = -6,
   CheckWIFIFail = -7,
   DataCheckFail = -8
}CheckScanData_Result_E;


extern SN_Context_struct g_SN;
#define M2S(x) #x

extern void UpdateLog ( kal_uint8 *pBuf, kal_uint16 iStep );
extern void DrawLogData(Log_struct *pData);
extern void ClearLog ( void );
extern void UpdateIndicator ( kal_bool bOK );
extern void ResetIndicator ( void );
extern void UpdateProgress ( void );
extern void EnableTimer2 ( kal_bool bEnable );



extern void ContextInit ( void );
extern void ContextDeInit ( void );
extern void GetParaFromIni( void );
extern void SaveParaToIni ( void );
extern void UpdateUIComponent( kal_bool bDir );
extern void AccompanyActionWithDualIMEI( void );
extern void AccompanyActionWithThirdIMEI( void );
extern void AccompanyActionWithFourIMEI( void );
extern void AccompanyActionWithDataCall(void);
extern void AccompanyActionWithSet(void);
extern void AccompanyActionWithAMR(void);
extern void AccompanyActionWithClear(void);
extern void AccompanyActionWithData(void);
extern void AccompanyActionWithCall(void);
extern void AccompanyActionWithSetAMR(void);
extern void AccompanyActionWithClearAMR(void);
extern void AccomanyActionWithModeSel(void);

//-------------------add by mtk71596----------------------
extern void UpdateIMEI ( kal_bool bDir );
extern void UpdateBarCode( kal_bool bDir );
extern void UpdateBT( kal_bool bDir );
extern void UpdateWIFIMacadr(kal_bool bDir);
extern void UpdateWIFIEEPROMCopy(kal_bool bDir);


/*
extern void UpdateHDCP( kal_bool bDir );
extern void UpdateDRMKeyInstall( kal_bool bDir );
*/
//----------------------------------------------------

extern void UpdateCheckSum ( kal_bool bDir );
extern void UpdateDualIMEI ( kal_bool bDir );
extern void UpdateThreeIMEI ( kal_bool bDir );
extern void UpdateFourIMEI ( kal_bool bDir );


/*

extern void UpdateLockIMEI ( kal_bool bDir );
extern void UpdateLockIMEI_Enable ( kal_bool bDir );

*/
extern void UpdateDataCall ( kal_bool bDir );

extern void UpdateAMR( kal_bool bDir );
extern void UpdateSDS( kal_bool bDir );
extern void UpdateSet ( kal_bool bDir );
extern void UpdateSetAMR( kal_bool bDir );
extern void UpdateClearAMR( kal_bool bDir );
extern void UpdateClear ( kal_bool bDir );
extern void UpdateDataprefer ( kal_bool bDir );
extern void UpdateCallprefer ( kal_bool bDir );
/*
extern void UpdateCheckFTStatus ( kal_bool bDir );
extern void UpdateThirdIMEI ( kal_bool bDir );
extern void UpdateFourIMEI( kal_bool bDir );
extern void UpdatePowerONDelayTime ( kal_bool bDir );
extern void UpdateBaudRate ( kal_bool bDir );
extern void UpdateModeType ( kal_bool bDir );
extern void UpdateSwitchDataCard ( kal_bool bDir );

*/

extern void UpdateCOMPort ( kal_bool bDir );

extern void UpdateTargetType ( kal_bool bDir );

extern void UpdateModemDatabasePath ( kal_bool bDir );
extern void UpdateModemDatabasePath_2 ( kal_bool bDir );
extern void UpdateAPDatabasePath ( kal_bool bDir );
//extern void UpdateAuthFilePath ( kal_bool bDir );
extern void UpdateImeiSvnPad ( kal_bool bDir );
extern void UpdateMenuBBChip ( kal_bool bDir );
extern void UpdateMenuCom ( kal_bool bDir, int menuItem );
extern void UpdateMenuBaudRate ( kal_bool bDir, int menuItem );
extern void UpdateMenuTarget ( kal_bool bDir, int menuItem );
extern void UpdateMenuMode ( kal_bool bDir, int menuItem );
extern void UpdateMenuFunc ( kal_bool bDir, int menuItem  );
extern void UpdateMenuBTPowerOn ( kal_bool bDir, int menuItem );
extern void UpdateMenuBTChip ( kal_bool bDir, int menuItem );


/*
extern void UpdateFuncHDCP( kal_bool bDir );
extern void UpdateFuncDRMKeyInstall( kal_bool bDir );
*/
//--------------------------------------------------------------------


//----------------add by mtk71596--------------------------------------
extern void UpdateMenuIMEI ( kal_bool bDir );
extern void UpdateMenuBarCode( kal_bool bDir );
extern void UpdateMenuBT( kal_bool bDir );
extern void UpdateMenuWIFI( kal_bool bDir );
extern void UpdateMenuHDCP( kal_bool bDir);
extern void UpdateMenuDRM_Key_Install( kal_bool bDir );
//---------------------------------------------------------------------



extern void UpdateMenuIMEICheckSum ( kal_bool bDir );
extern void UpdateMenuEnMetaWithoutBattery(kal_bool bDir);    //mtk71409  by JiXiang
extern void UpdateMenuEnDualTalk(kal_bool  bDir);   //mtk71409  by JiXiang
extern void UpdateMenuEnDatacard(kal_bool  bDir);   //mtk71409  by JiXiang
extern void UpdateMenuSDS(kal_bool  bDir); 
extern void UpdateMenuIMEILock ( kal_bool bDir );
extern void UpdateMenuDualIMEI ( kal_bool bDir );
extern void UpdateMenuThreeIMEI ( kal_bool bDir );
extern void UpdateMenuFourIMEI ( kal_bool bDir );


extern void UpdateMenuFTStatusCheck( kal_bool bDir );
//extern void UpdateMenuFourIMEI( kal_bool bDir );
extern void UpdateMetaLog ( kal_bool bDir );
//extern void UpdateCDrom ( kal_bool bDir );
//-------------------------------------------------------------------------------
extern E_OPERATE_MODE GetOperMode ( void );
extern E_FUNCTION_TYPE GetFuncMode ( void );
extern void FillLogData(Log_struct tData);
extern void GetLogData(Log_struct *pData);
extern void UpdateLog_Display ( kal_bool bDir );

//--------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
extern kal_uint8* GetModemDatabasePath ( void );
extern kal_uint8* GetModem2DatabasePath ( void );
extern kal_uint8* GetAPDatabasePath ( void );
extern kal_uint8* GetAuthFilePath ( void );
extern kal_uint8* SpGetAuthFilePath ( void );
extern kal_uint8* SpGetSecuFilePath ( void );

//--------------------------------------------------------------------------------
extern E_COM_NUMBER GetCOMPort ( void );
extern kal_bool IsUSBCOMPort ( void );
extern UART_BAUDRATE GetBaudRate ( void );
extern kal_bool GetIs6276M(void);
extern kal_bool GetIsCDrom ( void );
extern kal_bool GetIsDataCall ( void );
extern kal_bool GetIsSDS ( void );
extern kal_bool GetIsDataprefer( void );
extern kal_bool GetIsSetAMR( void );
extern kal_bool GetIsSet( void );
extern kal_bool GetIsClear( void );
extern kal_bool GetIsAMR( void );
extern kal_bool GetIsswitchtool ( void );

extern BBCHIP_TYPE GetBBChip ( void );
extern E_TARGET_TYPE GetTargetType ( void );
extern kal_bool GetIsDualImei ( void );
extern kal_bool GetIsSVNPAD_Enable ( void );
extern kal_bool GetIsImeiCheckSum ( void );
extern kal_bool GetIsAutoCheckSum ( void );
extern kal_bool GetIsCheckFTStatus ( void );
extern kal_bool GetIsImeiLock ( void );
extern IMEISV_struct_T GetSVNPAD ( void );
extern kal_bool GetIsEnableMetaLog ( void );

extern kal_int32 GetPowerOnDelayTime ( void );

extern void UpdateCount( kal_bool bPass);
extern kal_uint8* ResultToString(kal_uint8 MR);

extern kal_bool CheckIdentityPasswd(kal_char *strPasswd);
extern void GetPassword (int hpanel, kal_uint16 ctrlID, kal_char *strPasswd);
extern void SetPassword (int hpanel, kal_uint16 ctrlID, kal_char *strPasswd);
extern void EngineerSwitchToOperator (void);
extern void OperatorSwitchToEngineer (void);
extern kal_bool ConfirmNewPassword (kal_char *strNewpasswd, kal_char *strConfpasswd);


extern void UpdateCheckBarCode( kal_bool bDir );
extern void UpdateCheckIMEI_1( kal_bool bDir );
extern void UpdateCheckIMEI_2( kal_bool bDir );
extern void UpdateCheckIMEI_3( kal_bool bDir );
extern void UpdateCheckIMEI_4( kal_bool bDir );

extern void UpdateCheckBT( kal_bool bDir );
extern void UpdateCheckWIFI( kal_bool bDir );

extern int GetIMEInums(void);
extern void UpdateHeadInfo(kal_bool bDir);
extern void CreateScanOrder(void);
extern void ResetScanItem(void);
extern  void disableUSBSwitch(void);
extern void * enableUSBSwitch(void);



extern void GetCurrentScanData(int currentID, kal_char *strScanData, kal_char *strHead);
extern int GetNextScanControlID(int currentID);


extern CheckScanData_Result_E CheckCurrentScanData(int controlID);
extern CheckScanData_Result_E CheckAllScanData(void);

extern void HighLightCurrentScanData(int controlID);
extern kal_bool CheckScanDataHead(const kal_char *strScanData, const kal_char *strHead);
extern kal_bool CheckIMEIData(const kal_char *strScanData);
extern kal_bool CheckBT_WIFIData(const kal_char *strScanData);



extern void GetPasswordFromCtrl(kal_int32 panelID, int currentID, kal_char* strPassword);
extern void GetIMEIConfig(void);

extern void DimmedMenuItem(kal_bool bDimmed);











//extern void write_SetCleanBoot_Flag();

#endif
