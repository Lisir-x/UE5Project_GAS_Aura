

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class A3_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	/*----------Enemy Interface----------*/
	//显示高亮
	virtual void HighlightActor() override;
	//取消高亮
	virtual void UnHighlightActor() override;
	/*-----------------------------------*/

protected:
	virtual void BeginPlay() override;
};
