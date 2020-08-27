#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include<ncurses.h>
#define ROW_D 4
#define COL_D 4
#define EMPTY 0

int game_on(int board[ROW_D][COL_D]);
void generate_random(int board[ROW_D][COL_D], int emptys);
int check_board (int board[ROW_D][COL_D]);
void reverse_board(char input, int board[ROW_D][COL_D]);
void show(int board[ROW_D][COL_D]);
void add_element_vertical(int board[ROW_D][COL_D]);
void add_element_horizontal(int board[ROW_D][COL_D]);
void rm_blankspace_vertical(int board[ROW_D][COL_D], int columns, int rows);
void rm_blankspace_horizontal(int board[ROW_D][COL_D], int rows, int columns);

void rm_blankspace_horizontal(int board[ROW_D][COL_D], int rows, int columns)
{
  int j,tmp;
  
  for (j=columns; j<COL_D-1; ++j)//Move os elementos usando um bubble sort na linha inteira
  {
    tmp = board[rows][j];
    board[rows][j] = board[rows][j+1];
    board[rows][j+1] = tmp;
  }
}
 
void rm_blankspace_vertical(int board[ROW_D][COL_D], int columns, int rows)
{
  int i,tmp;
 
  for (i=rows; i<ROW_D-1; ++i)//Move os elementos usando um bubble sort na coluna inteira
  {
    tmp = board[i][columns];
    board[i][columns] = board[i+1][columns];
    board[i+1][columns] = tmp;
  }
}
 
void add_element_horizontal(int board[ROW_D][COL_D])
{
  int i,j,flag;

  for (i=0; i<ROW_D; ++i)
    for (j=0,flag=0; j<COL_D-1 && flag!=4; ++j)
      if(board[i][j] == EMPTY)
      {
        rm_blankspace_horizontal(board,i,j);
        --j;
        ++flag;
      }
      else
      {
        if (board[i][j+1] == EMPTY)
        {
          board[i][j+1] = board[i][j];
          board[i][j] = EMPTY;
          --j;
        }
        else if(board[i][j] == board[i][j+1])
        {
          board[i][j] += board[i][j+1];
          board[i][j+1] = EMPTY;
        }  
      }
}
 
void add_element_vertical(int board[ROW_D][COL_D])
{
  int i,j,flag;
 
  for (j=0; j<COL_D; ++j)
    for (i=0,flag=0; i<ROW_D-1 && flag!=4; ++i) 
      if (board[i][j] == EMPTY)
      {
        rm_blankspace_vertical(board,j,i);//realoca todos os elementos movendo-os uma linha para baixo
        --i;//retorna para a posição i anterior
        ++flag;//sinal de controle para o final da linha
      }
      else
      {
        if (board[i+1][j] == EMPTY)//Se o próxima campo conter Vazio, aloca o elemento atual no próximo
        {
          board[i+1][j] = board[i][j];
          board[i][j] = EMPTY;
          --i;//retornar para a posição anterior
        }
        else if(board[i][j] == board[i+1][j])//realiza a soma das Potências de 2
        {
          board[i][j] += board[i+1][j];
          board[i+1][j] = EMPTY;//Esvazia o próximo campo visto que o atual agora contem a soma de ambos
        }
      }
}
 
void show(int board[ROW_D][COL_D])
{
  int i,j;
 
  for (i=0; i<ROW_D; ++i)
  {
    printw("\n");
    for (j=0; j<COL_D; ++j)
      printw("%4d",board[i][j]);//imprime o elemento inteiro(%d) com um espaço de 4
  }
  printw("\n");
  refresh();
}
 
void reverse_board(char input, int board[ROW_D][COL_D])
{
  int i,j,aux,tmp;
 
  if (input=='d')//inverte a tabela onde direita vira esquerda e esquerda vira direita,inversão de coordenadas
    for(i=0; i<ROW_D; ++i)
      for (j=0,aux=3; j<2; ++j,--aux)
      {
        tmp = board[i][j];
        board[i][j] = board[i][aux];
        board[i][aux] = tmp;
      }
  else if(input=='b')//inverte a tabela onde baixo vira cima e cima vira baixo, inversão de coordenadas
    for (i=0; i<ROW_D; ++i)
      for (j=0,aux=3; j<2; ++j,--aux)
      {
        tmp = board[j][i];
        board[j][i] = board[aux][i];
        board[aux][i] = tmp;
      }
}
 
int check_board (int board[ROW_D][COL_D])
{
  int i,j;
  int flag = 0,blanks = 0;
  
  for (i=0; i<ROW_D; ++i)
    for (j=0; j<COL_D; ++j)
      if (board[i][j] == 2048)
	      flag = -1;
      else if (board[i][j] == EMPTY)
	      ++blanks;

  if(flag!=-1)
    return blanks;//retorna o número de campos vazios disponíveis
  else
    return flag;//retorna se o usuário conseguiu alcançar 2048
}
 
void generate_random(int board[ROW_D][COL_D], int emptys)
{
  srand(time(NULL));
  int i, j;
  int random_pos = 0;
  int num = 0;
 
  blanks_spaces = rand() % emptys;//Número aleatório gerado entre a quantidade de campos vazios, caso não haja, pega o número 0
  while (1) //Loop para gerar um número aleatório sendo 2 ou 4
  {
    if (num == 4 || num == 2)
      break;
    else
      num = rand() % 5;
  }

  for (i=0; i<ROW_D; ++i)
    for (j=0; j<COL_D; ++j)
      if (board[i][j]==EMPTY && blanks_spaces!=0)//Verifica se a posição[i][j] é um campo vazio e caso seja, diminui do número de campos vazios
	      --blanks_spaces;
      else if (board[i][j]==EMPTY && blanks_spaces==0)//Aloca o número na posição [i][j] caso seja vazia e tenha se esgotado o número de campos vazios
      {
        board[i][j]=num;
	      return;
      }
}
 
int game_on(int board[ROW_D][COL_D])
{
  char direction;
  int space=0,flag=0;
 
  cbreak();
  while(1)
  {
    printw("Digite uma das direcoes a seguir: d=direita, e=esquerda, c=cima, b=baixo, s=sair >> ");
    refresh();
    direction = getch();
    if(direction == 'b')//(strcmp(direction,"b")==0)
    {
      reverse_board(direction,board); // inverte para realizar a movimentação dos elementos para cima 
      add_element_vertical(board); // adiciona os elementos para cima
      space = check_board(board); // retorna se o jogador ganhou(-1) ou se o número de campos disponíveis acabou(0)
      if (space==-1)
	      return -1;
      else if (space==0)
	      return 0;
      generate_random(board,space);// gera o próximo número(2 ou 4) com base no número de campos disponíveis
      reverse_board(direction, board);// restaura a matriz nas posições corretas
      ++flag;
    }
    else if(direction == 'c')//(strcmp(direction,"c")==0)
    {
      add_element_vertical(board); // adiciona os elementos para cima
      space = check_board(board); // retorna se o jogador ganhou(-1) ou se o número de campos disponíveis acabou(0)
      if (space==-1)
	      return -1;
      else if (space==0)
	      return 0;
      generate_random(board,space);// gera o próximo número(2 ou 4) com base no número de campos disponíveis
      ++flag;
    }
    else if(direction == 'd')//(strcmp(direction,"d")==0)
    {
      reverse_board(direction,board); // inverte para realizar a movimentação dos elementos para a esquerda
      add_element_horizontal(board); // adiciona o elemento na horizontal para a esquerda
      space = check_board(board); // retorna se o jogador ganhou(-1) ou se o número de campos disponíveis acabou(0)
      if (space==-1)
	      return -1;
      else if (space==0)
	      return 0;
      generate_random(board,space); // gera o próximo número(2 ou 4) com base no número de campos disponíveis
      reverse_board(direction, board); // restaura a matriz nas posições corretas
      ++flag;
    }
    else if(direction == 'e')//(strcmp(direction,"e")==0)
    {
      add_element_horizontal(board); // adiciona o elemento na horizontal para a esquerda
      space = check_board(board); // retorna se o jogador ganhou(-1) ou se o número de campos disponíveis acabou(0)
      if (space == -1)
	      return -1;
      else if (space == 0)
	      return 0;
      generate_random(board,space); // gera o próximo número(2 ou 4) com base no número de campos disponíveis
      ++flag;
    }
    else if(direction == 's')//(strcmp(direction,"sair")==0)
      return 1;
    else
    {
      printw("\nComando Invalido, digite novamente!\n");
      refresh();
      ++flag;
    }
    if(flag == 7) //Condição de limpar a tela para as próximas jogadas
    {
      clear();
      flag = 0;
    }
    show(board);
  }
}
 
int main()
{
  int win_condition;
  int board[ROW_D][COL_D];
  for(int i=0; i<ROW_D; ++i)
    for(int j=0; j<COL_D; ++j)
      board[i][j] = 0;
  
  initscr();
  raw();
  generate_random(board,16); // inicializa o jogo. (4*4=16)
  printw("Use as direcoes(d=direita, e=esquerda, c=cima, b=baixo) para movimentar os blocos;\n"\
   "Quando dois blocos de numeros iguais se chocam, eles viram um so com valor igual a soma dos dois;\n"\
	 "A cada movimento eh acrescentado um bloco com valor 2 ou com valor 4 \n"\
	 "Voce ganha quando conseguir um bloco no valor de 2048.\n");
  refresh();
  show(board);
  win_condition = game_on(board);//recebe o valor de condição do jogo
    if(win_condition==1)//1 = desistência do usuário
    {
      clear();
      printw("\nJogo terminado por desistencia do usuario!\n");
      refresh();
    }
  else if(win_condition==0)//0 = sem possibilidade de criar um 2 ou 4 em algum campo vazio
  {
    clear();
    printw("\nVoce estourou o numero de campos disponiveis!\n");
    refresh();
    show(board);
  }
  else if(win_condition==-1)//1 = Conseguiu obter a soma até chegar em 2048
  {
    clear();
    printw("\nVoce ganhou, Parabens!\n");
    refresh();
    show(board);
  }
  getch();
  endwin();
  return 0;
}