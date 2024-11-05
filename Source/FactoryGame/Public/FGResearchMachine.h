// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGResearchManager.h"
#include "Components/SceneComponent.h"
#include "FGRecipeProducerInterface.h"
#include "FGResearchMachine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), meta=(DefaultToInstanced) )
class FACTORYGAME_API UFGResearchMachine : public USceneComponent, public IFGRecipeProducerInterface
{
	GENERATED_BODY()

public:	
	UFGResearchMachine();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetResearchRecipe( TSubclassOf<class UFGResearchRecipe> researchRecipe );

	/** Returns current M.A.M. user */
	UFUNCTION( BlueprintPure, Category = "Research" )
	FORCEINLINE class AFGCharacterPlayer* GetMachineUser(){ return mPlayerUsingMachine; }
	
	/** Returns the Static Mesh Component that displays the mesh of what is being researched */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	UStaticMeshComponent* GetResearchMeshComponent();

	/** Sets the Static Mesh Component that displays the mesh of what is being researched */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetResearchMeshComponent( UStaticMeshComponent* staticMeshComponent );

	/** Sets the curve float for the mesh that is being researched */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetResearchMeshCurveScale( UCurveFloat* curveScale );

	UFUNCTION( )
	void OnResearchStarted( TSubclassOf<class UFGSchematic> schematic );
	
	UFUNCTION( )
	void OnResearchConcluded( TSubclassOf<class UFGSchematic> schematic );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetMachineUser( class AFGCharacterPlayer* player );

	UFUNCTION(BlueprintPure, Category = "Research")
	FORCEINLINE bool IsResearchBeingConducted() const { return AFGResearchManager::Get( this->GetWorld() ) ? AFGResearchManager::Get( this->GetWorld() )->IsAnyResearchBeingConducted() : false; }

protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	// End AActor Interface

private:
	UFUNCTION( )
	void OnRep_ResearchMesh();

protected:
	UPROPERTY( Replicated )
	TSubclassOf<class UFGResearchRecipe> mCurrentResearchRecipe;

	UPROPERTY( Replicated )
	AFGCharacterPlayer* mPlayerUsingMachine;

private:
	UPROPERTY( )
	UStaticMeshComponent* mResearchingMeshComponent;

	/** This holds the actual mesh to be displayed by the assigned Static Mesh Component for mResearchingMeshComponent */
	UPROPERTY( ReplicatedUsing = OnRep_ResearchMesh )
	UStaticMesh* mResearchingMesh;

	UPROPERTY( )
	UCurveFloat* mItemScaleCurve;

};
