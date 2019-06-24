#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildEffect_ConveyorBeltSegment_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildEffect_ConveyorBeltSegment.BP_BuildEffect_ConveyorBeltSegment_C
// 0x0088 (0x03B0 - 0x0328)
class ABP_BuildEffect_ConveyorBeltSegment_C : public AActor
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0328(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USplineComponent*                            Spline;                                                   // 0x0330(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0338(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              Finalize_Glow_Power_B40707AE49467F261979CEB8628D7242;     // 0x0340(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              Finalize_Width_Lower_B40707AE49467F261979CEB8628D7242;    // 0x0344(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ETimelineDirection>                    Finalize__Direction_B40707AE49467F261979CEB8628D7242;     // 0x0348(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0349(0x0007) MISSED OFFSET
	class UTimelineComponent*                          Finalize;                                                 // 0x0350(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              Materialize_MaterializeAmount_033AF93841C8F0855E90EA8FAC2A42A9;// 0x0358(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ETimelineDirection>                    Materialize__Direction_033AF93841C8F0855E90EA8FAC2A42A9;  // 0x035C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x035D(0x0003) MISSED OFFSET
	class UTimelineComponent*                          Materialize;                                              // 0x0360(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     mStartTangent;                                            // 0x0368(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mEndTangent;                                              // 0x0374(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mMesh;                                                    // 0x0380(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mMaterialBelt;                                            // 0x0388(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mMaterialSides;                                           // 0x0390(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class USplineMeshComponent*                        MeshComponent;                                            // 0x0398(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UMaterialInterface*                          mMaterialFinish_Sides;                                    // 0x03A0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInterface*                          mMaterialFinish_Belt;                                     // 0x03A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildEffect_ConveyorBeltSegment.BP_BuildEffect_ConveyorBeltSegment_C");
		return ptr;
	}


	void UserConstructionScript();
	void Materialize__FinishedFunc();
	void Materialize__UpdateFunc();
	void Finalize__FinishedFunc();
	void Finalize__UpdateFunc();
	void PlayFinishEffect();
	void AddMesh();
	void ExecuteUbergraph_BP_BuildEffect_ConveyorBeltSegment(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
