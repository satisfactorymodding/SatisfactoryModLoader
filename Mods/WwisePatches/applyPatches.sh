#!/bin/bash

# Get the script directory and set up paths
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
patches_folder="$script_dir/Patches"
third_party_dir="$script_dir/ThirdParty"

# Ensure the patches folder exists
if [[ ! -d "$patches_folder" ]]; then
    echo "The specified patches folder does not exist: $patches_folder"
    exit 1
fi

# Check if patch command is available
if ! command -v patch &> /dev/null; then
    echo "The patch executable was not found in PATH"
    exit 1
fi

# Get the project dir passed as argument
if [[ $# -lt 1 ]]; then
    echo "Usage: applyPatches.sh <path>"
    exit 1
fi
project_dir="$1"

if [[ ! -d "$project_dir" ]]; then
    echo "The specified project dir does not exist: $project_dir"
    exit 1
fi

# Check patches that have already been applied
applied_patches_file="$project_dir/Plugins/Wwise/applied_patches.txt"
applied_patches=()
if [[ -f "$applied_patches_file" ]]; then
    # Read applied patches into array, handling empty lines
    while IFS= read -r line || [[ -n "$line" ]]; do
        [[ -n "$line" ]] && applied_patches+=("$line")
    done < "$applied_patches_file"
fi

# Get all .patch files in the patches folder, sorted alphabetically
mapfile -t patch_files < <(find "$patches_folder" -name "*.patch" -type f | sort)

# Check if there are any .patch files in the folder
if [[ ${#patch_files[@]} -eq 0 ]]; then
    echo "No .patch files found in the folder: $patches_folder"
    exit 1
fi

# Function to check if patch is already applied
is_patch_applied() {
    local patch_name="$1"
    for applied in "${applied_patches[@]}"; do
        if [[ "$applied" == "$patch_name" ]]; then
            return 0
        fi
    done
    return 1
}

# Convert Wwise source file line endings to LF for patching
find "$project_dir"/Plugins/Wwise*/Source -type f | xargs dos2unix -q -k

# Iterate through the patch files
for patch_file in "${patch_files[@]}"; do
    patch_filename="$(basename "$patch_file")"
    
    # Skip if the patch has already been applied
    if is_patch_applied "$patch_filename"; then
        echo "Patch '$patch_filename' has already been applied. Skipping."
        continue
    fi
    
    # Read patch content and ensure it has LF line endings
    patch_content="$(cat "$patch_file")"
    patch_content="${patch_content//$'\r\n'/$'\n'}"
    
    # Create temporary file for patch content
    temp_file="$(mktemp)"
    echo -n "$patch_content" > "$temp_file"
    
    # Verify the patch can be applied with --dry-run before applying it
    dry_run_args="-N -s -p1 -d \"$project_dir\" -i \"$temp_file\" --dry-run"
    echo "Checking if patch can be applied: patch $dry_run_args"
    
    if ! patch -N -s -p1 -d "$project_dir" -i "$temp_file" --dry-run; then
        echo "Error: Dry run failed for patch '$patch_filename'. Exiting."
        rm -f "$temp_file"
        exit 1
    fi
    
    # Apply the patch if dry run is successful
    apply_args="-N -s -p1 -d \"$project_dir\" -i \"$temp_file\""
    echo "Applying patch: patch $apply_args"
    
    if ! patch -N -s -p1 -d "$project_dir" -i "$temp_file"; then
        echo "Error: Failed to apply patch '$patch_filename'. Exiting."
        rm -f "$temp_file"
        exit 1
    fi
    
    # Cleanup temp file
    rm -f "$temp_file"
    
    # After applying the patch successfully, log it
    echo "$patch_filename" >> "$applied_patches_file"
    echo "Patch '$patch_filename' applied successfully."
done

# Undo the dos2unix conversion for Wwise source files
find "$project_dir"/Plugins/Wwise*/Source -type f | xargs unix2dos -q -k
