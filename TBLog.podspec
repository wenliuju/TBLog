Pod::Spec.new do |s|
  s.name             = 'TBLog'
  s.version          = '1.0.0'
  s.summary          = 'Shared iOS logging framework with per-module log scopes.'
  s.description      = <<-DESC
    TBLog 是公司内部共用的日志框架：各 SDK 通过 scopeForModule: 拿到自己的 TBLogScope，
    输出由 TBLog 总闸和该 scope 的阈值共同决定，多个接入方互不覆盖。
    本 pod 只提供编译好的静态 framework（真机 arm64 单 slice），不含源码。
  DESC

  s.homepage         = 'https://github.com/wenliuju/TBLog'
  # HTTPS：任何配了 GitHub 凭据的机器都能装；私有仓库要求本机已通过 keychain 或 PAT 认证
  s.source           = { :git => 'https://github.com/wenliuju/TBLog.git', :tag => s.version.to_s }
  s.license          = { :type => 'Proprietary', :text => '内部框架，仅限公司内部项目使用。' }
  # 发布者。头文件署名的原作者是 Sam（bundle id com.vimoto.TBLog），
  # 他的邮箱未确认，先不把猜测值写进元数据
  s.author           = { 'wenliuju' => '24311021+wenliuju@users.noreply.github.com' }

  s.ios.deployment_target = '15.0'
  s.static_framework      = true
  s.vendored_frameworks   = 'TBLog.framework'
end
