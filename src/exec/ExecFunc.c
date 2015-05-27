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

#include "SLA.h"  
#include "thread.h"
#include"AUTH.h"
#include "fpexec.h"
//#include "wmexec.h" //add by mtk71596
#include "uipara.h"
#include "execfunc.h"

#include "utility.h"



typedef enum{
		ST_START = 0,
		ST_AP,
		ST_IMEI,
		ST_SN_MD,
		ST_SN_AP,
		ST_SN,
		ST_BT,
		ST_WIFI,
		ST_HDCP,
		ST_DRAM_KEY_INSTALL,
		ST_MD,
		ST_BACK_NVRAM,
		ST_END,
    }statue;

int ret_statues = 0;
MetaCommon_struct g_Meta;
extern kal_bool bMetaEntered;
static MetaAP_struct g_MetaAP;//add by mtk71596

extern MetaModem_struct g_MetaModem;  

extern kal_char imei[4][16];


extern clock_t StartTime_g;
extern OptionSelect_struct *g_pWriteOption;

//±äÁ¿
//*******************************************************************************
   int sp_nv_to_nvram = 0;

   statue statues = ST_START;
   static kal_uint8 strLog [1024];
   kal_uint8 strTip [256];
   kal_uint16 iLoop = 0;

   IMEISV_struct_T tImei_Svn_Pad;
    
//	ret_statue ret_sta = statue_ok;

   extern kal_char imei[4][16];
   kal_uint8 strMacHeader[13];
   kal_uint32 value,iMacHeaderLen = 0;
   unsigned int status;    
   META_RESULT MR;
   kal_bool IsApMode = KAL_TRUE;
 kal_uint32 BackupSecondIMEI = 1;



//**************************************************************************
extern kal_bool MetaModemHandleInit(void);
extern void MetaModemHandleDeInit (void);
extern kal_bool MetaAPHandleInit (void);
extern void	MetaAPHandleDeInit (void);

extern kal_uint8* GetAuthFilePath ( void );
extern kal_uint8* SpGetAuthFilePath ( void );
extern kal_uint8* GetModemDatabasePath ( void );
extern kal_uint8* GetModem2DatabasePath ( void );

extern kal_uint8* SpGetSecuFilePath ( void );
//add by mtk71596
//----------------------------------------------
extern kal_uint32 IsIMEIChecked(void); 
extern kal_uint32 IsBarCodeChecked(void); 
extern kal_uint32 IsBTChecked(void); 
extern kal_uint32 IsWIFIChecked(void); 
/*
extern kal_uint32 IsHDCPChecked(void); 
extern kal_uint32 IsDRM_Key_InstallChecked(void); 
*/
extern void SetStartButton_Disable(kal_bool bEnable);

//-------------------------------------------------

//add by mtk71596
extern void Seg_MetaAPConnectReq ( void );//sp
extern kal_bool IsAPNvramDatabaseInit (void);
extern kal_bool IsNvramDatabaseInit ( void );
extern E_INPUTBOX_STATUS InputBoxPopup (kal_uint8* strTitle, kal_uint8* strText, kal_int8* buffer, kal_uint16 iMaxLength );
extern kal_bool GetIsAutoCheckSum ( void );
extern void SetMetaConnectReq ( void );//feature phone
extern kal_bool Prepare_For_USB_AT_CMD (void);
extern kal_bool COMContextInit (E_COM_NUMBER eComPort, UART_BAUDRATE eBaudRate );
extern kal_bool EnterMetaModemMode ( void );
extern kal_bool Exit_MetaModemMode ( void );
extern E_INPUTBOX_STATUS DisplayCodeScanner(void);//add by mtk71596
void Seg_MetaModemConnectReq ( void );//sp sn&imei

extern kal_bool Exit_MetaAPMode ( void );
extern kal_bool EnterMetaAPMode ( void );
extern void * enableUSBSwitch(void);
extern  void disableUSBSwitch(void);
extern void GetIMEIConfig(); 


extern kal_bool WM_META_SetCleanBootFlag_Customize  ( const int meta_handle, int writeOption );
extern kal_bool Switch2WM_META_Mode  ( const int meta_handle );
extern kal_bool ExitMetaMode ( void );
extern kal_bool EnterMetaMode (void);
extern int ModemMetaToAPMeta (void);

extern int func_barcode_imei_meta_hdlr_smart_phone_ap(void);
extern int func_drm_key_meta_hdlr_smart_phone( void );

//---------------------------------------------------------------------------------
extern int func_barcode_meta_hdlr_feature_phone (void);
extern int func_imei_meta_hdlr_feature_phone (void);
extern void func_combine_meta_feature_phone(void);
extern int func_bt_address_meta_hdlr_feature_phone ( void );
extern int func_wifi_mac_meta_hdlr_feature_phone ( void );
extern int func_wifi_mac_meta_hdlr_feature_phone_Ex( void );


extern void func_barcode_meta_hdlr_smart_phone (void);
extern void func_imei_meta_hdlr_smart_phone (void);
extern int func_bt_address_meta_hdlr_smart_phone ( void );
extern int func_wifi_mac_meta_hdlr_smart_phone ( void );
extern int func_wifi_mac_meta_hdlr_smart_phone_Ex ( void );


extern int func_barcode_meta_hdlr_smart_phone_modem (E_TARGET_TYPE targetStype);
extern void func_combine_meta_hdlr_smart_phone_modem (void);
extern int func_imei_meta_hdlr_smart_phone_modem (E_TARGET_TYPE targetStype);

extern void func_barcode_at_hdlr_feature_phone (void);
extern void func_Imei_at_hdlr_feature_phone (IMEISV_struct_T *tImei_Svn_Pad,kal_uint8 *i,kal_uint32 *isUsbAt);
extern void func_combine_at_feature_phone (void);
extern int func_hdcp_key_meta_hdlr_smart_phone(void);

//-------------------------------------------------------------------------
void SetAuthenEnableFlag ( kal_bool enable ){

	g_Meta.bAuthenEnable = enable;
}

kal_bool GetAuthenEnableFlag ( void ){
	
	return g_Meta.bAuthenEnable;
}

//-------------------------------------------------------------------------
void SetConnectedFlag ( kal_bool enable ){
	
	g_Meta.bIsConnected = enable;
}

kal_bool GetConnectedFlag ( void ){
	
	return g_Meta.bIsConnected;
}

//-------------------------------------------------------------------------
void SetBootStopFlag ( kal_bool enable ){
	
	g_Meta.bootstop = enable ? BOOT_STOP : 0 ;
}
//-------------------------------------------------------------------------
kal_bool GetBootStopFlag ( void ){
	
	return ( BOOT_STOP == g_Meta.bootstop ) ? KAL_TRUE : KAL_FALSE;
}

//---------------------------------------------------------------------------
kal_bool AuthInit () {

	
		if ( REQ_AUTH_Load ( GetAuthFilePath () )) {

			MessagePopup ("WARNING", "Load Authentication file fail!");

			return KAL_TRUE;
		}

		return KAL_FALSE;
	
}
kal_bool SpAuthInit () {

	
		if ( !SPATE_AUTH_Load ( SpGetAuthFilePath () )) {

			MessagePopup ("WARNING", "Load SpAuthentication file fail!");

			return KAL_TRUE;
		}

		return KAL_FALSE;
	
}
kal_bool SpSecuInit () {

	
		if ( !SPATE_AUTH_Load ( SpGetAuthFilePath () )) {

			MessagePopup ("WARNING", "Load SpSecuentication file fail!");

			return KAL_TRUE;
		}

		return KAL_FALSE;
	
}

//------------------------------------------------------------
kal_bool AuthHandleInit () {

	if ( REQ_AUTH_Create () ) {

			MessagePopup ("WARNING", "Init Authentication handle fail!");

			return KAL_TRUE;
		}	
	REQ_AUTH_Load ( GetAuthFilePath () );
	return KAL_FALSE;

}
kal_bool SpAuthHandleInit () {

	if ( !SPATE_AUTH_Create () ) {

			MessagePopup ("WARNING", "Init SP Authentication handle fail!");

			return KAL_TRUE;
		}	
	SPATE_AUTH_Load ( SpGetAuthFilePath () );
	return KAL_FALSE;

}
kal_bool SpSecuHandleInit () {

	if ( !SPATE_AUTH_Create () ) {

			MessagePopup ("WARNING", "Init Authentication handle fail!");

			return KAL_TRUE;
		}	
	SPATE_AUTH_Load ( SpGetAuthFilePath () );
	return KAL_FALSE;

}

//------------------------------------------------------
void MetaContextInit (void){

	g_Meta.bIsConnected = KAL_FALSE;
	g_Meta.bootstop = BOOT_STOP;  
	g_Meta.bAuthenEnable = KAL_FALSE;
	g_Meta.bIsDatabaseInitialized [0] = KAL_FALSE;
	g_Meta.bIsDatabaseInitialized [1] = KAL_FALSE;
	g_Meta.bIsDatabaseInitialized[2] = KAL_FALSE;
	g_Meta.bhdcpenable = KAL_FALSE;
	g_Meta.bdrmenable = KAL_FALSE;	
	//MetaModemHandleInit ();
	MetaAPHandleInit ();
	AuthHandleInit ();
	SpAuthHandleInit ();
	SpSecuHandleInit ();
}



//------------------------------------------------------
void MetaContextDeInit (void){

	REQ_AUTH_Unload ();
    REQ_AUTH_Destroy ();
	MetaModemHandleDeInit ();
	MetaAPHandleDeInit ();
}


//----------------------------------------------------------------------
void func_mac_address_at_hdlr (void)
{
	MessagePopup ("Feature Solution Info", "Not support Yet!");
};
//----------------------------------------------------------------------
void func_bt_test_chip_meta_hdlr (void)
{
	MessagePopup ("Feature Solution Info", "Not support Yet!");
};
//----------------------------------------------------------------------
void func_bt_test_chip_at_hdlr (void)
{
	MessagePopup ("Feature Solution Info", "Not support Yet!");
};
//----------------------------------------------------------------------
void func_bt_test_earphone_meta_hdlr (void)
{
	MessagePopup ("Feature Solution Info", "Not support Yet!");
};
//----------------------------------------------------------------------
void func_bt_test_earphone_at_hdlr (void)
{
	MessagePopup ("Feature Solution Info", "Not support Yet!");	

};

void AT_Mode_Func(void)
{
	MessagePopup ("Anyone At Info", "AT Mode NOT SUPPORT YET!");
}

//meta_mode smart phone
int sp_write_imei_fun(void)
{
	E_TARGET_TYPE targetStype = GetTargetType ();

   if(targetStype == SP_DUALMODEM)
   	{
   	  g_SN.tIMEI.bDualIMEI = KAL_TRUE;
	  g_SN.tIMEI.eImeiNum  = DUAL_IMEI;
   	}
   return func_imei_meta_hdlr_smart_phone_modem(targetStype);
}
int sp_write_barcode_modem_fun(void)
{
   E_TARGET_TYPE targetStype = GetTargetType ();
   return func_barcode_meta_hdlr_smart_phone_modem(targetStype);
}
int sp_write_barcode_imei_ap_fun(void)
{
  return func_barcode_imei_meta_hdlr_smart_phone_ap();
}
int sp_write_bt_fun(void)
{
    return func_bt_address_meta_hdlr_smart_phone();
}
int sp_write_wifi_fun(void)
{
    
	return func_wifi_mac_meta_hdlr_smart_phone_Ex();
    
}
int sp_Copy_wifi_fun(void)
{
    
	return func_wifi_mac_meta_hdlr_smart_phone();
    
}

int sp_write_hdcp_fun(void)
{
    return func_hdcp_key_meta_hdlr_smart_phone();
}
int sp_write_drm_key_fun(void)
{
    return func_drm_key_meta_hdlr_smart_phone();
}

//meta_mode feature phone

int fp_write_imei_fun(void)
{
	
	 return func_imei_meta_hdlr_feature_phone (); 	 
}
int fp_write_barcode_fun(void)
{
  return func_barcode_meta_hdlr_feature_phone();
}
int fp_write_bt_fun(void)
{
  return func_bt_address_meta_hdlr_feature_phone();
}
int fp_write_wifi_fun(void)
{
  return func_wifi_mac_meta_hdlr_feature_phone();
}

/*
void fp_write_hdcp_fun(void)
{
   
	MessagePopup ("hdcp feature phone", "NOT SUPPORT YET!");
	return;
}
void fp_write_drmkey_install_fun(void)
{ 
   
	MessagePopup ("drm key install feature phone", "NOT SUPPORT YET!");
	return;
}
*/

//-------------------------changed by mtk71596--------------------------------------- 
//----------------------------smart phone----------------------------------------------
int Enter_Meta_Mode_init_database(void)    
{
  E_TARGET_TYPE targetStype;
  targetStype = GetTargetType();
  
  if( g_pWriteOption->bWriteIMEI || g_pWriteOption->bWriteBarcode)
  {
	    if(targetStype == Tablet_WIFI_ONLY)
	 	{
		   sprintf ( strLog, "Warning: Tablet_WIFI_ONLY don`t need to write barcode&imei to modem!\n" );
		   strcat(strLog, "      And the barcode&imei info will be writed to product_info.\n");
	       UpdateLog ( strLog, 30 );
	 	}
	    else
	    {
	        sprintf ( strLog, ">>Step: Start to Connect with target...\n" );
	        UpdateLog ( strLog, 30 );
		
		    Seg_MetaModemConnectReq ();
		    if ( EnterMetaModemMode () ) 
		    {
			    Exit_MetaModemMode ();
			    sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode \n" );
			    UpdateLog ( strLog, 100 );					
			    return KAL_TRUE;
		    }
		    sprintf ( strLog, "   OK: Enter Smart phone modem meta, Connect to target successfully.\n" );
		    UpdateLog ( strLog, 40 );
		
		    sprintf ( strLog, "\n>>Step: Star init Modem nvram database...\n");
		    UpdateLog ( strLog, 80 );
		    if ( IsNvramDatabaseInit () ) 
		    {
		       Exit_MetaModemMode ();
			   sprintf ( strLog, "   Error: Init Modem Nvram Database failed.\n");
			   UpdateLog ( strLog, 100);	
			   SetStartButton_Disable ( KAL_FALSE );		
			   return KAL_TRUE;
	        }
		    sprintf ( strLog, "	OK: Init Modem Nvram Database successfully.\n");
            UpdateLog ( strLog, 100 ); 
	   }
   }

  if((IsNeedScanData() || g_pWriteOption->bWriteHDCP)) //2013.7.17
  {
   sprintf ( strLog, ">>Step: Start to Init AP Nvram Database...\n");
   UpdateLog ( strLog, 20 );

   if ( IsAPNvramDatabaseInit() ) 
   { 
	   sprintf ( strLog, "   Error: Init AP Nvram Database failed.\n");
	   UpdateLog ( strLog, 100);
	   return KAL_TRUE;
   }
   sprintf ( strLog, "	OK: Init AP Nvram Database successfully.\n");
   UpdateLog ( strLog, 100 );   
  }
  else
  {
  	  //drm key not store in nvram --->may be should fix this 2013.7.17
  }
   return KAL_FALSE;
}

int Enter_Ap_Mode(void)
{
  if(IsApMode == KAL_FALSE)
  {
      MR = ModemMetaToAPMeta();
      if (MR != 0 )
      {
           Exit_MetaModemMode ();
	       sprintf ( strLog, ">>Step: ModemMetaToApMeta fail, result is %s.\nNow exit the Modem meta\n", ResultToString(MR));
	       UpdateLog ( strLog, 100 );
		   
		   return KAL_TRUE;   
      } 
	  sprintf ( strLog,  "   OK: modem meta to ap meta successfully.\n" );
	  UpdateLog ( strLog, 50 );
	  
	  return KAL_FALSE;
  }
  else
  {
	    Seg_MetaAPConnectReq();	
	    sprintf ( strLog, ">>Step: Start to Connect with target...\n" );
	    UpdateLog ( strLog, 30 );
		if( EnterMetaAPMode () ) 
        {
			Exit_MetaAPMode ();		
			sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode and turn to next phone.\n" );
			UpdateLog ( strLog, 100 );		
			return KAL_TRUE; 	
		}
	    sprintf ( strLog,  "   OK:EnterMetaApMode, Connect to target successfully.\n" );
		UpdateLog ( strLog, 50 );
		IsApMode = KAL_TRUE;
		
		return KAL_FALSE;
  }
}
int SP_Back_up_NV(void)
{
       int ret = 0;
	   int writeOption;       
	   if(g_pWriteOption->bWriteBarcode == KAL_TRUE && g_pWriteOption->bWriteIMEI == KAL_FALSE)//Only write barcode
	   {
	      writeOption  = 1;
	   }
	   else if(g_pWriteOption->bWriteBarcode == KAL_FALSE && g_pWriteOption->bWriteIMEI == KAL_TRUE)//Only write IMEI
	   {
	      writeOption  = 2;
	   }
	   else if(g_pWriteOption->bWriteBarcode == KAL_TRUE && g_pWriteOption->bWriteIMEI == KAL_TRUE)//write barcode & IMEI
	   {
	      writeOption  = 3;
	   }
	   
	   sprintf ( strLog, "\n>>Step: To Backup NVRAM to Bin Region, and Set Clean Boot Flag\n" );
	   UpdateLog ( strLog, 90 );
	   Delay (0.5);
	   if ( META_SUCCESS != WM_META_SetCleanBootFlag_Customize ( g_Meta.iMeta_handle, writeOption ) )   ///// Clean boot is very Importnant for Customer.
	   {
	   	   Exit_MetaAPMode ();
		   sprintf ( strLog, "	  Error:!!!!! Fail to Backup NVRAM to BinRegion, writeOption = %d\n", writeOption);
		   UpdateLog ( strLog, 100 );	 
		   UpdateIndicator ( KAL_FALSE );
		   ret = 1;
		   goto err;
//	return;
	   }
	   else
	   {
		   sprintf ( strLog, "	  OK: Backup NVRAM to BinRegion successfully, writeOption = %d\n", writeOption );
		   UpdateLog ( strLog, 95 ); 
		   UpdateIndicator ( KAL_TRUE );
	   }
  err:
  	    IsApMode = KAL_TRUE;
	   	return ret;

}

void sp_handle_state(statue *pState)
{
	E_TARGET_TYPE targetStype = GetTargetType();
	
	//smart phone state machine
	  switch(*pState)
	  {
	       case ST_START:		 	
		  	  if(g_pWriteOption->bWriteIMEI|| g_pWriteOption->bWriteBarcode)
			  {
				  if(targetStype == Tablet_WIFI_ONLY) //don`t need write to modem side
				  {
				     *pState = ST_AP;
					 IsApMode = KAL_TRUE;
				  }
				  else
				  {
					 IsApMode = KAL_FALSE;
					 *pState = ST_MD;
				  }
		      }	  
		      else 
		      {
			      *pState = ST_AP;
				  IsApMode = KAL_TRUE;
		      }
		      break;
			
		  case ST_IMEI:		 	
		     if(!g_pWriteOption->bWriteIMEI) 
		     {
			    *pState = ST_SN_MD;
		     }
		     else
		     {
			    if(sp_write_imei_fun())
			    {
				   *pState = ST_END;
				   sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_IMEI\n");
			       UpdateLog ( strLog, 100 );	
			    }
			    else
			    {
				   *pState = ST_SN_MD;
			    }
		     }
		     break;
			
		case ST_SN_MD:
			if(!g_pWriteOption->bWriteBarcode) 
			{
				*pState = ST_AP;
			}
			else
			{
				if(sp_write_barcode_modem_fun())
				{
				   *pState = ST_END;
				  	sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_SN_MD\n");
			        UpdateLog ( strLog, 100 );	
			    }else
			   {
				  *pState = ST_AP;
			   }
			}
			break;
			
		case ST_MD:	
			*pState = ST_IMEI;  // imei write first
			break;
			
		case ST_AP:
			if(Enter_Ap_Mode())	
			{
				*pState = ST_END;
				sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_AP\n");
			    UpdateLog ( strLog, 100 );
			}
		    else
		   	{
				if(!(g_pWriteOption->bWriteBarcode) && !(g_pWriteOption->bWriteIMEI) )
				{
					*pState = ST_BT;
				}
				else
				{
					*pState = ST_SN_AP;
				}
		   	}
		   break;
		   
		case ST_SN_AP:
	   	   if (sp_write_barcode_imei_ap_fun())
		   {
				*pState = ST_END;
				sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_SN_AP\n");
		        UpdateLog ( strLog, 100 );	
		   }
		   else
		   {
		       *pState = ST_BT;
		   }
		   break;
		   
		case ST_BT:
			if(!g_pWriteOption->bWriteBT) 
			{
				*pState = ST_WIFI;
			}			
			else//BT
			{
		       if( sp_write_bt_fun())	
		       {
		           *pState = ST_END;
				   sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_BT\n");
			       UpdateLog ( strLog, 100 );	
		       }
			   else
			   {
				   *pState = ST_WIFI;
			   }
		    }
			break;
			
		case ST_WIFI:
			if(!g_pWriteOption->bWriteWIFI && (!g_pWriteOption->bWIFIEEPROMCopy ))
			{
				*pState = ST_HDCP;
			}		
			else//WIFI
			{
			if(g_pWriteOption->bWriteWIFI)//wifi
			 {
			  if( sp_write_wifi_fun())
			  {
			       *pState = ST_END;
				 	sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_WIFI\n");
			        UpdateLog ( strLog, 100 );	
			  }else
			  {
				*pState = ST_HDCP;
			  }
			 }
		     else//wifieepromcopy
	          {
			   if( sp_Copy_wifi_fun())
			    {
			       *pState = ST_END;
				 	sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_WIFI(WIFIEEPROMCopy)\n");
			        UpdateLog ( strLog, 100 );	
			    }
			   else
			   {
				*pState = ST_HDCP;
			   }
		     }
		  }
		break;

		case ST_HDCP:
	     if(!g_pWriteOption->bWriteHDCP)
		 {
			*pState = ST_DRAM_KEY_INSTALL;
		 }		  
		 else//hdcp
		  {
			if( sp_write_hdcp_fun())
				{
					*pState = ST_END;
					sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_HDCP\n");
					UpdateLog ( strLog, 100 );
//               		MessagePopup ("WARNING", strLog);
					g_MetaAP.eRunStatus = CANCEL_STATUS;//fix write  hdcp fail but not stop
				}
			    else
				{
					*pState = ST_DRAM_KEY_INSTALL;
				}
		  }	
	  	break;
			
		case ST_DRAM_KEY_INSTALL:
		 if(!g_pWriteOption->bWriteDRMKeyInstall)
			{
			    if((!g_pWriteOption->bWriteWIFI) && (!g_pWriteOption->bWriteBT)
					   && (!g_pWriteOption->bWriteBarcode) && (!g_pWriteOption->bWriteIMEI)
					   && (!g_pWriteOption->bWIFIEEPROMCopy)&& (!g_pWriteOption->bWriteHDCP))
			    	{
			    	  *pState = ST_END;
			    	}
				    else
				    {
				      *pState = ST_BACK_NVRAM;
					}
			}		 
			else //DRAM_KEY
			{			   
				if(func_drm_key_meta_hdlr_smart_phone())
				{
					*pState = ST_END;
					sprintf ( strLog, "ERROR!! Go to ST_END statues is:  ST_DRAM_KEY_INSTALL\n");
					UpdateLog ( strLog, 100 );			
					UpdateIndicator ( KAL_FALSE );
					g_MetaAP.eRunStatus = CANCEL_STATUS;//fix write  drmkey  fail but not stop
				}
				else
				{
					if((!g_pWriteOption->bWriteWIFI) && (!g_pWriteOption->bWriteBT)
					   && (!g_pWriteOption->bWriteBarcode) && (!g_pWriteOption->bWriteIMEI)
					   && (!g_pWriteOption->bWIFIEEPROMCopy)&& (!g_pWriteOption->bWriteHDCP))
					{
					   *pState = ST_END;
				  
					}
					else
					{
					  *pState = ST_BACK_NVRAM;
					}
				}
			}
		break;	 
		case ST_BACK_NVRAM:
			//todo: backup nvram
			if(SP_Back_up_NV())
				{
				  	sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_BACK_NVRAM\n");
			        UpdateLog ( strLog, 100 );
					if(! IsNeedScanData() && g_pWriteOption->bWriteHDCP)
						{
						  g_MetaAP.eRunStatus = CANCEL_STATUS;//fix write  hdcp fail but not stop
						}
				}
			*pState = ST_END;
			break;
			
		case ST_END:
			break;
		default:
			sprintf ( strLog, "   ERROR!! unknown statues.\n" );
			UpdateLog ( strLog, 100 );
			break;
		}
}

//--------------------------------------------------------------------------------
kal_int32 Smart_Phone_Fun(void)
{	  
     kal_bool bScanData = KAL_TRUE;
	 kal_bool bAnyWriteOption = KAL_TRUE;
     
      if(IsNeedScanData() == KAL_FALSE )
      {
          bScanData = KAL_FALSE;
          if((!g_pWriteOption->bWriteHDCP) && (!g_pWriteOption->bWriteDRMKeyInstall))
          {
             bAnyWriteOption = KAL_FALSE;
             sprintf ( strLog, " Warning: At least one Smart Phone WriteOption must be select.\n");
	         UpdateLog ( strLog, 100 );
		     return KAL_FALSE;
          }
		  else
		  {
		     bAnyWriteOption = KAL_TRUE;
		  }
      }
	  else
	  {
	      bScanData = KAL_TRUE;
	  }
	 	
	
	 sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
	 strcat ( strLog, ">>Step: Enter Meta Mode && Smart Phone;\n");
	 UpdateLog ( strLog, 100 );
 	 BackupSecondIMEI = 1; 
	
	 g_MetaAP.eRunStatus = RUN_STATUS;
	   
	 while( CANCEL_STATUS != g_MetaAP.eRunStatus && KAL_TRUE != GetBootStopFlag())
	 {	      
	      if(bScanData == KAL_TRUE)
	      {
	      	   sprintf ( strLog, "\n>>Step:Begin Scan Smart Phone data...\n");
		       UpdateLog ( strLog, 10 );
		       g_MetaAP.eRunStatus = DisplayCodeScanner();		  
	      }
		  else if(bAnyWriteOption == KAL_TRUE)
		  {
			   g_MetaAP.eRunStatus = OK_STATUS;
		  }
	       	  
		ResetIndicator ();
		if ( iLoop++ == 50)
		{
			ClearLog ();
			iLoop = 0;
		}
		
		if( g_MetaAP.eRunStatus == OK_STATUS)
		{	
			if(Enter_Meta_Mode_init_database())
            {
				UpdateIndicator ( KAL_FALSE );
				return KAL_FALSE;
			}
			
	        statues = ST_START;
			do
			{
				sp_handle_state(&statues);

			} while( statues!=ST_START && statues!=ST_END );

		    sprintf ( strLog, "\n>>Step: Meta Disconnect with target.\n");
		    UpdateLog ( strLog, 100 );
		    Exit_MetaAPMode ();
		}  
		else if(g_MetaAP.eRunStatus == CANCEL_STATUS)
	    {
	   	   sprintf ( strLog, "\n>>Step: Cancel scan Barcode DiagBox.\n");
		   UpdateLog ( strLog, 100 );		
		   return KAL_FALSE;
	    }
     }
	 
	   
	 return 0;
}


//-----------------------------------feature phone---------------------------------------------------
int Init_Database()
{ 
	sprintf ( strLog, "\n>>Step: Start to Init feature phone Database...\n");
	UpdateLog ( strLog, 20 );
	
	if ( IsNvramDatabaseInit () )
	{
		sprintf ( strLog, "   Error: Init feature phone Database failed.\n");
		UpdateLog ( strLog, 100);
		return KAL_TRUE;
	}
	
	return KAL_FALSE;
}
int Enter_Meta_Mode()
{
	int ret = 0;
	sprintf ( strLog, ">>Step: Start to Connect with target...\n" );
	UpdateLog ( strLog, 30 );
	SetMetaConnectReq ();
	if(EnterMetaMode()) 
	{
		Exit_MetaModemMode ();
	
		sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode and turn to next phone.\n" );
		UpdateLog ( strLog, 100 );
				
		UpdateIndicator ( KAL_FALSE );
		ret = 1;
		goto err;
	}
	sprintf ( strLog, "   OK: Connect successfully.\n\n" );
	UpdateLog ( strLog, 40 );
	err:
	return ret;

}


int Fp_Back_up_NV(void)
{
	MR = META_QueryIfFunctionSupportedByTarget_r(/*meta_handle*/0, 500, "META_MISC_EX_BackupCalibrationToStorage_r");
	sprintf ( strLog, ">> Query target support SDS/Backup_Partition...\n result = %s\n\n",ResultToString(MR));
	UpdateLog ( strLog, 10 );

	if(METAAPP_SUCCESS == MR)
	 {
		sprintf ( strLog, ">> Set the SDS\n");
		UpdateLog ( strLog, 10 );
		if(META_MISC_EX_BackupCalibrationToStorage_r(g_Meta.iMeta_handle,5000,0,&status))
	    {
			  sprintf ( strLog, " Error: BackupCalibrationToStorage fail, Exit Meta Mode and turn to next phone.\n" );
			  UpdateLog ( strLog, 100 );
			  return KAL_TRUE;
		}
		else
		{
			 sprintf ( strLog, "   OK: BackupCalibrationToStorage OK, Exit Meta Mode and turn to next phone.\n" );
			 UpdateLog ( strLog, 100 );
			 UpdateIndicator ( KAL_TRUE);
			 return KAL_FALSE;
		}
	 }
	 else
	 {
	     sprintf ( strLog, " Target without SDS/Backup_Partition feature, Exit Meta Mode and turn to next phone.\n" );
	     UpdateLog ( strLog, 100 );
		 sprintf ( strLog, " >>---------------------------------------------------------------------------<<.\n" );
	     UpdateLog ( strLog, 100 );
		 UpdateIndicator ( KAL_TRUE);
		 return KAL_FALSE;
	 }
}

void fp_handle_state(statue *pState)
{
  	   switch(*pState)
    	{
         case ST_START:		  			
		  	*pState = ST_IMEI;
		 case ST_IMEI:
		 	if(!g_pWriteOption->bWriteIMEI) *pState = ST_SN;
            else
				{ //IMEI
		 		  if(fp_write_imei_fun())
				  	{
                       *pState = ST_END;
					   sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_IMEI\n");
			           UpdateLog ( strLog, 100 ); 
            		}
				  else
				  	{
				  	   *pState = ST_SN;
				  	}
			    }
			break;
			
		case ST_SN:
			if(!g_pWriteOption->bWriteBarcode) *pState = ST_BT;				
			else
				{//SN
		 		  if(fp_write_barcode_fun())
				  	{
                       *pState = ST_END;
					   sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_SN\n");
			           UpdateLog ( strLog, 100 );
	            	}
				  else
				  	{
				  	   *pState = ST_BT;
				  	}
			    }
			break;
			
		case ST_BT:
			if(!g_pWriteOption->bWriteBT) *pState = ST_WIFI;
			else
				{//BT
				  if(fp_write_bt_fun())
				    {
                       *pState = ST_END;
					   sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_BT");
			           UpdateLog ( strLog, 100 );

            		}
				  else
				  	{
				  	   *pState = ST_WIFI;
				  	}
				}		
			break;
			
		case ST_WIFI:
			if(!g_pWriteOption->bWriteWIFI) 
			{
				*pState = ST_BACK_NVRAM;
			}
			else
				{//WIFI
				  if(fp_write_wifi_fun())
				  	{
				  	   *pState = ST_END;
					   sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_WIFI\n");
			           UpdateLog ( strLog, 100 );
					   
				  	}
				  else
				  	{
				  	   *pState = ST_BACK_NVRAM;
				  	}
				}
		     break;
			 
		case ST_BACK_NVRAM:
			if(Fp_Back_up_NV())
				{
				    sprintf ( strLog, "ERROR!! Go to ST_END statues is: ST_BACK_NVRAM\n");
			        UpdateLog ( strLog, 100 );	
					
					UpdateIndicator ( KAL_FALSE );
				}
			*pState = ST_END;
		    break;
			
		case ST_END:
			 break;
			 
		default:
			 sprintf ( strLog, "   ERROR!! unknown statues.\n" );
			 UpdateLog ( strLog, 100 );
		     break;
	   	}
}

kal_bool IsNeedScanData()
{
    if(g_pWriteOption->bWriteBarcode 
		|| g_pWriteOption->bWriteIMEI 
		|| g_pWriteOption->bWriteBT
		|| g_pWriteOption->bWriteWIFI)
    {
	   return KAL_TRUE;
    }
	else
	{
	   return KAL_FALSE;
	}
}

kal_int32 Feature_Phone_Fun(void)
{	 
	if(IsNeedScanData() == KAL_FALSE)
	{
	   sprintf ( strLog, "Warning: At least feature phone WriteOption must be selected.\n");
       UpdateLog ( strLog, 10 );
	   return KAL_FALSE;
	}
			
    if(g_SN.tFuncMode.eFuncType.bDRMKeyInstall)
	{
	   MessagePopup ("DRM Key feature phone", "DRM Key feature phone NOT SUPPORT YET!");
	   return KAL_FALSE;
	}

	if(g_SN.tFuncMode.eFuncType.bHDCP)
	{
	   MessagePopup ("hdcp feature phone", "hdcp feature phone NOT SUPPORT YET!");
	   return KAL_FALSE;
	}
	
    sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
    strcat ( strLog, ">>Step: Enter Meta Mode && feature Phone;\n");
    UpdateLog ( strLog, 0 );
	g_MetaModem.eRunStatus = RUN_STATUS;

	/*
	if(Init_Database())
	{
		return KAL_FALSE;
	}
	*/
	
    while( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
    {     
	  
	   sprintf ( strLog, ">>Step: Scan Featurephone code...\n");
	   UpdateLog ( strLog, 10 );
       g_MetaModem.eRunStatus = DisplayCodeScanner();
	   
	   
       ResetIndicator ();
	   if ( iLoop++ == 50)
       {
			 ClearLog ();
			 iLoop = 0;
	   }
	   
       if(g_MetaModem.eRunStatus == OK_STATUS)
       {      
          if(Enter_Meta_Mode())
          { 
             ExitMetaMode();
		     sprintf ( strLog, "\n>> Meta connect fail.\n");
	         UpdateLog ( strLog, 100 );
		     return KAL_FALSE;
          }

		  if(Init_Database())
	      {
		     return KAL_FALSE;
	      }
		  
	      statues = ST_START;
		  do
		  {
		 	  fp_handle_state(&statues);
		  } while( statues!=ST_START && statues!=ST_END );

		  ExitMetaMode();
		  sprintf ( strLog, "\n>> Meta connect fail.\n");
	      UpdateLog ( strLog, 100 );		  
	    
       }	  
	   else if(g_MetaModem.eRunStatus == CANCEL_STATUS)
	   {
	   	  sprintf ( strLog, "\n>>Step: Cancel scan Barcode DiagBox.\n");
		  UpdateLog ( strLog, 100 );		
		  return KAL_FALSE;
	   }
    }
	return 0;
}

//-------------------------------------------------------------
kal_int32 CVICALLBACK SNWriteThread (void *pParaData)
{
 kal_bool bScanData;
 E_TARGET_TYPE targetStype;
 kal_bool bWriteBarcode = g_pWriteOption->bWriteBarcode;
 kal_bool bWriteIMEI = g_pWriteOption->bWriteIMEI;
 kal_bool bWriteBT = g_pWriteOption->bWriteBT;
 kal_bool bWriteWIFI = g_pWriteOption->bWriteWIFI;
 IsApMode == KAL_TRUE;//init
 targetStype = GetTargetType();
 if(targetStype == SP_DUALMODEM)
 {
 	g_SN.tIMEI.bDualIMEI = KAL_TRUE;
	g_SN.tIMEI.bThreeIMEI = KAL_FALSE;
	g_SN.tIMEI.bFourIMEI = KAL_FALSE;
 }

 if(g_SN.bEnableSwitchDataCard)
 {
    enableUSBSwitch();
 }
 
 if((GetOperMode() == META_MODE) )
 {
    if(( targetStype == TARGET_SMARTPHONE)||( targetStype == RNDIS_DONGLE) || ( targetStype == SP_DUALMODEM) || ( targetStype == Tablet_WIFI_ONLY))
    { 
        if(g_SN.isEntryDualTalk)
	    {
	       g_pWriteOption->bWriteBarcode = KAL_FALSE;
		   g_pWriteOption->bWriteIMEI = KAL_FALSE;
	    }
        Smart_Phone_Fun();
    }
	else if( ( targetStype == TARGET_FEATURE_PHONE)||(targetStype == PCMCIA_CARD))
	{
	    if(g_SN.isEntryDualTalk)
	    {
	       g_pWriteOption->bWriteBT = KAL_FALSE;
		   g_pWriteOption->bWriteWIFI = KAL_FALSE;
	    }
	    Feature_Phone_Fun();
	}
 }
 else
 {
     AT_Mode_Func();
 }
 
  if(g_SN.bEnableSwitchDataCard)
  {
      disableUSBSwitch();
  }

  g_pWriteOption->bWriteBarcode = bWriteBarcode;
  g_pWriteOption->bWriteIMEI = bWriteIMEI;
  g_pWriteOption->bWriteBT = bWriteBT;
  g_pWriteOption->bWriteWIFI = bWriteWIFI;
  
  return 0;
}

