// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGRecipeManagerReplicationComponent.generated.h"

class UFGRecipe;
class AFGRecipeManager;
class UFGItemDescriptor;
struct FGameplayTag;

enum class ERecipeManagerMessageId : uint32
{
	InitialReplication = 0x01,
	StateUpdate = 0x02,
};

struct FRecipeManagerInitialReplicationMessage
{
	static constexpr ERecipeManagerMessageId MessageId = ERecipeManagerMessageId::InitialReplication;
	TArray<TSubclassOf<UFGRecipe>> AllRecipes;
	TArray<TSubclassOf<UFGItemDescriptor>> AllItemDescriptors;
	TArray<TSubclassOf<UFGRecipe>> AllAvailableRecipes;
	TArray<TSubclassOf<UFGItemDescriptor>> AllAvailableItemDescriptors;
	
	friend FArchive& operator<<(FArchive& Ar, FRecipeManagerInitialReplicationMessage& Message);
};
struct FRecipeManagerStateUpdateMessage
{
	static constexpr ERecipeManagerMessageId MessageId = ERecipeManagerMessageId::StateUpdate;
	TArray<TSubclassOf<UFGRecipe>> NewAvailableRecipes;
	TArray<TSubclassOf<UFGRecipe>> RemovedRecipes;
	TArray<TSubclassOf<UFGItemDescriptor>> NewAvailableItemDescriptors;
	
	friend FArchive& operator<<(FArchive& Ar, FRecipeManagerStateUpdateMessage& Message);
};

UCLASS(NotBlueprintable, Within = PlayerController)
class FACTORYGAME_API UFGRecipeManagerReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGRecipeManagerReplicationComponent();
	
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// End UActorComponent interface

	// Begin AFGRecipeManager interface
	void NotifyAddedAvailableRecipes(const TArray<TSubclassOf<UFGRecipe>>& Recipes);
	void NotifyRemovedAvailableRecipes(const TArray<TSubclassOf<UFGRecipe>>& Recipes);
	void NotifyAddedAvailableItemDescriptors(const TArray<TSubclassOf<UFGItemDescriptor>>& ItemDescriptors);
	// End AFGRecipeManager interface

	/** Returns true if the player has received the initial replication message for the initial available recipes */
	FORCEINLINE bool HasReceivedInitialReplicationMessage() const { return mHasReceivedInitialReplicationMessage; }
protected:
	/** Called to initialize on the client once the schematic manager is available */
	void InitializeAsClient();
	/** Sends the initial replication message to the player */
	void SendInitialReplicationMessageToPlayer();
	
	/** Handles schematic manager reliable message */
	void HandleRawMessage(FGameplayTag InTag, TArray<uint8>&& InMessageData);
	/** Sends a schematic manager reliable message */
	void SendRawMessage(ERecipeManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	void ReceivedInitialReplicationMessage(const FRecipeManagerInitialReplicationMessage& InitialReplicationMessage);
	void ReceivedStateUpdateMessage(const FRecipeManagerStateUpdateMessage& UpdateMessage) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendMessage(T& Message)
	{
		SendRawMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	TObjectPtr<AFGRecipeManager> mRecipeManager;

	FRecipeManagerStateUpdateMessage mPendingUpdateMessage;

	UPROPERTY()
	TArray<TSubclassOf<UFGRecipe>> mPendingAvailableRecipes;
	UPROPERTY()
	TArray<TSubclassOf<UFGRecipe>> mPendingRemovalRecipes;
	UPROPERTY()
	TArray<TSubclassOf<UFGItemDescriptor>> mPendingAvailableItemDescriptors;

	bool mHasReceivedInitialReplicationMessage{false};
};
