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
//  AAViewController.m
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import "AAViewController.h"
#import <AAKeyboardManager/AAKeyboardManager.h>

@interface AAViewController ()

@property(weak, nonatomic) IBOutlet UIView *contentView;
@property(weak, nonatomic) IBOutlet UITextField *textField;
@property(strong, nonatomic) AAKeyboardManager *keyboardManager;
@property(weak, nonatomic) IBOutlet NSLayoutConstraint *bottomMarginConstraint;

@end

@implementation AAViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  self.bottomMarginConstraint.constant = 0.0;
  self.keyboardManager =
    [[AAKeyboardManager alloc] initWithReferenceView:self.contentView];

  [self.keyboardManager addConstraintAnimator:self.bottomMarginConstraint
                                   isInverted:YES];

  [self.keyboardManager start];
}

- (void)viewWillAppear:(BOOL)animated {
  [super viewWillAppear:animated];
  [self.keyboardManager resume];
}

- (void)viewWillDisappear:(BOOL)animated {
  [super viewWillDisappear:animated];
  [self.keyboardManager pause];
}

- (void)dealloc {
  [self.keyboardManager stop];
}

- (IBAction)onTap:(id)sender {
  [self.textField resignFirstResponder];
}

@end
