#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <ctime>

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22

using namespace std;


char field[FIELD_HEIGHT][FIELD_WIDTH];         // FIELD描画用レイヤー
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH]; // MINO描画用レイヤー

enum {
	MINO_TYPE_I,
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_T,
	MINO_TYPE_MAX
};

enum {
	MINO_ANGLE_0,
	MINO_ANGLE_90,
	MINO_ANGLE_180,
	MINO_ANGLE_270,
	MINO_ANGLE_MAX
};

#define MINO_WIDTH 4
#define MINO_HEIGHT 4
char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] = {
	//MINO_TYPE_I
	{
		//MINO_ANGLE_0,
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0 ,1 ,0, 0,
			0, 1, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1 ,1, 1,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0 ,1 ,0, 0,
			0, 1, 0, 0
		},
		//MINO_ANGLE_270,
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1 ,1, 1,
			0, 0, 0, 0
		}
	},

	//MINO_TYPE_O,
	{
		//MINO_ANGLE_0,
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_270,
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		}
	},

	//MINO_TYPE_S,
	{
		//MINO_ANGLE_0,
		{
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0, 
			0, 0, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_270,
		{
			1, 0, 0, 0,
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},

	//MINO_TYPE_Z,
	{
		//MINO_ANGLE_0,
		{
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 0, 0, 0,
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_270,
		{
			0, 1, 0, 0,
			1, 1, 0, 0,
			1, 0, 0, 0,
			0, 0, 0, 0
		}
	},

	//MINO_TYPE_J,
	{
		//MINO_ANGLE_0,
		{
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			1, 0, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_270,
		{
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},

	//MINO_TYPE_L,
	{
		//MINO_ANGLE_0,
		{
			1, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_270,
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0
		}
	},

	//MINO_TYPE_T,
	{
		//MINO_ANGLE_0,
		{
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_90,
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_180,
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		//MINO_ANGLE_270,
		{
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},
};

int minoX = 5;      // minoの(左上)初期位置
int minoY = 0;
int minoTYPE = 6;
int minoANGLE = 0;


void display() 
{
	memcpy(displayBuffer, field, sizeof(field));  // displayの初期化

	for (int i = 0; i < MINO_HEIGHT; ++i) {
		for (int j = 0; j < MINO_WIDTH; ++j) {
			displayBuffer[minoY + i][minoX + j] = minoShapes[minoTYPE][minoANGLE][i][j];
		}
	}

	std::system("cls"); // コンソールを全てクリア
	for (int i = 0; i < FIELD_HEIGHT; ++i) {
		for (int j = 0; j < FIELD_WIDTH; ++j) {
			std::cout << (displayBuffer[i][j] ? "■" : "　");
		}
		std::cout << std::endl;
	}
}

bool isHit(int _minoX, int _minoY, int _minoTYPE, int _minoANGLE) {
	for (int i = 0; i < MINO_HEIGHT; ++i) {
		for (int j = 0; j < MINO_WIDTH; ++j) {
			if (minoShapes[_minoTYPE][_minoANGLE][i][j] && field[_minoY + i][_minoX + j]) {
				return true;
			}
		}
	}
	return false;
}

int main() 
{
	memset(field, 0, sizeof(field));  // fieldの初期化
	
	for (int i = 0; i < FIELD_HEIGHT; ++i) {
		field[i][0] = field[i][FIELD_WIDTH - 1] = 1;
	}
	for(int i=0; i<FIELD_WIDTH; ++i){
		field[FIELD_HEIGHT-1][i] = 1;
	}

	std::time_t  t = time(NULL);
	while (1) 
	{
		/* 1 秒ずつ進める */
		if (t != time(NULL)) {
			t = time(NULL);

			if (!isHit(minoX, minoY - 1, minoTYPE, minoANGLE))
				minoY++;

			display();
		}

		/* kbhit : 標準入力上にデータが存在する場合は 1 無い場合は 0 を返す */
		if (_kbhit()) { 
			switch (_getch()) {
			//case 'w':
			case 's':  // Down
				minoY++;
				break; 
			case 'a':  // Left
				if ( !isHit(minoX - 1, minoY, minoTYPE, minoANGLE) )
				minoX--;
				break;
			case 'd': // Right
				if ( !isHit(minoX + 1, minoY, minoTYPE, minoANGLE) )
				minoX++;	
				break;
			case 0x20:
				if ( !isHit(minoX + 1, minoY, minoTYPE, (minoANGLE + 1) % MINO_ANGLE_MAX) )
				minoANGLE = (minoANGLE + 1) % MINO_ANGLE_MAX;
				break;
			}
		}	
	}

	


	//_getch();

	return 0;
}