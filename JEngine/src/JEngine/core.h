#ifdef JE_PLATFORM_WINDOWS
	#ifdef JE_BUILD_DLL
		#define JE_API __declspec(dllexport)	
	#else
		#define JE_API __declspec(dllimport)
	#endif 
#else
	#error JEning only supports windows platform !!
#endif

#ifdef JE_ENABLE_ASSERTS
	#define JE_CLIENT_ASSERT(x, ...)  {if(!(x)) {JE_CLIENT_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); } }
	#define JE_CORE_ASSERT(x, ...)    {if(!(x)) {JE_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
#else
	#define JE_CLIENT_ASSERT(x, ...)
	#define JE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) 1<<x


#define JE_BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)