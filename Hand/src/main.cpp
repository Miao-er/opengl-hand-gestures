


#define _CRT_SECURE_NO_WARNINGS

#define DIFFUSE_TEXTURE_MAPPING

#include "gl_env.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include<string>
#include<map>
#include<vector>
#include<direct.h>

#ifndef M_PI
#define M_PI (3.1415926535897932)
#endif

#include <iostream>

#include "skeletal_mesh.h"
#include "shaders/shader.h"
#include "stb_image.h"
#include <glm\gtc\matrix_transform.hpp>

char ABSO_PATH[1024];
struct Vertices {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texcoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
}norm_vertices[36];
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
void computeTangentBasis() {
	for (int i = 0; i < 36; i+=3)
	{
		norm_vertices[i].pos = glm::vec3(vertices[8*i],vertices[8*i+1],vertices[8*i+2]);
		norm_vertices[i].normal = glm::vec3(vertices[8 * i +3], vertices[8 * i + 4], vertices[8 * i + 5]);
		norm_vertices[i].texcoord = glm::vec2(vertices[8 * i + 6], vertices[8 * i + 7]);
		norm_vertices[i+1].pos = glm::vec3(vertices[8 * (i+1)], vertices[8 * (i + 1) + 1], vertices[8 * (i + 1) + 2]);
		norm_vertices[i + 1].normal = glm::vec3(vertices[8 * (i + 1) + 3], vertices[8 * (i + 1) + 4], vertices[8 * (i + 1) + 5]);
		norm_vertices[i+1].texcoord = glm::vec2(vertices[8 * (i+1) + 6], vertices[8 * (i+1) + 7]);
		norm_vertices[i + 2].pos = glm::vec3(vertices[8 * (i + 2)], vertices[8 * (i + 2) + 1], vertices[8 * (i + 2) + 2]);
		norm_vertices[i + 2].normal = glm::vec3(vertices[8 * (i + 2)+3], vertices[8 * (i + 2) + 4], vertices[8 * (i + 2) + 5]);
		norm_vertices[i+2].texcoord = glm::vec2(vertices[8 * (i+2) + 6], vertices[8 * (i+2) + 7]);
		glm::vec3 deltaPos1 = norm_vertices[i+1].pos - norm_vertices[i].pos;
		glm::vec3 deltaPos2 = norm_vertices[i + 2].pos - norm_vertices[i].pos;
		glm::vec2 deltaUV1 = norm_vertices[i + 1].texcoord - norm_vertices[i].texcoord;
		glm::vec2 deltaUV2 = norm_vertices[i + 2].texcoord - norm_vertices[i].texcoord;
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		norm_vertices[i].tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		norm_vertices[i+1].tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		norm_vertices[i+2].tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		norm_vertices[i].bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
		norm_vertices[i+1].bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
		norm_vertices[i+2].bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
		//norm_vertices[i].normal = glm::normalize(glm::cross(norm_vertices[i].tangent, norm_vertices[i].bitangent));
		//norm_vertices[i+1].normal = glm::normalize(glm::cross(norm_vertices[i+1].tangent, norm_vertices[i+1].bitangent));
		//norm_vertices[i+2].normal = glm::normalize(glm::cross(norm_vertices[i+2].tangent, norm_vertices[i+2].bitangent));
	}
}
float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};
glm::vec3 cubePositions[] = {
	   glm::vec3(30.0f,  0.0f,  10.0f),
	   glm::vec3(10.0f,  15.0f, -15.0f),
	   glm::vec3(-15.f, -22.f, -25.f),
	   glm::vec3(-3.8f, -20.f, -12.3f),
	   glm::vec3(2.4f, -4.f, -3.5f),
	   glm::vec3(-17.f,  3.0f, -7.5f),
	   glm::vec3(13.f, -2.0f, -25.f),
	   glm::vec3(15.f,  20.f, -2.5f),
	   glm::vec3(15.f,  0.2f, -15.f),
	   glm::vec3(-13.f,  10.f, -15.f)
};
std::vector<std::string>sky_box_faces =
{
	/*"\\src\\textures\\skybox\\right.jpg",
	"\\src\\textures\\skybox\\left.jpg",
	"\\src\\textures\\skybox\\top.jpg",
	"\\src\\textures\\skybox\\bottom.jpg",
	"\\src\\textures\\skybox\\front.jpg",
	"\\src\\textures\\skybox\\back.jpg"*/
	"\\src\\textures\\night\\posx.jpg",
	"\\src\\textures\\night\\negx.jpg",
	"\\src\\textures\\night\\posy.jpg",
	"\\src\\textures\\night\\negy.jpg",
	"\\src\\textures\\night\\posz.jpg",
	"\\src\\textures\\night\\negz.jpg",
};
unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(((std::string)ABSO_PATH+faces[i]).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
GLuint load_light()
{
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	return VAO;
}
GLuint load_box()
{
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(norm_vertices), norm_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
	return VAO;
}
GLuint load_sky()
{
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	return skyboxVAO;
}

/*pre code begin*/
#define JOINT_NUM 16
std::string str_hand[JOINT_NUM] = { "metacarpals",
"thumb_proximal_phalange","thumb_intermediate_phalange","thumb_distal_phalange",
"index_proximal_phalange","index_intermediate_phalange","index_distal_phalange",
"middle_proximal_phalange","middle_intermediate_phalange","middle_distal_phalange",
"ring_proximal_phalange","ring_intermediate_phalange","ring_distal_phalange",
"pinky_proximal_phalange","pinky_intermediate_phalange","pinky_distal_phalange" };
std::string str_bend_labels[JOINT_NUM];
std::string str_swing_labels[JOINT_NUM];
#define radian(angle) (angle*M_PI/180)

struct Angles
{
	std::map<std::string, float> angle_list;
	Angles(float metacarpals,
		float thumb_b,float thumb_m,float thumb_e,
		float index_b, float index_m, float index_e,
		float middle_b, float middle_m, float middle_e,
		float ring_b, float ring_m, float ring_e,
		float pinky_b, float pinky_m, float pinky_e
		)
	{
		angle_list[str_hand[0]] = metacarpals;
		angle_list[str_hand[1]] = thumb_b;
		angle_list[str_hand[2]] = thumb_m;
		angle_list[str_hand[3]] = thumb_e;
		angle_list[str_hand[4]] = index_b;
		angle_list[str_hand[5]] = index_m;
		angle_list[str_hand[6]] = index_e;
		angle_list[str_hand[7]] = middle_b;
		angle_list[str_hand[8]] = middle_m;
		angle_list[str_hand[9]] = middle_e;
		angle_list[str_hand[10]] = ring_b;
		angle_list[str_hand[11]] = ring_m;
		angle_list[str_hand[12]] = ring_e;
		angle_list[str_hand[13]] = pinky_b;
		angle_list[str_hand[14]] = pinky_m;
		angle_list[str_hand[15]] = pinky_e;
	}
	Angles() {
		for (int i = 0; i < JOINT_NUM; i++)
			angle_list[str_hand[i]] = 0;
	}
	bool operator ==(Angles angles)
	{
		for (int i = 0; i < JOINT_NUM; i++)
			if (abs(angle_list[str_hand[i]] - angles.angle_list[str_hand[i]]) >= 1e-3)
				return false;
		return true;
	}
	void step_to_target_angles(Angles target_angles, float time, float anime_speed)
	{
		for (int i = 0; i < JOINT_NUM; i++)
		{
			if (abs(angle_list[str_hand[i]] - target_angles.angle_list[str_hand[i]]) < 1e-3)
				continue;
			if (angle_list[str_hand[i]] < target_angles.angle_list[str_hand[i]])
				angle_list[str_hand[i]] += anime_speed * time;
			else angle_list[str_hand[i]] -= anime_speed * time;
		}
	}
};
struct Hand_Angles
{
	float anime_speed;
	float rotate_speed;
	bool auto_rotate;
	float metacarpal_rotate;
	Angles bend_angles;
	Angles swing_angles;
	Hand_Angles()
	{
		bend_angles = Angles();
		swing_angles = Angles();
		anime_speed = M_PI / 3;
		rotate_speed = M_PI / 2;
		auto_rotate = false;
		metacarpal_rotate = 0;
	}
	template<class T>
	void set_False(std::vector<T>& actions)
	{
		for (auto& action : actions)
			action.state = false;
	}
};
struct FixedAction
{
	std::string name;
	bool state;
	Angles bend_angles, swing_angles;
	FixedAction() {}
	FixedAction(std::string _name) {
		name = _name;
		state = false;
		bend_angles = Angles();
		swing_angles = Angles();
	}
	FixedAction(std::string _name,Angles bend,Angles swing)
	{
		name = _name;
		state = false;
		bend_angles = bend;
		swing_angles = swing;
	}
	void check(Hand_Angles& hand_angles, float time)
	{
		if (hand_angles.bend_angles == bend_angles && hand_angles.swing_angles == swing_angles)
			state = false;
		else
		{
			hand_angles.bend_angles.step_to_target_angles(bend_angles, time, hand_angles.anime_speed);
			hand_angles.swing_angles.step_to_target_angles(swing_angles, time, hand_angles.anime_speed);
		}
	}
};
struct CycleAction
{
	std::string name;
	struct Cycle_args
	{
		int index;
		float min_angle, max_angle;
		float *speed;
		int direct;
		Cycle_args(int _index, float min, float max, float* _speed, int _direct) :
			index(_index), min_angle(min), max_angle(max), speed(_speed), direct(_direct) {}
		Cycle_args(int _index, float min, float max, float _speed, int _direct) :
			index(_index), min_angle(min), max_angle(max),  direct(_direct) {
			speed = new float;
			*speed = _speed;
		}
	};
	bool state;
	FixedAction base_action;
	std::vector<Cycle_args>active_bend, active_swing;

	CycleAction(std::string _name,FixedAction _base_action)
	{
		name = _name;
		state = false;
		base_action = _base_action;
		active_bend.reserve(JOINT_NUM);
		active_bend.reserve(JOINT_NUM);
	}
	void cycle(Hand_Angles &hand_angles,float time)
	{
		for (auto& item : active_bend)
		{
			float& angle = hand_angles.bend_angles.angle_list[str_hand[item.index]];
			if (angle > item.max_angle)
				item.direct = -1;
			else if (angle < item.min_angle)
				item.direct = 1;
			angle += item.direct *  *(item.speed) * time;
		}
		for (auto& item : active_swing)
		{
			float& angle = hand_angles.swing_angles.angle_list[str_hand[item.index]];
			if (angle > item.max_angle)
				item.direct = -1;
			else if (angle < item.min_angle)
				item.direct = 1;
			angle += item.direct * *(item.speed) * time;
		}
	}
	void check(Hand_Angles& hand_angles,float time)
	{
		if (state)
			if (base_action.state) base_action.check(hand_angles,time);
			else cycle(hand_angles,time);
	}
};
/*pre code end*/
Hand_Angles hand_angles = Hand_Angles();
std::vector<FixedAction> fixed_Actions;
std::vector<FixedAction>num_Actions;
std::vector<CycleAction> cycle_Actions;
void Action_init()
{
	for (int i = 0; i < JOINT_NUM; i++)
	{
		str_bend_labels[i] = str_hand[i].substr(0, 10) + "_bend";
		str_swing_labels[i] = str_hand[i].substr(0, 10) + "_swing";
	}
	fixed_Actions.push_back(FixedAction("Reset"));
	num_Actions.push_back(FixedAction("0",
		Angles(radian(0.0),
			radian(20.0), radian(15.0), radian(45.0),
			radian(30.0), radian(75.0), radian(45.0),
			radian(30.0), radian(75.0), radian(45.0),
			radian(30.0), radian(75.0), radian(45.0),
			radian(30.0), radian(75.0), radian(45.0)),
		Angles(radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(-5.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(-10.0), radian(0.0), radian(0.0),
			radian(-15.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("1",
		Angles(radian(0.0),
			radian(20.0), radian(20.0), radian(75.0),
			radian(-12.0), radian(-12.0), radian(0.0),
			radian(90.0), radian(90.0), radian(90.0),
			radian(90.0), radian(90.0), radian(90.0),
			radian(90.0), radian(90.0), radian(90.0)),
		Angles()));
	num_Actions.push_back(FixedAction("2",
		Angles(radian(0.0),
			radian(30.0), radian(40.0), radian(45.0),
			radian(-10.0), radian(-15.0), radian(0.0),
			radian(-10.0), radian(-15.0), radian(0.0),
			radian(75.0), radian(90.0), radian(60.0),
			radian(90.0), radian(90.0), radian(90.0)),
		Angles(radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(-10.0), radian(0.0), radian(0.0),
			radian(5.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("3",
		Angles(radian(0.0),
			radian(20.0), radian(15.0), radian(45.0),
			radian(30.0), radian(75.0), radian(45.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0)),
		Angles(radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(-10.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("4",
		Angles(radian(0.0),
			radian(0.0), radian(75.0), radian(90.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0)),
		Angles(radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("5",
		Angles(radian(0.0),
			radian(-10.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0),
			radian(-15.0), radian(-15.0), radian(0.0)),
		Angles()));
	num_Actions.push_back(FixedAction("6",
		Angles(radian(0.f),
			radian(0.f), radian(0.f), radian(0.f),
			radian(90.f), radian(90.f), radian(90.f),
			radian(90.0), radian(90.0), radian(90.0),
			radian(90.0), radian(90.0), radian(90.0),
			radian(-15.f), radian(-15.0), radian(0.0)),
		Angles(radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("7",
		Angles(radian(0.0),
			radian(30.0), radian(40.0), radian(45.0),
			radian(5.0), radian(-15.0), radian(0.0),
			radian(-10.0), radian(-15.0), radian(0.0),
			radian(75.0), radian(90.0), radian(60.0),
			radian(90.0), radian(90.0), radian(90.0)),
		Angles(radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(15.0), radian(0.0), radian(0.0),
			radian(-15.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("8", Angles(radian(0.0),
		radian(-30.0), radian(0.0), radian(0.0),
		radian(-5.0), radian(-15.0), radian(0.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0)),
		Angles(radian(0.0),
			radian(30.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	num_Actions.push_back(FixedAction("9",
		Angles(radian(0.0),
			radian(20.0), radian(20.0), radian(75.0),
			radian(-15.0), radian(90.0), radian(75.0),
			radian(90.0), radian(90.0), radian(90.0),
			radian(90.0), radian(90.0), radian(90.0),
			radian(90.0), radian(90.0), radian(90.0)),
		Angles()));
	fixed_Actions.push_back(FixedAction("Thumb up", Angles(radian(0.0),
		radian(-30.0), radian(-15.0), radian(0.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0)),
		Angles(radian(90.0),
			radian(15.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	fixed_Actions.push_back(FixedAction("Direct the way", Angles(radian(90.0),
		radian(20.0), radian(20.0), radian(35.0),
		radian(-12.0), radian(-12.0), radian(0.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0)),
		num_Actions[1].swing_angles));
	fixed_Actions.push_back(FixedAction("Handgun", num_Actions[8].bend_angles,
		Angles(radian(90.0),
			radian(30.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	fixed_Actions.push_back(FixedAction("Ok", num_Actions[3].bend_angles, num_Actions[3].swing_angles));
	fixed_Actions.push_back(FixedAction("Pinch", Angles(radian(56.45),
		radian(30.0), radian(3.95), radian(17.31),
		radian(45.58), radian(13.58), radian(42.87),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0),
		radian(90.0), radian(90.0), radian(90.0)),
		Angles(radian(0.0),
			radian(-20.0), radian(0.0), radian(15.0),
			radian(-13.5), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0),
			radian(0.0), radian(0.0), radian(0.0))));
	cycle_Actions.push_back(CycleAction("Wave", fixed_Actions[0]));
	cycle_Actions[0].active_swing.push_back(CycleAction::Cycle_args(0, radian(-30.0), radian(30.0), &hand_angles.anime_speed, 1));
	cycle_Actions.push_back(CycleAction("No", num_Actions[1]));
	cycle_Actions[1].active_swing.push_back(CycleAction::Cycle_args(4, radian(-10.0), radian(10.0), &hand_angles.anime_speed, 1));
	cycle_Actions.push_back(CycleAction("rabbit", num_Actions[2]));
	for (int i = 1; i <= 2; i++)
	{
		cycle_Actions[2].active_bend.push_back(CycleAction::Cycle_args(3 * i + 2, radian(-15.f), radian(80.0), M_PI, 1));
		cycle_Actions[2].active_bend.push_back(CycleAction::Cycle_args(3 * i + 3, radian(-15.f), radian(80.0), M_PI, 1));
	}
}
static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char* argv[])
{
	GLFWwindow* window;
	_getcwd(ABSO_PATH, 1024);
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	window = glfwCreateWindow(1200, 800, "OpenGL output", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);
	/*install imgui*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io; 
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsClassic();
	ImGui_ImplOpenGL3_Init("#version 450");
	/*install imgui end*/

	Shader handshader(true, ((std::string)ABSO_PATH + "\\src\\shaders\\hand.vs").c_str(), ((std::string)ABSO_PATH + "\\src\\shaders\\hand.fs").c_str());
	GLuint hand_diffuse = loadTexture((std::string(ABSO_PATH)+"\\src\\textures\\skin.jpg").c_str());
	GLuint hand_specular = loadTexture((std::string(ABSO_PATH) + "\\src\\textures\\skin_spec.png").c_str());
	handshader.use();
	handshader.setInt("u_diffuse", 0);
	handshader.setInt("u_specular", 2);

	Shader lightshader(true, ((std::string)ABSO_PATH + "\\src\\shaders\\light.vs").c_str(), ((std::string)ABSO_PATH + "\\src\\shaders\\light.fs").c_str());
	computeTangentBasis();
	GLuint lightVAO = load_light();
	GLuint light_texture = loadTexture((std::string(ABSO_PATH) + "\\src\\textures\\block.png").c_str());
	unsigned int light_normal = loadTexture((std::string(ABSO_PATH) + "\\src\\textures\\block_spec.png").c_str());
	lightshader.use();
	lightshader.setInt("material.diffuse", 0);
	lightshader.setInt("material.texture", 1);

	Shader boxshader(true, ((std::string)ABSO_PATH+"\\src\\shaders\\box.vs").c_str(), ((std::string)ABSO_PATH + "\\src\\shaders\\box.fs").c_str());
	GLuint boxVAO = load_box();
	unsigned int box_diffuse = loadTexture((std::string(ABSO_PATH) + "\\src\\textures\\color.bmp").c_str());
	unsigned int box_normal = loadTexture((std::string(ABSO_PATH) + "\\src\\textures\\normal.bmp").c_str());
	unsigned int box_specular = loadTexture((std::string(ABSO_PATH) + "\\src\\textures\\color_spec.png").c_str());
	boxshader.use();
	boxshader.setInt("material.diffuse", 0);
	boxshader.setInt("material.normal_texture", 1);
	boxshader.setInt("material.specular", 2);

	Shader skyshader(true, ((std::string)ABSO_PATH + "\\src\\shaders\\skybox.vs").c_str(), ((std::string)ABSO_PATH + "\\src\\shaders\\skybox.fs").c_str());
	GLuint skyboxVAO = load_sky();
	GLuint skybox_texture = loadCubemap(sky_box_faces);
	skyshader.use();
	skyshader.setInt("skybox", 0);

	SkeletalMesh::Scene& sr = SkeletalMesh::Scene::loadScene("Hand", "Hand.fbx");
	if (&sr == &SkeletalMesh::Scene::error)
		std::cout << "Error occured in loadMesh()" << std::endl;
	sr.setShaderInput(handshader.ID, "in_position", "in_texcoord", "in_normal", "in_bone_index", "in_bone_weight");
	SkeletalMesh::SkeletonModifier modifier;
	glEnable(GL_DEPTH_TEST);

	float passed_time, last_time, during_time;
	glm::vec3 light_positon = glm::vec3(10.f, 5.f,10.f);
	glm::vec3 light_dir = glm::vec3(0.f, -1.f, 0.f);
	float pitch_factor = 0.0, yaw_factor = 0.f;
	glm::vec3 position(0.f, 5.f, 30.f), direct(0.f, 0.f, -1.f), up(0.f, 1.f, 0.f), right(1.f, 0.f, 0.f);
	passed_time = clock() / double(CLOCKS_PER_SEC);

	Action_init();
	while (!glfwWindowShouldClose(window))
	{
		/*modify code begin*/
		{
			last_time = passed_time;
			passed_time = clock() / double(CLOCKS_PER_SEC);
			during_time = passed_time - last_time;
			for (auto& item : num_Actions)
				if (item.state)
					item.check(hand_angles, during_time);
			for (auto& item : fixed_Actions)
				if (item.state)
					item.check(hand_angles, during_time);
			for(auto& item : cycle_Actions)
				item.check(hand_angles, during_time);
			if (hand_angles.auto_rotate)
				hand_angles.metacarpal_rotate = fmod(hand_angles.metacarpal_rotate + during_time * hand_angles.rotate_speed, 2 * M_PI);
			modifier["metacarpals"] = glm::rotate(glm::fmat4(), hand_angles.metacarpal_rotate, glm::fvec3(1.0, 0.0, 0.0));
			modifier["metacarpals"] *= glm::rotate(glm::fmat4(), hand_angles.swing_angles.angle_list["metacarpals"], glm::fvec3(0.0, 1.0, 0.0));
			modifier["metacarpals"] *= glm::rotate(glm::fmat4(), hand_angles.bend_angles.angle_list["metacarpals"], glm::fvec3(0.0, 0.0, 1.0));
			for (int i = 1; i < JOINT_NUM; i++)
			{
				modifier[str_hand[i]] = glm::rotate(glm::fmat4(), hand_angles.swing_angles.angle_list[str_hand[i]], glm::fvec3(0.0, 1.0, 0.0));
				modifier[str_hand[i]] *= glm::rotate(glm::fmat4(), hand_angles.bend_angles.angle_list[str_hand[i]], glm::fvec3(0.0, 0.0, 1.0));
			}
		}
		/*modify code end*/
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*keyboard code begin*/
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				pitch_factor -= 0.005;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				pitch_factor += 0.005;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
				yaw_factor -= 0.005;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
				yaw_factor += 0.005;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			pitch_factor = .0f;
			yaw_factor = 0.f;
			position = glm::vec3(0.f,5.f,30.f);

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= 0.05f * direct;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += 0.05f * direct;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			position -= 0.05f * right;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			position += 0.05f * right;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			position -= 0.05f * up;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			position += 0.05f * up;
		/*keyboard code end*/


		direct = glm::vec3(cos(pitch_factor) * sin(yaw_factor), sin(pitch_factor), -cos(pitch_factor) * cos(yaw_factor));
		right = glm::normalize(glm::cross(direct, glm::fvec3(0.f, sin(pitch_factor + M_PI / 2), 0.f)));
		up = glm::normalize(glm::cross(right,direct));
		glm::fmat4 mvp = glm::perspective(float(radian(45.f)), ratio, 0.1f, 1000.f)
			* glm::lookAt(position, position + direct, up);

		handshader.use();
		handshader.setMat4("u_mvp", mvp);
		handshader.setVec3("cameraPos", position);
		handshader.setVec3("pointlight.position", light_positon);
		handshader.setVec3("pointlight.ambient", 0.5f, 0.5f, 0.5f);
		handshader.setVec3("pointlight.diffuse", 0.8f, 0.8f, 0.8f);
		handshader.setVec3("pointlight.specular", 1.0f, 1.0f, 1.0f);
		handshader.setFloat("pointlight.constant", 1.0f);
		handshader.setFloat("pointlight.linear", 0.014f);
		handshader.setFloat("pointlight.quadratic", 0.0007f);

		handshader.setVec3("dirlight.direction", light_dir);
		handshader.setVec3("dirlight.ambient", 0.2f, 0.2f, 0.2f);
		handshader.setVec3("dirlight.diffuse", 0.4f, 0.4f, 0.4f);
		handshader.setVec3("dirlight.specular", 0.5f, 0.5f, 0.5f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, hand_diffuse);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, hand_specular);
		SkeletalMesh::Scene::SkeletonTransf bonesTransf;
		sr.getSkeletonTransform(bonesTransf, modifier);
		if (!bonesTransf.empty())
			glUniformMatrix4fv(glGetUniformLocation(handshader.ID, "u_bone_transf"), bonesTransf.size(), GL_FALSE, (float*)bonesTransf.data());
		 sr.render();

		boxshader.use();
		boxshader.setVec3("cameraPos", position);
		boxshader.setVec3("PointLightPos", light_positon);
		boxshader.setVec3("dirLight", light_dir);
		boxshader.setVec3("dirlight.ambient", 0.2f, 0.2f, 0.2f);
		boxshader.setVec3("dirlight.diffuse", 0.4f, 0.4f, 0.4f);
		boxshader.setVec3("dirlight.specular", 0.5f, 0.5f, 0.5f);

		boxshader.setVec3("pointlight.ambient", 0.5f, 0.5f, 0.5f);
		boxshader.setVec3("pointlight.diffuse", 0.8f, 0.8f, 0.8f);
		boxshader.setVec3("pointlight.specular", 1.0f, 1.0f, 1.0f);
		boxshader.setFloat("pointlight.constant", 1.0f);
		boxshader.setFloat("pointlight.linear", 0.014f);
		boxshader.setFloat("pointlight.quadratic", 0.0007f);
		boxshader.setFloat("material.shininess", 32.0f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,box_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, box_normal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, box_specular);
		glBindVertexArray(boxVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::scale(model, glm::vec3(4.f,4.f,4.f));
			//model = glm::scale(model, glm::vec3(4.f,4.f,4.f));
			boxshader.setMat4("model",model);
			boxshader.setMat4("mvp", mvp * model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightshader.use();
		//boxshader.setFloat("material.shininess", 32.0f);
		glBindVertexArray(lightVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, light_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, light_normal);
		glm::mat4 model = glm::mat4(1.0f); 
		model = glm::translate(model, light_positon);
		lightshader.setMat4("mvp", mvp *model);
		lightshader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		skyshader.use();
		glDepthFunc(GL_LEQUAL);
		mvp = glm::perspective(float(radian(45.f)), ratio, 0.1f, 1000.f)
			* glm::mat4(glm::mat3(glm::lookAt(position, position + direct, up)));
		skyshader.setMat4("mvp", mvp);
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default

		{
			bool Imgui = false;
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Operations", &Imgui, ImGuiWindowFlags_MenuBar);
			ImGui::Text("fps : %.0fHz", floor(1/during_time));
			if (ImGui::CollapsingHeader("pointlight position")) {
				ImGui::SliderFloat("x:", &light_positon.x, -100.f, 100.f, "%.1f");
				ImGui::SliderFloat("y:", &light_positon.y, -100.f, 100.f, "%.1f");
				ImGui::SliderFloat("z:", &light_positon.z, -100.f, 100.f, "%.1f");
			}
			if (ImGui::CollapsingHeader("dirlight direction")) {
				ImGui::SliderFloat(".x:", &light_dir.x, -1.f, 1.f, "%.2f");
				ImGui::SliderFloat(".y:", &light_dir.y, -1.f, 1.f, "%.2f");
				ImGui::SliderFloat(".z:", &light_dir.z, -1.f, 1.f, "%.2f");
			}
			for (auto& item : num_Actions)
			{
				if (ImGui::Button(item.name.c_str(), ImVec2(32.5, 20)))
				{
					hand_angles.set_False(num_Actions);
					hand_angles.set_False(fixed_Actions);
					hand_angles.set_False(cycle_Actions);
					item.state = true;
				}
				ImGui::SameLine();
			}
			ImGui::NewLine();
			for (auto& item : fixed_Actions)
				if (ImGui::Button(item.name.c_str(), ImVec2(400, 20)))
				{
					hand_angles.set_False(num_Actions);
					hand_angles.set_False(fixed_Actions);
					hand_angles.set_False(cycle_Actions);
					item.state = true;
				}
			for (auto& item : cycle_Actions)
				if (ImGui::Button(item.name.c_str(), ImVec2(400, 20)))
				{
					hand_angles.set_False(num_Actions);
					hand_angles.set_False(fixed_Actions);
					hand_angles.set_False(cycle_Actions);
					item.state = true;
					item.base_action.state = true;
				}
			ImGui::NewLine();
			ImGui::SliderAngle("anime speed", &hand_angles.anime_speed, 0.0, 120.0, " %.2f deg");
			if (ImGui::CollapsingHeader("Rotate Show"))
			{
				ImGui::Checkbox("auto rotate", &hand_angles.auto_rotate);
				ImGui::SliderAngle("rotate speed", &hand_angles.rotate_speed, 0.0, 360.0, " %.2f deg");
				ImGui::SliderAngle("metacarpal_angle", &hand_angles.metacarpal_rotate, 0.0, 360.0, " %.2f deg");
			}
			if (ImGui::CollapsingHeader("Finger Bend Angles")) {
				ImGui::SliderAngle(str_bend_labels[0].c_str(), &hand_angles.bend_angles.angle_list[str_hand[0]], -90.0, 90.0, " %.2f deg");
				ImGui::SliderAngle(str_bend_labels[1].c_str(), &hand_angles.bend_angles.angle_list[str_hand[1]], -45.0, 30.0, " %.2f deg");
				ImGui::SliderAngle(str_bend_labels[2].c_str(), &hand_angles.bend_angles.angle_list[str_hand[2]], -15, 90.0, " %.2f deg");
				ImGui::SliderAngle(str_bend_labels[3].c_str(), &hand_angles.bend_angles.angle_list[str_hand[3]], 0.0, 90.0, " %.2f deg");
				for (int i = 1; i < (JOINT_NUM - 1) / 3; i++)
				{
					ImGui::SliderAngle(str_bend_labels[i * 3 + 1].c_str(), &hand_angles.bend_angles.angle_list[str_hand[i * 3 + 1]], -15.0, 90.0, " %.2f deg");
					ImGui::SliderAngle(str_bend_labels[i * 3 + 2].c_str(), &hand_angles.bend_angles.angle_list[str_hand[i * 3 + 2]], -15.0, 90.0, " %.2f deg");
					ImGui::SliderAngle(str_bend_labels[i * 3 + 3].c_str(), &hand_angles.bend_angles.angle_list[str_hand[i * 3 + 3]], 0.0, 90.0, " %.2f deg");
				}
			}
			if (ImGui::CollapsingHeader("Finger Swing Angles")) {
				ImGui::SliderAngle(str_swing_labels[0].c_str(), &hand_angles.swing_angles.angle_list[str_hand[0]], -90.0, 90.0, " %.2f deg");
				ImGui::SliderAngle(str_swing_labels[1].c_str(), &hand_angles.swing_angles.angle_list[str_hand[1]], -30.0, 30.0, " %.2f deg");
				for (int i = 1; i < (JOINT_NUM - 1) / 3; i++)
					ImGui::SliderAngle(str_swing_labels[i * 3 + 1].c_str(), &hand_angles.swing_angles.angle_list[str_hand[i * 3 + 1]], -15.0, 15.0, " %.2f deg");
			}
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	SkeletalMesh::Scene::unloadScene("Hand");

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}