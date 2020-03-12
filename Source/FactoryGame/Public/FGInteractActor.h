#pragma once
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGUseableInterface.h"
#include "FGInteractActor.generated.h"

UCLASS( abstract )
class FACTORYGAME_API AFGInteractActor : public AActor, public IFGUseableInterface
{
	GENERATED_BODY()
public:
	/** ctor */
	AFGInteractActor();

	/** Called when player interacts with this actor	*/
	UFUNCTION( BlueprintImplementableEvent )
	void OnInteract( class AFGCharacterPlayer* byCharacter );

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

public:
	FORCEINLINE ~AFGInteractActor() = default;
};