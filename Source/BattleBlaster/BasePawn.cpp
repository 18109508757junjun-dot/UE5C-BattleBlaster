// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建一个胶囊组件，并将其设置为根组件
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	//创建一个静态网格组件(炮台)，并将其附加到胶囊组件上
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	//创建一个静态网格组件(炮塔)，并将其附加到炮台身体上
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	//创建一个场景组件(发射点)，并将其附加到炮塔上
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();//获取炮塔位置到目标位置的向量
	FRotator LookAtRotation = FRotator(0.f, VectorToTarget.Rotation().Yaw, 0.f);//获取炮塔位置到目标位置的旋转
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 10.0f);//使用这个参数可以让旋转变得更平滑。
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABasePawn::OpeanFire()
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	/*DrawDebugSphere(GetWorld(), SpawnLocation, 20.0f, 12, FColor::Yellow,false,3.f);*/
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
}



