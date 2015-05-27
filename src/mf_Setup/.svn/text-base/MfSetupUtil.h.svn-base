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
 *   MfSetupUtil.h
 *
 * Project:
 * --------
 *   Maui META APP
 *
 * Description:
 * ------------
 *   MF_Setup.txt file handler header
 *
 * Author:
 * -------
 *  Xuhua Gao
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
#ifndef  _MFSETUPUTIL_H_
#define  _MFSETUPUTIL_H_

#include <inifile.h> 
#include "general.h" 
#include "context.h"
    

#define SETUP_FILE "SN_SETUP.txt" 

typedef enum {
	INI_BOOLEAN = 0,
	INI_INTEGER,
	INI_STRING, 
} E_INI_DATA_TYPE;


typedef union _struct_INI_ITEM
{
   kal_bool    bData;
   kal_uint32  mData;
   kal_char   *pData;
} U_INI_DATA_TYPE;

typedef struct 
{
	E_INI_DATA_TYPE eType;
	U_INI_DATA_TYPE uData;
} ini_item_struct;

typedef struct {
	kal_int8 baudrate[7];
} baudrate_struct;

extern IniText g_IniSetupFile;
/*---------------------------------------------------------------------------*/

	
//------------------------------------------------------------
extern void read_SP_WIFI_NVRAM_Path( char path[] );

extern UART_BAUDRATE read_BaudRate( void );
extern void write_BaudRate(UART_BAUDRATE mCommPort );

extern void read_PidFilter ( kal_uint8 *strPath );
extern void read_SpBromPortFilter ( kal_uint8 *strPath );
extern void read_SpPreloaderPortFilter ( kal_uint8 *strPath );
extern kal_bool read_Is_Composite_Device_Enable( void );
extern void read_Kernel_COMPort_Filter ( kal_uint8 *strPath );


extern void read_Imei_SvnPad ( IMEISV_struct_T * );
extern void write_Imei_SvnPad ( IMEISV_struct_T tSvnPad );

extern kal_uint32 read_BackupFlag(void);
extern void write_SetCleanBoot_Flag(void);

extern kal_uint32 read_spMD_Index(void);
extern kal_uint32 read_spSW_Version(void);

//Add mtk71518 begin, 2013-07-05
extern void read_HeadInfo ( HeadInfo_struct *tHeadInfo);
extern void write_HeadInfo( HeadInfo_struct tHeadInfo );

extern int read_EngineerPasswd ( kal_char *strPassword );
extern int write_EngineerPasswd ( kal_char *strPassword );



extern kal_bool read_BoolValueFromSetupFile( kal_uint8* strSecName, kal_uint8* strFieldName);
extern void write_BoolValueToSetupFile(  kal_uint8* strSecName, kal_uint8* strFieldName, kal_bool boolValue );

extern int read_IntValueFromSetupFile( kal_uint8* strSecName, kal_uint8* strFieldName);
extern void write_IntValueToSetupFile(  kal_uint8* strSecName, kal_uint8* strFieldName, int intValue );

extern void read_StringValueFromSetupFile(kal_uint8* strSecName, kal_uint8* strFieldName, kal_uint8 * strValue);
extern void write_StringValueToSetupFile (kal_uint8* strSecName, kal_uint8* strFieldName, kal_uint8 *strValue ); 
extern void GetUILegacyUSBautodetection(kal_bool flag, kal_uint32* checked);

//Add mtk71518 end, 2013-07-05











/*---------------------------------------------------------------------------*/

#endif
