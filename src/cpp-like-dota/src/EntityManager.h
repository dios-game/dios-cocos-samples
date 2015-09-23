#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "BaseGameEntity.h"
#include "cocos2d.h"

/**
	ȫ�ֵ�����������Ϸ�д��ڵ�����ʵ�壬��Ϊ����
*/
class EntityManager
{
public:
    typedef std::map<int, BaseGameEntity*> EntityMap;

private:
    EntityMap* _entityMap;     // ȫ�ֵ�ʵ��id--->ʵ���ӳ��
    static EntityManager *_instance;

    EntityManager();
    ~EntityManager();
    EntityManager(const EntityManager&);
    EntityManager &operator=(const EntityManager&);

public:
    static EntityManager* instance();
    
    /**
    	 ע��һ��ʵ�壬��idΪ��
    */
    void registerEntity(BaseGameEntity *entity);

    /**
    	 ����ʵ��id���ض�Ӧ��ʵ��
    */
    BaseGameEntity* getEntityFromID(int id);

    /**
    	 �Ƴ�ĳ��ʵ��
    */
    void removeEntity(BaseGameEntity *entity);

    /**
    	 Ϊ�˷����ⲿ������ǰ���е�ʵ��
    */
    const EntityMap* getEntityMap();

    /**
    	 ����ʵ�壬Ҳ���ǽ����û������
    */
    CC_SYNTHESIZE(BaseGameEntity*, _mainEntity, mainEntity);
};

#define EntityMgr   EntityManager::instance()

#endif