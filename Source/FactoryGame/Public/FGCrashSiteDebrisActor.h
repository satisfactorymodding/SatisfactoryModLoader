// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSignificanceInterface.h"
#include "FGCrashSiteDebrisActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGCrashSiteDebrisActor : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGCrashSiteDebrisActor();

	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
protected:
	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* mMesh;

public:
	FORCEINLINE ~AFGCrashSiteDebrisActor() = default;
};
