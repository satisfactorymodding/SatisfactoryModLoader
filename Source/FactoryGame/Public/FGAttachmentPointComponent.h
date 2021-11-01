// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGAttachmentPointComponent.generated.h"

UENUM()
enum class EAttachmentPointUsage : uint8
{
	EAPU_Default		UMETA( DisplayName = "Default" ),
	EAPU_BuildableOnly	UMETA( DisplayName = "Buildable Only" ),
	EAPU_HologramOnly	UMETA( DisplayName = "Hologram Only" )
};

/**
* Generic class used to set up attachment points for buildables.
*/
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGAttachmentPointComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UFGAttachmentPointComponent();

	struct FFGAttachmentPoint CreateAttachmentPoint( AActor* owner ) const;

	EAttachmentPointUsage GetAttachmentPointUsage() const { return mUsage; }

private:
	/** Whether or not we should create this hologram for the buildable, hologram, or both (Default). */
	UPROPERTY( EditDefaultsOnly, Category = "Attachment Point")
	EAttachmentPointUsage mUsage;

	/** What type of attachment point to create. */
	UPROPERTY( EditDefaultsOnly, Category = "Attachment Point")
	TSubclassOf< class UFGAttachmentPointType > mType;
};
