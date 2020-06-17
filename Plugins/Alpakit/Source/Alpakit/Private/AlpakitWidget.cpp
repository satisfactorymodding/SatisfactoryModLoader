#include "AlpakitWidget.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Editor/UATHelper/Public/IUATHelperModule.h"
#include "Dom/JsonObject.h"
#include "SML/SatisfactoryModLoader.h"
#include "PropertyEditorModule.h"

void SAlpakaWidget::Construct(const FArguments& InArgs)
{
	Settings = GetMutableDefault<UAlpakitSettings>();
	// initialize settings view
	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowSearch = true;
		DetailsViewArgs.bHideSelectionTip = true;
		DetailsViewArgs.bLockable = false;
		DetailsViewArgs.bSearchInitialKeyFocus = true;
		DetailsViewArgs.bUpdatesFromSelection = false;
		DetailsViewArgs.bShowOptions = true;
		DetailsViewArgs.bShowModifiedPropertiesOption = true;
		DetailsViewArgs.bShowActorLabel = false;
		DetailsViewArgs.bCustomNameAreaLocation = true;
		DetailsViewArgs.bCustomFilterAreaLocation = true;
		DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
		DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
		DetailsViewArgs.bShowScrollBar = false; // Don't need to show this, as we are putting it in a scroll box
	}

	DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(Settings);

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		//~~~~~~~~~~~~~~~~~~~~
		//  Being Slate Construct Block
		[
			SNew(SVerticalBox)
			+	SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SNew(SScrollBox)
					//The actual list view creation
					+ SScrollBox::Slot()
						[
							DetailsView.ToSharedRef()
						]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Right)
				[
					SNew(SHorizontalBox)
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						[
							SAssignNew(AlpakitButton, SButton)
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Center)
							.Text(FText::FromString("Alpakit!"))
							.OnClicked_Raw(this, &SAlpakaWidget::Pakit)
						]
				]
		]; //End Slate Construct Block
		//~~~~~~~~~~~~~~~~~~~~~~~~

}

TSharedRef<SWidget> SAlpakaWidget::AsWidget()
{
	return SharedThis(this);
}

FReply SAlpakaWidget::Pakit()
{
	AlpakitButton.Get()->SetEnabled(false);
	Alpakit([this]() {
		AlpakitButton.Get()->SetEnabled(true);
	});
	return FReply::Handled();
}

void SAlpakaWidget::Alpakit(TFunction<void()> Done) {
	UAlpakitSettings* Settings = GetMutableDefault<UAlpakitSettings>();
	Settings->SaveConfig();
	CookContent(Settings, Done);
}

FString GetAutomationLogDirV1() {
	return FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Programs/AutomationTool/Saved/Logs"));
}

FString GetAutomationLogDirV2() {
	FString UEPathPlus = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT(".."));
	UEPathPlus = UEPathPlus.Replace(TEXT(":"), TEXT(""));
	UEPathPlus = UEPathPlus.Replace(TEXT("/"), TEXT("+"));
	UEPathPlus = UEPathPlus.Replace(TEXT(" "), TEXT("+"));
	return FString(FPlatformProcess::UserSettingsDir()) / TEXT("..") / TEXT("Roaming") / TEXT("Unreal Engine") / TEXT("AutomationTool") / TEXT("Logs") / UEPathPlus;
}

FString GetPakListPathV1(FString moduleName) {
	return GetAutomationLogDirV1() / FString::Printf(TEXT("PakList_%s-WindowsNoEditor.txt"), *moduleName);
}

FString GetPakListPathV2(FString moduleName) {
	return GetAutomationLogDirV2() / FString::Printf(TEXT("PakList_%s-WindowsNoEditor.txt"), *moduleName);
}

int FindUsedAutomationLogDir() {
	FString v1LogPath = GetPakListPathV1("FactoryGame");
	FString v2LogPath = GetPakListPathV2("FactoryGame");

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.FileExists(*v1LogPath))
		return 0;
	else if (PlatformFile.FileExists(*v2LogPath))
		return 1;
	
	UE_LOG(LogTemp, Error, TEXT("No PakList was created in either AutomationTool log directory"));
	return -1;
}

void ClearAutomationLogForVersionCheck() {
	FString v1LogPath = GetPakListPathV1("FactoryGame");
	FString v2LogPath = GetPakListPathV2("FactoryGame");

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.FileExists(*v1LogPath)) {
		PlatformFile.DeleteFile(*v1LogPath);
	}
	if (PlatformFile.FileExists(*v2LogPath)) {
		PlatformFile.DeleteFile(*v2LogPath);
	}	
}

void SAlpakaWidget::CookDone(FString result, double runtime,UAlpakitSettings* Settings, TFunction<void()> Done)
{
	if (result.Equals("completed", ESearchCase::IgnoreCase))
	{
		// Cooking was successful
		FString CmdExe = TEXT("cmd.exe");
		FString UPakPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Binaries/Win64/UnrealPak.exe"));
		FString PakListPath;

		int automationLogVersion = FindUsedAutomationLogDir();
		if (automationLogVersion == 0) {
			PakListPath = GetPakListPathV1("FactoryGame");
		}
		else if (automationLogVersion == 1) {
			PakListPath = GetPakListPathV2("FactoryGame");
		}
		else
			return;

		UE_LOG(LogTemp, Log, TEXT("%s"), *PakListPath);

		// Get list of all cooked assets
		TArray<FString> FilesToPak;
		FFileHelper::LoadFileToStringArray(FilesToPak, *PakListPath);
		FVersion smlVersion = SML::GetModLoaderVersion();
		FString smlVersionString = FString::Printf(TEXT("%llu.%llu.%llu"), smlVersion.Major, smlVersion.Minor, smlVersion.Patch);

		int modsCopied = 0;
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		for (FAlpakitMod mod : Settings->Mods)
		{
			if (!mod.Enabled) {
				UE_LOG(LogTemp, Log, TEXT("Skipping %s"), *mod.Name);
				continue;
			}
			// Choose from the cooked list only the current mod assets
			TArray<FString> ModFilesToPak;
			FString contentFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / FString::Printf(TEXT("Saved/Cooked/WindowsNoEditor/%s/Content"), FApp::GetProjectName()));
			FString modCookFolder = (contentFolder / FString::Printf(TEXT("%s"), *mod.Name)).Replace(TEXT("/"), TEXT("\\"));
			UE_LOG(LogTemp, Log, TEXT("%s"), *modCookFolder);
			bool didOverwrite = false;
			for (FString file : FilesToPak)
			{
				if (file.TrimQuotes().StartsWith(modCookFolder))
					ModFilesToPak.Add(file);
				else if (file.TrimQuotes().StartsWith((contentFolder / TEXT("FactoryGame")).Replace(TEXT("/"), TEXT("\\"))))
				{
					for (FString path : mod.OverwritePaths)
					{
						FString cookedFilePath = (contentFolder / path.RightChop(6)).Replace(TEXT("/"), TEXT("\\")); // Should cut /Game/ from the path. Pls don't cause issues.
						FString uassetPath = FString::Printf(TEXT("%s.uasset"), *cookedFilePath);
						FString uexpPath = FString::Printf(TEXT("%s.uexp"), *cookedFilePath);
						if (file.TrimQuotes().StartsWith(uassetPath) || file.TrimQuotes().StartsWith(uexpPath)) {
							ModFilesToPak.Add(file);
							didOverwrite = true;
						}
					}
				}
			}

			if (ModFilesToPak.Num() == 0) {
				UE_LOG(LogTemp, Error, TEXT("Mod %s has no files! Check that the mod name is set correctly (it should be the mod folder name, not path, check for typos)"), *mod.Name);
				continue;
			}

			FString pakName = FString::Printf(TEXT("%s%s"), *mod.Name, didOverwrite ? TEXT("_p") : TEXT(""));

			// Save it for UnrealPak.exe
			FString ModPakListPath;

			if (automationLogVersion == 0) {
				ModPakListPath = GetPakListPathV1(pakName);
			}
			else if (automationLogVersion == 1) {
				ModPakListPath = GetPakListPathV2(pakName);
			}
			else
				return;

			FFileHelper::SaveStringArrayToFile(ModFilesToPak, *ModPakListPath);
			
			// Setup the pak file path
			FString modPakFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Mods"));
			if (!PlatformFile.DirectoryExists(*modPakFolder))
				PlatformFile.CreateDirectory(*modPakFolder);
			FString localModFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Mods") / mod.Name);
			FString pakFilePath = localModFolderPath / FString::Printf(TEXT("%s.pak"), *pakName);
			FString dataJsonPath = localModFolderPath / TEXT("incomplete-data.json");
			
			TSharedPtr<FJsonObject> dataJson = MakeShared<FJsonObject>(FJsonObject());
			dataJson->SetStringField(TEXT("mod_reference"), mod.Name);
			dataJson->SetStringField(TEXT("name"), mod.DisplayName);
			dataJson->SetStringField(TEXT("description"), mod.Description);
			dataJson->SetStringField(TEXT("version"), mod.Version);
			dataJson->SetStringField(TEXT("sml_version"), smlVersionString);
			TArray<TSharedPtr<FJsonValue>> authorsJson;
			for (FString author : mod.Authors) {
				authorsJson.Add(MakeShared<FJsonValueString>(FJsonValueString(author)));
			}
			dataJson->SetArrayField(TEXT("authors"), authorsJson);
			TArray<TSharedPtr<FJsonValue>> objectsJson;
			TSharedPtr<FJsonObject> objectJson = MakeShared<FJsonObject>(FJsonObject());
			objectJson->SetStringField(TEXT("type"), TEXT("pak"));
			objectJson->SetStringField(TEXT("path"), FString::Printf(TEXT("%s.pak"), *pakName));
			objectsJson.Add(MakeShared<FJsonValueObject>(FJsonValueObject(objectJson)));
			dataJson->SetArrayField(TEXT("objects"), objectsJson);

			FString resultString;
			TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
			FJsonSerializer Serializer;
			Serializer.Serialize(dataJson.ToSharedRef(), writer);
			FFileHelper::SaveStringToFile(resultString, *dataJsonPath);

			// Run the paker and wait
			FString FullCommandLine = FString::Printf(TEXT("/c \"\"%s\" %s\""), *UPakPath, *FString::Printf(TEXT("\"%s\" -create=\"%s\""), *pakFilePath, *ModPakListPath));
			TSharedPtr<FMonitoredProcess> PakingProcess = MakeShareable(new FMonitoredProcess(CmdExe, FullCommandLine, true));
			PakingProcess->OnOutput().BindLambda([mod](FString output) { UE_LOG(LogTemp, Log, TEXT("Paking %s: %s"), *mod.Name, *output); });
			PakingProcess->Launch();

			UE_LOG(LogTemp, Log, TEXT("Packing %s"), *mod.Name);
			while (PakingProcess->Update())
				FPlatformProcess::Sleep(0.03);
			UE_LOG(LogTemp, Log, TEXT("Packed %s"), *mod.Name);

			if (Settings->CopyModsToGame) {
				modsCopied++;
				FString gameModsDir = FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.Path / TEXT("mods"));
				if (!FPaths::DirectoryExists(gameModsDir)) {
					PlatformFile.CreateDirectoryTree(*gameModsDir);
				}
				// Copy to Satisfactory mods folder
				PlatformFile.CopyFile(*(gameModsDir / FString::Printf(TEXT("%s.pak"), *pakName)), *pakFilePath);
				UE_LOG(LogTemp, Log, TEXT("Copied %s to game dir"), *mod.Name);
			}
		}
		if (Settings->CopyModsToGame && modsCopied > 0) {
			// Enable SML developmentMode
			FString gameConfigDir = FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.Path / TEXT("configs"));
			FString smlConfigFile = gameConfigDir / TEXT("SML.cfg");
			if (!FPaths::DirectoryExists(*gameConfigDir)) {
				PlatformFile.CreateDirectoryTree(*gameConfigDir);
			}
			
			TSharedPtr<FJsonObject> smlCfg = MakeShared<FJsonObject>(FJsonObject());
			if (FPaths::FileExists(smlConfigFile)) {
				FString contents;
				FFileHelper::LoadFileToString(contents, *smlConfigFile);

				TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*contents);
				FJsonSerializer Serializer;
				Serializer.Deserialize(reader, smlCfg);

			}
			if (!smlCfg->HasField(TEXT("developmentMode")) || !smlCfg->GetBoolField(TEXT("developmentMode"))) {
				smlCfg->SetBoolField(TEXT("developmentMode"), true);
				
				FString resultString;
				TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
				FJsonSerializer Serializer;
				Serializer.Serialize(smlCfg.ToSharedRef(), writer);
				FFileHelper::SaveStringToFile(resultString, *smlConfigFile);
			}
		}
		if (Settings->StartGame)
		{
			FString gamePath = *FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.Path / TEXT("FactoryGame/Binaries/Win64/FactoryGame-Win64-Shipping.exe")).Replace(TEXT("/"), TEXT("\\"));
			system(TCHAR_TO_ANSI(*FString::Printf(TEXT("start \"\" \"%s\""), *gamePath)));
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Error while running Aplakit. Cooking returned: %s"), *result);
	Done();
}

// https://answers.unrealengine.com/questions/500324/how-create-folder-when-my-game-is-running.html
//If this function cannot find or create the directory, returns false.
static FORCEINLINE bool VerifyOrCreateDirectory(const FString& TestDir)
{
	// Every function call, unless the function is inline, adds a small
	// overhead which we can avoid by creating a local variable like so.
	// But beware of making every function inline!
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Directory Exists?
	if (!PlatformFile.DirectoryExists(*TestDir))
	{
		PlatformFile.CreateDirectory(*TestDir);

		if (!PlatformFile.DirectoryExists(*TestDir))
		{
			return false;
			//~~~~~~~~~~~~~~
		}
	}
	return true;
}

void SAlpakaWidget::CookContent(UAlpakitSettings* Settings, TFunction<void()> Done)
{
	// Create WwiseAudio folder if it doesn't exist
	VerifyOrCreateDirectory(FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()) / TEXT("WwiseAudio"));
	ClearAutomationLogForVersionCheck();

	// Run the cook
	FString ProjectPath = FPaths::IsProjectFilePathSet() ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()) : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");
	FString CommandLine = FString::Printf(TEXT("BuildCookRun -nop4 -project=\"%s\" -cook -package -pak -skipstage -iterate"), *ProjectPath);

	IUATHelperModule::Get().CreateUatTask(CommandLine, FText::FromString("Windows"), FText::FromString("Cooking content"), FText::FromString("Cooking"), nullptr, [Settings, Done](FString result, double runtime) {
		CookDone(result, runtime, Settings, Done);
	});
}