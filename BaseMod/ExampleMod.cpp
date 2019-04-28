#include <stdafx.h>
#include <string>
#include <game/Global.h>
#include <game/Input.h>
#include <util/Configuration.h>
#include <mod/Mod.h>
#include <mod/ModFunctions.h>

//version of SML that this was compiled for.
#define SML_VERSION "0.1.1"

// config
Configuration config("ExampleMod");
bool testValue;

//global variables required by the mod
AFGPlayerController* player;

// Function to be called as a command (called when /kill is called)
void killPlayer() {
	info_mod("ExampleMod", "Killed Player");
	call<&AFGPlayerController::Suicide>(player);
}

//information about the mod
Mod::Info modInfo {
	//target sml version
	SML_VERSION,

	// name
	"ExampleMod",

	// version
	"0.2",

	// description
	"A basic mod created to showcase SML's functionality.",

	// authors
	"SuperCoder79, Nomnom, anttirt",

	// dependencies
	{}
};

//The mod's class, put all functions inside here
class ExampleMod : public Mod {

	//function to be hooked
	void beginPlay(ModReturns*, AFGPlayerController* playerIn) {
		info_mod("ExampleMod", "Got player");
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

		// use a member function as handler
		subscribe<&AFGPlayerController::BeginPlay>(std::bind(&ExampleMod::beginPlay, this, _1, _2)); //bind the beginPlay function, with placeholder variables
		// because there are two inputs to the function, we use _1 and _2. If there were 3 inputs, we would use _1, _2, and _3, and so forth.

		// use a lambda with captured this-ptr as handler
		subscribe<&PlayerInput::InputKey>([this](ModReturns*, PlayerInput* playerInput, FKey key, InputEvent event, float amount, bool gamePad) {
			if(GetAsyncKeyState('G')) {
				info_mod("ExampleMod", "G key pressed");
				call<&AFGPlayerController::Suicide>(player);
			}
			return false;
		});

		// register /kill to call the killPlayer function
		registerCommand("kill", killPlayer);
	}

	void post_setup() override {
		// write things to be done after other mods' setup functions
		// Called after the post setup functions of mods that you depend on.
	}

	~ExampleMod() {
		// cleanup
	}
};

//required function to create the mod, do not rename!
MOD_API Mod* ModCreate() {
	return new ExampleMod();
}