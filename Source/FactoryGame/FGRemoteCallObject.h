// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "UObject/NoExportTypes.h"
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
	int32 GetFunctionCallspace( UFunction* Function, void* Parameters, FFrame* Stack ) override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the NetDriver of the outer PlayerController.*/
	bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;

	/** Helper function to get the game state. Can't be done in BluePrint since the GetGameState function hides it world context pin */
	UFUNCTION( BlueprintPure, Category = "Game State" )
	class AFGGameState* GetGameState();
protected:

	/** Returns the cast outer as a FGPlayerControlelr */
	class AFGPlayerController* GetOuterFGPlayerController();
};
