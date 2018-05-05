import numpy as np
 
def listAppend_builtIn(rhs): rhs.append(123);        print(rhs, id(rhs))
def listAppend_ndarray(rhs): rhs=np.append(rhs,123); print(rhs, id(rhs))
def listAppend_builtIn_ndarray(rhs): rhs[0]=np.append(rhs[0],123); print(rhs[0], id(rhs[0]))

def listChar(rhs): rhs[0]='9'; rhs.append('D'); print(rhs, id(rhs))

def main():
 
    print("1. -- List (built in type) ---------")
    arr=[1, 2, 3];           print(arr, id(arr))
    listAppend_builtIn(arr); print(arr, id(arr))
    print()
 
    print("2. -- List (ndarray type) ---------")
    npArr=np.array([1, 2, 3]); print(npArr, id(npArr))
    listAppend_ndarray(npArr); print(npArr, id(npArr))
    print()
 
    print("3. -- List (ndarray type) ---------")
    npArr=[np.array([1, 2, 3])]; print(npArr, id(npArr))
    listAppend_builtIn_ndarray(npArr); print(npArr, id(npArr))
 
    print("4. -- ListChar ---------")
    lhs=['a', 'b', 'c',]; print(lhs, id(lhs))
    listChar(lhs); print(lhs, id(lhs))
 
main()
