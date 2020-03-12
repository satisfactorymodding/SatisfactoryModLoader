#pragma once
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "Resources/FGItemDescriptor.h"
#include "FGRenderTargetStage.generated.h"

UCLASS(HideCategories=(Input,Actor))
class FACTORYGAME_API AFGRenderTargetStage : public AActor
{
	GENERATED_BODY()
public:
	// Ctor
	AFGRenderTargetStage();

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	//~ End AActor interface
	
	/** 
	 * Starts the rendering of the rendertarget scene
	 **/
	UFUNCTION( BlueprintCallable, Category="Stage")
	void BeginCapture();

	/**
	 * Stops the rendering of the rendertarget scene
	 **/
	UFUNCTION( BlueprintCallable, Category = "Stage" )
	void EndCapture();

	/**
	 * Capture a picture once
	 */
	UFUNCTION( BlueprintCallable, Category = "Stage" )
	void CaptureOnce();

	/**
	 * Set the format of the current rendertarget
	 * @param width - width of rendertarget
	 * @param height - height of rendertarget
	 * @param pixelFormat - pixelformat of rendertarget (valid are PF_B8G8R8A8, PF_A16B16G16R16 if you want to be able to convert the to static textures)
	 **/
	void SetRenderTargetFormat( int32 width, int32 height, EPixelFormat pixelFormat );

	/** Get the stage of this preview scene */
	UFUNCTION( BlueprintPure, Category="Stage")
	FORCEINLINE class USceneComponent* GetStage() const{ return mStage; }

	/** Call this when you have attached/detached components from our stage, this will make sure only they get rendered */
	UFUNCTION( BlueprintCallable, Category="Stage")
	void UpdateRenderedComponents();

	/** Set the distance we want to preview the stage from */
	UE_DEPRECATED( 4.16, "SetPreviewDistance has been replaced by SetPreviewView" )
	UFUNCTION( BlueprintCallable, Category="Stage", meta = ( DeprecatedFunction, DeprecationMessage = "SetPreviewDistance has been replaced by SetView" ) )
	void SetPreviewDistance( float distance );

	/** Move the camera so it looks at the stage from this view */
	UFUNCTION( BlueprintCallable, Category = "Stage" )
	void SetView( const FItemView& view );

	/** Get the render target that this stage renders to */
	UFUNCTION( BlueprintCallable, Category="Stage")
	class UTextureRenderTarget2D* GetRenderTarget() const;
protected:
	/** If we create a dynamic render target (that is, a new one every time), then this is it's x size */
	UPROPERTY(EditDefaultsOnly, Category = "Stage|RenderTarget" )
	int32 mDynamicRenderTargetSizeX;

	/** If we create a dynamic render target (that is, a new one every time), then this is it's y size */
	UPROPERTY(EditDefaultsOnly, Category = "Stage|RenderTarget" )
	int32 mDynamicRenderTargetSizeY;

	/** Set the pixel format of a dynamic rendertarget */
	UPROPERTY( EditDefaultsOnly, Category="Stage|RenderTarget")
	TEnumAsByte<EPixelFormat> mDynamicPixelFormat;

	/** The scene captor component that will generate the result of our render target */
	UPROPERTY(VisibleDefaultsOnly)
	class USceneCaptureComponent2D* mSceneCaptureComponent;

	/**
	 * The stage we want to change to preview the mesh when we do our preview, this is where the components will get attached when
	 * they get set
	 **/
	UPROPERTY()
	class USceneComponent* mStage;

	/** If true, then we create our own render target every time we want to play */
	UPROPERTY(EditDefaultsOnly,Category="Stage|RenderTarget")
	uint8 mDynamicRenderTarget:1;

public:
	FORCEINLINE ~AFGRenderTargetStage() = default;
};