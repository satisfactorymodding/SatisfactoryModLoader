// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Components/ActorComponent.h"
#include "FGCreatureSpawnerDebugComponent.generated.h"


/** @todo: Should we be able to blueprint this and do different spawning paradigms */
/** @todo: We could potentially generalize this even more to spawn whatever actor depending on some special rules */
/** @todo: Do we maybe want to create a scene proxy for this, so that we can always draw cylinders, even when we ain't clicked (see USphereComponent) */
UCLASS( DefaultToInstanced, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=(Tags,Activation) )
class FACTORYGAME_API UFGCreatureSpawnerDebugComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFGCreatureSpawnerDebugComponent();
protected:

};
