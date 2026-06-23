// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "WorldCollision.h"
#include "FGSubsystem.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"
#include "FGLocalAudioContextSubsystem.generated.h"

/*
 * This subsystem handles dynamic audio reverb effects based on the player's local acoustic context.
 * 
 * - The class calculates the acoustic properties of the player's environment by performing raycasts both horizontally and vertically around the player’s location (3 per plane).
 * - The `CalculateAzimuthPlane` method computes an average width across multiple raycasts in the horizontal plane, and the `CalculateZenithPlane` method computes an average height across vertical raycasts.
 * - These computed values are used to dynamically update the Wwise sound engine’s RTPC (Real-Time Parameter Controls) for local acoustic context width and height, ensuring that in-game sound reverberation adapts to the player’s surroundings.
 * 
 * The subsystem maintains short- and long-term histories for both width and height values, which help smooth out abrupt changes in the local environment’s geometry.
 * Debugging options allow developers to visualize raycasts, hit locations, and calculated distances in real time.
 */

class UAkAudioEvent;

struct AudioHitInfo
{
	FVector HitLocation;
	FVector OriginLocation;

	float Distance;

	TWeakObjectPtr< UPhysicalMaterial > PhysMaterial;
};

UCLASS( config = Game, Blueprintable, defaultconfig, meta = ( DisplayName = "Local Audio Context Subsystem" ) )
class FACTORYGAME_API AFGLocalAudioContextSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFGLocalAudioContextSubsystem();
	static AFGLocalAudioContextSubsystem* Get( class UWorld* world );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	const TArray<AudioHitInfo> & GetAngularHits() const { return AngularHitPointsHistory; }
	const TArray<bool> & GetAngularHistory() const { return AngularHistory; }
	const TMap< TSoftObjectPtr< UPhysicalMaterial >, TObjectPtr<class UAkSwitchValue> > & GetMaterialTypeToAkSwitchMap() const { return mMaterialTypeToAkSwitchMap; }
	TWeakObjectPtr<UPhysicalMaterial> GetMostHitMaterial() const { return MostHitMaterial; }
	
	float GetIsInsideFactor() const { return mPreviousIsInside; }
	float GetHeightFactor() const { return mPreviousRTPCHeight; }
	
	void TickHorizontalRTPC();
	void TickVerticalRTPC();
	void TickAngularRTPC();
	void TickSlapbackRTPC();
	void TickMaterialTypeRTPC();

	void SetActiveChannelsNumberRTPC();

	float CalculateAzimuthPlane();
	float CalculateZenithPlane();
	void CalculateAngularPlane( float VerticalPlaneHeight );
	void CalculateWallPlanes( float& AveragedLeftPlane, float& AveragedRightPlane );

	//Performs 3 evenly placed raycasts across horizontal plane, and returns averaged width of 2 smallest one
	float PerformHorizontalPhase( int32 OffsetDegree, TArray< AudioHitInfo >& HitPoints );

	//Perform 3 evenly placed raycasts across vertical plane. Return height if all of them agree with each other, otherwise return -1
	void PerformVerticalPhase( float& out_resultedAverageHeight, TWeakObjectPtr< UPhysicalMaterial >& out_mostHitMaterial );

	//Perform 3 evenly placed raycasts across angular plane. Returns largest distance from the casts
	void PerformAngularPhase( float OffsetZ );

	void OnHorizontalTraceCompleted( const FTraceHandle& Handle, FTraceDatum& Data );
	void OnVerticalTraceCompleted( const FTraceHandle& Handle, FTraceDatum& Data );
	void OnAngularTraceCompleted( const FTraceHandle& Handle, FTraceDatum& Data );

	static TWeakObjectPtr< UPhysicalMaterial > FindMostHitMaterial( const TArray< TWeakObjectPtr< UPhysicalMaterial > >& MaterialsHistory );

	static void MakeAsyncAudioRaycast( UWorld* World, const FVector& Start, const FVector& End, const FTraceDelegate& Delegate);

	UFUNCTION(BlueprintPure, Category = "Audio")
	static UAkAudioEvent* ResolveSoftAudioReference(TSoftObjectPtr< UAkAudioEvent> InputSoftObject);
	
public:
	UPROPERTY( EditDefaultsOnly, Category = Audio )
	TObjectPtr<class UAkRtpc> mLocalAcousticContextHeight = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = Audio )
	TObjectPtr<class UAkRtpc> mLocalAcousticContextWidth = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = Audio )
	TObjectPtr<class UAkRtpc> mSlapbackLeft = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = Audio )
	TObjectPtr<class UAkRtpc> mSlapbackRight = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = Audio )
	TObjectPtr<class UAkRtpc> mIsInside = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = Audio )
	TObjectPtr<class UAkRtpc> mCurrentChannelNumber = nullptr;
	
	//Material type to AK state value mapping
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TMap< TSoftObjectPtr< UPhysicalMaterial >, TObjectPtr<class UAkStateValue> > mMaterialTypeToAkStateMap;

	//Height Material type to AK state value mapping. It should be a separate set because of wwise limitations
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TMap< TSoftObjectPtr< UPhysicalMaterial >, TObjectPtr<class UAkStateValue> > mHeightMaterialTypeToAkStateMap;
	
	//Default ak state value to set when no material type is found
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TObjectPtr<class UAkStateValue> mDefaultMaterialTypeState = nullptr;

	//Default ak state value to set when no material type is found
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TObjectPtr<class UAkStateValue> mDefaultHeightMaterialTypeState = nullptr;

	//Default ak state value to set when no material type is found
    UPROPERTY( EditDefaultsOnly, Category = "Audio" )
    TObjectPtr<class UAkStateValue> mNoHitHeightMaterialTypeState = nullptr;
	
	//Material type to AK switch value mapping
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TMap< TSoftObjectPtr< UPhysicalMaterial >, TObjectPtr<class UAkSwitchValue> > mMaterialTypeToAkSwitchMap;

	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TObjectPtr<class UAkSwitchValue> mDefaultMaterialTypeSwitch = nullptr;
	
	//Default states per group
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	TMap< FString, TObjectPtr<class UAkStateValue> > mDefaultStatesPerGroup;

protected:
	friend class FGLocalAudioContextDebugWindow;

	AkUInt32 MaterialStateGroupLacMaterialType { 0 };
	AkUInt32 MaterialStateGroupLacHeightMaterialType { 0 };
	
	// Frame stats
	int32 ActualFrameNum{0}; // Frame number in [0-15] range, always updated
	int32 ProcessingFrameNum{0}; // Frame number in [0-15] range, updated only during processing
	int32 CurrentPhaseNum{0};

	FVector mCurrentLocation{FVector::ZeroVector};

	// History of averaged width (fed by PerformHorizontalPhase)
	TArray<float> ShortHistory; // 4-element history of averaged width (fed by each phase separately)
	TArray<float> LongHistory; // 16-frame history of averaged width (fed by ShortHistory combined value)
	TArray<AudioHitInfo> LongHistoryHitPoints;

	// History of height (fed by PerformVerticalPhase)
	TArray<float> HeightHistory; // 4-element history of height (fed by each phase)
	TArray<TWeakObjectPtr<UPhysicalMaterial>> HeightMaterialsHistory;

	// Angular
	TArray<bool> AngularHistory;
	TArray<AudioHitInfo> AngularHitPointsHistory;
	TArray<TWeakObjectPtr<UPhysicalMaterial>> AngularMaterialsHistory;
	int32 AngularCounter{0};

	//Most hit material around the player
	TWeakObjectPtr<UPhysicalMaterial> MostHitMaterial;

	// Most hit vertical material
	TWeakObjectPtr<UPhysicalMaterial> MostHitVerticalMaterial;

	UPROPERTY()
	TObjectPtr<UAkStateValue> MostHitMaterialState { nullptr };

	UPROPERTY()
	TObjectPtr<UAkStateValue> MostHitVerticalMaterialState { nullptr };
	
	float mPreviousRTPCWidth{0.0f};
	float mPreviousRTPCHeight{0.0f};
	float mPreviousSlapbackLeft{0.0f};
	float mPreviousSlapbackRight{0.0f};
	float mPreviousIsInside{0.0f};

	TArray<AudioHitInfo> mHorizontalHitPoints;
	TArray<AudioHitInfo> mVerticalHitPoints;
	TArray<AudioHitInfo> mAngularHitPoints;

	FTraceDelegate mTraceDelegateHorizontal;
	FTraceDelegate mTraceDelegateVertical;
	FTraceDelegate mTraceDelegateAngular;
};