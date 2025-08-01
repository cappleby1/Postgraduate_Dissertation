#include "SlidingPuzzleLogic.h"

void USlidingPuzzleLogic::NativeConstruct()
{
    Super::NativeConstruct();

    MenuTiles.SetNum(16);

    MenuTiles[0] = Tile_0;
    MenuTiles[1] = Tile_1;
    MenuTiles[2] = Tile_2;
    MenuTiles[3] = Tile_3;
    MenuTiles[4] = Tile_4;
    MenuTiles[5] = Tile_5;
    MenuTiles[6] = Tile_6;
    MenuTiles[7] = Tile_7;
    MenuTiles[8] = Tile_8;
    MenuTiles[9] = Tile_9;
    MenuTiles[10] = Tile_10;
    MenuTiles[11] = Tile_11;
    MenuTiles[12] = Tile_12;
    MenuTiles[13] = Tile_13;
    MenuTiles[14] = Tile_14;
    MenuTiles[15] = Tile_15;

    SetupBoard();

    UE_LOG(LogTemp, Warning, TEXT("Board Set Up"));

    // Bind OnTileClicked to each tile's click event
    for (int i = 0; i < MenuTiles.Num(); ++i)
    {
        if (MenuTiles[i])
        {
            // Bind all the tiles' OnClicked events to the same handler
            MenuTiles[i]->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
            // Keep track of which button is being clicked
            ButtonToGridMap.Add(MenuTiles[i], FIntPoint(i / 4, i % 4));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Tile %d is null!"), i);
        }
    }
}



void USlidingPuzzleLogic::SetCurrentButton(UButton* Button)
{
    if (Button)
    {
        CurrentButton = Button;
        UE_LOG(LogTemp, Warning, TEXT("CurrentButton set to: %s"), *Button->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempted to set CurrentButton to nullptr"));
    }
}

bool USlidingPuzzleLogic::IsAdjacent(int r, int c)
{
    int EmptyRow = EmptyPos.X;
    int EmptyCol = EmptyPos.Y;

    return (
        (r == EmptyRow && FMath::Abs(c - EmptyCol) == 1) ||
        (c == EmptyCol && FMath::Abs(r - EmptyRow) == 1)
        );
}

void USlidingPuzzleLogic::UpdateMenuTileVisibility()
{
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            int TileIndex = Board[r][c];
            if (TileIndex < 0 || TileIndex >= MenuTiles.Num())
            {
                UE_LOG(LogTemp, Error, TEXT("TileIndex %d is out of bounds!"), TileIndex);
                continue;
            }

            UButton* TileButton = MenuTiles[TileIndex];
            if (!TileButton)
            {
                UE_LOG(LogTemp, Error, TEXT("TileButton at index %d is null!"), TileIndex);
                continue;
            }

            TileGrid->AddChildToUniformGrid(TileButton, r, c);
            ButtonToGridMap.Add(TileButton, FIntPoint(r, c));

            // Debugging the ButtonToGridMap setup
            UE_LOG(LogTemp, Warning, TEXT("Added Tile %d at Grid Position [%d, %d]"), TileIndex, r, c);
        }
    }

}

void USlidingPuzzleLogic::OnTileClicked()
{
    // Get the button that was clicked
    UButton* ClickedButton = Cast<UButton>(GetWidgetFromName("Tile_0"));
    if (!ClickedButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("CurrentButton is not set properly."));
        return;
    }

    // Log the button click for debugging
    UE_LOG(LogTemp, Warning, TEXT("Tile clicked: %s"), *ClickedButton->GetName());

    // Retrieve the grid position of the clicked button
    FIntPoint ClickedPos = ButtonToGridMap[ClickedButton];
    UE_LOG(LogTemp, Warning, TEXT("Tile clicked at position: [%d, %d]"), ClickedPos.X, ClickedPos.Y);

    // Check if the clicked tile is adjacent to the empty tile
    if (IsAdjacent(ClickedPos.X, ClickedPos.Y))
    {
        // Perform the move logic
        Board[EmptyPos.X][EmptyPos.Y] = Board[ClickedPos.X][ClickedPos.Y];
        Board[ClickedPos.X][ClickedPos.Y] = 0;

        // Update the UI, grid position, and visibility of the tiles
        TileGrid->AddChildToUniformGrid(ClickedButton, EmptyPos.X, EmptyPos.Y);
        ClickedButton->SetVisibility(ESlateVisibility::Hidden);  // Hide the clicked tile

        // Update visibility of the empty tile
        UButton* EmptyTile = MenuTiles[0];  // assuming 0 represents the empty tile
        EmptyTile->SetVisibility(ESlateVisibility::Visible);

        // Update the position of the empty tile
        EmptyPos = ClickedPos;
        UpdateMenuTileVisibility();
    }
}





void USlidingPuzzleLogic::SetupBoard()
{
    if (MenuTiles.Num() != 16)
    {
        UE_LOG(LogTemp, Error, TEXT("Tiles array is not properly initialized."));
        return;
    }

    if (!TileGrid)
    {
        UE_LOG(LogTemp, Error, TEXT("TileGrid is invalid!"));
        return;
    }

    int n = 1;
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            Board[r][c] = (r == 3 && c == 3) ? 0 : n++;
        }
    }

    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            int TileIndex = Board[r][c];
            if (TileIndex < 0 || TileIndex >= MenuTiles.Num())
            {
                UE_LOG(LogTemp, Error, TEXT("TileIndex %d is out of bounds!"), TileIndex);
                continue;
            }

            UButton* TileButton = MenuTiles[TileIndex];
            if (!TileButton)
            {
                UE_LOG(LogTemp, Error, TEXT("TileButton at index %d is null!"), TileIndex);
                continue;
            }

            // Debugging visibility logic
            UE_LOG(LogTemp, Warning, TEXT("Setting visibility for TileIndex %d at position (%d, %d) to %s"),
                TileIndex, r, c, TileIndex == 0 ? TEXT("Hidden") : TEXT("Visible"));

            TileGrid->AddChildToUniformGrid(TileButton, r, c);
            TileButton->SetVisibility(TileIndex == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
            ButtonToGridMap.Add(TileButton, FIntPoint(r, c));
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Board setup complete."));
}
