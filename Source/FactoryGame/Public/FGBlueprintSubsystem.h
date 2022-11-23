// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryBlueprintTypes.h"
#include "FGRemoteCallObject.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "FGBlueprintSubsystem.generated.h"

extern TAutoConsoleVariable< int32 > CVarBlueprintDebug;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBlueprintDescriptorUpdated, UFGBlueprintDescriptor*, blueprintDesc );

USTRUCT()
struct FBlueprintNameAndHash
{
	GENERATED_BODY()
	
public:
	FBlueprintNameAndHash() : BlueprintName( "" ), Hash("") {}
	FBlueprintNameAndHash( const FString& name, const FString& hash ) :
		BlueprintName( name ),
		Hash( hash)
	{}
	
	UPROPERTY()
	FString BlueprintName;

	UPROPERTY()
	FString Hash;
	
};

USTRUCT()
struct FBlueprintManifest
{
	GENERATED_BODY()

	UPROPERTY()
	TArray< FBlueprintNameAndHash > Entries;
	
};

struct FFileNameToRawFileData
{
	FFileNameToRawFileData() : FileName( "" ) {}
	FFileNameToRawFileData( const FString& fileName ) : FileName( fileName ) {}
	
	FString FileName;
	TArray< uint8 > RawData;
};

USTRUCT()
struct FBlueprintBuildEffectData
{
	GENERATED_BODY()

	FBlueprintBuildEffectData() : Transform( FTransform::Identity ), ID( INDEX_NONE ), NumBuildables( 0 )
	{}
	
	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	int32 ID;

	UPROPERTY()
	int32 NumBuildables;

	UPROPERTY( NotReplicated )
	TArray< class AFGBuildable* > Buildables;

	UPROPERTY()
	APawn* Instigator;
};

UCLASS()
class FACTORYGAME_API UFGBlueprintRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGSignDataRemoteCallObject = false;

	// Client Notify Server of Category Record Data Changes
	UFUNCTION( Server, Reliable )
	void Server_SetCategoryRecordData( const TArray< FBlueprintCategoryRecord >& categoryRecords );

	UFUNCTION( Server, Reliable )
	void Server_SetBlueprintRecordData( const TArray< FBlueprintRecord >& categoryRecords );
	
	// Request Blueprint Desc File
	UFUNCTION( Server, Reliable )
	void Server_RequestFileData( const FString& fileName, int32 currentProgress );

	// Respond to client with requested data
	UFUNCTION( Client, Reliable )
	void Client_RespondFileDataResponse( const TArray< uint8 >& fileData );

	// Final Response to client, includes the Blueprint Record data so we can write out a Blueprint Config file as well
	UFUNCTION( Client, Reliable )
	void Client_RespondFinalFileDataResponse( const TArray< uint8 >& fileData, FBlueprintRecord record );

	// Response from the server indicating the client requested a bad file (no desc was found, or file was not found)
	UFUNCTION( Client, Reliable )
	void Client_RespondFileFailure( const FString& fileName );
	
	///////////////////////////////////////////////
	/// Designer RPCS
	
	// Server call from client to initiate a save of a designer
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SaveBlueprintInDesigner( class AFGBuildableBlueprintDesigner* designer, class AFGPlayerController* controller, FBlueprintRecord record );

	UFUNCTION( Server, Reliable )
	void Server_ClearBlueprintDesigner( class AFGBuildableBlueprintDesigner* designer, class AFGPlayerController* controller );

	UFUNCTION( Server, Reliable )
	void Server_LoadBlueprintInDesigner( class AFGBuildableBlueprintDesigner* designer, class AFGPlayerController* controller, const FString& blueprintName );

};

/**
 * Subsystem responsible for saving/loading/replicating Blueprint files and category data to clients
 */
UCLASS(Blueprintable, config = Game, defaultconfig, meta = ( DisplayName = "Factory Blueprint Settings" ))
class FACTORYGAME_API AFGBlueprintSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGBlueprintSubsystem();

	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface
	
	/// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Tick( float deltaTime ) override;
	/// End AActor Interface
	
	/** Get the circuit subsystem. */
	static AFGBlueprintSubsystem* Get( UWorld* world );

	/** Get the circuit subsystem */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|FactoryBlueprint", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGBlueprintSubsystem* GetBlueprintSubsystem( UObject* worldContext );
	
	/** Used to initialize all neccessary desc and subcategories */
	void Init();

	/** Clients evaluate their checksums at startup for existing blueprints to notify Server of what files they have */
	void GenerateManifest();

	/** Enumerates all existing blueprints, and creates the neccesary descriptors for each */
	void RefreshBlueprintsAndDescriptors();

	/** Iterates all existing blueprint descriptors and sets whether they meet the recipe requirements */
	void RefreshBlueprintRecipeRequirements();

	/** Iterates over all existing blueprint descriptors and attempts to add them to categories (noteably when a client updates the category data) */
	void UpdateBlueprintCategoryPlacement();

	/** Flags record data as dirty so that it can be rebuilt next tick */
	void MarkRecordDataDirty() { mRecordDataIsDirty = true; }

	/** Finds and assigns a category or subcategory to a BlueprintRecord (so that it can be placed into those categories) */
	void AssignCategoryAndSubcategoryToBlueprintRecord( FBlueprintRecord& record );
	
	/** Flags the blueprint descriptors for a full refresh next tick. This will invalidate all descriptors and rebuild all */
	void MarkBlueprintDescriptorsForRefresh() { mBlueprintDescriptorsRequireRefresh = true; }

	/** Sets the hologram to construct when spawning a blueprint hologram locally */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|FactoryBlueprint" )
	void SetActiveBlueprintHologramDescriptor( UFGBlueprintDescriptor* desc );

	UFUNCTION( BlueprintPure, Category="FactoryGame|FactoryBlueprint" )
	UFGBlueprintDescriptor* GetActiveBlueprintDescriptor() const { return mActiveBlueprintDescriptor; }
	
	/** Serialize a blueprint Header from an Archive */
	static bool SerializeBlueprintHeader( FArchive& ar, FBlueprintHeader& blueprintHeader );

	/** Serialize a blueprint config(record) */
	static bool SerializeBlueprintConfig( FArchive& ar, FBlueprintRecord& blueprintRecord );
	
	/** Creates the world for temp placement of buildables for displaying holograms */
	void CreateBlueprintWorld();
	
	/** Write a TArray of actor data out to blueprint Save data */
	FBlueprintHeader WriteBlueprintToArchive(FBlueprintRecord& record, const FTransform& blueprintOrigin, class AFGBuildableBlueprintDesigner* designer, TArray< class AFGBuildable* >& buildables, FIntVector dimensions );

	/** Writes a Blueprint to disc */
	bool WriteBlueprintToDisk( FBlueprintRecord& record );

	/** Writes just an updated config to disk from a record */
	bool WriteBlueprintConfigToDisk( const FBlueprintRecord& record );

	/** Gathers the total cost for a list of buildables */
	void CalculateBlueprintCost( TArray< AFGBuildable* >& buildables, TArray< FBlueprintItemAmount >& out_cost );

	/** Loads a file from the blueprint directory into the passed location */
	bool LoadFileFromDisk( const FString& fileName, const FString& extension, TArray< uint8 >& out_FileData );

	/** Writes a raw data payload to disk with the passed name and extentions */
	bool WriteFileToDisk( const FString& fileName, const FString& extension, const TArray< uint8 >& dataToWrite );
	
	/** Reads a blueprint from disc */
	bool ReadBlueprintFromDisc( const FString& blueprintName );

	/** Caches a list of all found blueprint headers for the current session */
	void EnumerateBlueprints();

	/** Caches a list of all found blueprint headers for the current session */
	void EnumerateBlueprintConfigs();

	/** Find and Caches blueprint headers along with their file info in the active session directory */
	void FindBlueprintHeaders( FString blueprintDir, TArray< FBlueprintHeader >& out_Headers );
	
	/** Load Actors into blueprint designer
	 * @param instigator (optional)  AActor* the actor that requested the blueprint. */
	void LoadStoredBlueprint(UFGBlueprintDescriptor* blueprintDesc, const FTransform& blueprintOrigin, TArray< class AFGBuildable* >& out_spawnedBuildables, bool useBlueprintWorld = false, class
	                         AFGBuildableBlueprintDesigner* = nullptr, APawn* instigator = nullptr );

	/** Collects all objects for a given "root set". The root set in this case will be a list of buildables and we gather objects from them */
	void CollectObjects( TArray< class AFGBuildable* >& buildables, TArray< UObject* >& out_objectsToSerialize );

	/** Gets the folder for which Blueprint Read/Writes should occur */
	FString GetSessionBlueprintPath();

	/**
	 * Removes any invalid path characters from a blueprint name. This is a security meassure to block invalid access attempts by passing "../.." values in redirecting to higher level folders
	 * @return Returns true if any characters were removed
	**/
	static bool SanitizeBlueprintSessionOrFileName( FString& out_santizedString );

	/** Get an array to all blueprint world buildables present */
	const TArray< class AFGBuildable* >& GetBlueprintWorldBuildables() { return mBlueprintWorldBuildables; }

	/** Adds a blueprint designer to the list. Each designer should be added on begin play */
	void AddBlueprintDesigner( class AFGBuildableBlueprintDesigner* designer ) { mAllBlueprintDesigners.AddUnique( designer ); }
	/** Removes a blueprints designer from the list. Should be called by endplay on the designer */
	void RemoveBlueprintDesigner( class AFGBuildableBlueprintDesigner* designer ) { mAllBlueprintDesigners.Remove( designer ); }

	/** Collects all build with recipes for an array of buildables */
	void GatherRecipeObjectRefsForBuildableArray( const TArray< AFGBuildable* >& buildables, TArray< FObjectReferenceDisc >& out_recipeRefs );
	
	/** 
	 * Checks if a hit location is inside of a blueprint designer. If so the designer is returned.
	 * Used to flag constructed holograms as blueprint buildables (not added to factory tick) and inform designer of newly added buildables
	 */
	AFGBuildableBlueprintDesigner* IsLocationInsideABlueprintDesigner( const FVector& hitLocation );

	/** When a buildable with a certain blueprint build effect ID begins play it notifies the subsystem so we can add that data */
	void NotifyBuildableWithBlueprintBuildIDSet( class AFGBuildable* buildable, int32 id );

	int32 GetUniqueBlueprintBuildEffectID() { mBlueprintBuildEffectID++; return mBlueprintBuildEffectID; }
	
	UFUNCTION()
	void OnRep_BlueprintCategoryRecords();
	
	///
	/// Begin Asset Accessors and Helpers
	///
	bool DoesHeaderExistForDescriptor( UFGBlueprintDescriptor* desc )
	{
		return mCachedHeaders.ContainsByPredicate( [&]( const FBlueprintHeader& header ) { return AreNamesConsideredEqual( header.BlueprintName, desc->GetBlueprintNameAsString() ); } );
	}

	FBlueprintHeader* GetHeaderByName( const FString& name )
	{
		return mCachedHeaders.FindByPredicate( [&]( const FBlueprintHeader& header ) { return AreNamesConsideredEqual( header.BlueprintName, name ); } );
	}

	bool AreRecipeRequirementsMetForBlueprint( const FBlueprintHeader& header );

	UFUNCTION( BlueprintCallable, Category="Blueprint Subsystem")
	void SetBlueprintCategories( TArray< UFGBlueprintCategory* > blueprintCategories );

	/** Deletes a blueprint file and returns true if the file was found */
	UFUNCTION( BlueprintCallable, Category="Blueprint Subsystem" )
	bool DeleteBlueprintDescriptor( UFGBlueprintDescriptor* blueprintDesc );
	
	UFUNCTION(BlueprintCallable, Category="Blueprint Subsystem")
	static void GetBlueprintDescriptors( TArray< UFGBlueprintDescriptor* >& out_descriptors, UObject* worldContext );
	void GetBlueprintDescriptors_Internal( TArray< UFGBlueprintDescriptor* >& out_descriptors ) const { out_descriptors.Reset(); out_descriptors.Append( mAllBlueprintDescriptors ); }

	UFUNCTION( BlueprintCallable, Category="Blueprint Subsystem")
	void GetAllBlueprintCategories( TArray< UFGBlueprintCategory* >& out_Categories ) const { out_Categories.Reset(); out_Categories.Append( mAllBlueprintCategories ); }

	// From the save data, recreate all the blueprint categories that are expected to exist
	void CreateBlueprintCategoriesFromRecords();

	void GetBlueprintRecordForDescriptor( UFGBlueprintDescriptor* desc, FBlueprintRecord& out_blueprintRecord );
	void GetBlueprintCategoryAndSubCategoryForDescriptor( UFGBlueprintDescriptor* desc, UFGBlueprintCategory** out_Category, UFGBlueprintSubCategory** out_SubCategory );
	void GetBlueprintCategoryAndSubCategoryByName( const FString& catName, const FString& subName, UFGBlueprintCategory** out_Category, UFGBlueprintSubCategory** out_SubCategory );
	void GetBlueprintCategoryAndSubCategoryByPrio( const int32 catID, const int32 subID, UFGBlueprintCategory** out_Category, UFGBlueprintSubCategory** out_SubCategory );

	// Get a blueprint Descriptor by name. Null if that name could not be found
	UFGBlueprintDescriptor* GetBlueprintDescriptorByName( FText descName )
	{
		for( UFGBlueprintDescriptor* desc : mAllBlueprintDescriptors )
		{
			if( AreNamesConsideredEqual( desc->GetItemNameFromInstance(), descName ) )
			{
				return desc;
			}
		}
		return nullptr;
	}
	
	// Creates a blueprint desc with a new ID and tracks blueprint Desc
	UFGBlueprintDescriptor* CreateBlueprintDescriptor(const FBlueprintRecord& record, FBlueprintHeader& header, bool markDescriptorsForRefresh = true );

	/**
	 * Searches through categories and their subcategory records to find the correct location for this desc
	 */
	void FindSubcategoryAndAddBlueprintDescriptor( UFGBlueprintDescriptor* desc, const FBlueprintRecord& record );

	/** Removes a blueprint descriptor from a blueprint subcategory */
	void RemoveBlueprintDescriptorFromSubCategory( UFGBlueprintDescriptor* blueprintDesc );
	
	/** Iterates over all blueprint Categories and creates category record data into the passed record location */
	void RebuildCategoryRecordsFromDescriptors( TArray< FBlueprintCategoryRecord >& out_categoryRecords );
	
	UFGBlueprintCategory* CreateBlueprintCategory( const FBlueprintCategoryRecord& record );
	UFGBlueprintCategory* CreateBlueprintCategory( FText categoryName, int32 iconID, float menuPriority );
	
	UFGBlueprintSubCategory* CreateBlueprintSubCategory( const FBlueprintSubCategoryRecord& record );

	UFGBlueprintCategory* FindCategoryWithName(FText nameTxt )
	{
		for( UFGBlueprintCategory* category : mAllBlueprintCategories )
		{
			if( AreNamesConsideredEqual( category->GetCategoryNameFromInstance(), nameTxt ) )
			{
				return category;
			}
		}

		return nullptr;
	}

	void AddDescriptorToUndefined( UFGBlueprintDescriptor* desc )
	{
		UFGBlueprintSubCategory* undefSub = GetSubCategoryForUndefined();
		undefSub->AddBlueprintDescriptor( desc );
	}

	UFUNCTION( BlueprintCallable, Category="Blueprint Subsystem")
	UFGBlueprintCategory* GetCategoryForUndefined()
	{
		return *mAllBlueprintCategories.FindByPredicate( [&]( UFGBlueprintCategory* cat ) -> bool { return !!cat->mIsUndefined; } );
	}

	void GetGeneratedUndefinedCategoryRecord( FBlueprintCategoryRecord& out_catRecord )
	{
		out_catRecord.CategoryName = "Undef";
		out_catRecord.IconID = -1;
		out_catRecord.MenuPriority = FLT_MAX;
		out_catRecord.IsUndefined = 1;

		// Add undefined SubCategory
		FBlueprintSubCategoryRecord newSubRecord;
		newSubRecord.IsUndefined = 1;
		newSubRecord.MenuPriority = FLT_MAX;
		newSubRecord.SubCategoryName = "Undef";
		out_catRecord.SubCategoryRecords.Add( newSubRecord );
	}
	
	void GenerateUndefinedCategories()
	{
		UFGBlueprintCategory* cat = nullptr;
		UFGBlueprintSubCategory* subCat = nullptr;
		mAllBlueprintCategories.Remove( nullptr );
		if( mAllBlueprintCategories.ContainsByPredicate( [&]( UFGBlueprintCategory* category ) -> bool { return category->mIsUndefined == 1; } ) )
		{
			cat = *mAllBlueprintCategories.FindByPredicate( [&]( UFGBlueprintCategory* category )
			{
				return category->mIsUndefined == 1;
			} );
		}

		if( cat != nullptr )
		{
			if( mAllBlueprintSubCategories.ContainsByPredicate( [&]( UFGBlueprintSubCategory* subCategory ) { return subCategory->mIsUndefined == 1; } ) )
			{
				subCat = *cat->mSubCategories.FindByPredicate( [&]( UFGBlueprintSubCategory* subCategory )
				{
					return subCategory->mIsUndefined == 1;
				} );
			}
		}

		if( cat == nullptr )
		{
			FBlueprintCategoryRecord newRecord;
			GetGeneratedUndefinedCategoryRecord( newRecord );
			CreateBlueprintCategory( newRecord );
		}
		else if( subCat == nullptr )
		{
			FBlueprintSubCategoryRecord newSubRecord;
			newSubRecord.IsUndefined = 1;
			newSubRecord.MenuPriority = FLT_MAX;
			newSubRecord.SubCategoryName = "Undef";
			subCat = CreateBlueprintSubCategory( newSubRecord );
			cat->AddSubCategory( subCat );
		}
	}

	UFUNCTION( BlueprintCallable, Category="Blueprint Subsystem")
	UFGBlueprintSubCategory* GetSubCategoryForUndefined()
	{
		do
		{
			for( UFGBlueprintCategory* cat : mAllBlueprintCategories )
			{
				if( cat->mIsUndefined )
				{
					for( UFGBlueprintSubCategory* subCategory : cat->mSubCategories )
					{
						if( subCategory->mIsUndefined )
						{
							return subCategory;
						}
					}
				}
			}
			GenerateUndefinedCategories();
		} while(true);

		return nullptr;
	}
	
	static bool AreNamesConsideredEqual( const FText& A, const FText& B )
	{
		return A.ToLower().EqualTo( B.ToLower() );
	}

	static bool AreNamesConsideredEqual( const FString& A, const FString& B )
	{
		return A.ToLower().Equals( B.ToLower() );
	}
	
	bool DoesBlueprintCategoryExist( const FString& categoryName ) const
	{
		return mAllBlueprintCategories.ContainsByPredicate( [&]( UFGBlueprintCategory* category )
		{
			return AreNamesConsideredEqual( category->GetCategoryNameFromInstanceAsString(), categoryName );
		} );
	}

	FBlueprintCategoryRecord& FindOrAddCategoryRecordForCategory( UFGBlueprintCategory* category );
	bool DoesCategoryRecordExistForCategory( UFGBlueprintCategory* category )
	{
		FBlueprintCategoryRecord* recordPtr = mBlueprintCategoryRecords.FindByPredicate( [&]( const FBlueprintCategoryRecord& record )->bool
		{
			return AFGBlueprintSubsystem::AreNamesConsideredEqual( category->GetCategoryNameFromInstanceAsString(), record.CategoryName );
		});

		return recordPtr != nullptr;
	}
	
	bool DoesBlueprintExist( const FString& blueprintName ) const
	{
		return mAllBlueprintDescriptors.ContainsByPredicate( [&]( UFGBlueprintDescriptor* desc )
		{
			FString descName = desc->GetItemNameFromInstance().ToString();
			return AreNamesConsideredEqual( descName, blueprintName );
		} );
	}
	
	bool DoesBlueprintRecordExist( const FBlueprintRecord& record ) const
	{
		return mBlueprintRecords.ContainsByPredicate( [&]( const FBlueprintRecord& testRecord )->bool
		{
			return AFGBlueprintSubsystem::AreNamesConsideredEqual( record.BlueprintName, testRecord.BlueprintName );
		} );
	}
	void FindOrAddBlueprintRecordFromHeader( const FBlueprintHeader& header, FBlueprintRecord& out_record );
	
	void NotifyBlueprintDescriptorUpdated( UFGBlueprintDescriptor* desc );
	///
	/// End Asset Accessors and Helpers
	///

	// When the server is responding to file requests we load file data into memory and keep it until the request is fullfilled
	FFileNameToRawFileData* FindOrAddRawDataForFile( const FString& fileName );
	void RemoveRawDataForFile( const FString& fileName );
	
private:
	
	UFUNCTION()
	void OnRep_ServerManifest();

	/** Sends a bulk update of all BlueprintRecords that have changed in a frame to clients on tick. See: mPendingBlueprintRecordsClientUpdate */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BroadcastBlueprintRecordChanges( const TArray< FBlueprintRecord >& records );

	/** Notify Clients of build effect data */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_AddBlueprintBuildEffectData( const FBlueprintBuildEffectData& buildeffectData );

	/** Adds or modifies and entry in the server manifest (called when saving a blueprint) */
	void AddOrModifyEntryToServerManifest( const FString& fileName, const FString& hash );

	/** Generates a comparison of the client manifest against the server manifest and adds files missing on the client */
	void GenerateClientServerManifestDiff();

	void RemoveEntryFromServerManifest( const FString& fileName )
	{
		int32 idx = mServerManifest.Entries.IndexOfByPredicate( [&]( const FBlueprintNameAndHash& nameAndHash )
		{
			return AreNamesConsideredEqual( nameAndHash.BlueprintName, fileName );
		} );

		if( idx != INDEX_NONE )
		{
			mServerManifest.Entries.RemoveAtSwap( idx );
		}
	}
	
	/** Remove Completed or failed Missing blueprint from client list */
	void RemovePendingClientBlueprint( const FString& fileName )
	{
		int32 idx = mMissingClientBlueprints.IndexOfByPredicate( [&]( const FBlueprintNameAndHash& nameAndHash )
		{
			return AreNamesConsideredEqual( nameAndHash.BlueprintName, fileName );
		} );

		if( idx != INDEX_NONE )
		{
			mMissingClientBlueprints.RemoveAtSwap( idx );
		}
	}
	
public:
	
	/** When a blueprint is read or writen to memory it is stored here. The data can then be loaded/wrote to disc */
	UPROPERTY()
	FBlueprintSaveData mStoredBlueprintData;

	/** Stores an array of all buildables that have been loaded into the blueprint world */
	UPROPERTY()
	TArray< AFGBuildable* > mBlueprintWorldBuildables;

	/** UI Callback for when blueprint descriptors have changed */
	UPROPERTY( BlueprintAssignable )
	FOnBlueprintDescriptorUpdated OnBlueprintDescriptorUpdated;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class AFGBuildEffectActor> mDefaultBuildEffectActor;

	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf<class AFGBuildable > > mBlacklistedDesignerBuildables;

	/** Some buildables are NOT available in the recipe manager but should still be able to be blueprinted. Add those here. Noteable mentions, signpoles, train switch*/
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf<class AFGBuildable > > mIgnoreRecipeRequirements;

	
private:
	friend class UFGBlueprintRemoteCallObject;
	
	///
	///	Begin Blueprint Asset Declarations
	///

	UPROPERTY()
	TArray< UFGBlueprintDescriptor* > mAllBlueprintDescriptors;

	UPROPERTY()
	TArray< UFGBlueprintCategory* > mAllBlueprintCategories;

	UPROPERTY()
	TArray< UFGBlueprintSubCategory* > mAllBlueprintSubCategories;

	/** For saving/loading and replication we want the Blueprint information in an easy to modify environment
	 * Initially the blueprint info was only stored on the blueprints themselves (in the header). This leads to
	 * excess data over the network and high latency requirements for modifying small aspects of the blueprints
	 * like their icon or description etc. So instead we manage the "records" of the blueprints and replicate that data
	 */
	UPROPERTY()
	TArray< FBlueprintRecord > mBlueprintRecords;
	
	/** For saving and loading purposes (and so we can track which Icons belong to which categories) we save them here */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_BlueprintCategoryRecords )
	TArray< FBlueprintCategoryRecord > mBlueprintCategoryRecords;

	/** Array of blueprint records that is added to when a blueprint record is dirtied so they can be batch sent in tick */
	UPROPERTY()
	TArray< FBlueprintRecord > mBlueprintRecordsPendingNetSend;

	UPROPERTY()
	float mTimeSinceLastBlueprintRecordMulticast;

	UPROPERTY()
	float mTimeSinceLastRecipeCheck;
	
	UPROPERTY()
	bool mRecordDataIsDirty;

	UPROPERTY()
	bool mBlueprintDescriptorsRequireRefresh;
	
	///
	/// End Blueprint Asset Declarations
	///
	
	/** A world for loading Blueprint Data into so that the buildables can be analyzed / duplicated for holograms in the actual world */
	UPROPERTY()
	UWorld* mBlueprintWorld;

	UPROPERTY()
	TArray< FBlueprintRecord > mCachedRecords;
	
	UPROPERTY()
	TArray< FBlueprintHeader > mCachedHeaders;

	UPROPERTY()
	bool mHasInitialized = false;

	/** This property is used to specify locally to the blueprint hologram which file to use in construction when the player selects a descriptor */
	UPROPERTY()
	UFGBlueprintDescriptor* mActiveBlueprintDescriptor;

	/** List of all Blueprint Designers active in the world */
	UPROPERTY()
	TArray< class AFGBuildableBlueprintDesigner* > mAllBlueprintDesigners;

	// List of all blueprints and their hash values on the server
	UPROPERTY( ReplicatedUsing=OnRep_ServerManifest )
	FBlueprintManifest mServerManifest;

	// List Of Pending BuildEffects ( just waiting for building replication )
	UPROPERTY()
	TArray< FBlueprintBuildEffectData > mPendingBlueprintBuildEffects;

	// Fail safe tracking for if a buildable replicates BEFORE the rpc notifying clients that there is a pending build effect 
	UPROPERTY()
	TArray< FBlueprintBuildEffectData > mTemporaryBuildEffectData;

	UPROPERTY()
	int32 mBlueprintBuildEffectID;

	////////////////////////////////////
	/// Server File Transfer tracking

	// Temporary holding of raw file data so we dont have to keep our file streams open or repeatedly open/close files to
	// send blocks of data for file transfers that occur over many net frames
	TArray< FFileNameToRawFileData* > mFileNameRawData;
	
	////////////////////////////////////
	/// Client Properties
	
	// Client copy reflecting the clients current state of blueprints and hashes
	UPROPERTY()
	FBlueprintManifest mClientManifest;

	UPROPERTY()
	bool mClientHasGeneratedInitialManifest;

	// List for tracking which blueprints are still missing on clients
	UPROPERTY()
	TArray< FBlueprintNameAndHash > mMissingClientBlueprints;

	UPROPERTY()
	TArray< uint8 > mFileTransferData;
	
	UPROPERTY()
	FString mPendingFileTransferName;
	
	UPROPERTY()
	bool mHasActiveFileTransfer;

	UPROPERTY()
	bool mClientAwaitingResponse;
	
};
