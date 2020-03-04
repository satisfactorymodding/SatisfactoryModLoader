// Copyright 2016-2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGConnectionComponent.h"
#include "FGRoadConnectionComponent.generated.h"


UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGRoadConnectionComponent : public UFGConnectionComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGRoadConnectionComponent() = default;
};
