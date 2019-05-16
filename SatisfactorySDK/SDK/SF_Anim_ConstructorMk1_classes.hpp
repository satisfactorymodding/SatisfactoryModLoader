#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_ConstructorMk1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_ConstructorMk1.Anim_ConstructorMk1_C
// 0x0CB1 (0x1661 - 0x09B0)
class UAnim_ConstructorMk1_C : public UFGFAnimInstanceFactory
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_EE25C9DE4FCC24B6648207984D8104F5;// 0x09B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1CEFF83543FDFC2AA7280490EC14ED04;// 0x0A00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_56A39FA24B70F097CAE83FB5EF656952;// 0x0A48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F5FD74CF4665DC291CF9D7B1F5DE98AA;// 0x0A90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B4F6D3BF43B2690B477B0E907548A929;// 0x0AD8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E6ABA23E42EA726002BC46939CEDDF17;// 0x0B20(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_E36F19304B3E29B2391B7BB7F3DA8B19;// 0x0B68(0x0070)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_BEB334904D31D35791B45EB6B32A1E99;// 0x0BD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3FAE7C4247011BD0A3130C8B850E7B46;// 0x0C20(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_E948DF4B42FC43EBB614A98201F5601D;// 0x0CD0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_278E0C114ADE9B04C6D7C091A85F7CD5;// 0x0D18(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_608000764B46C8C221199FAD05152414;// 0x0DC8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B6B3E67C4FC0B9537DF900A071C952B5;// 0x0E10(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_E03E3DCF4006B2D497BA45AAA31F28FD;// 0x0EC0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_E8E8FAF342304B8867452F922EFE4483;// 0x0F08(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_Root_F30834C444728AA30EBBF5AA5E0F976C;      // 0x0FE8(0x0048)
	struct FAnimNode_RigidBody                         AnimGraphNode_RigidBody_172D51874A133A909731388D7A105107; // 0x1030(0x05A0)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_170139A24C063FA857B9F688373D3AA8;// 0x15D0(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_B6DE2BAE4D493B84DE5920828DDF505E;// 0x1618(0x0048)
	bool                                               mIsIndustrial;                                            // 0x1660(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_ConstructorMk1.Anim_ConstructorMk1_C");
		return ptr;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_TransitionResult_B4F6D3BF43B2690B477B0E907548A929();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_TransitionResult_E6ABA23E42EA726002BC46939CEDDF17();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_SequenceEvaluator_E36F19304B3E29B2391B7BB7F3DA8B19();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_TransitionResult_F5FD74CF4665DC291CF9D7B1F5DE98AA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_SequencePlayer_3FAE7C4247011BD0A3130C8B850E7B46();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_SequencePlayer_278E0C114ADE9B04C6D7C091A85F7CD5();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_TransitionResult_56A39FA24B70F097CAE83FB5EF656952();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_SequencePlayer_B6B3E67C4FC0B9537DF900A071C952B5();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_TransitionResult_1CEFF83543FDFC2AA7280490EC14ED04();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_ConstructorMk1_AnimGraphNode_TransitionResult_EE25C9DE4FCC24B6648207984D8104F5();
	void ExecuteUbergraph_Anim_ConstructorMk1(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
