#pragma once
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Interfaces/Interface_PostProcessVolume.h"
#include "GameFramework/Volume.h"
#include "FGDamageOverTimeVolume.generated.h"

UCLASS( hidecategories=(Mobile,Physics,Cooking,Collision) )
class AFGDamageOverTimeVolume : public AVolume, public IInterface_PostProcessVolume
{
	GENERATED_BODY()
public:
	/** ctor */
	AFGDamageOverTimeVolume();

	//~ Begin IInterface_PostProcessVolume Interface
	virtual bool EncompassesPoint( FVector point, float sphereRadius = 0.f, float* out_distanceToPoint = nullptr ) override;
	virtual FPostProcessVolumeProperties GetProperties() const override;
	//~ End IInterface_PostProcessVolume Interface

	//~ Begin AActor Interface
	virtual void PostUnregisterAllComponents( void ) override;
	virtual void PostRegisterAllComponents() override;
	//~ End AActor Interface

#if WITH_EDITOR
	// Begin AActor interface
	virtual void CheckForErrors() override;
	// End AActor interface
#endif
protected:
	/** Some damage over time volumes will want a post process effect attached to it*/
	UPROPERTY( EditInstanceOnly, Category = "PostProcess" )
	TSubclassOf<class UFGSharedPostProcessSettings> mPostProcessSettings;

	/** The component that will do the damage to actors */
	UPROPERTY( VisibleInstanceOnly, Category="Damage")
	class UFGDotComponent* mDotComponent;
};
