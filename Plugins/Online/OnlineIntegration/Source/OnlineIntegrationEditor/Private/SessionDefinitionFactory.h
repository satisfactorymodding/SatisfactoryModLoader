// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AssetTypeActions_Base.h"
#include "CoreMinimal.h"
#include "Factories/Factory.h"

#include "SessionDefinitionFactory.generated.h"

class USessionDefinition;
class FAssetTypeActions_SessionDefinition: public FAssetTypeActions_Base
{
public:
	// Begin IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	// End IAssetTypeActions interface
};
/**
 * 
 */
UCLASS()
class USessionDefinitionFactory : public UFactory
{
	GENERATED_BODY()
public:
	USessionDefinitionFactory();

protected:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
