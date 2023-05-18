#pragma once

#include "Interfaces/IPluginManager.h"

struct FModTargetsConfig
{
public:
	FModTargetsConfig() {}
	FModTargetsConfig(TSharedRef<IPlugin> InMod);

	void Save();

	bool bWindowsNoEditor;
	bool bWindowsServer;
	bool bLinuxServer;
private:
	TSharedPtr<IPlugin> Mod;

	FConfigFile ConfigFile;

	FString GetConfigPath() const;
};
