// Copyright Coffee Stain Studios. All Rights Reserved.


#include "EditorDebugSubsystem.h"
#include "Editor.h"
#include "FGClearanceInterface.h"
#include "Debug/DebugDrawService.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Modules/ModuleManager.h"

void UEditorDebugSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
	Super::Initialize( Collection );
	FEngineShowFlags::RegisterCustomShowFlag( TEXT("EditorDebugString"), true, SFG_Developer,FText::FromString("Editor Debug String") );
	DrawDebugDelegateHandle = UDebugDrawService::Register( TEXT("EditorDebugString"), FDebugDrawDelegate::CreateUObject(this, &UEditorDebugSubsystem::DebugDrawCanvas) );

	FWorldDelegates::OnWorldPreActorTick.AddStatic( &UEditorDebugSubsystem::OnWorldPreActorTick );
}

void UEditorDebugSubsystem::Deinitialize()
{
	EditorDebugStrings.Empty();
	UDebugDrawService::Unregister( DrawDebugDelegateHandle );
	Super::Deinitialize();
}

void UEditorDebugSubsystem::DebugDrawCanvas( UCanvas* Canvas, APlayerController* )
{
	UWorld* EditorWorld = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	if( !EditorWorld )
	{
		return;
	}
	
	DrawDebugDelta = EditorWorld->TimeSeconds - LastDebugDrawTime;
	if( IsValid( Canvas ) && !EditorDebugStrings.IsEmpty() )
	{
		for( int32 i = EditorDebugStrings.Num() - 1; i >= 0; --i)
		{
			FEditorDebugString& currentDebugString = EditorDebugStrings[i];

			FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::FromString( currentDebugString.Text ), GEngine->GetSmallFont(), currentDebugString.TextColor);
			TextItem.SlateFontInfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), currentDebugString.FontSize);
			currentDebugString.DrawShadow ? TextItem.EnableShadow(FLinearColor::Black) : TextItem.DisableShadow();
			const FVector screenLocation = Canvas->Project(currentDebugString.TextLocation);
			
			Canvas->Canvas->DrawItem(TextItem, FVector2D(FMath::CeilToFloat(screenLocation.X), FMath::CeilToFloat(screenLocation.Y)));
			
			// Count down the non persistent debug strings 
			if( currentDebugString.Duration != -1.f )
			{
				currentDebugString.TimeRemaining -= DrawDebugDelta;
				if( currentDebugString.TimeRemaining < 0 )
				{
					EditorDebugStrings.RemoveAt( i );
				}
			}
		}
	}

	LastDebugDrawTime = EditorWorld->TimeSeconds;
}

void UEditorDebugSubsystem::DrawEditorDebugString( const FVector WorldLocation, const FString& Text, FLinearColor TextColor,
                                                   float Duration, bool DrawShadow, int32 FontSize )
{
	if( UEditorDebugSubsystem* EditorDebugSubsystem = GEditor ? GEditor->GetEditorSubsystem<UEditorDebugSubsystem>() : nullptr )
	{
		EditorDebugSubsystem->EditorDebugStrings.Emplace(
			FEditorDebugString( WorldLocation, Text, TextColor, Duration, DrawShadow, FontSize ) );
	}
}

void UEditorDebugSubsystem::ClearAllEditorDebugStrings()
{
	if( UEditorDebugSubsystem* EditorDebugSubsystem = GEditor ? GEditor->GetEditorSubsystem<UEditorDebugSubsystem>() : nullptr )
	{
		EditorDebugSubsystem->EditorDebugStrings.Empty();
	}
}

void UEditorDebugSubsystem::OnWorldPreActorTick( UWorld* World, ELevelTick TickType, float DeltaSeconds )
{
	if( World->WorldType == EWorldType::EditorPreview )
	{
		for ( FConstLevelIterator LevelIt = World->GetLevelIterator(); LevelIt; ++LevelIt )
		{
			for( const AActor* actor : (*LevelIt)->Actors )
			{
				// Check if the actor implements the clearance interface
				if( actor && actor->Implements< UFGClearanceInterface >() )
					
				{    	
					// Get the clearance data from the actor and visualize it
					TArray< FFGClearanceData > clearanceData;
					IFGClearanceInterface::Execute_GetClearanceData( actor, clearanceData );
        
					for( FFGClearanceData& clearance : clearanceData )
					{
						if( clearance.Visualize )
						{
							// Visualize clearance box
							const FTransform ClearanceTransform = clearance.RelativeTransform * actor->GetActorTransform();
                		
							FVector center, extent;
							clearance.ClearanceBox.GetCenterAndExtents( center, extent );
        
							FColor debugColor;
                				
							switch( clearance.Type )
							{
								case EClearanceType::CT_Soft:
									debugColor = FColor::Yellow;
								break;
                					
								case EClearanceType::CT_BlockEverything:
									debugColor = FColor::Red;
								break;
                					
								default:
									debugColor = FColor::Green;
								break;
							}
                				
							DrawDebugBox( World, ClearanceTransform.TransformPositionNoScale( center ), extent, ClearanceTransform.GetRotation(), debugColor );
							debugColor.A = debugColor.A * 0.01f;
                				
							DrawDebugSolidBox( World, clearance.ClearanceBox, debugColor, ClearanceTransform );
						}
					}
				}
			}
		}
	}
}
