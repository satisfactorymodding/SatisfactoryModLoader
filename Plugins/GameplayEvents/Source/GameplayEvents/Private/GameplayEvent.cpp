// Copyright Coffee Stain Studios. All Rights Reserved.

#include "GameplayEvent.h"

bool UGameplayEventsBlueprintLibrary::GetGameplayEventIntPayload(const FGameplayEvent& GameplayEvent, int32& OutIntPayload)
{
	if(GameplayEvent.Payload.GetType() == EVariantTypes::Int32)
	{
		OutIntPayload = GameplayEvent.Payload.GetValue<int32>();
		return true;
	}

	return false;
}

bool UGameplayEventsBlueprintLibrary::GetGameplayEventStringPayload(const FGameplayEvent& GameplayEvent, FString& OutStringPayload)
{
	if (GameplayEvent.Payload.GetType() == EVariantTypes::String)
	{
		OutStringPayload = GameplayEvent.Payload.GetValue<FString>();
		return true;
	}

	return false;
}

FGameplayEvent UGameplayEventsBlueprintLibrary::MakeIntGameplayEvent(FGameplayTag EventTag, const TArray<APlayerController*>& InInstigators, int32 IntPayload)
{
	return FGameplayEvent(EventTag, InInstigators, IntPayload);
}

FGameplayEvent UGameplayEventsBlueprintLibrary::MakeStringGameplayEvent(FGameplayTag EventTag, const TArray<APlayerController*>& InInstigators, const FString& StringPayload)
{
	return FGameplayEvent(EventTag, InInstigators, StringPayload);
}