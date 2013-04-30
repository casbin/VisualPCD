; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVisualPCDInputDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "visualpcd.h"
LastPage=0

ClassCount=10
Class1=CAdvEdit
Class2=CVisualPCDApp
Class3=CVisualPCDAboutDlg
Class4=CAboutDlg
Class5=CVisualPCDDlg

ResourceCount=6
Resource1=IDD_VISUALPCD_DIALOG
Resource2=IDD_TRANS
Class6=CVisualPCDResultDlg
Class7=CVisualPCDFileDlg
Resource3=IDD_RESULT
Class8=CVisualPCDTransDlg
Resource4=IDD_INPUT
Class9=CVisualPCDInputDlg
Resource5=IDD_ABOUTBOX
Class10=CVisualPCDGraphDlg
Resource6=IDD_GRAPH

[CLS:CAdvEdit]
Type=0
BaseClass=CEdit
HeaderFile=AdvEdit.h
ImplementationFile=AdvEdit.cpp

[CLS:CVisualPCDApp]
Type=0
BaseClass=CWinApp
HeaderFile=VisualPCD.h
ImplementationFile=VisualPCD.cpp

[CLS:CVisualPCDAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=VisualPCDAboutDlg.h
ImplementationFile=VisualPCDAboutDlg.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=VisualPCDDlg.cpp
ImplementationFile=VisualPCDDlg.cpp
LastObject=CAboutDlg

[CLS:CVisualPCDDlg]
Type=0
BaseClass=CBitmapDialog
HeaderFile=VisualPCDDlg.h
ImplementationFile=VisualPCDDlg.cpp
LastObject=IDC_EDIT3
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CVisualPCDAboutDlg
ControlCount=0

[DLG:IDD_VISUALPCD_DIALOG]
Type=1
Class=CVisualPCDDlg
ControlCount=3
Control1=IDC_EDIT1,edit,1342247044
Control2=IDC_EDIT2,edit,1342247044
Control3=IDC_EDIT3,edit,1342247044

[DLG:IDD_RESULT]
Type=1
Class=CVisualPCDResultDlg
ControlCount=1
Control1=IDC_EDIT_RESULT,edit,1352732676

[CLS:CVisualPCDResultDlg]
Type=0
HeaderFile=VisualPCDResultDlg.h
ImplementationFile=VisualPCDResultDlg.cpp
BaseClass=CDialog
Filter=C
LastObject=CVisualPCDResultDlg
VirtualFilter=dWC

[CLS:CVisualPCDFileDlg]
Type=0
HeaderFile=VisualPCDFileDlg.h
ImplementationFile=VisualPCDFileDlg.cpp
BaseClass=CFileDialog
Filter=N
LastObject=CVisualPCDFileDlg

[DLG:IDD_TRANS]
Type=1
Class=CVisualPCDTransDlg
ControlCount=0

[CLS:CVisualPCDTransDlg]
Type=0
HeaderFile=VisualPCDTransDlg.h
ImplementationFile=VisualPCDTransDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CVisualPCDTransDlg

[DLG:IDD_INPUT]
Type=1
Class=CVisualPCDInputDlg
ControlCount=2
Control1=IDC_EDIT_INPUT1,edit,1352732676
Control2=IDC_EDIT_INPUT2,edit,1352732676

[CLS:CVisualPCDInputDlg]
Type=0
HeaderFile=VisualPCDInputDlg.h
ImplementationFile=VisualPCDInputDlg.cpp
BaseClass=CBitmapDialog
Filter=D
LastObject=IDC_EDIT_INPUT1
VirtualFilter=dWC

[DLG:IDD_GRAPH]
Type=1
Class=CVisualPCDGraphDlg
ControlCount=1
Control1=IDC_GRAPH,static,1073741831

[CLS:CVisualPCDGraphDlg]
Type=0
HeaderFile=VisualPCDGraphDlg.h
ImplementationFile=VisualPCDGraphDlg.cpp
BaseClass=CBitmapDialog
Filter=M
VirtualFilter=dWC
LastObject=CVisualPCDGraphDlg

