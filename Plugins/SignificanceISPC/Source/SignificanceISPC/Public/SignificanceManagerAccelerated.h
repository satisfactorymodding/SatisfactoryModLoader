// Copyright Ben de Hullu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SignificanceManager.h"
#include "SignificanceManagerAccelerated.generated.h"

DECLARE_STATS_GROUP( TEXT("SignificanceISPC"), STATGROUP_SignificanceManagerAccelerated, STATCAT_Advanced );

enum class SignificanceState : int8
{
	Unknown = -1,
	Insignificant = 0,
	Significant = 1
};


struct SIGNIFICANCEISPC_API FStaticAcceleratedManagedSignificanceInfo
{
	FVector3f CachedLocation;
	float SignificanceDistanceSquare;
	int8 NumTickStages;
	float TickRateResponseExp;

	int8 CurrentTickStage;	
	float CurrentSignificance;

	/* -1 for unknown, 0 false, 1 true. */
	SignificanceState bIsSignificant;
	SignificanceState bWasSignificant;
	SignificanceState bDidChangeTickState;

	bool bSupportsTickRateDilation;
 
	FStaticAcceleratedManagedSignificanceInfo( const FVector& InLocation, float InSignificanceDistance, bool bInHandlesTickRate = false, int32 InTickLevels = 0, float InTickExponent = 1) :
		SignificanceDistanceSquare(FMath::Square(InSignificanceDistance)),
		NumTickStages(InTickLevels),
		TickRateResponseExp(InTickExponent),
		CurrentTickStage(NumTickStages),
		CurrentSignificance(-1),
		bIsSignificant(SignificanceState::Unknown),
		bWasSignificant(SignificanceState::Unknown),
		bDidChangeTickState(SignificanceState::Unknown),
		bSupportsTickRateDilation(bInHandlesTickRate)
	{
		CachedLocation = FVector3f(InLocation);
	}
};

// TODO extend from the native version.
struct SIGNIFICANCEISPC_API FStaticAcceleratedManagedObjectInfo
{
	TWeakObjectPtr<UObject> ManagedObject;
	FName Tag;
	USignificanceManager::EPostSignificanceType Type;
	USignificanceManager::FManagedObjectPostSignificanceFunction PostSignificanceFunction;

	FStaticAcceleratedManagedObjectInfo(UObject* InObject, const FName& InTag, USignificanceManager::EPostSignificanceType InType, USignificanceManager::FManagedObjectPostSignificanceFunction InPostSignificanceFunction )
	{
		ManagedObject = InObject;
		Tag = InTag;
		Type = InType;
		PostSignificanceFunction = MoveTemp(InPostSignificanceFunction);
	}
};

struct SIGNIFICANCEISPC_API FServerSideAcceleratedManagedSignificanceInfo
{
	FVector3f CachedLocation;
	float SignificanceDistanceSquare;
	uint8 NumSignificance;
	SignificanceState bWasSignificant;

	FServerSideAcceleratedManagedSignificanceInfo(const FVector& InLocation, float InSignificanceDistance) :
		CachedLocation( FVector3f(InLocation) ),
		SignificanceDistanceSquare( FMath::Square(InSignificanceDistance) ),
		NumSignificance( 0 ),
		bWasSignificant(SignificanceState::Unknown)
	{
		
	}
};


/**
 * 
 */
UCLASS(Blueprintable)
class SIGNIFICANCEISPC_API USignificanceManagerAccelerated : public USignificanceManager
{
	GENERATED_BODY()
	
protected:
	// Begin USignificanceManager interface.
	virtual void RegisterObject(UObject* Object, FName Tag, FManagedObjectSignificanceFunction SignificanceFunction, EPostSignificanceType InPostSignificanceType, FManagedObjectPostSignificanceFunction InPostSignificanceFunction) override;
	virtual void Update(TArrayView<const FTransform> InViewpoints) override;
	// End USignificanceManager interface.

	bool IsEntrySignificant(FVector Location,float Range) const;
	virtual float GetSignificanceRange(UObject* Object) const	{ /* Implement in sub class*/ return 0;}
	virtual FVector GetObjectLocation(UObject* Object) const	{ /* Implement in sub class */ return FVector::ZeroVector; }
	virtual bool GetIsTickManaged(UObject* Object) const		{ /* Implement in sub class */ return false;}
	virtual int32 GetNumTickLevels(UObject* Object) const		{ /* Implement in sub class */ return -1;}
	virtual float GetTickExponent(UObject* Object) const		{ /* Implement in sub class */ return 1.f; }
	virtual void SetIsSignificance(UObject* Object, bool bState){ return; }
	
	/////////////////
	/* Client side.*/
	/////////////////
	
	/* Client side on significance loss, expecting a project based interface call to be implemented in subclass.*/
	virtual void OnSignificanceLoss(UObject* Object, EPostSignificanceType InPostSignificanceType);

	/* Client side on significance gain, expecting a project based interface call to be implemented in subclass.*/
	virtual void OnSignificanceGain(UObject* Object, EPostSignificanceType InPostSignificanceType);
	
	/* Tick rate dilation only for client side until there is a good case for server side too.*/
	virtual void OnSignificanceTickRateUpdate(UObject* Object, int32 TickLevel, int32 NumTickLevels);

	////////////////////////////////////////////
	// Begin Networked version
	////////////////////////////////////////////
	
	virtual float GetServerSignificanceNetworkRange(UObject* Object) const
	{ /* Implement in sub class*/
		return 0;
	}
	
	/* host AND client on significance gain, expecting a project based interface call to be implemented in subclass.*/
	virtual void OnServerSignificanceGain(UObject* Object, EPostSignificanceType InPostSignificanceType)
	{
		return;
	}
	
	/* host AND client on significance loss, expecting a project based interface call to be implemented in subclass.*/
	virtual void OnServerSignificanceLoss(UObject* Object, EPostSignificanceType InPostSignificanceType)
	{
		return;
	}
	
	////////////////////////////////////////////
	// End Networked version
	////////////////////////////////////////////

	void AddStaticEntryToArrays(const FVector& Location, const float& SignificanceRange );
	
public:
	virtual void RegisterStaticObject(UObject* Object, FName Tag, EPostSignificanceType InPostSignificanceType, FManagedObjectPostSignificanceFunction InPostSignificanceFunction);
	virtual void RemoveStaticObject(UObject* Object);

	/////////////////
	/* Client side.*/
	/////////////////
	/*	Arrays with aligned ID's, one contains the data for the ispc function to compute the relevancy, the other
	 *	contains the same implementation as native Unreal Engine's significance system. */
	TArray<FStaticAcceleratedManagedSignificanceInfo> StaticEntries;
	TArray<FStaticAcceleratedManagedObjectInfo*> StaticEntriesObjects;

	//////////////////////
	/* Networked version*/

	TArray<FVector3f> CachedViewPoints;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	int32 NumFramesForFullCycle = 10;

private:
	int32 LastHandledItem = 0;
	
public:
	void DumpSignificanceDebugData();
};
