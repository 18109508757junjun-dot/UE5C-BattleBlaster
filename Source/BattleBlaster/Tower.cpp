// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
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
	if (Tank && InFireRange())
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

	

