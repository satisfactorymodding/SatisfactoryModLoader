[![Build Status](https://ci.ficsit.app/job/SatisfactoryModLoader/job/Development/badge/icon)](https://ci.ficsit.app/job/SatisfactoryModLoader/job/Development/)
# SatisfactoryModLoader
A tool used to load mods for the game Satisfactory. It's under development until Coffee Stain releases a proper Unreal modding API.

# Discord Server
Join our [discord server](https://discord.gg/QzcG9nX) to talk about SML or just Satisfactory Modding in general.

# DISCLAIMER
This software is provided by the author "as is". In no event shall the author be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and on any 
theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of the use of this software, even if advised of the possibility of such damage.

# Compiling SatisfactoryModLoader
When this tool is ready to use, stable releases will be found in the releases section. For now, you can compile this yourself.
## Required tools
* Visual Studio 2017
* Git client (optional, but makes things easier)

First, make sure to run the commands `git submodule init` and then `git submodule update`. This will download the Detours repository and place it in the detours folder, which is needed for compilation. If you did not download a git client, or if you downloaded the repository instead of cloning it, you will need to manually download the Detours repo (https://github.com/Microsoft/Detours) and extract it into Detours/, otherwise visual studio will not find the files to compile. After that, you will see 3 projects in the solution: Detours, BaseMod, and SatisfactoryModLoader. __Make sure you build with the configuration options Release and x64! It will not work otherwise!__ When the SatisfactoryModLoader project is compiled, you will find an xinput1_3.dll file in x64/Release folder.
# Running SatisfactoryModLoader
Take the xinput1_3.dll file and place it next to FactoryGame/Binaries/Win64/FactoryGame-Win64-Shipping.exe (the game install directory), and then click that exe to run. If everything went well, a console window should appear. It will disappear once and then reappear; then the game should be good to go!

Mods will be loaded from the folder FactoryGame/Binaries/Win64/mods.
