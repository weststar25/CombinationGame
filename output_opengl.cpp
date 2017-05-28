#pragma once
#include"output_opengl.h"

double x = 0, y = 0, z = 0;
iArg *eArgp;

GLubyte color[10][3] = {
	{ 0, 0, 0 }, // ������ ����1
	{ 55, 95, 145 }, // �����񽺹��� ����2
	{ 255, 0, 100 }, // ����ũ ����3
	{ 255, 255, 255 }, // ��� ���1
	{ 255, 200, 15 }, // ����� ���2
	{ 240, 124, 180 }, // ���ֻ� ���3
	/*   {255,0,0}, // 0 ���� ����1
	{0,0,255}, // 1 �Ķ� ����2
	{255,228,0}, // 2 ��� ����3
	{255,255,255}, // 3 �Ͼ� ���1
	{189,189,189}, // 4 ȸ�� ���2
	{0,0,0}, // 5 ���� ���3
	{217,65,197}, // 6 Ŀ������
	{240,124,180}, // 7 Ÿ�̸ӻ��� */
	{ 0, 0, 255 }, // �Ķ��� Ŀ������
	{ 100, 70, 70 },   // ���� Ÿ�̸� ��
	{ 45, 180, 0 },   // 8 ���(�� ��ư ����)
	{ 180, 125, 85 }   // ���Ѱ��� Ÿ�̸� ��
};

// �׸���
static void draw(void)
{
	int i, j, k;
	int num = 0;
	/* glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); */
	glClear(GL_COLOR_BUFFER_BIT);                           //�÷����� ���� Ȱ��ȭ�� ���� �����(�ּ�ó��=>���)

	glColor3f(1.0, 1.0, 1.0);                              //����� �����ΰ�?

	// card[3].setSelect(1); //�׽�Ʈ

	for (i = 0; i<3; i++)                                       //ī�� �׸���
	{
		y = i*(-1.15);
		for (j = 0; j<3; j++)
		{
			x = j*1.15;
			glPushMatrix();                                 //��� �׸� �����
			glTranslatef(-1.5 + x, 1.5 + y, 1.5 + z);
			if (eArgp->hapEDa == 1 && eArgp->cList[num].getSelect() == 1){   //���� ��� ������
				glRotatef(Angle, 0.0, 0.0, 1.0);
			}
			else if (eArgp->cList[num].getSelect() == 1) {               //���ý� ������
				glRotatef(Angle, 0.0, 1.0, 0.0);
				//cout << card[8].getSelect() << endl;
			}
			if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
				glBindTexture(GL_TEXTURE_2D, TexObj[0]); // �̰� �Ű澲�� x
#endif
			}
			else {
				//glCallList(TexObj[card[num][2]]);         //���ٲٱ�
				glCallList(TexObj[eArgp->cList[num].getShape() * 9 + eArgp->cList[num].getColor() * 3 + eArgp->cList[num].getBgColor()]);
			}
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex2f(-0.5, -0.5);
			glTexCoord2f(1.0, 0.0);
			glVertex2f(0.5, -0.5);
			glTexCoord2f(1.0, 1.0);
			glVertex2f(0.5, 0.5);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(-0.5, 0.5);
			glEnd();
			glPopMatrix();
			num++;
			if (num >= 9){
				num = 0;
			}
		}
	}

	/* draw '��' polygon */
	glPushMatrix();
	glTranslatef(-1.5, 1.5 + y - 0.65, 1.5);
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[8]);
#endif
	}
	else {
		glCallList(TexObj[27]);
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);      glVertex2f(-0.5, -0.55);
	glTexCoord2f(1.0, 0.0);      glVertex2f(2.8, -0.55);
	glTexCoord2f(1.0, 1.0);      glVertex2f(2.8, 0.0);
	glTexCoord2f(0.0, 1.0);      glVertex2f(-0.5, 0.0);
	/*glTexCoord2f(0.0, 0.0);      glVertex2f(-0.5, -0.55);
	glTexCoord2f(1.0, 0.0);      glVertex2f(1.15, -0.55);
	glTexCoord2f(1.0, 1.0);      glVertex2f(1.15, 0.0);
	glTexCoord2f(0.0, 1.0);      glVertex2f(-0.5, 0.0);*/

	glEnd();
	glPopMatrix();

	/* draw timer(outside) polygon */
	glPushMatrix();
	glTranslatef(1.75, 0.0, 1.5);
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[8]);
#endif
	}
	else {
		glCallList(TexObj[29]);
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);   glVertex2f(-0.22, -2.0);
	glTexCoord2f(1.0, 0.0);   glVertex2f(0.22, -2.0);
	glTexCoord2f(1.0, 1.0);   glVertex2f(0.22, 2.0);
	glTexCoord2f(0.0, 1.0);   glVertex2f(-0.22, 2.0);
	glEnd();
	glPopMatrix();

	/* draw timer(inside) polygon */
	glPushMatrix();
	glTranslatef(1.75, 0.0, 1.5);
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[8]);
#endif
	}
	else {
		glCallList(TexObj[30]);
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);   glVertex2f(-0.15, -1.9);
	glTexCoord2f(1.0, 0.0);   glVertex2f(0.15, -1.9);
	glTexCoord2f(1.0, 1.0);   glVertex2f(0.15, 1.9 - (eArgp->time * 0.025));
	glTexCoord2f(0.0, 1.0);   glVertex2f(-0.15, 1.9 - (eArgp->time * 0.025));
	glEnd();
	glPopMatrix();

	/* draw cursor polygon */
	glPushMatrix();
	glTranslatef((eArgp->center.x - 320)*0.0081875, (240 - eArgp->center.y)*0.010583, 1.0);
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[8]);
#endif
	}
	else {
		glCallList(TexObj[28]);
	}
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(-0.05, -0.05);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(0.05, -0.05);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(0.05, 0.05);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-0.05, 0.05);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}
static void idle(void)
{
	Angle += 0.8;            //ȸ�� �ӵ�
	glutPostRedisplay();
	//   
	//
}

static void reshape(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 6.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -8.0);
}

// �ʱ�ȭ
static void init(void)
{
	static int width = 8, height = 8;
	int choice = 0;
	static GLubyte tex1[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	static GLubyte tex2[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	static GLubyte tex3[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	static GLubyte tex4[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1
	};

	static GLubyte tex5[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};

	GLubyte tex[64][3];
	GLint i, j;

	//glClearColor(0.557, 0.941, 0.984, 1.0);      //����
	glClearColor(0.961, 0.863, 0.510, 1.0);      //����
	glDisable(GL_DITHER);

	/* Setup texturing */
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

	/* generate texture object IDs */
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glGenTextures(31, TexObj);
#endif
	}
	else {
		TexObj[0] = glGenLists(31);
		TexObj[1] = TexObj[0] + 1;
		TexObj[2] = TexObj[1] + 1;
		TexObj[3] = TexObj[2] + 1;
		TexObj[4] = TexObj[3] + 1;
		TexObj[5] = TexObj[4] + 1;
		TexObj[6] = TexObj[5] + 1;
		TexObj[7] = TexObj[6] + 1;
		TexObj[8] = TexObj[7] + 1;
		TexObj[9] = TexObj[8] + 1;
		TexObj[10] = TexObj[9] + 1;
		TexObj[11] = TexObj[10] + 1;
		TexObj[12] = TexObj[11] + 1;
		TexObj[13] = TexObj[12] + 1;
		TexObj[14] = TexObj[13] + 1;
		TexObj[15] = TexObj[14] + 1;
		TexObj[16] = TexObj[15] + 1;
		TexObj[17] = TexObj[16] + 1;
		TexObj[18] = TexObj[17] + 1;
		TexObj[19] = TexObj[18] + 1;
		TexObj[20] = TexObj[19] + 1;
		TexObj[21] = TexObj[20] + 1;
		TexObj[22] = TexObj[21] + 1;
		TexObj[23] = TexObj[22] + 1;
		TexObj[24] = TexObj[23] + 1;
		TexObj[25] = TexObj[24] + 1;
		TexObj[26] = TexObj[25] + 1;
		TexObj[27] = TexObj[26] + 1;
		TexObj[28] = TexObj[27] + 1;
		TexObj[29] = TexObj[28] + 1;
		TexObj[30] = TexObj[29] + 1;
	}

	for (int a = 0; a<3; a++)
	{
		for (int b = 0; b<3; b++)
		{
			/* setup first texture object */
			if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
				glBindTexture(GL_TEXTURE_2D, TexObj[0]); //�Ű� x
#endif
			}
			else {
				glNewList(TexObj[0 + a * 3 + b], GL_COMPILE);
			}
			for (i = 0; i < height; i++) {
				for (j = 0; j < width; j++) {
					int p = i * width + j;
					if (tex1[(height - i - 1) * width + j]) {
						memcpy(tex[p], color[a], sizeof(GLubyte)* 3);
					}
					else {
						memcpy(tex[p], color[b + 3], sizeof(GLubyte)* 3);
					}
				}
			}
			glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (!HaveTexObj) {
				glEndList();
			}
			/* end of texture object */

			/* setup second texture object */
			if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
				glBindTexture(GL_TEXTURE_2D, TexObj[1]);
#endif
			}
			else {
				glNewList(TexObj[9 + a * 3 + b], GL_COMPILE);
			}
			/* green on blue */
			for (i = 0; i < height; i++) {
				for (j = 0; j < width; j++) {
					int p = i * width + j;
					if (tex2[(height - i - 1) * width + j]) {
						memcpy(tex[p], color[a], sizeof(GLubyte)* 3);
					}
					else {
						memcpy(tex[p], color[b + 3], sizeof(GLubyte)* 3);
					}
				}
			}
			glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (!HaveTexObj) {
				glEndList();
			}
			/* end texture object */

			/* setup 3 texture object */
			if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
				glBindTexture(GL_TEXTURE_2D, TexObj[2]);
#endif
			}
			else {
				glNewList(TexObj[18 + a * 3 + b], GL_COMPILE);
			}
			/* red on white */
			for (i = 0; i < height; i++) {
				for (j = 0; j < width; j++) {
					int p = i * width + j;
					if (tex3[(height - i - 1) * width + j]) {
						memcpy(tex[p], color[a], sizeof(GLubyte)* 3);

					}
					else {
						memcpy(tex[p], color[b + 3], sizeof(GLubyte)* 3);
					}
				}
			}
			glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (!HaveTexObj) {
				glEndList();
			}
			/* end of texture object */
		}
	}


	/* setup '��' texture object */
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[1]);
#endif
	}
	else {
		glNewList(TexObj[27], GL_COMPILE);
	}
	/* green on blue */
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int p = i * width + j;
			if (tex4[(height - i - 1) * width + j]) {
				memcpy(tex[p], color[3], sizeof(GLubyte)* 3);      //���ư ����κ�
			}
			else {
				memcpy(tex[p], color[8], sizeof(GLubyte)* 3);      //���ư ����κ�
			}
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (!HaveTexObj) {
		glEndList();
	}
	/* end texture object */

	/* setup cursor texture object */
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[1]);
#endif
	}
	else {
		glNewList(TexObj[28], GL_COMPILE);
	}
	/* green on blue */
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int p = i * width + j;
			if (tex5[(height - i - 1) * width + j]) {
				memcpy(tex[p], color[6], sizeof(GLubyte)* 3);
				/* tex[p][0]=0;
				tex[p][0]=255;
				tex[p][0]=0;*/
			}
			else {
				memcpy(tex[p], color[6], sizeof(GLubyte)* 3);
			}
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (!HaveTexObj) {
		glEndList();
	}
	/* end texture object */

	/* setup timer(outside) texture object */
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[1]);
#endif
	}
	else {
		glNewList(TexObj[29], GL_COMPILE);
	}
	/* green on blue */
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int p = i * width + j;
			if (tex5[(height - i - 1) * width + j]) {
				memcpy(tex[p], color[7], sizeof(GLubyte)* 3);
			}
			else {
				memcpy(tex[p], color[7], sizeof(GLubyte)* 3);
			}
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (!HaveTexObj) {
		glEndList();
	}
	/* end texture object */


	/* setup timer(inside) texture object */
	if (HaveTexObj) {
#ifdef TEXTURE_OBJECT
		glBindTexture(GL_TEXTURE_2D, TexObj[1]);
#endif
	}
	else {
		glNewList(TexObj[30], GL_COMPILE);
	}
	/* green on blue */
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int p = i * width + j;
			if (tex5[(height - i - 1) * width + j]) {
				memcpy(tex[p], color[9], sizeof(GLubyte)* 3);
			}
			else {
				memcpy(tex[p], color[9], sizeof(GLubyte)* 3);
			}
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (!HaveTexObj) {
		glEndList();
	}
	/* end texture object */
}
void visible(int vis)
{
	if (vis == GLUT_VISIBLE)
	{
		glutIdleFunc(idle);
	}
	else
	{
		glutIdleFunc(NULL);
	}

}

// ���
int output(iArg *ap)
{
	glutInit(&(ap->oArgc), ap->oArgv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 640); //������������
	glutCreateWindow("���հ���");

	/* check that renderer has the GL_EXT_texture_object
	extension * or supports OpenGL 1.1 */
#ifdef TEXTURE_OBJECT
	{
		char *exten = (char *)glGetString(GL_EXTENSIONS);
		char *version = (char *)glGetString(GL_VERSION);
		if (strstr(exten, "GL_EXT_texture_object")
			|| strncmp(version, "1.1", 3) == 0) {
				HaveTexObj = GL_TRUE;
		}
	}
#endif


	init();

	glutVisibilityFunc(visible);

	glutDisplayFunc(draw);

	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;             /* ANSI C requires main to return int. */
}