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

#include "Tests.h"

static byte document[16536];
typedef ::Dto::Dto DtoType;

/*TEST(Yaml, ParsesJsonEmptyObject)
{
	cstring yaml = "{}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.length(), 5);
	EXPECT_EQ(dto.entryCount(), 0);
}

TEST(Yaml, ParsesJsonTrue)
{
	cstring yaml = "{\"a\":true}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_TRUE(i.toBool());
}

TEST(Yaml, ParsesJsonFalse)
{
	cstring yaml = "{\"a\":false}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_FALSE(i.toBool());
}

TEST(Yaml, ParsesJsonIntegers)
{
	cstring yaml = "{\"a\":123}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_EQ(i.toInt32(), 123);
}

TEST(Yaml, ParsesJsonNegativeIntegers)
{
	cstring yaml = "{\"a\":-123}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_EQ(i.toInt32(), -123);
}

TEST(Yaml, ParsesJsonNegativeIntegersInsideArrays)
{
	cstring yaml = "{\"a\":[-123, -1, -2]}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
}

TEST(Yaml, ParsesJsonDecimals)
{
	cstring yaml = "{\"a\":12.23}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_EQ(i.toDouble(), 12.23);
}

TEST(Yaml, ParsesJsonNegativeDecimals)
{
	cstring yaml = "{\"a\":-12.23}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_EQ(i.toDouble(), -12.23);
}

TEST(Yaml, ParsesJsonNegativeDecimalsInsideArrays)
{
	cstring yaml = "{\"a\":[-12.23, -1.2]}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
}

TEST(Yaml, ParsesJsonStrings)
{
	cstring yaml = "{\"a\":\"hello world\"}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);

	EXPECT_TRUE(i.toString() == "hello world");
}

TEST(Yaml, ParsesJsonComplexObjects)
{
	cstring yaml = "{\"a\":12.23,\"b\":1,\"c\":true}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
}

TEST(Yaml, HandlesJsonWhitespaceChars)
{
	cstring yaml = "{\"a\" :   12.23,\"b\":1,\r\n\n\r\n\"c\": \ttrue}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
}

TEST(Yaml, ParsesJsonNestedEmptyObjects)
{
	cstring yaml = "{\"a\":{}}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
	EXPECT_EQ(i.type(), DtoKeyValue);
}

TEST(Yaml, ParsesJsonNestedEmptyArrays)
{
	cstring yaml = "{\"a\":[]}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
	EXPECT_EQ(i.type(), DtoSequence);
}

TEST(Yaml, ParsesJsonNestedObjects)
{
	cstring yaml = "{\"a\":{\"b\":0}}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
	EXPECT_EQ(i.type(), DtoKeyValue);
}

TEST(Yaml, ParsesJsonNestedComplexObjects)
{
	cstring yaml = "{\"a\":{\"b\":0,\"c\":1,\"d\":2}}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);
	EXPECT_EQ(dto.entryCount(), 1);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
	EXPECT_EQ(i.type(), DtoKeyValue);
}

TEST(Yaml, ParsesJsonNestedComplexArrays)
{
	cstring yaml = "{\"a\":[0,1,2,3]}";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_TRUE(dto);

	DtoIter i = dto.find("a");
	ASSERT_TRUE(i);
	EXPECT_EQ(i.type(), DtoSequence);
}

TEST(Yaml, WontParseJsonRootArray)
{
	cstring yaml = "[]";
	DtoType dto = dtoParse<YamlDtoReader>(yaml, document, sizeof(document));
	ASSERT_FALSE(dto);
}*/