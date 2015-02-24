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
//  AAKeyboardNotification.h
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, AAKeyboardNotificationType) {
  AAKeyboardWillShow = 1,
  AAKeyboardWillHide = 1 << 1,
  AAKeyboardDidShow = 1 << 2,
  AAKeyboardDidHide = 1 << 3
};

@interface AAKeyboardNotification : NSObject

@property(assign, nonatomic, readonly) CGRect oldFrame;
@property(assign, nonatomic, readonly) CGRect newFrame;
@property(assign, nonatomic, readonly) AAKeyboardNotificationType type;

+ (instancetype)notificationWithOldFrame:(CGRect)oldFrame
                                newFrame:(CGRect)newFrame
                                    type:(AAKeyboardNotificationType)type;

@end
