#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameMapRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameMapRegistry, All, All);

USTRUCT(BlueprintType)
struct SML_API FSMLGameMapStartingLocationData {
	GENERATED_BODY()
public:
	/** Name of the starting location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Location Data")
	FText DisplayName;

	/** Description of the starting location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Location Data")
	FText Description;

	/** Difficulty of the starting location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Location Data")
	FText Difficulty;
	
	/** Icon of the starting location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Location Data")
	UTexture2D* LocationIcon;

	/** PlayerStart tag associated with this starting location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Location Data")
	FName PlayerStartTag;
};

UCLASS(NotBlueprintable, BlueprintType)
class SML_API USMLGameMapData : public UDataAsset {
	GENERATED_BODY()
public:
	/** Map asset that we want to register */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Map Data")
	TSoftObjectPtr<UWorld> MapAsset;

	/** Localized name of the map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Map Data")
	FText MapName;

	/** Localized description of the map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Map Data")
	FText MapDescription;

	/** Icon of the map to show in the map picker */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Map Data")
	UTexture2D* MapIcon;

	/** Starting locations */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Map Data")
	TArray<FSMLGameMapStartingLocationData> StartingLocations;
};

USTRUCT(BlueprintType)
struct SML_API FSMLGameMapRegistryEntry {
	GENERATED_BODY()

	/** Name of the owning plugin */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Map Registry Entry")
	FString OwningPluginName;

	/** Registered map data */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Map Registry Entry")
	USMLGameMapData* MapData;
};

UCLASS()
class SML_API USMLGameMapRegistry : public UGameInstanceSubsystem {
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = "Game Map Data Registry")
	TArray<FSMLGameMapRegistryEntry> RegisteredMaps;
public:
	UFUNCTION(BlueprintCallable, Category = "Game Map Data Registry")
	void RegisterGameMap(const FString& PluginName, USMLGameMapData* MapData);

	UFUNCTION(BlueprintCallable, Category = "Game Map Data Registry")
	void UnregisterGameMap(USMLGameMapData* MapData);

	UFUNCTION(BlueprintPure, Category = "Game Map Data Registry")
	TArray<FSMLGameMapRegistryEntry> GetGameMaps() const;
};
