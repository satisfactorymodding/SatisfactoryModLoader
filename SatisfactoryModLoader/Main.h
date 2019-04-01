#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>

static const char* modLoaderVersion = "v0.1 beta";

static const std::string targetVersion = "96032"; //CL of Satisfactory

void mod_loader_entry();

void cleanup();