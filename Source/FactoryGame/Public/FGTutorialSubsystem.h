// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "FGTutorialSubsystem.generated.h"


USTRUCT( BlueprintType )
struct FACTORYGAME_API FTutorialData
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< UObject > ClassBuilt;

	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGMessageBase > MessageID;

public:
	FORCEINLINE ~FTutorialData() = default;
};

struct FACTORYGAME_API FFindByClassBuilt
{
	TSubclassOf< UObject > ClassBuilt;

	FFindByClassBuilt( TSubclassOf< UObject > InClassBuilt ) : ClassBuilt( InClassBuilt ) { }

	bool operator() ( const FTutorialData Element ) const
	{
		return ( ClassBuilt == Element.ClassBuilt );
	}

public:
	FORCEINLINE ~FFindByClassBuilt() = default;
};

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGTutorialSubsystem : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Starts checking if we should show a tutorial for the thing that was built */
	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void AddToBuiltClasses( TSubclassOf< UObject > inClass );

	/** Setup delegates */
	void Init();

	/** Called when the local player builds anything */
	UFUNCTION()
	void OnBuildingBuilt( TSubclassOf< class UFGItemDescriptor > itemDesc );

	/** Hax function for clearing all saved config data */
	UFUNCTION(BlueprintCallable, Category = "Tutorial" )
	void ClearBuiltData();

	/** Check if we should add the intro tutorial messages */
	void PonderAddingIntroTutorial();
private: 
	/** classes of things we have build */
	UPROPERTY( SaveGame )
	TArray< TSubclassOf< UObject > > mBuildingsBuilt;

	/** Used to indicate if we should push the intro messages */
	UPROPERTY( SaveGame )
	bool mHasSeenIntroTutorial;

	/** Messages to display when first starting the game */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TArray< TSubclassOf< class UFGMessageBase > > mIntroTutorialMessages;

	/** In this array we specify what buildings we want in-game tutorial for */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TArray< FTutorialData > mTutorialData;
public:
	/** Needed to set up delegates */
	UPROPERTY( SaveGame )
	class AFGPlayerState* mOwningPlayerState;

public:
	FORCEINLINE ~UFGTutorialSubsystem() = default;
};
