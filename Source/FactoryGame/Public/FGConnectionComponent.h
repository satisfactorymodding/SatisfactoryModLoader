// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/SceneComponent.h"
#include "FGSaveInterface.h"
#include "FGConnectionComponent.generated.h"


/**
 * Base class for connection components, i.e. factory, power, track connections...
 */
UCLASS( Abstract, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGConnectionComponent : public USceneComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFGSaveInterface
};
