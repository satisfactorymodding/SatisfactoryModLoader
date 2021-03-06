// This file has been automatically generated by the Unreal Header Implementation tool

#include "Equipment/FGEquipmentZipline.h"

AFGEquipmentZipline::AFGEquipmentZipline() : Super() {
	this->mZiplineJumpLaunchVelocity = 600;
	this->mMaxZiplineAngle = 0.949999988079071;
	this->mTraceDistance = 500;
	this->mTraceStartOffset = 300;
	this->mTraceRadius = 70;
	this->mZiplineReattachCooldown = 1;
	this->PrimaryActorTick.TickGroup = TG_PrePhysics; this->PrimaryActorTick.EndTickGroup = TG_PrePhysics; this->PrimaryActorTick.bTickEvenWhenPaused = false; this->PrimaryActorTick.bCanEverTick = true; this->PrimaryActorTick.bStartWithTickEnabled = false; this->PrimaryActorTick.bAllowTickOnDedicatedServer = true; this->PrimaryActorTick.TickInterval = 0;
	this->bOnlyRelevantToOwner = true;
	this->bNetUseOwnerRelevancy = true;
	this->SetReplicates(true);
}
void AFGEquipmentZipline::AddEquipmentActionBindings(){ }
void AFGEquipmentZipline::DoDefaultPrimaryFire_Native(){ }
void AFGEquipmentZipline::UnEquip(){ }
void AFGEquipmentZipline::OnDefaultPrimaryFireReleased(){ }
void AFGEquipmentZipline::Server_DefaultPrimaryFireReleased_Implementation(){ }
bool AFGEquipmentZipline::Server_DefaultPrimaryFireReleased_Validate(){ return bool(); }
void AFGEquipmentZipline::DoDefaultPrimaryFireReleased_Native(){ }
void AFGEquipmentZipline::Tick(float delta){ }
void AFGEquipmentZipline::ZiplineEnd(){ }
void AFGEquipmentZipline::Server_DoDrop_Implementation(){ }
bool AFGEquipmentZipline::Server_DoDrop_Validate(){ return bool(); }
void AFGEquipmentZipline::DoDrop(){ }
void AFGEquipmentZipline::Server_JumpExit_Implementation(){ }
bool AFGEquipmentZipline::Server_JumpExit_Validate(){ return bool(); }
void AFGEquipmentZipline::JumpExit(){ }
void AFGEquipmentZipline::OnCrouchPressed(){ }
void AFGEquipmentZipline::OnCrouchReleased(){ }
void AFGEquipmentZipline::OnJumpPressed(){ }
void AFGEquipmentZipline::TryToGrab(){ }
