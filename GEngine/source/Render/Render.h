#pragma once
#include "../GEngine.h"

#include "../Math/Vector3f.h"
//#include "../Math/Quaternion.h"
#include "../Render/Color4f.h"
#include "../Core/Camera.h"

class Render
{
public:
	Camera	camera;
	bool	fullscreen;
	bool	light;
	size_t width;
	size_t height;
	float moveScale;
	float rotateScale;
	
	Render(size_t width_, size_t height_, const Vector3f& pos_, float angle_, const Vector3f& axic_, bool fullscreen_, bool light_, float moveScale_, float rotateScale_)
		: width(width_)
		, height(height_)
		, fullscreen(fullscreen_)
		, light(light_)
		, camera(pos_, angle_, axic_)
		, moveScale(moveScale_)
		, rotateScale(rotateScale_)
	{}
	//Render(InitData& initData);
	virtual ~Render() {};

	virtual bool Init(const char* title, void *wndProc) = 0;
	virtual void Resize(size_t width_, size_t height_) = 0;
	virtual bool LoadTextures() = 0;
	virtual bool swithFullscreen() = 0;
	virtual void UpdateLight() = 0;

	virtual void buildFont() = 0;
	virtual void killFont() = 0;
	virtual void print(float x, float y, const char * fmt, ...) = 0;

	virtual void beginDraw() const = 0;
	virtual void endDraw() const = 0;

	virtual void Translate(const Vector3f& t) const = 0;
	virtual void Rotate(float angle, Vector3f axic) const = 0;
	virtual void Rotate(const Quaternion& q) const = 0;
	virtual void LoadIdentity() const = 0;

	//virtual void CreateVBO(const float *data, const size_t num_vert, const size_t *index, const size_t num_index) = 0;

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

	void SetLight(bool light_);
	bool GetLight();

	//Camera& GetCamera() { return camera; }
public:


protected:
	virtual bool createWindow(const char* title, void* wndProc) = 0;
	virtual void killWindow() = 0;

	static Render* p_instance;

private:
	Render(const Render& r);
	Render& operator=(Render&);

};

/*
inline Render::Render(InitData& initData)
: width(initData.width)
, height(initData.height)
, fullscreen(initData.fullscreen)
, light(initData.light)
, camera(initData.pos, initData.aangle, initData.axic)
, moveScale(initData.moveScale)
, rotateScale(initData.rotateScale)
{
}
*/

inline void Render::RotateCamera(const Quaternion &q)
{
	Quaternion r(camera.angle, camera.axic);
	r *= q;
	r.normalize();
	r.toAngleAxis(camera.angle, camera.axic);
	camera.axic.unit();
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

	//TODO
	Vector3f dif(0.0f, 0.0f, -1.0f);
	camera.axic += dif;
	dif *= s;
	camera.pos += dif;
}

inline void Render::SetLight(bool light_)
{
	light = light_;
}

inline bool Render::GetLight()
{
	return light;
}