#pragma once

#include "Interfaces/IPluginManager.h"

struct FModTargetsConfig
{
public:
	FModTargetsConfig() {}
	FModTargetsConfig(TSharedRef<IPlugin> InMod);

	void Save();
	TArray<FString> GetCookedPlatforms();

	bool bWindows = false;
	bool bWindowsServer = false;
	bool bLinuxServer = false;
private:
	TSharedPtr<IPlugin> Mod;

	FConfigFile ConfigFile;

	FString GetConfigPath() const;
};
