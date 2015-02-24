# AAKeyboardManager

[![CI Status](http://img.shields.io/travis/Anil Anar/AAKeyboardManager.svg?style=flat)](https://travis-ci.org/Anil Anar/AAKeyboardManager)
[![Version](https://img.shields.io/cocoapods/v/AAKeyboardManager.svg?style=flat)](http://cocoadocs.org/docsets/AAKeyboardManager)
[![License](https://img.shields.io/cocoapods/l/AAKeyboardManager.svg?style=flat)](http://cocoadocs.org/docsets/AAKeyboardManager)
[![Platform](https://img.shields.io/cocoapods/p/AAKeyboardManager.svg?style=flat)](http://cocoadocs.org/docsets/AAKeyboardManager)

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

Animates a constraint, modifying its `constant` property. 

-

`AAKeyboardManager::addFrameAnimator`

Animates a view frame, modifying its height.

-

`AAKeyboardManager::addScrollViewAnimator:` 

Animates a scroll view, modifying its content insets, scroll indicator insets and optionally content offset.

-

After initializing an animator, you can add it to your keyboard manager: `[keyboardManager addAnimator: someAnimator]`.

### Creating Custom Animators

There are currently two ways to create animators:

- Create a class that conforms to `AAKeyboardAnimator` and add it to your keyboard manager, see default animator classes in the source for examples. 

- Use `addAnimation:` method:

	```
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

