#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_SlateCore_classes.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum Paper2D.EFlipbookCollisionMode
enum class EFlipbookCollisionMode : uint8_t
{
	NoCollision                    = 0,
	FirstFrameCollision            = 1,
	EachFrameCollision             = 2,
	EFlipbookCollisionMode_MAX     = 3
};


// Enum Paper2D.EPaperSpriteAtlasPadding
enum class EPaperSpriteAtlasPadding : uint8_t
{
	DilateBorder                   = 0,
	PadWithZero                    = 1,
	EPaperSpriteAtlasPadding_MAX   = 2
};


// Enum Paper2D.ETileMapProjectionMode
enum class ETileMapProjectionMode : uint8_t
{
	Orthogonal                     = 0,
	IsometricDiamond               = 1,
	IsometricStaggered             = 2,
	HexagonalStaggered             = 3,
	ETileMapProjectionMode_MAX     = 4
};


// Enum Paper2D.ESpritePivotMode
enum class ESpritePivotMode : uint8_t
{
	Top_Left                       = 0,
	Top_Center                     = 1,
	Top_Right                      = 2,
	Center_Left                    = 3,
	Center_Center                  = 4,
	Center_Right                   = 5,
	Bottom_Left                    = 6,
	Bottom_Center                  = 7,
	Bottom_Right                   = 8,
	Custom                         = 9,
	ESpritePivotMode_MAX           = 10
};


// Enum Paper2D.ESpritePolygonMode
enum class ESpritePolygonMode : uint8_t
{
	SourceBoundingBox              = 0,
	TightBoundingBox               = 1,
	ShrinkWrapped                  = 2,
	FullyCustom                    = 3,
	Diced                          = 4,
	ESpritePolygonMode_MAX         = 5
};


// Enum Paper2D.ESpriteShapeType
enum class ESpriteShapeType : uint8_t
{
	Box                            = 0,
	Circle                         = 1,
	Polygon                        = 2,
	ESpriteShapeType_MAX           = 3
};


// Enum Paper2D.ESpriteCollisionMode
enum class ESpriteCollisionMode : uint8_t
{
	None                           = 0,
	Use2DPhysics                   = 1,
	Use3DPhysics                   = 2,
	ESpriteCollisionMode_MAX       = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Paper2D.PaperFlipbookKeyFrame
// 0x0010
struct FPaperFlipbookKeyFrame
{
	class UPaperSprite*                                Sprite;                                                   // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                FrameRun;                                                 // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.SpriteInstanceData
// 0x0050
struct FSpriteInstanceData
{
	struct FMatrix                                     Transform;                                                // 0x0000(0x0040) (Edit, ZeroConstructor, IsPlainOldData)
	class UPaperSprite*                                SourceSprite;                                             // 0x0040(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FColor                                      VertexColor;                                              // 0x0048(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                MaterialIndex;                                            // 0x004C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct Paper2D.PaperSpriteSocket
// 0x0040
struct FPaperSpriteSocket
{
	struct FTransform                                  LocalTransform;                                           // 0x0000(0x0030) (Edit, BlueprintVisible, BlueprintReadOnly, IsPlainOldData)
	struct FName                                       SocketName;                                               // 0x0030(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
};

// ScriptStruct Paper2D.PaperTerrainMaterialRule
// 0x0038
struct FPaperTerrainMaterialRule
{
	class UPaperSprite*                                StartCap;                                                 // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<class UPaperSprite*>                        Body;                                                     // 0x0008(0x0010) (Edit, ZeroConstructor)
	class UPaperSprite*                                EndCap;                                                   // 0x0018(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MinimumAngle;                                             // 0x0020(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MaximumAngle;                                             // 0x0024(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableCollision;                                         // 0x0028(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0029(0x0003) MISSED OFFSET
	float                                              CollisionOffset;                                          // 0x002C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                DrawOrder;                                                // 0x0030(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0034(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.PaperTileInfo
// 0x0010
struct FPaperTileInfo
{
	class UPaperTileSet*                               TileSet;                                                  // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                PackedTileIndex;                                          // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.IntMargin
// 0x0010
struct FIntMargin
{
	int                                                Left;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Top;                                                      // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Right;                                                    // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Bottom;                                                   // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct Paper2D.SpriteGeometryShape
// 0x0030
struct FSpriteGeometryShape
{
	ESpriteShapeType                                   ShapeType;                                                // 0x0000(0x0001) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	TArray<struct FVector2D>                           Vertices;                                                 // 0x0008(0x0010) (Edit, ZeroConstructor)
	struct FVector2D                                   BoxSize;                                                  // 0x0018(0x0008) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	struct FVector2D                                   BoxPosition;                                              // 0x0020(0x0008) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	float                                              Rotation;                                                 // 0x0028(0x0004) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	bool                                               bNegativeWinding;                                         // 0x002C(0x0001) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x002D(0x0003) MISSED OFFSET
};

// ScriptStruct Paper2D.SpriteGeometryCollection
// 0x0030
struct FSpriteGeometryCollection
{
	TArray<struct FSpriteGeometryShape>                Shapes;                                                   // 0x0000(0x0010) (Edit, ZeroConstructor)
	TEnumAsByte<ESpritePolygonMode>                    GeometryType;                                             // 0x0010(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0011(0x0003) MISSED OFFSET
	int                                                PixelsPerSubdivisionX;                                    // 0x0014(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                PixelsPerSubdivisionY;                                    // 0x0018(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bAvoidVertexMerging;                                      // 0x001C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x001D(0x0003) MISSED OFFSET
	float                                              AlphaThreshold;                                           // 0x0020(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              DetailAmount;                                             // 0x0024(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SimplifyEpsilon;                                          // 0x0028(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x002C(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.PaperTileMetadata
// 0x0040
struct FPaperTileMetadata
{
	struct FName                                       UserDataName;                                             // 0x0000(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FSpriteGeometryCollection                   CollisionData;                                            // 0x0008(0x0030) (Edit)
	unsigned char                                      TerrainMembership[0x4];                                   // 0x0038(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x003C(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.PaperTileSetTerrain
// 0x0018
struct FPaperTileSetTerrain
{
	class FString                                      TerrainName;                                              // 0x0000(0x0010) (Edit, ZeroConstructor)
	int                                                CenterTileIndex;                                          // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.PaperSpriteAtlasSlot
// 0x0040
struct FPaperSpriteAtlasSlot
{
	TSoftObjectPtr<class UPaperSprite>                 SpriteRef;                                                // 0x0000(0x0028)
	int                                                AtlasIndex;                                               // 0x0028(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                X;                                                        // 0x002C(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                Y;                                                        // 0x0030(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                Width;                                                    // 0x0034(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                Height;                                                   // 0x0038(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x003C(0x0004) MISSED OFFSET
};

// ScriptStruct Paper2D.SpriteDrawCallRecord
// 0x00D0
struct FSpriteDrawCallRecord
{
	struct FVector                                     Destination;                                              // 0x0000(0x000C) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
	class UTexture*                                    BaseTexture;                                              // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x30];                                      // 0x0018(0x0030) MISSED OFFSET
	struct FColor                                      Color;                                                    // 0x0048(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x84];                                      // 0x004C(0x0084) MISSED OFFSET
};

// ScriptStruct Paper2D.SpriteAssetInitParameters
// 0x0040
struct FSpriteAssetInitParameters
{
	unsigned char                                      UnknownData00[0x40];                                      // 0x0000(0x0040) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
