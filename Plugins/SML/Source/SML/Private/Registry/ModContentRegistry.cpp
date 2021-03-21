#include "Registry/ModContentRegistry.h"
#include "FGRecipeManager.h"
#include "FGResearchManager.h"
#include "FGResourceSinkSettings.h"
#include "FGResourceSinkSubsystem.h"
#include "FGSchematicManager.h"
#include "Unlocks/FGUnlockRecipe.h"
#include "IPlatformFilePak.h"
#include "Subsystem/ModSubsystemHolder.h"
#include "Patching/NativeHookManager.h"
#include "Reflection/ReflectionHelper.h"
#include "Subsystem/SMLSubsystemHolder.h"
#include "Engine/AssetManager.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Util/BlueprintAssetHelperLibrary.h"

DEFINE_LOG_CATEGORY(LogContentRegistry);

static bool GIsRegisteringVanillaContent = false;

void ExtractRecipesFromSchematic(TSubclassOf<UFGSchematic> Schematic, TArray<TSubclassOf<UFGRecipe>>& OutRecipes) {
    const TArray<UFGUnlock*> Unlocks = UFGSchematic::GetUnlocks(Schematic);
    for (UFGUnlock* Unlock : Unlocks) {
        if (UFGUnlockRecipe* UnlockRecipe = Cast<UFGUnlockRecipe>(Unlock)) {
            OutRecipes.Append(UnlockRecipe->GetRecipesToUnlock());
        }
    }
}

void ExtractSchematicsFromResearchTree(TSubclassOf<UFGResearchTree> ResearchTree, TArray<TSubclassOf<UFGSchematic>>& OutSchematics) {
    
    static UStructProperty* NodeDataStructProperty = NULL;
    static UClassProperty* SchematicStructProperty = NULL;
    static UClass* ResearchTreeNodeClass = NULL;
    
    //Lazily initialize research tree node reflection properties for faster access
    if (ResearchTreeNodeClass == NULL) {
        ResearchTreeNodeClass = LoadClass<UFGResearchTreeNode>(NULL, TEXT("/Game/FactoryGame/Schematics/Research/BPD_ResearchTreeNode.BPD_ResearchTreeNode_C"));
        check(ResearchTreeNodeClass);
        //Make sure class is not garbage collected
        ResearchTreeNodeClass->AddToRoot();
        
        NodeDataStructProperty = FReflectionHelper::FindPropertyChecked<UStructProperty>(ResearchTreeNodeClass, TEXT("mNodeDataStruct"));
        SchematicStructProperty = FReflectionHelper::FindPropertyByShortNameChecked<UClassProperty>(NodeDataStructProperty->Struct, TEXT("Schematic"));
        
        check(SchematicStructProperty->MetaClass->IsChildOf(UFGSchematic::StaticClass()));
    }

    const TArray<UFGResearchTreeNode*> Nodes = UFGResearchTree::GetNodes(ResearchTree);
    for (UFGResearchTreeNode* Node : Nodes) {
        if (!Node->IsA(ResearchTreeNodeClass)) {
            UE_LOG(LogContentRegistry, Warning,
                TEXT("Unsupported node class %s for research tree %s"), *Node->GetClass()->GetPathName(),
                *ResearchTree->GetPathName());
            continue;
        }
        const void* NodeDataStructPtr = NodeDataStructProperty->ContainerPtrToValuePtr<void>(Node);
        UClass* SchematicClass = Cast<UClass>(SchematicStructProperty->GetPropertyValue_InContainer(NodeDataStructPtr));
        if (SchematicClass == NULL) {
            UE_LOG(LogContentRegistry, Warning,
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
        FAssetDataTagMapSharedView::FFindTagResult GeneratedClassTextPath = AssetData.TagsAndValues.FindTag(FBlueprintTags::GeneratedClassPath);
        if (GeneratedClassTextPath.IsSet()) {
            const FString BlueprintClassPath = FPackageName::ExportTextPathToObjectPath(GeneratedClassTextPath.GetValue());
            UClass* LoadedClass = LoadClass<T>(NULL, *BlueprintClassPath);
            if (LoadedClass != NULL) {
                OutVanillaContent.Add(LoadedClass);
            }
        }
    }
    UE_LOG(LogContentRegistry, Display, TEXT("Discovered %d vanilla assets of type %s"), OutVanillaContent.Num(), *PrimaryAssetClass->GetName());
    return OutVanillaContent;
}

void AModContentRegistry::DisableVanillaContentRegistration() {
    //Prevent unnecessary vanilla schematic list population -
    //we are overriding it from content registry anyway, so let's save some processing time
    SUBSCRIBE_METHOD(AFGSchematicManager::PopulateSchematicsLists,
        [](auto& Call, AFGSchematicManager*) { Call.Cancel(); });
    SUBSCRIBE_METHOD(AFGSchematicManager::PopulateAvailableSchematicsList,
        [](auto& Call, AFGSchematicManager*) { Call.Cancel(); });
    SUBSCRIBE_METHOD(AFGResearchManager::PopulateResearchTreeList,
        [](auto& Call, AFGResearchManager*) { Call.Cancel(); });
}

FName AModContentRegistry::FindContentOwnerFast(UClass* ContentClass) {
    //Shortcut used for quickly registering vanilla content
    if (GIsRegisteringVanillaContent) {
        return FACTORYGAME_MOD_NAME;
    }
    
    //Use GetName on package instead of GetPathName() because it's faster and avoids string concat
    const FString ContentOwnerName = UBlueprintAssetHelperLibrary::FindPluginNameByObjectPath(ContentClass->GetOuterUPackage()->GetName());
    if (ContentOwnerName.IsEmpty()) {
        UE_LOG(LogContentRegistry, Error, TEXT("Failed to determine content owner for object %s. This is an error, report to mod author!"), *ContentClass->GetPathName());
        return FACTORYGAME_MOD_NAME;
    }
    return *ContentOwnerName;
}

void AModContentRegistry::FlushStateToSchematicManager(AFGSchematicManager* SchematicManager) const {
    const TArray<TSharedPtr<FSchematicRegistrationInfo>> RegisteredSchematics = SchematicRegistryState.GetAllObjects();

    //Empty lists while maintaining enough capacity to re-populate it later
    SchematicManager->mAllSchematics.Empty(RegisteredSchematics.Num());
    SchematicManager->mAvailableSchematics.Empty(RegisteredSchematics.Num());

    for (const TSharedPtr<FSchematicRegistrationInfo>& RegistrationInfo : RegisteredSchematics) {
        TSubclassOf<UFGSchematic> Schematic = RegistrationInfo->RegisteredObject;
        SchematicManager->mAllSchematics.Add(Schematic);

        if ((UFGSchematic::GetType(Schematic) == ESchematicType::EST_Milestone ||
            UFGSchematic::GetType(Schematic) == ESchematicType::EST_Tutorial ||
            UFGSchematic::GetType(Schematic) == ESchematicType::EST_ResourceSink) &&
            SchematicManager->CanGiveAccessToSchematic(Schematic)) {
            SchematicManager->mAvailableSchematics.Add(Schematic);
        }
    }
}

void AModContentRegistry::FlushStateToResearchManager(AFGResearchManager* ResearchManager) const {
    const TArray<TSharedPtr<FResearchTreeRegistrationInfo>> RegisteredResearchTrees = ResearchTreeRegistryState.GetAllObjects();

    //Empty lists while maintaining enough capacity to re-populate it later
    ResearchManager->mAvailableResearchTrees.Empty(RegisteredResearchTrees.Num());

    for (const TSharedPtr<FResearchTreeRegistrationInfo>& RegistrationInfo : RegisteredResearchTrees) {
        TSubclassOf<UFGResearchTree> ResearchTree = RegistrationInfo->RegisteredObject;
        ResearchManager->mAvailableResearchTrees.Add(ResearchTree);
    }
    //Update unlocked research trees
    ResearchManager->UpdateUnlockedResearchTrees();
}

void AModContentRegistry::SubscribeToSchematicManager(AFGSchematicManager* SchematicManager) {
    FScriptDelegate ScriptDelegate;
    ScriptDelegate.BindUFunction(this, GET_FUNCTION_NAME_STRING_CHECKED(AModContentRegistry, OnSchematicPurchased));
    SchematicManager->PurchasedSchematicDelegate.AddUnique(ScriptDelegate);
}

void AModContentRegistry::Init() {
    //Register vanilla content in the registry
    const FName FactoryGame = FACTORYGAME_MOD_NAME;

    UE_LOG(LogContentRegistry, Display, TEXT("Initializing mod content registry"));
    const TArray<TSubclassOf<UFGSchematic>> AllSchematics = DiscoverVanillaContentOfType<UFGSchematic>();
    const TArray<TSubclassOf<UFGResearchTree>> AllResearchTrees = DiscoverVanillaContentOfType<UFGResearchTree>();

    //Start registering vanilla content now
    GIsRegisteringVanillaContent = true;
    
    for (const TSubclassOf<UFGSchematic>& Schematic : AllSchematics) {
        if (UFGSchematic::GetType(Schematic) != ESchematicType::EST_Alternate) {
            RegisterSchematic(FactoryGame, Schematic);
        }
    }
    
    for (const TSubclassOf<UFGResearchTree>& ResearchTree : AllResearchTrees) {
        RegisterResearchTree(FactoryGame, ResearchTree);
    }

    //Stop registering vanilla content at this point
    GIsRegisteringVanillaContent = false;
}

void AModContentRegistry::FreezeRegistryState() {
    checkf(!bIsRegistryFrozen, TEXT("Attempt to re-freeze already frozen registry"));

    UE_LOG(LogContentRegistry, Display, TEXT("Freezing content registry"));
    this->bIsRegistryFrozen = true;
}

void AModContentRegistry::EnsureRegistryUnfrozen() const {
    if (bIsRegistryFrozen) {
        UE_LOG(LogContentRegistry, Fatal, TEXT("Attempt to register object in frozen mod content registry"));
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

void AModContentRegistry::OnSchematicPurchased(TSubclassOf<UFGSchematic> Schematic) {
    //Update research trees in case they depend on schematic unlocked dependency
    AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);
    if (ResearchManager != NULL && ResearchManager->HasAuthority()) {
        ResearchManager->UpdateUnlockedResearchTrees();
    }
}

void AModContentRegistry::MarkItemDescriptorsFromRecipe(const TSubclassOf<UFGRecipe>& Recipe, const FName ModReference) {
    TArray<FItemAmount> AllReferencedItems;
    AllReferencedItems.Append(UFGRecipe::GetIngredients(Recipe));
    AllReferencedItems.Append(UFGRecipe::GetProducts(Recipe));

    for (const FItemAmount& ItemAmount : AllReferencedItems) {
        const TSubclassOf<UFGItemDescriptor>& ItemDescriptor = ItemAmount.ItemClass;
        TSharedPtr<FItemRegistrationInfo> ItemRegistrationInfo = ItemRegistryState.FindObject(ItemDescriptor);
        if (!ItemRegistrationInfo.IsValid()) {
            const FName OwnerModReference = FindContentOwnerFast(ItemDescriptor);
            ItemRegistrationInfo = RegisterItemDescriptor(OwnerModReference, ModReference, ItemDescriptor);
        }
        //Associate item registration info with this recipe
        ItemRegistrationInfo->ReferencedBy.AddUnique(Recipe);
    }
}

TSharedPtr<FItemRegistrationInfo> AModContentRegistry::RegisterItemDescriptor(const FName OwnerModReference, const FName RegistrarModReference, const TSubclassOf<UFGItemDescriptor>& ItemDescriptor) {
    return ItemRegistryState.RegisterObject(MakeRegistrationInfo<FItemRegistrationInfo>(ItemDescriptor, OwnerModReference, RegistrarModReference));
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
    UE_LOG(LogContentRegistry, Error, TEXT("---------------------------------------------"));
    UE_LOG(LogContentRegistry, Error, TEXT("Found unregistered objects referenced in savegame:"));
    for (const FMissingObjectStruct& ObjectStruct : MissingObjects) {
        UE_LOG(LogContentRegistry, Error, TEXT("%s: %s"), *ObjectStruct.ObjectType, *ObjectStruct.ObjectPath);
    }
    UE_LOG(LogContentRegistry, Error, TEXT("They will be cleared out"));
    UE_LOG(LogContentRegistry, Error, TEXT("---------------------------------------------"));
}

void AModContentRegistry::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector) {
    AModContentRegistry* ModContentRegistry = Cast<AModContentRegistry>(InThis);
    //Register all non-UPROPERTY referenced objects from registry states (registry states cannot be UPROPERTY() because they are templates!)
    ModContentRegistry->ItemRegistryState.AddReferencedObjects(InThis, Collector);
    ModContentRegistry->RecipeRegistryState.AddReferencedObjects(InThis, Collector);
    ModContentRegistry->SchematicRegistryState.AddReferencedObjects(InThis, Collector);
    ModContentRegistry->ResearchTreeRegistryState.AddReferencedObjects(InThis, Collector);
}

void AModContentRegistry::RegisterSchematic(FName ModReference, TSubclassOf<UFGSchematic> Schematic) {
    check(Schematic.Get() != NULL);

    if (!SchematicRegistryState.ContainsObject(Schematic)) {
        EnsureRegistryUnfrozen();

        //Create registration entry and register
        const FName OwnerModReference = FindContentOwnerFast(Schematic);
        const TSharedPtr<FSchematicRegistrationInfo> RegistrationInfo = SchematicRegistryState.RegisterObject(
            MakeRegistrationInfo<FSchematicRegistrationInfo>(Schematic, OwnerModReference, ModReference));

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

void AModContentRegistry::RegisterResearchTree(FName ModReference, TSubclassOf<UFGResearchTree> ResearchTree) {
    check(ResearchTree.Get() != NULL);

    if (!ResearchTreeRegistryState.ContainsObject(ResearchTree)) {
        EnsureRegistryUnfrozen();

        //Create registration entry and register
        const FName OwnerModReference = FindContentOwnerFast(ResearchTree);
        const TSharedPtr<FResearchTreeRegistrationInfo> RegistrationInfo = ResearchTreeRegistryState.RegisterObject(
            MakeRegistrationInfo<FResearchTreeRegistrationInfo>(ResearchTree, OwnerModReference, ModReference));
        
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

void AModContentRegistry::RegisterRecipe(FName ModReference, TSubclassOf<UFGRecipe> Recipe) {
    check(Recipe.Get() != NULL);

    if (!RecipeRegistryState.ContainsObject(Recipe)) {
        EnsureRegistryUnfrozen();
        
        //Create registration entry and register
        const FName OwnerModReference = FindContentOwnerFast(Recipe);
        const TSharedPtr<FRecipeRegistrationInfo> RegistrationInfo = RecipeRegistryState.RegisterObject(
            MakeRegistrationInfo<FRecipeRegistrationInfo>(Recipe, OwnerModReference, ModReference));

        //Process registration callback
        OnRecipeRegistered.Broadcast(Recipe, *RegistrationInfo);

        //Associate referenced item descriptors with this recipe registrar
        MarkItemDescriptorsFromRecipe(Recipe, ModReference);
    }
}

void AModContentRegistry::RegisterResourceSinkItemPointTable(FName ModReference, UDataTable* PointTable) {
    AFGResourceSinkSubsystem* ResourceSinkSubsystem = AFGResourceSinkSubsystem::Get(this);

    if (ResourceSinkSubsystem != NULL && PointTable != NULL) {
        checkf(PointTable->RowStruct != nullptr &&
               PointTable->RowStruct->IsChildOf(FResourceSinkPointsData::StaticStruct()),
               TEXT("Invalid AWESOME Sink item points table in mod %s: Row Type should be Resource Sink Points Data"),
               *ModReference.ToString());
        
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
    //Item descriptor was not referenced in any registered recipe, fallback to registrar name = owner name logic
    const FName OwnerModReference = FindContentOwnerFast(ItemDescriptor);
    return *RegisterItemDescriptor(OwnerModReference, OwnerModReference, ItemDescriptor);
}


AModContentRegistry::AModContentRegistry() {
    bReplicates = true;
    bAlwaysRelevant = true;
    bIsRegistryFrozen = false;
    SchematicManagerInternalState = -1;
    ResearchManagerInternalState = -1;
    bSubscribedToSchematicManager = false;
    PrimaryActorTick.bCanEverTick = true;
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

void AModContentRegistry::Tick(float DeltaSeconds) {
    //Make sure vanilla states are up to date with registry
    AFGSchematicManager* SchematicManager = AFGSchematicManager::Get(this);
    AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);
    
    if (SchematicManager != NULL) {
        const int64 SchematicRegistryCounter = SchematicRegistryState.GetRegistrationCounter();
        
        if (SchematicRegistryCounter > SchematicManagerInternalState) {
            FlushStateToSchematicManager(SchematicManager);
            SchematicManagerInternalState = SchematicRegistryCounter;
        }

        if (!bSubscribedToSchematicManager) {
            SubscribeToSchematicManager(SchematicManager);
            bSubscribedToSchematicManager = true;
        }
    }
    
    if (ResearchManager != NULL) {
        const int64 ResearchTreeRegistryCounter = ResearchTreeRegistryState.GetRegistrationCounter();
        
        if (ResearchTreeRegistryCounter > ResearchManagerInternalState) {
            FlushStateToResearchManager(ResearchManager);
            ResearchManagerInternalState = ResearchTreeRegistryCounter;
        }
    }
}