#include "SlidingPuzzleObject.h"

void ASlidingPuzzleObject::OpenPuzzleMenu()
{
    if (PuzzleWidgetClass)
    {
        PuzzleWidget = CreateWidget(GetWorld(), PuzzleWidgetClass);
        if (PuzzleWidget)
        {
            PuzzleWidget->AddToViewport();
        }
    }
}
