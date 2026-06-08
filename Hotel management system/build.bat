@echo off
REM Smart Hotel Management System - Windows Build Script
REM Requires MinGW with g++ or equivalent C++ compiler

title Smart Hotel Management System - Build

echo.
echo ╔════════════════════════════════════════════════════╗
echo ║  Smart Hotel Management System - Windows Build     ║
echo ║  Northern Heights Hotel - Resort                   ║
echo ╚════════════════════════════════════════════════════╝
echo.

REM Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Error: g++ compiler not found!
    echo Please install MinGW or ensure g++ is in PATH
    echo Download from: https://www.mingw-w64.org/
    pause
    exit /b 1
)

echo ✓ Found g++ compiler
echo.

REM Get compiler version
echo Compiler Version:
g++ --version | findstr /R "."
echo.

REM Create bin directory
if not exist bin mkdir bin
echo ✓ Created 'bin' directory
echo.

REM Compile source files
echo Compiling source files...
echo =========================

setlocal enabledelayedexpansion
set COMPILE_FAILED=0

for %%f in (main.cpp Person.cpp Guest.cpp Employee.cpp Room.cpp Service.cpp Booking.cpp Bill.cpp Hotel.cpp) do (
    if exist %%f (
        echo   Compiling %%f...
        g++ -std=c++11 -c %%f -o bin\%%~nf.o 2>nul
        if !ERRORLEVEL! NEQ 0 (
            echo   ❌ Failed to compile %%f
            set COMPILE_FAILED=1
        ) else (
            echo   ✓ %%f compiled
        )
    ) else (
        echo   ✗ File %%f not found!
        set COMPILE_FAILED=1
    )
)

echo.

if !COMPILE_FAILED! EQU 1 (
    echo ❌ Compilation failed! Please check the errors above.
    pause
    exit /b 1
)

REM Link object files
echo Linking object files...
echo ======================

g++ bin\*.o -o bin\hotel_system.exe 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Linking failed!
    pause
    exit /b 1
) else (
    echo ✓ Linking successful
)

echo.
echo ╔════════════════════════════════════════════════════╗
echo ║  ✓ BUILD SUCCESSFUL!                              ║
echo ╚════════════════════════════════════════════════════╝
echo.
echo To run the application:
echo   bin\hotel_system.exe
echo.
echo To clean build files:
echo   del bin\*.o
echo   del bin\hotel_system.exe
echo.
echo Press any key to exit...
pause >nul
