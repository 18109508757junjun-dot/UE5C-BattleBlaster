// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Towers;
	/*UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers)
	是一个函数调用，它的作用是在当前游戏世界中查找所有属于ATower类的演员，并将它们存储在Towers数组中。*/
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Display, TEXT("Number of towers: %d"), TowerCount);
	//UGameplayStatics::GetPlayerPawn(GetWorld(), 0)
	// 是一个函数调用，它的作用是在当前游戏世界中获取玩家控制的第一个角色（Pawn）。GetWorld()函数返回当前游戏世界的指针，0表示获取第一个玩家的角色。返回值是一个指向APawn类型的指针，代表玩家控制的角色。
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to find the tank actor!"));
		}

	}

	int32 LoopIndex = 0;
	while (LoopIndex < TowerCount)
	{
		AActor* TowerActor = Towers[LoopIndex];
		if (TowerActor)
		{
			ATower* Tower = Cast<ATower>(TowerActor);
			if (Tower && Tank)
			{
				Tower->Tank = Tank;
				UE_LOG(LogTemp, Display, TEXT("%s setting the tank variable!"), *Tower->GetActorNameOrLabel());
			}
		}

		LoopIndex++;
	}
}
