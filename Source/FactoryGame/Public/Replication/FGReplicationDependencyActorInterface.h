#pragma once
#include "UObject/Interface.h"

#include "FGReplicationDependencyActorInterface.generated.h"

UINTERFACE( )
class FACTORYGAME_API UFGReplicationDependencyActorInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGReplicationDependencyActorInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGReplicationDependencyActorInterface() = default;
};

class FACTORYGAME_API IFGReplicationDependencyActorInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	FORCEINLINE IFGReplicationDependencyActorInterface() = default;
};