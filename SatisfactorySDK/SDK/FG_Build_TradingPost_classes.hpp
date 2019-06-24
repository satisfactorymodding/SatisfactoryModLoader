#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TradingPost_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_TradingPost.Build_TradingPost_C
// 0x0110 (0x0840 - 0x0730)
class ABuild_TradingPost_C : public AFGBuildableTradingPost
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0730(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USpotLightComponent*                         SpotLight;                                                // 0x0738(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPointLightComponent*                        PointLight;                                               // 0x0740(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      MainMesh_skl;                                             // 0x0748(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryLegsComponent*                     FGFactoryLegs;                                            // 0x0750(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       BP_LadderComponent1;                                      // 0x0758(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UChildActorComponent*                        PlayerStart3;                                             // 0x0760(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UChildActorComponent*                        PlayerStart2;                                             // 0x0768(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UChildActorComponent*                        PlayerStart1;                                             // 0x0770(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UChildActorComponent*                        PlayerStart0;                                             // 0x0778(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0780(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               Clearance;                                                // 0x0788(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FText                                       mWorkBenchOccupied;                                       // 0x0790(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FText                                       mWorkBenchFree;                                           // 0x07A8(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	TArray<class UStaticMesh*>                         meshes;                                                   // 0x07C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                mShipUpgradeLevel;                                        // 0x07D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x07D4(0x0004) MISSED OFFSET
	struct FText                                       mStorageText;                                             // 0x07D8(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FText                                       mMamFreeText;                                             // 0x07F0(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FText                                       mMamOccupiedText;                                         // 0x0808(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	class AFGCharacterPlayer*                          mLastTradingPostUser;                                     // 0x0820(0x0008) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FText                                       mMapText;                                                 // 0x0828(0x0028) (Edit, BlueprintVisible, Net, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_TradingPost.Build_TradingPost_C");
		return ptr;
	}


	struct FText SetActorRepresentationText(const struct FText& newText);
	bool UpdateRepresentation();
	struct FLinearColor GetActorRepresentationColor();
	struct FText GetActorRepresentationText();
	class UTexture2D* GetActorRepresentationTexture();
	ERepresentationType GetActorRepresentationType();
	bool GetActorShouldShowInCompass();
	float GetActorFogOfWarRevealRadius();
	EFogOfWarRevealType GetActorFogOfWarRevealType();
	bool RemoveAsRepresentation();
	struct FRotator GetRealActorRotation();
	struct FVector GetRealActorLocation();
	bool GetActorShouldShowOnMap();
	bool AddAsRepresentation();
	bool IsActorStatic();
	void UpdateTradingPostVisibility();
	void UpdateMainMesh();
	void UserConstructionScript();
	void ReceiveDestroyed();
	void ReceiveBeginPlay();
	void OnTradingPostUpgraded(int* Level, bool* suppressBuildEffects);
	void ExecuteUbergraph_Build_TradingPost(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
