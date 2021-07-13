#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
GLint screenSize[2] = {800, 500};	// width, height

struct polygonPoints {
	GLint x1, y1, x2, y2, x3, y3, x4, y4;
};
struct polygonPoints *skyPolygon, * outerskyPolygon, *oceanPolygon, *ozonePolygon, *landPolygon, *greenPolygon; // background
struct polygonPoints* factoryPolygon, * buildingPolygon, *windowPolygon; // elements

struct polygonVertices {
	GLint a[2];
	GLint b[2];
	GLint c[2];
	GLint d[2];
};
struct polygonVertices * skyVertices, * outerskyVertices, * oceanVertices, * ozoneVertices, * landVertices, * greenVertices; // background
struct polygonVertices* factoryVertices, * buildingVertices, *windowVertices; //elements

int CFC_array[13][13], xmin, xmax=100, ymin, ymax=100, xlen, ylen, ozonelen=10;
float ozoneVertices2[] = { 10, 10, 10, 10, 10, 10, 10, 10 };
float skyVertices2[] = { 10, 10, 10, 10, 10, 10, 10, 10 };
int translate = 0, tr_x, tr_y;
float color_sky[] = { 1, 0.768, 0.658 };
float color_green[] = { 0.290, 0.690, 0.011 };

void allocateMemory() {
	outerskyVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	outerskyPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	ozoneVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	ozonePolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	skyVertices = (struct polygonVertices *)malloc(sizeof(struct polygonVertices));
	skyPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	landVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	landPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	greenVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	greenPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	oceanVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	oceanPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));

	factoryVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	factoryPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	windowVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	windowPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));
	buildingVertices = (struct polygonVertices*)malloc(sizeof(struct polygonVertices));
	buildingPolygon = (struct polygonPoints*)malloc(sizeof(struct polygonPoints));

}

void polygonPointSetup(struct polygonPoints* ptr, GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4) {
	ptr->x1 = x1; ptr->y1 = y1;
	ptr->x2 = x2; ptr->y2 = y2;
	ptr->x3 = x3; ptr->y3 = y3;
	ptr->x4 = x4; ptr->y4 = y4;
}

void polygonVertexSetup(struct polygonVertices *ptr, struct polygonPoints *pnt) {
	ptr->a[0] = pnt->x1; ptr->a[1] = pnt->y1;
	ptr->b[0] = pnt->x2; ptr->b[1] = pnt->y2;
	ptr->c[0] = pnt->x3; ptr->c[1] = pnt->y3;
	ptr->d[0] = pnt->x4; ptr->d[1] = pnt->y4;
}

void polygonSetup() {

	allocateMemory();
	GLint width = screenSize[0], len = screenSize[1];
	// points
	polygonPointSetup(factoryPolygon, 0, 0, 0, 0, 0, 0, 0, 0);
	polygonPointSetup(windowPolygon, 0, 0, 10, 0, 10, 10, 0, 10 );
	polygonPointSetup(buildingPolygon, 0, 0, 0.1*width, 0, 0.1*width, 0.2*len, 0, 0.2*len);

	polygonPointSetup(outerskyPolygon, 0, 0.8*len, width, 0.8*len, width, len, 0, len);
	polygonPointSetup(ozonePolygon, 0, 0.7 * len, width, 0.7 * len, width, .8*len, 0, .8*len);

	ozonelen = ozoneVertices2[7] - ozoneVertices2[1];
	polygonPointSetup(skyPolygon, 0, 0.3 * len, width, 0.3 * len, width, .8 * len, 0, .8 * len);
	polygonPointSetup(landPolygon, 0, 0, 0.3*width, 0, 0.3*width, 0.3 * len, 0, 0.3 * len);
	polygonPointSetup(greenPolygon, 0.3 * width, 0, 0.6 * width, 0, 0.6 * width, 0.3 * len, 0.3*width, 0.3 * len);
	polygonPointSetup(oceanPolygon, 0.6 * width, 0, width, 0, width, 0.3 * len, 0.6*width, 0.3 * len);

	xmin = 0.015 * screenSize[0]; ymin = 0.025 * screenSize[1] + buildingPolygon->y4; // from draw_building
	xmax = 0.175 * screenSize[0] + buildingPolygon->x2; ymax = ozonePolygon->y4;
	xlen = xmax - xmin; ylen = ymax - ymin;

	// verices
	polygonVertexSetup(factoryVertices, factoryPolygon);
	polygonVertexSetup(windowVertices, windowPolygon);
	polygonVertexSetup(buildingVertices, buildingPolygon);

	polygonVertexSetup(outerskyVertices, outerskyPolygon);
	polygonVertexSetup(ozoneVertices, ozonePolygon);
	polygonVertexSetup(skyVertices, skyPolygon);
	polygonVertexSetup(landVertices, landPolygon);
	polygonVertexSetup(greenVertices, greenPolygon);
	polygonVertexSetup(oceanVertices, oceanPolygon);
}

void draw_polygon(struct polygonVertices* ptr, GLint i, GLint j) {
	glBegin(GL_POLYGON);
	glVertex2i(ptr->a[0]+i, ptr->a[1]+j);
	glVertex2i(ptr->b[0]+i, ptr->b[1]+j);
	glVertex2i(ptr->c[0]+i, ptr->c[1]+j);
	glVertex2i(ptr->d[0]+i, ptr->d[1]+j);
	glEnd();
}

void draw_outersky() {
	glColor3f(1, 0.549, 0.341);
	draw_polygon(outerskyVertices, 0, 0);
}

void draw_ozone() {
	//draw_polygon(ozoneVertices, 0 , 0);
	glColor3f(0.815, 0.705, 0.662);
	glBegin(GL_POLYGON);
	glVertex2f(ozoneVertices2[0], ozoneVertices2[1]);
	glVertex2f(ozoneVertices2[2], ozoneVertices2[3]);
	glVertex2f(ozoneVertices2[4], ozoneVertices2[5]);
	glVertex2f(ozoneVertices2[6], ozoneVertices2[7]);
	glEnd();
}

void draw_sky2() {
	glColor3fv(color_sky);
	glBegin(GL_POLYGON);
	glVertex2f(skyVertices2[0], skyVertices2[1]);
	glVertex2f(skyVertices2[2], skyVertices2[3]);
	glVertex2f(skyVertices2[4], skyVertices2[5]);
	glVertex2f(skyVertices2[6], skyVertices2[7]);
	glEnd();
}

void generateOzone() {
	float temp[] = { 0, 0.7 * screenSize[1], screenSize[0], 0.7 * screenSize[1], screenSize[0], .8 * screenSize[1], 0, .8 * screenSize[1] };
	for (int i = 0; i < 8; i++)
		ozoneVertices2[i] = temp[i];
}

void generateSky() {
	int temp[] = { 0, 0.3 * screenSize[1], screenSize[0], 0.3 * screenSize[1], screenSize[0], .8 * screenSize[1], 0, .8 * screenSize[1] };
	for (int i = 0; i < 8; i++)
		skyVertices2[i] = temp[i];
	draw_sky2();
}

void draw_land() {
	glColor3f(0.992, 0.709, 0.266);
	draw_polygon(landVertices, 0, 0);
}

void draw_green() {
	glColor3fv(color_green);
	draw_polygon(greenVertices, 0, 0);
}

void draw_ocean() {
	glColor3f(0.109, 0.811, 0.890);
	draw_polygon(oceanVertices, 0, 0);
}

void draw_factory() {
	glColor3f(0, 0, 0);
	draw_polygon(factoryVertices, 0, 0);
	glColor3f(1, 1, 1);
	for (int i = 10 + factoryPolygon->y1; i < 10 - factoryPolygon->y3; i += 10)
		for (int j = 10 + factoryPolygon->x1; j < 10 - factoryPolygon->x3; j += 10)
			draw_polygon(windowVertices, j, i);
}

void draw_building(GLint buildPosx, GLint buildPosy) {
	//glColor3f(0.964, 0.968, 0.470);
	glColor3f(0, 0, 0);
	draw_polygon(buildingVertices, buildPosx, buildPosy);
	glColor3f(1, 1, 1);
	GLint startx = buildingPolygon->x1 + 10+buildPosx, starty = buildingPolygon->y1 + 10+ buildPosy;
	GLint endx = buildingPolygon->x3 - 10+ buildPosx, endy = buildingPolygon->y3 - 10+ buildPosy;
	for (GLint i = startx; i < endx; i += 20) 
		for (GLint j = starty; j < endy; j += 20) 
			draw_polygon(windowVertices, i, j);
}

void draw_point(int p, int q) {
	// glColor3f(0.839, 0.658, 0.478);
	float theta = 0;
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.142 / 180;
		glVertex2f(p + 5 * cos(theta), q + 5 * sin(theta));
	}
	glEnd();
}

void generate_CFC() {
	if (translate == 1) {
		for (int i = 0; i < 13; i++) {
			CFC_array[i][0] = (rand() / (double)RAND_MAX) * xlen + xmin;
			CFC_array[i][1] = (rand() / (double)RAND_MAX) * ylen + ymin;
			draw_point(CFC_array[i][0], CFC_array[i][1]);
		}
	}
	if (translate == 3) {
		for (int i = 0; i < 4; i++) {
			CFC_array[i][0] = (rand() / (double)RAND_MAX) * xlen + xmin;
			CFC_array[i][1] = (rand() / (double)RAND_MAX) * ylen + ymin;
			draw_point(CFC_array[i][0], CFC_array[i][1]);
		}
	}
}

void translatepoint() {
	if (translate==1 || translate==3) {
		long j = 0;
		// delay(500);
		while (j++ < 100000000);
	}
}

void fish(int x, int y, int fcx, int fcy, int fcz)
{
	glColor3f(fcx, fcy, fcz);
	glBegin(GL_TRIANGLES);
	glVertex2i(350 + x , 30 + y );
	glVertex2i(360 + x , 40 + y );
	glVertex2i(360 + x , 30 + y );
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2i(350 + x , 30 + y );
	glVertex2i(360 + x , 40 + y );
	glVertex2i(340 + x , 60 + y );
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2i(345 + x , 80 + y );
	glVertex2i(340 + x , 60 + y );
	glVertex2i(325 + x , 70 + y );
	glEnd();
}

void translate_ozone() {
	glPushMatrix();
	glTranslatef(1, tr_y, 1);
	draw_ozone();
	glTranslatef(1, -tr_y, 1);
	glPopMatrix();
	draw_outersky();
	glutPostRedisplay();
}

void set_color(float *array, float r, float g, float b) {
	array[0] = r;
	array[1] = g;
	array[2] = b;
}

void initializeScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, screenSize[0], 0, screenSize[1]);	// make sure that it is sufficient
}

void draw_background() {
	polygonSetup();
	draw_outersky();
	generateSky();
	if (translate==1) {			// start
		translate_ozone();
		tr_y++;
		set_color(color_green, 0.65, 0.99, 0.41);
		set_color(color_sky, 1, 0.71, 0.47);
		if (tr_y >= ozonelen) {
			set_color(color_sky, 1, 0.549, 0.341);
			set_color(color_green, 0.8, 1, 0.2);
		}
	}
	else if (translate == 3) {
		translate_ozone();
		tr_y--;
		set_color(color_green, 0.65, 0.99, 0.41);
		set_color(color_sky, 1, 0.71, 0.47);
		if (tr_y == 0) {
			translate = 0;
		}
	}
	else if (translate == 2) {		// stop
		translate_ozone();
	}	
	else {		// reset
		draw_ozone();
		tr_y = 0;
		set_color(color_sky, 1, 0.768, 0.658);
		set_color(color_green, 0.290, 0.690, 0.011);
	}
	draw_land();
	draw_green();
	draw_ocean();

	fish(170, 60, 1, 1, 1);
	fish(270, 50, 1, 1, 1);
	if (translate == 0) {
		fish(280, 30, 1, 1, 1);
		fish(190, 50, 1, 1, 1);
	}
	if (tr_y < ozonelen) {
		fish(170, 10, 1, 1, 1);
		fish(220, 50, 1, 1, 1);
	}
	draw_building(0.15 * screenSize[0], 0.15 * screenSize[1]);
	draw_building(0.05 * screenSize[0], 0.05 * screenSize[1]);
	draw_building(0.015 * screenSize[0], 0.025 * screenSize[1]);
	draw_building(0.175 * screenSize[0], 0.075 * screenSize[1]);
}

void mouseactions(int key) {
	if (key == 1) {
		translate = 1;
	}
	if (key == 2 && translate==1) {
		translate = 2;
	}
	if (key == 3 && (translate == 1 || translate == 2)) {
		translate = 3;
	}
	if (key == 4) {
		translate = 0;
	}
}

void display() {
	draw_background();
	generateOzone();
	if(translate == 1 || translate == 3)
		generate_CFC();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(screenSize[0], screenSize[1]);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Trial");
	initializeScreen();
	glutDisplayFunc(display);
	glutCreateMenu(mouseactions);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Stop", 2);
	glutAddMenuEntry("Reduce", 3);
	glutAddMenuEntry("Reset", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutIdleFunc(translatepoint);
	glutMainLoop();
}