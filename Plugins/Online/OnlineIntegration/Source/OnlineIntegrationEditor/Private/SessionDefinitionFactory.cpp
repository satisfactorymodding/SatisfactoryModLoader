#include "SessionDefinitionFactory.h"

FText FAssetTypeActions_SessionDefinition::GetName() const{ return FText(); }
FColor FAssetTypeActions_SessionDefinition::GetTypeColor() const{ return FColor(); }
UClass* FAssetTypeActions_SessionDefinition::GetSupportedClass() const{ return nullptr; }
uint32 FAssetTypeActions_SessionDefinition::GetCategories(){ return 0; }
USessionDefinitionFactory::USessionDefinitionFactory(){ }
UObject* USessionDefinitionFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn){ return nullptr; }