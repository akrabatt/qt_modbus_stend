#ifndef GLOBALS_H
#define GLOBALS_H

#include <map>
#include <devices/mops.h>
#include <devices/mups.h>

extern std::map<int, mops> global_map_mops_18v;    // глобальный контейнер МОПСов на 18v
extern std::map<int, mups> globla_map_mups_18v;    // глобальный контейнер МУПСов на 18v

extern std::map<int, mops> global_map_mops_24v;    // глобальный контейнер МОПСов на 24v
extern std::map<int, mups> globla_map_mups_24v;    // глобальный контейнер МУПСов на 24v

extern std::map<int, mops> global_map_mops_28v;    // глобальный контейнер МОПСов на 28v
extern std::map<int, mups> globla_map_mups_28v;    // глобальный контейнер МУПСов на 28v

#endif // GLOBALS_H
