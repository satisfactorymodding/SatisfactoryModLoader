// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGActorRepresentation.h"
#include "FGActorRepresentationInterface.generated.h"

/**
* This interface makes sure this actor gets a representation that is to be shown in compass and
* in the minimap and similar things.
*/
UINTERFACE( Blueprintable, meta = ( CannotImplementInterfaceInBlueprint ) )
class FACTORYGAME_API UFGActorRepresentationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGActorRepresentationInterface
{
	GENERATED_IINTERFACE_BODY()

	/** Adds the actor to the actor representation manager */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool AddAsRepresentation() = 0;

	/** Updates the actor in the actor representation manager */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool UpdateRepresentation() = 0;

	/** Should be called when an actor is destroyed. Then we should remove this representation. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool RemoveAsRepresentation() = 0;

	/** Tells us if the actor is static or not. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool IsActorStatic() = 0;

	/** Called on the server to get the location of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FVector GetRealActorLocation() = 0;

	/** Called on the server to get the rotation of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FRotator GetRealActorRotation() = 0;

	/** Fetches the texture to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual class UTexture2D* GetActorRepresentationTexture() = 0;

	/** Fetches the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FText GetActorRepresentationText() = 0;

	/** Set the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorRepresentationText( const FText& newText ) = 0;

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FLinearColor GetActorRepresentationColor() = 0;

	/** Set the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorRepresentationColor( FLinearColor newColor ) = 0;

	/** Fetches the representation type to use for this actor */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual ERepresentationType GetActorRepresentationType() = 0;

	/** Should this actor ever be shown in the compass */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool GetActorShouldShowInCompass() = 0;

	/** Should this actor ever be shown on the map*/
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool GetActorShouldShowOnMap() = 0;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() = 0;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual float GetActorFogOfWarRevealRadius() = 0;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual ECompassViewDistance GetActorCompassViewDistance() = 0;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) = 0;
};