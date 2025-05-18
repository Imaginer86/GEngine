#pragma once
#include "Options.h"
#include "Math/GMath.h"
#include "Math/Vector3f.h"
#include "Math/Vector4f.h"
#include "Math/Quaternion.h"
#include "Math/Line.h"
#include "Render/Color4f.h"
#include "Physics/Camera.h"

class Render
{
//public:
	//static Render& getInstance();
	//Render(const Render&) = delete;
	//Render& operator=(const Render&) = delete;
//protected:
public:
	Render(const Options& option)
		: width(option.width)
		, height(option.height)
		, fovy(option.fovy)
		, near(option.near)
		, far(option.far)
		, fullscreen(option.fullscreen)
		, gLightAmbient(option.lightAmbient)
		, gLightDiffuse(option.lightDiffuse)
		, gLightPosition(option.lightPosition)
		, camera(option.cameraPos, option.cameraAngle, option.cameraaxis)
		, moveScale(option.moveScale)
		, rotateScale(option.rotateScale)
		, light(true)
		, textured(true)
	{
		strncpy_s(title, sizeof title, option.name, strlen(option.name));
		if (height == 0) height = 1;
	}
	virtual ~Render() {}

protected:
	Camera	camera;

	bool	fullscreen;
	bool	light;
	bool	textured;
	size_t width;
	size_t height;
	float fovy;
	float near;
	float far;
	
	float moveScale;
	float rotateScale;
	char title[20];	

	Vector4f gLightAmbient;
	Vector4f gLightDiffuse;
	Vector4f gLightPosition;
public:
	//Render(InitData& initData);
	//virtual ~Render() {/* delete[] title; */};

	void RotateCamera(const Quaternion& q);
	void MoveCamera(const Vector3f& v);
	void MoveCameraUD(float s);
	void MoveCameraLR(float s);
	void MoveCameraNF(float s);

	float getMoveScale() { return moveScale; }
	float getRotateScale() { return rotateScale; }

	void LightSwitch() { light = !light; LightUpdate(); }
	void LightOn() { light = true; }
	void LightOff() { light = false; }

	void TextuteSwitch() { textured = !textured; TextureUpdate(); }
	void TextureOn() { textured = true; }
	void TextureOff() { textured = false; }

	virtual void* Init() = 0;
	virtual void DeInit() = 0;
	virtual void Resize(size_t width_, size_t height_) = 0;
	//virtual bool LoadTextures() = 0;
	//virtual bool swithFullscreen() = 0;

//	virtual void buildFont() = 0;
//	virtual void killFont() = 0;
//	virtual void print(float x, float y, const char* fmt, ...) = 0;

	virtual void beginDraw() const = 0;
	virtual void endDraw() const = 0;

	virtual void Translate(const Vector3f& t) const = 0;
	virtual void Rotate(float angle, Vector3f axis) const = 0;
	virtual void Rotate(const Quaternion& q) const = 0;
	virtual void Color(const Color4f& color) = 0;
	virtual void LoadIdentity() const = 0;

	//virtual void CreateVBO(const float *data, const size_t num_vert, const size_t *index, const size_t num_index) = 0;


	virtual void drawLine(const Line& l, const Color4f& color) const = 0;
	virtual void drawLineAB(const Vector3f& a, const Vector3f& b, const Color4f& color) const = 0;
	virtual void drawTriangleStrip(size_t n, const Vector3f* vertexs, const Vector3f* normals, const Color4f& color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Color4f& color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& na, const Vector3f& nb, const Vector3f& nc, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& a, const Vector3f& b, const Vector3f& c, const Vector3f& d, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f* vertexs, const Vector3f& n, const Color4f& color) const = 0;
	virtual void drawQuad(const Vector3f& pos, float w, float h, const Quaternion& rotation, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, float angle, const Vector3f& axis, const Color4f& color) const = 0;
	virtual void drawBox(const Vector3f& pos, const Vector3f& size, const Quaternion& rotation, const Color4f& color) const = 0;
	virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const = 0;
	virtual void drawSphere(const Vector3f& pos, const float r, const Quaternion& q, const Color4f& color) const = 0;
	virtual void drawSphereT(const Vector3f& pos, const float r, const Color4f& color) const = 0;
	virtual void drawVBO() const = 0;
	//virtual void drawSphere(const Vector3f& pos, const float r, const Color4f& color) const = 0;
protected:
	//virtual bool createWindow() = 0;
	virtual void TextureUpdate() = 0;
	virtual void LightUpdate() = 0;
};

/*
inline Render::Render(InitData& initData)
: width(initData.width)
, height(initData.height)
, fullscreen(initData.fullscreen)
, light(initData.light)
, camera(initData.pos, initData.aangle, initData.axis)
, moveScale(initData.moveScale)
, rotateScale(initData.rotateScale)
{
}
*/

inline void Render::RotateCamera(const Quaternion &q)
{
	//std::cout << "one deg " << radToDeg(q.GetAngle()) << ' ' << q.GetAxis() << std::endl;
	//Quaternion q_ = q * rotateScale;
	//std::cout << "one deg scale " << radToDeg(q_.GetAngle()) << ' ' << q_.GetAxis() << std::endl;
	camera.Rotate(q);
}

inline void Render::MoveCamera(const Vector3f &s)
{
	camera.Move(s * moveScale);
}

inline void Render::MoveCameraUD(float s)
{
	camera.MoveUD(s * moveScale);
}

inline void Render::MoveCameraLR(float s)
{
	camera.MoveLR(s * moveScale);
}

inline void Render::MoveCameraNF(float s)
{
	camera.MoveNF(s * moveScale);
}