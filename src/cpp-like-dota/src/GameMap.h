#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
#include "GameCharacter.h"
#include "Wall2D.h"

using namespace cocos2d;
using namespace std;

class Projectile;

/**
	 游戏地图，此时不再使用网格，对于地图，只是一个四面有墙的矩形区域，地图作为
     全局单件存在
*/
class GameMap : public Layer
{
public:
    // 全局单件
    static GameMap* instance();

    // 返回地图上面的所有墙壁
    const vector<Wall2D>& getWalls() { return m_walls; }

    // 在地图上放置一个角色
    void placeGameCharacter(GameCharacter* player);

    // 在地图上添加子弹
    void addProjectile(Projectile* aProjectile);

    // 在玩家所在层添加一个子节点
    void addChildToPlayerLayer(Node* aChild);

    /**
    *	 返回在指定区域内的所有角色
    *   @_@ 目前使用效率不高的逻辑来处理，以后可能会对地图进行分块
    */ 
    vector<GameCharacter*> getCharactersInRadius(Vec2 aCenter, float aRadius);

protected:
    GameMap():MOUNTAIN_MOVE_SCALE(0.9f),SKY_MOVE_SCALE(0.15f),m_wallLBPos(0,0),
        m_wallRTPos(5120, 370), m_maxCameraRate(70){}
    ~GameMap();

    bool init () override;

    /**
    * 每一帧的回调 
    */
    void update(float) override;

    /**
    * 设置摄像机在初始位置移动了多少，这样来调整4个层的移动，每个层相对于此移动不同的距离，其中摄像机
    * 是跟着主角的
    */
    void cameraMove(float dm);

    static GameMap* m_instance;      // 全局单件

    /**
    * 构成地图的背景有4层，现在每一层都是由两幅图片拼成的
    */
    Node*       m_bg1;               // 人物所在的地面
    Node*       m_bg2;               // 背后的山
    Node*       m_bg3;               // 最后面的天空
    Node*       m_playerLayer;       // 放置角色的层

    vector<Wall2D> m_walls;          // 所有的墙壁

    /**
    * 为了形成分层，这里是人物移动的距离和其它层移动距离的比值 
    */
    const float MOUNTAIN_MOVE_SCALE;
    const float SKY_MOVE_SCALE;

    /**
    * 地图中墙壁的常量
    */
    const Vec2 m_wallLBPos;
    const Vec2 m_wallRTPos;

    /**
    *	摄像机的最大移动速度 
    */
    const float m_maxCameraRate;    // 摄像机的最大移动速度
};

#define GamepMapSingleton   GameMap::instance()

#endif