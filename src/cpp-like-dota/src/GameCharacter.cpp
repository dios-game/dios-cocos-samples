#include "GameCharacter.h"
#include "MessageDispatcher.h"
#include "UIViewManager.h"
#include "GoalCharacterThink.h"
#include "NormalCloseRangeWeapon.h"
#include "NormalLongRangeWeapon.h"
#include "TimeTool.h"
#include "GameCharacterState.h"

#include "WeaponZeusChoiceAI.h"
#include "WeaponSpiritChoiceAI.h"
#include "WeaponAerChoiceAI.h"
#include "WeaponPigNiuTheifChoiceAI.h"
#include "WeaponYSGChoiceAI.h"

#include "ZeusThumpSkillWeapon.h"
#include "SpiritFreezeSkillWeapon.h"
#include "SpiritSnowStormSkillWeapon.h"
#include "AerCryosphereSkillWeapon.h"
#include "YSGMeteoricStreamSkillWeapon.h"

GameCharacter* GameCharacter::create(int id)
{
    /**
    	 ��ʱ�ʹ���һ�ֽ�ɫ�������ǽ����һ����Ϸ��ɫ�Ĳ���ƴ����һ��
    */
    auto tmpRet = new GameCharacter();
    tmpRet->autorelease();

    /**
        Fuck��Ҫ���Ժ���ж����������ɣ���ʱ��������
        �ڴ˴�ƴװ״̬�������ε�
    */
    tmpRet->m_characterId   =   id;
    switch (id)
    {
    case 1:                                                 // ��Ӧ������˹
        {
            // ��ͬ�Ľ�ɫ�в�ͬ������
            tmpRet->m_shape         =   GameCharacterShape::create("zhousi");
            tmpRet->m_shape->retain();

            // ��ͬ�Ľ�ɫ�в�ͬ�ĳ�ʼ����
            tmpRet->m_attribute     =   GameCharacterAttribute(200, 10, 30);

            // ��ͨ�����빥������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // �ػ�
            tmpRet->getWeaponControlSystem()->addWeapon(new ZeusThumpSkillWeapon(tmpRet));
            // �ɴ���������ͨԶ���빥��
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, 
                PROJECTILE_TYPE_ZEUS_FLY_HAMMER, 600, "atk3"));

            // ��˹���е�����ѡ���߼�
            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponZeusChoiceAI(tmpRet));

            break;
        }

    case 2:                                                 // ����
        {
            tmpRet->m_shape         =   GameCharacterShape::create("xuejingling-qian");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(800, 70, 10);

            // ��ͨԶ�̹���������ȥ����������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_GALAXO_BALL, 
                600));
            // �����������õ��˱���ס
            tmpRet->getWeaponControlSystem()->addWeapon(new SpiritFreezeSkillWeapon(tmpRet));
            // ����ѩ
            tmpRet->getWeaponControlSystem()->addWeapon(new SpiritSnowStormSkillWeapon(tmpRet));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponSpiritChoiceAI(tmpRet));

            break;
        }

    case 3:                                                 // ��ʿ
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Aer");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(900, 20, 50);

            // ��ͨ���̹�������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // ��ʿ��Ȧ
            tmpRet->getWeaponControlSystem()->addWeapon(new AerCryosphereSkillWeapon(tmpRet));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponAerChoiceAI(tmpRet));

            break;
        }

    case 4:                                                 // Ұ���
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Pig");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 10, 10);

            // ��ͨ���̹�������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // ��ͨԶ���빥������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_PIG_FLY_KNIFE, 
                600, "atk2"));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponPigNiuTheifChoiceAI(tmpRet));

            break;
        }

    case 5:                                                 // ţ��
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Niu");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 15, 10);

            // ��ͨ���̹�������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // ��ͨԶ���빥������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_NIU_FLY_SHIELD,
                600, "atk2"));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponPigNiuTheifChoiceAI(tmpRet));

            break;
        }

    case 6:                                                 // �̿�
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Theif");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(300, 30, 5);

            // ��ͨ���̹�������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // ��ͨԶ���빥������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_THEIF_FLY_DAGGER,
                500, "atk2"));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponPigNiuTheifChoiceAI(tmpRet));

            break;
        }

    case 7:                                                 // ʯͷ��
        {
            tmpRet->m_shape         =   GameCharacterShape::create("YSG");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(500, 30, 40);

            // ��ͨ���̹�������
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            tmpRet->getWeaponControlSystem()->addWeapon(new YSGMeteoricStreamSkillWeapon(tmpRet));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponYSGChoiceAI(tmpRet));

            break;
        }

    default:
        break;
    }
    
    
    return tmpRet;
}

GameCharacter::GameCharacter()
{
    m_shape                         =   nullptr;
    m_team                          =   nullptr;
    m_state                         =   alive;

    // ��������ϵͳ
    m_weaponControlSystem           =   new WeaponControlSystem(this);

    // ��ɫ�Ĵ���
    m_brain                         =   new GoalCharacterThink(this);

    // ��������������
    m_steeringBehaviors             =   new SteeringBehaviors(this);

    // Ĭ�Ͼʹ򿪼���������
    m_steeringBehaviors->wallAvoidanceOn();
    m_steeringBehaviors->separationOn();

    // ��ɫ״̬��
    m_stateMachine                  =   CharacterStateMachine::create(this);
    m_stateMachine->retain();
    m_stateMachine->changeState(GameCharacterFreeState::create());
}

GameCharacter::~GameCharacter()
{
    // ���ý�ɫ����ʾ����ʾ�б����Ƴ�
    m_shape->removeFromParent();
    CC_SAFE_RELEASE_NULL(m_shape);

    CC_SAFE_DELETE(m_weaponControlSystem);
    m_weaponControlSystem   =   nullptr;

    CC_SAFE_DELETE(m_brain);
    m_brain                 =   nullptr;

    CC_SAFE_DELETE(m_steeringBehaviors);
    m_steeringBehaviors     =   nullptr;

    CC_SAFE_RELEASE_NULL(m_stateMachine);
}

void GameCharacter::update(float dm)
{
    // ������hp������Ϊ�����ı�׼��Ȼ����һ��ͳһ�ĵط�ɾ����������״̬��
    if (getAttribute().getHp() <= 0)
    {
        m_state =   dead;
    }

    // �����ǰ��ɫ�������ģ��Ͳ���update��
    if (m_state == dead)
    {
        return;
    }

    // ״̬��Ҳ����һ��
    m_stateMachine->update(dm);

    // ����ϵͳ
    m_weaponControlSystem->regularUpdate(dm);

    // �����ǰ��ɫ����dull���Ͳ��ü�����
    if (On(dull))
    {
        return;
    }

    // ˼��һ��
    m_brain->process();

    // ����MovingEntity������Shape������
    updateMovement(dm);

    // @_@ ��������ֱ�ǩ
    //m_shape->setPosNumber(m_movingEntity.getFormationPosId());

    // @_@ �����Ŀ���ǩ
    //m_shape->setCurrentGoal(m_brain->getGoalDescribe());
}

bool GameCharacter::handleMessage(Telegram& msg)
{
    // ����״̬��ȥ����
    m_stateMachine->handleMessage(msg);

    // ����Ϣ�����ó�Ա���Դ�
    if (m_brain->handleMessage(msg)) return true;

    /**
    *	������Ҫ����һЩ��AI����Ϣ 
    */
    switch (msg.type)
    {
    case TELEGRAM_ENUM_NORMAL_ATTACK:                       // �յ���ͨ������
        {
            // ��ͨ����ֻ��Ѫ��ͬʱ��ҪƮ��
            TelegramNormalAttack* tmpMsg    =   dynamic_cast<TelegramNormalAttack*>(&msg);
            auto tmpFrontHp                 =   m_attribute.getHp();
            m_attribute.sufferNormalAttack(tmpMsg->senderAtt);
            auto tmpHp                      =   tmpFrontHp - m_attribute.getHp();
            if (this->getType() == GAME_ENTITY_TYPE_PLAYER_CHARACTER)
            {
                m_shape->floatNumber(tmpHp, GameCharacterShape::FLOAT_NUMBER_YELLOW);
            }
            else if (this->getType() == GAME_ENTITY_TYPE_ENEMY_CHARACTER)
            {
                m_shape->floatNumber(tmpHp, GameCharacterShape::FLOAT_NUMBER_RED);
            }
            if (m_attribute.getHp() <= 0)
            {
                m_state =   dead;
                /**
                *	��Ҫ֪ͨ�����ߣ��Լ����� 
                */
                auto tmpDeadMsg =   Telegram::create(this->getId(), tmpMsg->senderId, TELEGRAM_ENUM_BE_KILLED);
                Dispatch->dispatchMessage(*tmpDeadMsg);
            }
            m_shape->setHpRatio(m_attribute.getHp() / m_attribute.getFullHp());

            // ͬʱ������Ϣ��֪UI
            if (this == dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity()))
            {
                RefreshUIMsg    tmpMsg(REFRESH_UI_EVENT_CHARACTER, this);
                UIViewMgr->refreshView(tmpMsg);
            }

            return true;
        }

    case TELEGRAM_ENUM_BE_KILLED:                           // �յ�Ŀ�걻�Լ�ɱ����֪ͨ
        {
            // �������Լ�ɱ���ˣ����Լ���������
            m_attribute.addEnergy(200);
        }

    default:
        break;
    }
    return false;
}

void GameCharacter::updateMovement(float dm)
{
    m_shape->setPosition(m_movingEntity.getPosition());
    // �����ǰ����ϵͳʹ�øý�ɫ�޷��ƶ�
   if (!m_weaponControlSystem->canCharacterMove())
   {
       return;
   }
    /**
    *  @_@ ������ʵҪ���������������ٶȡ��ٶȵȣ�������MovingEntity�е�
    *  ��Ϣ
    */
    // �ܵĺ���
    Vec2 tmpForce   =   m_steeringBehaviors->calculate();
    if (tmpForce.getLengthSq() < 5)
    {
        // �������С����ֱ�Ӱ��ٶȽ�Ϊ0
        const double BrakingRate = 0.1; 
        m_movingEntity.setVelocity(m_movingEntity.getVelocity() * BrakingRate);                                     
    }
    else
    {
        // ���ٶ�
        Vec2 tmpAccel   =   tmpForce / m_movingEntity.getMass();
        // �ı䵱ǰ�ٶ�
        m_movingEntity.setVelocity(m_movingEntity.getVelocity() + tmpAccel * dm);
    }

    // �����ƶ��Ķ���
    if (m_movingEntity.getSpeed() > 5)
    {
        if (m_movingEntity.getVelocity().x > 0)
        {
            m_shape->faceToRight();
        }
        else
        {
            m_shape->faceToLeft();
        }
        m_shape->playAction(RUN_ACTION);
    }
    else
    {
        m_shape->playAction(IDLE_ACTION);
    }

    /**
    *	 �ڸı䵱ǰ����ǰ��ʹ�ð���ǣ���������¼��㣬������Ҫ������Ϊ
    */
    if (m_steeringBehaviors->getTraction() != Vec2::ZERO)
    {
        // ���ǣ������Ϊ0������Ҫ����һ��
        Vec2 tmpRealForce   =   m_steeringBehaviors->calculateWithTraction();
        if (tmpRealForce.getLengthSq() < 5)
        {
            // �������С����ֱ�Ӱ��ٶȽ�Ϊ0
            const double BrakingRate = 0.1; 
            m_movingEntity.setRealVelocity(m_movingEntity.getRealVelocity() * BrakingRate);                                     
        }
        else
        {
            // ���ٶ�
            Vec2 tmpAccel   =   tmpRealForce / m_movingEntity.getMass();
            // �ı䵱ǰ�ٶ�
            m_movingEntity.setRealVelocity(m_movingEntity.getRealVelocity() + tmpAccel * dm);
        }
    }
    else
    {
        // ǣ����Ϊ0�������ٶȺ�ʵ���ٶ���ͬ
        m_movingEntity.setRealVelocity(m_movingEntity.getVelocity());
    }

    // �ı䵱ǰ����
    m_movingEntity.setPosition(m_movingEntity.getPosition() + m_movingEntity.getRealVelocity() * dm);
    m_shape->setPosition(m_movingEntity.getPosition());

    // @_@ ��ʾ��ǰ������
    // m_shape->setForce(tmpForce);
}

bool GameCharacter::hasGoal()
{
    return m_brain->hasSubgoal();
}
