#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Crate_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Crate.BP_Crate_C
// 0x0038 (0x0380 - 0x0348)
class ABP_Crate_C : public AFGCrate
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0348(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        StaticMesh_1;                                             // 0x0350(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             Scene;                                                    // 0x0358(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mIsShowingHud;                                            // 0x0360(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0361(0x0007) MISSED OFFSET
	struct FText                                       mMapText;                                                 // 0x0368(0x0028) (Edit, BlueprintVisible, Net, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Crate.BP_Crate_C");
		return ptr;
	}


	struct FText SetActorRepresentationText(const struct FText& newText);
	bool UpdateRepresentation();
	float GetActorFogOfWarRevealRadius();
	EFogOfWarRevealType GetActorFogOfWarRevealType();
	struct FLinearColor GetActorRepresentationColor();
	struct FText GetActorRepresentationText();
	class UTexture2D* GetActorRepresentationTexture();
	ERepresentationType GetActorRepresentationType();
	bool GetActorShouldShowInCompass();
	bool AddAsRepresentation();
	bool GetActorShouldShowOnMap();
	struct FVector GetRealActorLocation();
	struct FRotator GetRealActorRotation();
	bool IsActorStatic();
	bool RemoveAsRepresentation();
	void UserConstructionScript();
	void StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void OnUse(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void SwitchHUD(class AFGCharacterPlayer* byCharacter);
	void OnRequestReprecentMarker();
	void ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason);
	void ReceiveBeginPlay();
	void checkForClearAndRemove(class UClass* ItemClass, int numRemoved);
	void ExecuteUbergraph_BP_Crate(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
