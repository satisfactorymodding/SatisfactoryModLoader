// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/Font.h"
#include "FGSignificanceInterface.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Components/StaticMeshComponent.h"
#include "FGTextRenderer.generated.h"

USTRUCT(BlueprintType)
struct FTextRendererImageEntry
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	UFont* RenderFont;

	/* 0.0 - 1.0*/
	UPROPERTY(EditDefaultsOnly, Category="Render Settings", meta = (ClampMin = 0.f, ClampMax = 1.f))
	float ScreenPositionX;

	/* 0.0 - 1.0*/
	UPROPERTY(EditDefaultsOnly, Category="Render Settings", meta = (ClampMin = 0.f, ClampMax = 1.f))
	float ScreenPositionY;
	
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	float Kerning = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	FLinearColor TextColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	bool bHasDynamicLength = true;

	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	float ResolutionScale = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	FLinearColor ShadowColor = FLinearColor::Black;
	
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	bool bOutlined = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	FVector2D ShadowOffset = FVector2D::ZeroVector;
	
	UPROPERTY(EditDefaultsOnly, Category="Render Settings")
	FLinearColor OutlineColor;
	
	UPROPERTY(EditDefaultsOnly, Category="Texture Settings")
	FString MaterialContentName = FString("Content");
	
	UPROPERTY(EditDefaultsOnly, Category="Texture Settings")
	uint16 CanvasSizeX = 32;

	UPROPERTY(EditDefaultsOnly, Category="Texture Settings")
	uint16 CanvasSizeY = 32;

	UPROPERTY(EditAnywhere,Category="Text")
	FString Text = "Awesome String here";
	
	UPROPERTY(VisibleInstanceOnly)
	UCanvasRenderTarget2D* GeneratedTexture = nullptr;

	// Begin future proof if we want to expose this later down the line.
	bool bCentreX = true;
	bool bCentreY = true;
	// End future proof
	
	/* Runtime flag. */
	bool bDirty = true;

	float DynamicUpscale = 1.f;
};

UCLASS(Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ))
class FACTORYGAME_API UFGTextRenderer : public UStaticMeshComponent
{
	GENERATED_BODY()

	UFGTextRenderer();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void UpdateText(int32 ElementID, FString Text);

	UFUNCTION(BlueprintCallable)
	void SetPlaneSize(float SizeX, float SizeY);
	
	void GenerateOrUpdateRenderResource();
	
	void SetupMaterial();
	void CleanupTempData();

protected:
	UPROPERTY(EditDefaultsOnly,Category="Significance")
	float mSignificanceRange = 5000.f;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	UMaterialInterface* mBaseMaterial = nullptr;
	
	UPROPERTY(VisibleInstanceOnly)
	UMaterialInstanceDynamic* mMaterialInstance = nullptr;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	TArray<FTextRendererImageEntry> Elements;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	uint8 bHasDynamicText:1 = false;
	
	uint8 bIsSignificant:1 = false;
};
