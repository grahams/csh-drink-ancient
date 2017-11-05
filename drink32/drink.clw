; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDrinkButton
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "drink.h"
LastPage=0

ClassCount=18
Class1=CDrinkApp
Class2=CDrinkDoc
Class3=CDrinkView
Class4=CMainFrame

ResourceCount=16
Resource1=Drink_LoginInvalid
Resource2=Drink_Server_Dialog
Resource3=Drink_DropDelay_Dialog
Class5=CAboutDlg
Class6=CChildFrame
Resource4=Drink_Drop_Abort
Resource5=IDR_DRINKTYPE
Class7=CLoginDialog
Class8=COptionsDialog
Resource6=Drink_Drop_Failed
Resource7=Drink_DropDialog
Resource8=Drink_Drop
Resource9=Drink_Drop_Successful
Class9=CDropDialog
Class10=CDropDelayDialog
Resource10=IDR_DRINKTYPE_CNTR_IP
Class11=COpenDialog
Resource11=Drink_Login_Dialog
Class12=CInvalidLoginDialog
Resource12=IDR_MAINFRAME
Resource13=Drink_Options_Dialog
Class13=CDropFailed
Class14=CDropSuccess
Class15=CDropAbortDialog
Resource14=Drink_Open
Class16=Drink_ServerDialog
Resource15=Drink_Meta_FailedDialog
Class17=CMetaFailedDialog
Class18=CDrinkButton
Resource16=IDD_ABOUTBOX

[CLS:CDrinkApp]
Type=0
HeaderFile=drink.h
ImplementationFile=drink.cpp
Filter=W
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CDrinkApp

[CLS:CDrinkDoc]
Type=0
HeaderFile=drinkDoc.h
ImplementationFile=drinkDoc.cpp
Filter=N
LastObject=CDrinkDoc

[CLS:CDrinkView]
Type=0
HeaderFile=drinkView.h
ImplementationFile=drinkView.cpp
Filter=D
BaseClass=CView
VirtualFilter=VWC
LastObject=CDrinkView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=C
LastObject=CChildFrame

[CLS:CAboutDlg]
Type=0
HeaderFile=drink.cpp
ImplementationFile=drink.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=Drink_Close
Command3=Grey_Login
Command4=Grey_Logout
Command5=Grey_Logout_All
Command6=ID_APP_EXIT
Command7=ID_VIEW_STATUS_BAR
Command8=Grey_Options
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_DRINKTYPE]
Type=1
Class=CDrinkView
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=Drink_Login
Command4=Drink_Logout
Command5=Drink_Logout_All
Command6=ID_APP_EXIT
Command7=ID_VIEW_STATUS_BAR
Command8=Drink_Options
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_ARRANGE
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_DRINKTYPE_CNTR_IP]
Type=1
Class=CDrinkView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_WINDOW_CASCADE
Command9=ID_WINDOW_ARRANGE
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_CANCEL_EDIT_CNTR
Command6=ID_NEXT_PANE
Command7=ID_PREV_PANE
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
CommandCount=11

[ACL:IDR_DRINKTYPE_CNTR_IP]
Type=1
Class=CDrinkView
Command1=Drink_Logout_All
Command2=Drink_Login
Command3=Drink_Logout
Command4=ID_CANCEL_EDIT_CNTR
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_APP_EXIT
CommandCount=7

[DLG:Drink_Options_Dialog]
Type=1
Class=COptionsDialog
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=Drink_OptionsDelay,edit,1350631552
Control4=Drink_OptionsLabel4,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280
Control5=IDC_STATIC,button,1342177287
Control6=Drink_OptionsOpen,button,1342242819
Control7=Drink_OptionsLogin,button,1342242819
Control8=Drink_OptionsGamble,button,1342242819
Control9=Drink_OptionsSaveUser,button,1342242819
Control10=Drink_OptionsServer,edit,1350631552
Control11=Drink_OptionsLabel5,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280

[DLG:Drink_Login_Dialog]
Type=1
Class=CLoginDialog
ControlCount=7
Control1=Drink_LoginOK,button,1342242817
Control2=Drink_LoginCANCEL,button,1342242816
Control3=IDC_LABEL1,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280
Control4=IDC_LABEL2,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280
Control5=Drink_LoginUsername,edit,1350631552
Control6=Drink_LoginPassword,edit,1350631584
Control7=Drink_LoginSave,button,1342242819

[CLS:CLoginDialog]
Type=0
HeaderFile=LoginDialog.h
ImplementationFile=LoginDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginDialog
VirtualFilter=dWC

[CLS:COptionsDialog]
Type=0
HeaderFile=OptionsDialog.h
ImplementationFile=OptionsDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDCANCEL

[DLG:Drink_DropDialog]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=Drink_DropDelay,edit,1350631552
Control4=IDC_LABEL1,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280

[DLG:Drink_Drop]
Type=1
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:Drink_DropDelay_Dialog]
Type=1
Class=CDropDelayDialog
ControlCount=4
Control1=DelayDialog_Drop,button,1342242817
Control2=Drink_DropCancel,button,1342242816
Control3=Drink_DropDelay,edit,1350631552
Control4=IDC_LABEL1,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280

[CLS:CDropDialog]
Type=0
HeaderFile=DropDialog.h
ImplementationFile=DropDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDropDialog

[CLS:CDropDelayDialog]
Type=0
HeaderFile=DropDelayDialog.h
ImplementationFile=DropDelayDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDropDelayDialog
VirtualFilter=dWC

[DLG:Drink_Open]
Type=1
Class=COpenDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=Drink_OpenTree,SysTreeView32,1350631479
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1350701056
Control7=Drink_OpenHelp,button,1342242816

[CLS:COpenDialog]
Type=0
HeaderFile=OpenDialog.h
ImplementationFile=OpenDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=COpenDialog
VirtualFilter=dWC

[DLG:Drink_LoginInvalid]
Type=1
Class=CInvalidLoginDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CInvalidLoginDialog]
Type=0
HeaderFile=InvalidLoginDialog.h
ImplementationFile=InvalidLoginDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CInvalidLoginDialog

[DLG:Drink_Drop_Failed]
Type=1
Class=CDropFailed
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CDropFailed]
Type=0
HeaderFile=DropFailed.h
ImplementationFile=DropFailed.cpp
BaseClass=CDialog
Filter=D
LastObject=CDropFailed

[DLG:Drink_Drop_Successful]
Type=1
Class=CDropSuccess
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CDropSuccess]
Type=0
HeaderFile=DropSuccess.h
ImplementationFile=DropSuccess.cpp
BaseClass=CDialog
Filter=D
LastObject=CDropSuccess

[DLG:Drink_Drop_Abort]
Type=1
Class=CDropAbortDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CDropAbortDialog]
Type=0
HeaderFile=DropAbortDialog.h
ImplementationFile=DropAbortDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDropAbortDialog

[DLG:Drink_Server_Dialog]
Type=1
Class=Drink_ServerDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=Drink_ServerEdit,edit,1350631552
Control4=IDC_LABEL1,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280

[CLS:Drink_ServerDialog]
Type=0
HeaderFile=Drink_ServerDialog.h
ImplementationFile=Drink_ServerDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=Drink_ServerDialog
VirtualFilter=dWC

[DLG:Drink_Meta_FailedDialog]
Type=1
Class=CMetaFailedDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CMetaFailedDialog]
Type=0
HeaderFile=MetaFailedDialog.h
ImplementationFile=MetaFailedDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMetaFailedDialog

[CLS:CDrinkButton]
Type=0
HeaderFile=DrinkButton.h
ImplementationFile=DrinkButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CDrinkButton

