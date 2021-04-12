// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "FGConstructionMessageInterface.h"
#include "FGRemoteCallObject.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class FACTORYGAME_API UFGRemoteCallObject : public UObject
{
	GENERATED_BODY()

public:
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the Callspace of the outer PlayerController. */
	int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the NetDriver of the outer PlayerController.*/
	bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;

	/** Helper function to get the game state. Can't be done in BluePrint since the GetGameState function hides it world context pin */
	UFUNCTION( BlueprintPure, Category = "Game State" )
	class AFGGameState* GetGameState();

	void SendHologramConstructMessage( class AFGBuildGun* buildGun, class AFGHologram* hologram, AActor* upgradedActor = nullptr );

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ConstructHologram( FNetConstructionID netConstructionID, FConstructHologramMessage message );

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_AnswerCall( TSubclassOf< class UFGAudioMessage > messageClass );
protected:

	/** Returns the cast outer as a FGPlayerControlelr */
	class AFGPlayerController* GetOuterFGPlayerController();
};
