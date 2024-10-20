#ifndef TYPES_H
#define TYPES_H

#include "common.h"
//-----------------------------------------------------------------------------------------------------
//				複数の変数で構成されたデータ構造を宣言するファイル
// 
// 
//-----------------------------------------------------------------------------------------------------

//===========================================================
//         元のpngデータとスライスするための設定
// 
// widthとheightでスライスする四角を作る
// rowは横、coluwnは縦に何枚スライスするか決める
// スライスする枚数はrow * coluwnで算出できる
//===========================================================
struct UseTextureDataConfig
{
    const wchar_t* texturepath;     //pngのデータパス
    int width;                      //１枚のスライスに対する横の長さ
    int height;                     //１枚のスライスに対する縦の長さ
    int row;                        // 横方向に切り取る数
    int column;                     //縦方向に切り取る数
};

//===========================================================
// クラス内で enum class を宣言
//===========================================================
enum class TextureType {
    Title,
    Player,
    Bullet,
    Boss,
    BossSub,
    PlayerBomber,
    EnemyBomber,
    Map
};


//===========================================================
// マップチップの情報の配列と進行度を管理する
//===========================================================
struct MapStatus {
    std::array<int,MapConfig::MAP_H * MapConfig::MAP_W> data;
    int y;
};



#endif //TYPES_H