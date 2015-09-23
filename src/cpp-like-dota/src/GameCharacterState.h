#ifndef __GAME_CHARACTER_STATE_H__
#define __GAME_CHARACTER_STATE_H__

#include "GameCharacter.h"
#include "State.h"

/**
*	��Ϸ��ɫ��������״̬��Ҳ����ƽʱ��ʱ���ڵ�״̬
*/
class GameCharacterFreeState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override
    {

    }

    virtual void update(GameCharacter *owner, float dm) override
    {

    }

    virtual void onExit(GameCharacter *owner) override
    {

    }

    CREATE_FUNC(GameCharacterFreeState);
};

/**
*	��ɫ���ڱ�����״̬����ɫһ��������վ��������ڹ̶���ʱ����
*   �ⶳ
*/
class GameCharacterFrozenState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter *owner) override;

    virtual void update(GameCharacter *owner, float dm) override;

    virtual void onExit(GameCharacter *owner) override;

    CREATE_FUNC(GameCharacterFrozenState);

protected:
    GameCharacterFrozenState();

    CC_SYNTHESIZE(float, m_maxFrozenTime, MaxFrozenTime);   // ��󶳽�ʱ�䣬�ڽ������Զ��ⶳ

private:
    /**
    *	��ʱ����һ���ڽ����״̬ǰ��ɫ��һЩ���ݣ������˳���״̬��ʱ��
    *   �ָ�����
    */
    float           m_maxSpeed;         // ����ǰ������ٶȣ��ڽ������Ϊ0
    float           m_frozenTime;       // �Ѿ�����ʱ��

    Armature*       m_iceCake;          // ����
};

/**
*	��ɫ�����ܻ�״̬ 
*/
class GameCharacterHitedState : public State<GameCharacter>
{
protected:
    GameCharacterHitedState():m_actionName("hit")
    {

    }

public:
    virtual void onEnter(GameCharacter* owner) override;

    virtual void update(GameCharacter *owner, float dm) override;

    virtual void onExit(GameCharacter *owner) override;

    CREATE_FUNC(GameCharacterHitedState);

private:
    const string m_actionName;
};

/**
*	��ɫ�������Ѫ��<=50%��ʱ��ͻ�Ӷ��������������һ�����飬Ҳ���ǵ�ǰ��ɫ��
*   ��С״̬
*/
class GameCharacterTimidState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override {}

    virtual void update(GameCharacter *owner, float dm) override;

    virtual void onExit(GameCharacter *owner) override {}

    CREATE_FUNC(GameCharacterTimidState);

private:
    
};

/**
*	��ǰ��ɫ�������ܵ���һ�������״̬��
*/
class GameCharacterEscapeToNextTeam : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override;

    virtual void update(GameCharacter *owner, float dm) override {}

    virtual void onExit(GameCharacter *owner) override;

    virtual bool onMessage(GameCharacter *owner, Telegram& msg) override;

    CREATE_FUNC(GameCharacterEscapeToNextTeam);

private:
    float       m_originMaxSpeed;           // ԭʼ������
    float       m_originMaxForce;
};

#endif