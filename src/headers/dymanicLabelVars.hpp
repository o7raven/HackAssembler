#pragma once
#include <unordered_map>
static struct dyn_map{
   std::unordered_map<std::string,unsigned int> label_map;
   std::unordered_map<std::string,unsigned int> var_map;
   dyn_map();
} dyn_map;