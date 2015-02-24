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
//  AAKeyboardAnimator.h
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//
#import <Foundation/Foundation.h>
#import "AAKeyboardNotification.h"

/*!
 *  An animation block to be run when a keyboard notification event is emitted.
 *
 *  @param AAKeyboardNotification An object that provides information on the
 *notification
 *  such as old frame, new frame and notification type.
 *
 *  @since 0.1.0
 */
typedef void (^AAKeyboardAnimation)(AAKeyboardNotification*);

/*!
 *  The @c AAKeyboardAnimator protocol defines an animation to be run given a
 *keyboard
 *  notification.
 *
 *  @since 0.1.0
 */
@protocol AAKeyboardAnimator<NSObject>

/*!
 *  When overridden, this should define an animation to be run given the
 *keyboard
 *  notification.
 *
 *  @param notification The keyboard notification.
 *
 *  @since 0.1.0
 */
- (void)animateForNotification:(AAKeyboardNotification*)notification;

@end
