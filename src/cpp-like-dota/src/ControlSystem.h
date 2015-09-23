#ifndef __CONTROL_SYSTEM_H__
#define __CONTROL_SYSTEM_H__

class GameCharacter;

/**
* ���վ�����һ����ɫ�����п��Ʋ��ַ��뵽ÿ������ϵͳ�У������ƶ�����ϵͳ���������ƶ���Ҫȥ�ĵط�
* ����Ŀ��ѡ��ϵͳ������ݻ���ѡ�񹥻�Ŀ�꣬���ϵͳ������ݵ�ǰ����ѡ����ʵĹ�����ʽ�������Ϊ����
* �齨������ÿ��GameCharacter�У�ÿ��GameCharacter���ڸ�����Щ���
*/
class ControlSystem
{
public:
    ControlSystem(GameCharacter* owner, float updatePeriod = 0);
    ~ControlSystem();

    /**
    * �ⲿÿ��GameCharacter��update��ʱ�򶼿��Ե���tryUpdate��������Ϊ��Щϵͳû��Ҫ������ôƵ��������
    * �����update���˿��ƣ���֤�����ε���update�����ʱ����
    */
    void tryUpdate();

protected:
   /**
    *  ���¿���ϵͳ���״̬
    */
    virtual void update(float dm) = 0;

    GameCharacter*  m_owner;                        // ��ϵͳ��������

private:
    float   m_updatePeriod;                         // ����update�����ʱ����
    float   m_lastUpdateTime;                       // ���һ�ε���update��ʱ�䣬��λ�Ǻ���
};

#endif