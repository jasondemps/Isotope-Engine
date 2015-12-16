#include <algorithm>
#include <vector>
#include <string.h>
#include <stddef.h>
#include "glx_core_3_3.hpp"

#if defined(__APPLE__)
#include <mach-o/dyld.h>

static void* AppleGLGetProcAddress (const GLubyte *name)
{
  static const struct mach_header* image = NULL;
  NSSymbol symbol;
  char* symbolName;
  if (NULL == image)
  {
    image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
  }
  /* prepend a '_' for the Unix C symbol mangling convention */
  symbolName = malloc(strlen((const char*)name) + 2);
  strcpy(symbolName+1, (const char*)name);
  symbolName[0] = '_';
  symbol = NULL;
  /* if (NSIsSymbolNameDefined(symbolName))
	 symbol = NSLookupAndBindSymbol(symbolName); */
  symbol = image ? NSLookupSymbolInImage(image, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR) : NULL;
  free(symbolName);
  return symbol ? NSAddressOfSymbol(symbol) : NULL;
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#endif

static int TestPointer(const PROC pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

static PROC WinGetProcAddress(const char *name)
{
	HMODULE glMod = NULL;
	PROC pFunc = wglGetProcAddress((LPCSTR)name);
	if(TestPointer(pFunc))
	{
		return pFunc;
	}
	glMod = GetModuleHandleA("OpenGL32.dll");
	return (PROC)GetProcAddress(glMod, (LPCSTR)name);
}
	
#define IntGetProcAddress(name) WinGetProcAddress(name)
#else
	#if defined(__APPLE__)
		#define IntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define IntGetProcAddress(name) SunGetProcAddress(name)
		#else /* GLX */
		    #include <GL/glx.h>

			#define IntGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
		#endif
	#endif
#endif

namespace glX
{
	namespace exts
	{
	} //namespace exts
	
	namespace _detail
	{
	} //namespace _detail
	
	namespace sys
	{
		namespace 
		{
			typedef int (*PFN_LOADEXTENSION)();
			struct MapEntry
			{
				MapEntry(const char *_extName, exts::LoadTest *_extVariable)
					: extName(_extName)
					, extVariable(_extVariable)
					, loaderFunc(0)
					{}
					
				MapEntry(const char *_extName, exts::LoadTest *_extVariable, PFN_LOADEXTENSION _loaderFunc)
					: extName(_extName)
					, extVariable(_extVariable)
					, loaderFunc(_loaderFunc)
					{}
				
				const char *extName;
				exts::LoadTest *extVariable;
				PFN_LOADEXTENSION loaderFunc;
			};
			
			struct MapCompare
			{
				MapCompare(const char *test_) : test(test_) {}
				bool operator()(const MapEntry &other) { return strcmp(test, other.extName) == 0; }
				const char *test;
			};
			
			void InitializeMappingTable(std::vector<MapEntry> &table)
			{
				table.reserve(0);
			}
			
			void ClearExtensionVars()
			{
			}
			
			void LoadExtByName(std::vector<MapEntry> &table, const char *extensionName)
			{
				std::vector<MapEntry>::iterator entry = std::find_if(table.begin(), table.end(), MapCompare(extensionName));
				
				if(entry != table.end())
				{
					if(entry->loaderFunc)
						(*entry->extVariable) = exts::LoadTest(true, entry->loaderFunc());
					else
						(*entry->extVariable) = exts::LoadTest(true, 0);
				}
			}
		} //namespace 
		
		
		namespace 
		{
			static void ProcExtsFromExtString(const char *strExtList, std::vector<MapEntry> &table)
			{
				size_t iExtListLen = strlen(strExtList);
				const char *strExtListEnd = strExtList + iExtListLen;
				const char *strCurrPos = strExtList;
				char strWorkBuff[256];
			
				while(*strCurrPos)
				{
					/*Get the extension at our position.*/
					int iStrLen = 0;
					const char *strEndStr = strchr(strCurrPos, ' ');
					int iStop = 0;
					if(strEndStr == NULL)
					{
						strEndStr = strExtListEnd;
						iStop = 1;
					}
			
					iStrLen = (int)((ptrdiff_t)strEndStr - (ptrdiff_t)strCurrPos);
			
					if(iStrLen > 255)
						return;
			
					strncpy(strWorkBuff, strCurrPos, iStrLen);
					strWorkBuff[iStrLen] = '\0';
			
					LoadExtByName(table, strWorkBuff);
			
					strCurrPos = strEndStr + 1;
					if(iStop) break;
				}
			}
			
		} //namespace 
		
		exts::LoadTest LoadFunctions(Display *display, int screen)
		{
			ClearExtensionVars();
			std::vector<MapEntry> table;
			InitializeMappingTable(table);
			
			
			ProcExtsFromExtString((const char *)glXQueryExtensionsString(display, screen), table);
			return exts::LoadTest(true, 0);
		}
		
	} //namespace sys
} //namespace glX
