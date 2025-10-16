

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"


UCLASS()
class A3_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	//在服务器和客户端需要初始化角色信息的位置
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/*----------敌人接口----------*/
	//获取角色等级
	virtual int32 GetPlayerLevel() override;
	/*--------------------------*/

private:
	//初始化角色信息
	virtual void InitAbilityActorInfo() override;
};
