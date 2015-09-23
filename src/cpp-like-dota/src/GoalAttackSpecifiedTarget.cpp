#include "GoalAttackSpecifiedTarget.h"
#include "EntityManager.h"
#include "GoalPursuitTarget.h"
#include "GameTeam.h"

GoalAttackSpecifiedTarget::GoalAttackSpecifiedTarget( GameCharacter* owner, int targetId, int targetTeamId )
    :GoalComposite<GameCharacter>(owner)
{
    m_targetId      =   targetId;
    m_targetTeamId  =   targetTeamId;
}

void GoalAttackSpecifiedTarget::activate()
{
    m_pOwner->getWeaponControlSystem()->setAttackTarget(m_targetId);
    // @_@ ����һ������ϵͳ�Ĳ���
    m_pOwner->getWeaponControlSystem()->update();
}

GoalStateEnum GoalAttackSpecifiedTarget::process()
{
    activateIfInactive();

    do 
    {
        // ����趨Ŀ���Ѿ������ˣ����Ǹ�Ŀ���Ѿ����
        if (!isTargetAlive())
        {
            m_goalState = completed;
            break;
        }

        // ����ڹ�����Χ�ڣ���ֱ��ʹ������ϵͳ��������
        if (isInAttackDistance())
        {
            removeAllSubgoals();
            // ʹ�õ�ǰ����ϵͳ����
            auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
            m_pOwner->getWeaponControlSystem()->takeWeaponAndAttack(tmpCharacter);
        }
        else
        {
            // ������趨��׷����Ŀ��
            if (m_subgoalList.empty())
            {
                addSubgoal(new GoalPursuitTarget(m_pOwner, m_targetId));
            }
        }

        // ִ����Ŀ�꣬@_@ �������Ŀ���Ƿ���ɲ��������Ŀ�����
        processSubgoals();

    } while (0);

    return m_goalState;
}

bool GoalAttackSpecifiedTarget::isTargetAlive()
{
    /**
    *	��ʧĿ�������г��˽�ɫ���������ǽ�ɫ�Ѿ��뿪ԭ���Ķ��� 
    */
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpCharacter != nullptr && tmpCharacter->getTeam()->getTeamId() == m_targetTeamId && tmpCharacter->isAlive();
}

bool GoalAttackSpecifiedTarget::isInAttackDistance()
{
    // ������Ҫ���ݵ�ǰ���������ж��Ƿ��ڹ�����Χ��
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return m_pOwner->getWeaponControlSystem()->isInAttackRange(tmpCharacter);
}
