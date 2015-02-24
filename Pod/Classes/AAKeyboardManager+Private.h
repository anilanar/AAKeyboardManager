//
//  Copyright (C) 2015 Anil Anar.
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//
//  AAKeyboardManager+Private.h
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import "AAKeyboardManager.h"

@interface AADefaultKeyboardAnimator : NSObject<AAKeyboardAnimator>

@property(copy, nonatomic) AAKeyboardAnimation animation;

- (instancetype)initWithAnimation:(void (^)(AAKeyboardNotification *))animation;
- (void)animateForNotification:(AAKeyboardNotification *)notification;

@end

@interface AAKeyboardNotification ()

@property(assign, nonatomic, readwrite) AAKeyboardNotificationType type;

@end

@interface AAKeyboardManager ()

+ (NSArray *)notifications;
+ (SEL)selectorForIndex:(NSUInteger)index;

- (void)addObserver:(NSString *)name selector:(SEL)selector;
- (void)removeObserver:(NSString *)name;
- (AAKeyboardNotification *)convertNotification:(NSNotification *)notification;
- (void)runAnimators:(NSNotification *)notification;

@end
