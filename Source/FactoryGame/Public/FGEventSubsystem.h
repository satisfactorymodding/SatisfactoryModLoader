// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGInventoryComponent.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "UObject/ObjectMacros.h"

#include "FGEventSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FCalendarSlotUnlocked, int32, slot, bool, randomUnlock, UFGUnlock*, unlock );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FCalendarOpenEvent, class AFGCharacterPlayer*, player, class AFGBuildableCalendar*, calendar, bool, firstTimeOpening );

UENUM( BlueprintType )
enum class EEvents : uint8
{
	EV_None						UMETA( DisplayName = "None"),
	
	EV_Christmas				UMETA( DisplayName = "Christmas"),
	EV_Birthday					UMETA( DisplayName = "Satisfactory Birthday"),
	EV_CSSBirthday				UMETA( DisplayName = "CSS Birthday"),
	EV_FirstOfApril				UMETA( DisplayName = "First Of April"),

	// New events above this line
	EV_MAX						UMETA( Hidden )
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

USTRUCT()
struct FACTORYGAME_API FPlayerStateSetWrapper
{
	GENERATED_BODY()
	
	UPROPERTY( SaveGame )
	TSet< class AFGPlayerState* > PlayerStates;
};

/**
 * @todo Please comment me
 * No
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGEventSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	AFGEventSubsystem();

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	//~ End AActor interface

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	static AFGEventSubsystem* Get( UWorld* world );
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events", meta = ( DefaultToSelf = "worldContext" ) )
	static AFGEventSubsystem* GetEventSubsystem( UObject* worldContext );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events" )
	const TArray< EEvents >& GetCurrentEvents() const;

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events" )
	bool IsEventActive( EEvents event ) const { return GetCurrentEvents().Contains( event ); }

	const FFGEventData* GetEventData( EEvents event ) const { return mEvents.Find( event ); }

	void StoreCurrentCalendarData( const FCalendarData& calendarData );
	void StoreCalendarData( TSubclassOf<class UFGCalendarRewards> calendarRewardClass, const FCalendarData& calendarData );
	const FCalendarData* GetStoredCalendarData( TSubclassOf<class UFGCalendarRewards> calendarRewardClass ) const;
	const FCalendarData* GetStoredCurrentCalendarData() const;

	FCalendarData* GetStoredCalendarData( TSubclassOf<class UFGCalendarRewards> calendarRewardClass );
	FCalendarData* GetStoredCurrentCalendarData();
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events|Calendar" )
	bool CanOpenCalendarSlot( EEvents event, int32 dayNumber );

	void OnPlayerOpenedCalendar( class AFGCharacterPlayer* player, class AFGBuildableCalendar* calendar );

	const TSet< class AFGPlayerState* >& GetPlayersThatHaveSeenCalendar( TSubclassOf< UFGCalendarRewards > calendar );
	const TSet< class AFGPlayerState* >& GetPlayersThatHaveSeenCurrentCalendar();

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events|Calendar" )
	TSubclassOf< UFGCalendarRewards > GetCalendarRewardsClass() const { return mCalendarRewardsClass; }

	/** Returns the gift rain spawner for the specified event. Will be NULL on clients or if event isn't active. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events" )
	class AFGGiftRainSpawner* GetGiftRainSpawnerForEvent( EEvents event ) const;

	/** Returns a random active gift rain spawner. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Events" )
	class AFGGiftRainSpawner* GetRandomActiveGiftRainSpawner() const;

	static bool GetOverridenEventDateTime( EEvents event, FDateTime& out_OverriddenDateTime );

	bool ShouldRunEvent( const FSimpleDate& Begin, const FSimpleDate& End, const FDateTime& now );

	TSubclassOf<class AActor> GetCalendarClassForCurrentEvent();
	TSubclassOf<class AFGBuildable> GetHubMiniGameClassForCurrentEvent();

protected:
	/** Called from beginplay for each active event. */
	virtual void OnBeginEvent_Native( EEvents event);
	
	/** Called from beginplay for each active event. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Events" )
	void OnBeginEvent( EEvents event );

private:
	void CacheActiveEvents();
	
public:
	UPROPERTY( Replicated )
	TArray< EEvents > mCurrentEvents;

	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Events|Calendar" )
	FCalendarSlotUnlocked mOnCalendarSlotUnlocked;

	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Events|Calendar" )
	FCalendarOpenEvent mOnCalendarOpenedByPlayer;
	
private:
	/* Map with dates per event. */
	UPROPERTY( EditDefaultsOnly )
	TMap< EEvents, FFGEventData > mEvents;

	/** The calendar rewards class we use to get rewards for slots in the calendar. // TODO: This should be mapped per event */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< UFGCalendarRewards > mCalendarRewardsClass;

	/** What gift spawner class to use for an event, if any. */
	UPROPERTY( EditDefaultsOnly )
	TMap< EEvents, TSubclassOf< class AFGGiftRainSpawner > > mEventGiftSpawnerClasses;

	UPROPERTY( EditDefaultsOnly, meta=(AllowedClasses=FGBuildableCalendar) )
	TMap< EEvents, TSubclassOf<class AActor> > mBuildableCalendarClass;

	UPROPERTY( EditDefaultsOnly )
	TMap< EEvents, TSubclassOf<class AFGBuildable> > mHubMiniGameClass;

	UPROPERTY( SaveGame )
	TMap< EEvents, FCalendarData > mStoredCalendarData; // 2020 Stored just in case we need it -K2
	UPROPERTY( SaveGame )
	TMap< TSubclassOf<class UFGCalendarRewards>, FCalendarData > mCalendarData; // 2021 and forward. Should handle as many calendars as we can think of.

	UPROPERTY( SaveGame )
	TMap< TSubclassOf<class UFGCalendarRewards>, FPlayerStateSetWrapper > mCalendarsOpenedByPlayers;

	/** Map of active gift rain spawners. */
	UPROPERTY()
	TMap< EEvents, class AFGGiftRainSpawner* > mActiveGiftRainSpawners;
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
