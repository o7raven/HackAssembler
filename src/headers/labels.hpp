#pragma once
#include <unordered_map>
static struct Labels{
   std::unordered_map<std::string,unsigned int> label_map;
   Labels();
} Labels;