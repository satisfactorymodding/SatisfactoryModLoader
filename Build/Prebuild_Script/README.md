# README

## PreBuildSteps in FactoryGame.uproject

The PreBuildSteps section in FactoryGame.uproject are JSON strings that are executed as (batch script?) commands.

The command in this readme executes via powershell on one line to avoid excecution policy errors.
Doing it this way via powershell requires two layers of escaping is needed. 
* Escaping the strings for Batch - Otherwise there are parsing errors.
* Json String escaping the final string for the uProject File.


## Testing the PreBuild in the project folder from a powershell prompt.
To test the script from the project directory. Open a powershell prompt and paste this command in.
```
powershell ($assemblyPath = "$PWD\Build\Prebuild.Automation\Scripts\Prebuild.Automation.dll");  (Add-Type -Path $assemblyPath); [PreBuild]::Main("$PWD")
```
In order the executed commands do the following; (Based on my understanding)
* set the `assemblyPath` varible to the DLL Path of `Prebuild.Automation.dll`
* Load the C# DLL as a usable type
* Call the Main method of PreBuild.cs with `$PWD` as the parameter.


## Preparing the string for the uProject file.
First, prep the command by replacing the $PWD with $(ProjectDir)
```
powershell ($assemblyPath = "$(ProjectDir)\Build\Prebuild.Automation\Scripts\Prebuild.Automation.dll");  (Add-Type -Path $assemblyPath); [PreBuild]::Main("$(ProjectDir)")
```

Then escape all the `"` using`\` 
```
powershell ($assemblyPath = \"$(ProjectDir)\\Build\\Prebuild.Automation\\Scripts\\Prebuild.Automation.dll\");  (Add-Type -Path $assemblyPath); [PreBuild]::Main(\"$(ProjectDir)\")
```

Finally, JSON string escape
```
powershell ($assemblyPath = \\\"$(ProjectDir)\\\\Build\\\\Prebuild.Automation\\\\Scripts\\\\Prebuild.Automation.dll\\\");  (Add-Type -Path $assemblyPath); [PreBuild]::Main(\\\"$(ProjectDir)\\\")
```

Now update the command in the uproject file.
```
	"PreBuildSteps":
	{
		"Win64": [
			"powershell ($assemblyPath = \\\"$(ProjectDir)\\\\Build\\\\Prebuild.Automation\\\\Scripts\\\\Prebuild.Automation.dll\\\");  (Add-Type -Path $assemblyPath); [PreBuild]::Main(\\\"$(ProjectDir)\\\")"
		]
	}
```
