//
// This file is generated by GenericDelegateTypes.tt
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//

using System;
using System.Reflection;

namespace ReactNative.Bridge
{
    static class GenericDelegateTypes
    {
        public static Type[] ActionTypes =
        {
            typeof(SignatureAction0),
            typeof(SignatureAction1<>),
            typeof(SignatureAction2<,>),
            typeof(SignatureAction3<,,>),
            typeof(SignatureAction4<,,,>),
            typeof(SignatureAction5<,,,,>),
            typeof(SignatureAction6<,,,,,>),
            typeof(SignatureAction7<,,,,,,>),
            typeof(SignatureAction8<,,,,,,,>),
            typeof(SignatureAction9<,,,,,,,,>),
            typeof(SignatureAction10<,,,,,,,,,>),
            typeof(SignatureAction11<,,,,,,,,,,>),
            typeof(SignatureAction12<,,,,,,,,,,,>),
            typeof(SignatureAction13<,,,,,,,,,,,,>),
            typeof(SignatureAction14<,,,,,,,,,,,,,>),
            typeof(SignatureAction15<,,,,,,,,,,,,,,>),
            typeof(SignatureAction16<,,,,,,,,,,,,,,,>),
        };

        public static Type[] FuncTypes =
        {
            typeof(SignatureFunc0<>),
            typeof(SignatureFunc1<,>),
            typeof(SignatureFunc2<,,>),
            typeof(SignatureFunc3<,,,>),
            typeof(SignatureFunc4<,,,,>),
            typeof(SignatureFunc5<,,,,,>),
            typeof(SignatureFunc6<,,,,,,>),
            typeof(SignatureFunc7<,,,,,,,>),
            typeof(SignatureFunc8<,,,,,,,,>),
            typeof(SignatureFunc9<,,,,,,,,,>),
            typeof(SignatureFunc10<,,,,,,,,,,>),
            typeof(SignatureFunc11<,,,,,,,,,,,>),
            typeof(SignatureFunc12<,,,,,,,,,,,,>),
            typeof(SignatureFunc13<,,,,,,,,,,,,,>),
            typeof(SignatureFunc14<,,,,,,,,,,,,,,>),
            typeof(SignatureFunc15<,,,,,,,,,,,,,,,>),
            typeof(SignatureFunc16<,,,,,,,,,,,,,,,,>),
        };

        class SignatureAction0 : IGenericDelegate
        {
            Action _instancedDelegate;

            public SignatureAction0(MethodInfo method)
            {
                _instancedDelegate = (Action)method.CreateDelegate(typeof(Action));
            }

            public SignatureAction0(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action)method.CreateDelegate(typeof(Action), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate();
                return null;
            }
        }

        class SignatureFunc0<TResult> : IGenericDelegate
        {
            Func<TResult> _instancedDelegate;

            public SignatureFunc0(MethodInfo method)
            {
                _instancedDelegate = (Func<TResult>)method.CreateDelegate(typeof(Func<TResult>));
            }

            public SignatureFunc0(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<TResult>)method.CreateDelegate(typeof(Func<TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate();
        }
        class SignatureAction1<T0> : IGenericDelegate
        {
            Action<T0> _instancedDelegate;

            public SignatureAction1(MethodInfo method)
            {
                _instancedDelegate = (Action<T0>)method.CreateDelegate(typeof(Action<T0>));
            }

            public SignatureAction1(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0>)method.CreateDelegate(typeof(Action<T0>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0]);
                return null;
            }
        }

        class SignatureFunc1<T0, TResult> : IGenericDelegate
        {
            Func<T0, TResult> _instancedDelegate;

            public SignatureFunc1(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, TResult>)method.CreateDelegate(typeof(Func<T0, TResult>));
            }

            public SignatureFunc1(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, TResult>)method.CreateDelegate(typeof(Func<T0, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0]);
        }
        class SignatureAction2<T0, T1> : IGenericDelegate
        {
            Action<T0, T1> _instancedDelegate;

            public SignatureAction2(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1>)method.CreateDelegate(typeof(Action<T0, T1>));
            }

            public SignatureAction2(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1>)method.CreateDelegate(typeof(Action<T0, T1>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1]);
                return null;
            }
        }

        class SignatureFunc2<T0, T1, TResult> : IGenericDelegate
        {
            Func<T0, T1, TResult> _instancedDelegate;

            public SignatureFunc2(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, TResult>)method.CreateDelegate(typeof(Func<T0, T1, TResult>));
            }

            public SignatureFunc2(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, TResult>)method.CreateDelegate(typeof(Func<T0, T1, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1]);
        }
        class SignatureAction3<T0, T1, T2> : IGenericDelegate
        {
            Action<T0, T1, T2> _instancedDelegate;

            public SignatureAction3(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2>)method.CreateDelegate(typeof(Action<T0, T1, T2>));
            }

            public SignatureAction3(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2>)method.CreateDelegate(typeof(Action<T0, T1, T2>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2]);
                return null;
            }
        }

        class SignatureFunc3<T0, T1, T2, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, TResult> _instancedDelegate;

            public SignatureFunc3(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, TResult>));
            }

            public SignatureFunc3(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2]);
        }
        class SignatureAction4<T0, T1, T2, T3> : IGenericDelegate
        {
            Action<T0, T1, T2, T3> _instancedDelegate;

            public SignatureAction4(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3>));
            }

            public SignatureAction4(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3]);
                return null;
            }
        }

        class SignatureFunc4<T0, T1, T2, T3, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, TResult> _instancedDelegate;

            public SignatureFunc4(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, TResult>));
            }

            public SignatureFunc4(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3]);
        }
        class SignatureAction5<T0, T1, T2, T3, T4> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4> _instancedDelegate;

            public SignatureAction5(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4>));
            }

            public SignatureAction5(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4]);
                return null;
            }
        }

        class SignatureFunc5<T0, T1, T2, T3, T4, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, TResult> _instancedDelegate;

            public SignatureFunc5(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, TResult>));
            }

            public SignatureFunc5(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4]);
        }
        class SignatureAction6<T0, T1, T2, T3, T4, T5> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5> _instancedDelegate;

            public SignatureAction6(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5>));
            }

            public SignatureAction6(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5]);
                return null;
            }
        }

        class SignatureFunc6<T0, T1, T2, T3, T4, T5, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, TResult> _instancedDelegate;

            public SignatureFunc6(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, TResult>));
            }

            public SignatureFunc6(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5]);
        }
        class SignatureAction7<T0, T1, T2, T3, T4, T5, T6> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6> _instancedDelegate;

            public SignatureAction7(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6>));
            }

            public SignatureAction7(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6]);
                return null;
            }
        }

        class SignatureFunc7<T0, T1, T2, T3, T4, T5, T6, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, TResult> _instancedDelegate;

            public SignatureFunc7(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, TResult>));
            }

            public SignatureFunc7(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6]);
        }
        class SignatureAction8<T0, T1, T2, T3, T4, T5, T6, T7> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7> _instancedDelegate;

            public SignatureAction8(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7>));
            }

            public SignatureAction8(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7]);
                return null;
            }
        }

        class SignatureFunc8<T0, T1, T2, T3, T4, T5, T6, T7, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, TResult> _instancedDelegate;

            public SignatureFunc8(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, TResult>));
            }

            public SignatureFunc8(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7]);
        }
        class SignatureAction9<T0, T1, T2, T3, T4, T5, T6, T7, T8> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8> _instancedDelegate;

            public SignatureAction9(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8>));
            }

            public SignatureAction9(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8]);
                return null;
            }
        }

        class SignatureFunc9<T0, T1, T2, T3, T4, T5, T6, T7, T8, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, TResult> _instancedDelegate;

            public SignatureFunc9(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, TResult>));
            }

            public SignatureFunc9(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8]);
        }
        class SignatureAction10<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> _instancedDelegate;

            public SignatureAction10(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>));
            }

            public SignatureAction10(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9]);
                return null;
            }
        }

        class SignatureFunc10<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, TResult> _instancedDelegate;

            public SignatureFunc10(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, TResult>));
            }

            public SignatureFunc10(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9]);
        }
        class SignatureAction11<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> _instancedDelegate;

            public SignatureAction11(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>));
            }

            public SignatureAction11(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10]);
                return null;
            }
        }

        class SignatureFunc11<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TResult> _instancedDelegate;

            public SignatureFunc11(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TResult>));
            }

            public SignatureFunc11(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10]);
        }
        class SignatureAction12<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> _instancedDelegate;

            public SignatureAction12(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>));
            }

            public SignatureAction12(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11]);
                return null;
            }
        }

        class SignatureFunc12<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, TResult> _instancedDelegate;

            public SignatureFunc12(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, TResult>));
            }

            public SignatureFunc12(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11]);
        }
        class SignatureAction13<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> _instancedDelegate;

            public SignatureAction13(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>));
            }

            public SignatureAction13(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12]);
                return null;
            }
        }

        class SignatureFunc13<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, TResult> _instancedDelegate;

            public SignatureFunc13(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, TResult>));
            }

            public SignatureFunc13(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12]);
        }
        class SignatureAction14<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> _instancedDelegate;

            public SignatureAction14(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>));
            }

            public SignatureAction14(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12], (T13)args[13]);
                return null;
            }
        }

        class SignatureFunc14<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, TResult> _instancedDelegate;

            public SignatureFunc14(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, TResult>));
            }

            public SignatureFunc14(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12], (T13)args[13]);
        }
        class SignatureAction15<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> _instancedDelegate;

            public SignatureAction15(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>));
            }

            public SignatureAction15(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12], (T13)args[13], (T14)args[14]);
                return null;
            }
        }

        class SignatureFunc15<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, TResult> _instancedDelegate;

            public SignatureFunc15(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, TResult>));
            }

            public SignatureFunc15(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12], (T13)args[13], (T14)args[14]);
        }
        class SignatureAction16<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> : IGenericDelegate
        {
            Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> _instancedDelegate;

            public SignatureAction16(MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>));
            }

            public SignatureAction16(object instance, MethodInfo method)
            {
                _instancedDelegate = (Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>)method.CreateDelegate(typeof(Action<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>), instance);
            }

            public object Invoke(object[] args)
            {
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12], (T13)args[13], (T14)args[14], (T15)args[15]);
                return null;
            }
        }

        class SignatureFunc16<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, TResult> : IGenericDelegate
        {
            Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, TResult> _instancedDelegate;

            public SignatureFunc16(MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, TResult>));
            }

            public SignatureFunc16(object instance, MethodInfo method)
            {
                _instancedDelegate = (Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, TResult>)method.CreateDelegate(typeof(Func<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, TResult>), instance);
            }

            public object Invoke(object[] args) =>
                _instancedDelegate((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8], (T9)args[9], (T10)args[10], (T11)args[11], (T12)args[12], (T13)args[13], (T14)args[14], (T15)args[15]);
        }
    }
}
