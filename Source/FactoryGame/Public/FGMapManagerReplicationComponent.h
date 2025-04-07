// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGMapManagerReplicationComponent.generated.h"

class AFGMapManager;

enum class EMapManagerMessageId : uint32
{
	FullFogOfWaterData = 0x01,
};

struct FMapManagerFullFogOfWarDataMessage
{
	static constexpr EMapManagerMessageId MessageId = EMapManagerMessageId::FullFogOfWaterData;
	TArray<uint8> RawFogOfWarData;
	
	friend FArchive& operator<<(FArchive& Ar, FMapManagerFullFogOfWarDataMessage& Message);
};

UCLASS(NotBlueprintable, Within = PlayerController)
class FACTORYGAME_API UFGMapManagerReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	// End UActorComponent interface

	/** Sends the full FOW data to the player, overwriting results of local simulation */
	void SendFullFogOfWarDataToPlayer();
protected:
	/** Called to initialize on the client once the map manager is available */
	void InitializeAsClient();
	
	/** Handles schematic manager reliable message */
	void HandleRawMessage(TArray<uint8>&& InMessageData) const;
	/** Sends a schematic manager reliable message */
	void SendRawMessage(EMapManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	/** Handles Fog Of War update */
	void ReceiveFullFogOfWarUpdate(const FMapManagerFullFogOfWarDataMessage& Message) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendMessage(T& Message)
	{
		SendRawMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	AFGMapManager* mMapManager;
};
