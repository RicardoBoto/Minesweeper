// Copyright Epic Games, Inc. All Rights Reserved.

#include "IMinesweeperPlugin.h"

#include "MinesweeperEditorStyle.h"
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"
#include "UObject/ConstructorHelpers.h"

#include "EditorUtilityWidget.h"
// #include "WidgetBlueprint.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "EditorUtilitySubsystem.h"
#include "Editor.h"


class FMinesweeperPlugin : public IMinesweeperPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FMinesweeperPlugin, MinesweeperPlugin)


void FMinesweeperPlugin::StartupModule()
{
    FMinesweeperEditorStyle::Initialize();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &IMinesweeperPlugin::RegisterMenuExtensions));
}

void FMinesweeperPlugin::ShutdownModule()
{
    FMinesweeperEditorStyle::Shutdown();

    // Unregister the startup function
    UToolMenus::UnRegisterStartupCallback(this);

    // Unregister all our menu extensions
    UToolMenus::UnregisterOwner(this);
}


void IMinesweeperPlugin::RegisterMenuExtensions()
{
    FToolMenuOwnerScoped OwnerScoped(this);

    UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");
    FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("File");

    ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
        TEXT("MineSweeperToolbarButton"),
        FExecuteAction::CreateLambda([&]()
        {
            // Simply log for this example
            UE_LOG(LogTemp, Log, TEXT("MyCustomButton triggered!!"));

            UEditorUtilityWidgetBlueprint* MinesweeperWidget = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, TEXT("/Script/Blutility.EditorUtilityWidgetBlueprint'/MinesweeperPlugin/EWBP_MinesweeperRoot.EWBP_MinesweeperRoot'"));
            if (MinesweeperWidget != nullptr)
            {
                UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
                EditorUtilitySubsystem->SpawnAndRegisterTab(MinesweeperWidget);
            }
        }),
        INVTEXT("Mine sweeper menu button"),
        INVTEXT("Open the mine sweeper game"),
        FSlateIcon(FMinesweeperEditorStyle::GetStyleSetName(), "MineSweeperLogoIcon", "MineSweeperLogoIcon.Small")
    ));
}


