#ifndef _CALLBACK_H_
#define _CALLBACK_H_

// class CallbackBase
// {
// public:
//     CallbackBase();
//     ~CallbackBase();
//     void Reset();

//     static void Execute(CallbackBase& callback)
//     {
//         if(callback.mImpl && callback.mImpl->mObjectPointer)
//         {

//         }
//     }


// protected:
//     //function with static link
//     typedef void(*Function)(void);
//     //call member function
//     typedef void(CallbackBase::*MemberFunction)(void);
//     //call the correct member function
//     typedef void(*Dispatcher)(CallbackBase& base);
//     //used to destroy mObjectPointer(NULL if not owned)
//     typedef void(*Destructor)(void* object);
//     CallbackBase(const CallbackBase& rhs);
//     CallbackBase& operator=(const CallbackBase& rhs);

//     //Constructor for static function 
//     CallbackBase(Function function);
//     //constructor for member function, object is not owned
//     CallbackBase(void* object, MemberFunction function, Dispatcher dispatcher);
//     //constructor for member function, object is owned
//     CallbackBase(void* object, MemberFunction function, Dispatcher dispatcher, Destructor destructor);

// public:
//     struct Impl
//     {
//         Impl();
//         void* mObjectPointer;
//         Dispatcher mMemberFunctionDispatcher;
//         Destructor mDestructorDispatcher;
//     };
//     Impl* mImpl;

//     union
//     {
//         MemberFunction mMemberFunction;
//         Function mFunction;
//     };
    
// };

// bool operator==(const CallbackBase& lhs, const CallbackBase& rhs);

// //Dispatcher to delete an object.
// template<class T>
// struct Dstroyer
// {
//     static void Delete(void* object)
//     {
//         delete reinterpret_cast<T*>(object);
//     }
// };

// //Dispatcher to call the actual member function.
// template<class T>
// struct Dispatcher0
// {
//     static void Dispatch(CallbackBase& callback)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef void(T::*MemberFunction)(void);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         (object->*function)();
//     }
// };

// template<class T, typename P1>
// struct Dispatcher1
// {
//     static void Dispatch(CallbackBase& callback， P1 param1)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef void(T::*MemberFunction)(P1);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         (object->*function)(param1);
//     }
// };

// template<class T, typename P1, typename P2>
// struct Dispatcher2
// {
//     static void Dispatch(CallbackBase& callback， P1 param1, P2 param2)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef void(T::*MemberFunction)(P1, P2);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         (object->*function)(param1, param2);
//     }
// };

// template<class T, typename P1, typename P2, typename P3>
// struct Dispatcher3
// {
//     static void Dispatch(CallbackBase& callback， P1 param1, P2 param2, P3 param3)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef void(T::*MemberFunction)(P1, P2, P3);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         (object->*function)(param1, param2, param3);
//     }
// };

// template<class T, typename R>
// struct DispatcherReturn0
// {
//     static R Dispatch(CallbackBase& callback)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef R(T::*MemberFunction)(void);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         return (object->*function)();
//     }
// };

// template<class T, typename R, typename P1>
// struct DispatcherReturn1
// {
//     static R Dispatch(CallbackBase& callback, P1 param1)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef R(T::*MemberFunction)(P1);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         return (object->*function)(param1);
//     }
// };

// template<class T, typename R, typename P1, typename P2>
// struct DispatcherReturn2
// {
//     static R Dispatch(CallbackBase& callback, P1 param1, P2 param2)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef R(T::*MemberFunction)(P1, P2);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         return (object->*function)(param1, param2);
//     }
// };

// template<class T, typename R, typename P1, typename P2, typename P3>
// struct DispatcherReturn3
// {
//     static R Dispatch(CallbackBase& callback, P1 param1, P2 param2, P3 param3)
//     {
//         T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
//         typedef R(T::*MemberFunction)(P1, P2, P3);
//         MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
//         return (object->*function)(param1, param2, param3);
//     }
// };

// template<class T>
// class Callback : public CallbackBase
// {
// public:
//     Callback() : CallbackBase()
//     {

//     }

//     Callback(T* object, void(T::*MemberFunction)(void));
// }

template<class T>
class Callback
{
public:
    Callback(){}
    Callback( T* object, void(T::*memberFunction)(void) )
    {
        object->memberFunction();
    }
    
    template<typename P1>
    Callback(T* object, void(T::*memberFunction)(P1), P1 param1)
    {
        object->memberFunction(param1);
    }

    template<typename P1, typename P2>
    Callback(T* object, void(T::*memberFunction)(P1, P2), P1 param1, P2 param2)
    {
        object->memberFunction(param1, param2);
    }

    template<typename P1, typename P2, typename P3>
    Callback(T* object, void(T::*memberFunction)(P1, P2, P3), P1 param1, P2 param2, P3 param3)
    {
        object->memberFunction(param1, param2, param3);
    }
};

class CallbackFunction
{
public:
    CallbackFunction(){}
    CallbackFunction(void(*memberFunction)(void) )
    {
        memberFunction();
    }
    
    template<typename P1>
    CallbackFunction(void(*memberFunction)(P1), P1 param1)
    {
        memberFunction(param1);
    }

    template<typename P1, typename P2>
    CallbackFunction(void(*memberFunction)(P1, P2), P1 param1, P2 param2)
    {
        memberFunction(param1, param2);
    }

    template<typename P1, typename P2, typename P3>
    CallbackFunction(void(*memberFunction)(P1, P2, P3), P1 param1, P2 param2, P3 param3)
    {
        memberFunction(param1, param2, param3);
    }
};

#endif //_CALLBACK_H_