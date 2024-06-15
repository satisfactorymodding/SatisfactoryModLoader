#pragma once
#include "AlpakitSettings.h"

struct FAlpakitProfileGameInfo {
	FAlpakitProfileGameInfo() {}
	FAlpakitProfileGameInfo(bool bInCopyToGame, FDirectoryPath InGamePath, bool bInStartGame, EAlpakitStartGameType InStartGameType):
		bCopyToGame(bInCopyToGame), GamePath(InGamePath), bStartGame(bInStartGame), StartGameType(InStartGameType) {}
	
	bool bCopyToGame{false};
	FDirectoryPath GamePath;
	bool bStartGame{false};
	EAlpakitStartGameType StartGameType{};
	FString CustomLaunchPath;
	FString CustomLaunchArgs;
};

struct FAlpakitProfile {
	explicit FAlpakitProfile(FString InPluginName): BuildConfiguration(EBuildConfiguration::Shipping), PluginName(InPluginName) {}
	
	bool bBuild{false};
	EBuildConfiguration BuildConfiguration;
	TArray<FString> CookedPlatforms;
	FString PluginName;
	TMap<FString, FAlpakitProfileGameInfo> PlatformGameInfo;
	bool bMergeArchive{false};

	FString MakeUATCommandLine();
private:
	FString MakeUATPlatformArgs();
};
