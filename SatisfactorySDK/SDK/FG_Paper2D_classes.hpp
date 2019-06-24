#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Paper2D_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Paper2D.MaterialExpressionSpriteTextureSampler
// 0x0020 (0x0138 - 0x0118)
class UMaterialExpressionSpriteTextureSampler : public UMaterialExpressionTextureSampleParameter2D
{
public:
	bool                                               bSampleAdditionalTextures;                                // 0x0118(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0119(0x0003) MISSED OFFSET
	int                                                AdditionalSlotIndex;                                      // 0x011C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FText                                       SlotDisplayName;                                          // 0x0120(0x0028) (Edit)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.MaterialExpressionSpriteTextureSampler");
		return ptr;
	}

};


// Class Paper2D.PaperCharacter
// 0x0000 (0x0740 - 0x0740)
class APaperCharacter : public ACharacter
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperCharacter");
		return ptr;
	}

};


// Class Paper2D.PaperFlipbook
// 0x0028 (0x0050 - 0x0028)
class UPaperFlipbook : public UObject
{
public:
	float                                              FramesPerSecond;                                          // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x002C(0x0004) MISSED OFFSET
	TArray<struct FPaperFlipbookKeyFrame>              KeyFrames;                                                // 0x0030(0x0010) (Edit, ZeroConstructor)
	class UMaterialInterface*                          DefaultMaterial;                                          // 0x0040(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EFlipbookCollisionMode>                CollisionSource;                                          // 0x0048(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0049(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperFlipbook");
		return ptr;
	}


	bool IsValidKeyFrameIndex(int Index);
	float GetTotalDuration();
	class UPaperSprite* GetSpriteAtTime(float Time, bool bClampToEnds);
	class UPaperSprite* GetSpriteAtFrame(int FrameIndex);
	int GetNumKeyFrames();
	int GetNumFrames();
	int GetKeyFrameIndexAtTime(float Time, bool bClampToEnds);
};


// Class Paper2D.PaperFlipbookActor
// 0x0008 (0x0330 - 0x0328)
class APaperFlipbookActor : public AActor
{
public:
	class UPaperFlipbookComponent*                     RenderComponent;                                          // 0x0328(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperFlipbookActor");
		return ptr;
	}

};


// Class Paper2D.PaperFlipbookComponent
// 0x0050 (0x05D0 - 0x0580)
class UPaperFlipbookComponent : public UMeshComponent
{
public:
	class UPaperFlipbook*                              SourceFlipbook;                                           // 0x0580(0x0008) (Edit, Net, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          Material;                                                 // 0x0588(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0590(0x0004) (Edit, Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bLooping : 1;                                             // 0x0594(0x0001) (Net)
	unsigned char                                      bReversePlayback : 1;                                     // 0x0594(0x0001) (Net)
	unsigned char                                      bPlaying : 1;                                             // 0x0594(0x0001) (Net)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0595(0x0003) MISSED OFFSET
	float                                              AccumulatedTime;                                          // 0x0598(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	int                                                CachedFrameIndex;                                         // 0x059C(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                SpriteColor;                                              // 0x05A0(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class UBodySetup*                                  CachedBodySetup;                                          // 0x05B0(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnFinishedPlaying;                                        // 0x05B8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x8];                                       // 0x05C8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperFlipbookComponent");
		return ptr;
	}


	void Stop();
	void SetSpriteColor(const struct FLinearColor& NewColor);
	void SetPlayRate(float NewRate);
	void SetPlaybackPositionInFrames(int NewFramePosition, bool bFireEvents);
	void SetPlaybackPosition(float NewPosition, bool bFireEvents);
	void SetNewTime(float NewTime);
	void SetLooping(bool bNewLooping);
	bool SetFlipbook(class UPaperFlipbook* NewFlipbook);
	void ReverseFromEnd();
	void Reverse();
	void PlayFromStart();
	void Play();
	void OnRep_SourceFlipbook(class UPaperFlipbook* OldFlipbook);
	bool IsReversing();
	bool IsPlaying();
	bool IsLooping();
	float GetPlayRate();
	int GetPlaybackPositionInFrames();
	float GetPlaybackPosition();
	int GetFlipbookLengthInFrames();
	float GetFlipbookLength();
	float GetFlipbookFramerate();
	class UPaperFlipbook* GetFlipbook();
};


// Class Paper2D.PaperGroupedSpriteActor
// 0x0008 (0x0330 - 0x0328)
class APaperGroupedSpriteActor : public AActor
{
public:
	class UPaperGroupedSpriteComponent*                RenderComponent;                                          // 0x0328(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperGroupedSpriteActor");
		return ptr;
	}

};


// Class Paper2D.PaperGroupedSpriteComponent
// 0x0030 (0x05B0 - 0x0580)
class UPaperGroupedSpriteComponent : public UMeshComponent
{
public:
	TArray<class UMaterialInterface*>                  InstanceMaterials;                                        // 0x0580(0x0010) (ZeroConstructor)
	TArray<struct FSpriteInstanceData>                 PerInstanceSpriteData;                                    // 0x0590(0x0010) (Edit, ZeroConstructor)
	unsigned char                                      UnknownData00[0x10];                                      // 0x05A0(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperGroupedSpriteComponent");
		return ptr;
	}


	bool UpdateInstanceTransform(int InstanceIndex, const struct FTransform& NewInstanceTransform, bool bWorldSpace, bool bMarkRenderStateDirty, bool bTeleport);
	bool UpdateInstanceColor(int InstanceIndex, const struct FLinearColor& NewInstanceColor, bool bMarkRenderStateDirty);
	void SortInstancesAlongAxis(const struct FVector& WorldSpaceSortAxis);
	bool RemoveInstance(int InstanceIndex);
	bool GetInstanceTransform(int InstanceIndex, bool bWorldSpace, struct FTransform* OutInstanceTransform);
	int GetInstanceCount();
	void ClearInstances();
	int AddInstance(const struct FTransform& Transform, class UPaperSprite* Sprite, bool bWorldSpace, const struct FLinearColor& Color);
};


// Class Paper2D.PaperRuntimeSettings
// 0x0008 (0x0030 - 0x0028)
class UPaperRuntimeSettings : public UObject
{
public:
	bool                                               bEnableSpriteAtlasGroups;                                 // 0x0028(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bEnableTerrainSplineEditing;                              // 0x0029(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bResizeSpriteDataToMatchTextures;                         // 0x002A(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x5];                                       // 0x002B(0x0005) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperRuntimeSettings");
		return ptr;
	}

};


// Class Paper2D.PaperSprite
// 0x0098 (0x00C0 - 0x0028)
class UPaperSprite : public UObject
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0028(0x0010) MISSED OFFSET
	struct FVector2D                                   SourceUV;                                                 // 0x0038(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   SourceDimension;                                          // 0x0040(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  SourceTexture;                                            // 0x0048(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<class UTexture*>                            AdditionalSourceTextures;                                 // 0x0050(0x0010) (Edit, ZeroConstructor)
	struct FVector2D                                   BakedSourceUV;                                            // 0x0060(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   BakedSourceDimension;                                     // 0x0068(0x0008) (ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  BakedSourceTexture;                                       // 0x0070(0x0008) (ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          DefaultMaterial;                                          // 0x0078(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          AlternateMaterial;                                        // 0x0080(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TArray<struct FPaperSpriteSocket>                  Sockets;                                                  // 0x0088(0x0010) (Edit, ZeroConstructor)
	TEnumAsByte<ESpriteCollisionMode>                  SpriteCollisionDomain;                                    // 0x0098(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0099(0x0003) MISSED OFFSET
	float                                              PixelsPerUnrealUnit;                                      // 0x009C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	class UBodySetup*                                  BodySetup;                                                // 0x00A0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                AlternateMaterialSplitIndex;                              // 0x00A8(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x00AC(0x0004) MISSED OFFSET
	TArray<struct FVector4>                            BakedRenderData;                                          // 0x00B0(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperSprite");
		return ptr;
	}

};


// Class Paper2D.PaperSpriteActor
// 0x0008 (0x0330 - 0x0328)
class APaperSpriteActor : public AActor
{
public:
	class UPaperSpriteComponent*                       RenderComponent;                                          // 0x0328(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperSpriteActor");
		return ptr;
	}

};


// Class Paper2D.PaperSpriteAtlas
// 0x0000 (0x0028 - 0x0028)
class UPaperSpriteAtlas : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperSpriteAtlas");
		return ptr;
	}

};


// Class Paper2D.PaperSpriteBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UPaperSpriteBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperSpriteBlueprintLibrary");
		return ptr;
	}


	struct FSlateBrush MakeBrushFromSprite(class UPaperSprite* Sprite, int Width, int Height);
};


// Class Paper2D.PaperSpriteComponent
// 0x0020 (0x05A0 - 0x0580)
class UPaperSpriteComponent : public UMeshComponent
{
public:
	class UPaperSprite*                                SourceSprite;                                             // 0x0580(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          MaterialOverride;                                         // 0x0588(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FLinearColor                                SpriteColor;                                              // 0x0590(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperSpriteComponent");
		return ptr;
	}


	void SetSpriteColor(const struct FLinearColor& NewColor);
	bool SetSprite(class UPaperSprite* NewSprite);
	class UPaperSprite* GetSprite();
};


// Class Paper2D.PaperTerrainActor
// 0x0018 (0x0340 - 0x0328)
class APaperTerrainActor : public AActor
{
public:
	class USceneComponent*                             DummyRoot;                                                // 0x0328(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPaperTerrainSplineComponent*                SplineComponent;                                          // 0x0330(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPaperTerrainComponent*                      RenderComponent;                                          // 0x0338(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTerrainActor");
		return ptr;
	}

};


// Class Paper2D.PaperTerrainComponent
// 0x0050 (0x05B0 - 0x0560)
class UPaperTerrainComponent : public UPrimitiveComponent
{
public:
	bool                                               bClosedSpline;                                            // 0x0560(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               bFilledSpline;                                            // 0x0561(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0562(0x0006) MISSED OFFSET
	class UPaperTerrainSplineComponent*                AssociatedSpline;                                         // 0x0568(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                RandomSeed;                                               // 0x0570(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SegmentOverlapAmount;                                     // 0x0574(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                TerrainColor;                                             // 0x0578(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                ReparamStepsPerSegment;                                   // 0x0588(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESpriteCollisionMode>                  SpriteCollisionDomain;                                    // 0x058C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x058D(0x0003) MISSED OFFSET
	float                                              CollisionThickness;                                       // 0x0590(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0594(0x0004) MISSED OFFSET
	class UBodySetup*                                  CachedBodySetup;                                          // 0x0598(0x0008) (ZeroConstructor, Transient, DuplicateTransient, IsPlainOldData)
	unsigned char                                      UnknownData03[0x10];                                      // 0x05A0(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTerrainComponent");
		return ptr;
	}


	void SetTerrainColor(const struct FLinearColor& NewColor);
};


// Class Paper2D.PaperTerrainMaterial
// 0x0018 (0x0048 - 0x0030)
class UPaperTerrainMaterial : public UDataAsset
{
public:
	TArray<struct FPaperTerrainMaterialRule>           Rules;                                                    // 0x0030(0x0010) (Edit, ZeroConstructor)
	class UPaperSprite*                                InteriorFill;                                             // 0x0040(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTerrainMaterial");
		return ptr;
	}

};


// Class Paper2D.PaperTerrainSplineComponent
// 0x0010 (0x0650 - 0x0640)
class UPaperTerrainSplineComponent : public USplineComponent
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0640(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTerrainSplineComponent");
		return ptr;
	}

};


// Class Paper2D.PaperTileLayer
// 0x0070 (0x0098 - 0x0028)
class UPaperTileLayer : public UObject
{
public:
	struct FText                                       LayerName;                                                // 0x0028(0x0028) (BlueprintVisible, BlueprintReadOnly)
	int                                                LayerWidth;                                               // 0x0040(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                LayerHeight;                                              // 0x0044(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bHiddenInGame : 1;                                        // 0x0048(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bLayerCollides : 1;                                       // 0x0048(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bOverrideCollisionThickness : 1;                          // 0x0048(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bOverrideCollisionOffset : 1;                             // 0x0048(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0049(0x0003) MISSED OFFSET
	float                                              CollisionThicknessOverride;                               // 0x004C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              CollisionOffsetOverride;                                  // 0x0050(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                LayerColor;                                               // 0x0054(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                AllocatedWidth;                                           // 0x0064(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                AllocatedHeight;                                          // 0x0068(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x006C(0x0004) MISSED OFFSET
	TArray<struct FPaperTileInfo>                      AllocatedCells;                                           // 0x0070(0x0010) (ZeroConstructor)
	class UPaperTileSet*                               TileSet;                                                  // 0x0080(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	TArray<int>                                        AllocatedGrid;                                            // 0x0088(0x0010) (ZeroConstructor, Deprecated)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTileLayer");
		return ptr;
	}

};


// Class Paper2D.PaperTileMap
// 0x0080 (0x00A8 - 0x0028)
class UPaperTileMap : public UObject
{
public:
	int                                                MapWidth;                                                 // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                MapHeight;                                                // 0x002C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                TileWidth;                                                // 0x0030(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                TileHeight;                                               // 0x0034(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              PixelsPerUnrealUnit;                                      // 0x0038(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SeparationPerTileX;                                       // 0x003C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SeparationPerTileY;                                       // 0x0040(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SeparationPerLayer;                                       // 0x0044(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TSoftObjectPtr<class UPaperTileSet>                SelectedTileSet;                                          // 0x0048(0x0028)
	class UMaterialInterface*                          Material;                                                 // 0x0070(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TArray<class UPaperTileLayer*>                     TileLayers;                                               // 0x0078(0x0010) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor)
	float                                              CollisionThickness;                                       // 0x0088(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESpriteCollisionMode>                  SpriteCollisionDomain;                                    // 0x008C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ETileMapProjectionMode>                ProjectionMode;                                           // 0x008D(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x008E(0x0002) MISSED OFFSET
	int                                                HexSideLength;                                            // 0x0090(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0094(0x0004) MISSED OFFSET
	class UBodySetup*                                  BodySetup;                                                // 0x0098(0x0008) (ZeroConstructor, IsPlainOldData)
	int                                                LayerNameIndex;                                           // 0x00A0(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x00A4(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTileMap");
		return ptr;
	}

};


// Class Paper2D.PaperTileMapActor
// 0x0008 (0x0330 - 0x0328)
class APaperTileMapActor : public AActor
{
public:
	class UPaperTileMapComponent*                      RenderComponent;                                          // 0x0328(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTileMapActor");
		return ptr;
	}

};


// Class Paper2D.PaperTileMapComponent
// 0x0050 (0x05D0 - 0x0580)
class UPaperTileMapComponent : public UMeshComponent
{
public:
	int                                                MapWidth;                                                 // 0x0580(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                MapHeight;                                                // 0x0584(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                TileWidth;                                                // 0x0588(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                TileHeight;                                               // 0x058C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	class UPaperTileSet*                               DefaultLayerTileSet;                                      // 0x0590(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	class UMaterialInterface*                          Material;                                                 // 0x0598(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	TArray<class UPaperTileLayer*>                     TileLayers;                                               // 0x05A0(0x0010) (ZeroConstructor, Deprecated)
	struct FLinearColor                                TileMapColor;                                             // 0x05B0(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                UseSingleLayerIndex;                                      // 0x05C0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bUseSingleLayer;                                          // 0x05C4(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x05C5(0x0003) MISSED OFFSET
	class UPaperTileMap*                               TileMap;                                                  // 0x05C8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTileMapComponent");
		return ptr;
	}


	void SetTileMapColor(const struct FLinearColor& NewColor);
	bool SetTileMap(class UPaperTileMap* NewTileMap);
	void SetTile(int X, int Y, int Layer, const struct FPaperTileInfo& NewValue);
	void SetLayerColor(const struct FLinearColor& NewColor, int Layer);
	void SetLayerCollision(int Layer, bool bHasCollision, bool bOverrideThickness, float CustomThickness, bool bOverrideOffset, float CustomOffset, bool bRebuildCollision);
	void SetDefaultCollisionThickness(float Thickness, bool bRebuildCollision);
	void ResizeMap(int NewWidthInTiles, int NewHeightInTiles);
	void RebuildCollision();
	bool OwnsTileMap();
	void MakeTileMapEditable();
	void GetTilePolygon(int TileX, int TileY, int LayerIndex, bool bWorldSpace, TArray<struct FVector>* Points);
	struct FLinearColor GetTileMapColor();
	struct FVector GetTileCornerPosition(int TileX, int TileY, int LayerIndex, bool bWorldSpace);
	struct FVector GetTileCenterPosition(int TileX, int TileY, int LayerIndex, bool bWorldSpace);
	struct FPaperTileInfo GetTile(int X, int Y, int Layer);
	void GetMapSize(int* MapWidth, int* MapHeight, int* NumLayers);
	struct FLinearColor GetLayerColor(int Layer);
	void CreateNewTileMap(int MapWidth, int MapHeight, int TileWidth, int TileHeight, float PixelsPerUnrealUnit, bool bCreateLayer);
	class UPaperTileLayer* AddNewLayer();
};


// Class Paper2D.PaperTileSet
// 0x0080 (0x00A8 - 0x0028)
class UPaperTileSet : public UObject
{
public:
	struct FIntPoint                                   TileSize;                                                 // 0x0028(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  TileSheet;                                                // 0x0030(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TArray<class UTexture*>                            AdditionalSourceTextures;                                 // 0x0038(0x0010) (Edit, ZeroConstructor)
	struct FIntMargin                                  BorderMargin;                                             // 0x0048(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FIntPoint                                   PerTileSpacing;                                           // 0x0058(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FIntPoint                                   DrawingOffset;                                            // 0x0060(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                WidthInTiles;                                             // 0x0068(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                HeightInTiles;                                            // 0x006C(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                AllocatedWidth;                                           // 0x0070(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                AllocatedHeight;                                          // 0x0074(0x0004) (ZeroConstructor, IsPlainOldData)
	TArray<struct FPaperTileMetadata>                  PerTileData;                                              // 0x0078(0x0010) (Edit, EditFixedSize, ZeroConstructor)
	TArray<struct FPaperTileSetTerrain>                Terrains;                                                 // 0x0088(0x0010) (ZeroConstructor)
	int                                                TileWidth;                                                // 0x0098(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                TileHeight;                                               // 0x009C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                Margin;                                                   // 0x00A0(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                Spacing;                                                  // 0x00A4(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.PaperTileSet");
		return ptr;
	}

};


// Class Paper2D.TileMapBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UTileMapBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Paper2D.TileMapBlueprintLibrary");
		return ptr;
	}


	struct FPaperTileInfo MakeTile(int TileIndex, class UPaperTileSet* TileSet, bool bFlipH, bool bFlipV, bool bFlipD);
	struct FName GetTileUserData(const struct FPaperTileInfo& Tile);
	struct FTransform GetTileTransform(const struct FPaperTileInfo& Tile);
	void BreakTile(const struct FPaperTileInfo& Tile, int* TileIndex, class UPaperTileSet** TileSet, bool* bFlipH, bool* bFlipV, bool* bFlipD);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
