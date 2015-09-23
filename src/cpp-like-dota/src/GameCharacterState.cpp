#include "GameCharacterState.h"
#include "TeamManager.h"
#include "GoalCharacterThink.h"
#include "EntityManager.h"

void GameCharacterFrozenState::onEnter( GameCharacter *owner )
{
    // ���ƽ�ɫ����ٶ�Ϊ0���ý�ɫ�޷��ƶ�
    m_maxSpeed      =   owner->getMovingEntity().getMaxSpeed();
    owner->getMovingEntity().setMaxSpeed(0);

    // ֹͣ��ǰ����
    owner->getShape()->freezeAnimation();

    // @_@ �ڽ�ɫ���Ϸ���һ�����飬��ʱ�ȷ��������
    ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/xuejingling_VFX.ExportJson");
    m_iceCake   =   Armature::create("xuejingling_VFX");
    m_iceCake->setPosition(owner->getShape()->getCenterPosLocation());
    owner->getShape()->addChild(m_iceCake, 10);
    m_iceCake->getAnimation()->play("atk3");

    // ����Ҫ���ݽ�ɫ����Ĵ�С���Ա����������
    float tmpShapeW     =   owner->getShape()->getContentSize().width;
    float tmpShapeH     =   owner->getShape()->getContentSize().height;
    float tmpShapeWToH  =   tmpShapeW / tmpShapeH;
    const float tmpIceH     =   140;
    const float tmpIceW     =   50;
    const float tmpIceWToH  = tmpIceW / tmpIceH;
    if (tmpShapeWToH >= tmpIceWToH)
    {
        // �����ɫ��һЩ
        m_iceCake->setScale(tmpShapeW * 0.6 / tmpIceW);
    }
    else
    {
        m_iceCake->setScale(tmpShapeH * 0.6 / tmpIceH);
    }
}

void GameCharacterFrozenState::update( GameCharacter *owner, float dm )
{
    m_frozenTime    +=  dm;
    if (m_frozenTime >= m_maxFrozenTime)
    {
        owner->getFSM()->changeState(GameCharacterFreeState::create());
    }
}

void GameCharacterFrozenState::onExit( GameCharacter *owner )
{
    owner->getMovingEntity().setMaxSpeed(m_maxSpeed);

    owner->getShape()->unfreezeAnimation(true);

    m_iceCake->removeFromParent();
}

GameCharacterFrozenState::GameCharacterFrozenState()
{
    // @_@ ������д�ɣ�����2����
    m_maxFrozenTime =   2;
    m_frozenTime    =   0;
}


void GameCharacterHitedState::onEnter( GameCharacter* owner )
{
    // �����ܻ�����
    owner->getShape()->playAction(m_actionName, false);

    // ͬʱ�ý�ɫ����
    owner->dullOn();
}

void GameCharacterHitedState::update( GameCharacter *owner, float dm )
{
    // ����������Ϻ���˳�
    if (owner->getShape()->getCurrentAnimationName() != m_actionName)
    {
        owner->getFSM()->changeState(GameCharacterFreeState::create());
    }
}

void GameCharacterHitedState::onExit( GameCharacter *owner )
{
    owner->dullOff();
}

void GameCharacterTimidState::update( GameCharacter *owner, float dm )
{
    // ÿ�θ��¶����ж�Ѫ���Ƿ�������������
    auto tmpAttribute   =   owner->getAttribute();
    if (tmpAttribute.getHp() / tmpAttribute.getFullHp() <= 0.7)
    {
        auto tmpCurrentTeam =   owner->getTeam();
        auto tmpNextTeam    =   TeamMgr->getNextTeam(tmpCurrentTeam->getTeamId());
        if (tmpNextTeam != nullptr)
        {
            // �Ӷ������������ý�ɫ�ĵ�ǰĿ��
            tmpCurrentTeam->removeMember(owner);
            owner->getBrain()->removeAllSubgoals();

            // ������һ�����飬ͬʱ�����ָ����͵�������
            tmpNextTeam->addMember(owner);

            // �л�״̬Ϊ������
            owner->getFSM()->changeState(GameCharacterEscapeToNextTeam::create());
            owner->getFSM()->setGlobalState(nullptr);
        }
    }
}

void GameCharacterEscapeToNextTeam::onEnter( GameCharacter* owner )
{
    // ͬʱ�ѽ�ɫ������ٶȺ����
    m_originMaxForce    =   owner->getMovingEntity().getMaxForce();
    m_originMaxSpeed    =   owner->getMovingEntity().getMaxSpeed();
    owner->getMovingEntity().setMaxForce(2 * m_originMaxForce);
    owner->getMovingEntity().setMaxSpeed(2 * m_originMaxSpeed);

    owner->getSteeringBehaviros()->keepFormationOn();

    // @_@ ��������ʱд��
    owner->getSteeringBehaviros()->pursuitOff();
    owner->getSteeringBehaviros()->setTraction(Vec2::ZERO);
}

void GameCharacterEscapeToNextTeam::onExit( GameCharacter *owner )
{
    owner->getSteeringBehaviros()->keepFormationOff();
    owner->getMovingEntity().setMaxForce(m_originMaxForce);
    owner->getMovingEntity().setMaxSpeed(m_originMaxSpeed);
}

bool GameCharacterEscapeToNextTeam::onMessage( GameCharacter *owner, Telegram& msg )
{
    // ���������յ�������Ϣ��ʱ���л�������
    switch (msg.type)
    {
    case TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET:
        {
            owner->getFSM()->changeState(GameCharacterFreeState::create());
            return true;
        }

    default:
        break;
    }

    return false;
}
