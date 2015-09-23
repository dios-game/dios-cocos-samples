#include "AppDelegate.h"
#include "GameScene.h"
#include "cocostudio/CCArmature.h"

USING_NS_CC;

#if CC_TARGET_PLATFORM==CC_PLATFORM_WIN32
static inline std::string ConvertPathFormatToUnixStyle(const std::string& path)
{
	std::string ret = path;
	int len = ret.length();
	for (int i = 0; i < len; ++i)
	{
		if (ret[i] == '\\')
		{
			ret[i] = '/';
		}
	}
	return ret;
}

static std::string GetCurrentDirectory()
{
	char current_directory[MAX_PATH];
	::GetCurrentDirectoryA(MAX_PATH, current_directory);
	return ConvertPathFormatToUnixStyle(std::string(current_directory) + "/");
}
static void SetDefaultDirectory(){
	FileUtils::getInstance()->setDefaultResourceRootPath(GetCurrentDirectory());
	{
		std::vector<std::string> searchPaths;
		searchPaths.push_back(GetCurrentDirectory());
		FileUtils::getInstance()->setSearchPaths(searchPaths);
	}
}
#endif //  CC_TARGET_PLATFORM==CC_PLATFORM_WIN32

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
#if CC_TARGET_PLATFORM==CC_PLATFORM_WIN32
	SetDefaultDirectory();
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("My Game");

        // 如果是windows版本就手动设置窗口大小，对于android版本不需要设置;
#ifdef WIN32
        glview->setFrameSize(1280, 800);
#endif
        director->setOpenGLView(glview);
    }

    // @_@ 难道cocos2d 3.x已经把自适应搞好了？？
    glview->setDesignResolutionSize(1280, 800, ResolutionPolicy::SHOW_ALL);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameScene::create();

    /**
    *	此处先把一些资源加载进来，以防止第一次使用的时候会卡; 
    */
    ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/xuejingling_VFX.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/YSG-VFX.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/Niu-wuqi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/Pig-wuqi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/Theif-wuqi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/xuejingling-texiao.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/zhousi-wuqi.ExportJson");

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
