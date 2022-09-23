// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	void UpdatePlayerData( FString playerName, FLinearColor playerColor, bool isPlayerOnline );

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

	/** The cached local players HUD. All name tags on the same instance of a game will have the same HUD */
	UPROPERTY( Transient )
	class AFGHUD* mCachedLocalHUD;
};
