// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGActorRepresentationInterface.h"
#include "FGBuildableFactory.h"
#include "FGBuildableGenerator.h"
#include "FGBuildableTradingPost.generated.h"

UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGTradingPostIntegratedBuildable : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGTradingPostIntegratedBuildable
{
	GENERATED_BODY()
public:
	/** Called when the buildable visibility changed */
	UFUNCTION( BlueprintNativeEvent, Category = "Trading Post" )
	void UpdateBuildableVisibility( bool isVisible, bool isTutorialComplete );
}; 

/**
 * The trading post, it has N inputs and sells inputed items for money.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableTradingPost : public AFGBuildableFactory, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGBuildableTradingPost();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	//~ Begin AFGBuildable interface
	virtual bool CanBeSampled_Implementation() const{ return false; }
	//~ End AFGBuildable interface

	//~ Begin IFGDismantleInterface
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	//~ End IFGDismantleInferface

	// Begin IFGActorRepresentationInterface
	UFUNCTION()
	virtual bool AddAsRepresentation() override;
	UFUNCTION()
	virtual bool UpdateRepresentation() override;
	UFUNCTION()
	virtual bool RemoveAsRepresentation() override;
	UFUNCTION()
	virtual bool IsActorStatic() override;
	UFUNCTION()
	virtual FVector GetRealActorLocation() override;
	UFUNCTION()
	virtual FRotator GetRealActorRotation() override;
	UFUNCTION()
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION()
	virtual FText GetActorRepresentationText() override;
	UFUNCTION()
	virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION()
	virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION()
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION()
	virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION()
	virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION()
	virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION()
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION()
	virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION()
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION()
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	UFUNCTION()
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface

	/** Upgrading the trading post to specified level */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "TradingPost" )
	void OnTradingPostUpgraded( int32 level, bool suppressBuildEffects = false );

	/** Returns true if the trading post is complete */
	UFUNCTION( BlueprintPure, Category = "Trading Post" )
	bool IsTradingPostComplete() const;

	/** Updates the visibility of the HUB sub buildings */
	UFUNCTION( BlueprintCallable, Category = "Trading Post" )
	void UpdateSubBuildingsVisibility();

	/** Sets up dismantle redirect on the sub-buildings of the HUB */
	void SetupSubBuildingsDismantleRedirect();

	bool GetStorageVisibility() const;
	bool GetLockerVisibility() const;
	bool GetMiniGameAndCalendarVisibility() const;
	bool GetGeneratorVisibility( int32 generatorIndex ) const;
	bool GetPottyVisibility() const;

	/** Returns level of trading post upgrade */
	UFUNCTION( BlueprintPure, Category = "Trading Post" )
	int32 GetTradingPostLevel() const;

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

protected:
	/** Handles the generators visibility depending on tutorial step */
	void UpdateGeneratorVisibility();
	/** Handles the storage visibility depending on tutorial step */
	void UpdateStorageVisibility();
	/** Updates the visibility of the terminal and work bench, depending on the current upgrade level of the hub */
	void UpdateTerminalAndWorkbenchVisibility();
	/** Updates the visibility of the locker */
	void UpdateLockerVisibility();
	/** Updates the visibility of the mini game and the calendar */
	void UpdateMiniGameAndCalendarVisibility();
	void UpdatePottyVisibility();
	
	UFUNCTION()
	void OnRep_HubTerminalOrWorkBench();
	UFUNCTION()
	void OnRep_Storage();
	UFUNCTION()
	void OnRep_Generators();
	UFUNCTION()
	void OnRep_Locker();
	UFUNCTION()
	void OnRep_Calendar();
	UFUNCTION()
	void OnRep_MiniGame();
	UFUNCTION()
	void OnRep_Potty();
	
	/** Returns the cached schematic manager */
	class AFGSchematicManager* GetSchematicManager();
private:
	/** Called when subsystems are available and our sub buildings begun play */
	UFUNCTION()
	void OnSubsystemsAvailable();
	/** Try to add event sub buildings like calendar and mini game */
	UFUNCTION()
	void TryAddEventSubBuildings();

	/** Spawn transient sub buildings that are not saved and are not constructed as a part of the hub hologram */
	void SpawnTransientSubBuildings();
public:
	/** Class of generators to create with the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	TSubclassOf< class UFGRecipe > mDefaultGeneratorRecipe;

	/** References to the created generators */
	UPROPERTY( ReplicatedUsing = OnRep_Generators, SaveGame )
	TArray< AFGBuildableGenerator* > mGenerators;

	//@todo Why are these recipes and not only TSubclassOf<AFGBuildable>? This seems like a lot of setup just for the extra buildables? Hologram can be created for buildables as well and not just recipes!
	/** Class of storage to create with the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	TSubclassOf< class UFGRecipe > mDefaultStorageRecipe;

	/** Class of hub terminal to create with the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	TSubclassOf< class UFGRecipe > mDefaultHubTerminalRecipe;

	/** Class of work bench to create with the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	TSubclassOf< class UFGRecipe > mDefaultWorkBenchRecipe;

	/** Class of locker to create with the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	TSubclassOf< class AFGBuildable > mLockerBuildableClass;

	/** Class of locker to create with the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	TSubclassOf< class AFGBuildable > mPioneerPottyClass;
	
	/** References to the created storage */
	UPROPERTY( ReplicatedUsing = OnRep_Storage, SaveGame )
	class AFGBuildable* mStorage;

	/** References to the created Hub Terminal */
	UPROPERTY( ReplicatedUsing = OnRep_HubTerminalOrWorkBench, SaveGame )
	class AFGBuildableHubTerminal* mHubTerminal;

	/** References to the created work bench */
	UPROPERTY( ReplicatedUsing = OnRep_HubTerminalOrWorkBench, SaveGame )
	class AFGBuildable* mWorkBench;

	/** References to customization locker */
	UPROPERTY( ReplicatedUsing = OnRep_Locker, SaveGame )
	AFGBuildable* mLocker;

	UPROPERTY( ReplicatedUsing = OnRep_Potty, SaveGame )
	AFGBuildable* mPioneerPotty;

	/** References to the created calendar */
	UPROPERTY( ReplicatedUsing = OnRep_Calendar )
	class AFGBuildableCalendar* mCalendar;

	/** References to the created mini game */
	UPROPERTY( ReplicatedUsing = OnRep_MiniGame )
	AFGBuildable* mMiniGame;
	
	/** Arrays containing ints for what level  we should activate/show the generator */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post", Meta = (NoAutoJson = true) )
	TArray< int32 > mGeneratorVisibilityLevels;

	/** Size of the storage box */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	int32 mStorageInventorySize;

	/** At what trading post level should the storage be visible */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	int32 mStorageVisibilityLevel;

	/** At what trading post level should the locker be visible */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	int32 mLockerVisibilityLevel;

	/** At what trading post level should the mini game and the calendar become visible */
	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	int32 mMiniGameAndCalendarVisibilityLevel;

	UPROPERTY( EditDefaultsOnly, Category = "Trading Post" )
	UMaterialInterface* mCompassMaterialInstance;

protected:

	/** How far above the ground the spawn-points should be adjusted */
	UPROPERTY( EditDefaultsOnly, Category="Spawning" )
	float mSpawningGroundZOffset;

	/** How much up and down we should search for the ground around all child actors that's spawning AFGPlayerStartTradingPost */
	UPROPERTY( EditDefaultsOnly, Category="Spawning" )
	float mGroundSearchZDistance;

	/** A cached schematic manager */
	UPROPERTY()
	class AFGSchematicManager* mSchematicManager;

	/** The starting resources in the tradingpost storage */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	TArray< FItemAmount > mDefaultResources;

	/** Component used to determine generators location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mGenerator1Location;

	/** Component used to determine generators location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mGenerator2Location;

	/** Component used to determine storage location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mStorageLocation;

	/** Component used to determine Hub terminal location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mHubTerminalLocation;

	/** Component used to determine work bench terminal location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mWorkBenchLocation;

	/** Component used to determine calendar location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mCalendarLocation;

	/** Component used to determine mini game location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mMiniGameLocation;

	/** Component used to determine customization location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mCharacterCustomizationLocation;

	/** Component used to determine customization location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mPioneerPottyLocation;

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mRepresentationText;
};
