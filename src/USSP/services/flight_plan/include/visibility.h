#ifndef USSP_VISIBILITY_H_
#define USSP_VISIBILITY_H_

#if defined(__GNUC__) || defined(__clang__)
#define USSP_EXPORT __attribute__((visibility("default")))
#elif defined(_MSC_VER)
#define USSP_EXPORT __declspec(dllexport)
#else
#pragma message("unknown compiler - default USSP_EXPORT to empty")
#define USSP_EXPORT
#endif

#endif  // USSP_VISIBILITY_H_
