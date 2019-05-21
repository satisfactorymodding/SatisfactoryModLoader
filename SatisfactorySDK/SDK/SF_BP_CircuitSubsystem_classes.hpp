#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_CircuitSubsystem_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_CircuitSubsystem.BP_CircuitSubsystem_C
// 0x0008 (0x03A0 - 0x0398)
class ABP_CircuitSubsystem_C : public AFGCircuitSubsystem
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0398(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CircuitSubsystem.BP_CircuitSubsystem_C");
		return ptr;
	}


	void UserConstructionScript();
	void PowerCircuit_OnFuseSet();
	void Multicast_PlayFuseSetSound();
	void ExecuteUbergraph_BP_CircuitSubsystem(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
