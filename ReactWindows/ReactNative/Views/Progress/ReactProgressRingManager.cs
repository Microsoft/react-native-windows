﻿using ReactNative.UIManager;
using ReactNative.UIManager.Annotations;
using ReactNative.UIManager.Events;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace ReactNative.Views.Progress
{
    /// <summary>
    /// Represents a native <see cref="ProgressRing"/> component.
    /// </summary>
    class ReactProgressRingViewManager : BaseViewManager<ProgressRing, ReactProgressRingShadowNode>
    {
        /// <summary>
        /// Instantiates the base class <see cref="ReactProgressRingViewManager"/>.
        /// </summary>
        public ReactProgressRingViewManager()
        {
        }

        /// <summary>
        /// Instantiates the base class <see cref="ReactProgressRingViewManager"/>.
        /// </summary>
        /// <param name="eventDispatcher">The event dispatcher to associate with this instance</param>
        public ReactProgressRingViewManager(IEventDispatcher eventDispatcher)
            : base(eventDispatcher)
        {
        }

        /// <summary>
        /// The name of this view manager. This will be the name used to 
        /// reference this view manager from JavaScript.
        /// </summary>
        public override string Name
        {
            get
            {
                return "WindowsProgressRing";
            }
        }

        /// <summary>
        /// Sets the font color for the node.
        /// </summary>
        /// <param name="view">The view instance.</param>
        /// <param name="color">The masked color value.</param>
        [ReactProp(ViewProps.Color, CustomType = "Color")]
        public void SetColor(ProgressRing view, uint? color)
        {
            view.Foreground = color.HasValue
                ? new SolidColorBrush(ColorHelpers.Parse(color.Value))
                : new SolidColorBrush(Colors.Black);
        }

        /// <summary>
        /// Determines the activity of a <see cref="ProgressRing"/> component.
        /// </summary>
        /// <param name="view">The native <see cref="ProgressRing"/>.</param>
        /// <param name="value">Whether the <see cref="ProgressRing"/> is active or not.</param>
        [ReactProp("animating")]
        public void SetAnimating(ProgressRing view, bool value)
        {
            view.IsActive = value;
        }

        /// <summary>
        /// This method should return the <see cref="ReactProgressRingShadowNode"/>
        /// which will be then used for measuring the position and size of the
        /// view. 
        /// </summary>
        /// <returns>The shadow node instance.</returns>
        public override ReactProgressRingShadowNode CreateShadowNodeInstance()
        {
            return new ReactProgressRingShadowNode();
        }

        /// <summary>
        /// Implement this method to receive optional extra data enqueued from
        /// the corresponding instance of <see cref="ReactShadowNode"/> in
        /// <see cref="ReactShadowNode.OnCollectExtraUpdates"/>.
        /// </summary>
        /// <param name="root">The root view.</param>
        /// <param name="extraData">The extra data.</param>
        public override void UpdateExtraData(ProgressRing root, object extraData)
        {
        }

        /// <summary>
        /// Creates a new view instance of a native <see cref="ProgressRing"/> component.
        /// </summary>
        /// <returns>Returns a native <see cref="ProgressRing"/> component.</returns>
        protected override ProgressRing CreateViewInstance()
        {
            return new ProgressRing();
        }
    }
}