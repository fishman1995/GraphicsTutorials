#include"Renderer.h"

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
	triangle = Mesh::GenerateTriangle();
	matrixShader = new Shader("MatrixVertex.glsl", "colourFragment.glsl");

	if (!matrixShader->LoadSuccess()) {
		return;
	}

	init = true;

	SwitchToOrthographic();
}

Renderer::~Renderer(void) {
	delete triangle;
	delete matrixShader;
}

void Renderer::SwitchToPerspective() {
	////param1&2: 近处和远处的Z; param3: 长宽比(aspect ratio), param4: 水平视野(horizontal field)
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);
}

void Renderer::SwitchToOrthographic() {
	////顺序是后、前、右、左、上、下
	projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f); //顺序是后、前、右、左、上、下
}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	BindShader(matrixShader);
	//更新着色器的矩阵统一变量, param1: 变量名称; param2: 更新多少个矩阵; param3: 矩阵是否应该被转置; param4: 第四个参数是指向矩阵数据的指针
	glUniformMatrix4fv(glGetUniformLocation(matrixShader->GetProgram(), "projMatrix"), 1, false, projMatrix.values);
	glUniformMatrix4fv(glGetUniformLocation(matrixShader->GetProgram(), "viewMatrix"), 1, false, viewMatrix.values);

	for (int i = 0; i < 3; ++i) {
		Vector3 tempPos = position;
		tempPos.z += (i * 500.0f);
		tempPos.x -= (i * 100.0f);
		tempPos.y -= (i * 100.0f);
		//将多个矩阵相乘
		modelMatrix = Matrix4::Translation(tempPos) * Matrix4::Rotation(rotation, Vector3(0, 1, 0)) * Matrix4::Scale(Vector3(scale, scale, scale));
		
		glUniformMatrix4fv(glGetUniformLocation(matrixShader->GetProgram(), "modelMatrix"), 1, false, modelMatrix.values);
		triangle->Draw();
	}
}