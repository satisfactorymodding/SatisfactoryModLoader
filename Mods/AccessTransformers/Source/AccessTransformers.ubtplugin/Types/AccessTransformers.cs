using System.Collections.Generic;
using System.IO;
using System.Text;
using EpicGames.Core;
using EpicGames.UHT.Types;
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
        public override List<string>? GetImplementation(UhtType type)
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
            property.AppendText(getterBuilder, UhtPropertyTextType.GenericFunctionArgOrRetVal);
            getterBuilder.Append(' ').Append("Get").Append(property.SourceName).Append("() const { return ").Append(property.SourceName).Append("; }");
            
            StringBuilder setterBuilder = new();
            setterBuilder.Append("void Set").Append(property.SourceName).Append($"(");
            property.AppendText(setterBuilder, UhtPropertyTextType.GenericFunctionArgOrRetVal);
            setterBuilder.Append(" value) { ").Append(property.SourceName).Append(" = value; }");
            
            return new List<string> { getterBuilder.ToString(), setterBuilder.ToString() };
        }
    }

    public static readonly AccessTransformerTable<FriendAccessTransformer> FriendAccessTransformers = new();
    public static readonly AccessTransformerTable<AccessorAccessTransformer> AccessorAccessTransformers = new();

    public static void Load(string projectFile)
    {
        var availablePlugins = PluginsBase.EnumeratePlugins(new FileReference(projectFile));
        foreach (var plugin in availablePlugins)
        {
            FileReference accessTransformersFile = new(Path.Combine(plugin.Directory.FullName, "Config", "AccessTransformers.ini"));
            if (accessTransformersFile.ToFileInfo().Exists)
            {
                var accessTransformers = new ConfigFile(accessTransformersFile, ConfigLineAction.Add);
                accessTransformers.TryGetSection("AccessTransformers", out var section);
                section!.Lines.ForEach((line) =>
                {
                    switch (line.Key)
                    {
                        case "Friend": {
							var data = StructParser.Parse(line.Value);
                            FriendAccessTransformers.Add(plugin.GetFileNameWithoutAnyExtensions(),
                                new FriendAccessTransformer(data["Class"], data["FriendClass"], accessTransformersFile.FullName, section.Lines.IndexOf(line) + 1));
                            break;
						}
                        case "Accessor": {
							var data = StructParser.Parse(line.Value);
                            AccessorAccessTransformers.Add(plugin.GetFileNameWithoutAnyExtensions(),
                                new AccessorAccessTransformer(data["Class"], data["Property"], accessTransformersFile.FullName, section.Lines.IndexOf(line) + 1));
                            break;
						}
                    }
                });
            }
        }
    }
}