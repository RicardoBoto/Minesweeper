// Fill out your copyright notice in the Description page of Project Settings.


#include "MinesweeperGameCell.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "MinesweeperGameGrid.h"
#include "UObject/ConstructorHelpers.h"

UMinesweeperGameCell::UMinesweeperGameCell(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> BombIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/bomb.bomb'"));
	if (BombIconClass.Succeeded())
	{
		BombIcon = BombIconClass.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> ExplosionIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/blast.blast'"));
	if (ExplosionIconClass.Succeeded())
	{
		ExplosionIcon = ExplosionIconClass.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> OneIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_one_bold_icon.number_one_bold_icon'"));
	if (OneIconClass.Succeeded())
	{
		OneIcon = OneIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> TwoIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_two_bold_icon.number_two_bold_icon'"));
	if (TwoIconClass.Succeeded())
	{
		TwoIcon = TwoIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> ThreeIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_three_bold_icon.number_three_bold_icon'"));
	if (ThreeIconClass.Succeeded())
	{
		ThreeIcon = ThreeIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> FourIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_four_bold_icon.number_four_bold_icon'"));
	if (FourIconClass.Succeeded())
	{
		FourIcon = FourIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> FiveIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_five_bold_icon.number_five_bold_icon'"));
	if (FiveIconClass.Succeeded())
	{
		FiveIcon = FiveIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> SixIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_six_bold_icon.number_six_bold_icon'"));
	if (SixIconClass.Succeeded())
	{
		SixIcon = SixIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> SevenIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_seven_bold_icon.number_seven_bold_icon'"));
	if (SevenIconClass.Succeeded())
	{
		SevenIcon = SevenIconClass.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> EightIconClass(TEXT("/Script/Engine.Texture2D'/MinesweeperPlugin/Textures/number_eight_bold_icon.number_eight_bold_icon'"));
	if (EightIconClass.Succeeded())
	{
		EightIcon = EightIconClass.Object;
	}
}


void UMinesweeperGameCell::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// CachedIndex = INDEX_NONE;

	// SetUISelection(false);
}

void UMinesweeperGameCell::NativeConstruct()
{
	Super::NativeConstruct();

	//CachedIndex = INDEX_NONE;
	//
	//SetUISelection(false);
}

bool UMinesweeperGameCell::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success || CellButton == nullptr || CellImg == nullptr)
	{
		return false;
	}

	CellImg->SetVisibility(ESlateVisibility::Collapsed);
	CellButton->OnClicked.AddDynamic(this, &UMinesweeperGameCell::CellClick);

	return true;
}

void UMinesweeperGameCell::CellClick()
{
	if (UMinesweeperGameGrid* GG = Cast<UMinesweeperGameGrid>(Parent))
	{
		GG->ClickPos(Col, Row);
	}
}

void UMinesweeperGameCell::SetCellVisible()
{
	if (CellImg == nullptr)
	{
		return;
	}

	if (CellImg->GetBrush().GetResourceObject() != nullptr)
	{
		CellImg->SetVisibility(ESlateVisibility::Visible);
	}

	CellButton->SetIsEnabled(false);
}

void UMinesweeperGameCell::SetCellExplosionVisible()
{
	if (CellImg == nullptr)
	{
		return;
	}

	CellImg->SetVisibility(ESlateVisibility::Visible);
	CellImg->SetBrushFromTexture(ExplosionIcon);
	CellButton->SetIsEnabled(false);
}

void UMinesweeperGameCell::SetCellNr(const int32 InNr)
{
	if (CellImg == nullptr)
	{
		return;
	}

	switch(InNr)
	{
		case 0:
			CellImg->SetBrushFromTexture(nullptr);
			CellImg->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case 1:
			CellImg->SetBrushFromTexture(OneIcon);
			break;
		case 2:
			CellImg->SetBrushFromTexture(TwoIcon);
			break;
		case 3:
			CellImg->SetBrushFromTexture(ThreeIcon);
			break;
		case 4:
			CellImg->SetBrushFromTexture(FourIcon);
			break;
		case 5:
			CellImg->SetBrushFromTexture(FiveIcon);
			break;
		case 6:
			CellImg->SetBrushFromTexture(SixIcon);
			break;
		case 7:
			CellImg->SetBrushFromTexture(SevenIcon);
			break;
		case 8:
			CellImg->SetBrushFromTexture(EightIcon);
			break;

		default:
			check(false);
	}
}

void UMinesweeperGameCell::SetCellBomb()
{
	if (CellImg == nullptr)
	{
		return;
	}

	CellImg->SetBrushFromTexture(BombIcon);
}



