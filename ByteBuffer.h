/**************************************************************************

The MIT License (MIT)

Copyright (c) 2017 Dmitry Sovetov

https://github.com/dmsovetov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

**************************************************************************/

#ifndef __Dto_ByteBuffer_H__
#define __Dto_ByteBuffer_H__

DTO_BEGIN

	//! This class implements an output stream in which the data is written into a byte array.
	class DtoByteArrayOutput
	{
	public:

		//! A proxy type used by writer to specify the following byte buffer size.
		struct size
		{
								size(int32 value) : value(value) {}
			int32				value;	//!< A total number of bytes to be written by a following call.
		};

								//! Constructs DtoByteArrayOutput instance.
								DtoByteArrayOutput(byte* output, int32 capacity);

								//! Constructs DtoByteArrayOutput instance as a nested inside a parent buffer.
								DtoByteArrayOutput(DtoByteArrayOutput& parent);

		//! Writes a 1-byte long boolean value to an output stream.
		DtoByteArrayOutput&		operator << (bool value);

		//! Writes a DTO value type as 1-byte long signed integer to an output stream.
		DtoByteArrayOutput&		operator << (DtoValueType value);
		
		//! Writes a 1-byte long signed integer value to an output stream.
		DtoByteArrayOutput&		operator << (byte value);

		//! Writes a 4-byte long signed integer value to an output stream.
		DtoByteArrayOutput&		operator << (int32 value);

		//! Writes a 8-byte long signed integer value to an output stream.
		DtoByteArrayOutput&		operator << (int64 value);

		//! Writes a 8-byte long unsigned integer value to an output stream.
		DtoByteArrayOutput&		operator << (uint64 value);

		//! Writes a 8-byte long decimal floating point value to an output stream.
		DtoByteArrayOutput&		operator << (double value);

		//! Writes a C-string to an output stream (includes a zero terminator).
		DtoByteArrayOutput&		operator << (cstring value);

		//! Writes a string view to an output stream (includes a zero terminator).
		DtoByteArrayOutput&		operator << (const DtoStringView& value);

		//! Sets a source byte buffer size that if followed after this call.
		DtoByteArrayOutput&		operator << (const size& size);

		//! Writes a byte buffer to an output stream (expects a previous call to operator << (const Size&)).
		DtoByteArrayOutput&		operator << (const byte* bytes);

		//! Returns a buffer pointer.
		const byte*				buffer() const;
		byte*					buffer();

		//! Returns a writable pointer.
		const byte*				ptr() const;
		byte*					ptr();

		//! Returns a total number of bytes written to an output stream.
		int32					length() const;

		//! Returns an output byte buffer capacity.
		int32					capacity() const;

		//! Returns a total number of bytes available for writing.
		int32					available() const;

	protected:

		//! Returns a writable pointer and advances a write head position by a specified number of bytes.
		byte*					advance(int32 count);

	protected:

		byte*					m_output;	//!< A pointer to the beginning of an output stream.
		byte*					m_ptr;		//!< A writable output stream position.
		int32					m_capacity;	//!< A maximum number of bytes that can be written to this byte array.
		size					m_size;		//!< A total number of bytes to be written by a next call of operator << (const byte*).
	};

	//! This class implements an output stream in which the data is written into a byte array, but is formated as UTF-8 text.
	class DtoTextOutput : public DtoByteArrayOutput
	{
	public:

		//! A special marker type to control an output.
		enum marker
		{
			  quotedString	//!< Indicates that a next string value should be quoted.
			, zero			//!< Writes a zero terminator to an output string.
		};

								//! Constructs DtoTextOutput instance.
								DtoTextOutput(byte* output, int32 capacity);

		//! Formats a boolean value as text and writes it to an output stream.
		DtoTextOutput&			operator << (bool value);

		//! Formats a 1-byte long signed integer value as text and writes it to an output stream.
		DtoTextOutput&			operator << (byte value);

		//! Formats a 4-byte long signed integer value as text and writes it to an output stream.
		DtoTextOutput&			operator << (int32 value);

		//! Formats a 8-byte long signed integer value as text and writes it to an output stream.
		DtoTextOutput&			operator << (int64 value);

		//! Formats a 8-byte long unsigned integer value as text and writes it to an output stream.
		DtoTextOutput&			operator << (uint64 value);

		//! Formats a 8-byte long decimal floating point value as text and writes it to an output stream.
		DtoTextOutput&			operator << (double value);

		//! Copies a C-string to an output stream (WITHOUT a zero terminator).
		DtoTextOutput&			operator << (cstring value);

		//! Copies a string view to an output stream (WITHOUT a zero terminator).
		DtoTextOutput&			operator << (const DtoStringView& value);

		//! Formats an outputs a DTO value to a text stream.
		DtoTextOutput&			operator << (const DtoValue& value);

		//! Controls an output formatting.
		DtoTextOutput&			operator << (marker value);

		//! Rewinds a write pointer back by a specified number of bytes.
		void					rewind(int32 count);

		//! Returns an output buffer as a C string.
		cstring					text() const;

	private:

		bool					m_isQuotedString;	//!< True if a next string value should be surrounded by quote symbols.
	};

	//! This class implements an input stream that contains bytes that may be read from the it.
	class DtoByteBufferInput
	{
	public:

		//! A proxy type to skip a specified amount of bytes.
		struct skip
		{
								skip(int32 value) : value(value) {}
			int32				value;	//!< A total number of bytes to skip from an input stream.
		};

								//! Constructs DtoByteBufferInput instance.
								DtoByteBufferInput(const byte* input, int32 capacity);

		//! Reads a 1-byte long boolean value from an input stream.
		DtoByteBufferInput&		operator >> (bool& value);

		//! Reads a DTO value type as 1-byte long signed integer from an input stream.
		DtoByteBufferInput&		operator >> (DtoValueType& value);

		//! Reads a 1-byte long signed integer value from an input stream.
		DtoByteBufferInput&		operator >> (byte& value);

		//! Reads a 4-byte long signed integer value from an input stream.
		DtoByteBufferInput&		operator >> (int32& value);

		//! Reads a 8-byte long signed integer value from an input stream.
		DtoByteBufferInput&		operator >> (int64& value);

		//! Reads a 8-byte long unsigned integer value from an input stream.
		DtoByteBufferInput&		operator >> (uint64& value);

		//! Reads a 8-byte long decimal floating point value to an output stream.
		DtoByteBufferInput&		operator >> (double& value);

		//! Reads a C-string from an input stream (includes a zero terminator).
		DtoByteBufferInput&		operator >> (cstring& value);

		//! Reads a C-string from an input stream to a string view and calculates it's length.
		DtoByteBufferInput&		operator >> (DtoStringView& value);

		//! Saves a current read pointer.
		DtoByteBufferInput&		operator >> (const byte*& value);

		//! Skips a specified number of bytes.
		DtoByteBufferInput&		operator >> (const skip& count);

		//! Returns an input byte buffer capacity.
		int32					capacity() const;

		//! Returns a total number of bytes available for reading.
		int32					available() const;

		//! Returns a total number of bytes consumed by a reader.
		int32					consumed() const;

		//! Returns a readable pointer and advances a read head position by a specified number of bytes.
		const byte*				advance(int32 count);

		//! Returns current read pointer.
		const byte*				ptr() const;

		//! Sets a current read pointer.
		void					setPtr(const byte* value);

	protected:

		const byte*				m_input;	//!< A pointer to the beginning of an input stream.
		const byte*				m_ptr;		//!< A readable input stream position.
		int32					m_capacity;	//!< A maximum number of bytes that can be read from this byte array.
	};

	/*!
	 This class implements an input stream in which the data is treated as a sequence of tokens.
	 */
	class DtoTokenInput : private DtoByteBufferInput
	{
	public:

		//! A maximum length of an error message.
		enum { MaxMessageLength = 60 };

		//! Enumeration of all available tokens.
		enum TokenType
		{
			  Nonterminal			//!< This special token type indicates that an unknown symbol encountered.
			, End					//!< A zero terminator reached.
			, NewLine				//!< A new line token is one of '\n' or '\r\n' symbols.
			, Space					//!< An empty space character.
			, Tab					//!< A single '\t' symbol.
			, Identifier			//!< An identifier is a sequence of symbols surrounded by spaces, tabs or new lines.
			, DoubleQuotedString	//!< A string token that starts with '"' symbol and ends with '"' symbol.
			, SingleQuotedString	//!< A string token that starts with '\'' symbole and ends with '\'' symbol.
			, Number				//!< A number token.
			, True					//!< The 'true' keyword.
			, False					//!< The 'false' keyword.
			, Colon					//!< A colon symbol ':'
			, Minus					//!< A minus symbol '-'
			, BraceOpen				//!< An opening brace symbol '{'
			, BraceClose			//!< A closing brace symbol '}'
			, BracketOpen			//!< An opening bracket symbol '['
			, BracketClose			//!< A closing bracket symbol ']'
			, Comma					//!< A comma symbol ','
			, TotalTokens			//!< A total number of tokens.
		};

		//! Token names.
		static cstring s_tokens[TotalTokens];

		//! A token data that is returned by text input.
		struct Token
		{
			DtoStringView		text;	//!< A token text.
			TokenType			type;	//!< A token type.
			int32				line;	//!< A line number this token occured.
			int32				column;	//!< A column number of a first character of this token.

			//! Returns true if this token is of specified type.
			bool				operator == (TokenType type) const;
		};

								//! Constructs a DtoTokenInput class.
								DtoTokenInput(const byte* input, int32 capacity);

								//! Constructs a DtoTokenInput class from a C string.
								DtoTokenInput(cstring input);

		//! Reads a next token from an input stream.
		const Token&			next();

		//! Reads a next non whitespace token from an input stream.
		const Token&			nextNonSpace();

		//! Returns a total numner of consumed bytes.
		int32					consumed() const;

		//! Returns current token.
		const Token&			currentToken() const;

		//! Consumes a number value from an input stream.
		DtoValue				consumeNumber(int sign = 1, bool nextNonSpace = false);

		//! Consumes a boolean value from an input stream.
		DtoValue				consumeBoolean(bool nextNonSpace = false);

		//! Consumes a string value from an input stream.
		DtoValue				consumeString(bool nextNonSpace = false);

		//! Expects that a current token matches the specified one and if so, reads the next one.
		bool					expect(TokenType type, bool nextNonSpace = false);

		//! Checks the type of a current token and if it matches the specified one consumes it and returns true.
		bool					consume(TokenType type, bool nextNonSpace = false);

		//! Checks the type of a current token and if it matches the specified one returns true.
		bool					check(TokenType type);

		//! Emits an unexpected token error.
		void					emitUnexpectedToken() const;

	private:

		//! Reads a token from an input stream and returns it's type.
		TokenType				readToken();

		//! Consumes a number token from an input stream.
		TokenType				readNumber();

		//! Consumes a string token.
		TokenType				readString(char quote, TokenType type);

		//! Returns a current symbol.
		char					currentSymbol() const;

		//! Returns a next symbol in stream.
		char					nextSymbol() const;

		//! Returns a symbol that is located at specified offset.
		char					lookAhead(int32 offset) const;

		//! Returns true if a specified sequence of symbols can be consumed and if so consumes it.
		bool					read(cstring symbols);

		//! A shortcut to consume symbol an return a token type.
		TokenType				readAs(TokenType type, int32 count = 1);

	private:

		int32					m_line;		//!< A current line number.
		int32					m_column;	//!< A current column number.
		Token					m_token;	//!< A current token.
		Token					m_prev;		//!< A previous token (used by error message formatter).
	};

DTO_END

#endif	/*	#ifndef __Dto_ByteBuffer_H__	*/