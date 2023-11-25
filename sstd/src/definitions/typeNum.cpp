#include "typeNum.hpp"


uchar sstd::type2num(              bool rhs){ return sstd::num_bool;   }
uchar sstd::type2num(              char rhs){ return sstd::num_char;   }
//uchar sstd::type2num(             uchar rhs){ return sstd::num_uchar;  }// same as uint8
uchar sstd::type2num(              int8 rhs){ return sstd::num_int8;   }
uchar sstd::type2num(             int16 rhs){ return sstd::num_int16;  }
uchar sstd::type2num(             int32 rhs){ return sstd::num_int32;  }
uchar sstd::type2num(             int64 rhs){ return sstd::num_int64;  }
uchar sstd::type2num(             uint8 rhs){ return sstd::num_uint8;  }
uchar sstd::type2num(            uint16 rhs){ return sstd::num_uint16; }
uchar sstd::type2num(            uint32 rhs){ return sstd::num_uint32; }
uchar sstd::type2num(            uint64 rhs){ return sstd::num_uint64; }
uchar sstd::type2num(             float rhs){ return sstd::num_float;  }
uchar sstd::type2num(            double rhs){ return sstd::num_double; }
uchar sstd::type2num(const std::string& rhs){ return sstd::num_str;    }

uchar sstd::type2num(const std::vector<       bool>& rhs){ return sstd::num_vec_bool;   }
uchar sstd::type2num(const std::vector<       char>& rhs){ return sstd::num_vec_char;   }
//uchar sstd::type2num(const std::vector<      uchar>& rhs){ return sstd::num_vec_uchar;  }// same as uint8
uchar sstd::type2num(const std::vector<       int8>& rhs){ return sstd::num_vec_int8;   }
uchar sstd::type2num(const std::vector<      int16>& rhs){ return sstd::num_vec_int16;  }
uchar sstd::type2num(const std::vector<      int32>& rhs){ return sstd::num_vec_int32;  }
uchar sstd::type2num(const std::vector<      int64>& rhs){ return sstd::num_vec_int64;  }
uchar sstd::type2num(const std::vector<      uint8>& rhs){ return sstd::num_vec_uint8;  }
uchar sstd::type2num(const std::vector<     uint16>& rhs){ return sstd::num_vec_uint16; }
uchar sstd::type2num(const std::vector<     uint32>& rhs){ return sstd::num_vec_uint32; }
uchar sstd::type2num(const std::vector<     uint64>& rhs){ return sstd::num_vec_uint64; }
uchar sstd::type2num(const std::vector<      float>& rhs){ return sstd::num_vec_float;  }
uchar sstd::type2num(const std::vector<     double>& rhs){ return sstd::num_vec_double; }
uchar sstd::type2num(const std::vector<std::string>& rhs){ return sstd::num_vec_str;    }

uchar sstd::type2num(const std::vector<std::vector<       bool>>& rhs){ return sstd::num_vvec_bool;   }
uchar sstd::type2num(const std::vector<std::vector<       char>>& rhs){ return sstd::num_vvec_char;   }
//uchar sstd::type2num(const std::vector<std::vector<      uchar>>& rhs){ return sstd::num_vvec_uchar;  }// same as uint8
uchar sstd::type2num(const std::vector<std::vector<       int8>>& rhs){ return sstd::num_vvec_int8;   }
uchar sstd::type2num(const std::vector<std::vector<      int16>>& rhs){ return sstd::num_vvec_int16;  }
uchar sstd::type2num(const std::vector<std::vector<      int32>>& rhs){ return sstd::num_vvec_int32;  }
uchar sstd::type2num(const std::vector<std::vector<      int64>>& rhs){ return sstd::num_vvec_int64;  }
uchar sstd::type2num(const std::vector<std::vector<      uint8>>& rhs){ return sstd::num_vvec_uint8;  }
uchar sstd::type2num(const std::vector<std::vector<     uint16>>& rhs){ return sstd::num_vvec_uint16; }
uchar sstd::type2num(const std::vector<std::vector<     uint32>>& rhs){ return sstd::num_vvec_uint32; }
uchar sstd::type2num(const std::vector<std::vector<     uint64>>& rhs){ return sstd::num_vvec_uint64; }
uchar sstd::type2num(const std::vector<std::vector<      float>>& rhs){ return sstd::num_vvec_float;  }
uchar sstd::type2num(const std::vector<std::vector<     double>>& rhs){ return sstd::num_vvec_double; }
uchar sstd::type2num(const std::vector<std::vector<std::string>>& rhs){ return sstd::num_vvec_str;    }

uchar sstd::type2num(const sstd::mat_c<       bool>& rhs){ return sstd::num_mat_c_bool;   }
uchar sstd::type2num(const sstd::mat_c<       char>& rhs){ return sstd::num_mat_c_char;   }
//uchar sstd::type2num(const sstd::mat_c<      uchar>& rhs){ return sstd::num_mat_c_uchar;  }// same as uint8
uchar sstd::type2num(const sstd::mat_c<       int8>& rhs){ return sstd::num_mat_c_int8;   }
uchar sstd::type2num(const sstd::mat_c<      int16>& rhs){ return sstd::num_mat_c_int16;  }
uchar sstd::type2num(const sstd::mat_c<      int32>& rhs){ return sstd::num_mat_c_int32;  }
uchar sstd::type2num(const sstd::mat_c<      int64>& rhs){ return sstd::num_mat_c_int64;  }
uchar sstd::type2num(const sstd::mat_c<      uint8>& rhs){ return sstd::num_mat_c_uint8;  }
uchar sstd::type2num(const sstd::mat_c<     uint16>& rhs){ return sstd::num_mat_c_uint16; }
uchar sstd::type2num(const sstd::mat_c<     uint32>& rhs){ return sstd::num_mat_c_uint32; }
uchar sstd::type2num(const sstd::mat_c<     uint64>& rhs){ return sstd::num_mat_c_uint64; }
uchar sstd::type2num(const sstd::mat_c<      float>& rhs){ return sstd::num_mat_c_float;  }
uchar sstd::type2num(const sstd::mat_c<     double>& rhs){ return sstd::num_mat_c_double; }
uchar sstd::type2num(const sstd::mat_c<std::string>& rhs){ return sstd::num_mat_c_str;    }

uchar sstd::type2num(const sstd::mat_r<       bool>& rhs){ return sstd::num_mat_r_bool;   }
uchar sstd::type2num(const sstd::mat_r<       char>& rhs){ return sstd::num_mat_r_char;   }
//uchar sstd::type2num(const sstd::mat_r<      uchar>& rhs){ return sstd::num_mat_r_uchar;  }// same as uint8
uchar sstd::type2num(const sstd::mat_r<       int8>& rhs){ return sstd::num_mat_r_int8;   }
uchar sstd::type2num(const sstd::mat_r<      int16>& rhs){ return sstd::num_mat_r_int16;  }
uchar sstd::type2num(const sstd::mat_r<      int32>& rhs){ return sstd::num_mat_r_int32;  }
uchar sstd::type2num(const sstd::mat_r<      int64>& rhs){ return sstd::num_mat_r_int64;  }
uchar sstd::type2num(const sstd::mat_r<      uint8>& rhs){ return sstd::num_mat_r_uint8;  }
uchar sstd::type2num(const sstd::mat_r<     uint16>& rhs){ return sstd::num_mat_r_uint16; }
uchar sstd::type2num(const sstd::mat_r<     uint32>& rhs){ return sstd::num_mat_r_uint32; }
uchar sstd::type2num(const sstd::mat_r<     uint64>& rhs){ return sstd::num_mat_r_uint64; }
uchar sstd::type2num(const sstd::mat_r<      float>& rhs){ return sstd::num_mat_r_float;  }
uchar sstd::type2num(const sstd::mat_r<     double>& rhs){ return sstd::num_mat_r_double; }
uchar sstd::type2num(const sstd::mat_r<std::string>& rhs){ return sstd::num_mat_r_str;    }

uchar sstd::type2num(const std::unordered_map<std::string,       bool>& rhs){ return sstd::num_hash_str_bool;   }
uchar sstd::type2num(const std::unordered_map<std::string,       char>& rhs){ return sstd::num_hash_str_char;   }
//uchar sstd::type2num(const std::unordered_map<std::string,      uchar>& rhs){ return sstd::num_hash_str_uchar;  }// same as uint8
uchar sstd::type2num(const std::unordered_map<std::string,       int8>& rhs){ return sstd::num_hash_str_int8;   }
uchar sstd::type2num(const std::unordered_map<std::string,      int16>& rhs){ return sstd::num_hash_str_int16;  }
uchar sstd::type2num(const std::unordered_map<std::string,      int32>& rhs){ return sstd::num_hash_str_int32;  }
uchar sstd::type2num(const std::unordered_map<std::string,      int64>& rhs){ return sstd::num_hash_str_int64;  }
uchar sstd::type2num(const std::unordered_map<std::string,      uint8>& rhs){ return sstd::num_hash_str_uint8;  }
uchar sstd::type2num(const std::unordered_map<std::string,     uint16>& rhs){ return sstd::num_hash_str_uint16; }
uchar sstd::type2num(const std::unordered_map<std::string,     uint32>& rhs){ return sstd::num_hash_str_uint32; }
uchar sstd::type2num(const std::unordered_map<std::string,     uint64>& rhs){ return sstd::num_hash_str_uint64; }
uchar sstd::type2num(const std::unordered_map<std::string,      float>& rhs){ return sstd::num_hash_str_float;  }
uchar sstd::type2num(const std::unordered_map<std::string,     double>& rhs){ return sstd::num_hash_str_double; }
uchar sstd::type2num(const std::unordered_map<std::string,std::string>& rhs){ return sstd::num_hash_str_str;    }

uchar sstd::type2num(const sstd::void_ptr                          & rhs){ return sstd::num_void_ptr;       }
uchar sstd::type2num(const             std::vector<sstd::void_ptr> & rhs){ return sstd::num_vec_void_ptr;   }
uchar sstd::type2num(const std::vector<std::vector<sstd::void_ptr>>& rhs){ return sstd::num_vvec_void_ptr;  }
uchar sstd::type2num(const sstd::mat_c<sstd::void_ptr>             & rhs){ return sstd::num_mat_c_void_ptr; }
uchar sstd::type2num(const sstd::mat_r<sstd::void_ptr>             & rhs){ return sstd::num_mat_r_void_ptr; }

uchar sstd::type2num(const std::unordered_map<std::string,    sstd::void_ptr>& rhs){ return sstd::num_hash_str_void_ptr;      }
//uchar sstd::type2num(const std::unordered_map<sstd::void_ptr, sstd::void_ptr>& rhs){ return sstd::num_hash_void_ptr_void_ptr; }

std::string sstd::typeNum2str(uchar rhs){

    switch(rhs){
    case sstd::num_void: return std::string("void");
    case sstd::num_len:  return std::string("len" );
    case sstd::num_err:  return std::string("err" );
    case sstd::num_null: return std::string("null");
        
    case sstd::num_bool:   return std::string("bool"  );
    case sstd::num_char:   return std::string("char"  );
    case sstd::num_uchar:  return std::string("uchar" );
    case sstd::num_int8:   return std::string("int8"  );
    case sstd::num_int16:  return std::string("int16" );
    case sstd::num_int32:  return std::string("int32" );
    case sstd::num_int64:  return std::string("int64" );
    case sstd::num_uint8:  return std::string("uint8" );
    case sstd::num_uint16: return std::string("uint16");
    case sstd::num_uint32: return std::string("uint32");
    case sstd::num_uint64: return std::string("uint64");
    case sstd::num_float:  return std::string( "float");
    case sstd::num_double: return std::string("double");
    case sstd::num_str:    return std::string("str"   );
        
    case sstd::num_vec_bool:   return std::string("vec_bool"  );
    case sstd::num_vec_char:   return std::string("vec_char"  );
    case sstd::num_vec_uchar:  return std::string("vec_uchar" );
    case sstd::num_vec_int8:   return std::string("vec_int8"  );
    case sstd::num_vec_int16:  return std::string("vec_int16" );
    case sstd::num_vec_int32:  return std::string("vec_int32" );
    case sstd::num_vec_int64:  return std::string("vec_int64" );
    case sstd::num_vec_uint8:  return std::string("vec_uint8" );
    case sstd::num_vec_uint16: return std::string("vec_uint16");
    case sstd::num_vec_uint32: return std::string("vec_uint32");
    case sstd::num_vec_uint64: return std::string("vec_uint64");
    case sstd::num_vec_float:  return std::string("vec_float" );
    case sstd::num_vec_double: return std::string("vec_double");
    case sstd::num_vec_str:    return std::string("vec_str"   );
        
    case sstd::num_vvec_bool:   return std::string("vvec_bool"  );
    case sstd::num_vvec_char:   return std::string("vvec_char"  );
    case sstd::num_vvec_uchar:  return std::string("vvec_uchar" );
    case sstd::num_vvec_int8:   return std::string("vvec_int8"  );
    case sstd::num_vvec_int16:  return std::string("vvec_int16" );
    case sstd::num_vvec_int32:  return std::string("vvec_int32" );
    case sstd::num_vvec_int64:  return std::string("vvec_int64" );
    case sstd::num_vvec_uint8:  return std::string("vvec_uint8" );
    case sstd::num_vvec_uint16: return std::string("vvec_uint16");
    case sstd::num_vvec_uint32: return std::string("vvec_uint32");
    case sstd::num_vvec_uint64: return std::string("vvec_uint64");
    case sstd::num_vvec_float:  return std::string("vvec_float" );
    case sstd::num_vvec_double: return std::string("vvec_double");
    case sstd::num_vvec_str:    return std::string("vvec_str"   );
        
    case sstd::num_mat_c_bool:   return std::string("mat_c_bool"  );
    case sstd::num_mat_c_char:   return std::string("mat_c_char"  );
    case sstd::num_mat_c_uchar:  return std::string("mat_c_uchar" );
    case sstd::num_mat_c_int8:   return std::string("mat_c_int8"  );
    case sstd::num_mat_c_int16:  return std::string("mat_c_int16" );
    case sstd::num_mat_c_int32:  return std::string("mat_c_int32" );
    case sstd::num_mat_c_int64:  return std::string("mat_c_int64" );
    case sstd::num_mat_c_uint8:  return std::string("mat_c_uint8" );
    case sstd::num_mat_c_uint16: return std::string("mat_c_uint16");
    case sstd::num_mat_c_uint32: return std::string("mat_c_uint32");
    case sstd::num_mat_c_uint64: return std::string("mat_c_uint64");
    case sstd::num_mat_c_float:  return std::string("mat_c_float" );
    case sstd::num_mat_c_double: return std::string("mat_c_double");
    case sstd::num_mat_c_str:    return std::string("mat_c_str"   );
        
    case sstd::num_mat_r_bool:   return std::string("mat_r_bool"  );
    case sstd::num_mat_r_char:   return std::string("mat_r_char"  );
    case sstd::num_mat_r_uchar:  return std::string("mat_r_uchar" );
    case sstd::num_mat_r_int8:   return std::string("mat_r_int8"  );
    case sstd::num_mat_r_int16:  return std::string("mat_r_int16" );
    case sstd::num_mat_r_int32:  return std::string("mat_r_int32" );
    case sstd::num_mat_r_int64:  return std::string("mat_r_int64" );
    case sstd::num_mat_r_uint8:  return std::string("mat_r_uint8" );
    case sstd::num_mat_r_uint16: return std::string("mat_r_uint16");
    case sstd::num_mat_r_uint32: return std::string("mat_r_uint32");
    case sstd::num_mat_r_uint64: return std::string("mat_r_uint64");
    case sstd::num_mat_r_float:  return std::string("mat_r_float" );
    case sstd::num_mat_r_double: return std::string("mat_r_double");
    case sstd::num_mat_r_str:    return std::string("mat_r_str"   );
        
    case sstd::num_vmat_c_bool:   return std::string("vmat_c_bool"  );
    case sstd::num_vmat_c_char:   return std::string("vmat_c_char"  );
    case sstd::num_vmat_c_uchar:  return std::string("vmat_c_uchar" );
    case sstd::num_vmat_c_int8:   return std::string("vmat_c_int8"  );
    case sstd::num_vmat_c_int16:  return std::string("vmat_c_int16" );
    case sstd::num_vmat_c_int32:  return std::string("vmat_c_int32" );
    case sstd::num_vmat_c_int64:  return std::string("vmat_c_int64" );
    case sstd::num_vmat_c_uint8:  return std::string("vmat_c_uint8" );
    case sstd::num_vmat_c_uint16: return std::string("vmat_c_uint16");
    case sstd::num_vmat_c_uint32: return std::string("vmat_c_uint32");
    case sstd::num_vmat_c_uint64: return std::string("vmat_c_uint64");
    case sstd::num_vmat_c_float:  return std::string("vmat_c_float" );
    case sstd::num_vmat_c_double: return std::string("vmat_c_double");
    case sstd::num_vmat_c_str:    return std::string("vmat_c_str"   );
        
    case sstd::num_vmat_r_bool:   return std::string("vmat_r_bool"  );
    case sstd::num_vmat_r_char:   return std::string("vmat_r_char"  );
    case sstd::num_vmat_r_uchar:  return std::string("vmat_r_uchar" );
    case sstd::num_vmat_r_int8:   return std::string("vmat_r_int8"  );
    case sstd::num_vmat_r_int16:  return std::string("vmat_r_int16" );
    case sstd::num_vmat_r_int32:  return std::string("vmat_r_int32" );
    case sstd::num_vmat_r_int64:  return std::string("vmat_r_int64" );
    case sstd::num_vmat_r_uint8:  return std::string("vmat_r_uint8" );
    case sstd::num_vmat_r_uint16: return std::string("vmat_r_uint16");
    case sstd::num_vmat_r_uint32: return std::string("vmat_r_uint32");
    case sstd::num_vmat_r_uint64: return std::string("vmat_r_uint64");
    case sstd::num_vmat_r_float:  return std::string("vmat_r_float" );
    case sstd::num_vmat_r_double: return std::string("vmat_r_double");
    case sstd::num_vmat_r_str:    return std::string("vmat_r_str"   );
        
    case sstd::num_hash_str_bool:   return std::string("hash_str_bool"  );
    case sstd::num_hash_str_char:   return std::string("hash_str_char"  );
    case sstd::num_hash_str_uchar:  return std::string("hash_str_uchar" );
    case sstd::num_hash_str_int8:   return std::string("hash_str_int8"  );
    case sstd::num_hash_str_int16:  return std::string("hash_str_int16" );
    case sstd::num_hash_str_int32:  return std::string("hash_str_int32" );
    case sstd::num_hash_str_int64:  return std::string("hash_str_int64" );
    case sstd::num_hash_str_uint8:  return std::string("hash_str_uint8" );
    case sstd::num_hash_str_uint16: return std::string("hash_str_uint16");
    case sstd::num_hash_str_uint32: return std::string("hash_str_uint32");
    case sstd::num_hash_str_uint64: return std::string("hash_str_uint64");
    case sstd::num_hash_str_float:  return std::string("hash_str_float" );
    case sstd::num_hash_str_double: return std::string("hash_str_double");
    case sstd::num_hash_str_str:    return std::string("hash_str_str"   );
        
    case sstd::num_void_ptr:       return std::string("void_ptr"      );
    case sstd::num_vec_void_ptr:   return std::string("vec_void_ptr"  );
    case sstd::num_vvec_void_ptr:  return std::string("vvec_void_ptr" );
    case sstd::num_mat_c_void_ptr: return std::string("mat_c_void_ptr");
    case sstd::num_mat_r_void_ptr: return std::string("mat_r_void_ptr");
        
    case sstd::num_hash_str_void_ptr:      return std::string("hash_str_void_ptr"     );
    //case sstd::num_hash_void_ptr_void_ptr: return std::string("hash_void_ptr_void_ptr");
        
    case sstd::num_vec_terp_var_v2:  return std::string("vec_terp_var_v2" );
    case sstd::num_hash_terp_var_v2: return std::string("hash_terp_var_v2");
        
    default: return std::string("err");
    }
    
    return "";
}
