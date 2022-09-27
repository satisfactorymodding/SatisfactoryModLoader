WHERE cargo >nul 2>nul
IF %ERRORLEVEL% EQU 0 (
	cargo build --release 2>&1
	copy target\release\ModdingCrashReporter.exe ..\Resources
)
