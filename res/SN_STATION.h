/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2013. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  Combine                         1
#define  Combine_Combine_OK              2       /* callback function: Combine_Ok_click */
#define  Combine_Combine_Cancel          3       /* callback function: Combine_Cancel_click */
#define  Combine_DECORATION              4
#define  Combine_AMR                     5       /* callback function: AMRSet_Click */
#define  Combine_SetAMR                  6       /* callback function: Set_AMR_click */
#define  Combine_ClearAMR                7       /* callback function: Clear_AMR_click */
#define  Combine_Data_prefer             8       /* callback function: Data_prefer_click */
#define  Combine_Call_prefer             9       /* callback function: Call_prefer_click */
#define  Combine_data_call               10      /* callback function: data_call_click */
#define  Combine_SDS                     11      /* callback function: SDS_click */

#define  PANEL                           2
#define  PANEL_IDBarCode                 2       /* callback function: ScanDataEdit_EnterKeyPress */
#define  PANEL_FirstIMEI                 3       /* callback function: ScanDataEdit_EnterKeyPress */
#define  PANEL_SecondIMEI                4       /* callback function: ScanDataEdit_EnterKeyPress */
#define  PANEL_IDBT                      5       /* callback function: ScanDataEdit_EnterKeyPress */
#define  PANEL_IDWIFI                    6       /* callback function: ScanDataEdit_EnterKeyPress */
#define  PANEL_OK                        7       /* callback function: OK_Key_Click */
#define  PANEL_Cancel                    8       /* callback function: Cancel_Key_Click */
#define  PANEL_DECORATION                9
#define  PANEL_Head                      10
#define  PANEL_strBarcHead               11
#define  PANEL_strImei1Head              12
#define  PANEL_strImei4Head              13
#define  PANEL_strImei3Head              14
#define  PANEL_strImei2Head              15
#define  PANEL_strBThead                 16
#define  PANEL_strWifiHead               17
#define  PANEL_FourthIMEI                18      /* callback function: ScanDataEdit_EnterKeyPress */
#define  PANEL_ThirdIMEI                 19      /* callback function: ScanDataEdit_EnterKeyPress */

#define  panelAbout                      3
#define  panelAbout_bnOK                 2       /* callback function: About_Quit_Click */
#define  panelAbout_ABOUT_TITLE_2        3
#define  panelAbout_ABOUT_TITLE_4        4
#define  panelAbout_ABOUT_TITLE_5        5
#define  panelAbout_ABOUT_TITLE_3        6
#define  panelAbout_ABOUT_TITLE          7

#define  panelCfg                        4
#define  panelCfg_bBarCode               2       /* callback function: BarCode_Click */
#define  panelCfg_bIMEI                  3       /* callback function: IMEI_Click */
#define  panelCfg_bBT                    4       /* callback function: BT_Click */
#define  panelCfg_bWIFIMacadr            5       /* callback function: WIFIMacadr_Click */
#define  panelCfg_DECORATION             6
#define  panelCfg_bCheckSum              7       /* callback function: CheckSum_Click */
#define  panelCfg_bDualIMEI              8       /* callback function: DualIMEI_Click */
#define  panelCfg_DECORATION_2           9
#define  panelCfg_strBarcHead            10
#define  panelCfg_bCheckBcHead           11      /* callback function: CheckBarcHead_Click */
#define  panelCfg_strIMEI1Head           12
#define  panelCfg_bCheckImei1Head        13      /* callback function: CheckImei1Head_Click */
#define  panelCfg_strIMEI2Head           14
#define  panelCfg_bCheckImei2Head        15      /* callback function: CheckImei2Head_Click */
#define  panelCfg_strBTHead              16
#define  panelCfg_bCheckBThead           17      /* callback function: CheckBTHead_Click */
#define  panelCfg_strWifiHead            18
#define  panelCfg_bCheckWifiHead         19      /* callback function: CheckWifiHead_Click */
#define  panelCfg_Modem_Database_Select  20      /* callback function: Modem_Database_Select_Click */
#define  panelCfg_Modem_DB_Select_2      21      /* callback function: Modem_DB_Select_2 */
#define  panelCfg_AP_Database_Select     22      /* callback function: AP_Database_Select_Click */
#define  panelCfg_ConfidOK               23      /* callback function: Cfg_OK_Click */
#define  panelCfg_DECORATION_3           24
#define  panelCfg_DECORATION_4           25
#define  panelCfg_strModem_Database      26
#define  panelCfg_strModem_Database_2    27
#define  panelCfg_strAP_Database         28
#define  panelCfg_TEXTMSG                29
#define  panelCfg_TEXTMSG_2              30
#define  panelCfg_TEXTMSG_3              31
#define  panelCfg_bWIFIEEPROMCopy        32      /* callback function: WIFIEEPROMCopy_Click */
#define  panelCfg_DualImeiSame           33      /* callback function: DualImei_Same_Click */
#define  panelCfg_TEXTMSG_4              34
#define  panelCfg_bThreeIMEI             35      /* callback function: ThreeIMEI_Click */
#define  panelCfg_bFourIMEI              36      /* callback function: FourIMEI_Click */
#define  panelCfg_strIMEI3Head           37
#define  panelCfg_strIMEI4Head           38
#define  panelCfg_bCheckImei3Head        39      /* callback function: CheckImei3Head_Click */
#define  panelCfg_bCheckImei4Head        40      /* callback function: CheckImei4Head_Click */

#define  PanelChgpw                      5
#define  PanelChgpw_OldPassword          2       /* callback function: ChgPasswordCtrl_EnterPress */
#define  PanelChgpw_NewPassword          3       /* callback function: ChgPasswordCtrl_EnterPress */
#define  PanelChgpw_ConfirmPassword      4       /* callback function: ChgPasswordCtrl_EnterPress */
#define  PanelChgpw_ChgpasswdOK          5       /* callback function: ChgpasswdOK_Click */
#define  PanelChgpw_ChgpasswdCancel      6       /* callback function: ChgpasswdCancel_Click */

#define  PanelEngin                      6
#define  PanelEngin_Password             2       /* callback function: PasswordCtrl_EnterPress */
#define  PanelEngin_IdentityCheckOK      3       /* callback function: IdentityCheckOK_Click */
#define  PanelEngin_IdenttityCheckCancel 4       /* callback function: IdenttityCheckCancel_Click */
#define  PanelEngin_MsgDefaultPswd       5

#define  panelIMEI                       7
#define  panelIMEI_IMEISVN               2
#define  panelIMEI_SvnPad_OK             3       /* callback function: Imei_SvnPad_OK_Click */
#define  panelIMEI_SvnPad_Cancel         4       /* callback function: Imei_SvnPad_Cancel_Click */
#define  panelIMEI_IMEIPAD               5
#define  panelIMEI_SvnPadEnable_2        6
#define  panelIMEI_AutoCheckSum          7

#define  panelInput                      8
#define  panelInput_mInputBox            2       /* callback function: InputBox_Click */
#define  panelInput_Enter                3       /* callback function: Enter_Click */
#define  panelInput_Cancel               4       /* callback function: Cancel_Click */

#define  panelMain                       9
#define  panelMain_START_WRITE           2       /* callback function: Start_Write_Click */
#define  panelMain_QUIT                  3       /* callback function: Quit_Click */
#define  panelMain_eCOMPort              4       /* callback function: COMPORT_Select_Click */
#define  panelMain_ResultIndicator       5
#define  panelMain_DR_TGT                6
#define  panelMain_ST_DSP                7
#define  panelMain_DR_IMEI               8
#define  panelMain_strLog_Display        9
#define  panelMain_eTargetSelect         10      /* callback function: TargetSelect_Click */
#define  panelMain_mProgressBar          11
#define  panelMain_mFail                 12
#define  panelMain_mPass                 13
#define  panelMain_mTotal                14
#define  panelMain_PRO_DISPLAY           15
#define  panelMain_System_Config         16      /* callback function: System_Config_Click */
#define  panelMain_mTIMER                17      /* callback function: TimerOut_Callback */
#define  panelMain_mTIMER_2              18      /* callback function: Timer2Out_Callback */
#define  panelMain_TEXTMSG               19


     /* Menu Bars, Menus, and Menu Items: */

#define  menuMain                        1
#define  menuMain_File                   2
#define  menuMain_File_ModemDatabase     3       /* callback function: menu_Modem_Database_Select_Click */
#define  menuMain_File_Modem2Database    4       /* callback function: menu_Modem2_Database_Select_Click */
#define  menuMain_File_APDatabase        5       /* callback function: menu_AP_Database_Select_Click */
#define  menuMain_File_AuthFile          6       /* callback function: menu_Authen_File_Select_Click */
#define  menuMain_File_SecuFile          7       /* callback function: menu_SpSecuen_File_Select_Click */
#define  menuMain_File_HdcpBinFile       8       /* callback function: menu_Hdcp_BinFile_Select */
#define  menuMain_File_DRMKeyFile        9       /* callback function: menu_DRM_Key_File_Select */
#define  menuMain_File_SEPARATOR         10
#define  menuMain_File_Exit              11      /* callback function: menu_Exit_Click */
#define  menuMain_Option                 12
#define  menuMain_Option_SPSecurreUSB    13      /* callback function: SP_Securre_USB_Click */
#define  menuMain_Option_Datacard        14      /* callback function: menu_Datacard_Click */
#define  menuMain_Option_DualTalk        15      /* callback function: menu_DualTalk_Click */
#define  menuMain_Option_BB              16
#define  menuMain_Option_BB_SUBMENU      17
#define  menuMain_Option_BB_AutoDetect   18      /* callback function: menu_BBAutoDetect_Click */
#define  menuMain_Option_COMM            19
#define  menuMain_Option_Baud            20
#define  menuMain_Option_Baud_SUBMENU    21
#define  menuMain_Option_Baud_Baud961200 22      /* callback function: menu_Baud_Rate_Click */
#define  menuMain_Option_Baud_Baud460800 23      /* callback function: menu_Baud_Rate_Click */
#define  menuMain_Option_Baud_BAUD230400 24      /* callback function: menu_Baud_Rate_Click */
#define  menuMain_Option_Baud_Baud115200 25      /* callback function: menu_Baud_Rate_Click */
#define  menuMain_Option_Baud_Baud57600  26      /* callback function: menu_Baud_Rate_Click */
#define  menuMain_Option_Target          27
#define  menuMain_Option_Target_SUBMENU  28
#define  menuMain_Option_Target_Phone    29      /* callback function: menu_TargetSelect_Click */
#define  menuMain_Option_Target_PPC      30      /* callback function: menu_TargetSelect_Click */
#define  menuMain_Option_Target_PCMCIA   31      /* callback function: menu_TargetSelect_Click */
#define  menuMain_Option_Target_WifiOnly 32      /* callback function: menu_TargetSelect_Click */
#define  menuMain_Option_Target_SPDualMD 33      /* callback function: menu_TargetSelect_Click */
#define  menuMain_Option_Target_RndisDong 34     /* callback function: menu_TargetSelect_Click */
#define  menuMain_Option_SEPARATOR_2     35
#define  menuMain_Option_OperMode        36
#define  menuMain_Option_OperMode_SUBMENU 37
#define  menuMain_Option_OperMode_Meta   38      /* callback function: menu_Write_Mode_Selection_Click */
#define  menuMain_Option_OperMode_AT     39      /* callback function: menu_Write_Mode_Selection_Click */
#define  menuMain_Option_Func            40
#define  menuMain_Option_Func_SUBMENU    41
#define  menuMain_Option_Func_Barcode    42      /* callback function: menu_Barcode_Click */
#define  menuMain_Option_Func_IMEI       43      /* callback function: menu_IMEI_Click */
#define  menuMain_Option_Func_BTAddr     44      /* callback function: menu_BTAddr_Click */
#define  menuMain_Option_Func_WIFIMac    45      /* callback function: menu_WIFI_Mac_Click */
#define  menuMain_Option_SEPARATOR_6     46
#define  menuMain_Option_FpOption        47
#define  menuMain_Option_FpOption_SUBMENU 48
#define  menuMain_Option_FpOption_SDS    49      /* callback function: menu_ATSDS_Click */
#define  menuMain_Option_FpOption_MetaNoB 50     /* callback function: menu_NoBattery_Click */
#define  menuMain_Option_SEPARATOR_3     51
#define  menuMain_Option_LogOption       52
#define  menuMain_Option_LogOption_SUBMEN 53
#define  menuMain_Option_LogOption_Enable 54     /* callback function: menu_EnableLog_Click */
#define  menuMain_Option_LogOption_Clear 55      /* callback function: menu_ClearCountLog_Click */
#define  menuMain_Option_Refresh_COM     56      /* callback function: menu_RefreshCOMPort_Click */
#define  menuMain_BTIMEI                 57
#define  menuMain_BTIMEI_Chip            58
#define  menuMain_BTIMEI_Chip_SUBMENU    59
#define  menuMain_BTIMEI_Chip_MT6601     60      /* callback function: menu_BT_Chip_Click */
#define  menuMain_BTIMEI_Chip_MT6611     61      /* callback function: menu_BT_Chip_Click */
#define  menuMain_BTIMEI_Chip_RFMD3500   62      /* callback function: menu_BT_Chip_Click */
#define  menuMain_BTIMEI_BTPower         63
#define  menuMain_BTIMEI_BTPower_SUBMENU 64
#define  menuMain_BTIMEI_BTPower_On      65      /* callback function: menu_BT_Power_Click */
#define  menuMain_BTIMEI_BTPower_Off     66      /* callback function: menu_BT_Power_Click */
#define  menuMain_BTIMEI_SEPARATOR_4     67
#define  menuMain_BTIMEI_SVNPAD          68      /* callback function: menu_SVNPAD_Setting_Click */
#define  menuMain_BTIMEI_CheckSum        69      /* callback function: Menu_Check_Sum_Click */
#define  menuMain_BTIMEI_LockIMEI        70      /* callback function: menu_Lock_IMEI_Click */
#define  menuMain_BTIMEI_DualIMEI        71      /* callback function: menu_Dual_IMEI_Click */
#define  menuMain_BTIMEI_ThreeIMEI       72      /* callback function: menu_ThreeIMEI_Click */
#define  menuMain_BTIMEI_FourIMEI        73      /* callback function: menu_FoutIMEI_Click */
#define  menuMain_BTIMEI_SEPARATOR_5     74
#define  menuMain_BTIMEI_FTStatus        75      /* callback function: menu_FT_Status_Click */
#define  menuMain_HDCPDRMKEY             76
#define  menuMain_HDCPDRMKEY_HDCP        77      /* callback function: menu_HDCP_Click */
#define  menuMain_HDCPDRMKEY_DRMKeyInstal 78     /* callback function: menu_DRMKey_Click */
#define  menuMain_Identity               79
#define  menuMain_Identity_Operator      80      /* callback function: menu_Operator_Click */
#define  menuMain_Identity_Operator_SUBME 81
#define  menuMain_Identity_Operator_Switc 82     /* callback function: menu_SwitchToEngineer_Click */
#define  menuMain_Identity_Engineer      83      /* callback function: menu_Engineer_Click */
#define  menuMain_Identity_Engineer_SUBME 84
#define  menuMain_Identity_Engineer_Switc 85     /* callback function: menu_SwitchToOperator_Click */
#define  menuMain_Identity_Engineer_Chang 86     /* callback function: menu_ChangePasswd_Click */
#define  menuMain_Help                   87
#define  menuMain_Help_About             88      /* callback function: menu_About_Click */


     /* Callback Prototypes: */ 

int  CVICALLBACK About_Quit_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AMRSet_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AP_Database_Select_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BarCode_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BT_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Call_prefer_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cancel_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cancel_Key_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cfg_OK_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckBarcHead_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckBTHead_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckImei1Head_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckImei2Head_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckImei3Head_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckImei4Head_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckSum_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckWifiHead_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChgpasswdCancel_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChgpasswdOK_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChgPasswordCtrl_EnterPress(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clear_AMR_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Combine_Cancel_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Combine_Ok_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK COMPORT_Select_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK data_call_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Data_prefer_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DualIMEI_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DualImei_Same_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enter_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FourIMEI_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdentityCheckOK_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdenttityCheckCancel_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IMEI_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Imei_SvnPad_Cancel_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Imei_SvnPad_OK_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK InputBox_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK menu_About_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_AP_Database_Select_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_ATSDS_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Authen_File_Select_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Barcode_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Baud_Rate_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_BBAutoDetect_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_BT_Chip_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_BT_Power_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_BTAddr_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_ChangePasswd_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Menu_Check_Sum_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_ClearCountLog_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Datacard_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_DRM_Key_File_Select(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_DRMKey_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Dual_IMEI_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_DualTalk_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_EnableLog_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Engineer_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Exit_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_FoutIMEI_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_FT_Status_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Hdcp_BinFile_Select(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_HDCP_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_IMEI_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Lock_IMEI_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Modem2_Database_Select_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Modem_Database_Select_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_NoBattery_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Operator_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_RefreshCOMPort_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_SpSecuen_File_Select_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_SVNPAD_Setting_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_SwitchToEngineer_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_SwitchToOperator_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_TargetSelect_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_ThreeIMEI_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_WIFI_Mac_Click(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menu_Write_Mode_Selection_Click(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Modem_Database_Select_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Modem_DB_Select_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OK_Key_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PasswordCtrl_EnterPress(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ScanDataEdit_EnterKeyPress(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SDS_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Set_AMR_click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK SP_Securre_USB_Click(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Start_Write_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK System_Config_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TargetSelect_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ThreeIMEI_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Timer2Out_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerOut_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WIFIEEPROMCopy_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WIFIMacadr_Click(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
