#include "FGRecipeManagerReplicationComponent.h"

UFGRecipeManagerReplicationComponent::UFGRecipeManagerReplicationComponent() : Super() {
	this->mRecipeManager = nullptr;
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
}
void UFGRecipeManagerReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGRecipeManagerReplicationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UFGRecipeManagerReplicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
void UFGRecipeManagerReplicationComponent::NotifyAddedAvailableRecipes(const TArray<TSubclassOf<UFGRecipe>>& Recipes){  }
void UFGRecipeManagerReplicationComponent::NotifyRemovedAvailableRecipes(const TArray<TSubclassOf<UFGRecipe>>& Recipes){  }
void UFGRecipeManagerReplicationComponent::InitializeAsClient(){  }
void UFGRecipeManagerReplicationComponent::SendInitialReplicationMessageToPlayer(){  }
void UFGRecipeManagerReplicationComponent::HandleRawMessage(TArray<uint8>&& InMessageData){  }
void UFGRecipeManagerReplicationComponent::SendRawMessage(ERecipeManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{  }
void UFGRecipeManagerReplicationComponent::ReceivedInitialReplicationMessage(const FRecipeManagerInitialReplicationMessage& InitialReplicationMessage){  }
void UFGRecipeManagerReplicationComponent::ReceivedAvailableRecipes(const FRecipeManagerAddAvailableRecipesMessage& AddAvailableRecipesMessage) const{  }
void UFGRecipeManagerReplicationComponent::ReceivedRemovedRecipes(const FRecipeManagerRemoveAvailableRecipesMessage& RemoveAvailableRecipesMessage) const{  }