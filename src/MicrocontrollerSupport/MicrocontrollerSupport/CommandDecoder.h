#pragma once
#include "Util.h"
#include "Timer.h"
#include "CommandConversions.h"
#include "Command.h"
#include "ElasticBuffer.h"

// Decodes commands from stream of characters sent to the microcontroller. Buffers incoming characters
// to prevent data loss from signal delays.
class CommandDecoder {
public:
	CommandDecoder();
	~CommandDecoder();

	const void addChar(const char nextChar);
	const void addChars(const char* nextChars, const int length);
	const bool hasNext() const;
	const Command* next();
	const void clear();
private:
	CommandConversions* conversions;		// Conversions between character stream and command type enum value
	Buffer<Command>* commandBuffer;			// Buffer for output parsed commands
	Buffer<char>* charBuffer;				// Buffer for input characters
	bool encounteredStart;					// Helpful indicator for determining whether or not to parse the characters into a command

	const int copyCharBuffer(char*& result, const int length) const;
	const char* dumpCharBuffer() const;
};