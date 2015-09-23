#ifndef __GAME_TEAM_H__
#define __GAME_TEAM_H__

#include "cocos2d.h"
#include "Telegram.h"
#include "BaseGameEntity.h"
#include "Formation.h"

using namespace cocos2d;
using namespace std;

class GameCharacter;
class GoalTeamThink;

/**
*	�������ͣ���ǰ��Ҫ�����������ĸ���������ң��ĸ������ǵ��� 
*/
enum GameTeamTypeEnum
{
    GAME_TEAM_TYPE_PLAYER,          // ��Ҷ���
    GAME_TEAM_TYPE_ENEMY,           // �з�����
};

/**
	 ��Ϸ���ҷ�����ĸ��Ϊ��ʵ�ֶ��鼶�����ϡ�AI�ĸ���
     @_@    ����Ͳ����ǵз������������
*/
class GameTeam : public Ref
{
public:
    ~GameTeam();

    // ���ö�����ӳ�Ա��ͬʱָ���ý�ɫ�������е�λ�ñ��
    void addMember(GameCharacter* player, int posId = 0);

    // �Ӷ�����ɾ��ָ����Ա�����ǲ�������ý�ɫ
    void removeMember(GameCharacter* player);

    // ÿһ֡�лص����������������г�Ա��update
    void update(float dm);

    // ���ض�������
    Formation& getTeamFormation() { return m_formation; }

    // ��ʼ����ǰ��
    void collectiveForwardStart();

    // ��������ǰ�����ڿ�ʼ�����з�����֮ǰҪ����������������͵�Լ����
    void collectiveForwardEnd();

    // �����еĳ�Ա������Ϣ�������Ժ���鼶�����Ϊ��Ա���Դ�����ÿһ����Ա����Ŀ��
    void sendMessageToAllMember(Telegram& msg);

    // ��ĳ��ָ���Ľ�ɫ������Ϣ
    void sendMessageToOneMember(Telegram& msg, GameCharacter* aCharacter);

    // ���������ҵ�ָ��λ��id�ĳ�Ա�����û���ˣ��ͷ���null
    GameCharacter* getMemberIdFromFormation(int posId);

    const list<GameCharacter*>& getMembers() { return m_members; }

    // ���ض������
    GoalTeamThink* getTeamBrain() { return m_teamBrain; }

    // ����id������ȫ��Ψһ��ʾһ������
    CC_SYNTHESIZE(int, m_teamId, TeamId);

    // ����һ�����飬�ڵ������������ö���ͱ����뵽TeamMgr����
    static GameTeam* create(GameTeamTypeEnum teamType);

    // �Ƿ���Ա�ɾ��
    bool canRemove() { return (m_teamState & GAME_TEAM_STATE_REMOVE) != 0; }

private:
    GameTeam();

    // ɾ����������״̬�Ľ�ɫ
    void removeDeadCharacter();

    void setCanRemove() { m_teamState |= GAME_TEAM_STATE_REMOVE; }

    /**
    *	�����ƶ�״̬�� 
    */
    void setCollectiveForwardState() { m_teamMoveState = GAME_TEAM_MOVE_COLLECTIVEFORWARD; }
    void setStayState() { m_teamMoveState = GAME_TEAM_MOVE_STAY; }
    void setFollowPlayerState() { m_teamMoveState = GAME_TEAM_MOVE_FOLLOW_PLAYER; }

    bool iscollectiveForwardState() { return m_teamMoveState == GAME_TEAM_MOVE_COLLECTIVEFORWARD; }
    bool isStayState() { return m_teamMoveState == GAME_TEAM_MOVE_STAY; }
    bool isFollowPlayerState() { return m_teamMoveState == GAME_TEAM_MOVE_FOLLOW_PLAYER; }

    static int m_nextValidId;                                       // ��һ����Ч�ض���id

    /**
    *	���鵱ǰ״̬��λ
    */
    enum GameTeamStateEnum
    {
        GAME_TEAM_STATE_ACTIVE  =   0x0001,         // ��ǰ���鴦�ڻ�Ծ״̬
        GAME_TEAM_STATE_REMOVE  =   0x0002,         // �����Ƴ���ǰ������
    };

    list<GameCharacter*>        m_members;                          // ��������г�Ա
    Formation                   m_formation;                        // ����

    GoalTeamThink*              m_teamBrain;                        // ���鼶��Ĵ���

    float m_advanceRate;                                            // �����ƽ��ٶ�

    CC_SYNTHESIZE_READONLY(GameTeamTypeEnum, m_teamType, TeamType); // ��������

    int                        m_teamState;                        // ���鵱ǰ״̬

    /**
    *	���鵱ǰ�ƶ�״̬ 
    */
    enum GameTeamMoveStateEnum
    {
        GAME_TEAM_MOVE_STAY,                                    // �̶�
        GAME_TEAM_MOVE_COLLECTIVEFORWARD,                       // ����ǰ��
        GAME_TEAM_MOVE_FOLLOW_PLAYER,                           // ���ݳ�Ա
    };
    GameTeamMoveStateEnum       m_teamMoveState;

    float                       m_lastUpdateTime;               // ���һ�θ��µ�
};

#endif