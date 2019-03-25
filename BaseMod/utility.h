#pragma once
#include <string>
#include <iostream>

enum Event {
	OnPreInit, // Called as soon as SML is finished constructing all mods.
	OnPickupFoliage, // Called when foliage is picked up by the player. Called once on the server and called once on the client.
	OnPlayerBeginPlay //Called when the player starts playing. Called once on the server and called once on the client.
};

void log(std::string msg);