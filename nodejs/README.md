* [����˵��](#����˵��)
  * [lame.js](#lame.js)
  * [lame.scanner.js](#lame.scanner.js)
  * [lame.sample.js](#lame.sample.js)

# ����˵��
___
- **lame.js**
>ʹ��nodejs��װ��ɨ����ӿڡ�
- **lame.scanner.js**
>����lame.jsʹ��nodejs��װ��һ�����Ӽ򵥵�ɨ�����ӿڡ�
- **lame.sample.js**
>ʹ��lame.scanner.js�ļ�ʾ����



## lame.js
___

����C��̬�Ⲣ��ȡ�ӿں����б�
```javascript
var node_lame = require('./build/release/node_lame');
```

��ȡ�汾��Ϣ����
```javascript
lame.prototype.GetVersionInfo();
lame.prototype.GetLicenceInfo();
````

�����������(���ء��ͷ�)
```javascript
lame.prototype.OpenVdb(vlib);
lame.prototype.CloseVdb();
```

���ļ�����
```javascript
lame.prototype.ExtractFile(filename, password, enter_file, leave_file, userdata);
lame.prototype.Extract_GetSize(handle);
lame.prototype.Extract_Seek(handle, offset, method);
lame.prototype.Extract_Tell(handle);
lame.prototype.Extract_Read(handle, size);
```

�������ɨ���ļ���
```javascript
lame.prototype.Load();
lame.prototype.SetParameters(param);
lame.prototype.Unload();
lame.prototype.ScanFile(path);
lame.prototype.ScanMem(data, size);
lame.prototype.ScanFileWithCallback(path, enter_file, leave_file, alarm, userdata);
lame.prototype.ScanMemWithCallback(data, size, enter_file, leave_file, alarm, userdata);
```

## lame.scanner.js
___

��װ��ɨ��ӿ���
```javascript
Scanner.prototype.Load()
Scanner.prototype.Unload();
Scanner.prototype.ScanFile(filepath);
Scanner.prototype.ScanFileWithCallback(filepath);
Scanner.prototype.ScanMem(data, size);
Scanner.prototype.ScanMemWithCallback(data, size, enter_file, leave_file, alarm, userdata);
Scanner.prototype.ShowVersion();
Scanner.prototype.ShowLicence();
```

��װ�Ľ���ӿ���
```javascript
Scanner.prototype.ExtractFile(filename, password, enter_file, leave_file, userdata);
Scanner.prototype.ExtGetSize(handle);
Scanner.prototype.ExtSeek(handle, offset, method);
Scanner.prototype.ExtTell(handle);
Scanner.prototype.ExtRead(handle, size);
```

## lame.sample.js
___

��ʾ������
```javascript
'use strict';
var fs = require('fs');

var Scanner = require('./lame.scanner.js');

var LSCT_CONTINUE = 1;
var LSCT_ABORT = 2;

var LCT_CONTINUE = 1;
var LCT_DO_EXTRACT = 2;
var LCT_ABORT = 3;

function scan_enter_file(filename, depth, userdata) {
	return LSCT_CONTINUE;
}

function scan_leave_file(filename, depth, userdata, l) {

}

function scan_alarm(filename, info, userdata) {
	if (null != info) {
		console.warn(target + '\tInfected: ' + info.vname);
	} else {
		console.log(target);
	}
	return LSCT_CONTINUE;
}

function extract_enter_file(filename, format, depth, FCLS, handle, userdata) {
	var scanner = userdata;
	if (null != handle) {
		var size = scanner.ExtGetSize(handle);
		scanner.ExtSeek(handle, 0, 0);
		var data = scanner.ExtRead(handle, size);
		console.log(data);
	}
	return LCT_CONTINUE;
}

function extract_leave_file(filename, format, depth, FCLS, handle, userdata, l) {
	console.log(filename + ' format: ' + format);
}

function GetVersion() {
	var scanner = new Scanner();
	scanner.ShowVersion();
	scanner.ShowLicence();
}

function DetectFile(path, flag) {
	var scanner = new Scanner();
	if (scanner.Load()) {
		if (flag) {
			scanner.ScanFile(path);
		} else {
			scanner.ScanFileWithCallback(path, scan_enter_file, scan_leave_file, scan_alarm, "filescan_callbck");
		}
		scanner.Unload();
	}
}

function DetectMemory(data, size, flag) {
	var scanner = new Scanner();
	if (scanner.Load()) {
		if (flag) {
			scanner.ScanMem(data, size);
		} else {
			scanner.ScanMemWithCallback(data, data.length, scan_enter_file, scan_leave_file, scan_alarm, "memscan_callbck");
		}
		scanner.Unload();
	}
}

function Extract(path) {
	var scanner = new Scanner();
	if (scanner.Load()) {
		scanner.ExtractFile(path, "", extract_enter_file, extract_leave_file, scanner);
		scanner.Unload();
	}
}

function main() {
	GetVersion();

	// extract
	Extract('d:/rsdata/5/5.zip');

	// file
	DetectFile('d:/rsdata/5/3949568_22900584_MYGL.exe.###', false);

	// memory
	var data = fs.readFileSync('d:/rsdata/5/3949568_22900584_MYGL.exe.###');
	DetectMemory(data, size, false);
}

// main
console.log("--------------- test start ---------------");
main();
console.log("--------------- test end -----------------");
```
