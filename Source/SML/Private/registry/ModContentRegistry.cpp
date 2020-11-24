#include "ModContentRegistry.h"
#include "FGRecipeManager.h"
#include "FGResearchManager.h"
#include "FGResourceSinkSettings.h"
#include "FGResourceSinkSubsystem.h"
#include "FGSchematicManager.h"
#include "FGUnlockRecipe.h"
#include "FileHelper.h"
#include "PlatformFilemanager.h"
#include "Kismet/GameplayStatics.h"
#include "IPlatformFilePak.h"
#include "Logging.h"
#include "ModSubsystemHolder.h"
#include "NativeHookManager.h"
#include "ReflectionHelper.h"
#include "SMLSubsystemHolder.h"
#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY(LogContentRegistry);

TMap<FString, FString> AModContentRegistry::ModOverwriteMap;

void ExtractRecipesFromSchematic(TSubclassOf<UFGSchematic> Schematic, TArray<TSubclassOf<UFGRecipe>>& OutRecipes) {
    const TArray<UFGUnlock*> Unlocks = UFGSchematic::GetUnlocks(Schematic);
    for (UFGUnlock* Unlock : Unlocks) {
        if (UFGUnlockRecipe* UnlockRecipe = Cast<UFGUnlockRecipe>(Unlock)) {
            OutRecipes.Append(UnlockRecipe->GetRecipesToUnlock());
        }
    }
}

void ExtractSchematicsFromResearchTree(TSubclassOf<UFGResearchTree> ResearchTree,
                                       TArray<TSubclassOf<UFGSchematic>>& OutSchematics) {
    static UStructProperty* NodeDataStructProperty;
    static UClassProperty* SchematicStructProperty;
    static UClass* ResearchTreeNodeClass = NULL;
    //Lazily initialize research tree node reflection properties for faster access
    if (ResearchTreeNodeClass == NULL) {
        ResearchTreeNodeClass = LoadClass<UFGResearchTreeNode>(
            NULL, TEXT("/Game/FactoryGame/Schematics/Research/BPD_ResearchTreeNode.BPD_ResearchTreeNode_C"));
        ResearchTreeNodeClass->AddToRoot(); //Make sure class is not garbage collected
        NodeDataStructProperty = FReflectionHelper::FindPropertyChecked<UStructProperty>(
            ResearchTreeNodeClass, TEXT("mNodeDataStruct"));
        SchematicStructProperty = FReflectionHelper::FindPropertyByShortName<UClassProperty>(
            NodeDataStructProperty->Struct, TEXT("Schematic"));
        check(SchematicStructProperty->MetaClass->IsChildOf(UFGSchematic::StaticClass()));
    }

    const TArray<UFGResearchTreeNode*> Nodes = UFGResearchTree::GetNodes(ResearchTree);
    for (UFGResearchTreeNode* Node : Nodes) {
        if (!Node->IsA(ResearchTreeNodeClass)) {
            SML_LOG(LogContentRegistry, Warning,
                TEXT("Unsupported node class %s for research tree %s"), *Node->GetClass()->GetPathName(),
                *ResearchTree->GetPathName());
            continue;
        }
        const void* NodeDataStructPtr = NodeDataStructProperty->ContainerPtrToValuePtr<void>(Node);
        UClass* SchematicClass = Cast<UClass>(SchematicStructProperty->GetPropertyValue_InContainer(NodeDataStructPtr));
        if (SchematicClass == NULL) {
            SML_LOG(LogContentRegistry, Warning,
                TEXT("Schematic not set on research tree %s, node %s"), *ResearchTree->GetPathName(),
                *Node->GetClass()->GetPathName());
            continue;
        }
        OutSchematics.Add(SchematicClass);
    }
}

template<typename T>
TArray<TSubclassOf<T>> DiscoverVanillaContentOfType() {
    UClass* PrimaryAssetClass = T::StaticClass();
    UAssetManager& AssetManager = UAssetManager::Get();
    
    const FPrimaryAssetType AssetType = PrimaryAssetClass->GetFName();
    TArray<FAssetData> FoundVanillaAssets;
    AssetManager.GetPrimaryAssetDataList(AssetType, FoundVanillaAssets);
    TArray<TSubclassOf<T>> OutVanillaContent;
    
    for (const FAssetData& AssetData : FoundVanillaAssets) {
        SML_LOG(LogContentRegistry, Log, TEXT("VANILLA ASSET DISCOVERY %s %s %s"), *PrimaryAssetClass->GetName(), *AssetData.AssetClass.ToString(), *AssetData.AssetName.ToString());
    }
    return OutVanillaContent;
}

void AModContentRegistry::InjectIntoVanillaManagers() {
    //Prevent unnecessary vanilla schematic list population -
    //we are overriding it from content registry anyway, so let's save some processing time
    SUBSCRIBE_METHOD(AFGSchematicManager::PopulateSchematicsLists,
        [](auto& Call, AFGSchematicManager*) { Call.Cancel(); });
    SUBSCRIBE_METHOD(AFGSchematicManager::PopulateAvailableSchematicsList,
        [](auto& Call, AFGSchematicManager*) { Call.Cancel(); });
    SUBSCRIBE_METHOD(AFGResearchManager::PopulateResearchTreeList,
        [](auto& Call, AFGResearchManager*) { Call.Cancel(); });
    
    //Make sure vanilla states are up to date with registry
    SUBSCRIBE_VIRTUAL_FUNCTION_AFTER(AFGSchematicManager, AActor::Tick, [](AFGSchematicManager* SchematicManager, float) {
        AModContentRegistry* ContentRegistry = AModContentRegistry::Get(SchematicManager);
        if (ContentRegistry != NULL) {
            const int64 SchematicRegistryCounter = ContentRegistry->SchematicRegistryState.GetRegistrationCounter();
            int64& SchematicManagerState = ContentRegistry->SchematicManagerInternalState;
            
            if (SchematicRegistryCounter > SchematicManagerState) {
                ContentRegistry->FlushStateToSchematicManager(SchematicManager);
                SchematicManagerState = SchematicRegistryCounter;
            }
        }
    });

    SUBSCRIBE_VIRTUAL_FUNCTION_AFTER(AFGResearchManager, AActor::Tick, [](AFGResearchManager* ResearchManager, float) {
        AModContentRegistry* ContentRegistry = AModContentRegistry::Get(ResearchManager);
        if (ContentRegistry != NULL) {
            const int64 ResearchTreeRegistryCounter = ContentRegistry->ResearchTreeRegistryState.GetRegistrationCounter();
            int64& ResearchManagerState = ContentRegistry->ResearchManagerInternalState;

            if (ResearchTreeRegistryCounter > ResearchManagerState) {
                ContentRegistry->FlushStateToResearchManager(ResearchManager);
                ResearchManagerState = ResearchTreeRegistryCounter;
            }
        }
    });
}

void AModContentRegistry::FlushStateToSchematicManager(AFGSchematicManager* SchematicManager) const {
    const TArray<TSharedPtr<FSchematicRegistrationInfo>> RegisteredSchematics = SchematicRegistryState.GetAllObjects();

    //Empty lists while maintaining enough capacity to re-populate it later
    SchematicManager->mAllSchematics.Empty(RegisteredSchematics.Num());
    SchematicManager->mAvailableSchematics.Empty(RegisteredSchematics.Num());

    for (const TSharedPtr<FSchematicRegistrationInfo>& RegistrationInfo : RegisteredSchematics) {
        TSubclassOf<UFGSchematic> Schematic = RegistrationInfo->RegisteredObject;
        SchematicManager->mAllSchematics.Add(Schematic);
        if (UFGSchematic::GetType(Schematic) == ESchematicType::EST_Milestone) {
            SchematicManager->mAvailableSchematics.Add(Schematic);
        }
    }
}

void AModContentRegistry::FlushStateToResearchManager(AFGResearchManager* ResearchManager) const {
    const TArray<TSharedPtr<FResearchTreeRegistrationInfo>> RegisteredResearchTrees = ResearchTreeRegistryState.GetAllObjects();

    //Empty lists while maintaining enough capacity to re-populate it later
    ResearchManager->mAllResearchTrees.Empty(RegisteredResearchTrees.Num());

    for (const TSharedPtr<FResearchTreeRegistrationInfo>& RegistrationInfo : RegisteredResearchTrees) {
        TSubclassOf<UFGResearchTree> ResearchTree = RegistrationInfo->RegisteredObject;
        ResearchManager->mAllResearchTrees.Add(ResearchTree);
    }
}

void AModContentRegistry::Init() {
    //Register vanilla content in the registry
    const FString FactoryGame = FACTORYGAME_MOD_REFERENCE;

    const TArray<TSubclassOf<UFGSchematic>> AllSchematics = DiscoverVanillaContentOfType<UFGSchematic>();
    const TArray<TSubclassOf<UFGResearchTree>> AllResearchTrees = DiscoverVanillaContentOfType<UFGResearchTree>();
    
    for (const TSubclassOf<UFGSchematic>& Schematic : AllSchematics) {
        RegisterSchematic(FactoryGame, Schematic);
    }
    
    for (const TSubclassOf<UFGResearchTree>& ResearchTree : AllResearchTrees) {
        RegisterResearchTree(FactoryGame, ResearchTree);
    }
}

void AModContentRegistry::FreezeRegistryState() {
    checkf(!bIsRegistryFrozen, TEXT("Attempt to re-freeze already frozen registry"));

    SML_LOG(LogContentRegistry, Display, TEXT("Freezing content registry"));
    this->bIsRegistryFrozen = true;
}

void AModContentRegistry::EnsureRegistryUnfrozen() const {
    if (bIsRegistryFrozen) {
        SML_LOG(LogContentRegistry, Fatal, TEXT("Attempt to register object in frozen mod content registry"));
    }
}

void AModContentRegistry::CheckSavedDataForMissingObjects() {
    AFGRecipeManager* RecipeManager = AFGRecipeManager::Get(this);
    AFGSchematicManager* SchematicManager = AFGSchematicManager::Get(this);
    AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);

    TArray<FMissingObjectStruct> MissingObjects;
    if (ResearchManager != NULL) {
        FindMissingResearchTrees(ResearchManager, MissingObjects);
    }
    if (SchematicManager != NULL) {
        FindMissingSchematics(SchematicManager, MissingObjects);
    }
    if (RecipeManager != NULL) {
        FindMissingRecipes(RecipeManager, MissingObjects);
    }

    if (MissingObjects.Num() > 0) {
        WarnAboutMissingObjects(MissingObjects);
    }
}

void AModContentRegistry::MarkItemDescriptorsFromRecipe(const TSubclassOf<UFGRecipe>& Recipe,
                                                        const FString& ModReference) {
    TArray<FItemAmount> AllReferencedItems;
    AllReferencedItems.Append(UFGRecipe::GetIngredients(Recipe));
    AllReferencedItems.Append(UFGRecipe::GetProducts(Recipe));

    for (const FItemAmount& ItemAmount : AllReferencedItems) {
        const TSubclassOf<UFGItemDescriptor>& ItemDescriptor = ItemAmount.ItemClass;
        TSharedPtr<FItemRegistrationInfo> ItemRegistrationInfo = ItemRegistryState.FindObject(ItemDescriptor);
        if (!ItemRegistrationInfo.IsValid()) {
           ItemRegistrationInfo = RegisterItemDescriptor(ModReference, ItemDescriptor);
        }
        //Associate item registration info with this recipe
        ItemRegistrationInfo->ReferencedBy.AddUnique(Recipe);
    }
}

TSharedPtr<FItemRegistrationInfo> AModContentRegistry::RegisterItemDescriptor(const FString& ModReference, const TSubclassOf<UFGItemDescriptor>& ItemDescriptor) {
    return ItemRegistryState.RegisterObject(MakeRegistrationInfo<FItemRegistrationInfo>(ItemDescriptor, ModReference));
}

void AModContentRegistry::FindMissingSchematics(AFGSchematicManager* SchematicManager,
                                                TArray<FMissingObjectStruct>& MissingObjects) const {
    //Clear references to unlocked schematics if they are not registered
    TArray<TSubclassOf<UFGSchematic>> PurchasedSchematics = SchematicManager->mPurchasedSchematics;
    for (const TSubclassOf<UFGSchematic> Schematic : PurchasedSchematics) {
        if (!IsSchematicRegistered(Schematic)) {
            MissingObjects.Add(FMissingObjectStruct{TEXT("schematic"), Schematic->GetPathName()});
            SchematicManager->mPurchasedSchematics.Remove(Schematic);
        }
    }
    //Do same thing for incomplete schematic progress
    SchematicManager->mPaidOffSchematic.RemoveAll([&](const FSchematicCost& SchematicCost) {
        return !IsSchematicRegistered(SchematicCost.Schematic);
    });
}

void AModContentRegistry::FindMissingResearchTrees(AFGResearchManager* ResearchManager,
                                                   TArray<FMissingObjectStruct>& MissingObjects) const {
    //Clear unlocked research trees
    TArray<TSubclassOf<UFGResearchTree>> UnlockedResearchTrees = ResearchManager->mUnlockedResearchTrees;
    for (const TSubclassOf<UFGResearchTree>& ResearchTree : UnlockedResearchTrees) {
        if (!IsResearchTreeRegistered(ResearchTree)) {
            ResearchManager->mUnlockedResearchTrees.Remove(ResearchTree);
            MissingObjects.Add(FMissingObjectStruct{TEXT("research_tree"), ResearchTree->GetPathName()});
        }
    }
    
    //Clear completed, but unclaimed researches
    ResearchManager->mCompletedResearch.RemoveAll([&](const FResearchData& ResearchData) {
        return !IsResearchTreeRegistered(ResearchData.InitiatingResearchTree) ||
            !IsSchematicRegistered(ResearchData.Schematic);
    });
    
    //Clear ongoing research data
    ResearchManager->mOngoingResearch.RemoveAll([&](const FResearchTime& ResearchTime){
        return !IsResearchTreeRegistered(ResearchTime.ResearchData.InitiatingResearchTree) ||
          !IsSchematicRegistered(ResearchTime.ResearchData.Schematic);
    });
}

void AModContentRegistry::FindMissingRecipes(AFGRecipeManager* RecipeManager,
                                             TArray<FMissingObjectStruct>& MissingObjects) const {
    //Clear unlocked recipes
    TArray<TSubclassOf<UFGRecipe>> UnlockedRecipes = RecipeManager->mAvailableRecipes;
    for (const TSubclassOf<UFGRecipe>& Recipe : UnlockedRecipes) {
        if (!IsRecipeRegistered(Recipe)) {
            RecipeManager->mAvailableRecipes.Remove(Recipe);
            MissingObjects.Add(FMissingObjectStruct{TEXT("recipe"), Recipe->GetPathName()});
        }
    }
}

void AModContentRegistry::WarnAboutMissingObjects(const TArray<FMissingObjectStruct>& MissingObjects) {
    SML_LOG(LogContentRegistry, Error, TEXT("---------------------------------------------"));
    SML_LOG(LogContentRegistry, Error, TEXT("Found unregistered objects referenced in savegame:"));
    for (const FMissingObjectStruct& ObjectStruct : MissingObjects) {
        SML_LOG(LogContentRegistry, Error, TEXT("%s: %s"), *ObjectStruct.ObjectType, *ObjectStruct.ObjectPath);
    }
    SML_LOG(LogContentRegistry, Error, TEXT("They will be cleared out"));
    SML_LOG(LogContentRegistry, Error, TEXT("---------------------------------------------"));
}

void AModContentRegistry::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector) {
    AModContentRegistry* ModContentRegistry = Cast<AModContentRegistry>(InThis);
    //Register all non-UPROPERTY referenced objects from registry states (registry states cannot be UPROPERTY() because they are templates!)
    ModContentRegistry->ItemRegistryState.AddReferencedObjects(InThis, Collector);
    ModContentRegistry->RecipeRegistryState.AddReferencedObjects(InThis, Collector);
    ModContentRegistry->SchematicRegistryState.AddReferencedObjects(InThis, Collector);
    ModContentRegistry->ResearchTreeRegistryState.AddReferencedObjects(InThis, Collector);
}

void AModContentRegistry::RegisterSchematic(const FString& ModReference, TSubclassOf<UFGSchematic> Schematic) {
    check(Schematic.Get() != NULL);

    if (!SchematicRegistryState.ContainsObject(Schematic)) {
        EnsureRegistryUnfrozen();
        AFGSchematicManager* SchematicManager = AFGSchematicManager::Get(this);
        check(SchematicManager);

        //Create registration entry and register
        const TSharedPtr<FSchematicRegistrationInfo> RegistrationInfo = SchematicRegistryState.RegisterObject(
            MakeRegistrationInfo<FSchematicRegistrationInfo>(Schematic, ModReference));

        //Register referenced recipes automatically and associate schematic with them
        TArray<TSubclassOf<UFGRecipe>> OutReferencedRecipes;
        ExtractRecipesFromSchematic(Schematic, OutReferencedRecipes);
        for (const TSubclassOf<UFGRecipe>& Recipe : OutReferencedRecipes) {
            RegisterRecipe(ModReference, Recipe);
            const TSharedPtr<FRecipeRegistrationInfo> RecipeRegistrationInfo = RecipeRegistryState.FindObject(Recipe);
            RecipeRegistrationInfo->ReferencedBy.Add(Schematic);
        }

        //Process registration callback delegate
        OnSchematicRegistered.Broadcast(Schematic, *RegistrationInfo);
    }
}

void AModContentRegistry::RegisterResearchTree(const FString& ModReference, TSubclassOf<UFGResearchTree> ResearchTree) {
    check(ResearchTree.Get() != NULL);

    if (!ResearchTreeRegistryState.ContainsObject(ResearchTree)) {
        EnsureRegistryUnfrozen();
        AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);
        check(ResearchManager);

        //Create registration entry and register
        const TSharedPtr<FResearchTreeRegistrationInfo> RegistrationInfo = ResearchTreeRegistryState.RegisterObject(
            MakeRegistrationInfo<FResearchTreeRegistrationInfo>(ResearchTree, ModReference));

        //Register referenced schematics automatically and associate research tree with them
        TArray<TSubclassOf<UFGSchematic>> OutReferencedSchematics;
        ExtractSchematicsFromResearchTree(ResearchTree, OutReferencedSchematics);
        for (const TSubclassOf<UFGSchematic>& Schematic : OutReferencedSchematics) {
            RegisterSchematic(ModReference, Schematic);
            const TSharedPtr<FSchematicRegistrationInfo> SchematicRegistrationInfo = SchematicRegistryState.FindObject(Schematic);
            SchematicRegistrationInfo->ReferencedBy.Add(ResearchTree);
        }
        //Process registration callback
        OnResearchTreeRegistered.Broadcast(ResearchTree, *RegistrationInfo);
    }
}

void AModContentRegistry::RegisterRecipe(const FString& ModReference, TSubclassOf<UFGRecipe> Recipe) {
    check(Recipe.Get() != NULL);

    if (!RecipeRegistryState.ContainsObject(Recipe)) {
        EnsureRegistryUnfrozen();
        
        //Create registration entry and register
        const TSharedPtr<FRecipeRegistrationInfo> RegistrationInfo = RecipeRegistryState.RegisterObject(
            MakeRegistrationInfo<FRecipeRegistrationInfo>(Recipe, ModReference));

        //Process registration callback
        OnRecipeRegistered.Broadcast(Recipe, *RegistrationInfo);
    }
}

//TODO should this be callable only on host and then replicated down to clients, like with all other methods here?
void AModContentRegistry::RegisterResourceSinkItemPointTable(const FString& ModReference, UDataTable* PointTable) {
    AFGResourceSinkSubsystem* ResourceSinkSubsystem = AFGResourceSinkSubsystem::Get(this);

    if (ResourceSinkSubsystem != NULL && PointTable != NULL) {
        checkf(PointTable->RowStruct != nullptr &&
               PointTable->RowStruct->IsChildOf(FResourceSinkPointsData::StaticStruct()),
               TEXT("Invalid AWESOME Sink item points table in mod %s: Row Type should be Resource Sink Points Data"),
               *ModReference);
        TArray<FResourceSinkPointsData*> OutModPointsData;
        PointTable->GetAllRows(TEXT("ResourceSinkPointsData"), OutModPointsData);
        for (FResourceSinkPointsData* ModItemRow : OutModPointsData) {
            int32 Points = FMath::Max(ModItemRow->Points, ModItemRow->OverriddenResourceSinkPoints);
            ResourceSinkSubsystem->mResourceSinkPoints.Add(ModItemRow->ItemClass, Points);
        }
    }
}

TArray<FItemRegistrationInfo> AModContentRegistry::GetLoadedItemDescriptors() {
    //Since we don't have consistent registry, we have to iterate all loaded classes and generate information from them
    //We also keep all referenced classes loaded, so they will be included there too
    TArray<FItemRegistrationInfo> OutRegistrationInfo;
    
    UClass* ItemDescriptorClass = UFGItemDescriptor::StaticClass();
    ForEachObjectOfClass(UClass::StaticClass(), [&](UObject* LoadedClassObject) {
        UClass* Class = Cast<UClass>(LoadedClassObject);
        if (Class->IsChildOf(ItemDescriptorClass)) {
            const TSubclassOf<UFGItemDescriptor> ItemDescriptor = Class;
            OutRegistrationInfo.Add(GetItemDescriptorInfo(ItemDescriptor));
        }
    });
    return OutRegistrationInfo;
}

TArray<FItemRegistrationInfo> AModContentRegistry::GetObtainableItemDescriptors() const {
    //All obtainable item descriptors are guaranteed to be present in ItemDescriptorRegistrationList,
    //So we can just iterate it and filter item descriptors without associated recipes out
    TArray<FItemRegistrationInfo> OutRegistrationInfo;
    
    for (const TSharedPtr<FItemRegistrationInfo>& RegistrationInfo : ItemRegistryState.GetAllObjects()) {
        if (RegistrationInfo->ReferencedBy.Num() > 0) {
            OutRegistrationInfo.Add(*RegistrationInfo);
        }
    }
    return OutRegistrationInfo;
}

FItemRegistrationInfo AModContentRegistry::GetItemDescriptorInfo(TSubclassOf<UFGItemDescriptor> ItemDescriptor) {
    //Use cached registration information if it's available
    const TSharedPtr<FItemRegistrationInfo> CachedRegistrationInfo = ItemRegistryState.FindObject(ItemDescriptor);
    if (CachedRegistrationInfo.IsValid()) {
        return *CachedRegistrationInfo;
    }
    //Item descriptor was not referenced in any registered recipe, generate dummy registration info in runtime
    const FString GuessedModReference = GetClassOwnerModReference(ItemDescriptor);
    return *RegisterItemDescriptor(GuessedModReference, ItemDescriptor);
}


AModContentRegistry::AModContentRegistry() {
    bReplicates = true;
    bAlwaysRelevant = true;
    bIsRegistryFrozen = false;
    SchematicManagerInternalState = -1;
    ResearchManagerInternalState = -1;
}

AModContentRegistry* AModContentRegistry::Get(UObject* WorldContext) {
    USMLSubsystemHolder* SubsystemHolder = UModSubsystemHolder::GetSubsystemHolder<USMLSubsystemHolder>(WorldContext);
    return SubsystemHolder != NULL ? SubsystemHolder->GetModContentRegistry() : NULL;
}

void AModContentRegistry::BeginPlay() {
    //Freeze registry now, when BeginPlay is dispatched we already have save loaded
    FreezeRegistryState();
    CheckSavedDataForMissingObjects();
}

FString AModContentRegistry::GetClassOwnerModReference(UClass* ClassObject) {
    check(ClassObject);
    const FString& PackagePathName = ClassObject->GetOuterUPackage()->GetPathName();

    if (PackagePathName.StartsWith(TEXT("/Game/"))) {
        //Class is blueprint class located inside game's content directory
        const FString TrimmedPathName = PackagePathName.Mid(6);
        int32 FirstSlashIndex;
        TrimmedPathName.FindChar(TEXT('/'), FirstSlashIndex);
        if (FirstSlashIndex == INDEX_NONE)
            FirstSlashIndex = TrimmedPathName.Len();
        //Take second part between two slashes, so /Game/SML/Example will evaluate to SML
        return TrimmedPathName.Mid(0, FirstSlashIndex);
    }
    if (PackagePathName.StartsWith(TEXT("/Script/"))) {
        //Class is defined in native package, their names follow pattern /Script/ModuleName
        //And usually ModuleName matches ModReference
        const FString OwnerModuleName = PackagePathName.Mid(8);
        return OwnerModuleName;
    }
    if (PackagePathName.StartsWith(TEXT("/Engine/"))) {
        //We assume all engine files to be owned by FactoryGame directly
        return TEXT("FactoryGame");
    }
    //Otherwise it should be /Config/ or something like that. Either way, we fallback to FactoryGame
    return TEXT("FactoryGame");
}

void AModContentRegistry::RegisterOverwriteForMod(const FString& ModReference, const FString& OverwritePath) {
    if (ModOverwriteMap.Contains(OverwritePath)) {
        const FString OldModReference = ModOverwriteMap.FindChecked(OverwritePath);
        SML_LOG(LogContentRegistry, Error,
            TEXT("SML detected two mods trying to overwrite same asset at path '"), *OverwritePath, TEXT("': "),
            *ModReference, TEXT(" and "), *OldModReference);
        SML_LOG(LogContentRegistry, Error,
            TEXT("This setup is not stable, and mods can break depending on which overwrite takes precedence"));
        SML_LOG(LogContentRegistry, Error, TEXT("Proceed with caution, and make sure to report to mod authors about the conflict"));
    }
    ModOverwriteMap.Add(OverwritePath, ModReference);
}

FString AModContentRegistry::FindOverwriteOwner(UClass* Class, const TCHAR* Fallback) {
    const FString PackageName = Class->GetOuterUPackage()->GetPathName();
    if (ModOverwriteMap.Contains(PackageName)) {
        return ModOverwriteMap.FindChecked(PackageName);
    }
    return Fallback;
}

void AModContentRegistry::DiscoverOverwriteListForModReference(const FString& ModReference) {
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    const FString DirectoryPath = FPaths::Combine(FPaths::ProjectContentDir(), ModReference, TEXT("ModOverwriteLists"));
    TArray<FString> ResultOverwriteArray;
    PlatformFile.IterateDirectory(*DirectoryPath, [&ResultOverwriteArray](const TCHAR* FilenameOrDirectory, bool bIsDirectory) {
        const FString FilenameString = FilenameOrDirectory;
        if (!bIsDirectory && FPaths::GetExtension(FilenameOrDirectory) == TEXT("txt")) {
            FFileHelper::LoadFileToStringArray(ResultOverwriteArray, FilenameOrDirectory);
        }
        return true;
    });
    for (const FString& ResultString : ResultOverwriteArray) {
        if (ResultString.StartsWith(TEXT("#")))
            continue; //Skip comments starting with #
        RegisterOverwriteForMod(ModReference, ResultString);
    }
}
