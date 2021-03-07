#pragma once
#include "UObject/Object.h"
#include "Toolkit/AssetTypes/AssetCategory.h"
#include "Dom/JsonObject.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "AssetTypeSerializer.generated.h"

/** Additional parameters passed to SerializeAsset */
class SML_API FAssetSerializationContext {
public:
    virtual ~FAssetSerializationContext() = default;

    /** Retrieves path to additional file created by this asset */
    virtual FString GetAdditionalFilePath(const FString& FilenamePostfix, const FString& FileExtension) = 0;
    
    /**
    * Adds additional file to be saved alongside asset json dump
    * Filename will be the same as for asset dump json, but with different extension,
    * as specified by Extension argument
    * Mostly intended for saving binary files, like images, models and raw data blobs
    */
    FORCEINLINE bool SaveAdditionalAssetFile(const FString& FileExtension, const TArray64<uint8>& Data, const FString& FilenamePostfix = TEXT("")) {
        const FString OutFileName = GetAdditionalFilePath(FilenamePostfix, FileExtension);
        return FFileHelper::SaveArrayToFile(Data, *OutFileName);
    }
};

UCLASS(Abstract)
class SML_API UAssetTypeSerializer : public UObject {
    GENERATED_BODY()
public:
    /**
     * Performs asset serialization and writes result into the out json object
     * Object hierarchy serializer is already populated with fresh copy of property serializer and source asset package
     * Serialized object hierarchy will be automatically appended into output json object after function return
     * Type of asset package is automatically written into the output object type, additionally to package path
     */
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const PURE_VIRTUAL(UAssetTypeSerializer::SerializeAsset,);
    
    /**
     * Returns asset category that this handler is handling
     * Note that this method will be called on Class Default Object
     */
    virtual EAssetCategory GetAssetCategory() const PURE_VIRTUAL(UAssetTypeSerializer::GetAssetCategory, return EAssetCategory::EAC_Unknown; );

    /**
     * Returns serializer capable of serializing asset of specified category,
     * or NULL if such serializer cannot be resolved.
     * Uses reflection internally to find matching serializer
     */
    static UAssetTypeSerializer* FindSerializerForAssetCategory(EAssetCategory AssetCategory);
};
