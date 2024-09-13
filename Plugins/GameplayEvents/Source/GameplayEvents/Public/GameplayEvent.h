// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/Variant.h"

#include "GameplayEvent.generated.h"

USTRUCT(BlueprintType)
struct FGameplayEvent
{
	GENERATED_BODY()

	FGameplayEvent() = default;
	FGameplayEvent(const FGameplayEvent&) = default;
	FGameplayEvent(FGameplayEvent&&) = default;
	
	FGameplayEvent(const FGameplayTag& Tag, const TArray<APlayerController*>& InInstigators)
	: EventTag(Tag)
	, Instigators(InInstigators) {}

	FGameplayEvent(const FGameplayTag& Tag, const TArray<APlayerController*>& InInstigators, int32 IntPayload)
		: FGameplayEvent(Tag, InInstigators)
	{
		Payload = IntPayload;
	}

	FGameplayEvent(const FGameplayTag& Tag, const TArray<APlayerController*>& InInstigators, const FString& StringPayload)
	: FGameplayEvent(Tag, InInstigators)
	{
		Payload = StringPayload;
	}

	FGameplayEvent& operator=(const FGameplayEvent&) = default;
	FGameplayEvent& operator=(FGameplayEvent&&) = default;
	
	/**
	 * A tag that uniquely identifies an event
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag EventTag;

	/**
	 * The players that caused, or instigated, this event
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<APlayerController>> Instigators;

	FVariant Payload;
};

UCLASS()
class GAMEPLAYEVENTS_API UGameplayEventsBlueprintLibrary: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static bool GetGameplayEventIntPayload(const FGameplayEvent& GameplayEvent, int32 &OutIntPayload);

	UFUNCTION(BlueprintPure)
	static bool GetGameplayEventStringPayload(const FGameplayEvent& GameplayEvent, FString &OutStringPayload);
	
	UFUNCTION(BlueprintPure)
	static FGameplayEvent MakeIntGameplayEvent(FGameplayTag EventTag, const TArray<APlayerController*>& InInstigators, int32 IntPayload);

	UFUNCTION(BlueprintPure)
	static FGameplayEvent MakeStringGameplayEvent(FGameplayTag EventTag, const TArray<APlayerController*>& InInstigators, const FString& StringPayload);
};