// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "CharacterAnimationTypes.h"
#include "FGCharacterAnimInstance.h"
#include "FGAnimPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimPlayer : public UFGCharacterAnimInstance
{
	GENERATED_BODY()
public:	
	/** Caching stuff */
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	/** Sets value for arm slot */
	void CacheArmSlotData();

	/** Sets value for back slot */
	void CacheBackSlotData();
private:
	/* Begin AFGCharacterAnimInstance*/
	virtual FVector GetCharacterVelocity() const override;
	/* End AFGCharacterAnimInstance*/
public: 
	/** Is first or third person mesh? */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	bool mIsFirstPerson; 

	/** Saved value of arm equipment */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	EArmEquipment mArmSlotType; 

	/** Saved value of back equipment */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	EBackEquipment mBacklotType;

	/** Character this anim belongs to */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	class AFGCharacterPlayer* mCharacter;

public:
	FORCEINLINE ~UFGAnimPlayer() = default;
};
