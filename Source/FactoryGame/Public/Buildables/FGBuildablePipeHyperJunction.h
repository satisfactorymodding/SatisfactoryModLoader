#pragma once
#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildablePipeHyperAttachment.h"
#include "FGCharacterMovementComponent.h"
#include "FGPipeHyperInterface.h"
#include "FGBuildablePipeHyperJunction.generated.h"

class USplineComponent;

USTRUCT()
struct FACTORYGAME_API FFGPipeHyperJunctionPipeData
{
	GENERATED_BODY()

	/** Index of the route inside the junction being travelled */
	UPROPERTY(VisibleAnywhere, Category = "Pipe Hyper")
	int32 TravelRouteIndex = 0;
};

USTRUCT(BlueprintType)
struct FFGPipeHyperJunctionPath
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* Connection0{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* Connection1{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	USplineComponent* SplineComponent{};
};

USTRUCT(BlueprintType)
struct FFGPipeHyperJunctionDefaultPath
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* InputConnection{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* DefaultOutputConnection{};
};

UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyperJunction : public AFGBuildablePipeHyperAttachment, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:
	//Begin IFGPipeHyperInterface
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const override;
	virtual EPipeHyperEnterResult OnPipeEnterReal( AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, FFGDynamicStruct& outPipeData, const FFGDynamicStruct& predictionPipeData ) override;
	virtual bool FindDistanceClosestToWorldLocation( AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, FFGDynamicStruct& out_pipeData, float& out_distance ) const override;
	virtual float GetLengthAlongPipe( AFGCharacterPlayer* charPlayer, const FFGDynamicStruct& pipeData ) override;
	virtual void GetLocationAndRotationAlongPipe( AFGCharacterPlayer* charPlayer, const FFGDynamicStruct& pipeData, float distance, FVector& outLocation, FVector& outDirection ) override;
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough( AFGCharacterPlayer* charPlayer, const FFGDynamicStruct& pipeData, float distance, float& outExitOffset ) override;
	//End IFGPipeHyperInterface
protected:
	/** A list of valid paths for this junction, needs to be populated by the SCS */
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	TArray<FFGPipeHyperJunctionPath> JunctionPaths;

	/** A list of default output routes for this junction, needs to be populated by the SCS */
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	TArray<FFGPipeHyperJunctionDefaultPath> DefaultPaths;
public:
	/** Returns a list of available output connections given the input connection and the player querying the data */
	UFUNCTION(BlueprintPure, Category = "Pipe Hyper")
	virtual TArray<FFGHypertubeJunctionOutputConnectionInfo> GetAvailableOutputConnections( const UFGPipeConnectionComponentBase* connectionEnteredThrough, AFGCharacterPlayer* forPlayer ) const;

	/** Returns a default output connection for the entrance */
	UFUNCTION(BlueprintPure, Category = "Pipe Hyper")
	virtual UFGPipeConnectionComponentBase* GetDefaultOutputConnection( const UFGPipeConnectionComponentBase* connectionEnteredThrough ) const;
	
	/** Deprecated function called by BP_RemoteCallObject, which is checked out right now. Will be removed once the file is released */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void UpdateConnectionInfo( const FFGHypertubeJunctionOutputConnectionInfo& ConnectionInfo) {}
protected:
	virtual FFGDynamicStruct PopulateOutputConnectionMetadataForPlayer( const UFGPipeConnectionComponentBase* connectionEnteredThrough, const UFGPipeConnectionComponentBase* outputConnection, AFGCharacterPlayer* forPlayer ) const;
};
