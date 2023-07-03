#pragma once
#include "CoreMinimal.h"
#include "Resources/FGResourceDescriptor.h"
#include "Resources/FGResourceNode.h"
#include "FGResourceNodeGeyser.h"
#include "Resources/FGResourceNodeFrackingCore.h"
#include "Resources/FGResourceNodeFrackingSatellite.h"
#include "SMLResourceDetailsInterface.generated.h"

UENUM(BlueprintType)
enum class ESMLResourceExtractionType : uint8 {
    Mining UMETA(DisplayName = "Mining Node", ToolTip = "Mineable ore node, ex. Iron" ),
    Fracking UMETA(DisplayName = "Fracking Node", ToolTip = "Requires a Pressurizer, ex. Nitrogen Gas" ),
    DecalOnly UMETA(DisplayName = "Decal-Only Node", ToolTip = "No mesh, just a decal on the ground, ex. the Oil variant you must use the Oil Extractor for" ),
    Geyser UMETA(DisplayName = "Geyser Node", ToolTip = "Resources that don't actually extract into an item, ex. Geyser"),
    Custom UMETA(DisplayName = "Custom", ToolTip = "Custom implementation of a resource" )
};

/**
* The information a resource's Mining Node uses for display in the world
*/
USTRUCT(BlueprintType)
struct SML_API FSMLMiningNodeDisplay {
    GENERATED_BODY()
public:
    /** The material a Resource Node uses (if any) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInstance* NodeMaterial;

    /** The static mesh we want the Resource Node to use when it has this class selected */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMesh* NodeMesh;

    /** Actor class other mods should use to spawn nodes of this resource. Your actor should allow specifying purity and other relevant information on construct. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf< AFGResourceNode > ActorClass;

    FSMLMiningNodeDisplay();
};

/**
 * The information a resource's Fracking Node and Fracking Satellites use for display in the world
 */
USTRUCT(BlueprintType)
struct SML_API FSMLFrackingNodeDisplay {
    GENERATED_BODY()
public:
    /** The static mesh we want the Resource Node to use when it has this class selected */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMesh* CoreNodeMesh;

    /** The static mesh we want the Resource Node to use when it has this class selected */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMesh* SatelliteNodeMesh;

    /** Returns the material this Resource Node uses (if any) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInstance* CoreNodeMaterial;

    /** Returns the material this Resource Node uses (if any) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInstance* SatelliteNodeMaterial;

    /** Actor class other mods should use to spawn nodes of this resource. Your actor should allow specifying purity and other relevant information on construct. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf< AActor > ActorClass;

    /** Actor class used for the core node */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf< AFGResourceNodeFrackingCore > CoreActorClass;

    /** Actor class used for the satellite nodes */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf< AFGResourceNodeFrackingSatellite > SatelliteActorClass;

    FSMLFrackingNodeDisplay();
};

/**
 * Information about a resource's Decal Node
 */
USTRUCT(BlueprintType)
struct SML_API FSMLDecalNodeDisplay {
    GENERATED_BODY()
public:
    /** Actor class other mods should use to spawn nodes of this resource. Your actor should allow specifying purity and other relevant information on construct. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf< AFGResourceNode > ActorClass;
};

/**
 * Information about a resource's Geyser Node
 */
USTRUCT(BlueprintType)
struct SML_API FSMLGeyserNodeDisplay {
    GENERATED_BODY()
public:
    /** Actor class other mods should use to spawn nodes of this resource. Your actor should allow specifying purity and other relevant information on construct. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf< AFGResourceNodeGeyser > ActorClass;
};

/**
 * Information about a resource's Custom Node
 */
USTRUCT(BlueprintType)
struct SML_API FSMLCustomNodeDisplay {
    GENERATED_BODY()
public:
    /** Actor class other mods should use to spawn nodes of this resource. Your actor should allow specifying purity and other relevant information on construct. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf< AActor > ActorClass;

     FSMLCustomNodeDisplay();
};

/**
* Resources should define this so other mods can obtain information on how their resources are represented in the world.
* Note that Deposit and DecalOnly information is already handled by FGResourceDescriptor
**/
UCLASS(NotBlueprintable, BlueprintType)
class SML_API USMLResourceExtractionData : public UDataAsset {
    GENERATED_BODY()
public:
    /** The resource this data asset provides information about */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
        TSubclassOf< UFGResourceDescriptor > Resource;

    /** Information about Mining Nodes for this resource. Blank if Mining is not an extraction method for this resource. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
        FSMLMiningNodeDisplay MiningNodeDetails;

    /** Information about Fracking Nodes for this resource. Blank if Fracking is not an extraction method for this resource. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
        FSMLFrackingNodeDisplay FrackingNodeDetails;

    // TODO should decal be here or should it be expected for other mods to handle it with the info already on AFGResourceDescriptor?
    /** Information about Decal-Only Nodes for this resource. Blank if Decal-Only is not an extraction method for this resource. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
        FSMLDecalNodeDisplay DecalNodeDetails;

    // TODO should deposit be here or should it be expected for other mods to handle it with the info already on AFGResourceDescriptor?

    /** Information about Geyser Nodes for this resource. Blank if Geyser is not an extraction method for this resource. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
        FSMLGeyserNodeDisplay GeyserNodeDetails;

    /** Information about Custom Nodes for this resource. Blank if Custom is not an extraction method for this resource. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
        FSMLCustomNodeDisplay CustomNodeDetails;

    /** What extraction methods this resource supports. Resources can come from multiple extraction methods (ex. oil is decal and fracking). Call this to determine in advance which NodeDetails methods have valid outputs. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Extraction Data")
    TSet< ESMLResourceExtractionType > SupportedExtractionMethods;
};


UINTERFACE(Blueprintable)
class SML_API USMLResourceDetailsInterface : public UInterface {
    GENERATED_BODY()
};

/**
* Resources should implement this so other mods can obtain information on how their resources are represented in the world.
* Note that Deposit and DecalOnly information is already handled by FGResourceDescriptor
**/
class ISMLResourceDetailsInterface {
    GENERATED_BODY()
public:
    /** Information about Mining Nodes for this resource */
    UFUNCTION(BlueprintNativeEvent, Category = "Descriptor|World")
    FSMLMiningNodeDisplay GetMiningNodeDetails();

    /** Information about Fracking Nodes for this resource */
    UFUNCTION(BlueprintNativeEvent, Category = "Descriptor|World")
    FSMLFrackingNodeDisplay GetFrackingNodeDetails();

    /** Information about Custom Nodes for this resource */
    UFUNCTION(BlueprintNativeEvent, Category = "Descriptor|World")
    FSMLCustomNodeDisplay GetCustomNodeDetails();

    /** What extraction methods this resource supports. Resources can come from multiple extraction methods (ex. oil is decal and fracking). Use this to determine which NodeDetails methods have valid outputs. */
    UFUNCTION(BlueprintNativeEvent, Category = "Descriptor|World")
    TSet< ESMLResourceExtractionType > GetSupportedExtractionMethods() const;
};

// TODO interface for packaging/unpackaging
