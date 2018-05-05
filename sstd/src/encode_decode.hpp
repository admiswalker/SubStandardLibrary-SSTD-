#pragma once
#include <stdio.h>
#include <string.h>
#include <string> // std::string
#include "typeDef.h"


namespace sstd{
	std::string base64_encode(const uchar* str, size_t strLen);
	std::string base64_encode(const uchar* str);
	std::string base64_encode(const std::string& str);

	std::string base64_decode(const uchar* str, size_t strLen); // when it was error, return 0 size std::string.
	std::string base64_decode(const uchar* str);                      // when it was error, return 0 size std::string.
	std::string base64_decode(const std::string& str);                     // when it was error, return 0 size std::string.
	void print_base64_decode_table(); // for developers

	extern const char bin2str_table[256][3];
	std::string url_encode(const char* str, size_t strLen);
	std::string url_encode(const char* str);
	std::string url_encode(std::string& str);
	std::string url_encode_type2(const char* str, size_t strLen); // for developers
	void url_encode_compare_speed(); // for developers

	std::string url_decode(const char* str, size_t strLen); // when it was error, return 0 size std::string.
	std::string url_decode(const char* str);                      // when it was error, return 0 size std::string.
	std::string url_decode(std::string& str);                     // when it was error, return 0 size std::string.
	void print_url_decode_table(); // for developers

//	std::u16string utf8_to_utf16(const std::string& str);
//	std::string utf16_to_utf8(const std::u16string& str);
	// utf functions are not checked yet.
	std::u32string utf16_to_utf32(const std::u16string& str);
	std::u16string utf32_to_utf16(const std::u32string& str);
	std::   string utf32_to_utf8 (const std::u32string& str);
	std::u32string  utf8_to_utf32(const std::   string& str);
	std::u16string  utf8_to_utf16(const std::   string& str);
	std::   string utf16_to_utf8 (const std::u16string& str);

	extern const uchar str2bin_table[256];
	std::string    unicodeEscape_encode(const std::u16string& str);
	std::u16string unicodeEscape_decode(const char* str, size_t strLen);
	std::u16string unicodeEscape_decode(const char* str);
	std::u16string unicodeEscape_decode(const std::string& str);
	std::u16string unicodeEscape_decode_type2(const char* str, size_t strLen); // for developers
	void unicodeEscape_compare_speed(); // for developers
	void print_unicodeEscape_decode_table();
};
