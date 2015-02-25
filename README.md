# AAKeyboardManager

[![CI Status](http://img.shields.io/travis/Anil Anar/AAKeyboardManager.svg?style=flat)](https://travis-ci.org/Anil Anar/AAKeyboardManager)
[![Version](https://img.shields.io/cocoapods/v/AAKeyboardManager.svg?style=flat)](http://cocoadocs.org/docsets/AAKeyboardManager)
[![License](https://img.shields.io/cocoapods/l/AAKeyboardManager.svg?style=flat)](http://cocoadocs.org/docsets/AAKeyboardManager)
[![Platform](https://img.shields.io/cocoapods/p/AAKeyboardManager.svg?style=flat)](http://cocoadocs.org/docsets/AAKeyboardManager)

`AAKeyboardManager` lets you manage the keyboard for iOS apps version `>7.1`. It introduces what's called animators that let you move up and down your views or content of scroll views when the keyboard displays or hides. It works well with rotations, hardware keyboard mode and undocking/splitting for iPad. It even lets your create your own custom animators if default ones won't meet your needs.

## AAKeyboardNotification

If you were to handle keyboard events yourself, you would register yourself as observer to `NSNotificationCenter` and handle incoming `NSNotification` objects. It has information about the keyboard animation, the begin frame and the new frame. One problem is, frames are in the coordinate system of the screen. The other is, height of the keyboard that is reported will always be the same even if it is displayed or dismissed.

`AAKeyboardNotification` converts them to the coordinate system of a reference view, and the height reported is for the region the keyboard covers in the reference view. `AAKeyboardNotification` converts frames into something more meaningful.


## Installation

AAKeyboardManager is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

    pod "AAKeyboardManager"
    
## Getting Started
	
`#import <AAKeyboardManager/AAKeyboardManager.h>`

There is a demo project with two examples: one with a regular view and the other with a scroll view both using `AutoLayout`. To run the example project, clone the repo, and run `pod install` from the Example directory first.

### Animating `UIScrollView`
If you want to animate scroll views and its subclasses such as `UICollectionView`, see `AAScrollViewController` in the demo project.

### Animating `UIView`
If you want to animate regular views, see `AAViewController` in the demo project.

### Using Default Animators

There are currenty three default animators:

-
`AAKeyboardManager::addConstraintAnimator:`

Animates a constraint, modifying its `constant` property. One would typically use this if `AutoLayout` is used.

-

`AAKeyboardManager::addFrameAnimator`

Animates a view frame, modifying its height. One would typically use this if `AutoLayout` isn't used.

-

`AAKeyboardManager::addScrollViewAnimator:` 

Animates a scroll view, modifying its content insets, scroll indicator insets and optionally content offset.

-

### Creating Custom Animators

There are currently two ways to create animators:

- Create a class that conforms to `AAKeyboardAnimator`.

- Use `addAnimation:` method:

	```
	// An example of animating a frame
	__weak typeof(self) weakSelf = self;
	[keyboardManager addAnimation: ^(AAKeyboardNotification *notification) {
	  CGRect frame = weakSelf.myView.frame;
	  CGFloat keyboardHeight = notification.newFrame.size.height;
	  if(notification.type == AAKeyboardWillShow)
	    frame.size.height -= keyboardHeight;
	  else if(notification.type == AAKeyboardWillHide)
	    frame.size.height += keyboardHeight;
	}
	```

## Author

Anıl Anar

## License

AAKeyboardManager is available under the MIT license. See the LICENSE file for more info.

