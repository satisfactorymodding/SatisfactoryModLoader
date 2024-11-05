// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGIconLibrary.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "FGIconDatabaseSubsystem.generated.h"

class UFGIconLibrary;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FFGOnIconDatabaseAvailable );

/** Struct used to remap the Global IDs to Local IDs and back */
union FGlobalIconIdStruct
{
	struct
	{
		uint16 IconId;
		uint16 IconLibraryId;
	} IconIdComponents;
	int32 GlobalIconId;
};

/** Maintains Consistent ID mappings between save reloads and FGIconLibrary addition/removals */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGIconDatabaseSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGIconDatabaseSubsystem();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
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

	void Init();

	FORCEINLINE const TArray<FIconData>& GetAllIconData() const { return mAllIconData; }
	
	/** Returns the full array of all icons available */
	UFUNCTION( BlueprintPure, Category = "Icon Database" )
	void GetIconData( TArray<FIconData>& out_allIconData ) const;
	
	/** Attempts to retrieve the index of an icon with the corresponding texture */
	UFUNCTION( BlueprintCallable, Category = "Icon Database" )
	int32 GetIconIDForTexture( UObject* texture ) const;
	
	/* Get all the icon data from Icon Settings for a given icon type type. If includeHidden is not true, this will filter out those elements */
	UFUNCTION( BlueprintCallable, Category = "Icon Database" )
	void GetAllIconDataForType( EIconType iconType, bool includeHidden, TArray< FIconData >& out_iconData ) const;

	/** Get the icon data for a specific icon ID */
	UFUNCTION( BlueprintCallable, Category = "Icon Database" )
	bool GetIconDataForIconID( int32 iconID, FIconData& out_iconData ) const;

	UFUNCTION( BlueprintCallable, Category = "Icon Database" )
	UObject* GetIconTextureFromIconID( int32 iconID ) const;

	/** Resolves Persistent, Global IconID into the ItemID that is local to this SaveGame and can be used in other functions in the database */
	UFUNCTION( BlueprintPure, Category = "Icon Database" )
	int32 ResolvePersistentGlobalIconId( const FPersistentGlobalIconId& IconId ) const;

	/** Resolves local IconID into the persistent, globally unique IconID that is safe to be passed across the save games */
	UFUNCTION( BlueprintPure, Category = "Icon Database" )
	FPersistentGlobalIconId ResolveLocalIconId( int32 iconID ) const;

	/** Returns the database for the world */
	static AFGIconDatabaseSubsystem* Get( const UWorld* world );

	/** Retrieves the database from the world context */
	UFUNCTION( BlueprintPure, Category = "Icon Database", DisplayName = "GetIconDatabaseSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGIconDatabaseSubsystem* Get( const UObject* worldContext );

	UFUNCTION( BlueprintPure, Category = "Icon Database" )
	FORCEINLINE bool IsInitialized() const { return mDatabaseInitialized; }
protected:
	UFUNCTION()
	void OnRep_GlobalIconLibraries();

	/** Scans for icon libraries available in the Asset Registry and populates IDs from them */
	void ScanForIconLibraries();

	void TryInitializeDatabase();
	void BuildGlobalIconData();
public:
	/** Fired when the icon database is fully populated and available for use on the client */
	UPROPERTY( BlueprintAssignable, Category = "Icon Database" )
	FFGOnIconDatabaseAvailable mOnDatabaseAvailable;
	
protected:
	/** Default icon library to initialize first, only exists to maintain SaveGame compatibility */
	UPROPERTY( EditDefaultsOnly, Category = "Icon Database" )
	TSoftObjectPtr<UFGIconLibrary> mDefaultIconLibrary;
	
	/** A global list of Icon Libraries used in this save. Libraries are never deleted from it, even if they cannot be resolved anymore. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_GlobalIconLibraries )
	TArray<TSoftObjectPtr<UFGIconLibrary>> mGlobalIconLibraries;

	/** Transient icon data list build from all of the icon libraries combined */
	UPROPERTY()
	TArray<FIconData> mAllIconData;
	
	/** Transient Icon Data cache built from all of the icon libraries combined */
	UPROPERTY()
	TMap<int32, FIconData> mIconIdToIconDataMap;

	/** Map of Texture objects to the IDs they belong to, used for fast reverse lookups */
	TMap<TSoftObjectPtr<UObject>, int32> mIconTextureToGlobalId;
	TMap<EIconType, TArray<int32>> mIconCategoryToGlobalIds;

	/** True if the local database has been initialized */
	bool mDatabaseInitialized;
};