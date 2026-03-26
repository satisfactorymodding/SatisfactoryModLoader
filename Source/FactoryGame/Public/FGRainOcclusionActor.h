// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGDynamicStruct.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "Math/GenericOctree.h"
#include "UI/FGDebugOverlayWidget.h"
#include "FGRainOcclusionActor.generated.h"

class UNiagaraComponent;
class UBoxComponent;
class USceneCaptureComponent2D;
class UInstancedStaticMeshComponent;
class AFGBuildable;

DECLARE_STATS_GROUP( TEXT( "RainOcclusion" ), STATGROUP_RainOcclusion, STATCAT_Advanced );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnRainOcclusionSceneModified );

struct FRuntimeBuildableInstanceData;

struct FRainHashKey
{
	uint64 Hash = 0;
	bool bIsFromBuildable = false;

	friend uint64 GetTypeHash(const FRainHashKey& ShapeData)
	{
		return HashCombine(GetTypeHash(ShapeData.Hash),GetTypeHash(ShapeData.bIsFromBuildable));
	}

	FRainHashKey(uint64 InHash, bool bInIsFromBuildable)
	{
		Hash = InHash;
		bIsFromBuildable = bInIsFromBuildable;
	}

	FORCEINLINE bool operator ==(const FRainHashKey& Other) const
	{
		return	bIsFromBuildable == Other.bIsFromBuildable && Hash == Other.Hash;
	}
};

UENUM()
enum class EFGRainOcclusionShape : uint8
{
	ROCS_Box  			UMETA(DisplayName = "Box"),
	ROCS_CustomMesh		UMETA(DisplayName = "Custom Mesh (Expensive)")
};

struct FACTORYGAME_API FSimpleOcclusionData
{
	FTransform Transform;
	FFGDynamicStruct TypeSpecificData;
};

struct FACTORYGAME_API FRainOcclusionShapeData
{
	FVector3f Location;
	FVector3f Scale;
	FRotator3f Rotation;
	FRainHashKey Hash;
	TWeakObjectPtr<UInstancedStaticMeshComponent> AssociatedInstanceComponent;
};

struct FRainOcclusionShapeDataOctreeSemantics
{
	enum { MaxElementsPerLeaf = 10 };
	enum { MinInclusiveElementsPerNode = 5 };
	enum { MaxNodeDepth = 20 };
	
	using FOctree = TOctree2< FRainOcclusionShapeData*, FRainOcclusionShapeDataOctreeSemantics >;
	using ElementAllocator = TInlineAllocator< MaxElementsPerLeaf >;
	static FBoxCenterAndExtent GetBoundingBox( const FRainOcclusionShapeData* Element );
	static bool AreElementsEqual( const FRainOcclusionShapeData* A, const FRainOcclusionShapeData* B );
	static void SetElementId( FOctree& Octree,const FRainOcclusionShapeData* Element, FOctreeElementId2 OctreeElementID );
};

struct FOcclusionShapeDataOctree : public TOctree2< FRainOcclusionShapeData*, FRainOcclusionShapeDataOctreeSemantics >
{
	FOcclusionShapeDataOctree( const FVector& Origin, FVector::FReal Extent) : TOctree2( Origin, Extent ) { }
	FOcclusionShapeDataOctree() = default;
	TMap<FRainHashKey,FOctreeElementId2> mElementIDMap;
};



struct FLookupData
{
	int32 Index;
	/* This component is owned by the AFGRainOcclusionActor and will be never destroyed.*/
	UInstancedStaticMeshComponent* Owner;
};

UCLASS(Config = Game, DefaultConfig)
class FACTORYGAME_API URainOcclusionWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	// Begin UTickableWorldSubsystem interface.
	// Initializes Octree, Base actor and default component
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FRainOcclusionSubsystem, STATGROUP_Tickables);
	}
	// End UTickableWorldSubsystem interface.
	
public:
	/* Adds shape to octree */
	static void AddShapeFromBuildable( const AFGBuildable* Buildable, const FSimpleOcclusionData& InstanceData, FRainHashKey Hash );

	static void AddShapeFromClass( const UObject* WorldContext, const AFGBuildable* BuildableCDO, const FSimpleOcclusionData& InstanceData, FRainHashKey Hash);
	
	/* Removes shape to octree */
	static void RemoveShape(const UObject* WorldContext, const AFGBuildable* BuildableCDO, FRainHashKey Hash);
	
	UFUNCTION(BlueprintCallable, category="RainOcclusion")
	AActor* GetRainRootActor() const { return WorldActor; }
	
	UPROPERTY(BlueprintAssignable, Category = "Rain Occlusion")
	FOnRainOcclusionSceneModified OnRainOcclusionSceneModified;

private:
	/* Gets ISM or creates new one if none is found for the given material
	 * NOTE: None will use default material which is a square shape with depth offset in primitive custom data 0 in cm. */
	UInstancedStaticMeshComponent* CreateOrGetShapeComponent( UMaterialInterface* InMaterial );

	/* Gets or creates an ISM if none is found based on the StaticMesh*/
	UInstancedStaticMeshComponent* CreateOrGetMeshShapeComponent(UStaticMesh* Mesh);
	
	/* INTERNAL.
	 * Add Sprite to oct tree */
	void AddBoxSprite( const AFGBuildable* Buildable,const FTransform& ActorTransform, FRainHashKey Hash);
	void RemoveBoxSprite( FRainHashKey Hash);

	/* Add custom shaped mesh to the rain occlusion scene */
	void AddMeshShape(const AFGBuildable* Buildable,const FSimpleOcclusionData& InstanceData, FRainHashKey Hash);
	void RemoveMeshShape( FRainHashKey Hash );
	
	void ProcessAddsAndRemovals();
	void EnsureWTTaskComplete() const;
	
	/* Outer actor that contains all instance static meshes. */
	UPROPERTY()
	TObjectPtr<AActor> WorldActor = nullptr;

	/* Material instance map to instance staticmesh component.*/
	UPROPERTY()
	TMap<TObjectPtr<UMaterialInterface>, TObjectPtr<UInstancedStaticMeshComponent>> mInstanceToComponentMap; 

	UPROPERTY()
	TMap<TObjectPtr<UStaticMesh>, TObjectPtr<UInstancedStaticMeshComponent>> mStaticMeshToComponentMap; 

	/* Default mesh for the instance static mesh component, assumes default material is assigned.
	 * Example of assigning in DefaultGame.ini:
	 * [/Script/FactoryGame.RainOcclusionWorldSubsystem]
	 * DefaultMesh=/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane */
	UPROPERTY(Config)
	TSoftObjectPtr<UStaticMesh> DefaultMesh;

	/* Octree containing all potential entries for the rain occluder. */
	FOcclusionShapeDataOctree mOcclusionShapeOctTree;

	/* Current active shapes in the world which exists in the mInstanceToComponentMap */
	TSet<FRainOcclusionShapeData*> ActiveOcclusionShapes;
	
	/* This frame added shapes which need to be added to the instance mesh components.*/
	TSet<FRainOcclusionShapeData*> AddedOcclusionShapes;

	/* TODO */
	TSet<FRainOcclusionShapeData*> NewOcclusionShapes;

	/* This frame removed shapes which need to be removed from the instance mesh components.*/
	TSet<FRainOcclusionShapeData*> RemovedOcclusionShapes;

	/* Hash to lookup data map, used for instance removal.*/
	TMap<FRainHashKey, FLookupData> mLookupTable;

	/* Map with ISM to Array of "free" instances, populated when an instance is removed from the ISM
	 * and consumed when instances are added back to the ISM.
	 * NOTE : UInstancedStaticMeshComponent* pointers are managed by the system and won't be nulled. */
	TMap<UInstancedStaticMeshComponent*,TArray<int32> > mOccluderPoolInstances;

	// TODO make this param.
	float CellSize = 51200;

	void DrawCells(FVector PC) const;
	
	FGraphEventRef LookupTask;
	
#if !UE_BUILD_SHIPPING
//	TSet<FRainHashKey> DebugHashList = {};
	TMap<FRainHashKey, FString> HashDebugMap = {};
#endif
};

UCLASS()
class FACTORYGAME_API AFGStaticWorldRainOcclusionManager : public AActor
{
	GENERATED_BODY()

	AFGStaticWorldRainOcclusionManager();

protected:
	virtual void BeginPlay() override;
	
	/* Update which cells are relevant right now. */
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetOcclusionDataForWorldLocation(FVector WorldPosition,FVector& GridCellWPLocation, FIntVector2& XY) const;

	UFUNCTION(BlueprintCallable)
	void RequestForceUpdateRainTextureInfoNextFrame() { bForceUpdateNextFrame = true; }
	
private:
	/* Cached pointer to the current active texture to ensure it stays in memory and to test against. */
	UPROPERTY()
	TObjectPtr<UTexture2D> mCurrentOcclusionTexture = nullptr;

	/* Cell id's to texture soft ptr map, loaded on demand once the player traverses through the world.*/
	UPROPERTY(VisibleAnywhere)
	TMap<FIntVector2,TSoftObjectPtr<UTexture2D>> mCellToTextureMap;

	/* Texture used when the tile is disabled, should have a pure black texture assign R16 format.
	 * This way we don't have to branch on the gpu. */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> mDisabledTileTextureFallBack = nullptr;
	
	/* Cell size to map to. */
	UPROPERTY(EditAnywhere)
	float CellSize = 102400;
	
	/* Amount of over render we want to do for the texture, should closely match the max draw distance of the wetness
	 * of the injection compute shader. */
	UPROPERTY(EditAnywhere)
	float OverCapture = 10000;

	/* Capture rendertarget texture size, Memory = (Size^2 * float16) with mips disabled. */
	UPROPERTY(EditAnywhere)
	int32 TextureSize = 512;

	bool bForceUpdateNextFrame = false;
	
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	void CaptureWorld();

	UFUNCTION(CallInEditor)
	void UpdateDisabledCells();
	
	void CaptureCell(FIntVector2 Location, FVector LocationWS);
	void MoveCameraToLocation(FIntVector2 CellLocation, FVector LocationWS);
	void SetupIgnoreActors();
	
	UFUNCTION(BlueprintCallable)
	void DrawCells();
	
#if WITH_EDITORONLY_DATA
	UFUNCTION(BlueprintCallable)
	void AddRemoveFromIgnoreList(int32 X, int32 Y);
	
	UPROPERTY(EditInstanceOnly)
	TSet<FIntVector2> IgnoreList;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ActorsToExcludeFromCapture;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> WorldBounds;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneCaptureComponent2D> CaptureCamera;

	UPROPERTY(EditInstanceOnly)
	TObjectPtr<UTextureRenderTarget2D> CameraSourceRenderTarget;
#endif
#endif
};


// TODO pre exp 1.2, remove all references to this class
UCLASS()
class FACTORYGAME_API AFGRainOcclusionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGRainOcclusionActor(); 
};


UCLASS()
class FACTORYGAME_API AFGRainActor : public AActor
{
	GENERATED_BODY()

	AFGRainActor();
	
public:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> mRainComponent = nullptr;
};