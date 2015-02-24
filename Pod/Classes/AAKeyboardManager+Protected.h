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
//  AAKeyboardManager+Protected.h
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import "AAKeyboardManager.h"

@interface AAKeyboardManager ()

@property(strong, nonatomic) NSMutableArray *mutableAnimators;

/*!
 *  @brief A Boolean value specifying whether keyboard is visible or not.
 *
 *  @discussion Default value is @c NO. This will not represent keyboard
 *  visibility accruately in the following cases:
 *  <li>after @c -start is called until first keyboard notification is
 *  emitted.</li>
 *  <li>after @c -stop is called.</li>
 *
 *  @since 0.1.0
 */
@property(assign, nonatomic, readwrite, getter=isKeyboardVisible)
  BOOL keyboardVisible;
@property(assign, nonatomic, getter=isStarted) BOOL started;
@property(assign, nonatomic, getter=isPaused) BOOL paused;
@property(assign, nonatomic, getter=isStopped) BOOL stopped;

- (void)willShow:(NSNotification *)notification;
- (void)willHide:(NSNotification *)notification;
- (void)didShow:(NSNotification *)notification;
- (void)didHide:(NSNotification *)notification;

@end
