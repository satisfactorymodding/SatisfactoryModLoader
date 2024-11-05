// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "FGAttachmentPoint.generated.h"

struct FFGAttachmentPoint;
class UFGAttachmentPointType;

/**
 * Basic attachment point struct. Used for snapping actors together.
 */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FFGAttachmentPoint
{
	GENERATED_BODY()

	FFGAttachmentPoint();
	virtual ~FFGAttachmentPoint() {}
	
	bool CanAttachTo( const FFGAttachmentPoint* otherPoint ) const;

	/** Relative transform of the attachment point. */
	UPROPERTY(BlueprintReadOnly, Category = "Attachment Point")
	FTransform RelativeTransform;

	/** Type of the attachment point. */
	UPROPERTY(BlueprintReadOnly, Category = "Attachment Point")
	TSubclassOf< UFGAttachmentPointType > Type;

	/** The actor this attachment point belongs to. */
	UPROPERTY(BlueprintReadOnly, Category = "Attachment Point")
	AActor* Owner;
};

/** Type class for attachment points, used to allow / disallow snapping. */
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGAttachmentPointType : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintNativeEvent, Category = "Attachment Point" )
	bool CanAttach( const FFGAttachmentPoint& point, const FFGAttachmentPoint& targetPoint ) const;

	/** What attachment point types this type can snap to. */
	UPROPERTY( EditDefaultsOnly, Category = "Attachment Point" )
	TArray< TSubclassOf< UFGAttachmentPointType > > mAllowedAttachmentPointSnapTypes;
};
