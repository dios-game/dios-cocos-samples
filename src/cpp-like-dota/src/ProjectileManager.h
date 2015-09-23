#ifndef __PROJECTILE_MANAGER_H__
#define __PROJECTILE_MANAGER_H__

#include "cocos2d.h"
#include "Projectile.h"

using namespace std;

/**
*	���ڷ����еġ��ӵ��������� 
*/
class ProjectileManager
{
public:
    static ProjectileManager* instance();

    void addProjectile(Projectile* aProjectile);

    void update(float dm);

private:
    ProjectileManager() {}
    ~ProjectileManager() {}

    // �Ƴ����п����Ƴ����ӵ�
    void removeAllCanRemoveProjectile();

    // �ж���û�г�����Ļ����
    bool isOutWindow(Projectile* aPorjectile);

    static ProjectileManager*   m_instance;

    typedef map<int, Projectile*> ProjectileMap;
    ProjectileMap               m_projectilesMap;          // ��ǰ���ڻ�Ծ���ӵ�
};

#define ProjectileMgr   ProjectileManager::instance()

#endif