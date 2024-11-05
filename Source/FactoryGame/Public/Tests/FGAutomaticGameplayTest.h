// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGGameplayTest.h"
#include "Misc/AutomationTest.h"
#include "Templates/SubclassOf.h"
#include "UObject/GCObject.h"

enum class EFGGameplayTestFlags : uint8;
class UFGGameplayTest;

#if WITH_AUTOMATION_TESTS

// Runs a series of Automation Gameplay Tests based on the provided Filter flags
class FACTORYGAME_API FFGRunGameplayAutomationTests : public FAutomationTestBase
{
	EFGGameplayTestFlags FilterTestFlags;
public:
	FFGRunGameplayAutomationTests( const FString& InName, EFGGameplayTestFlags InFilterTestFlags );

	virtual uint32 GetTestFlags() const override;
	virtual bool IsStressTest() const;
	virtual uint32 GetRequiredDeviceNum() const override;
	virtual FString GetTestSourceFileName() const override;
	virtual int32 GetTestSourceFileLine() const override;
protected:
	virtual void GetTests(TArray<FString>& OutBeautifiedNames, TArray <FString>& OutTestCommands) const override;
	virtual bool RunTest(const FString& Parameters) override;
	virtual FString GetBeautifiedTestName() const override;
};

class FACTORYGAME_API FFGRunGameplayTestCommand : public IAutomationLatentCommand, public FGCObject
{
	TObjectPtr<UClass> GameplayTest{};
	TObjectPtr<UFGGameplayTest> RunningTestInstance{};
	TOptional<FFGGameplayTestResult> CachedTestResult{};
	bool bInitializedTest{false};
public:
	FFGRunGameplayTestCommand( TSubclassOf<UFGGameplayTest> InGameplayTest );

	virtual bool Update() override;

	// Begin FGCObject Interface
	virtual FString GetReferencerName() const override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End FGCObject Interface
protected:
	virtual bool InitializeGameplayTest();
	virtual void FinishGameplayTest();
	
	static EAutomationEventType MessageLevelToEventType( EFGGameplayTestMessageLevel InLevel );
	static FString TestResultToFriendlyName( EFGGameplayTestResult InResult );
	virtual void OnGameplayTestStateChanged( UFGGameplayTest* InGameplayTest );
};

#endif