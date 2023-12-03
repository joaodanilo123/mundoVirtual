#pragma once
#include<glm/glm.hpp>

class Primitive
{
public:

	//Constructors
	Primitive();
	virtual ~Primitive();

	//Functions
	void Create();
	virtual void Draw() = 0;

	//Setters
	void SetPosition(float x, float y, float z);

	//Getters
	glm::mat4 GetPosition() const;
	unsigned int GetModelVBO() const;

protected:
	unsigned int _VAO;
	unsigned int _EBO;
	unsigned int _positionVBO;
	unsigned int _colorVBO;
	unsigned int _modelVBO;

	unsigned int _total;
	
	glm::vec3 _position;
	glm::mat4 _model;

	void CreateBuffers();
	virtual void FillBuffers()=0;
	virtual void LinkBuffers()=0;
	

	void UpdatePosition();

};


class Cube:public Primitive
{
public: 
	Cube(unsigned int totalCubes);
	void Draw();

private:
	void FillBuffers();
	void LinkBuffers();

};

class Rectangle:public Primitive
{
public: 
	Rectangle(unsigned int totalRectangles);
	void Draw();

private:
	void FillBuffers();
	void LinkBuffers();

};

class Pyramid :public Primitive
{
public:
	Pyramid(unsigned int totalPyramids);
	void Draw();

private:
	void FillBuffers();
	void LinkBuffers();
};

class Pentahedron:public Primitive
{
public: 
	Pentahedron(unsigned int totalPentahedron);
	void Draw();

private:
	void FillBuffers();
	void LinkBuffers();

};

class Diamond:public Primitive
{
public: 
	Diamond(unsigned int totalHexahedron);
	void Draw();

private:
	void FillBuffers();
	void LinkBuffers();

};

class Terrain :public Primitive
{
public:
	Terrain(float side = 50.f);
	void Draw();

private:
	float _side;
	unsigned int _totalIndices;
	void FillBuffers();
	void LinkBuffers();
};