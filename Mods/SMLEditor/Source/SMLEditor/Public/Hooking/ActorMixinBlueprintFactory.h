#pragma once

#include "CoreMinimal.h"
#include "Factories/BlueprintFactory.h"
#include "ActorMixinBlueprintFactory.generated.h"

UCLASS(HideCategories = Object, CollapseCategories)
class SMLEDITOR_API UActorMixinBlueprintFactory : public UBlueprintFactory {
	GENERATED_BODY()
public:
	explicit UActorMixinBlueprintFactory(const FObjectInitializer& ObjectInitializer);

	// UFactory interface
	virtual bool ConfigureProperties() override;
	virtual FText GetDisplayName() const override;
	virtual FName GetNewAssetThumbnailOverride() const override;
	virtual uint32 GetMenuCategories() const override;
	virtual FText GetToolTip() const override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual FString GetDefaultNewAssetName() const override;
	// End of UFactory interface

	UPROPERTY()
	TObjectPtr<UBlueprintGeneratedClass> MixinTargetClass{};
};
