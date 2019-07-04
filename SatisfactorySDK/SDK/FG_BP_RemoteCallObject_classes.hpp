#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_RemoteCallObject_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_RemoteCallObject.BP_RemoteCallObject_C
// 0x000C (0x0034 - 0x0028)
class UBP_RemoteCallObject_C : public UFGRemoteCallObject
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0028(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	int                                                numToPayOff;                                              // 0x0030(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_RemoteCallObject.BP_RemoteCallObject_C");
		return ptr;
	}


	void GetRemainingCostForSchematic(class UClass* Schematic, class UClass* ForItem, int* Cost);
	void ServerSetWorkingAtBench(class AFGPlayerController* PlayerWorking, class UFGWorkBench* ResearchMachine);
	void Server_SetRecipeOnManufacturingProxy(class AFGBuildableManufacturer* Manufacturer, class UClass* Recipe);
	void ServerSetBeaconTexture(class UTexture2D* Texture, class ABP_Beacon_C* Beacon);
	void Server_SplitResource(class UFGInventoryComponent* InventoryComponent, int sourceIdx, int numResourceToMove);
	void Server_MoveItem(class UFGInventoryComponent* SourceComponent, class UFGInventoryComponent* destinationComponent, int sourceIdx, int destinationIdx);
	void Server_MoveItemIfSpace(class UFGInventoryComponent* SourceComponent, int sourceIdx, class UFGInventoryComponent* destinationComponent);
	void PlayDismantlePortableMinerEffects(class ABP_PortableMiner_C* PortableMiner);
	void ServerExtractResourceToPlayer(class AFGResourceNode* resourceNode, class AChar_Player_C* Player, int amount);
	void Server_RemoveAllFromIndex(class UFGInventoryComponent* SourceComponent, int sourceIdx);
	void ServerSetBeaconText(const struct FText& Text, class ABP_Beacon_C* Beacon);
	void ServerSetBeaconColor(const struct FLinearColor& Color, class ABP_Beacon_C* Beacon);
	void ServerPickUpBeacon(class ABP_Beacon_C* Beacon, class AChar_Player_C* toPlayer);
	void Server_DropItem(class UFGInventoryComponent* InventoryComponent, int sourceIdx, const struct FVector& SpawnLocation, const struct FRotator& spawnRotation);
	void Server_RemoveIngredientsAndAwardRewards(class UFGWorkBench* Workbench, class UFGInventoryComponent* inventory, class UClass* Recipe);
	void ServerSetPendingPotentialOnFactory(class AFGBuildableFactory* FACTORY, float newPotential);
	void ServerDismantlePortableMiner(class ABP_PortableMiner_C* inPortableMiner);
	void ServerOpenVehicleTrunk(class ABP_WheeledVehicle_C* inVehicle, class AFGCharacterPlayer* inPlayer);
	void ServerRegisterInteractingPlayerOnUseInterface(class UObject* interactObject, class AFGCharacterPlayer* Player);
	void ServerUnregisterInteractingPlayerOnUseInterface(class UObject* interactObject, class AFGCharacterPlayer* Player);
	void Server_RemoveNumFromIndex(class UFGInventoryComponent* SourceComponent, int sourceIdx, int NumToRemove);
	void Server_PayOffOnSchematic(class UClass* Schematic, class UFGInventoryComponent* FromInventoryComponent, int idx);
	void ServerSetSpeedLimit(class ABuild_SpeedRoadSign_C* speedRoadSignProxy, int NewLimit);
	void Server_LaunchShip();
	void ServerCloseVehicleTrunk(class ABP_WheeledVehicle_C* inVehicle, class AFGCharacterPlayer* inPlayer);
	void Server_ResetFuse(int circuitID);
	void ServerRemoveTargetPoint(class AFGTargetPoint* inTargetPoint, class AFGWheeledVehicle* inVehicle);
	void Server_ResizeInventory(int newSize, class UFGInventoryComponent* inInventoryComp);
	void Server_PayOffTowTruckUpgrade(class AFGBuildableSpaceElevator* SpaceElevator, class UFGInventoryComponent* inventory, int inventorySlotIndex);
	void Server_RemoveSortRule(class AFGBuildableSplitterSmart* Splitter_Smart, int Index);
	void Server_SetTrainStationName(class AFGTrainStationIdentifier* Station, const struct FText& Name);
	void Server_UpdateSortRule(class AFGBuildableSplitterSmart* SplitterSmart, int Index, const struct FSplitterSortRule& Rule);
	void Server_GrabAllItemsFromInventory(class UFGInventoryComponent* SourceComponent, class UFGInventoryComponent* destinationComponent, class UClass* onlyGrabOfDesc);
	void Server_RepairDropPod(class ABP_DropPod_C* DropPod, class AFGCharacterPlayer* byCharacter);
	void Server_AddSortRule(class AFGBuildableSplitterSmart* SplitterSmart, const struct FSplitterSortRule& Rule);
	void Server_SetLoadModeOnDockingStation(class AFGBuildableDockingStation* DockingStation, bool isInLoadMode);
	void ServerSetActiveSchematic(class UClass* newActiveSchematic);
	void Server_SetIsProductionPausedOnFactory(class AFGBuildableFactory* FACTORY, bool IsProductionPaused);
	void Client_RemovePawnHUD();
	void Client_AddPawnHUD(class UClass* HUDClass, class APawn* Pawn);
	void Server_SpaceElevatorUpgradePressed(class AFGBuildableSpaceElevator* SpaceElevator);
	void Server_LaunchTowTruck(class AFGBuildableSpaceElevator* SpaceElevator);
	void Server_UpdateTutorial(EIntroTutorialSteps newTutorialID, class AFGTutorialIntroManager* introManager);
	void Client_PlayTradingPostSequence(class ABuild_TradingPost_C* Tradingpost);
	void ServerSetUsingMAM(class AFGPlayerController* PlayerWorking, class UFGResearchMachine* ResearchMachine);
	void ServerPayOffResearch(class AFGResearchManager* ResearchManager, class UClass* ResearchToPayOff, class UFGInventoryComponent* inventory, int Inventory_Slot_Index);
	void ServerInitiateResearch(class AFGResearchManager* ResearchManager, class UClass* Research);
	void ServerClaimResearchResults(class AFGResearchManager* ResearchManager, class AFGCharacterPlayer* Player, class UClass* Research, int selectedIndex);
	void ServerSetWaitTime(class AFGTargetPoint* inTargetPoint, float newWaitTime);
	void ServerSetRadarTowerText(const struct FText& Text, class ABuild_RadarTower_C* RadarTower);
	void Server_SetStandaloneSignData(const TScriptInterface<class UFGSignInterface>& SignInterface, const struct FSignData& SignData, bool Update);
	void Server_SetSignWallData(class AFGBuildableSignWall* SignWall, const struct FSignWallData& SignData, bool Update);
	void Server_SortInventory(class UFGInventoryComponent* InventoryComponent);
	void Server_DropItemIntoStack(class UFGInventoryComponent* InventoryComponent, int sourceIdx, const struct FVector& SpawnLocation, const struct FRotator& spawnRotation);
	void Server_SetLoadModeOnTrainCargoPlatform(class AFGBuildableTrainPlatformCargo* CargoPlatform, bool isInLoadMode);
	void Server_SetTimeTableStops(class AFGRailroadTimeTable* TimeTable, TArray<struct FTimeTableStop> stops);
	void Server_SetTimeTableCurrentStop(class AFGRailroadTimeTable* TimeTable, int Index);
	void ExecuteUbergraph_BP_RemoteCallObject(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
