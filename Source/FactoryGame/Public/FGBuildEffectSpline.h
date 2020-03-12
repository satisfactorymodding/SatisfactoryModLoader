// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGBuildEffectSpline.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FEffectDoneDelegate );

UCLASS()
class FACTORYGAME_API AFGBuildEffectSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGBuildEffectSpline();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Effect" )
	void SetupAttachment( class AFGPipeBuilderTrail* inAttachment );

	/** Getter for attachment */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Effect" )
	FORCEINLINE class AFGPipeBuilderTrail* GetAttachment(){ return mAttachment; }
public:
	/** Attachment for this effect, can be null */
	UPROPERTY( BlueprintReadOnly, Category = "FactoryGame|Effect" , Meta = (ExposeOnSpawn = "true") )
	class AFGPipeBuilderTrail* mAttachment;

public:
	FORCEINLINE ~AFGBuildEffectSpline() = default;
};
