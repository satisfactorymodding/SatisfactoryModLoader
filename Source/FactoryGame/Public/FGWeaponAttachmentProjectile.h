// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Equipment/FGWeaponAttachment.h"
#include "FGWeaponAttachmentProjectile.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWeaponAttachmentProjectile : public AFGWeaponAttachment
{
	GENERATED_BODY()
	
protected:
	/** Called on remote clients when the player fires the weapon. Needed a function so I could overload in FGWeaponAttachmentProjectile */
	virtual void PlayerFired( FVector flashLocation ) override;
		

public:
	FORCEINLINE ~AFGWeaponAttachmentProjectile() = default;
};
