// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGActorRepresentationInterface.h"
#include "FGBeacon.generated.h"

UCLASS()
class FACTORYGAME_API AFGBeacon : public AFGStaticReplicatedActor, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGBeacon();

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText( const FText& newText ) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	// End IFGActorRepresentationInterface

	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	/** Pickup the beacon by the provided player */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Beacon" )
	void PickUpBeacon( class AFGCharacterPlayer* player );

	/** Sets the text to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	void SetRepresentationColor( const FLinearColor& color );

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetRepresentationColor();

	/** Sets the text to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	void SetRepresentationText( const FText& text );

	/** Fetches the text to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FText GetRepresentationText();

	/** Sets the compass view distance to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	void SetCompassViewDistance( ECompassViewDistance compassViewDistance );

	/** Fetches the compass view distance to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	ECompassViewDistance GetCompassViewDistance();

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;
	
};
