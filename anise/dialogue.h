#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "anise.h"
#include "memory.h"
#include "timer.h"
#include "input.h"
#include "video.h"
#include "animation.h"
#include "script_code.h"

using std::string;

#define FONT_HALF_WIDTH		8
#define FONT_HALF_HEIGHT	16
#define FONT_FULL_WIDTH		16
#define FONT_FULL_HEIGHT	16
#define FONT_MARGIN		2

#define FONT_FACTOR		0x20
#define FONT_PREDEFINED_FACTOR	0x80

#define WAIT_DURATION		1

class Dialogue {
private:
	Memory *memory;
	Timer *timer;
	Input *input;
	Video *video;
	Animation *animation;
	Option *option;

	const byte *font;
	int size;

	byte code_newline_first;
	byte code_newline_second;

	word previous_code;

	void initializeJisFont();
	void initializeJisHanFont();
	void initializeGameboxFont();

	void updatePosition();
	void breakNewLine();

public:
	Dialogue(Memory *memory, Timer *timer, Input *input, Video *video, Animation *animation, Option *option);
	~Dialogue();

	void putHalfWidthCharacters();
	void putStandardText();
	void putPredefinedText();
	void putFullWidthCharacter(byte first_code, byte second_code);

	void setPosition(word coord_xb, word coord_y);
	void setPosition();
	void getPosition(word *coord_xb, word *coord_y);

	void delay(word duration);
	void wait();
};

#endif
