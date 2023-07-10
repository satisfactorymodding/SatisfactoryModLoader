using System.Diagnostics.CodeAnalysis;
using EpicGames.Core;
using EpicGames.UHT.Tables;
using EpicGames.UHT.Utils;

[UnrealHeaderTool]
[SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Attribute accessed method")]
public class UhtCSSExtras
{
	[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.SingleString)]
	private static void CustomEventUsingSpecifier(UhtSpecifierContext specifierContext, StringView value)
	{
		
	}

	[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.None)]
	private static void CheatBoardSpecifier(UhtSpecifierContext specifierContext)
	{
		
	}

	[UhtSpecifier(Extends = UhtTableNames.PropertyMember, ValueType = UhtSpecifierValueType.None)]
	private static void CustomSerializationSpecifier(UhtSpecifierContext specifierContext)
	{
		
	}
}