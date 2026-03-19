// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle是一个定时器句柄，用于管理和控制定时器的生命周期。它可以用来启动、停止、暂停和恢复定时器，以及查询定时器的状态。
	FTimerHandle FireTimerHandle;
	//GetWorldTimerManager()是一个函数调用，它的作用是获取当前游戏世界的定时器管理器。定时器管理器负责管理和调度游戏中的定时器，可以用来设置定时器、清除定时器、查询定时器状态等。
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);//参数依次是：定时器句柄、定时器所属对象、定时器回调函数、定时器间隔时间、是否循环。这个函数的作用是在游戏世界中设置一个定时器，当定时器触发时会调用ATower类的CheckFireCondition函数，定时器的间隔时间为FireRate秒，并且会循环触发。
}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (Tank && InFireRange() && Tank->IsAlive)
	{
		OpeanFire();
	}
}

bool ATower::InFireRange()
{
	bool Result = false;
	if (Tank)
	{
		float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());//FVector;;Dist()是一个函数调用，用来计算两个参数之间的距离。
		Result = (DistanceToTank <= FireRange);
	}

	return Result;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
