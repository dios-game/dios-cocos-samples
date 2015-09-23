#ifndef __PROJECTILE_GALAXO_BALL_H__
#define __PROJECTILE_GALAXO_BALL_H__

#include "Projectile.h"

/**
*	单体攻击型子弹
*/
class ProjectileMonomerAttack : public Projectile
{
public:
    ProjectileMonomerAttack(GameCharacterAttribute& att, int targetId);
    virtual ~ProjectileMonomerAttack();

    virtual void update(float dm) override;

private:
    /**
    *	 测试是否碰撞
    */    
    bool testCollision(Vec2 aPos1, Vec2 aPos2, Vec2 aTargetPos);
    int             m_targetId;         // 攻击目标
    const float     m_collisionDisSq;   // 碰撞距离
};

#endif