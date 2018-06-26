#include "window.h"

//*******************************************************************************
//********	  Erebos	*********************************************************
//***Written by Cristian Lepadatu. Credits to TheChernoProject on youtube.com/
//*******************************************************************************
//
//Erebos  core engine - window class functions, and rogue functions
//	**Logic:
//		- graphics namespace
//	**Window class functions
//		- Non-default constructor Window(name, width, height) - assigns name, width, height as per instance
//		- 


	
		//----Window constructors
		//------------------------------------------------------------------------------------------

		Window::Window ( const char* name, int width, int height,bool fullscreen )
			{
			done = true;
			enable_text = false;
			text =-1;
			m_Title = name;
			m_Width = width;
			m_Height = height;
			this->fullscreen = fullscreen;
			//possible redundance, destroyst OpenGL window, cursor, resources. Investigate removal
			if ( !initialise () )
				glfwTerminate ();
			else
				init_OK = true;

			for ( int i = 0; i < MAX_KEYS; i++ )
				{
				m_Keys [i] = false;

				}

			for ( int i = 0; i < MAX_BUTTONS; i++ )
				{
				m_MouseButtons [i] = false;

				}
			}
		void Window::Set_vars ( const char* name, int width, int height )
			{
		
			}
		//------------------------------------------------------------------------------------------

		Window::~Window()
			{
				glfwTerminate();
			}

		//------------------------------------------------------------------------------------------
		//----end Window constructors

		
		//---WINDOW METHODS
		//-----Initialise GLFW Library, GLFW window creation, make window current, 
		//-----resize callback, initialise GLEW
		//------------------------------------------------------------------------------------------
		bool Window::initialise() 
							
			{
				//-------------------Error handle GLFW Library init
				if (!glfwInit() )//- Initialise GLFW Library,
					{
					std::cout << "Failed to initialize GLFW!" << std::endl;
					return false;
					}

				//--------------------GLFWwindow creation
				if (fullscreen)
					m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);//FUllscreen
				else
					m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
				//glfwSetInputMode ( m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED ); //unbounded
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); //overwatch-like
				//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //noob-like
				
				//glfwSetCursorPos(m_Window, m_Width/2, m_Height/2); not working
				//-------------------Error handle Window creation
				if (!m_Window)
					{	
					glfwTerminate();
					std::cout << "Failed to create GLFW Window." << std::endl;
					return false;
					}

				//-Make GLFWwindow current
				glfwMakeContextCurrent(m_Window);
				
				//-Instantiate pointer to current user window
				//-fetch with: glfwGetWindowUserPointer()
				glfwSetWindowUserPointer(m_Window, this);

				//-EVENT CALLBACKS
				glfwSetWindowSizeCallback(m_Window,windowResize);
				glfwSetKeyCallback(m_Window, key_callback);
				glfwSetCharCallback ( m_Window, character_callback );
				glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
				glfwSetCursorPosCallback(m_Window, cursor_position_callback);


				//-Initialise GLEW
				//-------------------Error handle GLEW initialisation
				if (glewInit() != GLEW_OK)
					{
					std::cout << "Could not initialise GLEW!" << std::endl;
					return false;
					}

				//Test print OpenGL version
				std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;
				return true;

			}
		//------------------------------------------------------------------------------------------

		//=============REFRESH SCREEN PART===========
		void Window::clear() const
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		//------------------------------------------------------------------------------------------

		//==========Tests window close flag, acts as game loop for now===========
		bool Window::closed() const
			{
				return glfwWindowShouldClose(m_Window)==1;
			}
		//------------------------------------------------------------------------------------------

		//==================Draw updates=========================================
		void Window::update()
			{

				GLenum error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error:" << error << std::endl;

				glfwPollEvents();//-process events in the event queue - eg input
				//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
				glfwSwapBuffers(m_Window);//Swap front and back buffers for rendering			

			}
		//------------------------------------------------------------------------------------------

		//============Resize window function=====================================
		void windowResize(GLFWwindow* window, int width, int height)
			{

				Window* win = (Window*)glfwGetWindowUserPointer(window);
				glViewport(0, 0, width, height);//sets viewport dimensions
				win->m_Width = width;
				win->m_Height = height;

			}
		//------------------------------------------------------------------------------------------

		//===========Set window background color====================================
		void Window::WindowColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}
		//------------------------------------------------------------------------------------------

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double &x, double & y) const
		{
			x = m_Mx;
			y = m_My;
		}
		
		void Window::Disable_text_receive()
		{
			enable_text = false;
			done = true;
			text = -1;
		}

		void Window::Enable_text_receive ()
			{
			enable_text = true;
			done = false;
			text = -1;
			};
		char Window::Retrieve_text ()
			{
			if (enable_text)
				enable_text = false;
				return text;
			}
		bool Window::Can_retrieve ()
			{
			if ( done==false &&enable_text==true)
				return true;
			else
				return false;
			}
		//=================KEYBOARD/MOUSE CALLBACKS=======================================

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
	//		std::cout << "Key " << scancode << " is pressed" << std::endl;
			/*
#define 	GLFW_KEY_RIGHT   262

#define 	GLFW_KEY_LEFT   263

#define 	GLFW_KEY_DOWN   264

#define 	GLFW_KEY_UP   265
			*/
			if ( key == 259 )
				{			
				win->enable_text = true;
				win->text = -2;
				}
			if (key == 257 && win->done == false)
			{
				win->done = true;
				win->enable_text = false;
			}

		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)

		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
			
		}
		void character_callback ( GLFWwindow* window, unsigned int codepoint )
			{
			
			Window* win = (Window*) glfwGetWindowUserPointer ( window );
			win->enable_text=true;
			if ( win->enable_text )
				{
				win->text= (char) codepoint;
				std::cout << codepoint << std::endl;
				std::cout << win->text << std::endl;
				}
			}
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Mx = xpos;
			win->m_My = ypos;

		}
		//=================================================================================

