#include "Registry/ModContentRegistry.h"
#include "Registry/SMLExtendedAttributeProvider.h"
#include "Registry/ContentTagRegistry.h"
#include "FGGameMode.h"
#include "FGGameState.h"
#include "FGResearchManager.h"
#include "FGResourceSinkSettings.h"
#include "FGResourceSinkSubsystem.h"
#include "FGSchematicManager.h"
#include "FGTutorialIntroManager.h"
#include "Unlocks/FGUnlockRecipe.h"
#include "FGCustomizationRecipe.h"
#include "IPlatformFilePak.h"
#include "AvailabilityDependencies/FGConsumablesConsumedDependency.h"
#include "AvailabilityDependencies/FGItemPickedUpDependency.h"
#include "AvailabilityDependencies/FGItemsManuallyCraftedDependency.h"
#include "AvailabilityDependencies/FGRecipeUnlockedDependency.h"
#include "AvailabilityDependencies/FGResearchTreeProgressionDependency.h"
#include "AvailabilityDependencies/FGSchematicPurchasedDependency.h"
#include "Creature/FGCreatureDescriptor.h"
#include "Patching/NativeHookManager.h"
#include "Reflection/ReflectionHelper.h"
#include "Engine/AssetManager.h"
#include "GameplayTagsModule.h"
#include "Kismet/BlueprintAssetHelperLibrary.h"
#include "ModLoading/PluginModuleLoader.h"
#include "Resources/FGAnyUndefinedDescriptor.h"
#include "Resources/FGConsumableDescriptor.h"
#include "Resources/FGNoneDescriptor.h"
#include "Resources/FGOverflowDescriptor.h"
#include "Resources/FGVehicleDescriptor.h"
#include "Resources/FGWildCardDescriptor.h"
#include "Resources/FGBuildingDescriptor.h"
#include "Unlocks/FGUnlockGiveItem.h"
#include "Unlocks/FGUnlockScannableObject.h"
#include "Unlocks/FGUnlockSchematic.h"

DEFINE_LOG_CATEGORY( LogContentRegistry );

FFrame* UModContentRegistry::ActiveScriptFramePtr{};

static bool GIsRegisteringVanillaContent = false;

/** Makes sure provided object instance is valid, crashes with both script call stack and native stack trace if it's not */
#define NOTIFY_INVALID_REGISTRATION(Context) \
	{ \
		/* Attempt to use cached script frame pointer first, then fallback to global script callstack (which is not available in shipping by default) */ \
		const FString ScriptCallstack = UModContentRegistry::GetCallStackContext(); \
		UE_LOG(LogContentRegistry, Error, TEXT("Attempt to register invalid content: %s"), Context); \
		UE_LOG(LogContentRegistry, Error, TEXT("Script Callstack: %s"), *ScriptCallstack); \
		ensureMsgf( false, TEXT("%s"), *Context ); \
	} \

UModContentRegistry::UModContentRegistry() {
}

UModContentRegistry* UModContentRegistry::Get( const UObject* WorldContext )
{
	if ( const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull) )
	{
		return World->GetSubsystem<UModContentRegistry>();
	}
	return nullptr;
}

FGameObjectRegistryState::~FGameObjectRegistryState()
{
	RegistrationMap.Empty();
	for ( FGameObjectRegistration*& Registration : RegistrationList )
	{
		delete Registration;
		Registration = nullptr;
	}
	RegistrationList.Empty();
}

const FGameObjectRegistration* FGameObjectRegistryState::RegisterObject( FName InRegistrationPluginName, UObject* Object, EGameObjectRegistrationFlags ExtraFlags )
{
	FString Context;
	if (!CanRegisterObject(Object, ExtraFlags, Context)) {
		NOTIFY_INVALID_REGISTRATION(*Context);
		return FindObjectRegistration(Object);
	}
	
	FGameObjectRegistration* Registration = FindOrAddObject( Object );

	// Filter flags, for example if being passed Implicit and BuiltIn, when the object is already explicitly registered
	const EGameObjectRegistrationFlags NewFlags = ExtraFlags & GetAllowedNewFlags( Object );

	Registration->ClearFlags( EGameObjectRegistrationFlags::Unregistered | EGameObjectRegistrationFlags::Implicit );
	Registration->AddFlags( NewFlags );
	Registration->RegistrarModReference = InRegistrationPluginName;

	const bool bIsRegistrationImplicit = Registration->HasAnyFlags( EGameObjectRegistrationFlags::Implicit );

	UE_LOG( LogContentRegistry, Verbose, TEXT("Registering Object '%s' (%s)%s [%s]"), *GetFullNameSafe( Object ), *InRegistrationPluginName.ToString(),
		bIsRegistrationImplicit ? TEXT(" [implicit]") : TEXT(""), *UModContentRegistry::GetCallStackContext() );

	OnObjectRegisteredDelegate.Broadcast( Registration );
	return Registration;
}

FGameObjectRegistration* FGameObjectRegistryState::FindOrAddObject( UObject* Object )
{
	fgcheck( Object );
	FGameObjectRegistration* ExistingRegistration = RegistrationMap.FindOrAdd( Object );
	if ( !ExistingRegistration )
	{
		ExistingRegistration = new FGameObjectRegistration();
		ExistingRegistration->RegisteredObject = Object;
		ExistingRegistration->OwnedByModReference = UModContentRegistry::FindContentOwnerFast( Object );
		ExistingRegistration->AddFlags( EGameObjectRegistrationFlags::Unregistered );

		RegistrationList.Add( ExistingRegistration );
		RegistrationMap.Add( Object, ExistingRegistration );
	}
	return ExistingRegistration;
}

bool FGameObjectRegistryState::CanRegisterObject(UObject* Object, EGameObjectRegistrationFlags ExtraFlags, FString& OutMessage) {
	if ( bRegistryFrozen )
	{
		OutMessage = FString::Printf( TEXT("Attempt to register object '%s' in frozen registry. Make sure your modded content registration is happening in the 'Initialization' Lifecycle Phase and not 'Post Initialization'"), *GetPathNameSafe( Object ) );
		return false;
	}
	if ( !IsValid( Object ) )
	{
		OutMessage = FString::Printf( TEXT("Attempt to register an invalid object in the content registry.") );
		return false;
	}
	if (EnumHasAnyFlags(ExtraFlags, EGameObjectRegistrationFlags::Unregistered)) {
		OutMessage = FString::Printf( TEXT("Attempt to register an object with Unregistered flag set.") );
		return false;
	}
	
	FGameObjectRegistration* Registration = FindOrAddObject( Object );
	
	// Allow implicit registration clarification (e.g. re-registering implicit entries)
	// Also allow re-registering if extra flags contains BuiltIn (e.g. vanilla registrations have priority over modded ones)
	if ( !Registration->HasAnyFlags( EGameObjectRegistrationFlags::Unregistered | EGameObjectRegistrationFlags::Implicit ) && !EnumHasAnyFlags( ExtraFlags, EGameObjectRegistrationFlags::BuiltIn ) )
	{
		OutMessage = FString::Printf( TEXT("Object '%s' has already been registered!"), *GetPathNameSafe( Object ) );
		return false;
	}

	return true;
}

EGameObjectRegistrationFlags FGameObjectRegistryState::GetAllowedNewFlags(UObject* Object) const {
	if ( !IsValid( Object ) )
	{
		return EGameObjectRegistrationFlags::None;
	}

	const FGameObjectRegistration* Registration = FindObjectRegistration( Object );

	// Never allow Removed, since it's handled by MarkObjectAsRemoved

	static FName baseGameProjectName = FApp::GetProjectName();

	EGameObjectRegistrationFlags allowedFlags = EGameObjectRegistrationFlags::None;

	if ( !Registration || Registration->OwnedByModReference == baseGameProjectName ) {
		allowedFlags |= EGameObjectRegistrationFlags::BuiltIn;
	}

	if ( !Registration || Registration->HasAnyFlags(EGameObjectRegistrationFlags::Unregistered | EGameObjectRegistrationFlags::Implicit) )
	{
		// Allow Implicit only on unregistered objects, or if it is already set
		// so that is is kept when re-registering as Implicit
		allowedFlags |= EGameObjectRegistrationFlags::Implicit;
	}

	return allowedFlags;
}

bool FGameObjectRegistryState::AttemptRegisterObject( FName InRegistrationPluginName, UObject* Object, EGameObjectRegistrationFlags ExtraFlags )
{
	FString Message;
	if ( !CanRegisterObject(Object, ExtraFlags, Message) )
	{
		return false;
	}
	const FGameObjectRegistration* ExistingRegistration = FindOrAddObject( Object );
	const EGameObjectRegistrationFlags NewFlags = ExtraFlags & GetAllowedNewFlags( Object );

	if ( !ExistingRegistration->HasAllFlags( NewFlags ) )
	{
		RegisterObject( InRegistrationPluginName, Object, NewFlags );
		return true;
	}
	return false;
}

void FGameObjectRegistryState::MarkObjectAsRemoved( UObject* Object )
{
	if ( bRegistryFrozen )
	{
		const FString Context = FString::Printf( TEXT("Attempt to remove object '%s' in frozen registry. Make sure your modded content registration is happening in the 'Initialization' Lifecycle Phase and not 'Post Initialization'"), *GetPathNameSafe( Object ) );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	if ( !IsValid( Object ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to mark invalid object as Removed.") );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	FGameObjectRegistration* ExistingRegistration = FindOrAddObject( Object );
	if ( !ExistingRegistration->HasAnyFlags( EGameObjectRegistrationFlags::Removed ) )
	{
		UE_LOG( LogContentRegistry, Display, TEXT("Marking Object '%s' as Removed [%s]"), *GetPathNameSafe( Object ), *UModContentRegistry::GetCallStackContext() );

		ExistingRegistration->AddFlags( EGameObjectRegistrationFlags::Removed );
	}
}

void FGameObjectRegistryState::AddObjectReference( UObject* Object, UObject* ReferencedBy )
{
	if ( !IsValid( Object ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to add a Reference to an invalid object from %s"), *GetPathNameSafe( ReferencedBy ) );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	if ( !IsValid( ReferencedBy ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to add a Reference to %s from invalid object"), *GetPathNameSafe( Object ) );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	
	FGameObjectRegistration* ExistingRegistration = FindOrAddObject( Object );
	if ( !ExistingRegistration->ReferencedBy.Contains( ReferencedBy ) )
	{
		UE_LOG( LogContentRegistry, Verbose, TEXT("Adding Reference to '%s' from '%s' [%s]"), *GetPathNameSafe( Object ), *GetPathNameSafe( ReferencedBy ), *UModContentRegistry::GetCallStackContext() );
		
		ExistingRegistration->ReferencedBy.Add( ReferencedBy );
	}
}

void FGameObjectRegistryState::FreezeRegistry()
{
	bRegistryFrozen = true;
}

const TArray<const FGameObjectRegistration*>& FGameObjectRegistryState::GetAllRegistrationsCopyFree() const
{
	// This is a little bit unsafe but we 100% know that size and structure of const pointer is the same as the non-const one
	return *reinterpret_cast<const TArray<const FGameObjectRegistration*>*>( &RegistrationList );
}

void FGameObjectRegistryState::GetAllRegistrations( TArray<FGameObjectRegistration>& OutRegistrations, bool bIncludeRemoved ) const
{
	for ( const FGameObjectRegistration* Registration : RegistrationList )
	{
		// TODO @SML: Should we actually include Unregistered objects into the list? Not so sure about that
		if ( !Registration->HasAnyFlags( EGameObjectRegistrationFlags::Unregistered ) )
		{
			if ( bIncludeRemoved || !Registration->HasAnyFlags( EGameObjectRegistrationFlags::Removed ) )
			{
				OutRegistrations.Add( *Registration );
			}
		}
	}
}

const FGameObjectRegistration* FGameObjectRegistryState::FindObjectRegistration( UObject* Object ) const
{
	if ( const FGameObjectRegistration* const* ExistingObject = RegistrationMap.Find( Object ) )
	{
		return *ExistingObject;
	}
	return nullptr;
}

void FGameObjectRegistryState::AddReferencedObjects( FReferenceCollector& ReferenceCollector )
{
	for ( FGameObjectRegistration* Registration : RegistrationList )
	{
		ReferenceCollector.AddPropertyReferences( FGameObjectRegistration::StaticStruct(), Registration );
	}
}

FName UModContentRegistry::FindContentOwnerFast( const UObject* Object ) {
	// Exit early on nullptr
	if ( !Object )
	{
		return NAME_None;
	}
	static FName StaticProjectName = FApp::GetProjectName();

    //Shortcut used for quickly registering vanilla content
    if (GIsRegisteringVanillaContent) {
        return StaticProjectName;
    }
    //Use GetName on package instead of GetPathName() because it's faster and avoids string concat
    const FString ContentOwnerName = UBlueprintAssetHelperLibrary::FindPluginNameByObjectPath(Object->GetPackage()->GetName());

	if (ContentOwnerName.IsEmpty()) {
        UE_LOG(LogContentRegistry, Error, TEXT("Failed to determine content owner for object %s. This is an error, report to mod author!"), *Object->GetPathName());
        return StaticProjectName;
    }
    return *ContentOwnerName;
}

void UModContentRegistry::OnSchematicPurchased(TSubclassOf<UFGSchematic> Schematic)
{
    //Update research trees in case they depend on schematic unlocked dependency
    AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);
    if (ResearchManager != NULL && ResearchManager->HasAuthority())
    {
        ResearchManager->UpdateUnlockedResearchTrees();
    }
}

void UModContentRegistry::ModifySchematicList(TArray<TSubclassOf<UFGSchematic>>& RefSchematics) {
	// PopulateSchematicList happens during PreInitializeComponents,
	// while WorldModules get constructed during OnActorsInitialized
	// BeginPlay is a reasonable moment in the lifecycle past OnActorsInitialized to delay this to,
	// since mods could technically register schematics during POST_INITIALIZE, and we can't guarantee
	// the order in which bindings to the same delegate are executed.

	// On the client, the world will BeginPlay before the actor is replicated,
	// so by the time we reach this point, WorldBeginPlayDelegate will have already fired.
	// But this also means that mod content was registered, so we can safely modify the list here.
	
	if (bBegunPlay) {
		ModifySchematicListInternal(RefSchematics);
	} else {
		OnWorldBeginPlayDelegate.AddWeakLambda(this, [&] {
			ModifySchematicListInternal(RefSchematics);
		});
	}
}

void UModContentRegistry::ModifySchematicListInternal( TArray<TSubclassOf<UFGSchematic>>& RefSchematics )
{
	// Register vanilla schematics in the registry first
	{
		TGuardValue ScopedVanillaContent( GIsRegisteringVanillaContent, true );
		for ( TSubclassOf<UFGSchematic>& Schematic : RefSchematics )
		{
			if ( IsValid( Schematic ) )
			{
				SchematicRegistryState.RegisterObject( NAME_None, Schematic, EGameObjectRegistrationFlags::BuiltIn );
			}
		}
	}

	// Cleanup invalid or removed schematics from the list
	for ( int32 SchematicIndex = RefSchematics.Num() - 1; SchematicIndex >= 0; SchematicIndex-- )
	{
		if ( !IsValid( RefSchematics[SchematicIndex] ) )
		{
			RefSchematics.RemoveAt( SchematicIndex );
			continue;
		}

		const FGameObjectRegistration* Registration = SchematicRegistryState.FindObjectRegistration( RefSchematics[SchematicIndex] );
		fgcheck( Registration );

		if ( Registration->HasAnyFlags( EGameObjectRegistrationFlags::Removed ) )
		{
			RefSchematics.RemoveAt( SchematicIndex );
		}
	}

	// Append non-builtin objects to the resulting schematic list
	for ( const FGameObjectRegistration* Registration : SchematicRegistryState.GetAllRegistrationsCopyFree() )
	{
		if ( !Registration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn | EGameObjectRegistrationFlags::Removed | EGameObjectRegistrationFlags::Unregistered ) )
		{
			RefSchematics.AddUnique( CastChecked<UClass>( Registration->RegisteredObject ) );
		}
	}
	SchematicRegistryState.FreezeRegistry();
}

void UModContentRegistry::ModifyResearchTreeList(TArray<TSubclassOf<UFGResearchTree>>& RefResearchTrees) {
	// Similarly to PopulateSchematicList, PopulateResearchTreeList happens during PreInitializeComponents.
	if (bBegunPlay) {
		ModifyResearchTreeListInternal(RefResearchTrees);
	} else {
		OnWorldBeginPlayDelegate.AddWeakLambda(this, [&] {
			ModifyResearchTreeListInternal(RefResearchTrees);
		});
	}	
}


void UModContentRegistry::ModifyResearchTreeListInternal( TArray<TSubclassOf<UFGResearchTree>>& RefResearchTrees )
{
	// Register vanilla research trees in the registry first
	{
		TGuardValue ScopedVanillaContent( GIsRegisteringVanillaContent, true );
		for ( TSubclassOf<UFGResearchTree>& ResearchTree : RefResearchTrees )
		{
			if ( IsValid( ResearchTree ) )
			{
				ResearchTreeRegistryState.RegisterObject( NAME_None, ResearchTree, EGameObjectRegistrationFlags::BuiltIn );
			}
		}
	}

	// Cleanup invalid or removed research trees from the list
	for ( int32 ResearchTreeIndex = RefResearchTrees.Num() - 1; ResearchTreeIndex >= 0; ResearchTreeIndex-- )
	{
		if ( !IsValid( RefResearchTrees[ResearchTreeIndex] ) )
		{
			RefResearchTrees.RemoveAt( ResearchTreeIndex );
			continue;
		}

		const FGameObjectRegistration* Registration = ResearchTreeRegistryState.FindObjectRegistration( RefResearchTrees[ResearchTreeIndex] );
		fgcheck( Registration );

		if ( Registration->HasAnyFlags( EGameObjectRegistrationFlags::Removed ) )
		{
			RefResearchTrees.RemoveAt( ResearchTreeIndex );
		}
	}

	// Append non-builtin objects to the resulting research tree list
	for ( const FGameObjectRegistration* Registration : ResearchTreeRegistryState.GetAllRegistrationsCopyFree() )
	{
		if ( !Registration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn | EGameObjectRegistrationFlags::Removed | EGameObjectRegistrationFlags::Unregistered ) )
		{
			RefResearchTrees.AddUnique( CastChecked<UClass>( Registration->RegisteredObject ) );
		}
	}
	ResearchTreeRegistryState.FreezeRegistry();
}

void UModContentRegistry::RegisterSchematic(const FName ModReference, const TSubclassOf<UFGSchematic> Schematic) {
	if ( !IsValid( Schematic ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to register NULL Schematic. Mod Reference: %s"), *ModReference.ToString() );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	SchematicRegistryState.RegisterObject( ModReference, Schematic );
}

void UModContentRegistry::RegisterResearchTree(const FName ModReference, const TSubclassOf<UFGResearchTree> ResearchTree) {
	if ( !IsValid( ResearchTree ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to register NULL ResearchTree. Mod Reference: %s"), *ModReference.ToString() );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	ResearchTreeRegistryState.RegisterObject( ModReference, ResearchTree );
}

void UModContentRegistry::RegisterRecipe(const FName ModReference, const TSubclassOf<UFGRecipe> Recipe) {
	if ( !IsValid( Recipe ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to register NULL Recipe. Mod Reference: %s"), *ModReference.ToString() );
		NOTIFY_INVALID_REGISTRATION( *Context );
		return;
	}
	RecipeRegistryState.RegisterObject( ModReference, Recipe );
}

void UModContentRegistry::RemoveSchematic( TSubclassOf<UFGSchematic> Schematic )
{
	if ( !IsValid( Schematic ) )
	{
		NOTIFY_INVALID_REGISTRATION( TEXT("Attempt to Remove NULL Schematic") );
		return;
	}
	SchematicRegistryState.MarkObjectAsRemoved( Schematic );
}

void UModContentRegistry::RemoveResearchTree( TSubclassOf<UFGResearchTree> ResearchTree )
{
	if ( !IsValid( ResearchTree ) )
	{
		NOTIFY_INVALID_REGISTRATION( TEXT("Attempt to Remove NULL ResearchTree") );
		return;
	}
	ResearchTreeRegistryState.MarkObjectAsRemoved( ResearchTree );
}

TArray<FGameObjectRegistration> UModContentRegistry::GetLoadedItemDescriptors() const
{
	TArray<FGameObjectRegistration> Results;
	ItemRegistryState.GetAllRegistrations( Results );
	return Results;
}

void UModContentRegistry::GetObtainableItemDescriptors( TArray<FGameObjectRegistration>& OutItemDescriptors, EGetObtainableItemDescriptorsFlags Flags ) const
{
	for ( const FGameObjectRegistration* Registration : ItemRegistryState.GetAllRegistrationsCopyFree() )
	{
		if ( Registration->HasAnyFlags( EGameObjectRegistrationFlags::Unregistered | EGameObjectRegistrationFlags::Removed ) )
		{
			continue;
		}
		// We consider items that are used in Recipes or are Built-In (vanilla) obtainable (vanilla items that are not obtainable would not get into a packaged build)
		if ( Registration->ReferencedBy.IsEmpty() && !Registration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn ) )
		{
			continue;
		}

		// Apply filters specified by the user
		if ( IsDescriptorFilteredOut( Registration->RegisteredObject, Flags ) )
		{
			continue;
		}
		OutItemDescriptors.Emplace( *Registration );
	}
}

TArray<FGameObjectRegistration> UModContentRegistry::GetRegisteredSchematics() const
{
	TArray<FGameObjectRegistration> Results;
	SchematicRegistryState.GetAllRegistrations( Results );
	return Results;
}

TArray<FGameObjectRegistration> UModContentRegistry::GetRegisteredResearchTrees() const
{
	TArray<FGameObjectRegistration> Results;
	ResearchTreeRegistryState.GetAllRegistrations( Results );
	return Results;
}

TArray<FGameObjectRegistration> UModContentRegistry::GetRegisteredRecipes() const
{
	TArray<FGameObjectRegistration> Results;
	RecipeRegistryState.GetAllRegistrations( Results );
	return Results;
}

bool UModContentRegistry::GetResearchTreeRegistrationInfo( TSubclassOf<UFGResearchTree> ResearchTree, FGameObjectRegistration& OutRegistration ) const
{
	if ( const FGameObjectRegistration* ResearchTreeRegistration = ResearchTreeRegistryState.FindObjectRegistration( ResearchTree ) )
	{
		OutRegistration = *ResearchTreeRegistration;
		return true;
	}
	return false;
}

bool UModContentRegistry::GetSchematicRegistrationInfo( TSubclassOf<UFGSchematic> Schematic, FGameObjectRegistration& OutRegistration ) const
{
	if ( const FGameObjectRegistration* SchematicRegistration = SchematicRegistryState.FindObjectRegistration( Schematic ) )
	{
		OutRegistration = *SchematicRegistration;
		return true;
	}
	return false;
}

bool UModContentRegistry::GetRecipeInfo( TSubclassOf<UFGRecipe> Recipe, FGameObjectRegistration& OutRegistration ) const
{
	if ( const FGameObjectRegistration* RecipeRegistration = RecipeRegistryState.FindObjectRegistration( Recipe ) )
	{
		OutRegistration = *RecipeRegistration;
		return true;
	}
	return false;
}

FGameObjectRegistration UModContentRegistry::GetItemDescriptorInfo( TSubclassOf<UFGItemDescriptor> ItemDescriptor )
{
	ItemRegistryState.AttemptRegisterObject( NAME_None, ItemDescriptor );
	if (const FGameObjectRegistration* ItemRegistration = ItemRegistryState.FindObjectRegistration(ItemDescriptor))
	{
		return *ItemRegistration;
	}
	// Since the ItemRegistryState is never frozen, this will only be reached if the ItemDescriptor is invalid
	return FGameObjectRegistration{};
}

bool UModContentRegistry::IsItemDescriptorVanilla( TSubclassOf<UFGItemDescriptor> ItemDescriptor )
{
	ItemRegistryState.AttemptRegisterObject( NAME_None, ItemDescriptor );
	if ( const FGameObjectRegistration* ItemRegistration = ItemRegistryState.FindObjectRegistration( ItemDescriptor ) )
	{
		return ItemRegistration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn );
	}
	return false;
}

bool UModContentRegistry::IsRecipeVanilla( TSubclassOf<UFGRecipe> Recipe ) const
{
	if ( const FGameObjectRegistration* RecipeRegistration = RecipeRegistryState.FindObjectRegistration( Recipe ) )
	{
		return RecipeRegistration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn );
	}
	return false;
}

bool UModContentRegistry::IsSchematicVanilla( TSubclassOf<UFGSchematic> Schematic ) const
{
	if ( const FGameObjectRegistration* SchematicRegistration = SchematicRegistryState.FindObjectRegistration( Schematic ) )
	{
		return SchematicRegistration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn );
	}
	return false;
}

bool UModContentRegistry::IsResearchTreeVanilla( TSubclassOf<UFGResearchTree> ResearchTree ) const
{
	if ( const FGameObjectRegistration* ResearchTreeRegistration = ResearchTreeRegistryState.FindObjectRegistration( ResearchTree ) )
	{
		return ResearchTreeRegistration->HasAnyFlags( EGameObjectRegistrationFlags::BuiltIn );
	}
	return false;
}

void UModContentRegistry::RegisterResourceSinkItemPointTable(FName ModReference, UDataTable* PointTable, EResourceSinkTrack Track)
{
	if ( !IsValid( PointTable ) )
	{
		const FString Context = FString::Printf( TEXT("Attempt to register NULL ResourceSinkPointTable on %s track. Mod Reference: %s"), *UEnum::GetValueAsString(Track), *ModReference.ToString() );
		NOTIFY_INVALID_REGISTRATION(*Context);
		return;
	}

	if ( !IsValid( PointTable->RowStruct ) || !PointTable->RowStruct->IsChildOf(FResourceSinkPointsData::StaticStruct()) )
	{
		const FString Context = FString::Printf( TEXT("Invalid AWESOME Sink item points table in mod %s (%s): Row Type should be Resource Sink Points Data"),
			*ModReference.ToString(), *PointTable->GetPathName() );
		NOTIFY_INVALID_REGISTRATION(*Context);
		return;
	}

	FPendingResourceSinkRegistration Registration;
	Registration.Track = Track;
	Registration.ModReference = ModReference;
	Registration.PointTable = PointTable;

	PendingItemSinkPointsRegistrations.Add( Registration );
	if ( AFGResourceSinkSubsystem* ResourceSinkSubsystem = AFGResourceSinkSubsystem::Get( GetWorld() ) )
	{
		FlushPendingResourceSinkRegistrations( ResourceSinkSubsystem );
	}
}

void UModContentRegistry::FlushPendingResourceSinkRegistrations( AFGResourceSinkSubsystem* ResourceSinkSubsystem ) {

	for (const FPendingResourceSinkRegistration& Registration : PendingItemSinkPointsRegistrations) {

		UE_LOG(LogContentRegistry, Log, TEXT("Registering Resource Sink Points Table '%s' track type '%s' from Mod %s"),
			*Registration.PointTable->GetPathName(), *UEnum::GetValueAsString(Registration.Track), *Registration.ModReference.ToString());

		ResourceSinkSubsystem->SetupPointData( Registration.Track, Registration.PointTable );
	}
	PendingItemSinkPointsRegistrations.Empty();
}

bool UModContentRegistry::ShouldCreateSubsystem( UObject* Outer ) const
{
	UWorld* WorldOuter = CastChecked<UWorld>(Outer);
	return FPluginModuleLoader::ShouldLoadModulesForWorld(WorldOuter);
}

void UModContentRegistry::Initialize( FSubsystemCollectionBase& Collection )
{
	Super::Initialize( Collection );

	SchematicRegistryState.OnObjectRegistered().AddUObject( this, &UModContentRegistry::OnSchematicRegisteredCallback );
	ResearchTreeRegistryState.OnObjectRegistered().AddUObject( this, &UModContentRegistry::OnResearchTreeRegisteredCallback );
	RecipeRegistryState.OnObjectRegistered().AddUObject( this, &UModContentRegistry::OnRecipeRegisteredCallback );

	// TODO @SML: I don't know if this is the most performant thing to do, it fires on every UWorld::SpawnActor call, which might be a bit heavy.
	OnActorPreSpawnDelegateHandle = GetWorld()->AddOnActorPreSpawnInitialization( FOnActorSpawned::FDelegate::CreateUObject( this, &UModContentRegistry::OnActorPreSpawnInitialization ) );
	OnActorPostSpawnDelegateHandle = GetWorld()->AddOnActorSpawnedHandler( FOnActorSpawned::FDelegate::CreateUObject( this, &UModContentRegistry::OnActorPostSpawnInitialization ) );
}

void UModContentRegistry::OnWorldBeginPlay(UWorld& InWorld) {
	OnWorldBeginPlayDelegate.Broadcast();
	// Apparently World->bBegunPlay is not set by the time the manager delegates are called on clients
	// Maybe it just isn't set on clients at all
	bBegunPlay = true;
}

void UModContentRegistry::OnSchematicRegisteredCallback( const FGameObjectRegistration* Schematic )
{
	OnSchematicRegistered.Broadcast( *Schematic );
	AutoRegisterSchematicReferences( CastChecked<UClass>( Schematic->RegisteredObject ), Schematic->RegistrarModReference );
}

void UModContentRegistry::OnResearchTreeRegisteredCallback( const FGameObjectRegistration* ResearchTree )
{
	OnResearchTreeRegistered.Broadcast( *ResearchTree );
	AutoRegisterResearchTreeReferences( CastChecked<UClass>( ResearchTree->RegisteredObject ), ResearchTree->RegistrarModReference );
}

void UModContentRegistry::OnRecipeRegisteredCallback(const FGameObjectRegistration* Recipe) {
	OnRecipeRegistered.Broadcast(*Recipe);
	AutoRegisterRecipeReferences(CastChecked<UClass>(Recipe->RegisteredObject), Recipe->RegistrarModReference);
}

void UModContentRegistry::OnActorPreSpawnInitialization( AActor* Actor )
{
	if ( AFGSchematicManager* SchematicManager = Cast<AFGSchematicManager>( Actor ) )
	{
		SchematicManager->PopulateSchematicListDelegate.AddUObject( this, &UModContentRegistry::ModifySchematicList );
		SchematicManager->PurchasedSchematicDelegate.AddUniqueDynamic( this, &UModContentRegistry::OnSchematicPurchased );
		PreSpawnInitializationStack++;
	}
	if ( AFGResearchManager* ResearchManager = Cast<AFGResearchManager>( Actor ) )
	{
		ResearchManager->PopulateResearchTreeListDelegate.AddUObject( this, &UModContentRegistry::ModifyResearchTreeList );
		PreSpawnInitializationStack++;
	}
	
	if ( PreSpawnInitializationStack >= 2 )
	{
		GetWorld()->RemoveOnActorPreSpawnInitialization( OnActorPreSpawnDelegateHandle );
		OnActorPreSpawnDelegateHandle.Reset();
	}
}

void UModContentRegistry::OnActorPostSpawnInitialization( AActor* Actor )
{
	if ( AFGResourceSinkSubsystem* ResourceSinkSubsystem = Cast<AFGResourceSinkSubsystem>( Actor ) )
	{
		FlushPendingResourceSinkRegistrations( ResourceSinkSubsystem );
		PostSpawnInitializationStack++;
	}

	if ( PostSpawnInitializationStack >= 1 )
	{
		GetWorld()->RemoveOnActorSpawnedHandler( OnActorPostSpawnDelegateHandle );
		OnActorPostSpawnDelegateHandle.Reset();
	}
}

void UModContentRegistry::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
	UModContentRegistry* ModContentRegistry = CastChecked<UModContentRegistry>(InThis);

	//Register all referenced objects from registry states
	ModContentRegistry->ItemRegistryState.AddReferencedObjects(Collector);
	ModContentRegistry->RecipeRegistryState.AddReferencedObjects(Collector);
	ModContentRegistry->SchematicRegistryState.AddReferencedObjects(Collector);
	ModContentRegistry->ResearchTreeRegistryState.AddReferencedObjects(Collector);
}

FString UModContentRegistry::GetCallStackContext()
{
	// If we are registering vanilla content do not attempt to load symbols
	if ( GIsRegisteringVanillaContent )
	{
		return TEXT("[ModContentRegistry internals]");
	}
	
	// Prefer script callstack to the native one
	if ( ActiveScriptFramePtr != nullptr )
	{
		return ActiveScriptFramePtr->Node->GetPathName();
	}

	// Attempt to capture stack trace
	TArray<FProgramCounterSymbolInfo> NativeStackTrace = FPlatformStackWalk::GetStack(1, 10);
	if ( NativeStackTrace.IsEmpty() )
	{
		FProgramCounterSymbolInfo& Info = NativeStackTrace.Emplace_GetRef();
		TCString<ANSICHAR>::Strcpy(Info.Filename, FProgramCounterSymbolInfo::MAX_NAME_LENGTH, "Unknown");
		Info.LineNumber = 1;
	}

	// Find first frame that does not contain internal logic of content registry
	int32 FirstExternalFrameIndex = 0;
	while ( FirstExternalFrameIndex + 1 < NativeStackTrace.Num() &&
		FCStringAnsi::Strifind( NativeStackTrace[FirstExternalFrameIndex].Filename, __FILE__ ) != nullptr )
	{
		FirstExternalFrameIndex++;
	}
	return FString::Printf( TEXT("%hs:%d"), NativeStackTrace[FirstExternalFrameIndex].Filename, NativeStackTrace[FirstExternalFrameIndex].LineNumber );
}

void UModContentRegistry::AutoRegisterSchematicReferences(TSubclassOf<UFGSchematic> Schematic, FName RegistrarPluginName)
{
	const FGameObjectRegistration* Registration = SchematicRegistryState.FindObjectRegistration( Schematic );
	// Propagate BuiltIn flag
	const EGameObjectRegistrationFlags PropagateFlags = Registration->Flags & ( EGameObjectRegistrationFlags::BuiltIn );

	// Objects referenced receive the Implicit flag, along with the propagated flags
	const EGameObjectRegistrationFlags Flags = EGameObjectRegistrationFlags::Implicit | PropagateFlags; 
	
	for ( const FItemAmount& ItemAmount : UFGSchematic::GetCost( Schematic ) )
	{
		ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, ItemAmount.ItemClass, Flags );
		ItemRegistryState.AddObjectReference( ItemAmount.ItemClass, Schematic );
	}

	TArray<UFGAvailabilityDependency*> AvailabilityDependencies;
	UFGSchematic::GetSchematicDependencies( Schematic, AvailabilityDependencies );
	for ( UFGAvailabilityDependency* AvailabilityDependency : AvailabilityDependencies )
	{
		AutoRegisterAvailabilityDependencyReferences( AvailabilityDependency, Schematic, RegistrarPluginName, PropagateFlags );
	}
	
    const TArray<UFGUnlock*> Unlocks = UFGSchematic::GetUnlocks(Schematic);
    for ( UFGUnlock* Unlock : Unlocks )
    {
    	AutoRegisterUnlockReferences( Unlock, Schematic, RegistrarPluginName, PropagateFlags );
    }

	TArray<TSubclassOf<UFGSchematic>> RelevantShopSchematics;
	UFGSchematic::GetRelevantShopSchematics( Schematic, RelevantShopSchematics );
	for ( const TSubclassOf<UFGSchematic>& OtherSchematic : RelevantShopSchematics )
	{
		// FactoryGame itself has a None reference in one of it's schematics
		if ( OtherSchematic )
		{
			SchematicRegistryState.AttemptRegisterObject( RegistrarPluginName, OtherSchematic, Flags );			
            SchematicRegistryState.AddObjectReference( OtherSchematic, Schematic );
		}
	}
}

void UModContentRegistry::AutoRegisterResearchTreeReferences( TSubclassOf<UFGResearchTree> ResearchTree, FName RegistrarPluginName ) {
	const FGameObjectRegistration* Registration = ResearchTreeRegistryState.FindObjectRegistration( ResearchTree );
	// Propagate BuiltIn flag
	const EGameObjectRegistrationFlags PropagateFlags = Registration->Flags & ( EGameObjectRegistrationFlags::BuiltIn );

	// Objects referenced receive the Implicit flag, along with the propagated flags
	const EGameObjectRegistrationFlags Flags = EGameObjectRegistrationFlags::Implicit | PropagateFlags; 
	
    const TArray<UFGResearchTreeNode*> Nodes = UFGResearchTree::GetNodes( ResearchTree );
    for ( const UFGResearchTreeNode* Node : Nodes)
    {
        if ( const TSubclassOf<UFGSchematic> NodeSchematic = Node->GetNodeSchematic() )
        {
        	SchematicRegistryState.AttemptRegisterObject( RegistrarPluginName, NodeSchematic, Flags );
        	SchematicRegistryState.AddObjectReference( NodeSchematic, ResearchTree );
        }
    }

	TArray<UFGAvailabilityDependency*> UnlockDependencies = UFGResearchTree::GetUnlockDependencies( ResearchTree );
	for ( UFGAvailabilityDependency* Dependency : UnlockDependencies )
	{
		AutoRegisterAvailabilityDependencyReferences( Dependency, ResearchTree, RegistrarPluginName, PropagateFlags );
	}
}

void UModContentRegistry::AutoRegisterRecipeReferences( TSubclassOf<UFGRecipe> Recipe, FName RegistrarPluginName )
{
	const FGameObjectRegistration* Registration = RecipeRegistryState.FindObjectRegistration( Recipe );
	// Propagate BuiltIn flag
	const EGameObjectRegistrationFlags PropagateFlags = Registration->Flags & ( EGameObjectRegistrationFlags::BuiltIn );

	// Objects referenced receive the Implicit flag, along with the propagated flags
	const EGameObjectRegistrationFlags Flags = EGameObjectRegistrationFlags::Implicit | PropagateFlags; 
	
	TArray<FItemAmount> AllItemReferences;
	AllItemReferences.Append( UFGRecipe::GetProducts( Recipe ) );
	AllItemReferences.Append( UFGRecipe::GetIngredients( Recipe ) );

	for ( const FItemAmount& ItemAmount : AllItemReferences )
	{
		ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, ItemAmount.ItemClass, Flags );
		ItemRegistryState.AddObjectReference( ItemAmount.ItemClass, Recipe );
	}
	
	if ( const TSubclassOf<UFGCustomizationRecipe> CustomizationRecipe = UFGRecipe::GetMaterialCustomizationRecipe( Recipe ) )
	{
		RecipeRegistryState.AttemptRegisterObject( RegistrarPluginName, CustomizationRecipe, Flags );
		RecipeRegistryState.AddObjectReference( CustomizationRecipe, Recipe );
	}
}

static bool IsResourceFormFilteredOut(EResourceForm ResourceForm, EGetObtainableItemDescriptorsFlags Flags)
{
	using enum EGetObtainableItemDescriptorsFlags;
	using enum EResourceForm;

	switch (ResourceForm) {
	case RF_INVALID:
		return !EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags(IncludeBuildings | IncludeCustomizations | IncludeVehicles | IncludeCreatures | IncludeSpecial));
	case RF_SOLID:
		return false;
	case RF_LIQUID:
	case RF_GAS:
		return !EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags(IncludeNonSolid));
	case RF_HEAT: /* FIXME: Could be omitted, so that the default case handles it */
		return true;
	default:
		return true;
	}
}

bool UModContentRegistry::IsDescriptorFilteredOut( const UObject* ItemDescriptor, EGetObtainableItemDescriptorsFlags Flags ) const
{
	if (!ItemDescriptor) {
		UE_LOG(LogContentRegistry, Warning, TEXT("IsDescriptorFilteredOut called with null ItemDescriptor, returning true (filtering out)"));
		return true;
	}
	const TSubclassOf<UFGItemDescriptor> descriptorClass = const_cast<UClass*>(Cast<UClass>(ItemDescriptor));
	if (!descriptorClass) {
		UE_LOG(LogContentRegistry, Warning, TEXT("IsDescriptorFilteredOut called with non-ItemDescriptor, returning true (filtering out)"));
		return true;
	}
	if (IsResourceFormFilteredOut(UFGItemDescriptor::GetForm(descriptorClass), Flags)) {
		return true;
	}

	if (!EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags::IncludeBuildings) && descriptorClass->IsChildOf<UFGBuildingDescriptor>()) {
		return true;
	}
	if (!EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags::IncludeCustomizations) && descriptorClass->IsChildOf<UFGFactoryCustomizationDescriptor>()) {
		return true;
	}
	if (!EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags::IncludeCreatures) && descriptorClass->IsChildOf<UFGCreatureDescriptor>()) {
		return true;
	}
	if (!EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags::IncludeVehicles) && descriptorClass->IsChildOf<UFGVehicleDescriptor>()) {
		return true;
	}
	if (!EnumHasAnyFlags(Flags, EGetObtainableItemDescriptorsFlags::IncludeSpecial)) {
		if (descriptorClass->IsChildOf<UFGWildCardDescriptor>() || descriptorClass->IsChildOf<UFGAnyUndefinedDescriptor>() || descriptorClass->IsChildOf<UFGOverflowDescriptor>() || descriptorClass->IsChildOf<UFGNoneDescriptor>()) {
			return true;
		}
		const auto descriptorTags = UContentTagRegistry::Get(this)->GetGameplayTagContainerFor(descriptorClass);
		const auto SmlSpecialTag = FGameplayTag::RequestGameplayTag("SML.Registry.Item.SpecialItemDescriptor", true);
		return descriptorTags.HasTag(SmlSpecialTag);
	}
	return false;
}

void UModContentRegistry::AutoRegisterUnlockReferences( UFGUnlock* Unlock, UObject* ReferencedBy, FName RegistrarPluginName, EGameObjectRegistrationFlags PropagateFlags )
{
	// Objects referenced receive the Implicit flag, along with the propagated flags
	const EGameObjectRegistrationFlags Flags = EGameObjectRegistrationFlags::Implicit | PropagateFlags; 

	if ( const UFGUnlockRecipe* UnlockRecipe = Cast<UFGUnlockRecipe>( Unlock ) )
	{
		for ( TSubclassOf<UFGRecipe> Recipe : UnlockRecipe->GetRecipesToUnlock() )
		{
			RecipeRegistryState.AttemptRegisterObject( RegistrarPluginName, Recipe, Flags );			
			RecipeRegistryState.AddObjectReference( Recipe, ReferencedBy  );
		}
	}
	if ( const UFGUnlockScannableResource* ResourceUnlock = Cast<UFGUnlockScannableResource>( Unlock ) )
	{
		for ( const FScannableResourcePair& ResourcePair : ResourceUnlock->GetResourcesToAddToScanner() )
		{
			ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, ResourcePair.ResourceDescriptor, Flags );
			ItemRegistryState.AddObjectReference( ResourcePair.ResourceDescriptor, ReferencedBy  );
		}
	}
	if ( const UFGUnlockScannableObject* ObjectUnlock = Cast<UFGUnlockScannableObject>( Unlock ) )
	{
		for ( const FScannableObjectData& ObjectData : ObjectUnlock->GetScannableObjectsToUnlock() )
		{
			ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, ObjectData.ItemDescriptor, Flags );
			ItemRegistryState.AddObjectReference( ObjectData.ItemDescriptor, ReferencedBy  );
		}
	}
	if ( const UFGUnlockSchematic* SchematicUnlock = Cast<UFGUnlockSchematic>( Unlock ) )
	{
		for ( TSubclassOf<UFGSchematic> InnerSchematic : SchematicUnlock->GetSchematicsToUnlock() )
		{
			SchematicRegistryState.AttemptRegisterObject( RegistrarPluginName, InnerSchematic, Flags );
			SchematicRegistryState.AddObjectReference( InnerSchematic, ReferencedBy  );
		}
	}
	if ( const UFGUnlockGiveItem* ItemUnlock = Cast<UFGUnlockGiveItem>( Unlock ) )
	{
		for ( const FItemAmount& ItemAmount : ItemUnlock->GetItemsToGive() )
		{
			ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, ItemAmount.ItemClass, Flags );
			ItemRegistryState.AddObjectReference( ItemAmount.ItemClass, ReferencedBy  );
		}
	}
}

void UModContentRegistry::AutoRegisterAvailabilityDependencyReferences( UFGAvailabilityDependency* Dependency, UObject* ReferencedBy, FName RegistrarPluginName, EGameObjectRegistrationFlags PropagateFlags )
{
	// Objects referenced receive the Implicit flag, along with the propagated flags
	const EGameObjectRegistrationFlags Flags = EGameObjectRegistrationFlags::Implicit | PropagateFlags;
	
	if ( const UFGConsumablesConsumedDependency* ConsumableDependency = Cast<UFGConsumablesConsumedDependency>( Dependency ) )
	{
		for ( const auto& Pair : ConsumableDependency->GetItemAmount() )
		{
			ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, Pair.Key, Flags );
			ItemRegistryState.AddObjectReference( Pair.Key, ReferencedBy  );
		}
	}
	if ( const UFGItemPickedUpDependency* PickupDependency = Cast<UFGItemPickedUpDependency>( Dependency ) )
	{
		TArray<TSubclassOf<UFGItemDescriptor>> Items;
		PickupDependency->GetItems( Items );
		
		for ( const TSubclassOf<UFGItemDescriptor>& ItemDescriptor : Items )
		{
			ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, ItemDescriptor, Flags );
			ItemRegistryState.AddObjectReference( ItemDescriptor, ReferencedBy  );
		}
	}
	if ( const UFGItemsManuallyCraftedDependency* ManuallyCraftedDependency = Cast<UFGItemsManuallyCraftedDependency>( Dependency ) )
	{
		for ( const auto& Pair : ManuallyCraftedDependency->GetItemsManuallyCraftedCount() )
		{
			ItemRegistryState.AttemptRegisterObject( RegistrarPluginName, Pair.Key, Flags );			
			ItemRegistryState.AddObjectReference( Pair.Key, ReferencedBy  );
		}
	}
	if ( const UFGRecipeUnlockedDependency* RecipeUnlockedDependency = Cast<UFGRecipeUnlockedDependency>( Dependency ) )
	{
		TArray<TSubclassOf<UFGRecipe>> Recipes;
		RecipeUnlockedDependency->GetRecipes( Recipes );

		for ( const TSubclassOf<UFGRecipe>& Recipe : Recipes )
		{
			RecipeRegistryState.AttemptRegisterObject( RegistrarPluginName, Recipe, Flags );
			RecipeRegistryState.AddObjectReference( Recipe, ReferencedBy  );
		}
	}
	if ( const UFGSchematicPurchasedDependency* SchematicUnlockedDependency = Cast<UFGSchematicPurchasedDependency>( Dependency ) )
	{
		TArray<TSubclassOf<UFGSchematic>> Schematics;
		SchematicUnlockedDependency->GetSchematics( Schematics );

		for ( const TSubclassOf<UFGSchematic>& Schematic : Schematics )
		{
			SchematicRegistryState.AttemptRegisterObject( RegistrarPluginName, Schematic, Flags );
			SchematicRegistryState.AddObjectReference( Schematic, ReferencedBy  );
		}
	}
	if ( const UFGResearchTreeProgressionDependency* ResearchTreeProgressionDependency = Cast<UFGResearchTreeProgressionDependency>( Dependency ) )
	{
		TArray<TSubclassOf<UFGResearchTree>> ResearchTrees;
		ResearchTreeProgressionDependency->mResearchTrees.GetKeys( ResearchTrees );

		for ( const TSubclassOf<UFGResearchTree>& ResearchTree : ResearchTrees )
		{
			ResearchTreeRegistryState.AttemptRegisterObject( RegistrarPluginName, ResearchTree, Flags );
			ResearchTreeRegistryState.AddObjectReference( ResearchTree, ReferencedBy );
		}
	}
}

DEFINE_FUNCTION( UModContentRegistry::execRegisterResourceSinkItemPointTable )
{
	P_GET_PROPERTY(FNameProperty, ModReference);
	P_GET_OBJECT(UDataTable, PointTable);
	P_GET_ENUM(EResourceSinkTrack, Track);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	P_THIS->RegisterResourceSinkItemPointTable(ModReference, PointTable, Track);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UModContentRegistry::execRegisterRecipe) {
	P_GET_PROPERTY(FNameProperty,Z_Param_ModReference);
	P_GET_OBJECT(UClass,Z_Param_Recipe);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	P_THIS->RegisterRecipe(Z_Param_ModReference,Z_Param_Recipe);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UModContentRegistry::execRegisterResearchTree) {
	P_GET_PROPERTY(FNameProperty, ModReference);
	P_GET_OBJECT(UClass, ResearchTree);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	P_THIS->RegisterResearchTree(ModReference, ResearchTree);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UModContentRegistry::execRegisterSchematic) {
	P_GET_PROPERTY(FNameProperty, ModReference);
	P_GET_OBJECT(UClass, Schematic);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	P_THIS->RegisterSchematic(ModReference, Schematic);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UModContentRegistry::execRemoveResearchTree) {
	P_GET_OBJECT(UClass, ResearchTree);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	P_THIS->RemoveResearchTree( ResearchTree );
	P_NATIVE_END;
}

DEFINE_FUNCTION(UModContentRegistry::execRemoveSchematic) {
	P_GET_OBJECT(UClass, Schematic);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	P_THIS->RemoveSchematic( Schematic );
	P_NATIVE_END;
}

DEFINE_FUNCTION(UModContentRegistry::execGetItemDescriptorInfo) {
	P_GET_OBJECT(UClass, ItemDescriptor);
	P_FINISH;
	P_NATIVE_BEGIN;
	TGuardValue ScopedFrameOverride( ActiveScriptFramePtr, &Stack );
	*(FGameObjectRegistration*)RESULT_PARAM = P_THIS->GetItemDescriptorInfo( ItemDescriptor );
	P_NATIVE_END;
}
