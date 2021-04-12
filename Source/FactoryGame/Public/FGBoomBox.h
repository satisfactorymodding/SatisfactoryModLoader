// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGInventoryComponent.h"
#include "FGMusicPlayerInterface.h"

#include "FGBoomBox.generated.h"

UCLASS()
class FACTORYGAME_API AFGBoomBox : public AActor, public IFGSaveInterface, public IFGMusicPlayerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGBoomBox();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** What do we get back when picking this up */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
    TArray< FInventoryStack > GetInventoryReturns() const;  

};
