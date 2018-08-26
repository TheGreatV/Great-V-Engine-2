#pragma region Include

#pragma once

#include "Header.hpp"
#include "Size.hpp"
#include "Memory.hpp"
#include "String.hpp"
#include "Mathematics.hpp"
#include "Collection.hpp"
#include "Reference.hpp"
#include "Exception.hpp"
#include "Subscription.hpp"

#include <fstream>

#include "Tau/Tau.hpp"

#pragma endregion


namespace GreatVEngine2
{
	class Geometry2
	{
	public:
		using EventDestruction = Subscription<void()>;
	public:
		class Component;
	public:
		class Vertices;
		class Indices;
	public:
		class Vertexed;
		class Indexed;
	public:
		inline static StrongPointer<Geometry2> Load(const String& filePath_);
	protected:
		mutable EventDestruction onDestruction;
	public:
		inline virtual ~Geometry2() = default;
	public:
		inline EventDestruction::Unsubscriber OnDestruction(const EventDestruction::Subscriber& subscriber_) const
		{
			return Move(onDestruction += subscriber_);
		}
	};
#pragma region Geometry2::Component
	class Geometry2::Component
	{
	public:
		class Regular;
	public:
		virtual ~Component() = default;
	public:
		virtual bool operator == (const StrongPointer<Component>& source_) const = 0;
	};
#pragma endregion
#pragma region Geometry2::Component::Regular
	class Geometry2::Component::Regular:
		public Component
	{
	public:
		enum class Sign
		{
			Signed,
			Unsigned,
		};
		enum class Normalization
		{
			Normalized,
			Unnormalized,
		};
		enum class Conversion
		{
			Integer,
			Floating,
		};
	protected:
		const Size size;
		const Sign sign;
		const Normalization normalization;
		const Conversion conversion;
	public:
		inline Regular(const Size& size_, const Sign& sign_, const Normalization& normalization_, const Conversion& conversion_);
		inline ~Regular() override = default;
	public:
		inline bool operator == (const StrongPointer<Component>& source_) const override;
	public:
		inline Size GetSize() const;
		inline Sign GetSign() const;
		inline Normalization GetNormalization() const;
		inline Conversion GetConversion() const;
	};
#pragma endregion
#pragma region Geometry2::Vertexed
	class Geometry2::Vertexed:
		public Geometry2
	{
	protected:
		const StrongPointer<Vertices> vertices;
	public:
		inline Vertexed(const StrongPointer<Vertices>& vertices_);
	public:
		inline StrongPointer<Vertices> GetVertices() const;
	};
#pragma endregion
#pragma region Geometry2::Vertices
	class Geometry2::Vertices
	{
	public:
		using Data = Vector<UInt8>;
	public:
		class Attribute;
		class Attributes;
	public:
		class Unformatted;
	public:
		virtual ~Vertices() = default;
	public:
		virtual StrongPointer<Attributes> GetAttributes() const = 0;
		virtual Size GetCount() const = 0;
		virtual Data GetData() const = 0;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attribute
	class Geometry2::Vertices::Attribute
	{
	public:
		using Name = String;
	public:
		class Type;
	public:
		class Regular;
	public:
		virtual ~Attribute() = default;
	public:
		virtual bool operator == (const StrongPointer<Attribute>& source_) const = 0;
	public:
		virtual Name GetName() const = 0;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attributes
	class Geometry2::Vertices::Attributes
	{
	public:
		class Listed;
	public:
		virtual ~Attributes() = default;
	public:
		virtual bool operator == (const StrongPointer<Attributes>& source_) const = 0;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attributes::Listed
	class Geometry2::Vertices::Attributes::Listed:
		public Attributes
	{
	public:
		using Values = Vector<StrongPointer<Attribute>>;
	protected:
		const Values values;
	public:
		inline Listed(const Values& values_);
	public:
		inline bool operator == (const StrongPointer<Attributes>& source_) const override;
	public:
		inline StrongPointer<Attribute> operator [] (const Attribute::Name& name_) const;
	public:
		inline bool IsHas(const Attribute::Name& name_) const;
		inline Size GetCount() const;
		inline Values GetValues() const;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Type
	class Geometry2::Vertices::Attribute::Type
	{
	public:
		class Vector;
		class Matrix;
	public:
		virtual ~Type() = default;
	public:
		virtual bool operator == (const StrongPointer<Type>& source_) const = 0;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Type::Vector
	class Geometry2::Vertices::Attribute::Type::Vector:
		public Type
	{
	protected:
		const StrongPointer<Vertexed::Component> component;
		const Size componentsCount;
	public:
		inline Vector(const StrongPointer<Component>& component_, const Size& componentsCount_);
		inline ~Vector() override = default;
	public:
		inline bool operator == (const StrongPointer<Type>& source_) const override;
	public:
		inline StrongPointer<Component> GetComponent() const;
		inline Size GetComponentsCount() const;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Type::Matrix
	class Geometry2::Vertices::Attribute::Type::Matrix:
		public Type
	{
	public:
		enum class Order
		{
			RowMajor,
			ColumnMajor,
		};
	protected:
		const StrongPointer<Vertexed::Component> component;
		const Size rowsCount;
		const Size columnsCount;
		const Order order;
	public:
		inline Matrix(const StrongPointer<Component>& component_, const Size& rowsCount_, const Size& columnsCount_, const Order& order_);
		inline ~Matrix() override = default;
	public:
		inline bool operator == (const StrongPointer<Type>& source_) const override;
	public:
		inline StrongPointer<Component> GetComponent() const;
		inline Size GetRowsCount() const;
		inline Size GetColumnsCount() const;
		inline Order GetOrder() const;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Regular
	class Geometry2::Vertices::Attribute::Regular:
		public Attribute
	{
	public:
		using Offset = UInt8;
		using Stride = UInt8;
	protected:
		const Name name;
		const Offset offset;
		const Stride stride;
		const StrongPointer<Type> type;
	public:
		inline Regular(const Name& name_, const Offset& offset_, const Stride& stride_, const StrongPointer<Type>& type_);
		inline ~Regular() override = default;
	public:
		inline bool operator == (const StrongPointer<Attribute>& source_) const override;
	public:
		inline Name GetName() const override;
	public:
		inline Offset GetOffset() const;
		inline Offset GetStride() const;
		inline StrongPointer<Type> GetType() const;
	};
#pragma endregion
#pragma region Geometry2::Vertices::Unformatted
	class Geometry2::Vertices::Unformatted:
		public Vertices
	{
	protected:
		const StrongPointer<Attributes> attributes;
		const Size count;
		const Data data;
	public:
		inline Unformatted(const StrongPointer<Attributes>& attributes_, const Size& count_, const Data& data_);
		inline ~Unformatted() override = default;
	public:
		inline StrongPointer<Attributes> GetAttributes() const override;
		inline Size GetCount() const override;
		inline Data GetData() const override;
	};
#pragma endregion
#pragma region Geometry2::Indices
	class Geometry2::Indices
	{
	public:
		using Data = Vector<UInt8>;
	public:
		class Attributes;
	public:
		class Unformatted;
	public:
		virtual ~Indices() = default;
	public:
		virtual StrongPointer<Attributes> GetAttributes() const = 0;
		virtual Size GetCount() const = 0;
		virtual Data GetData() const = 0;
	};
#pragma endregion
#pragma region Geometry2::Indices::Attributes
	class Geometry2::Indices::Attributes
	{
	protected:
		const StrongPointer<Component> component;
	public:
		inline Attributes(const StrongPointer<Component>& component_);
	public:
		inline bool operator == (const StrongPointer<Attributes>& source_) const;
	public:
		inline StrongPointer<Component> GetComponent() const;
	};
#pragma endregion
#pragma region Geometry2::Indices::Unformatted
	class Geometry2::Indices::Unformatted:
		public Indices
	{
	protected:
		const StrongPointer<Attributes> attributes;
		const Size count;
		const Data data;
	public:
		inline Unformatted(const StrongPointer<Attributes>& attributes_, const Size& count_, const Data& data_);
		inline ~Unformatted() override = default;
	public:
		inline StrongPointer<Attributes> GetAttributes() const override;
		inline Size GetCount() const override;
		inline Data GetData() const override;
	};
#pragma endregion
#pragma region Geometry2::Indexed
	class Geometry2::Indexed:
		public Geometry2::Vertexed
	{
	protected:
		const StrongPointer<Indices> indices;
	public:
		inline Indexed(const StrongPointer<Vertices>& vertices_, const StrongPointer<Indices>& indices_);
	public:
		inline StrongPointer<Indices> GetIndices() const;
	};
#pragma endregion


#pragma region Geometry2
	StrongPointer<Geometry2> Geometry2::Load(const String& filePath_)
	{
		std::ifstream file(filePath_);

		const auto input = String(std::istreambuf_iterator<String::value_type>(file), std::istreambuf_iterator<String::value_type>());
		const auto parser = Tau::Parser();
		const auto root = parser.Parse(input);

		const auto verticesModel			= root["Vertices"];
		const auto verticesAttributesModel	= verticesModel["Attributes"];
		const auto indicesModel				= root["Indices"];

		// using
		using Component = Geometry2::Component::Regular;
		using Attribute = Geometry2::Vertexed::Vertices::Attribute;

		const auto sfloat32						= MakeStrong<Component>(32, Component::Sign::Signed, Component::Normalization::Unnormalized, Component::Conversion::Floating);
		const auto uint32						= MakeStrong<Component>(32, Component::Sign::Unsigned, Component::Normalization::Unnormalized, Component::Conversion::Integer);
		const auto vec3Attribute				= MakeStrong<Attribute::Type::Vector>(sfloat32, 3);

		// attributes
		auto verticesAttributesValues			= Geometry2::Vertices::Attributes::Listed::Values();

		const auto verticesAttributesModelKeys = verticesAttributesModel.Keys();

		for (int i = 0; i < static_cast<int>(verticesAttributesModelKeys.Length()); ++i)
		{
			const auto key		= verticesAttributesModelKeys[i];

			if (key.Is<Tau::String>())
			{
				const auto attributeName	= static_cast<String>(key);
				const auto attributeModel	= verticesAttributesModel[key];

				const auto attributeClass	= static_cast<String>(attributeModel["Class"]);
				
				if (attributeClass == "Regular Attribute")
				{
					const auto offsetModel			= static_cast<int>(attributeModel["Offset"]);
					const auto strideModel			= static_cast<int>(attributeModel["Stride"]);
					
					const auto attributeType		= attributeModel["Type"];
					const auto attributeTypeClass	= static_cast<String>(attributeType["Class"]);

					if (attributeTypeClass == "Vector Attribute Type")
					{
						const auto componentsCount	= static_cast<int>(attributeType["Size"]);
						const auto componentModel	= static_cast<String>(attributeType["Component"]);

						if (componentModel == "Signed 32-bit Float")
						{
							const auto attribute = MakeStrong<Attribute::Regular>(attributeName, offsetModel, strideModel, MakeStrong<Attribute::Type::Vector>(sfloat32, componentsCount));

							verticesAttributesValues.push_back(attribute);
						}
					}
					else if (attributeTypeClass == "Matrix Attribute Type")
					{
						const auto rowsCount		= static_cast<int>(attributeType["Rows"]);
						const auto columnsCount		= static_cast<int>(attributeType["Columns"]);
						const auto orderModel		= static_cast<String>(attributeType["Order"]);
						const auto order			=
							orderModel == "Row-major" ? Attribute::Type::Matrix::Order::RowMajor:
							orderModel == "Column-major" ? Attribute::Type::Matrix::Order::ColumnMajor:
							throw Exception();
						const auto componentModel	= static_cast<String>(attributeType["Component"]);

						if (componentModel == "Signed 32-bit Float")
						{
							const auto attribute = MakeStrong<Attribute::Regular>(attributeName, offsetModel, strideModel, MakeStrong<Attribute::Type::Matrix>(sfloat32, rowsCount, columnsCount, order));

							verticesAttributesValues.push_back(attribute);
						}
					}
				}
			}
		}

		const auto verticesAttributes	= MakeStrong<Geometry2::Vertices::Attributes::Listed>(verticesAttributesValues);

		// vertices
		const auto verticesCount		= static_cast<int>(verticesModel["Count"]);
		const auto verticesData			= verticesModel["Data"].Data();

		const auto vertices				= MakeStrong<Geometry2::Vertices::Unformatted>(verticesAttributes, verticesCount, verticesData);

		// indices
		const auto indicesType			= static_cast<String>(indicesModel["Type"]);
		const auto indicesCount			= static_cast<int>(indicesModel["Count"]);
		const auto indicesData			= indicesModel["Data"].Data();

		auto indicesAttributes			= MakeStrong<Geometry2::Indices::Attributes>(
			indicesType == "Unsigned 32-bit Integer" ? uint32 :
			throw Exception()
		);

		const auto indices				= MakeStrong<Geometry2::Indices::Unformatted>(indicesAttributes, indicesCount, indicesData);

		// geometry
		const auto geometry				= MakeStrong<Geometry2::Indexed>(vertices, indices);

		return geometry;
	}
#pragma endregion
#pragma region Geometry2::Component::Regular
	Geometry2::Component::Regular::Regular(const Size& size_, const Sign& sign_, const Normalization& normalization_, const Conversion& conversion_):
		size(size_),
		sign(sign_),
		normalization(normalization_),
		conversion(conversion_)
	{
	}

	bool Geometry2::Component::Regular::operator == (const StrongPointer<Component>& source_) const
	{
		if (const auto source = DynamicCast<Regular>(source_))
		{
			if (source->GetSize() != GetSize())
			{
				return false;
			}
			if (source->GetSign() != GetSign())
			{
				return false;
			}
			if (source->GetNormalization() != GetNormalization())
			{
				return false;
			}
			if (source->GetConversion() != GetConversion())
			{
				return false;
			}

			return true;
		}

		return false;
	}
	
	Size Geometry2::Component::Regular::GetSize() const
	{
		return size;
	}
	Geometry2::Component::Regular::Sign Geometry2::Component::Regular::GetSign() const
	{
		return sign;
	}
	Geometry2::Component::Regular::Normalization Geometry2::Component::Regular::GetNormalization() const
	{
		return normalization;
	}
	Geometry2::Component::Regular::Conversion Geometry2::Component::Regular::GetConversion() const
	{
		return conversion;
	}
#pragma endregion
#pragma region Geometry2::Vertexed
	Geometry2::Vertexed::Vertexed(const StrongPointer<Vertices>& vertices_):
		vertices(vertices_)
	{
	}
	
	StrongPointer<Geometry2::Vertexed::Vertices> Geometry2::Vertexed::GetVertices() const
	{
		return vertices;
	}
#pragma endregion
#pragma region Geometry2::Vertices::Attributes::Listed
	Geometry2::Vertices::Attributes::Listed::Listed(const Values& values_):
		values(values_)
	{
	}
	
	bool Geometry2::Vertices::Attributes::Listed::operator == (const StrongPointer<Attributes>& source_) const
	{
		if (const auto source = DynamicCast<Listed>(source_))
		{
			if (source->GetCount() != GetCount())
			{
				return false;
			}

			for (Size i = 0; i < values.size(); ++i)
			{
				const auto &attribute		= values[i];
				const auto attributeName	= attribute->GetName();

				if (source->IsHas(attributeName) == false)
				{
					return false;
				}

				const auto &sourceAttribute	= source->operator[](attributeName);

				if (attribute->operator==(sourceAttribute) == false)
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	StrongPointer<Geometry2::Vertices::Attribute> Geometry2::Vertices::Attributes::Listed::operator [] (const Geometry2::Vertices::Attribute::Name& name_) const
	{
		for (const auto &attribute : values)
		{
			if (attribute->GetName() == name_)
			{
				return attribute;
			}
		}

		throw Exception();
	}

	bool Geometry2::Vertices::Attributes::Listed::IsHas(const Geometry2::Vertices::Attribute::Name& name_) const
	{
		for (const auto &attribute : values)
		{
			if (attribute->GetName() == name_)
			{
				return true;
			}
		}

		return false;
	}
	Size Geometry2::Vertices::Attributes::Listed::GetCount() const
	{
		return values.size();
	}
	Geometry2::Vertices::Attributes::Listed::Values Geometry2::Vertices::Attributes::Listed::GetValues() const
	{
		return values;
	}
#pragma endregion
#pragma region Geometry2::Vertices::Unformatted
	Geometry2::Vertices::Unformatted::Unformatted(const StrongPointer<Attributes>& attributes_, const Size& count_, const Data& data_):
		attributes(attributes_),
		count(count_),
		data(data_)
	{
	}

	StrongPointer<Geometry2::Vertices::Unformatted::Attributes> Geometry2::Vertices::Unformatted::GetAttributes() const
	{
		return attributes;
	}
	Size Geometry2::Vertices::Unformatted::GetCount() const
	{
		return count;
	}
	Geometry2::Vertices::Unformatted::Data Geometry2::Vertices::Unformatted::GetData() const
	{
		return data;
	}
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Type::Vector
	Geometry2::Vertices::Attribute::Type::Vector::Vector(const StrongPointer<Component>& component_, const Size& componentsCount_):
		component(component_),
		componentsCount(componentsCount_)
	{
	}
	
	bool Geometry2::Vertices::Attribute::Type::Vector::operator == (const StrongPointer<Type>& source_) const
	{
		if (const auto source = DynamicCast<Vector>(source_))
		{
			if (source->GetComponentsCount() != GetComponentsCount())
			{
				return false;
			}
			if (source->component->operator==(component) == false)
			{
				return false;
			}

			return true;
		}

		return false;
	}

	StrongPointer<Geometry2::Component> Geometry2::Vertices::Attribute::Type::Vector::GetComponent() const
	{
		return component;
	}
	Size Geometry2::Vertices::Attribute::Type::Vector::GetComponentsCount() const
	{
		return componentsCount;
	}
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Type::Matrix
	Geometry2::Vertices::Attribute::Type::Matrix::Matrix(const StrongPointer<Component>& component_, const Size& rowsCount_, const Size& columnsCount_, const Order& order_):
		component(component_),
		rowsCount(rowsCount_),
		columnsCount(columnsCount_),
		order(order_)
	{
	}
	
	bool Geometry2::Vertices::Attribute::Type::Matrix::operator == (const StrongPointer<Type>& source_) const
	{
		if (const auto source = DynamicCast<Matrix>(source_))
		{
			if (source->GetRowsCount() != GetRowsCount())
			{
				return false;
			}
			if (source->GetColumnsCount() != GetColumnsCount())
			{
				return false;
			}
			if (source->GetOrder() != GetOrder())
			{
				return false;
			}
			if (source->component->operator==(component) == false)
			{
				return false;
			}

			return true;
		}

		return false;
	}

	StrongPointer<Geometry2::Component> Geometry2::Vertices::Attribute::Type::Matrix::GetComponent() const
	{
		return component;
	}
	Size Geometry2::Vertices::Attribute::Type::Matrix::GetRowsCount() const
	{
		return rowsCount;
	}
	Size Geometry2::Vertices::Attribute::Type::Matrix::GetColumnsCount() const
	{
		return columnsCount;
	}
	Geometry2::Vertices::Attribute::Type::Matrix::Order Geometry2::Vertices::Attribute::Type::Matrix::GetOrder() const
	{
		return order;
	}
#pragma endregion
#pragma region Geometry2::Indexed
	Geometry2::Indexed::Indexed(const StrongPointer<Vertices>& vertices_, const StrongPointer<Indices>& indices_):
		Vertexed(vertices_),
		indices(indices_)
	{
	}
	
	StrongPointer<Geometry2::Indexed::Indices> Geometry2::Indexed::GetIndices() const
	{
		return indices;
	}
#pragma endregion
#pragma region Geometry2::Vertices::Attribute::Regular
	Geometry2::Vertices::Attribute::Regular::Regular(const Name& name_, const Offset& offset_, const Stride& stride_, const StrongPointer<Type>& type_):
		name(name_),
		offset(offset_),
		stride(stride_),
		type(type_)
	{
	}
	
	bool Geometry2::Vertices::Attribute::Regular::operator == (const StrongPointer<Attribute>& source_) const
	{
		if (const auto source = DynamicCast<Regular>(source_))
		{
			if (source->GetName() != GetName())
			{
				return false;
			}
			if (source->GetOffset() != GetOffset())
			{
				return false;
			}
			if (source->GetStride() != GetStride())
			{
				return false;
			}
			if (type->operator==(source->type) == false)
			{
				return false;
			}
		}

		return false;
	}

	Geometry2::Vertices::Attribute::Name Geometry2::Vertices::Attribute::Regular::GetName() const
	{
		return name;
	}
	Geometry2::Vertices::Attribute::Regular::Offset Geometry2::Vertices::Attribute::Regular::GetOffset() const
	{
		return offset;
	}
	Geometry2::Vertices::Attribute::Regular::Offset Geometry2::Vertices::Attribute::Regular::GetStride() const
	{
		return stride;
	}
	StrongPointer<Geometry2::Vertices::Attribute::Type> Geometry2::Vertices::Attribute::Regular::GetType() const
	{
		return type;
	}
#pragma endregion
#pragma region Geometry2::Indices::Unformatted
	Geometry2::Indices::Unformatted::Unformatted(const StrongPointer<Attributes>& attributes_, const Size& count_, const Data& data_):
		attributes(attributes_),
		count(count_),
		data(data_)
	{
	}
	
	StrongPointer<Geometry2::Indices::Attributes> Geometry2::Indices::Unformatted::GetAttributes() const
	{
		return attributes;
	}
	Size Geometry2::Indices::Unformatted::GetCount() const
	{
		return count;
	}
	Geometry2::Indices::Unformatted::Data Geometry2::Indices::Unformatted::GetData() const
	{
		return data;
	}
#pragma endregion
#pragma region Geometry2::Indices::Attributes
	Geometry2::Indices::Attributes::Attributes(const StrongPointer<Component>& component_):
		component(component_)
	{
	}
	
	bool Geometry2::Indices::Attributes::operator == (const StrongPointer<Attributes>& source_) const
	{
		if (source_->component->operator==(component) == false)
		{
			return false;
		}

		return false;
	}

	StrongPointer<Geometry2::Component> Geometry2::Indices::Attributes::GetComponent() const
	{
		return component;
	}
#pragma endregion
}


#pragma region GreatVEngine2
#pragma endregion


#pragma region
#pragma endregion


