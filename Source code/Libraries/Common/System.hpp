#pragma region Include

#pragma once

#include "Header.hpp"
#include "Size.hpp"
#include "String.hpp"
#include "Mathematics.hpp"
#include "Collection.hpp"
#include "Reference.hpp"
#include "Exception.hpp"

#include <fstream>

#pragma endregion


#pragma region Macros
#pragma endregion


namespace GreatVEngine2
{
	class DataReader
	{
	public:
		virtual ~DataReader() = default;
	public:
		virtual UInt8 ReadUInt8() = 0;
		virtual UInt32 ReadUInt32() = 0;
		virtual Vector<UInt8> ReadUInt8Array(const Size& count_) = 0;
		virtual String ReadString(const Size& count_) = 0;
	};

	class File:
		public DataReader
	{
	public:
		using Name = WideString;
	protected:
		const Name name;
		Memory<FILE> file;
	public:
		inline File(const Name& name_):
			name(name_)
		{
			if (_wfopen_s(&file, name.c_str(), L"rb") != 0)
			{
				throw Exception();
			}
		}
		inline virtual ~File() override
		{
			if (fclose(file) != 0)
			{
				throw Exception();
			}
		}
	public:
		inline virtual UInt8 ReadUInt8() override
		{
			UInt8 data;

			if (fread_s(&data, sizeof(UInt8), sizeof(UInt8), 1, file) != 1)
			{
				throw Exception();
			}

			return data;
		}
		inline virtual UInt32 ReadUInt32() override
		{
			UInt32 data;

			if (fread_s(&data, sizeof(UInt32), sizeof(UInt32), 1, file) != 1)
			{
				throw Exception();
			}

			return data;
		}
		inline virtual Vector<UInt8> ReadUInt8Array(const Size& count_) override
		{
			Vector<UInt8> data(count_);

			if (fread_s(data.data(), sizeof(UInt8)* data.size(), sizeof(UInt8), data.size(), file) != data.size())
			{
				throw Exception();
			}

			return data;
		}
		inline virtual String ReadString(const Size& count_) override
		{
			auto data = ReadUInt8Array(count_);

			String result;

			result.resize(count_);

			for (auto &i : Range(count_))
			{
				result[i] = data[i];
			}

			return result;
		}
	};
}


#pragma region GreatVEngine2
#pragma endregion


#pragma region
#pragma endregion


