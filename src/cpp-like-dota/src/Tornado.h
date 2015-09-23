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
*	����磬�������ڵ�ͼ�Ϻ󣬻��һ���뾶�ڵĵз�Ŀ�����һ�������ĵ�������ͬʱ
*   ���Ŀ���Ѫ
*/
class Tornado : public Node
{
public:
    virtual void onEnter() override
    {
        Node::onEnter();

        // ��ʼ���Ŷ���
        m_tornadoArmature->getAnimation()->play("atk1", -1, 0);

        // ��ʼ��ÿһ֡�лص�
        this->scheduleUpdate();

        // @_@ Ϊ��Ч�ʣ�����ÿ�ζ�Ҫ����Ӱ��Ľ�ɫ
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

        // �˳���ʱ��Ҫ��ס����ɫ���ϵ�ǣ������Ϊ��0��0��
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
            // �����������Ͱ��Լ�ɾ����
            this->removeFromParent();
        }
        else
        {
            /**
            *	 �����������������ʱ�䣬�Ϳ�ʼ��Ѫ��
            */ 
            if (m_timeCount >= m_effectInterval)
            {
                m_timeCount =   0;    
            }

            // ����������Ӱ��Ľ�ɫ��ǣ����
            auto tmpCharacters  =   getAffectedCharacters();
            for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); tmpIterator++)
            {
                (*tmpIterator)->getSteeringBehaviros()->setTraction(calculateTraction((*tmpIterator)->getShape()->getPosition()));
                if (m_timeCount == 0)
                {
                    // �ڽ�ɫ��������ɱ��
                    effectLethality((*tmpIterator)->getId());
                }
            }

            m_timeCount +=  dm;
        }
    }

    /**
    *	����һ����ownerId��ɫ�ͷŵ������ 
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
    *	 �ͷ����Ƿ�ǰ���
    */ 
    bool isOwnerAlive()
    {
        auto tmpCharacter   =   
            dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_ownerId));
        return tmpCharacter != nullptr && tmpCharacter->isAlive();
    }

    /**
    *	�����������Ӱ�췶Χ�ڵĻᱻӰ��Ľ�ɫ��ֻ�ез���ɫ�ŻᱻӰ�죬������ʱΪ��
    *   Ч�ʣ�����ÿ�ζ��� �ӵ�ͼ��ȡ��Χ�Ľ�ɫ
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
    *	��������������ǣ�����Ĵ�С�����ǣ����������
    */
    Vec2 calculateTraction(const Vec2& characterPos)
    {
        Vec2 tmpTraction    =   this->getPosition() - characterPos;
        tmpTraction.normalize();
        tmpTraction         *=  m_traction;
        return tmpTraction;
    }

    /**
    *	�ڽ�ɫ��������ɱ���� 
    */
    void effectLethality(int targetId)
    {
        /**
        *	�������Ϊ��ͨ���������ɣ�ֻ�ǹ��������������¼�� 
        */
        auto tmpMsg = TelegramNormalAttack::create(m_ownerId, targetId, m_ownerAtt);
        Dispatch->dispatchMessage(*tmpMsg);
    }

    int                     m_ownerId;                      // ������ӵ����id
    GameCharacterAttribute  m_ownerAtt;                     // �����߷���������ʱ�������
    float                   m_timeCount;                    // ͳ��ʱ��ļ�����
    Armature*               m_tornadoArmature;              // ����粥�ŵĶ���
    vector<int>             m_affectedCharactersId;         // ��Ӱ��Ľ�ɫ��id

    const float             m_effectRadius;                 // Ӱ��뾶
    const float             m_effectInterval;               // ��������ɱ�˵ļ��ʱ��
    const float             m_lethality;                    // ɱ����@_@������ʱ������ɱ�����ļ�������
    const float             m_traction;                     // ǣ������С
};

#endif