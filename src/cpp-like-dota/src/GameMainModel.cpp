#include "GameMainModel.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "ProjectileManager.h"
#include "TimeTool.h"
#include "GameCharacter.h"
#include "WeaponControlSystem.h"
#include "WeaponChoiceAI.h"

GameMainModel::GameMainModel()
{
    // 开始循环
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameMainModel::update, this), 
        this, GAMEMAINMODEL_LOOP_INTERVAL, false, GAMEMAINMODEL_SCHEDULE_KEY);
}

GameMainModel::~GameMainModel()
{

}

void GameMainModel::moveToLeft()
{
    if (EntityMgr->getmainEntity() != nullptr)
    {
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_MOVE_LEFT, 0));
    }
    
    CCLOG("moveToLeft");
}

void GameMainModel::moveToRight()
{
    if (EntityMgr->getmainEntity() != nullptr)
    {
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_MOVE_RIGHT, 0));
    }
    
    CCLOG("moveToRight");
}

void GameMainModel::idle()
{
/**
    if (EntityMgr->getmainEntity() != nullptr)
    {
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_IDLE, 0));
    }

    CCLOG("idle");
*/
}

void GameMainModel::changeTarget()
{
    if (EntityMgr->getmainEntity() != nullptr)
    {
        // 告诉主角切换目标
        EntityMgr->getmainEntity()->handleMessage(*Telegram::create(0, 0, TELEGRAM_ENUM_USER_CHANGE_TARGET, 0));
    }
}

void GameMainModel::useSkill1()
{
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity());
    if (tmpCharacter != nullptr)
    {
        tmpCharacter->getWeaponControlSystem()->getWeaponChoiceAI()->userOrder(SPIRIT_SNOWSTORM_SKILL_WEAPON);
    }
}

void GameMainModel::useSkill2()
{
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity());
    if (tmpCharacter != nullptr)
    {
        tmpCharacter->getWeaponControlSystem()->getWeaponChoiceAI()->userOrder(SPIRIT_FREEZE_SKILL_WEAPON);
    }
}

void GameMainModel::update(float dm)
{
    // 这里是游戏逻辑更新的最上面的，所有游戏逻辑的时间都来自于此
    // dm  *=  2;

    // 时间
    TimeTool::update(dm);

    // 队伍逻辑更新
    TeamMgr->update(dm);

    // 飞行中的“子弹”更新
    ProjectileMgr->update(dm);

    // 直接在这里面加上如果
}

void GameMainModel::setMainGameCharacter(GameCharacter* character)
{
    EntityMgr->setmainEntity(character);

    // 同时显示主角光环
    character->getShape()->showHeroHalo();
}
