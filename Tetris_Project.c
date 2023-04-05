#include <stdio.h>
#include <windows.h>

#define block_h 4
#define block_w 4

#define HEIGHT 14
#define WIDTH 18

//void printxy(char*str , int x, int y );
void color(int x);

int surface [HEIGHT][WIDTH] = {0} ;//interface

enum block_type{
	O,
	J,
	L,
	I,
	Z,
	S,
	T,
};
int block_type_num = 7;

int cur_x=0,cur_y=0;

int BlockO[block_h][block_w] =	//O
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
	};

int BlockJ[block_h][block_w] =  //J
    {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
	};

int BlockL[block_h][block_w] =  //L
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
	};

int BlockI[block_h][block_w] =  //I
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
	};

int BlockZ[block_h][block_w] =  //Z
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
	};

int BlockS[block_h][block_w] =  //S
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
	};

int BlockT[block_h][block_w] =  //T
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
	};

int current_block[block_h][block_w];

void land_block()
{

    int w,h;

	for( w = 0; w < block_w; w++)
	{
		for( h = 0; h < block_h; h++)
		{
			if( current_block[h][w]==1)
			{
				surface[cur_y+h][cur_x+w]=1;
			}
		}
	}
}

//Week1_練習四 - 列印方塊
void print_block(int block[][block_w],int x,int y)
{

	int w,h;

	for( w = 0; w < block_w; w++)
	{
		for( h = 0; h < block_h; h++){

			if( block[h][w]==1)
			{
				printxy("O",x+w,y+h);
			}
		}
	}
}

//Week2_練習五 - 旋轉方塊
void copy_block(int block_s[][block_w],int block_d[][block_w])
{

    int w,h;

    for( w = 0; w < block_w; w++)
	{
        for( h = 0 ; h < block_h; h++)
		{
            block_d[h][w] = block_s[h][w];
        }
    }
}

void make_new_block()
{

    enum block_type type = (int)(rand()%block_type_num);

    switch(type)
	{
        case O:
            copy_block(BlockO,current_block);
            break;
        case J:
            copy_block(BlockJ,current_block);
            break;
        case L:
            copy_block(BlockL,current_block);
            break;
        case I:
            copy_block(BlockI,current_block);
            break;
        case S:
            copy_block(BlockS,current_block);
            break;
        case T:
            copy_block(BlockT,current_block);
            break;
        case Z:
            copy_block(BlockZ,current_block);
            break;
        default:
            break;
	}

    cur_x = (WIDTH-block_w)/2;
    cur_y = 0;
}

void rotate_block() //rotate blocks
{
    int temp[block_h][block_w] = {0};
    copy_block(current_block,temp);         //change block_cur to current_block
    int w,h;
	for( w = 0; w < block_w; w++)
	{
        for( h = 0; h < block_h; h++)
		{
            current_block[h][w] = temp[block_w-1-w][h];
        }
    }
}

//Week2_練習四 - 白邊判斷
int get_block_x_fill(int col) //傳入方塊的col
{

    int is_fill = 0;
    int row;

    //檢查方塊中，該row的每個col，是不是真的有方塊(1)
    //若有我們把is_fill改成1
	for( row = 0; row < block_w; row++)
	{
		if(current_block[row][col]==1)
		{
			return 1;
		}
	}

    return is_fill;
}

//Week2_練習四 - 白邊判斷
int get_block_y_fill(int row) //傳入方塊的row
{
	int is_fill = 0;
	int col;

	//檢查方塊中，該row的每個col，是不是真的有方塊(1)
    //若有我們把is_fill改成1
	for( col = 0; col < block_w; col++)
	{
		if( current_block[row][col]==1)
		{
			is_fill=1;
		}
	}
	return is_fill;
}

//Week2_練習四 - 白邊判斷
void get_block_top_bottom_margin(int *top_margin, int *bottom_margin)
{
	int i = 0;

	//檢查左半邊的白邊
    //如果有白邊(is_fill=0)，*left_margin+=1
	for( i = 0; i < block_h/2; i++){


        if( get_block_y_fill(i)==0)
		{
		    (*top_margin)+=1;
	    }
    }

    //檢查右半邊的白邊
    //如果有白邊(is_fill=1)，*right_margin+=1
	for( i = block_h-1; i >= block_h/2; i--)
	{
		if( get_block_y_fill(i)==0)
		{
            (*bottom_margin)+=1;
        }
	}
}

//Week2_練習四 - 白邊判斷
void get_block_left_right_margin(int *left_margin, int *right_margin)
{

	int i = 0;

	//檢查左半邊的白邊
    //如果有白邊(is_fill=0)，*left_margin+=1
	for( i = 0; i < block_w/2; i++)
	{
        if( get_block_x_fill(i)==0)
		{
            (*left_margin)+=1;
        }
	}

	//檢查右半邊的白邊
    //如果有白邊(is_fill=1)，*right_margin+=1
	for( i = block_w-1; i >= block_w/2; i--)
	{
        if( get_block_x_fill(i)==0)
		{
		    (*right_margin)+=1;
        }
	}
}

//Week2_練習三 - 邊界判斷
int isCollision(int x , int y)
{

	int top = 0,bottom = 0,left = 0,right = 0;
	get_block_left_right_margin(&left,&right);
    get_block_top_bottom_margin(&top,&bottom);

    //如果x<0或 x+方塊寬度 > surface的寬，表示撞到邊界回傳1。
    //如果y<0或 y+方塊高度 > surface的寬，表示撞到邊界回傳1。
    if( x < 0-left || x+block_w > WIDTH + right)
	{
    	return 1;
	}
	else if( y < 0-top || y+block_h > HEIGHT + bottom)
	{
		return 1;
	}
	int w,h;
    for( w = 0; w < block_w; w++)
	{
        for( h = 0; h < block_h; h++)
		{
            if( current_block[h][w]==1)
			{
                if(surface[y+h][x+w]==1)
                {
                	return 1;
				}
            }
        }
    }
	return 0;
}

//Week1_練習三 - 列印畫面
void print_surface()
{
	int x,y;
	for( x = 0; x < WIDTH; x++)
	{
		for( y = 0; y < HEIGHT; y++)
		{
			int row = y;
			int col = x;
			if ( surface[row][col]==0)
			{
				printxy(" ",x,y);
			} else {
				printxy("O",x,y);
			}
		}
	}
}
HANDLE hand;

//Week1_練習一 - 控制cursor
void setCursorVisable(int v)
{
	CONSOLE_CURSOR_INFO cursor_info = {100,v};
	SetConsoleCursorInfo(hand,&cursor_info);
}

//Week1_練習二 - 更改cursor位置並列印
void gotoxy(int x,int y)
{
	COORD loc;
	loc.X = x;
	loc.Y = y;
	SetConsoleCursorPosition(hand,loc);
}

void printxy(char*str , int x, int y)
{
	gotoxy(x,y);
	color(6);                           //block colour
	printf("%s", str);
	//color(7);
}

//Week1_練習五 - 列印+暫停+擦掉方塊
void erase_block(int block[][block_w],int x,int y)
{
	int w,h;
	for( w = 0; w < block_w; w++)
	{
		for( h = 0; h < block_h; h++)
		{
			if( block[h][w]==1)
			{
				printxy(" ",x+w,y+h);
			}
		}
	}
}

int tm = 800;
UINT_PTR timeId;

static void set_timer(int t)
{
    KillTimer(NULL, timeId);
    timeId = SetTimer(NULL,0,t,NULL);
}

static void close_timer()
{
	KillTimer(NULL, timeId);
}

int score = 0;

//week6_是否連線
int is_line_fill(int h)
{
    int w;
    for( w = 0; w < WIDTH; w++)
	{
        if( surface[h][w]==0)
		{
            return 0;
        }
    }
    return 1;
}

//week6_清除連線
void clear_one_line(int h)
{
	int w,row;
	for(row = h; row > 0; row--)
	{
		for( w = 0; w < WIDTH; w++)
		{
			surface[row][w] = surface[row-1][w];
		}
	}

	for( w = 0; w < WIDTH; w++)
	{
		surface[0][w] = 0;
	}

}

//scoring - 1 score for clearing 1 line
void check_line()
{

    int total_line = 0;
    int h;

    for( h = cur_x; h < HEIGHT; h++)
	{
        if( is_line_fill(h)==1)
		{
            clear_one_line(h);
            print_surface();
            total_line++;
        }
    }
    score = total_line;
}

void move_block_down()
{
    if ( isCollision(cur_x,cur_y+1)==0)
	{
        erase_block(current_block,cur_x,cur_y);
        cur_y++;
        print_block(current_block,cur_x,cur_y);
    }
    else{
        land_block();
        check_line();
        make_new_block();
        if ( isCollision(cur_x,cur_y)==1){

        	close_timer();
        	char arr[30];                       //XTRA
        	puts("");

        	color(7);                         //display score
        	printf("score %d\n",score);       //display score

            color(4);                         //display endgame
        	printf("Game over");               //display endgame

        	printxy(arr,30,0);
		}
        print_block(current_block,cur_x,cur_y);

    }
}




//Week2_練習一 - 重複讀取按鍵
//Week2_練習二 - 按鍵移動方塊
void key_control()
{

	int ch;
    MSG msg;

	while(1){
        if( PeekMessage(&msg,NULL,WM_TIMER,WM_TIMER,PM_REMOVE)!=0)
		{
            move_block_down();
        }
		if( kbhit()!=0){
			ch = getch();
			switch(ch){
				case 72://up
					if ( isCollision(cur_x,cur_y-1)==0)
					{
						erase_block(current_block,cur_x,cur_y);
				    	rotate_block();
				    	if ( isCollision(cur_x,cur_y)==1)
						{
				    		rotate_block();
				    		rotate_block();
				    		rotate_block();
						}
//						cur_y--;
				    	print_block(current_block,cur_x,cur_y);
					}
				    break;
				case 80://down
				    if ( isCollision(cur_x,cur_y+1)==0)
					{
						erase_block(current_block,cur_x,cur_y);
				    	cur_y++;
				    	print_block(current_block,cur_x,cur_y);
					}
				    break;
				case 75://left
				    if ( isCollision(cur_x-1,cur_y)==0)
					{
						erase_block(current_block,cur_x,cur_y);
				    	cur_x--;
				    	print_block(current_block,cur_x,cur_y);
					}
				    break;
				case 77://right
				    if ( isCollision(cur_x+1,cur_y)==0)
					{
						erase_block(current_block,cur_x,cur_y);
				    	cur_x++;
				    	print_block(current_block,cur_x,cur_y);
					}
				    break;
			}
		}
	}
}
void color(int x)   //XTRA
{

	if(x>=0 && x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	} else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
}


int main(){
	int y, x;
	//system("color 018");      //bg colour
	for ( y = 0; y <= 14; y++)
	{
		if ( y == 14 ){
			for ( x = 0; x <= 18; x++)
			{
				color(3);           //bottom margin
				printf(">");        //bottom margin
			}
			puts("");
		} else {
				color(9);                   //right margin
				printf("		  +\n");    //right margin
			}
		}
	}


	hand = GetStdHandle(STD_OUTPUT_HANDLE);
	setCursorVisable(0);
	//gotoxy(50,50);
	//printxy("bang!",10,10);
	srand(time(NULL));

//	copy_block(BlockJ,block_cur);
//	block_cur =BlockO;
	print_surface();
//	print_block(Block0,10,10);
	//for_sleep(INT_MAX);
//	Sleep(3000);
//	erase_block(Block0,10,10);
//	print_block(Block0,20,20);
	make_new_block();
	print_block(current_block,cur_x,cur_y);
	set_timer(tm);
	key_control();
	system("pause");
	return 0;

}
