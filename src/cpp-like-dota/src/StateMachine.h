#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "State.h"

/**
	 ״̬����ÿһ����Ϸʵ�嶼����һ��״̬����״̬������������Ϸʵ���״̬���¡�ת����
*/
template <class entity_type>
class StateMachine : public cocos2d::Ref
{
protected:
    entity_type *_owner;                        // ��״̬��������ʵ��
    State<entity_type>* _globalState;           // ȫ��״̬
    State<entity_type>* _currentState;          // ��ǰ��״̬
    State<entity_type>* _previousState;         // ֮ǰ��״̬��������ת��

protected:
    StateMachine(entity_type *owner)
    {
        _owner          =   owner;
        _currentState   =   nullptr;
        _globalState    =   nullptr;
        _previousState  =   nullptr;
    }

    ~StateMachine()
    {
        CC_SAFE_RELEASE_NULL(_currentState);
        CC_SAFE_RELEASE_NULL(_globalState);
        CC_SAFE_RELEASE_NULL(_previousState);
    }

public:
    State<entity_type>* getCurrentState()
    {
        return _currentState;
    }

    State<entity_type>* getPreState()
    {
        return _previousState;
    }

    /**
    	 ����
    */
    void update(float dm)
    {
        if (_globalState != nullptr)
        {
            _globalState->update(_owner, dm);
        }

        if (_currentState != nullptr)
        {
            _currentState->update(_owner, dm);
        }
    }

    /**
    	 ���ĵ�ǰ״̬
    */
    void changeState(State<entity_type> *state)
    {
        CC_SAFE_RELEASE_NULL(_previousState);

        if (_currentState != nullptr)
        {
            _currentState->onExit(_owner);
        }
        
        _previousState  =   _currentState;
        _currentState   =   state;

        _currentState->retain();
        _currentState->onEnter(_owner);
    }

    /**
    	 �л���֮ǰ��״̬
    */
    void reverseState()
    {
        if (_previousState == nullptr)
        {
            return;
        }

        _previousState->retain();
        changeState(_previousState);
    }

    /**
    	 ������Ϣ
    */
    bool handleMessage(Telegram& msg)
    {
        if (_currentState != nullptr && _currentState->onMessage(_owner, msg))
        {
            return true;
        }

        if (_globalState != nullptr && _globalState->onMessage(_owner, msg))
        {
            return true;
        }

        return false;
    }

    /**
    	
    */
    void setGlobalState(State<entity_type>* globalState)
    {
        if (_globalState != nullptr)
        {
            _globalState->onExit(_owner);
            CC_SAFE_RELEASE_NULL(_globalState);
        }
        if (globalState != nullptr)
        {
            _globalState    =   globalState;
            _globalState->retain();
        }
    }

    /**
    	 ʹ�øú���������״̬��
    */
    static StateMachine<entity_type> *create(entity_type *entity)
    {
        StateMachine<entity_type> *pRet = new StateMachine<entity_type>(entity);
        if (pRet != nullptr)
        {
            pRet->autorelease();
        }

        return pRet;
    }
};

#endif