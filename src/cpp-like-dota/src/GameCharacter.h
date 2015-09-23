#ifndef __GAME_CHARACTER_H__
#define __GAME_CHARACTER_H__

#include "BaseGameEntity.h"
#include "GameCharacterShape.h"
#include "GameCharacterAttribute.h"

#include "WeaponControlSystem.h"

#include "MovingEntity.h"
#include "SteeringBehaviors.h"

#include "StateMachine.h"

using namespace std;

class GameTeam;
class GoalCharacterThink;

/**
	 �ڴ����е���Ϸ��ɫ
*/
class GameCharacter : public BaseGameEntity
{
private:
    typedef StateMachine<GameCharacter> CharacterStateMachine;  

public:
    /**
    	 @_@ ��Ҫ�Ǵ���һ����ɫ��Ҫ�Ĳ���̫�࣬�Ժ�Ӧ���Ǵ����ñ��л�ȡ��
         ��������дһЩ��ɫ����
    */
    static GameCharacter* create(int id);

    /**
    	 ÿһ֡�ĸ���
    */
    virtual void update(float dm) override;

    /**
    	 ����������Ϣ��
    */
    virtual bool handleMessage(Telegram& msg) override;

    GameCharacterShape *getShape() { return m_shape; };

    /**
    	 ���ڽ�ɫ���ԵĲ���
    */
    GameCharacterAttribute& getAttribute() { return m_attribute; }
    WeaponControlSystem* const getWeaponControlSystem() { return m_weaponControlSystem; }
    MovingEntity& getMovingEntity() { return m_movingEntity; }
    SteeringBehaviors* const getSteeringBehaviros() { return m_steeringBehaviors; }

    /**
    * �йص�ǰ��ɫ״̬���ж� 
    */
    bool isAlive() { return m_state == alive; }
    bool isDead() { return m_state == dead; }

    /**
    *	�й�״̬������ 
    */
    void dullOn() { m_state |= dull; }
    void dullOff() { m_state &= ~dull; }

    /**
    * �йص�ǰĿ����жϣ������ڶ������Ŀ���ʱ����õ�����ӿ�
    */
    bool hasGoal();

    // ����״̬��
    CharacterStateMachine* getFSM() { return m_stateMachine; }

    // ���úͷ��ظý�ɫ�����Ķ��� 
    CC_SYNTHESIZE(GameTeam*, m_team, Team);

    // ��ɫid����ʾһ�����͵����� 
    CC_SYNTHESIZE_READONLY(int, m_characterId, CharacterId);

protected:
    GameCharacter();
    ~GameCharacter();

    /**
    * ���µ�ǰ������ 
    */
    void updateMovement(float dm);

    /**
    * ��ɫ�ĵ�ǰ״̬
    * @_@ Ŀǰֻ�����ͻ�����״̬
    */
    enum GameCharacterStateEnum
    {
        alive,                                // ��ǰ����
        dead,                                 // �Ѿ�����
        dull    =   0x0004,                   // �����λ�Ͳ�����update
    };

    bool On(GameCharacterStateEnum state) { return (m_state & state) != 0; }

    GameCharacterShape*             m_shape;                    // �ý�ɫ������
    GameCharacterAttribute          m_attribute;                // �ý�ɫ�ĸ�������

    CC_SYNTHESIZE_READONLY(GoalCharacterThink*, m_brain, Brain);// ��Ϊ���Դ��ڵģ���Ŀ��滮����߼���

    /**
    * һЩϵͳ
    */
    WeaponControlSystem*            m_weaponControlSystem;      // ����ϵͳ

    MovingEntity                    m_movingEntity;             // ���������ɫ�ƶ��Ķ���
    SteeringBehaviors*              m_steeringBehaviors;        // ��������������

    int                             m_state;                    // ��ɫ��ǰ��ǰ״̬
 
    CharacterStateMachine*   m_stateMachine;                    // ��ɫ��״̬��
};

#endif