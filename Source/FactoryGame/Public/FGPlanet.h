// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "FGPlanet.generated.h"

UCLASS()
class FACTORYGAME_API AFGPlanet : public AActor
{
	GENERATED_BODY()
public:
	// Begin AActor interface
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void BeginDestroy() override;
	// End AActor interface

	/** Update the preview of the planet in the editor */	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, meta = ( CallInEditor = "true" ) )
	void UpdatePreview();
	
	/** Set the position of the planet to the given postion. Takes the initial position into account */
	UFUNCTION( BlueprintImplementableEvent )
	void SetPosition( float pct );

	/** Set if movement of the planet should be enabled */
	UFUNCTION( BlueprintImplementableEvent )
	void EnableMovement( bool enabled );

	/** Set how fast the movement of the planet should be */
	UFUNCTION( BlueprintImplementableEvent )
	void SetMovementMultiplier( float multiplier );
	
private:
#if WITH_EDITOR
	/** Setup so that we get calls to UpdatePreview whenever time of day is updated in the editor */
	void SetupPreviewDelegate();
#endif
#if WITH_EDITORONLY_DATA
	// In editor, receive updates for whenever the time of day is updated
	FDelegateHandle mTimeOfDayUpdated;
#endif
};