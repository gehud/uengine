#include "client_application.h"

#include <uengine/delegates.h>
#include <uengine/log.h>

client_application::client_application()
{
	ue::lambda<void, int> f1([this](int a) 
	{
		foo(a);
	});
	f1(1);
	ue::function_ptr<void, int> f2([](const int& a) 
	{
		UE_TRACE("Foo {0}", a);
	});
	f2(2);
	ue::method_ptr<client_application, void, int> f3(this, &client_application::foo);
	f3(3);

	ue::action<int> a;
	a += new ue::lambda<void, int>([](int a) 
		{
			UE_TRACE("Foo {0}", a);
		});
	a += new ue::function_ptr<void, int>([](const int& a)
	{
		UE_TRACE("Foo {0}", a);
	});
	a += new ue::method_ptr<client_application, void, int>(this, &client_application::foo);
	a(4);
}

void client_application::foo(const int& a)
{
	UE_TRACE("Foo {0}", a);
}