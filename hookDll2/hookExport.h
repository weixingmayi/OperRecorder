#pragma once
#ifdef HOOK_EXPORT
#define HOOK_API __declspec(dllexport)
#else
#define HOOK_API __declspec(dllimport)
#endif
 