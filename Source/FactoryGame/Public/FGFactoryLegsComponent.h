// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/SceneComponent.h"
#include "FGSaveInterface.h"
#include "Misc/DefaultValueHelper.h"
#include "AbstractInstanceManager.h"
#include "FGFactoryLegsComponent.generated.h"

/**
 * Information about one leg on a factory.
 */
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
	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess )
	{
		Ar << FeetIndex;
		
		bOutSuccess = true;
		if( Ar.IsSaving() )
		{
			bOutSuccess = WriteFixedCompressedFloat<16384, 16>( OffsetZ, Ar );
		}
		else
		{
			bOutSuccess = ReadFixedCompressedFloat<16384, 16>( OffsetZ, Ar );
		}

		return bOutSuccess;
	}

	/** The index from the foot's socket name, i.e. foot_04 would be 4. */
	UPROPERTY( SaveGame )
	uint8 FeetIndex;

	/** The offset along the Z axis from the parent mesh origo. */
	UPROPERTY( SaveGame )
	float OffsetZ;

	/** Does this foot have a valid offset, only used during hologram placement. */
	UPROPERTY( NotReplicated )
	bool IsValidOffset;
};

template<>
struct TStructOpsTypeTraits<FFeetOffset> : public TStructOpsTypeTraitsBase2<FFeetOffset>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 * Class that manages the legs on a factory.
 * This component does:
 *   Trace for foot offsets for each leg.
 *   Save the offsets in the save game.
 *   Auto-create the legs on register and remove them on unregister.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGFactoryLegsComponent : public USceneComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UFGFactoryLegsComponent();

	//~ Begin UActorComponent interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
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

	/** Returns true if we have valid legs */
	bool HasValidLegs() const;

	/** Called by the buildable to create factory leg instances */
	void CreateLegInstances( TArray<FInstanceData>& out_legInstanceData );
private:
	FFeetOffset TraceFootOffset( FName socket, const FTransform& actorTransform, AActor* ignoreActor = nullptr ) const;

	class UStaticMesh* GetLegMesh() const;
	class UStaticMesh* GetFootMesh() const;

	void CreateFootInstanced( const FFeetOffset& offsetData, TArray<FInstanceData>& out_legInstanceData ) const;
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

	/** Scale of the factory leg mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	FVector mLegScale;

	/** The maximum length the legs can be. */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	float mMaxLegLengthOverride;

	/** Minimum trace length that the buildable should make before spawning legs, -1 means always spawn*/
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	float mMinimumLegLength;

private:
	/** Stored so that we know the offset of the feet */
	UPROPERTY( SaveGame, Replicated )
	TArray< FFeetOffset > mCachedFeetOffset;
};
