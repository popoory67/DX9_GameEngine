

// simplify DLL export and import definitions
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifndef SAFE_DELETE
// for pointers allocated with new.
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p) = nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
// for arrays allocated with new [].
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = nullptr; } }
#endif

using UINT = unsigned int;