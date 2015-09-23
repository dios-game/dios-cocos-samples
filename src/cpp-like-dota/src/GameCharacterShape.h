#ifndef __GAME_CHARACTER_SHAPE_H__
#define __GAME_CHARACTER_SHAPE_H__

#include "cocos2d.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"
#include "ui/UILoadingBar.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
using namespace std;

/**
	 �����һЩ�����ڶ����ļ��е�����
*/
#define IDLE_ACTION             "idle"
#define RUN_ACTION              "run"
#define NORMAL_ATTACK_ACTION    "atk1"
#define WIN_ACTION              "win"

/**
	 ��Ϸ�е����н�ɫ�����Σ���Щ����ӵ���ʾ�б��е�
*/
class GameCharacterShape : public Sprite
{
public:

    typedef std::function<void (string)> ActionFrameEventCallback;

    /**
    * ���������ϸ��������ֵ���ʽ��ö�� 
    */
    enum FloatNumberTypeEnum
    {
        FLOAT_NUMBER_GREEN,                     // ��ɫ
        FLOAT_NUMBER_RED,                       // ��ɫ
        FLOAT_NUMBER_YELLOW                     // ��ɫ
    };

    /**
    	 ��ɫ����ģ���ס���չ̶���������ʽ��������ֻ��Ҫ���붯������
    */
    static GameCharacterShape* create(const std::string& armatureName);

    /**
    	 ���Ŷ�������Ҫ�ṩ�������ƣ����������ң��Ƿ�ѭ��
    */
    void playAction(const std::string& actionName, bool loop = true, ActionFrameEventCallback eventCallBack = nullptr);

    /**
    	 ��������
    */
    void faceToRight();
    void faceToLeft();

    bool init() override;

    /**
    	 �������������ײ�ľ���
    */
    Rect getCollisionRect();

    /**
    	 ���ظý�ɫ���������꣬��Ϊ����Զ�̵�λ�Ĺ���Ŀ��
    */
    Vec2 getCenterPos();

    /**
    *	���ظý�ɫ���������꣬�����Ǳ������� 
    */
    Vec2 getCenterPosLocation();

    /**
    * �����øý�ɫ���ϳ�������Ʈ����ʱ����õĽӿ� 
    */
    void floatNumber(int num, FloatNumberTypeEnum type);

    /**
    *	����HP��ʾ�ı��ʣ����ǻ�ʣ�ٷ�֮����hp
    *   0~1
    */
    void setHpRatio(float ratio);

    /**
    * ���ص�ǰ���ŵĶ��� 
    */
    string getCurrentAnimationName();

    /**
    *	���ᶯ���������ý�ɫ���ڵ�ǰ֡�������ڽⶳ֮ǰ�����еĶ����������󶼱���ֹ
    */
    void freezeAnimation()
    {
        m_freezed    =   true;
        // ��ͣ
        _armature->getAnimation()->pause();
    }

    /**
    *	�ⶳ������remain��ʾ�Ǽ���֮ǰ�Ķ����أ����ǻָ���idle����״̬
    */
    void unfreezeAnimation(bool remain = false)
    {
        m_freezed   =   false;
        if (remain)
        {
            _armature->getAnimation()->resume();
        }
        else
        {
            playAction(IDLE_ACTION);
        }
    }

    /**
    * ��ʱ�õ�һ�����������Ǵ���������һ�����֣������ڽ�ɫ����ʾ 
    */
    void setPosNumber(int posNum) 
    {
     /**
        char tmpStr[10];
        sprintf(tmpStr, "%d", posNum);
        m_posNumLabel->setString(tmpStr);
        m_posNumLabel->setScaleX(this->getScaleX());
        */
    }

    /**
    *	��ʾ��ǰ��ɫ��Ŀ�� 
    */
    void setCurrentGoal(string goalDescribe)
    {
    /**
        m_goalLabel->setString(goalDescribe);
        m_goalLabel->setScaleX(this->getScaleX());
    */
    }

    /**
    *	��ʾ��ɫ��ǰ������ 
    */
    void setForce(Vec2 aForce)
    {
    /**
        char tmpStr[20];
        sprintf(tmpStr, "(%d, %d)", (int)aForce.x, (int)aForce.y);
        m_forceLabel->setString(tmpStr);
        m_forceLabel->setScaleX(this->getScaleX());
    */
    }

    Size getContentSize() { return _armature->getContentSize(); }
    
    /**
    *	չʾ���ǹ⻷ 
    */
    void showHeroHalo();

protected:
    GameCharacterShape(const std::string& armatureName);

    /**
    	 ��������������֡�¼���ʱ���ص��ú���
    */
    void onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex);

    /**
    *  ������������ֹͣ������ʱ��Ļص�������ֻ�ð��Լ�ɾ����OK��
    */
    void onFloatNumberMoveOver(Node* pNode);

    /**
    	 �жϵ�ǰ�����Ƿ��Ѿ�����
    */
    bool isNotInAnimation();

    Armature* _armature;
    string _currentAnimationName;                   // ��ǰ���ŵĶ���������

    ActionFrameEventCallback   _frameEventCallBack;    // �����Ŷ�����ʱ��֡�¼��Ļص�����

    LoadingBar* m_hpBar;                            // ÿ����ɫͷ�ϵ�Ѫ��

    /**
    * һЩ����@_@������ڶ���ʱ��֮��� 
    */
    const float FLOATNUMBERDIRATION;                // �������ֶ���ʱ��
    const float FLOATNUMBERMOVEBYY;                 // �ƶ�����
    static const string SHAPEDIR;                   // ���ε�Ŀ¼

    /**
    * ��ʱֵ 
    */
    Label*      m_posNumLabel;                      // ���ֱ�ǩ
    Label*      m_goalLabel;                        // ��ɫ��ǰĿ��
    Label*      m_forceLabel;                       // �������ı�ǩ

    bool        m_freezed;                          // �Ƿ񶳽�ý�ɫ����
};

#endif