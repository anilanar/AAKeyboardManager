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
//  AAKeyboardManagerDelegate.h
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import <Foundation/Foundation.h>
#import "AAKeyboardNotification.h"

@class AAKeyboardManager;

/*!
 *  The delegate of a keyboard manager must adopt the @c
 *  AAKeyboardManagerDelegate protocol. These methods allow the delegate to
 *  receive notifications when the notification center emits the following
 *  keyboard events:
 *  <li>@c UIKeyboardWillShowNotification</li>
 *  <li>@c UIKeyboardWillHideNotification</li>
 *  <li>@c UIKeyboardDidShowNotification</li>
 *  <li>@c UIKeyboardDidHideNotification</li>
 *
 *  @since 0.1.0
 */
@protocol AAKeyboardManagerDelegate<NSObject>

/*!
 *  Called immediately prior to the display of the keyboard
 *
 *  @param keyboardManager The keyboard manager observing keyboard
 *  notifications.
 *
 *  @param notification    The notification object including information about
 *  the frame change.
 *
 *  @since 0.1.0
 */
- (void)keyboardManager:(AAKeyboardManager *)keyboardManager
               willShow:(AAKeyboardNotification *)notification;

/*!
 *  Called immediately prior to the dismissal of the keyboard
 *
 *  @param keyboardManager The keyboard manager observing keyboard
 *  notifications.
 *
 *  @param notification    The notification object including information about
 *  the frame change.
 *
 *  @since 0.1.0
 */
- (void)keyboardManager:(AAKeyboardManager *)keyboardManager
               willHide:(AAKeyboardNotification *)notification;

/*!
 *  Called immediately after the display of the keyboard
 *
 *  @param keyboardManager The keyboard manager observing keyboard
 *  notifications.
 *
 *  @param notification    The notification object including information about
 *  the frame change.
 *
 *  @since 0.1.0
 */
- (void)keyboardManager:(AAKeyboardManager *)keyboardManager
                didShow:(AAKeyboardNotification *)notification;

/*!
 *  Called immediately after the dismissal of the keyboard
 *
 *  @param keyboardManager The keyboard manager observing keyboard
 *  notifications.
 *
 *  @param notification    The notification object including information about
 *  the frame change.
 *
 *  @since 0.1.0
 */
- (void)keyboardManager:(AAKeyboardManager *)keyboardManager
                didHide:(AAKeyboardNotification *)notification;

/*!
 *  Called immediately prior to the display or dismissal of the keyboard
 *
 *  @param keyboardManager The keyboard manager observing keyboard
 *  notifications.
 *
 *  @param notification    The notification object including information about
 *  the frame change.
 *
 *  @since 0.1.0
 */
- (void)keyboardManager:(AAKeyboardManager *)keyboardManager
        willChangeFrame:(AAKeyboardNotification *)notification;

/*!
 *  Called immediately after the display or dismissal of the keyboard
 *
 *  @param keyboardManager The keyboard manager observing keyboard
 *  notifications.
 *
 *  @param notification    The notification object including information about
 *  the frame change.
 *
 *  @since 0.1.0
 */
- (void)keyboardManager:(AAKeyboardManager *)keyboardManager
         didChangeFrame:(AAKeyboardNotification *)notification;

@end
