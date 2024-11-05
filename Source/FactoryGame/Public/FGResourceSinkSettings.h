// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/DataTable.h"
#include "FGResourceSinkSettings.generated.h"

USTRUCT( BlueprintType )
struct FResourceSinkRewardLevelsData : public FTableRowBase
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

};

USTRUCT(BlueprintType)
struct FResourceSinkPointsData : public FTableRowBase
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

};

/**
 * 
 */
UCLASS( Blueprintable, config = Game, defaultconfig, meta = ( DisplayName = "Resource Sink Settings" ) )
class FACTORYGAME_API UFGResourceSinkSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGResourceSinkSettings* Get() { return GetDefault<UFGResourceSinkSettings>(); };

	static TSubclassOf< class UFGItemDescriptor > GetCouponClass();

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
#endif

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UDataTable* GetPointsDataTable();
	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSoftObjectPtr< class UDataTable > GetPointsDataTablePtr() { return GetDefault<UFGResourceSinkSettings>()->mPointsDataTable; }

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UDataTable* GetRewardLevelsDataTable();
	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSoftObjectPtr< class UDataTable > GetRewardLevelsDataTablePtr() { return GetDefault<UFGResourceSinkSettings>()->mRewardLevelsDataTable; }

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UDataTable* GetExplorationPointsDataTable();
	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSoftObjectPtr< class UDataTable > GetExplorationPointsDataTablePtr() { return GetDefault<UFGResourceSinkSettings>()->mExplorationPointsDataTable; }

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UDataTable* GetExplorationRewardLevelsDataTable();
	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSoftObjectPtr< class UDataTable > GetExplorationRewardLevelsDataTablePtr() { return GetDefault<UFGResourceSinkSettings>()->mExplorationRewardLevelsDataTable; }

public:

	UPROPERTY( EditAnywhere, config, Category = "Data table" )
	TSoftObjectPtr< class UDataTable > mPointsDataTable;

	UPROPERTY( EditAnywhere, config, Category = "Data table" )
	TSoftObjectPtr< class UDataTable > mRewardLevelsDataTable;

	UPROPERTY( EditAnywhere, config, Category = "Data table" )
	TSoftObjectPtr< class UDataTable > mExplorationPointsDataTable;

	UPROPERTY( EditAnywhere, config, Category = "Data table" )
	TSoftObjectPtr< class UDataTable > mExplorationRewardLevelsDataTable;

	UPROPERTY( VisibleAnywhere, config, Category = "Settings", meta = ( ToolTip = "The maximum value an item can be worth, 0 = No cap" ) )
	int32 mMaxPointsForItem;

	UPROPERTY( VisibleAnywhere, config, Category = "Settings", meta = ( ToolTip = "The math expression used to calculate points for items" ) )
	FString mPointCalculationExpression;
	
	UPROPERTY( EditAnywhere, config, Category = "Coupons", meta = ( ToolTip = "The class that we use as coupon" ) )
	TSoftClassPtr< class UFGItemDescriptor > mCouponClass;

	UPROPERTY( EditAnywhere, config, Category = "History", meta = ( ToolTip = "The number of history points we save for the global resource sink history" ) )
	int32 mNumGlobalHistoryPoints;
	
	UPROPERTY( EditAnywhere, config, Category = "Cyber coupon", meta = ( ToolTip = "The schematic to unlock when sinking a coupon" ) )
	TSubclassOf<class UFGSchematic> mCyberCouponSchematic;

	UPROPERTY( EditAnywhere, config, Category = "Custom Rewards", meta = ( ToolTip = "Custom rewards that will be given in the form of a schematic when you sink a specific item." ) )
	TMap<TSubclassOf<class UFGItemDescriptor>, TSubclassOf<class UFGSchematic>> mCustomRewards;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Points = mMulitplier * level^mExponent" ) )
	float mMultiplier;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Points = mMulitplier * level^mExponent" ) )
	float mExponent;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Number of levels" ) )
	int32 mNumLevels;

	UPROPERTY( EditAnywhere, config, Category = "Rewards", meta = ( ToolTip = "Number of repeats per each level" ) )
	int32 mDefaultNumRepeats;

	UPROPERTY( EditAnywhere, config, Category = "Tool", meta = ( ToolTip = "The subclasses of UFGItemDescriptor that we don't want to show up in resource sink balancer", AllowAbstract=true ) )
	TArray<TSubclassOf<class UFGItemDescriptor>> mExcludedDescriptors;

};
