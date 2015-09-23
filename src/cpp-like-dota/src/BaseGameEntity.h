#ifndef __BASE_GAME_ENTITY_H__
#define __BASE_GAME_ENTITY_H__

#include "Telegram.h"

/**
	 ��Ϸʵ�����ͣ�����Ϸʵ����з���
*/
enum GameEntityTypeEnum
{
    GAME_ENTITY_TYPE_PLAYER_CHARACTER,                  // ��ҵĽ�ɫ
    GAME_ENTITY_TYPE_ENEMY_CHARACTER                    // ���˵Ľ�ɫ
};

#define INVALID_GAME_ENTITY_ID  -1

/**
	 ��Ϸ�����е�ʵ��Ļ���
*/
class BaseGameEntity : public cocos2d::Ref
{
private:
    int                 _id;               // ÿһ��ʵ�嶼��һ��Ψһ��id
    GameEntityTypeEnum  _type;

    static int m_nextValidId;           // ʵ���id���������ķ�ʽ����ÿһ��ʵ������Ψһ��id

protected:
    BaseGameEntity();
    virtual ~BaseGameEntity();

public:
    int getId();
    void setType(GameEntityTypeEnum type) {_type = type;};
    GameEntityTypeEnum getType() {return _type;};

    virtual void update(float dm) = 0;                      // ��ÿһ֡�б�����
    virtual bool handleMessage(Telegram& msg) = 0;          // ����ʵ�嶼���Դ�����Ϣ����
    virtual Sprite* getShape() {return nullptr;}
};

#endif