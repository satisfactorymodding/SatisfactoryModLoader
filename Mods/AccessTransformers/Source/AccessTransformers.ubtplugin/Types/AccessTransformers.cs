using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using EpicGames.Core;
using EpicGames.UHT.Types;
using EpicGames.UHT.Utils;
using UnrealBuildBase;
using UnrealBuildTool;

namespace AccessTransformers.Types;

public static class AccessTransformers
{
    public abstract class BaseAccessTransformer
    {
        public readonly string File;
        public readonly int Line;

        protected BaseAccessTransformer(string file, int line)
        {
            File = file;
            Line = line;
        }
        
        public abstract string Class { get; }
        public abstract List<string>? GetImplementation(UhtType type);
    }
    public class FriendAccessTransformer : BaseAccessTransformer
    {
        private readonly string _className;
        private readonly string _friendClassName;

        public FriendAccessTransformer(string className, string friendClassName, string file, int line) : base(file ,line)
        {
            _className = className;
            _friendClassName = friendClassName;
        }
        
        public override string ToString()
        {
            return $"{_className} -> {_friendClassName}";
        }

        public override string Class => _className;
        public override List<string> GetImplementation(UhtType type)
        {
            return new List<string> { "friend class " + _friendClassName + ";" };
        }
    }

    public class AccessorAccessTransformer : BaseAccessTransformer
    {
        private readonly string _className;
        private readonly string _fieldName;
        
        public AccessorAccessTransformer(string className, string fieldName, string file, int line) : base(file ,line)
        {
            _className = className;
            _fieldName = fieldName;
        }
        
        public override string ToString()
        {
            return $"{_className}:{_fieldName}";
        }

        public override string Class => _className;
        public override List<string>? GetImplementation(UhtType type)
        {
            var property = (UhtProperty?)type.Children.Find((child) => child.EngineName == _fieldName && child.EngineType == UhtEngineType.Property);
            if (property == null)
                return null;


            StringBuilder getterBuilder = new();
            getterBuilder.Append("FORCEINLINE ");
            property.AppendText(getterBuilder, UhtPropertyTextType.GenericFunctionArgOrRetVal);
            getterBuilder.Append(' ').Append("Get").Append(property.SourceName).Append("() const { return ").Append(property.SourceName).Append("; }");
            
            StringBuilder setterBuilder = new();
            setterBuilder.Append("FORCEINLINE ");
            setterBuilder.Append("void Set").Append(property.SourceName).Append($"(");
            property.AppendText(setterBuilder, UhtPropertyTextType.GenericFunctionArgOrRetVal);
            setterBuilder.Append(" value) { ").Append(property.SourceName).Append(" = value; }");
            
            return new List<string> { getterBuilder.ToString(), setterBuilder.ToString() };
        }
    }

    private static AccessTransformerTable<FriendAccessTransformer> _friendAccessTransformers = new();
    private static AccessTransformerTable<AccessorAccessTransformer> _accessorAccessTransformers = new();

    public static AccessTransformerTable<FriendAccessTransformer> FriendAccessTransformers => _friendAccessTransformers;
    public static AccessTransformerTable<AccessorAccessTransformer> AccessorAccessTransformers => _accessorAccessTransformers;

    public static void Load(UhtSession session)
    {
        // UHT can run multiple times in the same UBT process (for different targets for example)
        // but it should never run concurrently, so we only need to clean the previous state when
        // starting a new UHT session.
        // If UE ever makes changes that run UHT concurrently, replace this with per-UhtSession AccessTransformerTables
        _friendAccessTransformers = new();
        _accessorAccessTransformers = new();
        var availablePlugins = PluginsBase.EnumeratePlugins(new FileReference(session.ProjectFile!));
        foreach (var plugin in availablePlugins)
        {
            FileReference accessTransformersFile = new(Path.Combine(plugin.Directory.FullName, "Config", "AccessTransformers.ini"));
            if (accessTransformersFile.ToFileInfo().Exists)
            {
                var accessTransformers = new ConfigFile(accessTransformersFile, ConfigLineAction.Add);
                accessTransformers.TryGetSection("AccessTransformers", out var section);
                section?.Lines.ForEach((line) =>
                {
                    switch (line.Key)
                    {
                        case "Friend":
                        {
                            try
                            {
                                var data = StructParser.Parse(line.Value);
                                FriendAccessTransformers.Add(plugin.GetFileNameWithoutAnyExtensions(),
                                    new FriendAccessTransformer(data["Class"], data["FriendClass"],
                                        accessTransformersFile.FullName, section.Lines.IndexOf(line) + 2));
                            }
                            catch (Exception e)
                            {
                                session.AddMessage(UhtMessage.MakeMessage(UhtMessageType.Error, null,
                                    accessTransformersFile.FullName,
                                    section.Lines.IndexOf(line) + 2,
                                    $"Error parsing Friend \"{line.Value}\": {e.Message}"));
                            }

                            break;
                        }
                        case "Accessor":
                        {
                            try
                            {
                                var data = StructParser.Parse(line.Value);
                                AccessorAccessTransformers.Add(plugin.GetFileNameWithoutAnyExtensions(),
                                    new AccessorAccessTransformer(data["Class"], data["Property"],
                                        accessTransformersFile.FullName, section.Lines.IndexOf(line) + 2));
                            }
                            catch (Exception e)
                            {
                                session.AddMessage(UhtMessage.MakeMessage(UhtMessageType.Error, null,
                                    accessTransformersFile.FullName,
                                    section.Lines.IndexOf(line) + 2,
                                    $"Error parsing Accessor \"{line.Value}\": {e.Message}"));
                            }

                            break;
                        }
                    }
                });
            }
        }
    }
}
