#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ProceduralMeshComponent_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.SliceProceduralMesh
struct UKismetProceduralMeshLibrary_SliceProceduralMesh_Params
{
	class UProceduralMeshComponent*                    InProcMesh;                                               // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     PlanePosition;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     PlaneNormal;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bCreateOtherHalf;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	class UProceduralMeshComponent*                    OutOtherHalfProcMesh;                                     // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
	EProcMeshSliceCapOption                            CapOption;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          CapMaterial;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.GetSectionFromStaticMesh
struct UKismetProceduralMeshLibrary_GetSectionFromStaticMesh_Params
{
	class UStaticMesh*                                 InMesh;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                LODIndex;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (Parm, OutParm, ZeroConstructor)
	TArray<int>                                        Triangles;                                                // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector>                             Normals;                                                  // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector2D>                           UVs;                                                      // (Parm, OutParm, ZeroConstructor)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.GetSectionFromProceduralMesh
struct UKismetProceduralMeshLibrary_GetSectionFromProceduralMesh_Params
{
	class UProceduralMeshComponent*                    InProcMesh;                                               // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (Parm, OutParm, ZeroConstructor)
	TArray<int>                                        Triangles;                                                // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector>                             Normals;                                                  // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector2D>                           UVs;                                                      // (Parm, OutParm, ZeroConstructor)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.GenerateBoxMesh
struct UKismetProceduralMeshLibrary_GenerateBoxMesh_Params
{
	struct FVector                                     BoxRadius;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (Parm, OutParm, ZeroConstructor)
	TArray<int>                                        Triangles;                                                // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector>                             Normals;                                                  // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector2D>                           UVs;                                                      // (Parm, OutParm, ZeroConstructor)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.CreateGridMeshTriangles
struct UKismetProceduralMeshLibrary_CreateGridMeshTriangles_Params
{
	int                                                NumX;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumY;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWinding;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<int>                                        Triangles;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.CopyProceduralMeshFromStaticMeshComponent
struct UKismetProceduralMeshLibrary_CopyProceduralMeshFromStaticMeshComponent_Params
{
	class UStaticMeshComponent*                        StaticMeshComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                LODIndex;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UProceduralMeshComponent*                    ProcMeshComponent;                                        // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bCreateCollision;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.ConvertQuadToTriangles
struct UKismetProceduralMeshLibrary_ConvertQuadToTriangles_Params
{
	TArray<int>                                        Triangles;                                                // (Parm, OutParm, ZeroConstructor, ReferenceParm)
	int                                                Vert0;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Vert1;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Vert2;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Vert3;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.KismetProceduralMeshLibrary.CalculateTangentsForMesh
struct UKismetProceduralMeshLibrary_CalculateTangentsForMesh_Params
{
	TArray<struct FVector>                             Vertices;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<int>                                        Triangles;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UVs;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector>                             Normals;                                                  // (Parm, OutParm, ZeroConstructor)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.UpdateMeshSection_LinearColor
struct UProceduralMeshComponent_UpdateMeshSection_LinearColor_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector>                             Normals;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV0;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV1;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV2;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV3;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FLinearColor>                        VertexColors;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.UpdateMeshSection
struct UProceduralMeshComponent_UpdateMeshSection_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector>                             Normals;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV0;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FColor>                              VertexColors;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.SetMeshSectionVisible
struct UProceduralMeshComponent_SetMeshSectionVisible_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bNewVisibility;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.IsMeshSectionVisible
struct UProceduralMeshComponent_IsMeshSectionVisible_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.GetNumSections
struct UProceduralMeshComponent_GetNumSections_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection_LinearColor
struct UProceduralMeshComponent_CreateMeshSection_LinearColor_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<int>                                        Triangles;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector>                             Normals;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV0;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV1;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV2;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV3;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FLinearColor>                        VertexColors;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               bCreateCollision;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection
struct UProceduralMeshComponent_CreateMeshSection_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Vertices;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<int>                                        Triangles;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector>                             Normals;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FVector2D>                           UV0;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FColor>                              VertexColors;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FProcMeshTangent>                    Tangents;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               bCreateCollision;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.ClearMeshSection
struct UProceduralMeshComponent_ClearMeshSection_Params
{
	int                                                SectionIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.ClearCollisionConvexMeshes
struct UProceduralMeshComponent_ClearCollisionConvexMeshes_Params
{
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.ClearAllMeshSections
struct UProceduralMeshComponent_ClearAllMeshSections_Params
{
};

// Function ProceduralMeshComponent.ProceduralMeshComponent.AddCollisionConvexMesh
struct UProceduralMeshComponent_AddCollisionConvexMesh_Params
{
	TArray<struct FVector>                             ConvexVerts;                                              // (Parm, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
