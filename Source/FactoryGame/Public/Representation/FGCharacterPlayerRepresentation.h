// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "FGCharacterPlayerRepresentation.generated.h"

UCLASS()
class FACTORYGAME_API UFGCharacterPlayerRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
public:
	UFGCharacterPlayerRepresentation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Begin UFGActorRepresentation interface
	virtual void UpdateActorRepresentation() override;
	// End UFGActorRepresentation interface

	/** Opens the profile of the owning player in platform overlay */
	UFUNCTION( BlueprintCallable, Category = "Player Character Representation" )
	void ViewProfileOfOwningPlayer();

	/** Returns true if the owner player is on the same platform as the local player */
	UFUNCTION( BlueprintPure, Category = "Player Character Representation" )
	bool IsCharacterOwnerOnSamePlatform() const;

	/** Returns true if the local player is allowed to view profile of owning player */
	UFUNCTION( BlueprintPure, Category = "Player Character Representation" )
	bool IsPlayerAllowedToViewProfile() const;

	/** Returns account ID from the given player info handle */
	UE::Online::FAccountId ResolvePlayerAccountId() const;
protected:
	/** Handle to the information about the player possessing the owning character */
	UPROPERTY( Replicated )
	FPlayerInfoHandle mPlayerInfoHandle;
};
