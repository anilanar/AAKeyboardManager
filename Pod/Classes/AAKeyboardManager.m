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
//  AAKeyboardManager.m
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import "AAKeyboardManager.h"
#import "AAKeyboardManager+Protected.h"
#import "AAKeyboardManager+Private.h"

#pragma mark - AADefaultKeyboardAnimator
@implementation AADefaultKeyboardAnimator

- (instancetype)initWithAnimation:(AAKeyboardAnimation)animation {
  self = [super init];
  if (self) {
    _animation = animation;
  }
  return self;
}

- (void)animateForNotification:(AAKeyboardNotification *)notification {
  self.animation(notification);
}

@end

#pragma mark - AAKeyboardManager
@implementation AAKeyboardManager

static NSArray *KB_NOTIFICATIONS;

#pragma mark - Class methods
+ (NSArray *)notifications {
  if (!KB_NOTIFICATIONS) {
    KB_NOTIFICATIONS =
      [[NSArray alloc] initWithObjects:UIKeyboardWillShowNotification,
                                       UIKeyboardWillHideNotification,
                                       UIKeyboardDidShowNotification,
                                       UIKeyboardDidHideNotification, nil];
  }
  return KB_NOTIFICATIONS;
}

+ (SEL)selectorForIndex:(NSUInteger)index {
  switch (index) {
    case 0:
      return @selector(willShow:);

    case 1:
      return @selector(willHide:);

    case 2:
      return @selector(didShow:);

    default:
      return @selector(didHide:);
  }
}

#pragma mark - Init methods
- (instancetype)init {
  return [self initWithReferenceView:nil];
}

- (instancetype)initWithReferenceView:(UIView *)referenceView {
  self = [super init];
  if (self) {
    _referenceView = referenceView;
    _mutableAnimators = [[NSMutableArray alloc] init];
    _delegate = nil;
    _keyboardVisible = NO;
    _started = NO;
    _paused = NO;
    _stopped = NO;
  }
  return self;
}

#pragma mark - Public methods
- (NSArray *)animators {
  return [[NSArray alloc] initWithArray:self.mutableAnimators];
}

- (void)start {
  assert(![self isStarted]);
  assert(![self isStopped]);

  self.started = YES;
  self.paused = YES;
}

- (void)stop {
  assert([self isStarted]);
  assert(![self isStopped]);

  if (![self isPaused]) {
    [self pause];
  }

  self.stopped = YES;
}

- (void)resume {
  assert([self isStarted]);
  assert([self isPaused]);
  for (NSUInteger i = 0; i < AAKeyboardManager.notifications.count; ++i) {
    [self addObserver:AAKeyboardManager.notifications[i]
             selector:[AAKeyboardManager selectorForIndex:i]];
  }

  self.paused = NO;
}

- (void)pause {
  assert([self isStarted]);
  assert(![self isPaused]);

  for (NSString *notification in AAKeyboardManager.notifications) {
    [self removeObserver:notification];
  }

  self.paused = YES;
}

- (NSUInteger)addAnimator:(id<AAKeyboardAnimator>)animator {
  [self.mutableAnimators addObject:animator];
  return [self.mutableAnimators count] - 1;
}

- (NSUInteger)addAnimation:(AAKeyboardAnimation)animation {
  return [self addAnimator:[[AADefaultKeyboardAnimator alloc]
                             initWithAnimation:animation]];
}

- (NSUInteger)addConstraintAnimator:(NSLayoutConstraint *)constraint {
  return [self addConstraintAnimator:constraint isInverted:NO];
}

- (NSUInteger)addConstraintAnimator:(NSLayoutConstraint *)constraint
                         isInverted:(BOOL)isInverted {
  __weak NSLayoutConstraint *weakConstraint = constraint;
  return [self addAnimation:^(AAKeyboardNotification *notification) {
    CGFloat newValue = CGRectGetHeight(notification.newFrame);
    if (isInverted) {
      newValue = (-newValue);
    }
    weakConstraint.constant = newValue;
  }];
}

- (NSUInteger)addFrameAnimator {
  __weak typeof(self) weakSelf = self;
  return [self addAnimation:^(AAKeyboardNotification *notification) {
    CGRect frame = weakSelf.referenceView.frame;
    frame.size.height -= CGRectGetHeight(notification.newFrame);
  }];
}

- (NSUInteger)addScrollViewAnimator:(UIScrollView *)scrollView {
  return [self addScrollViewAnimator:scrollView shouldModifyOffset:YES];
}

- (NSUInteger)addScrollViewAnimator:(UIScrollView *)scrollView
                 shouldModifyOffset:(BOOL)shouldModifyOffset {
  assert(scrollView.superview == self.referenceView);
  __weak UIScrollView *weakScrollView = scrollView;
  return [self addAnimation:^(AAKeyboardNotification *notification) {
    CGFloat verticalChange = CGRectGetMaxY(weakScrollView.frame) -
                             CGRectGetMinY(notification.newFrame);
    if (verticalChange < 0) {
      verticalChange = 0.0;
    }
    UIEdgeInsets insets = weakScrollView.contentInset;
    insets.bottom = verticalChange;
    weakScrollView.contentInset = insets;
    weakScrollView.scrollIndicatorInsets = insets;
    if (shouldModifyOffset && verticalChange > 0) {
      CGPoint offset = weakScrollView.contentOffset;
      offset.y += verticalChange;
      weakScrollView.contentOffset = offset;
    }
  }];
}

- (void)removeAnimator:(id<AAKeyboardAnimator>)animator {
  [self.mutableAnimators removeObject:animator];
}

- (void)removeAnimatorAtIndex:(NSUInteger)index {
  [self.mutableAnimators removeObjectAtIndex:index];
}

- (void)removeAnimators {
  [self.mutableAnimators removeAllObjects];
}

#pragma mark - Protected methods
- (void)willShow:(NSNotification *)notification {
  // Keyboard must be in interractive dismissal mode
  // ignore this notification.
  if ([self isKeyboardVisible]) return;

  AAKeyboardNotification *myNotification =
    [self convertNotification:notification];
  myNotification.type = AAKeyboardWillShow;
  [self.delegate keyboardManager:self willChangeFrame:myNotification];
  [self.delegate keyboardManager:self willShow:myNotification];
  [self runAnimators:notification];
}

- (void)willHide:(NSNotification *)notification {
  assert([self isKeyboardVisible]);
  AAKeyboardNotification *myNotification =
    [self convertNotification:notification];
  myNotification.type = AAKeyboardWillHide;
  [self.delegate keyboardManager:self willChangeFrame:myNotification];
  [self.delegate keyboardManager:self willHide:myNotification];
  [self runAnimators:notification];
}

- (void)didShow:(NSNotification *)notification {
  // Keyboard must be in interractive dismissal mode
  // ignore this notification.
  if ([self isKeyboardVisible]) return;

  AAKeyboardNotification *myNotification =
    [self convertNotification:notification];
  myNotification.type = AAKeyboardDidShow;
  self.keyboardVisible = YES;
  [self.delegate keyboardManager:self didChangeFrame:myNotification];
  [self.delegate keyboardManager:self didShow:myNotification];
}

- (void)didHide:(NSNotification *)notification {
  assert([self isKeyboardVisible]);
  self.keyboardVisible = NO;
  AAKeyboardNotification *myNotification =
    [self convertNotification:notification];
  myNotification.type = AAKeyboardDidShow;
  [self.delegate keyboardManager:self didChangeFrame:myNotification];
  [self.delegate keyboardManager:self didHide:myNotification];
}

#pragma mark - Private methods

- (AAKeyboardNotification *)convertNotification:(NSNotification *)notification {
  NSDictionary *userInfo = notification.userInfo;
  CGRect oldFrame = [self.referenceView
    convertRect:[userInfo[UIKeyboardFrameBeginUserInfoKey] CGRectValue]
       fromView:nil];
  CGRect newFrame = [self.referenceView
    convertRect:[userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue]
       fromView:nil];

  oldFrame = [self fixedFrameForKeyboardFrame:oldFrame];
  newFrame = [self fixedFrameForKeyboardFrame:newFrame];

  return [AAKeyboardNotification notificationWithOldFrame:oldFrame
                                                 newFrame:newFrame
                                                     type:0];
}

- (CGRect)fixedFrameForKeyboardFrame:(CGRect)frame {
  frame.size.height =
    CGRectGetHeight(self.referenceView.bounds) - CGRectGetMinY(frame);
  if (frame.size.height < 0.0) {
    frame.size.height = 0.0;
  }
  return frame;
}

- (void)addObserver:(NSString *)name selector:(SEL)selector {
  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:selector
                                               name:name
                                             object:nil];
}

- (void)removeObserver:(NSString *)name {
  [[NSNotificationCenter defaultCenter] removeObserver:self
                                                  name:name
                                                object:nil];
}

- (void)runAnimators:(NSNotification *)notification {
  double duration =
    [notification.userInfo[UIKeyboardAnimationDurationUserInfoKey] doubleValue];
  NSInteger options =
    [notification.userInfo[UIKeyboardAnimationCurveUserInfoKey] integerValue]
    << 16;
  options |= UIViewAnimationOptionLayoutSubviews;
  options |= UIViewAnimationOptionBeginFromCurrentState;
  [UIView
    animateWithDuration:duration
                  delay:0.0
                options:options
             animations:^{
               for (id<AAKeyboardAnimator> animator in self.mutableAnimators) {
                 [animator
                   animateForNotification:[self
                                            convertNotification:notification]];
                 [self.referenceView layoutIfNeeded];
               }
             }
             completion:nil];
}

@end
