#pragma once
namespace NovelSample {
	// 仮想テキストバッファの横サイズ縦サイズ
	constexpr int STRBUF_WIDTH = 48;
	constexpr int STRBUF_HEIGHT = 20;
	constexpr int MARGIN_LEFT = 8;
	constexpr int FONT_SIZE = 24;
	constexpr int MAX_COL_NUM = 256;
	constexpr char TextPath[256] = "./Script/novel.txt";

	class TextLayer {
	public:
		TextLayer();
		~TextLayer();
		void update();
		void draw();
	private:
		int cursorX_;  // 仮想画面上での文字表示カーソルの位置
		int cursorY_;  // 仮想画面上での文字表示カーソルの位置
		int row_;  // 参照する文字列番号と文字列中の文字ポインタ
		int col_;  // 参照する文字列番号と文字列中の文字ポインタ
		bool isEnd_;  // 終了フラグ
		bool isWaitingForKey_;  // ボタン押し待ちフラグ
		char stringBuf_[STRBUF_HEIGHT][STRBUF_WIDTH + 1];  // 仮想テキストバッファ
		void lineBreak();
		char (*data_)[MAX_COL_NUM];  // 本文格納領域 *dataをnewして[][256]にする
		/*
		// 補足：次のような構造を想定している。実際には./Script/novel.txtから読み込む
		char data_[][MAX_COL_NUM] = {
			"　ゲームプログラムを習得するための一番の近道はとにかく沢山プログラムを組む",
			"ことである。\\B\\N" ,
			"　ﾌﾟﾛｸﾞﾗﾑの参考書にはゲームのプログラムの方法なんて何も書かれていない、\\B",
			"変数、\\B配列、\\B関数、\\Bループ、\\B条件分岐…\\Bこれらすべての説明はゲームで何に使うか",
			"なんてどこにも書いていない、\\Bせいぜい住所録を題材にした例がある程度である。\\B" ,
			"\\C　プログラムは習うより慣れろなのでプログラムを組むに当たって少しでも知識が",
			"つけば後はそこからは掘り下げ、広げていけば良いわけで、\\Bプログラムの参考書を",
			"読んでいて少しでも何か出来るような気がしたらそこでとにかくプログラム",
			"を打ってみることが大事である。\\E",
		};
		*/
	};
}

