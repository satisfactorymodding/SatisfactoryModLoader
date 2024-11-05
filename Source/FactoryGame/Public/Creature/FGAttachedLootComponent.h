// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGInventoryComponent.h"
#include "Components/SceneComponent.h"

#include "FGAttachedLootComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGAttachedLootComponent : public USceneComponent, public IFGSaveInterface
{
	GENERATED_BODY()

public:	
	UFGAttachedLootComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFGSaveInterface
	
	UFUNCTION( BlueprintCallable, Category = "Attached Loot" )
	void SpawnAttachedItemDrop( const FInventoryStack& stack );

private:
	void AttachItemPickup();
	
private:
	UPROPERTY( SaveGame )
	class AFGItemPickup_Spawnable* mAttachedItemPickup;
};
