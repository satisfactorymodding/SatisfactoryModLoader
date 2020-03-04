#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGConsumableEquipment.generated.h"

/** Used to hold consumeables, so we can eat berries, and consume medpacks a.s.o */
UCLASS()
class FACTORYGAME_API AFGConsumableEquipment : public AFGEquipment
{
	GENERATED_BODY()
public:
	/** ctor */
	AFGConsumableEquipment();

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	// End

	/** Called on the owner, client or server but not both. */
	UFUNCTION( BlueprintCallable, Category = "Consumeable" )
	void OnPrimaryFire();

	/** Called on the owner, client or server but not both. */
	UFUNCTION( BlueprintCallable, Category = "Consumeable" )
	void OnConsumePressed();

	/** Get the consumeable currently in hands */
	UFUNCTION( BlueprintPure, Category = "Consumeable" )
	void GetConsumeable( TSubclassOf< class UFGConsumableDescriptor >& out_consumeable, int32& out_numConsumeable ) const;

	/** Only server implementation of primary fire */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	/** Plays effects when consuming stuff */
	UFUNCTION( BlueprintNativeEvent, Category = "Consumeable" )
	void PlayConsumeEffects( class UFGConsumableDescriptor* consumable );
protected:
	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;
protected:

public:
	FORCEINLINE ~AFGConsumableEquipment() = default;
};