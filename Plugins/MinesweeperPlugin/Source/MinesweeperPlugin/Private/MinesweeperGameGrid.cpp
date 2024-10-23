// Fill out your copyright notice in the Description page of Project Settings.


#include "MinesweeperGameGrid.h"

#include "MinesweeperBaseMenu.h"
#include "MinesweeperGameCell.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

FCellInfo::FCellInfo()
	: IsVisible(false)
	, IsBomb(false)
	, NrNeighborBombs(0)
	, CellUISlot(nullptr)
{
}

void UMinesweeperGameGrid::SetParent(UUserWidget* InParent)
{
	Parent = InParent;
}

void UMinesweeperGameGrid::GenerateBoard(const int32 InWidth, const int32 InHeight, const int32 NrBombs)
{
	if (UIGrid == nullptr)
	{
		return;
	}

	CurrentVisibleCells = 0;
	TargetCells = (InWidth * InHeight) - NrBombs;

	// === Build board in memory and its UI cells ===
	UIGrid->ClearChildren();
	GameGrid.Empty();

	GameGrid.Init(TArray<FCellInfo>(), InWidth);

	for (int32 i = 0; i < InWidth; ++i)
	{
		GameGrid[i].Init(FCellInfo(), InHeight);

		for (int32 j = 0; j < InHeight; ++j)
		{
			FCellInfo& NewCell = GameGrid[i][j];

			NewCell.CellUI = Cast<UMinesweeperGameCell>(CreateWidget(this, CellWidgetClass));

			if (NewCell.CellUI != nullptr)
			{
				NewCell.CellUISlot = UIGrid->AddChildToUniformGrid(NewCell.CellUI, j, i);
				NewCell.CellUI->SetPadding(FMargin(0.0f));
				NewCell.CellUI->Col = i;
				NewCell.CellUI->Row = j;
				NewCell.CellUI->Parent = this;
			}
		}
	}

	// === Place Bombs ===
	int32 PlacedBombs = 0;
	int32 TmpCol = INDEX_NONE;
	int32 TmpRow = INDEX_NONE;

	while (PlacedBombs != NrBombs)
	{
		TmpCol = FMath::RandRange(0, InWidth - 1);
		TmpRow = FMath::RandRange(0, InHeight - 1);
		FCellInfo& CurrCell = GameGrid[TmpCol][TmpRow];

		if (!CurrCell.IsBomb)
		{
			CurrCell.IsBomb = true;
			++PlacedBombs;
		}
	}

	// === Calculate adjacent nr bombs ===
	for (int32 i = 0; i < InWidth; ++i)
	{
		for (int32 j = 0; j < InHeight; ++j)
		{
			if (GameGrid[i][j].IsBomb)
			{
				GameGrid[i][j].CellUI->SetCellBomb();
			}
			else
			{
				GameGrid[i][j].NrNeighborBombs = GetAdjacentBombs(i, j);
				GameGrid[i][j].CellUI->SetCellNr(GameGrid[i][j].NrNeighborBombs);
			}
		}
	}
}

void UMinesweeperGameGrid::ClickPos(const int32 InCol, const int32 InRow)
{
	FCellInfo& CellInf = GameGrid[InCol][InRow];

	if (CellInf.CellUI == nullptr)
	{
		return;
	}

	if (CellInf.IsBomb)
	{
		CellInf.CellUI->SetCellExplosionVisible();
		LoseGame();
	}
	else if (CellInf.NrNeighborBombs != 0)
	{
		SetCellVisible(CellInf);
	}
	else
	{
		OpenPos(InCol, InRow);
	}

	CheckWin();
}

int32 UMinesweeperGameGrid::GetAdjacentBombs(const int32 InCol, const int32 InRow)
{
	int32 AdjacentBombs = 0;

	for (int32 x = -1; x <= 1; ++x)
	{
		int32 AdjCol = InCol + x;

		if (!GameGrid.IsValidIndex(AdjCol))
		{
			continue;
		}

		for (int32 y = -1; y <= 1; ++y)
		{
			int32 AdjRow = InRow + y;
			if (!GameGrid[AdjCol].IsValidIndex(AdjRow))
			{
				continue;
			}

			if (GameGrid[AdjCol][AdjRow].IsBomb)
			{
				++AdjacentBombs;
			}
		}
	}

	return AdjacentBombs;
}

void UMinesweeperGameGrid::OpenPos(const int32 InCol, const int32 InRow)
{
	FCellInfo& CellInf = GameGrid[InCol][InRow];

	if (!CellInf.IsVisible)
	{
		SetCellVisible(CellInf);
	}

	for (int32 x = -1; x <= 1; ++x)
	{
		int32 AdjCol = InCol + x;

		if (!GameGrid.IsValidIndex(AdjCol))
		{
			continue;
		}

		for (int32 y = -1; y <= 1; ++y)
		{
			int32 AdjRow = InRow + y;
			if (!GameGrid[AdjCol].IsValidIndex(AdjRow))
			{
				continue;
			}

			FCellInfo& AdjCellInf = GameGrid[AdjCol][AdjRow];

			if (AdjCellInf.IsVisible)
			{
				continue;
			}
			else if (AdjCellInf.NrNeighborBombs > 0)
			{
				SetCellVisible(AdjCellInf);
			}
			else
			{
				OpenPos(AdjCol, AdjRow);
			}
		}
	}
}

void UMinesweeperGameGrid::SetCellVisible(FCellInfo& CellInf)
{
	if (CellInf.CellUI != nullptr)
	{
		++CurrentVisibleCells;
		CellInf.IsVisible = true;
		CellInf.CellUI->SetCellVisible();
	}
}

void UMinesweeperGameGrid::CheckWin()
{
	if (TargetCells == CurrentVisibleCells)
	{
		UMinesweeperBaseMenu* ParentMenu = Cast<UMinesweeperBaseMenu>(Parent);
		ParentMenu->FinalizeGame(true);
		ShowAll();
	}
}

void UMinesweeperGameGrid::LoseGame()
{
	UMinesweeperBaseMenu* ParentMenu = Cast<UMinesweeperBaseMenu>(Parent);
	ParentMenu->FinalizeGame(false);
	ShowAll();
}

void UMinesweeperGameGrid::ShowAll()
{
	for (TArray<FCellInfo>& Colum : GameGrid)
	{
		for (FCellInfo& Cell : Colum)
		{
			if (!Cell.IsVisible && Cell.CellUI != nullptr)
			{
				Cell.CellUI->SetCellVisible();
			}
		}
	}
}

