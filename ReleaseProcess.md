# Release Process

Rough notes on the steps we follow when making an SML release.

1. Add things demonstrating/testing new features to Example Mod and [SMLFeatureTests](https://github.com/satisfactorymodding/SMLFeatureTests) when relevant
1. Ensure docs repository is updated (on <https://docs-dev.ficsit.app/>, at least)
1. Write version-specific Updating Guide on the docs when relevant
1. Write [draft release changelog](https://github.com/satisfactorymodding/SatisfactoryModLoader/releases/) on GitHub, following the format from the previous release
1. Ensure SML VS project and mod compiles on a developer machine
1. Ensure the CI passes on the `dev` branch
1. Open a SML PR of `dev` to `master` and get approvals
1. Update the docs versions
    1. Create branch for old version
    1. Commit on old version branch: Set version number for version branch. Point to archived download links for SML and engine
        - See [79ae88c](https://github.com/satisfactorymodding/Documentation/commit/79ae88ca19731b361167924606d554d0496232b8) for example
    1. Commit on main (or dev to go into main) branch: add old version branch as another branch to build
        - See [1e7acf4](https://github.com/satisfactorymodding/Documentation/commit/1e7acf4d396626e80ea2f2de00fe38109fad4ecc) for example
1. After merging the PR, commit on master a `Bump version` commit
    - SML.uplugin GameVersion and SemVersion
    - ExampleMod.uplugin GameVersion and SML dependency version
1. Wait for CI to finish. We don't upload locally compiled versions so the version detailed suffix is consistent across versions.
1. While waiting for CI to finish:
    1. Merge the docs PR to master
    1. Update [SMLFeatureTests](https://github.com/satisfactorymodding/SMLFeatureTests) SML dependency version
1. Upload CI artifact to GitHub as release. Attach all of the CI zip file contents as release items (Windows (Client), Windows Server, Linux Server, SML (multi-target))
1. Upload CI artifact to SMR as a new version of the SML mod (multi-target zip file), SMR changelog is the GitHub changelog
1. Post in #toolkit-updates and/or #announcements on Discord
1. Clear/create ficsit.app announcements as needed
    1. Get a token from your browser cookies after logging into ficsit.app
    1. Visit <https://api.ficsit.app/v2>
    1. Set headers to:

        ```json
        {
            "Authorization": "your_token_here",
        }
        ```

    - To get active announcements, use:

        ```gql
        {
            getAnnouncements {
                importance
                message
                id
            }
        }
        ```

    - To create an announcement, use:

        ```gql
        # Query
        mutation CreateAnnouncement($announcement: NewAnnouncement!) {
            createAnnouncement(announcement: $announcement) {
                id
                message
                importance
            }
        }

        # Variables
        {
            "announcement": {
                "message": "Hello World",
                "importance": "Info"
            }
        }
        ```

    - To delete an announcement, use:

        ```gql
        # Query
        mutation DeleteAnnouncement($id: AnnouncementID!) {
            deleteAnnouncement(announcementId: $id)
        }

        # Variables
        {
            "id": "idFromGetGoesHere"
        }
        ```
