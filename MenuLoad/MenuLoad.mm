#import <UIKit/UIKit.h>
#include "Includes.h"

@interface MenuLoad()

@property (nonatomic, strong) ImGuiDrawView *vna;

- (ImGuiDrawView*) GetImGuiView;

@end

static MenuLoad* extraInfo;

UIButton* InvisibleMenuButton;
UIButton* VisibleMenuButton;
MenuInteraction* menuTouchView;
UITextField* hideRecordTextfield;
UIView* hideRecordView;
ImFont* Font;

static NSString *baseimage = @"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";

@interface MenuInteraction()

@end

@implementation MenuInteraction

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    if (![ImGuiDrawView isMenuShowing]) {
        return NO;
    }

    if (CGRectContainsPoint(VisibleMenuButton.frame, point)) {
        return NO;
    }

    CGRect touchableArea = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //CGRect touchableArea = CGRectMake(KTempVars.MenuOrigin.x, KTempVars.MenuOrigin.y, KTempVars.MenuSize.x, KTempVars.MenuSize.y); 

    if (CGRectContainsPoint(touchableArea, point)) {
        return [super pointInside:point withEvent:event];
    }
    return NO;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [[extraInfo GetImGuiView] updateIOWithTouchEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [[extraInfo GetImGuiView] updateIOWithTouchEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [[extraInfo GetImGuiView] updateIOWithTouchEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [[extraInfo GetImGuiView] updateIOWithTouchEvent:event];
}

@end

@implementation MenuLoad

- (ImGuiDrawView*) GetImGuiView {
    return _vna;
}

+ (void)load {
    [super load];
    timer(3){
        extraInfo = [MenuLoad new];
        [extraInfo initTapGes];  
    });
}

-(void)initTapGes {
    UIView* mainView = [UIApplication sharedApplication].windows[0].rootViewController.view;

    //STREAMER MODE
    hideRecordTextfield = [[UITextField alloc] init];
    hideRecordView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height)];
    [hideRecordView setBackgroundColor:[UIColor clearColor]];
    [hideRecordView setUserInteractionEnabled:YES];
    hideRecordTextfield.secureTextEntry = true;
    [hideRecordView addSubview:hideRecordTextfield];
    CALayer *layer = hideRecordTextfield.layer;
    
    if ([layer.sublayers.firstObject.delegate isKindOfClass:[UIView class]]) {
        hideRecordView = (UIView *)layer.sublayers.firstObject.delegate;
    } else {
        hideRecordView = nil;
    }

    [[UIApplication sharedApplication].keyWindow addSubview:hideRecordView];

    if (!_vna) {
        ImGuiDrawView *vc = [[ImGuiDrawView alloc] init];
        _vna = vc;
    }
    
    [ImGuiDrawView showChange:false];
    [hideRecordView addSubview:_vna.view];

    menuTouchView = [[MenuInteraction alloc] initWithFrame:mainView.frame];
    [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:menuTouchView];

    NSData* data = [[NSData alloc] initWithBase64EncodedString:baseimage options:0];
    UIImage* menuIconImage = [UIImage imageWithData:data];

    InvisibleMenuButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    InvisibleMenuButton.frame = CGRectMake(mainView.frame.size.width / 2, mainView.frame.size.height / 2, 50, 50);
    InvisibleMenuButton.backgroundColor = [UIColor clearColor];
    [InvisibleMenuButton addTarget:self action:@selector(buttonDragged:withEvent:) forControlEvents:UIControlEventTouchDragInside];
    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(showMenu:)];
    [InvisibleMenuButton addGestureRecognizer:tapGestureRecognizer];
    [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:InvisibleMenuButton];
    
    VisibleMenuButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    VisibleMenuButton.frame = CGRectMake(mainView.frame.size.width / 2, mainView.frame.size.height / 2, 50, 50);
    VisibleMenuButton.backgroundColor = [UIColor clearColor];
    VisibleMenuButton.layer.cornerRadius = VisibleMenuButton.frame.size.width * 0.5f;
    [VisibleMenuButton setBackgroundImage:menuIconImage forState:UIControlStateNormal];
    [hideRecordView addSubview:VisibleMenuButton];
}

-(void)showMenu:(UITapGestureRecognizer *)tapGestureRecognizer {
    if(tapGestureRecognizer.state == UIGestureRecognizerStateEnded) {
        [ImGuiDrawView showChange:![ImGuiDrawView isMenuShowing]];
    }
}

- (void)buttonDragged:(UIButton *)button withEvent:(UIEvent *)event {
    UITouch *touch = [[event touchesForView:button] anyObject];

    CGPoint previousLocation = [touch previousLocationInView:button];
    CGPoint location = [touch locationInView:button];
    CGFloat delta_x = location.x - previousLocation.x;
    CGFloat delta_y = location.y - previousLocation.y;

    button.center = CGPointMake(button.center.x + delta_x, button.center.y + delta_y);
    
    CGRect mainFrame = [UIApplication sharedApplication].windows[0].rootViewController.view.bounds;
    if(button.center.x < 0) button.center = CGPointMake(0,button.center.y);
    if(button.center.y < 0) button.center = CGPointMake(button.center.x,0);
    if(button.center.y > mainFrame.size.height) button.center = CGPointMake(button.center.x,mainFrame.size.height);
    if(button.center.x > mainFrame.size.width) button.center = CGPointMake(mainFrame.size.width,button.center.y);
    
    VisibleMenuButton.center = button.center;
    VisibleMenuButton.frame = button.frame;
}

@end