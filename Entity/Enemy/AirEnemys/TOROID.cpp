//----------------------------------------------------------------------------------------------------------------------------------------
//													トーロイド
// 
// 円盤の敵
// 1.プレイヤーが感知範囲に入るまで登場時に記憶したプレイヤーの位置に向かって進む
// 2.プレイヤーが感知範囲に入れば弾を発射して逆方向に逃げ出す
//----------------------------------------------------------------------------------------------------------------------------------------

#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION       = 5;
	constexpr int   DECELERATION_LINIT   = 5;
}


//========================================================================================
//					コンストラクタ
// 
// インスタンスが作られた時点でステータス、座標などの情報を取得する
//========================================================================================
TOROID::TOROID(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}
//========================================================================================
//								初期化
// 
// メンバ変数を全て初期化する
//========================================================================================
void TOROID::Init(){
	EnemyBase::Init();
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
int TOROID::Create( std::weak_ptr<IPlayer> player,int number)
{
	auto useplayer = player.lock();

	EnemyBase::StatusSetup(EnemyStatusData::TOROID);


	AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);

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
int TOROID::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							固有のアクション
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
//敵の種類によってかわる関数。
// 1.登場数フレームまではプレイヤーの位置を取得し続ける
// 2.固有のUpdateを行う
// 3.アクションパターン番号によって行動を変える
//========================================================================================
int TOROID::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	if(ownframecount < 5) TergetRadian(player->GetPosition());

	//被弾判定がtrueの場合
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	/*弾を撃つ前の動き*/
	if (actionpattern == 0)
	{
		return ActionPattern01(player->GetHitbox(), player->GetPosition());
	}

	if (actionpattern == 1) 
	{
		ActionPattern02();
	}
	if (actionpattern == 2) 
	{
		ActionPattern03();
	}
	return 0;
}
//========================================================================================
//								アクションパターン01
// 
// radian方向に向かって進む。
// プレイヤーのx方向の当たり判定のサイズ + 20 を感知範囲とする
//		感知範囲にプレイヤーが入ったら弾をうったらパターンを変更する
//========================================================================================
int TOROID::ActionPattern01(const Boxcollider& playerhitbox, const Vector2& playerpos)
{
	//出現時にプレイヤーがいた座標に向かって進む

		Enemy_Patterns(MovePatternID::TowardsTarget);		//行動パターン 0:自機に向かう

		/*Y軸の距離関係なくプレイヤーのの当たり判定とX軸が重なったら*/
		if (playerhitbox.left <= position.x  &&
			playerhitbox.right >= position.x &&
			playerpos.y > position.y) {		//自機とY軸が一致したとき


			actionpattern++;			//減速パターンへ移行する

			direction = position.x > playerpos.x ? -1 : 1;	//プレイヤーとの位置関係によって向きを再設定する

			if (status.type == 1) {
				return OnBulletShot;
			}
		}
	return 0;
}
//========================================================================================
//								アクションパターン02
// 
// 一定速度まで減速する。
// 速度が一定以下になったらパターン番号を繰り上げる
//========================================================================================
void TOROID::ActionPattern02()
{	//一定速度に落ちるまで減速する
	Enemy_Patterns(MovePatternID::TowardsTarget);		//行動パターン 0:自機に向かう

	status.speed -= 0.2f;					            //減速
	if (status.speed < 0.6)  actionpattern = 2; 		//速度が0.6を下回ったら逃走パターンに移行する
}
//========================================================================================
//								アクションパターン03
// 
// 逆方向に逃走する
//========================================================================================
void TOROID::ActionPattern03()
{
	//反対方向に向かって逃走する
	Enemy_Patterns(MovePatternID::EscapeX);		//行動パターン 5:加速度を加算しつつｘ軸方向に逃げる


}


