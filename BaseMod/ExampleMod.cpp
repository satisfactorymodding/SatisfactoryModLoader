#include <stdafx.h>
#include <string>
#include <game/Global.h>
#include <game/Input.h>
#include <mod/Mod.h>
#include <HookLoaderInternal.h>
#include <mod/ModFunctions.h>
#include <util/JsonConfig.h>

using namespace SML::Mod;
using namespace SML::Objects;

// Version of SML that this mod was compiled for.
#define SML_VERSION "1.0.0-pr4"

// define the mod name for easy changing and simple use
#define MOD_NAME "ExampleMod"

// Define a log macro to make outputting to the log easier
#define LOG(msg) SML::Utility::info_mod(MOD_NAME, msg)

// Config
json config = SML::Utility::JsonConfig::load(MOD_NAME, {
	{"Float", 1.0}
});

// Global variables required by the mod
AFGPlayerController* player;

// Function to be called as a command (called when /kill is called)
// All command functions need to have the same parameters, which is SML::CommandData
// CommandData has two things in it, the amount of parameters and a vector of the parameters.
// The first item in the vector is always the command, so if someone did "/kill me" data.argc would be 2 and data.argv would be {"/kill", "me"}.
void killPlayer(Functions::CommandData data) {
	for (std::string s : data.argv) {
		LOG(s);
	}
	LOG("Killed Player");
	::call<&AFGPlayerController::Suicide>(player);
}

// information about the mod
Mod::Info modInfo {
	// Target sml version
	SML_VERSION,

	// Name
	MOD_NAME,

	// Version
	"0.2",

	// Description
	"A basic mod created to showcase SML's functionality.",

	// Authors
	"SuperCoder79, Nomnom, anttirt",

	// Dependencies
	// Place mod names that you want to ensure is loaded in this vector. If you place an asterisk (*) before the mod name, it will be loaded as an optional dependency instead.
	{}
};

// The mod's class, put all functions inside here
class ExampleMod : public Mod {

	// Function to be hooked
	// Every hook has two parameters at the start, even when the target function does not have any parameters.
	// The first is a pointer to ModReturns, which allows you to disable SML calling the function after your hook.
	// The second is a pointer to an object of the base class of the function, which in this case is AFGPlayerController.
	void beginPlay(Functions::ModReturns* modReturns, AFGPlayerController* playerIn) {
		LOG("Got Player");
		player = playerIn;
	}

public:
	// Constructor for SML usage, do not rename!
	ExampleMod() : Mod(modInfo) {
	}

	// The setup function is the heart of the mod, where you hook your functions and register your commands and API functions. Do not rename!
	void setup() override {
		// Use the placeholders namespace
		using namespace std::placeholders;

		// More on namespaces:
		// * The functions that will be of use to you are in the SML::Mods::Functions namespace. A tip is to type Functions:: and see what functions are available for you to use. 

		// Use a member function as handler
		::subscribe<&AFGPlayerController::BeginPlay>(std::bind(&ExampleMod::beginPlay, this, _1, _2)); //bind the beginPlay function, with placeholder variables
		// Because there are two inputs to the function, we use _1 and _2. If there were 3 inputs, we would use _1, _2, and _3, and so forth.

		// Use a lambda with captured this-ptr as handler
		::subscribe<&PlayerInput::InputKey>([this](Functions::ModReturns* modReturns, PlayerInput* playerInput, FKey key, InputEvent event, float amount, bool gamePad) {
			if(GetAsyncKeyState('G')) {
				LOG("G key pressed");
				::call<&AFGPlayerController::Suicide>(player);
			}
			return false;
		});

		// Tick functions are called every frame of the game. BE VERY CAREFUL WHEN USING THIS FUNCTION!!! Putting a lot of code in here will slow the game down to a crawl!
		::subscribe<&UWorld::Tick>([this](Functions::ModReturns*, UWorld* world, ELevelTick tick, float delta) {
			//LOG("test");
		});

		// Register /kill to call the killPlayer function
		Functions::registerCommand("kill", killPlayer); //functions registered like this must exist outside of the class

		// Register killPlayer as a function that other mods can use if this mod is loaded.
		registerAPIFunction("KillPlayer", killPlayer);

		LOG("Finished ExampleMod setup!");
	}

	void post_setup() override {
		// Write things to be done after other mods' setup functions
		// Called after the post setup functions of mods that you depend on.

		// Check if mod "RandomMod" is loaded
		if (Functions::isModLoaded("RandomMod")) {
			LOG("Random mod is loaded!");
			// Grab the raw function pointer for "NonexistantFunction"
			PVOID nonexistantFuncRaw = Functions::getAPIFunction("NonexistantFunction");
			// Cast the raw function pointer into a usable function
			auto nonexistantFunc = (void(WINAPI*)())nonexistantFuncRaw;
			// Call the nonexistant function
			nonexistantFunc();
			// Sidenote: this code should crash because it is trying to access a function that is not registered, but it does not because we ensure the code is only run when "RandomMod" is loaded.
		}

	}

	~ExampleMod() {
		// Cleanup
	}
};

// Required function to create the mod, do not rename!
MOD_API Mod* ModCreate() {
	return new ExampleMod();
}