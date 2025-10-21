/*#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>

int R = 0, G=0, B = 0;

void display(void);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);
void DesenhaTexto(char *string);

int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  glutInitWindowSize (800, 800); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (100, 100); //Estabelece o tamanho (em pixels) da janela a ser criada
  glutCreateWindow ("Minha janelinha"); //Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(0.0, 0.5, 0.80, 0.0); //selecionar cor de fundo (Branco)
  glOrtho (-1, 1,-1, 1, -1 ,1); //define as coordenadas do volume de recorte (clipping volume),
  glutDisplayFunc(display); //Função callback chamada para fazer o desenho
  glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
  glutSpecialFunc(Special_keyboard); // Registra a função para tratamento das teclas NÂO ASCII
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  printf("\nTestando... \n");
  return 0;
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
  DesenhaTexto("Exemplo de texto para a atividade 2");
  glColor3ub (R, G, B);
  //glBegin(GL_POINTS);
  //glBegin(GL_LINES);
  //glBegin(GL_LINE_STRIP);
  //glBegin(GL_LINE_LOOP);
  //glBegin(GL_QUADS);
  //glBegin(GL_QUAD_STRIP);
  glBegin(GL_TRIANGLES);
  //glBegin(GL_TRIANGLE_STRIP);
  //glBegin(GL_TRIANGLE_FAN);
 // glBegin(GL_POLYGON);
    glVertex2f(0.25,0.25);
    glVertex2f(0.75,0.25);
    glVertex2f(0.75,0.75);
    glVertex2f(0.25,0.75);
  glEnd();
  glFlush(); ////Executa os comandos OpenGL para renderização
}

void keyboard(unsigned char key, int x, int y){
  printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",key);
  switch (key) {
    case 27: exit(0); // ESC
    case 32: R = 0; G += 50; B = 0; glutPostRedisplay(); break;
  }
}

void Special_keyboard(GLint tecla, int x, int y) {
  switch (tecla) { // GLUT_KEY_RIGHT GLUT_KEY_DOWN GLUT_KEY_PAGE_UP GLUT_KEY_PAGE_DOWN GLUT_KEY_F1...
    case GLUT_KEY_F12: R = 0; G = 200; B = 200; glutPostRedisplay(); break;
    case GLUT_KEY_F10: R = 0; G = 100; B = 200; glutPostRedisplay(); break;
  }
}

void DesenhaTexto(char *string) {
  	glColor3ub(150,200,250);
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(-0.4,-0.4);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
	glColor3ub(255,255,255);
}*/

#include <GL/glut.h>
#include <math.h>

void desenhaCriatura() {
    // Corpo (triângulo central)
    glColor3f(0.3, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
        glVertex2f(-20, -10);
        glVertex2f(0, 30);
        glVertex2f(20, -10);
    glEnd();

    // Olho (círculo simulado com polígonos)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 10) {
            float ang = i * 3.14159 / 180.0;
            glVertex2f(5 + cos(ang) * 5, 10 + sin(ang) * 5);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaCriatura();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Criatura Fantástica 2D");
    glClearColor(0.1, 0.1, 0.1, 1.0);
    gluOrtho2D(-100, 100, -100, 100);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}