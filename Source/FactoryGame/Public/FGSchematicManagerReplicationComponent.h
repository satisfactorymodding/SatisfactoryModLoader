// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/SoftObjectPtr.h"
#include "FGSchematicManagerReplicationComponent.generated.h"

enum class ESchematicUnlockFlags : uint8;
class UFGSchematic;
class AFGCharacterPlayer;

enum class ESchematicManagerMessageId : uint32
{
	InitialReplication = 0x01,
	PurchasedSchematics = 0x02,
	ResetSchematics = 0x03,
};

struct FSchematicManagerInitialReplicationMessage
{
	static constexpr ESchematicManagerMessageId MessageId = ESchematicManagerMessageId::InitialReplication;
	TArray<TSubclassOf<UFGSchematic>> AllPurchasedSchematics;
	
	friend FArchive& operator<<(FArchive& Ar, FSchematicManagerInitialReplicationMessage& Message);
};
struct FSchematicsPurchasedMessage
{
	static constexpr ESchematicManagerMessageId MessageId = ESchematicManagerMessageId::PurchasedSchematics;
	TArray<TSubclassOf<UFGSchematic>> NewPurchasedSchematics;
	ESchematicUnlockFlags UnlockFlags{};
	AFGCharacterPlayer* AccessInstigator{};
	
	friend FArchive& operator<<(FArchive& Ar, FSchematicsPurchasedMessage& Message);
};
struct FResetSchematicsMessage
{
	static constexpr ESchematicManagerMessageId MessageId = ESchematicManagerMessageId::ResetSchematics;
	TArray<TSubclassOf<UFGSchematic>> SchematicsToReset;
	
	friend FArchive& operator<<(FArchive& Ar, FResetSchematicsMessage& Message);
};

UCLASS(NotBlueprintable, Within = PlayerController)
class FACTORYGAME_API UFGSchematicManagerReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGSchematicManagerReplicationComponent();
	
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent interface

	// Begin AFGSchematicManager interface
	void NotifySchematicsPurchased(TArrayView<const TSubclassOf<UFGSchematic>> Schematics, AFGCharacterPlayer* AccessInstigator, ESchematicUnlockFlags UnlockFlags);
	void NotifySchematicsReset(TArrayView<const TSubclassOf<UFGSchematic>> Schematics);
	// End AFGSchematicManager interface

	/** Returns true if the player has received the initial replication message for all the unlocked schematics */
	FORCEINLINE bool HasReceivedInitialReplicationMessage() const { return bHasReceivedInitialReplicationMessage; }
protected:
	/** Called to initialize on the client once the schematic manager is available */
	void InitializeAsClient();
	/** Sends the initial replication message to the player */
	void SendInitialReplicationMessageToPlayer();
	
	/** Handles schematic manager reliable message */
	void HandleRawSchematicManagerMessage(TArray<uint8>&& InMessageData);
	/** Sends a schematic manager reliable message */
	void SendRawSchematicManagerMessage(ESchematicManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	void ReceivedInitialReplicationMessage(const FSchematicManagerInitialReplicationMessage& InitialReplicationMessage);
	void ReceivedSchematicsPurchasedMessage(const FSchematicsPurchasedMessage& SchematicsPurchasedMessage) const;
	void ReceivedSchematicsResetMessage(const FResetSchematicsMessage& ResetSchematicsMessage) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendSchematicManagerMessage(T& Message)
	{
		SendRawSchematicManagerMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	class AFGSchematicManager* mSchematicManager;

	bool bRegisteredMessageHandler{false};
	bool bHasReceivedInitialReplicationMessage{false};
};
