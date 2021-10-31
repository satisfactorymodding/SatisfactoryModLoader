// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGAttachmentPoint.generated.h"

/** Type class for attachment points, used to allow / disallow snapping. */
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGAttachmentPointType : public UObject
{
	GENERATED_BODY()
public:
	virtual bool CanAttach( const struct FFGAttachmentPoint& point, const struct FFGAttachmentPoint& targetPoint ) const;

	/** What attachment point types this type can snap to. */
	UPROPERTY( EditDefaultsOnly, Category = "Attachment Point")
	TArray< TSubclassOf< UFGAttachmentPointType > > mAllowedAttachmentPointSnapTypes;
};

/**
 * Basic attachment point struct. Used for snapping actors together.
 */
USTRUCT()
struct FACTORYGAME_API FFGAttachmentPoint
{
	GENERATED_BODY()

	FFGAttachmentPoint();
	virtual ~FFGAttachmentPoint() {}
	
	bool CanAttachTo( const FFGAttachmentPoint* otherPoint ) const;

	/** Relative transform of the attachment point. */
	UPROPERTY()
	FTransform RelativeTransform;

	/** Type of the attachment point. */
	UPROPERTY()
	TSubclassOf< UFGAttachmentPointType > Type;

	/** The actor this attachment point belongs to. */
	UPROPERTY()
	AActor* Owner;
};