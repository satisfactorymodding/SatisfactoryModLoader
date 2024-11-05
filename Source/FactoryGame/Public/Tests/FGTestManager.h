// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "FGTestManager.generated.h"

enum class EFGGameplayTestFlags : uint8;
DECLARE_LOG_CATEGORY_EXTERN( LogFGTestManager, All, All );

class UFGGameplayTest;
class UFGItemDescriptor;
class UFGPowerInfoComponent;
class UFGPowerConnectionComponent;

// Hosts the data needed to automatically keep the test spawned manufacturer stocked with resources/consume outputs
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGTestBuildableDescriptor_Manufacturer
{
	GENERATED_BODY()

	// Buildable associated with this descriptor
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Manufacturer" )
	class AFGBuildableManufacturer* Buildable{};

	// Whenever we should automatically populate inputs
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Manufacturer" )
	bool AutoSaturateInputs{};

	// Whenever we should automatically consume outputs
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Manufacturer" )
	bool AutoConsumeOutputs{};
};

// Hosts the data needed to automatically keep the test spawned generator stocked with resources/consume outputs
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGTestBuildableDescriptor_GeneratorFuel
{
	GENERATED_BODY()

	// Buildable associated with this descriptor
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Generator" )
	class AFGBuildableGeneratorFuel* Buildable{};

	// Class of the fuel to automatically saturate the generator with
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Generator" )
	TSubclassOf<UFGItemDescriptor> FuelItemDescriptor;

	// Whenever we should automatically consume outputs
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Generator" )
	bool AutoSaturateSupplementalResource{};

	// Whenever we should automatically consume outputs
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "FactoryGame | Generator" )
	bool AutoConsumeOutputs{};
};

/**
 * Test Manager is a central hub for testing related APIs and collecting test results
 * It is only instantiated on the server side and can run the tests when it's asked to.
 *
 * It also handles various buildable related testing routines, like keeping buildings stocked on resources.
 */
UCLASS( BlueprintType, Config = Game, DefaultConfig )
class FACTORYGAME_API AFGTestManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGTestManager();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Returns the test manager instance for this world
	UFUNCTION( BlueprintPure, Category = "FactoryGame | Testing", DisplayName = "Get Test Manager" )
	static AFGTestManager* Get( const UObject* worldContext );

	static bool ShouldSpawnForWorld( const UWorld* world );
	static FString GetWorldGameplayTestName( const UWorld* world );

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
	// End AActor interface

	// Starts the gameplay test from the given class name, returns the gameplay test instance that can be used to track it's execution
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing" )
	UFGGameplayTest* RunGameplayTest( TSubclassOf<UFGGameplayTest> gameplayTest );

	// Returns all gameplay tests currently running.
	UFUNCTION( BlueprintPure, Category = "FactoryGame | Testing" )
	void GetRunningGameplayTests( TArray<UFGGameplayTest*>& out_gameplayTests ) const;

	// Registers the given manufacturer as a test building with automatically managed inputs/outputs
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing" )
	void RegisterTestManufacturer( const FFGTestBuildableDescriptor_Manufacturer& manufacturerData );

	// Registers the given generator as a test building with automatically managed inputs/outputs
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing" )
	void RegisterTestGenerator( const FFGTestBuildableDescriptor_GeneratorFuel& generatorData );

	// Returns the power connection that is backed by a virtual battery with an infinite charge
	UFUNCTION( BlueprintPure, Category = "FactoryGame | Testing" )
	FORCEINLINE UFGPowerConnectionComponent* GetCheatPowerSourceConnection() const { return mCheatPowerSourceConnection; }

	// Returns the power connection that is backed by a virtual empty battery with an infinite capacity
	UFUNCTION( BlueprintPure, Category = "FactoryGame | Testing" )
	FORCEINLINE UFGPowerConnectionComponent* GetCheatPowerSinkConnection() const { return mCheatPowerSinkConnection; }

	static TSubclassOf<UFGGameplayTest> FindGameplayTestByName( const FString& gameplayTestName );
	static void ScanForGameplayTests( EFGGameplayTestFlags FilterFlags, TArray<TSubclassOf<UFGGameplayTest>>& out_gameplayTests );
	
	// Returns the default map we should use for running tests
	FORCEINLINE TSoftObjectPtr<UWorld> GetDefaultTestMap() const { return mDefaultTestMap; }
	FORCEINLINE FString GetDefaultTestMapOptions() const { return mDefaultTestMapOptions; }
protected:
	void OnGameplayTestStateChanged( UFGGameplayTest* gameplayTest ) const;
	
	void TickTestManufacturers() const;
	void TickTestGenerators() const;
	void TickPowerInfo() const;
	
	void TickGameplayTests( float dt );
	
	static void SaturateInventorySlot( class UFGInventoryComponent* inventoryComponent, int32 slotIndex, TSubclassOf<UFGItemDescriptor> itemDescriptor );
protected:
	// The default map on which tests should be run. Only used by Automation Testing Framework!
	UPROPERTY( Config )
	TSoftObjectPtr<UWorld> mDefaultTestMap;

	// The options that are passed to the map loaded for gameplay tests.
	UPROPERTY( Config )
	FString mDefaultTestMapOptions;
	
	UPROPERTY()
	UFGPowerInfoComponent* mCheatPowerSourcePowerInfo;
	UPROPERTY()
	UFGPowerInfoComponent* mCheatPowerSinkPowerInfo;

	UPROPERTY()
	UFGPowerConnectionComponent* mCheatPowerSourceConnection;
	UPROPERTY()
	UFGPowerConnectionComponent* mCheatPowerSinkConnection;
	
	UPROPERTY( Transient )
	TArray<FFGTestBuildableDescriptor_Manufacturer> mTestManufacturers;
	UPROPERTY( Transient )
	TArray<FFGTestBuildableDescriptor_GeneratorFuel> mTestGenerators;

	// List of running gameplay tests. This will include states in Running and Finished states.
	UPROPERTY( Transient )
	TArray<UFGGameplayTest*> mActiveGameplayTests;
};