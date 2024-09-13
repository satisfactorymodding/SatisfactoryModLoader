// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationTypes.h"
#include "SessionInformation.h"
#include "SessionCreationSettings.generated.h"

class USessionInformation;
class USessionCreationSettingInfo;
class USessionDefinition;
class ULocalUserInfo;

USTRUCT(BlueprintType)
struct ONLINEINTEGRATION_API FCommonSessionCreationSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category=Session)
	TObjectPtr<USessionDefinition> SessionDefinition;

	UPROPERTY(BlueprintReadWrite, Category=Session)
	FName SessionProfile = NAME_None;
	
	/** The map that will be loaded at the start of gameplay, this needs to be a valid long package name */
	UPROPERTY(BlueprintReadWrite, Category=Session, meta=(AllowedTypes="World"))
	FTopLevelAssetPath MapID;

	/** Extra arguments passed as URL options to the game */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	TMap<FString, FString> ExtraArgs;

	/** Maximum players allowed per gameplay session */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	int32 MaxPlayerCount = 16;
	
	UPROPERTY(BlueprintReadWrite, Category=Session)
	TObjectPtr<ULocalUserInfo> Host = nullptr;

	UPROPERTY(BlueprintReadWrite, Category=Session)
	TArray<FCustomOnlineSessionSetting> CustomSessionSettings;
	
	/** Returns the full map name that will be used during gameplay */
	FString GetMapName() const;
	/** Constructs the full URL that will be passed to ServerTravel */
	FString ConstructTravelURL(TMap<FString, FString> AdditionalOptions) const;

	bool operator==(const FCommonSessionCreationSettings& Other) const
	{
		return SessionDefinition == Other.SessionDefinition && SessionProfile == Other.SessionProfile && MapID == Other.MapID &&
			   ExtraArgs.OrderIndependentCompareEqual(Other.ExtraArgs) && MaxPlayerCount == Other.MaxPlayerCount && Host == Other.Host; 
	}
};

USTRUCT()
struct ONLINEINTEGRATION_API FSessionJoinParams
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<APlayerController> Player;
	
	UPROPERTY()
	TObjectPtr<USessionInformation> OnlineSession;

	UPROPERTY()
	FString RawAddress;
};