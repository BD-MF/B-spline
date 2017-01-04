#include <stdlib.h>
#include <glut.h>
#include <iostream>
using namespace std;
// input arguments
const int g_n = 8;  // ���Ƶ����Ϊn+1
int g_p = 3;  // ���߽���
int g_m = 12;  // m+1���ڵ�
//GLfloat g_U[] = { 0, 0.10, 0.20, 0.25, 0.30, 0.40, 
//				0.50, 0.60,  0.70, 0.75, 0.80, 0.90, 1.0 };
GLfloat g_U[] = { 0, 0, 0, 0, 0.10,  0.30,
0.50, 0.75,  0.80,  1.0 ,1.0, 1.0, 1.0 };
// ���Ƶ�
GLfloat g_CP[] = {
	-0.5, -0.5,
	-0.8, -0.1,
	-0.4, 0.5,
	-0.1,0.6,
	0.3, 0.4,
	0.5, 0.25,
	0.7, 0.0,
	0.8, -0.2,
	0.3, -0.4


};
float N[20];

// �ҳ�һ��������u�����ĸ��ڵ�����[uk,u(k+1)). ����k
int findRange(float u, int m) {
	int k = -1;
	for (int i = 0; i < m; i++) {
		if (u >= g_U[i] && u < g_U[i + 1])
			return i;
	}
	return k;
}

// ��������u��Ӧ��ϵ��
/*
	n: n+1�����Ƶ�
	p: ����
	m: m+1���ڵ�
	u: ��ֵ����
	U: �ڵ�����
	N: �����������ϵ����N�ĳ���ΪN+1
*/
void baseFun(int n, int p, int m, float u)
{
	// ��ʼ��N[0...n]Ϊ0
	for (int i = 0; i <= n; i++) {
		N[i] = 0;
	}
	// �ų�����
	if (u == g_U[0]) {
		N[0] = 1.0;
		return;
	}
	else if (u == g_U[m]) {
		N[n] = 1.0;
		return;
	}

	// ����u��u0��um֮��
	int k = findRange(u, m);
	N[k] = 1.0;  //0��ϵ��

	// ������1��p
	for (int d = 1; d <= p; d++) {
		N[k - d] = ((g_U[k+1] - u) / (g_U[k + 1] - g_U[(k - d) + 1])) * N[(k - d) + 1];
		cout << N[k - d] << " ";
		
		for (int i = k - d + 1; i <= k - 1; i++) {
			N[i] = ((u - g_U[i]) / (g_U[i + d] - g_U[i])) * N[i] + ((g_U[i + d + 1] - u) / (g_U[i + d + 1] - g_U[i + 1])) * N[i + 1];
			cout << N[i] << " ";
		}
		N[k] = ((u - g_U[k]) / (g_U[k + d] - g_U[k])) * N[k];
		cout << N[k] << " " << endl;
		cout << "------" << d << "��" << endl;
	}
}


// ��� ����u��Ӧ������
void cu(float u, int n, int p, int m, float* result) {
	float cu[] = { 0, 0 };
	// �������
	//float N[g_n+1];
	
	baseFun(n, p, m, u);
	//TEST
	cout << "���N" << endl;
	for (int i = 0; i <= n; i++) {
		cout << N[i] << " " << endl;
	}
	cout << "--------" << endl;
	for (int i = 0; i <= n; i++) {
		float x = N[i] * g_CP[2*i];
		float y = N[i] * g_CP[2*i+1];
		cu[0] += x;
		cu[1] += y;
	}
	result[0] = cu[0];
	result[1] = cu[1];
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, g_CP);
	glPointSize(2);
	glColor3d(255, 0, 0);
	//glBegin(GL_POINTS);
	glDrawArrays(GL_LINE_STRIP, 0, g_n + 1);
	//glEnd();

	float u;
	glColor3d(0, 255, 0);
	glBegin(GL_LINE_STRIP);
	glPointSize(3);
	for (int i = 0; i <= 100; i++) {
		u = i / 100.0;
		GLfloat point[2];
		cu(u, g_n, g_p, g_m, point);
		
		glVertex2f(point[0], point[1]);
		//cout << point[0] << point[1] << endl;
	}
	glEnd();

	//glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("��һ��OpenGL����");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}