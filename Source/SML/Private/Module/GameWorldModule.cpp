#include "Module/GameWorldModule.h"
#include "ChatCommandLibrary.h"
#include "ModContentRegistry.h"

void UGameWorldModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    Super::DispatchLifecycleEvent(Phase);

    //Register default content
    UWorld* WorldObject = GetWorld();
    AModContentRegistry* ModContentRegistry = AModContentRegistry::Get(WorldObject);
    AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(WorldObject);

    //Register schematics
    for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics) {
        ModContentRegistry->RegisterSchematic(GetOwnerModReference(), Schematic);
    }

    //Register research trees
    for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees) {
        ModContentRegistry->RegisterResearchTree(GetOwnerModReference(), ResearchTree);
    }

    //Register resource sink table points
    UDataTable* ModResourceSinkPointsTable = mResourceSinkItemPointsTable.LoadSynchronous();
    if (ModResourceSinkPointsTable != NULL) {
        ModContentRegistry->RegisterResourceSinkItemPointTable(GetOwnerModReference(), ModResourceSinkPointsTable);
    }

    //Register chat commands (on server side only)
    if (ChatCommandSubsystem != NULL) {
        for (const TSubclassOf<AChatCommandInstance>& ChatCommand : mChatCommands) {
            ChatCommandSubsystem->RegisterCommand(GetOwnerModReference().ToString(), ChatCommand);
        }
    }
}
