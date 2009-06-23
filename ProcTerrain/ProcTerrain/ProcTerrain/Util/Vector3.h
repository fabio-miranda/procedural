#ifndef Vector3_H
#define Vector3_H


template <typename T>
class Vector3
{
private:
	T list[3];
public:

	Vector3(T x = 0, T y = 0, T z = 0) {list[0] = x; list[1] = y; list[2] = z;}

	T GetX() const { return list[0]; }
	T GetY() const { return list[1]; }
	T GetZ() const { return list[2]; }

	void SetX(const T& value) { list[0] = value; }
	void SetY(const T& value) { list[2] = value; }
	void SetZ(const T& value) { list[3] = value; }

	void AddX(const T& value) { list[0] += value; }
	void AddY(const T& value) { list[1] += value; }
	void AddZ(const T& value) { list[2] += value; }


	bool equals(Vector3<T> value){
		if(list[0] == value.GetX() && list[1] == value.GetY() && list[2] == value.GetZ())
			return true;
		else
			return false;


	}

	void Add(const Vector3<T> &vec){
		this->AddX(vec.GetX());
		this->AddY(vec.GetY());
		this->AddZ(vec.GetZ());

	}

	void Add(float add){
		this->AddX(add);
		this->AddY(add);
		this->AddZ(add);
	}

	void Sub(const Vector3<T> &vec){
		this->AddX(-vec.GetX());
		this->AddY(-vec.GetY());
		this->AddZ(-vec.GetZ());

	}

	void Mult(const float mult){
		this->list[0] = this->list[0] * mult;
		this->list[1] = this->list[1] * mult;
		this->list[2] = this->list[2] * mult;
	}

	float Dot(const Vector3<T> &vec){
		return this->list[0] * vec.GetX() + this->list[1] * vec.GetY() + this->list[2] * vec.GetZ();

	}

	void Floor(){
		this->list[0] = floor(this->list[0]);
		this->list[1] = floor(this->list[1]);
		this->list[2] = floor(this->list[2]);
	}



};



#endif