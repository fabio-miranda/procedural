#ifndef VECTOR3_H
#define VECTOR3_H

template <typename T>
class Vector3
{
private:
	T X, Y, Z;
public:

	Vector3(T x = 0, T y = 0, T z = 0) : X(x), Y(y), Z(z) {}

	T GetX() const { return X; }
	T GetY() const { return Y; }
	T GetZ() const { return Z; }

	void SetX(const T& value) { X = value; }
	void SetY(const T& value) { Y = value; }
	void SetZ(const T& value) { Z = value; }

	void AddX(const T& value) { X += value; }
	void AddY(const T& value) { Y += value; }
	void AddZ(const T& value) { Z += value; }


	bool equals(Vector3<T> value){
		if(this->X == value.GetX() && this->Y == value.GetY() && this->Z == value.GetZ())
			return true;
		else
			return false;


	}

};



#endif