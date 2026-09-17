#import "Includes.h"
#import "GUI/UserMenu.h"
#import "../Resources/Fonts/Font.h"
#import "../Source/BasicHacks.h"

@interface ImGuiDrawView () <MTKViewDelegate>

@property (nonatomic, strong) id <MTLDevice> device;
@property (nonatomic, strong) id <MTLCommandQueue> commandQueue;

@end

@implementation ImGuiDrawView

static bool MenDeal = true;

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil
                          bundle:(nullable NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];

    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];

    if (!self.device)
        abort();

    R_BasicCheats.Initialize();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    //ImGui::StyleColorsClassic();

    io.Fonts->Clear();

    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    Font = io.Fonts->AddFontFromMemoryCompressedBase85TTF(
        CurvyBase85,
        40.f,
        &config,
        io.Fonts->GetGlyphRangesChineseFull()
    );

    ImGui_ImplMetal_Init(_device);

    return self;
}

+ (void)showChange:(BOOL)open
{
    MenDeal = open;
}

+ (BOOL)isMenuShowing
{
    return MenDeal;
}

- (MTKView *)mtkView
{
    return (MTKView *)self.view;
}

- (void)loadView
{
    CGFloat w = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width;
    CGFloat h = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height;

    self.view = [[MTKView alloc]
        initWithFrame:CGRectMake(0, 0, w, h)];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.mtkView.device = self.device;
    self.mtkView.delegate = self;
    self.mtkView.clearColor = MTLClearColorMake(0, 0, 0, 0);
    self.mtkView.backgroundColor =
        [UIColor colorWithRed:0 green:0 blue:0 alpha:0];
    self.mtkView.clipsToBounds = YES;

    UIWindow *window = [UIApplication sharedApplication].keyWindow;

    if (!window)
        window = [UIApplication sharedApplication].windows[0];

    if (window && menuTouchView)
    {
        if (menuTouchView.superview != window)
        {
            [menuTouchView removeFromSuperview];
            [window addSubview:menuTouchView];
        }

        [window bringSubviewToFront:menuTouchView];
    }
}

- (void)updateIOWithTouchEvent:(UIEvent *)event
{
    UITouch *anyTouch = event.allTouches.anyObject;

    if (!anyTouch)
        return;

    CGPoint touchLocation =
        [anyTouch locationInView:self.view];

    ImGuiIO &io = ImGui::GetIO();

    io.MousePos =
        ImVec2(touchLocation.x, touchLocation.y);

    BOOL hasActiveTouch = NO;

    for (UITouch *touch in event.allTouches)
    {
        if (touch.phase != UITouchPhaseEnded &&
            touch.phase != UITouchPhaseCancelled)
        {
            hasActiveTouch = YES;
            break;
        }
    }

    io.MouseDown[0] = hasActiveTouch;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches
          withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches
          withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches
              withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches
          withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)drawInMTKView:(MTKView *)view
{
    hideRecordTextfield.secureTextEntry =
        KTempVars.StreamerMode;

    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize.x = view.bounds.size.width;
    io.DisplaySize.y = view.bounds.size.height;

    CGFloat framebufferScale =
        view.window.screen.nativeScale
        ? view.window.screen.nativeScale
        : UIScreen.mainScreen.nativeScale;

    io.DisplayFramebufferScale =
        ImVec2(framebufferScale, framebufferScale);

    io.DeltaTime =
        1 / float(view.preferredFramesPerSecond
            ? view.preferredFramesPerSecond
            : 60);

    id<MTLCommandBuffer> commandBuffer =
        [self.commandQueue commandBuffer];

    MTLRenderPassDescriptor *renderPassDescriptor =
        view.currentRenderPassDescriptor;

    if (renderPassDescriptor != nil)
    {
        id<MTLRenderCommandEncoder> renderEncoder =
            [commandBuffer
                renderCommandEncoderWithDescriptor:
                    renderPassDescriptor];

        [renderEncoder
            pushDebugGroup:@"Dear ImGui Rendering"];

        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui::NewFrame();

        ImFont *font = ImGui::GetFont();

        if (font && font->FontSize > 0)
            font->Scale = 12.f / font->FontSize;

        if (MenDeal)
            Menu.Initialize();

        UserMenu::GetInstance().RenderingMenu();

        ImGui::Render();

        ImDrawData *draw_data =
            ImGui::GetDrawData();

        ImGui_ImplMetal_RenderDrawData(
            draw_data,
            commandBuffer,
            renderEncoder
        );

        [renderEncoder popDebugGroup];
        [renderEncoder endEncoding];

        [commandBuffer presentDrawable:
            view.currentDrawable];
    }

    [commandBuffer commit];
}

- (void)mtkView:(MTKView *)view
drawableSizeWillChange:(CGSize)size
{
}

@end

%ctor
{
}
