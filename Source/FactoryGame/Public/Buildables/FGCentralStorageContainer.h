// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	UFUNCTION()
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick(float DeltaSeconds) override;
	// End AActor interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	UFUNCTION( BlueprintPure, Category = "CentralStorage" )
	bool IsUploadingToCentralStorage();
	UFUNCTION( BlueprintPure, Category = "CentralStorage" )
	float GetCentralStorageUploadProgress() const;
	UFUNCTION( BlueprintPure, Category = "CentralStorage" )
	bool IsUploadInventoryEmpty();

	UFUNCTION()
	void UpdateTimeToUpload();
	
private:
	bool CanUploadItem();
	
	UFUNCTION()
	void TryUploadItem();

	UPROPERTY( Transient )
	class AFGCentralStorageSubsystem* mCentralStorageSubsystem;

	/** The timer we use to track upload of an item to central storage */
	UPROPERTY( SaveGame, Replicated )
	float mUploadTimer;

	/** How long does it take to upload an item to central storage */
	UPROPERTY( Replicated )
	float mTimeToUpload = 1.f;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mCompassMaterialInstance;
};
