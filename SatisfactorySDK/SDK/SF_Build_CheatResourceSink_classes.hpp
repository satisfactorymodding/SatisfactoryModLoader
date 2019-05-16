#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Build_CheatResourceSink_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_CheatResourceSink.Build_CheatResourceSink_C
// 0x0024 (0x064C - 0x0628)
class ABuild_CheatResourceSink_C : public AFGBuildableFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0628(0x0008) (Transient, DuplicateTransient)
	class UStaticMeshComponent*                        MainMesh;                                                 // 0x0630(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               Input0;                                                   // 0x0638(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        InputBox;                                                 // 0x0640(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                mNumResourcesGrabbed;                                     // 0x0648(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_CheatResourceSink.Build_CheatResourceSink_C");
		return ptr;
	}


	void UserConstructionScript();
	void Factory_CollectInput();
	void ExecuteUbergraph_Build_CheatResourceSink(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
