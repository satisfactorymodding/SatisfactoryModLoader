# Daedalus
A tool to load mods for the game Icarus . It's under development until RocketWerkz releases an unreal mod API.

# Discord Server
Join our [discord-server](https://discord.gg/CfHUqctN) to talk about Daedauls or Icarus modding in general.

# Compilation instructions
When this tool is ready to use, stable releases will be found in the releases section. for now, you can compile this yourself.
## Required tools:
* Visual Studio 2022

When you clone this repository, you will see that there are 3 projects: Daedalus, BaseMod, and xinput1_3. Daedalus houses the code which runs the modloader and the associated code, BaseMod is the basic modding framework for mods to build on, and xinput1_3 is a wrapper for the modloader which allows it to run automatically when the icarus shipping EXE is started. The xinput1_3 project is the one that you need. __Make sure you are building with the configuration options Release and x64! It will not work otherwise!__ Build the xinput1_3 project and the DLL that you need will appear in x64/Release.
## Running instructions
Take the xinput1_3.dll file and put it next to Icarus/Binaries/Win64/Icarus-Win64-Shipping.exe, and then click that exe to run.
