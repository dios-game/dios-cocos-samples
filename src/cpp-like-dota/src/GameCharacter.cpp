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
    	 临时就创建一种角色，这里是将组成一个游戏角色的部分拼接在一起
    */
    auto tmpRet = new GameCharacter();
    tmpRet->autorelease();

    /**
        Fuck主要是以后会有多种人物，这里吧，暂时就这样搞
        在此处拼装状态机、外形等
    */
    tmpRet->m_characterId   =   id;
    switch (id)
    {
    case 1:                                                 // 对应的是宙斯
        {
            // 不同的角色有不同的外形
            tmpRet->m_shape         =   GameCharacterShape::create("zhousi");
            tmpRet->m_shape->retain();

            // 不同的角色有不同的初始属性
            tmpRet->m_attribute     =   GameCharacterAttribute(200, 10, 30);

            // 普通近距离攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // 重击
            tmpRet->getWeaponControlSystem()->addWeapon(new ZeusThumpSkillWeapon(tmpRet));
            // 飞锤攻击的普通远距离攻击
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, 
                PROJECTILE_TYPE_ZEUS_FLY_HAMMER, 600, "atk3"));

            // 宙斯特有的武器选择逻辑
            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponZeusChoiceAI(tmpRet));

            break;
        }

    case 2:                                                 // 精灵
        {
            tmpRet->m_shape         =   GameCharacterShape::create("xuejingling-qian");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(800, 70, 10);

            // 普通远程攻击，丢出去的是闪电球
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_GALAXO_BALL, 
                600));
            // 冰冻攻击，让敌人被冻住
            tmpRet->getWeaponControlSystem()->addWeapon(new SpiritFreezeSkillWeapon(tmpRet));
            // 暴风雪
            tmpRet->getWeaponControlSystem()->addWeapon(new SpiritSnowStormSkillWeapon(tmpRet));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponSpiritChoiceAI(tmpRet));

            break;
        }

    case 3:                                                 // 骑士
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Aer");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(900, 20, 50);

            // 普通近程攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // 骑士冰圈
            tmpRet->getWeaponControlSystem()->addWeapon(new AerCryosphereSkillWeapon(tmpRet));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponAerChoiceAI(tmpRet));

            break;
        }

    case 4:                                                 // 野猪怪
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Pig");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 10, 10);

            // 普通近程攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // 普通远距离攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_PIG_FLY_KNIFE, 
                600, "atk2"));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponPigNiuTheifChoiceAI(tmpRet));

            break;
        }

    case 5:                                                 // 牛人
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Niu");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 15, 10);

            // 普通近程攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // 普通远距离攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_NIU_FLY_SHIELD,
                600, "atk2"));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponPigNiuTheifChoiceAI(tmpRet));

            break;
        }

    case 6:                                                 // 刺客
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Theif");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(300, 30, 5);

            // 普通进程攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));
            // 普通远距离攻击能力
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_THEIF_FLY_DAGGER,
                500, "atk2"));

            tmpRet->getWeaponControlSystem()->setWeaponChoiceAI(new WeaponPigNiuTheifChoiceAI(tmpRet));

            break;
        }

    case 7:                                                 // 石头人
        {
            tmpRet->m_shape         =   GameCharacterShape::create("YSG");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(500, 30, 40);

            // 普通近程攻击能力
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

    // 武器控制系统
    m_weaponControlSystem           =   new WeaponControlSystem(this);

    // 角色的大脑
    m_brain                         =   new GoalCharacterThink(this);

    // 驱动力产生对象
    m_steeringBehaviors             =   new SteeringBehaviors(this);

    // 默认就打开几个驱动力
    m_steeringBehaviors->wallAvoidanceOn();
    m_steeringBehaviors->separationOn();

    // 角色状态机
    m_stateMachine                  =   CharacterStateMachine::create(this);
    m_stateMachine->retain();
    m_stateMachine->changeState(GameCharacterFreeState::create());
}

GameCharacter::~GameCharacter()
{
    // 将该角色的显示从显示列表中移除
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
    // 这里以hp归零作为死亡的标准，然后在一个统一的地方删除处于死亡状态的
    if (getAttribute().getHp() <= 0)
    {
        m_state =   dead;
    }

    // 如果当前角色是死亡的，就不用update了
    if (m_state == dead)
    {
        return;
    }

    // 状态机也更新一下
    m_stateMachine->update(dm);

    // 武器系统
    m_weaponControlSystem->regularUpdate(dm);

    // 如果当前角色处于dull，就不用继续了
    if (On(dull))
    {
        return;
    }

    // 思考一下
    m_brain->process();

    // 根据MovingEntity来调整Shape的坐标
    updateMovement(dm);

    // @_@ 额外的数字标签
    //m_shape->setPosNumber(m_movingEntity.getFormationPosId());

    // @_@ 额外的目标标签
    //m_shape->setCurrentGoal(m_brain->getGoalDescribe());
}

bool GameCharacter::handleMessage(Telegram& msg)
{
    // 交给状态机去处理
    m_stateMachine->handleMessage(msg);

    // 把消息交给该成员的脑袋
    if (m_brain->handleMessage(msg)) return true;

    /**
    *	这里主要处理一些非AI的消息 
    */
    switch (msg.type)
    {
    case TELEGRAM_ENUM_NORMAL_ATTACK:                       // 收到普通攻击后
        {
            // 普通攻击只扣血，同时还要飘字
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
                *	需要通知攻击者，自己死了 
                */
                auto tmpDeadMsg =   Telegram::create(this->getId(), tmpMsg->senderId, TELEGRAM_ENUM_BE_KILLED);
                Dispatch->dispatchMessage(*tmpDeadMsg);
            }
            m_shape->setHpRatio(m_attribute.getHp() / m_attribute.getFullHp());

            // 同时发出消息告知UI
            if (this == dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity()))
            {
                RefreshUIMsg    tmpMsg(REFRESH_UI_EVENT_CHARACTER, this);
                UIViewMgr->refreshView(tmpMsg);
            }

            return true;
        }

    case TELEGRAM_ENUM_BE_KILLED:                           // 收到目标被自己杀死的通知
        {
            // 哈哈，自己杀人了，给自己增加能量
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
    // 如果当前武器系统使得该角色无法移动
   if (!m_weaponControlSystem->canCharacterMove())
   {
       return;
   }
    /**
    *  @_@ 这里其实要计算驱动力、加速度、速度等，并更新MovingEntity中的
    *  信息
    */
    // 总的合力
    Vec2 tmpForce   =   m_steeringBehaviors->calculate();
    if (tmpForce.getLengthSq() < 5)
    {
        // 如果力过小，就直接把速度降为0
        const double BrakingRate = 0.1; 
        m_movingEntity.setVelocity(m_movingEntity.getVelocity() * BrakingRate);                                     
    }
    else
    {
        // 加速度
        Vec2 tmpAccel   =   tmpForce / m_movingEntity.getMass();
        // 改变当前速度
        m_movingEntity.setVelocity(m_movingEntity.getVelocity() + tmpAccel * dm);
    }

    // 调用移动的动画
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
    *	 在改变当前坐标前，使用包含牵引力的重新计算，这里主要就是因为
    */
    if (m_steeringBehaviors->getTraction() != Vec2::ZERO)
    {
        // 如果牵引力不为0，才需要计算一次
        Vec2 tmpRealForce   =   m_steeringBehaviors->calculateWithTraction();
        if (tmpRealForce.getLengthSq() < 5)
        {
            // 如果力过小，就直接把速度降为0
            const double BrakingRate = 0.1; 
            m_movingEntity.setRealVelocity(m_movingEntity.getRealVelocity() * BrakingRate);                                     
        }
        else
        {
            // 加速度
            Vec2 tmpAccel   =   tmpRealForce / m_movingEntity.getMass();
            // 改变当前速度
            m_movingEntity.setRealVelocity(m_movingEntity.getRealVelocity() + tmpAccel * dm);
        }
    }
    else
    {
        // 牵引力为0，期望速度和实际速度相同
        m_movingEntity.setRealVelocity(m_movingEntity.getVelocity());
    }

    // 改变当前坐标
    m_movingEntity.setPosition(m_movingEntity.getPosition() + m_movingEntity.getRealVelocity() * dm);
    m_shape->setPosition(m_movingEntity.getPosition());

    // @_@ 显示当前驱动力
    // m_shape->setForce(tmpForce);
}

bool GameCharacter::hasGoal()
{
    return m_brain->hasSubgoal();
}
