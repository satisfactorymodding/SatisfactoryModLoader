// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "FGFallingTree.generated.h"


class UNiagaraSystem;
class UCapsuleComponent;
class UDynamicMeshComponent;
class UStaticMesh;
class UMaterialInterface;
class UAkAudioEvent;

UCLASS(BlueprintType)
class FACTORYGAME_API AFGFallingTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGFallingTree();

	UFUNCTION()
	static void SpawnFallingTree(UObject* WorldContext, TSubclassOf<AFGFallingTree> Class, UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& OverridenMaterials, const FTransform& MeshTransform, UFGFoliageDestructionData* Data );
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SetupAsync(UStaticMesh* StaticMesh,const TArray<UMaterialInterface*>& OverridenMaterials);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void PreSetup(UStaticMesh* StaticMesh,const TArray<UMaterialInterface*>& OverridenMaterials);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetupTree(UStaticMesh* StaticMesh,const TArray<UMaterialInterface*>& OverridenMaterials);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void PostSetup();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="visuals")
	UDynamicMeshComponent* RootMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="visuals")
	UDynamicMeshComponent* TrunkMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Collision")
	UCapsuleComponent* RootCapsule;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Collision")
	UCapsuleComponent* TrunkCapsule;

	UPROPERTY()
	UStaticMesh* TreeMesh;
	
	UPROPERTY(DisplayName="CutPivot",VisibleAnywhere,BlueprintReadOnly,Category="MeshGeneration")
	FVector SliceLocation;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="MeshGeneration")
	float TrunkRadius;
	
	/* Index for crown VFX */
	UPROPERTY(BlueprintReadOnly)
	int32 CrownID;

	UPROPERTY(BlueprintReadOnly)
	FName LeafSplashParameterIndexName;
	
	UPROPERTY(BlueprintReadOnly)
	FName LeafSplashSocketName;

	UPROPERTY(BlueprintReadOnly)
	UNiagaraSystem* LeafSplashVFXSystem;

	UPROPERTY(BlueprintReadOnly)
	UNiagaraSystem* TrunkSplashVFXSystem;
	
	UPROPERTY(BlueprintReadOnly)
	FName TrunkSplashVFXIndexName;

	UPROPERTY(BlueprintReadOnly,Category="Audio")
	UAkAudioEvent* mFoliageLeafSplatterAKEvent = nullptr;
	
	UPROPERTY(BlueprintReadOnly,Category="Audio")
	UAkAudioEvent* mTreeFallCrumbleAKEvent = nullptr;
	
	UPROPERTY(BlueprintReadOnly,Category="Audio")
	UAkAudioEvent* mTreeFallHitAKEvent = nullptr;

	/* Cap material read from the asset data, will be null if we use the default one. */
	UPROPERTY(BlueprintReadOnly)
	UMaterialInterface* mCapOverride = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float MaxWedgeAngle = 15;
	
	UFUNCTION(BlueprintCallable,Category="EditorOnly")
	static bool SetTrunkRadius(UStaticMesh* InMesh, float InRadius, FVector InPivot, FBoxSphereBounds InBounds, float InMaxWedge);

	UFUNCTION(BlueprintCallable,Category="EditorOnly")
	static void GetMeshData(UStaticMesh* InMesh, float& OutRadius, FVector& OutPivot,FBoxSphereBounds& OutBounds, float& OutMaxWedge);
};
