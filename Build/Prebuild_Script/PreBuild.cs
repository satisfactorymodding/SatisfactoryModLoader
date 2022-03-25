using System;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

public class PreBuild
{
    #region Constants

    private const bool bVerboseLogging = false;
    private const bool bErrorDialogs = false;
    private const bool bDoFreeSpaceCheck = true;
    private const long minFreeSpace = 1024L * 1024L * 1024L * 30L; //30GB

    #endregion

    #region Variables

    public static DirectoryInfo ProjectDir = null;
    public static DirectoryInfo PluginDir = null;
    public static DirectoryInfo WwiseDir = null;

    #endregion

    public static void Main(string[] args)
    {
        //If loaded correctly, args should contain the project directory path. But may need to be joined with spaces
        string projectDir = String.Join(" ", args).Trim();
        try
        {
            if (!Directory.Exists(projectDir))
            {
                ExitWithError($"Invalid Project Directory. PreBuild initialized incorrectly or there was another error. \r\n\r\nDirectory Specified was \"{projectDir}\"");
            }
            else if (bVerboseLogging)
            {
                Console.WriteLine("Working Directory: " + projectDir);
            }
        }
        catch (Exception ex)
        {
            ExitWithException(ex);
        }
        //Unless something broke, the above shouldn't show up

        //Prepare Paths
        ProjectDir = new DirectoryInfo(projectDir);
        PluginDir = new DirectoryInfo(ProjectDir.FullName + "\\Plugins");
        WwiseDir = new DirectoryInfo(PluginDir.FullName + "\\Wwise");

        //Wwise check
        if (!WwiseDir.Exists) 
        {
            ExitWithError("Wwise is not installed. Please go back and follow the docs at https://docs.ficsit.app/. Do not skip or skim though them. Follow the docs exactly.");
        }

        //Perform Additional Tasks
        PatchFiles();
        if (bDoFreeSpaceCheck) CheckFreeSpace();


        //Done. Exit explicitly with 0 to avoid auto-passing any other exit codes. Any output written to Standard Error will still terminate build.
        if (bVerboseLogging) Console.WriteLine("Prebuild Complete");
        System.Environment.Exit(0);
    }

    //Warn if Free Space is low
    private static void CheckFreeSpace()
    {
        var SystemDriveLetter = System.Environment.SystemDirectory.Substring(0, 1);
        var ProjectDriveLetter = Assembly.GetExecutingAssembly().Location.Substring(0, 1);

        DriveInfo systemDrive = new DriveInfo(SystemDriveLetter);
        DriveInfo projectDrive = (SystemDriveLetter.Equals(ProjectDriveLetter) ? null : new DriveInfo(ProjectDriveLetter));

        if (systemDrive.AvailableFreeSpace < minFreeSpace)
        {
            //Space is low
            WriteWarning($"Warning: Drive {SystemDriveLetter} has less than 30GB of free space. Builds may fail.");
        }

        if (projectDrive != null)
        {
            if (projectDrive.AvailableFreeSpace < minFreeSpace)
            {
                //Space is low
                WriteWarning($"Drive {ProjectDriveLetter} has less than 30GB of free space. Builds may fail.");
            }
        }

    }

    #region Patching

    private static void PatchFiles()
    {
        //Patch Wwise header file for Linux builds
        FileInfo AkOcclusionObstructionServiceHeader = new FileInfo(WwiseDir.FullName + "\\Source\\AkAudio\\Classes\\OcclusionObstructionService\\AkOcclusionObstructionService.h");

        string Search = "class AkOcclusionObstructionService";
        string Replace = "class AKAUDIO_API AkOcclusionObstructionService";

        ReplaceTextInFile(AkOcclusionObstructionServiceHeader, Search, Replace);
    }

    private static void ReplaceTextInFile(FileInfo File, string Search, string Replace)
    {
        if (!File.Exists)
        {
            ExitWithError("Wwise is corrupt or not integrated into the project. Please reintegrate Wwise.");
        }

        string HeaderFileText = System.IO.File.ReadAllText(File.FullName);
        if (HeaderFileText.Contains(Search))
        {
            HeaderFileText = HeaderFileText.Replace(Search, Replace);
            System.IO.File.WriteAllText(File.FullName, HeaderFileText);
        }
    }

    #endregion

    #region Error Handling and Logging

    /// <summary>
    /// Write Warning to output. Non-failing.
    /// </summary>
    /// <param name="warning"></param>
    public static void WriteWarning(string warning)
    {
        Console.WriteLine($"Warning: {warning}");
    }

    /// <summary>
    /// Write Error to Standard Error. Will fail build.
    /// </summary>
    /// <param name="warning"></param>
    public static void WriteError(string warning)
    {
        Console.Error.WriteLine($"Error: {warning}");
    }

    /// <summary>
    /// Display an Error Message and exit.
    /// </summary>
    /// <param name="errorMessage"></param>
    /// <param name="title"></param>
    /// <param name="icon"></param>
    /// <param name="exitCode"></param>
    public static void ExitWithError(string errorMessage, string title = "FactoryGame Build Error", MessageBoxIcon icon = MessageBoxIcon.Error, int exitCode = 1)
    {
        Console.Error.WriteLine(errorMessage);
        if (bErrorDialogs) MessageBox.Show(errorMessage, title, MessageBoxButtons.OK, icon);
        Environment.Exit(exitCode);
    }

    /// <summary>
    /// Display an Exception an exit
    /// </summary>
    /// <param name="exception"></param>
    /// <param name="title"></param>
    /// <param name="icon"></param>
    /// <param name="exitCode"></param>
    public static void ExitWithException(Exception exception, string title = "FactoryGame Build Error", MessageBoxIcon icon = MessageBoxIcon.Error, int exitCode = 1)
    {
        Console.Error.WriteLine(exception.Message);
        Console.WriteLine(exception);
        if (bErrorDialogs) MessageBox.Show($"An Exception occurred, Please check the logs for more details.\r\n{exception.Message}\r\n{exception}", title, MessageBoxButtons.OK, icon);
        Environment.Exit(exitCode);
    }

    #endregion

}