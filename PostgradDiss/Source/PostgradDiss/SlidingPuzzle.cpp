#include "SlidingPuzzle.h"

void USlidingPuzzle::NativeConstruct()
{
    Super::NativeConstruct();
    SetupBoard();
    UE_LOG(LogTemp, Warning, TEXT("Board Set Up"));

    if (Tile_0) { Tile_0->OnClicked.AddDynamic(this, &USlidingPuzzle::OnTileClicked); }
        
}

void USlidingPuzzle::OnTileClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Tile Pressed"));

    UButton* ClickedTile = Tile_0; 
    FIntPoint ClickedPos = ButtonToGridMap[ClickedTile];

    if (IsAdjacent(ClickedPos.X, ClickedPos.Y))
    {
        Board[EmptyPos.X][EmptyPos.Y] = Board[ClickedPos.X][ClickedPos.Y];
        Board[ClickedPos.X][ClickedPos.Y] = 0;

        TileGrid->AddChildToUniformGrid(ClickedTile, EmptyPos.X, EmptyPos.Y);
        ClickedTile->SetVisibility(ESlateVisibility::Hidden);
        Tiles[0]->SetVisibility(ESlateVisibility::Visible);

        EmptyPos = ClickedPos;

        UpdateMenuTileVisibility();  
    }
}

bool USlidingPuzzle::IsAdjacent(int r, int c)
{
    int EmptyRow = EmptyPos.X;
    int EmptyCol = EmptyPos.Y;

    return (
        (r == EmptyRow && FMath::Abs(c - EmptyCol) == 1) || // Left/Right
        (c == EmptyCol && FMath::Abs(r - EmptyRow) == 1)    // Up/Down
        );
}

void USlidingPuzzle::UpdateMenuTileVisibility()
{
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            int Index = Board[r][c];
            UButton* MenuTile = MenuTiles[Index];  // or however you track menu tiles
            if (MenuTile)
            {
                MenuTile->SetVisibility(Index == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
                UE_LOG(LogTemp, Warning, TEXT("Menu Updated"));


                // Optionally update position or text/image on menu
            }
        }
    }
}


void USlidingPuzzle::SetupBoard()
{
    //Fill board
    int n = 1;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 3; ++c)
            Board[r][c] = (r == 3 && c == 3) ? 0 : n++;

    EmptyPos = { 4, 3 };

    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
        {
            int Index = Board[r][c];
            UButton* Tile = Tiles[Index];
            if (Tile)
            {
                TileGrid->AddChildToUniformGrid(Tile, r, c);
                Tile->SetVisibility(Index == 0 ? ESlateVisibility::Hidden: ESlateVisibility::Visible);
            }
        }
}
