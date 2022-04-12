/****************************************************************************
 * Copyright (c) 2021 @aismann; Peter Eismann, Germany; dreifrankensoft

 https://adxeproject.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef _BOX2D_TESTBED_H_
#define _BOX2D_TESTBED_H_

#include "cocos2d.h"
#include "box2d/box2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(Box2DTestBedTests);

class Test;
typedef Test* TestCreateFcn();

struct TestEntry
{
    const char* category;
    const char* name;
    TestCreateFcn* createFcn;
};

#define MAX_TESTS 256
extern TestEntry g_testEntries[MAX_TESTS];

int RegisterTest(const char* category, const char* name, TestCreateFcn* fcn);

class Box2DTestBed : public TestCase, cocos2d::Layer
{
public:
    static Box2DTestBed* createWithEntryID(int entryId);

    Box2DTestBed();
    virtual ~Box2DTestBed();

    void onEnter() override;
    void onExit() override;

    void onDrawImGui();

    void initPhysics();
    void update(float dt) override;

    void createResetButton();

    bool initWithEntryID(int entryId);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void onMouseScroll(cocos2d::Event* event);

    cocos2d::EventListenerTouchOneByOne* _touchListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;

    TestEntry* m_entry;
    Test* m_test;
    int m_entryID;

private:
    b2World* world;
    cocos2d::Texture2D* _spriteTexture;

    b2Vec2 pos;
    b2Vec2 oldPos;
    bool button[2];

    // Debug stuff
    cocos2d::DrawNode* debugDrawNode;
    cocos2d::extension::PhysicsDebugNodeBox2D g_debugDraw;
};

#endif
