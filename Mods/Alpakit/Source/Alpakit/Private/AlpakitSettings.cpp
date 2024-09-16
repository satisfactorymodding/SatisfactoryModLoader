#include "AlpakitSettings.h"

const TCHAR* LexToString(EAlpakitStartGameType StartGameType) {	
	switch (StartGameType) {
	case EAlpakitStartGameType::STEAM:
		return TEXT("Steam");
	case EAlpakitStartGameType::STEAM_SERVER:
		return TEXT("SteamDS");
	case EAlpakitStartGameType::EPIC_STABLE:
		return TEXT("EpicEA");
	case EAlpakitStartGameType::EPIC_EXPERIMENTAL:
		return TEXT("EpicExp");
	case EAlpakitStartGameType::EPIC_SERVER:
		return TEXT("EpicDS");
	case EAlpakitStartGameType::EPIC_SERVER_EXPERIMENTAL:
		return TEXT("EpicDSExp");
	case EAlpakitStartGameType::CUSTOM:
		return TEXT("Custom");
	default:
		return TEXT("");
	}
}

UAlpakitSettings* UAlpakitSettings::Get()
{
    return GetMutableDefault<UAlpakitSettings>();
}

void UAlpakitSettings::SaveSettings()
{
    SaveConfig();
}

TArray<FString> UAlpakitSettings::GetAllowedBuildConfigurations() const
{
	return TArray<FString>
	{
		// LexToString(EBuildConfiguration::Debug      ),
		// LexToString(EBuildConfiguration::DebugGame  ),
		// LexToString(EBuildConfiguration::Development),
		// LexToString(EBuildConfiguration::Test       ),
		LexToString(EBuildConfiguration::Shipping   ),
	};
}

EBuildConfiguration UAlpakitSettings::GetBuildConfiguration() const
{
	EBuildConfiguration ResultBuildConfiguration = EBuildConfiguration::Shipping;
	// LexTryParseString( ResultBuildConfiguration, *BuildConfiguration );
	return ResultBuildConfiguration;
}

const TMap<FString, FAlpakitTargetSettings> UAlpakitSettings::GetPlatformTargetSettings() const {
	return {
		        {TEXT("Windows"), WindowsGameTargetSettings},
				{TEXT("WindowsServer"), WindowsServerTargetSettings},
				{TEXT("LinuxServer"), LinuxServerTargetSettings},
			};
}
