#ifndef XINPUT1_3_EXPORTS_H
#define XINPUT1_3_EXPORTS_H

#include <string>

typedef __int64(__stdcall *FUNCTION_PTR)();
typedef void* HLOADEDMODULE;
typedef HLOADEDMODULE(*LoadModuleFunc)(const wchar_t* filePath);
typedef FUNCTION_PTR(*GetModuleProcAddress)(HLOADEDMODULE module, const char* symbolName);
typedef bool(*IsLoaderModuleLoaded)(const char* moduleName);

struct BootstrapAccessors {
	const wchar_t* gameRootDirectory;
	LoadModuleFunc LoadModule;
	GetModuleProcAddress GetModuleProcAddress;
	IsLoaderModuleLoaded IsLoaderModuleLoaded;
};

typedef void(*BootstrapModuleFunc)(BootstrapAccessors& accessors);

#endif //XINPUT1_3_EXPORTS_H
