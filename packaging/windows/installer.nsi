; MarioISN Windows installer.
;
; Built in CI (see .github/workflows/build.yml) via:
;   makensis /DVERSION=<x.y.z> /DPAYLOAD_DIR=<absolute path to build-win/Release> installer.nsi
;
; Installs per-user (no admin elevation, no UAC prompt -- appropriate for
; unsigned freeware) into %LOCALAPPDATA%\MarioISN, with Start Menu/Desktop
; shortcuts and a proper uninstaller.

!include "MUI2.nsh"

!ifndef VERSION
  !define VERSION "0.0.0"
!endif
!ifndef PAYLOAD_DIR
  !define PAYLOAD_DIR "..\..\build-win\Release"
!endif

Name "MarioISN"
OutFile "MarioISN-windows-setup.exe"
InstallDir "$LOCALAPPDATA\MarioISN"
RequestExecutionLevel user
Unicode true
!define MUI_ICON "mario_isn.ico"
!define MUI_UNICON "mario_isn.ico"

!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

VIProductVersion "${VERSION}.0"
VIAddVersionKey "ProductName" "MarioISN"
VIAddVersionKey "ProductVersion" "${VERSION}"
VIAddVersionKey "FileVersion" "${VERSION}"
VIAddVersionKey "LegalCopyright" "MarioISN contributors"

!define UNINSTALL_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\MarioISN"

Section "Install"
  SetOutPath "$INSTDIR"
  File /r "${PAYLOAD_DIR}\*.*"

  CreateDirectory "$SMPROGRAMS\MarioISN"
  CreateShortcut "$SMPROGRAMS\MarioISN\MarioISN.lnk" "$INSTDIR\mario_isn.exe"
  CreateShortcut "$DESKTOP\MarioISN.lnk" "$INSTDIR\mario_isn.exe"

  WriteUninstaller "$INSTDIR\Uninstall.exe"
  CreateShortcut "$SMPROGRAMS\MarioISN\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

  WriteRegStr HKCU "${UNINSTALL_KEY}" "DisplayName" "MarioISN"
  WriteRegStr HKCU "${UNINSTALL_KEY}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKCU "${UNINSTALL_KEY}" "DisplayVersion" "${VERSION}"
  WriteRegStr HKCU "${UNINSTALL_KEY}" "InstallLocation" "$INSTDIR"
  WriteRegStr HKCU "${UNINSTALL_KEY}" "DisplayIcon" "$INSTDIR\mario_isn.exe"
  WriteRegDWORD HKCU "${UNINSTALL_KEY}" "NoModify" 1
  WriteRegDWORD HKCU "${UNINSTALL_KEY}" "NoRepair" 1
SectionEnd

Section "Uninstall"
  Delete "$SMPROGRAMS\MarioISN\MarioISN.lnk"
  Delete "$SMPROGRAMS\MarioISN\Uninstall.lnk"
  RMDir "$SMPROGRAMS\MarioISN"
  Delete "$DESKTOP\MarioISN.lnk"
  RMDir /r "$INSTDIR"
  DeleteRegKey HKCU "${UNINSTALL_KEY}"
SectionEnd
