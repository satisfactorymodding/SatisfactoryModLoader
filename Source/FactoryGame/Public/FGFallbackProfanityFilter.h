// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGFallbackProfanityFilter.generated.h"

UCLASS()
class FACTORYGAME_API UFGWordList : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FString> Words;
};

UCLASS( Config = "Game", DefaultConfig, meta = ( DisplayName = "Fallback Profanity Filter"))
class FACTORYGAME_API UFGFallbackProfanityFilterSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UFGWordList* GetWordList() const;

	const FRegexPattern& GetRegex() const;

	UPROPERTY( EditAnywhere, Config, Category = "Online" )
	TSoftObjectPtr< UFGWordList > mWordList;

	static const UFGFallbackProfanityFilterSettings& Get() { return *GetDefault<UFGFallbackProfanityFilterSettings>(); }
private:
	mutable TOptional<FRegexPattern> mRegex;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGFallbackProfanityFilter : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintCallable, Category = "Online", meta = (DisplayName = "Filter String (Fallback)"))
	static FString FilterString( const FString& UnfilteredString );

	UFUNCTION( BlueprintCallable, Category = "Online", meta = (DisplayName = "Filter Strings (Fallback)"))
	static TArray<FString> FilterStrings( const TArray<FString>& UnfilteredStrings );
};
