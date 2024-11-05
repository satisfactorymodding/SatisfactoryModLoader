// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGAvailabilityDependency.generated.h"

/**
 * A base class for a generic dependency system, enabling the creation of dependencies on the availability of certain game objects. 
 * For instance, a schematic might depend on the purchase of another schematic, or a research tree might depend on picking up a specific item class.
 *
 * Initially designed for scalable dependencies in schematics and research trees, this class has evolved to include specialized versions for narrative triggers.
 *
 * While some dependencies only work on the server, others function on both the server and client. An example is UFGSchematicPurchasedDependency, which works on both.
 * Most dependencies are primarily used on the server, but some also function on the client, with no restrictions on client-side checks.
 *
 * This is an area where the system could be improved by adding checks to prevent inappropriate dependency calls.
 *
 * This class might have grown a bit beyond its initial scope by also becoming a trigger class. However, considering the significant
 * overlaps in functionality, it was logical to broaden its role.
 *
 * Note: Base implementations of availability dependencies default to 'true' to avoid mandatory overrides. Opt-in is required for failure conditions.
 * ToString and FromString methods are used by the narrative trigger tool and message importer for converting dependencies to and from strings for spreadsheet integration.
 */
UCLASS( DefaultToInstanced, abstract, editinlinenew, Meta = ( AutoJSON = true ) )
class FACTORYGAME_API UFGAvailabilityDependency : public UObject
{
	GENERATED_BODY()

public:
	// Global dependencies that can be checked anywhere bust mostly relevant for server
	UFUNCTION( BlueprintPure )
	virtual bool AreDependenciesMet( UObject* worldContext ) const;
	// Player specific dependencies that can be checked anywhere bust mostly relevant for server
	virtual bool ArePlayerSpecificDependenciesMet( const class AFGPlayerState* playerState ) const;
	// Check local dependencies that can only be checked for the locally controlled player
	virtual bool AreLocalDependenciesMet( UObject* worldContext ) const;

#if WITH_EDITOR
	/** This should return the dependency parsed to a string"   */
	virtual FString ToString() const {return "Unsupported Dependency"; }
	// Populates this dependency with the given string
	virtual void FromString( const FString& inString ) {}
#endif
};
