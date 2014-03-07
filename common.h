// DEMO

#ifndef PLUGINS_COMMON_H_
#define PLUGINS_COMMON_H_

#if defined(_WIN32) || defined(WIN32)
  #ifdef LIB_STATIC
    #define PLUGIN_DECL
  #else
    #ifdef PLUGINS_EXPORT
      #define PLUGIN_DECL __declspec(dllexport)
    #else
      #define PLUGIN_DECL __declspec(dllimport)
    #endif
  #endif
#else
    #define PLUGIN_DEMOS_DECL
#endif



#endif
