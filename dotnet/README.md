* [����˵��](#����˵��)
  * [lame.dotnet[core]](#lame.dotnet[core])
  * [lame.dotnet[core].scanner](#lame.dotnet[core].scanner)
  * [lame.dotnet[core].sample](#lame.dotnet[core].sample)


# ����˵��
___
- **lame.dotnet[core]**
>��������CתC#�Ľӿڡ�
- **lame.dotnet[core].scanner**
>��������C#��װ�Ľӿڣ�����lame.dotnet��װ��C#�ӿڷ�װ��Lame�๩�û�ʹ�á�
- **lame.dotnet[core].sample**
>�������ǲ����������룬����lame.dotnet��װ��C#�ӿڣ�ʹ�������ַ�ʽɨ���ļ���һ����ֱ��ɨ��һ����ʹ�ûص�����ɨ�衣



## lame.dotnet[core]
___

Lame��ɨ���ļ��ӿ��ࡣ
```c#
public class Lame : LameBase
{
	public LameScanResult ScanFile(string sFile);
	public LameScanResult ScanMem(byte[] bytes);
	public object Clone();
}
```

LameWithEvent�����ص�������ɨ���ļ��ӿ��ࡣ
```c#
public delegate void ScanInternalFileEvent(string fname, LameScanResult result);
public class LameWithEvent : LameBase
{
	public void ScanFile(string sFile);
	public void ScanMem(byte[] bytes);
	private void ScanInternalFile(string fname, IntPtr resp, IntPtr zero);
	public object Clone();
	private LameScanResult FetchResult(IntPtr resp);
}
```

VirusLib����������غ��ͷ���
```c#
public class VirusLib
{
	public bool lame_open_vdb(string vdbf);
	public void lame_close_vdb();
	public IntPtr vdb_handle;
}
```


## lame.dotnet[core].scanner
___

IScan��ɨ���ļ��ӿڻ���
```c#
internal interface IScan
{
	bool SetParam(string param);
	bool Load();
	void Scan(string path);
	IScan Clone();
	void ShowVersion();
	void ShowLicense();
	void UnLoad();
}
```

Scanner��ɨ������
```c#
internal class Scanner : IScan
{
	public Scanner(VirusLib vdb);
	public Scanner(Lame lame, VirusLib vdb);
	public bool SetParam(string param);
	public bool Load();
	public void Scan(string path);
	public IScan Clone();
	public void ShowVersion();
	public void ShowLicense();
	public void UnLoad();
}
```

ScannerEx�����ص�������ɨ������
```c#
class ScannerEx : IScan
{
	public ScannerEx(VirusLib vdb);
	public ScannerEx(LameWithEvent lame, VirusLib vdb);
	public bool SetParam(string param);
	public bool Load();
	public IScan Clone();
	public void Scan(string path);
	public void ShowVersion();
	public void ShowLicense();
	public void UnLoad();
}
```


## lame.dotnet[core].sample
___

ɨ����ʾ��
```c#
internal class Program
{
    private static void Main(string[] args)
    {
        if (args.Length == 0) return;

        var vdb = new VirusLib();
        if (!vdb.lame_open_vdb(null))
        {
            Console.WriteLine("Faild to load virus lib.");
            return;
        }

        LameTest(vdb, args[0]);

        LameWithEventTest(vdb, args[0]);

        vdb.lame_close_vdb();
    }

    private static void PrintScanResult(string path, LameScanResult result)
    {
        if (result == null) return;

        Console.Write(path);
        if (result != null) Console.Write("     Infected:" + result.VirusName + " (" + result.EngineID + ")");
        Console.WriteLine("");
    }

    private static void LameTest(VirusLib vdb, string path)
    {
        if (vdb == null) return;


        // 1. load
        var _lame = new Lame();
        if (!_lame.Load(vdb)) return;

        //2. scan
        if (File.Exists(path))
        {
            var _result = _lame.ScanFile(path);
            PrintScanResult(path, _result);
        }
        else if (Directory.Exists(path))
        {
            var files = Directory.GetFiles(path);
            foreach (var f in files)
            {
                var _result = _lame.ScanFile(f);
                PrintScanResult(f, _result);
            }
            //travel dir......
        }

        //3.
        _lame.Unload();
    }

    private static LSCT AlarmEventHandle(string file, LameScanResult result)
    {
        Console.ForegroundColor = ConsoleColor.Green;
        Console.Write(file);
        if (result != null)
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("     Infected:" + result.VirusName + " (" + result.EngineID + ")");
        }

        Console.WriteLine("");
        return LSCT.CONTINUE;
    }

    private static LSCT EnterFileEventHandle(string fname, uint depth)
    {
        return LSCT.CONTINUE;
    }

    private static void LeaveFileEventHandle(string fname, uint depth)
    {
    }

    private static void LameWithEventTest(VirusLib vdb, string path)
    {
        if (vdb == null) return;

        // 1. load
        var _lame = new LameWithEvent();
        _lame.EnterFileEvent = EnterFileEventHandle;
        _lame.LeaveFileEvent = LeaveFileEventHandle;
        _lame.AlarmEvent = AlarmEventHandle;

        if (!_lame.Load(vdb)) return;

        //2. scan
        if (File.Exists(path))
        {
            _lame.ScanFile(path);
        }
        else if (Directory.Exists(path))
        {
            var files = Directory.GetFiles(path);
            foreach (var f in files) _lame.ScanFile(f);

            //travel dir......
        }

        //3.
        _lame.Unload();
    }
}
```
