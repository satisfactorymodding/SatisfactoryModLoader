// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "../FGSignInterface.h"
#include "../FGSignificanceInterface.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableStandaloneSign.generated.h"

/**
 * Class for the creating of placeable signs. Implements the sign interface for adding and removing element via a widget class
 */

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableStandaloneSign : public AFGBuildable, public IFGSignInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:
	AFGBuildableStandaloneSign();

	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin Actor Interface 
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	// End Actor Interface

	// Begin Save Interface Implementation
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface Implementation

	// Begin BUildable Interface Implementation
	virtual void OnConstruction( const FTransform& transform ) override;
	// End Buildable Interface Implementation

	// Begin Sign Interface Implementation
	virtual AFGBuildable* GetBuildable_Implementation() override;
	virtual void SetSignData_Implementation( const FSignData& data, bool bUpdate = true ) override;
	virtual FSignData GetSignData_Implementation() override;
	virtual int32 GetAvailableElementID_Implementation() override;
	virtual FVector2D GetSignDimensions_Implementation() override;
	virtual FVector2D GetGridSquareDimensions_Implementation() override;
	// End Sign Interface Implementation

	// Begin Significance Interface Implementation
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End  Significance Interface Implementation

	/** Updates all sign elements with currently set sign data */
	void UpdateSignElements();

	/** Updates background material on static mesh instance */
	void UpdateBackgroundMaterial();

	/** Force an update on the text render component */
	void UpdateSignText();

	// Begin Widget Getter Functions
	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	FORCEINLINE FSignElementConstraints GetSignConstraints() const { return mSignConstraints; }

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	float GetCurrentNormalizedTextScale( );

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	float GetCurrentNormalizedTextOffsetZ();

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	float GetTextScaleFromNormalizedValue( float value );
	

protected:
	/** Update sign components on replication */
	UFUNCTION()
	void OnRep_SignData();


protected:
	/** Map of Element Ids to their associated component */
	UPROPERTY()
	TMap<int32, USceneComponent*> mDataToComponentMap;

	/** Root Component that holds all the sign elements, text, mesh etc. */
	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	USceneComponent* mSignDisplayRoot;

	/** Root component that parents the text objects */
	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	USceneComponent* mTextDisplayRoot;

	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy;

	/** Bounding box used to cull text mesh. Is assign to the BoundedTextRenderComponents */
	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	UBoxComponent* mBoundingBox;

	/** The size of each grid square on the this sign*/
	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	FVector2D mGridSquareDimensions;

	/** Particle system visual */
	UPROPERTY( VisibleAnywhere,  Category = "StandaloneSign" )
	class UParticleSystemComponent* mHologramParticleComponent;

	/** Distance at which to gain significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mGainSignificanceDistance;

	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	FSignElementConstraints mSignConstraints;

	UPROPERTY( EditDefaultsOnly, Category="StandaloneSign" )
	UFont* mSignFont; 

	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	int32 mBackgroundGridSize;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_SignData )
	FSignData mSignData;


public:
	FORCEINLINE ~AFGBuildableStandaloneSign() = default;
};
