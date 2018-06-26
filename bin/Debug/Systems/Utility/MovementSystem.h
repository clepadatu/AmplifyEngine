#pragma		once

#include	<glm.hpp>
#include	<gtc/matrix_transform.hpp>
#include	<gtx/transform.hpp>
#include	<chrono>
#include <iostream>
#include	<GL/glew.h>//GL EXTENSION WRANGLER, OpenGL v5.4
#include	<GLFW/glfw3.h>//GL FOR WINDOWS, OpenGL v1.0

class	MovementSystem
	{

	private:
		int _type; // 0=keyboard rotation, 1=keyboard x/y strafe movement no rotation, 3=mouse bound movement
		glm::mat4	TranslationMatrix;
		glm::mat4	ModelMatrix;
		glm::mat4	ViewMatrix = glm::mat4 ( 1.0 );
		glm::mat4	ProjectionMatrix;
		glm::mat4 MVP_projectile;
		glm::mat4 TempMatrix;
		glm::mat4 RotationMatrix;
		glm::mat4	obj_move = glm::mat4 ( 1.0 );

		float xpos = 640.0f;
		float ypos = 650.0f;
		float delta = 0.0004f;
		float intermediate = 0.0f;

		int random;

		int		_width, _height;
		double	_x = 0, _y = 0;
		float speed = 0.05f; // 3 units / second kb
		float step = 0.05f;
		bool space_pressed = 0;
		float lastTime = 0;
		//maybe
		double mouse_x_last=0;
		double mouse_y_last=0;

		float size_obj_x;
		float size_obj_y;
		float size_obj_z;



	private:
		void computeMatrices ( );

	public:
		MovementSystem ( );
		~MovementSystem ( );
		
		//MVP Init flavors
		void initMVP(int	width, int		height, int		type);
		void initMVP_text(int	width, int		height, int		type);
		void initMVP_position(int	width, int		height, int		type, float position_x, float position_y);
		void initMVP_position_size(int	width, int		height, int		type, float position_x, float position_y, float size_x, float size_y, float size_z);

		//MAYBE NEEDED ???
		glm::mat4 getProjectionMatrix ( );
		glm::mat4 getViewMatrix ( );
		glm::mat4 getModelMatrix ( );
		glm::mat4 getMVP ( );

		void computeMatricesFromInputs ( int X, int Y,double mX, double mY );
		/*void computeMatricesFromInputs ( Window*	win, double	x, double	y );*/
		void computeAIMovement();
		float getPlayerX ( );
		float getPlayerY ( );
		/*bool check_click ( Window* win );*/
		void projectile_move ( float x, float y );
		float return_obj_y ( );
		float return_obj_x ( );
		float return_size_x ( );
		float return_size_y ( );
		float return_size_z ( );

	};