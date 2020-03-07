#ifndef XINPUT1_3_EXPORTS_H
#define XINPUT1_3_EXPORTS_H

typedef __int64(__stdcall *FUNCTION_PTR)();
typedef void* HLOADEDMODULE;
typedef HLOADEDMODULE(*LoadModuleFunc)(const char* unusedShouldBeEmptyString, const wchar_t* filePath);
typedef FUNCTION_PTR(*GetModuleProcAddress)(HLOADEDMODULE module, const char* symbolName);
typedef bool(*IsLoaderModuleLoaded)(const char* moduleName);
typedef FUNCTION_PTR(*ResolveGameSymbolPtr)(const char* symbolName);
typedef void(*FlushDebugSymbolsFunc)();

struct BootstrapAccessors {
	const wchar_t* gameRootDirectory;
	LoadModuleFunc LoadModule;
	GetModuleProcAddress GetModuleProcAddress;
	IsLoaderModuleLoaded IsLoaderModuleLoaded;
	ResolveGameSymbolPtr ResolveGameSymbol;
	const wchar_t* version;
	FlushDebugSymbolsFunc FlushDebugSymbols;
};

typedef void(*BootstrapModuleFunc)(BootstrapAccessors& accessors);
typedef const char*(*GetLinkageModuleNameFunc)();

#endif //XINPUT1_3_EXPORTS_H
