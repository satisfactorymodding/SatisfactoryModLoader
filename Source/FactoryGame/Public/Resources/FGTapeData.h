// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGTapeData.generated.h"


/** A struct that defines a single song */
USTRUCT( BlueprintType )
struct FSongData
{
	GENERATED_BODY()

	/** The actual audio event for this song */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	class UAkAudioEvent* Song = nullptr;

	/** The name of the artist */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FName ArtistName;

	/** The name (title) of the song */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FName SongName;
};

DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTapeTextureLoaded, UTexture2D*, Texture );

/**
 * Base class for mix tapes, define what songs exist in this tape
 */
UCLASS(Blueprintable, Abstract ,HideCategories=(Icon, Preview), meta=(AutoJSON=true))
class FACTORYGAME_API UFGTapeData : public UObject
{
	GENERATED_BODY()
public:
	/** Get songs in this tape */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Tape" )
    static TArray< class UAkAudioEvent* > GetSongs( TSubclassOf< class UFGTapeData > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Tape" )
	static TArray< FSongData > GetPlaylist( TSubclassOf< class UFGTapeData > inClass );

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Tape" )
	FText mTitle;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Tape" )
	FText mDescription;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Tape" )
	TSoftObjectPtr< UTexture2D > mSmallIcon;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Tape" )
	TSoftObjectPtr< UTexture2D > mBigIcon;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Tape" )
	TSoftObjectPtr< UTexture2D > mTapeTexture;
	
	/** Songs that exist on this tape */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Tape" )
	TArray< FSongData > mPlaylist;

	UFUNCTION( BlueprintCallable, Category = "Tape" )
	static void LoadSmallIcon( TSubclassOf< UFGTapeData > tapeClass, FOnTapeTextureLoaded OnTextureLoaded );

	UFUNCTION( BlueprintCallable, Category = "Tape" )
	static void LoadBigIcon( TSubclassOf< UFGTapeData > tapeClass, FOnTapeTextureLoaded OnTextureLoaded );

	UFUNCTION( BlueprintCallable, Category = "Tape" )
	static void LoadTapeTexture( TSubclassOf< UFGTapeData > tapeClass, FOnTapeTextureLoaded OnTextureLoaded );

private:
	static void LoadTapeTexture2DAsync( TSoftObjectPtr< UTexture2D >, FOnTapeTextureLoaded OnTextureLoaded );
};
