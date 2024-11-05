// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGMessagePlayedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGMessagePlayedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	virtual bool ArePlayerSpecificDependenciesMet( const class AFGPlayerState* playerState ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
    void GetMessages( TArray< class UFGMessage* >& out_messages ) const;

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The messages require for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TArray< class UFGMessage* > mMessages;

	/** Do we require all messages to be played for this dependency to be met */

	/**
	 * Indicates if all messages in the list are required to meet the dependency condition.
	 * The interpretation varies based on the dependency context:
	 * - In UFGMessagePlayedDependency: True means all messages must have been played. 
	 *   False means it's sufficient if at least one message has been played.
	 * - In UFGMessageNotPlayedDependency: True means all messages must not have been played. 
	 *   False means it's sufficient if at least one message has not been played.
	 * Note: The name might be misleading due to its origin before the introduction of UFGMessageNotPlayedDependency.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Dependency", meta = (DisplayName = "RequireAllMessages"))
	bool mRequireAllMessagesToBePlayed;

	
};

/**
 * Inverted version of UFGMessagePlayedDependency
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGMessageNotPlayedDependency : public UFGMessagePlayedDependency
{
	GENERATED_BODY()

public:
	virtual bool ArePlayerSpecificDependenciesMet( const class AFGPlayerState* playerState ) const override;
};
