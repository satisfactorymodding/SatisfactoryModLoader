// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "FGWarningIndicatorRepresentation.generated.h"

/** A generic class for representations that can occasionally show a flashing warning icon */
UCLASS()
class FACTORYGAME_API UFGWarningIndicatorRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
public:
	UFGWarningIndicatorRepresentation();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void UpdateActorRepresentation() override;
	virtual void UpdateRepresentationCompassMaterial(UMaterialInstanceDynamic* compassMaterialInstance, APlayerController* ownerPlayerController) const override;

	/** Returns true if the warning indicator is currently visible */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE bool IsWarningIndicatorVisible() const { return mIsWarningVisible; }

	/** Returns the color of the warning indicator */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE FLinearColor GetWarningIndicatorColor() const { return mWarningIndicatorColor; }
protected:
	virtual bool IsWarningIndicatorVisible( AActor* realActor, FLinearColor& out_warningIndicatorColor ) const PURE_VIRTUAL( IsWarningIndicatorVisible, return false; );
	
	/** True if the warning indicator is currently shown */
	UPROPERTY( Replicated )
	bool mIsWarningVisible;

	/** Color of the warning indicator */
	UPROPERTY( Replicated )
	FLinearColor mWarningIndicatorColor;
};
