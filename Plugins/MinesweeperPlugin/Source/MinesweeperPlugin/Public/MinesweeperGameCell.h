// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinesweeperGameCell.generated.h"

/**
 * 
 */
UCLASS()
class UMinesweeperGameCell : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UMinesweeperGameCell(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

protected:

	virtual bool Initialize() override;

public:

	UFUNCTION()
	void CellClick();

	void SetCellVisible();

	void SetCellExplosionVisible();

	void SetCellNr(const int32 InNr);

	void SetCellBomb();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* CellButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* CellImg;

	UPROPERTY(BlueprintReadOnly)
	int32 Col;

	UPROPERTY(BlueprintReadOnly)
	int32 Row;

	UPROPERTY(BlueprintReadOnly)
	class UWidget* Parent;

	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* BombIcon;

	UPROPERTY(BlueprintReadOnly)
	class UTexture2D* ExplosionIcon;

	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* OneIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* TwoIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* ThreeIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* FourIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* FiveIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* SixIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* SevenIcon;
	UPROPERTY(BlueprintReadOnly)
    class UTexture2D* EightIcon;
};
