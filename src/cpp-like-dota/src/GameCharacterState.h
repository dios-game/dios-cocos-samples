#ifndef __GAME_CHARACTER_STATE_H__
#define __GAME_CHARACTER_STATE_H__

#include "GameCharacter.h"
#include "State.h"

/**
*	游戏角色处于自由状态，也就是平时的时候处于的状态
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
*	角色处于被冰冻状态，角色一动不动的站在那里，并在固定的时间内
*   解冻
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

    CC_SYNTHESIZE(float, m_maxFrozenTime, MaxFrozenTime);   // 最大冻结时间，在结束后自动解冻

private:
    /**
    *	临时保存一下在进入该状态前角色的一些数据，以在退出该状态的时候
    *   恢复过来
    */
    float           m_maxSpeed;         // 进入前的最大速度，在进入后会变为0
    float           m_frozenTime;       // 已经冻结时间

    Armature*       m_iceCake;          // 冰块
};

/**
*	角色处于受击状态 
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
*	角色处于如果血量<=50%的时候就会从队伍脱离而加入下一个队伍，也就是当前角色是
*   胆小状态
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
*	当前角色处于逃跑到下一个队伍的状态中
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
    float       m_originMaxSpeed;           // 原始的数据
    float       m_originMaxForce;
};

#endif