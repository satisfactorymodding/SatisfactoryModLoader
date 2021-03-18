// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "UObject/ObjectMacros.h"
#include "FGSaveInterface.h"
#include "Engine/DeveloperSettings.h"
#include "FGInventoryComponent.h"

#include "FGEventSubsystem.generated.h"

UENUM( BlueprintType )
enum class EEvents : uint8
{
	EV_None = 0						UMETA( DisplayName = "None"),
	EV_Christmas = 1				UMETA( DisplayName = "Christmas"),
	EV_Birthday = 2					UMETA( DisplayName = "Satisfactory Birthday"),
	EV_CSSBirthday = 3				UMETA( DisplayName = "CSS Birthday"),
	EV_FirstOfApril = 4				UMETA( DisplayName = "First Of April"),
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSimpleDate
{
	GENERATED_BODY()	
	/* Does it begin in current year, but end in next? this should be on 1.*/
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Meta = ( ClampMin = 0, ClampMax = 1 ) )
	int32 mYearOffset;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Meta = ( ClampMin = 1, ClampMax = 12 ) )
	int32 mMonth;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Meta = ( ClampMin = 1, ClampMax = 31 ) ) 
	int32 mDay;	

	FDateTime GetDateTime() const
	{
		return FDateTime(FDateTime::Now().GetYear() + mYearOffset, mMonth, mDay);
	}

	FSimpleDate()
	{
		mYearOffset = 0;
		mMonth = 1;
		mDay = 1;
	}
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGEventData
{
	GENERATED_BODY()
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FSimpleDate mStartDate;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FSimpleDate mEndDate;

	FFGEventData()
	{
		mStartDate = FSimpleDate();
		mEndDate = FSimpleDate();
	}
};

USTRUCT()
struct FACTORYGAME_API FCalendarData
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame )
	TArray< FInventoryStack > InventoryStacks;

	UPROPERTY( SaveGame )
	TArray<int32> OpenedSlotsInCalendar;

	UPROPERTY( SaveGame )
	TMap< int32, int32 > InventoryIndexToRandomRewardIndexMapping;

	FCalendarData(){}
};

/**
 * @todo Please comment me
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGEventSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	AFGEventSubsystem();

	//~ Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	//~ End AActor interface

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	static AFGEventSubsystem* Get( UWorld* world );
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events", meta = ( DefaultToSelf = "worldContext" ) )
	static AFGEventSubsystem* GetEventSubsystem( UObject* worldContext );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events" )
	TArray< EEvents > GetCurrentEvents();

	void StoreCalendarDataForEvent( EEvents event, FCalendarData calendarData );
	bool GetStoredCalendarDataForEvent( EEvents event, FCalendarData& out_calendarData );

	static bool GetOverridenEventDateTime( EEvents event, FDateTime& out_OverriddenDateTime );

	bool ShouldRunEvent( const FSimpleDate& Begin, const FSimpleDate& End, const FDateTime& now );
	
public:
	UPROPERTY( Replicated )
	TArray< EEvents > mCurrentEvents;
	
private:
	/* Map with dates per event. */
	UPROPERTY( EditDefaultsOnly )
	TMap< EEvents, FFGEventData > mEvents;

	UPROPERTY()
	bool bIsReplicated;

	UPROPERTY( SaveGame )
	TMap< EEvents, FCalendarData > mStoredCalendarData;
};

UCLASS( config = EditorPerProjectUserSettings, meta = ( DisplayName = "Satisfactory Local Event settings" ) )
class FACTORYGAME_API UFGEventDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY( EditDefaultsOnly, Config )
	bool mDisableEvents;
	
	UPROPERTY( EditDefaultsOnly, Config )
	EEvents mOverwrittenEvent;
	
public:
	static bool ShouldOverwriteEvent()
	{
		return !GetDefault< UFGEventDeveloperSettings >()->mDisableEvents && GetDefault< UFGEventDeveloperSettings >()->mOverwrittenEvent != EEvents::EV_None ;
	}
	
	static EEvents GetCurrentOverwrittenEvent()
	{
		EEvents result = EEvents::EV_None;
		if ( ShouldOverwriteEvent() )
		{
			result = GetDefault< UFGEventDeveloperSettings >()->mOverwrittenEvent;
		}
		return result;
	}
};
