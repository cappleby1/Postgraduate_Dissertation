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

    for (int i = 0; i < MenuTiles.Num(); ++i)
    {
        if (MenuTiles[i])
        {
            MenuTiles[i]->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
        }
    }
}



void USlidingPuzzleLogic::OnTileClicked()
{
    if (!CurrentButton) return;

    // Your logic to handle the tile movement
    UButton* ClickedButton = CurrentButton;

    // Check if the clicked button exists in ButtonToGridMap
    if (ButtonToGridMap.Contains(ClickedButton))
    {
        FIntPoint ClickedPos = ButtonToGridMap[ClickedButton];
        UE_LOG(LogTemp, Warning, TEXT("Tile clicked at position: [%d, %d]"), ClickedPos.X, ClickedPos.Y);

        if (IsAdjacent(ClickedPos.X, ClickedPos.Y))
        {
            // Logic for moving the tile
            Board[EmptyPos.X][EmptyPos.Y] = Board[ClickedPos.X][ClickedPos.Y];
            Board[ClickedPos.X][ClickedPos.Y] = 0;

            // Update UI, grid position, visibility
            TileGrid->AddChildToUniformGrid(ClickedButton, EmptyPos.X, EmptyPos.Y);
            ClickedButton->SetVisibility(ESlateVisibility::Hidden);  // Hide the clicked tile

            // Update the empty tile visibility
            UButton* EmptyTile = Tiles[0];
            EmptyTile->SetVisibility(ESlateVisibility::Visible);

            // Update position
            EmptyPos = ClickedPos;
            UpdateMenuTileVisibility();
        }
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
            if (TileIndex >= 0 && TileIndex < MenuTiles.Num())  
            {
                UButton* TileButton = MenuTiles[TileIndex];
                if (TileButton)
                {
                    TileButton->SetVisibility(TileIndex == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
                    UE_LOG(LogTemp, Warning, TEXT("Menu Updated"));
                }
            }
        }
    }
}


void USlidingPuzzleLogic::SetupBoard()
{
    if (Tiles.Num() != 16)
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
            if (TileIndex < 0 || TileIndex >= Tiles.Num())
            {
                UE_LOG(LogTemp, Error, TEXT("TileIndex %d is out of bounds!"), TileIndex);
                continue;
            }

            UButton* TileButton = Tiles[TileIndex];  
            if (!TileButton)
            {
                UE_LOG(LogTemp, Error, TEXT("TileButton at index %d is null!"), TileIndex);
                continue;
            }

            TileGrid->AddChildToUniformGrid(TileButton, r, c);

            TileButton->SetVisibility(TileIndex == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

            ButtonToGridMap.Add(TileButton, FIntPoint(r, c));
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Board setup complete."));
}


