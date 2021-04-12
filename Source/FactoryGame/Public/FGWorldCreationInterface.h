// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGWorldCreationInterface.generated.h"

/**
* Necessary glue code to get interface into the UObject hierarchy, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class UFGWorldCreationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
* @brief Interface for all useable classes out there
*/
class IFGWorldCreationInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	/**
	 * Basic world creation...
	 */
	virtual class UWorld* CreateWorld( const FString& worldName ) = 0;

	/**
	 * Destroy a world created with CreateWorld
	 */
	virtual void DestroyWorld( class UWorld* world ) = 0;
};
