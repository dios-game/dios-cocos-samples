#ifndef __BATTLE_UI_H__
#define __BATTLE_UI_H__

#include "ui/CocosGUI.h"
#include "UIView.h"
#include "GameCharacter.h"
#include "InputManager.h"
#include "JoyStick.h"
#include "CircularProgress.h"

using namespace cocos2d;
using namespace ui;

/**
* ս��ʱ���UI���棬��Ҫ����һЩ������һЩ��Ϣ����ʾ��ͬʱ��Ҳ�̳У���Ϊ��Ϸ�������
*/
class BattleUI : public UIView, public InputManager
{
public:
    bool init() override;

    /**
    * �����¼��Ļص����� 
    */
    void onWee(RefreshUIMsg& msg) override;

    void update(float dm) override;

    CREATE_FUNC(BattleUI);

protected:
    BattleUI();

    void setWeeList() override;

    /**
    * ˢ��ս��UI�еĽ�ɫ���ݵ���ʾ 
    */
    void refreshCharacter(GameCharacter* character);

    /**
    * ˢ�µ�ǰ��Ϊ���ǹ���Ŀ��Ľ�ɫ 
    */
    void refreshTargetCharacter(GameCharacter* character);

    /**
    * �����ǽ��ܽ��水ť�ĵ���¼� 
    */
    void onClickChangeTargetBtn(Ref* target,Widget::TouchEventType type);
    void onClickConvergeBtn(Ref* target,Widget::TouchEventType type);
    void onClickSkillBtn(Ref* target,Widget::TouchEventType type);

private:
    /**
    *	 �������ϽǼ��ܰ�ť
    */
    void highLightSkillBtn();

    /**
    *	�����ϽǼ��ܰ�ť���� 
    */
    void dimSkillBtn();

    /**
    *	�����½ǵļ��ܰ�ť��ȴ�����٣�ratio��0~100 
    */
    void coolSkill2Btn(int ratio);

    LoadingBar*     m_leaderHpBar;                  // ����hp��
    ImageView*      m_leaderIcon;                   // ���ǵ�ͷ��

    LoadingBar*     m_enemyHpBar;                   // ��ǰ�������ڴ�ĵ��˵�hp
    ImageView*      m_enemyIcon;                    // ����ͷ��
    Node*           m_enemyPanel;                   // ������Ϣ�������ڵ�

    Button*         m_convergeBtn;                  // ���л����İ�ť
    CircularProgress*   m_circularProgress;         // Բ�ν�����

    Button*         m_changeTargetBtn;              // ������ǰ���ǵĹ���Ŀ��
    Button*         m_skillBtn;                     // ���ܰ�ť

    JoyStick*       m_jokStick;                     // ���ݱ�
};

#endif