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
 *  Xuhua    (MTK70506)
 *  Guanxian (MTK70615)
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

#include "brom.h"
#include "interface.h"
#include <formatio.h>

#include <userint.h>
#include <utility.h>

#include "context.h"

#include "SLA.h"
#include "thread.h"

#include "execfunc.h"
#include "uipara.h"

#include "fpexec.h"  

#include "atprocess.h"

#include <Com_enum.h>

#include <rs232.h>

#include<usbfinder.h>

#include<interface.h>

 #include <Xboot.h>

 #include"AUTH.h"

 #include"SCERT.h"

 #include"Sp_brom.h"

//#include <Initguid.h> 

extern MetaCommon_struct g_Meta;
extern COMM_BAUDRATE BaudMap [];
extern unsigned int us_temp_MDInex;  // add for MT6582 Support
extern unsigned int us_temp_SWInex;  // add for MT6582 Support

void *handle;

extern kal_uint32 BootROMUSBDetection ;//change6.5

void SetStartButton_Disable(kal_bool bEnable);

extern E_INPUTBOX_STATUS InputBoxPopup (kal_uint8* strTitle, kal_uint8* strText, kal_int8* buffer, kal_uint16 iMaxLength );

extern kal_bool Switch2WM_META_Mode  ( const int meta_handle );
extern kal_bool WM_META_SetCleanBootFlag_Customize  ( const int meta_handle , int writeOption);
extern kal_bool Exit_MetaAPMode ( void );
//extern void UpdateUIMACHead(void);
//extern void GetUIMACHead(kal_uint8* strMACHeader,kal_uint32* HeaderLen );
extern void swap_c ( kal_uint8* x, kal_uint8* y );

extern kal_bool GetIsAutoCheckSum ( void );

extern E_INPUTBOX_STATUS DisplayCodeScanner(void);//add by mtk71596

extern void GetDualImei(kal_bool Flag); 
extern void * enableUSBSwitch(void);

extern int Modem2_Database_Select_Click_Shell ( void );

extern void read_PidFilter ( kal_uint8 *strPath );
extern void read_SpPreloaderPortFilter ( kal_uint8 *strPath );
extern kal_bool read_Is_Composite_Device_Enable( void );
extern void read_SpBromPortFilter ( kal_uint8 *strPath );
extern void read_Kernel_COMPort_Filter ( kal_uint8 *strPath );
extern kal_uint16 read_Search_Kernel_Port_Time( void );
META_RESULT REQ_WriteDataprefer_Callprefer_Start (kal_uint8 mode);
META_RESULT REQ_WriteAMR_Start (kal_uint8 mode);


extern void ConstructBarcode(kal_uint8* pOutData, const kal_uint8* pInData, const kal_uint8* pScanData, const kal_uint32 dataLength);

//add for MT6589 barcode
//MODEM(DFO)
typedef struct 
{
    unsigned char reserved;   //just reserved
} MODEM_QUERY_INFO_REQ;

typedef struct 
{
    unsigned int modem_number;
    unsigned int modem_id;
} MODEM_QUERY_INFO_CNF;

extern META_RESULT __stdcall SP_META_MODEM_Query_Info(unsigned int  ms_timeout, MODEM_QUERY_INFO_REQ *pReq, MODEM_QUERY_INFO_CNF *pCnf);
extern META_RESULT __stdcall SP_META_MODEM_Query_Info_r(const int meta_handle, unsigned int  ms_timeout, MODEM_QUERY_INFO_REQ *pReq, MODEM_QUERY_INFO_CNF *pCnf);
extern META_RESULT __stdcall SP_META_NVRAM_GetRecLen(const char *LID, int *len);
extern META_RESULT __stdcall SP_META_NVRAM_Init(const char *PathName, unsigned long *p_nvram_CatcherTranAddr);
extern META_RESULT __stdcall SP_META_NVRAM_Init_r(const int meta_handle,const char *PathName, unsigned long *p_nvram_CatcherTranAddr);
extern META_RESULT __stdcall SP_META_NVRAM_Read(const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData);
extern META_RESULT __stdcall SP_META_NVRAM_Read_r(const int meta_handle, const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData);
extern META_RESULT __stdcall SP_META_NVRAM_Write(const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData);
extern META_RESULT __stdcall SP_META_NVRAM_Write_r(const int meta_handle, const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData);

extern void Seg_MetaAPConnectReq ( void );
extern kal_bool IsAPNvramDatabaseInit (void);
extern kal_bool APNvramDatabaseInit(void);
extern int ModemMetaToAPMeta (void);
extern int ModemMeta1ToModemMeta2 (void);
extern kal_bool EnterMetaAPMode ( void );
extern int REQ_WriteBarcode2NVRAM_Start(kal_uint8* strBarcode);
extern int REQ_ReadBarcodeFromNVRAM_Start(kal_uint8 * strBarcode);
extern int REQ_WriteImei2NVRAM_Start(kal_char (*pImei)[16], int imeiNums);
extern int REQ_ReadImeiFromNVRAM_Start(kal_char (*pImei)[16], int imeiNums);

extern kal_bool MetaModemHandleInit(void);
extern void MetaModemHandleDeInit (void);
extern kal_bool MetaAPHandleInit (void);
extern void	MetaAPHandleDeInit (void);



//
 MetaModem_struct g_MetaModem;

static MetaAP_struct g_Meta6516Modem;

SP_BOOT_ARG_S m_stModeArg;

  
char asBROMPortFilter[100];
char asPreloaderPortFilter[100];
char asKernelPortFilter[100];
kal_bool search_preloader_port_success=1;
kal_bool search_kernel_port_success=1;



extern kal_char imei[4][16];


static kal_uint8 strLog [1024];

static char Cal_Final_rep[10000];
unsigned short com_port_temp = 0;
kal_uint8 port;

int usb_port=0;
kal_uint8 SetAMR;
kal_uint8 SetDataCall;

int switchtool;

 HANDLE hCOM1=0;


int functionId;


//---------------------------------------------

//for ANDROID_USB2Ser
//#define N 10
//#define M 20
//typedef struct Stack{
// i/nt top;
 // char A[N][M];
//}*pStack;

kal_char * m_exist_symbolic_set[20]={"\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0"};
kal_char *m_exist_port_set[20]={"\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0"};
kal_char  s_com_symbol[100];
kal_char s_com_port[100];
//DEFINE_GUID(Guid_ANDROID_USB2Ser,0xA5DCBF10L,0x6530,0x11D2,0x90,0x1F,0x00,0xC0,0x4F,0xB9,0x51,0xED);
static const GUID  Guid_ANDROID_USB2Ser={0xA5DCBF10L,0x6530,0x11D2,{0x90,0x1F,0x00,0xC0,0x4F,0xB9,0x51,0xED}};
#define  PID_ANDROID       "2000"
#define  VID_ANDROID       "0E8D"
kal_char  valid_usb_info[100];       
#define  InterfaceClassGuidConstant  Guid_ANDROID_USB2Ser
#define  PID                      PID_ANDROID
#define  VID                      VID_ANDROID
#define  PreloaderUSB  1
#define  BootROMUSB    0

//DEFINE_GUID(GUID_PORT_CLASS_USB2SER, 0x4D36E978L,0xE325,0x11CE,0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18);
static const GUID  GUID_PORT_CLASS_USB2SER ={0x4D36E978L,0xE325,0x11CE,{0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18}};


int CVICALLBACK search_kernel_port(void *functionData)
{
    SP_COM_FILTER_LIST_S sCOMFilter;
	SP_COM_PROPERTY_S sCOMProperty;
    META_RESULT ret;
	char *ppFilter_kernel_port[2];
    kal_uint32  *pBootStop = &g_Meta.bootstop;
	kal_int16 Search_Kernel_Port_Time=35;
	
	memset (&sCOMFilter, 0x0, sizeof(SP_COM_FILTER_LIST_S));
    memset (&sCOMProperty, 0x0, sizeof(SP_COM_PROPERTY_S));
    //BootStop=SP_BOOT_INFINITE;
		 
    //Use USB port, necessary to scan  
    Search_Kernel_Port_Time= read_Search_Kernel_Port_Time();
    //read_Kernel_COMPort_Filter(asKernelPortFilter);
    ppFilter_kernel_port[0]=asPreloaderPortFilter;
	ppFilter_kernel_port[1]=asBROMPortFilter;
	sCOMFilter.m_uCount = 2;
    sCOMFilter.m_ppFilterID = ppFilter_kernel_port;	
	sCOMFilter.m_eType=SP_BLACK_LIST;
    search_kernel_port_success=1;
      
    if(IsUSBCOMPort())
	{
			
	        g_Meta6516Modem.eMeta_Result = SP_GetIncrementCOMPortWithFilter(&sCOMFilter, &sCOMProperty, &GUID_PORT_CLASS_USB2SER, 0, pBootStop, Search_Kernel_Port_Time);
               

              Delay(1);
		switch(g_Meta6516Modem.eMeta_Result)
	        {
	            case SP_S_DONE:
			 usb_port=sCOMProperty.m_uNumber;
	               
	                break;
	            case SP_S_STOP:
					
                       search_kernel_port_success=0;
			    return KAL_TRUE;
					
	            case SP_S_TIMEOUT:
	            {
	                MessagePopup("Search Kernel USB COM port timout!", "Fail");
	                search_kernel_port_success=0;
	                return KAL_TRUE;
	            }
	            default:
	            {
	                MessagePopup("Search Kernel USB COM port fail!", "Fail");
			 search_kernel_port_success=0;
	               
	                return KAL_TRUE;
	             }
	        }
	 }
	  return KAL_FALSE;
   
}


int CVICALLBACK Connect_with_preloader(void *functionData)
{

      	//for secured meta 
	unsigned int eType;   //0:BoorROMUSB,1:PreloaderUSB
    SP_COM_FILTER_LIST_S sCOMFilter;
	SP_COM_PROPERTY_S sCOMProperty;
	char *ppFilter[2];
	kal_uint32  *pBootStop;
//	kal_uint32	BootStop;

//	kal_uint32 BootROMUSBDetection = 0;//change301365
    int iRet;
    bool IsCompositeDeviceEnable;
	   
	unsigned short us_temp_is_capable = 1;	// add for MT6582 Support,by mtk71518 2013-05-13		
    unsigned short us_temp_is_mandatory = 1; // add for MT6582 Support, by mtk71518 2013-05-13	

//	GetUILegacyUSBautodetection(KAL_TRUE,&BootROMUSBDetection);
    read_SpBromPortFilter(asBROMPortFilter);
	read_SpPreloaderPortFilter(asPreloaderPortFilter);
	IsCompositeDeviceEnable=read_Is_Composite_Device_Enable();
	ppFilter[0]=asPreloaderPortFilter;
	ppFilter[1]=asBROMPortFilter;
    pBootStop = (kal_uint32*)&g_Meta.bootstop;
//	BootStop=SP_BOOT_INFINITE;

    m_stModeArg.m_pStopFlag= pBootStop;
//	m_stModeArg.m_pStopFlag= &BootStop;

    m_stModeArg.m_bIsUSBEnable=IsUSBCOMPort();
	m_stModeArg.m_bIsSymbolicEnable=KAL_FALSE;
	m_stModeArg.m_euBootMode=SP_META_BOOT;
	m_stModeArg.m_bIsCompositeDeviceEnable=IsCompositeDeviceEnable;
	
	m_stModeArg.m_uMDMode =  (us_temp_is_capable << 15) | (us_temp_is_mandatory << 14) | (((unsigned short)us_temp_MDInex) << 8) | ((unsigned short)us_temp_SWInex);  // add for MT6582 Support	

//	if(BootROMUSBDetection)
    if(g_SN.SpSecurreUSB)
	{
	sCOMFilter.m_uCount=2;
	
	}
	else
	{
	sCOMFilter.m_uCount=1;
	
	}
	sCOMFilter.m_ppFilterID=ppFilter;
	sCOMFilter.m_eType=SP_WHITE_LIST;


       if(!IsUSBCOMPort())
       {
		          m_stModeArg.m_uPortNumber=GetCOMPort();
		          eType=PreloaderUSB;
			  search_preloader_port_success=1;// 
       }
       else
       {
	  
			iRet=SP_GetIncrementCOMPortWithFilter(&sCOMFilter, &sCOMProperty, NULL, _TRUE,pBootStop,100); 
                     Delay(1);
		       if(0 == iRet)
		       {
			      
		            switch(sCOMProperty.m_iFilterIndex)
		            {
		                case 0:
		                      eType=PreloaderUSB;
				        search_preloader_port_success=1;
					  break;
				  case 1:
				        eType=BootROMUSB;
					search_preloader_port_success=1;
					   break;
				  default:
				  	MessagePopup ("Filter index error!", "fail.");
					search_preloader_port_success=0;
				    return KAL_FALSE;
		            }

		          m_stModeArg.m_uPortNumber=sCOMProperty.m_uNumber;

//			   sprintf ( strLog, "PortNum = %d", m_stModeArg.m_uPortNumber );	
//			   UpdateLog(strLog,20);
    
		       }
		     else
		     	{
		     	       MessagePopup ("Search new COM port fail!", "fail.");
				 search_preloader_port_success=0;
				 return KAL_FALSE;
		     	}
       	}

       Sleep (0.01);
       if(BootROMUSB==eType)
       {
          iRet=SP_BootROM_BootMode(&m_stModeArg);
       }
       else if(PreloaderUSB==eType)
       {
          iRet=SP_Preloader_BootMode(&m_stModeArg);
       }
       if(0!=iRet)
       {
          MessagePopup ("META mode entry fail!", "fail.");
	    search_preloader_port_success=0;
	    return KAL_FALSE;
       }
	return KAL_TRUE;

}


void scan_exist_com_port_str(
kal_char *exist_symbolic_str[] /*out*/,
kal_char *exist_port_str[] /*out*/,
char * PID_Scan,char * VID_Scan,GUID guid, kal_uint32*  device_num)
{
     unsigned long	device_number, i;
    char		port_name[2048];
    unsigned long	port_name_length;
    char		symbolic_name[2048];
    unsigned long	symbolic_name_length;
    device_number =  GetDeviceNumber(guid, PID_Scan, VID_Scan);//Get_Device_Number
    if( device_number == 0)
    {
        return;
    }
     *device_num=device_number;
    for( i=0; i<device_number; i++)
    {
        if(GetPresentDevicePath(guid, PID_Scan, VID_Scan, i,
                    port_name, sizeof(port_name), (unsigned long *) &port_name_length,
                    symbolic_name, sizeof(symbolic_name), (unsigned long *) &symbolic_name_length))//Get_Device_Path

        { *( exist_symbolic_str+i)=symbolic_name;
            
            *(exist_port_str+i)=port_name;
        }
    }
}

bool get_new_created_com_port_str(kal_char *symbolic_return_value, kal_char *port_return_value,
                                           kal_char * exist_symbolic_str[],
                                           kal_char * exist_port_str[],
                                           char * PID_Scan,char * VID_Scan,GUID guid)
{
    kal_char                         result_symbolic[100];
    kal_char                         result_port[100];
    kal_char *               currentSymbolicName[20]={"\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0"};
    kal_char *               currentPortName[20]={"\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0","\0"};
    kal_char *              itSymbolic;
    kal_uint32              device_num=0,i,j;
	
    scan_exist_com_port_str(currentSymbolicName, currentPortName, PID_Scan, VID_Scan, guid,&device_num);
/*
        sprintf ( strLog,  "scan device num is %d\n",device_num);	
        UpdateLog ( strLog, 10 );
	*/
    for( i=0; i<device_num; i++)
    {

            /*
            if(   *(*(currentPortName+i) )!=   *(*(exist_port_str+i) )   )
		{     

		         j=strlen(*(currentPortName+i));
		           memcpy(port_return_value,*(currentPortName+i),j);
		          //*port_return_value=*(*(currentPortName+i) );
		}
          */


	      if(   *(*(currentSymbolicName+i) )!=   *(*(exist_symbolic_str+i) )   )
		{
		      j=strlen(*(currentSymbolicName+i));	     
              memcpy(symbolic_return_value,*(currentSymbolicName+i),j);		 
			 return KAL_TRUE;
		}	
    }
  return KAL_FALSE;	
}





 META_RESULT  __stdcall EnumDynamicUSBComPort_rr( unsigned int ms_scan_timeout, unsigned short *com_port, int *p_scanstop)
{
    // this method is not used now for smart phone, and it will be obsoleted.
    int i, ret,j;
    unsigned short com_port_list_org[255];
    unsigned short com_port_count_org = sizeof(com_port_list_org)/sizeof(unsigned short);
    unsigned short com_port_list[255];
    unsigned short com_port_count = sizeof(com_port_list)/sizeof(unsigned short);
    char report[99];

    bool bFindComPort = 0;

    bool b_com_port_list[255];
    unsigned int ms_start_scan_time ;
    unsigned int ms_total_scan_time = 0;

    if(p_scanstop != NULL)  // reset the value
        (*p_scanstop) = 0;
    //  MessagePopup ("COM INFORMATION", "q");

    // check arguments
    if( NULL == com_port )
    {
        //	MTRACE_ERR(g_hMTRACE, "<%d> META_GetDynamicUSBComPort_r(): invalid arguments! , com_port(0x%08X).", meta_handle, com_port);
        return META_INVALID_ARGUMENTS;
    }


    memset(com_port_list_org, '\0', (com_port_count_org)*sizeof(unsigned short));
    memset(com_port_list, '\0', (com_port_count)*sizeof(unsigned short));


    ret = ComPortEnumerate(com_port_list_org, &com_port_count_org);

    if( COM_ENUM_NO_COM_PORT_FOUND == ret)  // the com port number is 0
    {
        com_port_count_org = 0;

    }
    else if(COM_ENUM_OK == ret)
    {
        // MTRACE(g_hMTRACE, "<%d> META_GetDynamicUSBComPort_r(): Current Port Number: %d", meta_handle,com_port_count_org);
    }
    else  // fail to enumerate
    {
        // MTRACE_ERR(g_hMTRACE, "<%d> META_GetDynamicUSBComPort_r(): First Time: Enumerate Port Fail (return: %d)", meta_handle, ret);
        return META_ENUMERATE_USB_FAIL;
    }

    // sprintf(devicename, "COM%d", comport);

    ms_start_scan_time = GetTickCount();

    //MessagePopup ("COM INFORMATION", "power on ,enum USB enter.........");


    for(; ;)
    {

	 if(KAL_TRUE == GetBootStopFlag())
	 	{
	 	
		return META_FAILED;
	 	}
        // check if timeout
        ms_total_scan_time = GetTickCount() - ms_start_scan_time;
        if(ms_scan_timeout < ms_total_scan_time)
        {
            return META_FAILED;
           
        }

        if((*p_scanstop) == ENUM_USB_STOP)
        {   
               return META_STOP_ENUM_USB_PROCEDURE;
        }

        ret=ComPortEnumerate(com_port_list, &com_port_count);

        // get current port
        if(COM_ENUM_OK != ret)
        {
            if(COM_ENUM_NO_COM_PORT_FOUND == ret)
            {
                com_port_count = 0;
            }
            else // fail
            {
           
                //	MTRACE_ERR(g_hMTRACE, "<%d> META_GetDynamicUSBComPort_r(): Enumerate Port Fail (return: %d)", meta_handle, ret);
                return META_ENUMERATE_USB_FAIL;
            }
        }

  

        if( com_port_count == com_port_count_org &&
                !memcmp((void *)com_port_list, (void *)com_port_list_org, com_port_count_org*sizeof(unsigned short)) )
        {
           
            com_port_count = sizeof(com_port_list)/sizeof(unsigned short);
            continue;
        }

        for( i = 0; i < 255; i++)
        {
            b_com_port_list[i] = 0;
        }
        for( i = 0; i < com_port_count_org; i++)
        {
            b_com_port_list[com_port_list_org[i]] = 1;
        }

        for( i = 0; i < com_port_count; i++)
        {
            if( b_com_port_list[com_port_list[i]] == 0 )
            {
               /*
                  for(j=0;j<=com_port_count;j++)
                   {sprintf(strLog, "COM%d", com_port_list[j]);
                    UpdateLog ( strLog, 10 );   
                    }
                    */         
                *com_port = com_port_list[i];
                bFindComPort = 1;
                break;
                //return META_SUCCESS;
            }
        }
        if(bFindComPort)
        {  

	
            return META_SUCCESS;
        }
        else
        {
            com_port_count_org = com_port_count;
            memcpy((void*)com_port_list_org, (void*)com_port_list, sizeof(com_port_list)/ sizeof(unsigned short));
        }

        Sleep(2);
    }


    return META_FAILED;
}












//-------------------------------------------------------------------------

kal_bool Prepare_For_USB_AT_CMD (void)
{
    META_RESULT meta_result = 0;
    kal_uint32 status = 1;
    
    HANDLE hCOM = INVALID_HANDLE_VALUE;
    char com_str[128];
    char temp_str[128];

    BOOT_MAUI_ARG bootMauiArg;
    BOOT_RESULT bootResult;
     //kal_uint32 boot_stop;
    unsigned short com_port_temp_r = 0;
   
 

    meta_result = META_GetDynamicUSBComPort_r (g_Meta.iMeta_handle, 30000, &com_port_temp_r, &g_Meta.bootstop);
    com_port_temp=com_port_temp_r;
    
	
    if (meta_result != META_SUCCESS)
    {
        
        sprintf ( strLog,  "Get Dynamic USB Com Port Fail!\n");	
        UpdateLog ( strLog, 10 );
		g_MetaModem.eRunStatus=CANCEL_STATUS;
        return  KAL_FALSE;
    }
    else
    {
        sprintf ( strLog,  "META_GetDynamicUSBComPort_r OK, %d\n", com_port_temp);	
        UpdateLog ( strLog, 10 );
       
    }

    sprintf (com_str, "\\\\.\\COM%u", com_port_temp);
    hCOM = CreateFile (com_str, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (INVALID_HANDLE_VALUE == hCOM)
    {
        return KAL_FALSE;
    }

    memset(&bootMauiArg, 0, sizeof(bootMauiArg));
    memset(&bootResult, 0, sizeof(bootResult));

    bootMauiArg.m_bbchip_type = AUTO_DETECT_BBCHIP;
    bootMauiArg.m_ext_clock = EXT_26M;

    bootMauiArg.m_ms_boot_timeout = BOOT_INFINITE;
    bootMauiArg.m_max_start_cmd_retry_count = DEFAULT_BROM_START_CMD_RETRY_COUNT;

    bootMauiArg.m_cb_com_init_stage = NULL;
    bootMauiArg.m_cb_com_init_stage_arg = NULL;

    bootMauiArg.m_cb_in_brom_stage = NULL;
    bootMauiArg.m_cb_in_brom_stage_arg = NULL;

    bootMauiArg.m_speedup_brom_baudrate = _TRUE;

    bootMauiArg.m_ready_power_on_wnd_handle = NULL;
    bootMauiArg.m_ready_power_on_wparam = NULL;
    bootMauiArg.m_ready_power_on_lparam = NULL;

    bootMauiArg.m_auth_handle = Get_AuthHandle();
    bootMauiArg.m_cb_sla_challenge = SLA_Challenge;
    bootMauiArg.m_cb_sla_challenge_arg = NULL;
    bootMauiArg.m_cb_sla_challenge_end = SLA_Challenge_END;
    bootMauiArg.m_cb_sla_challenge_end_arg = NULL;

    bootMauiArg.m_usb_enable = _TRUE; /* _TRUE for USB and _FALSE for UART */

    bootMauiArg.m_maui_mode = MAUI_MODE_NORMAL;
    bootMauiArg.m_maui_mode_option = MAUI_MODE_OPTION_CREATE_USB_COM_AFTER_BOOTUP;

    status = Boot_MAUI(hCOM, &bootMauiArg, &bootResult, &g_Meta.bootstop);
    if (S_DONE != status)
    {
         return KAL_FALSE;
    }
    else
    {


	sprintf ( strLog,  "Boot_MAUI OK\n");	
        UpdateLog ( strLog, 10 );
        
    }

    if (INVALID_HANDLE_VALUE != hCOM)
    {
        status = CloseHandle (hCOM);
        hCOM = INVALID_HANDLE_VALUE;
    }
  
    //MMS_INFO[WorkingMS].ComPort = com_port_temp;
    //com_port = com_port_temp;


	
    return KAL_TRUE;


}

/*
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability() (META_Handle.cpp:2227)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Querying (META_Handle.cpp:2233)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query number_of_md : 2 (META_Handle.cpp:2235)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query active_md_idx: 0 (META_Handle.cpp:2236)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query multi_talk   : 1 (META_Handle.cpp:2237)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query done (META_Handle.cpp:2238)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query number_of_mdSwImg : 1 (META_Handle.cpp:2240)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query active_mdtype_idx: 0 (META_Handle.cpp:2241)
08/22/13 19:22:50.992 META_DLL[1168][7832]: <0> META_HANDLE::QueryMultiTalkCapability(): [Custom] Query multi_mdtype   : 0 (META_Handle.cpp:2242)




typedef struct
{
    unsigned int number_of_md:8;
    unsigned int active_md_idx:8;
    unsigned int multi_talk:1; // 0: no multi-talk, 1: multi-talk
    unsigned int multi_frame_type:1; // 0: all MD use the same frame type, 1: each MD is assigned a frame type
    unsigned int number_of_mdSwImg:4;  //for MT6582 world phone (multi-MDtype)
    unsigned int active_mdtype_idx:4;
    unsigned int multi_mdtype:1; // 0: no multi-MDtype, 1: multi-MDtype
    unsigned int reserved:5;
} META_MD_Query_Result_T;
*/

#if 1

META_MD_Query_Result_T __stdcall MdQueryHandler(void* MdQuery_CB_Arg)
{
	META_MD_Query_Result_T result;
	
	if(g_SN.tTargetInfo.eTargetType == SP_DUALMODEM)
	{		
       result.number_of_md = 2;
	   result.active_md_idx = 0;
	   result.multi_talk = 1;
	   result.multi_frame_type = 1;
	   result.number_of_mdSwImg = 1;
	   result.active_mdtype_idx = 0;
	   result.multi_mdtype = 0;
	   result.reserved = 5;
	}
	else if(g_SN.tTargetInfo.eTargetType == TARGET_SMARTPHONE)
	{
		result.number_of_md = 1;
		result.active_md_idx = 0;
		result.multi_talk = 0;
		result.multi_frame_type = 0;
		result.number_of_mdSwImg = 2;
		if(us_temp_SWInex == 3)
		{
		    result.active_mdtype_idx = 0;
		}
		else if(us_temp_SWInex == 5)
		{
			result.active_mdtype_idx = 1;
		}
		result.multi_mdtype = 1;
		result.reserved = 5;

	}
	
	return result;
}

int MdTypeSwitchHandler(META_MDTYPE_Switch_Param_T mdtype_switch_param, void* MdTypeSwitch_CB_Arg)
{
    return 1;
}




kal_bool MetaModemHandleInit () {

    char *pFuncName;
	if ( METAAPP_GetAvailableHandle ( &g_Meta.iMeta_handle) ){
	
		MessagePopup ("WARNING", "Get Meta handle fail!");
		return KAL_TRUE;
	} 

	/*
	sprintf ( strLog, "us_temp_SWInex = %d.\n", us_temp_SWInex);
	UpdateLog ( strLog, 0);
	*/
	
	if(g_SN.tTargetInfo.bWorldPhone == KAL_TRUE)
	{
	    //g_SN.tTargetInfo.eTargetType = TARGET_SMARTPHONE;
	    pFuncName = "META_Init_Ex_2_r";
	    if(META_Init_Ex_2_r( g_Meta.iMeta_handle, NULL, MdQueryHandler, NULL, NULL, NULL, MdTypeSwitchHandler, NULL))
	    {
		    MessagePopup ("WARNING", "META_Init_Ex_2_r Init Meta handle fail!");
		    return KAL_TRUE;
	    }
	}
	else
	{
	   if(g_SN.tTargetInfo.eTargetType == SP_DUALMODEM)
	   {	
	       pFuncName = "META_Init_Ex_r";
	       if(META_Init_Ex_r( g_Meta.iMeta_handle, NULL, MdQueryHandler, NULL, NULL, NULL))
	       {
		      MessagePopup ("WARNING", "META_Init_Ex_r Init Meta handle fail!");
		       return KAL_TRUE;
	       }
	   }
	   else
	   {
	       pFuncName = "METAAPP_Init";
	       if ( METAAPP_Init( g_Meta.iMeta_handle ) )
	       {	           
		       MessagePopup ("WARNING", "METAAPP_Init Init Meta handle fail!");
		       return KAL_TRUE;
	       }
	   }
    }
	
	sprintf ( strLog, "%s: Init Modem handle successfully, TargetStype= %d.\n", pFuncName,  g_SN.tTargetInfo.eTargetType);
	UpdateLog ( strLog, 10);
	return KAL_FALSE;
}

#endif

void MetaModemHandleDeInit () {
	
	//METAAPP_DeInit ( g_Meta.iMeta_handle );
	META_Deinit_r( &g_Meta.iMeta_handle);
}


void ResetNvramUpdateFlag ()
{
	g_Meta.bIsDatabaseInitialized[0] = KAL_FALSE;
}

void ResetNvram2UpdateFlag ()
{
	g_Meta.bIsDatabaseInitialized[2] = KAL_FALSE;
}




//--------------------------------------------------------------------------
kal_bool NvramDatabaseInit () {

	kal_uint32 db;
	kal_uint8 *dbPath = "";
	kal_uint16 MDindex = 0;
	E_TARGET_TYPE targetStype;
	META_RESULT MR;
	kal_uint8 msgStr[1024] = {'\0'};
    
	unsigned int m_uiCurNvramMdTypeIdx;
	
	if(us_temp_SWInex == 3)  //WCDMA 
	{
	    m_uiCurNvramMdTypeIdx = 0;
	}
	else if(us_temp_SWInex == 5) //TDSCDMA
	{
	    m_uiCurNvramMdTypeIdx = 1;
	}
	
	EnableTimer2 ( KAL_TRUE );

	SetStartButton_Disable ( KAL_TRUE );

	dbPath = GetModemDatabasePath();
	
	targetStype = GetTargetType();
	//sprintf ( strLog, "NvramDatabaseInit : targetStype = %d.\n", targetStype);
	//UpdateLog ( strLog, 0);
	if(targetStype == TARGET_FEATURE_PHONE || targetStype == PCMCIA_CARD)
	{
	    MR = META_NVRAM_Init_r ( g_Meta.iMeta_handle, dbPath, &db);
	    if ( META_SUCCESS == MR || META_MAUI_DB_INCONSISTENT == MR)
	   	{
		    sprintf ( strLog, "META_NVRAM_Init_r : MetaResult = %s.\n", ResultToString(MR));
	        UpdateLog ( strLog, 10);
	    }
		else
		{
		    sprintf(msgStr, "Initial Database fail: %s!, Please reselect a database.", ResultToString(MR));
		    MessagePopup ("WARNING", msgStr);
		    return KAL_TRUE;
		}
	}
	else
	{
	    if(g_SN.tTargetInfo.bWorldPhone)
	    {
	        sprintf ( strLog, "NvramDatabaseInit : us_temp_SWInex = %d.\n", us_temp_SWInex);
	        UpdateLog ( strLog, 0);
	        MR = META_NVRAM_Init_Ex_Mdtype_r( g_Meta.iMeta_handle, MDindex, m_uiCurNvramMdTypeIdx, dbPath, &db);
	    }
		else
		{
	        MR = META_NVRAM_Init_Ex_r ( g_Meta.iMeta_handle, MDindex, dbPath, &db); 
		}

		#if 0
		if(META_MAUI_DB_INCONSISTENT == MR)
		{
		   int i = -1;
		   sprintf(msgStr, "Initial Database : %s!, Would you like to ignore this warning?.", ResultToString(MR));
		   //MessagePopup ("WARNING", msgStr);		   
		   //PromptPopup("WARNING", msgStr, tmpBuf, 1024);
		   i = ConfirmPopup("WARNING", msgStr);  // "1" User selected Yes.  "0" User selected No.		   
		   if(i == 0)
		   {
		       sprintf ( strLog, "Init Database: %s, reselect a database .\n", ResultToString(MR));
	           UpdateLog ( strLog, 0);
		       return KAL_TRUE;
		   }
		}
		#endif

		if ( META_SUCCESS == MR || META_MAUI_DB_INCONSISTENT == MR)
	   	{
		    sprintf ( strLog, "META_NVRAM_Init_Ex_r : MetaResult = %s.\n", ResultToString(MR));
	        UpdateLog ( strLog, 0);
	    }
	    else
	    {
	       sprintf(msgStr, "Initial Database fail: %s!, Please reselect a database.", ResultToString(MR));
		   MessagePopup ("WARNING", msgStr);
		   return KAL_TRUE;
	    }
	}
	
    g_Meta.bIsDatabaseInitialized [0] = KAL_TRUE; 

	SetStartButton_Disable ( KAL_FALSE );		
	EnableTimer2 ( KAL_FALSE );

	sprintf ( strLog, ">>Initial Modem1 Database success!.\n%s\n", dbPath);
	UpdateLog ( strLog, 0);
    return KAL_FALSE;

}


//add by mtk71518, support SmartPhone DualModem
kal_bool Nvram2DatabaseInit () {

	kal_uint32 db;  
	kal_uint8 *dbPath = "";
	kal_uint16 MDindex = 1;

	META_RESULT MR;
	kal_uint8 msgStr[1024] = {'\0'};
	
	EnableTimer2 ( KAL_TRUE );
    SetStartButton_Disable ( KAL_TRUE );

	dbPath =  GetModem2DatabasePath();
	MR = META_NVRAM_Init_Ex_r ( g_Meta.iMeta_handle, MDindex, dbPath, &db);
	{
	    if ( META_SUCCESS != MR )
	   	{
		   sprintf(msgStr, "Initial Database fail: %s!, Please reselect a database.", ResultToString(MR));
		   MessagePopup ("WARNING", msgStr);
		   return KAL_TRUE;
	    }
	}

	g_Meta.bIsDatabaseInitialized [2] = KAL_TRUE;

	SetStartButton_Disable ( KAL_FALSE );		
	EnableTimer2 ( KAL_FALSE );

	sprintf ( strLog, ">>Initial Modem2 Database success!.\n%s\n", dbPath);
	UpdateLog ( strLog, 0);
    return KAL_FALSE;

}

//--------------------------------------------------------------------------
kal_bool IsNvramDatabaseInit (void )
{

	
	extern int Modem_Database_Select_Click_Shell ( void );	
	extern int Modem2_Database_Select_Click_Shell ( void );
	
	if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [0] ) 
	{

		if ( NvramDatabaseInit () )
		{
			sprintf ( strLog, ">>Step: Reselect Modem1 database and start to initiaize.\n");
			UpdateLog ( strLog, 0);
			Modem_Database_Select_Click_Shell ();

			return NvramDatabaseInit();
		}	
		
	}

	//Add by mtk71518 2013/02/04, support smart phone dualmodem
	/*
	if(GetTargetType() == SP_DUALMODEM)
	{
	   if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [2] ) 
	   {
		  if ( Nvram2DatabaseInit () )
		  {
			sprintf ( strLog, ">>Step: Reselect Modem2 database and start to initiaize.\n");
			UpdateLog ( strLog, 0);
			Modem2_Database_Select_Click_Shell ();
			return Nvram2DatabaseInit();
		  }			
	   }
	}
	*/
	
	return KAL_FALSE;
}

//---------------------------------------------------------------------
kal_int32 CVICALLBACK EdgeCardThread ( void *pParaData )
{ 
	BOOL fFreeResult, fRunTimeLinkSuccess = FALSE; 
	HANDLE *hCOM = pParaData;
	HINSTANCE g_hDLL;
	HINSTANCE hinstLib;
	int ( *mio_pull ) ( HANDLE handle, int which, int up );
	HANDLE ( *mio_open ) ( void );
	void ( *mio_close )( HANDLE handle );
	
	// Get a handle to the DLL module. 
	hinstLib = LoadLibrary( "miodll" ); 
	// If the handle is valid, try to get the function address. 
	if ( hinstLib != NULL ) 
	{ 
		mio_pull = ( int ( * )( HANDLE, int, int ) ) GetProcAddress ( hinstLib, "mio_pull" );            
		mio_pull ( *hCOM, 0, 1 );   //reset
		Delay ( 0.1 );
		mio_pull( *hCOM, 0, 0 ); 
		Delay ( 0.1 );      
		mio_pull ( *hCOM, 1, 1 );
		// Free the DLL module 
		fFreeResult = FreeLibrary ( hinstLib ); 
		mio_pull  = NULL;
		mio_open  = NULL;
		mio_close = NULL;
		g_hDLL    = NULL;						
	} 	
  	return 0;  
} 

//--------------------------------------------------------------------
int __stdcall cb_PowerOnOxford(HANDLE hCOM, void *usr_arg)
{
  
    EdgeCardThreadExec( hCOM );
	
    return 0;
}

void SetMetaConnectReq ( void ) 
{
	
	 
	g_MetaModem.tMETA_Connect_Req.com_port = GetCOMPort();
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_bbchip_type = GetBBChip ();    

	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_ext_clock = AUTO_DETECT_EXT_CLOCK;

	g_MetaModem.tMETA_Connect_Req.baudrate[0] = META_BAUD115200;
	g_MetaModem.tMETA_Connect_Req.baudrate[1] = META_BAUD460800;
	g_MetaModem.tMETA_Connect_Req.baudrate[2] = META_BAUD921600;
	g_MetaModem.tMETA_Connect_Req.baudrate[3] = META_BAUD_END;	

		
	g_MetaModem.tMETA_Connect_Req.flowctrl = META_SW_FLOWCTRL;
	g_MetaModem.tMETA_Connect_Req.ms_connect_timeout = META_CONNECT_TIME_OUT;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_ms_boot_timeout = BOOT_INFINITE;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_max_start_cmd_retry_count = META_BOOT_TIMERS;

	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_in_brom_stage = NULL;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_in_brom_stage_arg = NULL;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_speedup_brom_baudrate = _TRUE; //115200

	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_ready_power_on_wnd_handle = NULL;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_ready_power_on_wparam = NULL;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_ready_power_on_lparam = NULL;

	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_auth_handle = Get_AuthHandle();
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_sla_challenge = SLA_Challenge;//SLA_Challenge(NULL,NULL,0,NULL,NULL);
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_sla_challenge_arg = NULL;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_sla_challenge_end = SLA_Challenge_END; // NULL;
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_sla_challenge_end_arg = NULL;
	 
	            
	    // EDGE PC card
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_com_init_stage_arg = NULL;
	switch ( GetTargetType() )
	{
		case TARGET_FEATURE_PHONE:
			g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_com_init_stage = NULL;
			
			break;

		case TARGET_SMARTPHONE:
		case Tablet_WIFI_ONLY:
		case SP_DUALMODEM:
			g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_com_init_stage = NULL;
			break;

		case PCMCIA_CARD:
			g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_cb_com_init_stage = cb_PowerOnOxford;
			break;
			
		default:
			break;
	}
	            
	//usb mode
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_usb_enable = IsUSBCOMPort();

	g_MetaModem.usb_req.ms_connect_timeout = META_CONNECT_TIME_OUT;
	g_MetaModem.usb_req.boot_meta_arg = g_MetaModem.tMETA_Connect_Req.boot_meta_arg;
	g_MetaModem.usb_req.boot_meta_arg.m_usb_enable = IsUSBCOMPort();
	//mtk71409
	g_MetaModem.tMETA_Connect_Req.boot_meta_arg.m_enable_without_battery = g_SN.isEntryMetaWithoutBattery;

}

//---------------------------------------------------
void Seg_MetaModemConnectReq ( void ) {

//******************************************************************************** 
//*************************************************************************************** 
//-------------------Baseband chipset select----------------------------  
//*****************************************************************************************
//*************************************************************************** 
//  -----------Boot ROM and Sync with Target ----------------------
//***************************************************************************
	
    g_Meta6516Modem.tMETA_Connect_Req.com_port = GetCOMPort();
    g_Meta6516Modem.tMETA_Connect_Req.baudrate[0] = META_BAUD115200;
    g_Meta6516Modem.tMETA_Connect_Req.baudrate[1] = META_BAUD460800;
    g_Meta6516Modem.tMETA_Connect_Req.baudrate[2] = META_BAUD921600;
    g_Meta6516Modem.tMETA_Connect_Req.baudrate[3] = META_BAUD_END;	
	
    g_Meta6516Modem.tMETA_Connect_Req.flowctrl = META_SW_FLOWCTRL;
    g_Meta6516Modem.tMETA_Connect_Req.ms_connect_timeout = META_CONNECT_TIME_OUT;
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



void Sp_ModemDebugOn(void)
{
      if ( GetIsEnableMetaLog() )
	{
		META_DebugOn ();
	    Brom_DebugOn();		
	}
	else
	{
		META_DebugOff ();
	    Brom_DebugOff();
	}

}









//----------------------------------------------------------------------
kal_bool Exit_MetaModemMode ( void )
{
	METAAPP_DisconnectWithTarget ( g_Meta.iMeta_handle );

	META_ShutDownTarget_r ( g_Meta.iMeta_handle );
	//MetaModemHandleDeInit ();
	//MetaAPHandleDeInit ();

	return META_SUCCESS;
};

//----------------------------------------------------------------------
//return KAL_FALSE -> Success
//return KAL_TURE  -> ERROR
kal_bool EnterMetaModemMode ( void )
{   
	Meta_Boot_Arg meta_arg;
	EBOOT_RESULT Eboot_Result;
	META_ConnectByUSB_Req usbRequest;
    META_ConnectByUSB_Report usbReport;
    int iRet;
    kal_uint32  BootStop;
   
	MetaModemHandleInit ();  //Move here because New META DLL for different platform need different InitHandle API
	/*
	MetaAPHandleInit();
	*/
	
    // ***********************************************
    // Search  preloader or brom COM port for META connection  and handshake with preloader
    // *********************************************** 
    sprintf ( strLog,  " COM port searching and preloader handshake...\n");	
    UpdateLog ( strLog, 10 );
    Connect_with_preloader(NULL); 
    
	if(search_preloader_port_success==0)  
	{
         sprintf ( strLog,  " COM port searching and preloader handshake  fail\n");	
         UpdateLog ( strLog, 10 );	
	     return KAL_TRUE;	
    }
	sprintf ( strLog,  " COM port searching and preloader handshake ok\n");	
    UpdateLog ( strLog, 10 );

    // ***********************************************
    // ***kernel  COM port searching and Kernel handshake ***
    // ***********************************************
    sprintf ( strLog,  " COM port searching and Kernel handshake...\n");	
    UpdateLog ( strLog, 10 );	
    search_kernel_port(NULL);

    if(search_kernel_port_success==0)
	     return KAL_TRUE;
         
    if(IsUSBCOMPort())
    {
       Delay(1.0);//delay for USB com port ready
       usbRequest.com_port = usb_port;
       usbRequest.ms_connect_timeout = g_Meta6516Modem.tMETA_Connect_Req.ms_connect_timeout;
       g_Meta6516Modem.eMeta_Result = META_ConnectInMetaModeByUSB_r(g_Meta.iMeta_handle, &usbRequest, &g_Meta.bootstop, &usbReport);
    }
    else
    {
       //Delay(1.0);  
	   g_Meta6516Modem.eMeta_Result = META_ConnectInMetaMode_r (g_Meta.iMeta_handle, &g_Meta6516Modem.tMETA_Connect_Req, &g_Meta.bootstop, &g_Meta6516Modem.tMETA_Connect_Report); 
    }

    if(g_Meta6516Modem.eMeta_Result != META_SUCCESS && g_Meta6516Modem.eMeta_Result != META_MAUI_DB_INCONSISTENT)
    {
	    sprintf ( strLog, "SP_META_ConnectInMetaMode_r Error: maybe is %s cause this error...\n", ResultToString(g_Meta6516Modem.eMeta_Result));
	    UpdateLog ( strLog, 30 );
	    return KAL_TRUE;
	}
	else
	{
	    return KAL_FALSE;
	}
};

//----------------------------------------------------------------------
kal_bool EnterMetaMode () 
{
	 META_RESULT  META_Result;
	 kal_char info[1000];
	 

	if ( GetIsEnableMetaLog() )
	{
		Brom_DebugOn ();
		META_DebugOn ();
	}
	else
	{
		Brom_DebugOff ();
		META_DebugOff ();
	}

	MetaModemHandleInit(); //Move here because New META DLL for different platform need different InitHandle API
	
	if ( !IsUSBCOMPort() )
	{
		//----------------------------Meta Connect to target-------------
		g_MetaModem.eMetaApp_Result = METAAPP_ConnectWithTarget (g_Meta.iMeta_handle, &g_MetaModem.tMETA_Connect_Req, &g_Meta.bootstop, &g_MetaModem.tMETA_Connect_Report); 

		switch ( g_MetaModem.eMetaApp_Result )
		{
			case METAAPP_SUCCESS:

				 return KAL_FALSE; 
				 break;
				 
			case METAAPP_NVRAM_DB_INCONSISTENT:
				
			 	MessagePopup ("Meta Warning", "Modem NVRAM database inconsistent with target...");
				break;

			case METAAPP_OPEN_UART_FAIL:

				MessagePopup ("Meta Error", "Open COM port fail...");
				break;

			case METAAPP_COM_ERROR:

				MessagePopup ("Meta Error", "COM port doesn't exist...");
				break;

			case METAAPP_TIMEOUT_FAIL:	

				MessagePopup ("Meta Error", "Connecting timeout...");
				break;

			case 	METAAPP_BOOT_FAIL:
				MessagePopup ("Meta Error", "Can't connect to target.\nPlease Enable Meta Dll.Log to get detail cause... ");
				break;

			default: 
				break;
		}	

	} 
	else
	{    
	    if(g_SN.bEnableSwitchDataCard)
		{
		    strcat ( strLog,  "Begin get dynamic USB comport... \n");
	        UpdateLog ( strLog, 0 );
            read_PidFilter(valid_usb_info);				 
		    META_Result = META_GetDynamicUSBComPortExWithFilter_r( g_Meta.iMeta_handle, g_MetaModem.usb_req.ms_connect_timeout, (kal_uint16*)&g_MetaModem.usb_req.com_port, &g_Meta.bootstop, info, 1000, valid_usb_info);
		}
		else if(g_SN.isEntryDualTalk)      //mtk71409 added by JiXiang
		{
			//add for DualTalk,2013-06-26 mtk71518
	        SP_BOOT_ARG_S stArg;
	        int BootStop = SP_BOOT_INFINITE;
	        int ret = S_DONE;
		    char asBROMPortFilter[100];
            char asPreloaderPortFilter[100];

			 //Parameter settings
			stArg.m_bbchip_type = SP_AUTO_DETECT_BBCHIP;
			stArg.m_ext_clock = SP_AUTO_DETECT_EXT_CLOCK;
			stArg.m_ms_boot_timeout = SP_BOOT_INFINITE;
			stArg.m_max_start_cmd_retry_count = SP_DEFAULT_BROM_START_CMD_RETRY_COUNT;

			stArg.m_uTimeout = 20000;
			stArg.m_uRetryTime = 2000;
			stArg.m_uInterval = 10;
			stArg.m_uBaudrate = CBR_115200;

			stArg.m_auth_handle = NULL;
			stArg.m_scert_handle = NULL;
			stArg.m_cb_sla_challenge = NULL;
			stArg.m_cb_sla_challenge_arg = NULL;
			stArg.m_cb_sla_challenge_end = NULL;
			stArg.m_cb_sla_challenge_end_arg = NULL;

			stArg.m_pStopFlag = &BootStop;
			stArg.m_bIsUSBEnable = KAL_TRUE;
			stArg.m_bIsSymbolicEnable = KAL_FALSE;
			stArg.m_bIsCompositeDeviceEnable = KAL_TRUE;
			stArg.m_euBootMode = SP_DUALTALK_SWITCH;
			//stArg.m_uPortNumber = us_com_port;
			memset(stArg.m_szPortSymbolic, 0, 256);

			read_SpBromPortFilter(asBROMPortFilter);
	        read_SpPreloaderPortFilter(asPreloaderPortFilter);

			// step1: Get Preloader Port
			sprintf( strLog,  " step1: Get Preloader Port...\n");
	        UpdateLog ( strLog, 0 );
			
		    META_Result = META_GetDynamicUSBComPortExWithFilter_r( g_Meta.iMeta_handle, g_MetaModem.usb_req.ms_connect_timeout, (kal_uint16*)&g_MetaModem.usb_req.com_port, &g_Meta.bootstop, info, 1000, asPreloaderPortFilter);
			if(META_SUCCESS != META_Result)
			{
                sprintf ( strLog,  " Get Preloader Port error\n");
	            UpdateLog ( strLog, 0 );
				return KAL_TRUE; 
                            
			}
			
			sprintf( strLog,  "Get Preloader Port OK\n");
	        UpdateLog ( strLog, 0 );
	
			// step2: Switch to Modem
			sprintf ( strLog,  "step2: Switch to Modem...\n");
	        UpdateLog ( strLog, 0 );
			
			//if (EBOOT_SUCCESS != SP_SwitchModem(g_MetaModem.usb_req.com_port, BAUD115200,  &g_Meta.bootstop))
		    stArg.m_uPortNumber = g_MetaModem.usb_req.com_port;
			if(0 != SP_Preloader_BootMode(&stArg)) // change to flashtoollib api,2013-06-26,mtk71518
			{     
			    sprintf ( strLog,  " Switch to Modem error\n");
	            UpdateLog ( strLog, 0 );
				return KAL_TRUE; 
				
			}

		       sprintf( strLog,  "Switch to Modem OK\n");
	              UpdateLog ( strLog, 0 );
			
			// step3: Get Modem Brom Port

			//Delay(20.0); //can't delay?
			sprintf ( strLog,  "step3: Get Modem Brom Port...\n");
	        UpdateLog ( strLog, 0 );
			
			META_Result = META_GetDynamicUSBComPortExWithFilter_r( g_Meta.iMeta_handle, g_MetaModem.usb_req.ms_connect_timeout, (kal_uint16*)&g_MetaModem.usb_req.com_port, &g_Meta.bootstop, info, 512, asBROMPortFilter);
			if(META_SUCCESS != META_Result)
			{

                sprintf ( strLog,  " Get Modem Brom Port error\n");
	            UpdateLog ( strLog, 0 );
				return KAL_TRUE; 
			}

		}//mtk71409  added by JiXiang
        else
        {
		    META_Result = META_GetDynamicUSBComPort_r (g_Meta.iMeta_handle, g_MetaModem.usb_req.ms_connect_timeout, (kal_uint16*)&g_MetaModem.usb_req.com_port,&g_Meta.bootstop);
        }

			  
		if ((META_Result != META_SUCCESS) && (META_Result == META_STOP_ENUM_USB_PROCEDURE))
		{
			MessagePopup ( "Meta Warning",  "Get dynamic USB COM fail, please Reconnect to target" );
        }
		else
	    {
	        sprintf ( strLog,  "Get Modem Brom Port  OK!\n");
	        UpdateLog ( strLog, 0 );
			
			sprintf ( strLog,  "  Begin to enter meta mode use META_ConnectWithTargetByUSB_r...!\n");
	        UpdateLog ( strLog, 0 );
	    }
		
		if (META_SUCCESS == META_Result)
		{
			META_Result = META_ConnectWithTargetByUSB_r (g_Meta.iMeta_handle, &g_MetaModem.usb_req,  &g_Meta.bootstop, &g_MetaModem.usb_report);
			if ((g_MetaModem.usb_report.boot_meta_ret != S_DONE) && (g_MetaModem.usb_report.boot_meta_ret != S_STOP) && (g_MetaModem.usb_report.boot_meta_ret != S_BROM_FAIL_TO_GET_BBCHIP_HW_VER))
			{
			       MessagePopup ("Meta Error", "Connecting timeout...");
			}
			else if ((META_Result == META_SUCCESS) || META_Result == META_MAUI_DB_INCONSISTENT)
			{
				return KAL_FALSE; 
			}
			else
			{
			     sprintf ( strLog, "Error: maybe is %s cause this error...\n", ResultToString(META_Result));
	             UpdateLog ( strLog, 30 );				 
			}
		}
	}
	return KAL_TRUE;

}
//----------------------------------------------------------------------
kal_bool ExitMetaMode ( void ) {

	return METAAPP_DisconnectWithTarget( g_Meta.iMeta_handle );
}


//-----------------------------------------------------------------------
kal_int8 Ascii2BCD ( kal_uint8 iAscii )
{
	kal_uint8 iBCD;
	if ( iAscii>= '0' && iAscii<= '9')
	{
        iBCD = iAscii - '0';
			
	} else if ( iAscii>= 'a' && iAscii<= 'f' )
	{
        iBCD = iAscii - 'a' + 0x0a;
		
	} else if ( iAscii>= 'A' && iAscii<= 'F' )
	{
        iBCD = iAscii - 'A' + 0x0a;
	} else
	{
		return -1;
	}

	return iBCD;

}

//----------------------------------------------------------------------
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
static void __stdcall CNF_ReadFromNVRAM(const FT_NVRAM_READ_CNF *cnf, const short token, void *usrData)
{
     if (cnf->status != META_SUCCESS)
    {  
       	ConfirmCallback (META_FAILED);  
		return; 
	}
	
	SetEvent (g_MetaModem.m_ReadFromNVRAMEvent);   
}
//-----------------------------------------------
static  void __stdcall CNF_WriteNVRAM ( const FT_NVRAM_WRITE_CNF *cnf, const short token, void *usrData)
{
    if (cnf->status != META_SUCCESS)
    {  
    	 ConfirmCallback (META_FAILED);  
		return; 
	}
	SetEvent (g_MetaModem.m_WriteToNVRAMEvent);   

}

//-----------------------------------------------
static META_RESULT REQ_WriteNVRAM(void)
{
       kal_int16 m_sNVRAM_OPID;
	DWORD wait_result;
	
	
   
    g_MetaModem.m_WriteToNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

    ResetEvent ( g_MetaModem.m_WriteToNVRAMEvent );

    g_MetaModem.eMeta_Result = META_NVRAM_Write_r ( g_Meta.iMeta_handle,
                                                   &g_MetaModem.tNVRAM_WriteReq,
                                                   CNF_WriteNVRAM,
                                                   &m_sNVRAM_OPID,
                                                   NULL);


    wait_result = WaitForSingleObject ( g_MetaModem.m_WriteToNVRAMEvent, 15000 );
	
    //CloseHandle ( g_MetaModem.m_WriteToNVRAMEvent );
	
    if ( WAIT_TIMEOUT == wait_result )
    {
        ConfirmCallback ( META_TIMEOUT );
        return META_TIMEOUT;
    }

    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        return g_MetaModem.eMeta_Result;
    }
    return META_SUCCESS;
}


//-----------------------------------------------
static META_RESULT REQ_ReadFromNVRAM ( void )
{
    DWORD wait_result;
	kal_int16 m_sNVRAM_OPID;
	 
    g_MetaModem.m_ReadFromNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	
    ResetEvent ( g_MetaModem.m_ReadFromNVRAMEvent );

    g_MetaModem.eMeta_Result = META_NVRAM_Read_r ( g_Meta.iMeta_handle,
                                	          &g_MetaModem.tNVRAM_ReadReq,
                                              &g_MetaModem.tNVRAM_ReadCnf,
                                              CNF_ReadFromNVRAM,
                                              &m_sNVRAM_OPID,
                                              NULL );

    wait_result = WaitForSingleObject ( g_MetaModem.m_ReadFromNVRAMEvent, 15000 );

    //CloseHandle ( g_MetaModem.m_ReadFromNVRAMEvent );
    if ( WAIT_TIMEOUT == wait_result )
    {
        ConfirmCallback ( META_TIMEOUT );
        return META_TIMEOUT;
    }

    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        return g_MetaModem.eMeta_Result;
    }

    return META_SUCCESS;
}

//===========================================================================
META_RESULT REQ_ReadBT6611AddrFromNVRAM_Start ( kal_uint32 iBTId, kal_uint8* pBTAddress )
{
    kal_int32 m_usRID = 1, m_iBTBufSize;
	kal_uint8 *pLID;
	nvram_ef_btradio_mt6611_struct  tBT;
      nvram_ef_btradio_mtk_bt_chip_struct tBT1;
       kal_int32  isbt=0;
	
	switch ( iBTId )	
	{
		case BTMODULE_MT6611:
			pLID = "NVRAM_EF_BTRADIO_MT6611_LID"; 
			break;

		case BTMODULE_MT6612:
			pLID="NVRAM_EF_BTRADIO_MT6612_LID";
			if(META_NVRAM_QueryIsLIDExist(pLID))
			{
			isbt=1;
			pLID= "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			}
			break;
			
		case BTMODULE_MT6616:
			pLID = "NVRAM_EF_BTRADIO_MT6616_LID"; 
			break;
			
		case BTMODULE_MT6622:
		case BTMODULE_MT6250:
		case BTMODULE_MT6260:
		case BTMODULE_MT6276:
			pLID = "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			break;
			
		default:
			pLID = "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			break;
	}
	if(MT6236 == g_MetaModem.tMETA_Connect_Report.boot_result.m_bbchip_type||g_MetaModem.usb_report.boot_result.m_bbchip_type==MT6236)
     { isbt=0;
      	if(META_NVRAM_QueryIsLIDExist(pLID))
	{
      pLID="NVRAM_EF_BTRADIO_MT6236_LID"; 
	}    
     }  
    g_MetaModem.eMeta_Result = META_NVRAM_GetRecLen( pLID, &m_iBTBufSize);
    if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }

	if ( NULL != g_MetaModem.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaModem.tNVRAM_ReadCnf.buf );	
	}

	g_MetaModem.tNVRAM_ReadReq.LID = pLID;
       g_MetaModem.tNVRAM_ReadReq.RID = m_usRID;
      g_MetaModem.tNVRAM_ReadCnf.len = m_iBTBufSize;
      g_MetaModem.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );

	g_MetaModem.eMeta_Result =  REQ_ReadFromNVRAM ();
	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }

	if(isbt==0)
       {
	g_MetaModem.eMeta_Result = META_NVRAM_BT_Decompose_MT6611Radio ( &tBT, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
       }
      else
      	{
      	g_MetaModem.eMeta_Result = META_NVRAM_BT_Decompose_MediatekBtChip ( &tBT1, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
      	}

	  if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
       {
    	return g_MetaModem.eMeta_Result;
       }
	if(isbt==0)
       {
	memcpy ( pBTAddress,  tBT.BDAddr, BD_ADDR_LEN ); 
	
        }
	else
	{
	memcpy ( pBTAddress,  tBT1.BDAddr, BD_ADDR_LEN ); 
	}
	free (g_MetaModem.tNVRAM_ReadCnf.buf);
	
	return g_MetaModem.eMeta_Result;
}

//===========================================================================
META_RESULT REQ_WriteBT6611Addr2NVRAM_Start (kal_uint32 iBTId, kal_uint8* pBTAddress)
{
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID;
    nvram_ef_btradio_mt6611_struct  tBT;
     nvram_ef_btradio_mtk_bt_chip_struct tBT1;
     kal_int32  isbt=0;
	
	switch ( iBTId )	
	{
		case BTMODULE_MT6611:
			pLID = "NVRAM_EF_BTRADIO_MT6611_LID"; 
			break;
			
		case BTMODULE_MT6612:
			pLID="NVRAM_EF_BTRADIO_MT6612_LID";
			if(META_NVRAM_QueryIsLIDExist(pLID))
			{
			isbt=1;
			pLID= "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			}
			
			break;
			
		case BTMODULE_MT6616:
			pLID = "NVRAM_EF_BTRADIO_MT6616_LID"; 
			break;
			
		case BTMODULE_MT6622:
		case BTMODULE_MT6250:
		case BTMODULE_MT6260:
		case BTMODULE_MT6276:
			pLID = "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			break;

		default:
			pLID = "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			break;
	}
	
    if(MT6236 == g_MetaModem.tMETA_Connect_Report.boot_result.m_bbchip_type||g_MetaModem.usb_report.boot_result.m_bbchip_type==MT6236)
     { isbt=0;
	if(META_NVRAM_QueryIsLIDExist(pLID))
	{
      pLID="NVRAM_EF_BTRADIO_MT6236_LID"; 
	}
     }  
	g_MetaModem.eMeta_Result = META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );
    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        //TODO: LOG
        return g_MetaModem.eMeta_Result;
    }

	if ( NULL != g_MetaModem.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaModem.tNVRAM_ReadCnf.buf );	
	}

	g_MetaModem.tNVRAM_ReadReq.LID = pLID;
        g_MetaModem.tNVRAM_ReadReq.RID = m_usRID;
       g_MetaModem.tNVRAM_ReadCnf.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

	g_MetaModem.eMeta_Result =  REQ_ReadFromNVRAM ();
	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }


     if(isbt==0)
       {
	g_MetaModem.eMeta_Result = META_NVRAM_BT_Decompose_MT6611Radio ( &tBT, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
       }
      else
      	{
      	g_MetaModem.eMeta_Result = META_NVRAM_BT_Decompose_MediatekBtChip ( &tBT1, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
      	}

	
	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }
	
	if(isbt==0)
       {
	memcpy ( tBT.BDAddr, pBTAddress, BD_ADDR_LEN ); 
        }
	else
	{
	memcpy ( tBT1.BDAddr, pBTAddress, BD_ADDR_LEN ); 
	}
	
	if (NULL != g_MetaModem.tNVRAM_WriteReq.buf)
	{
		free (g_MetaModem.tNVRAM_WriteReq.buf);	
	}

	switch ( iBTId )	
	{
		case BTMODULE_MT6601:  //6601
			pLID = "NVRAM_EF_BTRADIO_MT6601_LID";
			break;
			
		case BTMODULE_MT6611:
			pLID = "NVRAM_EF_BTRADIO_MT6611_LID"; 

		case BTMODULE_MT6612:
			pLID="NVRAM_EF_BTRADIO_MT6612_LID";
			if(META_NVRAM_QueryIsLIDExist(pLID))
			{
			isbt=1;
			pLID= "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			}
			
			break;
		case BTMODULE_MT6616:
			pLID = "NVRAM_EF_BTRADIO_MT6616_LID"; 
			break;
		case BTMODULE_MT6622:
		case BTMODULE_MT6250:
		case BTMODULE_MT6276:
			pLID = "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			break;

		default:
			pLID = "NVRAM_EF_BTRADIO_MTK_BT_CHIP_LID";
			break;
	}
	if(MT6236 == g_MetaModem.tMETA_Connect_Report.boot_result.m_bbchip_type||g_MetaModem.usb_report.boot_result.m_bbchip_type==MT6236)
        { isbt=0;
          	if(META_NVRAM_QueryIsLIDExist(pLID))
	      {
              pLID="NVRAM_EF_BTRADIO_MT6236_LID"; 
	       }  
  	     }    
	g_MetaModem.eMeta_Result = META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );
    	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
      {
        //TODO: LOG
        return g_MetaModem.eMeta_Result;
      }

	m_usRID = 1;
	g_MetaModem.tNVRAM_WriteReq.LID = pLID;
       g_MetaModem.tNVRAM_WriteReq.RID = m_usRID;
       g_MetaModem.tNVRAM_WriteReq.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_WriteReq.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );

	if(isbt==0)
       {
	g_MetaModem.eMeta_Result = META_NVRAM_BT_Compose_MT6611Radio ( &tBT, g_MetaModem.tNVRAM_WriteReq.buf, m_iBTBufSize);
       }
      else
      	{
      	g_MetaModem.eMeta_Result = META_NVRAM_BT_Compose_MediatekBtChip ( &tBT1, g_MetaModem.tNVRAM_WriteReq.buf, m_iBTBufSize);
      	}

 	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
      {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
      }


	g_MetaModem.eMeta_Result = REQ_WriteNVRAM ();
    
	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }
	
    return META_SUCCESS;
}

//----------------------------------------------------------------------


META_RESULT REQ_WriteCDrom_Start (kal_uint8 mode)
{   
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID;
    //port_setting_struct_1 tport;
     port_setting_struct  tport;
    pLID = "NVRAM_EF_PORT_SETTING_LID"; 	 
   g_MetaModem.eMeta_Result = META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );	  
    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
    }

	if ( NULL != g_MetaModem.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaModem.tNVRAM_ReadCnf.buf );	
	}

	g_MetaModem.tNVRAM_ReadReq.LID = pLID;
        g_MetaModem.tNVRAM_ReadReq.RID = m_usRID;
       g_MetaModem.tNVRAM_ReadCnf.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

	g_MetaModem.eMeta_Result =  REQ_ReadFromNVRAM ();

	
	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }
    g_MetaModem.tNVRAM_ReadCnf.buf[36]=mode;

	   /*
         g_MetaModem.eMeta_Result = META_NVRAM_Decompose_PortSetting ( &tport, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
      	
  	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
      {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
      }
	  */
      // memcpy(&tport,g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);//有问题
	//memcpy ( &tport.usb_cdrom_config, &mode, 1 ); 
	if (NULL != g_MetaModem.tNVRAM_WriteReq.buf)
	{
		free (g_MetaModem.tNVRAM_WriteReq.buf);	
	}
	g_MetaModem.tNVRAM_WriteReq.LID = pLID;
       g_MetaModem.tNVRAM_WriteReq.RID = m_usRID;
       g_MetaModem.tNVRAM_WriteReq.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_WriteReq.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );
		memcpy( g_MetaModem.tNVRAM_WriteReq.buf, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	
	//memcpy(g_MetaModem.tNVRAM_WriteReq.buf,g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	g_MetaModem.eMeta_Result = REQ_WriteNVRAM ();
    
	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
    
    	return g_MetaModem.eMeta_Result;
    }
    return META_SUCCESS;
	
}



/**************************************************************************
void func_combine_meta_hdlr_smart_phone_modem (){

	kal_uint8 strTip [256];
	kal_uint8 strBarcode_W [ BARCODE_MAX_LENGTH + 1 ];
	kal_uint8 strBarcode_R [ BARCODE_MAX_LENGTH + 1 ];
	kal_uint16 iLoop = 0;
	kal_uint32 BackupSecondImei;
	
	sprintf ( strLog, ">>Step: Enter func_combine_meta_hdlr_smart_phone_modem();\n");
	strcat ( strLog,  "        Write data prefer\call prefer  to smartphone modem nvram\n");
	UpdateLog ( strLog, 0 );
	
	sprintf ( strLog, ">>Step: Start to Init Modem Nvram Database...\n");
	UpdateLog ( strLog, 20 );
	
	if ( IsNvramDatabaseInit () ) 
	{
		sprintf ( strLog, "   Error: Init Modem Nvram Database failed.\n");
		UpdateLog ( strLog, 100);
		return;
	}
	
	sprintf ( strLog, "   OK: Init Modem Nvram Database successfully.\n");
	UpdateLog ( strLog, 100 );

	GetUISetCleanBootFlag(KAL_TRUE, &BackupSecondImei);
	
	Seg_MetaModemConnectReq ();
	
	g_Meta6516Modem.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_Meta6516Modem.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{
		sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );	

		
		ResetIndicator ();
		
		if ( iLoop++ == 50)
		{
			ClearLog ();
			iLoop = 0;
		}
		
		       sprintf ( strLog, ">>Step: Start to Connect with target.\n" );
			UpdateLog ( strLog, 30 );
					
		       if ( EnterMetaModemMode () ) 
			{
				Exit_MetaModemMode ();
				
				sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode and turn to next phone.\n" );
				UpdateLog ( strLog, 100 );
				
				UpdateIndicator ( KAL_FALSE );
				continue; 
			}

			sprintf ( strLog,  ">>Step: Start to Write data prefer\call prefer" );
			UpdateLog ( strLog, 50 );
			
            if(GetIsDataCall())
      	    {
	              if(GetIsDataprefer())
	             {
	                    SetDataCall=0x00;
                           sprintf ( strLog, ">> Set DATA_prefer\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				return;
				 }   
	             }
		      else
		      	{
                           SetDataCall=0x01;
      	                    sprintf ( strLog, ">> Set CALL_prefer\n");
	                    UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set CALL_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to Set  CALL_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				return;
				 } 

				
		      	}
		
      	}

		g_Meta6516Modem.eMeta_Result = META_DisconnectInMetaMode_r ( g_Meta.iMeta_handle );
		switch ( g_Meta6516Modem.eMeta_Result )
		{
			case METAAPP_SUCCESS:
				sprintf ( strLog, "   OK: META_DisconnectInMetaMode_r() \n"  );
				UpdateLog ( strLog, 85 );	
				break;
				
			default: 
				sprintf ( strLog, "   Error: META_DisconnectInMetaMode_r(). Meta Result = %d\n", g_Meta6516Modem.eMeta_Result );
				UpdateLog ( strLog, 100 );	
				UpdateIndicator ( KAL_FALSE );
				break;	
		}
		if ( Switch2WM_META_Mode ( g_Meta.iMeta_handle ) )
		{
			sprintf ( strLog, "   Error: Switch2WM_META_Mode()\n" );
			UpdateLog ( strLog, 100 );	
			UpdateIndicator ( KAL_FALSE );
		}
		else
		{
			sprintf ( strLog, "   OK: Switch2WM_META_Mode() \n" );
			UpdateLog ( strLog, 90 );
		}

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
		Exit_MetaAPMode ();
	}//while ()
}


******************************************************************************/
/*
Before write barcode, need backup cal & FT test flag
Avoid rewrite barcode drop these flag
Add by mtk71518, 2013-09-30
*/
void ConstructBarcode(kal_uint8* pOutData, const kal_uint8* pInData, const kal_uint8* pScanData, const kal_uint32 dataLength)
{
	int i = 0;
    char calFlag[2] = {0};
	char ftFlag;

	calFlag[0] = pInData[60];  //pInData read from nvram, get cal & FT test flag
	calFlag[1] = pInData[61];
    ftFlag = pInData[62];

	memset(pOutData, 0x20, 64);
	strncpy(pOutData, pScanData, dataLength);
	
	pOutData[60] = calFlag[0]; //pOutData will be writed to nvram
	pOutData[61] = calFlag[1];
    pOutData[62] = ftFlag;

	pOutData[63] = '\0';

}

int func_barcode_imei_meta_hdlr_smart_phone_ap ()
{
	kal_uint8 strTip [256];
	extern kal_char BarCode[64];
	extern kal_char imei[4][16];
	kal_char Imei_R[4][16] = {0};
	kal_uint8 strBarcode_R [ BARCODE_MAX_LENGTH] = {0};
	kal_uint16 iLoop = 0;
	kal_uint32 BackupSecondImei;

	int Meta_Result = 0;
	int imeiNums = g_SN.tIMEI.eImeiNum;
	int imeiIndex = 0;

	kal_uint8 strBarcode_W [ BARCODE_MAX_LENGTH];
	int dataLength = 0;
	int i = 0;
	char calFlag[2] = {0};
    char ftFlag;
  
	
	//kal_char **ppImei;
	//kal_char *pImei[] = {"123", "456", "789"};
	//ppImei = &pImei[0];
    //ppImei = pImei;
		
	sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
	UpdateLog ( strLog, 100 );
    sprintf ( strLog, "\n>>Step: Enter func_barcode_imei_meta_hdlr_smart_phone_ap();\n");
	strcat ( strLog,  "        Write BarCode&Imei to smart phone product_info\n");
	UpdateLog ( strLog, 100 );

	if(g_SN.tFuncMode.eFuncType.bBarCode)
	{
	   sprintf ( strLog, "Start to write Barcode to prod_info.\n"  );
	   UpdateLog ( strLog, 80 );	

	   if ( Meta_Result = REQ_ReadBarcodeFromNVRAM_Start (strBarcode_R) )
       {
		  sprintf ( strLog, "    Error: Read Barcode from AP Nvram  fail.\n Meta Result = %s\n", ResultToString(Meta_Result) );
		  UpdateLog ( strLog, 100 );
		  UpdateIndicator ( KAL_FALSE );
		  Exit_MetaAPMode ();   
		  return KAL_TRUE;
	   }
	   else
	   {
	       dataLength = strlen(BarCode);
	       ConstructBarcode(strBarcode_W, strBarcode_R, BarCode, dataLength); 
	   }
	   /*
	   else
	   {
	        calFlag[0] = strBarcode_R[60];
		    calFlag[1] = strBarcode_R[61];
			ftFlag = strBarcode_R[62];
	   }

	   memset(strBarcode_W, 0x20, 64);
	   dataLength = strlen(BarCode);
	   strncpy(strBarcode_W, BarCode, dataLength);
	   strBarcode_W[60] = calFlag[0];
	   strBarcode_W[61] = calFlag[1];
         strBarcode_W[62] = ftFlag;
       */
	   
	   if (Meta_Result = REQ_WriteBarcode2NVRAM_Start (strBarcode_W) )
	   {
		  sprintf ( strLog, "   Error: Write Barcode to AP Nvram fail.\n Meta Result = %s\n", ResultToString(Meta_Result) );
	      UpdateLog ( strLog, 100 );
		  UpdateIndicator ( KAL_FALSE );
						
		  Exit_MetaAPMode ();
	      return KAL_TRUE;
	   }
	   sprintf ( strLog, "    OK: Write Barcode to AP Nvram  successfully.\n"  );
	   UpdateLog ( strLog, 70 );	

	   sprintf ( strLog, "Start to check Barcode.\n"  );
	   UpdateLog ( strLog, 80 );	
						
	   if ( Meta_Result = REQ_ReadBarcodeFromNVRAM_Start (strBarcode_R) )
       {
		  sprintf ( strLog, "    Error: Read Barcode from AP Nvram  fail.\n Meta Result = %s\n", ResultToString(Meta_Result) );
		  UpdateLog ( strLog, 100 );
		  UpdateIndicator ( KAL_FALSE );
		  Exit_MetaAPMode ();   
		  return KAL_TRUE;
	   }

	   if ( strncmp ( strBarcode_R, strBarcode_W, dataLength))
	   {
		   sprintf ( strLog, "   Error: Check Barcode fail. Rd_Barcode = \"%s\".\n.", strBarcode_R );
		   UpdateLog ( strLog, 100 );
				
		   UpdateIndicator ( KAL_FALSE );								
		   Exit_MetaAPMode ();   
		   return KAL_TRUE;
	   }
	   else
	   {
		   sprintf ( strLog, "   OK: Check Barcode. Rd_Barcode = \"%s\".\n.", BarCode);
		   UpdateLog ( strLog, 70 );
	   }
	}

    // add mtk71518, 2013-07-09, write imei to product_info
	if(g_SN.tFuncMode.eFuncType.bIMEI)
	{
	   sprintf ( strLog, "Start to write IMEI to prod_info\n" );
	   UpdateLog ( strLog, 70 );
	   
	   if(Meta_Result = REQ_WriteImei2NVRAM_Start(imei, imeiNums))
	   {
	       sprintf ( strLog, "    Error: Write IMEI to AP Nvram fail.\n Meta Result = %s\n", ResultToString(Meta_Result) );
		   UpdateLog ( strLog, 100 );
		   UpdateIndicator ( KAL_FALSE );
		   Exit_MetaAPMode ();   
		   return KAL_TRUE;
	   }
	   sprintf ( strLog, "    OK: Write IMEI to AP Nvram  successfully.\n"  );
	   UpdateLog ( strLog, 70 );	

	   sprintf ( strLog, "Start to check IMEI.\n"  );
	   UpdateLog ( strLog, 80 );	
						
	   if ( Meta_Result = REQ_ReadImeiFromNVRAM_Start(Imei_R, imeiNums) )
       {
		   sprintf ( strLog, "    Error: Read IMEI from AP Nvram  fail.\n Meta Result = %s\n", ResultToString(Meta_Result) );
		   UpdateLog ( strLog, 100 );
		   UpdateIndicator ( KAL_FALSE );
		   Exit_MetaAPMode ();   
		   return KAL_TRUE;
	   }

	   for(imeiIndex = 0; imeiIndex < imeiNums; imeiIndex++)
	   {
	       if ( strcmp ( Imei_R[imeiIndex], imei[imeiIndex]))
	       {
		       sprintf ( strLog, "   Error: Check IMEI fail. Rd_IMEI[%d] = \"%s\".\n.", imeiIndex, Imei_R[imeiIndex] );
		       UpdateLog ( strLog, 100 );
				
		       UpdateIndicator ( KAL_FALSE );							
		       Exit_MetaAPMode ();   
		       return KAL_TRUE;
	       }
	       else
	       {
		       sprintf ( strLog, "   OK: Check IMEI. Rd_IMEI[%d] = \"%s\".\n.", imeiIndex, Imei_R[imeiIndex] );
		       UpdateLog ( strLog, 70 );
	       }
	   }   
	}
            
	if(GetIsDataCall())//?????????????????????????????????????????????????????????
    {
	    if(GetIsDataprefer())
	    {
	        SetDataCall=0x00;
            sprintf ( strLog, ">> Set DATA_prefer\n");
	        UpdateLog ( strLog, 10 );
            if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			{
				sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_TRUE );
			} 
			else 
			{
				sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_FALSE );
				return KAL_TRUE;
			}   
	    }
		else
		{
            SetDataCall=0x01;
      	    sprintf ( strLog, ">> Set CALL_prefer\n");
	        UpdateLog ( strLog, 10 );
			
            if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			{
				sprintf ( strLog, "    OK: Set CALL_prefer ok\n");
	        	UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_TRUE );
			} 
			else 
			{
				sprintf ( strLog,  "   Error ,fail to Set  CALL_prefer\n" );
				UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_FALSE );
				return KAL_TRUE;
			} 				
		}		
    }			   
}

//===========================================================================
int  func_barcode_meta_hdlr_smart_phone_modem (E_TARGET_TYPE targetStype){

    
	kal_uint8 strTip [256];
	extern kal_char BarCode[64];
	kal_uint8 strBarcode_R [ BARCODE_MAX_LENGTH];
	
	kal_uint16 iLoop = 0;
	kal_uint32 BackupSecondImei;

	//add by MT71518
	kal_uint16 iModemNums = 0;
	kal_uint16 MDindex = 0;
	META_RESULT MR = META_SUCCESS;
	//MODEM_QUERY_INFO_REQ infoReq;
	//MODEM_QUERY_INFO_CNF infoCnf;
	int Meta_Result = 0;
	extern int ret_statue;

	kal_uint8 strBarcode_W [ BARCODE_MAX_LENGTH];
	int dataLength = 0;
	int i = 0;
	char calFlag[2] = {0};
    char ftFlag;
	

	sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
    strcat ( strLog, "\n>>Step: Enter func_barcode_meta_hdlr_smart_phone_modem();\n");
	strcat ( strLog,  "        Write BarCode to smartphone modem nvram\n");
	UpdateLog ( strLog, 100 );

    g_Meta6516Modem.eRunStatus =  OK_STATUS;
	if ( OK_STATUS == g_Meta6516Modem.eRunStatus ) 
	{	   
	    if(targetStype == SP_DUALMODEM)
	   	{
	   	    iModemNums = 2;
	   	}
        else if(targetStype == Tablet_WIFI_ONLY)
        {
        	iModemNums = 0;
        }
        else
        {
        	iModemNums = 1;
        }						

				
        if(iModemNums == 1 || iModemNums == 2)
        {
		        sprintf ( strLog, "\n>>Step: Star write barcode to  Modem nvram ...\n");
	            UpdateLog ( strLog, 80 );
			    for(MDindex = 0; MDindex< iModemNums; MDindex++)
			    {	
			        #if 1
				    if(targetStype == SP_DUALMODEM)
				    {
				       sprintf ( strLog, ">>Star Switch to Modem Meta...\n");
			           UpdateLog ( strLog, 100 );
		               Meta_Result = META_SwitchCurrentModem_r(g_Meta.iMeta_handle, 5000, MDindex);				 
			           if (Meta_Result != 0 )
			           {
					       sprintf ( strLog, ">>Step: Switch to modem%d meta fail, result is:\n %s.\n", MDindex+1, ResultToString(Meta_Result));
					       UpdateLog ( strLog, 100 );
				 
					       UpdateIndicator ( KAL_FALSE );
					       return KAL_TRUE;
			           }
				       sprintf ( strLog, "	OK: Switch to modem%d meta success.\n", MDindex+1);
				       UpdateLog ( strLog,  100);

					   if(MDindex == 1)
	                   {
	                       if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [2] ) 
	                       {
	                           sprintf ( strLog, ">>Step: Start to load Modem2 database...\n");
			                   UpdateLog ( strLog, 0);
		                       if ( Nvram2DatabaseInit () )
		                       {
			                       sprintf ( strLog, ">>Step: Reselect Modem2 database and start to initiaize.\n");
			                       UpdateLog ( strLog, 0);
								   Modem2_Database_Select_Click_Shell();
			                       return Nvram2DatabaseInit();
		                        }			
	                        }
	                   }
				   }
                   #endif

				    memset(strBarcode_R, 0 , sizeof(strBarcode_R));
			        g_Meta6516Modem.eMeta_Result = METAAPP_readBarcodefromNVRAM( g_Meta.iMeta_handle, 5000, strBarcode_R );
			        if ( g_Meta6516Modem.eMeta_Result == METAAPP_SUCCESS )
   			        {
				          sprintf ( strLog, "   OK: Read Barcode successfully.\n"  );
					      UpdateLog ( strLog, 70 );	

						  dataLength = strlen(BarCode);
	                      ConstructBarcode(strBarcode_W, strBarcode_R, BarCode, dataLength);
			        }
					else
					{
					      sprintf ( strLog, "   ERROR: Read Barcode error.\n"  );
					      UpdateLog ( strLog, 70 );
						  
					      UpdateIndicator ( KAL_FALSE );
					      return KAL_TRUE;
					}
					
                    /*
					memset(strBarcode_W, 0x20, 64);
			            dataLength = strlen(BarCode);
			            strncpy(strBarcode_W, BarCode, dataLength);
			            strBarcode_W[60] = calFlag[0];
			            strBarcode_W[61] = calFlag[1];
			            strBarcode_W[62] = ftFlag;
					*/
			        g_Meta6516Modem.eMeta_Result = METAAPP_writeBarcodetoNVRAM( g_Meta.iMeta_handle, strBarcode_W, 5000 );
			        if ( g_Meta6516Modem.eMeta_Result ==  METAAPP_SUCCESS )
			        {
					    sprintf ( strLog, "   OK: Write Barcode successfully.\n"  );
					    UpdateLog ( strLog, 70 );	
			        }
				    else
				    {
				      	sprintf ( strLog, "   Error: Write Barcode fail. Meta Result = %d\n", g_Meta6516Modem.eMeta_Result );
					    UpdateLog ( strLog, 100 );
						 
					    UpdateIndicator ( KAL_FALSE );
					    Exit_MetaModemMode ();			
				        return KAL_TRUE;
					}
					        
			        memset(strBarcode_R, 0 , sizeof(strBarcode_R));
			        g_Meta6516Modem.eMeta_Result = METAAPP_readBarcodefromNVRAM( g_Meta.iMeta_handle, 5000, strBarcode_R );
			        if ( g_Meta6516Modem.eMeta_Result == METAAPP_SUCCESS )
   			        {
				          sprintf ( strLog, "   OK: Read Barcode successfully.\n"  );
					      UpdateLog ( strLog, 70 );						         
			        }
					else
					{
					      sprintf ( strLog, "   ERROR: Read Barcode error.\n"  );
					      UpdateLog ( strLog, 70 );
						  
					      UpdateIndicator ( KAL_FALSE );
					      return KAL_TRUE;
					}
 
			        if ( strncmp ( strBarcode_R, strBarcode_W, dataLength))
				    {
				         sprintf ( strLog, "   Error: Check Barcode fail. Rd_Barcode = \"%s\".\n.", strBarcode_R );
				         UpdateLog ( strLog, 100 );
				
				         UpdateIndicator ( KAL_FALSE );
					     return KAL_TRUE;
				    }
				    sprintf ( strLog, "  \n OK: Check Barcode. Rd_Barcode = \"%s\".\n.", BarCode);
				    UpdateLog ( strLog, 70 );

					if(GetIsDataCall())//?????????????????????????????????????????????
      	            {
	                     if(GetIsDataprefer())
	                     {
	                        SetDataCall=0x00;
                            sprintf ( strLog, ">> Set DATA_prefer\n");
	                        UpdateLog ( strLog, 10 );
                            if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			                {
				                sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	  	            UpdateLog ( strLog, 80 );
				                UpdateIndicator ( KAL_TRUE );
								return KAL_FALSE;
				            } 
				            else 
				            {
				                sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				                UpdateLog ( strLog, 80 );
				                UpdateIndicator ( KAL_FALSE );
								return KAL_TRUE;
				            }   
	                     }
		                 else
		      	         {
                             SetDataCall=0x01;
      	                     sprintf ( strLog, ">> Set CALL_prefer\n");
	                         UpdateLog ( strLog, 10 );
                             if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			                 {
				                 sprintf ( strLog, "    OK: Set CALL_prefer ok\n");
	        	  	             UpdateLog ( strLog, 80 );
				                 UpdateIndicator ( KAL_TRUE );
								 return KAL_FALSE;
				             } 
				             else 
				             {
				                 sprintf ( strLog,  "   Error ,fail to Set  CALL_prefer\n" );
				                 UpdateLog ( strLog, 80 );
				                 UpdateIndicator ( KAL_FALSE );
								 return KAL_TRUE;
				             } 				
		      	         }		
      	           }

                   #if 0
				   if(iModemNums == 2 && MDindex == 0)
				   {
				       sprintf ( strLog, ">>Star Switch to Modem Meta...\n");
			           UpdateLog ( strLog, 100 );
		               Meta_Result = META_SwitchCurrentModem_r(g_Meta.iMeta_handle, 5000, MDindex+1);				 
			           if (Meta_Result != 0 )
			           {
					       sprintf ( strLog, ">>Step: Switch to modem%d meta fail, result is:\n %s.\n", MDindex+2, ResultToString(Meta_Result));
					       UpdateLog ( strLog, 100 );
				 
					       UpdateIndicator ( KAL_FALSE );
					       return KAL_TRUE;
			           }
				       sprintf ( strLog, "	OK: Switch to modem%d meta success.\n", MDindex+2);
				       UpdateLog ( strLog,  100);

					   if(GetTargetType() == SP_DUALMODEM)
	                   {
	                       if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [2] ) 
	                       {
	                           sprintf ( strLog, ">>Step: Start to load Modem2 database...\n");
			                   UpdateLog ( strLog, 0);
		                       if ( Nvram2DatabaseInit () )
		                       {
			                       sprintf ( strLog, ">>Step: Reselect Modem2 database and start to initiaize.\n");
			                       UpdateLog ( strLog, 0);
								   Modem2_Database_Select_Click_Shell();
			                       return Nvram2DatabaseInit();
		                        }			
	                        }
	                   }
				  }
				  #endif
			 }
        } 
	    else if(0 == iModemNums)
	    {
			sprintf ( strLog, ">>Current Smart Phone have any modems.\n");
	        UpdateLog ( strLog, 100 );
		    return KAL_FALSE;
		}
    }

	return KAL_FALSE;
}

void func_barcode_at_hdlr_feature_phone ()
{

	kal_uint8 strTip [256];
	kal_uint8 strBarcode_w [ BARCODE_MAX_LENGTH + 1 ];
	kal_uint8 strBarcode_r [ BARCODE_MAX_LENGTH + 1 ];
	S_AT_REQUEST tRequest;
	S_AT_RESULT tResult ;
	kal_bool rt;
	kal_uint16 iLoop = 0;
	kal_uint32 length;
	kal_uint32 isUsbAt=0;
	kal_uint32 isusbfirst=0;
	EBOOT_RESULT xboot_result;

	kal_bool XBOOT_RESULT;
	int bootstop=0;
	
	sprintf ( strLog, ">> Step: Enter func_barcode_at_hdlr_feature_phone();\n");
	strcat ( strLog,  "               Write Barcode to feature modem nvram\n");
	UpdateLog ( strLog, 0 );
	if(!GetIs6276M())
	{
	     if( IsUSBCOMPort() )	
	     {
               isUsbAt=1;
	        isusbfirst=1;
		sprintf ( strLog, ">> Enum_for usb at cmd\n");
		UpdateLog ( strLog, 10 );
		     rt=Prepare_For_USB_AT_CMD();
			 if(rt==KAL_FALSE)
			 	return;
	g_SN.tCommPort.eComPort=com_port_temp;
	}	
		
	rt = COMContextInit ( GetCOMPort(), GetBaudRate() );
	
	g_MetaModem.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{     
	           if(isUsbAt==1&&isusbfirst!=1)
              {
                 sprintf ( strLog, ">> Prepare_for usb at cmd\n");
		    UpdateLog ( strLog, 10 );
		     rt==Prepare_For_USB_AT_CMD();
			/*
                      if(rt==KAL_FALSE)
                      	{
                             sprintf ( strLog,  "import 2!\n");	
                              UpdateLog ( strLog, 10 );
                      	}
					  
			 
			 if(rt==KAL_FALSE)
			 	return;
                     */



                   if(CANCEL_STATUS == g_MetaModem.eRunStatus)
			return;
			
			 
                    g_SN.tCommPort.eComPort=com_port_temp;
					
		     rt = COMContextInit ( GetCOMPort(), GetBaudRate() );

		}
              else
              {
              isusbfirst=0;
              }
		sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );	
	
		sprintf ( strLog, ">> Step: Start to scan S/N code...\n" );
		UpdateLog ( strLog, 10 );

		sprintf ( strTip, "Please scan Barcode, then PowerOn phone...");
		g_MetaModem.eRunStatus = InputBoxPopup ("Barcode (<64 Bytes)", strTip, (kal_int8*) strBarcode_w, BARCODE_MAX_LENGTH );

		sprintf ( strLog, "     OK: Barcode = \"%s\".\n", strBarcode_w );
		UpdateLog ( strLog, 20 );
		
		ResetIndicator ();
		
		if ( iLoop++ == 50)
		{
			ClearLog ();
			iLoop = 0;
		}
		
		if ( OK_STATUS == g_MetaModem.eRunStatus ) 
		{
		
			sprintf ( strLog,  ">> Step: Waiting for %d s Power On Delay...\n",  GetPowerOnDelayTime() );
			UpdateLog ( strLog, 250 );
			
			Delay ( GetPowerOnDelayTime() );
		    
			sprintf ( strLog,  ">> Step: Start to disable sleep mode.\n" );
			UpdateLog ( strLog, 30 );
			
			if ( !AT_Preset ( GetCOMPort(), GetPowerOnDelayTime()) )
			{
				sprintf ( strLog,  "     Error: Disable sleep mode fail. \n " );
				UpdateLog ( strLog, 70 );
				 if(isUsbAt==1)
	                          CloseCom (GetCOMPort());
				continue;
			}

			sprintf ( strLog,  "     OK: Disable sleep mode successfully. \n" );
			UpdateLog ( strLog, 40 );

			sprintf ( strLog,  ">> Step: Start to write S/N code...\n" );
			UpdateLog ( strLog, 50 );
			
			if ( !WriteBarcodeATMode ( GetCOMPort(), strBarcode_w ) )
			{
				sprintf ( strLog,  "    Error: Write S/N fail. \n" );
				UpdateLog ( strLog, 70 );
				 if(isUsbAt==1)
	                       CloseCom (GetCOMPort());
				continue;
			}
			
			sprintf ( strLog,  "     OK: Write S/N code successfully. \n");
			strcat ( strLog,  ">> Step: Start to check S/N code.\n" );
			UpdateLog ( strLog, 60 );

			if ( !ReadBarcodeATMode ( GetCOMPort(), strBarcode_r, &length) )
			{
				sprintf ( strLog,  ">> Error: Read S/N fail. \n" );
				UpdateLog ( strLog, 70 );
				if(isUsbAt==1)
	                       CloseCom (GetCOMPort());
				continue;
			}
			
			sprintf ( strLog,  "     OK:Read S/N code successfully.\n");
			UpdateLog ( strLog, 70 );
			
			if ( strcmp ( strBarcode_r, strBarcode_r )){

				sprintf ( strLog, "    Error: Check Barcode failed. Rd_Barcode = \"%s\".\n", strBarcode_r );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );

				MessagePopup ("Barcode Error", " Read/Write check Barcode error");
				
			}
			else
			{
				sprintf ( strLog, "    OK: Check Barcode. Rd_Barcode = \"%s\".\n", strBarcode_r );
				UpdateLog ( strLog, 70 );
				UpdateIndicator ( KAL_TRUE );
			}
    
                      	if(GetIsDataCall())
				{   
				    if(GetIsDataprefer())
				    	{
						   if ( WriteDataCallATMode ( GetCOMPort(), 0))
					           {
							sprintf ( strLog, "    OK: Set Data prefer OK...\n" );
			        	  		UpdateLog ( strLog, 80 );
						    } 
						   else 
						    {
							sprintf ( strLog,  "    Error: Set Data prefer Error!\n" );
							UpdateLog ( strLog, 80 );
							UpdateIndicator ( KAL_FALSE );
							CloseCom (GetCOMPort());
							continue;
						     }
				    	}
				    	else
				    	{
		                               if ( WriteDataCallATMode ( GetCOMPort(), 1) )
					           {
							sprintf ( strLog, "    OK: Set  Call prefer OK...\n");
			        	  		UpdateLog ( strLog, 80 );
						    } 
						   else 
						    {
							sprintf ( strLog,  "    Error: Set Call prefer Error!\n" );
							UpdateLog ( strLog, 80 );
							UpdateIndicator ( KAL_FALSE );
							 CloseCom (GetCOMPort());
							continue;
						     }
						
				    	}
				}
			

		} 
		else
		{
			sprintf ( strLog, ">>Step: Cancel scan Barcode DiagBox.\n");
			UpdateLog ( strLog, 100 );
			 if(isUsbAt==1)
	                CloseCom (GetCOMPort());
			
			break;
		}

		sprintf ( strLog, ">>Step: AT Disconnect with target.\n");
		UpdateLog ( strLog, 100 );

		//Add by mtk71262
           if( g_SN.isEntrySDS)
			{
				if ( !SDSATMode( GetCOMPort()) )
			{
				sprintf ( strLog,  "    Error: AT triger SDS fail. \n" );
				UpdateLog ( strLog, 70 );
				 if(isUsbAt==1)
	                       CloseCom (GetCOMPort());
				continue;
			}
			else
			{
			sprintf ( strLog,  "     OK: AT triger SDS successfully. \n");
			UpdateLog ( strLog, 70 );
			}
			}	
		  if(isUsbAt==1)
	         CloseCom (GetCOMPort());	

	}//while ()
        if(isUsbAt==0)
	rt = COMContextDeInit ( GetCOMPort(), GetBaudRate() );
    }
   else
   {    

	g_MetaModem.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{    


	            sprintf ( strLog, ">> Prepare_for usb at cmd\n");
		    UpdateLog ( strLog, 10 );
                    rt=EnumDynamicUSBComPort_rr(30000,&com_port_temp,&bootstop);
                    Sleep(200);
		 
			   if(rt==META_FAILED)
			       {
			        sprintf ( strLog,  ">> get enum com port fail \n");	
                            UpdateLog ( strLog, 10 );
			        
			 	return;
			      }
			     sprintf ( strLog,  ">> find com port  is %d \n",  com_port_temp);	
                          UpdateLog ( strLog, 10 );

			      if(CANCEL_STATUS == g_MetaModem.eRunStatus)
			       return;
			 
                           g_SN.tCommPort.eComPort=com_port_temp;
			      Sleep(2000);	
                    
                          Xboot_DebugOn ();
                          xboot_result  = XBOOT_COMPORT_Init_r (&hCOM1, GetCOMPort(), GetBaudRate());
			     if(xboot_result!=EBOOT_SUCCESS)
			     	{
			     	     sprintf ( strLog,  ">>Init COMPORT fail\n");	
                                 UpdateLog ( strLog, 10 );
			     	      break;
			     	}
	
		sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );	
	
		sprintf ( strLog, ">> Step: Start to scan S/N code...\n" );
		UpdateLog ( strLog, 10 );

		sprintf ( strTip, "Please scan Barcode, then PowerOn phone...");
		g_MetaModem.eRunStatus = InputBoxPopup ("Barcode (<64 Bytes)", strTip, (kal_int8*) strBarcode_w, BARCODE_MAX_LENGTH );

		sprintf ( strLog, "     OK: Barcode = \"%s\".\n", strBarcode_w );
		UpdateLog ( strLog, 20 );
		
		ResetIndicator ();
		
		if ( iLoop++ == 50)
		{
			ClearLog ();
			iLoop = 0;
		}
		
		if ( OK_STATUS == g_MetaModem.eRunStatus ) 
		{
		     
			sprintf ( strLog,  ">> Step: Waiting for %d s Power On Delay...\n",  GetPowerOnDelayTime() );
			UpdateLog ( strLog, 250 );
			
			Delay ( GetPowerOnDelayTime() );
		     
			sprintf ( strLog,  ">> Step: Start to disable sleep mode.\n" );
			UpdateLog ( strLog, 30 );
			
			if ( !AT_Preset_r( GetCOMPort(), GetPowerOnDelayTime()) )
			{
				sprintf ( strLog,  "     Error: Disable sleep mode fail. \n " );
				UpdateLog ( strLog, 70 );
				  if(isUsbAt==1)
	                     XBOOT_COMPORT_Close_r (hCOM1); 
				continue;
			}

			sprintf ( strLog,  "     OK: Disable sleep mode successfully. \n" );
			UpdateLog ( strLog, 40 );

			sprintf ( strLog,  ">> Step: Start to write S/N code...\n" );
			UpdateLog ( strLog, 50 );
			
			if ( !WriteBarcodeATMode_r ( GetCOMPort(), strBarcode_w ) )
			{
				sprintf ( strLog,  "    Error: Write S/N fail. \n" );
				UpdateLog ( strLog, 70 );
				  if(isUsbAt==1)
	                       XBOOT_COMPORT_Close_r (hCOM1); 
				continue;
			}
			else
			{
			sprintf ( strLog,  "     OK: Write S/N code successfully. \n");
			UpdateLog ( strLog, 60 );
			}
	
			/*
			sprintf ( strLog,  "     OK: Write S/N code successfully. \n");
			strcat ( strLog,  ">> Step: Start to check S/N code.\n" );
			UpdateLog ( strLog, 60 );
                    
			if ( !ReadBarcodeATMode ( GetCOMPort(), strBarcode_r, &length) )
			{
				sprintf ( strLog,  ">> Error: Read S/N fail. \n" );
				UpdateLog ( strLog, 70 );
				  if(isUsbAt==1)
	                       CloseCom (GetCOMPort());
				continue;
			}
			
			sprintf ( strLog,  "     OK:Read S/N code successfully.\n");
			UpdateLog ( strLog, 70 );
			
			if ( strcmp ( strBarcode_r, strBarcode_r )){

				sprintf ( strLog, "    Error: Check Barcode failed. Rd_Barcode = \"%s\".\n", strBarcode_r );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );

				MessagePopup ("Barcode Error", " Read/Write check Barcode error");
				
			}
			else
			{
				sprintf ( strLog, "    OK: Check Barcode. Rd_Barcode = \"%s\".\n", strBarcode_r );
				UpdateLog ( strLog, 70 );
				UpdateIndicator ( KAL_TRUE );
			}
			*/



		
		} 
		else
		{
			sprintf ( strLog, ">>Step: Cancel scan Barcode DiagBox.\n");
			UpdateLog ( strLog, 100 );
		       XBOOT_COMPORT_Close_r (hCOM1); 
			
			break;
		}

		sprintf ( strLog, ">>Step: AT Disconnect with this target.\n");
		UpdateLog ( strLog, 100 );
      
	         XBOOT_COMPORT_Close_r (hCOM1); 	
		      

	}//while ()


       // rt = COMContextDeInit ( GetCOMPort(), GetBaudRate() );
   
   }
}


int func_barcode_meta_hdlr_feature_phone (){

	kal_uint8 strTip [256];
	kal_uint8 strBarcode_W [ BARCODE_MAX_LENGTH + 1 ];
	extern kal_char BarCode[64];

	kal_uint8 strBarcode_R [ BARCODE_MAX_LENGTH];
	kal_uint16 iLoop = 0;
	unsigned int status;
	extern int ret_statue ;
	int ret = 0;
	int dataLength = 0;
	int i = 0;
	char calFlag[2] = {0};
    char ftFlag;
	
	sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
    strcat ( strLog, ">>Step: Enter func_barcode_meta_hdlr_feature_phone();\n");
    strcat ( strLog,	"		 Copy BarCode to feature phone nvram\n");
    UpdateLog ( strLog, 0 );

     
			sprintf ( strLog,  ">>Step: Start to write barcode:\"%s\".\n", BarCode);
			UpdateLog ( strLog, 50 );

			g_MetaModem.eMetaApp_Result = METAAPP_readBarcodefromNVRAM( g_Meta.iMeta_handle, 5000, strBarcode_R );
			switch ( g_MetaModem.eMetaApp_Result )
   			{
				case METAAPP_SUCCESS:	
					/*
					calFlag[0] = strBarcode_R[60];
					calFlag[1] = strBarcode_R[61];
					ftFlag = strBarcode_R[62];
					*/
					dataLength = strlen(BarCode);
	                ConstructBarcode(strBarcode_W, strBarcode_R, BarCode, dataLength);
					break;
			 
				default:
					UpdateIndicator ( KAL_FALSE );
					MessagePopup ("Barcode Error", " Read Barcode error");
				//	continue;	
				break;
			}

            /*
			memset(strBarcode_W, 0x20, 64);
			dataLength = strlen(BarCode);
			strncpy(strBarcode_W, BarCode, dataLength);
			strBarcode_W[60] = calFlag[0];
			strBarcode_W[61] = calFlag[1];
			strBarcode_W[62] = ftFlag;
			*/
			
			g_MetaModem.eMetaApp_Result = METAAPP_writeBarcodetoNVRAM( g_Meta.iMeta_handle, strBarcode_W, 5000 );
			switch ( g_MetaModem.eMetaApp_Result )
   			{
				case METAAPP_SUCCESS:
					sprintf ( strLog, "   OK: Write Barcode successfully.\n"  );
					UpdateLog ( strLog, 70 );	
					break;
			 
				default:
					sprintf ( strLog, "   Error: Write Barcode fail.\n Meta Result = %d\n", g_MetaModem.eMetaApp_Result );
					UpdateLog ( strLog, 100 );
					UpdateIndicator ( KAL_FALSE );	
					MessagePopup ("Barcode Error", " Write Barcode error");
				//	continue;	
				break;
			}

			memset(strBarcode_R, 0 , 64);
			g_MetaModem.eMetaApp_Result = METAAPP_readBarcodefromNVRAM( g_Meta.iMeta_handle, 5000, strBarcode_R );
			switch ( g_MetaModem.eMetaApp_Result )
   			{
				case METAAPP_SUCCESS:
					break;
			 
				default:
					UpdateIndicator ( KAL_FALSE );
					MessagePopup ("Barcode Error", " Read Barcode error");
				//	continue;	
				break;
			}
			

			
			if ( strncmp ( strBarcode_R, strBarcode_W , dataLength)){

				sprintf ( strLog, "   Error: Check Barcode failed.\n Rd_Barcode = \"%s\".\n.", strBarcode_R );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );

				MessagePopup ("Barcode Error", " Read/Write check Barcode error");
                ret = 1;
				goto err;
			}
			else
			{
				sprintf ( strLog, "   OK: Check Barcode.\n Rd_Barcode = \"%s\".\n.", BarCode );
				UpdateLog ( strLog, 70 );
				//UpdateIndicator ( KAL_TRUE );
			}


                    if(GetIsDataCall())
	           {        
	              if(GetIsDataprefer())
	              {
	                    SetDataCall=0x00;
                           sprintf ( strLog, ">> Set DATA_prefer\n");
	                    UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 //UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				 ret = 2;
				goto err;
				 }  
	              }
			else
			{
                           SetDataCall=0x01;
      	                    sprintf ( strLog, ">> Set  CALL_prefer\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set  CALL_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				// UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to set  CALL_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				 ret = 3;
				goto err;
				 } 

					 
			
			}
	     	    }	
	     
	         if(GetIsAMR())
	         {        
	                if(GetIsSetAMR())
	                {
	                   SetAMR=0x1f;
      	                   sprintf ( strLog, ">> SetAMR_FR/AMR_HR\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteAMR_Start(SetAMR) )
			      {
				sprintf ( strLog, "    OK: SetAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 //UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to SetAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				 ret = 4;
				goto err;
				  }  
	                }
			  else
			  {
			       SetAMR=0x07;
				sprintf ( strLog, ">> ClearAMR_FR/AMR_HR\n");
                            UpdateLog ( strLog, 10 );
                            if ( !REQ_WriteAMR_Start(SetAMR) )
			       {
				 sprintf ( strLog, "    OK: ClearAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				//UpdateIndicator ( KAL_TRUE );
				 } 
				else 
				{
				sprintf ( strLog,  "   Error ,fail to ClearAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_FALSE );
				ret = 5;
				goto err;
				 }			
			  }
	     
	         }
err:
	return ret;
}
	
int  func_imei_meta_hdlr_smart_phone_modem (E_TARGET_TYPE targetStype)//by mtk71596
{

	IMEISV_struct_T tIMEIScanBack,tImei_Svn_Pad;
	kal_int8 strSvn[4];
	kal_uint8 iIMEICheckSum;
	kal_uint32 BackupSecondIMEI;
	kal_uint8 strTip [256];
	kal_uint16 p_spare, iLoop = 0;

    kal_uint16 iModems = 0;
	kal_uint16 uiImeis = 0;
	kal_uint16 MDindex = 0;
	kal_uint16 IMEIindex = 0;
	int Meta_Result = 0;
	extern kal_char imei[4][16];
	MODEM_QUERY_INFO_REQ infoReq;
	MODEM_QUERY_INFO_CNF infoCnf;
	extern int ret_statue;
	int ret = 0;

    //---------------------------changed by mtk71596---------------------------------
	sprintf ( strLog, "\n>>---------------------------------------------------<<\n" );
    strcat ( strLog, ">>Step: Enter func_imei_meta_hdlr_smart_phone_modem();\n");
	strcat ( strLog,  "        Write IMEI to smartphone modem nvram\n");
	UpdateLog ( strLog, 100 );
    uiImeis = g_SN.tIMEI.eImeiNum;

	for(IMEIindex = 0; IMEIindex < uiImeis; IMEIindex++)
	{
		strcpy(tImei_Svn_Pad.imei, imei[IMEIindex]);	

		#if 1
        if(SP_DUALMODEM == targetStype)//only dual modem need to switch modem
		{
			sprintf ( strLog, "\n>>Star Switch to Modem Meta...\n");
			UpdateLog ( strLog, 100 );

			MDindex = IMEIindex;
		    Meta_Result = META_SwitchCurrentModem_r(g_Meta.iMeta_handle, 5000, MDindex);				 
			if (Meta_Result != 0 )
			{
			     sprintf ( strLog, ">>Step:  Switch to modem%d meta fail, result is:\n %s.\n", MDindex+1, ResultToString(Meta_Result));
    		     UpdateLog ( strLog, 100 );
				 
				 UpdateIndicator ( KAL_FALSE );
	             return KAL_TRUE;
			}
			sprintf ( strLog, "	OK: Switch to modem%d meta success.\n", MDindex+1);
			UpdateLog ( strLog,  100);

			if(IMEIindex == 1)
			{
			    if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [2] ) 
	            {
	                sprintf ( strLog, ">>Step: Start to load Modem2 database...\n");
			        UpdateLog ( strLog, 0);
		            if ( Nvram2DatabaseInit () )
		            {
			            sprintf ( strLog, ">>Step: Reselect Modem2 database and start to initiaize.\n");
			            UpdateLog ( strLog, 0);
			            Modem2_Database_Select_Click_Shell();
			            return Nvram2DatabaseInit();
		            }			
	            }	 
		    }
		}
		
		#endif
			
		if ( !GetIsSVNPAD_Enable ())
		{	
			sprintf ( strLog, ">>Step: To get SVN and PAD from phone.\n" );
			UpdateLog ( strLog, 40 );
					
			if ( METAAPP_readIMEIfromNVRAM_Ex3 ( g_Meta.iMeta_handle, 5000, IMEIindex + 1, &tIMEIScanBack))
			{
				sprintf ( strLog, "   Error: METAAPP_readIMEIfromNVRAM_Ex3 fail.\n" );
				UpdateLog ( strLog, 100 );
					   
				UpdateIndicator ( KAL_FALSE );
				return KAL_TRUE;
			}
								
			tImei_Svn_Pad.pad = tIMEIScanBack.pad ;
			tImei_Svn_Pad.svn = tIMEIScanBack.svn ;
		}
		else 
		{
			tImei_Svn_Pad.pad = GetSVNPAD().pad;
			tImei_Svn_Pad.svn = GetSVNPAD().svn;
		}				
		Fmt ( strSvn, "%s<%x", tImei_Svn_Pad.svn ); 
		
		if ( tImei_Svn_Pad.svn < 10)
		{  
		    strSvn[1] = strSvn[0]; 
			strSvn[0] = '0';
			strSvn[2] = '\0';
		}
		swap_c ( &strSvn[0], &strSvn[1]);
		sprintf ( strLog, "   OK: SVN=0x%s and PAD=0x%x \n", strSvn, tImei_Svn_Pad.pad );
		UpdateLog ( strLog, 50 );	

		if ( GetIsAutoCheckSum () )
		{
			sprintf ( strLog, "   Enable AutoCheckSum: The IMEI[%d] = \"%s\" \nhad been auto calculated checksum .\n", IMEIindex,tImei_Svn_Pad.imei );
			UpdateLog ( strLog, 100 );
					 
			METAAPP_Calcualte_IMEI_Spare ( g_Meta.iMeta_handle, tImei_Svn_Pad.imei, &p_spare);
			tImei_Svn_Pad.imei [14] = p_spare + '0';
					
			sprintf(strLog, "And the checksum result is IMEI[%d] = \"%s\ ", IMEIindex, tImei_Svn_Pad.imei);
			UpdateLog ( strLog, 100 );
		}
				
		sprintf ( strLog,  "\n>>Step: Start to write. CheckSum=%d, IMEILock=%d.\n", GetIsImeiCheckSum (), GetIsImeiLock());
		UpdateLog ( strLog, 60 );	

		//Add mtk71518, 2013-07-08, fix bug write multiple imei lock issue
		if(uiImeis > 1)//write multiple imeis
		{
			if(IMEIindex < (uiImeis - 1))
			{
				g_Meta6516Modem.eMeta_Result  = METAAPP_writeIMEItoNVRAM_Ex3( g_Meta.iMeta_handle, 5000, GetIsImeiCheckSum (), KAL_FALSE, IMEIindex+1, &tImei_Svn_Pad);
			} 
			else
			{
				g_Meta6516Modem.eMeta_Result  = METAAPP_writeIMEItoNVRAM_Ex3( g_Meta.iMeta_handle, 5000, GetIsImeiCheckSum (), GetIsImeiLock(), IMEIindex+1, &tImei_Svn_Pad);
			}
		}
		else //Only write one imei
		{
			g_Meta6516Modem.eMeta_Result  = METAAPP_writeIMEItoNVRAM_Ex3( g_Meta.iMeta_handle, 5000, GetIsImeiCheckSum (), GetIsImeiLock(), IMEIindex+1, &tImei_Svn_Pad);
		}

		if ( g_Meta6516Modem.eMeta_Result == METAAPP_SUCCESS)
    	{
			sprintf ( strLog, "   OK: Write IMEI successfully.\n"  );
			UpdateLog ( strLog, 65 );	
		}
		else if(g_Meta6516Modem.eMeta_Result == METAAPP_NVRAM_COMPOSE_IMEI_FAIL)
		{
			sprintf ( strLog, "   Error: IMEI Check Sum error!\n"  );
			UpdateLog ( strLog, 90 );	
			UpdateIndicator ( KAL_FALSE );
		 	return KAL_TRUE;
		}
		else
		{				
			sprintf ( strLog, "   Error: Write IMEI fail. Meta Result = %d\n", g_Meta6516Modem.eMeta_Result );
			UpdateLog ( strLog, 100 );	
			UpdateIndicator ( KAL_FALSE );
			return KAL_TRUE;
		}

		if ( METAAPP_readIMEIfromNVRAM_Ex3 ( g_Meta.iMeta_handle, 5000, IMEIindex + 1, &tIMEIScanBack))
		{

			sprintf ( strLog, "   Error: METAAPP_readIMEIfromNVRAM_Ex3 fail.\n" );
			UpdateLog ( strLog, 100 );
			UpdateIndicator ( KAL_FALSE );
			return KAL_TRUE;
				
		}

	    if ( memcmp ( tIMEIScanBack.imei, tImei_Svn_Pad.imei, IMEI_MAX_LENGTH ) )
		{
			sprintf ( strLog, "   Error: Check IMEI fail.  imei = \"%s\".\n", tIMEIScanBack.imei );
			UpdateLog ( strLog, 100 );
			UpdateIndicator ( KAL_FALSE );
			return KAL_TRUE;
		}
		else
		{
			sprintf ( strLog, "   OK: Check IMEI. Rd_imei = \"%s\".\n", tIMEIScanBack.imei );
			UpdateLog ( strLog, 70 );				
		}

		#if 0
		if(SP_DUALMODEM == targetStype && IMEIindex == 0)//only dual modem need to switch modem and load modem2 database
		{
			sprintf ( strLog, "\n>>Star Switch to Modem Meta...\n");
			UpdateLog ( strLog, 100 );

			MDindex = IMEIindex;
		    Meta_Result = META_SwitchCurrentModem_r(g_Meta.iMeta_handle, 5000, MDindex+1);				 
			if (Meta_Result != 0 )
			{
			     sprintf ( strLog, ">>Step:  Switch to modem%d meta fail, result is:\n %s.\n", MDindex+2, ResultToString(Meta_Result));
    		     UpdateLog ( strLog, 100 );
				 
				 UpdateIndicator ( KAL_FALSE );
	             return KAL_TRUE;
			}
			sprintf ( strLog, "	OK: Switch to modem%d meta success.\n", MDindex+2);
			UpdateLog ( strLog,  100);
	        
	        if ( KAL_FALSE == g_Meta.bIsDatabaseInitialized [2] ) 
	        {
	            sprintf ( strLog, ">>Step: Start to load Modem2 database...\n");
			    UpdateLog ( strLog, 0);
		        if ( Nvram2DatabaseInit () )
		        {
			         sprintf ( strLog, ">>Step: Reselect Modem2 database and start to initiaize.\n");
			         UpdateLog ( strLog, 0);
			         Modem2_Database_Select_Click_Shell();
			         return Nvram2DatabaseInit();
		        }			
	        }	      
		}
		#endif
	}

	if(GetIsDataCall())
	{
		if(GetIsDataprefer())
		{
			SetDataCall=0x00;
			sprintf ( strLog, ">> Set DATA_prefer\n");
			UpdateLog ( strLog, 10 );
			if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			{
			     sprintf ( strLog, "	 OK: Set DATA_prefer ok\n");
				 UpdateLog ( strLog, 80 );
			     UpdateIndicator ( KAL_TRUE );
				 return KAL_FALSE;
			} 
			else 
			{
			     sprintf ( strLog,  "	 Error ,fail to Set DATA_prefer\n" );
			     UpdateLog ( strLog, 80 );
			     UpdateIndicator ( KAL_FALSE );
			     return KAL_TRUE;
			}   
		}
		else
		{
			SetDataCall=0x01;
			sprintf ( strLog, ">> Set CALL_prefer\n");
			UpdateLog ( strLog, 10 );
			if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			{
			    sprintf ( strLog, "	 OK: Set CALL_prefer ok\n");
			    UpdateLog ( strLog, 80 );
			    UpdateIndicator ( KAL_TRUE );
				return KAL_FALSE;
			} 
			else 
			{
			    sprintf ( strLog,  "	 Error ,fail to Set  CALL_prefer\n" );
			    UpdateLog ( strLog, 80 );
			    UpdateIndicator ( KAL_FALSE );
				return KAL_TRUE;
			} 			
		}			
	}

	return KAL_FALSE;
}



META_RESULT REQ_WriteAMR_Start (kal_uint8 mode)
{   
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID;
     kal_int32 i,num; 
	 
    //port_setting_struct_1 tport;
     port_setting_struct  tport;
    pLID = "NVRAM_EF_MSCAP_LID"; 
    
    g_MetaModem.eMeta_Result = META_NVRAM_GetRecNum(pLID,&num);
    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
    }
   for(i=0;i<num;i++)	
   {
   g_MetaModem.eMeta_Result = META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );	  
    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
    }

	if ( NULL != g_MetaModem.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaModem.tNVRAM_ReadCnf.buf );	
	}

	g_MetaModem.tNVRAM_ReadReq.LID = pLID;
        g_MetaModem.tNVRAM_ReadReq.RID = m_usRID+i;
       g_MetaModem.tNVRAM_ReadCnf.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

	g_MetaModem.eMeta_Result =  REQ_ReadFromNVRAM ();

	
	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }


   g_MetaModem.eMeta_Result = META_NVRAM_SetRecFieldValue(pLID,"speech_version",g_MetaModem.tNVRAM_ReadCnf.buf,m_iBTBufSize,&mode,1);
   	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }
   
    //g_MetaModem.tNVRAM_ReadCnf.buf[0]=mode;

	  
         //g_MetaModem.eMeta_Result = META_NVRAM_Decompose_PortSetting ( &tport, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
      	
  	//if ( g_MetaModem.eMeta_Result != META_SUCCESS )
      //{
        //TODO: LOG
       
      //  return g_MetaModem.eMeta_Result;
      //}
	  
      // memcpy(&tport,g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);//有问题
	//memcpy ( &tport.usb_cdrom_config, &mode, 1 ); 
	
	if (NULL != g_MetaModem.tNVRAM_WriteReq.buf)
	{
		free (g_MetaModem.tNVRAM_WriteReq.buf);	
	}
	g_MetaModem.tNVRAM_WriteReq.LID = pLID;
       g_MetaModem.tNVRAM_WriteReq.RID = m_usRID+i;
       g_MetaModem.tNVRAM_WriteReq.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_WriteReq.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );
		memcpy( g_MetaModem.tNVRAM_WriteReq.buf, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	
	//memcpy(g_MetaModem.tNVRAM_WriteReq.buf,g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	g_MetaModem.eMeta_Result = REQ_WriteNVRAM ();
    
	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
    
    	return g_MetaModem.eMeta_Result;
    }
	}
	
    return META_SUCCESS;
	
}


META_RESULT REQ_WriteDataprefer_Callprefer_Start (kal_uint8 mode)
{   
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID;
     kal_int32 i,num; 
	 
    //port_setting_struct_1 tport;
     port_setting_struct  tport;
    pLID = "NVRAM_EF_RAC_PREFERENCE_LID"; 
    
    g_MetaModem.eMeta_Result = META_NVRAM_GetRecNum(pLID,&num);
    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
    }
   for(i=0;i<num;i++)	
   {
   g_MetaModem.eMeta_Result = META_NVRAM_GetRecLen ( pLID, &m_iBTBufSize );	  
    if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
        //TODO: LOG
       
        return g_MetaModem.eMeta_Result;
    }

	if ( NULL != g_MetaModem.tNVRAM_ReadCnf.buf )
	{
		free ( g_MetaModem.tNVRAM_ReadCnf.buf );	
	}

	g_MetaModem.tNVRAM_ReadReq.LID = pLID;
        g_MetaModem.tNVRAM_ReadReq.RID = m_usRID+i;
       g_MetaModem.tNVRAM_ReadCnf.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));

	g_MetaModem.eMeta_Result =  REQ_ReadFromNVRAM ();

	
	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }
    if(mode==0x00)
    g_MetaModem.tNVRAM_ReadCnf.buf[6]&=0xF0;
    else
    g_MetaModem.tNVRAM_ReadCnf.buf[6]|=0x05;

   //g_MetaModem.eMeta_Result = META_NVRAM_SetRecFieldValue(pLID,"preference",g_MetaModem.tNVRAM_ReadCnf.buf,m_iBTBufSize,&mode,1);
   	if ( g_MetaModem.eMeta_Result!=META_SUCCESS )
    {
    	return g_MetaModem.eMeta_Result;
    }
   
    //g_MetaModem.tNVRAM_ReadCnf.buf[0]=mode;

	  
         //g_MetaModem.eMeta_Result = META_NVRAM_Decompose_PortSetting ( &tport, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
      	
  	//if ( g_MetaModem.eMeta_Result != META_SUCCESS )
      //{
        //TODO: LOG
       
      //  return g_MetaModem.eMeta_Result;
      //}
	  
      // memcpy(&tport,g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);//有问题
	//memcpy ( &tport.usb_cdrom_config, &mode, 1 ); 
	
	if (NULL != g_MetaModem.tNVRAM_WriteReq.buf)
	{
		free (g_MetaModem.tNVRAM_WriteReq.buf);	
	}
	g_MetaModem.tNVRAM_WriteReq.LID = pLID;
       g_MetaModem.tNVRAM_WriteReq.RID = m_usRID+i;
       g_MetaModem.tNVRAM_WriteReq.len = m_iBTBufSize;
       g_MetaModem.tNVRAM_WriteReq.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );
		memcpy( g_MetaModem.tNVRAM_WriteReq.buf, g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	
	//memcpy(g_MetaModem.tNVRAM_WriteReq.buf,g_MetaModem.tNVRAM_ReadCnf.buf, m_iBTBufSize);
	g_MetaModem.eMeta_Result = REQ_WriteNVRAM ();
    
	if ( g_MetaModem.eMeta_Result != META_SUCCESS )
    {
    
    	return g_MetaModem.eMeta_Result;
    }
	}
	
    return META_SUCCESS;
	
}





/***********************************************************
void func_combine_meta_feature_phone()
{
         unsigned int status;

    	sprintf ( strLog, ">>---------------------------------------------------------------------------------------<<\n" );
	strcat ( strLog, ">>Step: Enter func_combine_meta_feature_phone();\n");
	strcat ( strLog,  "        Set special nvram lid value\n");
	UpdateLog ( strLog, 0 );
	
	sprintf ( strLog, ">>Step: Start to Init feature phone Database...\n");
	UpdateLog ( strLog, 20 );
	if ( IsNvramDatabaseInit () )
	{
		sprintf ( strLog, "   Error: Init feature phone Database failed.\n");
		UpdateLog ( strLog, 100);
		return;
	}

	sprintf ( strLog, "   OK: Init feature phone Database successfully.\n");
	UpdateLog ( strLog, 100 );

	SetMetaConnectReq ();

       g_MetaModem.eRunStatus = RUN_STATUS;
      while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
     {
		sprintf ( strLog, "\n>>----------------------------------------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );

	
	sprintf ( strLog, ">>Step: Start to Connect with target.\n" );
       UpdateLog ( strLog, 30 );
				
				
	if ( EnterMetaMode () )
	{
	     ExitMetaMode (); 
					
	     sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode and turn to next phone.\n" );
	     UpdateLog ( strLog, 100 );
	     UpdateIndicator ( KAL_FALSE );
	     return; 
	}
	sprintf ( strLog, "   OK: Connect successfully.\n" );
	UpdateLog ( strLog, 40 );


       
	     if(GetIsDataCall())
	     {        
	              if(GetIsDataprefer())
	              {
	                    SetDataCall=0x00;
                           sprintf ( strLog, ">> Set DATA_prefer\n");
	                    UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				//return;
				 }  
	              }
			else
			{
                           SetDataCall=0x01;
      	                    sprintf ( strLog, ">> Set  CALL_prefer\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set  CALL_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to set  CALL_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				//return;
				 } 

					 
			
			}
	     	}	
	     
	      if(GetIsAMR())
	     {        
	                if(GetIsSetAMR())
	                {
	                   SetAMR=0x1f;
      	                   sprintf ( strLog, ">> SetAMR_FR/AMR_HR\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteAMR_Start(SetAMR) )
			      {
				sprintf ( strLog, "    OK: SetAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to SetAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				//return;
				  }  
	                }
			  else
			  {
			       SetAMR=0x07;
				sprintf ( strLog, ">> ClearAMR_FR/AMR_HR\n");
                            UpdateLog ( strLog, 10 );
                            if ( !REQ_WriteAMR_Start(SetAMR) )
			       {
				 sprintf ( strLog, "    OK: ClearAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_TRUE );
				 } 
				else 
				{
				sprintf ( strLog,  "   Error ,fail to ClearAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_FALSE );
				//return;
				 }			
			  }
	     
	     }

		  
	    if(GetIsSDS())
	   {
               sprintf ( strLog, ">> Set the SDS\n");
               UpdateLog ( strLog, 10 );
	        if(META_MISC_EX_BackupCalibrationToStorage_r(g_Meta.iMeta_handle,5000,0,&status))
	        {

			   sprintf ( strLog, "   Error: BackupCalibrationToStorage fail, Exit Meta Mode and turn to next phone.\n" );
	                 UpdateLog ( strLog, 100 );
	                 UpdateIndicator ( KAL_FALSE );
	        }
		 else
		 {
	            sprintf ( strLog, "   OK: BackupCalibrationToStorage OK, Exit Meta Mode and turn to next phone.\n" );
	            UpdateLog ( strLog, 100 );
	            UpdateIndicator ( KAL_TRUE);
		 }
	   }
		
		
      	
	
       sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
       ExitMetaMode ();
	UpdateLog ( strLog, 100 ); 
   }

}





void func_combine_meta_feature_phone()
{


    	sprintf ( strLog, ">>---------------------------------------------------------------------------------------<<\n" );
	strcat ( strLog, ">>Step: Enter func_combine_meta_feature_phone();\n");
	strcat ( strLog,  "        Set special nvram lid value\n");
	UpdateLog ( strLog, 0 );
	
	sprintf ( strLog, ">>Step: Start to Init feature phone Database...\n");
	UpdateLog ( strLog, 20 );
	if ( IsNvramDatabaseInit () )
	{
		sprintf ( strLog, "   Error: Init feature phone Database failed.\n");
		UpdateLog ( strLog, 100);
		return;
	}

	sprintf ( strLog, "   OK: Init feature phone Database successfully.\n");
	UpdateLog ( strLog, 100 );

	SetMetaConnectReq ();

       g_MetaModem.eRunStatus = RUN_STATUS;
      while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
     {
		sprintf ( strLog, "\n>>----------------------------------------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );

	
	sprintf ( strLog, ">>Step: Start to Connect with target.\n" );
       UpdateLog ( strLog, 30 );
				
				
	if ( EnterMetaMode () )
	{
	     ExitMetaMode (); 
					
	     sprintf ( strLog, "   Error: Connect failed, Exit Meta Mode and turn to next phone.\n" );
	     UpdateLog ( strLog, 100 );
	     UpdateIndicator ( KAL_FALSE );
	     return; 
	}
	sprintf ( strLog, "   OK: Connect successfully.\n" );
	UpdateLog ( strLog, 40 );


       
	     if(GetIsDataCall())
	     {        
	              if(GetIsDataprefer())
	              {
	                    SetDataCall=0x00;
                           sprintf ( strLog, ">> Set DATA_prefer\n");
	                    UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				return;
				 }  
	              }
			else
			{
                           SetDataCall=0x01;
      	                    sprintf ( strLog, ">> Set  CALL_prefer\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set  CALL_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to set  CALL_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				return;
				 } 

					 
			
			}
	     	}	
	     
	      if(GetIsAMR())
	     {        
	                if(GetIsSetAMR())
	                {
	                   SetAMR=0x1f;
      	                   sprintf ( strLog, ">> SetAMR_FR/AMR_HR\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteAMR_Start(SetAMR) )
			      {
				sprintf ( strLog, "    OK: SetAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to SetAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				return;
				  }  
	                }
			  else
			  {
			       SetAMR=0x07;
				sprintf ( strLog, ">> ClearAMR_FR/AMR_HR\n");
                            UpdateLog ( strLog, 10 );
                            if ( !REQ_WriteAMR_Start(SetAMR) )
			       {
				 sprintf ( strLog, "    OK: ClearAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_TRUE );
				 } 
				else 
				{
				sprintf ( strLog,  "   Error ,fail to ClearAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_FALSE );
				return;
				 }			
			  }
	     
	     }
		
      	
	
       sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
       ExitMetaMode ();
	UpdateLog ( strLog, 100 ); 
   }

}





************************************************************/




int func_imei_meta_hdlr_feature_phone ()
{

	extern IMEISV_struct_T tImei_Svn_Pad;
	int imeiNums = 0;
	int imeiIndex = 0;
	IMEISV_struct_T tIMEIScanBack;
	kal_uint8 strPad [4], strSvn [4];
	kal_uint8 iIMEICheckSum;
	kal_uint8 strTip [256];
	kal_uint16 p_spare;
	kal_uint8 strBarcode_R [ BARCODE_MAX_LENGTH + 1 ];
	unsigned int status;
	extern kal_char imei[4][16];
	extern int ret_statue ;
    int ret = 0;
   sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
   strcat ( strLog, ">>Step: Enter func_imei_meta_hdlr_feature_phone();\n");
   UpdateLog ( strLog, 10 );
	
   imeiNums = g_SN.tIMEI.eImeiNum;
   
           for(imeiIndex = 0;imeiIndex < imeiNums;imeiIndex++)
			{
			  strcpy(tImei_Svn_Pad.imei, imei[imeiIndex]); 
			  if ( OK_STATUS == g_MetaModem.eRunStatus ) 
			   {
			       sprintf ( strLog, "\n Begin write IMEI[%d] = \"%s\".\n", imeiIndex, tImei_Svn_Pad.imei );
	        	       UpdateLog ( strLog, 20 );
					   
				if( 15 != strlen (tImei_Svn_Pad.imei) )
				{
					if(strlen (tImei_Svn_Pad.imei) == 14 && GetIsAutoCheckSum())
					{
						strcat(tImei_Svn_Pad.imei,"0");
						sprintf ( strLog, "Original IMEI 14 bit isn't correct\n Auto set to IMEI = \"%s\".\n", tImei_Svn_Pad.imei );
	        	       	UpdateLog ( strLog, 25 );
					}
					else
					{
						sprintf ( strLog,  "    Error: IMEI code < 15 bytes!\n");
						UpdateLog ( strLog, 70 );
						UpdateIndicator ( KAL_FALSE );
 					    ret = 1;
						goto err;
					}
				}
				
				if ( GetIsCheckFTStatus () )
				{
					g_MetaModem.eMetaApp_Result = METAAPP_readBarcodefromNVRAM( g_Meta.iMeta_handle, 5000, strBarcode_R );
					switch ( g_Meta6516Modem.eMeta_Result )
   					{
						case METAAPP_SUCCESS:
					
							break;
			 
						default:
							UpdateIndicator ( KAL_FALSE );
							MessagePopup ("Barcode Error", " Read Barcode error");
							break;	
					}

					if ( '1' == strBarcode_R [60] &&  '0' == strBarcode_R [61] )
					{
						sprintf ( strLog, "   OK: Calibration Flag check pass\n" );
						UpdateLog ( strLog, 30 );
					}
					else if ( '0' == strBarcode_R [60] &&  '1' == strBarcode_R [61] )
					{
						sprintf ( strLog, "   Error: Calibration Flag fail.\n" );
						UpdateLog ( strLog, 30 );
						UpdateIndicator ( KAL_FALSE );
					    ret = 2;
						goto err;

					} else 
					{
						sprintf ( strLog, "   Error: Target hasn't been Calibrated .\n" );
						UpdateLog ( strLog, 30 );
						UpdateIndicator ( KAL_FALSE );
					    ret = 3;
						goto err;
					}
				}
				
				if ( !GetIsSVNPAD_Enable ())
				{
					sprintf ( strLog, ">>Step: To get SVN and PAD from phone.\n" );
					UpdateLog ( strLog, 40 );
					
					if ( METAAPP_readIMEIfromNVRAM_Ex3 ( g_Meta.iMeta_handle, 5000, imeiIndex+1, &tIMEIScanBack))
					{
		           			sprintf ( strLog, "   Error: METAAPP_readIMEIfromNVRAM_Ex3 fail.\n" );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						
               					MessagePopup ("Meta Error", "Meta IMEI read fail!"); 
					    ret = 4;
						goto err;
				
					}
					tImei_Svn_Pad.pad = tIMEIScanBack.pad ;
					tImei_Svn_Pad.svn = tIMEIScanBack.svn ;
				} else {

					tImei_Svn_Pad.pad = GetSVNPAD().pad;
					tImei_Svn_Pad.svn = GetSVNPAD().svn;
				}

				if ( GetIsAutoCheckSum () )
				{
				     sprintf ( strLog, "   Enable AutoCheckSum: The IMEI[%d] = \"%s\" \nhad been auto calculated checksum .\n", imeiIndex,tImei_Svn_Pad.imei );
					 UpdateLog ( strLog, 100 );
					 
					 METAAPP_Calcualte_IMEI_Spare ( g_Meta.iMeta_handle, tImei_Svn_Pad.imei, &p_spare);
					tImei_Svn_Pad.imei [14] = p_spare + '0';
					
					sprintf(strLog, "And the auto checksum result is IMEI[%d] = \"%s\ ", imeiIndex, tImei_Svn_Pad.imei);
				    UpdateLog ( strLog, 100 );
				    
				}
				
				Fmt ( strSvn, "%s<%x", tImei_Svn_Pad.svn ); 
				
				if (tImei_Svn_Pad.svn < 10)
				{  
				   strSvn[1] = strSvn[0]; 
				   strSvn[0] = '0';
				   strSvn[2] = '\0';
				}
				swap_c ( &strSvn[0], &strSvn[1]);
				
				sprintf ( strLog, "   OK: SVN=0x%s and PAD=0x%x \n", strSvn, tImei_Svn_Pad.pad );
				UpdateLog ( strLog, 50 );	
				
				sprintf ( strLog,  ">>Step: Start to write. CheckSum=%d, IMEILock=%d.\n", GetIsImeiCheckSum (), GetIsImeiLock());
				UpdateLog ( strLog, 70 );	

				//Add mtk71518, 2013-07-08, fix bug write multiple imei lock issue
				if(imeiNums > 1)//write multiple imeis
				{
				    if(imeiIndex < (imeiNums - 1))
				    {
				        g_MetaModem.eMetaApp_Result = METAAPP_writeIMEItoNVRAM_Ex3( g_Meta.iMeta_handle, 5000, GetIsImeiCheckSum (), KAL_FALSE, imeiIndex+1, &tImei_Svn_Pad);
				    } 
					else
					{
					    g_MetaModem.eMetaApp_Result = METAAPP_writeIMEItoNVRAM_Ex3( g_Meta.iMeta_handle, 5000, GetIsImeiCheckSum (), GetIsImeiLock(), imeiIndex+1, &tImei_Svn_Pad);
					}
				}
				else //Only write one imei
				{
				    g_MetaModem.eMetaApp_Result = METAAPP_writeIMEItoNVRAM_Ex3( g_Meta.iMeta_handle, 5000, GetIsImeiCheckSum (), GetIsImeiLock(), imeiIndex+1, &tImei_Svn_Pad);
				}
				
				switch ( g_MetaModem.eMetaApp_Result )
    			       {
					case METAAPP_SUCCESS:
						sprintf ( strLog, "    OK: Write IMEI = \"%s\".\n", tImei_Svn_Pad.imei );
	        	      			UpdateLog ( strLog, 80 );
						//UpdateIndicator ( KAL_TRUE );
						break;
			 
					case METAAPP_NVRAM_COMPOSE_IMEI_FAIL:
						
						METAAPP_Calcualte_IMEI_Spare ( g_Meta.iMeta_handle, tImei_Svn_Pad.imei, &p_spare);
						tImei_Svn_Pad.imei [14] = p_spare + '0';
						sprintf ( strLog,  "   Error:IMEI CheckSum error!\n. Correct IMEI = \"%s\".\n", tImei_Svn_Pad.imei  );
						UpdateLog ( strLog, 80 );	
						
		 				MessagePopup ("IMEI CheckSum error", " The CheckSum of IMEI error!");
						UpdateIndicator ( KAL_FALSE );
						break;
						
					default: 
						sprintf ( strLog,  "   Error: METAAPP_writeIMEItoNVRAM_Ex3()!\n" );
						UpdateLog ( strLog, 80 );
						UpdateIndicator ( KAL_FALSE );
						break;	
				}

                            if(MT6276M== g_MetaModem.tMETA_Connect_Report.boot_result.m_bbchip_type||g_MetaModem.usb_report.boot_result.m_bbchip_type==MT6276M)
	                  {

                             if(!GetIsCDrom())
      	                     {      port=0x00;
      	                              sprintf ( strLog, ">> CDrom\n");
	                              UpdateLog ( strLog, 10 );
                                     if ( !REQ_WriteCDrom_Start(port) )
			               {
					  sprintf ( strLog, "    OK: enableCDrom ok\n");
	        	  		  UpdateLog ( strLog, 80 );
					   //UpdateIndicator ( KAL_TRUE );
				         } 
				         else 
				        {
					  sprintf ( strLog,  "   Error ,fail to enable CDrom\n" );
					  UpdateLog ( strLog, 80 );
					  UpdateIndicator ( KAL_FALSE );
					  ret = 5;
					  goto err;
				         }
							  
					
	                     }
	                    else
	                    	{
	                    	        port=0x01;
				         sprintf ( strLog, ">> COMport\n");
                                     UpdateLog ( strLog, 10 );
                                      if ( !REQ_WriteCDrom_Start(port) )
			               {
					  sprintf ( strLog, "    OK: enableCOMport ok\n");
	        	  		  UpdateLog ( strLog, 80 );
					  //UpdateIndicator ( KAL_TRUE );
				         } 
				         else 
				        {
					  sprintf ( strLog,  "   Error ,fail to enable COMport\n" );
					  UpdateLog ( strLog, 80 );
					  UpdateIndicator ( KAL_FALSE );
					  ret = 6;
					  goto err;
				         }								 
                            }		

	                 }	
 
                   if(GetIsDataCall())
	             {        
	              if(GetIsDataprefer())
	              {
	                    SetDataCall=0x00;
                           sprintf ( strLog, ">> Set DATA_prefer\n");
	                    UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set DATA_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 //UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to Set DATA_prefer\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				 ret = 7;
				goto err;
				 }  
	              }
			else
			{
                           SetDataCall=0x01;
      	                    sprintf ( strLog, ">> Set  CALL_prefer\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteDataprefer_Callprefer_Start(SetDataCall) )
			      {
				sprintf ( strLog, "    OK: Set  CALL_prefer ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 //UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to set  CALL_prefer\n" );
				UpdateLog ( strLog, 80 );
				 //UpdateIndicator ( KAL_FALSE );
				 ret = 8;
				goto err;
				 } 

					 
			
			}
	     	}	
	     
	      if(GetIsAMR())
	     {        
	                if(GetIsSetAMR())
	                {
	                   SetAMR=0x1f;
      	                   sprintf ( strLog, ">> SetAMR_FR/AMR_HR\n");
	                   UpdateLog ( strLog, 10 );
                           if ( !REQ_WriteAMR_Start(SetAMR) )
			      {
				sprintf ( strLog, "    OK: SetAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				 //UpdateIndicator ( KAL_TRUE );
				} 
				  else 
				{
				sprintf ( strLog,  "   Error ,fail to SetAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				 UpdateIndicator ( KAL_FALSE );
				ret = 9;
				goto err;
				  }  
	                }
			  else
			  {
			       SetAMR=0x07;
				sprintf ( strLog, ">> ClearAMR_FR/AMR_HR\n");
                            UpdateLog ( strLog, 10 );
                            if ( !REQ_WriteAMR_Start(SetAMR) )
			       {
				 sprintf ( strLog, "    OK: ClearAMR_FR/AMR_HR ok\n");
	        	  	UpdateLog ( strLog, 80 );
				//UpdateIndicator ( KAL_TRUE );
				 } 
				else 
				{
				sprintf ( strLog,  "   Error ,fail to ClearAMR_FR/AMR_HR\n" );
				UpdateLog ( strLog, 80 );
				UpdateIndicator ( KAL_FALSE );
				ret = 10;
				goto err;
				 }			
			  }
	     
	     }
		
	}
  }
err:
	return ret;
}
/*	
	void func_combine_at_feature_phone ()
{

	IMEISV_struct_T tIMEIScanBack,tImei_Svn_Pad;
	kal_uint8 strPad [4], strSvn [4];
	kal_uint8 iIMEICheckSum, i, iTimer;
	kal_uint8 strTip [256];
	kal_uint16 p_spare, iLoop = 0;
	kal_uint8 strBarcode_r [ BARCODE_MAX_LENGTH + 1 ];
	kal_uint32 length;
	kal_bool rt;
	kal_uint32 isUsbAt=0;
	kal_uint32 isusbfirst=0;
	int ii=0;
	
	sprintf ( strLog, ">> Step: Enter func_combine_at_feature_phone();\n");
	strcat ( strLog,  "               USE AT cmd for Switch  DATA prefer/CALL prefer\n");
	UpdateLog ( strLog, 0 );
	
	if( IsUSBCOMPort() )	
	{
               isUsbAt=1;
	        isusbfirst=1;
		sprintf ( strLog, ">> Enum_for usb at cmd\n");
		UpdateLog ( strLog, 10 );
		     rt=Prepare_For_USB_AT_CMD();
			 if(rt==KAL_FALSE)
			 	return;
			 g_SN.tCommPort.eComPort=com_port_temp;
	}
		
	rt = COMContextInit ( GetCOMPort(), GetBaudRate() );
	
	g_MetaModem.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{    
	       if(isUsbAt==1&&isusbfirst!=1)
              {
                 sprintf ( strLog, ">> Prepare_for usb at cmd\n");
		    UpdateLog ( strLog, 10 );
		     rt=Prepare_For_USB_AT_CMD();
			/* 
                      if(rt==KAL_FALSE)
                      	{
                             sprintf ( strLog,  "import 2!\n");	
                              UpdateLog ( strLog, 10 );
                      	}
					  
			 
			 if(rt==KAL_FALSE)
			 	return;

			 //*

/******************************************************************************

			 if(CANCEL_STATUS == g_MetaModem.eRunStatus)
			return;
			 
                    g_SN.tCommPort.eComPort=com_port_temp;
					
		     rt = COMContextInit ( GetCOMPort(), GetBaudRate() );

		}
              else
              {
              isusbfirst=0;
              }
		sprintf ( strLog, "\n>>----------------------------------------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );
			
		 sprintf ( strLog,  ">> USE AT cmd for Switch  DATA prefer/CALL prefer \n");
		UpdateLog ( strLog, 20 );	
		 sprintf ( strLog,  ">>please power on your DUT \n");
		UpdateLog ( strLog, 20 );	
		
			ResetIndicator ();
			if ( iLoop++ == 50)
			{
				ClearLog ();
				iLoop = 0;
			}
	  
				
					sprintf ( strLog,  ">> Step: Waiting for %d s Power On Delay...\n",  GetPowerOnDelayTime() );
					UpdateLog ( strLog, 20 );

					SetStartButton_Disable ( KAL_TRUE );
					for( iTimer = 0; iTimer < GetPowerOnDelayTime(); iTimer++)
					{
						sprintf ( strLog,  "   %d",  iTimer+1 );
						UpdateLog ( strLog, (20 + iTimer)%100 );
						Delay ( 1.0 );
					}
				     
					SetStartButton_Disable ( KAL_FALSE );
					
					sprintf ( strLog,  "\n>> Step: Start to disable sleep mode.\n" );
					UpdateLog ( strLog, 25 );

                                 

					

					if ( !AT_Preset ( GetCOMPort(), GetPowerOnDelayTime()) )
					{
						sprintf ( strLog,  "     Error: Disable sleep mode fail. \n " );
						UpdateLog ( strLog, 70 );
						UpdateIndicator ( KAL_FALSE );
						CloseCom (GetCOMPort());
					         continue;
					}	
					
					sprintf ( strLog,  "     OK: Disable sleep mode successfully. \n" );
					UpdateLog ( strLog, 40 );
					
					if ( GetIsCheckFTStatus () )
					{
						sprintf ( strLog,  ">> Step: Start to check calibration status.\n"  );
						UpdateLog ( strLog, 40 );
						
						if ( !ReadBarcodeATMode ( GetCOMPort(), strBarcode_r, &length) )
						{
							sprintf ( strLog,  ">> Error: Read barcode fail. \n" );
							UpdateLog ( strLog, 70 );
							break;
						}

						if ( '1' == strBarcode_r [60] &&  '0' == strBarcode_r [61] )
						{
							sprintf ( strLog, "   OK: Calibration Flag check pass\n" );
							UpdateLog ( strLog, 30 );
						}
						else if ( '0' == strBarcode_r [60] &&  '1' == strBarcode_r [61] )
						{
							sprintf ( strLog, "   Error: Calibration Flag fail.\n" );
							UpdateLog ( strLog, 30 );
							UpdateIndicator ( KAL_FALSE );
							break;	

						} else 
						{
							sprintf ( strLog, "   Error: Target hasn't been Calibrated .\n" );
							UpdateLog ( strLog, 30 );
							UpdateIndicator ( KAL_FALSE );
							break;	

						}
					}
				
				Delay ( 1.0 );
				
				sprintf ( strLog,  ">> Step: Start to write switch  data call code...\n" );
				UpdateLog ( strLog, 50 );
				
				if(GetIsDataCall())
				{   
				    if(GetIsDataprefer())
				    	{
						   if ( WriteDataCallATMode ( GetCOMPort(), 0))
					           {
							sprintf ( strLog, "    OK: Set Data prefer OK...\n" );
			        	  		UpdateLog ( strLog, 80 );
						    } 
						   else 
						    {
							sprintf ( strLog,  "    Error: Set Data prefer Error!\n" );
							UpdateLog ( strLog, 80 );
							UpdateIndicator ( KAL_FALSE );
							CloseCom (GetCOMPort());
							continue;
						     }
				    	}
				    	else
				    	{
		                               if ( WriteDataCallATMode ( GetCOMPort(), 1) )
					           {
							sprintf ( strLog, "    OK: Set  Call prefer OK...\n");
			        	  		UpdateLog ( strLog, 80 );
						    } 
						   else 
						    {
							sprintf ( strLog,  "    Error: Set Call prefer Error!\n" );
							UpdateLog ( strLog, 80 );
							UpdateIndicator ( KAL_FALSE );
							 CloseCom (GetCOMPort());
							continue;
						     }
						
				    	}
				}
				
					
			

		 // for (;;)
                   if(isUsbAt==1)
	         CloseCom (GetCOMPort());
		
	}//while ()
             if(isUsbAt==1)     
	rt = COMContextDeInit ( GetCOMPort(), GetBaudRate() );
}

*******************************************************************/			 







void func_Imei_at_hdlr_feature_phone (IMEISV_struct_T *tImei_Svn_Pad,kal_uint8 *i,kal_uint32 *isUsbAt)
{

	IMEISV_struct_T tIMEIScanBack;
	kal_uint8 strPad [4],j, strSvn [4];
	kal_uint8 iIMEICheckSum, iTimer;
	kal_uint8 strTip [256];
	kal_uint16 p_spare,iLoop;
	kal_uint8 strBarcode_r [ BARCODE_MAX_LENGTH + 1 ];
	kal_uint32 length;
	kal_bool rt;
	int ii=0;

	EBOOT_RESULT xboot_result;

	kal_bool XBOOT_RESULT;
	char  write_buffer[100],read_buffer[200];

	int bootstop=0;
/*
	sprintf ( strLog, ">> Step: Enter func_Imei_at_hdlr_feature_phone();\n");
	strcat ( strLog,  "               Write IMEI to feature modem nvram\n");
	UpdateLog ( strLog, 0 );
	if(!GetIs6276M())
	{
	     if( IsUSBCOMPort() )	
	      {
               isUsbAt=1;
	        isusbfirst=1;
		sprintf ( strLog, ">> Enum_for usb at cmd\n");
		UpdateLog ( strLog, 10 );
		     rt=Prepare_For_USB_AT_CMD();
			 if(rt==KAL_FALSE)
			 	return;
			 g_SN.tCommPort.eComPort=com_port_temp;
	       }
		
	       rt = COMContextInit ( GetCOMPort(), GetBaudRate() );
	
	
	g_MetaModem.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{    
          
	       if(isUsbAt==1&&isusbfirst!=1)
              {
                 sprintf ( strLog, ">> Prepare_for usb at cmd\n");
		    UpdateLog ( strLog, 10 );
		     rt=Prepare_For_USB_AT_CMD();
			/* 
                      if(rt==KAL_FALSE)
                      	{
                             sprintf ( strLog,  "import 2!\n");	
                              UpdateLog ( strLog, 10 );
                      	}
					  
			 
			 if(rt==KAL_FALSE)
			 	return;

			 */

/*

			 if(CANCEL_STATUS == g_MetaModem.eRunStatus)
			return;
			 
                    g_SN.tCommPort.eComPort=com_port_temp;
					
		     rt = COMContextInit ( GetCOMPort(), GetBaudRate() );

		}
              else
              {
              isusbfirst=0;
              }
         
	    
		sprintf ( strLog, "\n>>----------------------------------------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );

			
		 sprintf ( strLog,  ">> want to write Imei number  is %d \n",  GetIsDualImei()+1);
			
		for ( i = 0; i<= GetIsDualImei(); i++ )
		{
			if ( GetIsDualImei() )
			{
				if(i == 0)
				{
					while(1)
					{
						g_MetaModem.eRunStatus = DisplayDualImeiScanner();

						if(CANCEL_STATUS == g_MetaModem.eRunStatus)
						{
							sprintf ( strLog, "   User cancel IMEI input.\n");
							UpdateLog ( strLog, 10 );
							break;
						}
						else if(strlen(Imei[0]) == 15 && strlen(Imei[1]) == 15)
						{
							if(g_SN.tIMEI.bFourIMEI)
							{
								if(strlen(Imei[2]) == 15 && strlen(Imei[3]) == 15)
									break;
								else
								{
									sprintf ( strLog, "   Warning: at least 1 IMEI is illegal, re-scan IMEI.\n");
									UpdateLog ( strLog, 10 );
								}
							}else if(g_SN.tIMEI.eImeiNum == THREE_IMEI)
							{
								 if(strlen(Imei[2]) == 15)
								 	break;
								 else
								{
									sprintf ( strLog, "   Warning: at least 1 IMEI is illegal, re-scan IMEI.\n");
									UpdateLog ( strLog, 10 );
								}
							}
							else
							{
								break;
							}
						}
						else
						{
							sprintf ( strLog, "   Warning: at least 1 IMEI is illegal, re-scan IMEI.\n");
							UpdateLog ( strLog, 10 );
						}
					}
					strcpy(tImei_Svn_Pad.imei, Imei[0]);
				}
				else
				{
					strcpy(tImei_Svn_Pad.imei, Imei[i]);
				}
			
			} 
			else 
			{
				sprintf ( strLog, ">>Step: Scan feature phone IMEI.\n");
				UpdateLog ( strLog, 10 );
				
				sprintf ( strTip, "Please scan IMEI code, then PowerOn phone...");
				g_MetaModem.eRunStatus = InputBoxPopup ("IMEI (15 Bytes)", strTip, (kal_int8*) &tImei_Svn_Pad.imei, IMEI_MAX_LENGTH);
			}

		
			ResetIndicator ();
			if ( iLoop++ == 50)
			{
				ClearLog ();
				iLoop = 0;
			}
		
			if ( OK_STATUS == g_MetaModem.eRunStatus ) 
			{

				sprintf ( strLog, "    OK: Scan IMEI = \"%s\".\n", tImei_Svn_Pad.imei );
        	       		UpdateLog ( strLog, 15 );

				if(  strlen (tImei_Svn_Pad.imei)<14 )
				{
					sprintf ( strLog,  "    Error: IMEI code < 14 bytes!");
					UpdateLog ( strLog, 70 );
					UpdateIndicator ( KAL_FALSE );
					break;
				}

                             if(strlen (tImei_Svn_Pad.imei) == 14 && GetIsAutoCheckSum())
				{
						//sprintf(tImei_Svn_Pad.imei)
					strcat(tImei_Svn_Pad.imei,"0");
					sprintf ( strLog, "Original IMEI 14 bit isn't correct\n Auto set to IMEI = \"%s\".\n", tImei_Svn_Pad.imei );
	        	       	UpdateLog ( strLog, 25 );
				}


*/

//----------------------------------------------------------------------------------------


				if ( *i == 0 ) 
				{     
				  
					sprintf ( strLog,  ">> Step: Waiting for %d s Power On Delay...\n",  GetPowerOnDelayTime() );
					UpdateLog ( strLog, 20 );

					SetStartButton_Disable ( KAL_TRUE );
					for( iTimer = 0; iTimer < GetPowerOnDelayTime(); iTimer++)
					{
						sprintf ( strLog,  "   %d",  iTimer+1 );
						UpdateLog ( strLog, (20 + iTimer)%100 );
						Delay ( 1.0 );
					}
				     
					SetStartButton_Disable ( KAL_FALSE );
					
					sprintf ( strLog,  "\n>> Step: Start to disable sleep mode.\n" );
					UpdateLog ( strLog, 25 );
					if ( !AT_Preset ( GetCOMPort(), GetPowerOnDelayTime()) )
					{
						sprintf ( strLog,  "     Error: Disable sleep mode fail. \n " );
						UpdateLog ( strLog, 70 );
						UpdateIndicator ( KAL_FALSE );
						//break;
						return;
					}	
					
					sprintf ( strLog,  "     OK: Disable sleep mode successfully. \n" );
					UpdateLog ( strLog, 40 );
					
					if ( GetIsCheckFTStatus () )
					{
						sprintf ( strLog,  ">> Step: Start to check calibration status.\n"  );
						UpdateLog ( strLog, 40 );
						
						if ( !ReadBarcodeATMode ( GetCOMPort(), strBarcode_r, &length) )
						{
							sprintf ( strLog,  ">> Error: Read IMEI fail. \n" );
							UpdateLog ( strLog, 70 );
							//break;
							return;
						}

						if ( '1' == strBarcode_r [60] &&  '0' == strBarcode_r [61] )
						{
							sprintf ( strLog, "   OK: Calibration Flag check pass\n" );
							UpdateLog ( strLog, 30 );
						}
						else if ( '0' == strBarcode_r [60] &&  '1' == strBarcode_r [61] )
						{
							sprintf ( strLog, "   Error: Calibration Flag fail.\n" );
							UpdateLog ( strLog, 30 );
							UpdateIndicator ( KAL_FALSE );
						//	break;	
						return;

						} else 
						{
							sprintf ( strLog, "   Error: Target hasn't been Calibrated .\n" );
							UpdateLog ( strLog, 30 );
							UpdateIndicator ( KAL_FALSE );
							//break;	
							return;

						}
					}
				}
				Delay ( 0.1 );
				sprintf ( strLog,  ">>Step: Start to write. CheckSum=%d, IMEILock=%d.\n", GetIsImeiCheckSum (), GetIsImeiLock());
				UpdateLog ( strLog, 70 );
				
				if ( GetIsSVNPAD_Enable ())
				{
					(*tImei_Svn_Pad).pad = GetSVNPAD().pad;
					(*tImei_Svn_Pad).svn = GetSVNPAD().svn;
			
					Fmt ( strSvn, "%s<%x", (*tImei_Svn_Pad).svn ); 
					if ( (*tImei_Svn_Pad).svn < 10)
					{  strSvn[1] = strSvn[0]; strSvn[0] = '0';strSvn[2] = '\0';}
					
					swap_c ( &strSvn[0], &strSvn[1]);
		
					sprintf ( strLog, "    OK: SVN=0x%s and PAD=0x%x \n", strSvn, (*tImei_Svn_Pad).pad );
					UpdateLog ( strLog, 50 );	
				}
				
				
				METAAPP_Calcualte_IMEI_Spare ( g_Meta.iMeta_handle, (*tImei_Svn_Pad).imei, &p_spare);

				if ( GetIsAutoCheckSum () )
				{
					(*tImei_Svn_Pad).imei [14] = p_spare + '0';
				}
				
				if ( GetIsImeiCheckSum () )
				{
					if ( (*tImei_Svn_Pad).imei [14] != p_spare + '0' )
					{
						(*tImei_Svn_Pad).imei [14] = p_spare + '0';
						sprintf ( strLog, "    Error: Check Sum error.\n   IMEI = \"%s\".\n", (*tImei_Svn_Pad).imei ); 
						UpdateLog ( strLog, 90 );
						UpdateIndicator ( KAL_FALSE );
				//		break;
				return;
					}
				}
				
				sprintf ( strLog,  ">> Step: Start to write IMEI code...\n" );
				UpdateLog ( strLog, 50 );
				
				if ( WriteIMEIATMode ( GetCOMPort(), tImei_Svn_Pad, *i,  GetIsSVNPAD_Enable ()) ) 
			        {
					sprintf ( strLog, "    OK: Write IMEI = \"%s\".\n", (*tImei_Svn_Pad).imei );
	        	  		UpdateLog ( strLog, 80 );
				} else 
				{
					sprintf ( strLog,  "    Error: WriteIMEIATMode()!\n   Please delay more time after Power On!\n" );
					UpdateLog ( strLog, 80 );
					UpdateIndicator ( KAL_FALSE );
				//	break;
				return;
				}
					
				if ( ReadIMEIATMode ( GetCOMPort(), &tIMEIScanBack, *i) )
				{
					sprintf ( strLog,  "    OK:Read IMEI code successfully.\n");
					UpdateLog ( strLog, 70 );
				}
				else
				{
					sprintf ( strLog,  ">> Error: Read IMEI fail. \n" );
					UpdateLog ( strLog, 70 );
					UpdateIndicator ( KAL_FALSE );
				//	break;
				return;
				}
				
				
				
				if ( strcmp ( tIMEIScanBack.imei, (*tImei_Svn_Pad).imei ))
				{

					sprintf ( strLog, "    Error: Check IMEI failed. Read IMEI = \"%s\".\n", tIMEIScanBack.imei );
					UpdateLog ( strLog, 100 );
					UpdateIndicator ( KAL_FALSE );

					MessagePopup ("Barcode Error", " Read/Write check IMEI error");
					
				}
				else
				{
					sprintf ( strLog, "    OK: Check IMEI ok. Read IMEI = \"%s\".\n", tIMEIScanBack.imei );
					UpdateLog ( strLog, 70 );
					UpdateIndicator ( KAL_TRUE );
				}

				
				
				if(GetIsDataCall())
				{   

				   sprintf ( strLog,  ">> Step: Start to write switch  data call code...\n" );
				   UpdateLog ( strLog, 50 );
				    if(GetIsDataprefer())
				    	{
						   if ( WriteDataCallATMode ( GetCOMPort(), 0))
					           {
							sprintf ( strLog, "    OK: Set Data prefer OK...\n" );
			        	  		UpdateLog ( strLog, 80 );
						    } 
						   else 
						    {
							sprintf ( strLog,  "    Error: Set Data prefer Error!\n" );
							UpdateLog ( strLog, 80 );
							UpdateIndicator ( KAL_FALSE );
							CloseCom (GetCOMPort());
	//						continue;
						     }
				    	}
				    	else
				    	{
		                               if ( WriteDataCallATMode ( GetCOMPort(), 1) )
					           {
							sprintf ( strLog, "    OK: Set  Call prefer OK...\n");
			        	  		UpdateLog ( strLog, 80 );
						    } 
						   else 
						    {
							sprintf ( strLog,  "    Error: Set Call prefer Error!\n" );
							UpdateLog ( strLog, 80 );
							UpdateIndicator ( KAL_FALSE );
							 CloseCom (GetCOMPort());
				//			continue;
						     }
						
				    	}
				}
				
			
			
//		} 
			else 
			{
				sprintf ( strLog, ">>Step: Cancel scan IMEI DiagBox.\n");
				UpdateLog ( strLog, 90 );

			//	break;
			return;
			} 
//		} // for (;;)
		//add by mtk71262
		   if( g_SN.isEntrySDS)
			{
				if ( !SDSATMode( GetCOMPort()) )
			{
				sprintf ( strLog,  "    Error: AT triger SDS fail. \n" );
				UpdateLog ( strLog, 70 );
				 if(*isUsbAt==1)
	                       CloseCom (GetCOMPort());
//				continue;
			}
			else
			{
			sprintf ( strLog,  "     OK: AT triger SDS successfully. \n");
			UpdateLog ( strLog, 70 );
			}
			}
		   
              if(*isUsbAt==1)
	         CloseCom (GetCOMPort());
		
//	}//while ()
             if(*isUsbAt==0)     
	rt = COMContextDeInit ( GetCOMPort(), GetBaudRate() );
//	}
	else
	{
        g_MetaModem.eRunStatus = RUN_STATUS;

	while ( CANCEL_STATUS != g_MetaModem.eRunStatus && KAL_TRUE != GetBootStopFlag())
	{      
                
                 sprintf ( strLog, ">> Prepare_for usb at cmd\n");
		    UpdateLog ( strLog, 10 );
                    rt=EnumDynamicUSBComPort_rr(30000,&com_port_temp,&bootstop);
		            Sleep(200);
			   if(rt==META_FAILED)
			       {
			        sprintf ( strLog,  ">> get enum com port fail \n");	
                            UpdateLog ( strLog, 10 );
			        
			 	return;
			      }
			     sprintf ( strLog,  ">> find com port  is %d \n",  com_port_temp);	
                          UpdateLog ( strLog, 10 );

			      if(CANCEL_STATUS == g_MetaModem.eRunStatus)
			       return;
			 
                           g_SN.tCommPort.eComPort=com_port_temp;
			      Sleep(2000);	
                          Xboot_DebugClear();
                          Xboot_DebugOn ();
                          xboot_result  = XBOOT_COMPORT_Init_r (&hCOM1, GetCOMPort(), GetBaudRate());
			     if(xboot_result!=EBOOT_SUCCESS)
			     	{
			     	     sprintf ( strLog,  ">>Init COMPORT fail\n");	
                                 UpdateLog ( strLog, 10 );
				     UpdateIndicator ( KAL_FALSE );
			     	      break;
			     	}
	
		sprintf ( strLog, "\n>>----------------------------------------------------------------------------------<<\n" );
		UpdateLog ( strLog, 0 );
		 sprintf ( strLog,  ">> want to write Imei number  is %d \n",  GetIsDualImei()+1);	
		for ( j = 0; j<= GetIsDualImei(); j++ )
		{
			if ( GetIsDualImei() )
			{
				if ( j ==0 ) 
				{     sprintf ( strLog,  ">> want to write Imei number  is %d \n",  GetIsDualImei()+1);	
                                   UpdateLog ( strLog, 10 );

				
					sprintf ( strLog, ">> Step: Scan Gemini %d st IMEI.\n",j+1);
					UpdateLog ( strLog, 10 );
				
				        sprintf ( strTip, "Please scan Geimin %d st IMEI code, then PowerOn phone...",i+1);
				} 
				else if(j==GetIsDualImei() )
				{ 
				       sprintf ( strLog, ">> Step: Scan Gemini last IMEI.\n");
					UpdateLog ( strLog, 10 );
				
				        sprintf ( strTip, "Please scan Gemini last IMEI,then to nest phone");
				}
				else 
				{
					sprintf ( strLog, ">> Step: Scan Gemini %d nd IMEI.\n",j+1);
					UpdateLog ( strLog, 10 );
				
					sprintf ( strTip, "Please scan Geimin %d nd IMEI code......",j+1);
				}
			}
		    else 
		    {
				sprintf ( strLog, ">>S tep: Scan feature phone IMEI.\n");
				UpdateLog ( strLog, 10 );
			
				sprintf ( strTip, "Please scan IMEI code, then PowerOn phone...");
			}

		
			g_MetaModem.eRunStatus = InputBoxPopup ("IMEI (15 Bytes)", strTip, (kal_int8*)( (*tImei_Svn_Pad).imei), IMEI_MAX_LENGTH);

			ResetIndicator ();
			if ( iLoop++ == 50)
			{
				ClearLog ();
				iLoop = 0;
			}
		
			if ( OK_STATUS == g_MetaModem.eRunStatus ) 
			{

				sprintf ( strLog, "    OK: Scan IMEI = \"%s\".\n", (*tImei_Svn_Pad).imei );
        	       		UpdateLog ( strLog, 15 );

				if(  strlen ((*tImei_Svn_Pad).imei)<14 )
				{
					sprintf ( strLog,  "    Error: IMEI code < 14 bytes!");
					UpdateLog ( strLog, 70 );
					UpdateIndicator ( KAL_FALSE );
					break;
				}

                             if(strlen ((*tImei_Svn_Pad).imei) == 14 && GetIsAutoCheckSum())
				{
						//sprintf(tImei_Svn_Pad.imei)
					strcat((*tImei_Svn_Pad).imei,"0");
					sprintf ( strLog, "Original IMEI 14 bit isn't correct\n Auto set to IMEI = \"%s\".\n", (*tImei_Svn_Pad).imei );
	        	       	UpdateLog ( strLog, 25 );
				}

				
				if ( j == 0 ) 
				{ 
				   
					sprintf ( strLog,  ">> Step: Waiting for %d s Power On Delay...\n",  GetPowerOnDelayTime() );
					UpdateLog ( strLog, 20 );

					SetStartButton_Disable ( KAL_TRUE );
					for( iTimer = 0; iTimer < GetPowerOnDelayTime(); iTimer++)
					{
						sprintf ( strLog,  "   %d",  iTimer+1 );
						UpdateLog ( strLog, (20 + iTimer)%100 );
						Delay ( 1.0 );
					}
				     
					SetStartButton_Disable ( KAL_FALSE );
					
					sprintf ( strLog,  "\n>> Step: Start to disable sleep mode.\n" );
					UpdateLog ( strLog, 25 );

					if (  !AT_Preset_r( GetCOMPort(), GetPowerOnDelayTime()))
					{
						sprintf ( strLog,  "     Error: Disable sleep mode fail. \n " );
						UpdateLog ( strLog, 70 );
						UpdateIndicator ( KAL_FALSE );
					       XBOOT_COMPORT_Close_r (hCOM1);                             //                         COMContextDeInit ( GetCOMPort(), GetBaudRate() );
						break;
					}	
					
					sprintf ( strLog,  "     OK: Disable sleep mode successfully. \n" );
					UpdateLog ( strLog, 40 );
					/*
					if ( GetIsCheckFTStatus () )
					{
						sprintf ( strLog,  ">> Step: Start to check calibration status.\n"  );
						UpdateLog ( strLog, 40 );
						
						if ( !ReadBarcodeATMode ( GetCOMPort(), strBarcode_r, &length) )
						{
							sprintf ( strLog,  ">> Error: Read IMEI fail. \n" );
							UpdateLog ( strLog, 70 );
							COMContextDeInit ( GetCOMPort(), GetBaudRate() );
							break;
						}

						if ( '1' == strBarcode_r [60] &&  '0' == strBarcode_r [61] )
						{
							sprintf ( strLog, "   OK: Calibration Flag check pass\n" );
							UpdateLog ( strLog, 30 );
						}
						else if ( '0' == strBarcode_r [60] &&  '1' == strBarcode_r [61] )
						{
							sprintf ( strLog, "   Error: Calibration Flag fail.\n" );
							UpdateLog ( strLog, 30 );
							UpdateIndicator ( KAL_FALSE );
							break;	

						} else 
						{
							sprintf ( strLog, "   Error: Target hasn't been Calibrated .\n" );
							UpdateLog ( strLog, 30 );
							UpdateIndicator ( KAL_FALSE );
							break;	

						}
					}*/


 }
				Delay ( 1.0 );
				sprintf ( strLog,  ">>Step: Start to write. CheckSum=%d, IMEILock=%d.\n", GetIsImeiCheckSum (), GetIsImeiLock());
				UpdateLog ( strLog, 70 );
				
				if ( GetIsSVNPAD_Enable ())
				{
					(*tImei_Svn_Pad).pad = GetSVNPAD().pad;
					(*tImei_Svn_Pad).svn = GetSVNPAD().svn;
			
					Fmt ( strSvn, "%s<%x", (*tImei_Svn_Pad).svn ); 
					if ( (*tImei_Svn_Pad).svn < 10)
					{  strSvn[1] = strSvn[0]; strSvn[0] = '0';strSvn[2] = '\0';}
					
					swap_c ( &strSvn[0], &strSvn[1]);
		
					sprintf ( strLog, "    OK: SVN=0x%s and PAD=0x%x \n", strSvn, (*tImei_Svn_Pad).pad );
					UpdateLog ( strLog, 50 );	
				}
				
				
				METAAPP_Calcualte_IMEI_Spare ( g_Meta.iMeta_handle, (*tImei_Svn_Pad).imei, &p_spare);

				if ( GetIsAutoCheckSum () )
				{
					(*tImei_Svn_Pad).imei [14] = p_spare + '0';
				}
				
				if ( GetIsImeiCheckSum () )
				{
					if ( (*tImei_Svn_Pad).imei [14] != p_spare + '0' )
					{
						(*tImei_Svn_Pad).imei [14] = p_spare + '0';
						sprintf ( strLog, "    Error: Check Sum error.\n   IMEI = \"%s\".\n", (*tImei_Svn_Pad).imei ); 
						UpdateLog ( strLog, 90 );
						UpdateIndicator ( KAL_FALSE );
						break;
					}
				}
				
				sprintf ( strLog,  ">> Step: Start to write IMEI code...\n" );
				UpdateLog ( strLog, 50 );

				
				if ( WriteIMEIATMode_r ( GetCOMPort(), tImei_Svn_Pad, j,  GetIsSVNPAD_Enable ()) ) 
			        {
					sprintf ( strLog, "    OK: Write IMEI = \"%s\".\n", (*tImei_Svn_Pad).imei );
	        	  		UpdateLog ( strLog, 80 );
				} else 
				{
					sprintf ( strLog,  "    Error: WriteIMEIATMode()!\n   Please delay more time after Power On!\n" );
					UpdateLog ( strLog, 80 );
					UpdateIndicator ( KAL_FALSE );
					break;
				}
				/*	
				if ( ReadIMEIATMode ( GetCOMPort(), &tIMEIScanBack, i) )
				{
					sprintf ( strLog,  "    OK:Read IMEI code successfully.\n");
					UpdateLog ( strLog, 70 );
				}
				else
				{
					sprintf ( strLog,  ">> Error: Read IMEI fail. \n" );
					UpdateLog ( strLog, 70 );
					break;
				}
				
				
				
				if ( strcmp ( tIMEIScanBack.imei, tImei_Svn_Pad.imei ))
				{

					sprintf ( strLog, "    Error: Check IMEI failed. Read IMEI = \"%s\".\n", tIMEIScanBack.imei );
					UpdateLog ( strLog, 100 );
					UpdateIndicator ( KAL_FALSE );

					MessagePopup ("Barcode Error", " Read/Write check IMEI error");
					
				}
				else
				{
					sprintf ( strLog, "    OK: Check IMEI ok. Read IMEI = \"%s\".\n", tIMEIScanBack.imei );
					UpdateLog ( strLog, 70 );
					UpdateIndicator ( KAL_TRUE );
				}
/**/
                           //add for 76M enable CDrom or not

                            if(!GetIsCDrom())
      	                     {
      	                              sprintf ( strLog, ">> CDrom\n");
	                              UpdateLog ( strLog, 10 );
                                     if ( WriteCDROMATMode ( GetCOMPort(),0) )
			               {
					  sprintf ( strLog, "    OK: enableCDrom ok\n");
	        	  		  UpdateLog ( strLog, 80 );
					   UpdateIndicator ( KAL_TRUE );
				         } 
				         else 
				        {
					  sprintf ( strLog,  "   Error ,fail to enable CDrom\n" );
					  UpdateLog ( strLog, 80 );
					  UpdateIndicator ( KAL_FALSE );
					  break;
				         }
							  
					
	                     }
	                    else
	                    	{
	                    	
				         sprintf ( strLog, ">> COMport\n");
                                     UpdateLog ( strLog, 10 );
                                      if ( WriteCDROMATMode ( GetCOMPort(),1) )
			               {
					  sprintf ( strLog, "    OK: enableCOMport ok\n");
	        	  		  UpdateLog ( strLog, 80 );
					  UpdateIndicator ( KAL_TRUE );
				         } 
				         else 
				        {
					  sprintf ( strLog,  "   Error ,fail to enable COMport\n" );
					  UpdateLog ( strLog, 80 );
					  UpdateIndicator ( KAL_FALSE );
					  break;
				         }								 
                            }
		
			} 
			else 
			{
				sprintf ( strLog, ">>Step: Cancel scan IMEI DiagBox.\n");
				UpdateLog ( strLog, 90 );

				break;
			} 

		} // for (;;)
                
	         XBOOT_COMPORT_Close_r (hCOM1);
	}//while ()	
	}
}
//----------------------------------------------------------------------	
int func_bt_address_meta_hdlr_feature_phone ( void )
{
    kal_uint8 strTip [256] , i, iBCD_L, iBCD_H;
	
	BT_ModuleID_S 	BT_ID;

	S_HANDSET_BT_ADRRESS tBtAddress_W, tBtAddress_R;
//	kal_uint8 strBtAddress_W [ BT_ADDRESS_MAX_LENGTH + 1 ];
	extern kal_char BT[13];
	kal_uint8 strBtAddress_R [ BT_ADDRESS_MAX_LENGTH + 1 ];
	kal_uint16 iLoop = 0;
	unsigned int status;
	META_RESULT MR;
	extern int ret_statue;
	int ret = 0;
	sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
   strcat ( strLog, ">>Step: Enter func_bt_meta_hdlr_feature_phone();\n");
   strcat ( strLog,	"		 write BT to feature phone nvram\n");
   UpdateLog ( strLog, 0 );

    
			sprintf ( strLog,  ">>Step: Start to write BT Address:\"%s\"\n",BT );
			UpdateLog ( strLog, 50 );

			if ( !META_QueryIfFunctionSupportedByTarget_r ( g_Meta.iMeta_handle, 5000, "META_BT_QueryModuleID_r" ))
			{
				if ( META_BT_QueryModuleID_r (g_Meta.iMeta_handle, 5000, &BT_ID ))
				{
					MessagePopup ("BT Address Error", " Query BT Module fail!");
					ret = 1;
				    goto err;
				}

			}
			else
			{	
				MessagePopup ("BT Address Error", " Please Make sure the handset have the BT Module First");
				ret = 2;
				goto err;
			}

			if(MT6236 == g_MetaModem.tMETA_Connect_Report.boot_result.m_bbchip_type||g_MetaModem.usb_report.boot_result.m_bbchip_type==MT6236)
			{
				sprintf ( strLog, "Detect bbchip is MT6236.\n" );
				UpdateLog ( strLog, 40 );
				BT_ID.id = BTMODULE_MT6612;
			}

			for ( i = 0; i < BT_ADDRESS_MAX_LENGTH; i += 2 )
			{
				 
				 iBCD_H = Ascii2BCD( BT[i] );
				 iBCD_L = Ascii2BCD(BT[i + 1] );

				if ( BTMODULE_MT6601 == BT_ID.id  || BTMODULE_MT6611 == BT_ID.id ||
					 BTMODULE_MT6612 == BT_ID.id  || BTMODULE_MT6616 == BT_ID.id ||
					 BTMODULE_MT6622 == BT_ID.id  || BTMODULE_MT6250 == BT_ID.id ||
					 BTMODULE_MT6260 == BT_ID.id  || BTMODULE_MT6276 == BT_ID.id)
				{
					tBtAddress_W.bd_addr [BD_ADDR_LEN-1 - i/2] = iBCD_H<<4 | iBCD_L;
				}
				else
				{	
					tBtAddress_W.bd_addr [i/2] = iBCD_H<<4 | iBCD_L;
				}
			}

			if ( 0 )
			{
				if ( META_BT_DisableNvramOnlineUpdate_r ( g_Meta.iMeta_handle, 5000 ))
				{
					MessagePopup ( "Meta  API Error", " META_BT_DisableNvramOnlineUpdate_r error" );
				}
			}

            //sprintf(strLog, "BT_ID.id = %d", BT_ID.id);
			//UpdateLog(strLog, 10);
			
			MR = META_SUCCESS;
			switch ( BT_ID.id )	
			{
			
				case BTMODULE_MT6601:  //6601
					if ( MR |= METAAPP_BT_writeMT6601BTAddrtoNVRAM ( g_Meta.iMeta_handle, 5000, &tBtAddress_W ))
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", MR );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );  
						MessagePopup ("Meta  API Error", "BD Address write fail");  
					    ret = 3;
				        goto err;
					}
					
					if ( MR |= METAAPP_BT_readMT6601BTAddrfromNVRAM ( g_Meta.iMeta_handle, 5000, &tBtAddress_R ))
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", MR );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );  
						MessagePopup ("Meta API Error", "BD Address read fail");  
						ret = 4;
				        goto err;
					}
					
					break;
					
				case BTMODULE_RFMD3500:  //RFMD
					if ( MR |= METAAPP_BT_writeRFMD3500BTAddrtoNVRAM ( g_Meta.iMeta_handle, 5000, &tBtAddress_W ))
					{
						MessagePopup ("Meta  API Error", "BD Address write fail");
					    ret = 7;
				        goto err;
					}

					if ( MR |= METAAPP_BT_readRFMD3500BTAddrfromNVRAM ( g_Meta.iMeta_handle, 5000, &tBtAddress_R ))
					{
						MessagePopup ("Meta  API Error", "BD Address read fail");  
						ret = 8;
				        goto err;
					}					
					break;
										
				case BTMODULE_MT6611:
				case BTMODULE_MT6612:
				case BTMODULE_MT6616:
				case BTMODULE_MT6622:
				case BTMODULE_MT6250:
				case BTMODULE_MT6260:
				case BTMODULE_MT6276:
					if ( MR = REQ_WriteBT6611Addr2NVRAM_Start ( BT_ID.id, tBtAddress_W.bd_addr ))
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", MR );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						ExitMetaMode ();  
						
						MessagePopup ("Meta API Error", "BD Address write fail");  
					 
					    ret = 5;
				        goto err;
					}
					
					if ( MR |= REQ_ReadBT6611AddrFromNVRAM_Start ( BT_ID.id, tBtAddress_R.bd_addr ))
					{
						sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", MR );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						ExitMetaMode ();   
						
						MessagePopup ("Meta  API Error", "BD Address read fail");  
						ret = 6;
				        goto err;
					}
					break;
									
				default:
				if( MR = REQ_WriteBT6611Addr2NVRAM_Start ( BT_ID.id, tBtAddress_W.bd_addr ))

				  {	
				  sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", MR );
				  UpdateLog ( strLog, 100 );
				  UpdateIndicator ( KAL_FALSE );
				  ExitMetaMode ();  
				    MessagePopup ("BT Address Error", "Not support BT Chip.");  
					ret = 9;
				   goto err;
				  }
				if( MR != REQ_ReadBT6611AddrFromNVRAM_Start ( BT_ID.id, tBtAddress_R.bd_addr ))
					{
					sprintf ( strLog, "   Error: Write BT Address  fail. Meta Result = %d\n", MR );
						UpdateLog ( strLog, 100 );
						UpdateIndicator ( KAL_FALSE );
						ExitMetaMode ();   
						MessagePopup ("Meta  API Error", "BD Address read fail"); 
						ret = 10;
				        goto err;
					}
				//return
			}

			if(MR != META_SUCCESS)
			{
				sprintf ( strLog, "   Fail: Write BT Address Fail, result is %d.\n", MR);
				UpdateLog ( strLog, 70 );	
			}else
			{
				sprintf ( strLog, "   OK: Write BT Address successfully.\n"  );
				UpdateLog ( strLog, 70 );
				sprintf ( strLog, "   Step: Start to check BT Address.\n"  );
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
					ret = 11;
				    goto err;
					
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

					sprintf ( strLog, ">>OK: Check BT address Pass.\n");
					UpdateLog ( strLog, 100 );
					
					//UpdateIndicator ( KAL_TRUE );
					
				}
			}
err:
	return ret;
}
	 /*
		else 
		{
			sprintf ( strLog, ">>Step: Cancel scan Address DiagBox.\n");
			UpdateLog ( strLog, 100 );

			//break;
			return;
		} */



//\\              MR = META_QueryIfFunctionSupportedByTarget_r(/*meta_handle*/0, 500, "META_MISC_EX_BackupCalibrationToStorage_r");

/******************************************************************

            	if(METAAPP_SUCCESS == MR)
		{
			   sprintf ( strLog, ">> Set the SDS\n");
	                  UpdateLog ( strLog, 10 );
		        if(META_MISC_EX_BackupCalibrationToStorage_r(g_Meta.iMeta_handle,5000,0,&status))
		        {

				   sprintf ( strLog, "   Error: BackupCalibrationToStorage fail, Exit Meta Mode and turn to next phone.\n" );
		                 UpdateLog ( strLog, 100 );
		                 UpdateIndicator ( KAL_FALSE );
		        }
			 else
			 {
		            sprintf ( strLog, "   OK: BackupCalibrationToStorage OK, Exit Meta Mode and turn to next phone.\n" );
		            UpdateLog ( strLog, 100 );
		            UpdateIndicator ( KAL_TRUE);
		          }
		}
**************************************************************************/

		// dimmed by Guanxian 20100720: why we need switch to SP meta mode under feature phone mode ?
		/*g_Meta6516Modem.eMeta_Result = META_DisconnectInMetaMode_r ( g_Meta.iMeta_handle );
		switch ( g_Meta6516Modem.eMeta_Result )
		{
			case METAAPP_SUCCESS:
				sprintf ( strLog, "   OK: META_DisconnectInMetaMode_r() \n"  );
				UpdateLog ( strLog, 85 );	
				break;
				
			default: 
				sprintf ( strLog, "   Error: META_DisconnectInMetaMode_r(). Meta Result = %d\n", g_Meta6516Modem.eMeta_Result );
				UpdateLog ( strLog, 100 );	
				UpdateIndicator ( KAL_FALSE );
				break;	
		}
		if ( Switch2WM_META_Mode ( g_Meta.iMeta_handle ) )
		{
			sprintf ( strLog, "   Error: Switch2WM_META_Mode()\n" );
			UpdateLog ( strLog, 100 );	
			UpdateIndicator ( KAL_FALSE );
		}
		else
		{
			sprintf ( strLog, "   OK: Switch2WM_META_Mode() \n" );
			UpdateLog ( strLog, 90 );
		}
		sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
		Exit_MetaAPMode ();
		UpdateLog ( strLog, 100 );*/





//\\	ExitMetaMode (); 






		/*g_MetaModem.eMetaApp_Result = META_DisconnectWithTarget_r(g_Meta.iMeta_handle);
		if(METAAPP_SUCCESS == g_MetaModem.eMetaApp_Result)
		{
			sprintf ( strLog, ">>Step: Meta Disconnect with target.\n");
		}
		else
		{
			sprintf(strLog,">>Step: Disconnect with target but failed, result is %d !", g_MetaModem.eMetaApp_Result);
		}
		
		UpdateLog ( strLog, 100 );*/

					
//	\\       }//while ()

//  \\       }


//----------------------------------------------------------------------


int func_wifi_mac_meta_hdlr_feature_phone ( void )
{
	kal_uint8 strTip [256] , i, iBCD_L, iBCD_H, strTemp[20];
	
	WiFi_MacAddress_S tWifiMac_W, tWifiMac_R;
//	kal_uint8 strWifiMac_W [ WIFI_MAC_MAX_LENGTH + 1 ];
    extern kal_char WIFI[13];
	kal_uint8 srtWifiMac_R [ WIFI_MAC_MAX_LENGTH + 1 ];
	kal_uint16 iLoop = 0;
	kal_uint32 iMacHeaderLen = 0;
	unsigned int status;
    int ret = 0;
	META_RESULT MR;

	   sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
	   strcat ( strLog, ">>Step: Enter func_wifi_meta_hdlr_feature_phone();\n");
	   strcat ( strLog, "		 write wifi to feature phone nvram\n");
	   UpdateLog ( strLog, 0 );

   
			sprintf ( strLog,  ">>Step: Start to write Wifi MAC. Wifi Addr = \"%s\"\n", WIFI );
			UpdateLog ( strLog, 50 );

			for ( i = 0; i < WIFI_MAC_MAX_LENGTH; i+=2 )
			{
				 
				 iBCD_H = Ascii2BCD( WIFI[i] );
				 iBCD_L = Ascii2BCD( WIFI[i + 1] );

				 tWifiMac_W.mac_addr [i/2] = iBCD_H<<4 | iBCD_L;
			}

			if ( MR = METAAPP_WiFi_writeWiFiMacAddressToNVRAM ( g_Meta.iMeta_handle, 5000, &tWifiMac_W ))
			{
				sprintf ( strLog, "   Error: Write Wifi MAC  fail. Meta Result = %d\n", MR );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );
				MessagePopup ("Wifi MAC Error", "Wifi MAC write fail");

				ExitMetaMode ();
                ret = 1;
				goto err;
			}   
			
			sprintf ( strLog, "    OK: Write Wifi MACsuccessfully.\n"  );
			UpdateLog ( strLog, 70 );	

			sprintf ( strLog, " >>Step: Start to check Wifi MAC.\n"  );
			UpdateLog ( strLog, 80 );	
			
			if ( MR = METAAPP_WiFi_readWiFiMacAddressFromNVRAM ( g_Meta.iMeta_handle,5000,&tWifiMac_R))
			{
				sprintf ( strLog, "    Error: Read Wifi MAC  fail. Meta Result = %d\n", MR );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );
				ExitMetaMode ();   

				MessagePopup ("Meta  API Error", "BD Address read fail");  
				ret = 2;
				goto err;
			}
			
                        
	         	if ( memcmp  ( tWifiMac_W.mac_addr, tWifiMac_R.mac_addr, MAC_ADDR_LEN))
			{
				sprintf ( strLog, "    Error: Check Wifi MAC fail.Wifi MAC = \"%x %x %x %x %x %x\".\n",  tWifiMac_R.mac_addr[0],
																					  tWifiMac_R.mac_addr[1],
																					  tWifiMac_R.mac_addr[2],
																					  tWifiMac_R.mac_addr[3],
																					  tWifiMac_R.mac_addr[4],
																					  tWifiMac_R.mac_addr[5]);

				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );
				ret = 3;
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
				//UpdateIndicator ( KAL_TRUE );

			}
			
err:
	return ret;

}


int SetThermo_TrimtoNVRAM(int DUT_Handle, char AbsTemp, unsigned char ThermoValue, unsigned char XtalTrim)
{
    META_RESULT MetaResult;
    METAAPP_RESULT MetaAppResult;
    int BufSize = 0;
    char *ReadBuffer;
    FT_NVRAM_READ_REQ Nvram_Read_Req;
    char NVRAM_LID[100];
    FT_NVRAM_WRITE_REQ Nvram_Write_Req;

    strcpy(NVRAM_LID, "NVRAM_EF_WNDRV_EXT_SETTING_TRIMVAL_THERMOVAL_LID");

    MetaResult = META_NVRAM_GetRecLen(NVRAM_LID, (int *) &BufSize);
    if (MetaResult != META_SUCCESS)
    {
        return -1;
    }
    ReadBuffer = calloc (BufSize, sizeof(char));

    Nvram_Read_Req.LID = NVRAM_LID;	// The name of logical data item ID
    Nvram_Read_Req.RID = 1;			// Record ID (the first record is 1)

    MetaAppResult = METAAPP_NVRAM_Read(DUT_Handle, 10000, &Nvram_Read_Req, ReadBuffer, BufSize);
    if (MetaAppResult != METAAPP_SUCCESS)
    {
        return -1;
    }

    ReadBuffer[0] = AbsTemp;
    ReadBuffer[1] = ThermoValue;
    ReadBuffer[2] = XtalTrim;

    Nvram_Write_Req.LID = Nvram_Read_Req.LID;
    Nvram_Write_Req.RID = Nvram_Read_Req.RID;
    Nvram_Write_Req.len = BufSize;
    Nvram_Write_Req.buf = ReadBuffer;
    MetaAppResult = METAAPP_NVRAM_Write(DUT_Handle, 10000, &Nvram_Write_Req);
    if (MetaAppResult != METAAPP_SUCCESS)
    {
        return -1;
    }
    return 0;
}


//**************************************************************
int WiFiTxPcl_move_from_EEPROM_to_NVRAM(int meta_handle,char temp[20000] )
{
    double   virTX = 0;
    double d_max_p = 0;
    double d_min_p = 0;
    double d_CL = 0;
    int tx_power_ch_num = 0;
    int out_of_range_flag = 0; // set initial value
    int i_802_11_idx = 0;
    int ch_idx = 0;
    int iqv_status = 0;
    unsigned int freq_khz = 0;
    int rf_spec_check = 0;
    int array_cnt = 0;
    int rate_idx = 0;				  //foe check
    double display_rate = 0;
    //int as_module;
    char WifiTxBuf[500];
    int wifi_array[14];
    int array_idx = 0;
    int array_start_index = 0;
    int power_idx = 0;
    char wifi_strtemp[20];
    char wifi_first[5],wifi_sec[5];
    int value = 0;
    int support_alc = 0;
    int i = 0;
    
    E_TX_POWER_2400M_MOD mod;
    S_WIFICPT  wifi_cpt;
    WiFi_EEPROM_S wifi_eeprom_rdwrt[18];    //[15]; add aditonal 3 word MAC
    WiFi_TestPktTx_Ex_S pkt_tx_ex;
    WiFi_TxStatus_Ex_S pkt_tx_ex_status[14];

    WiFi_MacAddress_S MAC_Address; //MAC Address
    METAAPP_RESULT meta_app_result;

    //a. read all of the value from EEPROM
    array_cnt=14;
    array_start_index= EEPROM_TEST_ADDR;
    for(array_idx=0; array_idx<array_cnt; array_idx++)
    {
        wifi_eeprom_rdwrt[array_idx].index=array_start_index;
        array_start_index=array_start_index+1;
    }

    //add MAC read from EEPROM
    for(i=0; i<3; i++)
    {
        wifi_eeprom_rdwrt[array_idx].index= 0x10 + i;
        array_idx ++;
    }

    //wifi_eeprom_rdwrt.eeprom_data16=
    //meta_app_result=META_WiFi_EEPROM_Read_r(meta_handle,5000,wifi_eeprom_rdwrt,array_cnt);
    meta_app_result=META_WiFi_EEPROM_Read_r(meta_handle,5000,wifi_eeprom_rdwrt,array_cnt+3); // add aditional 3 word MAC
    if(meta_app_result != 0)
    {
        return meta_app_result;
    }
    power_idx=0;
    for(array_idx=0; array_idx<array_cnt; array_idx++)
    {
        sprintf(wifi_strtemp,"%4x",wifi_eeprom_rdwrt[array_idx].eeprom_data16);
        sprintf(wifi_first,"%c%c",wifi_strtemp[0],wifi_strtemp[1]);
        sprintf(wifi_sec,"%c%c",wifi_strtemp[2],wifi_strtemp[3]);
        if(array_idx==7)
        {
            power_idx=0;
        }
        if(array_idx<7)
        {
            Scan(wifi_first,"%s>%x",&value);
            m_sTxChannelDac2400M.CCKTxPWR[power_idx]= value;
            Scan(wifi_sec,"%s>%x",&value);
            m_sTxChannelDac2400M.CCKTxPWR[power_idx+1]=value;
            power_idx=power_idx+2;
        }
        else
        {
            Scan(wifi_first,"%s>%x",&value);
            m_sTxChannelDac2400M.OFDMTxPWR[power_idx]= value;
            Scan(wifi_sec,"%s>%x",&value);
            m_sTxChannelDac2400M.OFDMTxPWR[power_idx+1]=value;
            power_idx=power_idx+2;
        }
    }
    //b. and then write to the NVRAM
    //wifi_eeprom_rdwrt.eeprom_data16=
    meta_app_result=METAAPP_WiFi_writeTxPower2400MtoNVRAM(meta_handle,&m_sTxChannelDac2400M,5000);
    if(meta_app_result != 0)
    {
        sprintf ( strLog, "\n Write Tx Power to NVRAM Fail!");
        UpdateLog ( strLog, 100);
        return meta_app_result;
    }
    sprintf(strLog,"\n=============== Read TX From EEPROM and Write to NVRAM=====================\n");
    UpdateLog ( strLog, 100);

    //MAC address copy
    for(i = 0; i < 3; i++)
    {
        MAC_Address.mac_addr[2*i+1] 	= (unsigned char) ((wifi_eeprom_rdwrt[array_idx+i].eeprom_data16 & 0xFF00) >> 8);
        MAC_Address.mac_addr[2*i] = (unsigned char) (wifi_eeprom_rdwrt[array_idx+i].eeprom_data16 & 0x00FF);
    }
    meta_app_result = METAAPP_WiFi_writeWiFiMacAddressToNVRAM(meta_handle, 5000, &MAC_Address);
    if(meta_app_result != 0)
    {
        sprintf ( strLog, "\n Write MAC Address to NVRAM Fail!");
        UpdateLog ( strLog, 100 );
        return meta_app_result;
    }

    sprintf(strLog,"\n=============== Read MAC Address From EEPROM and Write to NVRAM=====================\n");
    UpdateLog ( strLog, 100);
  

    return 0;


}


// *******************************************************************************************************************
//            Support 5921 EEPROM copy to NVRAM
// *******************************************************************************************************************
int WiFiTxRelated_move_from_EEPROM_to_NVRAM_MT5921(int meta_handle, char temp[20000])
{
    META_RESULT MetaResult = 0;
    METAAPP_RESULT MetaAppResult = 0;
    S_WIFI_EEPROM m_sEE;
    unsigned int i = 0;
    unsigned int j = 0;
    WiFi_ALC_2400M_S m_sTxPwrAlc2400M;
    int index = 0;
    int offset_index = 0;
    WiFi_TxALC_2400M_S m_sWiFiAlcSlope2400M;
    WiFi_ALC_2400M_S   m_sWiFiAlcPower2400M;
    unsigned int CapID_Storage[2] = {0, 0};		//0: buffer index, 1: value
    unsigned int ThermalValue_Storage[2] = {0, 0};
    int EnvTemp_Storage[2] = {0, 0};
    int MAC_Storage = 0;
    WiFi_MacAddress_S MAC_Address;
    int ReturnValue = 0;
    //Basic procedure
    //a.Prepare the information for META_WiFi_EEPROM_Read_r()
    //b.Reconsturct the information from EEPROM buffer to NVRAM array
    //c.Write the information to NVRAM

    //Refers to TfrmWiFiALC2400M::Compose_EEPROM_Parameter_MT5921(void)
    m_sEE.count = (ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_END - ADDR_MT5921_EEPROM_2_4G_CCK_TX_POWER + 1) + 1;  // CCK, OFDM0,1,2,3: 21*5 = 105, ALC slope
    for (i=0; i<m_sEE.count; i++)
    {
        m_sEE.eeprom[i].index = ADDR_MT5921_EEPROM_ALC_SLOPE + i;
    }
	

    CapID_Storage[0] = m_sEE.count;
    m_sEE.eeprom[m_sEE.count].index = 0x11;
    m_sEE.count++;

    EnvTemp_Storage[0] = m_sEE.count;		//
    ThermalValue_Storage[0] = m_sEE.count;
    m_sEE.eeprom[m_sEE.count].index = 0x81;
    m_sEE.count++;

    //added MAC address read
    MAC_Storage = m_sEE.count;
    for (i=0; i<3; i++)
    {
        m_sEE.eeprom[m_sEE.count].index = 0x13 + i;
        m_sEE.count++;
    }

    MetaResult = META_WiFi_EEPROM_Read_r(meta_handle, 100*m_sEE.count, m_sEE.eeprom, m_sEE.count );
    if(MetaResult != 0)
    {
        sprintf ( strLog, "\n Read From EEPROM Fail!");
        UpdateLog ( strLog, 100);
         return MetaResult;
    }

    sprintf(strLog,"\n=============== Read Info From EEPROM =====================\n");
    UpdateLog (strLog,100);
   

    //Refers to TfrmWiFiALC2400M::WiFiAlcEEToNVRAMFormat_MT5921(void)
    // for VGA gain slope and thermo sensor slope
    m_sWiFiAlcSlope2400M.alcSlop1Divider  = m_sEE.eeprom[0].eeprom_data16 & 0x00FF;
    m_sWiFiAlcSlope2400M.alcSlop1Dividend = 0;
    m_sWiFiAlcSlope2400M.alcSlop2Divider  = (m_sEE.eeprom[0].eeprom_data16 & 0xFF00) >> 8;
    m_sWiFiAlcSlope2400M.alcSlop2Dividend = 0;

    //Write Tx ALC Slope to the NVRAM
    MetaAppResult = METAAPP_WiFi_writeWiFiAlcSlopeToNVRAM(meta_handle, 5000, &m_sWiFiAlcSlope2400M);
    if(MetaAppResult != 0)
    {
        sprintf ( strLog, "\n Write TX ALC Slope to NVRAM Fail!");
        UpdateLog (strLog,100);
        return MetaAppResult;
    }
     sprintf(strLog,"\n=============== Copy TX ALC Slope to NVRAM=====================\n");
     UpdateLog (strLog,100);
    

    offset_index = 1;  // because we read from 0x17 for slope
    for(i = 0; i< NUM_TX_POWER_2400M_CH; i++)
    {
        if(i*3%2 == 0)
        {
            m_sTxPwrAlc2400M.txOutputPowerDBCCK[i] 	= (unsigned char) m_sEE.eeprom[i*3/2+offset_index].eeprom_data16 & 0x00FF;	// TX power DAC
            m_sTxPwrAlc2400M.txAlcCCK[i] 			= (unsigned char) m_sEE.eeprom[i*3/2+1+offset_index].eeprom_data16 & 0x00FF;	// Target ALC
        }
        else // i*3 % 2  ==1
        {
            m_sTxPwrAlc2400M.txOutputPowerDBCCK[i] 	= (unsigned char) ( (m_sEE.eeprom[i*3/2+offset_index].eeprom_data16 & 0xFF00)>>8 );		// TX power DAC
            m_sTxPwrAlc2400M.txAlcCCK[i] 			= (unsigned char) ( (m_sEE.eeprom[i*3/2+1+offset_index].eeprom_data16 & 0xFF00)>>8 );	// Target ALC
        }
    }
    // 2.4GOFDMTxPWRTable 0 (6/9M), 1(12/18M), 2(24/36M), 3(48/54M)
    for(i = 0; i< NUM_TX_POWER_2400M_CH; i++)
    {
        for(j = 0; j< 4; j++)
        {
            index = (j+1)*(ADDR_MT5921_EEPROM_2_4G_OFDM_TX_POWER_STEP)+ i*3/2;
            if(i*3%2 == 0)
            {
                m_sTxPwrAlc2400M.txOutputPowerDBOFDM[j*2][i] = (unsigned char) m_sEE.eeprom[index+offset_index].eeprom_data16 & 0x00FF;	// TX power DAC
                m_sTxPwrAlc2400M.txAlcOFDM[j*2][i] =  (unsigned char) m_sEE.eeprom[index+1+offset_index].eeprom_data16 & 0x00FF;			// Target ALC
            }
            else // i*3 % 2  ==1
            {
                m_sTxPwrAlc2400M.txOutputPowerDBOFDM[j*2][i] = (unsigned char) ( (m_sEE.eeprom[index+offset_index].eeprom_data16 & 0xFF00)>>8 );	// TX power DAC
                m_sTxPwrAlc2400M.txAlcOFDM[j*2][i] =  (unsigned char) ( (m_sEE.eeprom[index+1+offset_index].eeprom_data16 & 0xFF00)>>8 );		// Target ALC
            }
            m_sTxPwrAlc2400M.txOutputPowerDBOFDM[j*2+1][i] = m_sTxPwrAlc2400M.txOutputPowerDBOFDM[j*2][i];	// TX power DAC
            m_sTxPwrAlc2400M.txAlcOFDM[j*2+1][i] = m_sTxPwrAlc2400M.txAlcOFDM[j*2][i];						// Target ALC
        }
    }
    // copy m_sTxPwrAlc2400M to m_sTxChannelDac2400M because it will be used when we "download to flash"
    // assign m_sTxChannelDac2400M according to m_sTxPwrAlc2400M's CCK and OFDM(48/54M)
    for(i = 0; i< NUM_TX_POWER_2400M_CH; i++)
    {
        m_sTxChannelDac2400M.CCKTxPWR[i] =  m_sTxPwrAlc2400M.txOutputPowerDBCCK[i];
        m_sTxChannelDac2400M.OFDMTxPWR[i] =  m_sTxPwrAlc2400M.txOutputPowerDBOFDM[6][i];
    }

    //Write Tx power Dac to the NVRAM
    MetaAppResult = METAAPP_WiFi_writeTxPower2400MtoNVRAM(meta_handle, &m_sTxChannelDac2400M,5000);
    if(MetaAppResult != 0)
    {
        sprintf ( strLog, "\n Write Tx Power to NVRAM Fail!");
        UpdateLog (strLog,100);
        return MetaAppResult;
    }
    MetaAppResult = METAAPP_WiFi_writeWiFiAlcPowerToNVRAM(meta_handle, 5000, &m_sTxPwrAlc2400M);
    if(MetaAppResult != 0)
    {
        sprintf ( strLog, "\n Write ALC Power to NVRAM Fail!");
       UpdateLog (strLog,100);
        return MetaAppResult;
    }
    sprintf(strLog,"\n=============== Copy Tx Power Dac to NVRAM=====================\n");
    UpdateLog (strLog,100);
  

    CapID_Storage[1] = (unsigned char) ((m_sEE.eeprom[CapID_Storage[0]].eeprom_data16 & 0x7F00) >> 8);
    ThermalValue_Storage[1] = (unsigned char) ((m_sEE.eeprom[ThermalValue_Storage[0]].eeprom_data16 & 0xFF00) >> 8);
    EnvTemp_Storage[1] = (char) (m_sEE.eeprom[EnvTemp_Storage[0]].eeprom_data16 & 0x00FF);
    ReturnValue = SetThermo_TrimtoNVRAM(meta_handle, (char) EnvTemp_Storage[1], (unsigned char) ThermalValue_Storage[1], (unsigned char) CapID_Storage[1]);
    if(ReturnValue != 0)
    {
        sprintf ( strLog, "\n Write Thermal and Trimming Info to NVRAM Fail!");
        UpdateLog (strLog,100);
        return MetaAppResult;
    }

     sprintf(strLog,"\n=============== Copy Thermal and Trimming Info to NVRAM=====================\n");
     UpdateLog (strLog,100);
    

    //added on 20090806, MAC address copy
    for(i = 0; i < 3; i++)
    {
        MAC_Address.mac_addr[2*i+1] 	= (unsigned char) ((m_sEE.eeprom[MAC_Storage + i].eeprom_data16 & 0xFF00) >> 8);
        MAC_Address.mac_addr[2*i] = (unsigned char) ( m_sEE.eeprom[MAC_Storage + i].eeprom_data16 & 0x00FF);
    }
    MetaAppResult = METAAPP_WiFi_writeWiFiMacAddressToNVRAM(meta_handle, 5000, &MAC_Address);
    if(MetaAppResult != 0)
    {
        sprintf ( strLog, "\n Write MAC Address to NVRAM Fail!");
        UpdateLog (strLog,100);
        return MetaAppResult;
    }

    sprintf(strLog,"\n=============== Copy MAC Address to NVRAM=====================\n");
    UpdateLog (strLog,100);
    

    return 0;


}

// *******************************************************************************************************************
//            Support 5921 Cap ID Calibration
// *******************************************************************************************************************


//----------------------------------------------------------------------



int func_wifi_mac_meta_hdlr_feature_phone_Ex ( void )
	{	  
		 META_RESULT MR;
		 WiFi_ChipCapability_S	WLAN_Chip_Info;
		 META_RESULT MetaResult = 0;
		 METAAPP_RESULT MetaAppResult = 0;
		 extern int ret_statue;
		 int ret = 0;
		  sprintf ( strLog, ">>-------------------------------------------------------------------<<\n");
		  strcat ( strLog, ">>Step: Enter func_wifi_mac_meta_hdlr_feature_phone_Ex();\n");
		  strcat ( strLog,	"		 Copy Wifi para from EEPROM  to feature phone nvram\n");
		  UpdateLog ( strLog, 0 );
		  
			   sprintf ( strLog,  ">>Step: Start to write Wifi MAC.\n" );
				UpdateLog ( strLog, 50 ); 
				 MetaResult = META_WiFi_QueryChipCapability_r(g_Meta.iMeta_handle, 5000, &WLAN_Chip_Info);
				 if (MetaResult != 0)
				 {	  
						sprintf (strLog, "Read WiFi chip type Fail!\n");
						UpdateLog ( strLog, 50 );
						UpdateIndicator ( KAL_FALSE );
						ret = 1;
						goto err;
				 }
				else
				{
						if(WLAN_Chip_Info.bb_chip_id == WIFI_BB_MT5911)
						{
						MetaAppResult = WiFiTxPcl_move_from_EEPROM_to_NVRAM(g_Meta.iMeta_handle, Cal_Final_rep);
						}
						else if(WLAN_Chip_Info.bb_chip_id == WIFI_BB_MT5921)
						{
						MetaAppResult = WiFiTxRelated_move_from_EEPROM_to_NVRAM_MT5921(g_Meta.iMeta_handle, Cal_Final_rep);
						}
						else
						{
						sprintf (strLog, "Such a WiFi chip is not supported.");
						UpdateLog ( strLog, 50 );
						UpdateIndicator ( KAL_FALSE );
					  
						}
	
					   if (MetaAppResult != 0)
						{
						sprintf (strLog, "Move EEPROM to NVRAM Fail!");
						UpdateLog ( strLog, 50 );
						UpdateIndicator ( KAL_FALSE );
						ret = 2;
						goto err;
						}
						else
						{
						sprintf (strLog, "Move EEPROM to NVRAM ok!");
						UpdateLog ( strLog, 50 );
						UpdateIndicator ( KAL_TRUE);
						}
				}
err:
	return ret;
}
			/*
		   else
			{
				sprintf ( strLog, ">>exit.\n");
				UpdateLog ( strLog, 100);
							
			} 
			
			ExitMetaMode ();   	
			*/
	

int ModemMeta1ToModemMeta2 (void)
{
	
	META_RESULT MetaResult;
	META_ConnectInMETA_Req BootRequest;
	int BootStop=0;
	META_ConnectInMETA_Report BootReport;
	
	
	
	META_ConnectByUSB_Req usbRequest;
	META_ConnectByUSB_Report usbReport;
	
	//MetaResult = META_DisconnectInMetaMode_r (g_Meta.iMeta_handle);
	//MetaResult = FP_META_DisconnectInMetaMode_r (g_Meta.iMeta_handle);
	if (META_SUCCESS != MetaResult)
	{
		return MetaResult;
	}
    if(Nvram2DatabaseInit ())
    {
        sprintf ( strLog, ">>Step: Load modem2 database fail.\n");
	    UpdateLog ( strLog, 100 );
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
		usbRequest.com_port = usb_port;
        usbRequest.ms_connect_timeout =8000;
        MetaResult = META_ConnectInMetaModeByUSB_r(g_Meta.iMeta_handle2, &usbRequest, &g_Meta.bootstop, &usbReport);
	}
    else
	{
        MetaResult = META_ConnectInMetaMode_r(g_Meta.iMeta_handle2, &BootRequest, &BootStop, &BootReport);
	}

	Sleep(100);	
	if(META_SUCCESS != MetaResult && META_MAUI_DB_INCONSISTENT != MetaResult)
	{
		return MetaResult;
	}

	return MetaResult;
	
}


int ApMetaToModemMeta ( void )
{
    META_RESULT MetaResult;
	META_ConnectInMETA_Req BootRequest;
	int BootStop=0;
	META_ConnectInMETA_Report BootReport;



	META_ConnectByUSB_Req usbRequest;
    META_ConnectByUSB_Report usbReport;

    MetaResult = AP_META_DisconnectInMetaMode_r (g_Meta.iMetaAP_handle);
	//MetaResult = WM_META_DisconnectInMetaMode_r(g_Meta.iMetaAP_handle);
	if(META_SUCCESS != MetaResult)
	{
             // MessagePopup ("SP", "DisconnectFromApMeta Fail!");
		return MetaResult;
	}

	//---------------------Connect with target ----------------------------------
	BootRequest.com_port = GetCOMPort ();
	// [META] META stage baudrate polling array, it must end with META_BAUD_END.
	BootRequest.baudrate[0] = META_BAUD115200;
	BootRequest.baudrate[1] = META_BAUD230400;
	BootRequest.baudrate[2] = META_BAUD460800;
	BootRequest.baudrate[3] = META_BAUD921600;
	BootRequest.baudrate[4] = META_BAUD57600;
	BootRequest.baudrate[5] = META_BAUD_END;

	BootRequest.flowctrl = META_SW_FLOWCTRL;
	BootRequest.ms_connect_timeout = 80000; //30000;

        if(IsUSBCOMPort())
        {
            
		    usbRequest.com_port = usb_port;
            usbRequest.ms_connect_timeout =8000;
            MetaResult = META_ConnectInMetaModeByUSB_r(g_Meta.iMeta_handle, &usbRequest, &g_Meta.bootstop, &usbReport);
		}
		else
		{
        MetaResult = META_ConnectInMetaMode_r(g_Meta.iMeta_handle, &BootRequest, &BootStop, &BootReport);
		}

		
	if(META_SUCCESS != MetaResult && META_MAUI_DB_INCONSISTENT != MetaResult)
	{
             // MessagePopup ("SP", "META_ConnectInMetaMode_r Fail!");
		return MetaResult;
	}

	return META_SUCCESS;
}


int  FP_META_DisconnectInMetaMode_r(const int meta_handle)
{
    META_RESULT meta_result = META_SUCCESS;
    meta_result = META_DisconnectInMetaMode_r (meta_handle);
    return meta_result;
}

int FP_METAAPP_writeBarcodetoNVRAM( const int meta_handle, int timeout, char *p_Barcode )
{
    METAAPP_RESULT metaapp_result = METAAPP_SUCCESS;
    metaapp_result = METAAPP_writeBarcodetoNVRAM(meta_handle, p_Barcode, timeout);
    return metaapp_result;
}

int FP_METAAPP_readBarcodefromNVRAM( const int meta_handle, int timeout, char *p_Barcode )
{
    METAAPP_RESULT metaapp_result = METAAPP_SUCCESS;
    metaapp_result = METAAPP_readBarcodefromNVRAM(meta_handle, timeout, p_Barcode);
    return metaapp_result;
}

int FP_WriteImeiToNvram(const int meta_handle, int timeout, char *p_IMEI1, char *p_IMEI2)
{
	IMEISV_struct_T tIMEIScanBack,tImei_Svn_Pad;
	kal_int8 strSvn[4];
	kal_uint8 iIMEICheckSum, i;
	kal_uint8 strTip [256];
	kal_uint16 iLoop = 0;

	strcpy(tImei_Svn_Pad.imei, p_IMEI1);
	
	for ( i = 0; i<= GetIsDualImei(); i++ )
	{
		if ( !GetIsSVNPAD_Enable ())
		{	
			sprintf ( strLog, ">>Step: To get SVN and PAD from phone.\n" );
			UpdateLog ( strLog, 40 );
			
			if ( METAAPP_readIMEIfromNVRAM_Ex3 ( meta_handle, 5000, i+1, &tIMEIScanBack))
			{
				sprintf ( strLog, "   Error: METAAPP_readIMEIfromNVRAM_Ex3 fail.\n" );
				UpdateLog ( strLog, 100 );
				UpdateIndicator ( KAL_FALSE );
				
				MessagePopup ("Meta Error", "Meta IMEI read fail!"); 
				break;
			}
						
			tImei_Svn_Pad.pad = tIMEIScanBack.pad ;
			tImei_Svn_Pad.svn = tIMEIScanBack.svn ;
		} else 
		{

			tImei_Svn_Pad.pad = GetSVNPAD().pad;
			tImei_Svn_Pad.svn = GetSVNPAD().svn;
		}
		
		Fmt ( strSvn, "%s<%x", tImei_Svn_Pad.svn ); 
		if ( tImei_Svn_Pad.svn < 10)
		{  strSvn[1] = strSvn[0]; strSvn[0] = '0';strSvn[2] = '\0';}
		swap_c ( &strSvn[0], &strSvn[1]);
		
		sprintf ( strLog, "   OK: SVN=0x%s and PAD=0x%x \n", strSvn, tImei_Svn_Pad.pad );
		UpdateLog ( strLog, 50 );	
		
		sprintf(strLog, "IMEI = %s is going to write\n", tImei_Svn_Pad.imei);
		UpdateLog ( strLog, 55 );
		
		sprintf ( strLog,  ">>Step: Start to write. CheckSum=%d, IMEILock=%d.\n", GetIsImeiCheckSum (), GetIsImeiLock());
		UpdateLog ( strLog, 60 );	

		g_Meta6516Modem.eMeta_Result = METAAPP_writeIMEItoNVRAM_Ex3( meta_handle, 5000, GetIsImeiCheckSum (), GetIsImeiLock(), i+1, &tImei_Svn_Pad);
		switch ( g_Meta6516Modem.eMeta_Result )
		{
		case METAAPP_SUCCESS:
			
			sprintf ( strLog, "   OK: Write IMEI successfully.\n"  );
			UpdateLog ( strLog, 65 );	
			break;
 
		case METAAPP_NVRAM_COMPOSE_IMEI_FAIL:
			
			sprintf ( strLog, "   Error: IMEI Check Sum error!\n"  );
			UpdateLog ( strLog, 90 );	
			UpdateIndicator ( KAL_FALSE );
			MessagePopup ("IMEI CheckSum error", " CheckSum of IMEI error!");
			break;
			
		default: 
			
			sprintf ( strLog, "   Error: Write IMEI fail. Meta Result = %d\n", g_Meta6516Modem.eMeta_Result );
			UpdateLog ( strLog, 100 );	
			UpdateIndicator ( KAL_FALSE );
			break;	
		}

		if ( METAAPP_readIMEIfromNVRAM_Ex3 ( meta_handle, 5000, i+1, &tIMEIScanBack))
		{
			sprintf ( strLog, "   Error: METAAPP_readIMEIfromNVRAM_Ex3 fail.\n" );
			UpdateLog ( strLog, 100 );
			UpdateIndicator ( KAL_FALSE );
			
			MessagePopup ("Meta Error", "Meta IMEI read fail!"); 
			break;
		
		}

		if ( memcmp ( tIMEIScanBack.imei, tImei_Svn_Pad.imei, IMEI_MAX_LENGTH ) )
		{
			sprintf ( strLog, "   Error: Check IMEI fail.  imei = \"%s\".\n", tIMEIScanBack.imei );
			UpdateLog ( strLog, 100 );
			UpdateIndicator ( KAL_FALSE );
			MessagePopup ("IMEI Error", " Read/Write check IMEI error");
		}
		else
		{
			sprintf ( strLog, "   OK: Check IMEI. Rd_imei = \"%s\".\n", tIMEIScanBack.imei );
			UpdateLog ( strLog, 70 );
			
		}
				
		if  ( !GetIsDualImei())
		{
			break;
		}else
		{
			strncpy(tImei_Svn_Pad.imei, p_IMEI2, strlen(p_IMEI2));
		}
		
	}
	return 1;
}

void ResetDatabaseInitFlag(void)
{ 
   g_Meta.bIsDatabaseInitialized[0] = KAL_FALSE;
   g_Meta.bIsDatabaseInitialized[1] = KAL_FALSE;
   g_Meta.bIsDatabaseInitialized[2] = KAL_FALSE;
}

