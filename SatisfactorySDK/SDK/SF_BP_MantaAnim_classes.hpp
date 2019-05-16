#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_MantaAnim_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass BP_MantaAnim.BP_MantaAnim_C
// 0x0208 (0x0568 - 0x0360)
class UBP_MantaAnim_C : public UAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_5245B92B4C6F4AF51C5BE69EBED466EC;      // 0x0368(0x0048)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_D8D8234F4E94FFAB8A87AFA85FF95534;// 0x03B0(0x0090)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_F7056B1F4FFB59D2A95023A830EC1771;// 0x0440(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_770B0E9249F21AAB5176C585899CF22F;// 0x0488(0x00E0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass BP_MantaAnim.BP_MantaAnim_C");
		return ptr;
	}


	void ExecuteUbergraph_BP_MantaAnim(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
