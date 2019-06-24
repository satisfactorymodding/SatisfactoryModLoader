#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum MeshDescription.EComputeNTBsOptions
enum class EComputeNTBsOptions : uint8_t
{
	None                           = 0,
	Normals                        = 1,
	Tangents                       = 2,
	WeightedNTBs                   = 3,
	EComputeNTBsOptions_MAX        = 4
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct MeshDescription.ElementID
// 0x0004
struct FElementID
{
	int                                                IDValue;                                                  // 0x0000(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MeshDescription.PolygonGroupID
// 0x0000 (0x0004 - 0x0004)
struct FPolygonGroupID : public FElementID
{

};

// ScriptStruct MeshDescription.PolygonID
// 0x0000 (0x0004 - 0x0004)
struct FPolygonID : public FElementID
{

};

// ScriptStruct MeshDescription.VertexID
// 0x0000 (0x0004 - 0x0004)
struct FVertexID : public FElementID
{

};

// ScriptStruct MeshDescription.EdgeID
// 0x0000 (0x0004 - 0x0004)
struct FEdgeID : public FElementID
{

};

// ScriptStruct MeshDescription.VertexInstanceID
// 0x0000 (0x0004 - 0x0004)
struct FVertexInstanceID : public FElementID
{

};

// ScriptStruct MeshDescription.MeshTriangle
// 0x000C
struct FMeshTriangle
{
	struct FVertexInstanceID                           VertexInstanceID0;                                        // 0x0000(0x0004) (BlueprintVisible)
	struct FVertexInstanceID                           VertexInstanceID1;                                        // 0x0004(0x0004) (BlueprintVisible)
	struct FVertexInstanceID                           VertexInstanceID2;                                        // 0x0008(0x0004) (BlueprintVisible)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
