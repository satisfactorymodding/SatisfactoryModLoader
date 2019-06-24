#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_InstancedSplines_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function InstancedSplines.FGInstancedSplineMeshComponent.UpdateInstanceTransform
struct UFGInstancedSplineMeshComponent_UpdateInstanceTransform_Params
{
	int                                                InstanceIndex;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     StartPos;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     StartTangent;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     EndPos;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     EndTangent;                                               // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	bool                                               bWorldSpace;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bMarkRenderStateDirty;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bTeleport;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function InstancedSplines.FGInstancedSplineMeshComponent.RemoveInstance
struct UFGInstancedSplineMeshComponent_RemoveInstance_Params
{
	int                                                InstanceIndex;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function InstancedSplines.FGInstancedSplineMeshComponent.GetInstanceCount
struct UFGInstancedSplineMeshComponent_GetInstanceCount_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function InstancedSplines.FGInstancedSplineMeshComponent.ClearInstances
struct UFGInstancedSplineMeshComponent_ClearInstances_Params
{
};

// Function InstancedSplines.FGInstancedSplineMeshComponent.AddInstance
struct UFGInstancedSplineMeshComponent_AddInstance_Params
{
	struct FVector                                     StartPos;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     StartTangent;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     EndPos;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     EndTangent;                                               // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
