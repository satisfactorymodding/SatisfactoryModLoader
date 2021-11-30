// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGSignInterface.h"
#include "FGBuildableSignBase.generated.h"


UENUM()
enum class ESignAttachmentPointSnapType : uint8
{
	ESAPST_Center	UMETA( DisplayName = "Center" ), 
	ESAPST_Top		UMETA( DisplayName = "Top" ),
	ESAPST_Bottom	UMETA( DisplayName = "Bottom" )
};

UCLASS()
class FACTORYGAME_API UFGSignAttachmentPoint : public UFGAttachmentPointType
{
	GENERATED_BODY()
public:
	// Begin UFGAttachmentPointType interface
	virtual bool CanAttach( const struct FFGAttachmentPoint& point, const struct FFGAttachmentPoint& targetPoint ) const override;
	// End UFGAttachmentPointType interface

	// What the sign should snap with when snapping to this attachment point
	UPROPERTY( EditDefaultsOnly, Category = "Snapping" )
	ESignAttachmentPointSnapType mSignSnapType;

	// Max size allowed for signs when snapping to this attachment point
	UPROPERTY( EditDefaultsOnly, Category = "Snapping" )
	FVector2D mMaxSignSize;
};

/**
 * Base Sign Class. Holds properties that all signs should utilize
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableSignBase : public AFGBuildable, public IFGSignInterface
{
	GENERATED_BODY()

public:
	AFGBuildableSignBase();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin Sign Interface Implementation
	virtual AFGBuildable* GetBuildable_Implementation() override;
	virtual TSubclassOf< UFGSignTypeDescriptor > GetSignTypeDescriptor_Implementation() override;
	virtual FVector2D GetSignDimensions_Implementation() override;
	virtual FVector2D GetWorldDimensions_Implementation() override;
	virtual FVector2D GetGridSquareDimensions_Implementation() override;
	// End Sign Interface Implementation

	// begin IFGDismantleInterface
	virtual void GetChildDismantleActors_Implementation( TArray<AActor*>& out_ChildDismantleActors ) const override;
	// end IFGDismantleInterface

	/** Returns the value for the local offset to apply when this sign is placed on a sign pole */
	FORCEINLINE FVector GetPoleOffset() { return mPoleOffset; }

	/** Returns the 2d Scale (x/y) for signs attached to this sign when constructed */
	FORCEINLINE FVector2D GetPoleScale() { return mPoleScale; }

	/** Get Sign To Sign offset for hologram placement */
	FORCEINLINE float GetSignToSignOffset() { return mSignToSignOffset; }

protected:
	friend class AFGStandaloneSignHologram;

	/** The supports that "belong" to this sign. Will be dismantled when the sign is dismantled. */
	UPROPERTY( SaveGame )
	TArray< class AFGBuildableSignSupport* > mSignPoles;

	UPROPERTY( VisibleAnywhere, Category = "SignBase" )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy;

	/** Sign Dimensions in World Space. Used by holograms to align snapping with other signs */
	UPROPERTY( EditDefaultsOnly, Category = "SignBase" )
	FVector2D mWorldDimensions;

	/** Local Offset from the pole to place this sign on a sign pole. This does not need, nor should not, take into account the sign dimensions */
	UPROPERTY( EditDefaultsOnly, Category = "SignBase" )
	FVector mPoleOffset;

	// 2D x/y optional scaling to apply to the child sign poles of this sign
	UPROPERTY( EditDefaultsOnly, Category = "SignBase" )
	FVector2D mPoleScale;

	// Optional value for aligning holograms on the Y axis for variable sizes
	UPROPERTY( EditDefaultsOnly, Category = "SignBase" )
	float mSignToSignOffset;
};
