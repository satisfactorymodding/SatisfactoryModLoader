// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "FGGasMask.generated.h"

UCLASS()
class AFGGasMask : public AFGEquipment
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGGasMask();
};

UCLASS()
class AFGGasMaskAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()
};
