#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

// Quadric global para dibujar la esfera y el disco
GLUquadric* quadric;

// ---------------------------
// Función de redimensionado (proyección en perspectiva)
// ---------------------------
void reshape_cb(int w, int h) {
	if (h == 0) h = 1; // evitar división por cero
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 1.0, 500.0); // Cambio a proyección en perspectiva
	glMatrixMode(GL_MODELVIEW);
}

// ---------------------------
// Dibujo principal (Saturno)
// ---------------------------
void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// Cámara mirando ligeramente desde arriba (para ver bien el disco)
	gluLookAt(0, 20, 80,   // posición de la cámara
			  0, 0, 0,     // mira al centro
			  0, 1, 0);    // eje Y hacia arriba
	
	// ---------------------------
	// Dibujo de los anillos
	// ---------------------------
	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);         // Plano horizontal (XY)
	glColor3f(0.7f, 0.7f, 0.7f);             // Gris claro
	gluDisk(quadric, 11.0, 18.0, 64, 1);     // Disco con hueco
	glPopMatrix();
	
	// ---------------------------
	// Dibujo de la esfera de Saturno
	// ---------------------------
	glPushMatrix();
	glColor3f(0.8f, 0.6f, 0.4f);             // Color de Saturno
	glutSolidSphere(9.0, 64, 64);            // Esfera con radio 9
	glPopMatrix();
	
	glutSwapBuffers();
}


// ---------------------------
// Inicialización de OpenGL
// ---------------------------
void initialize() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Activamos buffer de profundidad para 3D
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ventana OpenGL");
	
	glutDisplayFunc(display_cb);
	glutReshapeFunc(reshape_cb);
	
	glEnable(GL_DEPTH_TEST); // Habilita el Z-buffer
	glClearColor(1.f, 1.f, 1.f, 1.f); // Fondo blanco
	
	quadric = gluNewQuadric(); // Se crea el objeto quadric para dibujar esferas y discos
}

// ---------------------------
// Función principal
// ---------------------------
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
