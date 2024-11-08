
//----------------------------------------------------------------------------------------------------------------------------------------
//													ギドスパリオ
// 
// 破壊できる弾。青と赤で点滅している
// 動作は単純で画面出現時にプレイヤーの位置を取得し、その方向に向かって飛ぶだけ
//----------------------------------------------------------------------------------------------------------------------------------------


#include "AirEnemyBase.h"



#include "common.h"
#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;		//アニメーション画像を入れ替えるフレーム数
}


//========================================================================================
//					コンストラクタ
// 
// インスタンスが作られた時点でステータス、座標などの情報を取得する
//========================================================================================
GIDDOSPARIO::GIDDOSPARIO(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);		//インスタンス生成時に必要なステータスを設定する
}

//========================================================================================
//								初期化
// 
// メンバ変数を全て初期化する
//========================================================================================
void GIDDOSPARIO::Init() {
	EnemyBase::Init();		//メンバ変数を初期化する
}


//========================================================================================
//							生成(ステータスの取得など)
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 第２引数 : 敵の識別番号、及びタイプ。(100の位がタイプを表す [203 なら type 2、number 3となる])
// 
// インスタンス化に必要な情報を取得する
//	1.ステータスの初期値,設定値を取得する。
//	2.出現時の座標を設定する
//  3.activeやtypeなどEnemyBaseの変数で調整が必要なものを調整する
//========================================================================================
int GIDDOSPARIO::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();		//スマートポインタを一時shared_ptrに変換する

	//	1.ステータスの初期値,設定値を取得する。
	EnemyBase::StatusSetup(EnemyStatusData::GIDDOSPARIO);

	//	2.出現時の座標を設定する
	AirEnemyBase::InitPostionPattern();

	//  3.activeやtypeなどEnemyBaseの変数で調整が必要なものを調整する
	AirEnemyBase::Create(useplayer, number);

	return 0;
}


//========================================================================================
//							更新
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
// EnemyManagerに使ってもらうための関数
//  AirEnemyBase::Updateが固有のアクションを設定したUniqueUpdate関数を呼び出す。
//========================================================================================
int GIDDOSPARIO::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							固有のアクション
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
//敵の種類によってかわる関数。
// 1.アニメーションの更新
// 2.出現時にプレイヤーがいた座標に向かって進む
//========================================================================================
int GIDDOSPARIO::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

		// 1.アニメーションの更新
		AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

		// 2.出現時にプレイヤーがいた座標に向かって進む
		Enemy_Patterns(MovePatternID::TowardsTarget);


	return 0;
}
