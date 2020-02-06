// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Object.h"
#include "FGSettings.generated.h"

/**
*
*/
UCLASS( Blueprintable, abstract, meta = (AutoJson = true) )
class FACTORYGAME_API UFGSettings : public UObject
{
	GENERATED_BODY()
};
