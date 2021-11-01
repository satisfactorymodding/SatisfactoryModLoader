// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableDecor.generated.h" 


/**
 * Base for static non-interactable decor.
 */
UCLASS( Abstract, Meta = (AutoJson = false) )
class FACTORYGAME_API AFGBuildableDecor : public AFGBuildable
{
	GENERATED_BODY()
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Ctor */
	AFGBuildableDecor();

	/** Get the mesh of the decor */
	UFUNCTION( BlueprintPure, Category = "Decor" )
	FORCEINLINE class UStaticMesh* GetDecorMesh() const{ return mDecorMesh; }

	/** Set the mesh for this decor, should not be called after it has been properly replicated */
	UFUNCTION( BlueprintCallable, Category = "Decor" )
	void SetDecorMesh( class UStaticMesh* mesh ){ mDecorMesh = mesh; }
protected:
	/** The mesh we want to have for the decor */
	UPROPERTY( SaveGame, Replicated )
	class UStaticMesh* mDecorMesh;
};
