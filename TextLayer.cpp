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
		// �T�E���h�m�x����������`�揈�����s��
		if (!isEnd_) {
			// �{�^�������҂��t���O�������Ă����ꍇ�̓{�^�����������܂ł����ŏI��
			if (isWaitingForKey_) {
				if (DxLib::ProcessMessage() == 0 && DxLib::CheckHitKeyAll() != 0) {
					// �{�^����������Ă��������
					isWaitingForKey_ = false;
				}
			}
			else {
				// �����̕`��
				char moji = data_[row_][col_];
				switch (moji)
				{
				case '\\':  // ���䕶��
					moji = data_[row_][++col_]; // 1�����i�߂�
					switch (moji) {
					case 'N':	// ���s����
						// ���s��������юQ�ƕ����ʒu����i�߂�
						lineBreak();
						col_++;
						break;

					case 'B':	// �{�^�������҂�����
						isWaitingForKey_ = true;
						col_++;
						break;

					case 'E':	// �I������
						// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
						isEnd_ = true;
						col_++;
						break;

					case 'C':	// �N���A����
						// ���z�e�L�X�g�o�b�t�@�����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
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

				default: // �ʏ핶��
					int bytes = DxLib::GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &data_[row_][col_]);
					debug_printf("bytes[%d]\n", bytes);
					// �P�����e�L�X�g�o�b�t�@�ɑ��
					char debugStr[3] = { 0 };
					for (int i = 0; i < bytes; i++) {
						debugStr[i] = data_[row_][col_ + i];
						stringBuf_[cursorY_][cursorX_ + i] = data_[row_][col_ + i];
					}
					debug_printf("str[%s]\n", debugStr);
					col_ += bytes;  // �Q�ƕ����ʒu���ꕶ�����i�߂�
					cursorX_ += bytes;  // �J�[�\�����ꕶ�����i�߂�
					// �e�L�X�g�o�b�t�@��������͂ݏo������s����
					if (bytes != 1) {  // ���Y�������S�p�̏ꍇ
						if (cursorX_ >= STRBUF_WIDTH - 1) {  // -1�ɂ��Ă���͍̂s���ɔ��p���������Ă����ꍇ���l��
							debug_printf("kaigyo\n");
							lineBreak();
						}
					}
					else {  // ���p�̏ꍇ
						if (cursorX_ >= STRBUF_WIDTH) {
							debug_printf("kaigyo\n");
							lineBreak();
						}
					}
					break;
				}
				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (data_[row_][col_] == '\0') {
					row_++;
					col_ = 0;
				}
			}
		}
	}

	void TextLayer::draw() {
		// �o�b�t�@�͂��̎��̃��[�v�̃^�C�~���O�Ŋi�[����Ă���Ƃ���܂łł���B��{�I��2��̃��[�v��1�����ł���B
		for (int i = 0; i < STRBUF_HEIGHT; i++) {
			DxLib::DrawString(MARGIN_LEFT, i * FONT_SIZE, stringBuf_[i], GetColor(255, 255, 255));
		}
	}

	void TextLayer::lineBreak() {  // ���s�֐�
		cursorY_++;  // �`��s�ʒu���������
		cursorX_ = 0;  // �`�����ŏ��ɖ߂�
		// �����e�L�X�g�o�b�t�@�c������͂ݏo��Ȃ�e�L�X�g�o�b�t�@���c�X�N���[��������
		if (cursorY_ >= STRBUF_HEIGHT) {
			for (int i = 1; i < STRBUF_HEIGHT; i++) {
				for (int j = 0; j < STRBUF_WIDTH; j++) {
					stringBuf_[i - 1][j] = stringBuf_[i][j];
				}
			}
			cursorY_--;  // �`��s�ʒu���������
		}
	}
}