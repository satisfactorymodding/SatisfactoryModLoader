#include "Input/FGChildInputMappingContext.h"

FPrimaryAssetId UFGChildInputMappingContext::GetPrimaryAssetId() const
{
    // Avoid returning a valid primary asset ID for this class CDO itself
    if (HasAnyFlags(RF_ClassDefaultObject) && GetClass() == StaticClass())
    {
        return FPrimaryAssetId();
    }
    return FPrimaryAssetId(StaticClass()->GetFName(), GetFName());
}