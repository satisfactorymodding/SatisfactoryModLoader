// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "ItemAmount.h"
#include "IncludeInBuild.h"
#include "FGSchematicManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPurchasedSchematicDelegate, TSubclassOf< class UFGSchematic >, purchasedSchematic );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPaidOffOnSchematicDelegate, AFGSchematicManager*, schematicManager );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActiveSchematicChanged, TSubclassOf< UFGSchematic >, activeSchematic );

/** Holds info about a schematic and How much has been paid of on it. */
USTRUCT()
struct FSchematicCost
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	TSubclassOf< UFGSchematic > Schematic;

	/** Amount paid off */
	UPROPERTY( SaveGame, EditDefaultsOnly )
	TArray< FItemAmount > ItemCost;
};

/**
 * Keeps track of everything regarding schematics
 */
UCLASS( Blueprintable, abstract, HideCategories=("Actor Tick",Rendering,Replication,Input,Actor) )
class FACTORYGAME_API AFGSchematicManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Called when we players are granted a schematic. */
	UPROPERTY( BlueprintAssignable, Category = "Events|Schematics", DisplayName = "OnPurchasedSchematic" )
	FPurchasedSchematicDelegate PurchasedSchematicDelegate;

	/** Called when a payment on a schematic occurs */
	UPROPERTY( BlueprintAssignable, Category = "Events|Schematics", DisplayName = "OnPaidOffOnSchematic" )
	FPaidOffOnSchematicDelegate PaidOffOnSchematicDelegate;

public:
	/** Get the schematic manager, this should always return something unless you call it really early. */
	static AFGSchematicManager* Get( UWorld* world );

	/** Get the schematic manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Schematic", DisplayName = "GetSchematicManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGSchematicManager* Get( UObject* worldContext );

	/** Get the tech tier of a not loaded schematic asset */
	static int32 GetTechTier( const FAssetData& schematicAsset );

	/** Get if a asset should be included in build of a not loaded schematic asset */
	static EIncludeInBuilds GetIncludedInBuild( const FAssetData& schematicAsset );
public:
	AFGSchematicManager();

	//~ Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	//~ End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Returns the available schematics in the game. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Schematic" )
	void GetAvailableSchematics( TArray< TSubclassOf< UFGSchematic > >& out_schematics ) const;

	/** Returns all schematics the players have purchased. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Schematic" )
	void GetPurchasedSchematics( TArray< TSubclassOf< UFGSchematic > >& out_schematics ) const;

	/** Returns every possible schematic that is in the game. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Schematic" )
	void GetAllSchematics(TArray< TSubclassOf< UFGSchematic > >& out_schematics ) const;

	/** Returns the all schematics of a type. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Schematic" )
	void GetAllSchematicsOfType( ESchematicType type, TArray< TSubclassOf< UFGSchematic > >& out_schematics ) const;

	/** returns true if the passed schematic has been purchased */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	bool IsSchematicPurchased( TSubclassOf< UFGSchematic > schematicClass ) const;

	/** Give the player access to a schematic */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	void GiveAccessToSchematic( TSubclassOf< UFGSchematic > schematicClass, bool accessedViaCheats = false );

	/** adds a schematic to available schematics */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	void AddAvailableSchematic( TSubclassOf< UFGSchematic > schematicClassToAdd );
	
	/** Gives you the base cost, after random, for a schematic */
	UFUNCTION( BlueprintPure, DisplayName = "GetCostFor_Deprecated", Category = "Schematic", meta = ( DeprecatedFunction, DeprecationMessage = "Get the cost from the Schematic directly" ) )
	TArray< FItemAmount > GetCostFor( TSubclassOf< UFGSchematic > schematic );

	/** Returns remaining cost for a certain schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	TArray< FItemAmount > GetRemainingCostFor( TSubclassOf< UFGSchematic > schematic );

	/** Returns how much the players has paid off on a schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	TArray< FItemAmount > GetPaidOffCostFor( TSubclassOf< UFGSchematic > schematic );

	/** Returns how much the players has paid off on a schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	bool IsSchematicPaidOff( TSubclassOf< UFGSchematic > schematic );

	/** Adds paid off amount on a schematic */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	bool PayOffOnSchematic( TSubclassOf< UFGSchematic > schematic, UPARAM( ref ) TArray< FItemAmount >& amount );

	/** Sets the new active schematic to sell stuff towards */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	bool SetActiveSchematic( TSubclassOf< class UFGSchematic > newActiveSchematic );

	/** Can we set the passed schematic as the active one? */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	bool CanSetAsActiveSchematic( TSubclassOf< UFGSchematic > inSchematic );

	/** Get active Schematic. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	FORCEINLINE TSubclassOf< UFGSchematic > GetActiveSchematic() { return mActiveSchematic; }

	/** Player initiated launch of the ship */
	UFUNCTION( BlueprintCallable, Category = "Ship" )
	void LaunchShip();

	/** Returns true if the ship is at the trading post */
	UFUNCTION( BlueprintPure, Category = "Ship" )
	bool IsShipAtTradingPost();

	/** Returns the time until the ship is back */
	UFUNCTION( BlueprintPure, Category = "Ship" )
	float GetTimeUntilShipReturn();

	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	int32 GetHighestAvailableTechTier();

	/** Get the default tech tier from the default schematics manager */
	static int32 GetDefaultMaxAllowedTechTier();

	UFUNCTION(BlueprintPure, Category = "Schematic")
	int32 GetMaxAllowedTechTier() const;

	/** Resets schematics to their defaults. Used for resetting specific progressions for testing. */
	void ResetSchematicsOfType( ESchematicType type );

	/** Debug stuff */
	void Debug_DumpStateToLog() const;
	TArray< TSubclassOf< class UFGRecipe > > Debug_GetAllRecipes() const;

private:
	/** Populate list with all schematics */
	void PopulateSchematicsLists();

	/** Populate list with the default available schematics. */
	void PopulateAvailableSchematicsList();

	UFUNCTION()
	void OnRep_ActiveSchematic();
	UFUNCTION()
	void OnRep_PurchasedSchematic();
	UFUNCTION()
	void OnRep_PaidOffOnSchematic();

	/** Returns the highest tech tier available in lists */
	int32 FindHighestAvailableTechTier();

	/** Find or remove a given schematic in the pay off schematic list. */
	FSchematicCost* FindSchematicPayOff( TSubclassOf< class UFGSchematic > schematic );
	void AddSchematicPayOff( TSubclassOf< class UFGSchematic > schematic, const TArray< FItemAmount >& amount );
	void RemoveSchematicPayOff( TSubclassOf< class UFGSchematic > schematic );

protected:	
	/** All schematic assets that have been sucked up in the PopulateSchematicsList function. Contains cheats and all sort of schematic. */
	UPROPERTY()
	TArray< TSubclassOf< UFGSchematic > > mAllSchematics;

	/** All schematics that are available to the player */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< UFGSchematic > > mAvailableSchematics;

	/** Once schematic is purchased it ends up here */
	UPROPERTY( EditDefaultsOnly, SaveGame, ReplicatedUsing = OnRep_PurchasedSchematic, Category = "Schematic" )
	TArray< TSubclassOf< UFGSchematic > > mPurchasedSchematics;

	/* This keeps track of what players have paid off on different schematics */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_PaidOffOnSchematic )
	TArray< FSchematicCost > mPaidOffSchematic;
	
	/** The active schematic the resources is being sold towards. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ActiveSchematic )
	TSubclassOf< UFGSchematic > mActiveSchematic;

	/** Called when we the schematic has been changed . */
	UPROPERTY( BlueprintAssignable, Category = "Schematics" )
	FOnActiveSchematicChanged mOnActiveSchematicChanged;
	
	/* Time stamp for when the ship is gonna land back at the Trading Post. */
	UPROPERTY( Replicated )
	float mShipLandTimeStamp;

	/** Used to save the ship land timestamp */
	UPROPERTY( SaveGame )
	float mShipLandTimeStampSave;

	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	bool mHasTechTierLimit;

	UPROPERTY( EditDefaultsOnly, Category = "Schematic", meta = ( EditCondition = "mHasTechTierLimit" , ClampMin = "0", ClampMax = "99999", UIMin = "0", UIMax = "99999" ) )
	int32 mMaxAllowedTechTier = 6;

	/** Internal bool to keep track of the state of the ship  */
	bool mIsShipAtTradingPost; 

	/** Message sent when trading post ship has returned */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mShipReturnedMessage;
};
