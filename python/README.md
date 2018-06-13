* [����˵��](#����˵��)
  * [lame.py](#lame.py)
  * [lame.scanner.py](#lame.scanner.py)
  * [lame.sample.py](#lame.sample.py)

# ����˵��
___
- **lame.py**
>ʹ��python��װ��ɨ����ӿڣ����û�ֱ���ṩ��
- **lame.scanner.py**
>ʹ��lame.py�ӿ�д��һ��ɨ��������ֱ��ʹ��ɨ���ļ���
- **lame.sample.py**
>ʹ��lame.py�ļ�ʾ�������û��ṩ��



## lame.py
___

�����������(���ء��ͷ�)
```python
class VirusDb:
	def __init__(self , lpath);
	def OpenVdb(self,vdbf);
	def CloseVdb(self);
	def GetVbdHandle(self);
```

�����ص�������ɨ����
```python	
class Lame(LameBase):
	def __init__(self , lpath);
	def ScanFile(self,fname);
	def ScanMem(self, data);
	def Clone(self);
```

���ص�������ɨ����
```python
CMPFUNC = WINFUNCTYPE(None,c_char_p, POINTER(LameScanResult),c_void_p) 
def LameCallback(fname , result , userdata);

class LameWithFeedback(LameBase):
	def __init__(self , lpath);
	def SetCallack(self,cb);
	def Report(self , fname , result);
	def ScanFile(self,fname);
	def ScanMem(self, data );
	def Clone(self);
```


## lame.scanner.py
___

�����ص�������ɨ����
```python
class LameScanner:
    def __init__(self , lpath);
    def Load(self , vdb);
    def SetParam(self , param);
    def Scan(self , path_);
    def Unload(self);
    def ShowLicense(self);
    def ShowVersion(self);
```

���ص�������ɨ����
```python
class LameScanner2:
    def __init__(self , lpath);
    def Load(self , vdb);
    def SetParam(self , param);
    def Unload(self);
    def ShowLicense(self);
    def ShowVersion(self);
    def Scan(self , path_);
```


## lame.sample.py
___

��ʾ������
```python
def PrintLameScanResult(fname , result):
    sys.stdout.write(fname)
    if result is not None:
        sys.stdout.write(" " + "  Infected: " + result.vname + " (" + result.engid+")")
    sys.stdout.write("\n")

def lame_test(dbf , path):
    _lame = Lame(LAME_PATH)
    #_lame.SetParam("kill")
    if not _lame.Load(dbf):
        return
    _license = _lame.GetLicense()
    if _license is not None:
        print("License:")
        print("     Version: " + _license.version)
        print("     Owner  : " + _license.Owner)
        print("     Date   : " + _license.Data)
        print("     Authm  : " + _license.Authm)
    _version = _lame.GetVersion()
    if _version is not None: 
        print("Engine Version    :" + _version.engv)
        print("Viruse Lib Version: " + _version.vdbv)
    print(path)
    if os.path.isfile(path) :
        _result = _lame.ScanFile(path)
        PrintLameScanResult(path  , _result)
    else:
        for dirpath,dirnames,filenames in os.walk(path):
            for file in filenames:
                fullpath=os.path.join(dirpath,file)
                _result = _lame.ScanFile(fullpath)
                PrintLameScanResult(fullpath  , _result)
    _lame.Unload()

def LameCallBack(fname , result):
    sys.stdout.write(fname)
    if result is not None:
        sys.stdout.write(" " + "  Infected: " + result.vname + " (" + result.engid+")")
    sys.stdout.write("\n")

def lame_with_feedback_test(dbf , path):
    if dbf is None:
        return
    _lame = LameWithFeedback(LAME_PATH)
    _lame.SetCallack(LameCallBack)
    #_lame.SetParam("kill")
    if not _lame.Load(dbf):
        return
    _license = _lame.GetLicense()
    if _license is not None:
        print("License:")
        print("     Version: " + _license.version)
        print("     Owner  : " + _license.Owner)
        print("     Date   : " + _license.Data)
        print("     Authm  : " + _license.Authm)
    _version = _lame.GetVersion()
    if _version is not None: 
        print("Engine Version    :" + _version.engv)
        print("Viruse Lib Version: " + _version.vdbv)

    if os.path.isfile(path) :
        _lame.ScanFile(path)
    else:
        for dirpath,dirnames,filenames in os.walk(path):
            for file in filenames:
                fullpath=os.path.join(dirpath,file)
                _lame.ScanFile(fullpath)
    _lame.Unload()

```
