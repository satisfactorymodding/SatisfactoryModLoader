// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildableFactoryBuilding.h"
#include "FGBuildableWall.generated.h"

UENUM()
enum class EBuildableWallType : uint8
{
	BWT_Normal			UMETA( DisplayName = "Normal" ),
	BWT_Glass			UMETA( DisplayName = "Glass" ),
	BWT_DiagonalUp		UMETA( DisplayName = "Diagonal Up" ),
	BWT_DiagonalDown	UMETA( DisplayName = "Diagonal Down" ),
	BWT_Frame			UMETA( DisplayName = "Frame" )
};

/**
 * A wall that can be build on foundations, floors and other walls.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableWall : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableWall();

	void CalculateLocalSnapOffset( FVector& out_upVector, float& out_length ) const;

public:
	/** Width of the wall */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mWidth;

	/** Height of the wall */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mHeight;

	/** Elevation of the wall */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mElevation;

	/** How far forward the wall reaches, in case of angular walls. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mAngularDepth;

	/** What type of wall this is. Used for allowing / disallowing different types of walls to be built on top of eachother. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	EBuildableWallType mWallType;

	/** List of angled variants of this wall. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	TArray< TSubclassOf< class AFGBuildableWall > > mAngledVariants;
};
