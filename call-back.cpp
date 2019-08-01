#include "call-back.h"

CallbackBase::CallbackBase()
: mImpl( NULL ),
  mFunction( NULL )
{
}

CallbackBase::~CallbackBase()
{
  Reset();
}

CallbackBase::CallbackBase( Function function )
: mImpl( NULL ),
  mFunction( function )
{
}

CallbackBase::CallbackBase( void* object, MemberFunction function, Dispatcher dispatcher )
: mMemberFunction( function )
{
  mImpl = new CallbackBase::Impl;
  if( mImpl )
  {
    mImpl->mObjectPointer = object;
    mImpl->mMemberFunctionDispatcher = dispatcher;
    mImpl->mDestructorDispatcher = NULL; // object is not owned
  }
}

CallbackBase::CallbackBase( void* object, MemberFunction function, Dispatcher dispatcher, Destructor destructor )
: mMemberFunction( function )
{
  mImpl = new CallbackBase::Impl;
  if( mImpl )
  {
    mImpl->mObjectPointer = object;
    mImpl->mMemberFunctionDispatcher = dispatcher;
    mImpl->mDestructorDispatcher = destructor; // object is owned
  }
}

void CallbackBase::Reset()
{
  if( mImpl )
  {
    // if destructor function is set it means we own this object
    if ( mImpl->mObjectPointer &&
         mImpl->mDestructorDispatcher )
    {
      // call the destructor dispatcher
      (*mImpl->mDestructorDispatcher)( mImpl->mObjectPointer );
    }

    delete mImpl;
    mImpl = NULL;
  }

  mFunction = NULL;
}

// CallbackBase::Impl

CallbackBase::Impl::Impl()
: mObjectPointer( NULL ),
  mMemberFunctionDispatcher( NULL ),
  mDestructorDispatcher( NULL )
{
}

// Non-member equality operator

bool operator==( const CallbackBase& lhs, const CallbackBase& rhs )
{
  if( lhs.mImpl )
  {
    // check it's the same member function / object
    return ( lhs.mFunction == rhs.mFunction ) &&  ( lhs.mImpl->mObjectPointer == rhs.mImpl->mObjectPointer );
  }
  else
  {
    // check if it the same C function or a static member function
    return ( lhs.mFunction == rhs.mFunction );
  }
}
