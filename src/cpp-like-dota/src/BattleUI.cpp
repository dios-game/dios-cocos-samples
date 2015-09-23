#include "cocostudio/CCSGUIReader.h"
#include "BattleUI.h"
#include "UIViewIdEnum.h"
#include "EntityManager.h"

using namespace cocostudio;

bool BattleUI::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    // 加载界面部分
    auto tmpUIRoot = GUIReader::getInstance()->widgetFromJsonFile("battleui/battle_1.ExportJson");
    this->addChild(tmpUIRoot);

    // 获取对应的节点
    auto tmpRoot    =   tmpUIRoot->getChildByName("leaderhpbarbg");
    m_leaderHpBar   =   dynamic_cast<LoadingBar*>(tmpRoot->getChildByName("leaderhpbar"));
    tmpRoot         =   tmpUIRoot->getChildByName("leadericonbg");
    m_leaderIcon    =   dynamic_cast<ImageView*>(tmpRoot->getChildByName("leadericon"));

    m_enemyPanel    =   dynamic_cast<Node*>(tmpUIRoot->getChildByName("enemypanel"));
    tmpRoot         =   m_enemyPanel;
    tmpRoot         =   m_enemyPanel->getChildByName("enemyhpbarbg");
    m_enemyHpBar    =   dynamic_cast<LoadingBar*>(tmpRoot->getChildByName("enemyhpbar"));
    tmpRoot         =   m_enemyPanel->getChildByName("enemyiconbg");
    m_enemyIcon     =   dynamic_cast<ImageView*>(tmpRoot->getChildByName("enemyicon"));

    m_changeTargetBtn   =   dynamic_cast<Button*>(tmpUIRoot->getChildByName("changetargetbtn"));
    m_skillBtn          =   dynamic_cast<Button*>(tmpUIRoot->getChildByName("skillbtn"));
    m_convergeBtn       =   dynamic_cast<Button*>(tmpUIRoot->getChildByName("jihuobtn"));
    m_circularProgress  =   CircularProgress::create(38);
    m_circularProgress->setPosition(m_convergeBtn->getChildren().at(0)->getPosition());
    m_convergeBtn->addChild(m_circularProgress);

    // 在节点上绑定回调
    m_changeTargetBtn->addTouchEventListener(CC_CALLBACK_2(BattleUI::onClickChangeTargetBtn, this));
    m_convergeBtn->addTouchEventListener(CC_CALLBACK_2(BattleUI::onClickConvergeBtn, this));
    m_skillBtn->addTouchEventListener(CC_CALLBACK_2(BattleUI::onClickSkillBtn, this));

    // 操纵柄
    //m_jokStick    =   JoyStick::create(Sprite::create("battleui/000.png"), Sprite::create("battleui/001.png"));
    //m_jokStick->setPosition(140, 140);
    //tmpUIRoot->addChild(m_jokStick);
    // @_@ 这里开启每一帧回调
    //this->scheduleUpdate();

    return true;
}

BattleUI::BattleUI():UIView(UIVIEW_ID_BATTLE)
{

}

void BattleUI::onWee( RefreshUIMsg& msg )
{
    switch (msg.eventType)
    {
    case REFRESH_UI_EVENT_CHARACTER:
        {
            refreshCharacter((GameCharacter*)msg.extraInfo);
            break;
        }

    case REFRESH_UI_SKILL1_USABLE:              // 此时需要将最右边的按钮亮起来
        {
            highLightSkillBtn();
            break;
        }

    case REFRESH_UI_SKILL1_UNUSABLE:            // 将最右边的按钮暗下来
        {
            dimSkillBtn();
            break;
        }

    case REFRESH_UI_SKILL2_COOLING:             // 左边的按钮的冷却消息
        {
            coolSkill2Btn((int)msg.extraInfo);
            break;
        }

    default:
        break;
    }
}

void BattleUI::setWeeList()
{
    m_weeList.push_back(REFRESH_UI_EVENT_CHARACTER);
    m_weeList.push_back(REFRESH_UI_SKILL1_USABLE);
    m_weeList.push_back(REFRESH_UI_SKILL1_UNUSABLE);
    m_weeList.push_back(REFRESH_UI_SKILL2_COOLING);
}

void BattleUI::refreshCharacter( GameCharacter* character )
{
    if (character == EntityMgr->getmainEntity())
    {
        // 更新主角的UI
        auto tmpAttribute   =   character->getAttribute();
        m_leaderHpBar->setPercent(tmpAttribute.getHp() / tmpAttribute.getFullHp() * 100);
    }
}

void BattleUI::refreshTargetCharacter( GameCharacter* character )
{
    if (character == nullptr)
    {
        // 说明当前没有攻击目标
        m_enemyPanel->setVisible(false);
    }
    else
    {
        // 否则就显示该角色信息
        auto tmpAttribute   =   character->getAttribute();
        m_enemyPanel->setVisible(true);
        m_enemyHpBar->setPercent(tmpAttribute.getHp() / tmpAttribute.getFullHp() * 100);
    }
}

void BattleUI::update( float dm )
{
    // 判断操纵柄方向
    if (m_jokStick->getCtrlDirection().x > 10)
    {
        _delegate->moveToRight();
    }
    else if (m_jokStick->getCtrlDirection().x < -10)
    {
        _delegate->moveToLeft();
    }
    else
    {
        _delegate->idle();
    }
}

void BattleUI::onClickChangeTargetBtn( Ref* target,Widget::TouchEventType type )
{
    if (type == Widget::TouchEventType::ENDED)
    {
        // _delegate->changeTarget();
    }
}

void BattleUI::onClickConvergeBtn( Ref* target,Widget::TouchEventType type )
{
    if (type == Widget::TouchEventType::ENDED)
    {
        _delegate->useSkill2();
    }
}

void BattleUI::onClickSkillBtn( Ref* target,Widget::TouchEventType type )
{
    if (type == Widget::TouchEventType::ENDED)
    {
        _delegate->useSkill1();
    }
}

void BattleUI::highLightSkillBtn()
{
    // 右边的按钮
    auto tmpImage   =   m_skillBtn->getChildren().at(0);
    tmpImage->removeAllChildren();
    auto tmpHightImage  =   ImageView::create("battleui/hightlight1.png");
    tmpHightImage->setAnchorPoint(Vec2(0, 0));
    tmpImage->addChild(tmpHightImage);
    m_skillBtn->setEnabled(true);
}

void BattleUI::dimSkillBtn()
{
    // 右边的按钮
    auto tmpImage       =   m_skillBtn->getChildren().at(0);
    tmpImage->removeAllChildren();
    m_skillBtn->setEnabled(false);
}

void BattleUI::coolSkill2Btn( int ratio )
{
    m_circularProgress->setRatio(ratio);
}
