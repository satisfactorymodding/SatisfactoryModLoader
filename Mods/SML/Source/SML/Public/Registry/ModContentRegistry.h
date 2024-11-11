#pragma once

#include "FGResearchTree.h"
#include "FGSchematic.h"
#include "FGRecipe.h"
#include "FGResourceSinkSubsystem.h"
#include "Engine/DataTable.h"
#include "Misc/EnumClassFlags.h"
#include "Subsystems/WorldSubsystem.h"
#include "ModContentRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogContentRegistry, Log, All);

UENUM( BlueprintType, meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor ) )
enum class EGameObjectRegistrationFlags : uint8
{
	None = 0x00 UMETA( DisplayName = "None" ),
	// The object is a built-in (comes from the base game and not the content registry)
	BuiltIn = 0x01 UMETA( DisplayName = "Built-In" ),
	// The object has been explicitly marked as removed
	Removed = 0x02 UMETA( DisplayName = "Removed" ),
	// The registration of this object was implicit, and might not hold a meaningful registrar mod reference
	Implicit = 0x04 UMETA( DisplayName = "Implicit" ),
	// This object has not been registered yet in any way, but the entry exists because it was explicitly removed.
	Unregistered = 0x08 UMETA( DisplayName = "Unregistered" )
};
ENUM_CLASS_FLAGS( EGameObjectRegistrationFlags );

/** Holds basic information about a single content registration entry */
USTRUCT( BlueprintType )
struct SML_API FGameObjectRegistration {
    GENERATED_BODY()
public:
    /** Mod reference of the plugin which actually performed the object registration. Usually same as OwnedByModReference */
    UPROPERTY(BlueprintReadWrite, Category = "Mod Content Registry")
    FName RegistrarModReference;

	/** Mod reference of the plugin which owns the actual registered object */
    UPROPERTY(BlueprintReadWrite, Category = "Mod Content Registry")
    FName OwnedByModReference;

	/** Object that was registered */
    UPROPERTY(BlueprintReadWrite, Category = "Mod Content Registry")
    UObject* RegisteredObject{};

	/** Flags set on this object. */
	UPROPERTY(BlueprintReadWrite, Category = "Mod Content Registry", meta = ( Bitmask, BitmaskEnum = "/Script/SML.EGameObjectRegistrationFlags" ))
	EGameObjectRegistrationFlags Flags{};
	
	/** List of all objects that reference this one */
	UPROPERTY(BlueprintReadWrite, Category = "Mod Content Registry")
	TArray<UObject*> ReferencedBy;

	FORCEINLINE bool HasAnyFlags( EGameObjectRegistrationFlags InFlags ) const
	{
		return EnumHasAnyFlags( Flags, InFlags );
	}

	FORCEINLINE bool HasAllFlags( EGameObjectRegistrationFlags InFlags ) const
	{
		return EnumHasAllFlags( Flags, InFlags );
	}

	FORCEINLINE void ClearFlags( EGameObjectRegistrationFlags InFlags )
	{
		Flags = Flags & (~InFlags);
	}

	FORCEINLINE void AddFlags( EGameObjectRegistrationFlags InFlags )
	{
		Flags |= InFlags;
	}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FNativeOnObjectRegistered, const FGameObjectRegistration* );

/** Registry state holds all registration of the objects of one type. */
class SML_API FGameObjectRegistryState
{
	TArray<FGameObjectRegistration*> RegistrationList;
	TMap<UObject*, FGameObjectRegistration*> RegistrationMap;
	FNativeOnObjectRegistered OnObjectRegisteredDelegate;
	bool bRegistryFrozen{false};
public:
	~FGameObjectRegistryState();
	
	// Registers the given object and associates it with the provided plugin
	const FGameObjectRegistration* RegisterObject( FName InRegistrationPluginName, UObject* Object, EGameObjectRegistrationFlags ExtraFlags = EGameObjectRegistrationFlags::None );
	bool AttemptRegisterObject( FName InRegistrationPluginName, UObject* Object, EGameObjectRegistrationFlags ExtraFlags = EGameObjectRegistrationFlags::None );
	void MarkObjectAsRemoved( UObject* Object );

	// Adds a reference from one object to another. The object the reference is being added to must be registered.
	void AddObjectReference( UObject* Object, UObject* ReferencedBy );

	// Allows retrieving all registrations and searching for one for the given object
	void GetAllRegistrations( TArray<FGameObjectRegistration>& OutRegistrations, bool bIncludeRemoved = false ) const;
	const FGameObjectRegistration* FindObjectRegistration( UObject* Object ) const;

	// Allows iterating the registered object list without copying it. Keep in mind that the returned array may contain unregistered entries.
	const TArray<const FGameObjectRegistration*>& GetAllRegistrationsCopyFree() const;

	FNativeOnObjectRegistered& OnObjectRegistered() { return OnObjectRegisteredDelegate; }

	// Freezes the registry. No new registrations are accepted past this point.
	void FreezeRegistry();
	
	void AddReferencedObjects( FReferenceCollector& ReferenceCollector );
private:
	FGameObjectRegistration* FindOrAddObject( UObject* Object );
	bool CanRegisterObject( UObject* Object, EGameObjectRegistrationFlags ExtraFlags, FString& OutMessage );
	EGameObjectRegistrationFlags GetAllowedNewFlags( UObject* Object ) const;
};

// Holds information about a pending registration of item points table to the resource sink subsystem
USTRUCT()
struct FPendingResourceSinkRegistration {
    GENERATED_BODY()

	UPROPERTY()
    FName ModReference;

	UPROPERTY()
    EResourceSinkTrack Track;

	UPROPERTY()
    UDataTable* PointTable;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnGameObjectRegistered, FGameObjectRegistration, Registration );

// Flags to pass to GetObtainableItemDescriptors
UENUM( BlueprintType, meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor ) )
enum class EGetObtainableItemDescriptorsFlags : uint8
{
	None = 0x00 UMETA( DisplayName = "None" ),
	IncludeNonSolid = 0x01 UMETA( DisplayName = "Include Non-Solid" ),
	IncludeBuildings = 0x02 UMETA( DisplayName = "Include Buildings" ),
	IncludeCustomizations = 0x04 UMETA( DisplayName = "Include Customizations" ),
	IncludeVehicles = 0x08 UMETA( DisplayName = "Include Vehicles" ),
	IncludeCreatures = 0x10 UMETA( DisplayName = "Include Creatures" ),
	IncludeSpecial = 0x20 UMETA( DisplayName = "Include Special (WildCard, AnyUndefined, Overflow, None, SML.Registry.Item.SpecialItemDescriptor)" ),
	Default = None,
};

ENUM_CLASS_FLAGS(EGetObtainableItemDescriptorsFlags);

/**
 * Manages registration and lifetime of the modded content
 *
 * All modded content of supported types should be registered there
 * to be correctly saved, loaded and identified by the game
 * and other information mods
 *
 * If you don't need any dynamic behaviors, use properties in InitGameWorld instead
 * of calling methods on this object directly
 *
 * Content can only be registered before save is loaded,
 * after that moment registry is frozen and no changes can be made after that
 */
UCLASS()
class SML_API UModContentRegistry : public UWorldSubsystem {
    GENERATED_BODY()
public:
    UModContentRegistry();

    /** Retrieves global mod content registry instance */
	UFUNCTION(BlueprintPure, Category = "Mod Content Registry", DisplayName = "GetModContentRegistry", meta = (WorldContext = "WorldContext"))
    static UModContentRegistry* Get( const UObject* WorldContext);

    /**
     * Registers schematic to be usable by the game
     *    All recipes referenced by schematic are registered automatically
     *    All items referenced by registered recipes are associated with passed mod reference too
     *
     * @param ModReference identifier of the mod who is performing this registration
     * @param Schematic class of schematic to be registered
     */
    UFUNCTION(BlueprintCallable, Category = "Mod Content Registry", CustomThunk)
    void RegisterSchematic(const FName ModReference, TSubclassOf<UFGSchematic> Schematic);

    /**
     * Registers research tree to be usable by the game
     *     Also updates research trees so tree can be unlocked instantly if criteria are met
     *     All schematics referenced by this research tree are registered automatically
     *     Nodes should be of default BPD_ResearchTreeNode type to be discoverable for schematics
     *
     * @param ModReference identifier of the mod who is performing this registration
     * @param ResearchTree class of research tree being registered
     */
    UFUNCTION(BlueprintCallable, Category = "Mod Content Registry", CustomThunk)
    void RegisterResearchTree(const FName ModReference, TSubclassOf<UFGResearchTree> ResearchTree);

    /**
     * Registers recipe to be usable by the game
     *     Also associates items referenced by this recipe with passed mod reference if they are not
     *     associated with any other mod reference yet
     *
     * @param ModReference identifier of the mod who is performing this registration
     * @param Recipe class of recipe being registered
     */
    UFUNCTION(BlueprintCallable, Category = "Mod Content Registry", CustomThunk)
    void RegisterRecipe(const FName ModReference, TSubclassOf<UFGRecipe> Recipe);

    /** Register resource sink item points for each item row in the passed table object */
    UFUNCTION(BlueprintCallable, Category = "Mod Content Registry", CustomThunk)
    void RegisterResourceSinkItemPointTable(const FName ModReference, UDataTable* PointTable, EResourceSinkTrack Track);

	/** Explicitly removes the given schematic from the registry */
	UFUNCTION(BlueprintCallable, Category = "Mod Content Registry", CustomThunk)
	void RemoveSchematic(TSubclassOf<UFGSchematic> Schematic);

	/** Explicitly removes the given research tree from the registry */
	UFUNCTION(BlueprintCallable, Category = "Mod Content Registry", CustomThunk)
	void RemoveResearchTree(TSubclassOf<UFGResearchTree> ResearchTree);
	
    /** Retrieves list of all currently loaded item descriptors */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
    TArray<FGameObjectRegistration> GetLoadedItemDescriptors() const;

    /** Retrieves list of all obtainable item descriptors, e.g ones referenced by any recipe */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
    void GetObtainableItemDescriptors(TArray<FGameObjectRegistration>& OutItemDescriptors, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/SML.EGetObtainableItemDescriptorsFlags")) EGetObtainableItemDescriptorsFlags Flags = EGetObtainableItemDescriptorsFlags::Default) const;

	bool IsDescriptorFilteredOut( const UObject* ItemDescriptor, EGetObtainableItemDescriptorsFlags Flags ) const;
	
	/** Retrieves list of all currently registered research trees */
	UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	TArray<FGameObjectRegistration> GetRegisteredSchematics() const;
	
    /** Retrieves list of all currently registered research trees */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
    TArray<FGameObjectRegistration> GetRegisteredResearchTrees() const;

	/** Retrieves list of all currently registered recipes*/
	UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	TArray<FGameObjectRegistration> GetRegisteredRecipes() const;
	
    /** Retrieves registration entry for research tree */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	bool GetResearchTreeRegistrationInfo(TSubclassOf<UFGResearchTree> ResearchTree, FGameObjectRegistration& OutRegistration) const;
	
    /** Retrieves registration entry for schematic */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	bool GetSchematicRegistrationInfo(TSubclassOf<UFGSchematic> Schematic, FGameObjectRegistration& OutRegistration) const;

	/** Retrieves registration entry for recipe */
	UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	bool GetRecipeInfo(TSubclassOf<UFGRecipe> Recipe, FGameObjectRegistration& OutRegistration) const;
	
	/** Retrieves registration entry for item descriptor */
	UFUNCTION(BlueprintPure, Category = "Mod Content Registry", CustomThunk)
	FGameObjectRegistration GetItemDescriptorInfo(TSubclassOf<UFGItemDescriptor> ItemDescriptor);
	
	/** Returns true when given item descriptor is considered vanilla */
	UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	bool IsItemDescriptorVanilla(TSubclassOf<UFGItemDescriptor> ItemDescriptor);
	
    /** Returns true when given recipe is considered vanilla */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
    bool IsRecipeVanilla(TSubclassOf<UFGRecipe> Recipe) const;

    /** Returns true when given schematic is considered vanilla */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
    bool IsSchematicVanilla(TSubclassOf<UFGSchematic> Schematic) const;

    /** Returns true when given research tree is considered vanilla */
    UFUNCTION(BlueprintPure, Category = "Mod Content Registry")
	bool IsResearchTreeVanilla(TSubclassOf<UFGResearchTree> ResearchTree) const;
	
	/** Called when recipe is registered into content registry */
	UPROPERTY(BlueprintAssignable, Category = "Mod Content Registry")
	FOnGameObjectRegistered OnRecipeRegistered;

	/** Called when schematic is registered into content registry */
	UPROPERTY(BlueprintAssignable, Category = "Mod Content Registry")
	FOnGameObjectRegistered OnSchematicRegistered;

	/** Called when research tree is registered into the registry */
	UPROPERTY(BlueprintAssignable, Category = "Mod Content Registry")
	FOnGameObjectRegistered OnResearchTreeRegistered;

	// Begin USubsystem interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	// End USubsystem interface

	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);
private:
	friend class FGameObjectRegistryState;
	
	FGameObjectRegistryState ItemRegistryState;
	FGameObjectRegistryState RecipeRegistryState;
	FGameObjectRegistryState SchematicRegistryState;
	FGameObjectRegistryState ResearchTreeRegistryState;
	
	/** Pending registrations of item sink point tables */
    UPROPERTY( Transient )
    TArray<FPendingResourceSinkRegistration> PendingItemSinkPointsRegistrations;
	
	int32 PreSpawnInitializationStack{0};
	int32 PostSpawnInitializationStack{0};
	FDelegateHandle OnActorPreSpawnDelegateHandle;
	FDelegateHandle OnActorPostSpawnDelegateHandle;

	bool bBegunPlay{false};
	
	/** Pointer to the currently active script callstack frame, used for debugging purposes */
	static FFrame* ActiveScriptFramePtr;
	
    /** Quick version of UBlueprintAssetHelperLibrary, using predefined mod reference for vanilla content */
    static FName FindContentOwnerFast( const UObject* Object);
	
	/** Flushed pending resource sink registrations into the resource sink subsystem, if it is available */
	void FlushPendingResourceSinkRegistrations( class AFGResourceSinkSubsystem* ResourceSinkSubsystem );

    /** Called when schematic is purchased in schematic manager */
    UFUNCTION()
    void OnSchematicPurchased(TSubclassOf<UFGSchematic> Schematic);

	void OnSchematicRegisteredCallback( const FGameObjectRegistration* Schematic );
	void OnResearchTreeRegisteredCallback( const FGameObjectRegistration* ResearchTree );
	void OnRecipeRegisteredCallback( const FGameObjectRegistration* Recipe );

	void OnActorPreSpawnInitialization( AActor* Actor );
	void OnActorPostSpawnInitialization( AActor* Actor );

	DECLARE_MULTICAST_DELEGATE(FOnWorldBeginPlay);
	FOnWorldBeginPlay OnWorldBeginPlayDelegate;
	
	void ModifySchematicList( TArray<TSubclassOf<UFGSchematic>>& RefSchematics );
	void ModifySchematicListInternal( TArray<TSubclassOf<UFGSchematic>>& RefSchematics );
	void ModifyResearchTreeList( TArray<TSubclassOf<UFGResearchTree>>& RefResearchTrees );
	void ModifyResearchTreeListInternal( TArray<TSubclassOf<UFGResearchTree>>& RefResearchTrees );
	
	void AutoRegisterSchematicReferences(TSubclassOf<UFGSchematic> Schematic, FName RegistrarPluginName);
	void AutoRegisterResearchTreeReferences(TSubclassOf<UFGResearchTree> ResearchTree, FName RegistrarPluginName);
	void AutoRegisterRecipeReferences(TSubclassOf<UFGRecipe> Recipe, FName RegistrarPluginName);

	void AutoRegisterUnlockReferences(UFGUnlock* Unlock, UObject* ReferencedBy, FName RegistrarPluginName, EGameObjectRegistrationFlags PropagateFlags);
	void AutoRegisterAvailabilityDependencyReferences(UFGAvailabilityDependency* Dependency, UObject* ReferencedBy, FName RegistrarPluginName, EGameObjectRegistrationFlags PropagateFlags);

	static FString GetCallStackContext();

	//Custom Thunks for calling Register functions through Reflection, primary point of which
	//is providing FFrame callstack context to the registration methods for debugging in seamless manner
	DECLARE_FUNCTION(execRegisterResourceSinkItemPointTable);
	DECLARE_FUNCTION(execRegisterRecipe);
	DECLARE_FUNCTION(execRegisterResearchTree);
	DECLARE_FUNCTION(execRegisterSchematic);
	DECLARE_FUNCTION(execRemoveResearchTree);
	DECLARE_FUNCTION(execRemoveSchematic);
	DECLARE_FUNCTION(execGetItemDescriptorInfo);
};
