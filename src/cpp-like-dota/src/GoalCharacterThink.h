#ifndef __GOAL_THINK_H__
#define __GOAL_THINK_H__

#include "GoalComposite.h"

class GameCharacter;

/**
* ������߼���Ŀ�꣬�������ڶ�Ա�����AI�Լ���������Ŀ�꣬�����ɶ��鼶��
* ����Ա����Ŀ�꣬���������Ա֮���ͨ�Ŷ���ͨ����Ϣ�ķ�ʽ
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
    float       m_lastProcessTime;                  // ��Ϊ��ɫ�Ĵ���û��Ҫprocess̫Ƶ��
    const float m_processInterval;
};

#endif