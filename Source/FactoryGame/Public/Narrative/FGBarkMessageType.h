// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGBarkMessageType.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, BlueprintType, Abstract )
class FACTORYGAME_API UFGBarkMessageType : public UObject
{
	GENERATED_BODY()
public:
	UFGBarkMessageType();

	float GetMessageCooldown() const { return mMessageCooldown; }
	bool ShouldIgnoreGlobalMessageCooldown() const { return mIgnoreGlobalMessageCooldown; }

private:
	/** The cooldown of this bark message type. */
	UPROPERTY( EditDefaultsOnly, Category = "Bark Message" )
	float mMessageCooldown;

	/** Whether or not this bark message type should ignore the global message cooldown, in which case it will only use the cooldown specified for this type. */
	UPROPERTY( EditDefaultsOnly, Category = "Bark Message" )
	bool mIgnoreGlobalMessageCooldown;
};
