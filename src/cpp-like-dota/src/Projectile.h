#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"
#include "GameCharacter.h"
#include "ProjectileMovingPart.h"
#include "ProjectileShapePart.h"

using namespace cocos2d;

/**
*	 ���ӵ����͡�����Ҫ��ϣ����ͨ��Զ�������벻ͬ�ġ��ӵ�������������
*   ��ɫ�Ĳ�ͬ��ͨԶ�̹�����ʽ
*/
enum ProjectileTypeEnum
{
    PROJECTILE_TYPE_GALAXO_BALL,                // ������
    PROJECTILE_TYPE_ZEUS_FLY_HAMMER,            // ��˹�ķɴ�
    PROJECTILE_TYPE_PIG_FLY_KNIFE,              // Ұ��ɵ�
    PROJECTILE_TYPE_NIU_FLY_SHIELD,             // ţ�ķɵ�
    PROJECTILE_TYPE_THEIF_FLY_DAGGER,           // �̿ͷ�ذ��
};

/**
*	���ӵ�״̬���ı�־λ����ȫΪ0��ʱ���ֱ��ɾ��
*/
enum ProjectileStateEnum
{
    PROJECTILE_STATE_UPDATEMOVEMENT =   0x00001,        // �ӵ������ƶ��ĸ���
    PROJECTILE_STATE_UPDATE         =   0x00002,        // ����λ������ĸ���
};

/**
*	 Զ�̹������������ġ��ӵ���
*/
class Projectile : public Ref
{
public:
    /**
    *	ֻ��ͨ������ӿڴ����ӵ���������Ϊ���ƹ��������ã������ṩһ������
    *   �Զ������ݵ���������create��Ӧ�����������ݲ�ͬ������ʹ���������
    */
    static Projectile* create(GameCharacterAttribute& att, ProjectileTypeEnum type, void* extraData, int ownerId);

    /**
    *	�ڴ˴����λ�Ƹ��£�����ʹ��ԭ���ļ̳з�ʽ�����ǲ���
    */
    void updateMovement(float dm);

    /**
    *	������ʾ�ڵ㣬������������ͼ����ʾ�б� 
    */
    CC_SYNTHESIZE(ProjectileShapePart*, m_shapePart, ShapePart);

    /**
    *	�ڴ˴���ɳ���λ�Ƹ����������������
    */
    virtual void update(float dm) = 0;

protected:
    /**
    *	�ӵ������λ�ú��ٶȻ��о��Ƿ����ߵ�����һ����棬��ײ���������������Ա仯��
    *   �ӵ��������뷢�����޹���
    */
    Projectile(GameCharacterAttribute& att);

    virtual ~Projectile();

    /**
    *	�ӵ��ƽ��������������ӵ����ƶ�����
    */
    CC_SYNTHESIZE(ProjectileMovingPart*, m_movingPart, MovingPart);

    /**
    *	�����ӵ���״̬ 
    */
    CC_SYNTHESIZE(int, m_state, State);

    /**
    *	���ӵ���ӵ���ߣ����Ƿ�����
    */
    CC_SYNTHESIZE_READONLY(int, m_ownerId, OwnerId);

    bool canUpdate() { return (m_state & PROJECTILE_STATE_UPDATE) != 0; }
    bool canUpdateMovement() { return (m_state & PROJECTILE_STATE_UPDATEMOVEMENT) != 0; }
    bool canRemove() { return m_state == 0; }
    void updateOff() { m_state &= ~PROJECTILE_STATE_UPDATE; }
    void updateMovementOff() { m_state &= ~PROJECTILE_STATE_UPDATEMOVEMENT; }

    /**
    *	�������ڼ���ķ����ߵĸ������� 
    */
    GameCharacterAttribute      m_senderAtt;

private:
    ProjectileTypeEnum          m_projectileType;               // ���ӵ�������
    static int m_count;
    CC_SYNTHESIZE_READONLY(int, m_projectileId, ProjectileId);  // Ψһ��ʶ

    // ���ƶ����ֵ���updateMovement֮ǰ��λ��
    Vec2                        m_lastPos;
};

#endif