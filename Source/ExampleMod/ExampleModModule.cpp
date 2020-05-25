#include "ExampleModModule.h"
#include "mod/blueprint_hooking.h"
#include "util/Logging.h"

void FExampleModModule::StartupModule() {
}

IMPLEMENT_GAME_MODULE(FExampleModModule, ExampleMod);
