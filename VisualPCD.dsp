# Microsoft Developer Studio Project File - Name="VisualPCD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VisualPCD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisualPCD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisualPCD.mak" CFG="VisualPCD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisualPCD - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VisualPCD - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisualPCD - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wsock32.lib cximagecrtd.lib msimg32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VisualPCD - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib cximagecrt.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "VisualPCD - Win32 Release"
# Name "VisualPCD - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdvEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Arrow.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Enquirer.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\JRacerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\PCDControler.cpp
# End Source File
# Begin Source File

SOURCE=.\Policet.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleQuints.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Translator.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCD.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDAboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDGraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDInputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDResultDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPCDTransDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WndShadow.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLParser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdvEdit.h
# End Source File
# Begin Source File

SOURCE=.\Arrow.h
# End Source File
# Begin Source File

SOURCE=.\BitmapDialog.h
# End Source File
# Begin Source File

SOURCE=.\Enquirer.h
# End Source File
# Begin Source File

SOURCE=.\ErrorHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Lib\SonicUI_src\include\ISonicUI.h
# End Source File
# Begin Source File

SOURCE=.\JRacerInterface.h
# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=.\PCDControler.h
# End Source File
# Begin Source File

SOURCE=.\Policet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SampleQuints.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Translator.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCD.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDAboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDGraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDInputDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDResultDlg.h
# End Source File
# Begin Source File

SOURCE=.\VisualPCDTransDlg.h
# End Source File
# Begin Source File

SOURCE=.\WndShadow.h
# End Source File
# Begin Source File

SOURCE=.\XMLParser.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\button-click.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\button-hover.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\button.bmp
# End Source File
# Begin Source File

SOURCE=.\res\click.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VisualPCD.ico
# End Source File
# Begin Source File

SOURCE=.\VisualPCD.rc
# End Source File
# Begin Source File

SOURCE=.\res\VisualPCD.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
