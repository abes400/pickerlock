############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "Pickerlock"
!define COMP_NAME "Flying Map Entertainment"
!define VERSION "01.00.00.00"
!define COPYRIGHT "Copyright (c) 2025-2026 Flying Map Entertainment"
!define DESCRIPTION "A simple lock picking game made for 20 Second Game Jam 2025."
!define LICENSE_TXT "..\..\..\LICENSE"
!define INSTALLER_NAME "..\..\..\dist\windows_x64\Install_Pickerlock_1.0.exe"
!define MAIN_APP_EXE "Pickerlock.exe"
!define INSTALL_TYPE "SetShellVarContext all"
!define REG_ROOT "HKLM"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor ZLIB
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\Flying Map Entertainment\Pickerlock"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!insertmacro MUI_PAGE_WELCOME

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Flying Map Entertainment"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

######################################################################

Section -MainProgram
${INSTALL_TYPE}
SetOverwrite ifnewer
SetOutPath "$INSTDIR"
File "..\..\..\dist\windows_x64\Pickerlock\Pickerlock.exe"
SetOutPath "$INSTDIR\texture"
File "..\..\..\dist\windows_x64\Pickerlock\texture\20sgj.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\arrow.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\bg.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\button.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\button_down.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\cards.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\checkbox.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\cursor.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\flymap.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\hand.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\icon.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\inst_vis.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\lock.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\logo.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\start.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\start_down.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\statbox.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\uibox.png"
File "..\..\..\dist\windows_x64\Pickerlock\texture\uibox2.png"
SetOutPath "$INSTDIR\font"
File "..\..\..\dist\windows_x64\Pickerlock\font\numfont.png"
File "..\..\..\dist\windows_x64\Pickerlock\font\uifont.png"
SetOutPath "$INSTDIR\audio"
File "..\..\..\dist\windows_x64\Pickerlock\audio\beep.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\buzzer.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\dial.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\gamebgm.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\grunt.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\menubgm.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\slam.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\unlock.wav"
File "..\..\..\dist\windows_x64\Pickerlock\audio\wohoo.wav"
SectionEnd

######################################################################

Section -Icons_Reg
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
CreateDirectory "$SMPROGRAMS\$SM_Folder"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!insertmacro MUI_STARTMENU_WRITE_END
!endif

!ifndef REG_START_MENU
CreateDirectory "$SMPROGRAMS\Flying Map Entertainment"
CreateShortCut "$SMPROGRAMS\Flying Map Entertainment\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\Flying Map Entertainment\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\Flying Map Entertainment\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!endif

WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

!ifdef WEB_SITE
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
!endif
SectionEnd

######################################################################

Section Uninstall
${INSTALL_TYPE}
Delete "$INSTDIR\Pickerlock.exe"
Delete "$INSTDIR\texture\20sgj.png"
Delete "$INSTDIR\texture\arrow.png"
Delete "$INSTDIR\texture\bg.png"
Delete "$INSTDIR\texture\button.png"
Delete "$INSTDIR\texture\button_down.png"
Delete "$INSTDIR\texture\cards.png"
Delete "$INSTDIR\texture\checkbox.png"
Delete "$INSTDIR\texture\cursor.png"
Delete "$INSTDIR\texture\flymap.png"
Delete "$INSTDIR\texture\hand.png"
Delete "$INSTDIR\texture\icon.png"
Delete "$INSTDIR\texture\inst_vis.png"
Delete "$INSTDIR\texture\lock.png"
Delete "$INSTDIR\texture\logo.png"
Delete "$INSTDIR\texture\start.png"
Delete "$INSTDIR\texture\start_down.png"
Delete "$INSTDIR\texture\statbox.png"
Delete "$INSTDIR\texture\uibox.png"
Delete "$INSTDIR\texture\uibox2.png"
Delete "$INSTDIR\font\numfont.png"
Delete "$INSTDIR\font\uifont.png"
Delete "$INSTDIR\audio\beep.wav"
Delete "$INSTDIR\audio\buzzer.wav"
Delete "$INSTDIR\audio\dial.wav"
Delete "$INSTDIR\audio\gamebgm.wav"
Delete "$INSTDIR\audio\grunt.wav"
Delete "$INSTDIR\audio\menubgm.wav"
Delete "$INSTDIR\audio\slam.wav"
Delete "$INSTDIR\audio\unlock.wav"
Delete "$INSTDIR\audio\wohoo.wav"
 
RmDir "$INSTDIR\audio"
RmDir "$INSTDIR\font"
RmDir "$INSTDIR\texture"
 
Delete "$INSTDIR\uninstall.exe"
!ifdef WEB_SITE
Delete "$INSTDIR\${APP_NAME} website.url"
!endif

RmDir "$INSTDIR"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\$SM_Folder"
!endif

!ifndef REG_START_MENU
Delete "$SMPROGRAMS\Flying Map Entertainment\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\Flying Map Entertainment\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\Flying Map Entertainment\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\Flying Map Entertainment"
!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

