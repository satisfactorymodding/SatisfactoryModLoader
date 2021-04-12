// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableControlPanelHost.h"
#include "Buildables/FGBuildableLightSource.h"
#include "FGBuildableLightsControlPanel.generated.h"

/**
 * Native implementation for the lights control panel.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableLightsControlPanel : public AFGBuildableControlPanelHost
{
	GENERATED_BODY()
public:
	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End Actor Interface
	
	/** Turn the lights on or off */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "FactoryGame|Buildable|Light" )
    void SetLightEnabled( bool isEnabled );
	
	/** Set the control data for this light in one go, prefer this to multiple call to the specific parameters. */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "FactoryGame|Buildable|Light" )
    void SetLightControlData( FLightSourceControlData data );

	/** Are the lights on or off, valid on client. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    bool IsLightEnabled() const;
	
	/** Get the control data of this light, valid on client. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    FLightSourceControlData GetLightControlData() const;
	
private:
	/** The parameters for the light output. */
	UPROPERTY( SaveGame, Replicated )
	FLightSourceControlData mLightControlData;

	/** Are the lights on or off. */
	UPROPERTY( SaveGame, Replicated )
	bool mIsEnabled;
};
