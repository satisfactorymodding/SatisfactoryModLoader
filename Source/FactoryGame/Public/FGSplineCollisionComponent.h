// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "FGSplineCollisionComponent.generated.h"

struct FCachedCollisionBoxInfo
{
	FVector3f Location;
	FVector3f Extents;
	FRotator3f Rotation;
};

UCLASS()
class FACTORYGAME_API UFGSplineCollisionComponent : public UPrimitiveComponent
{
	GENERATED_UCLASS_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AddBox(const FVector& Location,const FVector& Extent, const FRotator& Rotation);
	void AddBoxes(const TArray<FCachedCollisionBoxInfo>& Boxes);
	
	UFUNCTION(BlueprintCallable)
	void CreatePhysics();

	UFUNCTION(BlueprintCallable)
	void DestroyPhysics();
	
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	
protected:
	virtual UBodySetup* GetBodySetup() override;
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual bool ShouldCreateRenderState() const override;
	
private:
	virtual bool CanEditSimulatePhysics() override { return false; }
	virtual bool ShouldCreatePhysicsState() const override { return true; }

	virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;
	virtual void GetNavigationData(FNavigationRelevantData& Data) const override;
	virtual bool IsNavigationRelevant() const override;
	
	/* Assigned physics body. */
	UPROPERTY(Transient)
	TObjectPtr<UBodySetup> mBodySetup = nullptr;

	TArray<FCachedCollisionBoxInfo> mCachedCollisionInfo = {};

	bool bDynamicObstacle = false;
};
