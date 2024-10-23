#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FMinesweeperEditorStyle final
{
public:

    static void Initialize();
    static void Shutdown();

    static ISlateStyle& Get()
    {
        return *StyleSet.Get();
    }

    static FName GetStyleSetName();

private:

    static FString RootToPluginContentDir(const FString& RelativePath);

    static TUniquePtr<FSlateStyleSet> StyleSet;


};