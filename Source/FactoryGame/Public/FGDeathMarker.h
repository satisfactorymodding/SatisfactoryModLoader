// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGActorRepresentationInterface.h"
#include "FGDeathMarker.generated.h"

UCLASS( Abstract )
class FACTORYGAME_API AFGDeathMarker : public AActor, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGDeathMarker();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

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

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( Replicated )
	FText mMapText;
};
