﻿#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "AccontScene.h"
USING_NS_CC;


Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto StartItem = MenuItemImage::create(
		"StartNormal.png",
		"StartSelected.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this)
	);
	StartItem->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 6 + 50));
	auto SettingItem = MenuItemImage::create(
		"SettingNormal.png",
		"SettingSelect.png",
		CC_CALLBACK_1(HelloWorld::menuSettingCallback, this)
	);
	SettingItem->setPosition(Vec2(visibleSize.width / 6, visibleSize.height / 6 ));
	auto ExitItem = MenuItemImage::create(
		"ExitNormal.png",
		"ExitSelected.png",
		CC_CALLBACK_1(HelloWorld::menuExitCallback, this));

	if (ExitItem == nullptr ||
		ExitItem->getContentSize().width <= 0 ||
		ExitItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x =  visibleSize.width/6;
		float y =  visibleSize.height / 6 - 50;// ExitItem->getContentSize().height / 2;
		ExitItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(StartItem, SettingItem, ExitItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("background2.png");
	if (sprite == nullptr)
	{
		problemLoading("'background.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	return true;
}
//音效待处理
void HelloWorld::menuStartCallback(Ref* pSender)
{
	auto scene = AccontScene::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}
void HelloWorld::menuSettingCallback(Ref* pSender)
{
	auto scene = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	/*if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}*/
}
void HelloWorld::menuExitCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
	//SimpleAudioEngine::getInstance()->playEffect("filename");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
void HelloWorld::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");
}

/*void HelloWorld::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld onEnterTransitionDidFinish");
	//播放
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("filename.mp3", true);
	}
}

void HelloWorld::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
}

void HelloWorld::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("HelloWorld onExitTransitionDidStart");
}

void HelloWorld::cleanup()
{
	Layer::cleanup();
	log("HelloWorld cleanup");
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("filename.mp3");
}
*/