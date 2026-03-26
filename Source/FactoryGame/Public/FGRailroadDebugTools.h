// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGRailroadSubsystem.h"
#include "FGTrain.h"
#include "SlateIMWidgetBase.h"
#include "Containers/RingBuffer.h"

class AFGRailroadSubsystem;
class AFGTrain;
class FGRailroadDebugWindowTrain;
class FGRailroadDebugWindowTrainPath;
class FGRailroadDebugWindowTrainTargetPoints;
class FGRailroadDebugWindowTrainPhysics;


/** Base for all train debug windows */
class FACTORYGAME_API FGRailroadDebugWindowBase : public FSlateIMWindowBase
{
public:
	FGRailroadDebugWindowBase( FStringView windowTitle, FVector2f windowSize, const TCHAR* command, const TCHAR* commandHelp ) :
		FSlateIMWindowBase( windowTitle, windowSize, command, commandHelp )
	{}

	void AddSubsystem( AFGRailroadSubsystem* subsystem );
	void RemoveSubsystem( AFGRailroadSubsystem* subsystem );

	void SetSelectedSubsystem( int32 index );
	int32 GetSelectedSubsystem() const { return mSelectedSubsystemIndex; }
	
protected:
	AFGRailroadSubsystem* SelectSubsystemUI();

	virtual void OnSelectedSubsystemChanged();
	
private:
	TArray< TWeakObjectPtr< AFGRailroadSubsystem > > mSubsystems;
	int32 mSelectedSubsystemIndex = INDEX_NONE;
	bool mHasSelectedSubsystemChanged = false;
};

/** Base window for showing information about individual trains. */
class FACTORYGAME_API FGRailroadDebugWindowTrainBase : public FGRailroadDebugWindowBase
{
public:
	FGRailroadDebugWindowTrainBase( FStringView windowTitle, FVector2f windowSize, const TCHAR* command, const TCHAR* commandHelp ) :
		FGRailroadDebugWindowBase( windowTitle, windowSize, command, commandHelp )
	{}

	void SetSelectedTrain( int32 index );
	int32 GetSelectedTrain() const { return mSelectedTrainIndex; }

protected:
	AFGTrain* SelectTrainUI( AFGRailroadSubsystem* subsystem );

	virtual void DrawWindow( float dt ) override final;
	virtual void DrawContent( float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train );

	virtual void OnSelectedSubsystemChanged() override;
	virtual void OnSelectedTrainChanged();
	
private:
	int32 mSelectedTrainIndex = INDEX_NONE;
	bool mHasSelectedTrainChanged = false;
};

/**
 * Debug window for showing information about individual trains.
 */
class FACTORYGAME_API FGRailroadDebugWindowTrain : public FGRailroadDebugWindowTrainBase
{
public:
	FGRailroadDebugWindowTrain() :
		FGRailroadDebugWindowTrainBase(
			TEXT( "Train Inspector" ),
			FVector2f( 1000, 500 ),
			TEXT( "Railroad.ToggleTrainInspector" ),
			TEXT( "Opens a window that can show in-depth information about the trains in the game." ) )
	{}

protected:
	virtual void DrawContent( float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train ) override;

	virtual void OnSelectedTrainChanged() override;

private:
	void UpdateGraphData( AFGTrain* train );
	void ClearGraphData();
	
	void ShowConsist( AFGTrain* train );
	void ShowDriving( AFGTrain* train );
	void ShowDocking( AFGTrain* train );
	void ShowATC( AFGTrain* train );
	void ShowSimulation( AFGTrain* train );

public:
	FGRailroadDebugWindowTrainPath* mPathInspectorWindow;
	FGRailroadDebugWindowTrainTargetPoints* mTargetPointInspectorWindow;
	FGRailroadDebugWindowTrainPhysics* mPhysicsInspectorWindow;
	
private:
	bool mShowAtcData = false;
	bool mShowRelevantAtcPointsOnly = true;
	bool mShowSimulationData = false;

	int32 mMaxSpeedGraphPoints = 300;
	TRingBuffer< double > mCurrentSpeedGraph;
	TRingBuffer< double > mTargetSpeedGraph;

	int32 mMaxBrakeDistanceGraphPoints = 300;
	TRingBuffer< double > mBrakeDistanceGraph;
	TRingBuffer< double > mRestrictiveSignalDistanceGraph;
};

/**
 * Debug window for showing information about the path for a train.
 */
class FACTORYGAME_API FGRailroadDebugWindowTrainPath : public FGRailroadDebugWindowTrainBase
{
public:
	FGRailroadDebugWindowTrainPath() :
		FGRailroadDebugWindowTrainBase(
			TEXT( "Train Path Inspector" ),
			FVector2f( 1000, 500 ),
			TEXT( "Railroad.ToggleTrainPathInspector" ),
			TEXT( "Opens a window that can show in-depth information about the trains' paths." ) )
	{}

protected:
	virtual void DrawContent( float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train ) override;

private:
	void ShowPathPoints( const FTrainAtcData& atc );
private:
	bool mShowRelevantAtcPointsOnly = false;
};

/**
 * Debug window for showing information about the atc points for a train.
 */
class FACTORYGAME_API FGRailroadDebugWindowTrainTargetPoints : public FGRailroadDebugWindowTrainBase
{
public:
	FGRailroadDebugWindowTrainTargetPoints() :
		FGRailroadDebugWindowTrainBase(
			TEXT( "Train Atc Target Points Inspector" ),
			FVector2f( 1000, 500 ),
			TEXT( "Railroad.ToggleTrainAtcTargetPointsInspector" ),
			TEXT( "Opens a window that can show in-depth information about the trains' atc target points." ) )
	{}

protected:
	virtual void DrawContent( float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train ) override;

private:
	void ShowTargetPoints( const FTrainAtcData& atc );
};

/**
 * Debug window for showing information about the physics simulation for a train.
 */
class FACTORYGAME_API FGRailroadDebugWindowTrainPhysics : public FGRailroadDebugWindowTrainBase
{
public:
	FGRailroadDebugWindowTrainPhysics() :
		FGRailroadDebugWindowTrainBase(
			TEXT( "Train Physics" ),
			FVector2f( 1000, 500 ),
			TEXT( "Railroad.ToggleTrainPhysicsInspector" ),
			TEXT( "Opens a window that can show in-depth information about the trains' physics data." ) )
	{}

protected:
	virtual void DrawContent( float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train ) override;
};

class FACTORYGAME_API FGRailroadDebugWindowSubsystem : public FGRailroadDebugWindowBase
{
public:
	FGRailroadDebugWindowSubsystem() :
		FGRailroadDebugWindowBase(
			TEXT( "Railroad Subsystem Inspector" ),
			FVector2f( 1000, 500 ),
			TEXT( "Railroad.ToggleSubsystemInspector" ),
			TEXT( "Opens a window that can show in-depth information about the railroad subsystem, such as trains, blocks, reservations, and scheduling." ) )
	{}

protected:
	virtual void DrawWindow( float dt ) override final;
	void DrawContent( float dt, AFGRailroadSubsystem* subsystem );

public:
	FGRailroadDebugWindowTrain* mTrainInspectorWindow;
	
private:
	bool mVisualizeTrackConnections = false;
	bool mVisualizeSignalBlocksUsingGameFeature = false;
	bool mVisualizeSignalBlocksUsingDebug = false;
	bool mVisualizeSignalReservations = false;
};

class FACTORYGAME_API FGRailroadDebugWindowSignal : public FGRailroadDebugWindowBase
{
public:
	FGRailroadDebugWindowSignal() :
		FGRailroadDebugWindowBase(
			TEXT( "Railroad Signal Inspector" ),
			FVector2f( 1000, 500 ),
			TEXT( "Railroad.ToggleSignalInspector" ),
			TEXT( "Opens a window that can show in-depth information about the railroad signal last interacted with." ) )
	{}

protected:
	AFGBuildableRailroadSignal* SelectInteractedSignal( UObject* worldContext );
	
	virtual void DrawWindow( float dt ) override final;
	void DrawContent( float dt, AFGBuildableRailroadSignal* signal );
	
private:
	TArray< AFGBuildableRailroadSignal* > mPinnedSignals;
	TArray< AFGBuildableRailroadSignal* > mPendingUnpins;
};
