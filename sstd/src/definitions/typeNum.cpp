#include "typeNum.hpp"


uchar sstd::type2num(       bool rhs){ return sstd::num_bool;   }
uchar sstd::type2num(       char rhs){ return sstd::num_char;   }
//uchar sstd::type2num(      uchar rhs){ return sstd::num_uchar;  }// same as uint8
uchar sstd::type2num(       int8 rhs){ return sstd::num_int8;   }
uchar sstd::type2num(      int16 rhs){ return sstd::num_int16;  }
uchar sstd::type2num(      int32 rhs){ return sstd::num_int32;  }
uchar sstd::type2num(      int64 rhs){ return sstd::num_int64;  }
uchar sstd::type2num(      uint8 rhs){ return sstd::num_uint8;  }
uchar sstd::type2num(     uint16 rhs){ return sstd::num_uint16; }
uchar sstd::type2num(     uint32 rhs){ return sstd::num_uint32; }
uchar sstd::type2num(     uint64 rhs){ return sstd::num_uint64; }
uchar sstd::type2num(      float rhs){ return sstd::num_float;  }
uchar sstd::type2num(     double rhs){ return sstd::num_double; }
uchar sstd::type2num(std::string rhs){ return sstd::num_str;    }

uchar sstd::type2num(std::vector<       bool> rhs){ return sstd::num_vec_bool;   }
uchar sstd::type2num(std::vector<       char> rhs){ return sstd::num_vec_char;   }
//uchar sstd::type2num(std::vector<      uchar> rhs){ return sstd::num_vec_uchar;  }// same as uint8
uchar sstd::type2num(std::vector<       int8> rhs){ return sstd::num_vec_int8;   }
uchar sstd::type2num(std::vector<      int16> rhs){ return sstd::num_vec_int16;  }
uchar sstd::type2num(std::vector<      int32> rhs){ return sstd::num_vec_int32;  }
uchar sstd::type2num(std::vector<      int64> rhs){ return sstd::num_vec_int64;  }
uchar sstd::type2num(std::vector<      uint8> rhs){ return sstd::num_vec_uint8;  }
uchar sstd::type2num(std::vector<     uint16> rhs){ return sstd::num_vec_uint16; }
uchar sstd::type2num(std::vector<     uint32> rhs){ return sstd::num_vec_uint32; }
uchar sstd::type2num(std::vector<     uint64> rhs){ return sstd::num_vec_uint64; }
uchar sstd::type2num(std::vector<      float> rhs){ return sstd::num_vec_float;  }
uchar sstd::type2num(std::vector<     double> rhs){ return sstd::num_vec_double; }
uchar sstd::type2num(std::vector<std::string> rhs){ return sstd::num_vec_str;    }

