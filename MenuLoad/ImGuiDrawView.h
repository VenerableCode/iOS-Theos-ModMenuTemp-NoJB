#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ImGuiDrawView : UIViewController

+ (void)showChange:(BOOL)open;
+ (BOOL)isMenuShowing;

- (void)updateIOWithTouchEvent:(UIEvent *)event;

@end

NS_ASSUME_NONNULL_END