#ifndef PJ_WATHER_H
#define PJ_WATHER_H

#include <iostream>
#include <fstream>

#include <filesystem>
#include <thread>

#include <string>

#include <list>
#include <vector>
#include <map>
#include <array>

#include <time.h>
#include <chrono>
#include <ratio>
#include <algorithm>

#include <filesystem> 
namespace std_fs = std::filesystem;

#ifdef __linux__
     #include <sys/stat.h>
     #include <sys/types.h>
#endif 


// name type file and count use 

enum PATH_TYPE {
     TYPE_DIR = 0,
     FTYPE_SUPPORTED,
     FTYPE_NOT_SUPPORTED
};

const std::list< std::string > supported_types_file = 
{ ".c",     ".cc",   ".c++", ".cpp", ".C" ,
  ".h",     ".hh" ,  ".hpp",

  ".py",    ".perl", ".go", ".php",
  ".html",  ".css",  ".js",

  ".ruby",  ".rb",   ".rust", ".rs",

  ".java",  ".class",
  ".cs",

  ".swift", ".R", ".d", ".dd", ".di"
};


#define DELAY_CHECKS_SEC 1

struct FileInfo {
     std_fs::path path;
          
     std::time_t original_time_change;
     std::size_t original_size;

     std::size_t num_changes;    

     // make func get formula 
};

class ProjectsWatcher {
     
private:
     std::vector< FileInfo > changed_files;
     std::thread watcher_thread;         

     enum PATH_TYPE GetPathType( const std_fs::path *cpath );
     std::time_t GetTimeChangeFile( std::string );

     void AddFileToWatcher( std_fs::path file_path, 
               std::time_t time_change );
     void FindNewChangeFiles( std::string root_path, 
               std::time_t &last_change_time, std::time_t &res );


     void Run( std::string root_path);
 
public:
     ProjectsWatcher( std::string root_path);
     ~ProjectsWatcher();
};


#endif
