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
*	 ��ʯ����Ϊ��ͼ�ϵ�һ�����������ڵ�ͼ��@_@
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
                // �ڷ�Χ�ڵĽ�ɫ��������һ��
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
    *	����һ����ʯ�� 
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
    *	 �ͷ����Ƿ�ǰ���
    */ 
    bool isOwnerAlive()
    {
        auto tmpCharacter   =   
            dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_ownerId));
        return tmpCharacter != nullptr && tmpCharacter->isAlive();
    }

    /**
    *	������Ӱ�췶Χ�ڵĽ�ɫ 
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
    *	�ڽ�ɫ��������ɱ���� 
    */
    void effectLethality(GameCharacter* target)
    {
        /**
        *	���ﲻ����ͨ����������Ҫ�ñ������߽����ܻ�״̬
        *   @_@ ����ֱ�ӽ���״̬ת����̫�ã�����ʱ����д��
        */
        target->getFSM()->changeState(GameCharacterHitedState::create());

        /**
        *	�������Ϊ��ͨ���������ɣ�ֻ�ǹ��������������¼�� 
        */
        auto tmpMsg = TelegramNormalAttack::create(m_ownerId, target->getId(), m_ownerAtt);
        Dispatch->dispatchMessage(*tmpMsg);
    }

private:
    Armature*               m_meteoricArmature;         // ��ʯ����
    GameCharacterAttribute  m_ownerAtt;                 // �����߷���������ʱ�������
    int                     m_ownerId;                  // �ͷ���ʯ�Ľ�ɫid
    GameEntityTypeEnum      m_ownerType;                // 
    float                   m_timeCount;                // ͳ��ʱ��ļ�����

    const float             m_effectInterval;           // ��Ѫ�ļ��ʱ��
    const float             m_effectRadius;             // Ӱ��뾶
    const float             m_lethality;                // ɱ����
};

#endif