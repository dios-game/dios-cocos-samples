#ifndef __GOAL_COMPOSITE_H__
#define __GOAL_COMPOSITE_H__

#include <list>
#include <assert.h>
#include "Goal.h"

using namespace std;

/**
* ���Ŀ���࣬��Ŀ���ɶ����Ŀ����� 
*/
template <class entity_type>
class GoalComposite : public Goal<entity_type>
{
public:
    /**
    * �Ƿ�ӵ����Ŀ�� 
    */
    bool hasSubgoal()
    {
        return m_subgoalList.size() > 0;
    }

    /**
    * ������Ϣ 
    */
    virtual bool handleMessage(Telegram& msg) override
    {
        return forwardMessageToFrontMostSubgoal(msg);
    }

    /**
    *	���ص�ǰ��ǰ���Ŀ������
    */
    virtual string getGoalDescribe() override
    {
        if (m_subgoalList.size() > 0)
        {
            return m_subgoalList.front()->getGoalDescribe();
        }
        else
        {
            return getCompositeGoalDescribe();
        }
    }

    /**
    * �Ƴ���Ŀ���������Ŀ��
    */
    void removeAllSubgoals()
    {
        auto tmpIterator = m_subgoalList.begin();
        for (; tmpIterator != m_subgoalList.end(); tmpIterator++)
        {
            (*tmpIterator)->terminate();

            // �����Ŀ��Ҳ�����Ŀ�꣬�ͻ��ڹ��캯����ȥ����������������Ŀ��
            delete *tmpIterator;
        }

        m_subgoalList.clear();
    }

protected:
    GoalComposite(entity_type* owner):Goal<entity_type>(owner)
    {

    }

    virtual ~GoalComposite()
    {
        removeAllSubgoals();
    }

    virtual void activate() = 0;

    /**
    * ������ϵ������Ĭ�ϵ�process��ֻ�Ǵ�����Ŀ�� 
    */
    virtual GoalStateEnum process()
    {
        this->activateIfInactive();

        this->m_goalState = processSubgoals();

        // Ĭ����������ʧ�ܣ���ɾ�����е���Ŀ��
        if (this->m_goalState == failed)
        {
            removeAllSubgoals();
        }
        return this->m_goalState;
    }

    /**
    *	�������Ŀ�������ʱ����Ҫ����������Ŀ���terminate 
    */
    virtual void terminate() override
    {
        removeAllSubgoals();
        Goal<entity_type>::terminate();
    }

protected:
    /**
    * �ں���׷��Ŀ����� 
    */
    virtual void addSubgoal(Goal<entity_type>* goal) override
    {
        assert(goal != nullptr && goal != this);

        m_subgoalList.push_back(goal);
    }

    /**
    * ��ǰ��׷��Ŀ�����
    */
    virtual void pushSubgoal(Goal<entity_type>* goal) override
    {
        assert(goal != nullptr && goal != this);

        m_subgoalList.push_front(goal);
    }

    /**
    * ������Ŀ�꣬��������Ŀ��Ĵ�����������������Ŀ�괦����ɣ��ͻ᷵��completed���������Ŀ��ʧ��
    * �ͻ᷵��ʧ�ܣ����ĳ����Ŀ����ɣ����ǻ�ʣ����Ŀ�꣬�ͻ᷵��activate��ʾ��Ŀ����Ȼ��Ծ
    */
    GoalStateEnum processSubgoals()
    {
        // ɾ���Ѿ���ɵ���Ŀ�꣬@_@ ֮���Ի�����������Ϊ��������Ŀ���ڲ��߼���ͨ�����Լ�����Ϊcompleted�������Լ�
        // ���������һ������Ҳɾ��ʧ�ܵ�Ŀ�꣬��Ϊ���ܻ�����Ŀ��ʧ�ܺ󣬸�Ŀ�����¹滮��Ŀ���ʱ��������removeAllSubgoals
        while (m_subgoalList.size() > 0 && m_subgoalList.front()->isComplete())
        {
            m_subgoalList.front()->terminate();
            delete m_subgoalList.front();
            m_subgoalList.pop_front();
        }

        // �����ǰ��Ŀ��û���ˣ���ô�����Ѿ����
        if (m_subgoalList.empty())
        {
            return completed;
        }

        // �����һ����Ŀ��
        GoalStateEnum tmpGoalState = m_subgoalList.front()->process();
        if (tmpGoalState == completed)
        {
            // �������Ŀ��ִ�гɹ����ͻ�ɾ��
            m_subgoalList.front()->terminate();
            delete m_subgoalList.front();
            m_subgoalList.pop_front();

            if (m_subgoalList.empty())
            {
                // ������е���Ŀ���Ѿ�������
                return completed;
            }
            else
            {
                // ��ʾ��Ŀ����Ȼ�ڻ�Ծ��
                return active;
            }
        }

        return tmpGoalState;
    }

    /**
    * ����Ϣ���ɸ���ǰ�����Ŀ�� 
    */
    bool forwardMessageToFrontMostSubgoal(Telegram& msg)
    {
        if (!m_subgoalList.empty())
        {
            return m_subgoalList.front()->handleMessage(msg);
        }
        return false;
    }

protected:
    virtual string getCompositeGoalDescribe()
    {
        return "";
    }
    typedef list<Goal<entity_type>*>    SubgoalList;

    SubgoalList     m_subgoalList;                          // ��Ŀ��
};

#endif