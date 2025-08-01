@echo off
setlocal ENABLEEXTENSIONS

:: Default values
set "build_type=Release"
set "do_install=NO"

:: Colored output (simple)
:info
echo [INFO] %~1
goto :eof

:die
echo [ERROR] %~1
pause
exit /b 1

:: Argument parsing
if "%~1"=="" goto :continue
if /i "%~1"=="debug" (
    set "build_type=Debug"
) else if /i "%~1"=="clean" (
    if not exist out mkdir out
    rmdir /s /q out
    rmdir /s /q clopts
    goto :end
) else if /i "%~1"=="install" (
    set "do_install=YES"
) else (
    call :die "Unrecognised option '%~1'"
)

:continue

if not exist out mkdir out
cd out || call :die "cd error"

:: Run CMake
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=%build_type% ..

:: Run build
if "%do_install%"=="YES" (
    ninja && (
        echo Running install...
        :: Use elevated prompt for install if needed (or adjust based on your setup)
        :: For simplicity, no sudo in Windows
        ninja install
    )
) else (
    ninja
)

:end
echo.
pause
