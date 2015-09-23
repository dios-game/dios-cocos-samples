#ifndef __TORNADO_H__
#define __TORNADO_H__

#include "cocos2d.h"
#include "cocostudio/CCArmature.h"
#include "EntityManager.h"
#include "GameCharacter.h"
#include "GameMap.h"
#include "MessageDispatcher.h"

using namespace cocos2d;
using namespace cocostudio;

/**
*	龙卷风，当被丢在地图上后，会对一定半径内的敌方目标产生一个向中心的力量，同时
*   会对目标扣血
*/
class Tornado : public Node
{
public:
    virtual void onEnter() override
    {
        Node::onEnter();

        // 开始播放动画
        m_tornadoArmature->getAnimation()->play("atk1", -1, 0);

        // 开始在每一帧中回调
        this->scheduleUpdate();

        // @_@ 为了效率，不是每次都要找受影响的角色
        auto tmpOwnerEntityType  =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_ownerId))->getType();
        auto tmpCharacters = GamepMapSingleton->getCharactersInRadius(this->getPosition(), m_effectRadius);
        for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); tmpIterator++)
        {
            if (tmpOwnerEntityType != (*tmpIterator)->getType())
            {
                m_affectedCharactersId.push_back((*tmpIterator)->getId());
            }
        }
    }

    virtual void onExit() override
    {
        Node::onExit();

        // 退出的时候要记住将角色身上的牵引力设为（0，0）
        auto tmpCharacters  =   getAffectedCharacters();
        for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); tmpIterator++)
        {
            (*tmpIterator)->getSteeringBehaviros()->setTraction(Vec2::ZERO);
        }
    }

    virtual void update(float dm) override
    {
        if (m_tornadoArmature->getAnimation()->isComplete() || !isOwnerAlive())
        {
            // 当动画播完后就把自己删除掉
            this->removeFromParent();
        }
        else
        {
            /**
            *	 如果到了龙卷风的作用时间，就开始扣血，
            */ 
            if (m_timeCount >= m_effectInterval)
            {
                m_timeCount =   0;    
            }

            // 依次设置受影响的角色的牵引力
            auto tmpCharacters  =   getAffectedCharacters();
            for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); tmpIterator++)
            {
                (*tmpIterator)->getSteeringBehaviros()->setTraction(calculateTraction((*tmpIterator)->getShape()->getPosition()));
                if (m_timeCount == 0)
                {
                    // 在角色身上作用杀伤
                    effectLethality((*tmpIterator)->getId());
                }
            }

            m_timeCount +=  dm;
        }
    }

    /**
    *	创建一个由ownerId角色释放的龙卷风 
    */
    static Tornado* create(int ownerId)
    {
        auto pRet   =   new Tornado(ownerId);
        if (pRet != nullptr)
        {
            pRet->autorelease();
        }
        return pRet;
    }

protected:
    Tornado(int ownerId):m_effectRadius(120), m_effectInterval(0.4), m_lethality(10), m_traction(200)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/xuejingling_VFX.ExportJson");
        m_tornadoArmature   =   Armature::create("xuejingling_VFX");
        this->addChild(m_tornadoArmature);
        m_ownerId           =   ownerId;
        m_timeCount         =   0;
        auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_ownerId));
        m_ownerAtt          =   tmpCharacter->getAttribute();
        m_ownerAtt.setAttack(m_lethality);
    }

private:
    /**
    *	 释放者是否当前存活
    */ 
    bool isOwnerAlive()
    {
        auto tmpCharacter   =   
            dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_ownerId));
        return tmpCharacter != nullptr && tmpCharacter->isAlive();
    }

    /**
    *	返回在龙卷风影响范围内的会被影响的角色，只有敌方角色才会被影响，这里暂时为了
    *   效率，不是每次都会 从地图获取周围的角色
    */
    vector<GameCharacter*> getAffectedCharacters()
    {
        vector<GameCharacter*> tmpRetCharacters;
        for (auto tmpIterator = m_affectedCharactersId.begin(); tmpIterator != m_affectedCharactersId.end(); tmpIterator++)
        {
            auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(*tmpIterator));
            if (tmpCharacter != nullptr)
            {
                tmpRetCharacters.push_back(tmpCharacter);
            }
        }

        return tmpRetCharacters;
    }

    /**
    *	计算龙卷风产生的牵引力的大小，这个牵引力会随着
    */
    Vec2 calculateTraction(const Vec2& characterPos)
    {
        Vec2 tmpTraction    =   this->getPosition() - characterPos;
        tmpTraction.normalize();
        tmpTraction         *=  m_traction;
        return tmpTraction;
    }

    /**
    *	在角色身上作用杀伤力 
    */
    void effectLethality(int targetId)
    {
        /**
        *	这里就作为普通攻击攻击吧，只是攻击力采用这里记录的 
        */
        auto tmpMsg = TelegramNormalAttack::create(m_ownerId, targetId, m_ownerAtt);
        Dispatch->dispatchMessage(*tmpMsg);
    }

    int                     m_ownerId;                      // 龙卷风的拥有者id
    GameCharacterAttribute  m_ownerAtt;                     // 攻击者发动攻击的时候的属性
    float                   m_timeCount;                    // 统计时间的计数器
    Armature*               m_tornadoArmature;              // 龙卷风播放的动画
    vector<int>             m_affectedCharactersId;         // 受影响的角色的id

    const float             m_effectRadius;                 // 影响半径
    const float             m_effectInterval;               // 龙卷风造成杀伤的间隔时间
    const float             m_lethality;                    // 杀伤力@_@现在暂时不考虑杀伤力的计算问题
    const float             m_traction;                     // 牵引力大小
};

#endif