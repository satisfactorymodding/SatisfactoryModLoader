#include "Dumper.h"
#include <windows.h>
#include "../UE4/Ue4.hpp"
#include "Globals.h"

Dumper* Dumper::DumpRef;

Dumper* Dumper::GetDumper()
{
	if (!DumpRef)
	{
		DumpRef = new Dumper();
	}
	return DumpRef;
}


bool Dumper::DumpObjectArray()
{
	FILE* Log = NULL;
	fopen_s(&Log, "ObjectDump.txt", "w+");
	if (UE4::UObject::GObjects != nullptr)
	{
		if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
		{
			for (int i = 0; i < UE4::UObject::GObjects->GetAsChunckArray().Num(); i++)
			{
				auto obj = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(i).Object;
				if (obj != nullptr)
					fprintf(Log, "[%06i] %-100s 0x%p\n", obj->GetIndex(), obj->GetFullName().c_str(), obj);
			}
			Log::SetupMessage("Done!", "Object Dump Complete!");
		}
		else
		{
			for (int i = 0; i < UE4::UObject::GObjects->GetAsTUArray().Num(); i++)
			{
				auto obj = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(i).Object;
				if (obj != nullptr)
					fprintf(Log, "[%06i] %-100s 0x%p\n", obj->GetIndex(), obj->GetFullName().c_str(), obj);
			}
			Log::SetupMessage("Done!", "Object Dump Complete!");
		}
		Log::Info("Object Dump Complete!");
		fclose(Log);
		return true;
	}
	else
	{
		return false;
	}
}


bool Dumper::DumpEngineInfo()
{
	FILE* Log = NULL;
	fopen_s(&Log, "EngineInfo.txt", "w+");
	fprintf(Log, "#Engine Info Dump\n");
	fprintf(Log, "[GInfo]\nIsGInfoPatterns=0\nGName=0x%p\nGObject=0x%p\nGWorld=0x%p\n", GameProfile::SelectedGameProfile.GName - (DWORD64)GetModuleHandleW(0), GameProfile::SelectedGameProfile.GObject - (DWORD64)GetModuleHandleW(0), GameProfile::SelectedGameProfile.GWorld - (DWORD64)GetModuleHandleW(0));
	fprintf(Log, "\n[UObjectDef]\nIndex=0x%p\nClass=0x%p\nName=0x%p\nOuter=0x%p\n", GameProfile::SelectedGameProfile.defs.UObject.Index, GameProfile::SelectedGameProfile.defs.UObject.Class, GameProfile::SelectedGameProfile.defs.UObject.Name, GameProfile::SelectedGameProfile.defs.UObject.Outer);
	fprintf(Log, "\n[UFieldDef]\nNext=0x%p\n", GameProfile::SelectedGameProfile.defs.UField.Next);
	fprintf(Log, "\n[UStructDef]\nSuperStruct=0x%p\nChildren=0x%p\nPropertiesSize=0x%p\n", GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct, GameProfile::SelectedGameProfile.defs.UStruct.Children, GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize);
	fprintf(Log, "\n[UFunctionDef]\nFunctionFlags=0x%p\nFunc=0x%p\n", GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags, GameProfile::SelectedGameProfile.defs.UFunction.Func);
	fclose(Log);
	Log::SetupMessage("Done!", "Engine Info Dump Complete!");
	Log::Info("Engine Info Dump Complete!");
	return true;
}

bool Dumper::DumpWorldActors()
{
	FILE* Log = NULL;
	std::string FileName = UE4::UGameplayStatics::GetCurrentLevelName(false).ToString() + "_Dump.txt";
	auto GameplayStatics = UE4::UObject::GetDefaultObjectFromArray<UE4::UGameplayStatics>(UE4::UGameplayStatics::StaticClass());
	fopen_s(&Log, FileName.c_str(), "w+");
	auto actors = UE4::UObject::GetAllObjectsOfType<UE4::AActor>(UE4::AActor::StaticClass(), true);
	for (size_t i = 0; i < actors.size(); i++)
	{
		auto actor = actors[i];
		if (actor->GetOuter()->GetClass() == UE4::ULevel::StaticClass())
		{
			auto Location = actor->GetActorLocation();
			auto Rotation = actor->GetActorRotation();
			auto Scale = actor->GetActorScale3D();
			fprintf(Log, "ActorName: %s\n", actor->GetName().c_str());
			fprintf(Log, "ClassName: %s\n", actor->GetClass()->GetName().c_str());
			fprintf(Log, "Location: %f, %f, %f\n", Location.X, Location.Y, Location.Z);
			fprintf(Log, "Rotation: %f, %f, %f\n", Rotation.Pitch, Rotation.Roll, Rotation.Yaw);
			fprintf(Log, "Scale: %f, %f, %f\n", Scale.X, Scale.Y, Scale.Z);
			fprintf(Log, "\n");
		}
	}
	Log::SetupMessage("Done!", "World Actors Dump Complete!");
	fclose(Log);
	return true;
}