#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_SpaceElevator_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_SpaceElevator.Build_SpaceElevator_C
// 0x00D0 (0x0740 - 0x0670)
class ABuild_SpaceElevator_C : public AFGBuildableSpaceElevator
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0670(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        UpperLine;                                                // 0x0678(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      SpaceElevator_skl;                                        // 0x0680(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               InPut3;                                                   // 0x0688(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_06;                                              // 0x0690(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_05;                                              // 0x0698(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_04;                                              // 0x06A0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_03;                                              // 0x06A8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_02;                                              // 0x06B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FogPlane_01;                                              // 0x06B8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input1;                                                   // 0x06C0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input2;                                                   // 0x06C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       BP_LadderComponent2;                                      // 0x06D0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       BP_LadderComponent1;                                      // 0x06D8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       BP_LadderComponent;                                       // 0x06E0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       Ladder;                                                   // 0x06E8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryLegsComponent*                     FGFactoryLegs;                                            // 0x06F0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input6;                                                   // 0x06F8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input5;                                                   // 0x0700(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input4;                                                   // 0x0708(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x0710(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0718(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class ALevelSequenceActor*                         mSendOffSequence;                                         // 0x0720(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FText                                       mMapText;                                                 // 0x0728(0x0028) (Edit, BlueprintVisible, Net, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_SpaceElevator.Build_SpaceElevator_C");
		return ptr;
	}


	struct FText SetActorRepresentationText(const struct FText& newText);
	bool UpdateRepresentation();
	struct FLinearColor GetActorRepresentationColor();
	struct FText GetActorRepresentationText();
	class UTexture2D* GetActorRepresentationTexture();
	ERepresentationType GetActorRepresentationType();
	bool GetActorShouldShowInCompass();
	bool AddAsRepresentation();
	float GetActorFogOfWarRevealRadius();
	EFogOfWarRevealType GetActorFogOfWarRevealType();
	bool GetActorShouldShowOnMap();
	struct FVector GetRealActorLocation();
	struct FRotator GetRealActorRotation();
	bool IsActorStatic();
	bool RemoveAsRepresentation();
	void UserConstructionScript();
	void CamShake_01();
	void CamShake_02();
	void CamShake_03();
	void CamShake_04();
	void UpperlineVisible();
	void Event_StartSound();
	void ReceiveBeginPlay();
	void OnPhaseChanged(TEnumAsByte<EGamePhase> gamePhase);
	void PlayUpgradeSequence();
	void Event_SE_SendOff();
	void ReceiveDestroyed();
	void ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason);
	void ExecuteUbergraph_Build_SpaceElevator(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
