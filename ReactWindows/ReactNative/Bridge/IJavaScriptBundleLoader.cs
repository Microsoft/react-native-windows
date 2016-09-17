﻿using System.Threading.Tasks;

namespace ReactNative.Bridge
{
    /// <summary>
    /// A class that stores JavaScript bundle information and allows the
    /// <see cref="IReactInstance"/> to load a correct bundle through the
    /// <see cref="IReactBridge"/>.
    /// </summary>
    public interface IJavaScriptBundleLoader
    {
        /// <summary>
        /// The source URL of the bundle.
        /// </summary>
        string SourceUrl { get; }

        /// <summary>
        /// Initializes the JavaScript bundle loader, typically making an
        /// asynchronous call to cache the bundle in memory.
        /// </summary>
        /// <returns>A task to await initialization.</returns>
        Task InitializeAsync();

        /// <summary>
        /// Loads the bundle into a JavaScript executor.
        /// </summary>
        /// <param name="executor">The JavaScript executor.</param>
        void LoadScript(IReactBridge executor);
    }
}
