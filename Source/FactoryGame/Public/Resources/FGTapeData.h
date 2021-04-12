// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGTapeData.generated.h"

/**
 * Base class for mix tapes, define what songs exist in this tape
 */
UCLASS(Blueprintable, Abstract,HideCategories=(Icon, Preview),meta=(AutoJSON=true))
class FACTORYGAME_API UFGTapeData : public UObject
{
	GENERATED_BODY()
public:
	/** Get songs in this tape */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Tape" )
    static TArray< class UAkAudioEvent* > GetSongs( TSubclassOf< class UFGTapeData > inClass );
public:
	/** Songs that exist in this tape */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TArray< class UAkAudioEvent *> mSongs;
};
