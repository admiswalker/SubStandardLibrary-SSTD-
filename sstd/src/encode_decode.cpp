#include "encode_decode.hpp"

#define MeasureTime
#include "measureTime.hpp"

#include <iostream>
#include <string>
#include <codecvt>
#include <cassert>
#include <locale>


std::string sstd::base64_encode(const char* str, const size_t strLen){

	uint retLen = sizeof(char)*(((strLen)*4+2)/3); // '=' のパディングを含めないサイズを，切り上げとなるように「+2」してから計算．(整数形は必ず切り捨てとなるため，「分母 - 1」を分子に足すと，切り上げとなる．)

	uint retLen_mod4 = retLen % 4;
	uint retLen_div4 = retLen - retLen_mod4; // same as 'retLen / 4'

	uint retLen_total;	// '=' のパディングを含めたサイズ
	if(retLen_mod4!=0){ retLen_total = retLen_div4 + 4;	// バッファが4の倍数になるように調整
	}       else      { retLen_total = retLen; }

	std::string ret(retLen_total, 0);	// 終端文字分は，std::string 側で確保される

	// 4 の倍数分を計算する．
	uint p=0, q=0;
	for(; p<retLen_div4; q+=3){
		ret[p++] =                (str[q+0]>>2)  & 0x3F; //     >>: bit shift
		ret[p++] = ((str[q+0]<<4)|(str[q+1]>>4)) & 0x3F; //      |: marge data
		ret[p++] = ((str[q+1]<<2)|(str[q+2]>>6)) & 0x3F; // & 0x3F: bit mask
		ret[p++] =  (str[q+2]<<0)                & 0x3F;
	}

	// 4 の倍数から溢れた分を計算する．
	if      (retLen_mod4==1){ ret[p++] =                (str[q+0]>>2)  & 0x3F;
	}else if(retLen_mod4==2){ ret[p++] =                (str[q+0]>>2)  & 0x3F;
							  ret[p++] =  (str[q+0]<<4)                & 0x3F;
	}else if(retLen_mod4==3){ ret[p++] =                (str[q+0]>>2)  & 0x3F;
							  ret[p++] = ((str[q+0]<<4)|(str[q+1]>>4)) & 0x3F;
							  ret[p++] =  (str[q+1]<<2)                & 0x3F;
	}

	const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //Base64の64文字
	uint p2=0;
	for(; p2<retLen;       p2++){ ret[p2] = b64_table[(uint)ret[p2]]; }
	for(; p2<retLen_total; p2++){ ret[p2] = '=';                      } // '=' padding

	return ret;
}
std::string sstd::base64_encode(const char* str){ return sstd::base64_encode(str, strlen(str)); }
std::string sstd::base64_encode(std::string& str){ return sstd::base64_encode(str.c_str(), str.size()); }


std::string sstd::base64_decode(const char* str, const size_t strLen){
	// str    : decodingするデータ (規格上，'=' padding により 4 の倍数に調整された文字列を渡す必要があるが，'=' padding がなくても，問題無くデコードできる．)
	// strLen : 終了コードを含まない str の長さを渡す．
	//
	// return : decodeした文字列を返す．

	// Base64encoding されているデータをdecodeするので，当然引数の「str」は，4バイト単位(4文字単位)のデータである．

//	size_t strLen;					// string length with '=' padding.
	size_t strLen_without_padding;	// string length without '=' padding.

	// counting length of 'str' without '='.
	for(strLen_without_padding=strLen; 0<strLen_without_padding && str[strLen_without_padding-1]=='='; strLen_without_padding--){}

	const uchar decode_table[256] = {	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x3F, 0x34, 0x35,

										0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04,
										0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
										0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
										0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1A, 0x1B, 0x1C,

										0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
										0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
										0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

										0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	// ASCIIコードの定義で記述されている文字列を，
	// Base64の定義である「'A'==0x00 ~ 'Z'==0x19, 'a'==0x1A ~ 'z'==0x33, '0'==0x34 ~ '9'==0x3D, '+'==0x3E, '/'==0x3F」に，
	// decode table を用いて変換する．
	std::string strBuf(strLen_without_padding, 0); // 終端文字分は，std::string 側で確保される
	for(uint i=0; i<strLen_without_padding; i++){
		uint buf=(uint)str[i]; if(buf==0xFF){ std::string ret_error(0, 0); return ret_error; /*ERROR*/ }
		strBuf[i]=decode_table[buf];
	}

	uint retLen = (strLen_without_padding*3)/4; //decodeするので，サイズは3/4倍になる．(strが4の倍数なので，割り切れなくなる事は無い．)
	std::string ret(retLen, 0);					// 終端文字分は，std::string 側で確保される

	uint retLen_mod3 = retLen % 3;
	uint retLen_div3 = retLen - retLen_mod3;	// same as 'retLen / 3'

	// 3 の倍数分を計算する．
	uint p=0, q=0;
	for(; p<retLen_div3; q+=4){ // 6bit と 8bit の最小公倍数が 6*4==24, 8*3==24 なので，4文字→3文字，単位でdecodeする．
		ret[p++] = (strBuf[q+0]<<2) | (strBuf[q+1]>>4);
		ret[p++] = (strBuf[q+1]<<4) | (strBuf[q+2]>>2);
		ret[p++] = (strBuf[q+2]<<6) | (strBuf[q+3]>>0);
	}

	// 3 の倍数から溢れた分を計算する．
	// [p], [q]は先ほどの続きから．
	if      (retLen_mod3==1){ ret[p++] = (strBuf[q+0]<<2) | (strBuf[q+1]>>4);
	}else if(retLen_mod3==2){ ret[p++] = (strBuf[q+0]<<2) | (strBuf[q+1]>>4);
							  ret[p++] = (strBuf[q+1]<<4) | (strBuf[q+2]>>2);
	}
//	// 別の書き方
//	for(uint k=0; p<retLen; p++, k++){ ret[p] = (strBuf[q+k]<<(1+k)*2) | (strBuf[q+k+1]>>(2-k)*2); }

	return ret;
}
std::string sstd::base64_decode(const char* str){ return sstd::base64_decode(str, strlen(str)); }
std::string sstd::base64_decode(std::string& str){ return sstd::base64_decode(str.c_str(), str.size()); }

void sstd::print_base64_decode_table(){

	const uchar b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	// Base64の64文字

	uchar decode_table[256];
	for(int i=0; i<256; i++){ decode_table[i] = 0xFF; }

	// make decode table
	for(int i=0; i<64; i++){ decode_table[b64_table[i]] = i; }

	for(uint i=0; i<256; i++){
		printf("0x%02X, ", decode_table[i]);
		if((i+1)%10==0){ printf("\n"); }
	}
	printf("\n");
}

//===

//変換テーブル :: 入力された数値をその数値の文字列に変換する。 ( 例 :: '0xE3' → "E3" )
const char sstd::bin2str_table[256][3] = { // 3 なのは、終端文字'\0'が挿入されるため。
	"00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F",
	"10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F",
	"20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F",
	"30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F",
	"40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F",
	"50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F",
	"60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F",
	"70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F",
	"80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F",
	"90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F",
	"A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF",
	"B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF",
	"C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF",
	"D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF",
	"E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF",
	"F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF"
};
std::string sstd::url_encode(const char* str, const size_t strLen){

	std::string ret;

	for(uint i=0; i<strLen; i++){

		if(	str[i] == '-' ||
			str[i] == '.' ||
			('0' <= str[i] && str[i] <= '9') ||
			('A' <= str[i] && str[i] <= 'Z') ||
			('a' <= str[i] && str[i] <= 'z') ||
			str[i] == '_' ||
			str[i] == '~'
		){
			// ASCII Code 順に、
			// '-'ハイフン、'.'ピリオド、数字、英語大文字、英語小文字、'_'アンダーバー、'~'チルダ
			// は、そのまま。

			ret += str[i];

		}else{
			// それ以外は%Codingする。

			ret += '%';
			ret += sstd::bin2str_table[ (uchar)str[i] ];	// ここは必ずunsignedにキャストしないと、負の値でバグる。
		}
	}
	return ret;
}
std::string sstd::url_encode(const char* str){ return sstd::url_encode(str, strlen(str)); }
std::string sstd::url_encode(std::string& str){ return sstd::url_encode(str.c_str(), str.size()); }


std::string sstd::url_encode_type2(const char* str, size_t strLen){

	std::string ret;

	for(uint i=0; i<strLen; i++){

		if(	str[i] == '-' ||
			str[i] == '.' ||
			('0' <= str[i] && str[i] <= '9') ||
			('A' <= str[i] && str[i] <= 'Z') ||
			('a' <= str[i] && str[i] <= 'z') ||
			str[i] == '_' ||
			str[i] == '~'
		){
			// ASCII Code 順に、
			// '-'ハイフン、'.'ピリオド、数字、英語大文字、英語小文字、'_'アンダーバー、'~'チルダ
			// は、そのまま。

			ret += str[i];

		}else{
			//それ以外は%Codingする。

			ret += '%';
			char str_buf[3];
		#ifdef _WIN32
			sprintf_s(str_buf, sizeof(str_buf), "%02X", (uchar)str[i]);
		#else
			sprintf(str_buf, "%02X", (uchar)str[i]);
		#endif
			str_buf[2] = 0x00; // 終端文字
			ret += str_buf;
		}
	}
	return ret;
}

void sstd::url_encode_compare_speed(){

	std::string str_url(256, 0); for(uint i=0; i<str_url.size(); i++){ str_url[i]=i; }

	printf("sstd::url_encode\n");
	time_m t1; sstd::measureTime_start(t1);
	for(uint i=0; i<10000; i++){ sstd::url_encode(str_url.c_str(), str_url.size()); }
	sstd::measureTime_stop(t1);
	
	printf("sstd::url_encode_type2\n");
	time_m t2; sstd::measureTime_start(t2);
	for(uint i=0; i<10000; i++){ sstd::url_encode_type2(str_url.c_str(), str_url.size()); }
	sstd::measureTime_stop(t2);
	
	/*
	  sstd::url_encode
	  --------------------------------
	  Execution time:     0. 101 sec
	  --------------------------------

	  sstd::url_encode_type2
	  --------------------------------
	  Execution time:     0. 393 sec
	  --------------------------------
	*/
}

//===

std::string sstd::url_decode(const char* str, const size_t strLen){

	// '0' -> 0, ..., '9' -> 9, 'A' -> 10, ..., 'F' -> 15
	// '0' -> 0, ..., '9' -> 9, 'a' -> 10, ..., 'f' -> 15
	// "GHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz-._~" -> 0xFE
	// the others -> 0xFF
	const uchar decode_table[256] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0x00, 0x01,
									  0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
									  0x0F, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
									  0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
									  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0x0A, 0x0B, 0x0C,
									  0x0D, 0x0E, 0x0F, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
									  0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
									  0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
									  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	std::string ret;
	
	for(uint i=0; i<strLen; i++){
		if(str[i]=='%'){
			if((i+2)>=strLen){ std::string ret_error(0, 0); return ret_error; /*ERROR*/ }

			uint buf1 = decode_table[(uchar)str[i+1]];
			uint buf2 = decode_table[(uchar)str[i+2]];
			if((buf1>=0xFE)||(buf2>=0xFE)){ std::string ret_error(0, 0); return ret_error; /*ERROR*/ }

			ret += (uchar)(16*buf1 + buf2);
			
			i+=2;
		}else if(decode_table[(uchar)str[i]] != 0xFF){ // same as "}else if(str[i] == '-' || str[i] == '.' || ('0' <= str[i] && str[i] <= '9') || ('A' <= str[i] && str[i] <= 'Z') || ('a' <= str[i] && str[i] <= 'z') || str[i] == '_' || str[i] == '~'){"
			ret += str[i];
			
		}else{
			std::string ret_error(0, 0); return ret_error; /*ERROR*/
		}
	}
	return ret;
}
std::string sstd::url_decode(const char* str){ return sstd::url_decode(str, strlen(str)); }
std::string sstd::url_decode(std::string& str){ return sstd::url_decode(str.c_str(), str.size()); }

void sstd::print_url_decode_table(){

	uchar decode_table[256];
	for(int i=0; i<256; i++){ decode_table[i] = 0xFF; }

	const uchar HEX_table[] = "0123456789ABCDEF";
	for(int i=0; i<16; i++){ decode_table[HEX_table[i]] = i; } // make decode table
	
	const uchar hex_table[] = "0123456789abcdef";
	for(int i=0; i<16; i++){ decode_table[hex_table[i]] = i; } // make decode table

	const uchar set0xFE_table[] = "GHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz-._~";
	for(int i=0; i<44; i++){ decode_table[set0xFE_table[i]] = 0xFE; } // make decode table

	for(uint i=0; i<256; i++){
//		if(decode_table[i]==0xFF){ printf("    0,");
//		}          else          { printf(" 0x%02X,", decode_table[i]); }
		printf(" 0x%02X,", decode_table[i]);
		
		if((i+1)%10==0){ printf("\n"); }
	}
	printf("\n");
}

//===

std::u16string sstd::utf8_to_utf16(const std::string& str){
	// MSVC++ だと，このテンプレにはバグがある
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cnv;
    return cnv.from_bytes(str);
}

std::string sstd::utf16_to_utf8(const std::u16string& str){
	// MSVC++ だと，このテンプレにはバグがある
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cnv;
    return cnv.to_bytes(str);
}

std::string sstd::unicodeEscape_encode(const std::u16string& str){

	std::string ret(6*str.size(), 0); ret.clear();

	for(uint i=0; i<str.size(); i++){
		ret += R"(\u)";
		
		uchar hi = (uchar)((str[i]>>8) & 0x00FF);
		uchar lo = (uchar)( str[i]     & 0x00FF);

		ret += bin2str_table[hi];
		ret += bin2str_table[lo];
	}
	return ret;
}

const uchar sstd::str2bin_table[256] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01,
										 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
										 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x0B, 0x0C,
										 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
										 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

std::u16string sstd::unicodeEscape_decode(const char* str, const size_t strLen){
	// in  : escaped string R"(\uABCD)"
	// out : bin '0xABCD'

	uint strLen_div6 = strLen / 6;
	uint strLen_mod6 = strLen - 6*strLen_div6; if(strLen_mod6!=0){ printf("error:001"); std::u16string ret_error(0); return ret_error; }
	int strLen_minus6 = strLen - 6; if(strLen_minus6<0){ printf("error:002"); std::u16string ret_error(0); return ret_error; }
	std::u16string ret(strLen_div6, 0);

	for(uint i=0, i2=0; i<=(uint)strLen_minus6; i2++){
		// '\\' と 'u' の二つ分ポインタを進める。
		i+=2;	//コールバイ・バリューなので、この操作はこの関数の中でのみ有効。
		
		uint16 buf;
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0, 0); return ret_error; }
		buf = sstd::str2bin_table[(uchar)str[i]];
		i++;
		
		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0, 0); return ret_error; }
		buf += sstd::str2bin_table[(uchar)str[i]];
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0, 0); return ret_error; }
		buf += sstd::str2bin_table[(uchar)str[i]];
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0, 0); return ret_error; }
		buf += sstd::str2bin_table[(uchar)str[i]];
		i++;

		ret[i2] = buf;
	}
	return ret;
}
std::u16string sstd::unicodeEscape_decode_type2(const char* str, const size_t strLen){
	// in  : escaped string "\\uABCD"	(エスケープ・シーケンスを考慮して「\」を「\\」として表記している。)
	// out : bin '0xABCD'

	uint strLen_div6 = strLen / 6;
	uint strLen_mod6 = strLen - 6*strLen_div6; if(strLen_mod6!=0){ printf("error:001"); std::u16string ret_error(0); return ret_error; }
	int strLen_minus6 = strLen - 6; if(strLen_minus6<0){ printf("error:002"); std::u16string ret_error(0); return ret_error; }
	std::u16string ret(strLen_div6, 0);

	for(uint i=0, i2=0; i<=(uint)strLen_minus6; i2++){
		// '\\' と 'u' の二つ分ポインタを進める。
		i+=2;	//コールバイ・バリューなので、この操作はこの関数の中でのみ有効。
		
		uint16 buf;
		
		if      ('0'<=str[i] && str[i]<='9'){ buf = str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf = str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf = str[i] - 'a' + 10;
		}               else                { printf("error:003"); std::u16string ret_error(0, 0); return ret_error; }
		i++;
		
		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if      ('0'<=str[i] && str[i]<='9'){ buf += str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf += str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf += str[i] - 'a' + 10;
		}               else                { printf("error:004"); std::u16string ret_error(0, 0); return ret_error; }
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if      ('0'<=str[i] && str[i]<='9'){ buf += str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf += str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf += str[i] - 'a' + 10;
		}               else                { printf("error:005"); std::u16string ret_error(0, 0); return ret_error; }
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if      ('0'<=str[i] && str[i]<='9'){ buf += str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf += str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf += str[i] - 'a' + 10;
		}               else                { printf("error:005"); std::u16string ret_error(0, 0); return ret_error; }
		i++;

		ret[i2] = buf;
	}
	return ret;
}
std::u16string sstd::unicodeEscape_decode(const char* str){ return sstd::unicodeEscape_decode(str, strlen(str)); }
std::u16string sstd::unicodeEscape_decode(const std::string& str){ return sstd::unicodeEscape_decode(str.c_str(), str.size()); }

void sstd::print_unicodeEscape_decode_table(){

	uchar decode_table[256];
	for(int i=0; i<256; i++){ decode_table[i] = 0xFF; }

	const uchar HEX_table[] = "0123456789ABCDEF";
	for(int i=0; i<16; i++){ decode_table[HEX_table[i]] = i; } // make decode table
	
	const uchar hex_table[] = "0123456789abcdef";
	for(int i=0; i<16; i++){ decode_table[hex_table[i]] = i; } // make decode table

	for(uint i=0; i<256; i++){
//		if(decode_table[i]==0xFF){ printf("    0,");
//		}          else          { printf(" 0x%02X,", decode_table[i]); }
		printf(" 0x%02X,", decode_table[i]);
		
		if((i+1)%10==0){ printf("\n"); }
	}
	printf("\n");
}

/*
std::string utf16_to_utf8(const char* str, size_t strLen){
//outバッファの使い方が分かり難いので、後で、やり直す。
//void Decode_escapedUTF16String_to_UTF8Binary(char* in, int &in_ReadSize, char* out, int &out_WriteSize){
	// in  : [例:サロゲートペア] 0x20B9Fなら、「\uD842\uDF9F」を入力すると、
	// out : UTF8で'0xF0','0xA0','0xAE','0x9F'が出力される。
	//
	// in  : あ : UTF16(Unicode)0x3042なら、「\u3042」を入力すると、
	// out : UTF8で'0xE3','0x81','0x82'が出力される。

	//文字列の読み込み。「\uD842\uDF9F」なら、前半分の「\uD842」だけ読み込む。
	Translate4ByteStringTo2ByteBinary( in , out );

	//value0は2Byte以上必要。(サロゲートペアなら3Byte以上必要。)
	unsigned long value0 = ((out[0]<<8)&0xFF00) | (out[1]&0x00FF);	//'0xD8','0x42' を 0xD842 のように、一つにまとめる。


	//サロゲートペアでは無い場合。
	//そのままUTF16をUTF8に変換する。

	if(/*0x00<=value0 && //value0<=0x7F){

		//UTF8で1Byteの文字
			//1Byte目
		out[0] = 0x00 | value0;			//out[0] = 0x00 | (value0 & 0x7F);	//最上位ビットなので、ビットマスクする必要が無い。

		in_ReadSize   = 6;	//[\uXXXX]
		out_WriteSize = 1;	//一文字

	}else if(/*0x80<=value0 && //value0<=0x7FF){

		//UTF8で2Byteの文字
			//2Byte目
		out[1] = 0x80 | (value0 & 0x3F);
			//1Byte目
		value0 = value0>>6;
		out[0] = 0xC0 | value0;			//out[0] = 0x00 | (value0 & 0x7F);	//最上位ビットなので、ビットマスクする必要が無い。

		in_ReadSize   = 6;	//[\uXXXX]
		out_WriteSize = 2;	//一文字

//	}else if(0x800<=value0 && value0<=0xFFFF){		//「0xD800<=value0 && value0<=0xDBFF」の範囲がサロゲートペアなので、その手前(0xD800-1)まで。
	}else if(value0<=(0xD800-1)||(0xDBFF+1)<=value0){

		//UTF8で3Byteの文字
			//3Byte目
		out[2] = 0x80 | (value0 & 0x3F);
			//2Byte目
		value0 = value0>>6;
		out[1] = 0x80 | (value0 & 0x3F);
			//1Byte目
		value0 = value0>>6;
		out[0] = 0xE0 | value0;			//out[0] = 0x00 | (value0 & 0x7F);	//最上位ビットなので、ビットマスクする必要が無い。

		in_ReadSize   = 6;	//[\uXXXX]
		out_WriteSize = 3;	//一文字

	}else{
//	}else if(0xD800<=value0 && value0<=0xDBFF){//この範囲の場合はサロゲートペアとして処理する必要がある。
//注意:区間[0xD800,0xDBFF]は、Unicodeの範囲と言うより、サロゲートペアが割り当てられている範囲。

		//サロゲートペアの処理。
		//サロゲートペアの処理

		//文字列の読み込み。「\uD842\uDF9F」なら、後ろ半分の「\uDF9F」だけ読み込む。
		Translate4ByteStringTo2ByteBinary( &in[6] , &out[2] );

		//value1は2Byte以上必要。
//		unsigned short value1 = ((out[2]<<8)&0xFF00) | (out[3]&0x00FF);	//'0xD8','0x42' を 0xD842 のように、一つにまとめる。
		unsigned short value1 = (out[2]<<8) | (out[3]&0x00FF);	//'0xD8','0x42' を 0xD842 のように、一つにまとめる。←このように、自分より大きい範囲を指定する場合でもビットマスクが必要。ただし、ビットシフトした方はゼロ埋めされるので不要。
		//この時、サロゲートペアの後半なので、value1は、[0xDC00,0xDFFF]の範囲に収まるはず。(収まっていなければ、文字コードの方がおかしいが、エラーの確認は省く。)

		//サロゲートペアによって4Byteに分割されたUTF16を、結合して元に戻す。(「\uD842\uDF9F」⇒「0x20B9F」の変換)
			//符号の除去
		value0 = value0 & 0x3FF;	//value0 -= 0xD800;と同じ。
//		value1 = value1 & 0x3FF;	//value1 -= 0xDC00;と同じ。//下記の結合処理でビットマスクする必要があるので、そちらにまとめる。(自分のサイズより大きい範囲にコピーするので、マスクしておく必要がある。ビットシフトした方はゼロ埋めされるので問題ない。)

		//(16～11Bitは符号ビットの部分なので、)10Bit目までを、単純につなげる。
		//代入先(value0)には3Byte以上必要
		value0 = (value0<<10)|(value1&0x3FF);

		value0 += 0x10000;//符号を加算

		//UTF16をUTF8に変換する。
		//サロゲートペアの場合は、「0x10000～0x10FFFFの範囲の文字」なので、必ず「0x 1 00 00 ～ 0x10 FF FF」の範囲に収まる。
		//→実際には「0x00 01 00 00  ～  0x00 1F FF FF」の範囲の文字は4ByteのUTF8が割り当てられており、
		//  4Byte以上のUTF8は現在定義されていないので、if文を回すまでも無く4Byteと判断できる。
		//→サロゲートペアの場合、UTF8に変換すると、必ず4Byteになる。
		//
		// 1Byte目           2Byte目           3Byte目           4Byte目
		// 1 1 1 1 0□□□   1 0□□□□□□   1 0□□□□□□   1 0□□□□□□
		//           1 0 0       0 0 1 1 1 1       1 1 1 1 1 1       1 1 1 1 1 1 == 0x10FFFF ← これはサロゲージペアを用いて表せる最大の範囲となる。時々ネットのサンプルで、UTF8で定義されていない5Byteや6Byteの範囲も計算できるように「一応」実装してみた、というパターンがあるが、UTF16のBinaryで表せる(Binaryで表せない==保存すらできない。(保存する規格が決まっていない。))最大値のサロゲージペアを使っても表せない領域なので、おおよそ意味を成さない。
		//           0 0 0       1 0 0 0 0 0       1 0 1 1 1 0       0 1 1 1 1 1 == 0x20B9F
			//4Byte目
		out[3] = 0x80 | (value0 & 0x3F);
			//3Byte目
		value0 = value0>>6;
		out[2] = 0x80 | (value0 & 0x3F);
			//2Byte目
		value0 = value0>>6;
		out[1] = 0x80 | (value0 & 0x3F);
			//1Byte目
		value0 = value0>>6;
		out[0] = 0xF0 | value0;				//out[0] = 0xF0 | (value0 & 0x07);	//最上位ビットなので、ビットマスクする必要が無い。

		in_ReadSize   = 6*2;	//[\uXXXX\uXXXX]
		out_WriteSize = 4;	//一文字
	}
}
*/
