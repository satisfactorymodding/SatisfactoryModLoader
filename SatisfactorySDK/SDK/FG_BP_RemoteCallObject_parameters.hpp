#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_RemoteCallObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.GetRemainingCostForSchematic
struct UBP_RemoteCallObject_C_GetRemainingCostForSchematic_Params
{
	class UClass*                                      Schematic;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ForItem;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Cost;                                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetWorkingAtBench
struct UBP_RemoteCallObject_C_ServerSetWorkingAtBench_Params
{
	class AFGPlayerController*                         PlayerWorking;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGWorkBench*                                ResearchMachine;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetRecipeOnManufacturingProxy
struct UBP_RemoteCallObject_C_Server_SetRecipeOnManufacturingProxy_Params
{
	class AFGBuildableManufacturer*                    Manufacturer;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetBeaconTexture
struct UBP_RemoteCallObject_C_ServerSetBeaconTexture_Params
{
	class UTexture2D*                                  Texture;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class ABP_Beacon_C*                                Beacon;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SplitResource
struct UBP_RemoteCallObject_C_Server_SplitResource_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                numResourceToMove;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_MoveItem
struct UBP_RemoteCallObject_C_Server_MoveItem_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       destinationComponent;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                destinationIdx;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_MoveItemIfSpace
struct UBP_RemoteCallObject_C_Server_MoveItemIfSpace_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       destinationComponent;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.PlayDismantlePortableMinerEffects
struct UBP_RemoteCallObject_C_PlayDismantlePortableMinerEffects_Params
{
	class ABP_PortableMiner_C*                         PortableMiner;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerExtractResourceToPlayer
struct UBP_RemoteCallObject_C_ServerExtractResourceToPlayer_Params
{
	class AFGResourceNode*                             resourceNode;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AChar_Player_C*                              Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                amount;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_RemoveAllFromIndex
struct UBP_RemoteCallObject_C_Server_RemoveAllFromIndex_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetBeaconText
struct UBP_RemoteCallObject_C_ServerSetBeaconText_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	class ABP_Beacon_C*                                Beacon;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetBeaconColor
struct UBP_RemoteCallObject_C_ServerSetBeaconColor_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class ABP_Beacon_C*                                Beacon;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerPickUpBeacon
struct UBP_RemoteCallObject_C_ServerPickUpBeacon_Params
{
	class ABP_Beacon_C*                                Beacon;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AChar_Player_C*                              toPlayer;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_DropItem
struct UBP_RemoteCallObject_C_Server_DropItem_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     SpawnLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    spawnRotation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_RemoveIngredientsAndAwardRewards
struct UBP_RemoteCallObject_C_Server_RemoveIngredientsAndAwardRewards_Params
{
	class UFGWorkBench*                                Workbench;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       inventory;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetPendingPotentialOnFactory
struct UBP_RemoteCallObject_C_ServerSetPendingPotentialOnFactory_Params
{
	class AFGBuildableFactory*                         FACTORY;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              newPotential;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerDismantlePortableMiner
struct UBP_RemoteCallObject_C_ServerDismantlePortableMiner_Params
{
	class ABP_PortableMiner_C*                         inPortableMiner;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerOpenVehicleTrunk
struct UBP_RemoteCallObject_C_ServerOpenVehicleTrunk_Params
{
	class ABP_WheeledVehicle_C*                        inVehicle;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          inPlayer;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerRegisterInteractingPlayerOnUseInterface
struct UBP_RemoteCallObject_C_ServerRegisterInteractingPlayerOnUseInterface_Params
{
	class UObject*                                     interactObject;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerUnregisterInteractingPlayerOnUseInterface
struct UBP_RemoteCallObject_C_ServerUnregisterInteractingPlayerOnUseInterface_Params
{
	class UObject*                                     interactObject;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_RemoveNumFromIndex
struct UBP_RemoteCallObject_C_Server_RemoveNumFromIndex_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumToRemove;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_PayOffOnSchematic
struct UBP_RemoteCallObject_C_Server_PayOffOnSchematic_Params
{
	class UClass*                                      Schematic;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       FromInventoryComponent;                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                idx;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetSpeedLimit
struct UBP_RemoteCallObject_C_ServerSetSpeedLimit_Params
{
	class ABuild_SpeedRoadSign_C*                      speedRoadSignProxy;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NewLimit;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_LaunchShip
struct UBP_RemoteCallObject_C_Server_LaunchShip_Params
{
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerCloseVehicleTrunk
struct UBP_RemoteCallObject_C_ServerCloseVehicleTrunk_Params
{
	class ABP_WheeledVehicle_C*                        inVehicle;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          inPlayer;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_ResetFuse
struct UBP_RemoteCallObject_C_Server_ResetFuse_Params
{
	int                                                circuitID;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerRemoveTargetPoint
struct UBP_RemoteCallObject_C_ServerRemoveTargetPoint_Params
{
	class AFGTargetPoint*                              inTargetPoint;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGWheeledVehicle*                           inVehicle;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_ResizeInventory
struct UBP_RemoteCallObject_C_Server_ResizeInventory_Params
{
	int                                                newSize;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       inInventoryComp;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_PayOffTowTruckUpgrade
struct UBP_RemoteCallObject_C_Server_PayOffTowTruckUpgrade_Params
{
	class AFGBuildableSpaceElevator*                   SpaceElevator;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       inventory;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                inventorySlotIndex;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_RemoveSortRule
struct UBP_RemoteCallObject_C_Server_RemoveSortRule_Params
{
	class AFGBuildableSplitterSmart*                   Splitter_Smart;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetTrainStationName
struct UBP_RemoteCallObject_C_Server_SetTrainStationName_Params
{
	class AFGTrainStationIdentifier*                   Station;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Name;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_UpdateSortRule
struct UBP_RemoteCallObject_C_Server_UpdateSortRule_Params
{
	class AFGBuildableSplitterSmart*                   SplitterSmart;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSplitterSortRule                           Rule;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_GrabAllItemsFromInventory
struct UBP_RemoteCallObject_C_Server_GrabAllItemsFromInventory_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       destinationComponent;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      onlyGrabOfDesc;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_RepairDropPod
struct UBP_RemoteCallObject_C_Server_RepairDropPod_Params
{
	class ABP_DropPod_C*                               DropPod;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_AddSortRule
struct UBP_RemoteCallObject_C_Server_AddSortRule_Params
{
	class AFGBuildableSplitterSmart*                   SplitterSmart;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSplitterSortRule                           Rule;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetLoadModeOnDockingStation
struct UBP_RemoteCallObject_C_Server_SetLoadModeOnDockingStation_Params
{
	class AFGBuildableDockingStation*                  DockingStation;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isInLoadMode;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetActiveSchematic
struct UBP_RemoteCallObject_C_ServerSetActiveSchematic_Params
{
	class UClass*                                      newActiveSchematic;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetIsProductionPausedOnFactory
struct UBP_RemoteCallObject_C_Server_SetIsProductionPausedOnFactory_Params
{
	class AFGBuildableFactory*                         FACTORY;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsProductionPaused;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Client_RemovePawnHUD
struct UBP_RemoteCallObject_C_Client_RemovePawnHUD_Params
{
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Client_AddPawnHUD
struct UBP_RemoteCallObject_C_Client_AddPawnHUD_Params
{
	class UClass*                                      HUDClass;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       Pawn;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SpaceElevatorUpgradePressed
struct UBP_RemoteCallObject_C_Server_SpaceElevatorUpgradePressed_Params
{
	class AFGBuildableSpaceElevator*                   SpaceElevator;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_LaunchTowTruck
struct UBP_RemoteCallObject_C_Server_LaunchTowTruck_Params
{
	class AFGBuildableSpaceElevator*                   SpaceElevator;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_UpdateTutorial
struct UBP_RemoteCallObject_C_Server_UpdateTutorial_Params
{
	EIntroTutorialSteps                                newTutorialID;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGTutorialIntroManager*                     introManager;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Client_PlayTradingPostSequence
struct UBP_RemoteCallObject_C_Client_PlayTradingPostSequence_Params
{
	class ABuild_TradingPost_C*                        Tradingpost;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetUsingMAM
struct UBP_RemoteCallObject_C_ServerSetUsingMAM_Params
{
	class AFGPlayerController*                         PlayerWorking;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGResearchMachine*                          ResearchMachine;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerPayOffResearch
struct UBP_RemoteCallObject_C_ServerPayOffResearch_Params
{
	class AFGResearchManager*                          ResearchManager;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ResearchToPayOff;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       inventory;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                Inventory_Slot_Index;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerInitiateResearch
struct UBP_RemoteCallObject_C_ServerInitiateResearch_Params
{
	class AFGResearchManager*                          ResearchManager;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Research;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerClaimResearchResults
struct UBP_RemoteCallObject_C_ServerClaimResearchResults_Params
{
	class AFGResearchManager*                          ResearchManager;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Research;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                selectedIndex;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetWaitTime
struct UBP_RemoteCallObject_C_ServerSetWaitTime_Params
{
	class AFGTargetPoint*                              inTargetPoint;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              newWaitTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ServerSetRadarTowerText
struct UBP_RemoteCallObject_C_ServerSetRadarTowerText_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	class ABuild_RadarTower_C*                         RadarTower;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetStandaloneSignData
struct UBP_RemoteCallObject_C_Server_SetStandaloneSignData_Params
{
	TScriptInterface<class UFGSignInterface>           SignInterface;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSignData                                   SignData;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               Update;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetSignWallData
struct UBP_RemoteCallObject_C_Server_SetSignWallData_Params
{
	class AFGBuildableSignWall*                        SignWall;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSignWallData                               SignData;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               Update;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SortInventory
struct UBP_RemoteCallObject_C_Server_SortInventory_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_DropItemIntoStack
struct UBP_RemoteCallObject_C_Server_DropItemIntoStack_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     SpawnLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    spawnRotation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetLoadModeOnTrainCargoPlatform
struct UBP_RemoteCallObject_C_Server_SetLoadModeOnTrainCargoPlatform_Params
{
	class AFGBuildableTrainPlatformCargo*              CargoPlatform;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isInLoadMode;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetTimeTableStops
struct UBP_RemoteCallObject_C_Server_SetTimeTableStops_Params
{
	class AFGRailroadTimeTable*                        TimeTable;                                                // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FTimeTableStop>                      stops;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.Server_SetTimeTableCurrentStop
struct UBP_RemoteCallObject_C_Server_SetTimeTableCurrentStop_Params
{
	class AFGRailroadTimeTable*                        TimeTable;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RemoteCallObject.BP_RemoteCallObject_C.ExecuteUbergraph_BP_RemoteCallObject
struct UBP_RemoteCallObject_C_ExecuteUbergraph_BP_RemoteCallObject_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
