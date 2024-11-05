// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "FGRiver.generated.h"

class ACharacter;
class USplineMeshComponent;
class UMaterialInterface;

UCLASS(HideCategories ="Input, Collision, LOD, Cooking, Actor")
class FACTORYGAME_API AFGRiver : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGRiver();

	USplineComponent* GetRiverSpline() const 	{ return mSplineComponent; }
	float GetVolumePrecision() const 			{ return mVolumePrecision; }
	float GetVolumeHeightOffset() const 		{ return mVolumeHeightOffset; }
	float GetRiverDepth() const 				{ return 1000; }

	// Begin IFGSignificanceInterface
	virtual float GetSignificanceRange() override { return 20000; }
	// End
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform & Transform) override;

	void FixupSplinePoints();
    void ConstructMesh();
	void ConstructVolumes();

	UFUNCTION(BlueprintCallable)
	void SetupMaterialValues(UMaterialInstanceDynamic* Material = nullptr);

	/* Set Red vertex color on the mesh component based on spline Z scale / 100. */
	void ApplyVertexColors(TArray<USplineMeshComponent*>& MeshComponents);

	FORCEINLINE float GetRiverLocationHeightOffset( FVector WorldLocation, float IntensityOnSpline) const
	{
		float Time = GetWorld()->GetTimeSeconds();
	
		float X = FMath::Sin((((WorldLocation.X / BuoyancyScale.X) + Time)) * PI * 2);
		float Y = FMath::Sin((((WorldLocation.Y / BuoyancyScale.Y) + Time)) * PI * 2);
	
		return (X + Y) * BuoyancyMaxIntensity * FMath::Max<float>(IntensityOnSpline, 0.01 );
	}
	
private:
	void HandlePush(float DeltaTime, ACharacter* Actor);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY()
	TArray<UBoxComponent*> mOverlappingShapes;
	
	UPROPERTY(VisibleAnywhere)
	TArray<USplineMeshComponent*> mSplineMeshComponents;
	
protected:
	UPROPERTY( BlueprintReadOnly )
	USplineComponent* mSplineComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* mSplineMesh;
	
	UPROPERTY(EditAnywhere)
	float mSegmentLengthMultiplier;

	/* how many units should be in between every volume.*/
	UPROPERTY(EditAnywhere)
    float mVolumePrecision = 1000;
	
	/* Height offset for water volume.*/
	UPROPERTY(EditDefaultsOnly)
	float mVolumeHeightOffset;
	
	/*Intensity the character will get pushed with. */
	UPROPERTY(EditAnywhere, Category = "Gameplay" )
	float mDefaultFlowRate;
	
	/* Material used by the spline mesh component */
	UPROPERTY(EditAnywhere, Category = "Art direction")
	UMaterialInterface* mBaseMaterial;

	UPROPERTY(EditAnywhere, Category = "Art direction")
	TMap< FString, float > mScalarParameters;

	UPROPERTY(EditAnywhere, Category = "Art direction")
	TMap< FString, FLinearColor > mVectorParameters;

	UPROPERTY(EditAnywhere)
	FVector2D BuoyancyScale;

	UPROPERTY(EditAnywhere)
	float BuoyancyMaxIntensity;

	UPROPERTY(EditAnywhere)
	class UMaterialParameterCollection* mDataCollection;
	
	UPROPERTY(EditInstanceOnly,Category="Visuals")
	bool bFadeIn = false;

	UPROPERTY(EditInstanceOnly,Category="Visuals")
	bool bSideFadeIn = false;
	
	UPROPERTY(EditInstanceOnly,Category="Visuals")
	bool bFadeOut = false;
	
	UPROPERTY(EditInstanceOnly,Category="Visuals")
	bool bSideFadeOut = false;

	
public:

#if WITH_EDITORONLY_DATA
	/* Visualization begin */
	void OnSelected(UObject* Object);
	void ReDraw();
	void DrawDebugData();
	void StopDrawDebugData();
	virtual void Destroyed() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* mEditorOnlyMaterialInstance;
	
	bool bWasSelected;

	/*Hide editor spline, mainly usefull for landscape based spline.*/
	UPROPERTY(EditAnywhere)
	bool ED_HideSpline;
	/* end */

	float DesiredSplineLength = 2000;
	
#endif
#if WITH_EDITOR
	
	UFUNCTION(CallInEditor)
	void UpdateFlowIntensity();

	UFUNCTION(CallInEditor, Category = "Art Direction")
	void PopulateMaterialSettings();

	UFUNCTION(BlueprintCallable, Category = "CSS Editor tools", meta = (DevelopmentOnly))
	static void BuildRiverFromData(const UObject* WorldContext, TSubclassOf<AFGRiver> BaseClass, TArray<FVector> WorldLocations, TArray<FVector> PointScales, TArray<FRotator> PointRotations, TArray<FVector> ArriaveTangets, TArray<FVector> LeaveTangents);

	UFUNCTION(BlueprintCallable, Category = "CSS Editor tools", meta = (DevelopmentOnly))
	static void UpdateRiverFromData( AFGRiver* River, USplineComponent* SourceSpline );

	UFUNCTION(BlueprintCallable, Category = "CSS Editor tools", meta = (DevelopmentOnly))
	static void BuildRiverFromSplineMeshActor(const AActor* SourceActor,TSubclassOf<AFGRiver> RiverClass, bool bAutoResample = false, float WidthUpscale = 2);
	
	UFUNCTION(CallInEditor)
	void ResampleSpline();
#endif
	
};