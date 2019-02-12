;NSIS Modern User Interface
;Start Menu Folder Selection Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"
 ; !include "zipdll.nsh"
;--------------------------------
;General
  !define MUI_WELCOMEPAGE_TEXT "Game made for AI class$\r$\nMenu made for configuration project 1$\r$\nInstaller made for configuration project."
  ;!insertmacro MUI_PAGE_LICENSE "1.txt"
  ;Name and file
  Name "X-Wing"
  OutFile "X-Wing_Installer.exe"

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\Modern UI Test"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\Modern UI Test" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Variables

  Var StartMenuFolder

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages
  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "license.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  
  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Modern UI Test" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Game files(required)" SecGameFiles
	SectionIn RO

  SetOutPath "$INSTDIR"

  ;File /r "Project\*"
  
  ;Store installation folder
  WriteRegStr HKCU "Software\Modern UI Test" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd

Section /o "Additional files" SecModules
  SetOutPath "$INSTDIR"
  CreateDirectory $INSTDIR\modules
SectionEnd
;--------------------------------
;Descriptions

  ;Language strings
  LangString descSecModules ${LANG_ENGLISH} "A test section."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecModules} $(descSecModules)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;For safety reasons specifying all folders and files in $INSTDIR
  RMDir /r "$INSTDIR\assets"
  RMDir /r "$INSTDIR\config"
  RMDir /r "$INSTDIR\localization"
  RMDir /r  "$INSTDIR\scenes"
  Delete "$INSTDIR\GameEngine.exe"
  Delete "$INSTDIR\freetype271MT.dll"
  Delete "$INSTDIR\Uninstall.exe"

  ;Will work Only if $INSTDIR is completely empty
  RMDir "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  
  DeleteRegKey /ifempty HKCU "Software\Modern UI Test"

SectionEnd