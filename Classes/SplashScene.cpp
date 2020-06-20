
#include "SplashScene.h"

#include "StartScene.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }



    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Chomp.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Drip.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Error.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Ka-Ching.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Scrape.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/Mining by Moonlight.mp3");

    UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, 1);
    UserDefault::getInstance()->setBoolForKey(SOUND_KEY, 1);
    
    log("%f", CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)==1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/Mining by Moonlight.mp3");
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::GoToStartScene), DISPLAY_TIME_SPLASH_SCENE);
    auto backgroundSprite = Sprite::create("background_gamescene.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    auto creditLabel = Label::createWithTTF("GitHub @Xuwangzilu @zhangbaiyi", "fonts/Marker Felt.ttf", 30);
    creditLabel->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
    this->addChild(creditLabel);


    return true;
}


void SplashScene::GoToStartScene(float dt)
{
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
