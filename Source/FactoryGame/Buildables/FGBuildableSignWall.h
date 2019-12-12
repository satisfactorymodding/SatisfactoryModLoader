// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableWall.h"
#include "FGBuildableSignWall.generated.h"


USTRUCT( BlueprintType )
struct FSignWallData
{
	GENERATED_BODY()
public: // MODDING EDIT?
	/** Index of the selected color for the text from the FGSignSettings color data array  */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "SignWall")
	int32 TextColorIndex;

	/** Index of the selected color for the background from the FGSignSettings color data array  */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "SignWall")
		int32 BackgroundColorIndex;

	/** Text to be displayed on the sign */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "SignWall")
		FString SignText;

	FSignWallData() :
		TextColorIndex( 0 ),
		BackgroundColorIndex( 2 ),
		SignText( "THIS IS A WALL SIGN" )
	{}

};


/**
 *  Represents a wall that contains sign elements and is interactable
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSignWall : public AFGBuildableWall
{
	GENERATED_BODY()
	
public:
	AFGBuildableSignWall();

	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin Actor Interface 
	virtual void BeginPlay() override;
	// End Actor Interface

	// Called by server or client to update sign data
	UFUNCTION( BlueprintCallable, Category = "WallSign" )
	void SetSignData( FSignWallData signData, bool bUpdate = true );

	/** Updates all sign elements with currently set sign data */
	void UpdateSignElements();

	/** Updates background material on static mesh instance */
	void UpdateBackgroundMaterial();

	/** Force an update on the text render component */
	void UpdateSignText();

	UFUNCTION( BlueprintPure, Category = "WallSign" )
	const FSignWallData& GetSignData();

protected:
	/** Update sign components on replication */
	UFUNCTION()
	void OnRep_SignData();

protected:
	/** Root Component that holds all the sign elements, text, mesh etc. */
	UPROPERTY( VisibleAnywhere, Category = "WallSign" )
	USceneComponent* mSignDisplayRoot;

	/** Root component that parents the text objects */
	UPROPERTY( VisibleAnywhere, Category = "WallSign" )
	USceneComponent* mTextDisplayRoot;

	/** Front text render component*/
	UPROPERTY( VisibleAnywhere, Category = "WallSign" )
	class UTextRenderComponent* mTextRenderComponent;

private:
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_SignData )
	FSignWallData mSignData;
	
};
