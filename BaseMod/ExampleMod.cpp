#include <stdafx.h>
#include <string>
#include <game/Global.h>
#include <game/Input.h>
#include <util/Configuration.h>
#include <mod/Mod.h>
#include <mod/ModFunctions.h>

//version of SML that this mod was compiled for.
#define SML_VERSION "1.0.0-pr2"

//define the mod name for easy changing and simple use
#define MOD_NAME "ExampleMod"

//define a log macro to make outputting to the log easier
#define LOG(msg) info_mod(MOD_NAME, msg)

// config
Configuration config(MOD_NAME);
bool testValue;

//global variables required by the mod
Classes::AFGPlayerController* player;

// Function to be called as a command (called when /kill is called)
void killPlayer() {
	LOG("Killed Player");
	call<&Classes::AFGPlayerController::Suicide>(player);
}

//information about the mod
Mod::Info modInfo {
	//target sml version
	SML_VERSION,

	// name
	MOD_NAME,

	// version
	"0.2",

	// description
	"A basic mod created to showcase SML's functionality.",

	// authors
	"SuperCoder79, Nomnom, anttirt",

	// dependencies
	// Place mod names that you want to ensure is loaded in this vector. If you place an asterisk (*) before the mod name, it will be loaded as an optional dependency instead.
	{}
};

//The mod's class, put all functions inside here
class ExampleMod : public Mod {

	//function to be hooked
	void beginPlay(ModReturns* modReturns, Classes::AFGPlayerController* playerIn) {
		LOG("Got Player");
		player = playerIn;
	}

public:
	//constructor for SML usage, do not rename!
	ExampleMod() : Mod(modInfo) {
	}

	// The setup function is the heart of the mod, where you hook your functions and register your commands and API functions. Do not rename!
	void setup() override {
		// Configs are horribly broken right now, disabled so the mod can actually load
		/* 
		if (!config.exists()) {
			config.set("TestValue", true);
			config.save();
		}

		config.load();

		testValue = config.get<bool>("TestValue");
		warning("Test Value: ", testValue);
		*/


		// use the placeholders namespace
		using namespace std::placeholders;

		// More on namespaces:
		// * The functions that will be of use to you are in the SML namespace. A tip is to type SML:: and see what functions are available for you to use. 
		// The only non-namespaced functions are subscribe() and call() which cannot go into a namespace for technical reasons.
		// * Classes that you can hook are in the Classes namespace.

		// use a member function as handler
		subscribe<&Classes::AFGPlayerController::BeginPlay>(std::bind(&ExampleMod::beginPlay, this, _1, _2)); //bind the beginPlay function, with placeholder variables
		// because there are two inputs to the function, we use _1 and _2. If there were 3 inputs, we would use _1, _2, and _3, and so forth.

		// use a lambda with captured this-ptr as handler
		subscribe<&Classes::PlayerInput::InputKey>([this](ModReturns* modReturns, Classes::PlayerInput* playerInput, FKey key, Classes::InputEvent event, float amount, bool gamePad) {
			if(GetAsyncKeyState('G')) {
				LOG("G key pressed");
				call<&Classes::AFGPlayerController::Suicide>(player);
			}
			return false;
		});

		//Tick functions are called every frame of the game. BE VERY CAREFUL WHEN USING THIS FUNCTION!!! Putting a lot of code in here will slow the game down to a crawl!
		subscribe<&Classes::UWorld::Tick>([this](ModReturns*, Classes::UWorld* world, Classes::ELevelTick tick, float delta) {
			//LOG("test");
		});

		// register /kill to call the killPlayer function
		SML::registerCommand("kill", killPlayer); //functions registered like this must exist outside of the class

		//register killPlayer as a function that other mods can use if this mod is loaded.
		SML::registerAPIFunction("KillPlayer", killPlayer);

		LOG("Finished ExampleMod setup!");
	}

	void post_setup() override {
		// write things to be done after other mods' setup functions
		// Called after the post setup functions of mods that you depend on.

		//Check if mod "RandomMod" is loaded
		if (SML::isModLoaded("RandomMod")) {
			LOG("Random mod is loaded!");
			//grab the raw function pointer for "NonexistantFunction"
			PVOID nonexistantFuncRaw = SML::getAPIFunction("NonexistantFunction");
			//Cast the raw function pointer into a usable function
			auto nonexistantFunc = (void(WINAPI*)())nonexistantFuncRaw;
			//call the nonexistant function
			nonexistantFunc();
			
			//Sidenote: this code should crash because it is trying to access a function that is not registered, but it does not because we ensure the code is only run when "RandomMod" is loaded.
		}

	}

	~ExampleMod() {
		// cleanup
	}
};

//required function to create the mod, do not rename!
MOD_API Mod* ModCreate() {
	return new ExampleMod();
}