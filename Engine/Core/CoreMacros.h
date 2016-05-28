// simplify DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#ifndef SAFE_DELETE
// for pointers allocated with new.
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p) = nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
// for arrays allocated with new [].
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = nullptr; } }
#endif