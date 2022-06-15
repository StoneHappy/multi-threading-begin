#pragma once

// join a thread I
namespace Demo00
{
	int main();
}

// join a thread II
namespace Demo01a01
{
	int main();
}

// pass arguments
namespace Demo01a02
{
	int main();
}

// using class method I (class public method)
namespace Demo01b01
{
	int main();
}

// using class method II (class private method)
namespace Demo01b02
{
	int main();
}

// using class method III (class static method, need not pass this pointer)
namespace Demo01b03
{
	int main();
}

// using class method IV (using functor)
namespace Demo01b04
{
	int main();
}

// using lambdas
namespace Demo01c01
{
	int main();
}

// do a heavy task
namespace Demo02a01
{
	int main();
}

// pass references variable to thread
namespace Demo03a01
{
	int main();
}

// Sleep for a specific duration
namespace Demo04a01
{
	int main();
}

// Sleep until
namespace Demo04a02
{
	int main();
}


// thread list
namespace Demo06a01
{
	int main();
}

// terminate thread
namespace Demo07a01
{
	int main();
}

/*
GETTING RETURNED VALUES FROM THREADS
Version A: Using pointers or references (traditional way)
*/
namespace Demo08a
{
	int main();
}


/*
GETTING RETURNED VALUES FROM THREADS
Version B: Using std::future with the promise
*/
namespace Demo08b
{
	int main();
}

/*
GETTING RETURNED VALUES FROM THREADS
Version C: Using std::future with std::packaged_task
*/
namespace Demo08c
{
	int main();
}

/*
THREAD DETACHING

NOTE: Detaches the thread represented by the object from the calling thread, allowing them to execute independently from each other.
*/
namespace Demo09
{
	int main();
}


/*
THREAD YIELDING
*/
namespace Demo10
{
	int main();
}


/*
EXECUTOR SERVICES AND THREAD POOLS
Executor services in C++ std threading are not supported by default.
So, I use mylib::ExecService for this demonstration.
*/

namespace Demo11a
{
	int main();
}

/*
EXECUTOR SERVICES AND THREAD POOLS
Executor services in C++ std threading are not supported by default.
So, I use mylib::ExecService for this demonstration.
*/
namespace Demo11b
{
	int main();
}