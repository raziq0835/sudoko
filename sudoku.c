#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

typedef struct node
{
    int val;
    int bno;
    int bx;
    int by;
}Node;

char board[9][3][3];
int no;


void initializeBoard();
bool solve();
bool checkSolve();
int clrscr()
{
    system("cls");
}
bool insertCom(int a,int bno,int bx,int by);
void setBoard();
void printBoard();
bool insertPlr(int a,int bno,int bx,int by);

void play();
void main()
{
    int ch;
    for(;;)
    {
        printf("1.play \n2.Exit\n");
        printf("Enter choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                play();
                break;
            case 2:
                exit(0);
                break;
            default:
                printf("Enter valid choice\n");
                break;
        }
    
    }
    

}

void initializeBoard()
{
    for(int k=0;k<9;k++)
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    board[k][i][j] = ' ';

}
void printBoard()
{
    printf("\n\n\tSUDUKO GAME\n\n");
    printf( "+-------+-------+-------+\n");
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[0][0][0],board[0][0][1],board[0][0][2],board[1][0][0],board[1][0][1],board[1][0][2],board[2][0][0],board[2][0][1],board[2][0][2]);
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[0][1][0],board[0][1][1],board[0][1][2],board[1][1][0],board[1][1][1],board[1][1][2],board[2][1][0],board[2][1][1],board[2][1][2]);
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[0][2][0],board[0][2][1],board[0][2][2],board[1][2][0],board[1][2][1],board[1][2][2],board[2][2][0],board[2][2][1],board[2][2][2]);
    printf( "|-------|-------|-------|\n");
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[3][0][0],board[3][0][1],board[3][0][2],board[4][0][0],board[4][0][1],board[4][0][2],board[5][0][0],board[5][0][1],board[5][0][2]);
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[3][1][0],board[3][1][1],board[3][1][2],board[4][1][0],board[4][1][1],board[4][1][2],board[5][1][0],board[5][1][1],board[5][1][2]);
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[3][2][0],board[3][2][1],board[3][2][2],board[4][2][0],board[4][2][1],board[4][2][2],board[5][2][0],board[5][2][1],board[5][2][2]);
    printf( "|-------|-------|-------|\n");
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[6][0][0],board[6][0][1],board[6][0][2],board[7][0][0],board[7][0][1],board[7][0][2],board[8][0][0],board[8][0][1],board[8][0][2]);
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[6][1][0],board[6][1][1],board[6][1][2],board[7][1][0],board[7][1][1],board[7][1][2],board[8][1][0],board[8][1][1],board[8][1][2]);
    printf("| %C %C %c | %C %C %C | %C %C %C |\n",board[6][2][0],board[6][2][1],board[6][2][2],board[7][2][0],board[7][2][1],board[7][2][2],board[8][2][0],board[8][2][1],board[8][2][2]);
    printf( "+-------+-------+-------+\n");


}

void setBoard()
{
    initializeBoard();    
    srand(time(0));
    no = rand()%35 + 10;
    int num = no;
    while(num != 0)
    {
        int a = rand()%9 + 1;
        int bno = rand()%9;
        int bx = rand()%3;
        int by = rand()%3; 
        if(!insertCom(a,bno,bx,by))
        continue;
        num--;
    }
}

bool insertCom(int a,int bno,int bx,int by)
{
    char boardValue;
    sprintf(&boardValue,"%d",a);
    if(board[bno][bx][by] != ' ')
    return false;

    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    {
        if(boardValue == board[bno][i][j])
        return false;
    }

    for(int k=bno % 3 ;k<9;k+=3)
    for(int i=0;i<3;i++)
    {
        if(boardValue == board[k][i][by])
        return false;
    }

    
    int cbno = (bno / 3) * 3;
    int ebno = cbno + 3;

    for(int k=cbno;k<ebno;k++)
    for(int j=0;j<3;j++)
    {
        if(boardValue == board[k][bx][j])
        return false;
    }

    board[bno][bx][by] = boardValue;
    return true;


}

void play()
{
    Node stack[50];
    int top = -1;
    int flag =0;
    
    int val,bno,bx,by;
    setBoard();
    for(;;)
    {
        printBoard();
        printf("\n\n0.Exit\n10.New game \n11.Undo \n12.solve\n13.play with guid \n14.stop play with guid \n");
        printf("Enter value : ");
        scanf("%d",&val);
        if(val<0 || val>14)
        {
            printf("invalid value");
            continue;
        }
        if(val == 0)
        exit(0);
        if(val == 10)
        {
            setBoard();
            top = -1;
            continue;
        }
        if(val == 11)
        {
            if(top == -1)
            {
                printf("Not played yet\n");
                continue;
            }
            
            board[stack[top].bno][stack[top].bx][stack[top].by] = ' ';
            top--;
            continue;
        }
        if(val == 12)
        {
            solve();
            continue;
        }
        if(val == 13)
        {
            flag = 1 ;
            continue;

        }
        if(val == 14)
        {
            flag = 0;
            continue;

        }
        printf("Enter bord no : ");
        scanf("%d",&bno);
        bno--;
        if(bno < 0 || bno > 8)
        {
            printf("Invalid bno");
            continue;
        }
        printf("Enter row : ");
        scanf("%d",&bx);
        bx--;
        if(bx < 0 || bx > 2)
        {
            printf("Invalid bno");
            continue;
        }
        printf("Enter col : ");
        scanf("%d",&by);
        by--;
        if(by < 0 || by > 2)
        {
            printf("Invalid bno");
            continue;
        }
        if(flag == 0)
        {
            if(!insertPlr(val,bno,bx,by))
            {
                printf("Can't Enter try Again : ");
                continue;
            }
            top++;
            stack[top].val = val;
            stack[top].bno = bno;
            stack[top].bx = bx;
            stack[top].by = by;
            no++;
            if(no == 81)
            {
                if(checkSolve())
                printf("\n\tSolved using computer help\n");
                printf("press any key to exit :");
                char q;
                scanf("%c",&q);
                exit(0);
            }
            
        }
        else
        {
            if(!insertCom(val,bno,bx,by))
            {
                printf("Can't Enter try Again : ");
                continue;
            }
            top++;
            stack[top].val = val;
            stack[top].bno = bno;
            stack[top].bx = bx;
            stack[top].by = by;
            no++;
            if(no == 81)
            {
                if(checkSolve())
                printf("\n\tSolved genuen\n");
                printf("press any key to exit :");
                char q;
                scanf("%c",&q);
                exit(0);
            }
        
        }

        


        
    }
}

bool insertPlr(int a,int bno,int bx,int by)
{
    char boardValue;
    sprintf(&boardValue,"%d",a);
    if(board[bno][bx][by] != ' ')
    return false;
    
    board[bno][bx][by] = boardValue;
    return true;
}


bool checkSolve()
{
    char boardValue;
    for(int bno=0;bno<9;bno++)
    for(int bx=0;bx<3;bx++)
    for(int by=0;by<3;by++)
    {
        boardValue = board[bno][bx][by];
        if(board[bno][bx][by] != ' ')
        return false;

    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    {
        if(boardValue == board[bno][i][j])
        return false;
    }

    for(int k=bno;k<9;k+=3)
    for(int i=0;i<3;i++)
    {
        if(boardValue == board[k][i][by])
        return false;
    }

    int cbno,ebno;
    if(bno<3)
    {
        cbno = 0;
        ebno = 3;
    }
    else if(bno < 6)
    {
        cbno = 3;
        ebno = 6;
    }
    else
    {
        cbno = 6;
        ebno = 9;
    }

    for(int k=cbno;k<ebno;k++)
    for(int j=0;j<3;j++)
    {
        if(boardValue == board[k][bx][j])
        return false;
    }
    }
    return true;
}

bool solve()
{
    char boardValue;
    int bno,bx,by,flag = 0;
    for(int k=0;k<9;k++)
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    {
        if(board[k][i][j] != ' ')
            continue;
        else
        {
            for(int l=1;l<10;l++)
            {
                bno = k;
                bx = i; 
                by = j;
                flag = 0;
                sprintf(&boardValue,"%d",l);
                board[k][i][j] = boardValue;

                for(int p=0;p<3;p++)
                for(int q=0;q<3;q++)
                {
                    if(boardValue == board[bno][p][q])
                    flag = 1;
                    
                }

                for(int r=bno % 3 ;r<9;r+=3)
                for(int p=0;p<3;p++)
                {
                    if(boardValue == board[r][p][by])
                    flag = 1;
                }

                int cbno = (bno / 3) * 3;
                int ebno = cbno + 3;

                for(int r=cbno;r<ebno;r++)
                for(int q=0;q<3;q++)
                {
                    if(boardValue == board[r][bx][q])
                    flag = 1;
                }
                if(flag == 1)
                continue;
                if(solve())
                return true;
                else
                continue;


            }
            
        }
    
    }
    return true;
    
}