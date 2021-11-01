// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableStorage.h"
#include "FGActorRepresentationInterface.h"
#include "FGCentralStorageContainer.generated.h"

/**
 * Storage container connected to the central storage interface.
 */
UCLASS()
class FACTORYGAME_API AFGCentralStorageContainer : public AFGBuildableStorage, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGCentralStorageContainer();

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

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor interface
private:
	// Recalled if the storage subsystem isn't created
	UFUNCTION()
	void AddToCentralStorageSubsystem();
};
