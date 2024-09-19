#pragma once

struct FEditorDebugString
{
	FString Text;
	FLinearColor TextColor;
	int FontSize;
	FVector TextLocation;
	bool DrawShadow;
	float Duration;
	float TimeRemaining;

	FEditorDebugString(const FVector& InTextLocation, const FString& InText, FLinearColor InTextColor, float InDuration, bool bInDrawShadow, int32 InFontSize)
		: Text(InText)
		, TextColor(InTextColor)
		, FontSize(InFontSize)
		, TextLocation(InTextLocation)
		, DrawShadow(bInDrawShadow)
		, Duration(InDuration)
		, TimeRemaining(InDuration)
	{
	};
};
