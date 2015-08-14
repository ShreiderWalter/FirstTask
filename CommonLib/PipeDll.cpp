#include "stdafx.h"
#include "PipeDll.h"

namespace PipeLine
{
	Message::Message() : buffer(nullptr), curr_length(BUFFER_SIZE)
	{
		buffer = new char[curr_length];
	}

	Message::Message(char * msg, int length) : buffer(nullptr), curr_length(length)
	{
		buffer = new char[length];
		std::memcpy(buffer, msg, curr_length);
	}

	Message::Message(const Message & other) : buffer(nullptr), curr_length(other.curr_length)
	{
		buffer = new char[curr_length];
		std::memcpy(buffer, other.buffer, other.curr_length);
	}

	Message::Message(Message && other) : buffer(nullptr), curr_length(other.curr_length)
	{
		std::swap(buffer, other.buffer);
	}

	Message::~Message()
	{
		delete buffer;
		buffer = nullptr;
	}

	Message & Message::operator=(const Message & other)
	{
		if(this != &other)
		{
			std::memcpy(buffer, other.buffer, other.curr_length);
		}
		return *this;
	}

	Message & Message::operator=(Message && other)
	{
		std::swap(buffer, other.buffer);
		return *this;
	}

	char * Message::getBuffer() const
	{
		return buffer;
	}

}