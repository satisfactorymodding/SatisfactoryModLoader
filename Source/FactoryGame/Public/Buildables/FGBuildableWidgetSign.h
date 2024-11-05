// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGBuildableSignBase.h"
#include "FGSignInterface.h"
#include "FGSignTypes.h"
#include "FGSignificanceInterface.h"
#include "FGBuildableWidgetSign.generated.h"

class UTextureRenderTarget2D;

UCLASS()
class FACTORYGAME_API UFGSignClipboardSettings : public UFGFactoryClipboardSettings
{
	GENERATED_BODY()
public:
	
	UPROPERTY( BlueprintReadWrite )
	FPrefabSignData mPrefabSignData;
};

/** Helper to convert legacy save data into the new format without having to load the widget class object */
USTRUCT()
struct FACTORYGAME_API FFGSignPrefabLayoutWidgetConversionHelper
{
	GENERATED_BODY()

	/** Converted prefab layout widget. */
	UPROPERTY( SaveGame )
	TSoftClassPtr<UFGSignPrefabWidget> PrefabLayoutWidget;

	bool SerializeFromMismatchedTag(const FPropertyTag& PropertyTag, FArchive& Ar);
};

template<>
struct TStructOpsTypeTraits<FFGSignPrefabLayoutWidgetConversionHelper> : TStructOpsTypeTraitsBase2<FFGSignPrefabLayoutWidgetConversionHelper>
{
	enum 
	{
		WithSerializeFromMismatchedTag = true
	};
};

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
	virtual float GetSignificanceRange() override { return mGainSignificanceDistance; }
	// End  Significance Interface Implementation

	//~ Begin IFGFactoryClipboardInterface
	bool CanUseFactoryClipboard_Implementation() override { return true; }
	UFGFactoryClipboardSettings* CopySettings_Implementation() override;
	bool PasteSettings_Implementation( UFGFactoryClipboardSettings* settings ) override;
	//~ End IFGFactoryClipboardInterface

	virtual void OnBuildEffectFinished() override;
	virtual void OnBuildEffectActorFinished() override;
	
	// When a text element is updated, this call will update that element and set the save data
	UFUNCTION( BlueprintCallable, Category = "WidgetSign" )
	void SetPrefabSignData( UPARAM( ref ) FPrefabSignData& signData );

	// When a text element is updated, this call will update that element and set the save data
	UFUNCTION( BlueprintPure, Category = "WidgetSign" )
	void GetSignPrefabData( FPrefabSignData& out_signData ) const;

	/** Updates all sign elements with currently set sign data */
	void UpdateSignElements( FPrefabSignData& prefabSignData );

	virtual float GetAdjustedEmissiveValue(int32 Level) const;

protected:

	/** Update sign prefab on replication */
	UFUNCTION()
	void OnRep_SignDataDirty();

	/* Generate GUID based on settings*/
	static uint32 GenerateGUID(FPrefabSignData& signData, UClass* Prefab, FVector2D Size);

	virtual void ConvertToEmissiveOnly(FPrefabSignData& prefabSignData) const;

	virtual void SetupMaterialInstanceForProxyPlane(UMaterialInstanceDynamic* Instance, UTextureRenderTarget2D* RenderTarget);

	static bool IsEmissiveOnly( FPrefabSignData& prefabSignData, const TSubclassOf<UFGSignPrefabWidget>& activePrefabLayout );
	bool ShouldPrefabSignTick( FPrefabSignData& prefabSignData ) const;
	UMaterialInterface* GetBackground( FPrefabSignData& prefabSignData ) const;

	void WaitForClientSubsystemsToInitializeSignPrefabData();
	void InitializeSignPrefabData();

	virtual void PreSerializedToBlueprint() override;
	virtual void PostSerializedToBlueprint() override;
	virtual void PostSerializedFromBlueprint(bool isBlueprintWorld) override;
protected:
	friend class UFGSignBuildingWidget;
	friend class AFGSignSubsystem;


	///** Root UMG component */
	//UPROPERTY( VisibleAnywhere, Category = "WidgetSign" )
	//class UWidgetComponent* mWidgetComponent;
	
	UPROPERTY( VisibleAnywhere, Category = "WidgetSign", meta = (AllowPrivateAccess = "true") )
	TObjectPtr<UStaticMeshComponent> mSignProxyPlane;

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

	/** Map of text element name to the string data stored */
	UPROPERTY()
	TMap< FString, FText > mTextElementToLocDataMap;

	/** Map of icon element name to the icon data index */
	UPROPERTY()
	TMap< FString, int32 > mIconElementToDataMap;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mWidgetMaterial;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mEmissiveOnlySignMaterial;
	
	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mDefaultSignMaterial;

	UPROPERTY(EditDefaultsOnly)
	FIntPoint mSignDrawSize;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mWidgetClass;
	
	//////////////////////////////////////////////////////////////////////////
	/// Saved Properties

	/** A path to the currently active sign prefab widget class. Stored as a soft pointer to avoid having to load it on the dedicated server. */
	UPROPERTY( SaveGame )
	TSoftClassPtr<UFGSignPrefabWidget> mSoftActivePrefabLayout;

	/** Helper for reading legacy save data for signs */
	UPROPERTY( SaveGame )
	FFGSignPrefabLayoutWidgetConversionHelper mActivePrefabLayout_DEPRECATED;

	UPROPERTY( SaveGame )
	TArray<FPrefabTextElementSaveData> mPrefabTextElementSaveData;

	UPROPERTY( SaveGame )
	TArray<FPrefabIconElementSaveData> mPrefabIconElementSaveData;

	/** Used instead of mPrefabIconElementSaveData to save Icon ID globally for blueprints */
	UPROPERTY( SaveGame )
	TArray<FGlobalPrefabIconElementSaveData> mGlobalPrefabIconElementSaveData;

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
	
	uint32 mCachedGUID = 0;
};
