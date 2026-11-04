#include "UI/FGFilteredMultiLineEditableText.h"

UFGFilteredMultiLineEditableText::UFGFilteredMultiLineEditableText(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){ }
void UFGFilteredMultiLineEditableText::InitializeFilteredText(const FText& initialText){ }
void UFGFilteredMultiLineEditableText::SynchronizeProperties(){ Super::SynchronizeProperties(); }
void UFGFilteredMultiLineEditableText::HandleTextChanged(const FText& newText){ }
void UFGFilteredMultiLineEditableText::HandleTextCommitted(const FText& newText, ETextCommit::Type commitMethod){ }
