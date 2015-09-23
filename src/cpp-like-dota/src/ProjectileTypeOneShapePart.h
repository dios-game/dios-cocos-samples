#ifndef __PROJECTILE_TYPE_ONE_SHAPE_H__
#define __PROJECTILE_TYPE_ONE_SHAPE_H__

#include "cocos2d.h"
#include "cocostudio/CCArmature.h"
#include "ProjectileShapePart.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

/**
*	 飞行道具的一种表现，只有一个动画，在飞行的时候可以开始循环播放或者
*    不播放，然后在撞击后再播放
*/
class ProjectileTypeOneShapePart : public ProjectileShapePart
{
public:
    /**
    *	 动画文件、动画名称、动作名称、是否在开始发射的时候就播放动画还是撞击的时候播放动画
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
    Armature*       m_armature;             // 对应的动画
    string          m_actionName;           // 动作名称
    bool            m_playOnLaunch;         // 是否在发射的时候播放动画

    static string   m_shapeDir;             // 飞行道具外形的目录
};

#endif