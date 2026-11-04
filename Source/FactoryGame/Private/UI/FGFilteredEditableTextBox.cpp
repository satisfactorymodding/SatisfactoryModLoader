#include "UI/FGFilteredEditableTextBox.h"

UFGFilteredEditableTextBox::UFGFilteredEditableTextBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){ }
void UFGFilteredEditableTextBox::InitializeFilteredText(const FText& initialText){ }
void UFGFilteredEditableTextBox::SynchronizeProperties(){ Super::SynchronizeProperties(); }
void UFGFilteredEditableTextBox::HandleTextChanged(const FText& newText){ }
void UFGFilteredEditableTextBox::HandleTextCommitted(const FText& newText, ETextCommit::Type commitMethod){ }
