#pragma once
#include "Render.h"

class RenderGL:	public Render
{
public:		
	RenderGL(unsigned width_, unsigned height_, Vector3f cameraPos, Quaternion cameraQ, bool fullscreen_, bool light_);
	virtual ~RenderGL();

	virtual void init();
	virtual void resize(unsigned width_, unsigned height_);
	virtual bool LoadGLTextures();
	virtual bool createWindow(const char* title, unsigned char bits);
	virtual void killWindow();
	virtual void beginDraw() const;
	virtual void endDraw() const;

	virtual void Translate(const Vector3f& t) const;
	virtual void Rotate(const Quaternion& q) const;
	virtual void LoadIdentity() const;

	virtual void buildFont();
	virtual void killFont();
	virtual void print(float x, float y, const char * fmt, ...);

	virtual void CreateVBO(const float *data, const unsigned num_vert, const unsigned *index, const unsigned num_index);
	
	virtual void drawTriangleStrip(size_t n, const Vector3f * vertexs, const Vector3f * normals, const Color4f & color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Color4f& color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& na, const Vector3f& nb, const Vector3f& nc, const Color4f& color) const;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Color4f& color) const;
	virtual void drawQuad(const Vector3f* vertexs, const Vector3f& n, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axic, const Color4f& color) const;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const;
	virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const;
	virtual void drawSphere(const Vector3f& pos, const float r, const Quaternion& q, const Color4f& color) const;
	virtual void drawVBO() const;
private:

	unsigned int LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void setLight();
	unsigned VBOVertexN;
	unsigned VBOIndexN;
};