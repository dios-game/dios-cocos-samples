#ifndef __GOAL_H__
#define __GOAL_H__

#include "cocos2d.h"
#include "Telegram.h"

using namespace std;

template <class entity_type>
class GoalComposite;

/**
* ��ǰĿ���״̬��ö��
*/
enum GoalStateEnum
{
    active,
    inactive,
    completed,
    failed
};

/**
*  ����Ŀ��Ļ��࣬�����ԭ��Ŀ�꣬���ܴ�����Ŀ�꣬��Ŀ��Ӧ��������ȥ�ص�ʵ��Ľӿ�
*  ������ʵ����ɸ�Ŀ��
*/
template <class entity_type>
class Goal
{
public:

    /**
    * �Ե�ǰ״̬���ж� 
    */
    bool isComplete()const{return m_goalState == completed;} 
    bool isActive()const{return m_goalState == active;}
    bool isInactive()const{return m_goalState == inactive;}
    bool hasFailed()const{return m_goalState == failed;}

    /**
    * Ŀ��Ҳ�д�����Ϣ������ 
    */
    virtual bool handleMessage(Telegram& msg) { return false; }

    /**
    *	����Ŀ�������
    */
    virtual string getGoalDescribe()
    {
        return "";
    }

protected:
    Goal(entity_type* owner)
    {
        m_pOwner    =   owner;
        m_goalState =   inactive;
    }

    virtual ~Goal()
    {

    }

    /**
    * Ϊ�˷������ֻ�д���δ����״̬��ʱ��ŵ���activate��
    */
    void activateIfInactive()
    {
        if (isInactive())
        {
            m_goalState = active;
            activate();
        }
    }

    /**
    *  �����Ŀ����߼���Ҳ���ǿ�ʼ���ո�Ŀ���Ҫȥ������ɫʵ�ָ�Ŀ��
    */
    virtual void activate() = 0;

    /**
    * ��ʱ�����Ŀ�꣬����᷵�ظ�Ŀ��ĵ�ǰ״̬�������Ŀ�� 
    */
    virtual GoalStateEnum process() = 0;

    /**
    * ��Ŀ�������ʱ�����õģ�����ȡ����ǰĿ���
    */
    virtual void terminate() {m_goalState = completed;}

    /**
    * ԭ��Ŀ�����޷�����Ŀ��ģ�����Ϊ�˱�֤��GoalCompositeͳһ�Ľӿ�
    * �ں���׷��Ŀ��
    */
    virtual void addSubgoal(Goal<entity_type>* goal)
    {
        assert(false && "Cannot add goals to atomic goals");
    }

    /**
    * ��ǰ���������Ŀ����� 
    */
    virtual void pushSubgoal(Goal<entity_type>* goal)
    {
        assert(false && "Cannot push goals to atomic goals");
    }

    friend class GoalComposite<entity_type>;

protected:
    GoalStateEnum       m_goalState;                    // Ŀ��״̬
    entity_type*        m_pOwner;                       // Ŀ���ӵ����
};

#endif