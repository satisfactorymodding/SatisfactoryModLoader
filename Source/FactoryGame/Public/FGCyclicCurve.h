// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveFloat.h"
#include "FGCyclicCurve.generated.h"

USTRUCT(BlueprintType)
struct FACTORYGAME_API FCyclicRuntimeFloatCurve
{
	GENERATED_USTRUCT_BODY()

	using ValueType = float;

	FCyclicRuntimeFloatCurve() = default;
	
	UPROPERTY( EditInstanceOnly )
	FRuntimeFloatCurve mCurveData;

	FORCEINLINE float ValueAt( float time ) const
	{
		return mCurveData.ExternalCurve ? mCurveData.ExternalCurve->GetFloatValue( time ) : mCurveData.GetRichCurveConst()->Eval( time );
	}

	FORCEINLINE void UpdateOrAddKey ( float time, float value )
	{
		fgcheck( !mCurveData.ExternalCurve );
		mCurveData.GetRichCurve()->UpdateOrAddKey( time, value );
	}
};

USTRUCT(BlueprintType)
struct FACTORYGAME_API FCyclicRuntimeColorCurve
{
	GENERATED_USTRUCT_BODY()
	using ValueType = FLinearColor;
	
	FCyclicRuntimeColorCurve() = default;
	
	UPROPERTY( EditInstanceOnly )
	FRuntimeCurveLinearColor mCurveData;

	FORCEINLINE FLinearColor ValueAt( float time ) const
	{
		return mCurveData.ExternalCurve ? mCurveData.ExternalCurve->GetLinearColorValue( time ) : mCurveData.GetLinearColorValue( time );
	}

	FORCEINLINE void UpdateOrAddKey ( float time, FLinearColor value )
	{
		fgcheck( !mCurveData.ExternalCurve );
		mCurveData.ColorCurves[0].UpdateOrAddKey( time, value.R );
		mCurveData.ColorCurves[1].UpdateOrAddKey( time, value.G );
		mCurveData.ColorCurves[2].UpdateOrAddKey( time, value.B );
		mCurveData.ColorCurves[3].UpdateOrAddKey( time, value.A );
	}
};
