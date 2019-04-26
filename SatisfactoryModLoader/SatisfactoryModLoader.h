#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mod/ModHandler.h>

static const std::string modLoaderVersion = "0.1.1"; // SML's version
static const std::string targetVersion = "97236"; //CL of Satisfactory
static bool loadConsole = true;
static bool debugOutput = false;
static bool supressErrors = false;

extern ModHandler modHandler;

void mod_loader_entry();
void read_config();
void cleanup();
