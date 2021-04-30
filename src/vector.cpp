#include "vector.hpp"

Vector3::Vector3() : Vector3(0.f, 0.f, 0.f) {}

Vector3::Vector3(float x) : Vector3(x, 0.f, 0.f) {}

Vector3::Vector3(float x, float y) : Vector3(x, y, 0.f) {}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::rotate(Matrix rotationMatrix, Vector3 origin)
{
	this->operator-=(origin);

	auto result = matrixVectorMultiplication(rotationMatrix, this);

	this->x = result[0];
	this->y = result[1];
	this->z = result[2];

	this->operator+=(origin);
}

std::string Vector3::toString()
{
	return std::string(
		"x: " + std::to_string(this->x) +
		"  y: " + std::to_string(this->y) +
		"  z: " + std::to_string(this->z)
	);
}

float Vector3::sqLength()
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vector3::length()
{
	return sqrtf(this->sqLength());
}

void Vector3::operator+=(Vector3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vector3::operator+=(float amount)
{
	this->x += amount;
	this->y += amount;
	this->z += amount;
}

void Vector3::operator-=(Vector3 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void Vector3::operator-=(float amount)
{
	this->x -= amount;
	this->y -= amount;
	this->z -= amount;
}

Vector3 Vector3::operator+(Vector3 v)
{
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator-(Vector3 v)
{
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator*(float amount)
{
	return Vector3(this->x * amount, this->y * amount, this->z * amount);
}

Vector3 Vector3::operator/(float amount)
{
	return Vector3(this->x / amount, this->y / amount, this->z / amount);
}