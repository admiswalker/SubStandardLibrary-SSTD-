#include "encode_decode.hpp"
#include "ssprintf.hpp"

#include "measureTime.hpp"

#include <iostream>
#include <string>
//#include <codecvt>
#include <cassert>
#include <locale>


std::string sstd::base64_encode(const uchar* str, size_t strLen){

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
std::string sstd::base64_encode(const uchar* str){ return sstd::base64_encode(str, strlen((const char*)str)); }
std::string sstd::base64_encode(const std::string& str){ return sstd::base64_encode((const uchar*)str.c_str(), str.size()); }


std::string sstd::base64_decode(const uchar* str, size_t strLen){
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
		uint buf=(uint)str[i]; if(buf==0xFF){ std::string ret_error(0); return ret_error; /*ERROR*/ }
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
std::string sstd::base64_decode(const uchar* str){ return sstd::base64_decode(str, strlen((const char*)str)); }
std::string sstd::base64_decode(const std::string& str){ return sstd::base64_decode((const uchar*)str.c_str(), str.size()); }

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
std::string sstd::url_encode(const char* str, size_t strLen){

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
	sstd::measureTime_stop_print(t1);
	
	printf("sstd::url_encode_type2\n");
	time_m t2; sstd::measureTime_start(t2);
	for(uint i=0; i<10000; i++){ sstd::url_encode_type2(str_url.c_str(), str_url.size()); }
	sstd::measureTime_stop_print(t2);
	
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

std::string sstd::url_decode(const char* str, size_t strLen){

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
			if((i+2)>=strLen){ std::string ret_error(0); return ret_error; /*ERROR*/ }

			uint buf1 = decode_table[(uchar)str[i+1]];
			uint buf2 = decode_table[(uchar)str[i+2]];
			if((buf1>=0xFE)||(buf2>=0xFE)){ std::string ret_error(0); return ret_error; /*ERROR*/ }

			ret += (uchar)(16*buf1 + buf2);
			
			i+=2;
		}else if(decode_table[(uchar)str[i]] != 0xFF){ // same as "}else if(str[i] == '-' || str[i] == '.' || ('0' <= str[i] && str[i] <= '9') || ('A' <= str[i] && str[i] <= 'Z') || ('a' <= str[i] && str[i] <= 'z') || str[i] == '_' || str[i] == '~'){"
			ret += str[i];
			
		}else{
			std::string ret_error(0); return ret_error; /*ERROR*/
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
/*
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
*/
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

std::u16string sstd::unicodeEscape_decode(const char* str, size_t strLen){
	// in  : escaped string, R"(\uABCD)"
	// out : bin '0xABCD'

	uint strLen_div6 = strLen / 6;
	uint strLen_mod6 = strLen - 6*strLen_div6; if(strLen_mod6!=0){ std::u16string ret_error(0); return ret_error; }
	int strLen_minus6 = strLen - 6; if(strLen_minus6<0){ std::u16string ret_error(0); return ret_error; }
	std::u16string ret(strLen_div6, 0);

	for(uint i=0, i2=0; i<=(uint)strLen_minus6; i2++){
		i+=2; // '\\' と 'u' の二つ分ポインタを進める。
		
		uint16 buf;
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0); return ret_error; }
		buf = sstd::str2bin_table[(uchar)str[i]];
		i++;
		
		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0); return ret_error; }
		buf += sstd::str2bin_table[(uchar)str[i]];
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0); return ret_error; }
		buf += sstd::str2bin_table[(uchar)str[i]];
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if(sstd::str2bin_table[(uchar)str[i]] == 0xFF){ std::u16string ret_error(0); return ret_error; }
		buf += sstd::str2bin_table[(uchar)str[i]];
		i++;

		ret[i2] = buf;
	}
	return ret;
}
std::u16string sstd::unicodeEscape_decode_type2(const char* str, size_t strLen){
	// in  : escaped string, R"(\uABCD)"
	// out : bin '0xABCD'

	uint strLen_div6 = strLen / 6;
	uint strLen_mod6 = strLen - 6*strLen_div6; if(strLen_mod6!=0){ std::u16string ret_error(0); return ret_error; }
	int strLen_minus6 = strLen - 6; if(strLen_minus6<0){ std::u16string ret_error(0); return ret_error; }
	std::u16string ret(strLen_div6, 0);

	for(uint i=0, i2=0; i<=(uint)strLen_minus6; i2++){
		i+=2; // '\\' と 'u' の二つ分ポインタを進める
		
		uint16 buf;
		
		if      ('0'<=str[i] && str[i]<='9'){ buf = str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf = str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf = str[i] - 'a' + 10;
		}               else                { std::u16string ret_error(0); return ret_error; }
		i++;
		
		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if      ('0'<=str[i] && str[i]<='9'){ buf += str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf += str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf += str[i] - 'a' + 10;
		}               else                { std::u16string ret_error(0); return ret_error; }
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if      ('0'<=str[i] && str[i]<='9'){ buf += str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf += str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf += str[i] - 'a' + 10;
		}               else                { std::u16string ret_error(0); return ret_error; }
		i++;

		buf = buf<<4;	// 一桁目を桁上げ	//「buf*=16;」と同じ意味。
		
		if      ('0'<=str[i] && str[i]<='9'){ buf += str[i] - '0';
		}else if('A'<=str[i] && str[i]<='F'){ buf += str[i] - 'A' + 10;
		}else if('a'<=str[i] && str[i]<='f'){ buf += str[i] - 'a' + 10;
		}               else                { std::u16string ret_error(0); return ret_error; }
		i++;

		ret[i2] = buf;
	}
	return ret;
}
std::u16string sstd::unicodeEscape_decode(const char* str){ return sstd::unicodeEscape_decode(str, strlen(str)); }
std::u16string sstd::unicodeEscape_decode(const std::string& str){ return sstd::unicodeEscape_decode(str.c_str(), str.size()); }

void sstd::unicodeEscape_compare_speed(){

	std::string str_encoded(0xFFFF, 0); str_encoded.clear();
	for(uint32 i=0; i<0xFFFF; i++){ str_encoded+=sstd::ssprintf("\\u%04X", i); }

	printf("sstd::url_encode\n");
	time_m t1; sstd::measureTime_start(t1);
	for(uint i=0; i<25; i++){ sstd::url_encode(str_encoded.c_str(), str_encoded.size()); }
	sstd::measureTime_stop_print(t1);
	printf("\n");
	
	printf("sstd::url_encode_type2\n");
	time_m t2; sstd::measureTime_start(t2);
	for(uint i=0; i<25; i++){ sstd::url_encode_type2(str_encoded.c_str(), str_encoded.size()); }
	sstd::measureTime_stop_print(t2);
	
	/*
	  sstd::url_encode
	  --------------------------------
	   Execution time:     0. 101 sec
	  --------------------------------
	  
	  sstd::url_encode_type2
	  --------------------------------
	   Execution time:     0. 373 sec
	  --------------------------------
	*/
}

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


std::u32string sstd::utf16_to_utf32(const std::u16string& str){

	std::u32string ret;

	uint i=0;
	for(; i<str.size()-1; i++){
		if(str[i]<=0xD7FF || 0xE000<=str[i]){ // same as "if((0x0000<=str[i] && str[i]<=0xD7FF)||(0xE000<=str[i] && str[i]<=0xFFFF)){"
			// When it is not a surrogate pair
			ret += str[i];
		}else if((0xD800<=str[i] && str[i]<=0xDBFF)&&(0xDC00<=str[i+1] && str[i+1]<=0xDFFF)){
			// In the case of a surrogate pair
			ret += 0x10000 + ((str[i]-0xD800)<<10) + (str[i+1]-0xDC00); // same as "ret += 0x10000 + (str[i]-0xD800)*0x400 + (str[i]-0xDC00);"
			i++;
		}else{
			return std::u32string(0); // Error
		}
	}
	if(i<str.size()){
		if(str[i]<=0xD7FF||0xE000<=str[i]){ // same as "if((0x0000<=str[i] && str[i]<=0xD7FF)||(0xE000<=str[i] && str[i]<=0xFFFF)){"
			// When it is not a surrogate pair
			ret += str[i];
		}else{
			return std::u32string(0); // Error
		}
	}
	
	return ret;
}
std::u16string sstd::utf32_to_utf16(const std::u32string& str){

	std::u16string ret;

	for(uint i=0; i<str.size(); i++){
		if(str[i]<=0xD7FF || (0xE000<=str[i] && str[i]<=0xFFFF)){ // if((0x0000<=str[i] && str[i]<=0xD7FF)||(0xE000<=str[i] && str[i]<=0xFFFF)){
			ret += str[i];
		}else if(0x10000<=str[i] && str[i]<=0x10FFFF){ // UTF-16 では，0x10FFFF が最大値で，少なくとも現在は，0x10FFFF より大きな値に 文字は割り当てられていない．
			uint16 str_val = str[i] - 0x10000;
			uint16 str_div = str_val << 10;
			uint16 str_mod = str_val - (str_div>>10);
			ret += str_div + 0xD800;
			ret += str_mod + 0xDC00;

			// same as"
			// uint16 hi = (str[i]-0x10000)/0x400 + 0xD800; ret += hi;
			// uint16 lo = (str[i]-0x10000)%0x400 + 0xDC00; ret += lo;
			// ".
		}else{
			// When a value is for surrogate pair. (0xD800<=str[i] && str[i]<=0xDFFF)
			return std::u16string(0); // Error
		}
	}

	return ret;
}
std::string sstd::utf32_to_utf8(const std::u32string& str){
	/*
	  変換表 (実際にはUTF8は4Byte目までしか現在定義されていない．)
	  +------------------------+-------------------------------------------------------------------+
	  | Unicode                | UTF-8                                                             |
	  |                        | 1Byte目    2Byte目    3Byte目    4Byte目    5Byte目    6Byte目    |
	  +------------------------+-------------------------------------------------------------------+
	  | 0x00000000～0x0000007F | 0b0XXXXXXX ---------- ---------- ---------- ---------- ---------- |
	  | 0x00000080～0x000007FF | 0b110XXXXX 0b10XXXXXX ---------- ---------- ---------- ---------- |
	  | 0x00000800～0x0000FFFF | 0b1110XXXX 0b10XXXXXX 0b10XXXXXX ---------- ---------- ---------- |
	  | 0x00010000～0x001FFFFF | 0b11110XXX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX ---------- ---------- |
	  | 0x00200000～0x03FFFFFF | 0b111110XX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX ---------- |
	  | 0x04000000～0x7FFFFFFF | 0b1111110X 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX |
	  +------------------------+-------------------------------------------------------------------+
	*/
	
	std::string ret;

	for(uint i=0; i<str.size(); i++){
		if      (str[i]<=0x0000007F){ // if      (0x00000000<=str[i] && str[i]<=0x0000007F){
			// 1 Byte, 7 bits valid
			ret += str[i];
		}else if(str[i]<=0x000007FF){ // }else if(0x00000080<=str[i] && str[i]<=0x000007FF){
			// 2 Bytes, 11 bits valid
			ret += 0b11000000 | (str[i]>>6);
			ret += 0b10000000 | (str[i] & 0b00111111);
		}else if(str[i]<=0x0000FFFF){ // }else if(0x00000800<=str[i] && str[i]<=0x0000FFFF){
			// 3 Bytes, 16 bits valid
			uint32 str_shift_6 = str[i]>>6;
			ret += 0b11100000 | (str_shift_6>>6);
			ret += 0b10000000 | (str_shift_6 & 0b00111111);
			ret += 0b10000000 | (str[i] & 0b00111111);

			// same as "
			// ret += 0b11100000 | (str[i]>>12);
			// ret += 0b10000000 |((str[i]>> 6) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 | (str[i] & 0b00111111);
			// "
		}else if(str[i]<=0x0001FFFF){ // }else if(0x00010000<=str[i] && str[i]<=0x0001FFFF){
 			// 4 Bytes, 21 bits valid
			uint32 str_shift_6 = str[i]>>6;
			uint32 str_shift12 = str_shift_6>>6;
			ret += 0b11110000 | (str_shift12>>6);
			ret += 0b10000000 | (str_shift12 & 0b00111111);
			ret += 0b10000000 | (str_shift_6 & 0b00111111);
			ret += 0b10000000 | (str[i] & 0b00111111);

			// same as "
			// ret += 0b11110000 | (str[i]>>18);
			// ret += 0b10000000 |((str[i]>>12) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 |((str[i]>> 6) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 | (str[i] & 0b00111111);
			// "
		}else if(str[i]<=0x03FFFFFF){ // }else if(0x00200000<=str[i] && str[i]<=0x03FFFFFF){
			// 5 Bytes, 26 bits valid
			uint32 str_shift_6 = str[i]>>6;
			uint32 str_shift12 = str_shift_6>>6;
			uint32 str_shift18 = str_shift12>>6;
			ret += 0b11110000 | (str_shift18>>6);
			ret += 0b10000000 | (str_shift18 & 0b00111111);
			ret += 0b10000000 | (str_shift12 & 0b00111111);
			ret += 0b10000000 | (str_shift_6 & 0b00111111);
			ret += 0b10000000 | (str[i] & 0b00111111);

			// same as "
			// ret += 0b11111000 | (str[i]>>24);
			// ret += 0b10000000 |((str[i]>>18) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 |((str[i]>>12) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 |((str[i]>> 6) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 | (str[i] & 0b00111111);
			// "
		}else if(str[i]<=0x7FFFFFFF){ // }else if(0x04000000<=str[i] && str[i]<=0x7FFFFFFF){
			// 6 Bytes, 31 bits valid
			uint32 str_shift_6 = str[i]>>6;
			uint32 str_shift12 = str_shift_6>>6;
			uint32 str_shift18 = str_shift12>>6;
			uint32 str_shift24 = str_shift18>>6;
			ret += 0b11110000 | (str_shift24>>6);
			ret += 0b10000000 | (str_shift24 & 0b00111111);
			ret += 0b10000000 | (str_shift18 & 0b00111111);
			ret += 0b10000000 | (str_shift12 & 0b00111111);
			ret += 0b10000000 | (str_shift_6 & 0b00111111);
			ret += 0b10000000 | (str[i] & 0b00111111);

			// same as "
			// ret += 0b11111100 | (str[i]>>30);
			// ret += 0b10000000 |((str[i]>>24) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 |((str[i]>>18) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 |((str[i]>>12) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 |((str[i]>> 6) & 0b00111111); // 余分な bits shift は良くない．
			// ret += 0b10000000 | (str[i] & 0b00111111);
			// "
		}else{
			return std::string(0); // Error
		}
	}

	return ret;
}
std::u32string sstd::utf8_to_utf32(const std::string& str){

	// 何故エラーチェックが必要か？
	//
	// 「なお、セキュリティの観点からはUTF-8の冗長表現が問題になることもあります。
	//   例えば0xC0 0xAF(11000000 10101111)は、
	//   ２バイトのUTF-8として扱うと[101111]の部分がデータになりますので、
	//   0x2F(バックスラッシュ）と等価になります。」
	// Refarence: http://www.ryusuke.net/archives/601
	
	std::u32string ret(str.size(), 0); ret.clear();
	uint p = 0; // place

	uint i=0;
	for(; i<str.size(); i++){
		uint remainingNum = str.size() - i;
		if(0b00000000<=(uint8)str[i] && (uint8)str[i]<=0b01111111){
			// 1 Bytes
			ret += (uint8)str[i];
			p++;
			
		}else if(0b11000000<=(uint8)str[i] && (uint8)str[i]<=0b11011111){
			// 2 Bytes
			if(remainingNum<2){ break; }
			if(((uint8)str[i+1]|0b11000000)==0b10000000)
			{
				return std::u32string(0); // Error
			}
			
			ret += (uint32)((uint8)str[i] & 0b00011111);
			ret[p] = ret[p]<<6 | (str[i+1] & 0b00111111);
			i+=1;

			if(!(0x00000080<=ret[p] && ret[p]<=0x000007FF)){ return std::u32string(0); /* Error */ }
			p++;
			
		}else if(0b11100000<=(uint8)str[i] && (uint8)str[i]<=0b11101111){
			// 3 Bytes
			if(remainingNum<3){ break; }
			if((((uint8)str[i+1]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+2]|0b11000000)==0b10000000))
			{
				return std::u32string(0); // Error
			}

			ret += (uint32)((uint8)str[i] & 0b00001111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+1] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+2] & 0b00111111);
			i+=2;
			
			if(!(0x00000800<=ret[p] && ret[p]<=0x0000FFFF)){ return std::u32string(0); /* Error */ }
			p++;

		}else if(0b11110000<=(uint8)str[i] && (uint8)str[i]<=0b11110111){
			// 4 Bytes
			if(remainingNum<4){ break; }
			if((((uint8)str[i+1]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+2]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+3]|0b11000000)==0b10000000))
			{
				return std::u32string(0); // Error
			}

			ret += (uint32)((uint8)str[i] & 0b00000111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+1] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+2] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+3] & 0b00111111);
			i+=3;
			
			if(!(0x00010000<=ret[p] && ret[p]<=0x001FFFFF)){ return std::u32string(0); /* Error */ }
			p++;

		}else if(0b11111000<=(uint8)str[i] && (uint8)str[i]<=0b11111011){
			// 5 Bytes
			if(remainingNum<5){ break; }
			if((((uint8)str[i+1]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+2]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+3]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+4]|0b11000000)==0b10000000))
			{
				return std::u32string(0); // Error
			}

			ret += (uint32)((uint8)str[i] & 0b00000011);
			ret[p] = ret[p]<<6 | ((uint8)str[i+1] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+2] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+3] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+4] & 0b00111111);
			i+=4;

			if(!(0x00200000<=ret[p] && ret[p]<=0x03FFFFFF)){ return std::u32string(0); /* Error */ }
			p++;

		}else if(0b11111100<=(uint8)str[i] && (uint8)str[i]<=0b11111101){
			// 6 Bytes
			if(remainingNum<6){ break; }
			if((((uint8)str[i+1]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+2]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+3]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+4]|0b11000000)==0b10000000) &&
			   (((uint8)str[i+5]|0b11000000)==0b10000000))
			{
				return std::u32string(0); // Error
			}

			ret += (uint32)((uint8)str[i] & 0b00000001);
			ret[p] = ret[p]<<6 | ((uint8)str[i+1] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+2] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+3] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+4] & 0b00111111);
			ret[p] = ret[p]<<6 | ((uint8)str[i+5] & 0b00111111);
			i+=5;

			if(!(0x04000000<=ret[p] && ret[p]<=0x7FFFFFFF)){ return std::u32string(0); /* Error */ }
			p++;

		}else{
			return std::u32string(0); // Error
		}
	}

	return ret;
}
std::u16string sstd::utf8_to_utf16(const std::string& str){
	std::u32string buf = sstd::utf8_to_utf32(str);
	return sstd::utf32_to_utf16(buf);
}
std::string sstd::utf16_to_utf8(const std::u16string& str){
	std::u32string buf = sstd::utf16_to_utf32(str);
	return sstd::utf32_to_utf8(buf);
}
