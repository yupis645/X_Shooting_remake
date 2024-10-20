#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "ResourceManager.h"

class SceneBase {
public:
    SceneBase() : init(true), state(0){}
    virtual ~SceneBase() = default; // 終了処理

    virtual int Init() {        // 初期化
        init = true; 
        state = 0;
        return 0; 
    };  
    virtual int Update() = 0;    // 更新処理
    virtual int Draw() = 0;      // 描画処理


protected:
    bool init;
    int state;
};


#endif // SCENEBASE_H