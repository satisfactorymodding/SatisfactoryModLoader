//#include <stdafx.h>
#include <windows.h>
#include <stdio.h>
#include "../Loader/Loader.h"
HINSTANCE mHinst = 0, mHinstDLL = 0;
extern "C" UINT_PTR mProcs[12] = { 0 };

void load_original_dll();

static bool hooked = false;

LPCSTR mImportNames[] = { "DllMain", "XInputEnable", "XInputGetBatteryInformation", "XInputGetCapabilities", "XInputGetDSoundAudioDeviceGuids", "XInputGetKeystroke", "XInputGetState", "XInputSetState", (LPCSTR)100, (LPCSTR)101, (LPCSTR)102, (LPCSTR)103 };
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	mHinst = hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH) {
		load_original_dll();
		for (int i = 0; i < 12; i++) {
			mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
		}
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		FreeLibrary(mHinstDLL);
	}

	if (hooked) {
		return (TRUE);
	}
	if (fdwReason == DLL_THREAD_ATTACH) {
		hooked = true;
		Loader::LoadModLoader();
	}
	return (TRUE);
}

extern "C" void DllMain_wrapper();
extern "C" void XInputEnable_wrapper();
extern "C" void XInputGetBatteryInformation_wrapper();
extern "C" void XInputGetCapabilities_wrapper();
extern "C" void XInputGetDSoundAudioDeviceGuids_wrapper();
extern "C" void XInputGetKeystroke_wrapper();
extern "C" void XInputGetState_wrapper();
extern "C" void XInputSetState_wrapper();
extern "C" void ExportByOrdinal100();
extern "C" void ExportByOrdinal101();
extern "C" void ExportByOrdinal102();
extern "C" void ExportByOrdinal103();


// Loads the original DLL from the default system directory
//	Function originally written by Michael Koch
void load_original_dll()
{
	char buffer[MAX_PATH];

	// Get path to system dir and to xinput1_3.dll
	GetSystemDirectoryA(buffer, MAX_PATH);

	// Append DLL name
	strcat_s(buffer, "\\xinput1_3.dll");

	// Try to load the system's xinput1_3.dll, if pointer empty
	if (!mHinstDLL) {
		mHinstDLL = LoadLibraryA(buffer);
	}

	// Debug
	if (!mHinstDLL) {
		OutputDebugStringA("PROXYDLL: Original xinput1_3.dll not loaded ERROR ****\r\n");
		ExitProcess(0); // Exit the hard way
	}
}

