#include "UI/FGFilteredEditableText.h"

UFGFilteredEditableText::UFGFilteredEditableText(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){ }
void UFGFilteredEditableText::InitializeFilteredText(const FText& initialText){ }
void UFGFilteredEditableText::SynchronizeProperties(){ Super::SynchronizeProperties(); }
void UFGFilteredEditableText::HandleTextChanged(const FText& newText){ }
void UFGFilteredEditableText::HandleTextCommitted(const FText& newText, ETextCommit::Type commitMethod){ }
