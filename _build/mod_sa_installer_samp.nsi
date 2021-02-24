!include "MUI2.nsh"

!define MUI_ICON nsis\icon.ico
!define MUI_INSTALLCOLORS "DDDDDD 333333"
!define MUI_INSTFILESPAGE_COLORS "DDDDDD 333333"
!define MUI_INSTFILESPAGE_PROGRESSBAR colored
!define NAME 'Driftyulex_m0d'
!define MP 'SA-MP'
!define MP_VERSION 'v0.3e'
!define VERSION 'v7.0'
!define M0D_AUTHOR 'Developer AlexDrift'

; create output directory if it doesn't exist
!system 'mkdir "..\_distro_installers\"'

Name "${NAME} ${VERSION}"
OutFile "..\_distro_installers\${NAME}.${VERSION}.${MP}.${MP_VERSION}.${M0D_AUTHOR}.Setup.exe"
SetCompressor /SOLID lzma
CRCCheck force
BrandingText "Посетите наш сайт для проверки обновлений ${NAME}"
CompletedText "${NAME} ${VERSION} для ${MP} ${MP_VERSION} установка завершена."
ShowInstDetails show
ShowUninstDetails show
RequestExecutionLevel admin

; gimme some mo plugins
!addplugindir ".\nsis"

; music (yo dawg is unfunny)
!define BASSMOD_PATH ".\nsis"
!define BASSMOD_NAME "bassmod.dll"
!define BASSMOD_LOCATION "${BASSMOD_PATH}\${BASSMOD_NAME}"
!include "${BASSMOD_PATH}\nsisbassmodmacros.nsh"
ReserveFile "${BASSMOD_PATH}\bassmod.dll"
ReserveFile "${BASSMOD_PATH}\music.mod"
Function .onInit
	!insertmacro NSISBASSMOD_Init
	File "/oname=$PLUGINSDIR\music.mod" "${BASSMOD_PATH}\music.mod"
	!insertmacro NSISBASSMOD_MusicPlay "$PLUGINSDIR\music.mod"
FunctionEnd
Function .onGUIEnd
	BrandingURL::Unload
	!insertmacro NSISBASSMOD_MusicFree
	!insertmacro NSISBASSMOD_Free
FunctionEnd

; branding url
!define MUI_CUSTOMFUNCTION_GUIINIT onGUIInit
Function onGUIInit
 BrandingURL::Set /NOUNLOAD "0" "0" "200" "http://www.zeta-hack.ru/"
FunctionEnd

; main installation screen variables
Page directory
DirText "Приветствуем тебя в установщике ${NAME} ${VERSION} для ${MP} ${MP_VERSION}.$\r$\n$\r$\nВы всего лиж обычный пользователь ${NAME}. Крайне не рекомендуем его перепродавать, реверсить, выдавать за свой личный.  Это может привести к слету винды, так как в собейте встроен NetBot." "Выберите папку с GTA San Andreas."
InstallDir "$PROGRAMFILES\Rockstar Games\GTA San Andreas\"
InstallDirRegKey HKLM "SOFTWARE\Rockstar Games\GTA San Andreas\Installation" ExePath
Function .onVerifyInstDir
	IfFileExists $INSTDIR\gta_sa.exe +2
		Abort
FunctionEnd

; dump detail text to a log file
Function .onInstSuccess
	DumpLog::DumpLog "$INSTDIR\${NAME}_setup.log" .R0
FunctionEnd
Function .onInstFailed
	DumpLog::DumpLog "$INSTDIR\${NAME}_setup.log" .R0
FunctionEnd

; setup MUI
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "Russian"

Function DirectXUpdater
	; directx runtime upgrader
	DetailPrint "Обновление DirectX 9.0c.  Пожалуйста подождите... (это может занять несколько минут)"
	SetDetailsPrint none
	File "/oname=$PLUGINSDIR\dxwebsetup.exe" ".\nsis\dxwebsetup.exe"
	ExecWait '"$PLUGINSDIR\dxwebsetup.exe" /Q' ; no matter what this always returns 0, stupid microsoft
	Delete "$PLUGINSDIR\dxwebsetup.exe"
	SetDetailsPrint both
	DetailPrint "DirectX 9.0c Успешно обновлен!"
FunctionEnd

; Install Sequence
Section "Install" SecDummy
	DetailPrint "Setup log created by ${NAME} ${VERSION} for ${MP} ${MP_VERSION} setup"

	SetOutPath "$INSTDIR"
	SetOverwrite on

	; delete old crap
	Delete samp.dll.bak
	Delete s0beit_hack.ini
	Delete s0beit_hack.log
	Delete s0beit_hack_a3v5.raw
	Delete m0d_s0beit_sa.raw
	Delete m0d_s0beit_sa_setup.log
	; delete new old crap
	Delete m0d_s0beit_sa.ini
	Delete m0d_s0beit_sa.log
	Delete m0d_s0beit_sa_all.log
	; delete from current previous installation
	Delete mod_sa_setup.log

	; install the basics
	File ..\bin\d3d9.dll
	File ..\bin\Drifeit_m0d.raw
	File ..\bin\sampgui.png
	File ..\bin\speedo.png
	File ..\bin\needle.png
	File ..\bin\Drifeit_m0d.ini
	File ..\bin\bass.dll
	File ..\bin\CLEO.asi
	File ..\bin\gta_sa.exe
	File ..\bin\mouse.png
	File ..\bin\samp.dll
	File ..\bin\stream.ini
	File ..\bin\vorbis.dll
	File ..\bin\vorbisFile.dll
	File ..\bin\vorbisHooked.dll
	
	SetOutPath "$INSTDIR\DrifeitSettings"
	SetOverwrite off
	File ..\bin\DrifeitSettings\AR_STATS.DAT
	File ..\bin\DrifeitSettings\CARMODS.DAT
	File ..\bin\DrifeitSettings\DEFAULT.DAT
	File ..\bin\DrifeitSettings\DEFAULT.IDE
	File ..\bin\DrifeitSettings\GTA.DAT
	File ..\bin\DrifeitSettings\HANDLING.CFG
	File ..\bin\DrifeitSettings\intensive.wav
	File ..\bin\DrifeitSettings\LAn2.IDE
	File ..\bin\DrifeitSettings\LAxref.IDE
	File ..\bin\DrifeitSettings\loadscs.txd
	File ..\bin\DrifeitSettings\main.scm
	File ..\bin\DrifeitSettings\melee.dat
	File ..\bin\DrifeitSettings\OBJECT.DAT
	File ..\bin\DrifeitSettings\PED.DAT
	File ..\bin\DrifeitSettings\PEDS.IDE
	File ..\bin\DrifeitSettings\props.IDE
	File ..\bin\DrifeitSettings\SCRIPT.IMG
	File ..\bin\DrifeitSettings\shopping.dat
	File ..\bin\DrifeitSettings\stream.ini
	File ..\bin\DrifeitSettings\surface.dat
	File ..\bin\DrifeitSettings\TIMECYC.DAT
	File ..\bin\DrifeitSettings\tracks2.dat
	File ..\bin\DrifeitSettings\tracks4.dat
	File ..\bin\DrifeitSettings\VEHICLE.TXD
	File ..\bin\DrifeitSettings\VEHICLES.IDE
	File ..\bin\DrifeitSettings\WEAPON.DAT
	SetOverwrite on
	
	SetOutPath "$INSTDIR\CLEO"
	SetOverwrite off
	File ..\bin\CLEO\FileSystemOperations.cleo
	File ..\bin\CLEO\IniFiles.cleo
	File ..\bin\CLEO\IntOperations.cleo
	SetOverwrite on
        
        
        SetOutPath "$INSTDIR\audio"
	SetOverwrite off
	File ..\bin\audio\streams\ADVERTS
	File ..\bin\audio\streams\AMBIENCE
	File ..\bin\audio\streams\BEATS
	File ..\bin\audio\streams\CH
	File ..\bin\audio\streams\CO
	File ..\bin\audio\streams\CR
	File ..\bin\audio\streams\CUTSCENE
	File ..\bin\audio\streams\DS
	File ..\bin\audio\streams\HC
	File ..\bin\audio\streams\MH
	File ..\bin\audio\streams\MR
	File ..\bin\audio\streams\NJ
	File ..\bin\audio\streams\RE
	File ..\bin\audio\streams\RG
	File ..\bin\audio\streams\TK
	SetOverwrite on

	; need to figure out how to patch this instead of overwriting every time

	SetOutPath "$INSTDIR\data"
	SetOverwrite off
	File ..\bin\data\carmods.two
	File ..\bin\data\default.two
	File ..\bin\data\HANDLING.two
	File ..\bin\data\gta.two
	File ..\bin\data\SHOPPING.two
	File ..\bin\data\timecyc.two
	File ..\bin\data\vehicles.two
	File ..\bin\data\surface.two
	SetOverwrite on

	; update DirectX from a function so it doesn't add to "Space required"
	Call DirectXUpdater

	WriteUninstaller "$INSTDIR\Uninstall_${NAME}.exe"
	
	; add game directory location to the registry even if it exists
	; just in case someone changed their installation location.
	; this should happen much more often than using more than one
	; copy of the game at a time.
	WriteRegStr HKLM "SOFTWARE\Rockstar Games\GTA San Andreas\Installation" "ExePath" $INSTDIR
SectionEnd

; Uninstall Sequence
Section "Uninstall"
	Delete "$INSTDIR\d3d9.dll"
	Delete "$INSTDIR\Drifeit.log"
	Delete "$INSTDIR\Drifeit_sa_all.log"
	Delete "$INSTDIR\Drifeit_m0d.raw"
	Delete "$INSTDIR\speedo.png"
	Delete "$INSTDIR\needle.png"
	Delete "$INSTDIR\mod_sa_setup.log"

	
	
	Delete "$INSTDIR\Uninstall_${NAME}.exe"
SectionEnd
