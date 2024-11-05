// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Info.h"
#include "FGActorRepresentationInterface.h"
#include "FGDeathMarker.generated.h"
#include "FGSaveInterface.h"
#include "FGItemPickupMarker.generated.h"

class UFGItemDescriptor;

/** Marker for an item pickup */
UCLASS( BlueprintType )
class FACTORYGAME_API AFGItemPickupMarker : public AInfo, public IFGActorRepresentationInterface, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGItemPickupMarker();
	
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

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
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface

	UFUNCTION( BlueprintCallable, Category = "Item Pickup Marker" )
	void SetItemDescriptor( TSubclassOf<UFGItemDescriptor> newItemDescriptor );

	UFUNCTION( BlueprintPure, Category = "Item Pickup Marker" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetItemDescriptor() const { return mItemDescriptor; }
protected:
	UPROPERTY( Replicated )
	TSubclassOf<UFGItemDescriptor> mItemDescriptor;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	UMaterialInterface* mCompassMaterialInstance;
};
