#include "drivers/keyboard/keycodes.h"
#include "drivers/keyboard/ps2.h"
#include "sys/io/io.h"
#include <stdint.h>

int shift_down = 0;
int caps = 0;

uint8_t kybrd_ctrl_read_status() {
	return inb(KYBRD_CTRL_STATS_REG);
}

void kybrd_ctrl_send_cmd (uint8_t cmd) {
	while (1) {
		if ((kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
		
        outb(KYBRD_CTRL_CMD_REG, cmd);
    }
}

uint8_t kybrd_enc_read_buf() {
	return inb(KYBRD_ENC_INPUT_BUF);
}

void kybrd_enc_send_cmd(uint8_t cmd) {
	while (1) {
		if((kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
		
        outb(KYBRD_ENC_CMD_REG, cmd);
    }
}

int is_shift_down() {
    if(caps) return caps;
    
	return shift_down;
}

// void getline(char* string, int len){
// 	uint8_t i=0;
// 	int flag = 0;
// 	char temp = 0;
// 	int column = 3;

// 	memset(string,0,len);
// 	while(i<len && temp != 0x0D){
// 		temp = getchar();
// 		if((is_ascii(temp) == 1) && temp != 0x0D){ //0x0D is ENTER
// 			if(temp == 0x08)
// 			{   //backspace
// 				column -= 2;
// 				if(column < 2) column = 2;
// 				kprint_at(" ", column, getCurrentRow() - 1); //cancel last char
// 				set_cursor_offset(get_cursor_offset() - 2);
// 				i--;
// 			}
// 			else
// 			{
// 				kprint(&temp);
// 				string[i] = temp;
// 				i++;
// 			}

// 			column++;
// 		}
// 	}
// 	string[i] = 0x0A; //endline
// }

char getchar() {
	uint8_t code = 0;
	uint8_t key = 0;

	while(1) {
		if(kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF) {
			code = kybrd_enc_read_buf();
			if(code <= 0x58){
				key = _kkybrd_scancode_std[code];
				break;
			}
		}
	}

	return key;
}

char nonblocking_getchar() {
    uint8_t code = 0;
	uint8_t key = 0;
		
    if (kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF) {
		code = kybrd_enc_read_buf();

		if(code == 0x2A) {
			shift_down = 1; // shift down
			return 0;
		}

		if(code == 0xAA) {
			shift_down = 0; // shift up
			return 0;
		}

        if(code == 0x3A) {
            if(caps) caps = 0;
            else caps = 1;
        }

		if(code <= 0x58){
			key = _kkybrd_scancode_std[code];
		}
	}

	return key;
}
