#pragma once
#include "CoreMinimal.h"
#include "FGBuildablePipeHyperAttachment.h"
#include "FGPipeHyperInterface.h"
#include "FGBuildablePipeHyperJunction.generated.h"

class USplineComponent;

USTRUCT()
struct FACTORYGAME_API FFGPipeHyperJunctionPipeData : public FFGPipeHyperBasePipeData
{
	GENERATED_BODY()

	/** Index of the route inside of the junction being travelled */
	UPROPERTY(VisibleAnywhere, Category = "Pipe Hyper")
	int32 TravelRouteIndex = 0;
};

USTRUCT(BlueprintType)
struct FFGPipeHyperJunctionPath
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* Connection0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* Connection1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Hyper")
	USplineComponent* SplineComponent;
};

USTRUCT(BlueprintType)
struct FFGPipeHyperJunctionConnectionInfo
{
	GENERATED_BODY()

	/** The connection this info is associated with */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, SaveGame, Category = "Pipe Hyper" )
	UFGPipeConnectionComponentBase* Connection;

	/** User editable label of the connection */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Pipe Hyper")
	FText ConnectionLabel;

	/** Index of the icon associated with the connection */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Pipe Hyper" )
	int32 ConnectionIconIndex;

	/** Whenever this connection is a default one to be taken when entering the junction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Pipe Hyper")
	bool bDefaultRoute;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPipeHyperJunctionConnectionInfoChanged, const FFGPipeHyperJunctionConnectionInfo&, newConnectionInfo );

UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyperJunction : public AFGBuildablePipeHyperAttachment, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeHyperJunction();

	//Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//End AActor interface
	
	//Begin IFGPipeHyperInterface
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const override;
	virtual EPipeHyperEnterResult OnPipeEnterReal( AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, TStructOnScope<FFGPipeHyperBasePipeData>& outPipeData, const TStructOnScope<FFGPipeHyperBasePipeData>& predictionPipeData ) override;
	virtual bool FindDistanceClosestToWorldLocation( AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, TStructOnScope<FFGPipeHyperBasePipeData>& out_pipeData, float& out_distance ) const override;
	virtual float GetLengthAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) override;
	virtual void GetLocationAndRotationAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, FVector& outLocation, FVector& outDirection ) override;
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, float& outExitOffset ) override;
	//End IFGPipeHyperInterface
protected:
	/** A list of valid paths for this junction, needs to be populated by the SCS */
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	TArray< FFGPipeHyperJunctionPath > JunctionPaths;

	/** A default template for the connection info set on all connections by default */
	UPROPERTY( EditAnywhere, Category = "Pipe Hyper" )
	FFGPipeHyperJunctionConnectionInfo DefaultConnectionInfo;

	/** User editable labels for the connections */
	UPROPERTY( VisibleAnywhere, SaveGame, ReplicatedUsing=OnRep_ConnectionInfoList, Category = "Pipe Hyper" )
	TArray< FFGPipeHyperJunctionConnectionInfo > ConnectionInfoList;

	UFUNCTION()
	void OnRep_ConnectionInfoList();
public:
	/** Called when one of the connection info is changed by the user, called both locally and on remote */
	UPROPERTY( BlueprintAssignable, Category = "Pipe Hyper" )
	FOnPipeHyperJunctionConnectionInfoChanged OnConnectionInfoChanged;
	
	/** Returns a list of connections for this junction */
	UFUNCTION(BlueprintPure, Category = "Pipe Hyper")
	TArray<FFGPipeHyperJunctionConnectionInfo> GetConnectionInfoList() const;

	UFUNCTION(BlueprintPure, Category = "Pipe Hyper")
	TArray<FFGPipeHyperJunctionConnectionInfo> GetConnectionInfoListForConnection(UFGPipeConnectionComponentBase* Connection) const;

	/** Returns a default output connection for the entrance */
	UFUNCTION(BlueprintPure, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* GetDefaultOutputConnection(UFGPipeConnectionComponentBase* ConnectionEnteredThrough) const;
	
	/** Updates the info for the passed connection */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Pipe Hyper")
	void UpdateConnectionInfo( const FFGPipeHyperJunctionConnectionInfo& ConnectionInfo);
};
