#include <GL/glut.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>

float largura = 800, altura = 600;
float angulo = 0.0f;
float velocidade = 0.0f, aumentoVelocidade = 0.1f; 
float camX = 0.0, camY = 2.0, camZ = 6.0;

GLUquadric *quad;

void DesenharTexto(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void desenhaLigacao(float x1, float y1, float z1, float x2, float y2, float z2){
    float vx = x2 - x1;
    float vy = y2 - y1;
    float vz = z2 - z1;
    float dist = sqrt(vx*vx + vy*vy + vz*vz);
    float ax;

    glPushMatrix();
        glTranslatef(x1, y1, z1);

        float v = sqrt(vx*vx + vz*vz);
        if (v < 0.0001){
            ax = (vy > 0 ? 0 : 180);
        } 
        else {
            ax = atan2(vx, vz) * 180.0 / 3.14159; // arco-tangente
        }

        glRotatef(ax, 0, 1, 0);
        glRotatef(-atan2(vy, v) * 180.0 / 3.14159, 1, 0, 0);

        glColor3f(0.5, 0.5, 0.5);
        gluCylinder(quad, 0.1, 0.1, dist, 10, 10);
    glPopMatrix();
}

void desenhaNO2() {
    float N[3]  = { 0.0,  0.5, 0.0}; 
    float O1[3] = {-1.2, -0.5, 0.0};
    float O2[3] = { 1.2, -0.5, 0.0};

    // Nitrogenio
    glPushMatrix();
        glTranslatef(N[0], N[1], N[2]);
        glColor3ub(0, 0, 255); 
        glutSolidSphere(0.6, 20, 20);
    glPopMatrix();

    // Oxigenio
    desenhaLigacao(N[0], N[1], N[2], O1[0], O1[1], O1[2]);
    glPushMatrix();
        glTranslatef(O1[0], O1[1], O1[2]);
        glColor3ub(255, 0, 0);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // Oxigenio
    desenhaLigacao(N[0], N[1], N[2], O2[0], O2[1], O2[2]);
    glPushMatrix();
        glTranslatef(O2[0], O2[1], O2[2]);
        glColor3ub(255, 0, 0);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

void desenhaSegundaViewport(){
    // Titulo
    glColor3ub(255, 0, 255);
    DesenharTexto(15, altura - 40, GLUT_BITMAP_TIMES_ROMAN_24, "MOLECULA:");
    
    glColor3ub(255, 0, 0);
    DesenharTexto(15, altura - 70, GLUT_BITMAP_HELVETICA_18, "Dioxido de");
    DesenharTexto(15, altura - 95, GLUT_BITMAP_HELVETICA_18, "Nitrogenio (NO2)");

    int yStart = altura - 150;
    glColor3ub(0, 0, 0);
    DesenharTexto(15, yStart, GLUT_BITMAP_HELVETICA_18, "CONTROLES:");
    
    DesenharTexto(15, yStart - 30, GLUT_BITMAP_HELVETICA_12, "Mouse Esquerdo:    Gira no sentido horario");
    DesenharTexto(15, yStart - 50, GLUT_BITMAP_HELVETICA_12, "Mouse Direito:        Gira no sentido anti-horario");
    DesenharTexto(15, yStart - 70, GLUT_BITMAP_HELVETICA_12, "Botao de Scroll:      Para a molecula");
    DesenharTexto(15, yStart - 90, GLUT_BITMAP_HELVETICA_12, "Botao +:                 Acelera a molecula");
    DesenharTexto(15, yStart - 110, GLUT_BITMAP_HELVETICA_12, "Botao -:                 Desacelera a molecula");
    DesenharTexto(15, yStart - 130, GLUT_BITMAP_HELVETICA_12, "Setas direcionais:    Move a camera");
    DesenharTexto(15, yStart - 150, GLUT_BITMAP_HELVETICA_12, "ESC:                      Sai do programa");

    // Velocidade
    char buffer[50];
    sprintf(buffer, "Velocidade: %.1f", velocidade);
    glColor3ub(100, 200, 255);
    DesenharTexto(15, 50, GLUT_BITMAP_HELVETICA_18, buffer);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float view1 = largura * 0.60, view2 = largura * 0.40;
    
    // VIEWPORT 1
    glViewport(0, 0, view1, altura);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, view1/altura, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    glRotatef(angulo, 0, 1, 0); 
    desenhaNO2();

    // VIEWPORT 2
    glViewport(view1, 0, view2, altura);
    
    glScissor(view1, 0, view2, altura);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Projecao 2D para o Texto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, largura*0.25, 0, altura);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    desenhaSegundaViewport();

    glFlush();
}

void idle() { // modifica o angulo pra molecula se mover
    angulo += velocidade;
    if(angulo > 360){
        angulo -= 360;
    }
    if(angulo < 0){
        angulo += 360;
    }
    glutPostRedisplay();
}

int flagDir = 2;
void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case '+': // mais
            if (flagDir){
                velocidade += aumentoVelocidade; 
                if (velocidade > 2.5){
                    velocidade -= aumentoVelocidade;
                }
            }
            else{
                velocidade -= aumentoVelocidade; 
                if (velocidade < -2.5){
                    velocidade += aumentoVelocidade;
                }
            }
            break;
        case '-': // menos
            if (flagDir){
                velocidade -= aumentoVelocidade;
                if (velocidade < 0){
                    velocidade += aumentoVelocidade;
                }
            }
            else{
                velocidade += aumentoVelocidade; 
                if (velocidade > 0){
                    velocidade -= aumentoVelocidade;
                }
            }
            break;
        case 27: // ESC
            exit(0); 
            break;
    }
    glutPostRedisplay();
}

void teclasEspeciais(int tecla, int x, int y){
    switch (tecla) {
        case GLUT_KEY_RIGHT: // seta direcional direita
            camX += 0.2; 
            break;
        case GLUT_KEY_LEFT: // seta direcional esquerda
            camX -= 0.2; 
            break;
        case GLUT_KEY_UP: // seta direcional pra cima
            camY += 0.2; 
            break;
        case GLUT_KEY_DOWN: //seta direcional pra baixo
            camY -= 0.2; 
            break;
    }
    glutPostRedisplay(); 
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){ // Somente quando pressionado, para nao acionar duas vezes
        // Sentido horario
        flagDir = 1;
        if (velocidade == 0){ 
            velocidade += aumentoVelocidade;
        }
        if (velocidade < 0){
            velocidade = 0;
            velocidade += aumentoVelocidade;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        // Sentido anti-horario
        flagDir = 0;
        if (velocidade == 0){ 
            velocidade -= aumentoVelocidade;
        }
        if (velocidade > 0){
            velocidade = 0;
            velocidade -= aumentoVelocidade;
        }
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
        // Parar
        velocidade = 0;
        flagDir = 2;
    }
}

void redimensionar(int w, int h) {
    largura = w;
    altura = h;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("NO2");
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    quad = gluNewQuadric(); // Para os cilindros
    gluQuadricDrawStyle(quad, GLU_FILL); // Cilindros preenchidos ou de arame
    glutDisplayFunc(display);
    glutReshapeFunc(redimensionar);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciais);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
