#include "GameCharacterShape.h"

const string GameCharacterShape::SHAPEDIR   =   "shape/";

GameCharacterShape::GameCharacterShape(const std::string& armatureName):
    FLOATNUMBERDIRATION(0.3f), FLOATNUMBERMOVEBYY(50)
{
    string tmpFileName  =   SHAPEDIR + armatureName;
    ArmatureDataManager::getInstance()->addArmatureFileInfo(tmpFileName + ".ExportJson");
    _armature = Armature::create(armatureName);
    _currentAnimationName = "";
    m_hpBar     =   nullptr;
    m_freezed    =   false;
    
    // @_@ ��������Ϊ����ÿ����Դ�����⣬��������ĳ���ͬ��ֻ�ü�������߼�
    if (armatureName == "xuejingling-qian" || armatureName == "Aer" || armatureName == "Theif" 
        || armatureName == "YSG")
    {
        _armature->setScaleX(-1);
    }
}

GameCharacterShape* GameCharacterShape::create(const std::string& armatureName)
{
    auto pRet   =   new GameCharacterShape(armatureName);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }

    return nullptr;
}

void GameCharacterShape::playAction(const std::string& actionName, bool loop, ActionFrameEventCallback eventCallBack)
{
    // ����Ѿ����ᣬ�Ͳ������κβ��Ŷ�������Ϊ
    if (m_freezed)
    {
        return;
    }

    // @_@ ��Ҫ���һ���Ƿ���ָ������
    std::vector<std::string> tmpNames = _armature->getAnimation()->getAnimationData()->movementNames;
    for (int i = 0; i < tmpNames.size(); i++)
    {
        if (tmpNames[i] == actionName)
        {
            if (isNotInAnimation() || _currentAnimationName != actionName)
            {
                _armature->getAnimation()->play(actionName, -1, loop ? 9999999 : 0); 
                _currentAnimationName = actionName;
                _frameEventCallBack = eventCallBack;

                // ����֡�¼��Ļص�����
                _armature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(GameCharacterShape::onFrameEvent));
            }
            
            return;
        }
    }

    // ���û�ж������Բ��ţ��Ͳ���һ��һ�����ڵĶ���idle
    playAction(IDLE_ACTION);
}

bool GameCharacterShape::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // ��Ӷ���
    this->addChild(_armature, 2);

    // ���Ѫ��
    auto tmpHpBarBg =   Sprite::create("character/barbg.png");
    tmpHpBarBg->setScale(0.5);
    m_hpBar =   LoadingBar::create("character/hpbar.png", 100);
    m_hpBar->setAnchorPoint(Vec2(0, 0));
    m_hpBar->setPosition(Vec2(3.5, 2));
    tmpHpBarBg->addChild(m_hpBar);
    tmpHpBarBg->setAnchorPoint(Vec2(0.5, 0));
    tmpHpBarBg->setPosition(Vec2(0, _armature->getContentSize().height));
    this->addChild(tmpHpBarBg);

/**
    // @_@ ���ӱ�ǩ
    m_posNumLabel = Label::createWithBMFont("font/greennumber.fnt", "-1");
    m_posNumLabel->setPositionY(this->getCenterPos().y);
    this->addChild(m_posNumLabel, 4);

    // @_@ ��ǰĿ��ı�ǩ
    m_goalLabel =   Label::createWithSystemFont("Hello World","Arial", 25);
    m_goalLabel->setColor(Color3B(255, 0, 0));
    m_goalLabel->setPositionY(this->getCenterPos().y + 50);
    this->addChild(m_goalLabel, 5);

    // @_@ �������ı�ǩ
    m_forceLabel =  Label::create("������","Arial", 25);
    m_forceLabel->setColor(Color3B(0, 255, 0));
    m_forceLabel->setPositionY(this->getCenterPos().y - 50);
    this->addChild(m_forceLabel, 5);
*/
    return true;
}

void GameCharacterShape::faceToRight()
{
    this->setScaleX(1);
}

void GameCharacterShape::faceToLeft()
{
    this->setScaleX(-1);
}

bool GameCharacterShape::isNotInAnimation()
{
    return !_armature->getAnimation()->isPlaying();
}

Rect GameCharacterShape::getCollisionRect()
{
    Rect tmpRect    =   _armature->getBoundingBox();
    Size tmpSize    =   tmpRect.size;
    tmpSize.width   -=  80;
    
    // ���ظýڵ��ڸ��ڵ��ϵ�����
    auto tmpPoint   =   this->getPosition();
    tmpRect.setRect(tmpPoint.x - tmpSize.width / 2, tmpPoint.y, tmpSize.width, tmpSize.height);
    return tmpRect;
}

void GameCharacterShape::onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex)
{
    if (_frameEventCallBack != nullptr)
    {
        _frameEventCallBack(evt);
    }
}

Vec2 GameCharacterShape::getCenterPos()
{
    auto tmpRect    =   this->getCollisionRect();
    auto tmpPos     =   Vec2(tmpRect.getMidX(), tmpRect.getMidY());
    return tmpPos;
}

void GameCharacterShape::floatNumber(int num, GameCharacterShape::FloatNumberTypeEnum type )
{
    char numStr[10];
    sprintf(numStr, "-%d", num);
    // ѡ��ʹ�õ�������ʽ
    auto tmpFntSrc  =   "";
    switch (type)
    {
    case GameCharacterShape::FLOAT_NUMBER_GREEN:
        tmpFntSrc   =   "font/greennumber.fnt";
        break;
    case GameCharacterShape::FLOAT_NUMBER_RED:
        tmpFntSrc   =   "font/rednumber.fnt";
        break;
    case GameCharacterShape::FLOAT_NUMBER_YELLOW:
        tmpFntSrc   =   "font/yellownumber.fnt";
        break;
    default:
        break;
    }

    // ������ǩ
    auto tmpText    =   Label::createWithBMFont(tmpFntSrc, numStr);
    tmpText->setPositionY(_armature->getContentSize().height / 2);
    this->addChild(tmpText, 4);
    tmpText->setScaleX(this->getScaleX());

    // �󶨸����Ķ��������Ŷ���
    auto tmpMoveBy  =   MoveBy::create(FLOATNUMBERDIRATION, Vec2(0, FLOATNUMBERMOVEBYY));
    tmpText->runAction(Sequence::create(tmpMoveBy, CallFuncN::create(std::bind(&GameCharacterShape::onFloatNumberMoveOver, this, std::placeholders::_1)), nullptr));
}

void GameCharacterShape::onFloatNumberMoveOver( Node* pNode )
{
    pNode->removeFromParentAndCleanup(true);
}

void GameCharacterShape::setHpRatio( float ratio )
{
    m_hpBar->setPercent(ratio * 100);
}

std::string GameCharacterShape::getCurrentAnimationName()
{
    // �����ǰû���ڲ��Ŷ������ͷ��ؿյ��ַ���
    if (isNotInAnimation())
    {
        return "";
    }
    return _currentAnimationName;
}

cocos2d::Vec2 GameCharacterShape::getCenterPosLocation()
{
    return getCenterPos() - this->getPosition();
}

void GameCharacterShape::showHeroHalo()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("halo/greenhalo.ExportJson");
    auto tmpHalo    =   Armature::create("greenhalo");
    this->addChild(tmpHalo);
    tmpHalo->getAnimation()->play("Animation1");
}
