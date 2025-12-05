@echo off
REM Build script (cmd) — compila todos los .c en output\main.exe
SET SCRIPT_DIR=%~dp0
IF NOT EXIST "%SCRIPT_DIR%output" (
    mkdir "%SCRIPT_DIR%output"
)

echo Compilando fuentes...
gcc -Wall -Wextra -g3 "%SCRIPT_DIR%*.c" -o "%SCRIPT_DIR%output\main.exe"
IF ERRORLEVEL 1 (
    echo Error de compilacion.
    EXIT /B 1
)

echo Compilacion exitosa: %SCRIPT_DIR%output\main.exe
EXIT /B 0
