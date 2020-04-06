#pragma once
#include "FGGameState.h"
#include "command/ChatCommandLibrary.h"
#include "ModSubsystems.generated.h"

class UModSubsystemHolder;

class FSubsystemInfoHolder {
public:
	/**
	 * Registers subsystem holder to be attached to game state
	 * and initialized on world load
	 */
	SML_API static void RegisterSubsystemHolder(TSubclassOf<UModSubsystemHolder> Class);

	static void SetupHooks();
	static void InitializeSubsystems(AFGGameState* GameState);
};

/**
 * Retrieves instance of the given subsystem holder for the world context
 * TODO: Similar function accessible from blueprints
 */
template <typename T>
T* GetSubsystemHolder(UObject* WorldContext) {
	UWorld* World = WorldContext->GetWorld();
	checkf(World, TEXT("GetWorld not implemented for passed WorldContext object"));
	AFGGameState* GameState = World->GetGameState<AFGGameState>();
	if (GameState == nullptr)
		return nullptr;
	return GameState->FindComponentByClass<T>();
}

/**
 * Abstract holder for mod defined subsystems
 * Component is initialized on server and replicated to client, but subsystem instances
 * are created only on server side, and replicated to clients as needed
 *
 * You should use it like that:
 * 1) Add number of subsystems to the static fields
 * 2) Initialize them in Init (Server-side only)
 * 3) Expose field via static getter
 *
 * Register your subsystem holders via FSubsystemInfoHolder or ASMLInitMod
 */
UCLASS(Abstract, Blueprintable)
class SML_API UModSubsystemHolder: public UActorComponent {
	GENERATED_BODY()
public:
	/**
	 * Called when FactoryGame subsystems are initialized
	 * Good place to initialize all other modded subsystems
	 * Called only on server side! Make sure subsystem actors are replicated and their properties
	 * are replicated too if you want to use subsystems on client!
	 */
	virtual void InitSubsystems();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InitSubsystems"))
	void K2_InitSubsystems();
};

UCLASS(MinimalAPI)
class USMLSubsystemHolder : public UModSubsystemHolder {
	GENERATED_BODY()
private:
	UPROPERTY()
	AChatCommandSubsystem* ChatCommandSubsystem;
public:
	FORCEINLINE AChatCommandSubsystem* GetChatCommandSubsystem() const { return ChatCommandSubsystem; }
	void InitSubsystems() override;

	/**
	* Spawns subsystem instance and sets it's pointer to returned object
	* TODO: Similar function accessible from blueprints
	*/
	template< class C >
	void SpawnSubsystem(C*& OutSpawnedSubsystem, TSubclassOf<AFGSubsystem> SpawnClass, FName SpawnName) {
		if (OutSpawnedSubsystem) {
			UE_LOG(LogTemp, Error, TEXT("ModSubsystems::SpawnSubsystem failed for '%s', already spawned or loaded."), *SpawnName.ToString());
			return;
		}
		if (!IsValid(SpawnClass)) {
			UE_LOG(LogTemp, Error, TEXT("ModSubsystems::SpawnSubsystem failed for '%s', no class given."), *SpawnName.ToString());
			return;
		}
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Name = SpawnName;

		OutSpawnedSubsystem = GetWorld()->SpawnActor<C>(SpawnClass, SpawnParams);
		check(OutSpawnedSubsystem);
	}
};