#ifdef PIPEDLL_EXPORTS
#define PIPEDLL_API __declspec(dllexport)
#else
#define PIPEDLL_API __declspec(dllimport)
#endif

#include <string>
#include <algorithm>

namespace PipeLine
{
	#define PIPE_NAME TEXT("\\\\.\\pipe\\Pipe")
	#define BUFFER_SIZE 1024

	class Message
	{
	private:
		char * buffer;
		int curr_length;

	public:
		PIPEDLL_API Message();
		PIPEDLL_API Message(char * msg, int length);
		PIPEDLL_API Message(const Message & other);
		PIPEDLL_API Message(Message && other);
		PIPEDLL_API ~Message();

		PIPEDLL_API Message & operator = (const Message & other);
		PIPEDLL_API Message & operator = (Message && other);

		PIPEDLL_API char * getBuffer() const;
	};
}