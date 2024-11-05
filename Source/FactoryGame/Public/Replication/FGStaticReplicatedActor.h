// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGStaticReplicatedActor.generated.h"

/*
* Base class for replicated actors that are static (cannot move after creation)
* Inherit from this to establish a common base to eliminate needing to add custom rules for the replication graph
*/

UCLASS()
class FACTORYGAME_API AFGStaticReplicatedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGStaticReplicatedActor();

};
