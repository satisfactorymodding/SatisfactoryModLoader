#include "Input/FGChildInputMappingContext.h"

FPrimaryAssetId UFGChildInputMappingContext::GetPrimaryAssetId() const
{
    // MODDING EDIT Implementation to address "does not match object's real id" error
    // https://discord.com/channels/555424930502541343/562722670974599227/1509925640747356301

    // Avoid returning a valid primary asset ID for this class CDO itself
    if (HasAnyFlags(RF_ClassDefaultObject) && GetClass() == StaticClass())
    {
        return FPrimaryAssetId();
    }
    return FPrimaryAssetId(StaticClass()->GetFName(), GetFName());
}