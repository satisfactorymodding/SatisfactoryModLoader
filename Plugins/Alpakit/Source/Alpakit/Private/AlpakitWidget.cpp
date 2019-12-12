#include "AlpakitWidget.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Editor/UATHelper/Public/IUATHelperModule.h"
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
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Satisfactory Game Folder"))
						]
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						[
							SNew(SEditableTextBox)
							.Text_Lambda([this]() { return Settings->SatisfactoryGamePath; })
							.OnTextChanged_Lambda([this](const FText& InText) { Settings->SatisfactoryGamePath = InText; Settings->SaveConfig(); })
						]
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						[
							SNew(SButton)
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Center)
							.Text(FText::FromString("Choose folder"))
							.OnClicked_Raw(this, &SAlpakaWidget::ChooseSatisfactoryFolder)
						]
				]	
			+	SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Start game after paking"))
						]
					+	SHorizontalBox::Slot()
						.Padding(3.0f)
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						[
							SNew(SCheckBox)
							.IsChecked_Lambda([this]() {return Settings->StartGame ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
							.OnCheckStateChanged_Lambda([this](ECheckBoxState state) { Settings->StartGame = (state == ECheckBoxState::Checked); Settings->SaveConfig(); })
						]
				]	
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
	CookContent();
	return FReply::Handled();
}

FReply SAlpakaWidget::ChooseSatisfactoryFolder()
{
	FString satisfactoryPath;
	if (OpenDirectoryDialog(FString("Choose Satisfactory install folder"), Settings->SatisfactoryGamePath.ToString(), satisfactoryPath))
	{
		Settings->SatisfactoryGamePath = FText::FromString(satisfactoryPath);
		Settings->SaveConfig();
	}
	return FReply::Handled();
}

bool SAlpakaWidget::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames)
{
	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	const void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
		? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
		: nullptr;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		//Opening the file picker!
		uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
		return DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);
	}
	return false;
}

bool SAlpakaWidget::OpenDirectoryDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName)
{
	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	const void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
		? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
		: nullptr;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		//Opening the file picker!
		return DesktopPlatform->OpenDirectoryDialog(ParentWindowHandle, DialogTitle, DefaultPath, OutFolderName);
	}
	return false;
}

void SAlpakaWidget::CookDone(FString result, double runtime)
{
	if (result.Equals("completed", ESearchCase::IgnoreCase))
	{
		// Cooking was successful
		FString CmdExe = TEXT("cmd.exe");
		FString UPakPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Binaries/Win64/UnrealPak.exe"));
		FString PakListPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Programs/AutomationTool/Saved/Logs") / FString::Printf(TEXT("PakList_%s-WindowsNoEditor.txt"), FApp::GetProjectName()));

		// Get list of all cooked assets
		TArray<FString> FilesToPak;
		FFileHelper::LoadFileToStringArray(FilesToPak, *PakListPath);

		for (FAlpakitMod mod : Settings->Mods)
		{
			// Choose from the cooked list only the current mod assets
			TArray<FString> ModFilesToPak;
			FString contentFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / FString::Printf(TEXT("Saved/Cooked/WindowsNoEditor/%s/Content"), FApp::GetProjectName()));
			FString modCookFolder = (contentFolder / FString::Printf(TEXT("FactoryGame/%s"), *mod.Name)).Replace(L"/", L"\\");
			UE_LOG(LogTemp, Log, TEXT("%s"), *modCookFolder);
			for (FString file : FilesToPak)
			{
				if (file.TrimQuotes().StartsWith(modCookFolder))
					ModFilesToPak.Add(file);
				else if (file.TrimQuotes().StartsWith((contentFolder / TEXT("FactoryGame")).Replace(L"/", L"\\")))
				{
					for (FString path : mod.OverwritePaths)
					{
						FString cookedFilePath = (contentFolder / path.RightChop(6)).Replace(L"/", L"\\"); // Should cut /Game/ from the path. Pls don't cause issues.
						FString uassetPath = FString::Printf(TEXT("%s.uasset"), *cookedFilePath);
						FString uexpPath = FString::Printf(TEXT("%s.uexp"), *cookedFilePath);
						if (file.TrimQuotes().StartsWith(uassetPath) || file.TrimQuotes().StartsWith(uexpPath))
							ModFilesToPak.Add(file);
					}
				}
			}

			FString pakName = FString::Printf(TEXT("%s%s"), *mod.Name, mod.OverwritePaths.Num() == 0 ? TEXT("") : TEXT("_p"));

			// Save it for UnrealPak.exe
			FString ModPakListPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Programs/AutomationTool/Saved/Logs") / FString::Printf(TEXT("PakList_%s-WindowsNoEditor.txt"), *pakName));
			FFileHelper::SaveStringArrayToFile(ModFilesToPak, *ModPakListPath);
			
			// Setup the pak file path
			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
			FString modPakFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / L"Mods");
			if (!PlatformFile.DirectoryExists(*modPakFolder))
				PlatformFile.CreateDirectory(*modPakFolder);
			FString pakFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / L"Mods" / FString::Printf(L"%s.pak", *pakName));
			
			// Run the paker and wait
			FString FullCommandLine = FString::Printf(TEXT("/c \"\"%s\" %s\""), *UPakPath, *FString::Printf(TEXT("\"%s\" -create=\"%s\""), *pakFilePath, *ModPakListPath));
			TSharedPtr<FMonitoredProcess> PakingProcess = MakeShareable(new FMonitoredProcess(CmdExe, FullCommandLine, true));
			PakingProcess->OnOutput().BindLambda([this, mod](FString output) { UE_LOG(LogTemp, Log, TEXT("Paking %s: %s"), *mod.Name, *output); });
			PakingProcess->Launch();

			UE_LOG(LogTemp, Log, TEXT("Packing %s"), *mod.Name);
			while (PakingProcess->Update())
				FPlatformProcess::Sleep(0.03);

			// Copy to Satisfactory Content/Paks folder
			PlatformFile.CopyFile(*FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.ToString() / FString::Printf(L"FactoryGame/Content/Paks/%s.pak", *pakName)), *pakFilePath);

			// Copy sig
			PlatformFile.CopyFile(*FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.ToString() / FString::Printf(L"FactoryGame/Content/Paks/%s.sig", *pakName)), *FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.ToString() / L"FactoryGame/Content/Paks/FactoryGame-WindowsNoEditor.sig"));

			UE_LOG(LogTemp, Log, TEXT("Packed %s"), *mod.Name);
		}
		AlpakitButton.Get()->SetEnabled(true);
		if (Settings->StartGame)
		{
			FString gamePath = FString::Printf(TEXT("\"%s\""), *FPaths::ConvertRelativePathToFull(Settings->SatisfactoryGamePath.ToString() / L"FactoryGame/Binaries/Win64/FactoryGame-Win64-Shipping.exe").Replace(L"/", L"\\"));
			int pathLength = gamePath.Len();
			char SatisfactoryPath[WINDOWS_MAX_PATH + 5];
			for (int i = 0; i < pathLength; i++)
			{
				SatisfactoryPath[i] = gamePath[i];
				SatisfactoryPath[i + 1] = '\000';
			}
			system(SatisfactoryPath);
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Error while running Aplakit. Cooking returned: %s"), *result);
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

void SAlpakaWidget::CookContent()
{
	// Create WwiseAudio folder if it doesn't exist
	VerifyOrCreateDirectory(FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()) / TEXT("WwiseAudio"));

	// Run the cook
	FString ProjectPath = FPaths::IsProjectFilePathSet() ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()) : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");
	FString CommandLine = FString::Printf(TEXT("BuildCookRun -nop4 -project=\"%s\" -cook -package -pak -skipstage -iterate"), *ProjectPath);

	IUATHelperModule::Get().CreateUatTask(CommandLine, FText::FromString("Windows"), FText::FromString("Cooking content"), FText::FromString("Cooking"), nullptr, [this](FString result, double runtime) { CookDone(result, runtime); });
}