#ifndef Vector2_H
#define Vector2_H

template <typename T>
class Vector2
{
private:
	T X, Y;
public:

	Vector2(T x = 0, T y = 0) : X(x), Y(y){}

	T GetX() const { return X; }
	T GetY() const { return Y; }

	void SetX(const T& value) { X = value; }
	void SetY(const T& value) { Y = value; }

	void AddX(const T& value) { X += value; }
	void AddY(const T& value) { Y += value; }
};



#endif