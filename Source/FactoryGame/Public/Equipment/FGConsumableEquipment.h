// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	
	UFUNCTION( BlueprintCallable, Category = "Consumeable", DisplayName = "Consume Equipment" )
	void Consume();

	/** Get the consumeable currently in hands */
	UFUNCTION( BlueprintPure, Category = "Consumeable", DisplayName = "Get Consumable Type and Amount" )
	void GetConsumeable( TSubclassOf< class UFGConsumableDescriptor >& out_consumeable, int32& out_numConsumeable ) const;

protected:
	/** Plays effects when consuming stuff */
	UFUNCTION( BlueprintNativeEvent, Category = "Consumeable" )
	void PlayConsumeEffects( class UFGConsumableDescriptor* consumable );

	UFUNCTION( Server, Reliable )
	void Server_Consume();
	
	UFUNCTION( NetMulticast, Unreliable )
	void Multicast_PlayConsumeEffects( TSubclassOf<UFGConsumableDescriptor> consumableClass );
	
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
};
