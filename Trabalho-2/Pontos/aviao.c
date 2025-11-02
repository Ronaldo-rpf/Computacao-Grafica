#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN -400
#define MAX 400
#define PI 3.1416;

void Desenho(void);
void Teclado(unsigned char tecla, int x, int y);

GLfloat dx=0, dy=0.0;
GLfloat aviao[17][2]= { //Coordenadas do aviao
      50,80, 55,70, 55,55, 100,50, 100,40, 55,40, 55,15, 60,10, 60,0,
      40,0, 40,10, 45,15, 45,40, 0,40, 0,50, 45,55, 45,70 };

void Desenho(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(3.0); //Altera a largura do desenho
  glColor3f (0.0,0.0,0.0);
  glBegin(GL_LINES);
    glVertex2f(MIN,0);
    glVertex2f(MAX,0);
    glVertex2f(0,MIN);
    glVertex2f(0,MAX);
  glEnd();
  glColor3f (1.0,0.0,0.0);
  glPushMatrix();
    glTranslatef(dx,dy,0.0);
    glBegin(GL_LINE_LOOP);
      for (int cont=0; cont<17; cont++)
          glVertex2f(aviao[cont][0],aviao[cont][1]);
    glEnd();
  glPopMatrix();
  glFlush(); //Força a execução dos comandos da opengl
}

//Função de tratamento de eventos do teclado com código ASCII
void Teclado(unsigned char tecla, int x, int y){
  switch (tecla) { //quando a tecla ESC (keycode=27) for pressionada
    case 27:       //o programa deverá ser finalizado
         exit(0);
    break;
  }
}

//Função de tratamento de eventos do teclado com código não-ASCII
void TeclasEspeciais(int tecla, int x, int y){
     GLfloat desloc=10;
	 switch (tecla) 		{   //Verifica se alguma tecla é pressionada
		case GLUT_KEY_RIGHT: //Seta direcional direita
		   dx+=desloc;
		   break;

       case GLUT_KEY_LEFT: //seta direcional esquerda
           dx-=desloc;
		   break;
        case GLUT_KEY_UP: //Seta direcional cima
		   dy+=desloc;
		   break;
        case GLUT_KEY_DOWN: //seta direcional baixo
           dy-=desloc;
		   break;
     }
     glutPostRedisplay(); // Chama a função display novamente, fazendo com
     //que a janela corrente seja redesenhada
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (800, 800); //Dimensões da janela
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("Aviao 4 por Vânia Cordeiro da Silva"); //Cria uma janela e define seu título
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glOrtho (MIN, MAX, MIN, MAX, -1 ,1);
  glutDisplayFunc(Desenho); //Chama a função de desenho
  glutKeyboardFunc(Teclado); //Trata eventos de teclado
  glutSpecialFunc(TeclasEspeciais); //Trata teclas com código não-ascii
  glutMainLoop(); //Inicia o loop de processamento de desenhos com GLUT
  return 0;
} 