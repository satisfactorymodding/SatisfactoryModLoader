// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableHologram.h"
#include "FGDecorHologram.generated.h"


UCLASS()
class FACTORYGAME_API AFGDecorHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

protected:
	// Begin AFGBuildableHologram interface
	virtual void CheckValidPlacement() override;
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName );
	// End AFGBuildableHologram interface

protected:
	/** The name of the component we want to set our decor mesh to */
	static FName mDecorMeshComponentName;

	/** The mesh we want to set to our decor to */
	UPROPERTY( Replicated )
	class UStaticMesh* mDecorMesh;
};