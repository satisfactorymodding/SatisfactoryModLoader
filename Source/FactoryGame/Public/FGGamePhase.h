// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGGamePhaseManager.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "FGGamePhase.generated.h"

/**
 * 
 */
UCLASS( BlueprintType )
class FACTORYGAME_API UFGGamePhase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/* Returns a sorted list of all game phases in the game */
	UFUNCTION( BlueprintCallable, Category="GamePhase")
	static TArray<UFGGamePhase*> GetAllGamePhaseAssetsSorted();

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="UI|Display" )
	FText mDisplayName;

	/* Determines the last tier of a game phase. A lower value indicates an earlier phase in game progression */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Progression)
	int32 mLastTierOfPhase;

	/* Used to establish order when mLastTierOfPhase is identical for two game phases. A lower value signifies an earlier phase. 
	 * Especially useful for the final game phase, as it may have the same mLastTierOfPhase as the phase just before it */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Progression)
	float mPriority;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category=Cost )
	TArray< FItemAmount > mCosts;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category=Legacy )
	TEnumAsByte< EGamePhase > mGamePhase;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FGameplayTag mPhaseTag;
	
	bool operator<(const UFGGamePhase& otherGamePhase) const;
	bool operator<=( const UFGGamePhase& otherGamePhase ) const;
	bool operator>(const UFGGamePhase& otherGamePhase) const;
	bool operator>=( const UFGGamePhase& otherGamePhase ) const;
	bool operator==( const UFGGamePhase& otherGamePhase ) const;
	
	UFUNCTION(BlueprintPure, meta=(DisplayName = "GamePhase > GamePhase", CompactNodeTitle = ">", Keywords = "> greater"), Category="GamePhase")
	static bool Greater_GamePhaseGamePhase(UFGGamePhase* gamePhaseA, UFGGamePhase* gamePhaseB);
	UFUNCTION(BlueprintPure, meta=(DisplayName = "GamePhase < GamePhase", CompactNodeTitle = "<", Keywords = "< less"), Category="GamePhase")
	static bool Less_GamePhaseGamePhase(UFGGamePhase* gamePhaseA, UFGGamePhase* gamePhaseB);
	UFUNCTION(BlueprintPure, meta=(DisplayName = "GamePhase >= GamePhase", CompactNodeTitle = ">=", Keywords = ">= greater"), Category="GamePhase")
	static bool GreaterEqual_GamePhaseGamePhase(UFGGamePhase* gamePhaseA, UFGGamePhase* gamePhaseB);
	UFUNCTION(BlueprintPure, meta=(DisplayName = "GamePhase <= GamePhase", CompactNodeTitle = "<=", Keywords = "<= less"), Category="GamePhase")
	static bool LessEqual_GamePhaseGamePhase(UFGGamePhase* gamePhaseA, UFGGamePhase* gamePhaseB);
};
