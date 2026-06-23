// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Modules/ModuleManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "RainRendering.generated.h"


class FRainRenderingModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnStaticRainOcclusionTextureUpdated, UTexture2D*, NewTexture, FVector, DepthTextureCentre );

UCLASS(config = Game, defaultconfig)
class RAINRENDERING_API UFGRainRenderingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Meta=(WorldContext ="WorldContextObject"))
	static void SetWetnessIntensity(UObject* WorldContextObject, float NewValue);
	
	static bool ShouldRunRainPass( const UWorld* World,float& OutIntensity);
	static void GetDepthCaptureInformation( const UWorld* World, FVector& FactoryCaptureLocation, FVector& StaticOcclusionCaptureLocation );
	static void GetTextures(const UWorld* World, UTexture2D*& OutDitherTexture, UTexture2D*& OutStaticWorldTexture, UTextureRenderTarget2D*& OutFactoryOcclusionRenderTarget);
	static void UpdateFactoryOcclusionCaptureLocation(const UWorld* World, const FVector& NewLocation);
	static void UpdateStaticOcclusionDepthTextureAndLocation(const UWorld* World,const FVector& NewCaptureLocation,UTexture2D* NewTexture);

	UFUNCTION(BlueprintPure)
	float GetRainIntensity() const { return RainIntensity; }
	
	UPROPERTY(BlueprintAssignable, Category = "Rain Occlusion")
	FOnStaticRainOcclusionTextureUpdated OnRainOcclusionTextureUpdate;

protected:
	UPROPERTY()
	float RainIntensity = 0;

private:
	UPROPERTY()
	TObjectPtr<UTexture2D> DitherTexture = nullptr;
	
	UPROPERTY()
	TObjectPtr<UTexture2D> StaticWorldOcclusionDepthTexture = nullptr;

	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> FactoryOcclusionRenderTarget = nullptr;

	UPROPERTY(Config)
	TSoftObjectPtr<UTexture2D> FallbackTexture = nullptr;

	UPROPERTY()
	TObjectPtr<UTexture2D> LoadedFallbackTexture = nullptr;
	
	FVector FactoryOcclusionCaptureLocation = FVector::ZeroVector;
	FVector StaticOcclusionCaptureLocation = FVector::ZeroVector;
	
	// UWorldSubsystem interface
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override { return WorldType == EWorldType::Game || WorldType == EWorldType::PIE; }
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End UWorldSubsystem;

	// Scene view extension.
	TSharedPtr<class FRainRenderingViewExtension, ESPMode::ThreadSafe> SceneViewExtension;
};

UCLASS(Config=Game, DefaultConfig, DisplayName="Rain shader")
class URainRenderingDeveloperSettings : public UDeveloperSettings
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,config)
	TSoftObjectPtr<UTextureRenderTarget2D> RainRenderTargetAsset;

	UPROPERTY(EditAnywhere,config)
	TSoftObjectPtr<UTexture2D> DitherTexture;
	
	UPROPERTY(EditAnywhere,config)
	TSoftObjectPtr<UTexture2D> StaticWorldDepthMap;

	UPROPERTY(EditAnywhere,config)
	FVector WorldHeightCaptureLocation = {0,0,0};
};