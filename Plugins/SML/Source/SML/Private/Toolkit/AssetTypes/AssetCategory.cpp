#include "Toolkit/AssetTypes/AssetCategory.h"
#include "FGMapAreaTexture.h"
#include "UObject/Object.h"
#include "UObject/Package.h"
#include "UObject/UObjectHash.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/BlendSpace1D.h"
#include "Animation/Skeleton.h"
#include "BehaviorTree/BlackboardData.h"
#include "Camera/CameraAnim.h"
#include "Engine/DataTable.h"
#include "Engine/FontFace.h"
#include "Engine/Texture2D.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Engine/MapBuildDataRegistry.h"
#include "Internationalization/StringTable.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Curves/CurveBase.h"
#include "Curves/CurveLinearColorAtlas.h"
#include "Engine/Font.h"
#include "Engine/StaticMesh.h"
#include "Engine/SubsurfaceProfile.h"
#include "Engine/TextureCube.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialParameterCollection.h"
#include "Particles/ParticleSystem.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicsEngine/PhysicsAsset.h"

EAssetCategory FAssetCategoryHelper::DeterminePackageCategory(UPackage* Package) {
    //Obtain all objects listed inside of the package first
    TArray<UObject*> ContainedObjects;
    ForEachObjectWithOuter(Package, [&ContainedObjects](UObject* Object){
        ContainedObjects.Add(Object);
    });

    //Try to determine type of asset by checking object types
    for (UObject* Object : ContainedObjects) {
	    UClass* ObjectType = Object->GetClass();
    	const FString ObjectPathName = ObjectType->GetPathName();

    	//Widget needs to be first, otherwise it will be categorized as blueprint
    	if (ObjectType == UWidgetBlueprintGeneratedClass::StaticClass()) {
    		return EAssetCategory::EAC_UserWidget;
    	}
    	if (ObjectType == UAnimBlueprintGeneratedClass::StaticClass()) {
    		return EAssetCategory::EAC_AnimationBlueprint;
    	}
    	if (ObjectType == UBlueprintGeneratedClass::StaticClass()) {
    		return EAssetCategory::EAC_Blueprint;
    	}
    	if (ObjectType == UUserDefinedStruct::StaticClass()) {
    		return EAssetCategory::EAC_UserDefinedStruct;
    	}
    	if (ObjectType == UUserDefinedEnum::StaticClass()) {
    		return EAssetCategory::EAC_UserDefinedEnum;
    	}
    	
    	if (ObjectType == UTexture2D::StaticClass()) {
    		return EAssetCategory::EAC_Texture2D;
    	}
    	if (ObjectType == UCurveLinearColorAtlas::StaticClass()) {
    		return EAssetCategory::EAC_CurveLinearColorAtlas;
    	}
    	if (ObjectType == UTextureCube::StaticClass()) {
    		return EAssetCategory::EAC_TextureCube;
    	}
    	if (ObjectType == UTextureRenderTarget2D::StaticClass()) {
    		return EAssetCategory::EAC_TextureRenderTarget2D;
    	}
    	if (ObjectType == UFGMapAreaTexture::StaticClass()) {
    		return EAssetCategory::EAC_FGMapAreaTexture;
    	}
    	
    	if (ObjectType == UMaterial::StaticClass()) {
    		return EAssetCategory::EAC_Material;
    	}
    	if (ObjectType == UMaterialInstanceConstant::StaticClass()) {
    		return EAssetCategory::EAC_MaterialInstance;
    	}
    	if (ObjectType == UMaterialParameterCollection::StaticClass()) {
    		return EAssetCategory::EAC_MaterialParameterCollection;
    	}
    	if (ObjectType == UMaterialFunction::StaticClass()) {
    		return EAssetCategory::EAC_MaterialFunction;
    	}
    	if (ObjectType == USubsurfaceProfile::StaticClass()) {
    		return EAssetCategory::EAC_SubsurfaceProfile;
    	}

    	if (ObjectType == UParticleSystem::StaticClass()) {
    		return EAssetCategory::EAC_ParticleSystem;
    	}

    	if (ObjectType == USkeleton::StaticClass()) {
    		return EAssetCategory::EAC_Skeleton;
    	}
    	if (ObjectType == UStaticMesh::StaticClass()) {
    		return EAssetCategory::EAC_StaticMesh;
    	}
    	if (ObjectType == USkeletalMesh::StaticClass()) {
    		return EAssetCategory::EAC_SkeletalMesh;
    	}
    	
    	//TODO these assets contain extra data important for playing destruction effects
    	//TODO this is used for example by nobelisks exploding boulders
    	//TODO but currently this is not really important to serialize it
    	if (ObjectType->GetPathName() == TEXT("/Script/ApexDestruction.DestructibleMesh")) {
    		return EAssetCategory::EAC_SkeletalMesh;
    	}

    	if (ObjectType == UAnimSequence::StaticClass()) {
    		return EAssetCategory::EAC_AnimSequence;
    	}
    	if (ObjectType == UAnimMontage::StaticClass()) {
    		return EAssetCategory::EAC_AnimMontage;
    	}
    	if (ObjectPathName == TEXT("/Script/LevelSequence.LevelSequence")) {
    		return EAssetCategory::EAC_LevelSequence;
    	}
    	
    	if (ObjectType == UCameraAnim::StaticClass()) {
    		return EAssetCategory::EAC_CameraAnim;
    	} 
    	if (ObjectType->IsChildOf<UBlendSpaceBase>()) {
    		return EAssetCategory::EAC_BlendSpaceBase;
    	}

    	if (ObjectType == UPhysicalMaterial::StaticClass()) {
    		return EAssetCategory::EAC_PhysicalMaterial;
    	}
    	if (ObjectType == UPhysicsAsset::StaticClass()) {
    		return EAssetCategory::EAC_PhysicsAsset;
    	}
    	if (ObjectPathName == TEXT("/Script/PhysXVehicles.TireConfig")) {
    		return EAssetCategory::EAC_TireConfig;
    	}

    	if (ObjectPathName == TEXT("/Script/AkAudio.AkAudioEvent")) {
    		return EAssetCategory::EAC_AkAudioEvent;
    	}
    	if (ObjectPathName == TEXT("/Script/AkAudio.AkAudioBank")) {
    		return EAssetCategory::EAC_AkAudioBank;	
    	}

    	if (ObjectType == UStringTable::StaticClass()) {
    		return EAssetCategory::EAC_StringTable;
    	}
    	if (ObjectType == UDataTable::StaticClass()) {
    		return EAssetCategory::EAC_DataTable;
    	}

    	if (ObjectType == UFont::StaticClass()) {
    		return EAssetCategory::EAC_Font;
    	}
    	if (ObjectType == UFontFace::StaticClass()) {
    		return EAssetCategory::EAC_FontFace;
    	}
    	
    	if (ObjectType->IsChildOf<UCurveBase>()) {
    		return EAssetCategory::EAC_CurveBase;
    	}

    	if (ObjectType == UMapBuildDataRegistry::StaticClass()) {
    		return EAssetCategory::EAC_MapBuildDataRegistry;
    	}
    	if (ObjectType == UWorld::StaticClass()) {
    		return EAssetCategory::EAC_World;
    	}
    	if (ObjectPathName == TEXT("/Script/Foliage.FoliageType_InstancedStaticMesh")) {
    		return EAssetCategory::EAC_FoliageType_InstancedStaticMesh;
    	}
    	if (ObjectPathName == TEXT("/Script/Landscape.LandscapeGrassType")) {
    		return EAssetCategory::EAC_LandscapeGrassType;
    	}
    	if (ObjectPathName == TEXT("/Script/Landscape.LandscapeLayerInfoObject")) {
    		return EAssetCategory::EAC_LandscapeLayerInfo;
    	}
    	
    	if (ObjectPathName == TEXT("/Script/MediaAssets.FileMediaSource")) {
    		return EAssetCategory::EAC_FileMediaSource;
    	}
    	if (ObjectPathName == TEXT("/Script/MediaAssets.MediaTexture")) {
    		return EAssetCategory::EAC_MediaTexture;
    	}
    	if (ObjectPathName == TEXT("/Script/MediaAssets.MediaPlayer")) {
    		return EAssetCategory::EAC_MediaPlayer;
    	}
    	
    	if (ObjectType == UBlackboardData::StaticClass()) {
    		return EAssetCategory::EAC_BlackboardData;
    	}
    	if (ObjectType == UBehaviorTree::StaticClass()) {
    		return EAssetCategory::EAC_BehaviorTree;
    	}
    	if (ObjectType == UEnvQuery::StaticClass()) {
    		return EAssetCategory::EAC_EnvQuery;
    	}
    }
	
    return EAssetCategory::EAC_Unknown;
}

FString FAssetCategoryHelper::AssetCategoryToString(EAssetCategory AssetCategory) {
	UEnum* EnumClass = StaticEnum<EAssetCategory>();
	return EnumClass->GetNameByValue((int64) AssetCategory).ToString();
}
