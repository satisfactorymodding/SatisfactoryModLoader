// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignInterface.h"
#include "FGSignificanceInterface.h"
#include "Buildables/FGBuildable.h"
#include "FGSignTypes.h"
#include "Buildables/FGBuildableSignBase.h"
#include "FGBuildableWidgetSign.generated.h"



/**
 * Class for the creating of placeable signs. Implements the sign interface for adding and removing element via a widget class
 */

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableWidgetSign : public AFGBuildableSignBase, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:
	AFGBuildableWidgetSign();

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
	virtual TSubclassOf< UFGSignTypeDescriptor > GetSignTypeDescriptor_Implementation() override;
	virtual FVector2D GetSignDimensions_Implementation() override;
	// End Sign Interface Implementation

	// Begin Significance Interface Implementation
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End  Significance Interface Implementation


	// When a text element is updated, this call will update that element and set the save data
	UFUNCTION( BlueprintCallable, Category = "WidgetSign" )
	void SetPrefabSignData( UPARAM( ref ) FPrefabSignData& signData );

	// When a text element is updated, this call will update that element and set the save data
	UFUNCTION( BlueprintPure, Category = "WidgetSign" )
	void GetSignPrefabData( FPrefabSignData& out_signData );

	/** Updates all sign elements with currently set sign data */
	void UpdateSignElements( FPrefabSignData& prefabSignData );

protected:

	/** Update sign prefab on replication */
	UFUNCTION()
	void OnRep_SignDataDirty();

protected:
	friend class UFGSignBuildingWidget;

	/** Root UMG component */
	UPROPERTY( VisibleAnywhere, Category = "WidgetSign" )
	class UWidgetComponent* mWidgetComponent;

	/** Sign Descriptor. This is a class that holds information that can be shared across different signs of similar aspect ratios */
	UPROPERTY( EditDefaultsOnly, Category = "WidgetSign" )
	TSubclassOf< UFGSignTypeDescriptor > mSignTypeDescriptor;

	/** Reference to the current prefab template */
	UPROPERTY()
	class UFGSignPrefabWidget* mPrefabLayout;

	/** Distance at which to gain significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mGainSignificanceDistance;

	/** Map of text element name to the string data stored */
	UPROPERTY()
	TMap< FString, FString > mTextElementToDataMap;

	/** Map of icon element name to the icon data index */
	UPROPERTY()
	TMap< FString, int32 > mIconElementToDataMap;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mWidgetMaterial;

	//////////////////////////////////////////////////////////////////////////
	/// Saved Properties

	/** Currently Active Sign Prefab Class */
	UPROPERTY( SaveGame )
	TSubclassOf< UFGSignPrefabWidget > mActivePrefabLayout;

	UPROPERTY( SaveGame )
	TArray< FPrefabTextElementSaveData > mPrefabTextElementSaveData;

	UPROPERTY( SaveGame )
	TArray< FPrefabIconElementSaveData > mPrefabIconElementSaveData;

	UPROPERTY( SaveGame )
	FLinearColor mForegroundColor;

	UPROPERTY( SaveGame )
	FLinearColor mBackgroundColor;

	UPROPERTY( SaveGame )
	FLinearColor mAuxilaryColor;

	UPROPERTY( SaveGame )
	float mEmissive;

	UPROPERTY( SaveGame )
	float mGlossiness;

	// When a signs data is changed, the server will increment this. When the onRep fires the client will add this sign to the PendingSigns array in the sign subsystem
	UPROPERTY( ReplicatedUsing=OnRep_SignDataDirty )
	uint8 mDataVersion;

};
