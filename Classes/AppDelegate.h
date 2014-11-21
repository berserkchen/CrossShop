//****************************************
//CrossShop  Demo0.01
//QQ��896793747
//****************************************
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CrossApp.h"

/**
@brief    The CrossApp Application.

The reason for implement as private inheritance is to hide some interface call by CAApplication.
*/
class  AppDelegate : private CrossApp::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CAApplication and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_
