// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGMapArea.generated.h"


UCLASS( Blueprintable )
class FACTORYGAME_API UFGMapArea : public UObject
{
	GENERATED_BODY()
public:
	/** Get area display name */
	UFUNCTION( BlueprintPure, Category = "MapArea" )
	static FText GetAreaDisplayName( TSubclassOf< UFGMapArea > inClass );

	/** Get area display name */
	UFUNCTION( BlueprintPure, Category = "MapArea" )
	static FText GetUserSetAreaDisplayName( TSubclassOf< UFGMapArea > inClass );

	/** Get the CDO of the zone type */
	UFUNCTION( BlueprintPure, Category = "MapArea" )
	static TSubclassOf< class UFGMapAreaZoneDescriptor > GetZoneType( TSubclassOf< UFGMapArea > inClass );

protected:
	/** This is the name we at CSS gave this area */
	UPROPERTY( EditDefaultsOnly, Category = "MapArea" )
	FText mDisplayName;

	/** What kind of zone this is */
	UPROPERTY( EditDefaultsOnly, Category = "MapArea" )
	TSubclassOf< class UFGMapAreaZoneDescriptor > mZoneType;

	/** This is the name the player has given this area */
	UPROPERTY()
	FText mUserSetDisplayName;

public:
	FORCEINLINE ~UFGMapArea() = default;
};
