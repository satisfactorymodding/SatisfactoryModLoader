// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/DataTable.h"
#include "FGResourceSinkSettings.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FResourceSinkRewardLevelsData : public FTableRowBase
{
	GENERATED_BODY()

	FResourceSinkRewardLevelsData() :
	RequiredPoints(0),
	NumRepeats(0)
	{}

	UPROPERTY( EditAnywhere )
	int64 RequiredPoints;

	UPROPERTY( EditAnywhere )
	int32 NumRepeats;

public:
	FORCEINLINE ~FResourceSinkRewardLevelsData() = default;
};

USTRUCT(BlueprintType)
struct FACTORYGAME_API FResourceSinkPointsData : public FTableRowBase
{
	GENERATED_BODY()

	FResourceSinkPointsData() : 
		ItemClass( nullptr ),
		Points( 0 ),
		OverriddenResourceSinkPoints(INDEX_NONE)
	{}

	bool operator==( const FResourceSinkPointsData &other ) const;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	int32 Points;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	int32 OverriddenResourceSinkPoints;


public:
	FORCEINLINE ~FResourceSinkPointsData() = default;
};

/**
 * 
 */
UCLASS( Blueprintable, config = Game, defaultconfig, meta = ( DisplayName = "Resource Sink" ) )
class FACTORYGAME_API UFGResourceSinkSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	FORCEINLINE static const UFGResourceSinkSettings* Get() { return GetDefault<UFGResourceSinkSettings>(); };

#if WITH_EDITOR

	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static int32 GetMaxPointsForItem() { return GetDefault<UFGResourceSinkSettings>()->mMaxPointsForItem; }

	UFUNCTION( BlueprintCallable, Category = "Settings" )
	static void SetMaxPointsForItem( int32 maxPointsForItem );

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static FString GetPointCalculationExpression() { return GetDefault<UFGResourceSinkSettings>()->mPointCalculationExpression; }

	UFUNCTION( BlueprintCallable, Category = "Settings" )
	static void SetPointCalculationExpression( FString pointCalculationExpression );

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static int32 GetNumRepeatsPerLevel() { return GetDefault<UFGResourceSinkSettings>()->mDefaultNumRepeats; }

	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetNumRepeatsPerLevel( int32 numRepeats );

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static int32 GetNumLevels() { return GetDefault<UFGResourceSinkSettings>()->mNumLevels; }

	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetNumLevels( int32 numLevels );

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSoftObjectPtr< class UDataTable > GetPointsDataTable() { return GetDefault<UFGResourceSinkSettings>()->mPointsDataTable; }

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSoftObjectPtr< class UDataTable > GetRewardLevelsDataTable() { return GetDefault<UFGResourceSinkSettings>()->mRewardLevelsDataTable; }

#endif

public:

	UPROPERTY( EditAnywhere, config, Category = "Data table" )
	TSoftObjectPtr< class UDataTable > mPointsDataTable;

	UPROPERTY( EditAnywhere, config, Category = "Data table" )
	TSoftObjectPtr< class UDataTable > mRewardLevelsDataTable;

	UPROPERTY( VisibleAnywhere, config, Category = "Settings", meta = ( ToolTip = "The maximum value an item can be worth, 0 = No cap" ) )
	int32 mMaxPointsForItem;

	UPROPERTY( VisibleAnywhere, config, Category = "Settings", meta = ( ToolTip = "The math expression used to calculate points for items" ) )
	FString mPointCalculationExpression;
	
	UPROPERTY( EditAnywhere, config, Category = "Coupons", meta = ( ToolTip = "The class that we use as coupon" ) )
	TSoftClassPtr< class UFGItemDescriptor > mCouponClass;

	UPROPERTY( EditAnywhere, config, Category = "History", meta = ( ToolTip = "The number of history points we save for the global resource sink history" ) )
	int32 mNumGlobalHistoryPoints;

	UPROPERTY( EditAnywhere, config, Category = "Failed sink messages", meta = ( ToolTip = "Play message when these items fail to sink" ) )
	TMap<TSubclassOf<class UFGItemDescriptor>, TSubclassOf<class UFGMessageBase>> mFailedSinkMessages;

	UPROPERTY( EditAnywhere, config, Category = "Failed sink messages", meta = ( ToolTip = "Play this message when items fail to sink that are not mapped to a message in FailedSinkMessages" ) )
	TSubclassOf<class UFGMessageBase> mGenericFailedSinkMessage;

	UPROPERTY( EditAnywhere, config, Category = "Cyber coupon", meta = ( ToolTip = "The schematic to unlock when sinking a coupon" ) )
	TSubclassOf<class UFGSchematic> mCyberCouponSchematic;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Points = mMulitplier * level^mExponent" ) )
	float mMultiplier;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Points = mMulitplier * level^mExponent" ) )
	float mExponent;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Number of levels" ) )
	int32 mNumLevels;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Number of repeats per each level" ) )
	int32 mDefaultNumRepeats;


public:
	FORCEINLINE ~UFGResourceSinkSettings() = default;
};
