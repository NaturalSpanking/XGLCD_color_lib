/*
 * fonts_GLCD.h
 *
 *  Created on: 26 ��� 2020 �.
 *      Author: Maksim Cherkasov
 *
 * ���������� �� �������� �������: http://we.easyelectronics.ru/lcd_gfx/shrifty-s-glcd-font-creator-na-kolenke.html
 * ���������: https://www.mikroe.com/glcd-font-creator
 * ��� ������� �������� �������� �������� 1040 - 1103
 *
 */

#ifndef FONTS_GLCD_H_
#define FONTS_GLCD_H_

typedef struct {
	const unsigned char FontWidth;		// ������ ������
	const unsigned char FontHeight;		// ������ ������
	const unsigned char isMono;			// ���� ������������� ������
	const unsigned char FirstChar;		// ������ �������� ������; ������ ' ', 32
	const unsigned char FirstCharRU;	// ������ ������� ������; ������ 'A', 0xC0
	const unsigned char *data_regular;	// ��������� �� ������ �������� ��������
	const unsigned char *data_ru;		// ��������� �� ������ ������� ��������
} FontGLCD_t;

// ��� ����������� ������ ������
#define CONSOLAS_9X16 		1
#define COURIER_NEW_16X26	1
#define RFM_SIGN_24X16		1
#define RFM_HEARTS_32X32	1
#define ISOCPEUR_19X35		1
#define COMIC_SANS_MS_20X24	1

#if CONSOLAS_9X16
extern const FontGLCD_t Consolas9x16;
#endif
#if COURIER_NEW_16X26
extern const FontGLCD_t Courier_New_Bold16x26;
#endif
#if RFM_SIGN_24X16
extern const FontGLCD_t RFM_sign24x16;
#endif
#if RFM_HEARTS_32X32
extern const FontGLCD_t RFM_hearts32x32;
#endif
#if ISOCPEUR_19X35
extern const FontGLCD_t ISOCPEUR19x35;
#endif
#if COMIC_SANS_MS_20X24
extern const FontGLCD_t Comic_Sans_MS20x24;
#endif

#endif /* FONTS_GLCD_H_ */
