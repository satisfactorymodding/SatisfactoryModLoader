// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableRailroadAttachment.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadAttachment : public AFGBuildable
{
	GENERATED_BODY()

	friend class AFGRailroadAttachmentHologram;
public:
	AFGBuildableRailroadAttachment();

	UFUNCTION( BlueprintPure, Category = "Railroad Attachment" )
	bool IsEndStop() const { return mIsEndStop; }

	UFUNCTION( BlueprintPure, Category = "Railroad Attachment" )
	class UFGRailroadTrackConnectionComponent* GetConnection() const { return mConnection; }

	UFUNCTION( BlueprintNativeEvent, Category = "Railroad Attachment" )
	void OnTrainVehicleHitEndStop( class AFGRailroadVehicle* vehicle, float velocity );
	
private:
	UPROPERTY( EditDefaultsOnly, Category = "Railroad Attachment" )
	bool mIsEndStop;

	UPROPERTY( EditDefaultsOnly, Category = "Railroad Attachment" )
	class UFGRailroadTrackConnectionComponent* mConnection;
};
