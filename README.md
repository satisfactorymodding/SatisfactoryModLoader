# SatisfactoryModLoader
A tool to load mods for the game Satisfactory. It's under development until Coffee Stain releases an unreal mod API.

# Compilation instructions
When this tool is ready to use, stable releases will be found in the releases section. for now, you can compile this yourself.
## Required tools:
* Visual Studio 2017

When you clone this repository, you will see that there are 3 projects: SatisfactoryModLoader, BaseMod, and xinput1_3. SatisfactoryModLoader houses the code which runs the modloader and the associated code, BaseMod is the basic modding framework for mods to build on, and xinput1_3 is a wrapper for the modloader which allows it to run automatically when the satisfactory EXE is started. The xinput1_3 project is the one that you need. __Make sure you are building with the configuration options Release and x64! It will not work otherwise!__ Build the xinput1_3 project and the DLL that you need will appear in x64/Release.
## Running instructions
Take the xinput1_3.dll file and put it next to FactoryGame/Binaries/Win64/FactoryGame-Win64-Shipping.exe, and then click that exe to run. If everything ran well, an popup window and a console window should appear. If you click "ok" Satisfactory Will run as normal. Mods will be loaded from FactoryGame/Binaries/Win64/mods.
