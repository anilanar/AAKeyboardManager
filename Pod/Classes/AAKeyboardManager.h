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
//  AAKeyboardManager.h
//  AAKeyboardManager
//
//  Created by Anil Anar on 19.02.2015.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AAKeyboardManagerDelegate.h"
#import "AAKeyboardAnimator.h"

/*!
 *  The @c AAKeyboardManager class provides a bridging between iOS keyboard
 *notifications
 *  and animations that are to be run along with the keyboard.
 *
 *  @since 0.1.0
 */
@interface AAKeyboardManager : NSObject

#pragma mark - Properties
/*!
 *  @brief View whose coordinate system is used for keyboard frame
 *notifications.
 *
 *  @discussion If @c nil, coordinate system of the screen is used.
 *
 *  @since 0.1.0
 */

@property(weak, nonatomic, readonly) UIView* referenceView;

/*!
 *  @brief Array of @c AAKeyboardAnimator instances.
 *
 *  @description Animators are run according to keyboard show/hide
 *notifications.
 *
 *  @since 0.1.0
 */
@property(copy, nonatomic, readonly) NSArray* animators;

/*!
 *  @brief The object that acts as the delegate of the keyboard manager.
 *
 *  @since 0.1.0
 */
@property(weak, nonatomic) id<AAKeyboardManagerDelegate> delegate;

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
@property(assign, nonatomic, readonly, getter=isKeyboardVisible)
  BOOL keyboardVisible;

/*!
 *  @brief The frame rectangle of the keyboard.
 *
 *  @discussion This will not represent the keyboard frame accurately in the
 *  following cases:
 *  <li>after @c -start is called until first keyboard notification is
 *  emitted.</li>
 *  <li>after @c -stop is called.</li>
 *
 *  @since 0.1.0
 */
@property(assign, nonatomic, readonly) CGRect keyboardFrame;

#pragma mark - Initializers
/*!
 *  @brief Initializes and returns a keyboard manager.
 *
 *  @discussion Reference view is set to nil, coordinate system of the screen
 *  is used.
 *
 *  @return Returns an initialized @c AAKeyboardManager
 *
 *  @since 0.1.0
 */
- (instancetype)init;

/*!
 *  @brief Initializes and returns a keyboard manager.
 *
 *  @discussion If @em referenceView is @c nil, coordinate system of the screen
 *is used.
 *
 *  @param referenceView View whose coordinate system is used for keyboard frame
 *  notifications.
 *
 *  @return Returns an initialized @c AAKeyboardManager.
 *
 *  @since 0.1.0
 *
 */
- (instancetype)initWithReferenceView:(UIView*)referenceView;

#pragma mark - Methods
/*!
 *  @brief Starts observing keyboard notifications.
 *
 *  @discussion This is be typically called in <code>-viewDidLoad</code>.
 *  Stopped keyboard managers cannot be restarted. Keyboard manager is initially
 *in
 *  paused state.
 *
 *  @see <code> -stop</code>, <code>-pause</code>
 *
 *  @since 0.1.0
 */
- (void)start;

/*!
 *  @brief Stops observing keyboard notifications.
 *
 *  @discussion Once stopped, keyboard manager cannot be restarted.
 *
 *  @since 0.1.0
 */
- (void)stop;

/*!
 *  @brief Resumes keyboard manager.
 *
 *  @discussion This will be typically called in <code>-viewWillAppear</code>.
 *Keyboard
 *  manager is initially paused when first started.
 *
 *  @see <code>-pause</code>
 *
 *  @since 0.1.0
 */
- (void)resume;

/*!
 *  @brief Pauses keyboard manager, ignoring keyboard notifications until
 *resumed.
 *
 *  @discussion This will be typically called in
 *<code>-viewWillDissapear</code>.
 *
 *  @see <code> -resume</code>
 *
 *  @since 0.1.0
 */
- (void)pause;

/*!
 *  Adds the @em animator object.
 *
 *  @param animator The animator to be run when keyboard frame changes.
 *
 *  @return Returns index of the newly added @em animator.
 *
 *  @since 0.1.0
 */
- (NSUInteger)addAnimator:(id<AAKeyboardAnimator>)animator;

/*!
 *  Adds the @em animation block.
 *
 *  @discussion This is a shortcut for @c -addAnimator: method. An @c
 *  AAKeyboardAnimator will be created and added to the animators array.
 *
 *  @param animator The animation block to be run when keyboard frame changes.
 *  It is called when a keyboard notification is emitted.
 *
 *  @return Returns index of the newly created and added animator.
 *
 *  @see <code> -addAnimator:</code>
 *
 *  @since 0.1.0
 */
- (NSUInteger)addAnimation:(AAKeyboardAnimation)animation;

/*!
 *  Adds a constraint animator.
 *
 *  @discussion The constraint will be incremented when the keyboard displays.
 *  See @c -addConstraintAnimator:isInverted: for further information.
 *
 *  @param constraint The constraint that will be modified when the keyboard
 *  displays or dismisses.
 *
 *  @return Returns index of the newly created and added animator.
 *
 *  @since 0.1.0
 */
- (NSUInteger)addConstraintAnimator:(NSLayoutConstraint*)constraint;

/*!
 *  Adds a constraint animator.
 *
 *  @param constraint The constraint that will be modified when the keyboard
 *  frame changes.
 *
 *  @param isInverted @c YES if the constraint should be incremented when the
 *  keyboard displays or dismisses.
 *
 *  @return Returns the index of the newly created and added animator.
 *
 *  @since 0.1.0
 */
- (NSUInteger)addConstraintAnimator:(NSLayoutConstraint*)constraint
                         isInverted:(BOOL)isInverted;

/*!
 *  Adds a frame animator. Frame of the reference view will be modified.
 *
 *  @return Returns the index of the newly created and added animator.
 *
 *  @since 0.1.0
 */
- (NSUInteger)addFrameAnimator;

/*!
 *  Adds a scroll view animator. The reference view must be the superview of
 *  the scroll view.
 *
 *  @discussion By default, content offset will be modified. See
 *  @c -addScrollViewAnimator:shouldModifyOffset for more information.
 *
 *  @param scrollView The scroll view whose insets and content offset will be
 *  modified when the keyboard displays or dismisses.
 *
 *  @return Returns the index of the newly created and added animator.
 *
 *  @since 0.1.0
 */
- (NSUInteger)addScrollViewAnimator:(UIScrollView*)scrollView;

/*!
 *  Adds a scroll view animator. The reference view must be the superview of
 *  the scroll view.
 *
 *  @param scrollView         The scroll view whose insets and optionally
 *  content offset will be modified when the keyboard displays or dismisses.
 *
 *  @param shouldModifyOffset @c YES if content offset should be animated when
 *  the keyboard displays or dismisses.
 *
 *  @return Returns the index of the newly created and added animator.
 *
 *  @since 0.1.0
 */
- (NSUInteger)addScrollViewAnimator:(UIScrollView*)scrollView
                 shouldModifyOffset:(BOOL)shouldModifyOffset;

/*!
 *  Removes the @em animator object.
 *
 *  @param animator The animator to remove from array of animators.
 *
 *  @since 0.1.0
 */
- (void)removeAnimator:(id<AAKeyboardAnimator>)animator;

/*!
 *  Removes the animator object at @em index.
 *
 *  @param index The index from which to remove the animator in the animators
 *array.
 *
 *  @since 0.1.0
 */
- (void)removeAnimatorAtIndex:(NSUInteger)index;

/*!
 *  Removes all animators.
 *
 *  @since 0.1.0
 */
- (void)removeAnimators;

@end
