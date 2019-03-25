//#pragma once
//#include "dllmain.h"
//#include <vector>
//#include <map>
//#include <detours.h>
//
//class OriginalFunction {
//public:
//	//registerFunc RegisterFunc;
//	PVOID Func;
//	const char* Name;
//};
//
//static std::map<Event, OriginalFunction> functionList = {
//	{Event::OnPickupFoliage, OriginalFunction { NULL, "UFGFoliageLibrary::CheckInventorySpaceAndGetStacks" }},
//	{Event::OnPlayerBeginPlay, OriginalFunction { NULL, "APlayerController::BeginPlay" }},
//	{Event::OnPlayerTakeDamage, OriginalFunction { NULL, "UFGHealthComponent::TakeDamage" }}
//};
//
//int8_t UFGFoliageLibrary_CheckInventorySpaceAndGetStacks(void* character, void* meshComponent, void* out_validStacks);
//
//void UFGHealthComponent_TakeDamage(void* healthComponent, void* actor, FLOAT damageAmount, void* damageType, void* instigatedByA, void* instigatedByB, void* damageCauserA, void* damageCauserB);
//
//void APlayerController_BeginPlay();
//
//void hook_event(Event event, PVOID hook);