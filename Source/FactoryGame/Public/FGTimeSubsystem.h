#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGTimeSubsystem.generated.h"

#if WITH_EDITOR
DECLARE_MULTICAST_DELEGATE( FTimeOfDayUpdated );
#endif

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FNewDayDelegate, int32, newDayNr );

UCLASS( Blueprintable, abstract )
class FACTORYGAME_API AFGTimeOfDaySubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	enum
	{
		SecondsPerMinute = 60,
		MinutesPerHour = 60,
		MinutesPerDay = 1440,
		SecondsPerHour = 3600,
		SecondsPerDay = 86400
	};

	AFGTimeOfDaySubsystem();
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	virtual void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty, class FDefaultAllocator> & OutReplicatedProps) const override; // MODDING EDIT

	/** Set the value of daySeconds, most useful for editor preview */
	void SetDaySeconds( float daySeconds );

	/** Get how long a day is (in minutes) */
	FORCEINLINE float GetDayLength() const{ return mDayLengthMinutes; }

	/** Get how long a night is (in minutes) */
	FORCEINLINE float GetNightLength() const{ return mNightLengthMinutes; }

	/** Get the current time subsystem */
	UFUNCTION(BlueprintPure, Category="Time", DisplayName="GetTimeSubsystem", meta=(DefaultToSelf="worldContext"))
	static AFGTimeOfDaySubsystem* Get( UObject* worldContext );

	/** Get the time of day manager for the current world */
	static AFGTimeOfDaySubsystem* Get( UWorld* world );

	/** Get the (game) time of day as a normalized form (0->1, where 0 is 00:00 and 1 is 24:00) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetNormalizedTimeOfDay() const;

	/** Get a value of how much "day" it is (0 means night, 1 means that the sun is at it's highest, and 0.5 means that it's halfway to day) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetDayPct() const;

	/** Get a value of how much "night" it is (0 means day, 1 means that it's "in the middle of the night", and 0.5 means that it's halfway there) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetNightPct() const;

	/** Get the (game) time of day as a float in the range (0->24) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetTimeOfDayHours() const;

	/** How many (game) seconds has passed in our current day (0->86400) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetDaySeconds() const;

	/** How many (game) seconds has passed since our last minute (0->60) */
	UFUNCTION(BlueprintPure, Category = "Time")
	float GetSeconds() const;

	/** How many (game) minutes has passed in our current day (0->1440) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	int32 GetDayMinutes() const;

	/** How many (game) minutes has passed since our last hour (0->60) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	int32 GetMinutes() const;

	/** How many (game) hours has passed in our current day (0->24) */
	UFUNCTION( BlueprintPure, Category = "Time" )
	int32 GetHours() const; 

	/** How many (game) days has passed since we started the server */
	UFUNCTION( BlueprintPure, Category = "Time" )
	int32 GetPassedDays() const;

	/** Return true if it's daytime */
	UFUNCTION( BlueprintPure, Category = "Time" )
	bool IsDay() const;

	/** Return true if it's nighttime */
	UFUNCTION( BlueprintPure, Category = "Time" )
	bool IsNight() const;

	/** Get how many real seconds the daytime consists of */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetDaytimeSeconds() const;

	/** Get how many real seconds the nighttime consists of */
	UFUNCTION( BlueprintPure, Category = "Time" )
	float GetNighttimeSeconds() const;
	
	/** Force a net update to clients */
	void ForceReplicateTimeToClients();

	/** Sets multiplier for speed of time */
	UFUNCTION( BlueprintCallable, Category = "Time" )
	void SetTimeSpeedMultiplier( float multiplier );

#if WITH_EDITOR
	/** Accessor so we can hook ourself up on editor preview thingies */
	FTimeOfDayUpdated& GetTimeOfDayUpdatedDelegate(){ return mTimeOfDayUpdated; }
#endif
protected:
	/** Get the daytime speed multiplier used to calculate delta seconds */
	float GetDaytimeSpeed() const;

	/** Get the nighttime speed multiplier used to calculate delta seconds */
	float GetNighttimeSpeed() const;

	/** Called on client whenever we update the server time  */
	UFUNCTION()
	void OnRep_ReplicatedDaySeconds();

	/** Update the current time of day to be replicated to clients */
	UFUNCTION()
	void UpdateServerDaySeconds();
	
	/** Used internally for clients to to get the time syncronized to server-time */
	float GetAdjustedDaySeconds() const;

	/** Convert a "real" dt to a "game" dt */
	float GetGameDeltaTime( float dt ) const;
protected:
	/** How often (in seconds) we should synchronize the time of day with the server */
	UPROPERTY( EditDefaultsOnly, Category="Time Replication")
	float mSyncronizeTimeOfDayInterval;
	
	/**
	* In minutes, how long is the day part of a day? (normally 06-18).
	* that is, how many minutes should it take to for the time 06 -> 18 to pass?
	*/
	UPROPERTY( EditDefaultsOnly, Replicated, Category="Time")
	float mDayLengthMinutes;

	/** 
	 * In minutes, how long is the night part of a day? (normally 18-06).
	 * that is, how many minutes should it take to for the time 18 -> 06 to pass? 
	 */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Time" )
	float mNightLengthMinutes;

	/** In hours, when does the day start (if you want 06.45, enter 06.75) */
	UPROPERTY( EditDefaultsOnly, Replicated, Category="Time" )
	float mDayStartTime;

	/** In hours, when does the night start (if you want 19.10, enter 19.1666667) */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Time" )
	float mNightStartTime;

	/** Multiplier for speeding up the day/night cycle */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Time" )
	float mSpeedMultiplier;

	/** Difference in our time compared to the server */
	float mServerDaySecondsDelta;

	/**  How many seconds that has passed into our current day */
	UPROPERTY( SaveGame )
	float mDaySeconds;

	/** Written to by server, sends over the time that the server currently have */
	UPROPERTY(ReplicatedUsing=OnRep_ReplicatedDaySeconds)
	float mReplicatedDaySeconds;

	/** The current day that has passed */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumberOfPassedDays;

	/** Used for regularly update the server time */
	FTimerHandle mUpdateServerTimeTimer;

#if WITH_EDITORONLY_DATA
	// Notify so that other can hook up themself on it to be notified in the editor if the time of day is updated
	FTimeOfDayUpdated mTimeOfDayUpdated;
#endif

	/** Will only update the time if we set this to true */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Time" )
	bool mUpdateTime;
public:
	/** Server and Client | Called when a new day starts */
	UPROPERTY( BlueprintAssignable, Category = "Events|Time", DisplayName = "OnNewDay" )
	FNewDayDelegate mOnNewDayDelegate;

public:
	FORCEINLINE ~AFGTimeOfDaySubsystem() = default;
};