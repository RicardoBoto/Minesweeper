// Fill out your copyright notice in the Description page of Project Settings.


#include "MinesweeperBaseMenu.h"

#include "MinesweeperGameGrid.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UMinesweeperBaseMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success || WidthTextBox == nullptr || HeightTextBox == nullptr || NrBombsTextBox == nullptr || ButtonNewGame == nullptr || MinesweeperGameGrid == nullptr || MessageTextBox == nullptr)
	{
		return false;
	}

	MinesweeperGameGrid->SetParent(this);
	MessageTextBox->SetVisibility(ESlateVisibility::Collapsed);

	WidthTextBox->OnTextChanged.AddDynamic(this, &UMinesweeperBaseMenu::OnWidthTextBoxChange);
	WidthTextBox->OnTextCommitted.AddDynamic(this, &UMinesweeperBaseMenu::OnWidthTextBoxCommit);

	HeightTextBox->OnTextChanged.AddDynamic(this, &UMinesweeperBaseMenu::OnHeightTextBoxChange);
	HeightTextBox->OnTextCommitted.AddDynamic(this, &UMinesweeperBaseMenu::OnHeightTextBoxCommit);

	NrBombsTextBox->OnTextChanged.AddDynamic(this, &UMinesweeperBaseMenu::OnNrBombsTextBoxChange);
	NrBombsTextBox->OnTextCommitted.AddDynamic(this, &UMinesweeperBaseMenu::OnNrBombsTextBoxCommit);

	ButtonNewGame->OnClicked.AddDynamic(this, &UMinesweeperBaseMenu::NewGame);

	return Success;
}

void UMinesweeperBaseMenu::NewGame()
{
	MessageTextBox->SetVisibility(ESlateVisibility::Collapsed);

	if (MinesweeperGameGrid != nullptr)
	{
		int32 Width = 0;
		int32 Height = 0;
		int32 NrBombs = 0;

		GetValues(Width, Height, NrBombs);
		MinesweeperGameGrid->GenerateBoard(Width, Height, NrBombs);
	}

}

void UMinesweeperBaseMenu::OnWidthTextBoxChange(const FText& Text)
{
	NumericSanitizer(WidthTextBox, Text);
}

void UMinesweeperBaseMenu::OnWidthTextBoxCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnCleared)
	{
		return;
	}

	NumericSanitizer(WidthTextBox, Text, true);
	DimensionVerification(WidthTextBox, Text);
}

void UMinesweeperBaseMenu::OnHeightTextBoxChange(const FText& Text)
{
	NumericSanitizer(HeightTextBox, Text);
}

void UMinesweeperBaseMenu::OnHeightTextBoxCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnCleared)
	{
		return;
	}

	NumericSanitizer(HeightTextBox, Text, true);
	DimensionVerification(HeightTextBox, Text);
}

void UMinesweeperBaseMenu::OnNrBombsTextBoxChange(const FText& Text)
{
	NumericSanitizer(NrBombsTextBox, Text);
}

void UMinesweeperBaseMenu::OnNrBombsTextBoxCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnCleared)
	{
		return;
	}

	NumericSanitizer(NrBombsTextBox, Text, true);
	BombVerification();
}

void UMinesweeperBaseMenu::FinalizeGame(const bool InIsVictory)
{
	MessageTextBox->SetVisibility(ESlateVisibility::Visible);

	if (InIsVictory)
	{
		MessageTextBox->SetText(WinText);
		MessageTextBox->SetColorAndOpacity(WinColor);
	}
	else
	{
		MessageTextBox->SetText(LoseText);
		MessageTextBox->SetColorAndOpacity(LoseColor);
	}
}

void UMinesweeperBaseMenu::NumericSanitizer(UEditableTextBox* const InEditableTextBox, const FText& InText, const bool InClearText /*= false*/)
{
	if (!InText.IsNumeric() && InEditableTextBox != nullptr)
	{
		InEditableTextBox->SetError(FText::FromString(TEXT("Must be numeric")));

		if (InClearText)
		{
			InEditableTextBox->SetText(FText());
		}
	}
	else
	{
		InEditableTextBox->ClearError();
	}
}

void UMinesweeperBaseMenu::DimensionVerification(class UEditableTextBox* const InEditableTextBox, const FText& InText)
{
	if (InEditableTextBox == nullptr)
	{
		return;
	}

	int32 Val = FCString::Atoi(*InText.ToString());

	if (Val < MinDim)
	{
		InEditableTextBox->SetText(FText::FromString(FString::FromInt(MinDim)));
	}
	else if (Val > MaxDim)
	{
		InEditableTextBox->SetText(FText::FromString(FString::FromInt(MaxDim)));
	}
}

void UMinesweeperBaseMenu::BombVerification()
{
	int32 Width = 0;
	int32 Height = 0;
	int32 NrBombs = 0;

	GetValues(Width, Height, NrBombs);

	int32 MaxBombs = Width * Height * 0.4;

	if (NrBombs > MaxBombs)
	{
		NrBombsTextBox->SetError(FText::FromString(FString::Printf(TEXT("Must be smaller then 40% of the tiles. CurrValue: %d"), MaxBombs)));
		NrBombsTextBox->SetText(FText::FromString(FString::FromInt(MaxBombs)));
		return;
	}
	else if(NrBombs < 1)
	{
		NrBombsTextBox->SetError(FText::FromString(TEXT("Must be greater then 1")));
		NrBombsTextBox->SetText(FText::FromString(FString::FromInt(1)));
		return;
	}

	NrBombsTextBox->ClearError();
}

void UMinesweeperBaseMenu::GetValues(int32& OutWidth, int32& OutHeight, int32& OutNrBombs)
{
	if (WidthTextBox != nullptr && HeightTextBox != nullptr && NrBombsTextBox != nullptr)
	{
		OutWidth = FCString::Atoi(*WidthTextBox->GetText().ToString());
		OutHeight = FCString::Atoi(*HeightTextBox->GetText().ToString());
		OutNrBombs = FCString::Atoi(*NrBombsTextBox->GetText().ToString());
	}
}
