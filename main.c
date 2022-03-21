/*
 * main.c
 *
 *  Created on: 18 ���. 2022 �.
 *      Author: CaHuTaP
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "fonts_GLCD.h"

#define RUSSIAN_CHARSET 0xC0
#define SPACE 2

typedef struct {
	uint16_t height;
	uint16_t width;
	void* data;
} TBitmapText;

typedef enum _TColor {
	clBlack = 0x0000, clWhite = 0xFFFF
} TColor;

TBitmapText MakeTextBitmap(const char *text, const FontGLCD_t* font,
		TColor text_color, TColor bg_color, uint8_t extra_space);

void PrintAndFree(TBitmapText bmp);

int main() {
	TBitmapText bmp;
	bmp = MakeTextBitmap("ABCDE", &Consolas9x16, clBlack, clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("ABCDE", &Courier_New_Bold16x26, clBlack, clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("ABCDE", &ISOCPEUR19x35, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("ABCDEFGH 123wesq", &Consolas9x16, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("ABCDEFGH 123wesq", &Courier_New_Bold16x26, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("ABCDEFGH 123wesq", &ISOCPEUR19x35, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("������� test 123", &Consolas9x16, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("������� test 123", &Courier_New_Bold16x26, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("������� test 123", &ISOCPEUR19x35, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("�������-���������� ������!", &Consolas9x16, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("�������-���������� ������!", &Courier_New_Bold16x26, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("�������-���������� ������!", &ISOCPEUR19x35, clBlack,clWhite,SPACE);
	PrintAndFree(bmp);
	bmp = MakeTextBitmap("�������-���������� ������!", &Comic_Sans_MS20x24, clBlack,clWhite,SPACE);
		PrintAndFree(bmp);
//	bmp = draw_text(" ", &RFM_hearts32x32, clWhite,clBlack);

	return 0;
}

TBitmapText MakeTextBitmap(const char *text, const FontGLCD_t* font, TColor color,
		TColor bg_color, uint8_t extra_space) {
	TBitmapText ret;

	int bytes_per_column = font->FontHeight / 8 // ��� ���������� ���� �� ������� ����������� � ���������� ������
			+ (font->FontHeight % 8 ? 1 : 0); // ���������� ���� �� 1 ������� �������
	int bytes_per_char = font->FontWidth * bytes_per_column + 1; // ���������� ���� �� ������
	int char_index;							// ������ ������� � ������� ������
	const uint8_t* chars_table;				// ������� ��������, � ������ �� ���
	ret.height = font->FontHeight;
	ret.width = 0;
	for (int i = 0; text[i]; i++) { // ������ �� ������ � ���������� ������ �������
		if ((uint8_t)text[i] >= RUSSIAN_CHARSET) {		//�������� �����
				chars_table = font->data_ru;
				char_index = ((uint8_t)text[i] - RUSSIAN_CHARSET) * bytes_per_char;// ������ ������� � ������� �������
			} else {
				chars_table = font->data_regular;
				char_index = ((uint8_t)text[i] - font->TableOffset) * bytes_per_char;	// ������ ������� � ������� �������
			}
		ret.width += (font->isMono ?font->FontWidth+extra_space :chars_table[char_index] + extra_space);
	}
	/*
	 * ��������� ����������� ������ �� ��������, ������ ��� �������� � ���� ������ ���������� � ������� ������ ������ ��� ���,
	 * uint8_t **buf = malloc(buf_size + sizeof(uint8_t*)* ret.height); // ����� �������
	 * for(int i = 0; i<ret.height;i++){
	 *	buf[i] = (uint8_t*)buf +ret.height+ i*ret.width;
	 *	}
	 *	*(*(buf+i)+j) = 0xAC; ���������� buf[i][j] =
	 *
	 * */
	uint16_t *buf = malloc(ret.height * ret.width * sizeof(uint16_t)); // ��������� ������ ��� �������

	for (int i = 0; i < ret.height; i++) {
		for (int j = 0; j < ret.width; j++) {
			buf[i * ret.width + j] = 0xAC35; // �������� ������ �� ����
		}
	}

	ret.data = buf;
	int stolb_idx = 0;
	for (int simv = 0; text[simv]; simv++) { // ������ �� ��������
		if ((uint8_t)text[simv] >= 0xC0) {		//�������� �����
						chars_table = font->data_ru;
						char_index = ((uint8_t)text[simv] - 0xC0) * bytes_per_char;// ������ ������� � ������� �������
					} else {
						chars_table = font->data_regular;
						char_index = ((uint8_t)text[simv] - font->TableOffset) * bytes_per_char;	// ������ ������� � ������� �������
					}
		int col_index = char_index + 1; // ������ ������� ������� ������� � ������� ������, �������� bytes_per_column
		int char_width = font->isMono ?	font->FontWidth : chars_table[char_index];
		for (int stolb = 0;	stolb < char_width; stolb++) { // ������ �� ��������
			for (int bait = 0; bait < bytes_per_column; bait++) { // ������ �� ������ �������
				int x = chars_table[col_index + bait]; // ����, ������� ����� ������ ����������
				int bit_count = font->FontHeight - bait * 8 >= 8 ? 8 : font->FontHeight % 8; // ���-�� ������������ ���
				for (int bit = 0; bit < bit_count; bit++) {	// ������ �� �����
					uint32_t buf_idx = 	bit * ret.width +
										bait * 8 * ret.width +
										stolb_idx +
										stolb;
					buf[buf_idx] = (x & 0b1) ? color : bg_color;
					x >>= 1;
				}
			}
			col_index += bytes_per_column;
		}
		stolb_idx += char_width;
		for (int stolb = 0; stolb < extra_space; stolb++) {// �������������� ������������ ����� ���������
					for (int stroka = 0; stroka < font->FontHeight; stroka++) { // ������ �� ������ �������
							uint32_t buf_idx =	stroka * ret.width +
												stolb_idx +
												stolb;
							buf[buf_idx] = bg_color;	//0xad;
					}
				}
		stolb_idx += extra_space;
	}
	return ret;
}

void PrintAndFree(TBitmapText bmp){
	printf("H = %d, W = %d\n\n", bmp.height, bmp.width); // fixme ������������ ����

		int idx = 0;
		for (int i = 0; i < bmp.height; i++) {
			for (int j = 0; j < bmp.width; j++) {
				//printf("%c", (((uint16_t*) bmp.data)[idx]==clBlack) ? ' ' : '0');
				switch (((uint16_t*) bmp.data)[idx]) {
				case clBlack:
					printf("%c", '0');
					break;
				case clWhite:
					printf("%c", ' ');
					break;
				default: // ����� �� ����
					printf("%c", '-');
				}
				idx++;
				if (idx % 10 == 0)
					fflush(stdout);
			}
			printf("\n");
			fflush(stdout);
		}
		printf("\n");
		free(bmp.data);
}
