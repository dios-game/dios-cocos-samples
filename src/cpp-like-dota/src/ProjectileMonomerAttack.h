#ifndef __PROJECTILE_GALAXO_BALL_H__
#define __PROJECTILE_GALAXO_BALL_H__

#include "Projectile.h"

/**
*	���幥�����ӵ�
*/
class ProjectileMonomerAttack : public Projectile
{
public:
    ProjectileMonomerAttack(GameCharacterAttribute& att, int targetId);
    virtual ~ProjectileMonomerAttack();

    virtual void update(float dm) override;

private:
    /**
    *	 �����Ƿ���ײ
    */    
    bool testCollision(Vec2 aPos1, Vec2 aPos2, Vec2 aTargetPos);
    int             m_targetId;         // ����Ŀ��
    const float     m_collisionDisSq;   // ��ײ����
};

#endif