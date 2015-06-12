#ifndef _DURAARK_OSDEF_HPP_
#define _DURAARK_OSDEF_HPP_

#ifdef _WIN32
#define EXPORTSPEC __declspec(dllexport)
#else
#define EXPORTSPEC
#endif

#endif /* _DURAARK_OSDEF_HPP_ */
