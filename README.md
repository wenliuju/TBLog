# TBLog

日志打印。公司内部共用的 iOS 日志框架，**以编译好的静态 framework 形式分发**（本仓库不含 TBLog 源码，源码在框架作者那边）。

## 这是什么

- `TBLog.framework`：静态 framework，`ar` archive + `Headers/` + `Modules/module.modulemap`。
- 只有 **真机 arm64 单 slice**（`LC_BUILD_VERSION platform = iOS`，MinimumOSVersion 15.0）。**没有模拟器 slice**，模拟器工程链接它会报
  `building for 'iOS-simulator', but linking in object file ... built for 'iOS'`。需要模拟器就在源码工程里补一个 slice 打成 xcframework 再发新版。

## 接口

```objc
#import <TBLog/TBLog.h>

TBLogScope *scope = [[TBLogManager shareInstance] scopeForModule:@"DDWebKit"];
[scope logWithLevel:TBLogLevelWarning file:__FILE__ line:__LINE__ message:@"..."];
```

- 等级：`TBLogLevelDebug < Info < Warning < Error`，`TBLogLevelNone` 只用于关闭输出。
- 是否输出由两级阈值共同决定，取更严的那个：`TBLogManager.shareInstance.logLevel` 是总闸，`scope.logLevel` 是模块阈值。
- `scopeForModule:` 同名返回同一个实例，所以各 SDK 把 scope 做成 `static inline` 函数也不会产生多份状态。
- 多个接入方各持自己的 scope 和阈值，互不覆盖 —— 这是它替代「每个 SDK 自己写一套 DDWebLogger」的原因。
- 一条日志的字段：模块名（`type`）、时间戳、等级、类名（由 `__FILE__` 推导）、行号、正文。没有方法名，`logWithLevel:` 不收 `__func__`。

## 接入

```ruby
pod 'TBLog', '~> 1.0'          # 从私有 Spec 仓库装（需要先 pod repo add）
```

没有 Spec 仓库时直接从 git 装，`podspec` 里的 `s.source` 用的是 HTTPS（私有仓库要求本机已配好 GitHub 凭据；习惯用 SSH key 的就在 Podfile 里覆盖成 `git@github.com:wenliuju/TBLog.git`）：

```ruby
pod 'TBLog', :git => 'https://github.com/wenliuju/TBLog.git', :tag => '1.0.0'
```

`vendored_frameworks` 是静态库，链接方需要 `-ObjC`；CocoaPods 装的话它自己会把 framework 加进 `OTHER_LDFLAGS`，手动拖 framework 的工程要注意这点。

## 发新版

framework 是二进制产物，每次更新都要替换文件、改 `TBLog.podspec` 的 `s.version`，然后**打 tag 一起推**（`s.source` 认的是 tag，只推分支消费方装不到）：

```sh
cp -R <新构建目录>/TBLog.framework .
vim TBLog.podspec              # 改 s.version
git add -A && git commit -m "TBLog 1.0.1"
git tag 1.0.1
git push origin main --follow-tags
```

发到私有 Spec 仓库（假设 spec 仓库是 `wenliuju/Specs`）：

```sh
pod repo add myspecs https://github.com/wenliuju/Specs.git
pod repo push myspecs TBLog.podspec \
  --sources='https://github.com/wenliuju/Specs.git,https://cdn.cocoapods.org/' \
  --allow-warnings --skip-import-validation
```

`--skip-import-validation` 是必需的：lint 默认拿 iphonesimulator 建 stub 去 import+链接，而本框架只有真机 slice，不跳就会失败。

## 校验产物

```sh
lipo -info TBLog.framework/TBLog                                  # arm64
otool -l TBLog.framework/TBLog | grep -A1 LC_BUILD_VERSION        # platform 2 = iOS 真机
nm -gU TBLog.framework/TBLog | grep OBJC_CLASS                    # TBLogManager / Scope / Entry / Model
```
