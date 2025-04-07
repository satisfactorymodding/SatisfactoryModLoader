// Copyright Coffee Stain Studios. All Rights Reserved.

#include "Buildables/FGBuildable.h"
#include "AkAudioDevice.h"
#include "AkComponent.h"
#include "AkGameplayStatics.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Buildables/FGBuildableConveyorBase.h"
#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGBuildableWire.h"
#include "Components/StaticMeshComponent.h"
#include "FGAttachmentPoint.h"
#include "FGAttachmentPointComponent.h"
#include "FGBackgroundThread.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGCharacterPlayer.h"
#include "FGCircuitConnectionComponent.h"
#include "FGDecorationTemplate.h"
#include "FGFactoryConnectionComponent.h"
#include "FGFactoryLegsComponent.h"
#include "FGFactorySettings.h"
#include "FGHUD.h"
#include "FGInventoryLibrary.h"
#include "FGMaterialEffectComponent.h"
#include "FGPlayerController.h"
#include "FGPowerCircuit.h"
#include "FGPowerConnectionComponent.h"
#include "FGRecipe.h"
#include "FGSplineComponent.h"
#include "FGSwatchGroup.h"
#include "FactoryGame.h"
#include "FactoryGameCustomVersion.h"
#include "Hologram/FGHologram.h"
#include "Resources/FGBuildingDescriptor.h"
#include "InstanceData.h"
#include "AbstractInstanceManager.h"
#include "DisplayDebugHelpers.h"
#include "Engine/Canvas.h"
#include "DrawDebugHelpers.h"
#include "FGBuildEffectActor.h"
#include "FGBlueprintProxy.h"
#include "FGBlueprintSubsystem.h"
#include "Buildables/FGBuildableBlueprintDesigner.h"
#include "FGBuildEffectSettings.h"
#include "FGCircuitSubsystem.h"
#include "FGColoredInstanceMeshProxy.h"
#include "FGProductionIndicatorInstanceComponent.h"
#include "FGGameState.h"
#include "FGLightweightBuildableSubsystem.h"
#include "FGPipeConnectionComponent.h"
#include "FGPowerInfoComponent.h"
#include "FGProximitySubsystem.h"
#include "FGRecipeManager.h"
#include "Net/UnrealNetwork.h"
#include "SharedStats.h"
#include "BlueprintNodeHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Engine/NetConnection.h"
#include "Kismet/GameplayStatics.h"
#include "UI/FGGameUI.h"
#include "Misc/DataValidation.h"
#include "AkAudioEvent.h"
#include "FGRailroadTrackConnectionComponent.h"
#include "FGSchematicManager.h"
#include "FGWorldSettings.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildablePipeBase.h"
#include "Internationalization/StringTableRegistry.h"


#if WITH_EDITOR
#include "FileHelpers.h"
#include "ISourceControlModule.h"
#include "Logging/MessageLog.h"
#include "Misc/UObjectToken.h"
#endif

#define LOCTEXT_NAMESPACE "Buildable"

static const float DISMANTLE_LIFE_SPAN_SAFE = 10.0f;
static const float DISMANTLE_LIFE_SPAN = 2.0f;

DECLARE_CYCLE_STAT( TEXT( "Buildable" ), STAT_ExecuteInterface_Buildable, STATGROUP_ExecuteInterface );
DECLARE_CYCLE_STAT( TEXT( "Buildable SetCustomizationData_Native" ), STAT_BuildableSetCustomizationData, STATGROUP_Game );
DECLARE_CYCLE_STAT( TEXT( "Buildable ApplyCustomizationData" ), STAT_BuildableApplyCustomizationData, STATGROUP_Game );
DECLARE_CYCLE_STAT( TEXT( "Buildable ApplySkinData" ), STAT_BuildableApplySkinData, STATGROUP_Game );

#if WITH_EDITOR

static TAutoConsoleVariable<bool> CVarDisablePlayerInteractionRegistration(
	TEXT("FGBuildable.DebugDisablePlayerInteractionRegistration"),
	false,
	TEXT("When set to true, interaction of the players with the buildables will not be handled through Register/UnregisterInteractingPlayer, allowing to check preconditions hold by conditional property replication."),
	ECVF_Cheat );

#endif

void AFGBuildable::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	FDoRepLifetimeParams params;

	params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mColorSlot, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mCustomizationData, params );

	params.bIsPushBased = false;
	params.Condition = COND_InitialOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mNetConstructionID, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mBuildEffectInstignator, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mBuiltWithRecipe, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mOriginalBuildableVariant, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mBlueprintProxy, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mIsMultiSpawnedBuildable, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mBlueprintBuildEffectID, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mReplicatedBuiltInsideBlueprintDesigner, params );
	DOREPLIFETIME_WITH_PARAMS_FAST( AFGBuildable, mBlueprintDesigner, params );
}

AFGBuildable::AFGBuildable(const FObjectInitializer& ObjectInitializer) :
	Super( ObjectInitializer ),
	MaxRenderDistance( -1 ),
	mSwatchGroup( UFGSwatchGroup_Standard::StaticClass() ),
	mShouldShowAttachmentPointVisuals( false ),
	//mInteractWidgetClass( nullptr ),
	mInteractWidgetSoftClass( nullptr ),
	mIsUseable( false ),
	mNetConstructionID(),
	mHideOnBuildEffectStart( false ),
	mShouldModifyWorldGrid( true ),
	mIsAboutToBeDismantled( false ),
	mBlueprintBuildEffectID( INDEX_NONE )
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	bReplicates = true;
	NetDormancy = DORM_Initial;

	
	HAS_BLUEPRINT_IMPLEMENTATION( mHasBlueprintFactoryTick, Factory_ReceiveTick, AFGBuildable );
	HAS_BLUEPRINT_IMPLEMENTATION( mHasFactory_PeekOutput, Factory_PeekOutput, AFGBuildable );
	HAS_BLUEPRINT_IMPLEMENTATION( mHasFactory_GrabOutput, Factory_GrabOutput, AFGBuildable );
	HAS_BLUEPRINT_IMPLEMENTATION( mHasSetupInstances, SetupInstances, AFGBuildable );

	mFactoryTickFunction.TickGroup = TG_PrePhysics;
	// Default to no tick function, but if we set 'never ticks' to false (so there is a tick function) it is enabled by default
	mFactoryTickFunction.bCanEverTick = false;
	mFactoryTickFunction.bStartWithTickEnabled = true;
	mFactoryTickFunction.SetTickFunctionEnable( false );

	RootComponent = CreateDefaultSubobject< USceneComponent >( TEXT("RootComponent") );
	RootComponent->SetMobility( EComponentMobility::Static );

	// 75k uu away
	NetCullDistanceSquared = 5625000000.f;

	// Default to all buildables being able to be colored
	mAllowColoring = true;
	mAllowPatterning = true;
}

void AFGBuildable::PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion )
{
}

void AFGBuildable::PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion )
{
	mBuildEffectInstignator = nullptr; //[HannaS 15/5-20] clear the effect instigator when saving so that clients do not get the build effect after a while
}
void AFGBuildable::PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion )
{
}
void AFGBuildable::PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion )
{
	QUICK_SCOPE_CYCLE_COUNTER( PostLoadGame_Implementation )

	mBuildEffectInstignator = nullptr; //[DavalliusA:Mon/01-04-2019] make sure the buildings loaded don't play the build effect. Just in case.

	// Migration for turning mColorSlot into its correspoinding SwatchAsset
	if( mCustomizationData.SwatchDesc == nullptr )
	{
		mCustomizationData.SwatchDesc = AFGBuildableSubsystem::Get( GetWorld() )->GetMigrationSwatchForSlot( mColorSlot );
	}

	// Update the replicated boolean variable on load to make sure it has correct value even if the buildable has not begun play yet
	mReplicatedBuiltInsideBlueprintDesigner = IsValid( mBlueprintDesigner );
}

void AFGBuildable::GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ){}
bool AFGBuildable::NeedTransform_Implementation() { return true; }
bool AFGBuildable::ShouldSave_Implementation() const { return !mIsLightweightTemporary && !mIsDismantled; }

TArray<FInstanceData> AFGBuildable::GetActorLightweightInstanceData_Implementation() const
{
	if (const UAbstractInstanceDataObject* StaticDataObject = GetLightweightInstanceData())
	{
		return StaticDataObject->GetInstanceData();
	}
	return TArray<FInstanceData>();
}

FInstanceHandleArray AFGBuildable::GetLightweightInstanceHandles() const
{
	TArray<FInstanceHandlePtr> OutInstanceHandles;
	for ( const FInstanceOwnerHandlePtr& OwnerHandlePtr : mInstanceHandles )
	{
		OutInstanceHandles.Add( OwnerHandlePtr );
	}
	return FInstanceHandleArray{ OutInstanceHandles };
}
	
FInstanceHandleArray AFGBuildable::GetDynamicLightweightInstanceHandles() const
{
	TArray<FInstanceHandlePtr> OutDynamicInstanceHandles;
	for ( const FInstanceOwnerHandlePtr& OwnerHandlePtr : mDynamicInstanceHandles )
	{
		OutDynamicInstanceHandles.Add( OwnerHandlePtr );
	}
	return FInstanceHandleArray{ OutDynamicInstanceHandles };
}

void AFGBuildable::PostLazySpawnInstances_Implementation()
{
	// Ensure colors to be applied.
	OnRep_CustomizationData();
}

void AFGBuildable::GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const
{
	out_data.Append( mClearanceData );
}

#if WITH_EDITOR
EDataValidationResult AFGBuildable::IsDataValid(FDataValidationContext& Context) const
{
	const EDataValidationResult SuperResult = Super::IsDataValid( Context );
	EDataValidationResult Result = EDataValidationResult::NotValidated;

	bool success = true;
	if( mManagedByLightweightBuildableSubsystem )
	{
		if( mInstanceDataCDO == nullptr )
		{
			FText ErrorMsg = FText::AsCultureInvariant("Lightweight management cannot occur on with Null Instance Data! Create AbstractInstanceData for buildable");
			Context.AddError(ErrorMsg);
			success = false;
		}

		// Blueprint added comps
		if( const UBlueprintGeneratedClass* ActorBlueprintGeneratedClass = Cast< UBlueprintGeneratedClass >( this->GetClass() ) )
		{
			const TArray< USCS_Node* >& ActorBlueprintNodes = ActorBlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes();

			for ( USCS_Node* Node : ActorBlueprintNodes )
			{
				if ( UClass::FindCommonBase( Node->ComponentClass, UFGConnectionComponent::StaticClass() ) &&
					!Node->IsEditorOnly() )
				{		
					if ( UFGConnectionComponent* BlueprintComponent = Cast< UFGConnectionComponent >( Node->ComponentTemplate ) )
					{
						FText ErrorMsg = FText::AsCultureInvariant("Lightweight management cannot occur With Connection Components as children. This will result in undesirable results!");
						Context.AddError(ErrorMsg);
						success = false;
					}
				}
			}
		}

		// native comps
		TInlineComponentArray< USceneComponent* > Components{this};
		for( USceneComponent* sceneComp : Components )
		{
			if( UFGConnectionComponent* ConnectionComponent = Cast<UFGConnectionComponent>(sceneComp) )
			{
				FText ErrorMsg = FText::AsCultureInvariant("Lightweight management cannot occur With Connection Components as children. This will result in undesirable results!");
				Context.AddError(ErrorMsg);
				success = false;
			}
		}
	}
	
	Result = success ? EDataValidationResult::Valid : EDataValidationResult::Invalid;

	return CombineDataValidationResults( Result, SuperResult );
}
#endif

void AFGBuildable::AddClearanceData( const FFGClearanceData& newData )
{
	mClearanceData.Add( newData );
}

void AFGBuildable::AddClearanceData( const TArray< FFGClearanceData >& newData )
{
	mClearanceData.Append( newData );
}

void AFGBuildable::ResetClearanceData()
{
	mClearanceData.Reset();
}

FBox AFGBuildable::GetCombinedClearanceBox() const
{
	FBox result( EForceInit::ForceInitToZero );
	
	for( const FFGClearanceData& clearance : mClearanceData )
	{
		result += clearance.GetTransformedClearanceBox();
	}

	return result;
}

void AFGBuildable::BeginPlay()
{
	QUICK_SCOPE_CYCLE_COUNTER(AFGBuildable_BeginPlay);
	Super::BeginPlay();

	// Make sure we have both world settings and the game state, we need subsystems from both to initialize
	AFGWorldSettings* worldSettings = CastChecked<AFGWorldSettings>( GetWorld()->GetWorldSettings() );
	AFGGameState* gameState = CastChecked<AFGGameState>( GetWorld()->GetGameState() );

	// Very first things first - Check to see that we have a built with recipe. If not then we need to find one that matches our buildable. Old saves can be missing this
	// We also only want to do this for buildables that can be actually placed so we verify a valid hologram class. Tex. Pipeline flow indicators are buildables but cannot be built by players
	if( HasAuthority() && !mBuiltWithRecipe && mHologramClass && gameState->GetSchematicManager() )
	{
		if( const TSubclassOf<UFGRecipe> recipe = gameState->GetSchematicManager()->FixupSave_FindBuiltByRecipe( this ) )
		{
			SetBuiltWithRecipe( recipe );
		}
	}

	// Early out path to initialize buildables that are either going to be immediately converted to lightweights OR are going to do so when their blueprint build effect finishes
	if( ShouldConvertToLightweight() )
	{
		// We want to set up the attachment points for lightweight temporaries but not for buildables that are being fully converted
		if( mIsLightweightTemporary )
		{
			CreateAttachmentPointsFromComponents( mAttachmentPoints, this );
		}

		// Will add to the lightweight subsystem and subsequently destroy this actor
		bool successfullyHandled = HandleLightweightAddition();

		// Finally safety check. Basically if this is false it means we didn't have a proper instance created so just leave the building as is
		if( successfullyHandled )
		{
			return;
		}
	}

	if ( mBlueprintBuildEffectID != INDEX_NONE )
	{
		if( AFGBlueprintSubsystem* blueprintSubsystem =  AFGBlueprintSubsystem::Get( GetWorld() ) )
		{
			blueprintSubsystem->NotifyBuildableWithBlueprintBuildIDSet( this, mBlueprintBuildEffectID );
		}
	}

	AFGBuildableSubsystem* buildableSubsystem = worldSettings->GetBuildableSubsystem();

	// Sync mReplicatedBuiltInsideBlueprintDesigner with the validity of the blueprint designer reference on BeginPlay on the host
	if ( HasAuthority() )
	{
		mReplicatedBuiltInsideBlueprintDesigner = IsValid( mBlueprintDesigner );
	}

	// !!TODO 1.0 we can cache this on the sparse data instead.
	if ( DoesContainLightweightInstances_Native() )
	{
		auto baseLocation = GetTransform().GetLocation();
		const auto& baseTransform = GetTransform();
		FBoxSphereBounds base(baseLocation,FVector(0,0,0),0.f);
		
		if ( auto InstanceData = GetLightweightInstanceData() )
		{
			for (auto& instance : InstanceData->GetInstanceData())
			{
				const FTransform instanceTransform = instance.RelativeTransform * baseTransform;
				auto bound = instance.StaticMesh->GetBounds().TransformBy(instanceTransform);
				base = base + bound;
			}
		}

		mCachedBounds = base.GetBox();
	}
	else
	{
		mCachedBounds = GetComponentsBoundingBox( false );
	}
	
	// Don't add blueprint buildables  to the buildable subsystem (we don't want simulation actually running on these)
	// We need to use replicated bool property instead of checking for valid blueprint designer, as it might not have been replicated yet
	if( !mReplicatedBuiltInsideBlueprintDesigner )
	{
		buildableSubsystem->AddBuildable( this );
	}
	else
	{
		buildableSubsystem->OnDesignerBuildableSpawned( this );
	}

	// Register ourselves to our blueprint proxy, if we have one
	if( IsValid( mBlueprintProxy ) )
	{
		mBlueprintProxy->RegisterBuildable( this );
	}
	
	// Get the specified default swatch
	if( mCustomizationData.SwatchDesc == nullptr )
	{
		mCustomizationData.SwatchDesc = GetDefaultSwatchCustomizationOverride( GetWorld() );
	}

	mCustomizationData.Initialize( gameState );
	// We do not require a skin update if we have no skin applied on BeginPlay
	mCustomizationData.NeedsSkinUpdate = mCustomizationData.SkinDesc != nullptr;

	const bool HasValidDecoratorClass = IsValid( mDecoratorClass );
	
	if( mBuildEffectInstignator && !mIsMultiSpawnedBuildable )
	{
		if(!bForceLegacyBuildEffect)
		{
			ExecutePlayBuildActorEffects();
		}
		else
		{
			// ! Legacy build effect, only used in super rare cases we shouldn't rely on this!
			ExecutePlayBuildEffects();
		}
	}
	else if( !mIsMultiSpawnedBuildable ) 
	{
		if ( HasValidDecoratorClass )
		{
			RegisterWithBackgroundThread();
		}

		// Handle lightweight instance data.
		CallSetupInstances();
	}

	if ( mIsMultiSpawnedBuildable )
	{
		for (auto comp : TInlineComponentArray<UFGColoredInstanceMeshProxy*>{this})
		{
			comp->SetInstanced(false);
		}

		SetActorHiddenInGame( true );
	}

	OnRep_CustomizationData();
	
	if( HasValidDecoratorClass )
	{
		CreateAttachmentPointsFromComponents( mAttachmentPoints, this );
	}
	if ( ShouldBeConsideredForBase() )
	{
		worldSettings->GetProximitySubsystem()->RegisterFactoryBuildingToProximitySystem( GetActorLocation(), GetConsideredForBaseWeight() );
	}
	mNumPowerConnectionsOnPlay = GetNumPowerConnections();
}

void AFGBuildable::EndPlay( const EEndPlayReason::Type endPlayReason )
{
	Super::EndPlay( endPlayReason );

	// Lightweight temporaries early out here
	if( ShouldConvertToLightweight() )
	{
		if( mBlueprintProxy )
		{
			mBlueprintProxy->UnregisterBuildable( this );
		}
		return;
	}

	if( endPlayReason == EEndPlayReason::Destroyed )
	{
		// Destroy handles
		if(mPoolHandles.Num() > 0)
		{
			FFGBackgroundThread::RemoveHandles( mPoolHandles, GetActorLocation(), GetWorld() );

			mPoolHandles.Empty();
			mRegisteredWithBackgroundThread = false;
		}

		// Remove all lightweight instances owned by this buildable
		Internal_CallRemoveInstances();

		// We need to use replicated bool property instead of checking for valid blueprint designer, as it might not have been replicated yet.
		if( !mReplicatedBuiltInsideBlueprintDesigner && !mHasBeenRemovedFromSubsystem)
		{
			AFGBuildableSubsystem::Get( GetWorld() )->RemoveBuildable( this );
		}
		else if ( mBlueprintDesigner )
		{
			mBlueprintDesigner->OnBuildableDismantledInsideDesigner( this );
		}

		// Unregister ourselves from the blueprint proxy.
		if( IsValid( mBlueprintProxy ) )
		{
			mBlueprintProxy->UnregisterBuildable( this );
		}

		// Remove from proximity system.
		if ( ShouldBeConsideredForBase() )
		{
			AFGProximitySubsystem::StaticRemoveFactoryBuildingToProximitySystem( this, GetConsideredForBaseWeight() );
		}
	}
}

void AFGBuildable::Serialize( FArchive& ar )
{
	// Make sure all buildings use the custom version, so we get it properly written into archives
	ar.UsingCustomVersion( FFactoryGameCustomVersion::GUID );

	Super::Serialize( ar );
}

void AFGBuildable::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITOR
	// All the migrations should only run on blueprint instances of this type
	if ( HasAnyFlags( RF_ClassDefaultObject | RF_ArchetypeObject ) )
	{
		// Legacy archetype variant of sparse data object needs to be moved to package root and have public and archetype flags cleared from it
		if ( mBuildableSparseDataEditorObject_DEPRECATED )
		{
			mBuildableSparseDataCDO = mBuildableSparseDataEditorObject_DEPRECATED;
			mBuildableSparseDataCDO->ClearFlags( RF_Public | RF_ArchetypeObject );
			mBuildableSparseDataCDO->Rename( nullptr, GetPackage(), REN_DoNotDirty | REN_NonTransactional | REN_DontCreateRedirectors | REN_ForceNoResetLoaders );
			
			mBuildableSparseDataEditorObject_DEPRECATED = nullptr;
		}

		// Legacy archetype variant of sparse data object needs to be moved to package root and have public and archetype flags cleared from it
		if ( mInstanceData_DEPRECATED )
		{
			mInstanceDataCDO = mInstanceData_DEPRECATED;
			mInstanceDataCDO->ClearFlags( RF_Public | RF_ArchetypeObject );
			mInstanceDataCDO->Rename( nullptr, GetPackage(), REN_DoNotDirty | REN_NonTransactional | REN_DontCreateRedirectors | REN_ForceNoResetLoaders );
			
			mInstanceData_DEPRECATED = nullptr;
		}

		// Migrate alien overclocking data into the sparse data object
		if ( mBuildableSparseDataCDO && !mBuildableSparseDataCDO->bMigratedOldAlienOverclockingData )
		{
			mBuildableSparseDataCDO->AlienOverClockingZOffset = mAlienOverClockingZOffset_DEPRECATED;
			mBuildableSparseDataCDO->AlienOverClockingAttenuationScalingFactor = mAlienOverClockingAttenuationScalingFactor_DEPRECATED;
			mBuildableSparseDataCDO->AlienOverClockingVolumeDB_RTPC = mAlienOverClockingVolumeDB_RTPC_DEPRECATED;
			mBuildableSparseDataCDO->AlienOverClockingHighpass_RTPC = mAlienOverClockingHighpass_RTPC_DEPRECATED;
			mBuildableSparseDataCDO->AlienOverClockingPitch_RTPC = mAlienOverClockingPitch_RTPC_DEPRECATED;

			// Mark the data as migrated now
			mBuildableSparseDataCDO->bMigratedOldAlienOverclockingData = true;
		}

		// TODO @Nick: This needs to be cleaned up, will look into it in the near future
		ForceUpdateCustomizerMaterialToRecipeMapping();
	}
#endif
}

TSubclassOf< class UFGItemDescriptor > AFGBuildable::GetBuiltWithDescriptor() const
{
	if( mBuiltWithRecipe )
	{
		auto products = UFGRecipe::GetProducts( mBuiltWithRecipe );
		fgcheck( products.Num() );
		return products[ 0 ].ItemClass;
	}

	return nullptr;
}

void AFGBuildable::OnConstruction( const FTransform& transform )
{
	Super::OnConstruction( transform );

	/**
	* Overridden to update and verify the defaults in the editor.
	* This enables us to give blueprint designers an error message when they've configured something wrong.
	* And if they ignore the warnings the game will probably crash.
	*/

	// TODO why?
	// Only set this when running in the game
	if( UFGBlueprintFunctionLibrary::IsGameWorld( this ) )
	{
		mFactoryTickFunction.bCanEverTick |= mHasBlueprintFactoryTick;
	}

#if WITH_EDITOR && 0
	if( true )
	{
		FString message;
		if( !VerifyDefaults( message ) )
		{
			//VISUAL_LOG( LogFactory, Warning, TEXT( "%s: %s" ), *GetName(), *message );
		}
	}
#endif
	
	// Add tag if we do affect the occlusion system
	if( DoesAffectOcclusionSystem() )
	{
		Tags.AddUnique( FName("RainOcclusion") );
	}

#if WITH_EDITOR
	// Spawn editor visualization for the buildable in Editor worlds
	if (GetWorld()->WorldType == EWorldType::Editor || GetWorld()->WorldType == EWorldType::EditorPreview)
	{
		CreateEditorVisualization();
	}
#endif
}

#if WITH_EDITOR

bool AFGBuildable::CanVisualizeBlueprintAsset() const
{
	// We need to render the thumbnail if we have abstract instances that can be captured, even if the buildable itself has no components.
	return DoesContainLightweightInstances_Native();
}

void AFGBuildable::CreateEditorVisualization()
{
	// Cleanup old visualization components
	for (UActorComponent* OldVisualizationComponent : VisualizationComponents)
	{
		if (IsValid(OldVisualizationComponent))
		{
			OldVisualizationComponent->DestroyComponent();
		}
	}
	VisualizationComponents.Empty();

	// Apply default factory customization data to the mesh
	FResolvedFactoryCustomizationData CustomizationData;
	CustomizationData.bHasPower = true;

	// Swatch group takes priority over the default swatch override if it is set
	if (mSwatchGroup)
	{
		CustomizationData.ApplyDefaultSwatchForSwatchGroup(mSwatchGroup);
	}
	// If this building has a default swatch override, apply it as color to get a more natural color
	else if (mDefaultSwatchCustomizationOverride)
	{
		CustomizationData.ApplySwatch(mDefaultSwatchCustomizationOverride);
	}

	// Apply default colors from buildable subsystem
	CustomizationData.ResolveDefaultColorForColorSlot();

	// We check the data on the default object to avoid issues with BP reinstancing, that will reset the mInstanceDataCDO pointer on the class
	const AFGBuildable* ClassDefaultObject = CastChecked<AFGBuildable>(GetClass()->ClassDefaultObject);

	// Abstract Instances visualization
	if (RootComponent != nullptr && ClassDefaultObject->DoesContainLightweightInstances_Native())
	{
		for (const FInstanceData& InstanceData : ClassDefaultObject->GetActorLightweightInstanceData_Implementation())
		{
			if (InstanceData.StaticMesh == nullptr) return;

			// Create visualization static mesh component
			UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this, NAME_None, RF_Transient);
			StaticMeshComponent->SetIsVisualizationComponent(true);
			StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			// Populate static mesh component with the data from the instance
			StaticMeshComponent->SetRelativeTransform(InstanceData.RelativeTransform);
			StaticMeshComponent->SetStaticMesh(InstanceData.StaticMesh);
			StaticMeshComponent->SetCastShadow(InstanceData.bCastShadows);
			StaticMeshComponent->OverrideMaterials = InstanceData.OverridenMaterials;

			// Populate primitive data with the defaults if they are provided
			if (!InstanceData.DefaultPerInstanceCustomData.IsEmpty())
			{
				for (int32 DataIndex = 0; DataIndex < InstanceData.DefaultPerInstanceCustomData.Num(); DataIndex++)
				{
					StaticMeshComponent->SetDefaultCustomPrimitiveDataFloat(DataIndex, InstanceData.DefaultPerInstanceCustomData[DataIndex]);
				}
			}
			
			// Apply color to the mesh
			CustomizationData.ApplyToMeshComponent(StaticMeshComponent);

			// Register the static mesh component
			StaticMeshComponent->SetupAttachment(RootComponent);
			StaticMeshComponent->RegisterComponent();
			
			VisualizationComponents.Add(StaticMeshComponent);
		}
	}

	// Apply default customization data to any mesh components on the buildable
	for (UMeshComponent* MeshComponent : TInlineComponentArray<UMeshComponent*>(this))
	{
		// We do not need to check for UFGColoredInstancedMeshProxy::IsInstanced here because they should never be instanced in Editor and EditorPreview worlds
		CustomizationData.ApplyToMeshComponent(MeshComponent);
	}
}

#endif

#if WITH_EDITOR
void AFGBuildable::CheckForErrors()
{
	Super::CheckForErrors();

	// Don't check for level related errors if we are template objects
	if( !IsTemplate() )
	{
		if( !IsInPersistentLevel( true ) )
		{
			FMessageLog( "MapCheck" ).Error()
				->AddToken( FUObjectToken::Create( this ) )
				->AddToken( FTextToken::Create( FText::FromString( TEXT( "Buildable not placed in a persistant level" ) ) ) );
		}
	}
}
#endif

uint8 AFGBuildable::MaxNumGrab( float delta ) const
{
	return 0;
}

uint8 AFGBuildable::EstimatedMaxNumGrab_Threadsafe( float estimatedDeltaTime ) const
{
	return 0;
}

bool AFGBuildable::VerifyDefaults( FString& out_message )
{
	// Check for legacy clearance components
	for( auto component : TInlineComponentArray<UBoxComponent*>{ this } )
	{		
		if( component->GetName() == TEXT("Clearance") )
		{
			out_message = FString::Printf( TEXT( "Legacy clearance component found! Replace with ClearanceData!" ) );
			return false;
		}
	}

	FString message;
	if( !CheckFactoryConnectionComponents( message ) )
	{
		out_message = FString::Printf( TEXT( "Checking of factory connection components failed: %s" ), *message );
		return false;
	}

	return true;
}

int32 AFGBuildable::GetCostMultiplierForLength( float totalLength, float costSegmentLength )
{
	if( costSegmentLength > KINDA_SMALL_NUMBER )
	{
		return FMath::Max( 1, FMath::RoundToInt( totalLength / costSegmentLength ) );
	}

	return 1;
}

TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > AFGBuildable::GetDefaultSwatchCustomizationOverride( UObject* worldContext )
{
	// First check if the game state has a swatch group for this buildable
	TSubclassOf<UFGFactoryCustomizationDescriptor_Swatch> swatch;

	// [ZolotukhinN:24/04/2024] Only check current swatch based on the swatch group if the buildable has a valid swatch group assigned (power poles do not, for example)
	if ( mSwatchGroup )
	{
		if ( AFGGameState* gameState = worldContext->GetWorld()->GetGameState<AFGGameState>() )
		{
			swatch = gameState->GetCurrentSwatchForSwatchGroup( mSwatchGroup );
		}
	}

	if( swatch == nullptr )
	{
		if( mDefaultSwatchCustomizationOverride )
		{
			swatch = mDefaultSwatchCustomizationOverride;
		}
		else
		{
			if( AFGBuildableSubsystem* buildableSubsystem = AFGBuildableSubsystem::Get( worldContext) )
			{
				TSubclassOf< UFGFactoryCustomizationCollection > swatchCollection = buildableSubsystem->GetCollectionForCustomizationClass( UFGFactoryCustomizationDescriptor_Swatch::StaticClass() );
				if( swatchCollection )
				{
					UFGFactoryCustomizationCollection* collectionObj = swatchCollection->GetDefaultObject< UFGFactoryCustomizationCollection >();
					TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > swatchDesc = *collectionObj->GetDefaultCustomization();
					swatch = swatchDesc;
				}
			}
		}
	}

	return swatch;
}

bool AFGBuildable::CheckFactoryConnectionComponents( FString& out_message )
{
	/**
	* Here we check and verify the naming of the factory connections.
	* Valid names are:
	* ({connector}){direction}{id}
	*
	* E.g:
	* Input5
	* Any1
	* PipeOutput4
	* ConveyorInput2
	* SnapOnly0
	*/
	TStaticArray< FString, 2 > connectors;
	connectors[ (uint8 )EFactoryConnectionConnector::FCC_CONVEYOR ] = FString( "Conveyor" );
	connectors[ (uint8 )EFactoryConnectionConnector::FCC_PIPE ] = FString( "Pipe" );

	TStaticArray< FString, 4 > directions;
	directions[ (uint8 )EFactoryConnectionDirection::FCD_INPUT ] = FString( "Input" );
	directions[ (uint8 )EFactoryConnectionDirection::FCD_OUTPUT ] = FString( "Output" );
	directions[ (uint8 )EFactoryConnectionDirection::FCD_ANY ] = FString( "Any" );
	directions[ (uint8 )EFactoryConnectionDirection::FCD_SNAP_ONLY ] = FString( "SnapOnly" );

	FOR_EACH_FACTORY_INLINE_COMPONENTS( connection )
	{
		FString name = connection->GetName();
		FString connector = connectors[ (uint8 )connection->GetConnector() ];
		FString direction = directions[ (uint8 )connection->GetDirection() ];

		// Try remove the (optional) prefix.
		name.RemoveFromStart( connector );

		// Try remove the direction.
		if( !name.RemoveFromStart( direction ) )
		{
			out_message = FString::Printf( TEXT( "Error: '%s' is not a valid name for this factory connection, the proper name is '(%s)%s{id}'" ),
										   *connection->GetName(),
										   *connector,
										   *direction );
			return false;
		}

		// Now we should be left with a number.
		if( !name.IsNumeric() )
		{
			out_message = FString::Printf( TEXT( "Error: '%s' is not a valid name for this factory connection, the proper name is '(%s)%s{id}'" ),
										   *connection->GetName(),
										   *connector,
										   *direction );
			return false;
		}
	}

	return true;
}

void AFGBuildable::TurnOffAndDestroy()
{
	if( HasAuthority() )
	{
		// Give the client time to play any effects. This is overridden if a dismantle effect is played.
		SetLifeSpan( DISMANTLE_LIFE_SPAN );

		SetReplicates( true );
	}
}

bool AFGBuildable::GetPoolHandleInitialState() const
{
	return true;
}

bool AFGBuildable::CreateDecoratorSignificantComponents( AFGPlayerController* controller )
{
	QUICK_SCOPE_CYCLE_COUNTER( STAT_CreateDecoratorSignificantComponents )

	if ( controller )
	{
		mActiveSignificantControllers.AddUnique( controller );
	}

	// If we have no component, try to make them.
	if ( mGeneratedSignificantComponents.Num() == 0 )
	{
		TArray< USceneComponent* > templateComponents = AFGDecorationTemplate::GetSignificantComponentsFromSubclass( mDecoratorClass );

		for ( USceneComponent* component: templateComponents )
		{
			USceneComponent* newComponent = AFGDecorationTemplate::SpawnComponentFromTemplate( this, component, EComponentMobility::Static );
			
			ConfigureDynamicDecoratorComponent( newComponent );
			
			mGeneratedSignificantComponents.Add( newComponent );
		}
	}

	return true;
}

void AFGBuildable::ConfigureDynamicDecoratorComponent( USceneComponent* newComponent )
{
}

void AFGBuildable::TryRemoveDecoratorSignificantComponents( AFGPlayerController* controller )
{	
	mActiveSignificantControllers.Remove( controller );
	
	if( mActiveSignificantControllers.Num() == 0 )
	{
		RemoveDecoratorSignificantComponents();
	}
}

void AFGBuildable::RemoveDecoratorSignificantComponents( )
{	
	for	( USceneComponent* Component: mGeneratedSignificantComponents )
	{
		if ( IsValid(this) && IsValid( Component ) )
		{
			Component->DestroyComponent( false );
		}
	}

	mGeneratedSignificantComponents.Empty();
}

void AFGBuildable::SetCustomizationData_Native( const FFactoryCustomizationData& customizationData, bool skipCombine /*false*/ )
{
	SCOPE_CYCLE_COUNTER( STAT_BuildableSetCustomizationData )
	if( customizationData.SkinDesc != mCustomizationData.SkinDesc )
	{
		mCustomizationData.NeedsSkinUpdate = true;
	}

	AFGGameState* gameState = GetWorld()->GetGameState< AFGGameState >();
	if( !skipCombine )
	{
		mCustomizationData.InlineCombine( customizationData );
	}
	else
	{
		mCustomizationData = customizationData;
	}
	mCustomizationData.Initialize( gameState );

	// The color slot is the ID of the swatch descriptor.
	int32 swatchID = UFGBlueprintFunctionLibrary::GetIDForCustomizationDesc( customizationData.SwatchDesc );
	if( swatchID != mColorSlot )
	{
		mColorSlot = swatchID > 0 && swatchID <= UINT8_MAX ? swatchID : 0;	  // Default to 0 if the swatch has an invalid ID
		MARK_PROPERTY_DIRTY_FROM_NAME( AFGBuildable, mColorSlot, this );
	}
	MARK_PROPERTY_DIRTY_FROM_NAME( AFGBuildable, mCustomizationData, this );
	
	ApplyCustomizationData_Native( mCustomizationData );
	mCustomizationData.NeedsSkinUpdate = false;

	// Tell the blueprint designer that we have changed our state and might need to update our cost
	if ( IsValid( mBlueprintDesigner ) )
	{
		mBlueprintDesigner->OnBuildableChangedInsideDesigner( this );
	}

	if( !mIsLightweightTemporary )
	{
		ForceNetUpdate();
	}

	if( ShouldConvertToLightweight() )
	{
		if( mIsLightweightTemporary && mHasTemporaryModifiedItsCustomiazationData )
		{
			AFGLightweightBuildableSubsystem* lightweightSubsystem = AFGLightweightBuildableSubsystem::Get( GetWorld() );
			lightweightSubsystem->CopyCustomizationDataFromTemporaryToInstance( this );
		}
	}
}

void AFGBuildable::SetCustomizationDataLightweightNoApply( const FFactoryCustomizationData& customizationData, bool skipCombine )
{
	AFGGameState* gameState = GetWorld()->GetGameState< AFGGameState >();
	if( !skipCombine )
	{
		mCustomizationData.InlineCombine( customizationData );
	}
	else
	{
		mCustomizationData = customizationData;
	}
	mCustomizationData.Initialize( gameState );

	// The color slot is the ID of the swatch descriptor.
	int32 swatchID = UFGBlueprintFunctionLibrary::GetIDForCustomizationDesc( customizationData.SwatchDesc );
	if( swatchID != mColorSlot )
	{
		mColorSlot = swatchID > 0 && swatchID <= UINT8_MAX ? swatchID : 0;	  // Default to 0 if the swatch has an invalid ID
		MARK_PROPERTY_DIRTY_FROM_NAME( AFGBuildable, mColorSlot, this );
	}
	MARK_PROPERTY_DIRTY_FROM_NAME( AFGBuildable, mCustomizationData, this );
}

void AFGBuildable::SetCustomizationData_Implementation( const FFactoryCustomizationData& customizationData )
{
	SetCustomizationData_Native( customizationData );
}

void AFGBuildable::ApplyCustomizationData_Native( const FFactoryCustomizationData& customizationData )
{
	SCOPE_CYCLE_COUNTER( STAT_BuildableApplyCustomizationData )
	if( customizationData.IsInitialized() == false )
	{
		UE_LOG( LogGame, Warning, TEXT( "IFGColorInterface::ApplyCustomizationData was called with uninitialized customization data. Intialize prior to triggering this call!" ) );
		return;
	}

	if( customizationData.NeedsSkinUpdate )
	{
		ApplySkinData( customizationData.SkinDesc );
	}
	mCustomizationData.NeedsSkinUpdate = false;

	// Apply color data as PrimitiveData
	ApplyMeshPrimitiveData( customizationData );
}

TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > AFGBuildable::GetActiveSkin_Native()
{
	return mCustomizationData.SkinDesc;
}

TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > AFGBuildable::GetActiveSkin_Implementation()
{
	return GetActiveSkin_Native();
}

bool AFGBuildable::GetCanBeColored_Native()
{
	return mAllowColoring;
}

void AFGBuildable::ApplyCustomizationData_Implementation( const FFactoryCustomizationData& customizationData )
{
	ApplyCustomizationData_Native( customizationData );
}

bool AFGBuildable::GetCanBeColored_Implementation()
{
	return GetCanBeColored_Native();
}

bool AFGBuildable::GetCanBePatterned_Implementation()
{
	return mAllowPatterning;
}

void AFGBuildable::StartIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter, bool isValid )
{
	if( mIsDismantled )
	{
		return;
	}
	bool showOutline = true;

	AFGPlayerController* pc = Cast<AFGPlayerController>( byCharacter->GetController() );
	if( pc )
	{
		AFGHUD* hud = Cast<AFGHUD>( pc->GetHUD() );
		if( hud )
		{
			showOutline = !hud->GetPumpiMode();
		}
	}

	if( showOutline )
	{
		if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
		{
			outline->ShowOutline( this, isValid ? EOutlineColor::OC_HOLOGRAMLINE : EOutlineColor::OC_RED );
		}
	}
}

void AFGBuildable::StopIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter )
{	
	if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
    {
    	outline->HideOutline( this );
    }
}

void AFGBuildable::OnRep_CustomizationData()
{
	// On Client this onRep may be triggered before the GameState is valid. If so we don't want to do anything since we lack the color data
	if( !HasAuthority() )
	{
		if( AFGGameState* gameState = GetWorld()->GetGameState< AFGGameState >() )
		{
			// Data on clients needs to be force initialized as it is not replicated
			mCustomizationData.Initialize( GetWorld()->GetGameState< AFGGameState >() );
		}
		else
		{
			return;
		}
	}

	ApplyCustomizationData_Native( mCustomizationData );

	Native_OnMaterialInstancesUpdated();
}

bool AFGBuildable::DoesContainLightweightInstances_Native() const
{
	if ( mCanContainLightweightInstances && mInstanceDataCDO != nullptr )
	{
		return true;
	}
	// We have dynamic lightweight instances for factory legs if legs exist, even if we do not have static instance data for this buildable
	const UFGFactoryLegsComponent* factoryLegsComponent = FindComponentByClass<UFGFactoryLegsComponent>();
	if ( factoryLegsComponent != nullptr && factoryLegsComponent->HasValidLegs() )
	{
		return true;
	}
	return false;
}

void AFGBuildable::SetupInstances_Implementation( bool bSpawnHidden )
{
	SetupInstances_Native( bSpawnHidden );
}

void AFGBuildable::AddDynamicInstanceHandle( const FInstanceOwnerHandlePtr& NewInstanceHandle )
{
	// Add to the shared list and to the dynamic list
	mInstanceHandles.Add( NewInstanceHandle );
	mDynamicInstanceHandles.Add( NewInstanceHandle );
}

void AFGBuildable::AddDynamicInstanceHandles( const TArray<FInstanceOwnerHandlePtr>& NewInstanceHandles )
{
	// Add to the shared list and to the dynamic list
	mInstanceHandles.Append( NewInstanceHandles );
	mDynamicInstanceHandles.Append( NewInstanceHandles );
}

void AFGBuildable::CallSetupInstances( bool bInitializeHidden )
{
	if ( !mLightweightInstancesRegistered )
	{
		mLightweightInstancesRegistered = true;
			
		/* Only call native to avoid blueprint VM */
		if( !mHasSetupInstances )
		{
			SetupInstances_Native( bInitializeHidden );
			return;
		}

		SetupInstances( bInitializeHidden );
	}
}

void AFGBuildable::Internal_CallRemoveInstances()
{
	RemoveInstances();
	mLightweightInstancesRegistered = false;
}

void AFGBuildable::SetupInstances_Native( bool bSpawnHidden )
{
	QUICK_SCOPE_CYCLE_COUNTER( AFGBuildable_SetupInstances_Native );
	
	if( DoesContainLightweightInstances_Native() && !mIsDismantled )
	{
		// Create abstract instances from static data derived from FInstanceData object for the buildable
		const TArray<FInstanceData> StaticInstanceData = Execute_GetActorLightweightInstanceData(this);
		for	( const FInstanceData& InstanceData : StaticInstanceData)
		{
			FInstanceOwnerHandlePtr Handle;
				AAbstractInstanceManager::SetInstanceFromDataStatic(this, GetActorTransform(), InstanceData,Handle, bSpawnHidden );
				mInstanceHandles.Add( Handle ); 
			}

		// Generate instances for factory legs if we have them
		if ( UFGFactoryLegsComponent* factoryLegsComponent = FindComponentByClass<UFGFactoryLegsComponent>() )
		{
			TArray<FInstanceData> legsInstanceData;
			factoryLegsComponent->CreateLegInstances( legsInstanceData );

			for	( const FInstanceData& instanceData : legsInstanceData )
			{
				FInstanceOwnerHandlePtr Handle;
				AAbstractInstanceManager::SetInstanceFromDataStatic(this, GetActorTransform(), instanceData, Handle, bSpawnHidden );

				// Factory legs instances are considered dynamic, because they do not come from GetActorLightweightInstanceData
				AddDynamicInstanceHandle( Handle );
			}
		}
	}
}

void AFGBuildable::ToggleInstanceVisibility( bool bNewState )
{
	for ( const FInstanceOwnerHandlePtr& Handle : mInstanceHandles )
	{
		Handle->SetInstanceVisibility( bNewState, true );
	}
}

void AFGBuildable::SetInsideBlueprintDesigner( AFGBuildableBlueprintDesigner* designer )
{
	// This function should only be called before BeginPlay is dispatched, as it will result in a discrepancy between the state of the buildable if it's called beyond that
	fgcheckf( HasAuthority() && !HasActorBegunPlay(), TEXT("SetInsideBlueprintDesigner should only be called on the Server before BeginPlay is dispatched!") );

	mBlueprintDesigner = designer;
	mReplicatedBuiltInsideBlueprintDesigner = IsValid( designer );
}

AFGBuildableBlueprintDesigner* AFGBuildable::GetBlueprintDesigner() const
{
	return mBlueprintDesigner;
}

void AFGBuildable::RemoveInstances_Implementation()
{
	RemoveInstances_Native();
}

void AFGBuildable::RemoveInstances_Native()
{
	if( mInstanceHandles.Num() > 0 )
	{
		AAbstractInstanceManager::RemoveInstances( this, mInstanceHandles );
		mInstanceHandles.Empty();
		mDynamicInstanceHandles.Empty();
	}
}

bool AFGBuildable::HandleLightweightAddition()
{
	if( mIsLightweightTemporary )
	{
		if( !mBlueprintBuildEffectIsPlaying )
		{
			SetReplicates( false );
		}
		
		if( mBlueprintProxy )
		{
			mBlueprintProxy->RegisterBuildable( this );
		}
		return true;
	}

	if( !IsValid( mBlueprintDesigner ) )
	{
		if( mCustomizationData.SwatchDesc == nullptr )
		{
			mCustomizationData.SwatchDesc = GetDefaultSwatchCustomizationOverride( GetWorld() );
		}
		
		AFGLightweightBuildableSubsystem* lightweightSubsystem = AFGLightweightBuildableSubsystem::Get( GetWorld() );
		mRuntimeDataIndex = lightweightSubsystem->AddFromBuildable( this, mBuildEffectInstignator, mBlueprintProxy );
		
		if( mBlueprintProxy && mRuntimeDataIndex != INDEX_NONE )
		{
			// Register not as a buildable but as a class and runtime index
			mBlueprintProxy->RegisterLightweightInstance( GetClass(), mRuntimeDataIndex );
			// Unregister in case it was already added
			mBlueprintProxy->UnregisterBuildable( this );
		}
			
		// Flags so destruction doesn't imply removal
		mIsLightweightTemporary = true;
		mIsStaleLightweightTemporary = true;
		Destroy();
		ForceNetUpdate();

		if( mRuntimeDataIndex != INDEX_NONE )
		{
			return true;
		}
	}

	return true;
}

void AFGBuildable::ApplyLightweightTypeSpecificData( const struct FFGDynamicStruct& typeSpecificData )
{
}

FFGDynamicStruct AFGBuildable::GetLightweightTypeSpecificData() const
{
	// Most lightweights do not have any type specific data
	return FFGDynamicStruct();
}

void AFGBuildable::CreateLightweightBuildableInstanceData( const struct FFGDynamicStruct& typeSpecificData, TArray<FInstanceData>& outLightweightInstanceData ) const
{
	// Fetch the data from the lightweight instance data on the CDO
	if ( const UAbstractInstanceDataObject* lightweightInstanceData = GetLightweightInstanceData() )
	{
		outLightweightInstanceData = lightweightInstanceData->GetInstanceData();
	}
}

void AFGBuildable::ForceUpdateCustomizerMaterialToRecipeMapping( bool bTryToSave )
{
	// TODO @Ben modding support, make this work runtime.
#if WITH_EDITOR

	UE_LOG( LogTemp, Log, TEXT("[%s] alts: %d"), *GetName(), mAlternativeMaterialRecipes.Num() );
	
	if( mAlternativeMaterialRecipes.Num() > 0 )
	{
		for	( int32 i = 0; i < mAlternativeMaterialRecipes.Num(); i++ )
		{
			UClass* ResolvedMaterial = nullptr;
			UClass* ResolvedRecipe = nullptr;

			if (auto GetMaterial = mAlternativeMaterialRecipes[i].mMaterial.Get())
			{
				ResolvedMaterial = GetMaterial;
			}
			else if ( auto LoadedMaterial = mAlternativeMaterialRecipes[i].mMaterial.LoadSynchronous() )
			{
				ResolvedMaterial = LoadedMaterial;
			}

			if (auto GetRecipe = mAlternativeMaterialRecipes[i].mRecipe.Get())
			{
				ResolvedRecipe = GetRecipe;
			}
			else if (auto LoadedRecipe = mAlternativeMaterialRecipes[i].mRecipe.LoadSynchronous())
			{
				ResolvedRecipe = LoadedRecipe;
			}

			if( ResolvedMaterial && ResolvedRecipe )
			{
				if ( UFGFactoryCustomizationDescriptor_Material* MaterialDesc = GetMutableDefault<UFGFactoryCustomizationDescriptor_Material >( ResolvedMaterial ) )
				{
					const bool bDidModifyValues = MaterialDesc->AddType( this->GetClass(),  ResolvedRecipe );

					UE_LOG(LogTemp,Log,TEXT("[%s] Adding %s to %s"),
						*GetName(),
						*ResolvedMaterial->GetName(),
						*ResolvedRecipe->GetName() )

#if WITH_EDITOR
					if( bTryToSave && bDidModifyValues )
					{
						UPackage* Package = ResolvedMaterial->GetPackage();
						Package->Modify(true);
						Package->MarkPackageDirty();
					
						TArray<UPackage*> PackageToSave;
						PackageToSave.Add( Package );
						
						FEditorFileUtils::PromptForCheckoutAndSave(PackageToSave, true, true);
						ISourceControlModule::Get().QueueStatusUpdate(ResolvedMaterial->GetPackage());
					}
#endif
				}
			}
		}
	}
#endif
}

void AFGBuildable::ApplySkinData( TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc )
{
	SCOPE_CYCLE_COUNTER( STAT_BuildableApplySkinData )
	if( mFactorySkinClass == nullptr )
	{
		return;
	}

	TMap< TSubclassOf< UFGFactoryCustomizationDescriptor_Skin >, FFactorySkinComponentGroup > actorSkinData;
	UFGFactorySkinActorData::GetSkinComponentDataForSkinActorData( mFactorySkinClass, actorSkinData );

	// Make sure this buildable has a mampping for the passed skinDesc
	if( newSkinDesc != nullptr && !actorSkinData.Contains( newSkinDesc ) )
	{
		UE_LOG( LogGame, Warning, TEXT( "Failed to apply skin desc: %s NOT FOUND in buildable %s" ), *GetPathNameSafe( newSkinDesc ), *GetFullName() );
		return;
	}
	
	TArray< UFGColoredInstanceMeshProxy* > proxyMeshes;
	GetComponents( proxyMeshes );

	// Uninstance the proxies (this will cause them to unregister and remove from their owning instance manager)
	for( UFGColoredInstanceMeshProxy* proxy : proxyMeshes )
	{
		proxy->SetInstanced( false );
	}

	FFactorySkinComponentGroup* groupData = nullptr;
	FFactorySkinComponentGroup defaultGroup;

	// For removal we need to build the "skin" from scratch based of the default object
	// Another way would be to have a "none" skin but this would require a lot of set up for every buildable that has skins
	if( newSkinDesc == nullptr )
	{
		AFGBuildable* cdo = GetClass()->GetDefaultObject< AFGBuildable >();
		TArray< UMeshComponent* > otherMeshComponents;
		UFGBlueprintFunctionLibrary::GetAllMeshComponentsInClass( GetClass(), otherMeshComponents );

		int32 idx = INDEX_NONE;
		
		for( UMeshComponent* meshComp : otherMeshComponents )
		{
			FFactorySkinComponentData data;
			FString compNameString = meshComp->GetFName().ToString();
			const FString genStrEnd = "_GEN_VARIABLE";
			int32 idxOfGen = compNameString.Find( genStrEnd );

			if( idxOfGen != INDEX_NONE )
			{
				compNameString.RemoveAt( idxOfGen, genStrEnd.Len() );
			}
			
			FName compName = FName( *compNameString );
			data.ComponentName = compName;
			int32 matIdx = 0;
			for( UMaterialInterface* matInstance : meshComp->GetMaterials() )
			{
				data.IndexToMaterialData.Emplace( FIndexToMaterialData( matIdx, matInstance )  );
				matIdx++;
			}
			defaultGroup.mComponentData.Emplace( data );
		}

		groupData = &defaultGroup;
	}
	else
	{
		groupData = &actorSkinData[ newSkinDesc ];
	}

	// Apply the override materials
	TArray< UMeshComponent* > allMeshComponents;
	GetComponents( allMeshComponents );

	UFGBlueprintFunctionLibrary::ApplySkinDataToMeshArray( allMeshComponents, *groupData );

	// Reinstance (with likely new instance manager)
	for( UFGColoredInstanceMeshProxy* proxy: proxyMeshes )
	{
		proxy->SetInstanced( true );
	}

	// BP Native Notify
	OnSkinCustomizationApplied_Implementation( newSkinDesc );
}

void AFGBuildable::ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData )
{
	int32 fallbackSlot = mCustomizationData.ColorSlot;
	UFGBlueprintFunctionLibrary::ApplyCustomizationPrimitiveData( this, customizationData, fallbackSlot, nullptr, mIsLightweightTemporary );
}

bool AFGBuildable::HasOverrideForHologramInClass( TSubclassOf<UFGItemDescriptor> OwnerBuilding, TSubclassOf< UFGItemDescriptor > HologramDescriptor )
{
	if(OwnerBuilding && OwnerBuilding->IsChildOf<UFGBuildDescriptor>())
	{
		if( const TSubclassOf<AFGBuildable> buildClass = UFGBuildingDescriptor::GetBuildableClass( *OwnerBuilding ) )
		{
			const AFGBuildable* cdo = buildClass.GetDefaultObject();
			return cdo && cdo->HasOverrideForHologram( HologramDescriptor );
		}
	}

	return false;
}

void AFGBuildable::ApplyHasPowerCustomData()
{
	mCustomizationData.HasPower = GetEmissivePower() > 0.0f ? true : false;
	mCustomizationData.UpdateHasPowerData();

	// Update meshes with prim data
	TInlineComponentArray< UMeshComponent* > smesh( this );
	for( UMeshComponent* comp: smesh )
	{
		if( const UFGColoredInstanceMeshProxy* Proxy = Cast<UFGColoredInstanceMeshProxy>(comp) )
		{
			// We should only skip indicators OR instanced proxies.
			if(Proxy->IsA(UFGProductionIndicatorInstanceComponent::StaticClass()) || !Proxy->ShouldBlockInstancing())
			{
				continue;		
			}
		}

		{
			using namespace BuildableColorConstants;
			comp->SetCustomPrimitiveDataFloat( (uint8)EColorDataIndices::CDI_HasPower, mCustomizationData.HasPower );
		}
	}

	// Update proxies with PIC data
	TInlineComponentArray< UFGColoredInstanceMeshProxy* > proxies( this );
	for( UFGColoredInstanceMeshProxy* proxy : proxies )
	{
		if( Cast<UFGProductionIndicatorInstanceComponent>(proxy) )
		{
			continue;
		}
		
		proxy->SetHasPowerData( mCustomizationData.HasPower );
	}
}

void AFGBuildable::OnRep_LightweightTransform()
{
	// nothing.
}

void AFGBuildable::RegisterWithBackgroundThread()
{
	if ( !mRegisteredWithBackgroundThread )
	{
		FFGBackgroundThread::RegisterActor( this );
		mRegisteredWithBackgroundThread = true;
	}
}

#if WITH_EDITOR
void AFGBuildable::DebugDrawOcclusionBoxes()
{
	for	( const FBox& Box : mOcclusionBoxInfo )
	{
		const auto& T = GetActorTransform();

		FVector Center = T.TransformPosition( Box.GetCenter() );
		FVector Extents = Box.GetExtent();

		DrawDebugBox( GetWorld(), Center, Extents, FColor::Red,false, 10.f, 1, 10.f );
	}
}

void AFGBuildable::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );
	
	if ( HasAnyFlags( RF_ClassDefaultObject | RF_ArchetypeObject ) )
	{
		if( PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED( AFGBuildable, mAlternativeMaterialRecipes ) )
		{
			ForceUpdateCustomizerMaterialToRecipeMapping(true);		
		}
		
		// Newly created inline objects will be parented to the CDO and marked as RF_Public and RF_ArchetypeObject. We do not want either, since they are not instanced sub-objects, but are prefab data
		if( PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(AFGBuildable, mInstanceDataCDO) && mInstanceDataCDO )
		{
			mInstanceDataCDO->ClearFlags( RF_Public | RF_ArchetypeObject );
			mInstanceDataCDO->Rename( nullptr, GetPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders );
		}
		if ( PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(AFGBuildable, mBuildableSparseDataCDO) && mBuildableSparseDataCDO )
		{
			mBuildableSparseDataCDO->ClearFlags( RF_Public | RF_ArchetypeObject );
			mBuildableSparseDataCDO->Rename( nullptr, GetPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders );
		}
	}
}

void AFGBuildable::PostEditChangeChainProperty( FPropertyChangedChainEvent& PropertyChangedEvent )
{
	Super::PostEditChangeChainProperty( PropertyChangedEvent );
	if( PropertyChangedEvent.PropertyChain.GetActiveMemberNode()->GetValue()->GetFName() == GET_MEMBER_NAME_CHECKED( AFGBuildable, mAlternativeMaterialRecipes ) )
	{
		ForceUpdateCustomizerMaterialToRecipeMapping(true);		
	}
}
#endif

const TArray< UMeshComponent* >& AFGBuildable::GetMainMeshes()
{
#if !WITH_EDITOR //Don't used cached in editor, won't work if the mesh is renamed.
	if( mCachedMainMeshes.Num() <= 0 )
	{
#endif
		mCachedMainMeshes.Empty();
		for( auto component : TInlineComponentArray<UMeshComponent*>{ this } )
		{
			if( component->GetFName().ToString().Contains( MAIN_MESH_NAME ) )
			{
				mCachedMainMeshes.Add( component );
			}
		}
#if !WITH_EDITOR
	}
#endif

	return mCachedMainMeshes;
}

bool AFGBuildable::CanDismantle_Implementation() const
{
	// Do not allow dismantling integrated actors (e.g. actors that have a dismantle actor redirect, such as railroad platform track, hub sub-buildings, blueprint designer storage, etc)
	// while their owner buildable is not dismantled. Owner buildable of integrated buildables should always be dismantled first.
	const AFGBuildable* parentBuildable = Cast<AFGBuildable>( mParentBuildableActor );

	return !mIsDismantled && ( !IsValid( parentBuildable ) || parentBuildable->GetIsDismantled() );
}

FVector AFGBuildable::GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const
{
	FVector spawnLocation = GetActorLocation();

	FVector origin, extent;
	GetActorBounds( true, origin, extent );
	out_radius = FMath::Min( extent.X, extent.Y );

	return spawnLocation;
}

void AFGBuildable::PreUpgrade_Implementation()
{
}

void AFGBuildable::Upgrade_Implementation( AActor* newActor )
{
}

void AFGBuildable::Dismantle_Implementation()
{
	// Fixes duplication bug when dismantling
	if( mIsDismantled )
	{
		return;
	}

	mIsDismantled = true;

	if( APlayerController* pc = UGameplayStatics::GetPlayerController( GetWorld(), 0 ) )
	{
		if( AFGCharacterPlayer* byCharacter = Cast<AFGCharacterPlayer>( pc->GetPawn() ) )
		{
			SCOPE_CYCLE_COUNTER( STAT_ExecuteInterface_Buildable );
			IFGDismantleInterface::Execute_StopIsLookedAtForDismantle( this, byCharacter );
		}
	}

	// Empty all inventory components to prevent Race Condition Duplicate item exploits
	// NOTE: Prior to this call All Dismantled objects should have return their inventories to the dismantling player or to crates
	TInlineComponentArray< UFGInventoryComponent* > inventoryComponents( this );
	for( UFGInventoryComponent* component : inventoryComponents )
	{
		// Mark inventory that its buildable is dismantling to prevent players adding items into the inventory (effectively destroying the item)
		component->SetLocked( true );
		component->Empty();
	}

	ForceNetUpdate();

	// Clear all factory connections.
	TInlineComponentArray< UFGFactoryConnectionComponent* > factoryConnections;
	GetComponents( factoryConnections );
	for( auto factoryConnection : factoryConnections )
	{
		factoryConnection->ClearConnection();
	}

	// This is not done in PreUpgrade cause we want them refunded when dismantling,
	// this means buildings with power lines will have to bee reconnected manually by the player.
	// Turn off and destroy all power lines too.
	TInlineComponentArray< UFGCircuitConnectionComponent* > circuitConnections;
	GetComponents( circuitConnections );
	for( auto circuitConnection : circuitConnections )
	{
		TArray< AFGBuildableWire* > wires;
		circuitConnection->GetWires( wires );
		for( auto wire : wires )
		{
			SCOPE_CYCLE_COUNTER( STAT_ExecuteInterface_Buildable );
			// Recursively dismantle any wires so fx can be played.
			IFGDismantleInterface::Execute_Dismantle( wire );
		}
	}

	// Hide instances only if not a lightweight temporary. If so this will be handled by EndPlay and the LightweightSubsystem
	if( mIsLightweightTemporary )
	{
		SetBlockCleanupOfTemporary( false );
		// The lightweight buildable subsystem needs to know of this actors destruction. It is a temporary "representing" an instance so the data needs to be cleaned up
		if( mIsLightweightTemporary && !mIsStaleLightweightTemporary )
		{
			AFGLightweightBuildableSubsystem* lightweightSubsystem = AFGLightweightBuildableSubsystem::Get( GetWorld() );
			lightweightSubsystem->RemoveByBuildable( this );
		}
	}
	else
	{
		// Hide the instances, but do not remove them yet. They are necessary to be able to correctly gather dynamically spawned lightweight instances for the dismantle effect
		// The instances will actually be removed during EndPlay
		ToggleInstanceVisibility( false );
	}

	if( mRemoveBuildableFromSubsystemOnDismantle && !mReplicatedBuiltInsideBlueprintDesigner )
	{
		AFGBuildableSubsystem::Get( GetWorld() )->RemoveBuildable( this );
		mHasBeenRemovedFromSubsystem = true;
	}

	// Destroy handles
	if(mPoolHandles.Num() > 0)
	{
		FFGBackgroundThread::RemoveHandles( mPoolHandles, GetActorLocation(), GetWorld() );

		mPoolHandles.Empty();
		mRegisteredWithBackgroundThread = false;
	}
	
	// This will setup actor destruction, and if we have no build effect, this will destroy the actor
	NetMulticast_Dismantle();
}

void AFGBuildable::StartIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter )
{
	if( mIsDismantled )
	{
		return;
	}
	if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
	{
		if( mIsDismantled )
		{
			outline->HideOutline( this );
		}
		else
		{
			outline->ShowOutline( this, EOutlineColor::OC_DISMANTLE );
		}
	}

	// Dynamically switch out materials on the buildable
	if( !mIsDismantled )
	{
		TogglePendingDismantleMaterial( true );
	}

	mPendingDismantleHighlighted = true;

	MarkComponentsRenderStateDirty();
}

void AFGBuildable::StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter )
{
	if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
	{
		outline->HideOutline( this );
	}

	TogglePendingDismantleMaterial( false );

	mPendingDismantleHighlighted = false;
}

void AFGBuildable::GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const
{
}

FText AFGBuildable::GetDismantleDisplayName_Implementation( AFGCharacterPlayer* byCharacter ) const
{
	return mDisplayName;
}

void AFGBuildable::GetDismantleDependencies_Implementation( TArray<AActor*>& out_dismantleDependencies ) const
{
	// When dismantling integrated buildables, we want to dismantle our parent first so that we will return true in CanDismantle and get proper dismantle refunds
	if ( IsValid( mParentBuildableActor ) )
	{
		out_dismantleDependencies.Add( mParentBuildableActor );
	}
}

void AFGBuildable::StartIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter, UFGCircuitConnectionComponent* overlappingConnection )
{
	if( mIsDismantled )
	{
		return;
	}
	if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
	{
		outline->ShowOutline( this, EOutlineColor::OC_HOLOGRAMLINE );
	}
}

void AFGBuildable::StopIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter )
{
	if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
	{
		outline->HideOutline( this );
	}
}
void AFGBuildable::PlayBuildEffects( AActor* inInstigator )
{
	// Don't play effects on hidden integrated buildables. i.e. hub upgrades.
	if( !GetRootComponent()->IsVisible() )
	{
		return;
	}

	mBuildEffectInstignator = inInstigator;
}

void AFGBuildable::ExecutePlayBuildEffects()
{
	if( ShouldSkipBuildEffect() )
	{
		RegisterWithBackgroundThread();
		CallSetupInstances();

		return;
	}

	const AFGGameState* gameState = GetWorld()->GetGameState<AFGGameState>();
	if( gameState && gameState->GetCheatTurboBuildMode() )
	{
		CallSetupInstances();
		RegisterWithBackgroundThread();
		
		return;
	}
	// [ZolotukhinN:17/05/2023] Allow playing build effect even when there is no instigator, the build effect handles that just fine
	if( mBuildEffectIsPlaying )
	{
		return;
	}

	// Don't play effects on hidden integrated buildables. i.e. hub upgrades
	if( GetRootComponent() && !GetRootComponent()->IsVisible()  && !DoesContainLightweightInstances_Native() )
	{
		return;
	}

	CallSetupInstances(true);
	SetActorHiddenInGame( mHideOnBuildEffectStart );

	// [ZolotukhinN:19/06/2023] If we have already been registered with the background thread (e.g. re-playing the build effect),
	// update the visibility of the handles on the build effect start to match the initial state
	if ( mRegisteredWithBackgroundThread )
	{
		FFGBackgroundThread::UpdateItemStateViaHandle( mPoolHandles, false, GetWorld() );
	}

	const TSoftClassPtr< UFGMaterialEffect_Build > buildEffectTemplate = GetBuildEffectTemplate();
	if( !buildEffectTemplate.IsNull() )
	{
		if( mActiveBuildEffect )
		{
			mActiveBuildEffect->Stop();
		}

		mActiveBuildEffect = NewObject< UFGMaterialEffect_Build >( this, buildEffectTemplate.LoadSynchronous() );
		fgcheck( mActiveBuildEffect );

		mActiveBuildEffect->SetInstigator( mBuildEffectInstignator );
		if( *mBuiltWithRecipe )
		{
			mActiveBuildEffect->SetCost( mBuiltWithRecipe.GetDefaultObject()->GetIngredients() );
		}
		
		mActiveBuildEffect->SetTransform( GetActorTransform() );
		mActiveBuildEffect->SetSpeed( mBuildEffectSpeed );
		mActiveBuildEffect->mOnEnded.BindUObject( this, &AFGBuildable::OnBuildEffectFinished );
		mActiveBuildEffect->RegisterComponent();

		mBuildEffectIsPlaying = true;
	}
	else
	{
		// Register the pool actor here otherwise.
		if ( IsValid( mDecoratorClass ) && !mIsDismantled )
		{
			RegisterWithBackgroundThread();
		}
	}
}

void AFGBuildable::OnBuildEffectFinished()
{
	mBuildEffectInstignator = nullptr;
	mActiveBuildEffect = nullptr;
	
	for( UFGProductionIndicatorInstanceComponent* indicator : TInlineComponentArray<UFGProductionIndicatorInstanceComponent*>{ this } )
	{
		//When the build effect is done we force an update of the indicator since material switching has messed with it.
		indicator->ForceUpdateVisuals();
		break;
	}

	if( mPendingDismantleHighlighted )
	{
		TogglePendingDismantleMaterial( true );
	}

	DestroyBuildEffectProxyComponents();
	
	mBuildEffectIsPlaying = false;
	K2_OnBuildEffectFinished();

	// Some build effects change the state of the buildable and some of the buildables have NET Dormancy == Initial 
	// Ensure these state changes are replicated once the build effect is finished.
	
	if ( IsValid( mDecoratorClass ) && !mIsDismantled )
	{
		// Register with background thread if we are not registered yet
		if ( !mRegisteredWithBackgroundThread )
		{
			RegisterWithBackgroundThread();
		}
		// Otherwise just toggle the visibility
		else
		{
			FFGBackgroundThread::UpdateItemStateViaHandle( mPoolHandles, true, GetWorld() );
		}
	}

	// Handle lightweight instance data.
	ToggleInstanceVisibility( true );

	ApplyMeshPrimitiveData( GetCustomizationData_Native() );
	
	FlushNetDormancy();
}

bool AFGBuildable::HandleBlueprintSpawnedBuildEffect( AFGBuildEffectActor* inBuildEffectActor )
{
	if( !ManagedByLightweightBuildableSubsystem() || mReplicatedBuiltInsideBlueprintDesigner )
	{
		const AFGGameState* gameState = GetWorld()->GetGameState<AFGGameState>();
		if( gameState && gameState->GetCheatTurboBuildMode() )
		{
			CallSetupInstances();
			RegisterWithBackgroundThread();
		
			return false;
		}

		CallSetupInstances(true );
	}


	inBuildEffectActor->SetActor( this );
	mBuildEffectActor = inBuildEffectActor;
	mBlueprintBuildEffectIsPlaying = true;
	mBuildEffectIsPlaying = true;
	
	if ( mBuiltWithRecipe )
	{
		inBuildEffectActor->SetRecipe(*mBuiltWithRecipe, this );
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogTemp,Error,TEXT("mBuiltWithRecipe Not set!"));
	}
#endif

	// there are specific binds for certain classes, we call a different on finished for spline buildables for example.
	inBuildEffectActor->GetBind( GetClass() ).AddDynamic( this, &AFGBuildable::OnBuildEffectActorFinished );
	
	return true;
}

void AFGBuildable::PlayBuildEffectActor( AActor* inInstigator )
{
	// Don't play effects on hidden integrated buildables. i.e. hub upgrades.
	if( !GetRootComponent()->IsVisible() )
	{
		return;
	}

	mBuildEffectInstignator = inInstigator;
}

void AFGBuildable::ExecutePlayBuildActorEffects()
{
	if( ShouldSkipBuildEffect() )
	{
		RegisterWithBackgroundThread();
		CallSetupInstances();

		return;
	}

	const AFGGameState* gameState = GetWorld()->GetGameState<AFGGameState>();
	if( gameState && gameState->GetCheatTurboBuildMode() )
	{
		CallSetupInstances();
		RegisterWithBackgroundThread();
		
		return;
	}
	// [ZolotukhinN:17/05/2023] Allow playing build effect even when there is no instigator, the build effect handles that just fine
	if( mBuildEffectIsPlaying )
	{
		return;
	}
	
	CallSetupInstances(true );

	const auto SparseData = GetBuildableSparseData();
	TSubclassOf<AFGBuildEffectActor> BuildEffectTemplate = SparseData ? SparseData->mSparseBuildEffectActorTemplate : nullptr;

	// Request build effect actor.
	AFGBuildEffectActor* BuildEffectActor = nullptr;
	AFGBuildableSubsystem::RequestBuildEffectActor( this, BuildEffectActor, BuildEffectTemplate, GetActorTransform(), mBuildEffectInstignator, bForceBuildEffectSolo );
	BuildEffectActor->SetActor( this );
	BuildEffectActor->SetRecipe( *mBuiltWithRecipe, this );
	BuildEffectActor->GetBind(GetClass()).AddDynamic(this, &AFGBuildable::OnBuildEffectActorFinished);
	mBuildEffectIsPlaying = true;
	mBuildEffectActor = BuildEffectActor;
	// Start is auto called next frame.
	
	for (auto comp : TInlineComponentArray<UFGColoredInstanceMeshProxy*>{this})
	{
		comp->SetInstanced(false);
	}

	SetActorHiddenInGame( true );
}

void AFGBuildable::OnBuildEffectActorFinished()
{
	if( ShouldConvertToLightweight() && mBlueprintBuildEffectIsPlaying )
	{
		bool successfullyAdded = HandleLightweightAddition();
		if( successfullyAdded )
		{
			return;
		}
	}
	
	if( mPendingDismantleHighlighted )
	{
		TogglePendingDismantleMaterial( true );
	}
	
	mBuildEffectIsPlaying = false;
	mActiveBuildEffect = nullptr;
	mBuildEffectInstignator = nullptr;
	mIsMultiSpawnedBuildable = false;
	K2_OnBuildEffectFinished();
	
	if ( IsValid( mDecoratorClass ) && !mIsDismantled )
	{
		RegisterWithBackgroundThread();
	}
	
	// Toggle visibility
	{
		ToggleInstanceVisibility( true );
	
		SetActorHiddenInGame( false );
		for (auto comp : TInlineComponentArray<UFGColoredInstanceMeshProxy*>{this})
		{
			comp->SetVisibility(true);
			comp->SetInstanced(true);
		}
	}

	ApplyMeshPrimitiveData( GetCustomizationData_Native() );
	
	mBuildEffectActor = nullptr;
	FlushNetDormancy();
}

void AFGBuildable::NetMulticast_Dismantle_Implementation()
{
	// Attempt to close all widgets that the local players might have
	// Small optimization to avoid doing that for buildings that can be dismantled in huge amount, like foundations, but do not have the UI
	if ( !IsRunningDedicatedServer() && mInteractWidgetSoftClass.IsValid() )
	{
		CloseAllInteractUIsWithBuildable();
	}

	TurnOffAndDestroy();
	PlayDismantleEffects();
}

void AFGBuildable::CloseAllInteractUIsWithBuildable() const
{
	for ( FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It )
	{
		const AFGHUD* HUD = It->Get()->GetHUD<AFGHUD>();
		if ( HUD != nullptr && HUD->GetGameUI() )
		{
			TArray<UFGInteractWidget*> WidgetsToClose;
			HUD->GetGameUI()->GetInteractWidgetsOfInteractObject( this, WidgetsToClose );

			// Pop all interact widgets belonging to this buildable
			for ( UFGInteractWidget* InteractWidget : WidgetsToClose )
			{
				HUD->GetGameUI()->PopWidget( InteractWidget );
			}
		}
	}
}

void AFGBuildable::PlayDismantleEffects()
{
	const TSoftClassPtr< UFGMaterialEffect_Build > dismantleEffectTemplate = GetDismantleEffectTemplate();
	if( !dismantleEffectTemplate.IsNull() )
	{
		//[DavalliusA:Mon/01-04-2019] keep this inside this if, if we play the effect, as the finish code have the same logics, and we will look to remove the object as sson as possible there anyway. So only bother to do this here for now.
		//Disable collision and queries.
		{
			SetActorEnableCollision( false );
			DisableComponentsSimulatePhysics();

			TInlineComponentArray< UPrimitiveComponent* > comps( this );
			for( UPrimitiveComponent* comp : comps )
			{
				comp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
			}
		}

		if( mActiveBuildEffect )
		{
			mActiveBuildEffect->Stop();
		}

		// Force visibility true again.
		SetActorHiddenInGame(false);

		mActiveBuildEffect = NewObject< UFGMaterialEffect_Build >( this, dismantleEffectTemplate.LoadSynchronous() );
		fgcheck( mActiveBuildEffect );

		mActiveBuildEffect->SetInstigator( nullptr );
		if( *mBuiltWithRecipe )
		{
			mActiveBuildEffect->SetCost( mBuiltWithRecipe.GetDefaultObject()->GetIngredients() );
		}

		mActiveBuildEffect->SetSpeed( mBuildEffectSpeed );
		const AFGGameState* gameState = GetWorld()->GetGameState<AFGGameState>();
		if( gameState && gameState->GetCheatTurboBuildMode() )
		{
			mActiveBuildEffect->SetSpeed( mBuildEffectSpeed * 20.0f );
		}
		mActiveBuildEffect->mOnEnded.BindUObject( this, &AFGBuildable::OnDismantleEffectFinished );
		mActiveBuildEffect->RegisterComponent();

		// Give the effect the time it needs.
		SetLifeSpan( DISMANTLE_LIFE_SPAN_SAFE ); // Safety so we don't depend on designer code (build effect) to trigger dismantle.
	}
	else
	{
		OnDismantleEffectFinished();
	}
}

void AFGBuildable::OnDismantleEffectFinished()
{
	mActiveBuildEffect = nullptr;

	// Hide and disable the collision during the remaining lifespan.
	SetActorHiddenInGame( true );
	SetActorEnableCollision( false );
	DisableComponentsSimulatePhysics();
	TInlineComponentArray< UPrimitiveComponent* > comps( this );
	for( UPrimitiveComponent* comp : comps )
	{
		comp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	}

	Destroy();
}

UFGMaterialEffect_Build* AFGBuildable::GetActiveBuildEffect()
{
	return mActiveBuildEffect;
}

void AFGBuildable::OnSkinCustomizationApplied_Implementation( TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > skin )
{
}

void AFGBuildable::GetAlienOverClockingSourceMesh_Implementation( UStaticMesh*& SourceMesh, FTransform& Transform )
{
	SourceMesh = nullptr;
	Transform = FTransform::Identity;
}

void AFGBuildable::PlayConstructSound_Implementation()
{
	if( auto sound = UFGFactorySettings::GetRandomConstructionSound() )
	{
		int32 dummy;
		UAkGameplayStatics::PostAkEvent( sound, this, 0, FOnAkPostEventCallback(), TArray<FAkExternalSourceInfo>(), dummy );
	}
}

void AFGBuildable::PlayDismantleSound_Implementation()
{
	if( auto sound = UFGFactorySettings::GetRandomDismantleSound() )
	{
		int32 dummy;
		UAkGameplayStatics::PostAkEvent( sound, this, 0, FOnAkPostEventCallback(), TArray<FAkExternalSourceInfo>(), dummy );
	}
}

void AFGBuildable::GetDismantleRefund_Implementation( TArray<FInventoryStack>& out_refund, bool noBuildCostEnabled ) const
{
	// Refund this.
	GetDismantleInventoryReturns( out_refund );
	if( !noBuildCostEnabled ) // Only add these additional refunds if NoBuildCost is disabled
	{
		GetDismantleRefundReturns( out_refund );
		GetDismantleBlueprintReturns( out_refund );

		// Refund any connected wires.
		TInlineComponentArray< UFGCircuitConnectionComponent* > circuitConnections;
		GetComponents( circuitConnections );
		for( auto circuitConnection : circuitConnections )
		{
			TArray< AFGBuildableWire* > wires;
			circuitConnection->GetWires( wires );

			SCOPE_CYCLE_COUNTER( STAT_ExecuteInterface_Buildable );
			for( auto wire : wires )
			{
				// Added a null check because early trigger of this on clients in blueprint designer was causing an access violation
				if( wire )
				{
					IFGDismantleInterface::Execute_GetDismantleRefund( wire, out_refund, noBuildCostEnabled );
				}
			}
		}

		// Refund customization data
		const TArray< FInventoryStack > RefundStacks = FFactoryCustomizationData::GetCustomizationRefunds( GetWorld(), mCustomizationData );
		out_refund.Append( RefundStacks );
	}
	
	UFGInventoryLibrary::ConsolidateInventoryItems( out_refund );
}

void AFGBuildable::GetDismantleRefundReturns( TArray< FInventoryStack >& out_returns ) const
{
	const int32 costMultiplier = GetDismantleRefundReturnsMultiplier();

	for( const auto& cost : UFGRecipe::GetIngredients( GetBuiltWithRecipe() ) )
	{
		if( cost.Amount > 0 )
		{
			UFGInventoryLibrary::MergeInventoryItem( out_returns, FInventoryStack( cost.Amount * costMultiplier, cost.ItemClass ) );
		}
	}
}

void AFGBuildable::GetLightweightBuildableDismantleRefundReturns( const TSubclassOf<UFGRecipe>& builtWithRecipe, const FFGDynamicStruct& typeSpecificData, TArray<FInventoryStack>& out_returns ) const
{
	const int32 costMultiplier = GetDismantleRefundReturnsMultiplierForLightweight( typeSpecificData );

	for( const auto& cost : UFGRecipe::GetIngredients( builtWithRecipe ) )
	{
		if( cost.Amount > 0 )
		{
			UFGInventoryLibrary::MergeInventoryItem( out_returns, FInventoryStack( cost.Amount * costMultiplier, cost.ItemClass ) );
		}
	}
}

int32 AFGBuildable::GetDismantleRefundReturnsMultiplier() const
{
	return 1;
}

int32 AFGBuildable::GetDismantleRefundReturnsMultiplierForLightweight( const FFGDynamicStruct& typeSpecificData ) const
{
	return 1;
}

void AFGBuildable::GetDismantleInventoryReturns( TArray< FInventoryStack >& out_returns ) const
{
	// Loop though all the inventories and get their items, merge them if possible.
	TInlineComponentArray< UFGInventoryComponent* > inventories;
	GetComponents( inventories );
	for( const auto inventory : inventories )
	{
		if( inventory->GetSizeLinear() > 0 )
		{
			FInventoryStack stack;
		
			for( int32 i = 0; inventory->GetStackFromIndex( i, stack ); ++i )
			{
				if( stack.HasItems() )
				{
					const EResourceForm form = UFGItemDescriptor::GetForm( stack.Item.GetItemClass() );

					// Only add items that are of form SOLID. We don't want to return liquids to the player since they can't hold them
					if( form == EResourceForm::RF_SOLID )
					{
						UFGInventoryLibrary::MergeInventoryItem( out_returns, stack );
					}
				}
			}
		}
	}
}

void AFGBuildable::TogglePendingDismantleMaterial( bool enabled )
{
	if( mBuildEffectIsPlaying )
	{
		return;
	}

	if( APlayerController * pc = UGameplayStatics::GetPlayerController( GetWorld(), 0 ) )
	{
		if( AFGCharacterPlayer * byCharacter = Cast<AFGCharacterPlayer>( pc->GetPawn() ) )
		{
			if( !mIsDismantled && byCharacter->GetOutline() )
			{
				if (enabled)
				{
					byCharacter->GetOutline()->ShowOutline( this, EOutlineColor::OC_DISMANTLE );
				}
				//<DSFL>[VilagosD] this function did nothing when enabled was false, which caused to leave dismantle outlines enabled in multiplayer sessions
				else if (byCharacter->GetOutline()->GetOutlineStateColorForActor( this ) == EOutlineColor::OC_DISMANTLE)
				{
					byCharacter->GetOutline()->ShowOutline( this, EOutlineColor::OC_NONE );
				}
			}
		}
	}
}

TArray< UStaticMeshComponent* > AFGBuildable::CreateBuildEffectProxyComponents()
{
	// Handle belts.
	if( AFGBuildableConveyorBelt* BeltActor = Cast<AFGBuildableConveyorBelt>(this) )
	{
		TArray< UStaticMeshComponent* > Out;
		
		const float splineLength = BeltActor->GetSplineComponent()->GetSplineLength();
		const int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( splineLength / BeltActor->GetMeshLength() ) + 1 );
		const USplineComponent* Spline = BeltActor->GetSplineComponent();
		const float segmentLength = splineLength / numMeshes;
		
		for(int32 i = 0; i < numMeshes; i++)
		{
			const float startDistance = ( float )i * segmentLength;
			const float endDistance = ( float )( i + 1 ) * segmentLength;
					
			const FVector startPos = Spline->GetLocationAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::World );
			const FVector startTangent = Spline->GetTangentAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::World ).GetSafeNormal() * segmentLength;
			const FVector endPos = Spline->GetLocationAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::World );
			const FVector endTangent = Spline->GetTangentAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::World ).GetSafeNormal() * segmentLength;

			USplineMeshComponent* SplineSegment = NewObject<USplineMeshComponent>(this);
			SplineSegment->SetWorldTransform( FTransform::Identity );
			SplineSegment->bAffectDistanceFieldLighting = false;
			SplineSegment->SetMobility( EComponentMobility::Movable );
			SplineSegment->SetStaticMesh( BeltActor->GetSplineMesh() );
			SplineSegment->SetStartAndEnd(startPos,startTangent,endPos,endTangent);
			
			SplineSegment->SetForcedLodModel( 1 );
			SplineSegment->RegisterComponent();
			
			Out.Add( SplineSegment );
		}

		return Out;
	}
	// Handle pipes
	if(AFGBuildablePipeBase* Pipe = Cast<AFGBuildablePipeBase>( this ))
	{
		TArray< UStaticMeshComponent* > Out;

		const float splineLength = Pipe->GetSplineComponent()->GetSplineLength();
		const int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( splineLength / Pipe->GetMeshLength() ) + 1 );
		const USplineComponent* Spline = Pipe->GetSplineComponent();
		const float segmentLength = splineLength / numMeshes;
				
		// Build instances.
		for(int32 i = 0; i < numMeshes; i++)
		{
			const float startDistance = ( float )i * segmentLength;
			const float endDistance = ( float )( i + 1 ) * segmentLength;
					
			const FVector startPos = Spline->GetLocationAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::World );
			const FVector startTangent = Spline->GetTangentAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::World ).GetSafeNormal() * segmentLength;
			const FVector endPos = Spline->GetLocationAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::World );
			const FVector endTangent = Spline->GetTangentAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::World ).GetSafeNormal() * segmentLength;

			USplineMeshComponent* SplineSegment = NewObject<USplineMeshComponent>(this);
			SplineSegment->SetWorldTransform( FTransform::Identity );
			SplineSegment->bAffectDistanceFieldLighting = false;
			SplineSegment->SetMobility( EComponentMobility::Movable );
			SplineSegment->SetStaticMesh( Pipe->GetSplineMesh() );
			SplineSegment->SetStartAndEnd(startPos,startTangent,endPos,endTangent);
			SplineSegment->SetForcedLodModel( 1 );
			SplineSegment->RegisterComponent();
			Out.Add( SplineSegment );
		}
		
		return Out;
	}
	
	for (auto component : TInlineComponentArray<UFGColoredInstanceMeshProxy*>{this} )
	{
		// Only create proxies for meshes that do instance, so should create no render state.
		if (IsValid( component ) &&
			component->GetStaticMesh() &&
			!component->ShouldCreateRenderState() )
		{
			UStaticMeshComponent* proxyBuildEffectMeshComponent = NewObject< UStaticMeshComponent >(this );
			proxyBuildEffectMeshComponent->SetStaticMesh( component->GetStaticMesh() );
			proxyBuildEffectMeshComponent->SetWorldTransform( component->GetComponentTransform() );
			proxyBuildEffectMeshComponent->bAffectDistanceFieldLighting = false;
			proxyBuildEffectMeshComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
			proxyBuildEffectMeshComponent->bDisallowNanite = true;
			
			proxyBuildEffectMeshComponent->RegisterComponent();

			mProxyBuildEffectComponents.Add( proxyBuildEffectMeshComponent );
		}
	}

	// Handle lightweight instances
	if( DoesContainLightweightInstances_Native() )
	{
		TArray<FInstanceData> InstanceDataArray = Execute_GetActorLightweightInstanceData( this );

		// Create proxy components for static lightweight instances
		for	( const FInstanceData& InstanceData : InstanceDataArray )
		{
			UStaticMeshComponent* proxyBuildEffectMeshComponent = NewObject< UStaticMeshComponent >(this );
			proxyBuildEffectMeshComponent->bAffectDistanceFieldLighting = false;
			proxyBuildEffectMeshComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
			proxyBuildEffectMeshComponent->bDisallowNanite = true;
			
			proxyBuildEffectMeshComponent->SetStaticMesh( InstanceData.StaticMesh );
			proxyBuildEffectMeshComponent->SetWorldTransform( InstanceData.RelativeTransform * GetActorTransform() );
			proxyBuildEffectMeshComponent->OverrideMaterials = InstanceData.OverridenMaterials;
			
			proxyBuildEffectMeshComponent->RegisterComponent();
			mProxyBuildEffectComponents.Add( proxyBuildEffectMeshComponent );
		}
	
		// Create proxy components for dynamic lightweight instances
		for ( const FInstanceHandlePtr& InstanceHandle : GetDynamicLightweightInstanceHandles().HandleArray )
		{
			const UHierarchicalInstancedStaticMeshComponent* MeshComponent = InstanceHandle->GetInstanceComponent();
			if ( MeshComponent == nullptr || !InstanceHandle->IsInstanced() ) continue;

			UStaticMeshComponent* proxyBuildEffectMeshComponent = NewObject< UStaticMeshComponent >(this );
			proxyBuildEffectMeshComponent->bAffectDistanceFieldLighting = false;
			proxyBuildEffectMeshComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
			proxyBuildEffectMeshComponent->bDisallowNanite = true;
			
			proxyBuildEffectMeshComponent->SetStaticMesh( MeshComponent->GetStaticMesh() );
			proxyBuildEffectMeshComponent->SetWorldTransform( InstanceHandle->GetWorldTransform() );
			proxyBuildEffectMeshComponent->OverrideMaterials = MeshComponent->OverrideMaterials;
			
			proxyBuildEffectMeshComponent->RegisterComponent();
			mProxyBuildEffectComponents.Add( proxyBuildEffectMeshComponent );
		}
	}

	return mProxyBuildEffectComponents;
}

void AFGBuildable::DestroyBuildEffectProxyComponents()
{
	for(auto component : mProxyBuildEffectComponents)
	{
		if ( IsValid( component ) )
		{
			component->DestroyComponent(false );
		}	
	}
}

void AFGBuildable::TickFactory( float dt, ELevelTick TickType )
{
	// Root of tick hierarchy

	// Don't tick in editor viewport
	const bool shouldTick = TickType != LEVELTICK_ViewportsOnly;
	if( shouldTick )
	{
		// If a buildable has been destroyed or its level has been unloaded don't execute any queued ticks.
		if( !IsValid(this) && GetWorld() )
		{
			Factory_Tick( dt );	// perform any tick functions unique to an buildables subclass.
		}
	}
}

void AFGBuildable::Factory_Tick( float dt )
{
	// Optimization, only try to call Factory_ReceiveTick if it's implemented instead of searching for it with FindFunction and then call ProcessEvent
	if( mHasBlueprintFactoryTick )
	{
		Factory_ReceiveTick( dt );
	}
}

void AFGBuildable::EnablePrimaryTickFunctions( bool enable )
{
	if( !IsTemplate() )
	{
		SetActorTickEnabled( enable );

		TInlineComponentArray<UActorComponent*> components;
		GetComponents( components );

		for( int32 idx = 0; idx < components.Num(); idx++ )
		{
			components[ idx ]->SetComponentTickEnabled( enable );
		}
	}
}

bool AFGBuildable::Factory_PeekOutput_Implementation( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const
{
	return false;
}

bool AFGBuildable::Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type )
{
	return false;
}

bool AFGBuildable::ShouldBlockGuidelinePathForHologram( const AFGHologram* hologram ) const
{
	return true;
}

bool AFGBuildable::ShouldShowCenterGuidelinesForHologram( const AFGHologram* hologram ) const
{
	return false;
}

uint8 AFGBuildable::GetNumPowerConnections() const
{
	return (TInlineComponentArray<UFGPowerConnectionComponent*>{ this }).Num();
}

uint8 AFGBuildable::GetNumPowerConnectionsCached() const
{
	return mNumPowerConnectionsOnPlay;
}

uint8 AFGBuildable::GetNumFactoryConnections() const
{
	return (TInlineComponentArray<UFGFactoryConnectionComponent*>{ this }).Num();
}

uint8 AFGBuildable::GetNumFactoryOuputConnections() const
{
	TInlineComponentArray< UFGFactoryConnectionComponent* > connectionComponents( this );
	uint8 count = 0;

	for( auto component : connectionComponents )
	{
		if( component->GetDirection() == EFactoryConnectionDirection::FCD_OUTPUT )
		{
			++count;
		}
	}

	return count;
}

void AFGBuildable::GetAttachmentPoints( TArray< const FFGAttachmentPoint* >& out_points ) const
{
	out_points.Reserve( out_points.Num() + mAttachmentPoints.Num() );
	
	for( const FFGAttachmentPoint& point : mAttachmentPoints )
	{
		out_points.Add( &point );
	}
}

void AFGBuildable::CreateAttachmentPointsFromComponents( TArray< FFGAttachmentPoint >& out_points, AActor* owner ) const
{
	const bool bOwnerIsHologram = owner->IsA< AFGHologram >();
	
	out_points.Empty();
	
	// Get attachment point components from deco class
	TArray<UFGAttachmentPointComponent*> attachmentPointComponents = AFGDecorationTemplate::GetComponentsFromSubclass<UFGAttachmentPointComponent>( GetDecorationTemplate() );

	// Get attachment point components from this actor
	for( auto comp : TInlineComponentArray< UFGAttachmentPointComponent* >{ this } )
	{
		attachmentPointComponents.AddUnique( comp );
	}

	for( const UFGAttachmentPointComponent* point : attachmentPointComponents )
	{
		// Only create attachment points depending on their usage
		const EAttachmentPointUsage Usage = point->GetAttachmentPointUsage();
		if(
			Usage == EAttachmentPointUsage::EAPU_Default || // Create for both holograms and buildables
			( Usage == EAttachmentPointUsage::EAPU_BuildableOnly && owner->IsA< AFGBuildable >() ) || // Create for buildables only
			( Usage == EAttachmentPointUsage::EAPU_HologramOnly && owner->IsA< AFGHologram >() ) // Create for holograms only
			)
		{
			out_points.Add( point->CreateAttachmentPoint( owner ) );
		}
	}
}

bool AFGBuildable::ShouldBeConsideredForBase_Implementation()
{
	return true;
}

void AFGBuildable::DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos )
{
	if( debugDisplay.IsDisplayOn( SHOWDEBUG_FACTORYCONNECTIONS ) )
	{
		TInlineComponentArray< UFGFactoryConnectionComponent* > connections;
		GetComponents( connections );
		if( connections.Num() > 0 ) // Only show for buildings using conveyor connections.
		{
			int32 numConnected = 0;
			for( int32 i = 0; i < connections.Num(); ++i )
			{
				if( connections[ i ]->IsConnected() )
				{
					numConnected++;
				}

				connections[ i ]->DisplayDebug( i, canvas, debugDisplay, YL, YPos );
			}

			FString info;
			info.Append( FString::Printf( TEXT( "%s\n" ), *GetName() ) );
			info.Append( FString::Printf( TEXT( "Connections %i\n" ), connections.Num() ) );
			info.Append( FString::Printf( TEXT( "Connected %i\n" ), numConnected ) );

			DrawDebugString( GetWorld(), GetActorLocation(), info, nullptr, FColor::White, 0.0f, false );
		}
	}
}

void AFGBuildable::UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState )
{
	out_useState.SetUseState( UFGUseState_Valid::StaticClass() );
}

void AFGBuildable::OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state )
{
	if( mIsDismantled )
	{
		return;
	}
	fgcheck( byCharacter );

	// Only local player controllers can create widgets.
	APlayerController* controller = Cast< APlayerController >( byCharacter->GetController() );
	if( controller && controller->IsLocalPlayerController() )
	{
		if( IsValid(mInteractWidgetSoftClass.LoadSynchronous()) )
		{
			if( auto hud = Cast< AFGHUD >( controller->GetHUD() ) )
			{
				hud->OpenInteractUI( mInteractWidgetSoftClass.Get(), this );
			}
		}
	}
}

void AFGBuildable::OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state )
{
	fgcheck( byCharacter );
}

bool AFGBuildable::IsUseable_Implementation() const
{
	return mIsUseable;
}

void AFGBuildable::StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state )
{
	if( mIsDismantled )
	{
		return;
	}
	bool showOutline = true;

	AFGPlayerController* pc = Cast<AFGPlayerController>( byCharacter->GetController() );
	if( pc )
	{
		AFGHUD* hud = Cast<AFGHUD>( pc->GetHUD() );
		if( hud )
		{
			showOutline = !hud->GetPumpiMode();
		}
	}

	if( showOutline )
	{
		if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
		{
			outline->ShowOutline( this, EOutlineColor::OC_USABLE );
		}
	}
}

FText AFGBuildable::GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const
{
	AFGPlayerController* PC = Cast< AFGPlayerController >( byCharacter ? byCharacter->GetController() : nullptr );
	
	FText keyText = PC ? PC->GetKeyNameForUseAction() : FText::FromString( TEXT( "N/A" ) );
	return FText::Format( LOCTABLE( "Buildables_UI", "Buildables/LookAtDescription/DefaultConfigure/Pattern" ), keyText, mDisplayName );
}

void AFGBuildable::StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state )
{
	if( UFGOutlineComponent * outline = byCharacter->GetOutline() )
	{
		outline->HideOutline( this );
	}
}

void AFGBuildable::RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player )
{
	fgcheck( player );
	fgcheck( HasAuthority() );

#if WITH_EDITOR
	if ( CVarDisablePlayerInteractionRegistration.GetValueOnAnyThread() )
	{
		return;
	}
#endif

	if( mInteractingPlayers.Contains( player ) )
	{
		UE_LOG( LogFactory, Warning, TEXT( "%s::RegisterInteractingPlayer, '%s' is already registered." ), *GetName(), *player->GetName() );
		return;
	}

	for( int32 i = mInteractingPlayers.Num() - 1; i >= 0; --i )
	{
		if( !IsValid( mInteractingPlayers[ i ] ) )
		{
			UE_LOG( LogFactory, Warning, TEXT( "%s::RegisterInteractingPlayer, invalid player '%s' found in list, forgot to unregister?" ),
					*GetName(), *GetNameSafe( mInteractingPlayers[ i ] ) );

			mInteractingPlayers.RemoveAt( i );
		}
	}

	UE_LOG( LogFactory, Verbose, TEXT( "%s::RegisterInteractingPlayer, register '%s'." ), *GetName(), *player->GetName() );

	mInteractingPlayers.Add( player );

	RegisterInteractingPlayerWithCircuit( player );

	if( mToggleDormancyOnInteraction )
	{
		SetNetDormancy( DORM_Awake );
	}

	if( mForceNetUpdateOnRegisterPlayer )
	{
		ForceNetUpdate();
	}
}

void AFGBuildable::UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player )
{
	fgcheck( player );
	fgcheck( HasAuthority() );

#if WITH_EDITOR
	if ( CVarDisablePlayerInteractionRegistration.GetValueOnGameThread() )
	{
		return;
	}
#endif
	UE_LOG( LogFactory, Verbose, TEXT( "%s::UnregisterInteractingPlayer, unregister '%s'." ), *GetName(), *player->GetName() );

	const int32 removed = mInteractingPlayers.Remove( player );

	UnregisterInteractingPlayerWithCircuit( player );

	if( removed == 0 )
	{
		UE_LOG( LogFactory, Warning, TEXT( "%s::UnregisterInteractingPlayer, '%s' is not registered." ), *GetName(), *player->GetName() );
	}

	if( mForceNetUpdateOnRegisterPlayer )
	{
		ForceNetUpdate();
	}
}

void AFGBuildable::Native_OnMaterialInstancesUpdated()
{
	OnMaterialInstancesUpdated();
}

void AFGBuildable::BlueprintCleanUpFaultyConnectionHookups()
{
	// Safety for connections to ensure no Blueprint to OtherBlueprint or Blueprint To World mingling
	TInlineComponentArray< UFGConnectionComponent* > connectionComps {this};
	for( UFGConnectionComponent* connectionComp : connectionComps )
	{
		if( UFGFactoryConnectionComponent* factoryComp = Cast< UFGFactoryConnectionComponent >( connectionComp ) )
		{
			if( factoryComp->IsConnected()  )
			{
				if( UFGFactoryConnectionComponent* connectedTo = factoryComp->GetConnection() )
				{
					if( factoryComp->GetOuterBlueprintDesigner() != connectedTo->GetOuterBlueprintDesigner() )
					{
						factoryComp->ClearConnection();
					}
					else if( connectedTo->GetConnection() != factoryComp )
					{
						factoryComp->ClearConnection();
					}
				}
				else
				{
					// Somehow it thinks we're connected but we are not so just clear to correct the data on the comp
					factoryComp->ClearConnection();
				}
			}
		}
		else if( UFGPipeConnectionComponentBase* pipeComp = Cast< UFGPipeConnectionComponentBase >( connectionComp ) )
		{
			// Pipes don't save mHasConnectedComp like factory connections so for these just clear if there's a mismatch on designer
			if( UFGPipeConnectionComponentBase* connectedTo = pipeComp->GetConnection() )
			{
				if( pipeComp->GetOuterBlueprintDesigner() != connectedTo->GetOuterBlueprintDesigner() )
				{
					pipeComp->ClearConnection();
				}
				else if( pipeComp != connectedTo->GetConnection() )
				{
					pipeComp->ClearConnection();
				}
			}
		}
		else if( UFGRailroadTrackConnectionComponent* railComp = Cast<UFGRailroadTrackConnectionComponent>( connectionComp ) )
		{
			for( UFGRailroadTrackConnectionComponent* connectedTo : railComp->GetConnections() )
			{
				if( railComp->GetOuterBlueprintDesigner() != connectedTo->GetOuterBlueprintDesigner() )
				{
					railComp->RemoveConnection( connectedTo );
				}
				else if( !connectedTo->GetConnections().Contains( railComp )  )
				{
					railComp->RemoveConnection( connectedTo );
				}
			}
		}
	}
}

void AFGBuildable::PreSerializedToBlueprint()
{
	BlueprintCleanUpFaultyConnectionHookups();
}

void AFGBuildable::PostSerializedToBlueprint()
{
	// Do nothing
}

void AFGBuildable::PostSerializedFromBlueprint(bool isBlueprintWorld )
{
	BlueprintCleanUpFaultyConnectionHookups();
	
	if( !isBlueprintWorld )
	{
		// the build effect will be handled through a build effect actor instead.
		mIsMultiSpawnedBuildable = true;

		TInlineComponentArray< UFGPipeConnectionComponent* > pipeComponents{ this };
		for( UFGPipeConnectionComponent* pipeConnection : pipeComponents )
		{
			pipeConnection->PostSerializedFromBlueprint();
		}

		// This is a hacky way to get the circuits to rebuild correctly when placing a blueprint. We are very close to release < 24hrs
		// And I need a way to catch the edge cases of circuits not rebuilding.
		// @TODO - There is likely a much better way to catch / modify these circuits so theyre rebuilt. This just blindly connects but it seems to work
		// Note - This is only an issue with the circuit subsystem, serialization wise the connections are correctly "connected"
		TInlineComponentArray< UFGCircuitConnectionComponent* > circuitComponents{ this };
		AFGCircuitSubsystem* CircuitSubsystem = AFGCircuitSubsystem::Get( GetWorld() );
		for( UFGCircuitConnectionComponent* circuitComponent : circuitComponents )
		{
			TArray< UFGCircuitConnectionComponent* > connectedToComps;
			circuitComponent->GetConnections( connectedToComps );
			for( UFGCircuitConnectionComponent* to : connectedToComps )
			{
				CircuitSubsystem->ConnectComponents( circuitComponent, to );
			}
		}
	}
}

TSoftClassPtr<UFGMaterialEffect_Build> AFGBuildable::GetBuildEffectTemplate_Implementation() const
{
	return UFGBuildEffectSettings::Get()->mDefaultBuildEffect;
}

TSoftClassPtr<UFGMaterialEffect_Build> AFGBuildable::GetDismantleEffectTemplate_Implementation() const
{
	return UFGBuildEffectSettings::Get()->mDefaultDismantleEffect;
}

void AFGBuildable::SetIsLightweightTemporary( TArray<FInstanceOwnerHandlePtr>& instanceHandles, int32 indexOfRuntimeData )
{
	mIsLightweightTemporary = true;
	mInstanceHandles.Reset();
	mInstanceHandles.Append( instanceHandles );
	bReplicates = false;
	mRuntimeDataIndex = indexOfRuntimeData;
	
	for( const FInstanceOwnerHandlePtr& handle : instanceHandles )
	{
		handle->SetOwner( this );
	}
}

bool AFGBuildable::ManagedByLightweightBuildableSubsystem() const
{
	return mManagedByLightweightBuildableSubsystem && LightweightBuildables::GAllowLightweightManagement;
}

void AFGBuildable::RegisterInteractingPlayerWithCircuit( class AFGCharacterPlayer* player )
{
	if( !mInteractionRegisterPlayerWithCircuit )
	{
		return;
	}

	TInlineComponentArray< UFGPowerConnectionComponent* > powerConnections( this );
	for( UFGPowerConnectionComponent* connection : powerConnections )
	{
		if( UFGPowerCircuit * circuit = connection->GetPowerCircuit() )
		{
			circuit->RegisterInteractingPlayer( player );
		}
	}
}

void AFGBuildable::UnregisterInteractingPlayerWithCircuit( class AFGCharacterPlayer* player )
{
	if( !mInteractionRegisterPlayerWithCircuit )
	{
		return;
	}

	TInlineComponentArray< UFGPowerConnectionComponent* > powerConnections( this );
	for( UFGPowerConnectionComponent* connection : powerConnections )
	{
		if( UFGPowerCircuit * circuit = connection->GetPowerCircuit() )
		{
			circuit->UnregisterInteractingPlayer( player );
		}
	}
}

void AFGBuildable::SetBuildableHiddenInGame( bool hide, bool disableCollisionOnHide )
{
	// Prevent buildable visibility changes before the buildable in question BeginPlays
	if ( !HasActorBegunPlay() )
	{
		UE_LOG( LogGame, Warning, TEXT("AFGBuildable::SetBuildableHiddenInGame called for Buildable '%s' before it BeginPlay!"), *GetFullName() );
		return;
	}

	// Hide the normal actor components and disable the collision
	SetActorHiddenInGame( hide );
	if( disableCollisionOnHide )
	{
		SetActorEnableCollision( !hide );
	}
	
	// Un-instance the legacy colored instance meshes
	TInlineComponentArray<UFGColoredInstanceMeshProxy*> instanceMeshes( this );
	for( UFGColoredInstanceMeshProxy* proxyComponent : instanceMeshes )
	{
		proxyComponent->SetInstanced( !hide );
		proxyComponent->SetVisibility( !hide );
	}

	// Ask the background thread to update the visibility of pooled components
	if ( mRegisteredWithBackgroundThread )
	{
		FFGBackgroundThread::UpdateItemStateViaHandle( mPoolHandles, !hide, GetWorld() );
	}

	// Ask the lightweight instance manager to hide lightweight instances
	if( !mBuildEffectIsPlaying )
	{
		ToggleInstanceVisibility( !hide );
	}
}

TSubclassOf< AFGBuildable > AFGBuildable::GetBuildableClassFromRecipe( TSubclassOf< class UFGRecipe > inRecipe )
{
	TArray< FItemAmount > recipeItems;
	UFGRecipe* defaultRecipe;
	defaultRecipe = inRecipe->GetDefaultObject< UFGRecipe >();

	recipeItems = defaultRecipe->GetProducts();

	auto product = recipeItems[ 0 ];
	return UFGBuildingDescriptor::GetBuildableClass( *product.ItemClass );
}

DECLARE_CYCLE_STAT( TEXT( "CreateFactoryStatID" ), STAT_CreateFactoryStatID, STATGROUP_StatSystem );
#if STATS
// Basically a copy of UObjectBase::CreateStatID, but appends on :FactoryTick, so that we know that it's another function
void AFGBuildable::CreateFactoryStatID() const
{
	SCOPE_CYCLE_COUNTER( STAT_CreateFactoryStatID );

	FString longName;
	longName.Reserve( 255 );
	TArray<UObjectBase const*, TInlineAllocator<24>> classChain;

	// Build class hierarchy
	UObjectBase const* target = this;
	do
	{
		classChain.Add( target );
		target = target->GetOuter();
	} while( target );

	// Start with class name
	if( GetClass() )
	{
		GetClass()->GetFName().GetDisplayNameEntry()->AppendNameToString( longName );
	}

	// Now process from parent -> child so we can append strings more efficiently.
	bool firstEntry = true;
	for( int32 i = classChain.Num() - 1; i >= 0; i-- )
	{
		target = classChain[ i ];
		const FNameEntry* nameEntry = target->GetFName().GetDisplayNameEntry();
		if( firstEntry )
		{
			nameEntry->AppendNameToPathString( longName );
		}
		else
		{
			if( !longName.IsEmpty() )
			{
				longName += TEXT( "." );
			}
			nameEntry->AppendNameToString( longName );
		}
		firstEntry = false;
	}
	longName.Append( TEXT( ":FactoryTick" ) );

	mFactoryStatID = FDynamicStats::CreateStatId<FStatGroup_STATGROUP_FactoryTick>( longName );
}
#endif

void AFGBuildable::Stat_Cost( TArray< FItemAmount >& out_amount ) const
{
	TArray< FInventoryStack > refund;
	GetDismantleRefundReturns( refund );
	for( const FInventoryStack& stack : refund )
	{
		out_amount.Add( FItemAmount( stack.Item.GetItemClass(), stack.NumItems ) );
	}
}

bool AFGBuildable::CanBeSampled_Implementation() const
{
	//[FreiholtzK:Mon/14-12-2020] We default this to false if for some reason recipemanager isn't available which should only happen really early or when we are about to exit the session
	bool isBuildingAvailable = false;
	if( AFGRecipeManager* recipeManager = AFGRecipeManager::Get( GetWorld() ) )
	{
		isBuildingAvailable = recipeManager->IsBuildingAvailable( GetClass() );

		// If our own buildable class is not available, check our original variant, if we have one assigned.
		if( !isBuildingAvailable && mOriginalBuildableVariant )
		{
			const auto Desc = UFGRecipe::GetDescriptorForRecipe( GetBuiltWithRecipe() );

			fgcheck( Desc );
			
			if( Desc && Desc->IsChildOf< UFGBuildDescriptor >() )
			{
				// If the recipe build class is the same as our original variant
				const TSubclassOf< AActor > RecipeBuildableClass = UFGBuildDescriptor::GetBuildClass( *Desc );

				if( RecipeBuildableClass == mOriginalBuildableVariant )
				{
					isBuildingAvailable = recipeManager->IsBuildingAvailable( mOriginalBuildableVariant );
				}
			}
		}
	}
	
	return isBuildingAvailable;
}

void AFGBuildable::Stat_StockInventory( TArray< FItemAmount >& out_amount ) const
{
	TArray< FInventoryStack > stacks;
	GetDismantleInventoryReturns( stacks );

	for( auto stack : stacks )
	{
		// we do not want to care about item states in the stats.
		new( out_amount ) FItemAmount( stack.Item.GetItemClass(), stack.NumItems );
	}
}

void UFGSignificantNetworkRCO::GetLifetimeReplicatedProps( ::TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION( UFGSignificantNetworkRCO, mForceNetField_UFGSignificantNetworkRemoteCallObject, COND_InitialOnly );
}

void UFGSignificantNetworkRCO::Server_RequestDecoratorSignificantComponents_Implementation( AFGBuildable* actor, AFGPlayerController* controller )
{
	if( actor )
	{
		actor->CreateDecoratorSignificantComponents( controller );
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Server_RequestDecoratorSignificantComponents_Implementation Missing buildable actor "));	
	}
}

void UFGSignificantNetworkRCO::Server_RemoveDecoratorSignificantComponents_Implementation( AFGBuildable* actor, AFGPlayerController* controller )
{
	if( actor )
	{
		actor->TryRemoveDecoratorSignificantComponents( controller );
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Server_RemoveDecoratorSignificantComponents_Implementation Missing buildable actor "));	
	}
}


void AFGBuildable::SetBuildableDisplayName( TSubclassOf< AFGBuildable > inClass, FText displayName )
{
	if( inClass )
	{
		AFGBuildable* buildable = inClass->GetDefaultObject< AFGBuildable >();

		buildable->mDisplayName = displayName;
	}
	else
	{
		UE_LOG( LogGame, Warning, TEXT( "FGBuildable::SetBuildableDisplayName: class was nullpeter." ) );
	}
}

#undef LOCTEXT_NAMESPACE