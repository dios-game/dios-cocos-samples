#ifndef __MOBILITY_CONTROL_SYSTEM_H__
#define __MOBILITY_CONTROL_SYSTEM_H__

#include "ControlSystem.h"

/**
* ��ɫ���ƶ�����ϵͳ��֮ǰ�ѽ�ɫ���ƶ�������״̬���У����ھ���ÿ����ɫӦ�������������Լ����ƶ� 
*/
class MobilityControlSystem : public ControlSystem
{
public:
    MobilityControlSystem(GameCharacter* owner, float updatePeriod = 0);

protected:
    void update(float dm) override;
};

#endif