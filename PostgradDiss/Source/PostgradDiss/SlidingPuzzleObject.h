// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "SlidingPuzzleObject.generated.h" 

UCLASS()
class POSTGRADDISS_API ASlidingPuzzleObject : public AActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> PuzzleWidgetClass; 

    UPROPERTY()
    UUserWidget* PuzzleWidget;

public:
    void OpenPuzzleMenu();
};
