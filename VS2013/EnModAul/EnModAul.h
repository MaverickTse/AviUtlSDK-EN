// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ENMODAUL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ENMODAUL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ENMODAUL_EXPORTS
#define ENMODAUL_API __declspec(dllexport)
#else
#define ENMODAUL_API __declspec(dllimport)
#endif

// This class is exported from the EnModAul.dll
class ENMODAUL_API CEnModAul {
public:
	CEnModAul(void);
	// TODO: add your methods here.
};

extern ENMODAUL_API int nEnModAul;

ENMODAUL_API int fnEnModAul(void);
