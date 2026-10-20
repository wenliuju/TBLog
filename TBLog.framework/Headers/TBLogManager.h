//
//  TBLogManager.h
//  
//
//  Created by Sam on 2026/10/19.
//

#import <Foundation/Foundation.h>
#import <TBLog/TBLogModel.h>
#import <TBLog/TBLogScope.h>

NS_ASSUME_NONNULL_BEGIN

@interface TBLogManager : NSObject

/// 单例初始化
+ (TBLogManager *)shareInstance;

/// TBLog 总闸阈值，和各模块自己的阈值取更严的一个；设为 TBLogLevelNone 关闭全部日志
@property (nonatomic) TBLogLevel logLevel;

/// 获取模块的日志作用域，同名返回同一个实例
/// @param moduleName 模块名，一般用一个 SDK 的名字
- (TBLogScope *)scopeForModule:(NSString *)moduleName;

///  日志打印
/// - Parameter log: 日志信息
+ (void)printTheLog:(TBLogEntry *)log;
@end

NS_ASSUME_NONNULL_END
