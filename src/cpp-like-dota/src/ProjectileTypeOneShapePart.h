#ifndef __PROJECTILE_TYPE_ONE_SHAPE_H__
#define __PROJECTILE_TYPE_ONE_SHAPE_H__

#include "cocos2d.h"
#include "cocostudio/CCArmature.h"
#include "ProjectileShapePart.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

/**
*	 ���е��ߵ�һ�ֱ��֣�ֻ��һ���������ڷ��е�ʱ����Կ�ʼѭ�����Ż���
*    �����ţ�Ȼ����ײ�����ٲ���
*/
class ProjectileTypeOneShapePart : public ProjectileShapePart
{
public:
    /**
    *	 �����ļ����������ơ��������ơ��Ƿ��ڿ�ʼ�����ʱ��Ͳ��Ŷ�������ײ����ʱ�򲥷Ŷ���
    */
    ProjectileTypeOneShapePart(string armatureName, string actionName, bool playOnLaunch = false)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfo(m_shapeDir + armatureName + ".ExportJson");
        m_armature      =   Armature::create(armatureName);
        m_actionName    =   actionName;
        m_playOnLaunch  =   playOnLaunch;
        this->addChild(m_armature);
    }

    virtual void onLaunchStart() override
    {
        if (m_playOnLaunch)
        {
            m_armature->getAnimation()->play(m_actionName);
        }
    }

    virtual void onImpact() override
    {
        if (!m_playOnLaunch)
        {
            m_armature->getAnimation()->play(m_actionName, -1, 0);
        }
    }

    virtual bool canBeDestroy() override
    {
        return (!m_playOnLaunch && !m_armature->getAnimation()->isPlaying()) || 
            (m_playOnLaunch);
    }

protected:
    Armature*       m_armature;             // ��Ӧ�Ķ���
    string          m_actionName;           // ��������
    bool            m_playOnLaunch;         // �Ƿ��ڷ����ʱ�򲥷Ŷ���

    static string   m_shapeDir;             // ���е������ε�Ŀ¼
};

#endif