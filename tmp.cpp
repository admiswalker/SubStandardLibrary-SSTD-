
std::vector<struct sstd_c2py::typeSet> sstd_c2py::format_str2typeSet(const std::vector<std::string>& fSList){
	std::vector<struct sstd_c2py::typeSet> fList(fSList.size());
	std::string type, tempT;
	for(uint i=0; i<fList.size(); i++){
		std::string fS = fSList[i];
		const struct sstd_c2py::typeSet& fmt = fList[i];
		split_const       (fmt, fS); // "const type*|*~" -> "const", "type*|*~"
		split_ret         (fmt, fS); //   "ret type*|*~" ->   "ret", "type*|*~"
		split_verticalLine(fmt, fS); //                              "type*|*~" -> "type*", "*~"           // vartical line is just a splitting symbol
		split_pointer     (fmt, fS); //                                            "type*" -> "type",  "*" // setting "true" or "false" of pointer
		if      (sstd::strcmp(fS,  "void")){ fmt.name=  "void"; fmt.N_num=num_void  ; fmt.case_num=fmt.N_num; if(fmt.pointer){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS,   "len")){ fmt.name=   "len"; fmt.N_num=num_len   ; fmt.case_num=fmt.N_num; if(!IsPrevious_pointer(fSList, fList, i)){ sstd::pdbg("ERROR: \"%s\": Previous of a len type must be a pointer type without \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS,  "bool")){ fmt.name=  "bool"; fmt.N_num=num_bool  ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,  "char")){ fmt.name=  "char"; fmt.N_num=num_char  ; fmt.case_num=fmt.N_num; if(fmt.pointer&& IsNext_Len(fSList, fList, i)){ sstd::pdbg("ERROR: \"%s\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else if(sstd::strcmp(fS, "uchar")){ fmt.name= "uchar"; fmt.N_num=num_uchar ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,   "int")){ fmt.name= "int32"; fmt.N_num=num_int32 ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,  "int8")){ fmt.name=  "int8"; fmt.N_num=num_int8  ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS, "int16")){ fmt.name= "int16"; fmt.N_num=num_int16 ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS, "int32")){ fmt.name= "int32"; fmt.N_num=num_int32 ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS, "int64")){ fmt.name= "int64"; fmt.N_num=num_int64 ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS, "uint8")){ fmt.name= "uint8"; fmt.N_num=num_uint8 ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,"uint16")){ fmt.name="uint16"; fmt.N_num=num_uint16; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,"uint32")){ fmt.name="uint32"; fmt.N_num=num_uint32; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,"uint64")){ fmt.name="uint64"; fmt.N_num=num_uint64; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS, "float")){ fmt.name= "float"; fmt.N_num=num_float ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,"double")){ fmt.name="double"; fmt.N_num=num_double; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,"string")){ fmt.name=   "str"; fmt.N_num=num_str   ; fmt.case_num=fmt.N_num;
		}else if(sstd::strcmp(fS,   "str")){ fmt.name=   "str"; fmt.N_num=num_str   ; fmt.case_num=fmt.N_num;
		}else if(Is_type_tempT(fS, type, tempT)){
			// Example: fS=="vec<double>"
			//  - type =="vec"
			//  - tempT=="double"
			if      (sstd::strcmp(type,  "vec")){ fmt.name=  "vec"; fmt.N_num=  VEC_NUM_BASE; fmt.case_num=fmt.N_num+  VEC_NUM_BASE; if(!setTandT_num(fmt, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type, "vvec")){ fmt.name= "vvec"; fmt.N_num= VVEC_NUM_BASE; fmt.case_num=fmt.N_num+ VVEC_NUM_BASE; if(!setTandT_num(fmt, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type,"mat_c")){ fmt.name="mat_c"; fmt.N_num=MAT_C_NUM_BASE; fmt.case_num=fmt.N_num+MAT_C_NUM_BASE; if(!setTandT_num(fmt, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else if(sstd::strcmp(type,"mat_r")){ fmt.name="mat_r"; fmt.N_num=MAT_R_NUM_BASE; fmt.case_num=fmt.N_num+MAT_R_NUM_BASE; if(!setTandT_num(fmt, tempT)){ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); return std::vector<struct sstd_c2py::typeSet>(0); }
		}else{
			if(fSList[i].size()==0){ sstd::pdbg("ERROR: There is a empty token. (There might be invalid \",\".)\n");
			}else{ sstd::pdbg("ERROR: \"%s\" is an unsupported type.\n", fSList[i].c_str()); }
			return std::vector<struct sstd_c2py::typeSet>(0);
		}
		fmt.case_num += fmt.T_num;
	}
	return fList;
}


