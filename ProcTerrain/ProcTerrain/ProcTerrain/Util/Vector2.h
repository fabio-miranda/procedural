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

	void Add(const Vector2<T> &vec){
		this->AddX(vec.GetX());
		this->AddY(vec.GetY());

	}

	void Sub(const Vector2<T> &vec){
		this->AddX(-vec.GetX());
		this->AddY(-vec.GetY());

	}

	void Mult(const float mult){
		this->X = this->X * mult;
		this->Y = this->Y * mult;

	}

	float Dot(const Vector2<T> &vec){
		return this->X * vec.GetX() + this->Y * vec.GetY();

	}

	void Floor(){
		floor(this->X);
		floor(this->Y);
	}
};



#endif