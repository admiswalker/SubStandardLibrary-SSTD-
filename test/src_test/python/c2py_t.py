#coding:UTF-8
import numpy as np
#from copy import deepcopy

#--------------------------------------------------------------------------------------------------------

def py_empty(): return
def py_emptyArg(): print("* * * Welcome to sstd::c2py<T> ! * * *")

#--------------------------------------------------------------------------------------------------------
# print functions for test code.
#  - below functions print parsed values for test code.

def inv_bool(rhs): # numpy is able to inv by '~', but bultin type can not inv by '~'.
    if rhs: return False
    else:   return True
def inv_bool_vec(vecRhs):
    for i in range(len(vecRhs)):
        vecRhs[i]=inv_bool(vecRhs[i])

#---

def print_bool(rhs):
    if rhs: print("T")
    else:   print("F")
def print_vec_bool(vecRhs):
    for i in range(len(vecRhs)):
        print_bool(vecRhs[i])
def print_mat_bool(mat):
    for col in range(len(mat)):
        for row in range(len(mat[0])):
            print_bool(mat[col][row])

#---

def print_char(rhs):
    print("%c" % rhs)
def print_vec_char(vecRhs):
    for rhs in vecRhs:
        print_char(rhs)
def print_mat_char(mat):
    for col in range(len(mat)):
        for row in range(len(mat[0])):
            print_char(mat[col][row])

#---

def print_vec(vecRhs): # print_vec_intX
    for i in range(len(vecRhs)):
        print(vecRhs[i])

#---

def print_float(rhs):
    print('%.4f' % rhs)
def print_vec_floatX(vec):
    for i in range(len(vec)):
        print_float(vec[i])
def print_vvec_floatX(vvec):
    for v in range(len(vvec)):
        for i in range(len(vvec[v])):
            print_float(vvec[v][i])
def print_mat_floatX(mat):
    for col in range(len(mat)):
        for row in range(len(mat[0])):
            print_float(mat[col][row])

#---

def print_mat(mat):
    for col in range(len(mat)):
        for row in range(len(mat[0])):
            print(mat[col][row])
    return

#--------------------------------------------------------------------------------------------------------

def py_bool(rhs):
    print_bool(rhs)
    return (rhs, not(rhs))
def py_pBool(vecRhs):
    print_vec_bool(vecRhs)
    inv_bool_vec(vecRhs)
    print_vec_bool(vecRhs)
def py_pBool_pBuiltin(pVecRhs):
    print_vec_bool(pVecRhs[0])
    inv_bool_vec(pVecRhs[0])
    print_vec_bool(pVecRhs[0])
def py_pBool_pBuiltin_clear(pVecRhs):
    pVecRhs[0]=[]

#---

def py_char(rhs):
    print_char(rhs[0])
    return (rhs, 'W')
def py_pChar(rhs):
    print(rhs)
def py_pChar_pBuiltin(pRhs): pRhs[0]="writeX"

#---

def py_integer(rhs):
    print(rhs.dtype)
    print(rhs[0])
    return (rhs, rhs[0])
def py_pInteger(vecRhs):
    print_vec(vecRhs)
    vecRhs[0]=9
    vecRhs[1]=2
    print_vec(vecRhs)
def py_pInteger_pCnvBuiltin(pVecRhs):
    print_vec(pVecRhs[0])
    pVecRhs[0][0]=9
    pVecRhs[0][1]=2
    print_vec(pVecRhs[0])

def py_floatX(rhs):
    print(rhs.dtype)
    print(rhs[0])
    return (rhs[0], rhs)
def py_pFloatX(vecRhs):
    print_vec_floatX(vecRhs)
    for i in range(len(vecRhs)): vecRhs[i]=100*vecRhs[i]
    print_vec_floatX(vecRhs)
def py_pFloatX_pCnvBuiltin(pVecRhs):
    print_vec_floatX(pVecRhs[0])
    for i in range(len(pVecRhs[0])): pVecRhs[0][i]=100*pVecRhs[0][i]
    print_vec_floatX(pVecRhs[0])

#--------------------------------------------------------------------------------------------------------
# std::string

def py_str (rhs): print(rhs); return (rhs, "0123456789_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX_ABCD")
def py_pStr(rhs): print(rhs) # rhs[0]='X'; # TypeError: 'str' object does not support item assignment
def py_pStr_pCnvBuiltin(pRhs): print(pRhs[0]); pRhs[0]="writeBack"

#--------------------------------------------------------------------------------------------------------
# std::vector<T>

def py_vecBool(vecRhs):
    print_vec_bool(vecRhs)
    return (vecRhs, vecRhs)
def py_pVecBool(vecRhs):
    print_vec_bool(vecRhs)
    inv_bool_vec(vecRhs)
#    rhs = np.append(rhs, True)
#    rhs = np.hstack((rhs,True)) # can not Write Back, because of a new appended object will be treated as the other new object.
    print_vec_bool(vecRhs)
def py_pVecBool_pCnvBuiltin(pVecRhs):
    print_vec_bool(pVecRhs[0])
    inv_bool_vec(pVecRhs[0])
    print_vec_bool(pVecRhs[0])
    pVecRhs[0].append(True)
    pVecRhs[0].append(True)
    pVecRhs[0].append(True)
def py_pVecBool_pCnvBuiltin_del(pVecRhs):
    pVecRhs[0].pop(0)
def py_pVecBool_pCnvBuiltin_clear(pVecRhs):
    pVecRhs[0].clear()

def py_vecChar(vecRhs):
    print_vec_char(vecRhs)
    return (['A', 'B', 'C'], ['W', 'X', 'Y', 'Z'])
def py_pVecChar(vecRhs):
    print_vec_char(vecRhs)
    vecRhs[0]='9'
    vecRhs.append('8')
    print_vec_char(vecRhs)
def py_pVecChar_del(vecRhs):
    vecRhs.pop(0)
def py_pVecChar_clear(vecRhs):
    vecRhs.clear()
def py_pVecChar_pCnvBuiltin(pVecRhs):
    print_vec_char(pVecRhs[0])
    pVecRhs[0][0]='9'
    pVecRhs[0].append('8')
    print_vec_char(pVecRhs[0])

def py_vecX(vec):
    print(vec[0].dtype)
    print_vec(vec)
    return ([9.0, 8.0, 7.0, 6.0], [5.0, 4.0, 3.0, 2.0, 1.0, 0.0])
def py_pVecX_const(vec):
    print_vec(vec)
def py_pVecX(vec):
    print_vec(vec)
    vec[0]=9
    # numpy における配列の追加は、破壊的書き換えとなるため、不可
    print_vec(vec)
def py_pVecX_cnvBuiltin(vec):
    print_vec(vec)
    vec[0]=9
    vec.append(88)
    print_vec(vec)
def py_pVecX_pCnvBuiltin(pVec):
    print_vec(pVec[0])
    pVec[0][0]=9
    pVec[0]=pVec[0]+[88]
    print_vec(pVec[0])
def py_pVecX_pCnv(pVec):
    print_vec(pVec[0])
    pVec[0][0]=9
    pVec[0]=pVec[0]+[88] # pVec[0].append(88) # 'numpy.ndarray' object has no attribute 'append'
    print_vec(pVec[0])

def py_vecFloatX(vec):
    print(vec[0].dtype)
    print_vec_floatX(vec)
    return ([9.0, 8.0, 7.0, 6.0], [5.0, 4.0, 3.0, 2.0, 1.0, 0.0])
def py_pVecFloatX_const(vec):
    print_vec_floatX(vec)
def py_pVecFloatX(vec):
    print_vec_floatX(vec)
    vec[0]=9
    # numpy における配列の追加は、破壊的書き換えとなるため、不可
    print_vec_floatX(vec)
def py_pVecFloatX_cnvBuiltin(vec):
    print_vec_floatX(vec)
    vec[0]=9
    vec.append(88.0)
    print_vec_floatX(vec)
def py_pVecFloatX_pCnvBuiltin(pVec):
    print_vec_floatX(pVec[0])
    pVec[0][0]=9
    pVec[0].append(88) # pVec[0]=pVec[0]+[88]
    print_vec_floatX(pVec[0])
def py_pVecFloatX_pCnv(pVec):
    print_vec_floatX(pVec[0])
    pVec[0][0]=9
    pVec[0]=np.append(pVec[0], 88) # pVec[0]=pVec[0]+[88] # pVec[0].append(88) # 'numpy.ndarray' object has no attribute 'append'
    print_vec_floatX(pVec[0])

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
    rhs.append(88.0)
def py_vecDouble_pointer(pRhs):
    pRhs[0] = np.append(pRhs[0], 88)

#def py_vecStr(rhs): print(rhs); return rhs
def py_vecStr(vec):
    print_vec(vec)
    return (["01234", "ABCDEFGHIJKLMNOPQRRRRRRRRZ", "STUUUUUUUUUUUUUUUUUUUUUUUUZ"], ["XXXXXXX", "YYYYYY", "ZZ"])
def py_pVecStr_const(vec):
    print_vec(vec)
def py_pVecStr(vec):
    print_vec(vec)
    vec[0]='abcdefg'
    vec.append('0123')
def py_pVecStr_pCnvBuiltin(pVec):
    print_vec(pVec[0])
    pVec[0][0]='abcdefg'
    pVec[0].append('0123')
#    pVec[0]=["ABCDEFGHIJKLMNOPQRST", "UV"]

#--------------------------------------------------------------------------------------------------------

def py_matBool(mat):
    print_mat_bool(mat)
    return (mat, mat)
def py_pMatBool_const(mat):
    print_mat_bool(mat)
def py_pMatBool(mat):
    print_mat_bool(mat)
    mat[0][0]=False
#    rhs = np.append(rhs, True)
#    rhs = np.hstack((rhs,88.0)) # 追加を行ったオブジェクトは別のオブジェクトとして扱われるようで，書き戻しは不可．
    print_mat_bool(mat)
def py_pMatBool_pCnvBuiltin(pMat):
    print_mat_bool(pMat[0])
    pMat[0][0][0]=False # pMat[0][0]=[True, True, True]
    print_mat_bool(pMat[0])

def py_matChar(mat):
    print_mat_char(mat)
    return (mat, mat)
def py_pMatChar_const(mat):
    print_mat_char(mat)
def py_pMatChar(mat):
    print_mat_char(mat)
    mat[0][0]='A'
    print_mat_char(mat)
def py_pMatChar_pCnvBuiltin(pMat):
    print_mat_char(pMat[0])
    pMat[0][0][0]='A'
    print_mat_char(pMat[0])

def py_matIntX(mat):
    print_mat(mat)
    return (mat, mat)
def py_pMatIntX_const(mat):
    print_mat(mat)
def py_pMatIntX(mat):
    print_mat(mat)
    mat[0][0]=9
    print_mat(mat)
def py_pMatIntX_pCnvBuiltin(pMat):
    print_mat(pMat[0])
    pMat[0][0][0]=9
    print_mat(pMat[0])
def py_pMatIntX_pCnvBuiltin_changeSize(pMat):
    print_mat(pMat[0])
    pMat[0]=[[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]

def py_matFloatX(mat):
    print_mat_floatX(mat)
    return (mat, mat)
def py_pMatFloatX_const(mat):
    print_mat_floatX(mat)
def py_pMatFloatX(mat):
    print_mat_floatX(mat)
    mat[0][0]=9
    print_mat_floatX(mat)
def py_pMatFloatX_pCnvBuiltin(pMat):
    print_mat_floatX(pMat[0])

def py_matStr(mat):
    print_mat(mat)
    return (mat, mat)
def py_pMatStr_const(mat):
    print_mat(mat)
def py_pMatStr(mat):
    print_mat(mat)
    mat[0][0]='XXX'
    print_mat(mat)
def py_pMatStr_pCnvBuiltin(pMat):
    print_mat(pMat[0])
    pMat[0][0][0]='XXX'
    print_mat(pMat[0])
def py_pMatChar_pCnv_clear(pMat):
#    pMat[0] = [['a', 'b', 'c'], ['d', 'e', 'f'], ['g', 'h', 'i'], ['j', 'k', 'l']]
    pMat[0]=[[]]
    return

#--------------------------------------------------------------------------------------------------------

def py_vec_return_null():
    return []
def py_mat_return_null():
    return [[]]

#--------------------------------------------------------------------------------------------------------

def py_ret(pRhs):
    ret1=1.0
    ret2=[2.0, 3.0]
    ret3=[4.0, 5.0, 6.0, 7.0]
    
    pRhs[0].append(88.0)
    return (ret1, ret2, ret3)

#--------------------------------------------------------------------------------------------------------

def plus_A_B(a, b):
    return a+b

def plus_vecA_vecB(vecA, vecB):
    #vecC = [0.0 for i in range(len(vecA))]
    #vecC = np.array([0.0 for i in range(len(vecA))], dtype = 'float64')
    vecC = np.array([0.0 for i in range(len(vecA))], dtype = 'float32')
    for i in range(len(vecA)):
        vecC[i] += vecA[i] + vecB[i]
    return vecC

def writeBack_vecA(vecA):
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

def ret_mat(mat):
    return mat

def ret_mat_r(mat):
    return mat

#--------------------------------------------------------------------------------------------------------
# vvec<T>

def py_vvecFloatX(vvec):
    print(vvec[0][0].dtype)
    print_vvec_floatX(vvec)
    return (vvec, [[0],[1]])
def py_pVvecFloat_const(vvec):
    print_vvec_floatX(vvec)
def py_pVvecFloat(vvec):
    print_vvec_floatX(vvec)
    vvec[0]=[999]
    vvec.append([88])
    print_vvec_floatX(vvec)
def py_pVvecFloat_pCnvBuiltin(pVvec):
    print_vvec_floatX(pVvec[0])
    pVvec[0][0]=[999]
    pVvec[0].append([88])
    print_vvec_floatX(pVvec[0])

#--------------------------------------------------------------------------------------------------------

import matplotlib as mpl        # "QXcbConnection: Could not connect to display" への対策
mpl.use('Agg')                  # "QXcbConnection: Could not connect to display" への対策
import matplotlib.pyplot as plt # "QXcbConnection: Could not connect to display" への対策
import matplotlib.ticker as tick
def vec2graph(writeName, vecX, vecY):
    plt.clf()
    fig = plt.figure(figsize=(8, 2.5)) # 3*5, 1*5 # アスペクト比の設定
    ax1 = fig.add_subplot(111)
    ax1.plot(vecX, vecY, color='k', linewidth=0.5)
    
    title  = "An example of Plotting a figure of sin wave data generated on C++,\n"
    title += "using matplotlib which is a famous graph plotting library of python. \n"
    title += "\"sstd::c2py()\" convertes a type of std::vector<double> on C++ to  \n"
    title += "numpy array type on Python, and calling a Python function from      \n"
    title += "only 2 lines of C++ code.                                                                    "
    ax1.set_title(title)
    
    ax1.grid(which='minor', linewidth=0.5, linestyle=':',  color='gainsboro')
    ax1.grid(which='major', linewidth=0.5, linestyle='-',  color='silver'    )
    
    ax1.tick_params(pad=5, which='major', direction='in', bottom=True, top=True, left=True, right=True, length=4) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax1.tick_params(pad=5, which='minor', direction='in', bottom=True, top=True, left=True, right=True, length=2) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    
    ax1.set_xlabel("Time [sec]\nFig 1.  0.1 Hz sin wave sampled by 10 Hz, 0-60 sec.")
    ax1.set_xlim(0-1, 60+1)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude")
    ax1.set_ylim(-1.1, 1.1)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(0.5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(0.1))
    
    plt.savefig(writeName, bbox_inches="tight") # , dpi=100
#---
#mpl.rcParams['legend.frameon'] = 'False'
mpl.rcParams['legend.framealpha'] = 1
#mpl.rcParams['legend.facecolor'] = 'white'
#mpl.rcParams['legend.edgecolor'] = 'black'
def vvec2graph(writeName, vLabel, vvecX, vvecY):
    plt.clf()
    #fig = plt.figure(figsize=(8, 2.5)) # 3*5, 1*5 # アスペクト比の設定
    fig = plt.figure(figsize=(8*1.033333333, 2.5*1.033333333)) # 3*5, 1*5 # アスペクト比の設定
    # 62 sec / 60 sec = 1.033333333
    ax1 = fig.add_subplot(111)
    vColor=['black', 'blue', 'red']
    vLineStyle = ['solid', 'dashed', 'dashdot'] # solid, dashed, dashdot, dotted
    for i in range(len(vvecX)):
        ax1.plot(vvecX[i], vvecY[i], linewidth=0.5, color=vColor[i], linestyle=vLineStyle[i], label=vLabel[i])
    ax1.legend(loc='upper right')
    
    ax1.grid(which='minor', linewidth=0.5, linestyle=':',  color='gainsboro')
    ax1.grid(which='major', linewidth=0.5, linestyle='-',  color='silver'    )
    
    ax1.tick_params(pad=5, which='major', direction='in', bottom=True, top=True, left=True, right=True, length=4) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax1.tick_params(pad=5, which='minor', direction='in', bottom=True, top=True, left=True, right=True, length=2) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    
    ax1.set_xlabel("Time [sec]\nFig 2.  0.1 Hz sin, cos and -cos wave sampled by 10 Hz, 0-60 sec.")
    ax1.set_xlim(0-1, 60+1)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude")
    ax1.set_ylim(-1.1, 1.1)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(0.5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(0.1))

    plt.legend(loc='best')
    plt.savefig(writeName, bbox_inches="tight") # , dpi=100

#--------------------------------------------------------------------------------------------------------

from PIL import Image
from io import BytesIO
def imgPath2mat_rRGB(path):
    imgRaw =Image.open(path)
    imgRGB = imgRaw.split()
    imgR = imgRGB[0]
    imgG = imgRGB[1]
    imgB = imgRGB[2]
    return (imgR, imgG, imgB)
def mat_rRGB2img(path, imgR, imgG, imgB):
    imgCombined = np.dstack((np.dstack((imgR, imgG)), imgB))
    imgPIL      = Image.fromarray(imgCombined)
    imgPIL.save(path)

#--------------------------------------------------------------------------------------------------------
