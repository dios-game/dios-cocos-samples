#ifndef __TEAM_MANAGER_H__
#define __TEAM_MANAGER_H__

#include "cocos2d.h"
#include "GameTeam.h"

using namespace std;

/**
	 Ϊ�˹���ǰ���ڵ����ж��飬��Ϊ���ǵ��Ժ���ܻ���ڷǳ���ı�ӣ���Ϊ
     ȫ�ֵ���
*/
class TeamManager
{
public:
    typedef map<int, GameTeam*> TeamMap;

    static TeamManager* instance();

    /**
    	 ÿһ֡���ã���ʵ���Ǹ���ÿһ֧����
    */
    void update(float dm);

    /**
    	 ע��һ������
    */
    void registerTeam(GameTeam* pTeam);

    /**
    	 Ϊ�˷����ⲿֱ�ӷ������еĶ���
    */
    const TeamMap& getTeamMap();

    /**
    	 ����
    */
    GameTeam* getTeamFromId(int id);

    /**
    *	���ض���idָ���Ķ������һ������ 
    */
    GameTeam* getNextTeam(int id);

private:
    // ɾ�����Ա�ɾ���Ķ���
    void removeCanRemoveTeam();

    static TeamManager* m_instance;

    TeamMap             m_allTeam;                  // �������еĶ��� 
};

#define TeamMgr TeamManager::instance()

#endif