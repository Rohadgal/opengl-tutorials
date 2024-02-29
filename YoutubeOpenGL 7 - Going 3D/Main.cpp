//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------
#include <vector>

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


const unsigned int width = 800;
const unsigned int height = 800;


struct cube_rotate {

	GLfloat angle, x, y, z;

};

GLfloat angle;
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k, gap, gap_crement;
cube_rotate cube_rotations[3][3][3];
//vector<cube_rotate> cube_rotations[3][3][3];

void apply_rotation(GLfloat angle) {

	cube_rotate face[3][3];
	int index;
	cube_rotate rotation = cube_rotate();

	// copy face to be rotated
	// apply rotation to face
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {

			index = 2 - j % 3;

			if (x_0 == x_k) {
				rotation = { angle, 1.0, 0.0, 0.0 };
				face[index][i] = cube_rotations[x_k][i][j];
			}

			if (y_0 == y_k) {
				rotation = { angle, 0.0, 1.0, 0.0 };
				face[index][i] = cube_rotations[j][y_k][i];
			}

			if (z_0 == z_k) {
				rotation = { -1 * angle, 0.0, 0.0, 1.0 };
				face[index][i] = cube_rotations[j][i][z_k];
			}

			face[index][i] = rotation;

		}

	// copy back rotated face
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {

			if (x_0 == x_k)
				cube_rotations[x_k][i][j] = face[i][j];

			if (y_0 == y_k)
				cube_rotations[j][y_k][i] = face[i][j];

			if (z_0 == z_k)
				cube_rotations[j][i][z_k] = face[i][j];
		}

}

// reset face selection parameters
void reset_selected_face() {

	x_0 = 0;
	x_k = 2;
	y_0 = 0;
	y_k = 2;
	z_0 = 0;
	z_k = 2;

}

// keyboard function callback
void keyboard_func(unsigned char key, int x, int y) {

	switch (key) {

	case '+':
		gap += gap_crement;
		break;

	case '-':
		gap -= gap_crement;
		break;
		// view rotation
		// INcrement or DEcrement
	case 'L': // right
	case 'l':
		rot_y = (rot_y - crement) % 360;
		break;

	case 'J': // left
	case 'j':
		rot_y = (rot_y + crement) % 360;
		break;

	case 'I': // down
	case 'i':
		rot_x = (rot_x + crement) % 360;
		break;

	case 'K': // up
	case 'k':
		rot_x = (rot_x - crement) % 360;
		break;
		// end of view rotation

		// cube movements

		// select cube face
		// x-axis faces
	case 'Q':
	case 'q':
		reset_selected_face();
		x_0 = 0;
		x_k = 0;
		break;

	case 'W':
	case 'w':
		reset_selected_face();
		x_0 = 1;
		x_k = 1;
		break;

	case 'E':
	case 'e':
		reset_selected_face();
		x_0 = 2;
		x_k = 2;
		break;

		// y-axis faces
	case 'A':
	case 'a':
		reset_selected_face();
		y_0 = 0;
		y_k = 0;
		break;

	case 'S':
	case 's':
		reset_selected_face();
		y_0 = 1;
		y_k = 1;
		break;

	case 'D':
	case 'd':
		reset_selected_face();
		y_0 = 2;
		y_k = 2;
		break;

		// z-axis faces
	case 'C':
	case 'c':
		reset_selected_face();
		z_0 = 0;
		z_k = 0;
		break;

	case 'X':
	case 'x':
		reset_selected_face();
		z_0 = 1;
		z_k = 1;
		break;

	case 'Z':
	case 'z':
		reset_selected_face();
		z_0 = 2;
		z_k = 2;
		break;

		// move selected face
	case 'U': // counter-clockwise
	case 'u':
		apply_rotation(-90);
		break;

	case 'O': // clockwise
	case 'o':
		apply_rotation(90);
		break;

		// end of cube movements

	default:
		break;

	}
}

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.25f,  //1  // *4
	-0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	0.75f, 0.25f, // 3
	 0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	0.5f, 0.25f, //2
	 0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.25f, 0.25f,  // 1  //2

	-0.5f, 0.5f, 0.5f,     0.92f, 0.86f, 0.76f,		0.0f, 0.5f,  // 1 //*4
	-0.5f, 0.5f, -0.5f,		0.83f, 0.70f, 0.44f,	0.75f, 0.5f, // 3
	0.5f, 0.5f, -0.5f,		0.83f, 0.70f, 0.44f,	0.5f, 0.5f,  //2
	0.5f, 0.5f, 0.5f,		0.83f, 0.70f, 0.44f,	0.25f, 0.5f,  // 1 //2

	-0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.25f,
	-0.5f, 0.5f, 0.5f,     0.92f, 0.86f, 0.76f,		1.0f, 0.5f,
	0.5f, 0.5f, 0.5f,		0.83f, 0.70f, 0.44f,	0.5f, 0.75f,   // 7  *6
	-0.5f, 0.5f, 0.5f,     0.92f, 0.86f, 0.76f,		0.75f, 0.75f,  // 4  *6
	-0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.75f, 0.0f,  //0  *5
	 0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.5f, 0.0f,  // 3  *5
};

// Indices for vertices order
GLuint indices[] =
{
	12, 1, 2,  // bottom
	12, 2, 13,
	8, 1, 9, //
	1, 5, 9, //
	2, 1, 5,
	2, 5, 6,
	2, 3, 7,
	2, 7, 6,
	3, 0, 4,
	3, 4, 7,
	10, 11, 5, // top
	10, 5, 6  // top
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/YoutubeOpenGL 7 - Going 3D/";

	// Texture
	Texture brickTex((parentDir + texPath + "dice.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	/*Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);*/

	// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	float j = 0.0f;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 model2 = glm::mat4(1.0f);
		glm::mat4 model3 = glm::mat4(1.0f);
		glm::mat4 model4 = glm::mat4(1.0f);
		glm::mat4 model5 = glm::mat4(1.0f);
		glm::mat4 model6 = glm::mat4(1.0f);
		glm::mat4 model7 = glm::mat4(1.0f);
		glm::mat4 model8 = glm::mat4(1.0f);


		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 0.0f));

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f));
		model2 = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model3 = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model4 = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
		model5 = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		model6 = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		model7 = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
		model8 = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -25.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");  // ID

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model5));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model6));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model7));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model8));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		
		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

// Rendering Multiple Objects in OpenGL - The Cherno
// https://stackoverflow.com/questions/9503866/how-do-i-display-2-or-more-objects-in-opengl-model-view-projection-matrices