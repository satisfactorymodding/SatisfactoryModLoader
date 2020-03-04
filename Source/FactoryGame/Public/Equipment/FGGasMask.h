// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "FGGasMask.generated.h"

UCLASS()
class FACTORYGAME_API AFGGasMask : public AFGEquipment
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGGasMask();

public:
	FORCEINLINE ~AFGGasMask() = default;
};

UCLASS()
class FACTORYGAME_API AFGGasMaskAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:
	FORCEINLINE ~AFGGasMaskAttachment() = default;
};
