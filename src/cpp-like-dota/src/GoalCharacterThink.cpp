#include "GoalCharacterThink.h"
#include "GoalAttackSpecifiedTarget.h"
#include "TimeTool.h"

GoalCharacterThink::GoalCharacterThink( GameCharacter* owner )
    :GoalComposite<GameCharacter>(owner), m_processInterval(0.3)
{
    m_lastProcessTime   =   -1;
}

GoalCharacterThink::~GoalCharacterThink()
{

}

GoalStateEnum GoalCharacterThink::process()
{
    if (TimeTool::getSecondTime() - m_lastProcessTime > m_processInterval)
    {
        m_lastProcessTime   =   TimeTool::getSecondTime();
        return GoalComposite<GameCharacter>::process();
    }
    return active;
}

void GoalCharacterThink::activate()
{

}

/**
* �ҷ��ֶ�Ա�Ĵ����Ѿ�����˽��ܶ�����Ϣ�ĵط��ˣ�Ȼ����ݶ�����Ϣ�������Լ���Ŀ�� 
*/
bool GoalCharacterThink::handleMessage( Telegram& msg )
{
    // ���Ƚ�����Ŀ�괦��
    if (forwardMessageToFrontMostSubgoal(msg)) return true;

    switch (msg.type)
    {
    case TELEGRAM_ENUM_TEAM_COLLECTIVE_FORWARD:                 // ����֪ͨ���¸������ǰ��
        {
            m_pOwner->getSteeringBehaviros()->keepFormationOn();
            return true;
        }

    case TELEGRAM_ENUM_TEAM_CANCEL_COLLECTIVE_FORWARD:          // ����֪ͨ���²��ø��������
        {
            m_pOwner->getSteeringBehaviros()->keepFormationOff();
            return true;
        }

    case TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET:            // �����������¹���ָ��Ŀ��
        {
            // ɾ�����еĵ�ǰ����Ȼ���趨�µ�����
            removeAllSubgoals();
            TelegramAttackSpecifiedTarget* pMsg =   dynamic_cast<TelegramAttackSpecifiedTarget*>(&msg);
            addSubgoal(new GoalAttackSpecifiedTarget(m_pOwner, pMsg->targetId, pMsg->targetTeamId));
            return true;
        }

    default:
        break;
    }

    return false;
}
