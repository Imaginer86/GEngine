#pragma once
#include "../Math/Vector3f.h"
#include "../Math//Quaternion.h"
#include "../Render/Color4f.h"
#include "../Core/Camera.h"

class Render
{
protected:
	Camera	camera;
	bool	fullscreen;
	bool	lightOn;
	unsigned width;
	unsigned height;
public:	
	
	Render(unsigned width_, unsigned height_, Vector3f cameraPos, Quaternion cameraQ, bool fullscreen_, bool light_);
	virtual ~Render() {};

	virtual void init() = 0;
	virtual void resize(unsigned width_, unsigned height_) = 0;
	virtual bool LoadGLTextures() = 0;
	virtual bool createWindow(const char* title, unsigned char bits) = 0;
	virtual void killWindow() = 0;
	virtual void setFullscreen(bool fullscreen_) { fullscreen = fullscreen_; }

	virtual void buildFont() = 0;
	virtual void killFont() = 0;
	virtual void print(float x, float y, const char * fmt, ...) = 0;

	virtual void beginDraw() const = 0;
	virtual void endDraw() const = 0;

	virtual void Translate(const Vector3f& t) const = 0;
	virtual void Rotate(const Quaternion& q) const = 0;
	virtual void LoadIdentity() const = 0;

	virtual void CreateVBO(const float *data, const unsigned num_vert, const unsigned *index, const unsigned num_index) = 0;

	virtual void drawTriangleStrip(size_t n, const Vector3f * vertexs, const Vector3f * normals, const Color4f & color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Color4f& color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& na, const Vector3f& nb, const Vector3f& nc, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f *vertexs, const Vector3f& n, const Color4f &color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axic, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const = 0;
	virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const = 0;
	virtual void drawSphere(const Vector3f& pos, const float r, const Quaternion& q, const Color4f& color) const = 0;
	virtual void drawVBO() const = 0;
	//virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const = 0;

	void RotateCamera(const Quaternion &q);
	void MoveCamera(const Vector3f &v);
	void MoveCameraQ(float s);

	//Camera& GetCamera() { return camera; }


};

inline Render::Render(unsigned width_, unsigned height_, Vector3f cameraPos, Quaternion cameraQ, bool fullscreen_, bool light_)
: width(width_)
, height (height_)
, fullscreen(fullscreen_)
, lightOn(light_)
, camera(cameraPos, cameraQ)
{
	//camera.q *= Quaternion(90, Vector3f(1.0f, 0.0f, 0.0f));
	//camera.q *= Quaternion(180, Vector3f(0.0f, 1.0f, 0.0f));

}

inline void Render::RotateCamera(const Quaternion &q)
{
	camera.q *= q;
	camera.q.normalize();
}

inline void Render::MoveCamera(const Vector3f &v)
{
	camera.pos += v;
}

inline void Render::MoveCameraQ(float s)
{
	//Vector3f v(0.0f, 0.0f, -1.0f);
	//Quaternion q(30.0f, Vector3f(0.0f, 0.0f, 1.0f));
	//q.rotate(v);

	Vector3f dif(0.0f, 0.0f, -1.0f);
	camera.q.rotate(dif);
	dif *= s;
	camera.pos += dif;
}