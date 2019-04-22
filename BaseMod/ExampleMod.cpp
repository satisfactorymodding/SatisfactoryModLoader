#include <stdafx.h>
#include <string>
#include <game/Global.h>
#include <game/Input.h>
#include <util/Configuration.h>
#include <mod/Mod.h>


//version of SML that this was compiled for.
#define SML_VERSION "0.1.1"

/// config
Configuration config("ExampleMod");
bool testValue;

//information about the mod
Mod::Info info_ {
	SML_VERSION,

	// name
	"ExampleMod",

	// version
	"0.2",

	// description
	"A basic mod created to showcase SML's functionality.",

	// authors
	"Nomnom, SuperCoder79",

	// dependencies
	{}
};

class ExampleMod : public Mod {
	AFGPlayerController* player;

	void beginPlay(ModReturns*, AFGPlayerController* player) {
		info_mod("ExampleMod", "Got player");
		this->player = player;
	}

public:
	ExampleMod() : Mod(info_) {
	}

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

		// hook events
		using namespace std::placeholders;

		// use a member function as handler
		subscribe<&AFGPlayerController::BeginPlay>(std::bind(&ExampleMod::beginPlay, this, _1, _2));

		// use a lambda with captured this-ptr as handler
		subscribe<&PlayerInput::InputKey>([this](ModReturns*, PlayerInput* thiz, FKey key, InputEvent event, float amount, bool gamePad) {
			if(GetAsyncKeyState('G')) {
				info_mod("ExampleMod", "G key pressed");
				call<&AFGPlayerController::Suicide>(player);
			}
			return false;
		});
	}

	void post_setup() override {
		// write things to be done after other mods' setup functions
		// Called after the post setup functions of mods that you depend on.
	}

	~ExampleMod() {
		// cleanup
	}
};

MOD_API Mod* ModCreate() {
	return new ExampleMod();
}