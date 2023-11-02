// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentationInterface.h"
#include "FGBuildableStorage.h"
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
	UFUNCTION()
	virtual bool AddAsRepresentation() override;
	UFUNCTION()
	virtual bool UpdateRepresentation() override;
	UFUNCTION()
	virtual bool RemoveAsRepresentation() override;
	UFUNCTION()
	virtual bool IsActorStatic() override;
	UFUNCTION()
	virtual FVector GetRealActorLocation() override;
	UFUNCTION()
	virtual FRotator GetRealActorRotation() override;
	UFUNCTION()
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION()
	virtual FText GetActorRepresentationText() override;
	UFUNCTION()
	virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION()
	virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION()
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION()
	virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION()
	virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION()
	virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION()
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION()
	virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION()
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION()
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
