#include <pic.h>

enum MOVE {
	STRAIGHT,
	RIGHT_DOWN,
	LEFT_DOWN,
	SMALL_LEFT_DOWN,
	SMALL_RIGHT_DOWN,
};


__CONFIG(0xFFFA);
int last_time;

int wait00(short k) {
	short i;
	short j;
   	for(j=0; j<k; j++){
		for(i=0; i<3; i++){

		}
	}
	return 0;
}

int left_down() {
	PORTA=0x03; /* both motor on */
	wait00(3);   /* 0.03msec wait */
	PORTA=0x01; /* right motor on */
	wait00(18);   /* 0.14msec wait */
	PORTA=0x00; /* both motor off */
	wait00(79);   /* 0.83msec wait */
}

int small_left_down() {
	PORTA=0x03; /* both motor on */
	wait00(5);   /* 0.05msec wait */
	PORTA=0x01; /* right motor on */
	wait00(12);   /* 0.10msec wait */
	PORTA=0x00; /* both motor off */
	wait00(83);   /* 0.85msec wait */
}

int right_down() {
	PORTA=0x03; /* both motor on */
	wait00(3);   /* 0.03msec wait */
	PORTA=0x02; /* left motor on */
	wait00(18);   /* 0.14msec wait */
	PORTA=0x00; /* both motor off */
	wait00(79);   /* 0.83msec wait */
}

int small_right_down() {
	PORTA=0x03; /* both motor on */
	wait00(5);   /* 0.05msec wait */
	PORTA=0x02; /* left motor on */
	wait00(12);   /* 0.10msec wait */
	PORTA=0x00; /* both motor off */
	wait00(83);   /* 0.85msec wait */
}


int straight() {
	PORTA=0x03; /* both motor on */
	wait00(20);   /* 0.15msec wait */
	PORTA=0x00; /* both motor off */
	wait00(80);   /* 0.85msec wait */
}

int led_sens() {
	RB3=RB0;
	RB4=RB1;
	RB5=RB2;
}

int takeAMove(int move) {
	// automat
	switch(move) {
		case LEFT_DOWN:
		left_down();
		break;
		case RIGHT_DOWN:
		right_down();
		break;
		case STRAIGHT:
		straight();
		break;
		case SMALL_LEFT_DOWN:
		small_left_down();
		break;
		case SMALL_RIGHT_DOWN:
		small_right_down();
		break;
		default:
		break;
	}
}

int utilityFunction(int flag, int rb0, int rb1, int rb2) {
	int result;

	if(rb0 == 0 && rb1 == 0 && rb2 == 0) {
		result = 000;
	} else if(rb0 == 0 && rb1 == 0 && rb2 == 1) {
		result = 001;
	} else if(rb0 == 0 && rb1 == 1 && rb2 == 0) {
		result = 010;
	} else if(rb0 == 0 && rb1 == 1 && rb2 == 1) {
		result = 011;
	} else if(rb0 == 1 && rb1 == 0 && rb2 == 0) {
		result = 100;
	} else if(rb0 == 1 && rb1 == 0 && rb2 == 1) {
		result = 101;
	} else if(rb0 == 1 && rb1 == 1 && rb2 == 0) {
		result = 110;
	} else if(rb0 == 1 && rb1 == 1 && rb2 == 1) {
		result = 111;
	}

	if(flag) {
		result += 1000;
	}

	return result;
}

int polling() {
	int flag = 0;
	int case000Flag = 0;
	led_sens();

	switch(utilityFunction(flag, RB0, RB1, RB2)) {
		case 000:
		takeAMove(last_time);
		case000Flag = 1;
		break;
		case 001:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(SMALL_LEFT_DOWN);           /* turn left a little */
		last_time = LEFT_DOWN;
		break;
		case 010:
		takeAMove(STRAIGHT);                  /* go to straight */
		last_time = STRAIGHT;
		flag = 0;
		break;
		case 101:
		takeAMove(STRAIGHT);                  /* go to straight */
		last_time = STRAIGHT;
		flag = 1;
		break;
		case 011:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(LEFT_DOWN);                 /* turn left */
		last_time = LEFT_DOWN;
		break;
		case 100:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(SMALL_RIGHT_DOWN);          /* turn right a little */
		last_time = RIGHT_DOWN;
		break;
		case 110:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(RIGHT_DOWN);                /* turn right */
		last_time = RIGHT_DOWN;
		break;
		case 111:
		takeAMove(last_time);
		break;


		case 1000:
		takeAMove(last_time);                /* turn right */
		case000Flag = 1;
		break;
		case 1001:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(RIGHT_DOWN);                /* turn right */
		last_time = RIGHT_DOWN;
		break;
		case 1010:
		takeAMove(STRAIGHT);                /* turn right */
		last_time = STRAIGHT;
		flag = 0;
		break;
		case 1101:
		takeAMove(STRAIGHT);                /* turn right */
		last_time = STRAIGHT;
		flag = 1;
		break;
		case 1011:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(SMALL_RIGHT_DOWN);                /* turn LEFT */
		last_time = RIGHT_DOWN;
		break;
		case 1100:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(LEFT_DOWN);                /* turn right */
		last_time = LEFT_DOWN;
		break;
		case 1110:
		// if(case000Flag) {
		// 	takeAMove(last_time);
		// 	case000Flag = 0;
		// 	break;
		// }
		takeAMove(SMALL_LEFT_DOWN);                /* turn right */
		last_time = LEFT_DOWN;
		break;
		case 1111:
		takeAMove(last_time);                /* turn right */
		break;
		default:
		break;
	}
}

int main() {
	TRISA = 0xFC; /* A 0,1:output, 2,3,4:input */
	TRISB = 0xC7; /* B0,1,2:input, B3,4,5:LEDoutput, other bits input */
	PORTB = 0;    /* PORTB clear */
	PORTA = 0;    /* PORTA clear */
	last_time = STRAIGHT;
	while(RA4 == 1) {
		led_sens();
	}
	while(1) {
		polling();
	}	
}