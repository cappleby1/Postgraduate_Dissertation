#include "SlidingPuzzleLogic.h"

void USlidingPuzzleLogic::NativeConstruct()
{
    Super::NativeConstruct();

    SetupBoard();
    UE_LOG(LogTemp, Warning, TEXT("Board Set Up"));

    // Lambda binding for each button
    if (Tile_0) Tile_0->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_1) Tile_1->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_2) Tile_2->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_3) Tile_3->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_4) Tile_4->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_5) Tile_5->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_6) Tile_6->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_7) Tile_7->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_8) Tile_8->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_9) Tile_9->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_10) Tile_10->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_11) Tile_11->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_12) Tile_12->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
    if (Tile_13) Tile_13->OnClicked.AddDynamic(this, &USlidingPuzzleLogic::OnTileClicked);
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
        (r == EmptyRow && FMath::Abs(c - EmptyCol) == 1) || // Left/Right
        (c == EmptyCol && FMath::Abs(r - EmptyRow) == 1)    // Up/Down
        );
}

void USlidingPuzzleLogic::UpdateMenuTileVisibility()
{
    // Loop through all the tiles and update visibility based on the board's state
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            int TileIndex = Board[r][c];  // Get the index of the tile
            if (TileIndex >= 0 && TileIndex < MenuTiles.Num())  // Ensure it's within bounds
            {
                UButton* TileButton = MenuTiles[TileIndex];
                if (TileButton)
                {
                    // Hide the tile if it's the empty space (TileIndex == 0)
                    TileButton->SetVisibility(TileIndex == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
                    UE_LOG(LogTemp, Warning, TEXT("Menu Updated"));
                }
            }
        }
    }
}


void USlidingPuzzleLogic::SetupBoard()
{
    int n = 1;
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            // Set the board values (3x3 grid of numbers and one empty space)
            Board[r][c] = (r == 3 && c == 3) ? 0 : n++;  // Last cell is 0 (empty space)
        }
    }

    EmptyPos = { 3, 3 };  // Empty space starts at the bottom-right corner

    // Now fill in the grid with buttons and map them to grid positions
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            int TileIndex = Board[r][c];

            UButton* TileButton = Tiles[TileIndex];  // Assuming Tiles[] holds your UButton references
            if (TileButton)
            {
                // Add button to the UniformGrid
                TileGrid->AddChildToUniformGrid(TileButton, r, c);

                // Set visibility for the empty tile
                TileButton->SetVisibility(TileIndex == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

                // Populate the ButtonToGridMap for quick lookups
                ButtonToGridMap.Add(TileButton, FIntPoint(r, c));
            }
        }
    }
}

