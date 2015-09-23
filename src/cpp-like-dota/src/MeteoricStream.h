#ifndef __METEORIC_STREAM_H__
#define __METEORIC_STREAM_H__

#include "cocos2d.h"
#include "cocostudio/CCArmature.h"
#include "GameCharacter.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "GameMap.h"
#include "GameCharacterState.h"

using namespace cocos2d;
using namespace cocostudio;

/**
*	 陨石雨作为地图上的一个东西放置在地图上@_@
*/
class MeteoricStream : public Node
{
public:
    virtual void onEnter() override
    {
        Node::onEnter();

        m_meteoricArmature->getAnimation()->play("atk", -1, 0);

        this->scheduleUpdate();
    }

    virtual void update(float dm) override
    {
        if (m_meteoricArmature->getAnimation()->isComplete() || !isOwnerAlive())
        {
            this->removeFromParent();
        }
        else
        {
            if (m_timeCount >= m_effectInterval)
            {
                m_timeCount =   0;
            }

            if (m_timeCount == 0)
            {
                // 在范围内的角色身上作用一次
                auto tmpCharacters  =   getAffectedCharacters();
                for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); tmpIterator++)
                {
                    effectLethality(*tmpIterator);
                }
            }

            m_timeCount +=  dm;
        }
    }

    /**
    *	创建一个陨石雨 
    */
    static MeteoricStream* create(int ownerId)
    {
        auto pRet   =   new MeteoricStream(ownerId);
        if (pRet != nullptr)
        {
            pRet->autorelease();
        }
        return pRet;
    }

protected:
    MeteoricStream(int ownerId):m_effectInterval(0.4), m_effectRadius(300), m_lethality(14)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/YSG-VFX.ExportJson");
        m_meteoricArmature  =   Armature::create("YSG-VFX");
        this->addChild(m_meteoricArmature);
        m_ownerId           =   ownerId;
        m_timeCount         =   0;
        auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_ownerId));
        m_ownerAtt          =   tmpCharacter->getAttribute();
        m_ownerAtt.setAttack(m_lethality);
        m_ownerType         =   tmpCharacter->getType();
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
    *	返回在影响范围内的角色 
    */
    vector<GameCharacter*> getAffectedCharacters()
    {
        auto tmpCharacters  =   
            GamepMapSingleton->getCharactersInRadius(this->getPosition(), m_effectRadius);
        for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); )
        {
            if (m_ownerType == (*tmpIterator)->getType())
            {
                tmpIterator =   tmpCharacters.erase(tmpIterator);
            }
            else
            {
                tmpIterator++;
            }
        }
        return tmpCharacters;
    }

    /**
    *	在角色身上作用杀伤力 
    */
    void effectLethality(GameCharacter* target)
    {
        /**
        *	这里不是普通攻击，还需要让被攻击者进入受击状态
        *   @_@ 这里直接进行状态转换不太好，但暂时这样写吧
        */
        target->getFSM()->changeState(GameCharacterHitedState::create());

        /**
        *	这里就作为普通攻击攻击吧，只是攻击力采用这里记录的 
        */
        auto tmpMsg = TelegramNormalAttack::create(m_ownerId, target->getId(), m_ownerAtt);
        Dispatch->dispatchMessage(*tmpMsg);
    }

private:
    Armature*               m_meteoricArmature;         // 陨石动画
    GameCharacterAttribute  m_ownerAtt;                 // 攻击者发动攻击的时候的属性
    int                     m_ownerId;                  // 释放陨石的角色id
    GameEntityTypeEnum      m_ownerType;                // 
    float                   m_timeCount;                // 统计时间的计数器

    const float             m_effectInterval;           // 扣血的间隔时间
    const float             m_effectRadius;             // 影响半径
    const float             m_lethality;                // 杀伤力
};

#endif