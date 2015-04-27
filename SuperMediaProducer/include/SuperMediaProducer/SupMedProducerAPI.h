//dynamic library macro define
//andycai_sc@163.com 2015-04-21

#ifndef SUPMEDPRODUCERAPI_H_INCLUDED
#define SUPMEDPRODUCERAPI_H_INCLUDED

#if defined(WIN32)
	#if defined(WIN_EXPORT)
		#define SUPMEDPRODUCER_API __declspec(dllexport)
	#else
		#define SUPMEDPRODUCER_API __declspec(dllimport)
	#endif
#else
	#define SUPMEDPRODUCER_API
#endif


#endif // SUPMEDPRODUCERAPI_H_INCLUDED
