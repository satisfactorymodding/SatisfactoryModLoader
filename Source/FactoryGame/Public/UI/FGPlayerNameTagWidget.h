// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGPlayerNameTagWidget.generated.h"

/**
 * The name tag widget placed over a player to identify them
 */
UCLASS( abstract )
class FACTORYGAME_API UFGPlayerNameTagWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdatePlayerData( FString playerName, FLinearColor playerColor, bool isPlayerOnline, bool useOverrideIcon = false );

protected:	
	virtual void NativeConstruct() override;
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Character" )
	void OnPlayerDataUpdated();

	UFUNCTION()
	void OnHiddenHUDModeChanged( bool hideHUD );
	
	UPROPERTY( BlueprintReadOnly, Category = "Character" )
	FString mPlayerName;
	
	UPROPERTY( BlueprintReadOnly, Category = "Character" )
	FLinearColor mPlayerColor;

	UPROPERTY( BlueprintReadOnly, Category = "Character" )
	bool mIsPlayerOnline;

	UPROPERTY( BlueprintReadOnly, Category = "Character" )
	bool mIsPlayerCheckmarked;

	UPROPERTY( BlueprintReadOnly, Category = "Character" )
	UTexture2D* mOverrideIcon;

	/** The cached local players HUD. All name tags on the same instance of a game will have the same HUD */
	UPROPERTY( Transient )
	class AFGHUD* mCachedLocalHUD;

	/** The cached icon for the player */
	UPROPERTY( Transient )
	UTexture2D* mCachedIcon;
};
