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
 *   func.c
 *
 * Project:
 * --------
 *   Maui META APP
 *
 * Description:
 * ------------
 * 
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
#ifndef _WMEXEC_H_
#define _WMEXEC_H_   

//#include "context.h"
#include "general.h"
#include "spmeta.h"


#define BD_ADDR_LEN  6
#define IMEI_MAX_LENGTH  15
#define IMEI_ARRAY_LEN IMEI_MAX_LENGTH + 1
#define BARCODE_MAX_LENGTH  64
#define BT_ADDRESS_MAX_LENGTH  ( BD_ADDR_LEN * 2 )
#define MAC_ADDR_LEN  6
#define WIFI_MAC_MAX_LENGTH  ( MAC_ADDR_LEN * 2 )
#define EEPROM_SIZE 512

#define MT5921 0x5921
#define MT5931 0x5931
#define MT6620 0x6620
#define MT6628 0x6628
#define MT6572 0x6572
#define MT6582 0x6582



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
	USB_VCOM = 17,
} E_COM_NUMBER;

typedef struct
{
	unsigned char bd_addr[BD_ADDR_LEN];
}S_HANDSET_BT_ADRRESS;

typedef enum {
	RUN_STATUS = 0,
	OK_STATUS,
	CANCEL_STATUS,
	
} E_INPUTBOX_STATUS;

typedef void ( *EXEC_FUNC_ext )( void );

typedef struct {

	WM_META_ConnectInMETA_Req tMETA_Connect_Req;
	WM_META_ConnectInMETA_Report tMETA_Connect_Report;
	META_RESULT eMetaAP_Result;
	E_INPUTBOX_STATUS eRunStatus;
	FT_NVRAM_WRITE_REQ tNVRAM_WriteReq;
	FT_NVRAM_READ_REQ tNVRAM_ReadReq;
	FT_NVRAM_READ_CNF tNVRAM_ReadCnf;
	EXEC_FUNC_ext cb;
	HANDLE m_WriteToNVRAMEvent;
	HANDLE m_ReadFromNVRAMEvent;
} MetaAP_struct;


//------------------------------
extern int func_barcode_meta_hdlr_smart_phone (void);
extern int func_imei_meta_hdlr_smart_phone (void);
extern int func_bt_address_meta_hdlr_smart_phone ( void );
extern int func_wifi_mac_meta_hdlr_smart_phone ( void );
extern int func_wifi_mac_meta_hdlr_smart_phone_Ex ( void );
extern META_RESULT SP_Read_Wifi_Para_From_EEPROM ( kal_uint8* eepromInByte );
extern void Checksum_Generation(unsigned char StorageBuf[]);
extern int AP_META_DisconnectInMetaMode_r(const int meta_handle);
extern int ModemMetaToAPMeta (void);
extern int ModemMeta1ToModemMeta2(void);
extern META_RESULT SP_WIFI_Save_NVRAM_To_File (int meta_handle, char file_path[], char file_name[]);

extern int ApMetaToModemMeta ( void );

extern int  FP_META_DisconnectInMetaMode_r(const int meta_handle);
extern int  FP_METAAPP_readBarcodefromNVRAM( const int meta_handle, int timeout, char *p_Barcode );
extern int FP_METAAPP_writeBarcodetoNVRAM( const int meta_handle, int timeout, char *p_Barcode );
extern int FP_WriteImeiToNvram(const int meta_handle, int timeout, char *p_IMEI1, char *p_IMEI2);
extern kal_bool GetIsDualImei ( void );

extern META_RESULT REQ_ReadWifiMACFromNVRAM_Start ( WiFi_MacAddress_S *MACAddress );
extern META_RESULT REQ_WriteWifiMAC2NVRAM_Start (WiFi_MacAddress_S *MACAddress);
extern int REQ_WriteBarcode2NVRAM_Start(kal_uint8* strBarcode);
extern int REQ_ReadBarcodeFromNVRAM_Start(kal_uint8 * strBarcode);
extern int REQ_WriteImei2NVRAM_Start(kal_char (*pImei)[16], int imeiNums);
extern int REQ_ReadImeiFromNVRAM_Start(kal_char (*pImei)[16], int imeiNums);
extern kal_bool IsNvramDatabaseInit ( void );
extern kal_uint8* ResultToString(kal_uint8 MR);
extern kal_bool WM_META_SetCleanBootFlag_Customize ( const int meta_handle, int writeOption );
extern kal_uint32 read_BackupFlag(void);

kal_bool IsAPNvramDatabaseInit (void);
kal_bool APNvramDatabaseInit(void);
void Seg_MetaAPConnectReq ( void );
META_RESULT REQ_Write2NVRAM(void);
kal_bool EnterMetaAPMode ( void );
void __stdcall CNF_WMWriteNVRAM ( const FT_NVRAM_WRITE_CNF *cnf, const short token, void *usrData);

extern int func_hdcp_key_meta_hdlr_smart_phone ( void );
META_RESULT REQ_ReadHdcpKeyFromNVRAM_Start ( void );
META_RESULT REQ_WriteHdcpKey2NVRAM_Start (void);
int Load_HDCP_Key_File(char *filepath);


extern int func_drm_key_meta_hdlr_smart_phone( void );
META_RESULT REQ_WriteDRMKey2NVRAM_Start(void);
META_RESULT REQ_ReadDRMKeyFromNVRAM_Start(void);
int Load_DRM_Key_File(char *filepath);


#endif

