// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGSchematic.h"
#include "FGSchematicTypeDependency.generated.h"

/**
 * Responsible for handling dependencies related to Schematic Types.
 * This class covers two specific cases:
 *
 * - Case 1: If mShouldCategoryMatch is true, it triggers when one or multiple Schematics of a specific type
 *   (e.g. 'Resource Sink') are unlocked, and all of them share the same specfied schematic category or subcategory.
 *   
 * - Case 2: If mShouldCategoryMatch is false, it triggers when multiple Schematics of a specific type
 *   (e.g. 'Resource Sink') are unlocked at the same time, but only if they belong to different categories or subcategories.
 *
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSchematicTypeDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	ESchematicType GetSchematicType() const { return mSchematicType; }
	bool GetShouldCategoryMatch() const { return mShouldCategoryMatch; }
	bool DoesSchematicsMatchDependency( const TArray<TSubclassOf<UFGSchematic>>& schematics );

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif


protected:
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	ESchematicType mSchematicType;

	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mShouldCategoryMatch;
	
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mShouldSubCategoriesMatch;

	UPROPERTY( EditDefaultsOnly, Category="Dependency", meta=( editcondition = "mShouldCategoryMatch" ) )
	TSubclassOf< class UFGSchematicCategory > mSchematicCategory;

	UPROPERTY( EditDefaultsOnly, Category="Dependency", meta=( editcondition = "mShouldSubCategoriesMatch" ) )
	TArray< TSubclassOf< class UFGSchematicCategory > > mSchematicSubcategories;
};
