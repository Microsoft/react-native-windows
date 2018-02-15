using ReactNative.UIManager;
#if WINDOWS_UWP
using Windows.UI.Xaml;
using Windows.UI.Xaml.Automation.Peers;
using Windows.UI.Xaml.Controls;
#else
using System.Windows;
using System.Windows.Automation.Peers;
using System.Windows.Controls;
#endif

namespace ReactNative.Views.ControlView
{
    /// <summary>
    /// A native control with a single Canvas child.
    /// </summary>
    public class ReactControl : UserControl, IAccessible
    {
        private readonly Canvas _canvas;

        /// <summary>
        /// Instantiates the <see cref="ReactControl"/>. 
        /// </summary>
        public ReactControl()
        {
            Content = _canvas = new Canvas
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
            };
#if WINDOWS_UWP
            UseSystemFocusVisuals = true;
#endif
        }

        /// <summary>
        /// The view children.
        /// </summary>
        public UIElementCollection Children
        {
            get
            {
                return _canvas.Children;
            }
        }

        /// <summary>
        /// Keys that should be handled during <see cref="UIElement.KeyDownEvent"/>. 
        /// </summary>
        public int[] HandledKeyDownKeys
        {
            get;
            set;
        }

        /// <summary>
        /// Keys that should be handled during <see cref="UIElement.KeyUpEvent"/>. 
        /// </summary>
        public int[] HandledKeyUpKeys
        {
            get;
            set;
        }

        // TODO: implement runtime change raising event to screen reader #1562
        /// <inheritdoc />                                                    
        public AccessibilityTrait[] AccessibilityTraits { get; set; }

        /// <inheritdoc />                                              
        protected override AutomationPeer OnCreateAutomationPeer()
        {
            return new DynamicAutomationPeer<ReactControl>(this);
        }
    }
}
