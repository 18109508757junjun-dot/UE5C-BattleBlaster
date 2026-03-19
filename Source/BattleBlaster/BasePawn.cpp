// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

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
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);//SpawnActor函数用于在游戏世界中生成一个新的Actor实例。它接受三个参数：要生成的Actor类、生成位置和生成旋转。这里我们使用了ProjectileClass作为要生成的Actor类，SpawnLocation作为生成位置，SpawnRotation作为生成旋转。
    if (Projectile)
	{
		Projectile->SetOwner(this);//将生成的Projectile实例的所有者设置为当前的BasePawn实例，即区分炮弹是tank的还是tower的
		// 如果Projectile有Damage属性，将当前Pawn的ProjectileDamage传递给它
		Projectile->Damage = ProjectileDamage;
	}
}
void ABasePawn::HandleDestruction()
{
	//UE_LOG(LogTemp, Display, TEXT("BasePawn HandleDestruction!"));
	if (DeathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation(), GetActorRotation());
		
	}

	if (ExplodeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, GetActorLocation());
	}

	if (DeathCameraShakeClass)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(DeathCameraShakeClass);
		}
	}
}

