#ifndef __PC_INPUT_MANAGER_H__
#define __PC_INPUT_MANAGER_H__

#include "InputManager.h"
#include "cocos2d.h"

using namespace cocos2d;

/**
	 PC������Ĺ���������Ϊ��ʹPC�˿���ͨ������������
*/
class PCInputManager : public InputManager
{
public:
    PCInputManager();
    ~PCInputManager();
    bool init();

private:
    EventListenerKeyboard *_keyBoardListener;

    // �������̵�
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* pEvent);

    // ÿһ֡�Ļص�
    void update(float dm);

    EventKeyboard::KeyCode  _currentKeyCode;                // ��ǰ�����µļ���KeyCode
};

#endif