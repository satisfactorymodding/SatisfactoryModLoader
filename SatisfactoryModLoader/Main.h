#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>

static const char* modLoaderVersion = "0.1 beta";

void mod_loader_entry();

void cleanup();