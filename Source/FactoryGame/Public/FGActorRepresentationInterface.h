// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGActorRepresentation.h"
#include "UObject/Interface.h"
#include "LocalUserInfo.h"
#include "Online/CoreOnline.h"
#include "Online/PlayerInfoCache.h"
#include "FGActorRepresentationInterface.generated.h"

/**
* This interface makes sure this actor gets a representation that is to be shown in compass and
* in the minimap and similar things.
*/
UINTERFACE( BlueprintType, NotBlueprintable )
class FACTORYGAME_API UFGActorRepresentationInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
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
	virtual bool IsActorStatic() { return true; }

	/** Called on the server to get the location of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FVector GetRealActorLocation() = 0;

	/** Called on the server to get the rotation of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FRotator GetRealActorRotation() { return FRotator::ZeroRotator; }

	/** Fetches the texture to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual class UTexture2D* GetActorRepresentationTexture() = 0;

	/** Fetches the material to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() = 0;
	
	/** Fetches the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FText GetActorRepresentationText() = 0;

	/** Set the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorRepresentationText( const FText& newText ) {};

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FLinearColor GetActorRepresentationColor() = 0;

	/** Set the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorRepresentationColor( FLinearColor newColor ) {};

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
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() { return EFogOfWarRevealType::FOWRT_None; }

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual float GetActorFogOfWarRevealRadius() { return 0.0f; }

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual ECompassViewDistance GetActorCompassViewDistance() { return ECompassViewDistance::CVD_Always; }

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) {};

	/** Returns the handle of the last player who has edited this representation, if any */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FPlayerInfoHandle GetLastEditedBy() const { return FPlayerInfoHandle(); }

	/** Updates the handle of the last player who has edited this representation (if this representation can be edited) */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorLastEditedByHandle( const FPlayerInfoHandle& playerInfoHandle ) {}
};