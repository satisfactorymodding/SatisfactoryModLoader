#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Components/SceneComponent.h"
#include "FGSaveInterface.h"
#include "DefaultValueHelper.h"
#include "FGFactoryLegsComponent.generated.h"

USTRUCT()
struct FFeetOffset
{
	GENERATED_BODY()
public:
	static uint8 GetFeetIndexFromSocketName( const FName socket );

	FFeetOffset();
	FFeetOffset( const FName socket );

	FName GetSocket() const;
public:
	/** The name of the foot's socket. */
	UPROPERTY( SaveGame )
	uint8 FeetIndex;

	/** The offset along the Z axis from the parent mesh origo. */
	UPROPERTY( SaveGame )
	float OffsetZ;

	/** Does this foot have a valid offset, only used during hologram placement. */
	UPROPERTY( NotReplicated )
	bool IsValidOffset;
};

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class UFGFactoryLegsComponent : public USceneComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UFGFactoryLegsComponent();

	//~ Begin UActorComponent interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
#if WITH_EDITOR
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
#endif
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	//~ End UActorComponent interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Get all the leg meshes. */
	UFUNCTION( BlueprintCallable, Category = "Legs" )
	TArray< class UStaticMeshComponent* > GetLegMeshComponents() const { return mLegMeshComponents; }
	/** Get all the foot meshes. */
	UFUNCTION( BlueprintCallable, Category = "Legs" )
	TArray< class UStaticMeshComponent* > GetFootMeshComponents() const { return mFootMeshComponents; }

	/**
	 * Trace for the feet offsets and return the results.
	 *
	 * @note Never call this in BeginPlay as all parts of the world are not loaded.
	 */
	TArray< FFeetOffset > TraceFeetOffsets( const FTransform& actorTransform, AActor* ignoreActor = nullptr ) const;

	/** Set/get the feet offsets from external data, must be set prior to BeginPlay. */
	void SetFeetOffsets( const TArray< FFeetOffset >& offsets );
	void ClearFeetOffsets();
	TArray< FFeetOffset > GetCachedFeetOffsets() const { return mCachedFeetOffset; }

	/** Reset the legs to zero length. */
	void SetFeetOffsetsToZero();

	/** Get the maximum length for these legs. */
	float GetMaxLegLength() const;

	/** Only here for the cheat manager. */
	void RecreateLegs()
	{
		RemoveLegs();
		CreateLegs();
	}

private:
	FFeetOffset TraceFootOffset( FName socket, const FTransform& actorTransform, AActor* ignoreActor = nullptr ) const;

	class UStaticMesh* GetLegMesh() const;
	class UStaticMesh* GetFootMesh() const;

	void CreateLegs();
	void RemoveLegs();

	void CreateFoot( const FFeetOffset& offset );

protected:
	/** Socket names on the parent mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	TArray< FName > mLegSocketNames;

	/** The mesh to be used as legs on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mLegMeshOverride;

	/** The mesh to be used as foots on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mFootMeshOverride;

	/** The maximum length the legs can be. */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	float mMaxLegLengthOverride;

private:
	/** The created leg components for this building */
	UPROPERTY( Transient )
	TArray< UStaticMeshComponent* > mLegMeshComponents;

	/** The created foot components for this building */
	UPROPERTY( Transient )
	TArray< UStaticMeshComponent* > mFootMeshComponents;

	/** Stored so that we know the offset of the feet */
	UPROPERTY( SaveGame, Replicated )
	TArray< FFeetOffset > mCachedFeetOffset;
};
