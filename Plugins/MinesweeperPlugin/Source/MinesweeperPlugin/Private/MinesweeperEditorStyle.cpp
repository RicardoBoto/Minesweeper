
#include "MinesweeperEditorStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"


TUniquePtr<FSlateStyleSet> FMinesweeperEditorStyle::StyleSet;

void FMinesweeperEditorStyle::Initialize()
{
    if (StyleSet.IsValid())
    {
        return;
    }

    // Create the style sheet
    StyleSet = MakeUnique<FSlateStyleSet>(GetStyleSetName());

    StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
    StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

    const FVector2D Icon20x20(20.0f, 20.0f);
    const FVector2D Icon16x16(16.0f, 16.0f);

    StyleSet->Set("MineSweeperLogoIcon", new FSlateImageBrush(RootToPluginContentDir("Slate/MineSweeperLogo.png"), Icon20x20));
    StyleSet->Set("MineSweeperLogoIcon.Small", new FSlateImageBrush(RootToPluginContentDir("Slate/MineSweeperLogo.png"), Icon16x16));

	StyleSet->Set("MineIcon", new FSlateImageBrush(RootToPluginContentDir("Slate/MineIcon.png"), Icon20x20));
	StyleSet->Set("MineIcon.Small", new FSlateImageBrush(RootToPluginContentDir("Slate/MineIcon.png"), Icon16x16));



	// StyleSet->Set("ContentBrowserIcon", new FSlateVectorImageBrush(RootToContentDir("Starship/Common/ContentBrowser.svg"), Icon20x20));
	// StyleSet->Set("ContentBrowserIcon.Small", new FSlateVectorImageBrush(RootToContentDir("Starship/Common/ContentBrowser.svg"), Icon16x16));



    // Register the style set
    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FMinesweeperEditorStyle::Shutdown()
{
    // Unregister the style set
    if (StyleSet.IsValid())
    {
        FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
        StyleSet.Reset();
    }
}

FName FMinesweeperEditorStyle::GetStyleSetName()
{
    static const FName StyleSetName(TEXT("MinesweeperEditorStyle"));
    return StyleSetName;
}

FString FMinesweeperEditorStyle::RootToPluginContentDir(const FString& RelativePath)
{
    TSharedPtr<IPlugin> MinePlugin = IPluginManager::Get().FindPlugin(TEXT("MinesweeperPlugin"));

	if (!MinePlugin.IsValid())
	{
        return FString();
    }

    static const FString ContentDir = MinePlugin->GetContentDir();
    return ContentDir / RelativePath;
}
