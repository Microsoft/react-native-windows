﻿// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System;

namespace ReactNative.Common
{
    static class InetHelpers
    {
        public static uint LittleEndianToHost(uint value)
        {
            if (!BitConverter.IsLittleEndian)
            {
                // TODO: if you need big-endianess, please implement
                throw new NotSupportedException("Only little-endian hosts are currently supported.");
            }

            return value;
        }
    }
}
