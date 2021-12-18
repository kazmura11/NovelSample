#pragma once
#include <vector>
#include <string>

namespace NovelSample {
	// ���z�e�L�X�g�o�b�t�@�̉��T�C�Y�c�T�C�Y
	constexpr int STRBUF_WIDTH = 48;
	constexpr int STRBUF_HEIGHT = 20;
	constexpr int MARGIN_TOP = 8;
	constexpr int MARGIN_LEFT = 16;
	constexpr int FONT_SIZE = 24;
	//constexpr int MAX_COL_NUM = 256;  // �����P�p
	constexpr char TextPath[256] = "./Script/novel.txt";

	class TextLayer {
	public:
		TextLayer();
		~TextLayer();
		void update();
		void draw();
	private:
		int cursorX_;  // ���z��ʏ�ł̕����\���J�[�\���̈ʒu
		int cursorY_;  // ���z��ʏ�ł̕����\���J�[�\���̈ʒu
		int row_;  // �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
		int col_;  // �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
		bool isEnd_;  // �I���t���O
		bool isWaitingForKey_;  // �{�^�������҂��t���O
		char stringBuf_[STRBUF_HEIGHT][STRBUF_WIDTH + 1];  // ���z�e�L�X�g�o�b�t�@
		void lineBreak();
		//char (*data_)[MAX_COL_NUM];  // �{���i�[�̈� *data��new����[][256]�ɂ���
		std::vector<std::string> data_;  // �኱�x���Ȃ邪��������������Ȃ̂ő吨�ɉe���Ȃ�
		// C++�̏ꍇ[]���Z�q�̃I�[�o�[���[�h���f���炵���̂Ń\�[�X�R�[�h�̉e�����قڂȂ�
		
		// �⑫�F���̂悤�ȍ\����z�肵�Ă���B���ۂɂ�./Script/novel.txt����ǂݍ���
		// ������ς����̂Ŏ��ۂɂ�std::vector<string>�����A�C���[�W�Ƃ��Ă͉��L�̂܂�
		//char data_[][MAX_COL_NUM] = {
		//	"�@�Q�[���v���O�������K�����邽�߂̈�Ԃ̋ߓ��͂Ƃɂ�����R�v���O������g��",
		//	"���Ƃł���B\\B\\N" ,
		//	"�@��۸��т̎Q�l���ɂ̓Q�[���̃v���O�����̕��@�Ȃ�ĉ���������Ă��Ȃ��A\\B",
		//	"�ϐ��A\\B�z��A\\B�֐��A\\B���[�v�A\\B��������c\\B����炷�ׂĂ̐����̓Q�[���ŉ��Ɏg����",
		//	"�Ȃ�Ăǂ��ɂ������Ă��Ȃ��A\\B���������Z���^���ނɂ����Ⴊ������x�ł���B\\B" ,
		//	"\\C�@�v���O�����͏K����芵���Ȃ̂Ńv���O������g�ނɓ������ď����ł��m����",
		//	"���Ό�͂�������͌@�艺���A�L���Ă����Ηǂ��킯�ŁA\\B�v���O�����̎Q�l����",
		//	"�ǂ�ł��ď����ł������o����悤�ȋC�������炻���łƂɂ����v���O����",
		//	"��ł��Ă݂邱�Ƃ��厖�ł���B\\E",
		//};
	};
}

