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

using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;

bool keyPressed = false;
//
//
struct cube_rotate {

	GLfloat angle, x, y, z;

};
//
GLfloat angle;
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k, gap, gap_crement;
cube_rotate cube_rotations[3][3][3];
//vector<cube_rotate> cube_rotations[3][3][3];

int spinRowOne, spinRowTwo, spinRowThree,
spinColOne, spinColTwo, spinColThree,
spinDepOne, spinDepTwo, spinDepThree;

bool rowOnePressed, rowTwoPressed, rowThreePressed,
colOnePressed, colTwoPressed, colThreePressed,
depthOnePressed, depthTwoPressed, depthThreePressed;

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
				rotation = { angle, 1.0, 0.0, 0.0 };  // guardar rotación en eje x
				face[index][i] = cube_rotations[x_k][i][j];
			}

			if (y_0 == y_k) {
				rotation = { angle, 0.0, 1.0, 0.0 };  // guardar rotación en eje y
				face[index][i] = cube_rotations[j][y_k][i];
			}

			if (z_0 == z_k) {
				rotation = { -1 * angle, 0.0, 0.0, 1.0 };  // gaurdar rotación en eje z
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

glm::mat4 modelCopy[27] = {
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),

			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),

			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
};

// reset face selection parameters
void reset_selected_face() {

	x_0 = 0;
	x_k = 2;
	y_0 = 0;
	y_k = 2;
	z_0 = 0;
	z_k = 2;

}




//void rotateCube(size_t _i, size_t _j, size_t _k, glm::mat4& _model) {
//	if (rowOnePressed && _j == 0) { // Q
//		_model =  glm::rotate(_model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
//
//	}
//	if (rowTwoPressed) {
//		if (_j == 1) {
//
//		}
//	}
//	if (rowThreePressed) {
//		if (_j == 2) {
//
//		}
//	}
//	if (colOnePressed) {
//		if (_i == 0) {
//
//		}
//	}
//	if (colTwoPressed) {
//		if (_i == 1) {
//
//		}
//	}
//	if (colThreePressed) {
//		if (_i == 2) {
//
//		}
//	}
//	if (depthOnePressed) {
//		if (_k == 0) {
//
//		}
//	}
//	if (depthTwoPressed) {
//		if (_k == 1) {
//
//		}
//	}
//	if (depthThreePressed) {
//		if (_k == 2) {
//
//		}
//	}
//}


float qRotation = 0.0f, aRotation = 0.0f, zRotation = 0.0f, wRotation = 0.0f;;
void keyboard_func(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_Q:
			if (action == GLFW_PRESS && !keyPressed) {
            qRotation += 90.0f;
            keyPressed = true;
			//rowOnePressed = true;
        } else if (action == GLFW_RELEASE) {
            keyPressed = false;
		//	rowOnePressed = false;
        }
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS && !keyPressed) {
				aRotation += 90.0f;
				keyPressed = true;
			} else if (action == GLFW_RELEASE) {
				keyPressed = false;
			}
			break;
		case GLFW_KEY_Z:
			if (action == GLFW_PRESS && !keyPressed) {
				zRotation += 90.0f;
				keyPressed = true;
			}
			else if (action == GLFW_RELEASE) {
				keyPressed = false;
			}
			break;
		case GLFW_KEY_W:
			if (action == GLFW_PRESS && !keyPressed) {
				wRotation += 90.0f;
				keyPressed = true;
			}
			else if (action == GLFW_RELEASE) {
				keyPressed = false;
			}
			break;
		case GLFW_KEY_I:
			rot_x = (rot_x + crement) % 360;
			break;
		case GLFW_KEY_K:
			rot_x = (rot_x - crement) % 360;
			break;
		case GLFW_KEY_U:
			apply_rotation(-90);
			break;
		case GLFW_KEY_O:
			apply_rotation(90);
			break;
		}
	//}
}
// Vertices coordinates
GLfloat vertices[] =
{ 
#pragma region FirstCube
	//     COORDINATES     /        COLORS      /   TexCoord  //
	- 0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.25f,  //1  // *4
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
#pragma endregion

	
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
	
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	float j = 0.0f;
	// Main while loop

	glfwSetKeyCallback(window, keyboard_func);

	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		/*double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}*/


		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -25.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");  // ID
		// Initializes matrices so they are not the null matrix



		glm::mat4 model[27] = {
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),

			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),

			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
			glm::mat4(1.0f),
		};

		
		

		/*if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			rotation += 1.0f;
			keyPressed = true;
		}*/


		GLint it = 0;
		
		//model[0] = glm::rotate(model[0], glm::radians(rotation), glm::vec3(1.0f, 1.0f, 0.0f));
		
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if ( j == -1) {
						model[it] = glm::rotate(model[it], glm::radians(qRotation), glm::vec3(0.0f, 1.0f, 0.0f));
						//rotateCube(i, j, k, model[it]);
					}
					if (j == 0) {
						model[it] = glm::rotate(model[it], glm::radians(aRotation), glm::vec3(0.0f, 1.0f, 0.0f));
					}
					if (j == 1) {
						model[it] = glm::rotate(model[it], glm::radians(zRotation), glm::vec3(0.0f, 1.0f, 0.0f));
					}
					
					

						//keyPressed = false;
					//}
					model[it] = glm::translate(model[it], glm::vec3(k, j, i));
					//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[it]));
					//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
					// 
					//modelCopy[it] =  proj * model[it] * view;
					
					//cout<< modelCopy[2][2].z << endl;
					it++;
				}
			}
		}

		it = 0;

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
				
					modelCopy[it] = model[it];
					//keyPressed = false;
					
					//model[it] = glm::translate(model[it], glm::vec3(k, j, i));
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCopy[it]));
					glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
					//modelCopy[it] =  proj * model[it] * view;

					//cout<< modelCopy[2][2].z << endl;
					it++;
				}
			}
		}

		// Assigns different transformations to each matrix



		//// Outputs the matrices into the Vertex Shader
		//int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");  // ID

		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

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