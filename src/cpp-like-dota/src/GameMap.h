#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
#include "GameCharacter.h"
#include "Wall2D.h"

using namespace cocos2d;
using namespace std;

class Projectile;

/**
	 ��Ϸ��ͼ����ʱ����ʹ�����񣬶��ڵ�ͼ��ֻ��һ��������ǽ�ľ������򣬵�ͼ��Ϊ
     ȫ�ֵ�������
*/
class GameMap : public Layer
{
public:
    // ȫ�ֵ���
    static GameMap* instance();

    // ���ص�ͼ���������ǽ��
    const vector<Wall2D>& getWalls() { return m_walls; }

    // �ڵ�ͼ�Ϸ���һ����ɫ
    void placeGameCharacter(GameCharacter* player);

    // �ڵ�ͼ������ӵ�
    void addProjectile(Projectile* aProjectile);

    // ��������ڲ����һ���ӽڵ�
    void addChildToPlayerLayer(Node* aChild);

    /**
    *	 ������ָ�������ڵ����н�ɫ
    *   @_@ Ŀǰʹ��Ч�ʲ��ߵ��߼��������Ժ���ܻ�Ե�ͼ���зֿ�
    */ 
    vector<GameCharacter*> getCharactersInRadius(Vec2 aCenter, float aRadius);

protected:
    GameMap():MOUNTAIN_MOVE_SCALE(0.9f),SKY_MOVE_SCALE(0.15f),m_wallLBPos(0,0),
        m_wallRTPos(5120, 370), m_maxCameraRate(70){}
    ~GameMap();

    bool init () override;

    /**
    * ÿһ֡�Ļص� 
    */
    void update(float) override;

    /**
    * ����������ڳ�ʼλ���ƶ��˶��٣�����������4������ƶ���ÿ��������ڴ��ƶ���ͬ�ľ��룬���������
    * �Ǹ������ǵ�
    */
    void cameraMove(float dm);

    static GameMap* m_instance;      // ȫ�ֵ���

    /**
    * ���ɵ�ͼ�ı�����4�㣬����ÿһ�㶼��������ͼƬƴ�ɵ�
    */
    Node*       m_bg1;               // �������ڵĵ���
    Node*       m_bg2;               // �����ɽ
    Node*       m_bg3;               // ���������
    Node*       m_playerLayer;       // ���ý�ɫ�Ĳ�

    vector<Wall2D> m_walls;          // ���е�ǽ��

    /**
    * Ϊ���γɷֲ㣬�����������ƶ��ľ�����������ƶ�����ı�ֵ 
    */
    const float MOUNTAIN_MOVE_SCALE;
    const float SKY_MOVE_SCALE;

    /**
    * ��ͼ��ǽ�ڵĳ���
    */
    const Vec2 m_wallLBPos;
    const Vec2 m_wallRTPos;

    /**
    *	�����������ƶ��ٶ� 
    */
    const float m_maxCameraRate;    // �����������ƶ��ٶ�
};

#define GamepMapSingleton   GameMap::instance()

#endif