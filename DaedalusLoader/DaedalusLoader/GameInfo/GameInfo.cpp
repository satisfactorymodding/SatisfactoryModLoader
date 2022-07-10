#include "GameInfo.h"
#include <iostream>
#include "Utilities/Logger.h"
#include <string>
#include <filesystem>
#include <detours.h>
#include "INI.h"
#include "Utilities/Pattern.h"
#include "Utilities/Version.h"
#include "../Hooks.h"
#include "../UE4/Ue4.hpp"

#pragma execution_character_set("utf-8")

GameProfile GameProfile::SelectedGameProfile;

void PrintLogo()
{
    const char* logo =
        " ██████╗░░█████╗░███████╗██████╗░░█████╗░██╗░░░░░██╗░░░██╗░██████╗ \n"
        " ██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗██║░░░░░██║░░░██║██╔════╝ \n"
        " ██║░░██║███████║█████╗░░██║░░██║███████║██║░░░░░██║░░░██║╚█████╗░ \n"
        " ██║░░██║██╔══██║██╔══╝░░██║░░██║██╔══██║██║░░░░░██║░░░██║░╚═══██╗ \n"
        " ██████╔╝██║░░██║███████╗██████╔╝██║░░██║███████╗╚██████╔╝██████╔╝ \n"
        " ╚═════╝░╚═╝░░╚═╝╚══════╝╚═════╝░╚═╝░░╚═╝╚══════╝░╚═════╝░╚═════╝░ \n";

    std::cout << logo;
}

DWORD StringToDWord(std::string str)
{
    unsigned int m_dwIP;
    std::istringstream ss(&str[2]);
    ss >> std::hex >> m_dwIP;
    return m_dwIP;
}

std::string GetModuleFilePath(HMODULE hModule)
{
    std::string ModuleName = "";
    char szFileName[MAX_PATH] = { 0 };

    if (GetModuleFileNameA(hModule, szFileName, MAX_PATH))
        ModuleName = szFileName;

    return ModuleName;
}

void SetupProfile()
{
    char game_c[MAX_PATH];
    GetModuleFileNameA(NULL, game_c, MAX_PATH);
    std::string gamename = std::string(game_c);
    gamename = gamename.substr(0, gamename.find_last_of("."));
    gamename = gamename.substr(gamename.find_last_of("/\\"));
    gamename = gamename.substr(1);
    //Output File Initialization

    ShowWindow(GetConsoleWindow(), SW_SHOW);
    FreeConsole();
    AllocConsole();
    SetConsoleOutputCP(65001);
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    PrintLogo();

    Log::Info("UnrealModLoader Created by ~Russell.J Release V %s", MODLOADER_VERSION);
    Log::Info("Adapted by edmiester777 for use with Icarus");

    GameProfile::SelectedGameProfile.ProfileName = gamename;
    Log::Info("Profile Detected: %s", gamename.c_str());
    std::ifstream file("Profile");

    // icarus definitions - referenced UnrealDumper

    GameProfile::SelectedGameProfile.IsUObjectMissing = false;
    GameProfile::SelectedGameProfile.defs.UObject.Index = 0xC;
    GameProfile::SelectedGameProfile.defs.UObject.Class = 0x10;
    GameProfile::SelectedGameProfile.defs.UObject.Name = 0x18;
    GameProfile::SelectedGameProfile.defs.UObject.Outer = 0x20;

    GameProfile::SelectedGameProfile.IsUStructMissing = false;
    GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct = 0x40;
    GameProfile::SelectedGameProfile.defs.UStruct.Children = 0x48;
    GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize = 0x58;

    GameProfile::SelectedGameProfile.IsUFieldMissing = false;
    GameProfile::SelectedGameProfile.defs.UField.Next = 0x28;
    
    GameProfile::SelectedGameProfile.IsPropertyMissing = false;
    GameProfile::SelectedGameProfile.defs.Property.ArrayDim = 0x38;
    GameProfile::SelectedGameProfile.defs.Property.Offset = 0x4C;

    GameProfile::SelectedGameProfile.IsUFunctionMissing = false;
    GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags = 0xB0;
    GameProfile::SelectedGameProfile.defs.UFunction.Func = 0xB0 + 0x28;

    GameProfile::SelectedGameProfile.UsesFNamePool = true;

    auto FPoolPat = Pattern::Find("74 09 48 8D 15 ? ? ? ? EB 16");
    if (FPoolPat != nullptr)
    {
        auto FPoolPatoffset = *reinterpret_cast<uint32_t*>(FPoolPat + 5);
        GameProfile::SelectedGameProfile.GName = (DWORD64)(FPoolPat + 9 + FPoolPatoffset);
        Log::Info("FoundNamePool: 0x%p", GameProfile::SelectedGameProfile.GName);
    }
    else
    {
        Log::Error("GName Could Not Be Found!");
    }

    auto GObjectPat = Pattern::Find("8B 46 10 3B 46 3C 75 0F 48 8B D6 48 8D 0D ? ? ? ? E8");
    if (GObjectPat != nullptr)
    {
        auto GObjectOffset = *reinterpret_cast<uint32_t*>(GObjectPat + 14);
        GameProfile::SelectedGameProfile.GObject = (DWORD64)(GObjectPat + 18 + GObjectOffset);
        Log::Info("GObject: 0x%p", GameProfile::SelectedGameProfile.GObject);
    }
    else
    {
        Log::Error("GObject Could Not Be Found!");
    }

    auto GWorldPat = Pattern::Find("0F 2E ? 74 ? 48 8B 1D ? ? ? ? 48 85 DB 74");
    if (GWorldPat != nullptr)
    {
        auto GWorldAddress = *reinterpret_cast<uint32_t*>(GWorldPat + 8);
        GameProfile::SelectedGameProfile.GWorld = (DWORD64)(GWorldPat + 12 + GWorldAddress);
        Log::Info("GWorld: 0x%p", GameProfile::SelectedGameProfile.GWorld);
    }
    else
    {
        Log::Error("GWorld Could Not Be Found!");
    }

    GameProfile::SelectedGameProfile.GameStateInit = (DWORD64)Pattern::Find("40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91");
    Log::Info("GameStateInit: 0x%p", (void*)GameProfile::SelectedGameProfile.GameStateInit);
    if (!GameProfile::SelectedGameProfile.GameStateInit)
    {
        Log::Error("GameStateInit NOT FOUND!");
    }

    auto BeginPlay = Pattern::Find("48 8B D9 E8 ?? ?? ?? ?? F6 83 ?? ?? ?? ?? ?? 74 12 48 8B 03");
    BeginPlay += 0x3;
    if (BeginPlay != nullptr)
    {
        GameProfile::SelectedGameProfile.BeginPlay = (DWORD64)MEM::GetAddressPTR(BeginPlay, 0x1, 0x5);
        Log::Info("AActor::BeginPlay: 0x%p", (void*)GameProfile::SelectedGameProfile.BeginPlay);
    }
    else
    {
        Log::Error("AActor::BeginPlay NOT FOUND!");
    }

    auto StaticLoadObject = Pattern::Find("89 64 24 ? 48 8B C8 E8 ? ? ? ? 41 BE ? ? ? ? EB 05 E8"); // Sig 1
    if (StaticLoadObject != nullptr)
    {
        StaticLoadObject += 0x7;
    }
    else
    {
        StaticLoadObject = Pattern::Find("C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B 8D ? ? ? ? 48 85 C9 74 05 E8 ? ? ? ? 45 33 C9 ? 89 74 24");
        if (StaticLoadObject != nullptr)
        {
            StaticLoadObject += 0x8;
        }
        else
        {
            StaticLoadObject = Pattern::Find("89 6C 24 20 48 8B C8 E8 ? ? ? ? 48 8B 4C 24 ? 48 8B F0 48 85 C9 74 05");
            if (StaticLoadObject != nullptr)
            {
                StaticLoadObject += 0x7;
            }
            else
            {
                if (StaticLoadObject = Pattern::Find("48 8B C8 89 5C 24 20 E8 ? ? ? ? 48"))
                {
                    StaticLoadObject += 0x7;
                }
                else
                {
                    Log::Error("StaticLoadObject NOT FOUND!");
                }
            }
        }
    }
    GameProfile::SelectedGameProfile.StaticLoadObject = (DWORD64)MEM::GetAddressPTR(StaticLoadObject, 0x1, 0x5);

    Log::Info("StaticLoadObject: 0x%p", (void*)GameProfile::SelectedGameProfile.StaticLoadObject);

    auto SpawnActorFTrans = Pattern::Find("4C 8B C6 48 8B C8 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24");
    if (SpawnActorFTrans != nullptr)
    {
        SpawnActorFTrans += 0x9;
    }
    else
    {
        SpawnActorFTrans = Pattern::Find("4C 8B CE 4C 8D 44 24 ? 48 8B D7 48 8B CB E8 ? ? ? ? 48 8B 4C 24 ? 48 33 CC");
        if (SpawnActorFTrans != nullptr)
        {
            SpawnActorFTrans += 0xE;
        }
        else
        {
            Log::Error("SpawnActorFTrans NOT FOUND!");
        }
    }

    GameProfile::SelectedGameProfile.SpawnActorFTrans = (DWORD64)MEM::GetAddressPTR(SpawnActorFTrans, 0x1, 0x5);
    Log::Info("UWorld::SpawnActor: 0x%p", (void*)GameProfile::SelectedGameProfile.SpawnActorFTrans);

    auto CallFunctionByNameWithArguments = Pattern::Find("8B ? E8 ? ? ? ? ? 0A E8 FF ? EB 9E ? 8B");
    if (CallFunctionByNameWithArguments != nullptr)
    {
        CallFunctionByNameWithArguments += 0x2;
        GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments = (DWORD64)MEM::GetAddressPTR(CallFunctionByNameWithArguments, 0x1, 0x5);
    }
    else
    {
        CallFunctionByNameWithArguments = Pattern::Find("49 8B D4 E8 ? ? ? ? 44 0A F8 FF C3 EB 9A");
        if (CallFunctionByNameWithArguments != nullptr)
        {
            CallFunctionByNameWithArguments += 0x3;
            GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments = (DWORD64)MEM::GetAddressPTR(CallFunctionByNameWithArguments, 0x1, 0x5);
        }
        else
        {
            // falling back to searching by PDB
            CallFunctionByNameWithArguments = (PBYTE)DetourFindFunction(GAME_EXECUTABLE_NAME, "UObject::CallFunctionByNameWithArguments");
            if (CallFunctionByNameWithArguments != nullptr)
            {
                // no need to convert address pointer due to PDB lookup giving us real address
                GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments = (DWORD64)CallFunctionByNameWithArguments;
            }
            else
            {
                Log::Error("CallFunctionByNameWithArguments NOT FOUND!");
            }
        }
    }
    Log::Info("CallFunctionByNameWithArguments: 0x%p", (void*)GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments);

    auto ProcessEvent = Pattern::Find("75 0E ? ? ? 48 ? ? 48 ? ? E8 ? ? ? ? 48 8B ? 24 ? 48 8B ? 24 38 48 8B ? 24 40");
    ProcessEvent += 0xB;
    if (ProcessEvent != nullptr)
    {
        GameProfile::SelectedGameProfile.ProcessEvent = (DWORD64)MEM::GetAddressPTR(ProcessEvent, 0x1, 0x5);
        Log::Info("UObject::ProcessEvent: 0x%p", (void*)GameProfile::SelectedGameProfile.ProcessEvent);
    }
    else
    {
        Log::Error("ProcessEvent NOT FOUND!");
    }

    GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Pattern::Find("4C 8B DC 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9 ? ? ? ? ? 48 8B F9 ");
    if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
    {
        //FallBack 1
        GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Pattern::Find("4C 8B DC 55 53 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 83 B9 ? ? ? ? ? 48 8B D9 0F 85");
        if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
        {
            //FallBack 2
            GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Pattern::Find("4C 8B DC 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9");
            if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
            {
                //Final FallBack
                GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Pattern::Find("4C 8B DC ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? 48 ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ? ? ? ? ?? 8B ?? ? ? ? ? ?? ?? ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ? ? ? ? ?? ?? ?? 48");
                if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
                {
                    GameProfile::SelectedGameProfile.bIsDefaultObjectArrayed = true;
                    Log::Warn("CreateDefualtObject NOT FOUND!, Will Use Object Array Instead!");
                }
            }
        }
    }
    Log::Info("UClass::CreateDefualtObject: 0x%p", (void*)GameProfile::SelectedGameProfile.CreateDefaultObject);
    DWORD64 ProcessAddy = (DWORD64)Pattern::Find("41 F6 C7 02 74 ? 4C 8B C7 48 8B ? ? 8B ? E8");
    if (ProcessAddy)
    {
        auto ProcessAddyOffset = *reinterpret_cast<uint32_t*>(ProcessAddy + 16);
        GameProfile::SelectedGameProfile.ProcessInternals = (ProcessAddy + 20 + ProcessAddyOffset);
        Log::Info("ProcessInternalFunction: 0x%p", (void*)GameProfile::SelectedGameProfile.ProcessInternals);
    }
    auto StaticConstructObject_Internal = Pattern::Find("48 8B 84 24 ?? ?? 00 00 48 89 44 24 ?? C7 44 24 ?? 00 00 00 00 E8"); // Sig 1
    if (StaticConstructObject_Internal != nullptr)
    {
        StaticConstructObject_Internal += 0x15;
    }
    else
    {
        StaticConstructObject_Internal = Pattern::Find("48 8B C8 89 7C 24 ?? E8");
        if (StaticConstructObject_Internal != nullptr)
        {
            StaticConstructObject_Internal += 0x7;
        }
        else
        {
            GameProfile::SelectedGameProfile.IsUsingUpdatedStaticConstruct = true;
            StaticConstructObject_Internal = Pattern::Find("E8 ? ? ? ? 45 8B 47 70");
            if (!StaticConstructObject_Internal)
            {
                StaticConstructObject_Internal = Pattern::Find("89 6C 24 38 48 89 74 24 ? E8");
                if (StaticConstructObject_Internal != nullptr)
                {
                    StaticConstructObject_Internal += 0x9;
                }
                else
                {
                    Log::Warn("StaticConstructObject_Internal Not Found! This will prevent Mods using the ModObjectInstance from working properly.");
                }
            }
        }
    }
    GameProfile::SelectedGameProfile.StaticConstructObject_Internal = (DWORD64)MEM::GetAddressPTR(StaticConstructObject_Internal, 0x1, 0x5);
    Log::Info("StaticConstructObject_Internal 0x%p", (void*)GameProfile::SelectedGameProfile.StaticConstructObject_Internal);
    Hooks::SetupHooks();
}

void GameProfile::CreateGameProfile()
{
    //auto Module = GetModuleHandleA("DaedalusLoader.dll");
    //std::string path = GetModuleFilePath(Module);
    //path = path.substr(0, path.find_last_of("/\\"));
    SetupProfile();
}