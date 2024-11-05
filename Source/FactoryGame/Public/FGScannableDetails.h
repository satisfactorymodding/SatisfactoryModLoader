// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "FGScannableDetails.generated.h"

UENUM()
enum class EActorToScanState : uint8
{
	ATSS_Undetermined			UMETA( DisplayName = "Undetermined" ),
	ATSS_Visible				UMETA( DisplayName = "Visible" ),
	ATSS_Claimed				UMETA( DisplayName = "Claimed" ),
	ATSS_TemporaryClaimed		UMETA( DisplayName = "TemporaryClaimed" )
};

UENUM( BlueprintType )
enum class EScannableActorType : uint8
{
	RTWOT_Default		UMETA( DisplayName = "Default" ),
	RTWOT_WeakSignal	UMETA( DisplayName = "Weak Signal" ),
	RTWOT_Fauna			UMETA( DisplayName = "Fauna" ),
	RTWOT_Flora			UMETA( DisplayName = "Flora" ), 
};

USTRUCT( BlueprintType )
struct FScannableObjectData
{
	GENERATED_BODY()

	/** The item descriptor we will allow to scan for */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Scannable Object" )
	TSubclassOf< class UFGItemDescriptor > ItemDescriptor;

	// Objects of this class or derived from this class will be allowed to scan for the ItemDescriptor. For example object scannner and radar tower
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Scannable Object" )
	TArray<TSubclassOf< class UObject >> ActorsAllowedToScan;

	bool operator ==(const FScannableObjectData& other) const;

	bool operator !=(const FScannableObjectData& other) const;
};

USTRUCT()
struct FActorToScan
{
	GENERATED_BODY()

	FActorToScan(){}

	FActorToScan( AActor* actor, TSubclassOf<AActor> scanningClass, FVector location, EActorToScanState state ) :
		FoundActor( actor ),
		ScanningClass( scanningClass ),
		Location( location ),
		State( state )
	{}

	UPROPERTY()
	AActor* FoundActor;

	/* This is the actor class specified to scan for. It might not be the same class as the instance above.
	 * e.g if ScannedForActorClass is a creature FoundActor will probably be an CreatureSpawner
	 * */
	UPROPERTY()
	TSubclassOf<AActor> ScanningClass;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	EActorToScanState State;
	
};

USTRUCT()
struct FScannedActor
{
	GENERATED_BODY()

	FScannedActor( AActor* actor, ULevel* level, class UFGScannableDetails* scannableDetails ) :
		Actor( actor ),
		Level( level ),
		ScannableDetails( scannableDetails )
	{}
	FScannedActor(){}

	UPROPERTY()
	class AActor* Actor;

	UPROPERTY()
	class ULevel* Level;

	UPROPERTY()
	class UFGScannableDetails* ScannableDetails;
	
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FScannableDetails
{
	GENERATED_BODY()
	
	FScannableDetails() :
		ScannableClass( nullptr ),
		DisplayText( FText::GetEmpty() ),
		ScannerLightColor( FColor::White ),
		Icon( nullptr ),
		PreCacheAllOfType( true ),
		ShouldOverrideDetectionRange( false ),
		NewDetectionRange( 1000.0f ),
		NumActorsFound( 1 )
	{}
	
	/** Type of object to scan for */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf< AActor > ScannableClass;
	
	/** Name of object to scan for */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FText DisplayText;

	/** Scanner light color */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FColor ScannerLightColor;

	/** The icon that should be shown in the UI when sacnning for the ScannableClass */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSoftObjectPtr< class UTexture2D > Icon;
	
	/** Required schematic to search for this object. None means no requirement. */
	UPROPERTY( EditDefaultsOnly )
	TSoftClassPtr< class UFGSchematic > RequiredSchematic;
	
	/** Return true if this object has a required schematic */
	bool HasRequiredSchematic() const;

	/** Get the required schematic to be able to scan stuff, null signifies that the schematic isn't loaded OR there is none */
	TSubclassOf< class UFGSchematic > GetRequiredSchematic() const;
	
	/**
	* Should we get all actors at load and cache them? or do we need to update these every frame.
	* Better to cache it, but some things can't be cached (eg. Enemies). Only relevant for objects revealed by hand scanner
	*/
	UPROPERTY( EditDefaultsOnly )
	bool PreCacheAllOfType;

	/**
	* If true, NewDetectionRange will be used.
	*/
	UPROPERTY( EditDefaultsOnly )
	bool ShouldOverrideDetectionRange;

	/** Override the base detection range of the scanner. Only relevant for objects revealed by hand scanner */
	UPROPERTY( EditDefaultsOnly, meta = ( EditCondition = "ShouldOverrideDetectionRange" ) )
	float NewDetectionRange;

	/** How many actors of ScannableClass did we find. Only relevant for objects revealed by radar towers scans */
	UPROPERTY( Transient, BlueprintReadOnly )
	int32 NumActorsFound;
	
};

/** Details that are needed by the object scanner to track a potentially unloaded actor */
USTRUCT()
struct FACTORYGAME_API FScannableActorDetails
{
	GENERATED_BODY()

	FScannableActorDetails() = default;
	explicit FScannableActorDetails( AActor* actor );
	explicit FScannableActorDetails( const struct FWorldScannableData& scannableData );

	FORCEINLINE bool IsValidDetails() const { return !Actor.IsNull(); }

	friend bool operator==(const FScannableActorDetails& A, const FScannableActorDetails& B)
	{
		return A.Actor == B.Actor;
	}

	/** Returns actor location if the actor is loaded, or cached actor location if not */
	FVector GetActorLocation() const;

	/** Soft pointer to the actor in world. The actor might not be streamed in yet */
	UPROPERTY()
	TSoftObjectPtr<AActor> Actor;
	
	/** Location of the actor in world. If the actor is loaded, it's location is preferred to this value */
	UPROPERTY()
	FVector ActorLocation{ForceInit};
};

/**
 * Base class for a scanning logic for a particular item descriptor
 */
UCLASS( BlueprintType )
class FACTORYGAME_API UFGScannableDetails : public UObject
{
	GENERATED_BODY()
public:
	virtual FScannableActorDetails FindClosestRelevantActor( class UWorld* world, const FVector& scanLocation, const float maxRangeSquare, TSubclassOf<AActor> actorClassToScanFor ) const;
};

UCLASS()
class FACTORYGAME_API UFGScannableDetailsHostileCreature : public UFGScannableDetails
{
	GENERATED_BODY()
public:
	virtual FScannableActorDetails FindClosestRelevantActor(UWorld* world, const FVector& scanLocation, const float maxRangeSquared, TSubclassOf<AActor> actorClassToScanFor) const override;
};

UCLASS()
class FACTORYGAME_API UFGScannableDetailsRegrowingPickups : public UFGScannableDetails
{
	GENERATED_BODY()
public:
	virtual FScannableActorDetails FindClosestRelevantActor(UWorld* world, const FVector& scanLocation, const float maxRangeSquared, TSubclassOf<AActor> actorClassToScanFor) const override;
};

UCLASS()
class FACTORYGAME_API UFGScannableDetailsHarddrive : public UFGScannableDetails
{
	GENERATED_BODY()
public:
	virtual FScannableActorDetails FindClosestRelevantActor(UWorld* world, const FVector& scanLocation, const float maxRangeSquared, TSubclassOf<AActor> actorClassToScanFor) const override;
};


