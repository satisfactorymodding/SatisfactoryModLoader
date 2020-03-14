# 1. Environment Setup  
  
### 1.1 Login on epicgames.com   
- Go to your account (top right)    
- Connected account   
- Add GitHub   
- Open your email, accept Epic github invitation   

### 1.2 Download custom UnrealEngine release (.exe):   
https://github.com/SatisfactoryModdingUE/UnrealEngine/releases   

### 1.3 Setup Visual Studio 2017 ( Community is fine )   
- (Download Visual Studio 2017)[https://visualstudio.microsoft.com/vs/older-downloads/]
- Select “Desktop Development with C++”  
- Select “Game Development with C++”  
- Make sure to select unreal engine integration from the right side  
- Eventually is possible to add them after Installation, by relaunching the installer.  


### 1.4 Fix the file association (UE <-> Windows)
- Copy UnrealVersionSelector.exe from EpicGame Launcher folder   
    C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe
- Into Unreal Engine - CSS folder   
    C:\Program Files\Unreal Engine - CSS\Engine\Binaries\Win64
And run it from within the new folder.



# 2. Dependencies Setup
### 2.1 Download and Install Wwise
https://www.audiokinetic.com/download/ ( more steps later ) 

#### (Optional) Download a Git client (one of them)
https://www.sourcetreeapp.com/  
https://desktop.github.com/  
https://tortoisegit.org/download/  

#### (Optional) Download Satisfactory Mod Launcher
https://github.com/satisfactorymodding/SatisfactoryModLauncher/releases

# 3. Project Setup
### 3.1 Git-clone or download the base project:
https://github.com/satisfactorymodding/SatisfactoryModLoader 


### 3.2 Run WWise (AkAudio)
- Select “Unreal Engine” Tab
- From “Recent Unreal Engine Projects” select “Browse for project...”
- Select “FactoryGame.uproject”
- Click “Integrate Wwise into Project…”
- If you a prompred with some red boxes, no panic:
  - **Copy of Wwise SDK files**
    - From the click “Install Wise <version_proposed>”
    - Make sure to select “SDK (C++)” and “Microsoft -> Windows -> Visual Studio 2017 and Visual Studio 2015 ”
    - Follow the instructions (next, next, next, ...  )
  - **Wwise Project Path**
    - Just select “new” from the little arrow on the right side.
    - Now your “integrate” button should be enabled, click it.
    - Close WWise

### 3.3 Go to your fresh copy of SatisfactoryModLoader folder
- Right click on “FactoryGame.uproject” and select “Generate Visual studio project files”.  
  If you don’t have “Generate Visual studio project files” go back to “Fix the file association” in the previous section.  
- Wait for the process to finish.  
- Dobule click the newly created “FactoryGame.sln”.  
- Make sure to open it with “Visual Studio 2017”, eventually just right-click -> open with… -> Visual Studio 2017.  
- Within Visual Studio 2017, select from the top menu “Build -> Build Solution”.  
- Go make yourself a coffe.  
- Now the compilation should be over, close Visual Studio 2017.  

### 3.4 Go back to SatisfactoryModLoader folder:
- Double click “FactoryGame.uproject” 
