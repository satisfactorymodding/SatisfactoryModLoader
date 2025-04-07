// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGRecipeManagerReplicationComponent.generated.h"

class UFGRecipe;
class AFGRecipeManager;

enum class ERecipeManagerMessageId : uint32
{
	InitialReplication = 0x01,
	AddAvailableRecipes = 0x02,
	RemoveAvailableRecipes = 0x03,
};

struct FRecipeManagerInitialReplicationMessage
{
	static constexpr ERecipeManagerMessageId MessageId = ERecipeManagerMessageId::InitialReplication;
	TArray<TSubclassOf<UFGRecipe>> AllAvailableRecipes;
	
	friend FArchive& operator<<(FArchive& Ar, FRecipeManagerInitialReplicationMessage& Message);
};
struct FRecipeManagerAddAvailableRecipesMessage
{
	static constexpr ERecipeManagerMessageId MessageId = ERecipeManagerMessageId::AddAvailableRecipes;
	TArray<TSubclassOf<UFGRecipe>> NewAvailableRecipes;
	
	friend FArchive& operator<<(FArchive& Ar, FRecipeManagerAddAvailableRecipesMessage& Message);
};
struct FRecipeManagerRemoveAvailableRecipesMessage
{
	static constexpr ERecipeManagerMessageId MessageId = ERecipeManagerMessageId::RemoveAvailableRecipes;
	TArray<TSubclassOf<UFGRecipe>> RecipesToRemove;
	
	friend FArchive& operator<<(FArchive& Ar, FRecipeManagerRemoveAvailableRecipesMessage& Message);
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
	// End AFGRecipeManager interface

	/** Returns true if the player has received the initial replication message for the initial available recipes */
	FORCEINLINE bool HasReceivedInitialReplicationMessage() const { return mHasReceivedInitialReplicationMessage; }
protected:
	/** Called to initialize on the client once the schematic manager is available */
	void InitializeAsClient();
	/** Sends the initial replication message to the player */
	void SendInitialReplicationMessageToPlayer();
	
	/** Handles schematic manager reliable message */
	void HandleRawMessage(TArray<uint8>&& InMessageData);
	/** Sends a schematic manager reliable message */
	void SendRawMessage(ERecipeManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	void ReceivedInitialReplicationMessage(const FRecipeManagerInitialReplicationMessage& InitialReplicationMessage);
	void ReceivedAvailableRecipes(const FRecipeManagerAddAvailableRecipesMessage& AddAvailableRecipesMessage) const;
	void ReceivedRemovedRecipes(const FRecipeManagerRemoveAvailableRecipesMessage& RemoveAvailableRecipesMessage) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendMessage(T& Message)
	{
		SendRawMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	AFGRecipeManager* mRecipeManager;

	UPROPERTY()
	TArray<TSubclassOf<UFGRecipe>> mPendingAvailableRecipes;
	UPROPERTY()
	TArray<TSubclassOf<UFGRecipe>> mPendingRemovalRecipes;

	bool mHasReceivedInitialReplicationMessage{false};
};
