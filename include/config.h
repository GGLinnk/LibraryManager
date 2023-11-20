#define PROJECT_NAME    "LibraryManager"
#define PROJECT_VERSION "0.1.0"
#define PROJECT_NAMEVER "LibraryManager 0.1.0"

#define UI_DISABLED true
#define FTXUI_DISABLED true

#ifdef WIN32
    #define APPDATAROOT "LOCALAPPDATA"
#elif UNIX or __linux__
    #define APPDATAROOT "HOME"
#endif
