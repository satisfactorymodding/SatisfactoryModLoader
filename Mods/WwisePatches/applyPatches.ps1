# Get the folders in the WwisePatches dir (same dir as this script)
$patchesFolder = Join-Path -Path (Split-Path -Parent $MyInvocation.MyCommand.Path) -ChildPath "Patches"
$thirdPartyDir = Join-Path -Path (Split-Path -Parent $MyInvocation.MyCommand.Path) -ChildPath "ThirdParty"
$ptchExecutable = Join-Path -Path $thirdPartyDir -ChildPath "ptch.exe"

# Ensure the patches folder exists
if (-Not (Test-Path -Path $patchesFolder)) {
    Write-Host "The specified patches folder does not exist: $patchesFolder"
    exit
}

# Ensure the ptch.exe exists and can run
if (-Not (Test-Path -Path $ptchExecutable)) {
    Write-Host "The ptch.exe executable was not found in: $thirdPartyDir"
    exit
}
Unblock-File $ptchExecutable

# Get the project dir passed by UE
if ($args.Count -lt 1) {
    Write-Host "Usage: applyPatches.ps1 <path>"
    exit
}
$projectDir = $args[0]

if (-Not (Test-Path -Path $projectDir)) {
    Write-Host "The specified project dir does not exist: $projectDir"
    exit
}

# Check patches that have already been applied
$appliedPatchesFile = Join-Path -Path $projectDir -ChildPath "Plugins\Wwise\applied_patches.txt"
$appliedPatches = @()
if (Test-Path -Path $appliedPatchesFile) {
    $appliedPatches = Get-Content -Path $appliedPatchesFile
} else {
    # Workaround for existing project setups. Remove this after the next wwise upgrade!
    # Before using patches, we were find-and-replace modifying `Plugins/Wwise/Source/AudiokineticTools/Private/WwiseProject/AcousticTextureParamLookup.cpp`
    # so we need to check if that file has been modified, and if so, consider the patch `01-ignore_missing_soundbanks.patch` as applied.
    # The marker of a modified file is `UE_LOG(LogAudiokineticTools, Warning, TEXT("LoadAllTextures: ProjectDatabase not loaded"));`
    $acousticTextureParamLookupFile = Join-Path -Path $projectDir -ChildPath "Plugins\Wwise\Source\AudiokineticTools\Private\WwiseProject\AcousticTextureParamLookup.cpp"
    if (Test-Path -Path $acousticTextureParamLookupFile) {
        $acousticTextureParamLookupContent = Get-Content -Path $acousticTextureParamLookupFile -Raw
        if ($acousticTextureParamLookupContent -match 'UE_LOG\(LogAudiokineticTools, Warning, TEXT\("LoadAllTextures: ProjectDatabase not loaded"\)\);') {
            $appliedPatches += "01-ignore_missing_soundbanks.patch"
            # Also write the applied patch to the file for future runs
            Add-Content -Path $appliedPatchesFile -Value "01-ignore_missing_soundbanks.patch"
        }
    }
}

# Enumerate all .patch files in the patches folder, sorted alphabetically
$files = Get-ChildItem -Path $patchesFolder -File | Where-Object { $_.Extension -eq ".patch" } | Sort-Object Name

# Check if there are any .patch files in the folder
if ($files.Count -eq 0) {
    Write-Host "No .patch files found in the folder: $patchesFolder"
    exit
}

# Iterate through the patch files
foreach ($file in $files) {
    $patchFileName = $file.Name

    # Skip if the patch has already been applied
    if ($appliedPatches -contains $patchFileName) {
        Write-Host "Patch '$patchFileName' has already been applied. Skipping."
        continue
    }
    
    $patchContent = Get-Content -Path $file.FullName -Raw
    # patch expects the patch files to be CRLF
    if ($patchContent -notmatch "`r`n") {
        $patchContent = $patchContent -replace "`n", "`r`n"
    }
    
    # Piping to stdin didn't work, use a temp file instead
    $tempFile = [System.IO.Path]::GetTempFileName()
    $patchContent | Set-Content -Path $tempFile -Encoding UTF8
    
    $arguments = "-N -s -p1 -d `"$projectDir`" -i `"$tempFile`""
    
    # Verify the patch can be applied with --dry-run before applying it
    $dryRunArguments = "$arguments --dry-run"
    Write-Host "Checking if patch can be applied: $ptchExecutable $dryRunArguments"
    $dryRunProcess = Start-Process -FilePath $ptchExecutable -ArgumentList $dryRunArguments -NoNewWindow -Wait -PassThru
    if ($dryRunProcess.ExitCode -ne 0) {
        Write-Host "Error: Dry run failed for patch '$patchFileName'. Exiting."
        exit $dryRunProcess.ExitCode
    }
    
    # TODO: redirect patch stdout/stderr to console, so that it can be logged

    # Apply the patch if dry run is successful
    Write-Host "Applying patch: $ptchExecutable $arguments"
    $process = Start-Process -FilePath $ptchExecutable -ArgumentList $arguments -NoNewWindow -Wait -PassThru
    if ($process.ExitCode -ne 0) {
        Write-Host "Error: Failed to apply patch '$patchFileName'. Exiting."
        exit $process.ExitCode
    }
    
    # Cleanup temp file
    Remove-Item -Path $tempFile

    # After applying the patch successfully, log it
    Add-Content -Path $appliedPatchesFile -Value $patchFileName
    Write-Host "Patch '$patchFileName' applied successfully."
}
