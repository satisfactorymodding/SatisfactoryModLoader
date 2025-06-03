#include "FGPhotoModeComponent.h"
#include "CineCameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

UFGPhotoModeComponent::UFGPhotoModeComponent() : Super() {
	this->mAllOptions = nullptr;
	this->mPhotoModeCameraClass = AFGPhotoModeCamera::StaticClass();
	this->mDCMoveDistanceLimit = 3000.0;
	this->mDCCutoffDistanceLimit = 4000.0;
	this->mCameraCharacter = nullptr;
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
	this->SetIsReplicatedByDefault(true);
}
UFGPhotoModeComponent* UFGPhotoModeComponent::GetUFGPhotoModeComponent(const APlayerController* playerController){ return nullptr; }
void UFGPhotoModeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGPhotoModeComponent, mCameraCharacter);
}
void UFGPhotoModeComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGPhotoModeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UFGPhotoModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
void UFGPhotoModeComponent::TakePhoto(const int captureX, const int captureY, const int captureW, const int captureH){  }
bool UFGPhotoModeComponent::TogglePhotoMode(){ return bool(); }
bool UFGPhotoModeComponent::EnterPhotoMode(){ return bool(); }
bool UFGPhotoModeComponent::ExitPhotoMode(){ return bool(); }
void UFGPhotoModeComponent::ToggleDecoupledCamera(){  }
void UFGPhotoModeComponent::SetPlayerVisibilityInPhotoMode(const bool isVisible){  }
void UFGPhotoModeComponent::MoveForward(const float moveValue){  }
void UFGPhotoModeComponent::MoveBackwards(const float moveValue){  }
void UFGPhotoModeComponent::MoveLeft(const float moveValue){  }
void UFGPhotoModeComponent::MoveRight(const float moveValue){  }
void UFGPhotoModeComponent::MoveUp(const float moveValue){  }
void UFGPhotoModeComponent::MoveDown(const float moveValue){  }
void UFGPhotoModeComponent::MoveMouseX(const float axisValue){  }
void UFGPhotoModeComponent::MoveMouseY(const float axisValue){  }
void UFGPhotoModeComponent::MoveFaster(const float moveValue){ }
void UFGPhotoModeComponent::MoveSlower(const float moveValue){ }
bool UFGPhotoModeComponent::SetPMOption(const FString& optionKey, const float optionValue, const bool isResetCall){ return bool(); }
bool UFGPhotoModeComponent::ClearPMOption(const FString& optionKey){ return bool(); }
void UFGPhotoModeComponent::ClearPMOMap(const int expectedNumElements){  }
float UFGPhotoModeComponent::GetOptionValueFromID(const FString& ID) const{ return float(); }
void UFGPhotoModeComponent::Client_ProperlyResetClientAfterTogglingDecoupledCamera_Implementation(){ }
AFGCharacterPlayer* UFGPhotoModeComponent::GetOwnerPlayerCharacter() const{ return nullptr; }
AFGPlayerController* UFGPhotoModeComponent::GetPlayerController() const{ return nullptr; }
void UFGPhotoModeComponent::SetHandEquipmentVisibility(const bool isVisible){  }
FString UFGPhotoModeComponent::CreateScreenShotPath() const{ return FString(); }
FString UFGPhotoModeComponent::CreateScreenShotName(){ return FString(); }
FString UFGPhotoModeComponent::CreateScreenShotCommand(const int captureX, const int captureY, const int captureW, const int captureH) const{ return FString(); }
void UFGPhotoModeComponent::HandleDecoupledCameraPlacing(const bool isDecoupled){  }
void UFGPhotoModeComponent::PlaceDecoupledCameraAtPlayerCharacter(const AFGCharacterPlayer* playerCharacter){  }
float UFGPhotoModeComponent::GetMouseMovementFromAxisValue(const float axisValue) const{ return float(); }
void UFGPhotoModeComponent::OnRep_CameraCharacter(){  }
void UFGPhotoModeComponent::Server_ToggleDecoupledCamera_Implementation(const bool isOn){  }
void UFGPhotoModeComponent::Server_TogglePhotoMode_Implementation(const bool isOn){  }
class UCineCameraComponent* UFGPhotoModeComponent::GetCameraComponent() const{ return nullptr; }
float UFGPhotoModeComponent::ControllerTurnAtRate(float rate, bool WithInvertHandling){ return float(); }
float UFGPhotoModeComponent::ControllerLookUpAtRate(float rate, bool WithInvertHandling){ return float(); }
AFGPhotoModeCamera::AFGPhotoModeCamera() : Super() {
	this->mControllingPlayerCharacter = nullptr;
	this->mCameraComp = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	this->mCameraComp->SetMobility(EComponentMobility::Movable);
	this->mSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	this->mSpringArmComp->SetMobility(EComponentMobility::Movable);
	this->mCameraComp->SetupAttachment(mSpringArmComp);
	this->bOnlyRelevantToOwner = true;
	this->NetCullDistanceSquared = 1000000000000.0;
	this->mSpringArmComp->SetupAttachment(GetCapsuleComponent());
}
void AFGPhotoModeCamera::HandleDecoupledCameraMoveSpeed(){ }
void AFGPhotoModeCamera::Server_SetMoveSpeed_Implementation(const float newSpeed){ }
void AFGPhotoModeCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGPhotoModeCamera, mControllingPlayerCharacter);
}
