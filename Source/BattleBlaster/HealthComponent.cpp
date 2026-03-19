// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);//为拥有该组件的Actor添加一个OnTakeAnyDamage事件的动态绑定，当该Actor受到任何类型的伤害时，会调用UHealthComponent类的OnDamageTaken函数
	//将获取gamemode的代码放在这里可以性能优化，因为我们只需要在游戏开始时获取一次游戏模式的指针，而不是在每次受到伤害时都获取一次。这样可以避免不必要的性能开销，提高游戏的效率。
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (GameMode)
	{
		BattleBlasterGameMode = Cast<ABattleBlasterGameMode>(GameMode);
	}

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage>0.0f)
	{
		Health -= Damage ;
		if (Health <= 0.0f)
		{
			if (BattleBlasterGameMode)
			{
				BattleBlasterGameMode->ActorDied(DamagedActor);
			}

		}
	}
}

