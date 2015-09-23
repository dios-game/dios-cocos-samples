#ifndef __GOAL_THINK_H__
#define __GOAL_THINK_H__

#include "GoalComposite.h"

class GameCharacter;

/**
* 属于最高级的目标，不过对于队员级别的AI自己不再设置目标，而是由队伍级别
* 给队员分配目标，而队伍与队员之间的通信都是通过消息的方式
*/
class GoalCharacterThink : public GoalComposite<GameCharacter>
{
public:
    GoalCharacterThink(GameCharacter* owner);
    ~GoalCharacterThink();

    virtual GoalStateEnum process() override;

    virtual bool handleMessage(Telegram& msg) override;

protected:
    virtual void activate() override;

    virtual string getCompositeGoalDescribe() override
    {
        return "GoalCharacterThink";
    }

private:
    float       m_lastProcessTime;                  // 作为角色的大脑没必要process太频繁
    const float m_processInterval;
};

#endif