# Example ContentLib Mod

This template was obtained from the
[ContentLib Documentation](https://docs.ficsit.app/contentlib/latest/index.html).

Before you release a mod from this template,
you must switch over some files to use your mod reference
instead of the current value of `ExampleContentLibMod`

Once you have decided on a
[Mod Reference](https://docs.ficsit.app/satisfactory-modding/latest/Development/BeginnersGuide/index.html#_mod_reference),
you will have to:

- Rename this plugin folder (from `ExampleContentLibMod` to `YourModReferenceHere`)
- Rename the .uplugin file in this directory (from `ExampleContentLibMod.uplugin` to `YourModReferenceHere.uplugin`)
- Edit the FriendlyName, Description, and CreatedBy fields of `YourModReferenceHere.uplugin`
- You may need to change the SemVersion value of the SML plugin to the latest SML version number.
- You may need to change the SemVersion value of the ContentLib plugin to the latest ContentLib version number.

You should check the documentation to see if anything else needs to be done,
as it will be updated more frequently than this readme file.
