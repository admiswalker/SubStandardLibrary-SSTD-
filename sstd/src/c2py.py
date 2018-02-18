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
        self.retTF              = False  # ret
        self.constTF            = True   # const
        self.name               = "x"    # void, int, vec<T>... and so on.
        self.T                  = "x"    # template<typename "T"> or ""
        self.pointer            = False  # *
        self.pointer_sidePy     = False  # *
        self.cnv2builtIn_sidePy = False  # ~
        self.arrLen             = []     # array length

def c2bool(rhs):
    if   rhs=='T': return True
    elif rhs=='F': return False
    else: print("ERROR: %s" % location()); return False

def fopen(readPath, option):
    try:
        fp = open(readPath, option)
    except IOError:
        print("ERROR: %s :: %s can not be opened.\n" % (location(), readPath))
    return fp
def read_typeList(readPath):
    lines=readSplitLine(readPath)

    argList=[]
    for line in lines:
        s_line = line.split()
        buf = typeSet()
        buf.retTF              = c2bool(s_line[0])
        buf.constTF            = c2bool(s_line[1])
        buf.name               =        s_line[2]
        buf.T                  =        s_line[3]
        buf.pointer            = c2bool(s_line[4])
        buf.pointer_sidePy     = c2bool(s_line[5])
        buf.cnv2builtIn_sidePy = c2bool(s_line[6])
        lenOfarrLen            =    int(s_line[7])
        for i in range(lenOfarrLen):
            buf.arrLen.append(int(s_line[8+i]))
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
def read_matStr(readPath, arrLen):
    fp=fopen(readPath, "rb");
    strBuf=fp.read();
    matStr=[[[] for i in range(arrLen[1])] for i in range(arrLen[0])]
    s=0
    for q in range(arrLen[1]): # col
        for p in range(arrLen[0]): # row
            i=2+p+arrLen[0]*q # adding 2, in order to pass rows and cols.
            matStr[p][q] = strBuf[s : s + arrLen[i]]
            s += arrLen[i]
    return matStr
def read_mat(readPath, arrLen, matType):
    fp=fopen(readPath, "rb")
    ret=(np.fromfile(fp, np.dtype(matType), arrLen[0]*arrLen[1])).reshape(arrLen[1], arrLen[0])
    fp.close()
    return ret.flatten('F').reshape(arrLen[0], arrLen[1]) # numpy は行優先のため，列優先の行列を受け取った場合は，このように転置が発生する．

def read_mat_rChar(readPath, arrLen):
    fp=fopen(readPath, "rb")
    charBuf=fp.read()
    mat_rChar=[[' ' for i in range(arrLen[1])] for i in range(arrLen[0])]
    for p in range(arrLen[0]):
        for q in range(arrLen[1]):
            mat_rChar[p][q] = charBuf[arrLen[1]*p+q]
    return mat_rChar
def read_mat_rStr(readPath, arrLen):
    fp=fopen(readPath, "rb")
    strBuf=fp.read()
    mat_rStr=[[[] for i in range(arrLen[1])] for i in range(arrLen[0])]
    s=0
    for p in range(arrLen[0]): # row
        for q in range(arrLen[1]): # col
            i=2+p*arrLen[1]+q # adding 2, in order to pass rows and cols.
            mat_rStr[p][q] = strBuf[s : s + arrLen[i]]
            s += arrLen[i]
    return mat_rStr
def read_mat_r(readPath, arrLen, matType):
    fp=fopen(readPath, "rb")
    ret=(np.fromfile(fp, np.dtype(matType), arrLen[0]*arrLen[1])).reshape(arrLen[0], arrLen[1])
    fp.close()
    return ret

#--------------------------------------------------------------------------------------------------------

def builtIn_readFile(typeList, i, readPFunc, readFunc, readPath):
    if typeList[i].pointer: return readPFunc(readPath, typeList[i].arrLen)
    else: return readFunc(readPath)

#--------------------------------------------------------------------------------------------------------
    
def cnv_numpy2builtin(Type, val):
    if   val.ndim==0: return np.asscalar(val) # scalar
    elif val.ndim==1: return [np.asscalar(val[i]) for i in range(val.shape[0])] # vector
    elif val.ndim==2: return [[np.asscalar(val[p][q]) for q in range(val.shape[1])] for p in range(val.shape[0])] # matrix
    else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), Type.name, Type.T))

#--------------------------------------------------------------------------------------------------------

def cnv2correctDtype(Type, ret):
    if   Type.name==  "bool" and ret.dtype!=np.bool:    return ret.astype(np.bool   )
    elif Type.name==  "char" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
    elif Type.name== "uchar" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
    elif Type.name==  "int8" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
    elif Type.name== "uint8" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
    elif Type.name== "int16" and ret.dtype!=np.int16:   return ret.astype(np.int16  )
    elif Type.name=="uint16" and ret.dtype!=np.uint16:  return ret.astype(np.uint16 )
    elif Type.name== "int32" and ret.dtype!=np.int32:   return ret.astype(np.int32  )
    elif Type.name=="uint32" and ret.dtype!=np.uint32:  return ret.astype(np.uint32 )
    elif Type.name== "int64" and ret.dtype!=np.int64:   return ret.astype(np.int64  )
    elif Type.name=="uint64" and ret.dtype!=np.uint64:  return ret.astype(np.uint64 )
    elif Type.name== "float" and ret.dtype!=np.float32: return ret.astype(np.float32)
    elif Type.name=="double" and ret.dtype!=np.float64: return ret.astype(np.float64)
    elif Type.name=="vec" or Type.name=="mat" or Type.name=="mat_r":
        if   Type.T==  "bool" and ret.dtype!=np.bool:    return ret.astype(np.bool   )
        elif Type.T==  "char" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
        elif Type.T== "uchar" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
        elif Type.T==  "int8" and ret.dtype!=np.int8:    return ret.astype(np.int8   )
        elif Type.T== "uint8" and ret.dtype!=np.uint8:   return ret.astype(np.uint8  )
        elif Type.T== "int16" and ret.dtype!=np.int16:   return ret.astype(np.int16  )
        elif Type.T=="uint16" and ret.dtype!=np.uint16:  return ret.astype(np.uint16 )
        elif Type.T== "int32" and ret.dtype!=np.int32:   return ret.astype(np.int32  )
        elif Type.T=="uint32" and ret.dtype!=np.uint32:  return ret.astype(np.uint32 )
        elif Type.T== "int64" and ret.dtype!=np.int64:   return ret.astype(np.int64  )
        elif Type.T=="uint64" and ret.dtype!=np.uint64:  return ret.astype(np.uint64 )
        elif Type.T== "float" and ret.dtype!=np.float32: return ret.astype(np.float32)
        elif Type.T=="double" and ret.dtype!=np.float64: return ret.astype(np.float64)
        else: return ret
    else: return ret

#--------------------------------------------------------------------------------------------------------

def cnv2numpy(Type, val):
    if   Type.name==  "bool": return np.array(val, dtype =   "bool")
    elif Type.name==  "char": return val # there is nothing to do
    elif Type.name== "uchar": return np.array(val, dtype =  "uint8")
    elif Type.name==  "int8": return np.array(val, dtype =   "int8")
    elif Type.name== "int16": return np.array(val, dtype =  "int16")
    elif Type.name== "int32": return np.array(val, dtype =  "int32")
    elif Type.name== "int64": return np.array(val, dtype =  "int64")
    elif Type.name== "uint8": return np.array(val, dtype =  "uint8")
    elif Type.name=="uint16": return np.array(val, dtype = "uint16")
    elif Type.name=="uint32": return np.array(val, dtype = "uint32")
    elif Type.name=="uint64": return np.array(val, dtype = "uint64")
    elif Type.name== "float": return np.array(val, dtype ="float32")
    elif Type.name=="double": return np.array(val, dtype ="float64")
    elif Type.name==   "str": return val # there is nothing to do
    elif Type.name==   "vec":
        if   Type.T==  "bool": return np.array(val, dtype =   "bool")
        elif Type.T==  "char": return val # there is nothing to do
        elif Type.T== "uchar": return np.array(val, dtype =  "uint8")
        elif Type.T==  "int8": return np.array(val, dtype =   "int8")
        elif Type.T== "int16": return np.array(val, dtype =  "int16")
        elif Type.T== "int32": return np.array(val, dtype =  "int32")
        elif Type.T== "int64": return np.array(val, dtype =  "int64")
        elif Type.T== "uint8": return np.array(val, dtype =  "uint8")
        elif Type.T=="uint16": return np.array(val, dtype = "uint16")
        elif Type.T=="uint32": return np.array(val, dtype = "uint32")
        elif Type.T=="uint64": return np.array(val, dtype = "uint64")
        elif Type.T== "float": return np.array(val, dtype ="float32")
        elif Type.T=="double": return np.array(val, dtype ="float64")
        elif Type.T==   "str": return val # there is nothing to do
        else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), Type.name, Type.T))
    elif Type.name==   "mat":
        if   Type.T==  "bool": return np.array(val, dtype =   "bool")
        elif Type.T==  "char": return val # there is nothing to do
        elif Type.T== "uchar": return np.array(val, dtype =  "uint8")
        elif Type.T==  "int8": return np.array(val, dtype =   "int8")
        elif Type.T== "int16": return np.array(val, dtype =  "int16")
        elif Type.T== "int32": return np.array(val, dtype =  "int32")
        elif Type.T== "int64": return np.array(val, dtype =  "int64")
        elif Type.T== "uint8": return np.array(val, dtype =  "uint8")
        elif Type.T=="uint16": return np.array(val, dtype = "uint16")
        elif Type.T=="uint32": return np.array(val, dtype = "uint32")
        elif Type.T=="uint64": return np.array(val, dtype = "uint64")
        elif Type.T== "float": return np.array(val, dtype ="float32")
        elif Type.T=="double": return np.array(val, dtype ="float64")
        elif Type.T==   "str": return val # there is nothing to do
        else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), Type.name, Type.T))
    elif Type.name== "mat_r":
        if   Type.T==  "bool": return np.array(val, dtype =   "bool")
        elif Type.T==  "char": return val # there is nothing to do
        elif Type.T== "uchar": return np.array(val, dtype =  "uint8")
        elif Type.T==  "int8": return np.array(val, dtype =   "int8")
        elif Type.T== "int16": return np.array(val, dtype =  "int16")
        elif Type.T== "int32": return np.array(val, dtype =  "int32")
        elif Type.T== "int64": return np.array(val, dtype =  "int64")
        elif Type.T== "uint8": return np.array(val, dtype =  "uint8")
        elif Type.T=="uint16": return np.array(val, dtype = "uint16")
        elif Type.T=="uint32": return np.array(val, dtype = "uint32")
        elif Type.T=="uint64": return np.array(val, dtype = "uint64")
        elif Type.T== "float": return np.array(val, dtype ="float32")
        elif Type.T=="double": return np.array(val, dtype ="float64")
        elif Type.T==   "str": return val # there is nothing to do
        else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), Type.name, Type.T))
    else: print("ERROR: %s :: \"%s\" is an unsupported type." % (location(), Type.name))

#--------------------------------------------------------------------------------------------------------

def vecChar_serialize(rhs):
    charBuf=""
    for i in range(len(rhs)): charBuf+=rhs[i][0]
    return charBuf
def vecStr_serialize(rhs):
    strBuf=""
    for i in range(len(rhs)): strBuf+=rhs[i]
    return strBuf

def matChar_serialize(rhs):
    charBuf=""
    for q in range(len(rhs[0])):
        for p in range(len(rhs)):
            charBuf+=rhs[p][q]
    return charBuf
def matStr_serialize(rhs):
    strBuf=""
    for q in range(len(rhs[0])):
        for p in range(len(rhs)):
            strBuf+=rhs[p][q]
    return strBuf

def mat_rChar_serialize(rhs):
    charBuf=""
    for p in range(len(rhs)):
        for q in range(len(rhs[0])):
            charBuf+=rhs[p][q]
    return charBuf
def mat_rStr_serialize(rhs):
    strBuf=""
    for p in range(len(rhs)):
        for q in range(len(rhs[0])):
            strBuf+=rhs[p][q]
    return strBuf
    
def cnv2writeType(Type, val):
    if   Type.name=="vec":
        if   Type.T==  "char": return vecChar_serialize(val) # reshape to one strign array
        elif Type.T==   "str": return vecStr_serialize (val) # reshape to one strign array
        else: return val
    elif Type.name=="mat":
        if   Type.T==  "char": return matChar_serialize(val) # reshape to one strign array
        elif Type.T==   "str": return matStr_serialize (val) # reshape to one strign array
        else: return val.flatten('F').reshape(val.shape[0], val.shape[1]) # Corresponding column-major matrix or not is a problem of python, so this needs to deal in python side.
    elif Type.name== "mat_r":
        if   Type.T==  "char": return mat_rChar_serialize(val) # reshape to one strign array
        elif Type.T==   "str": return mat_rStr_serialize (val) # reshape to one strign array
        else: return val
    else: return val

#--------------------------------------------------------------------------------------------------------
# write back "argList.bin"

def val2argLine_vecStr(val):
    changeStr = ("F F vec str F F F %lu" % len(val))
    for i in range(len(val)):
        changeStr += (" %lu" % len(val[i]))
    return changeStr

def val2argLine_matStr(val):
    rows=len(val   )
    cols=len(val[0])
    changeStr = ("F F mat str F F F %lu %lu %lu" % (rows*cols+2, rows, cols))
    for q in range(cols): # col
        for p in range(rows): # row
            changeStr += (" %lu" % len(val[p][q]))
    return changeStr

def val2argLine_mat_rStr(val):
    rows=len(val   )
    cols=len(val[0])
    changeStr = ("F F mat_r str F F F %lu %lu %lu" % (rows*cols+2, rows, cols))
    for p in range(rows): # row
        for q in range(cols): # col
            changeStr += (" %lu" % len(val[p][q]))
    return changeStr

def generate_argListBin_line(Type, val, line):
    if   Type.name==  "vec":
        if   Type.T=="char": return ("F F mat %s F F F 2 %lu %lu" % (Type.T, len(val), len(val[0])))
        elif Type.T== "str": return val2argLine_vecStr(val)
        else:                return ("F F vec %s F F F 1 %lu" % (Type.T, val.shape[0]))
    elif Type.name==  "mat":
        if   Type.T=="char": return ("F F mat %s F F F 2 %lu %lu" % (Type.T, len(val), len(val[0])))
        elif Type.T== "str": return val2argLine_matStr(val)
        else:                return ("F F mat %s F F F 2 %lu %lu" % (Type.T, val.shape[0], val.shape[1]))
    elif Type.name=="mat_r":
        if   Type.T=="char": return ("F F mat_r %s F F F 2 %lu %lu" % (Type.T, len(val), len(val[0])))
        elif Type.T== "str": return val2argLine_mat_rStr(val)
        else:                return ("F F mat_r %s F F F 2 %lu %lu" % (Type.T, val.shape[0], val.shape[1]))
    else: return line

#--------------------------------------------------------------------------------------------------------

def main():
    args = sys.argv
    if len(args)<=1: print("ERROR: %s :: too few args" % location()); return
    (basePath, importFile, funcName) = (args[1], args[2], args[3])
    
    typeList = read_typeList(basePath + "/argList.bin")
    valList  = [[] for i in range(len(typeList))]
    
    retNum=int(0)
    ignoreValList=[]
    if(typeList[0].name=="void"): ignoreValList.append(0)
    else:                         retNum+=1
    
    for i in range(1, len(typeList)): # begin 1 for return value type. (passing the ret of "valList[0]".)
        if(typeList[i].retTF): retNum+=1; continue;
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
        elif typeList[i].name==   "len": ignoreValList.append(i); pass
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
            elif typeList[i].T==   "str": valList[i]=read_matStr (readPath, typeList[i].arrLen)
            else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[i].name, typeList[i].T))
        elif typeList[i].name== "mat_r":
            if   typeList[i].T==  "bool": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,    'bool')
            elif typeList[i].T==  "char": valList[i]=read_mat_rChar(readPath, typeList[i].arrLen)
            elif typeList[i].T==  "int8": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,    'int8')
            elif typeList[i].T== "int16": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,   'int16')
            elif typeList[i].T== "int32": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,   'int32')
            elif typeList[i].T== "int64": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,   'int64')
            elif typeList[i].T== "uint8": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,   'uint8')
            elif typeList[i].T=="uint16": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,  'uint16')
            elif typeList[i].T=="uint32": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,  'uint32')
            elif typeList[i].T=="uint64": valList[i]=read_mat_r    (readPath, typeList[i].arrLen,  'uint64')
            elif typeList[i].T== "float": valList[i]=read_mat_r    (readPath, typeList[i].arrLen, 'float32')
            elif typeList[i].T=="double": valList[i]=read_mat_r    (readPath, typeList[i].arrLen, 'float64')
            elif typeList[i].T==   "str": valList[i]=read_mat_rStr (readPath, typeList[i].arrLen)
            else: print("ERROR: %s :: \"%s<%s>\" is an unsupported type." % (location(), typeList[i].name, typeList[i].T))
        else: print("ERROR: %s :: \"%s\" is an unsupported type." % (location(), typeList[i].name))

    # conversion of numpy type to builtin type while retTF is true.
    for i in range(1,len(valList)):
        if IsNumpy(valList[i])==False: continue
        if typeList[i].cnv2builtIn_sidePy: valList[i]=cnv_numpy2builtin(typeList[i], valList[i])

    # convert to a pseudo pointer type
    for i in range(1,len(valList)):
        if typeList[i].pointer_sidePy: valList[i]=[valList[i]]
        
    # import running function
    exec ("sys.path.append(\"%s\")" % os.path.dirname(importFile))
    exec ("from %s import *" % os.path.basename(importFile))
    
    # run function
    valNumList=[int(i) for i in range(len(valList))]
    n=int(0)
    for i in reversed(xrange(len(ignoreValList))):
        valNumList.pop(ignoreValList[i])
    run_pyFunc=""
    if retNum>=1:
        run_pyFunc = ("(valList[%d]" % valNumList[n]); n+=1
        for i in range(1,retNum):
            run_pyFunc += (",valList[%d]" % valNumList[n]); n+=1
        run_pyFunc += ")="
    run_pyFunc += "eval(funcName)("
    if (len(valNumList)-retNum)>=1:
        run_pyFunc += ("valList[%d]" % valNumList[n]); n+=1
        for i in range(len(valNumList)-retNum-1):
            run_pyFunc += (",valList[%d]" % valNumList[n]); n+=1
    run_pyFunc += ")"
    exec run_pyFunc
    
    # Inverse transformation of a pseudo pointer type
    for i in range(1,len(valList)):
        if typeList[i].pointer_sidePy: valList[i]=valList[i][0]
    
    # rewriting array length of return value to "./temp/sec_millisec/argList.bin"
    # needing to count array length before changing shape of "valList[0]".
    argListBin_lines=readSplitLine(basePath + "/argList.bin")
    for i in range(0, len(typeList)):
        if i==0 and typeList[i].name=="void": continue
        if typeList[i].retTF==False and typeList[i].constTF==True: continue
        if i!=0 and typeList[i].pointer==False: continue

        # If it is not correct return value (valList[0]), below lines will translate to a correct type.
        if IsNumpy(valList[i]): valList[i]=cnv2correctDtype(typeList[i], valList[i])
        else:                   valList[i]=cnv2numpy       (typeList[i], valList[i]) # translating to numpy type
        
        argListBin_lines[i]=generate_argListBin_line(typeList[i], valList[i], argListBin_lines[i])
    writeBuf=""
    if len(argListBin_lines)!=0:             writeBuf+=     argListBin_lines[0]
    for i in range(1,len(argListBin_lines)): writeBuf+="\n"+argListBin_lines[i]
    fp=fopen(basePath + "/argList.bin", "wb")
    fp.write(writeBuf)
    fp.close()
    
    # write back non const pointer args.
    for i in range(len(typeList)):
        if i==0 and typeList[i].name=="void": continue
        if typeList[i].constTF==True: continue
        if i!=0 and typeList[i].pointer==False: continue

        # conversion of numpy type
        valList[i]=cnv2writeType(typeList[i], valList[i])

        fp = fopen(basePath + ("/arg%04u.bin" % i), "wb")
        fp.write(valList[i])
        fp.close()

#--------------------------------------------------------------------------------------------------------

#import time
#startTime = time.time()
main()
#endTime   = time.time()
#print (" Execution time: {0}".format(endTime-startTime) + " [sec]")

#--------------------------------------------------------------------------------------------------------

