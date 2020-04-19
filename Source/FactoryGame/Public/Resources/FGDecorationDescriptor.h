// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Resources/FGEquipmentDescriptor.h"
#include "FGDecorationDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGDecorationDescriptor : public UFGEquipmentDescriptor
{
	GENERATED_BODY()

public:
	UFGDecorationDescriptor();
	/** The static mesh we want for representing the decoration when placed on ground
	 * @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static class UStaticMesh* GetGroundMesh( TSubclassOf< UFGItemDescriptor > inClass );

	/** The static mesh we want for representing the decoration when equipped in 1p.
	 * @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static class UStaticMesh* GetMesh1p( TSubclassOf< UFGItemDescriptor > inClass );

	/** The static mesh we want for representing the decoration when equipped in 3p.
	 * @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static class UStaticMesh* GetMesh3p( TSubclassOf< UFGItemDescriptor > inClass );

	/**  @return The actor to spawn on primary fire, can be null */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static TSubclassOf< AActor > GetDecorationActorClass( TSubclassOf< UFGItemDescriptor > inClass );

	/**  @return Scale of ground mesh actor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FVector GetGroundMeshScale( TSubclassOf< UFGItemDescriptor > inClass );
protected:
	/** The static mesh we want for representing the decoration when placed on ground. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	class UStaticMesh* mGroundMesh;
	
	/** Scale that can be used for the ground mesh  */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	FVector mGroundMeshScale;

	/** The static mesh we want for representing the decoration when equipped in 1p. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	class UStaticMesh* mMesh1p;

	/** The static mesh we want for representing the decoration when equipped in 3p. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	class UStaticMesh* mMesh3p;

	/** The actor to spawn on primary fire press if we want one, can be null */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	TSubclassOf< class AActor > mDecorationActorClass;

public:
	FORCEINLINE ~UFGDecorationDescriptor() = default;
};
