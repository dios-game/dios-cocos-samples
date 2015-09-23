#ifndef __GAME_MAIN_MODEL_H__
#define __GAME_MAIN_MODEL_H__

#include "InputManager.h"
#include "GameCharacter.h"

#define GAMEMAINMODEL_SCHEDULE_KEY  "GAMEMAINMODEL_SCHEDULE_KEY"

// �Լ������߼�ѭ�����
#define GAMEMAINMODEL_LOOP_INTERVAL 0

/**
	 ��Ϸ����ģ�ͣ���ģ�͵��û���������û���һЩ��������
*/
class GameMainModel : public InputManagerDelegate
{
public:
    GameMainModel();
    ~GameMainModel();
    /**
    	 �������������ƶ��Ĳ���
    */
    virtual void moveToLeft() override;          // ����
    virtual void moveToRight() override;         // ����
    virtual void idle() override;                // ������
    virtual void changeTarget() override;        // ѡ��Ŀ��

    virtual void useSkill1() override;
    virtual void useSkill2() override;

    /**
    	 ������������Ϸ��ɫ�������ɫ���յ���ҿ���
    */
    void setMainGameCharacter(GameCharacter* character);

private:
    void update(float dm);                      // ��Ϸ���߼��ĸ���     
};

#endif