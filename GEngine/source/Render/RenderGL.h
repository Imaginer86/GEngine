#pragma once
#include "Render.h"
class RenderGL:	public Render
{
public:		
	RenderGL(const char* title_, /*void* wndProc_,*/ const Options& option)
		:Render(title_, /*wndProc_,*/option) {}
		//p_instance = this;//}

	virtual ~RenderGL() {};

	virtual void* Init();
	virtual void Resize(size_t  width_, size_t height_);
	//virtual bool LoadTextures();
	virtual bool swithFullscreen();
	virtual void UpdateLight();
	virtual void beginDraw() const;
	virtual void endDraw() const;

	virtual void Translate(const Vector3f& t) const;
	virtual void Rotate(float angle, Vector3f axis) const;
	virtual void Rotate(const Quaternion& q) const;
	virtual void Color(const Color4f& color);
	virtual void LoadIdentity() const;

//	virtual void buildFont();
//	virtual void killFont();
//	virtual void print(float x, float y, const char * fmt, ...);

	//virtual void CreateVBO(const float *data, const size_t num_vert, const size_t *index, const size_t num_index);
	
	virtual void drawTriangleStrip(size_t n, const Vector3f * vertexs, const Vector3f * normals, const Color4f & color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Color4f& color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& na, const Vector3f& nb, const Vector3f& nc, const Color4f& color) const;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Color4f& color) const;
	virtual void drawQuad(const Vector3f* vertexs, const Vector3f& n, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axis, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const;
	virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const;
	virtual void drawSphere(const Vector3f& pos, const float r, const Quaternion& q, const Color4f& color) const;
	virtual void drawVBO() const;

	//static Render* getInstance() {
		//if (!p_instance) //TODO
			//p_instance = new RenderGL("GEngine", 1024, 768, Vector3f(0.0f, 0.0f, -1000.0f), 0.0f, Vector3f(0.0f, 1.0f, 0.0f), false, true, 0.1f, 0.1f);
		//return p_instance;
	//}

protected:
	//static void key_callback(int key, GLFWwindow* window, int scancode, int action, int mods);
	virtual bool createWindow();
	virtual void killWindow();

	bool InitGL();
	//static void key_callback(int key, int scancode, int action, int mods);
private:   
};