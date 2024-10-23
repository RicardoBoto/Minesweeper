// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinesweeperGameGrid.generated.h"

USTRUCT(BlueprintType)
struct FCellInfo
{
    GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsVisible;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsBomb;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NrNeighborBombs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUniformGridSlot* CellUISlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMinesweeperGameCell* CellUI;

public:

    /** Constructor default */
	FCellInfo();

};

/**
 * 
 */
UCLASS()
class UMinesweeperGameGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetParent(UUserWidget* InParent);

	void GenerateBoard(const int32 InWidth, const int32 InHeight, const int32 NrBombs);

	void ClickPos(const int32 InCol, const int32 InRow);
	
private:

	int32 GetAdjacentBombs(const int32 InCol, const int32 InRow);

	void OpenPos(const int32 InCol, const int32 InRow);

	void SetCellVisible(FCellInfo& CellInf);


	void CheckWin();

	void LoseGame();

	void ShowAll();

public:

	TArray<TArray<FCellInfo>> GameGrid;

	UPROPERTY()
	UUserWidget* Parent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUniformGridPanel* UIGrid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMinesweeperGameCell> CellWidgetClass;

	int32 CurrentVisibleCells;

	int32 TargetCells;
};
