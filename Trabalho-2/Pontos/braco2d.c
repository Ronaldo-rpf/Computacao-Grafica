#include <GL/glut.h>
#include <stdlib.h>

static GLint ombro = 0, cotovelo = 0, mao = 0;

void Desenho(void);
void Teclado (unsigned char tecla, GLint x, GLint y);
void DesenhaQuadrado(void);
void DesenhaTexto(char*);

void DesenhaQuadrado(void) {
     glBegin(GL_LINE_LOOP);
          glVertex2f(-1,1);
          glVertex2f(-1,-1);
          glVertex2f(1,-1);
          glVertex2f(1,1);
     glEnd();
}

void Desenho(void) {

   glClearColor (0.5, 0.50, 0.50, 0.0);  glClear (GL_COLOR_BUFFER_BIT);
   DesenhaTexto("Exemplo de TGs Hierarquicas");
   glPushMatrix();
        glTranslatef(-2,0.0,0.0);
        glRotatef ((GLfloat) ombro, 0.0, 0.0, 1.0);
        glTranslatef(1.0,0.0,0.0);
        glPushMatrix();
            glScalef(1.0,0.5,1.0);
            DesenhaQuadrado(); //Braço
        glPopMatrix();
        glPushMatrix();
            glTranslatef(1.0,0.0,0.0);
            glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
            glTranslatef(1,0.0,0.0);
            glPushMatrix();
                glScalef(1,0.5,1.0);
               glColor3ub(255,0,0);
               DesenhaQuadrado(); //Anti-braço
            glPopMatrix();
            glPushMatrix();
                glTranslatef(1,0.0,0.0);
                glRotatef ((GLfloat) mao, 0.0, 0.0, 1.0);
                glTranslatef(1,0.0,0.0);
                glPushMatrix();
                    glScalef(1,0.5,1.0);
                    glColor3ub(0,0,255);
                    DesenhaQuadrado(); //Mão
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
   glPopMatrix();
   glutSwapBuffers();
}

void Teclado (unsigned char tecla, GLint x, GLint y) {
   switch (tecla) {
      case 'a':
         ombro = (ombro + 5);  glutPostRedisplay();
         break;
      case 's':
         ombro = (ombro - 5);  glutPostRedisplay();
         break;
      case 'n':
         cotovelo = (cotovelo + 5); glutPostRedisplay();
         break;
      case 'm':
         cotovelo = (cotovelo - 5); glutPostRedisplay();
         break;
      case 'z':
         mao = (mao + 5); glutPostRedisplay();
         break;
      case 'x':
         mao = (mao - 5); glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;
      default: break;
   }
}

// Desenha um texto na janela GLUT
void DesenhaTexto(char *string) {
  	glColor3ub(255,0,0);
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(-4,-4);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
	glColor3ub(255,255,255);
}


int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1000, 1000);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glutDisplayFunc(Desenho);
   gluOrtho2D(-5.0,5.0,-5.0,5.0);//Exibição Bidimensional
   glutKeyboardFunc(Teclado);
 //  glutFullScreen();
   glutMainLoop();
   return 0;
}