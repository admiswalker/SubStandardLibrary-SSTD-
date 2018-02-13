import numpy as np
#from copy import deepcopy

#--------------------------------------------------------------------------------------------------------

def py_emptyArg(): print("* * * Welcome to sstd::c2py<T> ! * * *")

#--------------------------------------------------------------------------------------------------------

def py_bool(rhs):
    if rhs==True: print("T");
    else: print("F");
    return (rhs, True)
def py_pBool(rhs):
    print(rhs)
    for i in range(len(rhs)): rhs[i]=~rhs[i]
    print(rhs)
def py_pBool_builtin(rhs):
    print(rhs)
    for i in range(len(rhs)):
        if rhs[i]: rhs[i]=False
        else: rhs[i]=True
    print(rhs)
def py_pBool_pBuiltin(pRhs):
    print(pRhs)
    for i in range(len(pRhs[0])):
        if pRhs[0][i]: pRhs[0][i]=False
        else: pRhs[0][i]=True
    print(pRhs)
    
def py_char (rhs): print("char: %c" %  rhs); return (rhs, 'W')
def py_pChar(rhs): print("pChar: %s" % rhs)
def py_pChar_pBuiltin(pRhs): pRhs[0]="writeX"

def py_uchar (rhs): print("uchar: %u" % rhs); return rhs
def py_pUchar(rhs):
    print(rhs)
    for i in range(len(rhs)): rhs[i]=~rhs[i]
    print(rhs)

def py_builtIn(rhs): print(rhs); return rhs
def py_pBuiltIn(rhs):
    print(rhs)
    rhs[0]=9
    print(rhs)

def py_floatXX (rhs): print(rhs); print(rhs.dtype); return rhs
def py_pFloatXX(rhs):
    print(rhs)
    for i in range(len(rhs)): rhs[i]=100*rhs[i]
    print(rhs)

#--------------------------------------------------------------------------------------------------------
# std::string

def py_str (rhs): print(rhs); return rhs
def py_pStr(rhs): print(rhs) # rhs[0]='X'; # TypeError: 'str' object does not support item assignment

#--------------------------------------------------------------------------------------------------------
# std::vector<T>

def py_vecBool       (rhs): print(rhs); return [True, True, False, False]
def py_pVecBool_const(rhs): print(rhs)
def py_pVecBool      (rhs):
    print(rhs)
    rhs[0]=False
    rhs = np.append(rhs, True)
#    rhs = np.hstack((rhs,True)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print(rhs)

def py_vecChar       (rhs): print(rhs); return ['W', 'X', 'Y', 'Z']
def py_pVecChar_const(rhs): print(rhs)
def py_pVecChar      (rhs):
    print(rhs)
    rhs[0]='9'
    rhs.append('8')
    print(rhs)
    
def py_vecX       (rhs): print(rhs); return [9, 8, 7, 6]
def py_pVecX_const(rhs): print(rhs)
def py_pVecX      (rhs):
    print(rhs)
    rhs[0]=9
    rhs = np.append(rhs, 88) # uint64 でこれを実装すると，なぜか float 型になる．(おそらく numpy の仕様．dtype まで指定しないといけない．)
#    rhs = np.hstack((rhs,88.0)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print(rhs)

#def py_vecDouble       (rhs): print(rhs); return rhs
def py_vecDouble       (rhs): print(rhs); return [9.0, 8.0, 7.0, 6.0]
def py_pVecDouble_const(rhs): print(rhs)
def py_pVecDouble      (rhs):
    print(rhs)
    rhs[0]=9.0
    rhs = np.append(rhs, 88.0)
#    rhs = np.hstack((rhs,88.0)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print(rhs)
def py_vecDouble_cnv2builtIn(rhs):
    print(rhs)
    rhs.append(88.0)
def py_vecDouble_pointer(pRhs):
    print(pRhs)
    pRhs[0] = np.append(pRhs[0], 88) # uint64 でこれを実装すると，なぜか float 型になる．(おそらく numpy の仕様．dtype まで指定しないといけない．)
    
#def py_vecStr(rhs): print(rhs); return rhs
def py_vecStr       (rhs): print(rhs); return ["01234", "ABCDEFGHIJKLMNOPQRRRRRRRRZ", "STUUUUUUUUUUUUUUUUUUUUUUUUZ"]
def py_pVecStr_const(rhs): print(rhs); return 0
def py_pVecStr      (rhs): print(rhs); return 0

#--------------------------------------------------------------------------------------------------------

def py_pMatChar(rhs):
    print(rhs)
    rhs[0][0]='A'
    rhs = np.append(rhs, 'X') # uint64 でこれを実装すると，なぜか float 型になる．(おそらく numpy の仕様．dtype まで指定しないといけない．)
#    rhs = np.hstack((rhs,88.0)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print(rhs)

def py_pMatBool(rhs):
    print(rhs)
    rhs[0][0]=False
    rhs = np.append(rhs, True)
#    rhs = np.hstack((rhs,88.0)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print(rhs)

def py_pMatStr(rhs):
    print(rhs)
    rhs[0][0]="reWrite"
    print(rhs)

def py_matX       (rhs): print(rhs); return rhs
def py_pMatX_const(rhs): print(rhs);
def py_pMatX      (rhs):
    print(rhs)
    rhs[0][0]=9
    rhs = np.append(rhs, 88) # uint64 でこれを実装すると，なぜか float 型になる．(おそらく numpy の仕様．dtype まで指定しないといけない．)
#    rhs = np.hstack((rhs,88.0)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print(rhs)

#--------------------------------------------------------------------------------------------------------

def py_ret(pRhs):
    ret1=1.0
    ret2=[2.0, 3.0]
    ret3=[4.0, 5.0, 6.0, 7.0]

    pRhs[0].append(88.0)
    return (ret1, ret2, ret3)

#--------------------------------------------------------------------------------------------------------

def plus_A_B(a, b):
    print("I am in plus_A_B.")
    return a+b

def plus_vecA_vecB(vecA, vecB):
    print("□ begin: plus_vecA_vecB.")
    #vecC = [0.0 for i in range(len(vecA))]
    #vecC = np.array([0.0 for i in range(len(vecA))], dtype = 'float64')
    vecC = np.array([0.0 for i in range(len(vecA))], dtype = 'float32')
    for i in range(len(vecA)):
        vecC[i] += vecA[i] + vecB[i]
    print("□ end")
    return vecC

def writeBack_vecA(vecA):
    print(vecA)
    vecA[0]=9
    vecA[1]=9
    vecA[2]=9
    #vecA = [9, 9, 9] # これは，python が別変数として扱うため，書き戻しが発生しない．
    return 0

def mat2print(mat):
    print(mat)
    return 0

def mat_r2print(mat):
    print(mat)
    return 0

def ret_mat_r(mat):
    print(mat)
    return mat


from PIL import Image
from io import BytesIO
def path2mat_r_img(path):
    img = np.array(Image.open(path).convert("L"))
    return img
    #print(img.shape[0])
    #print(img.shape[1])
    #print(img.shape[2])
    #img_mid_v = np.max(img, axis = 2)/2 +np.min(img, axis = 2)/2 # https://qiita.com/secang0/items/1229212a37d8c9922901 # 中間値法による白黒化
    #return img_mid_v

import matplotlib as mpl        # "QXcbConnection: Could not connect to display" への対策
mpl.use('Agg')                  # "QXcbConnection: Could not connect to display" への対策
import matplotlib.pyplot as plt # "QXcbConnection: Could not connect to display" への対策
def mat_r_img2png(writePath, mat_r_img):
    plt.clf()#メモリのクリア
    ax = plt.imshow(mat_r_img, cmap='gray')
    
    SetFontSize = 11
    #plt.title("Title",fontsize=SetFontSize)
    plt.xlabel("pixel", fontsize=SetFontSize)
    plt.ylabel("pixel",fontsize=SetFontSize)
    
    cb = plt.colorbar(ax)
    plt.savefig(writePath, bbox_inches="tight")
    
    return 0


import matplotlib.ticker as tick
def vec2graph(writeName, vecX, vecY):
    plt.clf()
    fig = plt.figure(figsize=(8, 2.5)) # 3*5, 1*5 # アスペクト比の設定
    ax1 = fig.add_subplot(111)
    ax1.plot(vecX, vecY, color='k', linewidth=0.5)

    title  = "Example of a \"vec2graph()\" python function called by \"sstd::c2py()\".   \n"
    title += "In this exmaple, a type of std::vector<double> in C++ is converted to\n"
    title += "a graph through the matplotlib in Python. Python function is called by  \n"
    title += "C++ only 2 lines enabled by \"sstd::c2py()\".                                           "
    ax1.set_title(title)
    ax1.set_xlabel("Time [sec]\nFig 1.  0.1 Hz sin wave sampled by 10 Hz.")
    #ax1.set_xlim(0, 60)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude")
    ax1.set_ylim(-1.1, 1.1)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(0.5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(0.1))
    
    plt.savefig(writeName, bbox_inches="tight") # , dpi=100
    return 0

