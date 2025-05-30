// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGStorySubsystem.h"
#include "Net/UnrealNetwork.h"

void UFGStorySubsystemRemoteCallObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGStorySubsystemRemoteCallObject, mForceNetField_UFGStorySubsystemRemoteCallObject);
}
void UFGStorySubsystemRemoteCallObject::Server_MessageStartedForPlayer_Implementation(class AFGPlayerController* player, class UFGMessage* message){  }
void UFGStorySubsystemRemoteCallObject::Client_ForwardMessagesToGameUI_Implementation(const TArray<class UFGMessage*>& newMessages){ }
void UFGStorySubsystemRemoteCallObject::Server_MessageFinishedForPlayer_Implementation( AFGPlayerController* player,  UFGMessage* message){ }
AFGStorySubsystem::AFGStorySubsystem() : Super() {

}
AFGStorySubsystem* AFGStorySubsystem::Get(UWorld* world){ return nullptr; }
AFGStorySubsystem* AFGStorySubsystem::Get(UObject* worldContext){ return nullptr; }
void AFGStorySubsystem::BeginPlay(){ Super::BeginPlay(); }
void AFGStorySubsystem::OnOnboardingStepUpdated( UFGOnboardingStep* newOnboardingStep){ }
void AFGStorySubsystem::OnSchematicsPurchased(TArray<TSubclassOf<UFGSchematic>> newSchematics, class AFGCharacterPlayer* purchaseInstigator, ESchematicUnlockFlags unlockFlags){  }
void AFGStorySubsystem::OnGamePhaseChanged(UFGGamePhase* currentGamePhase, bool bSuppressNarrativeMessages){  }
void AFGStorySubsystem::OnGameCompleted(bool bSuppressNarrativeMessages){  }
void AFGStorySubsystem::OnLocalPlayerMessageStarted(class UFGMessage* message){  }
void AFGStorySubsystem::OnLocalPlayerMessageFinished( UFGMessage* message){ }
void AFGStorySubsystem::OnItemPickuped(AFGPlayerState* playerState, const FItemAmount& totalAmountPickuped){ }
void AFGStorySubsystem::OnItemManuallyCrafted(AFGPlayerState* playerState, const FItemAmount& totalAmountCrafted){ }
void AFGStorySubsystem::OnBuildingBuilt(AFGPlayerState* playerState, class AActor* builtActor, const struct FActorBuiltData& actorBuiltData){  }
void AFGStorySubsystem::OnBuildingDismantled(AFGPlayerState* playerState, TSubclassOf<class AActor> builtActor, const struct FActorBuiltData& actorBuiltData){  }
void AFGStorySubsystem::OnItemsSunk(TSet<TSubclassOf<UFGItemDescriptor>> items){ }
void AFGStorySubsystem::OnFirstItemSinkFailure(TSubclassOf<UFGItemDescriptor> itemFailedToSink){ }
void AFGStorySubsystem::OnCalendarSlotUnlocked(int32 slot, bool isRandomUnlock, class UFGUnlock* unlock){ }
void AFGStorySubsystem::OnCalendarOpenedByPlayer(class AFGCharacterPlayer* byCharacter,	class AFGBuildableCalendar* calendar, bool firstTime){ }
void AFGStorySubsystem::OnMessageStartedForPlayer(class AFGPlayerController* player, class UFGMessage* message){  }
void AFGStorySubsystem::OnMessageFinishedForPlayer(class AFGPlayerController* player, class UFGMessage* message){  }
void AFGStorySubsystem::OnPlayerFinishedSpawning(class AFGCharacterPlayer* player){ }
void AFGStorySubsystem::OnPersonalElevatorBeginMove(const TArray<class AFGCharacterPlayer*>& OccupyingPlayers, float estimatedTravelTime){  }
void AFGStorySubsystem::OnPersonalElevatorEndMove(const TArray<class AFGCharacterPlayer*>& OccupyingPlayers, float estimatedTravelTime){  }
void AFGStorySubsystem::OnToiletFlushed(class AFGCharacterPlayer* byCharacter, class AFGPioneerPotty* toilet){ }
void AFGStorySubsystem::OnActorTookDamage(AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser){  }
void AFGStorySubsystem::OnSpaceElevatorShipmentLockedIn(AFGPlayerState* playerState,  UFGGamePhase* gamePhase){ }
void AFGStorySubsystem::OnSpaceElevatorFullyBuilt(){ }
void AFGStorySubsystem::ForwardMessagesToGameUI(const TArray<class UFGMessage*>& messages){ }
UFGMessage* AFGStorySubsystem::GetPlayableInterruptMessage(AFGPlayerState* instigatingPlayerState) const{ return nullptr; }
void AFGStorySubsystem::GetStoryDebugData(TArray<FString>& out_debugData){ }
void AFGStorySubsystem::SetupDelegates(){ }
void AFGStorySubsystem::TryPlayMessages(const TArray<class UFGMessage*>& messages, const AFGPlayerState* instigatingPlayerState, bool bSuppressNarrativeMessages){  }
