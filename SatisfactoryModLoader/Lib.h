#pragma once

#include <string>
#include <vector>

#if defined(SATISFACTORYMODLOADER_EXPORTS)
#define SML_API __declspec(dllexport)
#else
#define SML_API __declspec(dllimport)
#endif
