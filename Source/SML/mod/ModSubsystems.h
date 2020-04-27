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
 * Abstract holder for mod defined subsystems
 * Component is initialized on server only, so if you need
 * to access subsystem instances on client you should set bReplicates to true
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

	/**
	 * Spawns subsystem instance and returns created actor
	 * Store it in member variable for faster access
	 * @return spawned subsystem instance, or nullptr if spawning failed
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SpawnSubsystem"))
	AFGSubsystem* K2_SpawnSubsystem(TSubclassOf<AFGSubsystem> SpawnClass, FName SpawnName);
	
	/**
	* Spawns subsystem instance and sets it's pointer to returned object
	* Type-safe wrapper around K2_SpawnSubsystem
	*/
	template< class C >
	void SpawnSubsystem(C*& OutSpawnedSubsystem, TSubclassOf<AFGSubsystem> SpawnClass, FName SpawnName) {
		if (OutSpawnedSubsystem) {
			UE_LOG(LogTemp, Error, TEXT("ModSubsystems::SpawnSubsystem failed for '%s', already spawned or loaded."), *SpawnName.ToString());
			return;
		}
		auto* Subsystem = Cast<C>(K2_SpawnSubsystem(SpawnClass, SpawnName));
		OutSpawnedSubsystem = Subsystem;
		check(OutSpawnedSubsystem);
	}

	/**
	* Retrieves instance of the given subsystem holder for the world context
	* You need to cast it to your class afterwards
	* In C++, use helper template function GetSubsystemHolder<T>()
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetModSubsystemHolder", WorldContext = "WorldContextObject"))
	static UModSubsystemHolder* K2_GetModSubsystemHolder(TSubclassOf<UModSubsystemHolder> HolderClass, UObject* WorldContextObject);
};

/**
 * Retrieves instance of the given subsystem holder for the world context
 */
template <typename T>
T* GetSubsystemHolder(UObject* WorldContext) {
	return Cast<T>(UModSubsystemHolder::K2_GetModSubsystemHolder(T::StaticClass(), WorldContext));
}

UCLASS(MinimalAPI)
class USMLSubsystemHolder : public UModSubsystemHolder {
	GENERATED_BODY()
private:
	UPROPERTY()
	AChatCommandSubsystem* ChatCommandSubsystem;
public:
	FORCEINLINE AChatCommandSubsystem* GetChatCommandSubsystem() const { return ChatCommandSubsystem; }
	void InitSubsystems() override;
};