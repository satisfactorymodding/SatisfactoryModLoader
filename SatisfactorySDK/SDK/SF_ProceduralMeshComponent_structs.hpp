#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Basic.hpp"
#include "SF_Engine_classes.hpp"
#include "SF_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum ProceduralMeshComponent.EProcMeshSliceCapOption
enum class EProcMeshSliceCapOption : uint8_t
{
	NoCap                          = 0,
	CreateNewSectionForCap         = 1,
	UseLastSectionForCap           = 2,
	EProcMeshSliceCapOption_MAX    = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct ProceduralMeshComponent.ProcMeshTangent
// 0x0010
struct FProcMeshTangent
{
	struct FVector                                     TangentX;                                                 // 0x0000(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	bool                                               bFlipTangentY;                                            // 0x000C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x000D(0x0003) MISSED OFFSET
};

// ScriptStruct ProceduralMeshComponent.ProcMeshVertex
// 0x004C
struct FProcMeshVertex
{
	struct FVector                                     Position;                                                 // 0x0000(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector                                     Normal;                                                   // 0x000C(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	struct FProcMeshTangent                            Tangent;                                                  // 0x0018(0x0010) (Edit, BlueprintVisible)
	struct FColor                                      Color;                                                    // 0x0028(0x0004) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   UV0;                                                      // 0x002C(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   UV1;                                                      // 0x0034(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   UV2;                                                      // 0x003C(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   UV3;                                                      // 0x0044(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
};

// ScriptStruct ProceduralMeshComponent.ProcMeshSection
// 0x0040
struct FProcMeshSection
{
	TArray<struct FProcMeshVertex>                     ProcVertexBuffer;                                         // 0x0000(0x0010) (ZeroConstructor)
	TArray<uint32_t>                                   ProcIndexBuffer;                                          // 0x0010(0x0010) (ZeroConstructor)
	struct FBox                                        SectionLocalBox;                                          // 0x0020(0x001C) (IsPlainOldData)
	bool                                               bEnableCollision;                                         // 0x003C(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bSectionVisible;                                          // 0x003D(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x003E(0x0002) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
