;NSIS Modern User Interface
;Start Menu Folder Selection Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI
  !include "MUI2.nsh"
  !addplugindir "nsis_plugins"
;--------------------------------
;General
  !define MUI_WELCOMEPAGE_TEXT "GDP Bondarenko Bogdan$\r$\nGame made for AI class$\r$\nMenu made for configuration project 1$\r$\nInstaller made for configuration project 2."
  ;!insertmacro MUI_PAGE_LICENSE "1.txt"
  ;Name and file
  Name "X-Wing"
  OutFile "X-Wing_Installer.exe"

  ;Default installation folder
  InstallDir "C:\cnd\BondarenkoBogdan\x-wing"
  
  ;Get installation folder from registry if available
  ;InstallDirRegKey HKCU "Software\Modern UI Test" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

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
  
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "SOFTWARE\INFO6025\BONDARENKOBOGDAN" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "x-wing"
  
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section
  InitPluginsDir
  SetOutpath "$PLUGINSDIR"
    File "Project.zip"
  SetOutpath "$INSTDIR"
    nsisunz::UnzipToLog "$PLUGINSDIR\Project.zip" "$INSTDIR"
	RMDir /r "$INSTDIR\extra_assets"
    Pop $0
SectionEnd


Section "Game files(required)" SecGameFiles
	SectionIn RO

  SetOutPath "$INSTDIR"

  
  ;Store installation folder
  SetRegView 64
  WriteRegStr HKLM "SOFTWARE\INFO6025\BONDARENKOBOGDAN" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
	CreateShortcut "$SMPROGRAMS\$StartMenuFolder\x-wing.lnk" "$INSTDIR\GameEngine.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd

Section /o "Additional files" SecModules
  SetOutPath "$INSTDIR"
  nsisunz::UnzipToLog /file "extra_assets\dummy1.png" "$PLUGINSDIR\Project.zip" "$INSTDIR"
  nsisunz::UnzipToLog /file "extra_assets\dummy2.png" "$PLUGINSDIR\Project.zip" "$INSTDIR"
  nsisunz::UnzipToLog /file "extra_assets\dummy3.png" "$PLUGINSDIR\Project.zip" "$INSTDIR"
  nsisunz::UnzipToLog /file "extra_assets\dummy4.png" "$PLUGINSDIR\Project.zip" "$INSTDIR"
  nsisunz::UnzipToLog /file "extra_assets\dummy5.png" "$PLUGINSDIR\Project.zip" "$INSTDIR"
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
  RMDir /r "$INSTDIR\extra_assets"
  Delete "$INSTDIR\GameEngine.exe"
  Delete "$INSTDIR\freetype271MT.dll"
  Delete "$INSTDIR\Uninstall.exe"

  ;Will work Only if $INSTDIR is completely empty
  RMDir "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\x-wing.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  SetRegView 64
  DeleteRegKey HKLM "SOFTWARE\INFO6025"

SectionEnd