//
//  TBLogModel.h
//  TBLog
//
//  Created by Sam on 2026/10/19.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 日志等级，数值越大越严重；作为输出阈值时，低于阈值的日志会被丢弃
 * TBLogLevelNone 不是真实等级，仅用于关闭全部日志输出
 */
typedef NS_ENUM(NSInteger, TBLogLevel) {
    TBLogLevelDebug,
    TBLogLevelInfo,
    TBLogLevelWarning,
    TBLogLevelError,
    TBLogLevelNone
};


@interface TBLogEntry : NSObject
/// 模块
@property (nonatomic, readonly, copy) NSString *type;
/// 时间戳
@property (nonatomic, readonly, strong) NSDate *timestamp;
/// 日志等级
@property (nonatomic, readonly, assign) TBLogLevel level;
/// 类名
@property (nonatomic, readonly, copy) NSString *className;
/// 代码行号
@property (nonatomic, readonly, assign) NSInteger lineNumber;
/// 日志内容
@property (nonatomic, readonly, copy) NSString *message;


/// 构造器
- (instancetype)initWithType:(NSString *)type
                   timestamp:(NSDate *)timestamp
                       level:(TBLogLevel)level
                   className:(NSString *)className
                  lineNumber:(NSInteger)lineNumber
                     message:(NSString *)message;
@end



@interface TBLogModel : NSObject

@end

NS_ASSUME_NONNULL_END
