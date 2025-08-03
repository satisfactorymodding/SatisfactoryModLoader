// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGIconDatabaseSubsystem.h"
#include "AkInstancedGeometryComponent.h"
#include "FGUseableInterface.h"

#include "FGElevatorTypes.generated.h"

class UTexture2D;

UCLASS( EditInlineNew )
class FACTORYGAME_API UFGBuildableElevatorSparseData : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* mHeightSegment1m;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* mHeightSegment4m;
	
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mTopMesh;
	
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mBottomMesh;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGElevatorCabin > mElevatorCabinClass;
	
	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mMaxElevatorHeight = 49900;

	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	AkInstancedMeshType AkMeshType = AkInstancedMeshType::CollisionMesh;
	
	// ------ Elevator Button Coloring Properties ----------

	// Default "illumination" to apply to buttons that are inactive
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	FLinearColor mInactiveStopColor = FLinearColor( 0.2f, 0.2f, 0.2f, 1.f );;
	
	// Color of the button indicating the Nex
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	FLinearColor mTargetStopColor = FLinearColor( 0.f, 1.f, 0.5f, 1.f );

	// color of a button that is queued but not the next stop
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	FLinearColor mQueuedStopColor = FLinearColor( 0.8f, 0.8f, 0.8f, 1.f );

	// The color of the current stop we are sitting at
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	FLinearColor mCurrentStopColor = FLinearColor( 0.5f, 1.f, 0.1f, 1.f );

	// Default "illumination" to apply to buttons that are inactive
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	FLinearColor mPowerOutColor = FLinearColor( 0.6f, 0.1f, 0.1f, 1.f );;
};

UENUM( BlueprintType )
enum class EElevatorDirection : uint8
{
	EED_Up,
	EED_Down,
	EED_Any
};

UENUM( BlueprintType )
enum class EElevatorState : uint8
{
	EES_NONE,
	EES_IdleAtFloor,
	EES_ArrivedAtFloor,
	EES_PauseBeforeDoorOpen,
	EES_WaitingAtFloor,
	EES_DoorsOpening,
	EES_DoorsClosing,
	EES_PauseBeforeMove,
	EES_Moving,
	EES_PausePowerOut,
	EES_SafetyStopping // For when power cuts
	
};

UENUM()
enum class EElevatorFloorStopQueuedStatus : uint8
{
	EEFSQS_None,
	EEFSQS_Current,
	EEFSQS_Next,
	EEFSQS_Queued
};


struct FACTORYGAME_API FElevatorDelegates
{
	// Delegates for the replication graph - Dependency actor hookup
	DECLARE_MULTICAST_DELEGATE_TwoParams( FOnElevatorDependantActorAdded, AActor*, AActor* );
	DECLARE_MULTICAST_DELEGATE_TwoParams( FOnElevatorDependantActorRemoved, AActor*, AActor* );

	inline static FOnElevatorDependantActorAdded OnElevatorDependantActorAdded = FElevatorDelegates::FOnElevatorDependantActorAdded();
	inline static FOnElevatorDependantActorRemoved OnElevatorDependantActorRemoved = FElevatorDelegates::FOnElevatorDependantActorRemoved();
};

UCLASS()
class FACTORYGAME_API UFGUseState_Elevator_MustTargetButton final : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_Elevator_MustTargetButton() : Super() { mIsUsableState = false; }
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FElevatorFloorStopInfo
{
	GENERATED_BODY()

	FElevatorFloorStopInfo() {};

	FORCEINLINE bool IsValid( bool hasAuthority ) const
	{
		// Clients may not have the Floor Stop replicated so we can't use that as part of the valid check
		if( hasAuthority )
		{
			return FloorStop != nullptr && Height >= 0.f;
		}

		return Height >= 0.f;
	}

	void GenerateName( bool makeRandom = false)
	{
		FloorName.Empty();
		if( makeRandom )
		{
			FloorName = "Floor_";
			FString randomSet = "qwertyuiopasdfghjklzxchklmn";
			int32 length = FMath::RandRange( 5, 10 );
			for( int32 i = 0; i < length; ++i)
			{
				FloorName.AppendChar( randomSet.GetCharArray()[ FMath::RandRange( 0, GetNum(randomSet) ) ]);
			}
		}
		else
		{
			FloorName = FString::Printf( L"%im", static_cast<int32>(Height / 100.f) );
		}
	}

	FORCEINLINE bool operator==( const FElevatorFloorStopInfo& other ) const { return this->FloorName.Equals( other.FloorName ) && this->IconId == other.IconId && this->IconColor == other.IconColor; }
	FORCEINLINE bool operator!=( const FElevatorFloorStopInfo& other ) const { return !( *this == other); }
	
	UPROPERTY( BlueprintReadOnly, SaveGame )
	class AFGBuildableElevatorFloorStop* FloorStop = nullptr;
	
	UPROPERTY( BlueprintReadOnly, SaveGame )
	FString FloorName;
	
	UPROPERTY( BlueprintReadOnly, SaveGame )
	int32 IconId = INDEX_NONE;

	UPROPERTY( BlueprintReadOnly, SaveGame )
	FLinearColor IconColor = FLinearColor::White;
	
	// Runtime helpful property for the local "height" position of this stop in elevator space
	UPROPERTY(BlueprintReadOnly)
	int32 Height = -1;

	UPROPERTY( Transient )
	TObjectPtr< UTexture2D > CachedIconTexture;
	
	static const FElevatorFloorStopInfo EmptyFloor;
};


