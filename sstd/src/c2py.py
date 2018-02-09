import os
import sys
import importlib
import numpy as np

#--------------------------------------------------------------------------------------------------------

import inspect

def location():
    frame = inspect.currentframe().f_back
    return ("Line: %d, File: %s, Function: %s" % (frame.f_lineno, os.path.basename(frame.f_code.co_filename), frame.f_code.co_name))

#--------------------------------------------------------------------------------------------------------

def readSplitLine(readPath):
    fp = fopen(readPath, "rb")
    lines = (fp.read()).split('\n')
    fp.close()
    return lines

#--------------------------------------------------------------------------------------------------------

# typeSet struct
class typeSet:
    def __init__(self):
        self.name    = "x"    # void, int, vec<T>... and so on.
        self.T       = "x"    # template<typename "T"> or ""
        self.pointer = False  # *
        self.ref     = False  # &
        self.arrLen  = []     # array length

def c2bool(rhs):
    if   rhs=='T': return True
    elif rhs=='F': return False
    else: print("ERROR: %s" % location()); return False

def fopen(readPath, option):
    try:
        fp = open(readPath, option)
    except IOError:
        print("ERROR: %s can not be opened.\n" % readPath)
        exit(0)
    return fp
def read_typeList(readPath):
    lines=readSplitLine(readPath)

    argList=[]
    for line in lines:
        s_line = line.split()
        buf = typeSet()
        buf.constTF = c2bool(s_line[0])
        buf.name    =        s_line[1]
        buf.T       =        s_line[2]
        buf.pointer = c2bool(s_line[3])
        buf.ref     = c2bool(s_line[4])
        lenOfarrLen =    int(s_line[5])
        for i in range(lenOfarrLen):
            buf.arrLen.append(int(s_line[6+i]))
        argList.append(buf)
    return argList

#--------------------------------------------------------------------------------------------------------

def IsBuiltin(rhs): return type(rhs).__module__==__builtins__.__name__
def IsNumpy  (rhs): return type(rhs).__module__==np.__name__

#--------------------------------------------------------------------------------------------------------

# このあたりのコード，どう考えても同じなので，関数化して・・・

def read_bool   (readPath): return read_int32 (readPath).astype(np.bool   )
def read_int8   (readPath): return read_int32 (readPath).astype(np.int8   )
def read_int16  (readPath): return read_int32 (readPath).astype(np.int16  )
def read_int32  (readPath):         fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(  'int32'), 1        ); fp.close(); return ret
def read_int64  (readPath):         fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(  'int64'), 1        ); fp.close(); return ret
def read_uint8  (readPath): return read_uint32(readPath).astype(np.uint8  )
def read_uint16 (readPath): return read_uint32(readPath).astype(np.uint16 )
def read_uint32 (readPath):         fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype( 'uint32'), 1        ); fp.close(); return ret
def read_uint64 (readPath):         fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype( 'uint64'), 1        ); fp.close(); return ret
def read_float  (readPath): return read_double(readPath).astype(np.float32)
def read_double (readPath):         fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype('float64'), 1        ); fp.close(); return ret

def read_pBool  (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(   'bool'), arrLen[0]); fp.close(); return ret
def read_pChar  (readPath, arrLen): fp=fopen(readPath, "rb"); ret= fp.read(arrLen[0]);                              fp.close(); return ret
def read_pInt8  (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(   'int8'), arrLen[0]); fp.close(); return ret
def read_pInt16 (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(  'int16'), arrLen[0]); fp.close(); return ret
def read_pInt32 (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(  'int32'), arrLen[0]); fp.close(); return ret
def read_pInt64 (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(  'int64'), arrLen[0]); fp.close(); return ret
def read_pUint8 (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype(  'uint8'), arrLen[0]); fp.close(); return ret
def read_pUint16(readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype( 'uint16'), arrLen[0]); fp.close(); return ret
def read_pUint32(readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype( 'uint32'), arrLen[0]); fp.close(); return ret
def read_pUint64(readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype( 'uint64'), arrLen[0]); fp.close(); return ret
def read_pFloat (readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype('float32'), arrLen[0]); fp.close(); return ret
def read_pDouble(readPath, arrLen): fp=fopen(readPath, "rb"); ret= np.fromfile(fp, np.dtype('float64'), arrLen[0]); fp.close(); return ret

def read_vecChar(readPath):
    fp=fopen(readPath, "rb");
    charBuf=fp.read();
    vecChar=['' for i in range(len(charBuf))]
    for i in range(len(charBuf)):
        vecChar[i] = charBuf[i]
    return vecChar
def read_vecStr(readPath, arrLen):
    fp=fopen(readPath, "rb");
    strBuf=fp.read();
    s=0
    vecStr=[[] for v in range(len(arrLen))]
    for v in range(len(arrLen)):
        vecStr[v] = strBuf[s : s + arrLen[v]]
        s += arrLen[v]
    return vecStr
def read_vec(readPath, arrLen, vecType):
    fp=fopen(readPath, "rb")
    ret= np.fromfile(fp, np.dtype(vecType), arrLen[0])
    fp.close()
    return ret

def read_matChar(readPath, arrLen):
    fp=fopen(readPath, "rb");
    charBuf=fp.read();
    matChar=[[' ' for i in range(arrLen[1])] for i in range(arrLen[0])]
    for q in range(arrLen[1]):
        for p in range(arrLen[0]):
            matChar[p][q] = charBuf[p+arrLen[0]*q]
    return matChar
def read_mat(readPath, arrLen, matType):
    fp=fopen(readPath, "rb")
    ret=(np.fromfile(fp, np.dtype(matType), arrLen[0]*arrLen[1])).reshape(arrLen[1], arrLen[0])
    fp.close()
    return ret.flatten('F').reshape(arrLen[0], arrLen[1]) # numpy は行優先のため，列優先の行列を受け取った場合は，このように転置が発生する．

def read_mat_rChar(readPath, arrLen):
    fp=fopen(readPath, "rb");
    charBuf=fp.read();
    mat_rChar=[[' ' for i in range(arrLen[1])] for i in range(arrLen[0])]
    for p in range(arrLen[0]):
        for q in range(arrLen[1]):
            mat_rChar[p][q] = charBuf[arrLen[1]*p+q]
    return mat_rChar
def read_mat_r(readPath, arrLen, matType):
    fp=fopen(readPath, "rb");
    ret=(np.fromfile(fp, np.dtype(matType), arrLen[0]*arrLen[1])).reshape(arrLen[0], arrLen[1]);
    fp.close();
    return ret

#--------------------------------------------------------------------------------------------------------

def builtIn_readFile(typeList, i, readPFunc, readFunc, readPath):
    if typeList[i].pointer: return readPFunc(readPath, typeList[i].arrLen)
    else: return readFunc(readPath)
            
#--------------------------------------------------------------------------------------------------------

def cnv2correctDtype(typeList, ret):
    if   typeList[0].name==  "bool" and ret.dtype!=np.bool:    return ret.astype(np.bool   )
    elif typeList[0].name==  "char" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
    elif typeList[0].name== "uchar" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
    elif typeList[0].name==  "int8" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
    elif typeList[0].name== "uint8" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
    elif typeList[0].name== "int16" and ret.dtype!=np.int16:   return ret.astype(np.int16  )
    elif typeList[0].name=="uint16" and ret.dtype!=np.uint16:  return ret.astype(np.uint16 )
    elif typeList[0].name== "int32" and ret.dtype!=np.int32:   return ret.astype(np.int32  )
    elif typeList[0].name=="uint32" and ret.dtype!=np.uint32:  return ret.astype(np.uint32 )
    elif typeList[0].name== "int64" and ret.dtype!=np.int64:   return ret.astype(np.int64  )
    elif typeList[0].name=="uint64" and ret.dtype!=np.uint64:  return ret.astype(np.uint64 )
    elif typeList[0].name== "float" and ret.dtype!=np.float32: return ret.astype(np.float32)
    elif typeList[0].name=="double" and ret.dtype!=np.float64: return ret.astype(np.float64)
    elif typeList[0].name=="vec" or typeList[0].name=="mat" or typeList[0].name=="mat_r":
        if   typeList[0].T==  "bool" and ret.dtype!=np.bool:    return ret.astype(np.bool   )
        elif typeList[0].T==  "char" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
        elif typeList[0].T== "uchar" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
        elif typeList[0].T==  "int8" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
        elif typeList[0].T== "uint8" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
        elif typeList[0].T== "int16" and ret.dtype!=np.int16:   return ret.astype(np.int16  )
        elif typeList[0].T=="uint16" and ret.dtype!=np.uint16:  return ret.astype(np.uint16 )
        elif typeList[0].T== "int32" and ret.dtype!=np.int32:   return ret.astype(np.int32  )
        elif typeList[0].T=="uint32" and ret.dtype!=np.uint32:  return ret.astype(np.uint32 )
        elif typeList[0].T== "int64" and ret.dtype!=np.int64:   return ret.astype(np.int64  )
        elif typeList[0].T=="uint64" and ret.dtype!=np.uint64:  return ret.astype(np.uint64 )
        elif typeList[0].T== "float" and ret.dtype!=np.float32: return ret.astype(np.float32)
        elif typeList[0].T=="double" and ret.dtype!=np.float64: return ret.astype(np.float64)
        else: return ret
    else: return ret
            
#--------------------------------------------------------------------------------------------------------

def matChar_serialize(rhs):
    charBuf=""
    for q in range(len(rhs[0])):
        for p in range(len(rhs)):
            charBuf+=rhs[p][q]
    return charBuf

def mat_rChar_serialize(rhs):
    charBuf=""
    for p in range(len(rhs)):
        for q in range(len(rhs[0])):
            charBuf+=rhs[p][q]
    return charBuf
    
def cnv_builtin2numpy(typeList, rhs):
    if   typeList[0].name==  "bool": return np.array(rhs, dtype =   "bool")
    elif typeList[0].name==  "char": return np.array(rhs, dtype =   "int8")
    elif typeList[0].name== "uchar": return np.array(rhs, dtype =  "uint8")
    elif typeList[0].name==  "int8": return np.array(rhs, dtype =   "int8")
    elif typeList[0].name== "int16": return np.array(rhs, dtype =  "int16")
    elif typeList[0].name== "int32": return np.array(rhs, dtype =  "int32")
    elif typeList[0].name== "int64": return np.array(rhs, dtype =  "int64")
    elif typeList[0].name== "uint8": return np.array(rhs, dtype =  "uint8")
    elif typeList[0].name=="uint16": return np.array(rhs, dtype = "uint16")
    elif typeList[0].name=="uint32": return np.array(rhs, dtype = "uint32")
    elif typeList[0].name=="uint64": return np.array(rhs, dtype = "uint64")
    elif typeList[0].name== "float": return np.array(rhs, dtype ="float32")
    elif typeList[0].name=="double": return np.array(rhs, dtype ="float64")
    elif typeList[0].name==   "str": pass # there is nothing to do (pass is for just avoid syntax error)
    elif typeList[0].name==   "vec":
        if   typeList[0].T==  "bool": return np.array(rhs, dtype =   "bool")
        elif typeList[0].T==  "char":
            # reshape to one strign array
            retBuf=""
            for i in range(len(rhs)): retBuf+=rhs[i][0]
            return retBuf
        elif typeList[0].T== "uchar": return np.array(rhs, dtype =  "uint8")
        elif typeList[0].T==  "int8": return np.array(rhs, dtype =   "int8")
        elif typeList[0].T== "int16": return np.array(rhs, dtype =  "int16")
        elif typeList[0].T== "int32": return np.array(rhs, dtype =  "int32")
        elif typeList[0].T== "int64": return np.array(rhs, dtype =  "int64")
        elif typeList[0].T== "uint8": return np.array(rhs, dtype =  "uint8")
        elif typeList[0].T=="uint16": return np.array(rhs, dtype = "uint16")
        elif typeList[0].T=="uint32": return np.array(rhs, dtype = "uint32")
        elif typeList[0].T=="uint64": return np.array(rhs, dtype = "uint64")
        elif typeList[0].T== "float": return np.array(rhs, dtype ="float32")
        elif typeList[0].T=="double": return np.array(rhs, dtype ="float64")
        elif typeList[0].T==   "str":
            # reshape to one strign array
            retBuf=""
            for i in range(len(rhs)): retBuf+=rhs[i]
            return retBuf
        else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[0].name, typeList[0].T))
    elif typeList[0].name==   "mat":
        if typeList[0].T==  "char": return matChar_serialize(rhs) # reshape to one strign array
        else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[0].name, typeList[0].T))
    elif typeList[0].name== "mat_r":
        if typeList[0].T==  "char": return mat_rChar_serialize(rhs) # reshape to one strign array
        else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[0].name, typeList[0].T))
    else: print("ERROR: %s :: \"%s\" is an unsupported type." % (location(), typeList[0].name))

#--------------------------------------------------------------------------------------------------------

def main():
    args = sys.argv
    if len(args)<=1: print("ERROR: too few args"); return
    (basePath, importFile, funcName) = (args[1], args[2], args[3])

    # return を リストの最後に変更するように．
    
    typeList = read_typeList(basePath + "/argList.bin")
    valList  = [[] for i in range(len(typeList))]
    for i in range(1, len(typeList)): # begin 1 for return value type. (passing the ret of "valList[0]".)
        readPath = basePath + ("/arg%04u.bin" % i)
        if   typeList[i].name==  "bool": valList[i]=builtIn_readFile(typeList, i, read_pBool,   read_bool,   readPath)
        elif typeList[i].name==  "char": valList[i]=builtIn_readFile(typeList, i, read_pChar,   read_int8,   readPath)
        elif typeList[i].name== "uchar": valList[i]=builtIn_readFile(typeList, i, read_pUint8,  read_uint8,  readPath)
        elif typeList[i].name==  "int8": valList[i]=builtIn_readFile(typeList, i, read_pInt8,   read_int8,   readPath)
        elif typeList[i].name== "int16": valList[i]=builtIn_readFile(typeList, i, read_pInt16,  read_int16,  readPath)
        elif typeList[i].name== "int32": valList[i]=builtIn_readFile(typeList, i, read_pInt32,  read_int32,  readPath)
        elif typeList[i].name== "int64": valList[i]=builtIn_readFile(typeList, i, read_pInt64,  read_int64,  readPath)
        elif typeList[i].name== "uint8": valList[i]=builtIn_readFile(typeList, i, read_pUint8,  read_uint8,  readPath)
        elif typeList[i].name=="uint16": valList[i]=builtIn_readFile(typeList, i, read_pUint16, read_uint16, readPath)
        elif typeList[i].name=="uint32": valList[i]=builtIn_readFile(typeList, i, read_pUint32, read_uint32, readPath)
        elif typeList[i].name=="uint64": valList[i]=builtIn_readFile(typeList, i, read_pUint64, read_uint64, readPath)
        elif typeList[i].name== "float": valList[i]=builtIn_readFile(typeList, i, read_pFloat,  read_float,  readPath)
        elif typeList[i].name=="double": valList[i]=builtIn_readFile(typeList, i, read_pDouble, read_double, readPath)
#       elif typeList[i].name==   "len": pass # len element is not used on "c2py.py" (ignored in ), so argList.bin does not have this type.
        elif typeList[i].name==   "str": valList[i]=read_pChar(readPath, typeList[i].arrLen)
        elif typeList[i].name==   "vec":
            if   typeList[i].T==  "bool": valList[i]=read_vec    (readPath, typeList[i].arrLen,    'bool') # bool is 8 bits type in numpy
            elif typeList[i].T==  "char": valList[i]=read_vecChar(readPath)
            elif typeList[i].T== "uchar": valList[i]=read_vec    (readPath, typeList[i].arrLen,   'uint8')
            elif typeList[i].T==  "int8": valList[i]=read_vec    (readPath, typeList[i].arrLen,    'int8')
            elif typeList[i].T== "int16": valList[i]=read_vec    (readPath, typeList[i].arrLen,   'int16')
            elif typeList[i].T== "int32": valList[i]=read_vec    (readPath, typeList[i].arrLen,   'int32')
            elif typeList[i].T== "int64": valList[i]=read_vec    (readPath, typeList[i].arrLen,   'int64')
            elif typeList[i].T== "uint8": valList[i]=read_vec    (readPath, typeList[i].arrLen,   'uint8')
            elif typeList[i].T=="uint16": valList[i]=read_vec    (readPath, typeList[i].arrLen,  'uint16')
            elif typeList[i].T=="uint32": valList[i]=read_vec    (readPath, typeList[i].arrLen,  'uint32')
            elif typeList[i].T=="uint64": valList[i]=read_vec    (readPath, typeList[i].arrLen,  'uint64')
            elif typeList[i].T== "float": valList[i]=read_vec    (readPath, typeList[i].arrLen, 'float32')
            elif typeList[i].T=="double": valList[i]=read_vec    (readPath, typeList[i].arrLen, 'float64')
            elif typeList[i].T==   "str": valList[i]=read_vecStr (readPath, typeList[i].arrLen)
            else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[i].name, typeList[i].T))
        elif typeList[i].name== "mat": 
            if   typeList[i].T==  "bool": valList[i]=read_mat    (readPath, typeList[i].arrLen,    'bool')
            elif typeList[i].T==  "char": valList[i]=read_matChar(readPath, typeList[i].arrLen)
            elif typeList[i].T==  "int8": valList[i]=read_mat    (readPath, typeList[i].arrLen,    'int8')
            elif typeList[i].T== "int16": valList[i]=read_mat    (readPath, typeList[i].arrLen,   'int16')
            elif typeList[i].T== "int32": valList[i]=read_mat    (readPath, typeList[i].arrLen,   'int32')
            elif typeList[i].T== "int64": valList[i]=read_mat    (readPath, typeList[i].arrLen,   'int64')
            elif typeList[i].T== "uint8": valList[i]=read_mat    (readPath, typeList[i].arrLen,   'uint8')
            elif typeList[i].T=="uint16": valList[i]=read_mat    (readPath, typeList[i].arrLen,  'uint16')
            elif typeList[i].T=="uint32": valList[i]=read_mat    (readPath, typeList[i].arrLen,  'uint32')
            elif typeList[i].T=="uint64": valList[i]=read_mat    (readPath, typeList[i].arrLen,  'uint64')
            elif typeList[i].T== "float": valList[i]=read_mat    (readPath, typeList[i].arrLen, 'float32')
            elif typeList[i].T=="double": valList[i]=read_mat    (readPath, typeList[i].arrLen, 'float64')
            else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[i].name, typeList[i].T))
        elif typeList[i].name== "mat_r":
            if   typeList[i].T==  "bool": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,    'bool')
            elif typeList[i].T==  "char": valList[i]=read_mat_rChar(readPath, typeList[i].arrLen)
            elif typeList[i].T==  "int8": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,    'int8')
            elif typeList[i].T== "int16": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,   'int16')
            elif typeList[i].T== "int32": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,   'int32')
            elif typeList[i].T== "int64": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,   'int64')
            elif typeList[i].T== "uint8": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,   'uint8')
            elif typeList[i].T=="uint16": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,  'uint16')
            elif typeList[i].T=="uint32": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,  'uint32')
            elif typeList[i].T=="uint64": valList[i]=read_mat_r  (readPath, typeList[i].arrLen,  'uint64')
            elif typeList[i].T== "float": valList[i]=read_mat_r  (readPath, typeList[i].arrLen, 'float32')
            elif typeList[i].T=="double": valList[i]=read_mat_r  (readPath, typeList[i].arrLen, 'float64')
            else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[i].name, typeList[i].T))
        else: print("ERROR: %s :: \"%s\" is an unsupported type." % (location(), typeList[i].name))

    # import running function
    exec ("sys.path.append(\"%s\")" % os.path.dirname(importFile))
    exec ("from %s import *" % os.path.basename(importFile))
    
    # run function
    run_pyFunc = "valList[0]=eval(funcName)("
    if len(valList)>=1:
        run_pyFunc += "valList[1]"
    for i in range(2,len(valList)):
        run_pyFunc += (",valList[%d]" % i)
    run_pyFunc += ")"
    exec run_pyFunc

    # arg と valList[0] で書き戻しの処理は同じだが，分割されているので，まどろっこしい．
    # したがって，下記 2 つの処理は，統合するように．-> どう共通化すべきか，よくわからない．
    
    # write back non const pointer args.
    # ここ，ビルトイン型の場合に numpy 型へ変換する必要があるが，ひとますパス．
    for i in range(1, len(typeList)): # minus 1 for return value type
        if typeList[i].constTF==False and typeList[i].pointer==True:
            if typeList[i].name=="vec" and typeList[i].T=="str":
                strBuf=""
                for v in range(len(valList[i])):
                    strBuf+=valList[i][v]
                valList[i]=strBuf
            elif typeList[i].name=="vec" and typeList[i].T=="char":
                charBuf=""
                for v in range(len(valList[i])):
                    charBuf+=valList[i][v][0]
                valList[i]=charBuf
            elif typeList[i].name=="mat":
                if typeList[i].T=="char": valList[i]=matChar_serialize(valList[i])
                else:
                    # transpose args of sstd::mat<T>
                    valList[i]=valList[i].flatten('F').reshape(valList[i].shape[0], valList[i].shape[1]) # Corresponding column-major matrix or not is a problem of python, so this needs to deal in python side.
            elif typeList[i].name=="mat_r":
                if typeList[i].T=="char": valList[i]=mat_rChar_serialize(valList[i])
            fp = fopen(basePath + ("/arg%04u.bin" % i), "wb")
            fp.write(valList[i])
            fp.close()
    
    # rewriting array length of return value to "./temp/sec_millisec/argList.bin"
    # needing to count array length before changing shape of "valList[0]".
    argListBin_lines=readSplitLine(basePath + "/argList.bin")
    if   typeList[0].name==  "vec":
        if typeList[0].T=="str":
            changeStr = ("F vec str F F %lu" % len(valList[0]))
            for i in range(len(valList[0])):
                changeStr += (" %lu" % len(valList[0][i]))
            argListBin_lines[0]=changeStr
    elif typeList[0].name==  "mat":
        if typeList[0].T=="char": argListBin_lines[0]=("F mat %s F F 2 %lu %lu" % (typeList[i].T, len(valList[0]),     len(valList[0][0]) ))
        else:                     argListBin_lines[0]=("F mat %s F F 2 %lu %lu" % (typeList[i].T, valList[0].shape[0], valList[0].shape[1])); valList[0]=valList[0].flatten('F').reshape(valList[0].shape[0], valList[0].shape[1]) # Corresponding column-major matrix or not is a problem of python, so this needs to deal in python side.
    elif typeList[0].name=="mat_r":
        if typeList[0].T=="char": argListBin_lines[0]=("F mat_r %s F F 2 %lu %lu" % (typeList[i].T, len(valList[0]),     len(valList[0][0]) ))
        else:                     argListBin_lines[0]=("F mat_r %s F F 2 %lu %lu" % (typeList[i].T, valList[0].shape[0], valList[0].shape[1]))
    writeBuf=""
    if len(argListBin_lines)!=0:
        writeBuf+=argListBin_lines[0]
    for i in range(1,len(argListBin_lines)):
        writeBuf+="\n"+argListBin_lines[i]
    fp=fopen(basePath + "/argList.bin", "wb")
    fp.write(writeBuf)
    fp.close()

    # Is return type is void
    if typeList[0].name=="void": return
    
    # If it is not correct return value (valList[0]), below lines will translate to a correct type.
    if IsNumpy(valList[0]): valList[0]=cnv2correctDtype(typeList, valList[0])
    
    # transition of builtin type to numpy
    if IsBuiltin(valList[0]): valList[0]=cnv_builtin2numpy(typeList, valList[0])

    # write return value to a file
    fp = fopen(basePath + "/arg0000.bin", "wb")
    fp.write(valList[0])
    fp.close()

#--------------------------------------------------------------------------------------------------------

main()

#--------------------------------------------------------------------------------------------------------

