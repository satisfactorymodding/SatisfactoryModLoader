// Copyright Coffee Stain Studios. All Rights Reserved.


/* <FL>[KonradA]
* 
* A Helper class + it's structures that will allow for easy blueprint accessible - local session - persistance of commonly used data
* 
* Usecase 1:
*	- I want to persist a "last focused sub widget state" after I close the menu (perhaps on accident)
*	- I want to restore that saved state when the widget is reopened
*	- I want this data to only persist for 5 seconds
*	- I only need this data locally
*	- I don't need this data to persist game-shutdowns
*/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGLocalPersistenceStore.generated.h"


USTRUCT(BlueprintType)
struct FACTORYGAME_API FFGLocalPersistenceStoreEntry
{
	GENERATED_BODY()
public:
	friend class UFGLocalPersistenceStore;

	UPROPERTY(BlueprintReadWrite)
	float ValidTime;
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> StringData;
	UPROPERTY(BlueprintReadWrite)
	TArray< float > NumberData;
	UPROPERTY(BlueprintReadWrite)
	TArray< UObject* > ObjectData;

protected:
	double mTimeAdded;
};

/**
 * 
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGLocalPersistenceStore : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	


public:

	UFGLocalPersistenceStore();

	// Stores data in the persistence store, optionally if a dataset with the same identifier already exists will overwrite or keep previous dataset
	// Returns: True if data was successfully stored
	UFUNCTION(BlueprintCallable)
	bool StoreData( FString HumanReadableIdentifier, FFGLocalPersistenceStoreEntry data, bool bOverwriteIfDuplicate = true );

	// Retrieves data from the store
	// Returns True if the dataset existed
	UFUNCTION( BlueprintCallable )
	bool GetStoredData( FString HumanReadableIdentifier, FFGLocalPersistenceStoreEntry& outData );

	// Removes data from the store by identifier
	// Returns True if the dataset was removed
	UFUNCTION( BlueprintCallable )
	bool RemoveStoredData( FString HumanReadableIdentifier );

private:
	UPROPERTY()
	TMap< FString, FFGLocalPersistenceStoreEntry > mLocalStore;


/* Tickable Interface */
public:
	virtual void Tick( float DeltaTime ) override;

	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
	virtual TStatId GetStatId() const override
	{
		return UObject::GetStatID();	
	}
	virtual bool IsTickableWhenPaused() const { return true; }
	virtual bool IsTickableInEditor() const { return false; }
	
private:
	uint32 LastFrameTicked = INDEX_NONE;
};
