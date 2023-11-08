#pragma once
#include "AlpakitSettings.h"

struct FAlpakitProfileGameInfo {
	FAlpakitProfileGameInfo(): bCopyToGame(false), StartGameType(EAlpakitStartGameType::NONE) {}
	FAlpakitProfileGameInfo(bool bInCopyToGame, FString InGamePath, EAlpakitStartGameType InStartGameType):
		bCopyToGame(bInCopyToGame), GamePath(InGamePath), StartGameType(InStartGameType) {}
	
	bool bCopyToGame;
	FString GamePath;
	EAlpakitStartGameType StartGameType;
};

struct FAlpakitProfile {
	explicit FAlpakitProfile(FString InPluginName): BuildConfiguration(EBuildConfiguration::Shipping), PluginName(InPluginName) {}
	
	bool bBuild{false};
	EBuildConfiguration BuildConfiguration;
	TArray<FString> CookedPlatforms;
	FString PluginName;
	TMap<FString, FAlpakitProfileGameInfo> PlatformGameInfo;

	FString MakeUATCommandLine();
private:
	FString MakeUATPlatformArgs();
};
