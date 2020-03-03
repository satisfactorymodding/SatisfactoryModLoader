// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGSaveInterface.h"
#include "FGTargetPointLinkedList.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGTargetPointLinkedList : public UObject, public IFGSaveInterface
{
public:
	GENERATED_BODY()

	/** Ctor */
	UFGTargetPointLinkedList();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	/** Add a new item in the end of the linked list */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void InsertItem( class AFGTargetPoint* newTarget );

	/** Removes the desired element from the linked list */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void RemoveItem( class AFGTargetPoint* targetToRemove );

	/** Get the current target */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	FORCEINLINE class AFGTargetPoint* GetCurrentTarget() { return mCurrentTarget; }

	/** Set the current target */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void SetCurrentTarget( class AFGTargetPoint* newTarget );

	/** Get the first target in linked list */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	FORCEINLINE class AFGTargetPoint* GetFirstTarget() { return mFirst; }

	/** Get the first target in linked list */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	FORCEINLINE class AFGTargetPoint* GetLastTarget() { return mLast; }

	/** Sets visibility ( and collision ) status of all the targets in the linked list */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void SetPathVisibility( bool inVisible );

	/** Sets target in the linked list to the next available. Will loop */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void SetNextTarget();

	/** Will go through the linked list and set the target node that is closest to the vehicles position as current target */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void SetClosestPointAsTarget();

	/** Clears the linked list and destroyes the targets */
	UFUNCTION( BlueprintCallable, Category = "Path" )
	void ClearRecording();
public:
	/** First node in linked list */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mFirst; 

	/** Last node in linked list */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mLast;
private:
	/** Current node */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mCurrentTarget;

	/** Max length that the linked list can be */
	UPROPERTY( EditDefaultsOnly, Category = "LinkedList" )
	int32 mMaxLength;

public:
	FORCEINLINE ~UFGTargetPointLinkedList() = default;
};
