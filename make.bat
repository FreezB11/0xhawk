@echo off
REM Check if MinGW is installed
where g++ >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo MinGW g++ compiler not found in PATH.
    echo Please install MinGW and add it to your PATH.
    exit /b 1
)

REM Compile the provided .cc file
@echo "🚧 Building..."
g++ -o "builds/main" main.cc src/*.cc

if %ERRORLEVEL% neq 0 (
    echo Compilation failed.
    exit /b 1
)

echo Compilation successful.
exit /b 0