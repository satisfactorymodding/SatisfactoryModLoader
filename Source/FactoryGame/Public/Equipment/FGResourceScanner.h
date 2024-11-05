// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGEquipment.h"
#include "Resources/FGResourceNodeBase.h"
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

	FNodeClusterData( AFGResourceNodeBase* singleNode ) :
	Nodes( { singleNode} ),
	MidPoint( singleNode->GetActorLocation() ),
	ResourceDescriptor( singleNode->GetResourceClass() )
	{
	}

	/** Cost of schematic if there are more than once item in this array the true cost will be randomly selected. */
	UPROPERTY( BluePrintReadOnly )
	TArray< class AFGResourceNodeBase* > Nodes;

	/** The average location of all the nodes */
	UPROPERTY( BluePrintReadOnly )
	FVector MidPoint;

	/** The resource descriptor of this cluster */
	UPROPERTY( BluePrintReadOnly )
	TSubclassOf< class UFGResourceDescriptor > ResourceDescriptor;
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

	/** Create resource node representations for the given cluster */
	UFUNCTION( BlueprintCallable, Category = "Resource Scanner" )
	void CreateResourceNodeRepresentations( const FNodeClusterData& cluster );

	/** Show the resource descriptor selection UI */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Scanner" )
	bool ShowResourceDescriptorSelectUI();

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
	/** The function that play effects, sound and particle, in the world at the found node */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Scanner" )
	void PlayClusterEffects( const TArray< FNodeClusterData >& clusters );

	/** Plays the scan released effect. Will be played on all clients. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Scanner" )
	void PlayScanReleasedEffect();
	
	/** server notified of when a scanning was made */
	UFUNCTION( Server, Reliable )
	void Server_ScanReleased();

	UFUNCTION( NetMulticast, Unreliable )
	void Multicast_ScanReleased();

	/** Scan button released */
	void ScanReleased();

	virtual void AddEquipmentActionBindings() override;

	/** Key binded functions */
	virtual void OnScanPressed();
	virtual void OnScanReleased();

	/** Constructs the list of nodes cluster used when scanning */
	void GenerateNodeClusters();

	/** Finds nodes within a radius of the passed node */
	void GetNodesWithinDistance( class AFGResourceNodeBase* node, float dist, TArray< class AFGResourceNodeBase* >& clusterNodes, TArray< class AFGResourceNodeBase* >& remainingNodes );

	void GetClosetClusters( TArray<FNodeClusterData>& closestClusters );

	void SplitNearbyClusters( TArray< FNodeClusterData >& clusters );

	/** Input Actions */
	void Input_Scan( const FInputActionValue& actionValue );

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

	/** Within what range to a node in a cluster will we start showing them as separate entities on map/compass */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Scanner" )
	float mUnclusterRange;
	
	UPROPERTY( EditDefaultsOnly, Category = "Resource Scanner" )
	float mRepresentationLifeSpan;

	/** A list of all the clusters of nodes non the level */
	UPROPERTY()
	TArray< FNodeClusterData > mNodeClusters;
};
