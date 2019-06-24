#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_HubTerminal_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_HubTerminal.Build_HubTerminal_C
// 0x0008 (0x0578 - 0x0570)
class ABuild_HubTerminal_C : public AFGBuildableHubTerminal
{
public:
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0570(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_HubTerminal.Build_HubTerminal_C");
		return ptr;
	}


	bool CanDismantle();
	void UpdateUseState(class AFGCharacterPlayer** byCharacter, struct FVector* atLocation, class UPrimitiveComponent** componentHit, struct FUseState* out_useState);
	struct FText GetLookAtDecription(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
