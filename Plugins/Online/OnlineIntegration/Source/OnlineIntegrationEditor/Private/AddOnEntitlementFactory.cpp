#include "AddOnEntitlementFactory.h"

FText FAssetTypeActions_AddOnEntitlement::GetName() const{ return FText(); }
FColor FAssetTypeActions_AddOnEntitlement::GetTypeColor() const{ return FColor(); }
UClass* FAssetTypeActions_AddOnEntitlement::GetSupportedClass() const{ return nullptr; }
uint32 FAssetTypeActions_AddOnEntitlement::GetCategories(){ return 0; }
UAddOnEntitlementFactory::UAddOnEntitlementFactory(){ }
UObject* UAddOnEntitlementFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn){ return nullptr; }
