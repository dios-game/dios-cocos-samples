#ifndef __REFRESH_UI_EVENT_ENUM_H__
#define __REFRESH_UI_EVENT_ENUM_H__

/**
* ����Ҫ��ˢ�½�����¼���ö��ֵ��ÿ����ͼ���Ӧһ������¼����ڷ�����Щ�¼���ʱ���
* ȥ���ý����ˢ���¼����պ���
*/
enum RefreshUIEventEnum
{
    REFRESH_UI_EVENT_CHARACTER,                      // ����ɫ���ݷ����仯��ʱ��

    REFRESH_UI_SKILL1_USABLE,                        // ����ˢ���������ܰ�ť���Ƿ���Ե��
    REFRESH_UI_SKILL1_UNUSABLE,

    REFRESH_UI_SKILL2_COOLING,                       // ����2��ȴ����Ϣ��ˢ�µ�ǰ��ȴ����ʾ
};

#endif