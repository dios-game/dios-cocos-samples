#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameMap.h"
#include "PCInputManager.h"
#include "GameMainModel.h"

using namespace cocos2d;

/**
	 ��Ϸ������
*/
class GameScene : public Scene
{
private:
    GameScene():m_celebrateFrame(90)
    {
        
    }

public:
    bool init() override;

    CREATE_FUNC(GameScene);

protected:
    GameMap*    m_map;                  // ��ͼ

    InputManager* m_pcInputManager;     // ������������ģ���������
    InputManager* m_mobileInputManager; // ʹ���ֻ���Ļ��ʽ����

    GameMainModel*  m_mainModel;        // ��Ϸ���߼�����

    const int m_celebrateFrame;         // ������ף����֡
    int m_celebrateFrameCount;          // �����õ�
};

#endif