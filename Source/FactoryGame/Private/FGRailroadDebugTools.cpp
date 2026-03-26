#include "FGRailroadDebugTools.h"

void FGRailroadDebugWindowBase::AddSubsystem(AFGRailroadSubsystem* subsystem){ }
void FGRailroadDebugWindowBase::RemoveSubsystem(AFGRailroadSubsystem* subsystem){ }
void FGRailroadDebugWindowBase::SetSelectedSubsystem(int32 index){ }
AFGRailroadSubsystem* FGRailroadDebugWindowBase::SelectSubsystemUI(){ return nullptr; }
void FGRailroadDebugWindowBase::OnSelectedSubsystemChanged(){ }
void FGRailroadDebugWindowTrainBase::SetSelectedTrain(int32 index){ }
AFGTrain* FGRailroadDebugWindowTrainBase::SelectTrainUI(AFGRailroadSubsystem* subsystem){ return nullptr; }
void FGRailroadDebugWindowTrainBase::DrawWindow(float dt){ }
void FGRailroadDebugWindowTrainBase::DrawContent(float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train){ }
void FGRailroadDebugWindowTrainBase::OnSelectedSubsystemChanged(){ FGRailroadDebugWindowBase::OnSelectedSubsystemChanged(); }
void FGRailroadDebugWindowTrainBase::OnSelectedTrainChanged(){ }
void FGRailroadDebugWindowTrain::DrawContent(float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train){ }
void FGRailroadDebugWindowTrain::OnSelectedTrainChanged(){ FGRailroadDebugWindowTrainBase::OnSelectedTrainChanged(); }
void FGRailroadDebugWindowTrain::UpdateGraphData(AFGTrain* train){ }
void FGRailroadDebugWindowTrain::ClearGraphData(){ }
void FGRailroadDebugWindowTrain::ShowConsist(AFGTrain* train){ }
void FGRailroadDebugWindowTrain::ShowDriving(AFGTrain* train){ }
void FGRailroadDebugWindowTrain::ShowDocking(AFGTrain* train){ }
void FGRailroadDebugWindowTrain::ShowATC(AFGTrain* train){ }
void FGRailroadDebugWindowTrain::ShowSimulation(AFGTrain* train){ }
void FGRailroadDebugWindowTrainPath::DrawContent(float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train){ }
void FGRailroadDebugWindowTrainPath::ShowPathPoints(const FTrainAtcData& atc){ }
void FGRailroadDebugWindowTrainTargetPoints::DrawContent(float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train){ }
void FGRailroadDebugWindowTrainTargetPoints::ShowTargetPoints(const FTrainAtcData& atc){ }
void FGRailroadDebugWindowTrainPhysics::DrawContent(float dt, AFGRailroadSubsystem* subsystem, AFGTrain* train){ }
void FGRailroadDebugWindowSubsystem::DrawWindow(float dt){ }
void FGRailroadDebugWindowSubsystem::DrawContent(float dt, AFGRailroadSubsystem* subsystem){ }
AFGBuildableRailroadSignal* FGRailroadDebugWindowSignal::SelectInteractedSignal(UObject* worldContext){ return nullptr; }
void FGRailroadDebugWindowSignal::DrawWindow(float dt){ }
void FGRailroadDebugWindowSignal::DrawContent(float dt, AFGBuildableRailroadSignal* signal){ }
