#pragma once
#include "utils.h"

namespace MathX
{
	class Matrix3
	{
	public:
		union
		{
			struct
			{
				Vector3 xAxis;
				Vector3 yAxis;
				Vector3 zAxis;
			};

			struct
			{
				Vector3 right;
				Vector3 up;
				Vector3 backward;
			};

			struct
			{
				float m1, m2, m3,
					m4, m5, m6,
					m7, m8, m9;
			};

			Vector3 axis[3];
			float m[9];
			float mm[3][3];
		};

		Matrix3();
		Matrix3(const Matrix3& z);
		Matrix3(float *ptr);
		Matrix3(float m1, float m2, float m3,
			float m4, float m5, float m6,
			float m7, float m8, float m9);
		~Matrix3();

		Matrix3 Identity();
		Matrix3 GetTranslation(float x, float y);
		Matrix3 GetTranslation(const Vector2 &v);
		void Translate(float x, float y);
		void Translate(const Vector2 &v);
		void SetRotateX(float rot);
		void SetRotateY(float rot);
		void SetRotateZ(float rot);
		void Rotate(float angle);
		Matrix3 GetRotation(float rot);
		Matrix3 GetScale(float xScale, float yScale);
		void Scale(float xScale, float yScale);
		//Rebuild the matrix
		void Set(float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9);
		//Rebuild the matrix - expects pointer to array of 9 floats
		void Set(float *ptr);
		void Transpose();
		Matrix3 GetTranspose() const;

	#pragma region Operators
		Matrix3 operator + (const Matrix3 &rhs)
		{
			Matrix3 tempMatrix = *this;

			for (int i = 0; i < 9; i++)
			{
				tempMatrix.m[i] += rhs.m[i];
			}

			return tempMatrix;
		}
		Matrix3 operator + (const float &rhs)
		{
			Matrix3 tempMatrix = *this;

			for (int i = 0; i < 9; i++)
			{
				tempMatrix.m[i] += rhs;
			}


			return tempMatrix;
		}
		Matrix3 operator += (const Matrix3 &rhs)
		{
			(*this) = (*this) + rhs;
			return (*this);
		}
		Matrix3 operator += (const float &rhs)
		{
			(*this) = (*this) + rhs;
			return (*this);
		}
		Matrix3 operator - (const Matrix3 &rhs)
		{
			Matrix3 tempMatrix = *this;

			for (int i = 0; i < 9; i++)
			{

				tempMatrix.m[i] -= rhs.m[i];

			}

			return tempMatrix;
		}
		Matrix3 operator - (const float &rhs)
		{
			Matrix3 tempMatrix = *this;

			for (int i = 0; i < 9; i++)
			{
				tempMatrix.m[i] -= rhs;
			}

			return tempMatrix;
		}
		Matrix3 operator -= (const Matrix3 &rhs)
		{
			(*this) = (*this) - rhs;
			return (*this);
		}
		Matrix3 operator -= (const float &rhs)
		{
			(*this) = (*this) - rhs;
			return (*this);
		}
		Matrix3	operator * (const Matrix3 &rhs)
		{
			Matrix3 tempMatrix;

			tempMatrix.m[0] = m[0] * rhs.m[0] + m[3] * rhs.m[1] + m[6] * rhs.m[2];
			tempMatrix.m[3] = m[0] * rhs.m[3] + m[3] * rhs.m[4] + m[6] * rhs.m[5];
			tempMatrix.m[6] = m[0] * rhs.m[6] + m[3] * rhs.m[7] + m[6] * rhs.m[8];
			tempMatrix.m[1] = m[1] * rhs.m[0] + m[4] * rhs.m[1] + m[7] * rhs.m[2];
			tempMatrix.m[4] = m[1] * rhs.m[3] + m[4] * rhs.m[4] + m[7] * rhs.m[5];
			tempMatrix.m[7] = m[1] * rhs.m[6] + m[4] * rhs.m[7] + m[7] * rhs.m[8];
			tempMatrix.m[2] = m[2] * rhs.m[0] + m[5] * rhs.m[1] + m[8] * rhs.m[2];
			tempMatrix.m[5] = m[2] * rhs.m[3] + m[5] * rhs.m[4] + m[8] * rhs.m[5];
			tempMatrix.m[8] = m[2] * rhs.m[6] + m[5] * rhs.m[7] + m[8] * rhs.m[8];

			return tempMatrix;
		}
		Matrix3	operator * (const float &rhs)
		{
			Matrix3 tempMatrix = *this;

			for (int i = 0; i < 9; i++)
				tempMatrix.m[i] *= rhs;

			return tempMatrix;
		}
		Matrix3 operator = (const Matrix3 &rhs)
		{
			if (this == &rhs)
				return *this;

			for (int i = 0; i < 9; i++)
				m[i] = rhs.m[i];

			return *this;
		}
		Matrix3 operator = (const float rhs[9])
		{
			if (this->m == rhs)
				return *this;

			for (int i = 0; i < 9; i++)
				m[i] = rhs[i];

			return *this;
		}
		Matrix3 operator *= (const Matrix3 &rhs)
		{
			(*this) = (*this) * rhs;
			return (*this);
		}
		Matrix3 operator *= (const float &rhs)
		{
			(*this) = (*this) * rhs;
			return (*this);
		}
		bool operator != (const Matrix3 &rhs)
		{
			for (int i = 0; i < 9; i++)
				if (m[i] != rhs.m[i])
					return true;

			return false;
		}
		bool operator == (const Matrix3 &rhs) const
		{
			bool check[9];

			Matrix3 temp1 = rhs;
			Matrix3 temp2 = Matrix3(*this);

			for (int i = 0; i < 9; ++i)
			{
				//Calculates the difference.
				float diff1 = fabs(temp1.m[i] - temp2.m[i]);
				temp1.m[i] = fabs(temp1.m[i]);
				temp2.m[i] = fabs(temp2.m[i]);

				//Finds the largest of the 2 values.
				float largest1 = (temp2.m[i] > temp1.m[i]) ? temp2.m[i] : temp1.m[i];

				if (diff1 <= largest1 * FLOATMIN)
					check[i] = true;
				else check[i] = false;
			}

			bool result = false;
			for (int i = 0; i < 9; ++i) if (check[i]) result = true;
			return result;
		}

		Matrix3 operator + (const Vector3 &rhs)
		{
			Matrix3 tempMatrix = *this;

			tempMatrix.m[0] += rhs.X;
			tempMatrix.m[1] += rhs.X;
			tempMatrix.m[2] += rhs.X;

			tempMatrix.m[3] += rhs.Y;
			tempMatrix.m[4] += rhs.Y;
			tempMatrix.m[5] += rhs.Y;

			tempMatrix.m[6] += rhs.Z;
			tempMatrix.m[7] += rhs.Z;
			tempMatrix.m[8] += rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator += (const Vector3 &rhs)
		{
			(*this) = (*this) + rhs;
			return (*this);
		}
		Matrix3 operator - (const Vector3 &rhs)
		{
			Matrix3 tempMatrix = *this;

			tempMatrix.m[0] -= rhs.X;
			tempMatrix.m[1] -= rhs.X;
			tempMatrix.m[2] -= rhs.X;

			tempMatrix.m[3] -= rhs.Y;
			tempMatrix.m[4] -= rhs.Y;
			tempMatrix.m[5] -= rhs.Y;

			tempMatrix.m[6] -= rhs.Z;
			tempMatrix.m[7] -= rhs.Z;
			tempMatrix.m[8] -= rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator -= (const Vector3 &rhs)
		{
			(*this) = (*this) - rhs;
			return (*this);
		}
		Matrix3	operator * (const Vector3 &rhs)
		{
			Matrix3 tempMatrix;

			tempMatrix.m[0] = m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z;
			tempMatrix.m[3] = m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z;
			tempMatrix.m[6] = m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z;
			tempMatrix.m[1] = m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z;
			tempMatrix.m[4] = m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z;
			tempMatrix.m[7] = m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z;
			tempMatrix.m[2] = m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z;
			tempMatrix.m[5] = m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z;
			tempMatrix.m[8] = m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator = (const Vector3 &rhs)
		{
			Matrix3 tempMatrix = *this;

			tempMatrix.m[0] = rhs.X;
			tempMatrix.m[1] = rhs.X;
			tempMatrix.m[2] = rhs.X;

			tempMatrix.m[3] = rhs.Y;
			tempMatrix.m[4] = rhs.Y;
			tempMatrix.m[5] = rhs.Y;

			tempMatrix.m[6] = rhs.Z;
			tempMatrix.m[7] = rhs.Z;
			tempMatrix.m[8] = rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator *= (const Vector3 &rhs)
		{
			(*this) = (*this) * rhs;
			return (*this);
		}

		Matrix3 operator + (const Vector4 &rhs)
		{
			Matrix3 tempMatrix = *this;

			tempMatrix.m[0] += rhs.X;
			tempMatrix.m[1] += rhs.X;
			tempMatrix.m[2] += rhs.X;

			tempMatrix.m[3] += rhs.Y;
			tempMatrix.m[4] += rhs.Y;
			tempMatrix.m[5] += rhs.Y;

			tempMatrix.m[6] += rhs.Z;
			tempMatrix.m[7] += rhs.Z;
			tempMatrix.m[8] += rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator += (const Vector4 &rhs)
		{
			(*this) = (*this) + rhs;
			return (*this);
		}
		Matrix3 operator - (const Vector4 &rhs)
		{
			Matrix3 tempMatrix = *this;

			tempMatrix.m[0] -= rhs.X;
			tempMatrix.m[1] -= rhs.X;
			tempMatrix.m[2] -= rhs.X;

			tempMatrix.m[3] -= rhs.Y;
			tempMatrix.m[4] -= rhs.Y;
			tempMatrix.m[5] -= rhs.Y;

			tempMatrix.m[6] -= rhs.Z;
			tempMatrix.m[7] -= rhs.Z;
			tempMatrix.m[8] -= rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator -= (const Vector4 &rhs)
		{
			(*this) = (*this) - rhs;
			return (*this);
		}
		Matrix3	operator * (const Vector4 &rhs)
		{
			Matrix3 tempMatrix;

			tempMatrix.m[0] = m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z;
			tempMatrix.m[3] = m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z;
			tempMatrix.m[6] = m[0] * rhs.X + m[3] * rhs.Y + m[6] * rhs.Z;
			tempMatrix.m[1] = m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z;
			tempMatrix.m[4] = m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z;
			tempMatrix.m[7] = m[1] * rhs.X + m[4] * rhs.Y + m[7] * rhs.Z;
			tempMatrix.m[2] = m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z;
			tempMatrix.m[5] = m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z;
			tempMatrix.m[8] = m[2] * rhs.X + m[5] * rhs.Y + m[8] * rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator = (const Vector4 &rhs)
		{
			Matrix3 tempMatrix = *this;

			tempMatrix.m[0] = rhs.X;
			tempMatrix.m[1] = rhs.X;
			tempMatrix.m[2] = rhs.X;

			tempMatrix.m[3] = rhs.Y;
			tempMatrix.m[4] = rhs.Y;
			tempMatrix.m[5] = rhs.Y;

			tempMatrix.m[6] = rhs.Z;
			tempMatrix.m[7] = rhs.Z;
			tempMatrix.m[8] = rhs.Z;

			return tempMatrix;
		}
		Matrix3 operator *= (const Vector4 &rhs)
		{
			(*this) = (*this) * rhs;
			return (*this);
		}
#pragma endregion Matrix3 Operators
	};
}