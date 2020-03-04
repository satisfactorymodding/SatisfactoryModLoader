#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGResourceScanner.generated.h"

/** Holds information about resource node clusters. This could be saved in actors on the level for optimization. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FNodeClusterData
{
	GENERATED_BODY()

	FNodeClusterData() :
		MidPoint( FVector::ZeroVector ),
		ResourceDescriptor( nullptr )
	{
	}

	/** Cost of schematic if there are more than once item in this array the true cost will be randomly selected. */
	UPROPERTY( BluePrintReadOnly )
	TArray< class AFGResourceNode* > Nodes;

	/** The average location of all the nodes */
	UPROPERTY( BluePrintReadOnly )
	FVector MidPoint;

	/** The resource descriptor of this cluster */
	UPROPERTY( BluePrintReadOnly )
	TSubclassOf< class UFGResourceDescriptor > ResourceDescriptor;

public:
	FORCEINLINE ~FNodeClusterData() = default;
};


/**
* Locates resources for the player.
*/
UCLASS()
class FACTORYGAME_API AFGResourceScanner : public AFGEquipment
{
	GENERATED_BODY()

public:
	AFGResourceScanner();

	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	virtual bool ShouldSaveState() const;

	/** The function that play effects, sound and particle, in the world at the found node */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Scanner" )
	void PlayClusterEffects( const TArray< FNodeClusterData >& clusters );

	/** Show the resource descriptor selection UI */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Scanner" )
	void ShowResourceDescriptorSelectUI();

	/** Close the resource descriptor selection UI */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Resource Scanner" )
	void CloseResourceDescriptorSelectUI();

	/** Returns the current resource descriptor class that we scan for nodes that has */
	UFUNCTION( BlueprintPure, Category = "Resource Scanner" )
	FORCEINLINE TSubclassOf< UFGResourceDescriptor > GetResourceDescriptorToScanFor() const { return mResourceDescriptorToScanFor; }

	/** Returns the current resource descriptor classes that we should be able to chose from */
	UFUNCTION( BlueprintPure, Category = "Resource Scanner" )
	TArray< TSubclassOf< UFGResourceDescriptor > > GetScannableResources() const;
	
	/** Set resource descriptor class we should scan for */
	UFUNCTION( BlueprintCallable, Category = "Resource Scanner" )
	void SetResourceDescriptorToScanFor( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Put the equipment away. */
	virtual void UnEquip();

	/** Sets the status of mIsPressingScan */
	UFUNCTION( BlueprintCallable, Category = "Resource Scanner" )
	void SetPressingScan( bool isPressingScan ) { mIsPressingScan = isPressingScan; }
protected:
	/** server notified of when a scanning was made */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_ScanReleased();

	/** Scan button released */
	void ScanReleased();

	virtual void AddEquipmentActionBindings() override;

	/** Key binded functions */
	virtual void OnScanPressed();
	virtual void OnScanReleased();

	/** Constructs the list of nodes cluster used when scanning */
	void GenerateNodeClusters();

	/** Finds nodes within a radius of the passed node */
	void GetNodesWithinDistance( AFGResourceNode* node, float dist, TArray< AFGResourceNode* >& clusterNodes, TArray< AFGResourceNode* >& remainingNodes );

protected:
	/** This is the resource class to scan for */
	UPROPERTY()
	TSubclassOf< UFGResourceDescriptor > mResourceDescriptorToScanFor;
	
	/** How many node clusters should be marked */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Scanner" )
	int32 mNrOfClosestClustersToMark;

	/** Keeps track of the last time we pressed Scan */
	UPROPERTY()
	float mLastPressedTimeStamp;

	/** Time needed to hold down the key to show the selection UI */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Scanner" )
	float mHoldDownDurationForUI;

	/** True in between OnScanPressed and OnScanReleased */
	UPROPERTY()
	bool mIsPressingScan;

	/** True if we are waiting for the selection UI */
	UPROPERTY()
	bool mIsWaitingForSelectionUI;

	/** If nodes are closer that dist they are considered within the cluster */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Scanner" )
	float mDistBetweenNodesInCluster;

	/** A list of all the clusters of nodes non the level */
	UPROPERTY()
	TArray< FNodeClusterData > mNodeClusters;

private:
	// Temp fix for avoiding scanning when opening CheatBoard, function is bound to CheatBoard input
	void OnCheatBoardOpened();

public:
	FORCEINLINE ~AFGResourceScanner() = default;
};