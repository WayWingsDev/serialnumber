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
#ifndef _FPEC_H_
#define _FPEC_H_   

#include "METAAPP.h"
#include "context.h"

#define IMEI_MAX_LENGTH  15
#define IMEI_ARRAY_LEN IMEI_MAX_LENGTH + 1
#define BARCODE_MAX_LENGTH  64
#define BT_ADDRESS_MAX_LENGTH  ( BD_ADDR_LEN * 2 )
#define MAC_ADDR_LEN  6
#define WIFI_MAC_MAX_LENGTH  ( MAC_ADDR_LEN * 2 )
#define   NUM_TX_POWER_2400M_CH   14


#define WIFI_MAX_COUNT  200		//add for WiFi EEPROM of MT5921, 20090711
// EEPROM read/write
#define  ADDR_MT5921_EEPROM_ALC_SLOPE                     0x17					//add for WiFi EEPROM of MT5921, 20090711
#define  ADDR_MT5921_EEPROM_2_4G_CCK_TX_POWER             0x18    // 0x18~0x2C	//add for WiFi EEPROM of MT5921, 20090711
#define  ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_END        0x80    // 0x80		//add for WiFi EEPROM of MT5921, 20090711
#define  ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_STEP       0x15					//add for WiFi EEPROM of MT5921, 20090711

#define  ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_0          0x2D    // 0x2D~0x41  //add for WiFi EEPROM of MT5921, 20090711
#define  ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_1          0x42    // 0x42~0x56  //add for WiFi EEPROM of MT5921, 20090711
#define  ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_2          0x57    // 0x57~0x6B  //add for WiFi EEPROM of MT5921, 20090711
#define  ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_3          0x6C    // 0x6C~0x80  //add for WiFi EEPROM of MT5921, 20090711
#define  EEPROM_TEST_ADDR 0x16

int WLAN_Tester_init;

// WiFi MAC header
#define  WIFI_MAC_HEAD_FRAME_CTRL_LEN 2
#define  WIFI_MAC_HEAD_DURATION_LEN   2
#define  WIFI_MAC_HEAD_ADDRESS_LEN    6
#define  WIFI_MAC_HEAD_SEQ_CTRL_LEN   2
#define  WIFI_MAC_HEAD_LEN           24




WiFi_TxPower_2400M_S m_sTxChannelDac2400M;
WiFi_TxPower_5000M_S m_sTxChannelDac5000M;

typedef struct
{
    WiFi_EEPROM_S eeprom[WIFI_MAX_COUNT];
    unsigned int count;
} S_WIFI_EEPROM;



typedef enum
{
    WIFI_MOD_CCK = 0,
    WIFI_MOD_OFDM
} E_WIFI_MOD;

typedef struct
{
    unsigned char frame_ctrl[WIFI_MAC_HEAD_FRAME_CTRL_LEN];
    unsigned char duration[WIFI_MAC_HEAD_DURATION_LEN];
    unsigned char address1[WIFI_MAC_HEAD_ADDRESS_LEN];
    unsigned char address2[WIFI_MAC_HEAD_ADDRESS_LEN];
    unsigned char address3[WIFI_MAC_HEAD_ADDRESS_LEN];
    unsigned char seq_ctrl[WIFI_MAC_HEAD_SEQ_CTRL_LEN];

} S_WiFiMacHead;


typedef struct {

	META_Connect_Req tMETA_Connect_Req;
	META_Connect_Report tMETA_Connect_Report;
	METAAPP_RESULT eMetaApp_Result;
	E_INPUTBOX_STATUS eRunStatus;
		
	META_RESULT eMeta_Result;
	FT_NVRAM_WRITE_REQ tNVRAM_WriteReq;
	FT_NVRAM_READ_REQ tNVRAM_ReadReq;
	FT_NVRAM_READ_CNF tNVRAM_ReadCnf;
	
	HANDLE m_WriteToNVRAMEvent;
	HANDLE m_ReadFromNVRAMEvent;

	META_ConnectByUSB_Req usb_req;
	META_ConnectByUSB_Report usb_report;

}  MetaModem_struct;
typedef enum
{
    TX_POWER_2400M_CCK = 0,
    TX_POWER_2400M_OFDM
} E_TX_POWER_2400M_MOD;

typedef struct
{
    int wifi_id;
    WiFi_RegDomain_S reg_domain;
    unsigned int channel_freq;
    WiFi_TestRate_E tx_rate;
    unsigned int pkt_length;
    unsigned int pkt_count;
    unsigned int pkt_interval;
    unsigned short tx_pwr_dac;
    WiFi_TestPktTxPattern_E pattern;
    unsigned char is_short_preamble;
    S_WiFiMacHead     s_mac_header;
} S_WIFICPT;







typedef struct {

	META_ConnectInMETA_Req tMETA_Connect_Req;
	META_ConnectInMETA_Report tMETA_Connect_Report;
	META_RESULT eMeta_Result;
	E_INPUTBOX_STATUS eRunStatus;
	FT_NVRAM_WRITE_REQ tNVRAM_WriteReq;
	FT_NVRAM_READ_REQ tNVRAM_ReadReq;
	FT_NVRAM_READ_CNF tNVRAM_ReadCnf;
	//EXEC_FUNC cb;
	HANDLE m_WriteToNVRAMEvent;
	HANDLE m_ReadFromNVRAMEvent;
} MetaAP_struct;

extern int func_barcode_meta_hdlr_feature_phone (void);
extern int func_imei_meta_hdlr_feature_phone (void);
extern void func_combine_meta_feature_phone(void);
extern int func_bt_address_meta_hdlr_feature_phone ( void );
extern int func_wifi_mac_meta_hdlr_feature_phone ( void );
extern int func_wifi_mac_meta_hdlr_feature_phone_Ex( void );

extern int func_barcode_meta_hdlr_smart_phone_modem (E_TARGET_TYPE targetStype);
extern void func_combine_meta_hdlr_smart_phone_modem (void);
extern int func_imei_meta_hdlr_smart_phone_modem (E_TARGET_TYPE targetStype);
extern void func_Imei_at_hdlr_feature_phone (IMEISV_struct_T *tImei_Svn_Pad,kal_uint8 *i,kal_uint32 *isUsbAt);
extern void func_combine_at_feature_phone (void);

extern int  FP_META_DisconnectInMetaMode_r(const int meta_handle);
int ApMetaToModemMeta ( void );
int ModemMeta1ToModemMeta2(void);
extern int AP_META_DisconnectInMetaMode_r(const int meta_handle);


extern int  FP_METAAPP_readBarcodefromNVRAM( const int meta_handle, int timeout, char *p_Barcode );
extern int FP_METAAPP_writeBarcodetoNVRAM( const int meta_handle, int timeout, char *p_Barcode );
extern int FP_WriteImeiToNvram(const int meta_handle, int timeout, char *p_IMEI1, char *p_IMEI2);
extern kal_bool IsNvramDatabaseInit ( void );
extern kal_uint32 read_BackupFlag(void);
extern void ResetDatabaseInitFlag(void);

//extern void GetUISetCleanBootFlag(kal_bool flag, kal_uint32* checked);
extern void GetUILegacyUSBautodetection(kal_bool flag, kal_uint32* checked);
#endif
