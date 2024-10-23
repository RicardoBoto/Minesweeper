// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinesweeperBaseMenu.generated.h"

/**
 * 
 */
UCLASS()
class UMinesweeperBaseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;

public:

	UFUNCTION()
	void NewGame();

	UFUNCTION()
	void OnWidthTextBoxChange(const FText& Text);
	UFUNCTION()
	void OnWidthTextBoxCommit(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnHeightTextBoxChange(const FText& Text);
	UFUNCTION()
	void OnHeightTextBoxCommit(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnNrBombsTextBoxChange(const FText& Text);
	UFUNCTION()
	void OnNrBombsTextBoxCommit(const FText& Text, ETextCommit::Type CommitMethod);

	void FinalizeGame(const bool InIsVictory);

private:

	void NumericSanitizer(class UEditableTextBox* const InEditableTextBox, const FText& InText, const bool InClearText = false);

	void DimensionVerification(class UEditableTextBox* const InEditableTextBox, const FText& InText);

	void BombVerification();

	void GetValues(int32& OutWidth, int32& OutHeight, int32& OutNrBombs);


public:

	UPROPERTY(EditDefaultsOnly, category = "Game Settings", meta = (BindWidget))
	int32 MinDim = 2;
	UPROPERTY(EditDefaultsOnly, category = "Game Settings", meta = (BindWidget))
	int32 MaxDim = 40;

	UPROPERTY(EditDefaultsOnly, category = "Game Settings")
	FLinearColor WinColor;
	UPROPERTY(EditDefaultsOnly, category = "Game Settings")
	FLinearColor LoseColor;

	UPROPERTY(EditDefaultsOnly, category = "Game Settings")
	FText WinText;
	UPROPERTY(EditDefaultsOnly, category = "Game Settings")
	FText LoseText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* WidthTextBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* HeightTextBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* NrBombsTextBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UMinesweeperGameGrid* MinesweeperGameGrid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ButtonNewGame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* MessageTextBox;

};
