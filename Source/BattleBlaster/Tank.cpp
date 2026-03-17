// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建一个弹簧臂组件，并将其附加到胶囊组件上
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CapsuleComp);

	//创建一个摄像机组件，并将其附加到弹簧臂组件上
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//获取玩家控制器 cast<>()是将（）里的对象转换成（）里的类型，如果转换成功就返回这个对象，如果转换失败就返回nullptr
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{//获取玩家控制器的本地玩家
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{//获取玩家控制器的增强输入子系统
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{//将默认输入映射上下文添加到增强输入子系统中
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}


}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		HitResult.ImpactPoint;
		RotateTurret(HitResult.ImpactPoint);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.0f, 12, FColor::Blue);
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);//绑定输入动作，当MoveAction被触发时调用ATank::MoveInput函数
		EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);
		EIC->BindAction(OpeanFireAction, ETriggerEvent::Started, this, &ATank::OpeanFire);
	}
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	DeltaLocation.X = InputValue * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());//UGameplayStatics::GetWorldDeltaSeconds(GetWorld())获取世界的每帧时间
	AddActorLocalOffset(DeltaLocation, true);//第二个参数为true表示如果发生碰撞会停止而不会穿过物体
	
}

void ATank::TurnInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	FRotator DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
	DeltaRotation.Yaw = InputValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalRotation(DeltaRotation, true);
}
