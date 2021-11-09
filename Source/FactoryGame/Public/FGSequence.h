// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGSequence.generated.h"

static const float SEQUENCE_FRAME_RATE = 30.0f;

USTRUCT(BlueprintType)
struct FFGSequenceKeyFrame
{
	GENERATED_BODY()

	FFGSequenceKeyFrame() :
		IsSet( false )
	{};

	UPROPERTY( BlueprintReadWrite, SaveGame )
	FFrameTime KeyFrameTime;

	UPROPERTY( BlueprintReadWrite, SaveGame )
	bool IsSet;

	// Ease in and similar
};

USTRUCT(BlueprintType)
struct FFGSequenceFloatKeyFrame : public FFGSequenceKeyFrame
{
	GENERATED_BODY()

	FFGSequenceFloatKeyFrame() :
		Value( 0.f )
	{};

	FFGSequenceFloatKeyFrame( const FFrameTime& frameTime, const float value ) :
		Value( value )
	{
		KeyFrameTime = frameTime;
		IsSet = true;
	};

	UPROPERTY( BlueprintReadWrite, SaveGame )
	float Value;
};

USTRUCT(BlueprintType)
struct FFGSequenceSection
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, SaveGame )
	FFrameTime SectionFrameTime;

	float GetSectionTimeInSeconds() const;

};

USTRUCT(BlueprintType)
struct FFGSequenceFloatSection : public FFGSequenceSection
{
	GENERATED_BODY()

	FFGSequenceFloatSection()
	{}

	FFGSequenceFloatSection( const FFrameTime& frameTime, const float FOV)
	{
		SectionFrameTime = frameTime;
		Value = FFGSequenceFloatKeyFrame( frameTime, FOV );
	};

	UPROPERTY( BlueprintReadWrite, SaveGame )
	FFGSequenceFloatKeyFrame Value;
};

USTRUCT(BlueprintType)
struct FFGSequenceVectorSection : public FFGSequenceSection
{
	GENERATED_BODY()

	FFGSequenceVectorSection()
	{};

	FFGSequenceVectorSection( const FFrameTime& frameTime, const FVector vector )
	{
		SectionFrameTime = frameTime;
		X = FFGSequenceFloatKeyFrame( frameTime, vector.X );
		Y = FFGSequenceFloatKeyFrame( frameTime, vector.Y );
		Z = FFGSequenceFloatKeyFrame( frameTime, vector.Z );
	};

	FFGSequenceVectorSection( const FFrameTime& frameTime, const FRotator rotator )
	{
		SectionFrameTime = frameTime;
		X = FFGSequenceFloatKeyFrame( frameTime, rotator.Roll );
		Y = FFGSequenceFloatKeyFrame( frameTime, rotator.Pitch );
		Z = FFGSequenceFloatKeyFrame( frameTime, rotator.Yaw );
	};

	UPROPERTY( BlueprintReadWrite, SaveGame ) // Roll
	FFGSequenceFloatKeyFrame X;
	UPROPERTY( BlueprintReadWrite, SaveGame ) // Pitch
	FFGSequenceFloatKeyFrame Y;
	UPROPERTY( BlueprintReadWrite, SaveGame ) // Yaw
	FFGSequenceFloatKeyFrame Z;

	FVector GetSequenceAsVector() const { return FVector( X.Value, Y.Value, Z.Value ); }
	FRotator GetSequenceAsRotator() const { return FRotator( Y.Value, Z.Value, X.Value ); }
};

USTRUCT(BlueprintType)
struct FFGSequenceTrack
{
	GENERATED_BODY()

	FFGSequenceTrack(){};

};

USTRUCT(BlueprintType)
struct FFGSequenceFloatTrack : public FFGSequenceTrack
{
	GENERATED_BODY()

	FFGSequenceFloatTrack(){};

	UPROPERTY( BlueprintReadWrite, SaveGame )
	TArray<FFGSequenceFloatSection> FloatSections;

	void AddFloatSection( FFGSequenceFloatSection section );
	const FFrameTime GetLastFrameTime() const;
	bool EvaluateFloatTrack( float seconds, float& out_float );
	bool EvaluateFloatTrack( FFrameTime frameTime, float& out_float );
};

USTRUCT(BlueprintType)
struct FFGSequenceVectorTrack : public FFGSequenceTrack
{
	GENERATED_BODY()

	FFGSequenceVectorTrack(){};

	UPROPERTY( BlueprintReadWrite, SaveGame )
	TArray<FFGSequenceVectorSection> VectorSections;

	void AddVectorSection( FFGSequenceVectorSection section );
	const FFrameTime GetLastFrameTime() const;
	bool EvaluateLocationTrack(float seconds, FVector& out_location);
	bool EvaluateLocationTrack(FFrameTime frameTime, FVector& out_location);
	bool EvaluateRotationTrack(float seconds, FRotator& out_rotation);
	bool EvaluateRotationTrack(FFrameTime frameTime, FRotator& out_rotation);
};

USTRUCT(BlueprintType)
struct FFGSequence
{
	GENERATED_BODY()
	
	FFGSequence() :
		SequenceStart( 0 ),
		SequenceEnd( 150 ),
		Pawn( nullptr ),
		PlayerController( nullptr ),
		IsPlaying( false ),
		SequenceTimer( 0.f ),
		SequenceEndTime( 0.f )
	{}

public:
	UPROPERTY( BlueprintReadWrite, SaveGame )
	FFGSequenceVectorTrack LocationTrack;
	UPROPERTY( BlueprintReadWrite, SaveGame )
	FFGSequenceVectorTrack RotationTrack;
	UPROPERTY( BlueprintReadWrite, SaveGame )
	FFGSequenceFloatTrack FOVTrack;

	void AddPlayerLocation( const FFrameTime& frameTime, const FVector location );
	void AddPlayerRotation( const FFrameTime& frameTime, const FRotator rotation );
	void AddPlayerFOV( const FFrameTime& frameTime, const float FOV );
	void StartSequence( APawn* pawn );
	float TickSequence( float dt );
	bool GetIsPlaying() const { return IsPlaying; }
	void EvaluateFrame( APawn* pawn, const FFrameTime& frameTime, FVector& out_location, FRotator& out_rotation, float& out_FOV  );
	void EvaluateFrameDry( APawn* pawn, const FFrameTime& frameTime, FVector& out_location, FRotator& out_rotation, float& out_FOV  );

	void GetDebugStrings( TArray<FString>& out_debugText );

	UPROPERTY( SaveGame )
	FFrameTime SequenceStart;
	UPROPERTY( SaveGame )
	FFrameTime SequenceEnd;

private:
	UPROPERTY()
	APawn* Pawn;
	UPROPERTY()
	APlayerController* PlayerController;

	bool IsPlaying;

	float SequenceTimer;
	float SequenceEndTime;


};
