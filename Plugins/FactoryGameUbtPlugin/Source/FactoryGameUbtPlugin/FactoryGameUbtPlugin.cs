// Copyright Epic Games, Inc. All Rights Reserved.

using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using EpicGames.Core;
using EpicGames.UHT.Tables;
using EpicGames.UHT.Types;
using EpicGames.UHT.Utils;

namespace FactoryGameUbtPlugin
{
	class FGServerRequestHandlerMetadata
	{
		public UhtFunction? Function;
		public UhtFunction? AsyncCompleteRequestFunction;
		public string RequestHandlerName = "";
		public string RequestHandlerPrivilegeLevel = "";
		public bool EnableCompression = false;
	}
	
	class FGServerRequestEmitterMetadata
	{
		public UhtFunction? EmitterFunction;
		public UhtFunction? ResponseHandlerFunction;
		public string RequestName = "";
		public string RequestHandlerPrivilegeLevel = "";
		public List<string> PassthroughParams = new List<string>();
	}

	[UnrealHeaderTool]
    class FactoryGameExporter
    {
	    private static readonly List<string> AllowedPrivilegeLevels =
		    new() { "NotAuthenticated", "Client", "Administrator", "InitialAdmin" };
	    private static readonly string DefaultPrivilegeLevel = "NotAuthenticated";

	    // FGServerRequestHandler
		[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]
		private static void FGServerRequestHandlerSpecifier(UhtSpecifierContext specifierContext, StringView? value)
		{
			UhtFunction function = (UhtFunction)specifierContext.Type;
			function.MetaData.Add( "FGServerRequestHandler", value?.ToString() ?? "" );
		}
		
		// FGServerAsyncCompleteRequest
		[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]
		private static void FGServerAsyncCompleteRequestSpecifier(UhtSpecifierContext specifierContext, StringView? value)
		{
			UhtFunction function = (UhtFunction)specifierContext.Type;
			function.MetaData.Add( "FGServerAsyncCompleteRequest", value?.ToString() ?? "" );
			function.MetaData.Add("CSS_CustomProcessEvent", "InternalCompleteAPIRequest");
			function.MetaData.Add("CSS_CustomProcessEventAPIMacro", "FACTORYDEDICATEDSERVER_API");
			
			function.FunctionFlags |= EFunctionFlags.Event;
			function.FunctionFlags |= EFunctionFlags.BlueprintEvent;
			function.FunctionFlags &= ~EFunctionFlags.Native;
			function.MetaData.Add("BlueprintInternalUseOnly", "true");
		}
		
		// FGServerRequestPrivilegeLevel
		[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.String)]
		private static void FGServerRequestPrivilegeLevelSpecifier(UhtSpecifierContext specifierContext, StringView value)
		{
			UhtFunction function = (UhtFunction)specifierContext.Type;

			var privilegeLevel = value.ToString();
			if (string.IsNullOrEmpty(privilegeLevel))
			{
				privilegeLevel = DefaultPrivilegeLevel;
			}

			if (!AllowedPrivilegeLevels.Contains(privilegeLevel))
			{
				specifierContext.MessageSite.LogError(specifierContext.TokenReader.InputLine, 
					$"FactoryGame: Only Allowed FGServerRequestPrivilegeLevel values are {string.Join(", ", AllowedPrivilegeLevels)}. Found: {privilegeLevel}");
				privilegeLevel = DefaultPrivilegeLevel;
			}
			function.MetaData.Add( "FGServerRequestPrivilegeLevel", privilegeLevel );
		}

		// FGServerRequestHandlerEnableCompression
		[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]
		private static void FGServerRequestHandlerEnableCompressionSpecifier(UhtSpecifierContext specifierContext)
		{
			UhtFunction function = (UhtFunction)specifierContext.Type;
			function.MetaData.Add("FGServerRequestHandlerEnableCompression", true);
		}
		
		// FGServerRequest
		[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]
		private static void FGServerRequestSpecifier(UhtSpecifierContext specifierContext, StringView? value)
		{
			UhtFunction function = (UhtFunction)specifierContext.Type;
			function.MetaData.Add( "FGServerRequest", value?.ToString() ?? "" );
			function.MetaData.Add("CSS_CustomProcessEvent", "InternalProcessServerAPIRequest");
			function.MetaData.Add("CSS_CustomProcessEventAPIMacro", "FACTORYDEDICATEDCLIENT_API");

			function.FunctionFlags |= EFunctionFlags.Event;
			function.FunctionFlags |= EFunctionFlags.BlueprintEvent;
			function.FunctionFlags &= ~EFunctionFlags.Native;
			function.MetaData.Add("BlueprintInternalUseOnly", "true");
		}
		
		// FGServerResponse
		[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.OptionalString)]
		private static void FGServerResponseSpecifier(UhtSpecifierContext specifierContext, StringView? value)
		{
			UhtFunction function = (UhtFunction)specifierContext.Type;

			function.MetaData.Add( "FGServerResponse", value?.ToString() ?? "" );
		}

		// FGServerRequestPassThrough
		[UhtSpecifier(Extends = UhtTableNames.PropertyArgument, ValueType = UhtSpecifierValueType.None)]
		private static void FGServerRequestPassThroughSpecifier(UhtSpecifierContext specifierContext)
		{
			specifierContext.MetaData.Add("FGServerRequestPassThrough", true);
		}

		private static void ProcessRequestHandlerFunction(UhtFunction function, Dictionary<string, FGServerRequestHandlerMetadata> requestHandlers)
		{
			if (function.MetaData.ContainsKey("FGServerRequestHandler"))
			{
				var functionName = function.MetaData.GetValueOrDefault("FGServerRequestHandler");
				var privilegeLevel = function.MetaData.GetValueOrDefault("FGServerRequestPrivilegeLevel");

				if (string.IsNullOrEmpty(functionName))
				{
					functionName = function.EngineName.Replace("Handler_", "");
				}
				if (!requestHandlers.ContainsKey(functionName))
				{
					requestHandlers.Add(functionName, new FGServerRequestHandlerMetadata { RequestHandlerName = functionName });
				}
				FGServerRequestHandlerMetadata handlerMetadata = requestHandlers[functionName];
				handlerMetadata.Function = function;
				handlerMetadata.RequestHandlerPrivilegeLevel = privilegeLevel;
				handlerMetadata.EnableCompression = function.MetaData.ContainsKey("FGServerRequestHandlerEnableCompression");
			}

			if (function.MetaData.ContainsKey("FGServerAsyncCompleteRequest"))
			{
				var functionName = function.MetaData.GetValueOrDefault("FGServerAsyncCompleteRequest");
				
				if (string.IsNullOrEmpty(functionName))
				{
					functionName = function.EngineName.Replace("CompleteRequest_", "");
				}
				if (!requestHandlers.ContainsKey(functionName))
				{
					requestHandlers.Add(functionName, new FGServerRequestHandlerMetadata { RequestHandlerName = functionName });
				}
				requestHandlers[functionName].AsyncCompleteRequestFunction = function;
			}
		}

		private static void ProcessRequestEmitterFunction(UhtFunction function, Dictionary<string, FGServerRequestEmitterMetadata> requestEmitters)
		{
			string? clientRequestName;
			string? clientResponseName;
			if (function.MetaData.TryGetValue("FGServerRequest", out clientRequestName))
			{
				var privilegeLevel = function.MetaData.GetValueOrDefault("FGServerRequestPrivilegeLevel");
				
				if (string.IsNullOrEmpty(clientRequestName))
				{
					clientRequestName = function.EngineName.Replace("Request_", "");
				}
				if (!requestEmitters.ContainsKey(clientRequestName))
				{
					requestEmitters.Add(clientRequestName, new FGServerRequestEmitterMetadata { RequestName = clientRequestName });
				}
				requestEmitters[clientRequestName]!.EmitterFunction = function;
				requestEmitters[clientRequestName]!.RequestHandlerPrivilegeLevel = privilegeLevel;
				
				for (int i = 0; i < function.ParameterProperties.Length; ++i)
				{
					if (function.ParameterProperties.ToArray()[i].MetaData.ContainsKey("FGServerRequestPassThrough"))
					{
						requestEmitters[clientRequestName].PassthroughParams.Add(function.ParameterProperties.ToArray()[i].EngineName);
					}
				}
			}
			else if (function.MetaData.TryGetValue("FGServerResponse", out clientResponseName))
			{
				if (string.IsNullOrEmpty(clientResponseName))
				{
					clientResponseName = function.EngineName.Replace("Response_", "");
				}
				if (!requestEmitters.ContainsKey(clientResponseName))
				{
					requestEmitters.Add(clientResponseName, new FGServerRequestEmitterMetadata { RequestName = clientResponseName });
				}
				requestEmitters[clientResponseName]!.ResponseHandlerFunction = function;
			}
		}

		private static void GenerateRequestHandlers(IUhtExportFactory factory, UhtPackage package, List<FGServerRequestHandlerMetadata> requestHandlers, List<FGServerRequestEmitterMetadata> requestEmitters)
		{
			StringBuilder stringBuilder = new StringBuilder();

			stringBuilder.AppendLine("");
			stringBuilder.AppendLine("#include \"CoreMinimal.h\"");
			stringBuilder.AppendLine("#include \"Server/FGServerAPIManagerInternals.h\"");
			
			List<UhtFunction> allFunctionDeclarations = new List<UhtFunction>();
			
			foreach (var requestHandler in requestHandlers)
			{
				if (requestHandler.AsyncCompleteRequestFunction != null && requestHandler.Function == null)
				{
					requestHandler.AsyncCompleteRequestFunction.LogError($"FactoryGame: FGServerAsyncCompleteRequest is declared without a matching FGServerRequestHandler");
					continue;
				}
				
				allFunctionDeclarations.Add(requestHandler.Function!);

				if (requestHandler.AsyncCompleteRequestFunction != null)
				{
					allFunctionDeclarations.Add(requestHandler.AsyncCompleteRequestFunction);
				}
			}
			
			foreach (var requestEmitter in requestEmitters)
			{
				if (requestEmitter.EmitterFunction == null)
				{
					requestEmitter.ResponseHandlerFunction!.LogError($"FactoryGame: FGClientResponse function is declared without a matching FGClientRequest");
					continue;
				}
				allFunctionDeclarations.Add(requestEmitter.EmitterFunction);
				if (requestEmitter.ResponseHandlerFunction != null)
				{
					allFunctionDeclarations.Add(requestEmitter.ResponseHandlerFunction);
				}
			}

			stringBuilder.AppendLine("");

			foreach (var function in allFunctionDeclarations.Distinct())
			{
				stringBuilder.Append("extern UFunction* Z_Construct_U").Append(function.EngineClassName).AppendOuterNames(function).Append("();\n");
			}
			stringBuilder.AppendLine("");

			stringBuilder.AppendLine($"static void Z_{package.ShortName}_PopulateIOHandlers( TArray<FFGRequestHandlerFunctionDefinition>& OutRequestHandlers, TArray<FFGRequestEmitterFunctionDefinition>& OutRequestEmitters )");
			stringBuilder.AppendLine("{");

			foreach (var requestHandler in requestHandlers)
			{
				stringBuilder.Append($"\tOutRequestHandlers.Add( FFGRequestHandlerFunctionDefinition{{ ");
				stringBuilder.Append("Z_Construct_U").Append(requestHandler.Function!.EngineClassName).AppendOuterNames(requestHandler.Function!);
				stringBuilder.Append($"(), TEXT(\"{requestHandler.RequestHandlerName}\"), TEXT(\"{requestHandler.RequestHandlerPrivilegeLevel}\")");

				if (requestHandler.AsyncCompleteRequestFunction != null)
				{
					stringBuilder.Append(", Z_Construct_U").Append(requestHandler.AsyncCompleteRequestFunction!.EngineClassName).AppendOuterNames(requestHandler.AsyncCompleteRequestFunction!);
					stringBuilder.Append("()");
				}
				else
				{
					stringBuilder.Append(", nullptr");
				}

				stringBuilder.Append(", ");
				stringBuilder.Append(requestHandler.EnableCompression ? "true" : "false");
				stringBuilder.AppendLine(" } );");
			}
			stringBuilder.AppendLine("");
			
			foreach (var requestEmitter in requestEmitters)
			{
				stringBuilder.Append("\tOutRequestEmitters.Add( FFGRequestEmitterFunctionDefinition{ ");
				stringBuilder.Append("Z_Construct_U").Append(requestEmitter.EmitterFunction!.EngineClassName).AppendOuterNames(requestEmitter.EmitterFunction!);
				stringBuilder.Append("(), ");

				if (requestEmitter.ResponseHandlerFunction != null)
				{
					stringBuilder.Append("Z_Construct_U").Append(requestEmitter.ResponseHandlerFunction!.EngineClassName).AppendOuterNames(requestEmitter.ResponseHandlerFunction!);
					stringBuilder.Append("(), ");
				}
				else
				{
					stringBuilder.Append("nullptr, ");
				}

				stringBuilder.Append($"TEXT(\"{requestEmitter.RequestName}\"), ");
				stringBuilder.Append($"TEXT(\"{requestEmitter.RequestHandlerPrivilegeLevel}\"), ");
				stringBuilder.Append("{ ");

				for (int i = 0; i < requestEmitter.PassthroughParams.Count; ++i)
				{
					if (i != 0) stringBuilder.Append(", ");
					stringBuilder.Append($"TEXT(\"{requestEmitter.PassthroughParams[i]}\")");
				}

				stringBuilder.Append(" }");
				stringBuilder.AppendLine(" } );");
			}
			
			stringBuilder.AppendLine("}");
			stringBuilder.AppendLine("");
			
			stringBuilder.AppendLine($"static FFGRequestIORegistrar GRegisterIOHandlers_{package.ShortName}( &Z_{package.ShortName}_PopulateIOHandlers );");
			stringBuilder.AppendLine("");
			
			var filePath = Path.Combine(package.Module.OutputDirectory, package.ShortName) + ".request_handlers.gen.cpp";
			factory.CommitOutput( filePath, stringBuilder );
		}

		[UhtExporter(Name = "FactoryGameUbtPlugin", Description = "FactoryGame specific UBT Plugin", Options = UhtExporterOptions.Default, ModuleName="FactoryGame", 
			CppFilters = new string[] {"*.request_handlers.gen.cpp"})]
		private static void FactoryGameMain(IUhtExportFactory factory)
		{
			foreach (var uhtPackage in factory.Session.Packages)
			{
				if (uhtPackage.IsPartOfEngine) continue;
				Dictionary<string, FGServerRequestHandlerMetadata> allRequestHandlers = new Dictionary<string, FGServerRequestHandlerMetadata>();
				Dictionary<string, FGServerRequestEmitterMetadata> allRequestEmitters = new Dictionary<string, FGServerRequestEmitterMetadata>();
				
				foreach (var uhtHeaderFile in uhtPackage.Children)
				{
					foreach (var uhtType in uhtHeaderFile.Children)
					{
						if (uhtType is UhtClass uhtClass)
						{
							foreach (var function in uhtClass.Functions)
							{
								ProcessRequestHandlerFunction(function, allRequestHandlers);
								ProcessRequestEmitterFunction(function, allRequestEmitters);
							}
						}
					}
				}

				if (allRequestHandlers.Count != 0 || allRequestEmitters.Count != 0)
				{
					GenerateRequestHandlers(factory, uhtPackage, allRequestHandlers.Values.ToList(), allRequestEmitters.Values.ToList());
				}
			}
		}
	}
}
