#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Engine/StaticMeshActor.h"
#include "FGProceduralStaticMeshActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGProceduralStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	/** @copydoc AActor::PostEditChangeProperty */
	virtual void PreEditChange( UProperty* PropertyThatWillChange ) override;

	/** @copydoc AActor::PostEditChangeProperty */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& propertyChangedEvent ) override;

	/** Moved in the editor, on done, regenerate foliage if we have foliage type */
	virtual void PostEditMove( bool bFinished ) override;
#endif
private:
#if WITH_EDITOR
	void PaintBucket_Add();
	void PaintBucket_Remove();

	float GetMeshArea( const FVector& origin, const FVector& extent ) const;
	void GetRandomTraceInBounds( const FVector& origin, const FVector& extent, FVector& out_start, FVector& out_end ) const;
#endif
public:
#if WITH_EDITORONLY_DATA
	// MODDING EDIT: FoliageTypes.h could not open FoliageTypes.generated.h
	///** The foliage types that we want to be placed upon us */
	//UPROPERTY(EditInstanceOnly)
	//TArray<class UFoliageType*> mFoliageTypes;
#endif
};