// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "ScreenMessage.h"
#include "BattleBlasterGameMode.generated.h"

/**
 *
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;

	UScreenMessage* ScreenMessageWidget;


	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;

	ATank* Tank;
	int32 TowerCount;
	int32 CountdownDelay = 3;
	int32 CountdownSeconds;

	FTimerHandle CountdownTimerHandle;

	bool IsVictory = false;

	void ActorDied(AActor* DeadActor);

	void OnGameOverTimeOut();//这个函数的作用是在游戏结束后执行一些操作，比如显示游戏结束界面或者重置游戏状态。
	void OnCountdownTimeOut();//这个函数的作用是在倒计时结束后执行一些操作，比如开始游戏或者显示倒计时结束的提示。
};