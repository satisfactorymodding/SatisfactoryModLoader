// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGRemoteCallObject.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, Abstract, Within = FGPlayerController )
class FACTORYGAME_API UFGRemoteCallObject : public UObject
{
	GENERATED_BODY()

public:
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;
	virtual UWorld* GetWorld() const override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the Callspace of the outer PlayerController. */
	int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the NetDriver of the outer PlayerController.*/
	bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;

	/** Helper function to get the game state. Can't be done in BluePrint since the GetGameState function hides it world context pin */
	UFUNCTION( BlueprintPure, Category = "Remote Call Object" )
	class AFGGameState* GetGameState() const;

	/** Returns the FGPlayerController owning this RCO */
	UFUNCTION( BlueprintPure, Category = "Remote Call Object" )
	class AFGPlayerController* GetOwnerPlayerController() const;

	/** Returns the player character owning this RCO */
	UFUNCTION( BlueprintPure, Category = "Remote Call Object" )
	class AFGCharacterPlayer* GetOwnerPlayerCharacter() const;

	/** Whenever RCO of this class should be registered */
	virtual bool ShouldRegisterRemoteCallObject( const class AFGGameMode* gameMode ) const;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
