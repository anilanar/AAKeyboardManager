Pod::Spec.new do |s|
  s.name             = "AAKeyboardManager"
  s.version          = "0.1.0"
  s.summary          = "Keyboard manager for quickly integrating animations"
  s.homepage         = "https://github.com/anilanar/AAKeyboardManager"
  s.license          = 'MIT'
  s.author           = { "Anıl Anar" => "anilanar@hotmail.com" }
  s.source           = { :git => "https://github.com/anilanar/AAKeyboardManager.git", :tag => s.version.to_s }
  s.platform     = :ios, '7.1'
  s.requires_arc = true
  s.source_files = 'Pod/Classes/**/*'
  s.frameworks = 'UIKit', 'Foundation'
end
