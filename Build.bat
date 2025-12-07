@echo off
rem **********************************************
rem * File        :Build.bat
rem * Description :call CMAKE in bat
rem **********************************************

rem ********************Var Init******************
set PRO_ROOT=%~dp0
set CMAKE_ROOT=%PRO_ROOT%TOOLS/CMAKE

echo ***** Build Configure *****
if "%*"=="" (
    cd %CMAKE_ROOT%
	CMAKE --list-presets
    echo Please select a build configure, call like .\Build.bat none-rel-ads
	echo If you want to perform preburn, call like .\Build.bat none-re1-adS -DBUILD PREBURN_VERSION V2:B00L-TRUE
    goto END
)

echo * BUILD_CONFIG:   %*
echo * Project Root:   %PRO_ROOT%
echo * CMAKE Root :    %CMAKE_ROOT%

echo ***** Set ADS time stamp to green it *****
rem Get time stamp and sub 8 hours, and sub most significant bit due to cmd's data length limit, latter we will xoR it mannually.
for /f %%x in ('powershell -command "(Get-Date -UFormat %%s) - 1610641536"') do set timestamp=%%x
for /f "tokens=1 delims=." %%a in ("%timestamp%") do set "integer_part==%%a"
set /a "number=integer_part"

rem Remove XOR parameter's most significant bit.
set /a "XOR=57328953"
set /a "XORNumber=number^XOR"

rem Turn it into hex format string.
set hex_number=
for /f "tokens=*" %%a in ('powershell -command "[Convert]::ToString(%XORNumber%,16)"') do set "hex_number=%%a"
set timestamp_str=c%hex_number%
set TASKING_RUN_STAMP=%timestamp_str%
echo TASKING_RUN_STAMP  =%TASKING_RUN_STAMP%

echo ***** Start Build *****
cd %CMAKE_ROOT%
cmake --preset %*
cmake --build --preset %*

:END
echo ***** End Build *****
cd %PRO_ROOT%