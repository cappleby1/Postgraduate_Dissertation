#include "SlidingPuzzle.h"

void USlidingPuzzle::NativeConstruct()
{
    Super::NativeConstruct();
    SetupBoard();

    if (Tile_0) { Tile_0->OnClicked.AddDynamic(this, &USlidingPuzzle::OnTileClicked); }
        
}

void USlidingPuzzle::OnTileClicked()
{

}

void USlidingPuzzle::SetupBoard()
{
    //Fill board
    int n = 1;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 3; ++c)
            Board[r][c] = (r == 3 && c == 3) ? 0 : n++;

    EmptyPos = { 5, 3 };

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
