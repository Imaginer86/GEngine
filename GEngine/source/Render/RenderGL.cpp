#include "RenderGL.h"

#include "../Game.h"
#include "../Core/Input.h"


#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>




//#define GL_GLEXT_PROTOTYPES
//#include <gl/gl.h>
//#include <gl/glu.h>

GLFWwindow* window;
GLuint  base;      // База списка отображения для фонта
GLUquadricObj* quadratic;

GLuint texture[1];

float rot = 0.0f;
//#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "GLu32.lib")


void error_callback(int error, const char* description)
{
	//fprintf(stderr, "Error: %s\n", description);
	std::cerr << description << std::endl << "Error code: " << error << std::endl;
}


void* RenderGL::Init()
{

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		return nullptr;	// Ошибка инициализации
	}
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;	// Window or OpenGL context creation failed
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		return nullptr;
	}


	Resize(width, height);

	// Load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("data/EarthMap.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// Создание текстуры
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	else
		return nullptr;



	//buildFont();

	

	// Установка параметров текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	TextureUpdate();

	glLightfv(GL_LIGHT0, GL_AMBIENT, gLightAmbient.v);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gLightDiffuse.v);
	glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition.v);
	glEnable(GL_LIGHT0);

	LightUpdate();


	// Создание объекта квадрики
	//GLUquadric* quad = gluNewQuadric();
	//gluQuadricTexture(quad, GL_TRUE);

	// Создание объекта квадрики
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, GL_TRUE);

	return window;
} 

void RenderGL::DeInit()
{
	gluDeleteQuadric(quadratic);
	glfwSetWindowShouldClose(window, GLFW_TRUE);
	glfwDestroyWindow(window);

}

void RenderGL::TextureUpdate()
{
	if (textured)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
}


/*
bool RenderGL::swithFullscreen()
{
	//return false;

	fullscreen = !fullscreen;
	//if (!createWindow())
	{
		std::cerr << "Cannot Switch FullScreen.";
		//MessageBox(NULL, "Cannot Switch FullScreen.", "ERROR", MB_OK | MB_ICONSTOP);
		return false;
	}
	return true;
}
*/
/*
bool RenderGL::InitGL()
{
	//gLightAmbient[0] = 0.25f;; 
	//gLightAmbient[1] = 0.25f;
	//gLightAmbient[2] = 0.25f; 
	//gLightAmbient[3] = 1.0f;
	//gLightDiffuse[0] = 0.5f;
	//gLightDiffuse[1] =  0.5f;
	//gLightDiffuse[2] =  0.5f; 
	//gLightDiffuse[3] = 1.0f;
	//gLightPosition[0] = 0.0f;
	//gLightPosition[1] = 500.0f;
	//gLightPosition[2] = 0.0f;
	//gLightPosition[3] = 1.0f;
	
	Resize(width, height);              // Настроим перспективу для нашего OpenGL экрана.

	//glClearDepth(1.0f);              // Ð Ð°Ð·Ñ€ÐµÑˆÐ¸Ñ‚ÑŒ Ð¾Ñ‡Ð¸ÑÑ‚ÐºÑƒ Ð±ÑƒÑ„ÐµÑ€Ð° Ð³Ð»ÑƒÐ±Ð¸Ð½Ñ‹
	//glDepthFunc(GL_LEQUAL);            // Ð¢Ð¸Ð¿ Ñ‚ÐµÑÑ‚Ð° Ð³Ð»ÑƒÐ±Ð¸Ð½Ñ‹
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glShadeModel(GL_SMOOTH);            // Ð Ð°Ð·Ñ€ÐµÑˆÐ¸Ñ‚ÑŒ Ð¿Ð»Ð°Ð²Ð½Ð¾Ðµ Ñ†Ð²ÐµÑ‚Ð¾Ð²Ð¾Ðµ ÑÐ³Ð»Ð°Ð¶Ð¸Ð²Ð°Ð½Ð¸Ðµ
	//glEnable(GL_DEPTH_TEST);

	



	//UpdateLight();

	//glEnable(GL_COLOR_MATERIAL);	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	return true;
	



	//----------

	//glEnable(GL_TEXTURE_2D);

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	

	//glGenVertexArray(1, &VAO);
	//glBindVertexArray(VAO);

	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	// Сначала генерируем OpenGL буфер и сохраняем указатель на него в vertexbuffer
	//glGenBuffers(1, &vertexbuffer);

	// Биндим буфер
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Предоставляем наши вершины в OpenGL
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);

	//Shaders
	//shaderProgram = LoadShaders("../GEngine/src/shaders/vertex_shader.glsl", "../GEngine/src/shaders/fragment_shader.glsl");
	//LoadGLTextures();

	//std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	//std::string vendorInfo = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
	//std::string extensionsInfo = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
	//std::cout << "OpenGL version: " << version << std::endl;
	//std::cout << "OpenGL vendor: " << vendorInfo << std::endl;
	//std::cout << "Full OpenGL extensions list: " << extensionsInfo << std::endl;
	
}
*/

// Загрузка картинки и конвертирование в текстуру

/*
bool RenderGL::LoadTextures()
{
	// Load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("data/EarthMap.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		// Создание текстуры
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			return true;
	}
	else
		return false;	
}
*/



void RenderGL::Resize(size_t width_, size_t height_)
{
	width = width_;
	height = height_;
	if (height == 0) height = 1;
	float aspect = static_cast<float>(width) / static_cast<float>(height);
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, near, far);
	//glFrustum(-aspect, aspect, -1.0, 1.0, 1.5, 20.0); //ex
	//glOrtho(-50.0 * aspect, 50.0 * aspect, -50.0, 50.0, 1.0, -1.0); //ex
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

/*
void RenderGL::buildFont()
{
	HFONT  font;            // Идентификатор фонта
	base = glGenLists(96);  // Выделим место для 96 символов ( НОВОЕ )								
	font = CreateFont(-24,        // Высота фонта ( НОВОЕ )
		0,        // Ширина фонта
		0,        // Угол отношения
		0,        // Угол наклона
		FW_BOLD,      // Ширина шрифта
		FALSE,        // Курсив
		FALSE,        // Подчеркивание
		FALSE,        // Перечеркивание
		ANSI_CHARSET,      // Идентификатор набора символов
		OUT_TT_PRECIS,      // Точность вывода
		CLIP_DEFAULT_PRECIS,    // Точность отсечения
		ANTIALIASED_QUALITY,    // Качество вывода
		FF_DONTCARE | DEFAULT_PITCH,  // Семейство и шаг
		"Courier New");      // Имя шрифта

	SelectObject(hDC, font);        // Выбрать шрифт, созданный нами ( НОВОЕ )
	wglUseFontBitmaps(hDC, 32, 96, base); // Построить 96 символов начиная с пробела ( НОВОЕ )
}


void RenderGL::killFont()
{
	glDeleteLists(base, 96);        // Удаление всех 96 списков отображения ( НОВОЕ )
}



void RenderGL::print(float x, float y, const char* fmt, ...)
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	glRasterPos2f(x, y);
	char    text[256];      // Место для нашей строки

	va_list    ap;          // Указатель на список аргументов
	if (fmt == NULL)	return;// Если нет текста Ничего не делать

	va_start(ap, fmt);           // Разбор строки переменных
	vsprintf_s(text, fmt, ap); // И конвертирование символов в реальные коды
	va_end(ap);                  // Результат помещается в строку
	glPushAttrib(GL_LIST_BIT);      // Протолкнуть биты списка отображения ( НОВОЕ )
	glListBase(base - 32);          // Задать базу символа в 32 ( НОВОЕ )
	glCallLists(static_cast<GLsizei>(strlen(text)), GL_UNSIGNED_BYTE, text);// Текст списками отображения(НОВОЕ)
	glPopAttrib(); // Возврат битов списка отображения ( НОВОЕ )s	
}
*/

/*void RenderGL::CreateVBO(const float* data, const 
num_vert, const size_t* index, const size_t num_index)
{
	
	//glBindVertexArray(VAO);
	VBOVertexN = num_vert;
	VBOIndexN = num_index;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VBOVertexN * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VBOIndexN * sizeof(size_t), index, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);


	//glVertexAttribPointer(0, VBOIndexN, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
}
*/


/*
size_t int RenderGL::LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
	// создаем шейдеры
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// читаем вершинный шейдер из файла
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// читаем фрагментный шейдер из файла
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Компилируем вершинный шейдер
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Устанавливаем параметры
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);

	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Компилируем фрагментный шейдер
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Устанавливаем параметры
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Устанавливаем параметры
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
	
	return 0;
}
*/

void RenderGL::LightUpdate()
{
	if (light)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}

void RenderGL::beginDraw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float angle = camera.q.GetAngle();
	Vector3f axis = camera.q.GetAxis();
	glRotatef(radToDeg(angle), axis.x, axis.y, axis.z);
	glTranslatef(-camera.pos.x, -camera.pos.y, -camera.pos.z);

	//gluLookAt(camera.pos.x, camera.pos.y,-camera.pos.z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderGL::endDraw() const
{
	//gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void RenderGL::Translate(const Vector3f & t) const
{
	glTranslatef(t.x, t.y, t.z);
}

void RenderGL::Rotate(float angle, Vector3f axis) const
{
	glRotatef(angle, axis.x, axis.y, axis.z);
}

void RenderGL::Rotate(const Quaternion & q) const
{
	float angle;
	Vector3f axis;
	q.toAngleAxis(angle, axis);
	glRotatef(angle, axis.x, axis.y, axis.z);
}

void RenderGL::Color(const Color4f& color)
{
	glColor4f(color.a, color.g, color.b, color.a);
}

void RenderGL::LoadIdentity() const
{
	glLoadIdentity();
}

void RenderGL::drawLine(const Line& l, const Color4f& color) const
{
	Vector3f a = l.P - l.L.unit() * far;
	Vector3f b = l.P + l.L.unit() * far;
	drawLineAB(a, b, color);
}
void RenderGL::drawLineAB(const Vector3f& a, const Vector3f& b, const Color4f& color) const
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINES);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
	glEnd();
}


void RenderGL::drawTriangleStrip(size_t n, const Vector3f * vertexs, const Vector3f * normals, const Color4f & color) const
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < n; ++i)
	{
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
	}
	glEnd();
}

void RenderGL::drawTriangle(const Vector3f & a, const Vector3f & b, const Vector3f & c, const Color4f & color) const
{
	Vector3f n = Vector3f(a - b) * Vector3f(c - b);
	n.unitize();
	glNormal3f(n.x, n.y, n.z);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLES);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
	glEnd();
}

void RenderGL::drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const
{
	glBegin(GL_TRIANGLES);
	glColor4f(color.r, color.g, color.b, color.a);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
	glEnd();
}

void RenderGL::drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& na, const Vector3f& nb, const Vector3f& nc, const Color4f& color) const
{	
	glBegin(GL_TRIANGLES);
		glColor4f(color.r, color.g, color.b, color.a);
		glNormal3f(na.x, na.y, na.z);
		glVertex3f(a.x, a.y, a.z);
		glNormal3f(nb.x, nb.y, nb.z);
		glVertex3f(b.x, b.y, b.z);
		glNormal3f(nc.x, nc.y, nc.z);
		glVertex3f(c.x, c.y, c.z);
	glEnd();
}


void RenderGL::drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const
{
	
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
		glVertex3f(d.x, d.y, d.z);
	glEnd();
}

void RenderGL::drawQuad(const Vector3f & a, const Vector3f & b, const Vector3f & c, const Vector3f & d, const Color4f& color) const
{
	Vector3f n = Vector3f(a - b) * Vector3f(c - b);
	n.unitize();
	glNormal3f(n.x, n.y, n.z);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	//glBegin(GL_LINES);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
		glVertex3f(d.x, d.y, d.z);
	glEnd();
}

void RenderGL::drawQuad(const Vector3f * vertexs, const Vector3f & n, const Color4f & color) const
{
	glNormal3f(n.x, n.y, n.z);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
		glVertex3f(vertexs[0].x, vertexs[0].y, vertexs[0].z);
		glVertex3f(vertexs[1].x, vertexs[1].y, vertexs[1].z);
		glVertex3f(vertexs[2].x, vertexs[2].y, vertexs[2].z);
		glVertex3f(vertexs[3].x, vertexs[3].y, vertexs[3].z);
	glEnd();

}

void RenderGL::drawQuad(const Vector3f& pos, float w, float h, const Quaternion& rotation, const Color4f& color) const
{
	//Vector3f ld = Vector3f(pos.x - w / 2.0, pos.y - h / 2.0f, pos.z);
	//Vector3f lu = Vector3f(pos.x - w / 2.0, pos.y + h / 2.0f, pos.z);
	//Vector3f ru = Vector3f(pos.x + w / 2.0, pos.y + h / 2.0f, pos.z);
	//Vector3f rd = Vector3f(pos.x + w / 2.0, pos.y - h / 2.0f, pos.z);
	Vector3f ld = Vector3f(- w / 2.0, - h / 2.0f, 0.0f);
	Vector3f lu = Vector3f(- w / 2.0, h / 2.0f, 0.0f);
	Vector3f ru = Vector3f(w / 2.0, h / 2.0f, 0.0f);
	Vector3f rd = Vector3f(w / 2.0, - h / 2.0f, 0.0f);
	glPushMatrix();
	float angle;
	Vector3f axis;
	rotation.toAngleAxis(angle, axis);
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(angle, axis.x, axis.y, axis.z);
	
	drawQuad(ld, lu, ru, rd, color);
	glPopMatrix();
}


void RenderGL::drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	Vector3f ad = Vector3f(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f bd = Vector3f(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f cd = Vector3f(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f dd = Vector3f(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f au = Vector3f(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
	Vector3f bu = Vector3f(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f cu = Vector3f(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f du = Vector3f(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

	drawQuad(ad, bd, cd, cd, color);
	drawQuad(cd, cu, du, dd, color);
	drawQuad(dd, du, au, ad, color);
	drawQuad(ad, au, bu, bd, color);
	drawQuad(bd, bu, cu, cd, color);
	drawQuad(cu, bu, au, du, color);

	glPopMatrix();
}

void RenderGL::drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axis, const Color4f& color) const
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(angle, axis.x, axis.y, axis.z);
	Vector3f ad = Vector3f(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f bd = Vector3f(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f cd = Vector3f(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f dd = Vector3f(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f au = Vector3f(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
	Vector3f bu = Vector3f(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f cu = Vector3f(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f du = Vector3f(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

	drawQuad(ad, bd, cd, cd, color);
	drawQuad(cd, cu, du, dd, color);
	drawQuad(dd, du, au, ad, color);
	drawQuad(ad, au, bu, bd, color);
	drawQuad(bd, bu, cu, cd, color);
	drawQuad(au, bu, cu, du, color);

	glPopMatrix();
}

void RenderGL::drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	Rotate(rotation);
	Vector3f ad = Vector3f(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f bd = Vector3f(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f cd = Vector3f(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
	Vector3f dd = Vector3f(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
	Vector3f au = Vector3f(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
	Vector3f bu = Vector3f(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f cu = Vector3f(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
	Vector3f du = Vector3f(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

	drawQuad(ad, bd, cd, cd, color);
	drawQuad(cd, cu, du, dd, color);
	drawQuad(dd, du, au, ad, color);
	drawQuad(ad, au, bu, bd, color);
	drawQuad(bd, bu, cu, cd, color);
	drawQuad(cu, bu, au, du, color);

	glPopMatrix();
}

void RenderGL::drawSphere(const Vector3f & pos, const float r, const Color4f & color) const
{

	//gluQuadricDrawStyle(quadratic, GLU_FILL);
	//gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	//gluQuadricTexture(quadratic, GLU_FALSE);

	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glColor4f(color.r, color.g, color.b, color.a);


	gluSphere(quadratic, r, 64, 64);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	
	glPopMatrix();

	//gluDeleteQuadric(quadratic);
}

void RenderGL::drawSphereT(const Vector3f& pos, const float r, const Color4f& color) const
{


	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(90, 1, 0, 0);
	glRotatef(rot, 0, 0, 1);
	rot += 1;
	glColor4f(color.r, color.g, color.b, color.a);

	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	gluSphere(quadratic, r, 64, 64);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
	
}

void RenderGL::drawSphere(const Vector3f& pos, const float r, const Quaternion& q, const Color4f& color) const
{
	
	//gluQuadricTexture(quadratic, GLU_TRUE);

	//glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Texture
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping	

	glColor3f(color.r, color.g, color.b);
	//glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	float angle;
	Vector3f axis;
	q.toAngleAxis(angle, axis);
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(-angle, q.x, q.y, q.z);
	//GLUquadric *qobj = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping	


	//gluQuadricTexture(qobj, GL_TRUE);
	gluSphere(quadratic, r, 128, 128);
	//gluDeleteQuadric(qobj);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);

	
	//glPushMatrix();
	//glLoadIdentity();
	//glColor4f(color.r, color.g, color.b, color.a);

	//gluQuadricOrientation(quadratic, GLU_OUTSIDE);
	//gluQuadricDrawStyle(quadratic, GLU_FILL);
	//gluQuadricNormals(quadratic, GLU_SMOOTH);
	//gluQuadricTexture(quadratic, GL_TRUE);

	//gluSphere(quadratic, r, 16, 16);
	//glPopMatrix();
	
	//gluDeleteQuadric(quadratic);
}

void RenderGL::drawVBO() const
{
	/*
	//glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	

	// Первый буфер атрибутов: вершины
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(
		//0,                  // Атрибут 0. Сакрального смысла в нуле нет, но число должно совпадать с числом в шейдере
		//3,                  // количество
		//GL_FLOAT,           // тип
		//GL_FALSE,           // нормализировано ли?
		//0,                  // шаг
		//(void*)0            // смещение в буфере
	//);
	

	// Рисуем треугольник !
	//glDrawArrays(GL_LINE_LOOP, 0, 3); //Начиная с вершины 0 и рисуем 3 штуки. Всего => 1 треугольник
	//glisableVertexAttribArray(0);



	//glUseProgram(shaderProgram);

	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, VBOIndexN, GL_size_t_INT, 0);
	*/
}
/*
bool RenderGL::createWindow()
{
	int PixelFormat;              // Хранит результат после поиска
	WNDCLASS  wc;                // Структура класса окна
	DWORD    dwExStyle;              // Расширенный стиль окна
	DWORD    dwStyle;              // Обычный стиль окна
	RECT WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;              // Установить левую составляющую в 0
	WindowRect.right = (long)width;              // Установить правую составляющую в Width
	WindowRect.top = (long)0;                // Установить верхнюю составляющую в 0
	WindowRect.bottom = (long)height;              // Установить нижнюю составляющую в Height
	//!!!fullscreen = fullscreen;              // Устанавливаем значение глобальной переменной fullscreen
	hInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
	wc.lpfnWndProc = (WNDPROC)ptr_wndProc;          // Процедура обработки сообщений
	//TODO wc.lpfnWndProc =
	wc.cbClsExtra = 0;              // Нет дополнительной информации для окна
	wc.cbWndExtra = 0;              // Нет дополнительной информации для окна
	wc.hInstance = hInstance;            // Устанавливаем дескриптор
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // Загружаем указатель мышки
	wc.hbrBackground = NULL;              // Фон не требуется для GL
	wc.lpszMenuName = NULL;              // Меню в окне не будет
	wc.lpszClassName = "OpenGL";            // Устанавливаем имя классу
	if (!RegisterClass(&wc))              // Пытаемся зарегистрировать класс окна
	{
		std::cerr << "Failed To Register The Window Class." << std::endl;
		//MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Выход и возвращение функцией значения false
	}
	if (fullscreen)                // Полноэкранный режим?
	{
		DEVMODE dmScreenSettings;            // Режим устройства
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // Очистка для хранения установок
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Размер структуры Devmode
		dmScreenSettings.dmPelsWidth = (DWORD)width;        // Ширина экрана
		dmScreenSettings.dmPelsHeight = (DWORD)height;        // Высота экрана
		dmScreenSettings.dmBitsPerPel = 32;        // Глубина цвета
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя
																				 // Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			//TODO
			// Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"GEngine G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;          // Выбор оконного режима (fullscreen = false)
			}
			else
			{
				std::cerr << "Program Will Now Close." << std::endl;
				//MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;            // Выход и возвращение функцией false
			}
		}
	}
	if (fullscreen)                  // Мы остались в полноэкранном режиме?
	{
		dwExStyle = WS_EX_APPWINDOW;          // Расширенный стиль окна
		dwStyle = WS_POPUP;            // Обычный стиль окна
		ShowCursor(false);              // Скрыть указатель мышки
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // Расширенный стиль окна
		dwStyle = WS_OVERLAPPEDWINDOW;        // Обычный стиль окна
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры
	hWnd = CreateWindowEx(dwExStyle,          // Расширенный стиль для окна
		"OpenGL",          // Имя класса
		title,            // Заголовок окна
		WS_CLIPSIBLINGS |        // Требуемый стиль для окна
		WS_CLIPCHILDREN |        // Требуемый стиль для окна
		dwStyle,          // Выбираемые стили для окна
		0, 0,            // Позиция окна
		WindowRect.right - WindowRect.left,    // Вычисление подходящей ширины
		WindowRect.bottom - WindowRect.top,    // Вычисление подходящей высоты
		NULL,            // Нет родительского
		NULL,            // Нет меню
		hInstance,          // Дескриптор приложения
		NULL);
	if (!hWnd)          // Не передаём ничего до WM_CREATE (???)
	{
		killWindow();                // Восстановить экран
		std::cerr << "Window Creation Error." << std::endl;
		//MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	static  PIXELFORMATDESCRIPTOR pfd =            // pfd сообщает Windows каким будет вывод на экран каждого пикселя
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // Размер дескриптора данного формата пикселей
		1,                  // Номер версии
		PFD_DRAW_TO_WINDOW |              // Формат для Окна
		PFD_SUPPORT_OPENGL |              // Формат для OpenGL
		PFD_DOUBLEBUFFER,              // Формат для двойного буфера
		PFD_TYPE_RGBA,                // Требуется RGBA формат
		32,                  // Выбирается бит глубины цвета
		0, 0, 0, 0, 0, 0,              // Игнорирование цветовых битов
		0,                  // Нет буфера прозрачности
		0,                  // Сдвиговый бит игнорируется
		0,                  // Нет буфера накопления
		0, 0, 0, 0,                // Биты накопления игнорируются
		32,                  // 32 битный Z-буфер (буфер глубины)
		0,                  // Нет буфера трафарета
		0,                  // Нет вспомогательных буферов
		PFD_MAIN_PLANE,                // Главный слой рисования
		0,                  // Зарезервировано
		0, 0, 0                  // Маски слоя игнорируются
	};
	hDC = GetDC(hWnd);
	if (!hDC)              // Можем ли мы получить Контекст Устройства?
	{
		killWindow();                // Восстановить экран
		std::cerr << "Can't Create A GL Device Context." << std::endl;
		//MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	PixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!PixelFormat)        // Найден ли подходящий формат пикселя?
	{
		killWindow();                // Восстановить экран
		std::cerr << "Can't Find A Suitable PixelFormat." << std::endl;
		//MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?
	{
		killWindow();                // Восстановить экран
		std::cerr << "Can't Set The PixelFormat." << std::endl;
		//MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	hRC = wglCreateContext(hDC);
	if (!hRC)          // Возможно ли установить Контекст Рендеринга?
	{
		killWindow();                // Восстановить экран
		std::cerr << "Can't Create A GL Rendering Context." << std::endl;
		//MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	if (!wglMakeCurrent(hDC, hRC))            // Попробовать активировать Контекст Рендеринга
	{
		killWindow();                // Восстановить экран
		std::cerr << "Can't Activate The GL Rendering Context." << std::endl;
		//MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}

	ShowWindow(hWnd, SW_SHOW);              // Показать окно
	SetForegroundWindow(hWnd);              // Слегка повысим приоритет
	SetFocus(hWnd);                // Установить фокус клавиатуры на наше окно

	return true;
}
*/


/*
void RenderGL::killWindow()
{
	if (fullscreen)              // ÐœÑ‹ Ð² Ð¿Ð¾Ð»Ð½Ð¾ÑÐºÑ€Ð°Ð½Ð½Ð¾Ð¼ Ñ€ÐµÐ¶Ð¸Ð¼Ðµ?
	{
		ChangeDisplaySettings(NULL, 0);        // Ð•ÑÐ»Ð¸ Ð´Ð°, Ñ‚Ð¾ Ð¿ÐµÑ€ÐµÐºÐ»ÑŽÑ‡Ð°ÐµÐ¼ÑÑ Ð¾Ð±Ñ€Ð°Ñ‚Ð½Ð¾ Ð² Ð¾ÐºÐ¾Ð½Ð½Ñ‹Ð¹ Ñ€ÐµÐ¶Ð¸Ð¼
		ShowCursor(true);            // ÐŸÐ¾ÐºÐ°Ð·Ð°Ñ‚ÑŒ ÐºÑƒÑ€ÑÐ¾Ñ€ Ð¼Ñ‹ÑˆÐºÐ¸
	}

	if (hRC)                // Ð¡ÑƒÑ‰ÐµÑÑ‚Ð²ÑƒÐµÑ‚ Ð»Ð¸ ÐšÐ¾Ð½Ñ‚ÐµÐºÑÑ‚ Ð ÐµÐ½Ð´ÐµÑ€Ð¸Ð½Ð³Ð°?
	{
		if (!wglMakeCurrent(NULL, NULL))        // Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾ Ð»Ð¸ Ð¾ÑÐ²Ð¾Ð±Ð¾Ð´Ð¸Ñ‚ÑŒ RC Ð¸ DC?
		{
			std::cerr << "Release Of DC And RC Failed." << std::endl;
			//MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))        // Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾ Ð»Ð¸ ÑƒÐ´Ð°Ð»Ð¸Ñ‚ÑŒ RC?
		{
			std::cerr << "Release Rendering Context Failed." << std::endl;
			//MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;              // Ð£ÑÑ‚Ð°Ð½Ð¾Ð²Ð¸Ñ‚ÑŒ RC Ð² NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))          // Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾ Ð»Ð¸ ÑƒÐ½Ð¸Ñ‡Ñ‚Ð¾Ð¶Ð¸Ñ‚ÑŒ DC?
	{
		std::cerr << "Release Device Context Failed." << std::endl;
		//MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                // Ð£ÑÑ‚Ð°Ð½Ð¾Ð²Ð¸Ñ‚ÑŒ DC Ð² NULL
	}

	if (hWnd && !DestroyWindow(hWnd))            // Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾ Ð»Ð¸ ÑƒÐ½Ð¸Ñ‡Ñ‚Ð¾Ð¶Ð¸Ñ‚ÑŒ Ð¾ÐºÐ½Ð¾?
	{
		std::cerr << "Could Not Release hWnd." << std::endl;
		//MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                // Ð£ÑÑ‚Ð°Ð½Ð¾Ð²Ð¸Ñ‚ÑŒ hWnd Ð² NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))        // Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾ Ð»Ð¸ Ñ€Ð°Ð·Ñ€ÐµÐ³Ð¸ÑÑ‚Ñ€Ð¸Ñ€Ð¾Ð²Ð°Ñ‚ÑŒ ÐºÐ»Ð°ÑÑ
	{
		std::cerr << "Could Not Unregister Class." << std::endl;
		//MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                // Ð£ÑÑ‚Ð°Ð½Ð¾Ð²Ð¸Ñ‚ÑŒ hInstance Ð² NULL
	}

	gluDeleteQuadric(quadratic);

	killFont();
}
*/