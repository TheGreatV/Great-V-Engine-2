#pragma region Include

#pragma once

#include "Header.hpp"
#include "Mathematics.hpp"

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	namespace Helpers
	{
		namespace Transformation
		{
			namespace Dimension3
			{
				class Position;
				class Angle;
				class Size;
				class Scale;
				class Velocity;
				class Torque;

				class RotationMatrix;
				class ViewMatrix;
				class ModelMatrix;
				class HierarchyMatrix;
			}
			
			namespace D3 = Dimension3;
		}
	}

	namespace Helpers
	{
		namespace Transformation
		{
			namespace Dimension3
			{
				class Position
				{
				public:
					using Value = Vec3;
				protected:
					Value position;
				public:
					inline Position() = default;
					inline Position(const Value& position_):
						position(position_)
					{
					}
					inline Position(const Position&) = default;
				public:
					inline Position& operator = (const Position& source) = default;
				public:
					inline Value GetPosition() const
					{
						return position;
					}
					inline void SetPosition(const Value& position_)
					{
						position = position_;
					}
				};
				class Angle
				{
				public:
					using Value = Vec3;
				protected:
					Value angle;
				public:
					inline Angle() = default;
					inline Angle(const Value& angle_):
						angle(angle_)
					{
					}
					inline Angle(const Angle&) = default;
				public:
					inline Angle& operator = (const Angle& source) = default;
				public:
					inline Value GetAngle() const
					{
						return angle;
					}
					inline void SetAngle(const Value& angle_)
					{
						angle = angle_;
					}
				};
				class Size
				{
				public:
					using Value = Vec3;
				protected:
					Value size;
				public:
					inline Size() = default;
					inline Size(const Value& size_):
						size(size_)
					{
					}
					inline Size(const Size&) = default;
				public:
					inline Size& operator = (const Size& source) = default;
				public:
					inline Value GetSize() const
					{
						return size;
					}
					inline void SetSize(const Value& size_)
					{
						size = size_;
					}
				};
				class Scale
				{
				public:
					using Value = Vec3;
				protected:
					Value scale;
				public:
					inline Scale() = default;
					inline Scale(const Value& scale_):
						scale(scale_)
					{
					}
					inline Scale(const Scale&) = default;
				public:
					inline Scale& operator = (const Scale& source) = default;
				public:
					inline Value GetScale() const
					{
						return scale;
					}
					inline void SetScale(const Value& scale_)
					{
						scale = scale_;
					}
				};
				class Velocity
				{
				public:
					using Value = Vec3;
				protected:
					Value velocity;
				public:
					inline Velocity() = default;
					inline Velocity(const Value& velocity_):
						velocity(velocity_)
					{
					}
					inline Velocity(const Velocity&) = default;
				public:
					inline Velocity& operator = (const Velocity& source) = default;
				public:
					inline Value GetVelocity() const
					{
						return velocity;
					}
					inline void SetVelocity(const Value& velocity_)
					{
						velocity = velocity_;
					}
				};
				class Torque
				{
				public:
					using Value = Vec3;
				protected:
					Value torque;
				public:
					inline Torque() = default;
					inline Torque(const Value& torque_):
						torque(torque_)
					{
					}
					inline Torque(const Torque&) = default;
				public:
					inline Torque& operator = (const Torque& source) = default;
				public:
					inline Value GetTorque() const
					{
						return torque;
					}
					inline void SetTorque(const Value& torque_)
					{
						torque = torque_;
					}
				};

				class RotationMatrix:
					protected Angle
				{
				public:
					using Value = Mat3;
				protected:
					using UpdateFlags = UInt8;
					enum class UpdateFlagBits: UpdateFlags
					{
						None = 0x00,
						DirectRotateMatrixUpdated = 0x01,
						InverseRotateMatrixUpdated = 0x02,
					};
				protected:
					mutable UpdateFlags updateFlags = (UpdateFlags)UpdateFlagBits::None;
					mutable Value directRotateMatrix;
					mutable Value inverseRotateMatrix;
				public:
					inline RotationMatrix() = default;
					inline explicit RotationMatrix(const Angle& angle_):
						Angle(angle_)
					{
					}
					inline explicit RotationMatrix(const Angle::Value& angle_):
						Angle(angle_)
					{
					}
				public:
					inline void SetAngle(const Angle::Value& angle_)
					{
						if (angle_ != angle)
						{
							angle = angle_;
							updateFlags &= ~((UpdateFlags)UpdateFlagBits::DirectRotateMatrixUpdated | (UpdateFlags)UpdateFlagBits::InverseRotateMatrixUpdated);
						}
					}
					inline Angle::Value GetAngle() const
					{
						return Angle::GetAngle();
					}
					inline Value GetRotateMatrix() const
					{
						if ((updateFlags & (UpdateFlags)UpdateFlagBits::DirectRotateMatrixUpdated) == 0)
						{
							updateFlags |= (UpdateFlags)UpdateFlagBits::DirectRotateMatrixUpdated;
							directRotateMatrix = RotateZXY3(angle);
						}

						return directRotateMatrix;
					}
					inline Value GetRotateInverseMatrix() const
					{
						if ((updateFlags & (UpdateFlags)UpdateFlagBits::InverseRotateMatrixUpdated) == 0)
						{
							updateFlags |= (UpdateFlags)UpdateFlagBits::InverseRotateMatrixUpdated;
							inverseRotateMatrix = RotateYXZ3(-angle);
						}

						return inverseRotateMatrix;
					}
				public:
					inline Value GetRMat() const
					{
						return GetRotateMatrix();
					}
					inline Value GetRIMat() const
					{
						return GetRotateInverseMatrix();
					}
				};
				class ViewMatrix:
					protected Position,
					protected RotationMatrix
				{
				public:
					using Value = Mat4;
				protected:
					enum class UpdateFlagBits: RotationMatrix::UpdateFlags
					{
						None = 0x00,
						DirectRotateMatrixUpdated = 0x01,
						InverseRotateMatrixUpdated = 0x02,
						DirectViewMatrixUpdated = 0x04,
						InverseViewMatrixUpdated = 0x08,
					};
					mutable Value directViewMatrix;
					mutable Value inverseViewMatrix;
				public:
					inline ViewMatrix() = default;
					inline ViewMatrix(const Position& position_, const Angle& angle_):
						Position(position_),
						RotationMatrix(angle_)
					{
					}
					inline ViewMatrix(const Position::Value& position_, const Angle::Value& angle_) :
						Position(position_),
						RotationMatrix(angle_)
					{
					}
				public:
					inline void SetAngle(const Angle::Value& angle_)
					{
						if (angle_ != angle)
						{
							angle = angle_;
							updateFlags &= ~(
								(UpdateFlags)UpdateFlagBits::DirectViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::DirectRotateMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseRotateMatrixUpdated);
						}
					}
					inline Angle::Value GetAngle() const
					{
						return RotationMatrix::GetAngle();
					}
					inline RotationMatrix::Value GetRotateMatrix() const
					{
						return RotationMatrix::GetRotateMatrix();
					}
					inline RotationMatrix::Value GetRotateInverseMatrix() const
					{
						return RotationMatrix::GetRotateInverseMatrix();
					}
					inline void SetPosition(const Position::Value& position_)
					{
						if (position_ != position)
						{
							position = position_;
							updateFlags &= ~(
								(UpdateFlags)UpdateFlagBits::DirectViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseViewMatrixUpdated);
						}
					}
					inline Position::Value GetPosition() const
					{
						return Position::GetPosition();
					}
					inline Value GetViewMatrix() const
					{
						if ((updateFlags & (UpdateFlags)UpdateFlagBits::DirectViewMatrixUpdated) == 0)
						{
							updateFlags |= (UpdateFlags)UpdateFlagBits::DirectViewMatrixUpdated;
							directViewMatrix = To4(GetRotateInverseMatrix()) * Move4(-position);
						}

						return directViewMatrix;
					}
					inline Value GetViewInverseMatrix() const
					{
						if ((updateFlags & (UpdateFlags)UpdateFlagBits::InverseViewMatrixUpdated) == 0)
						{
							updateFlags |= (UpdateFlags)UpdateFlagBits::InverseViewMatrixUpdated;
							inverseViewMatrix = Move4(position) * To4(GetRotateMatrix());
						}

						return inverseViewMatrix;
					}
					inline void Rotate(const Angle::Value& angle_)
					{
						SetAngle(GreatVEngine2::GetAngle(GetRotateMatrix() * RotateZXY3(angle_)));
					}
					inline void Move(const Position::Value& position_)
					{
						SetPosition((GetViewInverseMatrix() * Vec4(position_, 1.0f)).xyz);
					}
				public:
					inline RotationMatrix::Value GetRMat() const
					{
						return RotationMatrix::GetRMat();
					}
					inline RotationMatrix::Value GetRIMat() const
					{
						return RotationMatrix::GetRIMat();
					}
					inline Value GetVMat() const
					{
						return GetViewMatrix();
					}
					inline Value GetVIMat() const
					{
						return GetViewInverseMatrix();
					}
				};
				class ModelMatrix:
					protected Scale,
					protected ViewMatrix
				{
				public:
					using Value = Mat4;
				protected:
					enum class UpdateFlagBits: RotationMatrix::UpdateFlags
					{
						None = 0x00,
						DirectRotateMatrixUpdated = 0x01,
						InverseRotateMatrixUpdated = 0x02,
						DirectViewMatrixUpdated = 0x04,
						InverseViewMatrixUpdated = 0x08,
						DirectModelMatrixUpdated = 0x10,
						InverseModelMatrixUpdated = 0x20,
					};
					mutable Value directModelMatrix;
					mutable Value inverseModelMatrix;
				public:
					inline ModelMatrix() = default;
					inline ModelMatrix(const Position& position_, const Angle& angle_, const Scale& scale_):
						Scale(scale_),
						ViewMatrix(position_, angle_)
					{
					}
					inline ModelMatrix(const Position::Value& position_, const Angle::Value& angle_, const Scale::Value& scale_) :
						Scale(scale_),
						ViewMatrix(position_, angle_)
					{
					}
				public:
					inline void SetAngle(const Angle::Value& angle_)
					{
						if (angle_ != angle)
						{
							angle = angle_;
							updateFlags &= ~(
								(UpdateFlags)UpdateFlagBits::DirectViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::DirectRotateMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseRotateMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::DirectModelMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseModelMatrixUpdated);
						}
					}
					inline Angle::Value GetAngle() const
					{
						return ViewMatrix::GetAngle();
					}
					inline RotationMatrix::Value GetRotateMatrix() const
					{
						return ViewMatrix::GetRotateMatrix();
					}
					inline RotationMatrix::Value GetRotateInverseMatrix() const
					{
						return ViewMatrix::GetRotateInverseMatrix();
					}
					inline void SetPosition(const Position::Value& position_)
					{
						if (position_ != position)
						{
							position = position_;
							updateFlags &= ~(
								(UpdateFlags)UpdateFlagBits::DirectViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseViewMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::DirectModelMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseModelMatrixUpdated);
						}
					}
					inline Position::Value GetPosition() const
					{
						return Position::GetPosition();
					}
					inline ViewMatrix::Value GetViewMatrix() const
					{
						return ViewMatrix::GetViewMatrix();
					}
					inline ViewMatrix::Value GetViewInverseMatrix() const
					{
						return ViewMatrix::GetViewInverseMatrix();
					}
					inline Scale::Value GetScale() const
					{
						return Scale::GetScale();
					}
					inline void SetScale(const Scale::Value& scale_)
					{
						if (scale_ != scale)
						{
							scale = scale_;
							updateFlags &= ~(
								(UpdateFlags)UpdateFlagBits::DirectModelMatrixUpdated |
								(UpdateFlags)UpdateFlagBits::InverseModelMatrixUpdated);
						}
					}
					inline Value GetModelMatrix() const
					{
						if ((updateFlags & (UpdateFlags)UpdateFlagBits::DirectModelMatrixUpdated) == 0)
						{
							updateFlags |= (UpdateFlags)UpdateFlagBits::DirectModelMatrixUpdated;
							directModelMatrix = GetViewInverseMatrix() * Scale4(scale);
						}

						return directModelMatrix;
					}
					inline Value GetModelInverseMatrix() const
					{
						if ((updateFlags & (UpdateFlags)UpdateFlagBits::InverseModelMatrixUpdated) == 0)
						{
							updateFlags |= (UpdateFlags)UpdateFlagBits::InverseModelMatrixUpdated;
							inverseModelMatrix = Scale4(1.0f / scale) * GetViewMatrix();
						}

						return inverseModelMatrix;
					}
					inline void Rotate(const Angle::Value& angle_)
					{
						SetAngle(GreatVEngine2::GetAngle(GetRotateMatrix() * RotateZXY3(angle_)));
					}
					inline void Move(const Position::Value& position_)
					{
						SetPosition((GetModelMatrix() * Vec4(position_, 1.0f)).xyz);
					}
				public:
					inline RotationMatrix::Value GetRMat() const
					{
						return RotationMatrix::GetRMat();
					}
					inline RotationMatrix::Value GetRIMat() const
					{
						return RotationMatrix::GetRIMat();
					}
					inline ViewMatrix::Value GetVMat() const
					{
						return ViewMatrix::GetVMat();
					}
					inline ViewMatrix::Value GetVIMat() const
					{
						return ViewMatrix::GetVIMat();
					}
					inline Value GetMMat() const
					{
						return GetModelMatrix();
					}
					inline Value GetMIMat() const
					{
						return GetModelInverseMatrix();
					}
				};
				class HierarchyMatrix:
					protected ModelMatrix
				{
				public:
					using Parent = HierarchyMatrix*;
				protected:
					Parent parent;
				public:
					inline HierarchyMatrix() = default;
					inline HierarchyMatrix(const Position& position_, const Angle& angle_, const Scale& scale_, const Parent& parent_ = nullptr):
						ModelMatrix(position_, angle_, scale_),
						parent(parent_)
					{
					}
					inline HierarchyMatrix(const Position::Value& position_, const Angle::Value& angle_, const Scale::Value& scale_, const Parent& parent_ = nullptr) :
						ModelMatrix(position_, angle_, scale_),
						parent(parent_)
					{
					}
				public:
					inline void SetParent(Parent parent_)
					{
						parent = parent_;
					}
					inline Parent GetParent() const
					{
						return parent;
					}
				public:
					inline void SetLocalAngle(const Angle::Value& angle_)
					{
						ModelMatrix::SetAngle(angle_);
					}
					inline void SetLocalPosition(const Position::Value& position_)
					{
						ModelMatrix::SetPosition(position_);
					}
					inline void SetLocalScale(const Scale::Value& scale_)
					{
						ModelMatrix::SetScale(scale_);
					}
					inline Angle::Value GetLocalAngle() const
					{
						return ModelMatrix::GetAngle();
					}
					inline Position::Value GetLocalPosition() const
					{
						return ModelMatrix::GetPosition();
					}
					inline Scale::Value GetLocalScale() const
					{
						return ModelMatrix::GetScale();
					}
					inline RotationMatrix::Value GetLocalRotateMatrix() const
					{
						return ModelMatrix::GetRotateMatrix();
					}
					inline RotationMatrix::Value GetLocalRotateInverseMatrix() const
					{
						return ModelMatrix::GetRotateInverseMatrix();
					}
					inline ViewMatrix::Value GetLocalViewMatrix() const
					{
						return ModelMatrix::GetViewMatrix();
					}
					inline ViewMatrix::Value GetLocalViewInverseMatrix() const
					{
						return ModelMatrix::GetViewInverseMatrix();
					}
					inline ModelMatrix::Value GetLocalModelMatrix() const
					{
						return ModelMatrix::GetModelMatrix();
					}
					inline ModelMatrix::Value GetLocalModelInverseMatrix() const
					{
						return ModelMatrix::GetModelInverseMatrix();
					}
				public:
					inline RotationMatrix::Value GetLRMat() const
					{
						return ModelMatrix::GetRMat();
					}
					inline RotationMatrix::Value GetLRIMat() const
					{
						return ModelMatrix::GetRIMat();
					}
					inline ViewMatrix::Value GetLVMat() const
					{
						return ModelMatrix::GetVMat();
					}
					inline ViewMatrix::Value GetLVIMat() const
					{
						return ModelMatrix::GetVIMat();
					}
					inline Value GetLMMat() const
					{
						return ModelMatrix::GetMMat();
					}
					inline Value GetLMIMat() const
					{
						return ModelMatrix::GetMIMat();
					}
					inline void LocalRotate(const Angle::Value& angle_)
					{
						SetLocalAngle(GreatVEngine2::GetAngle(GetLocalRotateMatrix() * RotateZXY3(angle_)));
					}
					inline void LocalMove(const Position::Value& position_)
					{
						SetLocalPosition((GetLocalModelMatrix() * Vec4(position_, 1.0f)).xyz);
					}
				public:
					inline void SetAngle(const Angle::Value& angle_);
					inline void SetPosition(const Position::Value& position_);
					inline void SetScale(const Scale::Value& scale_);
					inline Angle::Value GetAngle() const
					{
						// TODO: ensure that this is OK
						return GreatVEngine2::GetAngle(parent ?
							parent->GetRotateMatrix() * GetLocalRotateMatrix() :
							GetLocalRotateMatrix());
					}
					inline Position::Value GetPosition() const
					{
						if (parent)
						{
							auto v = parent->GetMMat() * Vec4(position, 1.0f);

							return Vec3(v.x, v.y, v.z);
						}

						return position;
					}
					inline Scale::Value GetScale() const;
					inline RotationMatrix::Value GetRotateMatrix() const
					{
						return parent ?
							parent->GetRotateMatrix() * GetLocalRotateMatrix() :
							GetLocalRotateMatrix();
					}
					inline RotationMatrix::Value GetRotateInverseMatrix() const
					{
						return parent ?
							GetLocalRotateInverseMatrix() * parent->GetRotateInverseMatrix() :
							GetLocalRotateInverseMatrix();
					}
					inline ViewMatrix::Value GetViewMatrix() const
					{
						return parent ?
							parent->GetViewMatrix() * GetLocalViewMatrix() :
							GetLocalViewMatrix();
					}
					inline ViewMatrix::Value GetViewInverseMatrix() const
					{
						return parent ?
							GetLocalViewInverseMatrix() * parent->GetViewInverseMatrix() :
							GetLocalViewInverseMatrix();
					}
					inline Value GetModelMatrix() const
					{
						return parent ?
							parent->GetModelMatrix() * GetLocalModelMatrix() :
							GetLocalModelMatrix();
					}
					inline Value GetModelInverseMatrix() const
					{
						return parent ?
							GetLocalModelInverseMatrix() * parent->GetModelInverseMatrix() :
							GetLocalModelInverseMatrix();
					}
				public:
					inline RotationMatrix::Value GetRMat() const
					{
						return GetRotateMatrix();
					}
					inline RotationMatrix::Value GetRIMat() const
					{
						return GetRotateInverseMatrix();
					}
					inline ViewMatrix::Value GetVMat() const
					{
						return GetViewMatrix();
					}
					inline ViewMatrix::Value GetVIMat() const
					{
						return GetViewInverseMatrix();
					}
					inline Value GetMMat() const
					{
						return GetModelMatrix();
					}
					inline Value GetMIMat() const
					{
						return GetModelInverseMatrix();
					}
				};
			}
			
			namespace D3 = Dimension3;
		}
	}
}


#pragma region GreatVEngine2
#pragma endregion


#pragma region
#pragma endregion


