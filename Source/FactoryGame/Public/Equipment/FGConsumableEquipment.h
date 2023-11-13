// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	UFUNCTION( Server, Reliable )
	void Server_Consume();
	
	UFUNCTION( BlueprintCallable, Category = "Consumeable" )
	void Consume();

	/** Get the consumeable currently in hands */
	UFUNCTION( BlueprintPure, Category = "Consumeable" )
	void GetConsumeable( TSubclassOf< class UFGConsumableDescriptor >& out_consumeable, int32& out_numConsumeable ) const;

	/** Plays effects when consuming stuff */
	UFUNCTION( BlueprintNativeEvent, Category = "Consumeable" )
	void PlayConsumeEffects( class UFGConsumableDescriptor* consumable );

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
};
