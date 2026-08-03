@echo off
title Área27 Sinuca - Build Firmware .bin
echo ========================================================
echo   Compilando Área27 Sinuca Firmware para ESP8266
echo ========================================================
echo.

where arduino-cli >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERRO] arduino-cli nao foi encontrado no PATH do sistema.
    echo Baixe o arduino-cli ou use na Arduino IDE: Sketch -> Exportar Binario Compilado.
    echo.
    pause
    exit /b 1
)

echo [1/3] Atualizando índice do ESP8266...
arduino-cli core update-index --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json

echo.
echo [2/3] Compilando sketch Area27_Sinuca.ino...
arduino-cli compile --fqbn esp8266:esp8266:generic --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json --output-dir . Area27_Sinuca.ino

if %errorlevel% equ 0 (
    if exist "Area27_Sinuca.ino.bin" (
        copy /y "Area27_Sinuca.ino.bin" "firmware.bin" >nul
    )
    echo.
    echo ========================================================
    echo  [SUCESSO] firmware.bin gerado com sucesso!
    echo  Pronto para subir no GitHub para Auto-Update.
    echo ========================================================
) else (
    echo.
    echo [ERRO] Falha na compilacao do firmware.
)

pause
