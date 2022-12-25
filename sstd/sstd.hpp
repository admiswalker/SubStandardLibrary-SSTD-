#pragma once

// todo:
//   - sstdf::file, fp; sstd::fopen, sstd::fread, sstd::write, 
//     C言語関数辞典: stdio.h (http://www.c-tipsref.com/reference/stdio.html) を参考に実装するとよい．
//   - loadImg(); tiff (lzw, jpg), gif, png, jpg, bmp あたりに対応できるとよいのでは>?
//   - loadWave(); wave. (mp3 は，後回しでよいだろう・・・)
//   - zip の展開・圧縮
//   - std::move, std::swap() における動作確認．(tmat, tmat_r, bmat)

//#include "./src/FileReader.hpp"
//#include "./src/FileWriter.hpp"
//#include "./src/LineFeedCode.h"

// C:\Users\username\Documents\Visual Studio 2015\Projects\FileNameTranslator_Ver00.00_00\FileNameTranslator_Ver00.00_00
// の main.cpp 内の文字列比較関数．

// 以下は恐らく，Cygwin ではなく，ネイティブの環境が必要．(thread 等の問題)
// makeConnection // win32 and linux
// sendMail
// serial communication interface // win and linux
// getTimeOfSNTP

// save/load as a wave
// save/load as a bitmap, tiff, jpg, png
// tiff, png 画像の読み込み (lzw 圧縮のみに対応予定？)

// 数値計算系の関数 (スプライン補完等)

#include "src/cast/typeConversion.hpp"

#include "src/container/matrixContainer_binary/bmat.hpp"
#include "src/container/vector/slice.hpp"
#include "src/container/vector/stdVector_expansion.hpp"
#include "src/container/vector/typeDef.hpp"
#include "src/container/vector/vvec.hpp"

#include "src/definitions/itr.hpp"
#include "src/definitions/typeDef.h"
#include "src/definitions/typeNum.hpp"

#include "src/file/cp.hpp"
#include "src/file/csv.hpp"
#include "src/file/file.hpp"
#include "src/file/file_c.hpp"
#include "src/file/file_operations.hpp"
#include "src/file/glob.hpp"
#include "src/file/read_write.hpp"
#include "src/file/mkdir.hpp"
#include "src/file/mv.hpp"
#include "src/file/path.hpp"
#include "src/file/read_write.hpp"
#include "src/file/rm.hpp"
#include "src/file/tinyInterpreter.hpp"

#include "src/math/hashFnc_of_MD5_SHA1_SHA2/hashSum.hpp"
#include "src/math/hashFnc_of_MD5_SHA1_SHA2/sstd_md5_sha1_sha2_wrapper.hpp"
#include "src/math/linearAlgebra/matCal.hpp"
#include "src/math/math.hpp"
#include "src/math/signal.hpp"

//#include "src/print/pdbg.hpp" // 後ろで include しないと，extern での定義を置換してしまう．
//#include "src/print/print.hpp" // 後ろで include しないと，extern での定義を置換してしまう．

#include "src/python/c2py.hpp"

#include "src/string/encode_decode.hpp"
#include "src/string/ssprintf.hpp"
#include "src/string/strEdit.hpp"
#include "src/string/strmatch.hpp"
#include "src/string/utf8.hpp"

#include "src/sys/pause.hpp"
#include "src/sys/pid.hpp"
#include "src/sys/status.hpp"
#include "src/sys/system.hpp"

#include "src/time/measureTime.hpp"
#include "src/time/time.hpp"
#include "src/time/sleep.hpp" // use_sstd_gcc4_4_7

//---

#include "src/container/matrixContainer_colMajor/mat_c.hpp" // Because of this header use "pdbg.hpp", we need to define after namespace sstd{}.
#include "src/container/matrixContainer_rowMajor/mat_r.hpp" // Because of this header use "pdbg.hpp", we need to define after namespace sstd{}.

#include "src/print/pdbg.hpp"                     // In order to avoid conflict of "pdbg.hpp", we need to define after namespace sstd{}.
#include "src/print/print.hpp"                    // In order to avoid conflict of "print.hpp", we need to define after namespace sstd{}.

#include "compileOption.hpp"
#ifndef use_sstd_pdbg
    #undef pdbg
    #undef pdbg_if
    #undef pdbg_if_exit
    #undef pdbg_if_stop_exit
    #undef  dbg
    #undef ndbg
    #undef pdbg_alway
    #undef pdbg_always_stop_exit
#endif
#ifndef use_sstd_printn
    #undef printn
    #undef printn_all
    #undef printn_c
    #undef printn_all_c
#endif

