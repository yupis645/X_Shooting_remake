

#ifndef TESTINPUTMANAGER_H
#define TESTINPUTMANAGER_H
#include "IInputManager.h"
#include "Geometry.h"

class TestInputManager: public IInputManager {
	public:
		TestInputManager() : active(true), gamemode(0), pressFlags(0), triggerFlags(0), releaseFlags(0), toggleFlags(0), directionkeyaxis(Vector2::zero) {}
		~TestInputManager() {}

		int InputReception()override;
		void GetKeySetup() override;
		Vector2 Dirctionkeyinput(InputMode mode) override;
		Vector2 DirctionkeyinputAxis(float x_value, float y_value,float maxspeed) override;
		void left() override;
		void right() override;
		void up() override;
		void down() override;
		void select() override;
		void cancel() override;
		void shot() override;
		void bom() override;
		void pose() override;
		void esc() override;

		// 全てのフラグをクリア
		void ClearAll()override;

		// フラグを取得
		int GetFlags(InputMode mode) const override;

		// フラグの設定（ビットOR）
		void SetFlag(InputFlag flag, InputMode mode)override;

		// フラグの解除（ビットAND NOT）
		void ClearFlag(InputFlag flag, InputMode mode)override;

		// フラグのトグル（ビットXOR）
		void ToggleFlag(InputFlag flag)override;

		// フラグが設定されているか確認（ビットAND）
		bool IsFlagSet(InputFlag flag, InputMode mode) const;

		//ビット同士で比較し、同じビット列が立っているならtrue,ないならfalseを返す
		bool FlagsCompare(int a, int b, InputFlag flag);

		void InputFlagsControl(InputFlag flag, bool inputley);

		void InputPritf();

		void SetActive(bool ac)override { active = ac; }
		bool Active()const override { return active; }
		void SetGamemode(int mode)override { gamemode = mode; }
		int Gamemode() const override { return gamemode; }
		Vector2 GetAxis()const  override { return directionkeyaxis; };

private:
	bool active;
	int gamemode;
	int pressFlags = 0;       // キーが押されている間のフラグ
	int triggerFlags = 0;     // 押下の瞬間のフラグ
	int releaseFlags = 0;     // 離した瞬間のフラグ
	int toggleFlags = 0;      // トグル状態のフラグ
	Vector2 directionkeyaxis;
};


#endif // TESTINPUTMANAGER_H