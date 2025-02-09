#include "mString.h"
#include "debug.h"
#include <iostream>
mString::mString(const char *str)
{
	if (str)
	{
		char c = NULL;
		for (size = 0; (c = str[size]) != NULL; size++)
			;
		ptr = std::make_unique<char[]>(size + 1);
		for (unsigned int i = 0; i <= size; i++)
			ptr[i] = str[i];
	}
}

mString::mString(const mString &other)
{
	if (other.ptr)
	{
		size = other.size;
		ptr = std::make_unique<char[]>(size + 1);
		for (unsigned int i = 0; i <= size; i++)
			ptr[i] = other.ptr[i];
	}
}

mString &mString::operator=(const mString &other)
{
	if (*this == other)
		return *this;
	size = other.size;
	if (other.ptr)
	{
		ptr = std::make_unique<char[]>(size + 1);
		for (unsigned int i = 0; i <= size; i++)
			ptr[i] = other.ptr[i];
	}
	return *this;
}

bool mString::operator==(const mString &other) const
{
	if (size != other.size)
		return false;
	if (!ptr)
		return true;
	for (unsigned int i = 0; i < size; i++)
		if (ptr[i] != other.ptr[i])
			return false;
	return true;
}

bool mString::operator<(const mString &other) const
{
	if (!ptr && !other.ptr)
		return false;
	if (!other.ptr)
		return false;
	if (!ptr)
		return true;

	unsigned int min_size = size < other.size ? size : other.size;
	for (unsigned int i = 0; i < min_size; i++)
	{
		if (ptr[i] > other.ptr[i])
			return false;
		else if (ptr[i] < other.ptr[i])
			return true;
	}
	return other.size > size;
}

bool mString::operator>(const mString &other) const
{
	if (!ptr && !other.ptr)
		return false;
	if (!other.ptr)
		return true;
	if (!ptr)
		return false;

	unsigned int min_size = size < other.size ? size : other.size;
	for (unsigned int i = 0; i < min_size; i++)
	{
		if (ptr[i] > other.ptr[i])
			return true;
		else if (ptr[i] < other.ptr[i])
			return false;
	}
	return other.size < size;
}

char &mString::operator[](unsigned int index)
{
	try
	{
		if (index >= size)
			throw "ERROR::MSTRING: index out of range in mString ";
	}
	catch (const char *e)
	{
		std::cerr << e << ptr.get() << std::endl;
		MDEBUG();
	}
	return ptr[index];
}

void mString::append(const char c)
{
	if (c != NULL)
	{
		unsigned int new_size = size + 1;
		std::unique_ptr<char[]> new_ptr = std::make_unique<char[]>(new_size + 1);
		for(unsigned int i = 0; i < size; i++)
			new_ptr[i] = ptr[i];
		new_ptr[new_size - 1] = c;
		new_ptr[new_size] = NULL;
		ptr = std::move(new_ptr);
		size = new_size;
	}
}

void mString::append(const mString &other)
{
	if (other.ptr)
	{
		unsigned int new_size = size + other.size;
		std::unique_ptr<char[]> new_ptr = std::make_unique<char[]>(new_size + 1);
		for (unsigned int i = 0; i < size; i++)
			new_ptr[i] = ptr[i];
		for (unsigned int i = 0; i < other.size; i++)
			new_ptr[size + i] = other.ptr[i];
		new_ptr[new_size] = NULL;
		ptr = std::move(new_ptr);
		size = new_size;
	}
}

const char *mString::getStr() const
{
	return static_cast<const char *>(ptr.get());
}