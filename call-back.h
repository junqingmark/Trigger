#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include <cstdio>

class CallbackBase
{
public:
    CallbackBase();
    ~CallbackBase();
    void Reset();

    static void Execute(CallbackBase& callback)
    {
        if(callback.mImpl && callback.mImpl->mObjectPointer)
        {
            Dispatcher dispatcher = callback.mImpl->mMemberFunctionDispatcher;
            (*dispatcher)( callback );
        }
        else if( !callback.mImpl && callback.mFunction )
        {
            (*(callback.mFunction))();
        }
        else
        {
            printf("no function to execute");
        }
    }

    template< typename R >
    static R ExecuteReturn( CallbackBase& callback )
    {
        R returnVal = R();
    
        if( callback.mImpl && callback.mImpl->mObjectPointer )
        {
        typedef R(*Dispatcher)(CallbackBase& base);
        Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
        returnVal = (*dispatcher)( callback );
        }
        else if( !callback.mImpl && callback.mFunction )
        {
        typedef R(*Function1)();
        returnVal = (*(reinterpret_cast< Function1 >( callback.mFunction )))();
        }

        return returnVal;
    }

    template< typename P1 >
    static void Execute( CallbackBase& callback, P1 param1 )
    {
        
        if( callback.mImpl && callback.mImpl->mObjectPointer )
        {
            typedef void(*Dispatcher)(CallbackBase& base,P1);
            Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
            (*dispatcher)( callback, param1 );
        }
        else if( !callback.mImpl && callback.mFunction )
        {
            typedef void(*Function1)(P1);
            (*(reinterpret_cast< Function1 >( callback.mFunction )))( param1 );
        }
    }

    template< typename R, typename P1 >
    static R ExecuteReturn( CallbackBase& callback, P1 param1 )
    {
        R returnVal =  R();
        
        if( callback.mImpl && callback.mImpl->mObjectPointer )
        {
            typedef R(*Dispatcher)(CallbackBase& base,P1);
            Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
            returnVal = (*dispatcher)( callback, param1 );
        }
        else if( !callback.mImpl && callback.mFunction )
        {
            // convert function type
            typedef R(*Function1)(P1);
            returnVal = (*(reinterpret_cast< Function1 >( callback.mFunction )))( param1 );
        }

        return returnVal;
    }

    template< typename P1, typename P2 >
    static void Execute( CallbackBase& callback, P1 param1, P2 param2 )
    {
    
        if( callback.mImpl && callback.mImpl->mObjectPointer )
        {
            typedef void(*Dispatcher)(CallbackBase& base,P1,P2);
            Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
            (*dispatcher)( callback, param1, param2 );
        }
        else if( !callback.mImpl && callback.mFunction )
        {
        // convert function type
        typedef void(*Function2)(P1,P2);
        (*(reinterpret_cast< Function2 >( callback.mFunction )))( param1, param2 );
        }
    }

    template< typename R, typename P1, typename P2 >
    static R ExecuteReturn( CallbackBase& callback, P1 param1, P2 param2 )
    {
        R returnVal= R();
    
        if( callback.mImpl && callback.mImpl->mObjectPointer )
        {
            typedef R(*Dispatcher)(CallbackBase& base,P1,P2);
            Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
            returnVal = (*dispatcher)( callback, param1, param2 );
        }
        else if( !callback.mImpl && callback.mFunction )
        {
            // convert function type
            typedef R(*Function2)(P1,P2);
            returnVal = (*(reinterpret_cast< Function2 >( callback.mFunction )))( param1, param2 );
        }

    return returnVal;
  }

  template< typename P1, typename P2, typename P3 >
  static void Execute( CallbackBase& callback, P1 param1, P2 param2, P3 param3 )
  {
    
    if( callback.mImpl && callback.mImpl->mObjectPointer )
    {
        typedef void(*Dispatcher)(CallbackBase& base,P1,P2,P3);
        Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
        (*dispatcher)( callback, param1, param2, param3 );
    }
    else if( !callback.mImpl && callback.mFunction )
    {
        // convert function type
        typedef void(*Function2)(P1,P2,P3);
        (*(reinterpret_cast< Function2 >( callback.mFunction )))( param1, param2, param3 );
    }
  }

  template< typename R, typename P1, typename P2, typename P3 >
  static R ExecuteReturn( CallbackBase& callback, P1 param1, P2 param2, P3 param3 )
  {
    R returnVal= R();
    
    if( callback.mImpl && callback.mImpl->mObjectPointer )
    {
      typedef R(*Dispatcher)(CallbackBase& base,P1,P2,P3);
      Dispatcher dispatcher = reinterpret_cast< Dispatcher >( callback.mImpl->mMemberFunctionDispatcher );
      returnVal = (*dispatcher)( callback, param1, param2, param3 );
    }
    else if( !callback.mImpl && callback.mFunction )
    {
      // convert function type
      typedef R(*Function2)(P1,P2,P3);
      returnVal = (*(reinterpret_cast< Function2 >( callback.mFunction )))( param1, param2, param3 );
    }

    return returnVal;
  }

protected:
    //function with static link
    typedef void(*Function)(void);
    //call member function
    typedef void(CallbackBase::*MemberFunction)(void);
    //call the correct member function
    typedef void(*Dispatcher)(CallbackBase& base);
    //used to destroy mObjectPointer(NULL if not owned)
    typedef void(*Destructor)(void* object);
    CallbackBase(const CallbackBase& rhs);
    CallbackBase& operator=(const CallbackBase& rhs);

    //Constructor for static function 
    CallbackBase(Function function);
    //constructor for member function, object is not owned
    CallbackBase(void* object, MemberFunction function, Dispatcher dispatcher);
    //constructor for member function, object is owned
    CallbackBase(void* object, MemberFunction function, Dispatcher dispatcher, Destructor destructor);

public:
    struct Impl
    {
        Impl();
        void* mObjectPointer;
        Dispatcher mMemberFunctionDispatcher;
        Destructor mDestructorDispatcher;
    };
    Impl* mImpl;

    union
    {
        MemberFunction mMemberFunction;
        Function mFunction;
    };
    
};

bool operator==(const CallbackBase& lhs, const CallbackBase& rhs);

//Dispatcher to delete an object.
template<class T>
struct Dstroyer
{
    static void Delete(void* object)
    {
        delete reinterpret_cast<T*>(object);
    }
};

//Dispatcher to call the actual member function.
template<class T>
struct Dispatcher0
{
    static void Dispatch(CallbackBase& callback)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef void(T::*MemberFunction)(void);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        (object->*function)();
    }
};

template<class T, typename P1>
struct Dispatcher1
{
    static void Dispatch(CallbackBase& callback, P1 param1)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef void(T::*MemberFunction)(P1);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        (object->*function)(param1);
    }
};

template<class T, typename P1, typename P2>
struct Dispatcher2
{
    static void Dispatch(CallbackBase& callback, P1 param1, P2 param2)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef void(T::*MemberFunction)(P1, P2);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        (object->*function)(param1, param2);
    }
};

template<class T, typename P1, typename P2, typename P3>
struct Dispatcher3
{
    static void Dispatch(CallbackBase& callback, P1 param1, P2 param2, P3 param3)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef void(T::*MemberFunction)(P1, P2, P3);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        (object->*function)(param1, param2, param3);
    }
};

template<class T, typename R>
struct DispatcherReturn0
{
    static R Dispatch(CallbackBase& callback)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef R(T::*MemberFunction)(void);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        return (object->*function)();
    }
};

template<class T, typename R, typename P1>
struct DispatcherReturn1
{
    static R Dispatch(CallbackBase& callback, P1 param1)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef R(T::*MemberFunction)(P1);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        return (object->*function)(param1);
    }
};

template<class T, typename R, typename P1, typename P2>
struct DispatcherReturn2
{
    static R Dispatch(CallbackBase& callback, P1 param1, P2 param2)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef R(T::*MemberFunction)(P1, P2);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        return (object->*function)(param1, param2);
    }
};

template<class T, typename R, typename P1, typename P2, typename P3>
struct DispatcherReturn3
{
    static R Dispatch(CallbackBase& callback, P1 param1, P2 param2, P3 param3)
    {
        T* object = reinterpret_cast<T*>(callback.mImpl->mObjectPointer);
        typedef R(T::*MemberFunction)(P1, P2, P3);
        MemberFunction function = reinterpret_cast<MemberFunction>(callback.mMemberFunction);
        return (object->*function)(param1, param2, param3);
    }
};

template<class T>
class Callback : public CallbackBase
{
public:
    Callback() : CallbackBase()
    {

    }

    Callback( T* object, void(T::*memberFunction)(void) )
    : CallbackBase( object,
                  reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                  reinterpret_cast< CallbackBase::Dispatcher >( &Dispatcher0<T>::Dispatch ) ) { }
    template< typename P1 >
    Callback( T* object, void(T::*memberFunction)(P1) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &Dispatcher1<T,P1>::Dispatch ) ) { }
    template< typename P1, typename P2 >
    Callback( T* object, void(T::*memberFunction)(P1, P2) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &Dispatcher2<T,P1,P2>::Dispatch ) ) { }
    template< typename P1, typename P2, typename P3 >
    Callback( T* object, void(T::*memberFunction)(P1, P2, P3) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &Dispatcher3<T,P1,P2,P3>::Dispatch ) ) { }
    template< typename R >
    Callback( T* object, R(T::*memberFunction)(void) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &DispatcherReturn0<T,R>::Dispatch ) ) { }
    template< typename R, typename P1 >
    Callback( T* object, R(T::*memberFunction)(P1) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &DispatcherReturn1<T,R,P1>::Dispatch ) ) { }
    template< typename R, typename P1, typename P2 >
    Callback( T* object, R(T::*memberFunction)(P1, P2) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &DispatcherReturn2<T,R,P1,P2>::Dispatch ) ) { }
    template< typename R, typename P1, typename P2, typename P3 >
    Callback( T* object, R(T::*memberFunction)(P1, P2, P3) )
    : CallbackBase( object,
                    reinterpret_cast< CallbackBase::MemberFunction >( memberFunction ),
                    reinterpret_cast< CallbackBase::Dispatcher >( &DispatcherReturn3<T,R,P1,P2,P3>::Dispatch ) ) { }
};

class CallbackFunction : public CallbackBase
{
public:

  CallbackFunction()
  : CallbackBase()
  {
  }

  CallbackFunction( void(*function)() )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename R >
  CallbackFunction( R(*function)() )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename P1 >
  CallbackFunction( void(*function)(P1) )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename P1, typename R >
  CallbackFunction( R(*function)(P1)  )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename P1, typename P2 >
  CallbackFunction( void(*function)(P1,P2)  )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename P1, typename P2, typename R >
  CallbackFunction( R(*function)(P1,P2) )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename P1, typename P2, typename P3 >
  CallbackFunction( void(*function)(P1,P2,P3)  )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }
  template< typename P1, typename P2, typename P3, typename R >
  CallbackFunction( R(*function)(P1,P2,P3) )
  : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
  { }

};

inline CallbackBase* MakeCallback( void(*function)(void) )
{
  return new CallbackFunction( function );
}

template< typename P1 >
inline CallbackBase* MakeCallback( void(*function)(P1) )
{
  return new CallbackFunction( function );
}

template< typename R >
inline CallbackBase* MakeCallback( R(*function)(void) )
{
  return new CallbackFunction( function );
}

template< typename R, typename P1 >
inline CallbackBase* MakeCallback( R(*function)(P1) )
{
  return new CallbackFunction( function );
}

template< typename P1, typename P2 >
inline CallbackBase* MakeCallback( void(*function)(P1,P2) )
{
  return new CallbackFunction( function );
}

template< typename R, typename P1, typename P2 >
inline CallbackBase* MakeCallback( R(*function)(P1,P2) )
{
  return new CallbackFunction( function );
}

template< typename P1, typename P2, typename P3 >
inline CallbackBase* MakeCallback( void(*function)(P1,P2,P3) )
{
  return new CallbackFunction( function );
}

template< typename R, typename P1, typename P2, typename P3 >
inline CallbackBase* MakeCallback( R(*function)(P1,P2,P3) )
{
  return new CallbackFunction( function );
}

template< class T >
inline CallbackBase* MakeCallback( T* object, void(T::*function)(void) )
{
  return new Callback< T >( object, function );
}

template< class T, typename P1 >
inline CallbackBase* MakeCallback( T* object, void(T::*function)(P1) )
{
  return new Callback< T >( object, function );
}

template< class T, typename P1, typename P2 >
inline CallbackBase* MakeCallback( T* object, void(T::*function)(P1,P2) )
{
  return new Callback< T >( object, function );
}

template< class T, typename P1, typename P2, typename P3 >
inline CallbackBase* MakeCallback( T* object, void(T::*function)(P1,P2,P3) )
{
  return new Callback< T >( object, function );
}

template< class T, typename R >
inline CallbackBase* MakeCallback( T* object, R(T::*function)() )
{
  return new Callback< T >( object, function );
}

template< class T, typename P1, typename R >
inline CallbackBase* MakeCallback( T* object, R(T::*function)(P1) )
{
  return new Callback< T >( object, function );
}

template< class T, typename P1, typename P2, typename R >
inline CallbackBase* MakeCallback( T* object, R(T::*function)(P1,P2) )
{
  return new Callback< T >( object, function );
}

template< class T, typename P1, typename P2, typename P3, typename R >
inline CallbackBase* MakeCallback( T* object, R(T::*function)(P1,P2,P3) )
{
  return new Callback< T >( object, function );
}


#endif //_CALLBACK_H_