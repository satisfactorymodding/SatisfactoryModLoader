// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGMapAreaTexture.generated.h"

USTRUCT()
struct FColorMapAreaPair
{
	GENERATED_BODY();

	FColorMapAreaPair() :
		MinX( MAX_int32 ),
		MinY( MAX_int32 ),
		MaxX( 0 ),
		MaxY( 0 )
	{
	}

#if WITH_EDITORONLY_DATA
	UPROPERTY( VisibleDefaultsOnly )
	FColor PaletteColor;
#endif

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UFGMapArea > MapArea;

	/** A top left pixel that together with MaxX/MaxY encompasses the entire area */
	UPROPERTY()
	int32 MinX;
	UPROPERTY()
	int32 MinY;

	UPROPERTY()
	int32 MaxX;
	UPROPERTY()
	int32 MaxY;
};


/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGMapAreaTexture : public UObject
{
	GENERATED_BODY()

public:

#if WITH_EDITOR

	/** When this is changed in the editor, propagate the changes to the preview window */
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;

	/** Generate a icon for this item */
	virtual void GenerateAreaData( bool reopenAssetEditor, TArray<UPackage*>& out_modifiedAddedPackages );

#endif

	/** Init the map area texture, fetches scale and offset */
	void InitMapAreaTexture( class AFGMinimapCaptureActor* inCaptureActor );

	/** Returns the map area encompassing the world location passed */
	TSubclassOf< UFGMapArea > GetMapAreaForWorldLocation( FVector worldLocation );

	/** Creates and inits the fog of war texture */
	void InitFogOfWarTexture( UObject* worldContext );

	/** Returns the current fog of war texture that has been generated */
	UFUNCTION( BlueprintPure, Category = "Fog of War" )
	UTexture2D* GetFogOfWarTexture() const;

	void GetAllMapAreas( TArray< TSubclassOf< UFGMapArea > > out_MapAreas ) const;

private:

	/** Called when any player enters a new area on the map, should case a redraw of the fog of war texture */
	UFUNCTION()
	void OnNewMapAreaVisisted( TSubclassOf< UFGMapArea > newMapArea );

	/** Updates the fog of war texture */
	void UpdateFogOfWarTexture( TSubclassOf< UFGMapArea > newMapArea  );

private:

#if WITH_EDITORONLY_DATA
	/** This is the texture that the level designers made to define areas on the map  */
	UPROPERTY( EditDefaultsOnly, Category = "1. Pick a texture" )
	UTexture2D* mAreaTexture;
#endif

	/** The current fog of war is generated to this texture */
	UPROPERTY()
	UTexture2D* mFogOfWarTexture;

	/** This is where we store the raw data we generated from the texture */
	UPROPERTY()
	TArray< uint8 > mAreaData;	

	/** This are all the unique colors found in the texture */
	UPROPERTY()
	TArray< FColor > mColorPalette;

	UPROPERTY( EditDefaultsOnly, Category = "2. Assign areas to match Palette" )
	TArray< FColorMapAreaPair > mColorToArea;

	/** A cached camera in the Skye */
	UPROPERTY()
	class AFGMinimapCaptureActor* mCaptureActor;

	/** The width of the data and the texture */
	UPROPERTY()
	int32 mDataWidth;

	/** Used for the map area check, world coordinate for "upper left". */
	FVector2D mUpperLeftWorld;

	/** Unreal Unit to pixel of map texture scale */
	float mWorldToMapScale;

	UPROPERTY()
	class AFGGameState* mCachedGameState;
};
