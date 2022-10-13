# gh0st_remote
gh0st远控复现，可通过文件夹包含的库选择是否调用制定目标进行远控的功能添加、删改。

***本示例在实现时使用VS2015与VS2017开发，VS2017可能无法完全执行实现示例所有功能，且由于时间久远，在文件上传时未经过完整性检查，请参照文件内已命名为“2015Remote”的资源列表文件和导入项目文件自行进行检查***  

## 功能列表示例  
***下图为“注册表管理”与“屏幕管理”功能**  
![212](https://github.com/funkpopo/gh0st_remote/blob/main/functions-image1.png)

## 项目结构
<details>
<summary>项目结构</summary>

```
.
├── client
│   ├── Audio.cpp
│   ├── Audio.h
│   ├── AudioManager.cpp
│   ├── AudioManager.h
│   ├── Buffer.cpp
│   ├── Buffer.h
│   ├── CaptureVideo.cpp
│   ├── CaptureVideo.h
│   ├── ClientDll.cpp
│   ├── ClientDll.sln
│   ├── ClientDll.vcxproj
│   ├── ClientDll.vcxproj.filters
│   ├── ClientDll.vcxproj.user
│   ├── ClientDll_vs2015.vcxproj
│   ├── ClientDll_vs2015.vcxproj.user
│   ├── Common.cpp
│   ├── Common.h
│   ├── CursorInfo.h
│   ├── d3drmdef.h
│   ├── d3drm.h
│   ├── d3drmobj.h
│   ├── dxtrans.h
│   ├── ExportFunTable.def
│   ├── FileManager.cpp
│   ├── FileManager.h
│   ├── ghost.vcxproj
│   ├── ghost.vcxproj.filters
│   ├── ghost.vcxproj.user
│   ├── ghost_vs2015.vcxproj
│   ├── ghost_vs2015.vcxproj.user
│   ├── IOCPClient.cpp
│   ├── IOCPClient.h
│   ├── KernelManager.cpp
│   ├── KernelManager.h
│   ├── LoginServer.cpp
│   ├── LoginServer.h
│   ├── lz4
│   │   ├── lz4.h
│   │   └── lz4.lib
│   ├── Manager.cpp
│   ├── Manager.h
│   ├── qedit.h
│   ├── RegisterManager.cpp
│   ├── RegisterManager.h
│   ├── RegisterOperation.cpp
│   ├── RegisterOperation.h
│   ├── remote.ini
│   ├── Res
│   │   ├── ghost.ico
│   │   ├── msg.ico
│   │   └── msg.wav
│   ├── resource1.h
│   ├── resource.h
│   ├── ScreenManager.cpp
│   ├── ScreenManager.h
│   ├── ScreenSpy.cpp
│   ├── ScreenSpy.h
│   ├── Script.aps
│   ├── Script.rc
│   ├── ServicesManager.cpp
│   ├── ServicesManager.h
│   ├── ShellManager.cpp
│   ├── ShellManager.h
│   ├── StdAfx.cpp
│   ├── StdAfx.h
│   ├── SystemManager.cpp
│   ├── SystemManager.h
│   ├── TalkManager.cpp
│   ├── TalkManager.h
│   ├── test.cpp
│   ├── TestRun.rc
│   ├── TestRun.vcxproj
│   ├── TestRun.vcxproj.filters
│   ├── TestRun.vcxproj.user
│   ├── TestRun_vs2015.vcxproj
│   ├── TestRun_vs2015.vcxproj.user
│   ├── VideoCodec.h
│   ├── VideoManager.cpp
│   ├── VideoManager.h
│   ├── zconf.h
│   ├── zlib.h
│   ├── zlib.lib
│   └── zstd
│       ├── zstd.h
│       └── zstd.lib
├── functions-image1.png
├── .git
│   ├── branches
│   ├── config
│   ├── description
│   ├── HEAD
│   ├── hooks
│   │   ├── applypatch-msg.sample
│   │   ├── commit-msg.sample
│   │   ├── fsmonitor-watchman.sample
│   │   ├── post-update.sample
│   │   ├── pre-applypatch.sample
│   │   ├── pre-commit.sample
│   │   ├── pre-merge-commit.sample
│   │   ├── prepare-commit-msg.sample
│   │   ├── pre-push.sample
│   │   ├── pre-rebase.sample
│   │   ├── pre-receive.sample
│   │   ├── push-to-checkout.sample
│   │   └── update.sample
│   ├── index
│   ├── info
│   │   └── exclude
│   ├── logs
│   │   ├── HEAD
│   │   └── refs
│   │       ├── heads
│   │       │   └── main
│   │       └── remotes
│   │           └── origin
│   │               └── HEAD
│   ├── objects
│   │   ├── info
│   │   └── pack
│   │       ├── pack-2a6f26066c482086c5d7d52256e0b00da9968f11.idx
│   │       └── pack-2a6f26066c482086c5d7d52256e0b00da9968f11.pack
│   ├── packed-refs
│   └── refs
│       ├── heads
│       │   └── main
│       ├── remotes
│       │   └── origin
│       │       └── HEAD
│       └── tags
├── LICENSE
├── README.md
├── Remote.sln
└── server
    ├── Remote
    │   ├── 2015Remote.aps
    │   ├── 2015Remote.rc
    │   ├── Audio.cpp
    │   ├── AudioDlg.cpp
    │   ├── AudioDlg.h
    │   ├── Audio.h
    │   ├── Buffer.cpp
    │   ├── Buffer.h
    │   ├── BuildDlg.cpp
    │   ├── BuildDlg.h
    │   ├── CpuUseage.cpp
    │   ├── CpuUseage.h
    │   ├── EditDialog.cpp
    │   ├── EditDialog.h
    │   ├── FileManagerDlg.cpp
    │   ├── FileManagerDlg.h
    │   ├── FileTransferModeDlg.cpp
    │   ├── FileTransferModeDlg.h
    │   ├── gh0st2Remote.h
    │   ├── iniFile.cpp
    │   ├── iniFile.h
    │   ├── InputDlg.cpp
    │   ├── InputDlg.h
    │   ├── IOCPServer.cpp
    │   ├── IOCPServer.h
    │   ├── lz4
    │   │   ├── lz4.h
    │   │   └── lz4.lib
    │   ├── RegisterDlg.cpp
    │   ├── RegisterDlg.h
    │   ├── RemoteTool.aps
    │   ├── RemoteTool.cpp
    │   ├── RemoteToolDlg.cpp
    │   ├── RemoteToolDlg.h
    │   ├── RemoteTool.h
    │   ├── RemoteTool.sln
    │   ├── RemoteTool.vcxproj
    │   ├── RemoteTool.vcxproj.filters
    │   ├── RemoteTool.vcxproj.user
    │   ├── RemoteTool_vs2019.vcxproj
    │   ├── RemoteTool_vs2019.vcxproj.user
    │   ├── res
    │   │   ├── 1.cur
    │   │   ├── 2.cur
    │   │   ├── 3.cur
    │   │   ├── 4.cur
    │   │   ├── arrow.cur
    │   │   ├── audio.ico
    │   │   ├── Bitmap
    │   │   │   ├── bmp00001.bmp
    │   │   │   ├── Online.bmp
    │   │   │   ├── toolbar1.bmp
    │   │   │   ├── ToolBar_File.bmp
    │   │   │   └── ToolBar_Main.bmp
    │   │   ├── Bitmap_4.bmp
    │   │   ├── Bitmap_5.bmp
    │   │   ├── cmdshell.ico
    │   │   ├── Cur
    │   │   │   ├── Drag.cur
    │   │   │   └── MutiDrag.cur
    │   │   ├── dot.cur
    │   │   ├── dword.ico
    │   │   ├── file.ico
    │   │   ├── gh0st.ico
    │   │   ├── gh0st.rc2
    │   │   ├── keyboard.ico
    │   │   ├── MyRemote.rc2
    │   │   ├── pc.ico
    │   │   ├── Remote.ico
    │   │   ├── string.ico
    │   │   ├── system.ico
    │   │   ├── toolbar1.bmp
    │   │   ├── toolbar2.bmp
    │   │   └── webcam.ico
    │   ├── resource.h
    │   ├── ScreenSpyDlg.cpp
    │   ├── ScreenSpyDlg.h
    │   ├── ServicesDlg.cpp
    │   ├── ServicesDlg.h
    │   ├── SettingDlg.cpp
    │   ├── SettingDlg.h
    │   ├── ShellDlg.cpp
    │   ├── ShellDlg.h
    │   ├── stdafx.cpp
    │   ├── stdafx.h
    │   ├── SystemDlg.cpp
    │   ├── SystemDlg.h
    │   ├── TalkDlg.cpp
    │   ├── TalkDlg.h
    │   ├── targetver.h
    │   ├── TrueColorToolBar.cpp
    │   ├── TrueColorToolBar.h
    │   ├── VideoDlg.cpp
    │   ├── VideoDlg.h
    │   ├── zconf.h
    │   ├── zlib.h
    │   ├── zlib.lib
    │   └── zstd
    │       ├── zstd.h
    │       └── zstd.lib
    └── Remote.sln
```
</details>