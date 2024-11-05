// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryColoringTypes.h"
#include "UObject/NoExportTypes.h"
#include "Internationalization/StringTableRegistry.h"
#include "FGSwatchGroup.generated.h"

#define LOCTEXT_NAMESPACE "Swatch Groups"

/**
 * Base for subsequent SwatchGroup definitions. A swatch group is a buildable default group to allow for
 * changing the "default" swatch to use when building a buildable
 */
UCLASS( Blueprintable, Abstract)
class FACTORYGAME_API UFGSwatchGroup : public UObject
{
	GENERATED_BODY()

public:
	UFGSwatchGroup() :
		mGroupName( LOCTEXT( "UFGSwatchGroup", "This should never be seen!") )
	{
	}

	UFUNCTION( BlueprintPure, Category="SwatchGroup")
	static FText GetGroupName( TSubclassOf< UFGSwatchGroup > inClass );

protected:
	UPROPERTY( VisibleDefaultsOnly )
	FText mGroupName;
	
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSwatchGroupData
{
	GENERATED_BODY()
	
public:
	UPROPERTY( SaveGame, EditDefaultsOnly, BlueprintReadOnly, Category="SwatchGroup" )
	TSubclassOf< UFGSwatchGroup > SwatchGroup;
	
	UPROPERTY( SaveGame, EditDefaultsOnly, BlueprintReadOnly, Category="SwatchGroup" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch> Swatch;
	
};


UCLASS()
class FACTORYGAME_API UFGSwatchGroup_Standard : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_Standard()
	{
		mGroupName = LOCTABLE( "Customization_Data", "Categories/Standard" );
	}
};

UCLASS()
class FACTORYGAME_API UFGSwatchGroup_FicsitFoundation : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_FicsitFoundation()
	{
		mGroupName = LOCTABLE( "Customization_Data", "Materials/Foundations/FICSIT" );
	}
};

UCLASS()
class FACTORYGAME_API UFGSwatchGroup_ConcreteFoundation : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_ConcreteFoundation()
	{
		mGroupName = LOCTABLE( "Customization_Data", "Materials/Foundations/Concrete" );
	}
};

UCLASS()
class FACTORYGAME_API UFGSwatchGroup_CoatedConcreteFoundation : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_CoatedConcreteFoundation()
	{
		mGroupName = LOCTABLE( "Customization_Data", "Materials/Foundations/CoatedConcrete" );
	}
};

UCLASS()
class FACTORYGAME_API UFGSwatchGroup_ConcreteWall : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_ConcreteWall()
	{ 
		mGroupName = LOCTABLE( "Customization_Data", "Materials/Walls/Concrete" );
	}
};

UCLASS()
class FACTORYGAME_API UFGSwatchGroup_Pipeline : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_Pipeline()
	{
		mGroupName = LOCTABLE( "Customization_Data", "Categories/Pipes" );
	}
};

UCLASS()
class FACTORYGAME_API UFGSwatchGroup_Vehicle : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_Vehicle()
	{
		mGroupName = LOCTABLE( "Customization_Data", "Categories/Vehicles" );
	}
};

#undef LOCTEXT_NAMESPACE
