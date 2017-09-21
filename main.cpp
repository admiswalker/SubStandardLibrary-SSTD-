#include <stdio.h>
#include <iostream>

#define DEBUG
//#define sstd_usePause		// Enable to switch "Pause" or "Not Pause" by "#define UseSysPause".
#define sstd_usePauseIfWin32	// Enable to switch "Pause" or "Not Pause" by "#define UsePauseIfWin32".
#define sstd_measureTime
#include "./sstd/sstd.hpp"


void TEST_sstd_src(){

	printf("■ measureTime_start---------------\n\n");
	time_m timem; sstd::measureTime_start(timem);

	// something you want to mesure time.
	printf("■ sleep\n\n");
//	sstd::sleep_hour(1);
//	sstd::sleep_min (1);
//	sstd::sleep_s   (1);
//	sstd::sleep_ms  (1000);
//	sstd::sleep_us  (1000*1000);
//	sstd::sleep_ns  (1000*1000*1000);

	printf("■ measureTime_stop----------------\n");
	sstd::measureTime_stop(timem);

	//===
	
	printf("■ typeDef\n");
	uchar   uc =  1; printf("uchar:  %u\n",     uc);
	uint    ui =  2; printf("uint:   %u\n",     ui);
	uint8   u8 =  8; printf("uint8:  %u\n",     u8);
	uint16 u16 = 16; printf("uint16: %u\n",    u16);
	uint32 u32 = 32; printf("uint32: %u\n",    u32);
	uint64 u64 = 64; printf("uint64: %lu\n\n", u64);

	//===

	printf("■ #define DEBUG\n");
	printf("  □ pdbg (printf debugger)\n");
	sstd::pdbg("abc\n");
	printf("true: "); sstd::pdbg_if(true, "print txt"); printf("\n");
	printf("false: "); sstd::pdbg_if(false, "not print txt"); printf("\n");
//	printf("true: "); sstd::pdbg_if_exit(true, "exit");
	printf("false: "); sstd::pdbg_if_exit(false, "not exit"); printf("\n");
//	printf("true: "); sstd::pdbg_if_stop_exit(true, "exit"); printf("\n");
//	printf("false: "); sstd::pdbg_if_stop_exit(false, "not exit"); printf("\n");
	sstd::dbg(printf("run debug code."););
	sstd::ndbg(printf("run ndebug code."););
	printf("\n");

	sstd::pdbg_always("%s\n", "always print message");
//	sstd::pdbg_always_stop_exit("%s\n", "always print message, stop and exit.");
	printf("\n");

	//===

	printf("■ math\n");
		// 偶数への丸め (round to even)
	 float re_f1 = sstd::round2even(1.5); printf("round to even: %lf ≒ %lf\n", 1.5, re_f1);
	 float re_f2 = sstd::round2even(2.5); printf("round to even: %lf ≒ %lf\n", 2.5, re_f2);
	double re_d1 = sstd::round2even(1.5); printf("round to even: %lf ≒ %lf\n", 1.5, re_d1);
	double re_d2 = sstd::round2even(2.5); printf("round to even: %lf ≒ %lf\n", 2.5, re_d2);
		// 奇数への丸め (round to odd)
	 float ro_f1 = sstd::round2odd(1.5); printf("round to odd: %lf ≒ %lf\n", 1.5, ro_f1);
	 float ro_f2 = sstd::round2odd(2.5); printf("round to odd: %lf ≒ %lf\n", 2.5, ro_f2);
	double ro_d1 = sstd::round2odd(1.5); printf("round to odd: %lf ≒ %lf\n", 1.5, ro_d1);
	double ro_d2 = sstd::round2odd(2.5); printf("round to odd: %lf ≒ %lf\n", 2.5, ro_d2);
	printf("\n");

	std::vector<float> buf_f = {-3, -2, -1, 0, 1, 2, 3, 4};
	printf("sum: %f\n", sstd::sum(buf_f));
	printf("sum_abs: %f\n", sstd::sum_abs(buf_f));
	printf("ave: %f\n", sstd::ave(buf_f));
	printf("max: %f\n", sstd::max(buf_f));
	printf("max_abs: %f\n", sstd::max_abs(buf_f));
	printf("min: %f\n", sstd::min(buf_f));
	printf("min_abs: %f\n", sstd::min_abs(buf_f));
	printf("var: %f\n", sstd::var(buf_f));
	printf("var_p: %f\n", sstd::var_p(buf_f));
	printf("stdev: %f\n", sstd::stdev(buf_f));
	printf("stdev_p: %f\n", sstd::stdev_p(buf_f));
	printf("\n");
	
	std::vector<double> buf_d = {-3, -2, -1, 0, 1, 2, 3, 4};
	printf("sum: %f\n", sstd::sum(buf_d));
	printf("sum_abs: %f\n", sstd::sum_abs(buf_d));
	printf("ave: %f\n", sstd::ave(buf_d));
	printf("max: %f\n", sstd::max(buf_d));
	printf("max_abs: %f\n", sstd::max_abs(buf_d));
	printf("min: %f\n", sstd::min(buf_d));
	printf("min_abs: %f\n", sstd::min_abs(buf_d));
	printf("var: %f\n", sstd::var(buf_d));
	printf("var_p: %f\n", sstd::var_p(buf_d));
	printf("stdev: %f\n", sstd::stdev(buf_d));
	printf("stdev_p: %f\n", sstd::stdev_p(buf_d));
	printf("\n");

	/* test: Kahan summation algorithm 01 */
	std::vector<float> buf_f2 = {100000.0, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125}; // float の有効桁数 = 24/1og2(10) ≒ 7.224 ≒ 7
	printf("sum: %lf\n", sstd::sum(buf_f2));
	std::vector<double> buf_d2 = {100000000000000.0, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125}; // double の有効桁数 = 24/1og2(10) ≒ 15.955 ≒ 15
	printf("sum: %lf\n", sstd::sum(buf_d2));
	printf("\n");
	
	/* test: Kahan summation algorithm 02 */
	/*
	double d1=100000000.0;
	double d2=0.000000001;
	for(uint i=0; i<1000000000; i++){ d1+=d2; }
	printf("normal sum: %lf\n", d1);

	double lhs=d1;
	double del=0;
	for(uint i=0; i<1000000000; i++){
		double r1=d2-del;
		double r2=lhs+r1;
		del=(r2-lhs)-r1;
		lhs=r2;
	}
	printf(" Kahan sum: %lf\n", lhs);
	printf("\n");
	*/
	
	//===

	printf("■ fopen\n");

	FILE* fp;
	const char* FileName = "./test_fopen.txt";

	if(!sstd::fopen(&fp, FileName, "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
		// falied
		printf("false\n\n");
	}else{
		// success
		printf("example.txt was made.\n\n");
		std::string buf="abc";
		fwrite(buf.c_str(), 1, buf.size(), fp);
	}
	fclose(fp);

	//===
	
	printf("■ mkdir\n\n");
	sstd::mkdir("./test_mkdir");	// <- 再帰的にディレクトリを生成できるようにすること．

	//===

	printf("■ ssprintf(const char* format, ...)\n");
	printf("%s", sstd::ssprintf("Num: %d, Str: %s\n\n", 1234, "abcd").c_str());

	//===
	
	printf("■ strmatch\n");
	const char* str = "abcdefghijk"; // str: 比較する文字列
	const char* WildCard1 = "abc*";
	const char* WildCard2 = "a?cdefghijk";
	const char* WildCard3 = "a?";
	printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard1, sstd::strmatch(str, WildCard1)?"true":"false");
	printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard2, sstd::strmatch(str, WildCard2)?"true":"false");
	printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard3, sstd::strmatch(str, WildCard3)?"true":"false");
	printf("\n");

	printf("  □ isNum, isAlphabet\n");
	printf("    isNum               ('%c') -> %s\n", '0', sstd::isNum               ('0')?"true":"false");
	printf("    isAlphabet          ('%c') -> %s\n", 'a', sstd::isAlphabet          ('a')?"true":"false");
	printf("    isAlphabet_onlyUpper('%c') -> %s\n", 'A', sstd::isAlphabet_onlyUpper('A')?"true":"false");
	printf("    isAlphabet_onlyLower('%c') -> %s\n", 'a', sstd::isAlphabet_onlyLower('a')?"true":"false");
	printf("\n");

	//===

	printf("■ getFilePathInDir\n");
	
	const char* DirAndFileName_withWildCard = R"(./sstd/src/*.hpp)";
	printf("DirAndFileName_withWildCard: %s\n\n", DirAndFileName_withWildCard);
	std::vector<std::string> PathList = sstd::getFilePathInDir(DirAndFileName_withWildCard);
	for(uint i=0; i<PathList.size(); i++){ printf("%s\n", PathList[i].c_str()); } printf("\n");

	//===
	
	printf("■ pathNameExtractor\n"); // <- 不足する関数を追加する必要がある．
	
	const char* pPath="./abc/def/text.abc.txt\0";
	
	printf("Input pPath: %s\n", pPath);
	printf("Output getPath: %s\n",                     sstd::getPath                     (pPath).c_str());
	printf("Output getFileName: %s\n",                 sstd::getFileName                 (pPath)        );
	printf("Output getFileNameWithoutExtension: %s\n", sstd::getFileName_withoutExtension(pPath).c_str());
	printf("Output getFileExtension: %s\n",            sstd::getExtension                (pPath)        );
	printf("\n");

	//===

	printf("■ tinyInterpreter\n");
	printf("  □ readAll_withoutBOM & splitByLine\n");
	std::string str_tI = sstd::readAll_withoutBOM(R"(./tinyInterpreter.txt)");
	std::vector<std::string> splitLList = sstd::splitByLine(str_tI);
	printf("\n");
	printf("  tinyInterpreter.txt\n");
	printf("+----+----------------------------------------------------------------------------+\n");
	for(uint i=0; i<splitLList.size(); i++){
		printf("| %2d | %-74s |\n", i, splitLList[i].c_str());
	}
	printf("+----+----------------------------------------------------------------------------+\n");
	printf("\n");
	
	printf("  □ getCommandList & splitByComma\n");
	std::vector<std::string> cmdList = sstd::getCommandList(R"(./tinyInterpreter.txt)");
	for(uint i=0; i<cmdList.size(); i++){
		std::vector<std::string> splitCList = sstd::splitByComma(cmdList[i]);
		for(uint n=0; n<splitCList.size(); n++){ printf("[%5s] ", splitCList[n].c_str()); } printf("\n");
	}
	printf("\n");


	//===

	printf("■ encode_decode\n");
	printf("  □ base64_encode\n");
	std::string str_b64  = "#include \"./sstd/sstd.hpp\".+=ABCD";
	printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64.c_str(), str_b64.size()).c_str());
	printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64.c_str()).c_str());
	printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64).c_str());

	printf("  □ base64_decode\n");
	std::string str_b64e = sstd::base64_encode(str_b64);
	printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e.c_str(), str_b64e.size()).c_str());
	printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e.c_str()).c_str());
	printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e).c_str());

	printf("  □ make_base64_decode_table\n");
	sstd::print_base64_decode_table(); // for developers
	printf("\n");

	printf("  □ url_encode\n");
	std::string str_url(256, 0); for(uint i=0; i<str_url.size(); i++){ str_url[i]=i; }
	printf("    [url encode]-> %s\n", sstd::url_encode(str_url.c_str(), str_url.size()).c_str());
	printf("    [url encode]-> %s\n", sstd::url_encode(str_url.c_str()).c_str()); // 先頭が 0 なので、終端だと判断されている。
	printf("    [url encode]-> %s\n", sstd::url_encode(str_url).c_str());
	printf("\n");

	sstd::url_encode_compare_speed(); // for developers
	printf("\n");
	
	printf("  □ url_decode\n");
	std::string str_url_d = sstd::url_encode("#include \"./sstd/sstd.hpp\".+=ABCD");
	printf("    %s ->[url encode]-> %s\n", "#include \"./sstd/sstd.hpp\".+=ABCD", str_url_d.c_str());
	printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d.c_str(), str_url_d.size()).c_str());
	printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d.c_str()).c_str());
	printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d).c_str());
	printf("\n");
	
	printf("  □ make_url_decode_table\n");
	sstd::print_url_decode_table();
	printf("\n");

	//===

	printf("■ utf8 <-> utf16\n");
	printf("  □ unicode escape (utf16) -> utf16 (binary)\n");
	std::string escaped_utf16 = R"(\u30e6\u30cb\u30b3\u30fc\u30c9)"; // "ユニコード"
	std::u16string utf16_bin = sstd::unicodeEscape_decode(escaped_utf16);
	for(uint i=0; i<utf16_bin.size(); i++){
		printf("%X\n", utf16_bin[i]);
	}
	printf("  □ utf16 (binary) -> utf8\n");
	std::string utf8 = sstd::utf16_to_utf8(utf16_bin);
	printf("%s\n", utf8.c_str());

	printf("  □ utf16 (binary) -> unicode escape (utf16)\n");
	printf("%s\n", sstd::unicodeEscape_encode(utf16_bin).c_str());
	
	printf("  □ make_unicodeEscape_decode_table\n");
	sstd::print_unicodeEscape_decode_table();
	printf("\n");

	//===

//	printf("■ #define UsePause\n");
	sstd::pause();
//	printf("■ #define UsePauseIfWin32\n");
	sstd::pauseIfWin32(); // win32 の場合のみ停止
//	printf("\n");
}


void TEST_tmat(){
	
	printf("■ Init sstd::tmat<type>\n");
	printf("\n");
	
	sstd::tmat<double> Matd(5, 3);
	printf("RowNum: %d\n", Matd.rows());
	printf("ColNum: %d\n", Matd.cols());
	printf("Length: %d\n", Matd.len());

	printf("Indication of column major\n");
	uint i=0;
	for(uint q=0; q<Matd.cols(); q++){
		for(uint p=0; p<Matd.rows(); p++){
			Matd(p, q) = i; i++;
		}
	}
	tmat::print(Matd);
	printf("\n");
	
	//===
	
	i=0;
	for(uint q=0; q<Matd.len(); q++){ Matd[i] = i; i++; }
	tmat::print(Matd);
	printf("\n");

	//===
	
	sstd::tmat<double>* pMatd = new sstd::tmat<double>(5, 3);
	printf("RowNum: %d\n", pMatd->rows());
	printf("ColNum: %d\n", pMatd->cols());
	printf("Length: %d\n", pMatd->len());

	printf("Indication of column major\n");
	i=0;
	for(uint q=0; q<pMatd->cols(); q++){
		for(uint p=0; p<pMatd->rows(); p++){
			(*pMatd)(p, q) = i; i++;
		}
	}

	tmat::print(*pMatd);
	printf("\n");
	delete pMatd;
	
	//===

	printf("■ copy\n");printf("\n");
	sstd::tmat<double> Matd_copy = Matd;
	Matd_copy = Matd; // "tmat::copy(Matd_copy, Matd);" is called.
	tmat::print(Matd_copy); printf("\n");

	//===

	printf("■ copy row\n");printf("\n");
	sstd::tmat<double> Matd_rowCopy(5, 3); tmat::zeros(Matd_rowCopy);
	Matd_rowCopy(1, ':') = Matd(1, ':');
	tmat::print(Matd_rowCopy); printf("\n");
	
	printf("■ copy col\n");printf("\n");
	sstd::tmat<double> Matd_colCopy(5, 3); tmat::zeros(Matd_colCopy);
	Matd_colCopy(':', 2) = Matd(':', 2);
	tmat::print(Matd_colCopy); printf("\n");
}


int main(){

	printf("=== Hello SubStandard Library ! ===\n\n");

	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);

//	printf("== sstd_src ==\n\n"); TEST_sstd_src();

	printf("== sstd_src_MatrixStore_tmat ==\n\n"); TEST_tmat();
	
	printf("■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem);

	

	return 0;
}
