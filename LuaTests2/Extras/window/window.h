#pragma once

#include <iostream>
#include <GL/glew.h>//GL EXTENSION WRANGLER, OpenGL v5.4
#include <GLFW/glfw3.h>//GL FOR WINDOWS, OpenGL v1.0
#define MAX_KEYS 1024
#define MAX_BUTTONS 32



		class Window
		{
			//(my vars - m_Var)
			private:
				//Window basic traits
				int m_Width;
				int m_Height;
				const char* m_Title;
			
				
			
				//Window basic states
				bool m_Closed;

				//GLFW Window object instance
				GLFWwindow* m_Window;

				//Input vars
				bool m_Keys[MAX_KEYS];
				bool m_MouseButtons[MAX_BUTTONS];
				double m_Mx, m_My;

			public:
				bool init_OK = false;
				bool fullscreen = false;
				char text;
				bool enable_text;
				//Constructors
				void Set_vars ( const char* name, int width, int height );
				Window ( const char* name, int width, int height,bool fullscreen );
				~Window();
				//Tool methods
				bool closed() const;
				void update();
				void clear() const;
				inline int getWidth() const { return m_Width; };
				inline int getHeight() const { return m_Height; };

				bool isKeyPressed( unsigned int keycode) const;
				bool isMouseButtonPressed(unsigned int button) const;
				void getMousePosition(double &x, double & y) const;

				void WindowColor(float r, float g, float b, float a);
				void Enable_text_receive ();
				void Disable_text_receive();
				char Retrieve_text ();
				bool Can_retrieve ();
				bool done;
			private:
				//Window Initialisation method
				bool initialise();
				friend void windowResize(GLFWwindow* window, int width, int height);
				friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
				friend static void character_callback ( GLFWwindow* window, unsigned int codepoint );
				friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
				friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};


