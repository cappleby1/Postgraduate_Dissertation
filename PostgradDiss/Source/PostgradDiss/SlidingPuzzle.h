// SlidingPuzzle.h
#pragma once

#include "CoreMinimal.h"
#include <string>
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "SlidingPuzzle.generated.h"     


UCLASS(Blueprintable)
class POSTGRADDISS_API USlidingPuzzle : public UUserWidget
{
    GENERATED_BODY()                   

protected:
    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* TileGrid;

    UPROPERTY(meta = (BindWidget))
    TArray<UButton*> MenuTiles;

    UPROPERTY(meta = (BindWidget))
    UButton* Tile_0;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_1;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_2;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_3;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_4;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_5;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_6;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_7;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_8;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_9;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_10;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_11;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_12;
    UPROPERTY(meta = (BindWidget))
    UButton* Tile_13;
    
    
    virtual void NativeConstruct() override; 

    // Board variables
    TArray<UButton*> Tiles;
    int Board[4][4];
    FIntPoint EmptyPos;
    int x;
    int y;
    int max_x = 4;
    int max_y = 3;
    TMap<UButton*, FIntPoint> ButtonToGridMap;


    UFUNCTION(BlueprintCallable)
    void OnTileClicked();
    UFUNCTION(BlueprintCallable)
    void SetupBoard();
    UFUNCTION(BlueprintCallable)
    bool IsAdjacent(int r, int c);
    UFUNCTION(BlueprintCallable)
    void UpdateMenuTileVisibility();

};
