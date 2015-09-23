#include "GoalTeamAttackTargetTeam.h"
#include "GoalTeamAdvance.h"
#include "GameCharacter.h"
#include "MessageDispatcher.h"
#include "TeamManager.h"
#include "MathTool.h"

GoalTeamAttackTargetTeam::GoalTeamAttackTargetTeam( GameTeam* owner, GameTeam* target ) 
    :GoalComposite<GameTeam>(owner), m_attDistance(500)
{
    m_targetTeam    =   target;
    m_targetId      =   target->getTeamId();
    
    // 0��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[0].push_back(0);
    m_targetRule[0].push_back(1);
    m_targetRule[0].push_back(2);
    m_targetRule[0].push_back(3);
    m_targetRule[0].push_back(4);
    m_targetRule[0].push_back(5);
    m_targetRule[0].push_back(6);
    m_targetRule[0].push_back(7);
    m_targetRule[0].push_back(8);

    // 1��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[1].push_back(1);
    m_targetRule[1].push_back(0);
    m_targetRule[1].push_back(2);
    m_targetRule[1].push_back(4);
    m_targetRule[1].push_back(3);
    m_targetRule[1].push_back(5);
    m_targetRule[1].push_back(7);
    m_targetRule[1].push_back(6);
    m_targetRule[1].push_back(8);

    // 2��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[2].push_back(2);
    m_targetRule[2].push_back(1);
    m_targetRule[2].push_back(0);
    m_targetRule[2].push_back(5);
    m_targetRule[2].push_back(4);
    m_targetRule[2].push_back(3);
    m_targetRule[2].push_back(8);
    m_targetRule[2].push_back(7);
    m_targetRule[2].push_back(6);

    // 3��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[3].push_back(0);
    m_targetRule[3].push_back(1);
    m_targetRule[3].push_back(2);
    m_targetRule[3].push_back(3);
    m_targetRule[3].push_back(4);
    m_targetRule[3].push_back(5);
    m_targetRule[3].push_back(6);
    m_targetRule[3].push_back(7);
    m_targetRule[3].push_back(8);

    // 4��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[4].push_back(1);
    m_targetRule[4].push_back(0);
    m_targetRule[4].push_back(2);
    m_targetRule[4].push_back(4);
    m_targetRule[4].push_back(3);
    m_targetRule[4].push_back(5);
    m_targetRule[4].push_back(7);
    m_targetRule[4].push_back(6);
    m_targetRule[4].push_back(8);

    // 5��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[5].push_back(2);
    m_targetRule[5].push_back(1);
    m_targetRule[5].push_back(0);
    m_targetRule[5].push_back(5);
    m_targetRule[5].push_back(4);
    m_targetRule[5].push_back(3);
    m_targetRule[5].push_back(8);
    m_targetRule[5].push_back(7);
    m_targetRule[5].push_back(6);

    // 6��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[6].push_back(0);
    m_targetRule[6].push_back(1);
    m_targetRule[6].push_back(2);
    m_targetRule[6].push_back(3);
    m_targetRule[6].push_back(4);
    m_targetRule[6].push_back(5);
    m_targetRule[6].push_back(6);
    m_targetRule[6].push_back(8);

    // 7��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[7].push_back(1);
    m_targetRule[7].push_back(0);
    m_targetRule[7].push_back(2);
    m_targetRule[7].push_back(4);
    m_targetRule[7].push_back(3);
    m_targetRule[7].push_back(5);
    m_targetRule[7].push_back(7);
    m_targetRule[7].push_back(6);
    m_targetRule[7].push_back(8);

    // 8��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[8].push_back(2);
    m_targetRule[8].push_back(1);
    m_targetRule[8].push_back(0);
    m_targetRule[8].push_back(5);
    m_targetRule[8].push_back(4);
    m_targetRule[8].push_back(3);
    m_targetRule[8].push_back(8);
    m_targetRule[8].push_back(7);
    m_targetRule[8].push_back(6);
}

void GoalTeamAttackTargetTeam::activate()
{
    // �жϾ��룬����������Ӿ���̫Զ�����øò������ߵ���ط�һ������ĵط�
    auto tmpOwnerXPos   =   m_pOwner->getTeamFormation().getFormationAnchor().x;
    auto tmpTargetXPos  =   m_targetTeam->getTeamFormation().getFormationAnchor().x;
    if (abs(tmpTargetXPos - tmpOwnerXPos) > m_attDistance)
    {
        if (m_pOwner->getTeamFormation().getFormationType() == Formation::FORMATION_TYPE_RIGHT)
        {
            addSubgoal(new GoalTeamAdvance(m_pOwner, tmpTargetXPos - m_attDistance));
        }
        else if (m_pOwner->getTeamFormation().getFormationType() == Formation::FORMATION_TYPE_LEFT)
        {
            addSubgoal(new GoalTeamAdvance(m_pOwner, tmpTargetXPos + m_attDistance));
        }
    }
}

GoalStateEnum GoalTeamAttackTargetTeam::process()
{
    // ��������Ӧ�����ݹ۴�֣���ʱ�����ȷ�������ֱ���Է���������Ÿ�Ϊcompleted
    activateIfInactive();
    
    // ����Ŀ�������ŻῪս
    if (processSubgoals() == completed)
    {
        inspectTeamMembers();
    }

    return m_goalState;
}

void GoalTeamAttackTargetTeam::inspectTeamMembers()
{
    // �ж��Ƿ��ж���ʧ����
    if (isWin())
    {
        // Ŀ�����
        m_goalState =   completed;
        return;
    }

    /**
    * ���������չ���˳�����θ���Ա���ù���Ŀ�� 
    */
    auto tmpOwnMembers      =   m_pOwner->getMembers();
    auto tmpTargetMembers   =   m_targetTeam->getMembers();

    // ��ʼ�����ҷ���ɫ
    for (auto tmpIterator = tmpOwnMembers.begin(); tmpIterator != tmpOwnMembers.end(); tmpIterator++)
    {
        auto tmpOwnCharacter    =   dynamic_cast<GameCharacter*>(*tmpIterator);
        if (tmpOwnCharacter->hasGoal())
        {
            // ��ǰ��Ŀ��Ķ�Ա�Ͳ��ù�
            continue;
        }
        auto tmpRule            =   m_targetRule[tmpOwnCharacter->getMovingEntity().getFormationPosId()];
        GameCharacter* tmpTarget=   nullptr;
        for (auto tmpPosIterator = tmpRule.begin(); tmpPosIterator != tmpRule.end(); tmpPosIterator++)
        {
            // �ӹ�����ǰ��Ѱ�ҵ�һ����λ���˵�
            tmpTarget   =   m_targetTeam->getMemberIdFromFormation(*tmpPosIterator);
            if (tmpTarget != nullptr)
            {
                break;
            }
        }

        if (tmpTarget != nullptr)
        {
            // ������Ϣ��֪����
            auto tmpMsg = TelegramAttackSpecifiedTarget::create(tmpOwnCharacter->getId(),
                tmpTarget->getId(), tmpTarget->getTeam()->getTeamId());
            m_pOwner->sendMessageToOneMember(*tmpMsg, tmpOwnCharacter);
        }

        break;
    }
}

bool GoalTeamAttackTargetTeam::isWin()
{
    // �з�������ʧ
    return TeamMgr->getTeamFromId(m_targetId) == nullptr;
}
