; MarioISN Windows installer.
;
; Built in CI (see .github/workflows/build.yml) via:
;   makensis /DVERSION=<x.y.z> /DPAYLOAD_DIR=<absolute path to build-win/Release> \
;            /DICON_PATH=<absolute path to mario_isn.ico> installer.nsi
;
; Installs per-user (no admin elevation, no UAC prompt -- appropriate for
; unsigned freeware) into %LOCALAPPDATA%\MarioISN, with Start Menu/Desktop
; shortcuts and a proper uninstaller.

!ifndef VERSION
  !define VERSION "0.0.0"
!endif
!ifndef PAYLOAD_DIR
  !define PAYLOAD_DIR "..\..\build-win\Release"
!endif
; Passed as an absolute path from CI (see build.yml) rather than a bare
; relative filename resolved against this script's own directory --
; makensis resolves relative File/Icon paths against the *invoking* working
; directory (repo root in CI), not the .nsi's location, which is an easy
; way to point at a file that doesn't exist from there.
!ifndef ICON_PATH
  !define ICON_PATH "mario_isn.ico"
!endif
; Same reasoning as ICON_PATH above: an OutFile without a directory
; component is written relative to makensis's compile-time behaviour for
; unqualified paths, which does not reliably match the repo-root path the
; workflow's "Upload artifact (Windows)" step expects -- it previously
; caused the installer to go missing from the artifact/release entirely
; (silent "no files found" warning from upload-artifact, not a build
; failure). Passed as an absolute path from CI, like PAYLOAD_DIR/ICON_PATH.
!ifndef OUTFILE
  !define OUTFILE "MarioISN-windows-setup.exe"
!endif

; MUI_ICON/MUI_UNICON are read by MUI2.nsh's own top-level code when it's
; !include'd, so they must be defined before that -- not just before the
; page macros that come later.
!define MUI_ICON "${ICON_PATH}"
!define MUI_UNICON "${ICON_PATH}"

!include "MUI2.nsh"

Name "MarioISN"
OutFile "${OUTFILE}"
InstallDir "$LOCALAPPDATA\MarioISN"
RequestExecutionLevel user
Unicode true

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
