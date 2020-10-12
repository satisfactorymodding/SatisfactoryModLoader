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
#include "mod/ModSubsystems.h"
#include "util/Logging.h"
#include "util/ReflectionHelper.h"

IMPLEMENT_FG_SAVE_INTERFACE(AModContentRegistry, false, true);

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
            SML::Logging::Format::warning(
                TEXT("Unsupported node class %s for research tree %s"), *Node->GetClass()->GetPathName(),
                *ResearchTree->GetPathName());
            continue;
        }
        const void* NodeDataStructPtr = NodeDataStructProperty->ContainerPtrToValuePtr<void>(Node);
        UClass* SchematicClass = Cast<UClass>(SchematicStructProperty->GetPropertyValue_InContainer(NodeDataStructPtr));
        if (SchematicClass == NULL) {
            SML::Logging::Format::warning(
                TEXT("Schematic not set on research tree %s, node %s"), *ResearchTree->GetPathName(),
                *Node->GetClass()->GetPathName());
            continue;
        }
        OutSchematics.Add(SchematicClass);
    }
}

void AModContentRegistry::Init() {
    AFGSchematicManager* SchematicManager = AFGSchematicManager::Get(this);
    AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);

    //Register vanilla content in the registry now
    const FString FactoryGame = FACTORYGAME_MOD_REFERENCE;
    this->bIsRegisteringVanillaContent = true;

    for (const TSubclassOf<UFGSchematic>& Schematic : SchematicManager->mAllSchematics) {
        //Just register entry, no need to register dependent schematics for vanilla
        RegisterSchematic(FactoryGame, Schematic);
    }
    
    for (const TSubclassOf<UFGResearchTree>& ResearchTree : ResearchManager->mAllResearchTrees) {
        //Just register entry, no need to register dependent schematics for vanilla
        RegisterResearchTree(FactoryGame, ResearchTree);
    }
    this->bIsRegisteringVanillaContent = false;
}

void AModContentRegistry::FreezeRegistryState() {
    checkf(!bIsRegistryFrozen, TEXT("Attempt to re-freeze already frozen registry"));

    SML::Logging::Format::info(TEXT("Freezing content registry"));
    this->bIsRegistryFrozen = true;

    AFGRecipeManager* RecipeManager = AFGRecipeManager::Get(this);
    AFGSchematicManager* SchematicManager = AFGSchematicManager::Get(this);
    AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);

    TArray<FMissingObjectStruct> MissingObjects;
    FindMissingResearchTrees(ResearchManager, MissingObjects);
    FindMissingSchematics(SchematicManager, MissingObjects);
    FindMissingRecipes(RecipeManager, MissingObjects);

    if (MissingObjects.Num() > 0) {
        WarnAboutMissingObjects(MissingObjects);
    }
}

void AModContentRegistry::EnsureRegistryUnfrozen() const {
    if (bIsRegistryFrozen) {
        checkf(0, TEXT("Attempt to register object in frozen mod content registry"));
        //Just in case of checks being disabled, this should 100% crash
        SML::Logging::Format::fatal(TEXT("Attempt to register object in frozen mod content registry"));
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

void AModContentRegistry::RegisterSchematicInternal(AFGSchematicManager* SchematicManager,
                                                    const TSubclassOf<UFGSchematic>& Schematic) {
    //Skip performing schematic manager registration if we are registering vanilla content
    if (!bIsRegisteringVanillaContent) {
        SchematicManager->mAllSchematics.Add(Schematic);
        if (UFGSchematic::GetType(Schematic) == ESchematicType::EST_Milestone) {
            SchematicManager->mPurchasedSchematics.Add(Schematic);
        }
    }
}

void AModContentRegistry::RegisterResearchTreeInternal(AFGResearchManager* ResearchManager,
                                                       const TSubclassOf<UFGResearchTree>& ResearchTree) {
    //Skip performing research manager registration if we are registering vanilla content
    if (!bIsRegisteringVanillaContent) {
        ResearchManager->mAllResearchTrees.Add(ResearchTree);
        //Schedule research tree re-scan so it can be unlocked automatically
        ResearchManager->UpdateUnlockedResearchTrees();
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
    TArray<FSchematicCost> PayedOffSchematics = SchematicManager->mPaidOffSchematic;
    for (const FSchematicCost& SchematicCost : PayedOffSchematics) {
        if (!IsSchematicRegistered(SchematicCost.Schematic)) {
            MissingObjects.Add(FMissingObjectStruct{TEXT("schematic"), SchematicCost.Schematic->GetPathName()});
            SchematicManager->mPaidOffSchematic.Remove(SchematicCost);
        }
    }
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
    TArray<FResearchData> CompletedResearch = ResearchManager->mCompletedResearch;
    for (const FResearchData& ResearchData : CompletedResearch) {
        if (!IsResearchTreeRegistered(ResearchData.InitiatingResearchTree) ||
            !IsSchematicRegistered(ResearchData.Schematic)) {
            ResearchManager->mCompletedResearch.Remove(ResearchData);
        }
    }
    //Clear ongoing research data
    TArray<FResearchTime> OngoingResearch = ResearchManager->mOngoingResearch;
    for (const FResearchTime& ResearchTime : OngoingResearch) {
        if (!IsResearchTreeRegistered(ResearchTime.ResearchData.InitiatingResearchTree) ||
            !IsSchematicRegistered(ResearchTime.ResearchData.Schematic)) {
            ResearchManager->mOngoingResearch.Remove(ResearchTime);
        }
    }
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
    SML::Logging::Format::error(TEXT("---------------------------------------------"));
    SML::Logging::Format::error(TEXT("Found unregistered objects referenced in savegame:"));
    for (const FMissingObjectStruct& ObjectStruct : MissingObjects) {
        SML::Logging::Format::error(TEXT("%s: %s"), *ObjectStruct.ObjectType, *ObjectStruct.ObjectPath);
    }
    SML::Logging::Format::error(TEXT("They will be cleared out"));
    SML::Logging::Format::error(TEXT("---------------------------------------------"));
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
        RegisterSchematicInternal(SchematicManager, Schematic);

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
        RegisterResearchTreeInternal(ResearchManager, ResearchTree);

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
    bIsRegisteringVanillaContent = false;
}

AModContentRegistry* AModContentRegistry::Get(UObject* WorldContext) {
    USMLSubsystemHolder* SubsystemHolder = GetSubsystemHolder<USMLSubsystemHolder>(WorldContext);
    return SubsystemHolder != NULL ? SubsystemHolder->GetModContentRegistry() : NULL;
}

void AModContentRegistry::BeginPlay() {
    //Freeze registry now, when BeginPlay is dispatched we already have save loaded
    FreezeRegistryState();
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
        SML::Logging::error(
            TEXT("SML detected two mods trying to overwrite same asset at path '"), *OverwritePath, TEXT("': "),
            *ModReference, TEXT(" and "), *OldModReference);
        SML::Logging::error(
            TEXT("This setup is not stable, and mods can break depending on which overwrite takes precedence"));
        SML::Logging::error(TEXT("Proceed with caution, and make sure to report to mod authors about the conflict"));
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
