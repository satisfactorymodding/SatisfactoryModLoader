#pragma once
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "GameFramework/Actor.h"
#include "ModSubsystemHolder.generated.h"

/**
 * Abstract holder for mod defined subsystems
 * Component is initialized on server only, so if you need
 * to access subsystem instances on client you should set bReplicates to true
 *
 * You should use it like that:
 * 1) Add number of subsystems to the static fields
 * 2) Initialize them in InitSubsystems (Server-side only)
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

	/**
	 * Called when Game State is initialized
	 * Called on both sides unlike InitSubsystems, so you can have local
	 * subsystems that are not replicated and exist on both sides
	 */
	virtual void InitLocalSubsystems();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InitSubsystems"))
	void K2_InitSubsystems();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InitLocalSubsystems"))
    void K2_InitLocalSubsystems();
	
	/**
	 * Spawns subsystem instance and returns created actor
	 * Store it in member variable for faster access
	 * @return spawned subsystem instance, or nullptr if spawning failed
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Subsystem", DeterminesOutputType = "SpawnClass"))
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
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetModSubsystemHolder", WorldContext = "WorldContextObject", DeterminesOutputType = "HolderClass"))
	static UModSubsystemHolder* K2_GetModSubsystemHolder(TSubclassOf<UModSubsystemHolder> HolderClass, UObject* WorldContextObject);

	template <typename T>
	static T* GetSubsystemHolder(UObject* WorldContext) {
		return Cast<T>(K2_GetModSubsystemHolder(T::StaticClass(), WorldContext));
	}
};