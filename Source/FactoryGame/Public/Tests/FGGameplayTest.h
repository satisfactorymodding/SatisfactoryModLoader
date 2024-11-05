// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/SoftObjectPtr.h"
#include "IncludeInBuild.h"
#include "FGGameplayTest.generated.h"

class FJsonObject;
class AFGTestManager;
class UFGGameplayTest;
class AActor;

DECLARE_MULTICAST_DELEGATE_OneParam( FFGOnGameplayTestStateChanged, UFGGameplayTest* );

UENUM( BlueprintType, meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EFGGameplayTestFlags : uint8
{
	None = 0x00 UMETA( DisplayName = "None" ),
	// Automation tests are automatically run by FGAutomationGameplayTest with no filters specified
	AutomationTest = 0x01 UMETA( DisplayName = "Automation Test" )
};
ENUM_CLASS_FLAGS( EFGGameplayTestFlags );

// Lifecycle of a gameplay test object
UENUM( BlueprintType )
enum class EFGGameplayTestState : uint8
{
	None UMETA( DisplayName = "Uninitialized" ),
	Running UMETA( DisplayName = "Running" ),
	Finished UMETA( DisplayName = "Finished" ),
	Ended UMETA( DisplayName = "Ended" )
};

// Possible results of the gameplay test
UENUM( BlueprintType )
enum class EFGGameplayTestResult : uint8
{
	Undetermined UMETA( DisplayName = "Undetermined" ),
	Passed UMETA( DisplayName = "Pass" ),
	Failed UMETA( DisplayName = "Fail" ),
	TimedOut UMETA( DisplayName = "Fail (timed out)" )
};

// Levels of messages gameplay tests can emit
UENUM( BlueprintType )
enum class EFGGameplayTestMessageLevel : uint8
{
	Info UMETA( DisplayName = "Info" ),
	Warning UMETA( DisplayName = "Warning" ),
	Error UMETA( DisplayName = "Error" )
};

// A single message the test has emitted.
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGGameplayTestMessage
{
	GENERATED_BODY()

	// Level of importance of this message
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Gameplay Test" )
	EFGGameplayTestMessageLevel Level;

	// Message in question
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Gameplay Test" )
	FText Message;

	// Context the message was emitted in. For blueprints, that would be the name of the function, for C++ code, it has to pass it in manually
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Gameplay Test" )
	FString Context;
};

// Describes a result of running a gameplay test
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGGameplayTestResult
{
	GENERATED_BODY()

	// The result of the text
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Gameplay Test" )
	EFGGameplayTestResult TestResult{};

	// Messages emitted by the test.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Gameplay Test" )
	TArray<FFGGameplayTestMessage> Messages;

	// Custom metadata passed around the system.
	TSharedPtr<FJsonObject> Metadata;

	// The time it took to execute the test
	float TestExecutionTime{0.0f};

	FFGGameplayTestResult();
};

/**
 * Gameplay test is a class that describes an environment in which gameplay test is performed,
 * determines it's results and rules for their interpretation, and handles
 * the progression of the test as the time passes.
 *
 * Gameplay tests are ran through FGTestManager and their lifetime is managed by it automatically
 */
UCLASS( Abstract, Blueprintable, Within = FGTestManager )
class FACTORYGAME_API UFGGameplayTest : public UObject
{
	GENERATED_BODY()
public:
	UFGGameplayTest();
	
	// Begin UObject interface
	virtual UWorld* GetWorld() const override;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	// End UObject interface

	// Returns the test manager owning this test
	UFUNCTION( BlueprintPure, Category = "Gameplay Test" )
	AFGTestManager* GetTestManager() const;

	// Returns the current state of the test
	UFUNCTION( BlueprintPure, Category = "Gameplay Test" )
	EFGGameplayTestState GetGameplayTestState() const;

	// Returns the results of running the test. Only available when the test is past the finished state
	UFUNCTION( BlueprintPure, Category = "Gameplay Test" )
	FFGGameplayTestResult GetGameplayTestResult() const;
	
	/**
	 * Adds the actor to the list of actors owned by this test. Such actors will be automatically cleaned up when the test ends.
	 * Buildables spawned by the test via FGTestBlueprintFunctionLibrary are automatically added there when the functions are called in the context of Start Test/End Test/Tick Test
	 * In all other cases, you need to manually add them there if you want them gone by the time the test ends
	 */
	UFUNCTION( BlueprintCallable, Category = "Gameplay Test" )
	void AddTestActor( AActor* testActor );

	// Makes the test transition to the next state. This will catch invalid transitions and assert on them.
	void Internal_TransitionToState( EFGGameplayTestState newState );

	// Dispatched by the test manager on all running tests to allow them to update their state
	void Internal_Tick( float dt );

	// Used to draw debug information about the running test instance.
	virtual void DrawDebug( UCanvas* canvas );

	/**
	 * Adds the message to the output of this test.
	 * Fully qualified form, do not use directly, use AddInfo/AddWarning/AddError instead.
	 * This will automatically fetch the Context from the call stack if you do not provide one.
	 */
	UFUNCTION( BlueprintCallable, CustomThunk, Category = "Gameplay Test" )
	void AddMessage( EFGGameplayTestMessageLevel messageLevel, const FText& message, const FString& context = TEXT(""), int32 stackOffset = 0 );

	// Adds info message to the test output log. Info messages do not fail a test.
	UFUNCTION( BlueprintCallable, CustomThunk, Category = "Gameplay Test" )
	void AddInfo( const FText& message, const FString& context = TEXT(""), int32 stackOffset = 0 );

	// Adds warning to the output of the test. Warnings will not fail the test.
	UFUNCTION( BlueprintCallable, CustomThunk, Category = "Gameplay Test" )
	void AddWarning( const FText& message, const FString& context = TEXT(""), int32 stackOffset = 0 );

	// Adds the error to the output of the test. Errors in the test output will automatically fail the test, regardless of the outcome
	UFUNCTION( BlueprintCallable, CustomThunk, Category = "Gameplay Test" )
	void AddError( const FText& message, const FString& context = TEXT(""), int32 stackOffset = 0 );

	DECLARE_FUNCTION( execAddMessage );
	DECLARE_FUNCTION( execAddInfo );
	DECLARE_FUNCTION( execAddWarning );
	DECLARE_FUNCTION( execAddError );
public:
	// The gameplay test running at this particular moment of time. Only valid during the calls to Test functions on GameThread
	static UFGGameplayTest* ActiveGameplayTest;

	// User friendly name of the test
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Test" )
	FText mDisplayName;

	// Maximum duration of the test above which the test will be considered failed.
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Test" )
	float mMaximumTestDuration;

	// Flags to set on the test.
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Test",  meta = ( Bitmask, BitmaskEnum = "/Script/FactoryGame.EFGGameplayTestFlags") )
	int32 GameplayTestFlags;

	// Allows overriding the map that will be loaded for this test when AutomationTool is running it
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Test", AdvancedDisplay )
	TSoftObjectPtr<UWorld> TestMapOverride;

	// Allows overriding the options passed to the map
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay Test", AdvancedDisplay )
	FString TestMapOptionsOverride;

#if WITH_EDITORONLY_DATA
	/** Allows removing the test from the packaged builds based on the value. */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category="Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif
	
	// This delegate is fired when the state of the gameplay test changes.
	FFGOnGameplayTestStateChanged OnGameplayTestChanged;
	
protected:
	static FString CaptureStackTraceContext( int32 StackOffset = 0 );
	static FString CaptureScriptContext( const FFrame& Stack );
	static FColor GetDebugColorForLevel( EFGGameplayTestMessageLevel level );
	
	// Called when the test is started by the test manager
	virtual void OnTestStarted();
	// Called when the test has been finished but has not been destroyed yet. Gives time to add additional metadata from actors that are still alive.
	virtual void OnTestFinished();
	// Called when the test has finished and is about to be destroyed by the test manager
	virtual void OnTestEnded();

	// Called every tick when the test is active.
	virtual void TickRunningTest( float dt );
	
	// Called when the test is started by the test manager
	UFUNCTION( BlueprintImplementableEvent, Category = "Gameplay Test", DisplayName = "Start Test" )
	void K2_OnTestStarted();
	
	// Called when the test has finished and is about to be destroyed by the test manager
    UFUNCTION( BlueprintImplementableEvent, Category = "Gameplay Test", DisplayName = "End Test" )
	void K2_OnTestEnded();

	// Called when the test has been finished but has not been destroyed yet. Gives time to add additional metadata from actors that are still alive.
	UFUNCTION( BlueprintImplementableEvent, Category = "Gameplay Test", DisplayName = "End Test" )
	void K2_OnTestFinished( EFGGameplayTestResult testResult );

	// Called every tick when the test is active.
	UFUNCTION( BlueprintImplementableEvent, Category = "Gameplay Test", DisplayName = "Tick Test" )
	void K2_TickRunningTest( float dt );

	UFUNCTION( BlueprintImplementableEvent, Category = "Gameplay Test", DisplayName = "Draw Debug" )
	void K2_DrawDebug( UCanvas* canvas );
	
	/**
	 * Finishes running this test with the provided reason.
	 * Note that the status provided here might be overwritten if the Test has Succeeded, but it has reported Errors.
	 * The test object will be destroyed shortly after.
	 */
	UFUNCTION( BlueprintCallable, Category = "Gameplay Test" )
	void FinishTest( EFGGameplayTestResult testResult );

	// Adds metadata to this test instance. The metadata will be included into the test results
	UFUNCTION( BlueprintCallable, Category = "Gameplay Test" )
	void AddTestMetadata( const FString& metadataKey, const FString& metadataValue );

	void KillTestSpawnedActors();
	bool HasAnyErrorMessagesInLog() const;

	// Array of actors owned by this gameplay test instance, the actors in question will be automatically removed when the test is finished
	UPROPERTY( Transient, VisibleInstanceOnly, Category = "Gameplay Test" )
	TArray<AActor*> mTestOwnedActors;

	// Amount of time since this test has been started
	float mCurrentTimeSinceTestStart;
	float mTimeSinceTestFinished;
	
	// Current state of the test
	UPROPERTY( Transient, VisibleInstanceOnly, Category = "Gameplay Test" )
	EFGGameplayTestState mTestState;

	// Result of the test, only accessible if the test has been finished.
	UPROPERTY( Transient, VisibleInstanceOnly, Category = "Gameplay Test" )
	FFGGameplayTestResult mTestResult;
};