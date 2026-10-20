//
//  TBLogScope.h
//  TBLog
//

#import <Foundation/Foundation.h>
#import <TBLog/TBLogModel.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 单个模块（通常是一个 SDK）的日志作用域
 *
 * 多个接入方共用 TBLog 时，各自持有自己的 scope 和 logLevel，互不覆盖。
 * 是否真正输出由 TBLog 的总闸和该作用域的阈值共同决定，取更严的一个。
 */
@interface TBLogScope : NSObject

/// 模块名，日志输出时用于区分来源
@property (nonatomic, copy, readonly) NSString *moduleName;

/// 本模块的输出阈值，低于该等级的日志不输出；设为 TBLogLevelNone 关闭本模块全部日志
@property (nonatomic) TBLogLevel logLevel;

/// 指定模块名初始化，阈值默认为 TBLogLevelDebug
- (instancetype)initWithModuleName:(NSString *)moduleName;

- (instancetype)init NS_UNAVAILABLE;

/// 快捷日志输出，自动补齐模块名、时间戳、文件名和行号
/// @param level 当前日志等级
/// @param file 当前文件，传 __FILE__
/// @param line 当前行数，传 __LINE__
/// @param message 日志内容
- (void)logWithLevel:(TBLogLevel)level
                file:(const char *)file
                line:(int)line
             message:(NSString *)message;
@end

NS_ASSUME_NONNULL_END
