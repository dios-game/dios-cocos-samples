#include "NormalCloseRangeWeapon.h"
#include "MessageDispatcher.h"
#include "TimeTool.h"
#include "MathTool.h"

NormalCloseRangeWeapon::NormalCloseRangeWeapon( GameCharacter* owner, float minAttackInterval, string actionName )
    :Weapon(owner, NORMAL_CLOSE_RANGE_WEAPON), m_actionName(actionName), m_xOffset(80), m_yOffset(8)
{
    m_minAttackInterval     =   minAttackInterval;
    m_nextAttackReadyTime   =   0;
}

NormalCloseRangeWeapon::~NormalCloseRangeWeapon()
{

}

void NormalCloseRangeWeapon::attack( GameCharacter* target )
{
    // ������ͨ�Ľ��̹���ֻ��Ҫ���Ŷ�����Ȼ���ڶ�Ӧ�Ķ���֡������Ϣ��OK��
    m_pOwner->getShape()->playAction(m_actionName, false, 
        std::bind(&NormalCloseRangeWeapon::onAttackEffect, this, std::placeholders::_1));
    m_lastAttackTime        =   TimeTool::getSecondTime();
    m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
    m_targetId              =   target->getId();
}

bool NormalCloseRangeWeapon::isInAttackRange( GameCharacter* target )
{
    auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
    auto tmpTargetPos   =   target->getMovingEntity().getPosition();
    auto tmpOwnerRadius =   m_pOwner->getMovingEntity().getRadius();
    auto tmpTargetRadius=   target->getMovingEntity().getRadius();
    
    // ������ͨ�����Ĺ�����Χ������ѽ綨����Ϊ����ÿһ���ƶ���ľ��벻ͬ������������һ����Χ����˫���İ뾶�йأ�����һ������
    auto tmpAttRectW    =   (tmpOwnerRadius + tmpTargetRadius + m_xOffset) * 2;
    auto tmpAttRectH    =   (tmpTargetRadius - m_yOffset) * 2;
    Rect tmpAttRect(tmpOwnerPos.x - tmpAttRectW / 2, tmpOwnerPos.y - tmpAttRectH / 2, tmpAttRectW, tmpAttRectH);

    return tmpAttRect.containsPoint(tmpTargetPos);
}

bool NormalCloseRangeWeapon::isReadyForNextAttack()
{
    return m_nextAttackReadyTime < TimeTool::getSecondTime();
}

bool NormalCloseRangeWeapon::isAttacking()
{
    return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
}

void NormalCloseRangeWeapon::onAttackEffect(string evt)
{
    // ���ܻ��߷���һ����Ϣ
    auto tmpMsg = TelegramNormalAttack::create(m_pOwner->getId(), m_targetId, m_pOwner->getAttribute());
    Dispatch->dispatchMessage(*tmpMsg);

    // ͬʱ�������Լ�������ֵ120
    m_pOwner->getAttribute().addEnergy(120);
}
