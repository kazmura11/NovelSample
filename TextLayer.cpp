#include "TextLayer.h"
#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define debug_printf printf
#else
#define debug_printf /* DELETE */
#endif

namespace NovelSample {
	TextLayer::TextLayer()
		: cursorX_(0), cursorY_(0), row_(0), col_(0), isEnd_(false), isWaitingForKey_(false),
		stringBuf_{ 0 } {
		DxLib::SetFontSize(FONT_SIZE);
		std::ifstream filein(TextPath);
		if (filein.fail()) {
			std::cerr << "failed" << std::endl;
			exit(-1);
		}
		char temp[MAX_COL_NUM] = { 0 };
		int rowCount = 0;
		while (filein.getline(temp, MAX_COL_NUM - 1)) {
			rowCount++;
		}
		filein.clear();
		filein.seekg(0);
		data_ = new char[rowCount][MAX_COL_NUM];
		rowCount = 0;
		while (filein.getline(temp, MAX_COL_NUM - 1)) {
			strcpy(data_[rowCount], temp);
			rowCount++;
		}
	}
	TextLayer::~TextLayer() {
		delete[] data_;
	}

	void TextLayer::update() {
		// サウンドノベル風文字列描画処理を行う
		if (!isEnd_) {
			// ボタン押し待ちフラグがたっていた場合はボタンが押されるまでここで終了
			if (isWaitingForKey_) {
				if (DxLib::ProcessMessage() == 0 && DxLib::CheckHitKeyAll() != 0) {
					// ボタンが押されていたら解除
					isWaitingForKey_ = false;
				}
			}
			else {
				// 文字の描画
				char moji = data_[row_][col_];
				switch (moji)
				{
				case '\\':  // 制御文字
					moji = data_[row_][++col_]; // 1文字進める
					switch (moji) {
					case 'N':	// 改行文字
						// 改行処理および参照文字位置を一つ進める
						lineBreak();
						col_++;
						break;

					case 'B':	// ボタン押し待ち文字
						isWaitingForKey_ = true;
						col_++;
						break;

					case 'E':	// 終了文字
						// 終了フラグを立てるおよび参照文字位置を一つ進める
						isEnd_ = true;
						col_++;
						break;

					case 'C':	// クリア文字
						// 仮想テキストバッファを初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
						for (int i = 0; i < STRBUF_HEIGHT; i++) {
							for (int j = 0; j < STRBUF_WIDTH + 1; j++) {
								stringBuf_[i][j] = 0;
							}
						}
						cursorY_ = 0;
						cursorX_ = 0;
						col_++;
						break;
					}
					break;

				default: // 通常文字
					int bytes = DxLib::GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &data_[row_][col_]);
					debug_printf("bytes[%d]\n", bytes);
					// １文字テキストバッファに代入
					char debugStr[3] = { 0 };
					for (int i = 0; i < bytes; i++) {
						debugStr[i] = data_[row_][col_ + i];
						stringBuf_[cursorY_][cursorX_ + i] = data_[row_][col_ + i];
					}
					debug_printf("str[%s]\n", debugStr);
					col_ += bytes;  // 参照文字位置を一文字分進める
					cursorX_ += bytes;  // カーソルを一文字分進める
					// テキストバッファ横幅からはみ出たら改行する
					if (bytes != 1) {  // 当該文字が全角の場合
						if (cursorX_ >= STRBUF_WIDTH - 1) {  // -1にしているのは行中に半角が混じっていた場合を考慮
							debug_printf("kaigyo\n");
							lineBreak();
						}
					}
					else {  // 半角の場合
						if (cursorX_ >= STRBUF_WIDTH) {
							debug_printf("kaigyo\n");
							lineBreak();
						}
					}
					break;
				}
				// 参照文字列の終端まで行っていたら参照文字列を進める
				if (data_[row_][col_] == '\0') {
					row_++;
					col_ = 0;
				}
			}
		}
	}

	void TextLayer::draw() {
		// バッファはその時のループのタイミングで格納されているところまでである。基本的に2回のループで1文字である。
		for (int i = 0; i < STRBUF_HEIGHT; i++) {
			DxLib::DrawString(MARGIN_LEFT, i * FONT_SIZE, stringBuf_[i], GetColor(255, 255, 255));
		}
	}

	void TextLayer::lineBreak() {  // 改行関数
		cursorY_++;  // 描画行位置を一つ下げる
		cursorX_ = 0;  // 描画列を最初に戻す
		// もしテキストバッファ縦幅からはみ出るならテキストバッファを縦スクロールさせる
		if (cursorY_ >= STRBUF_HEIGHT) {
			for (int i = 1; i < STRBUF_HEIGHT; i++) {
				for (int j = 0; j < STRBUF_WIDTH; j++) {
					stringBuf_[i - 1][j] = stringBuf_[i][j];
				}
			}
			cursorY_--;  // 描画行位置を一つあげる
		}
	}
}