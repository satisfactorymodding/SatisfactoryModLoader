#include "AlpakitSettings.h"

const TCHAR* LexToString(EAlpakitStartGameType StartGameType) {	
	switch (StartGameType) {
	case EAlpakitStartGameType::STEAM:
		return TEXT("Steam");
	case EAlpakitStartGameType::EPIC_EARLY_ACCESS:
		return TEXT("EpicEA");
	case EAlpakitStartGameType::EPIC_EXPERIMENTAL:
		return TEXT("EpicExp");
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
