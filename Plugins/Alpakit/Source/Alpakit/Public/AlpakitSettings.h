#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Editor/DetailCustomizations/Public/DetailCustomizations.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"
#include "DetailLayoutBuilder.h"
#include "AlpakitSettings.generated.h"

USTRUCT()
struct FAlpakitMod
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, config)
	FString Name;

	UPROPERTY(EditAnywhere, config)
	TArray<FString> OverwritePaths;
};

UCLASS(config = Game)
class UAlpakitSettings : public UObject
{
	GENERATED_BODY()

public:
	UAlpakitSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, config, Category = Config)
	FDirectoryPath SatisfactoryGamePath;
	
	UPROPERTY(EditAnywhere, config, Category = Mods)
	TArray<FAlpakitMod> Mods;

	UPROPERTY(EditAnywhere, config, Category = Config)
	bool StartGame;

	UPROPERTY(EditAnywhere, config, Category = Config)
	bool CopyModsToGame;

};