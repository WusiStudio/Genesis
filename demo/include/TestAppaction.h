#pragma once
#ifndef __TEST_APPACTION_H__
#define __TEST_APPACTION_H__

#include "Appaction.h"

using namespace engine;

class TestAppaction : public Appaction
{
public:
    static TestAppaction & Instance(void);

protected:

    CREATEFUNC(TestAppaction);
    
    //程序开始
    virtual void start(void);

    void onWindowSizeChange(const Size2 & window_size);

    //每一帧
    virtual void update(const float dt);

    virtual ~TestAppaction(void){};
private:
    TestAppaction(void){}

};


#endif //__TEST_APPACTION_H__