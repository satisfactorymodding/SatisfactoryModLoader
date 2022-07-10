/*
   Feather INI Parser - 2.0
   You are free to use this however you wish.

   If you find a bug, please attept to debug the cause.
   Post your environment details and the cause or fix in the issues section of GitHub.

   Written by Turbine1991.

   Website:
   http://code.google.com/p/feather-ini-parser/downloads

   Help:
   Bundled example & readme.
   https://github.com/Turbine1991/cpp-feather-ini-parser/tree/master/example
*/

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>

#ifndef FINI_WIDE_SUPPORT
  typedef std::stringstream fini_sstream_t;
  typedef std::string fini_string_t;
  typedef char fini_char_t;
  typedef std::ifstream fini_ifstream_t;
  typedef std::ofstream fini_ofstream_t;
#else
  typedef std::wstringstream fini_sstream_t;
  typedef std::wstring fini_string_t;
  typedef wchar_t fini_char_t;
  typedef std::wifstream fini_ifstream_t;
  typedef std::wofstream fini_ofstream_t;
#endif


fini_string_t& l_trim(fini_string_t& str, const fini_string_t trim_chars = "\t\v\f; ") {
  str.erase(0, str.find_first_not_of(trim_chars)); return str;
}

fini_string_t& r_trim(fini_string_t& str, const fini_string_t trim_chars = "\t\v\f; ") {
  str.erase(str.find_last_not_of(trim_chars) + 1); return str;
}

fini_string_t& trim(fini_string_t& str, const fini_string_t trim_chars = "\t\v\f; ") {
  return l_trim(r_trim(str, trim_chars), trim_chars);
}

template <typename T>
T convert_to (const fini_string_t &str) {
  fini_sstream_t ss(str);
  T num;
  ss >> num;
  return num;
}

template <>
fini_string_t convert_to<fini_string_t>(const fini_string_t &str) {
  return str;
}

template <>
const char* convert_to<const char*>(const fini_string_t &str) {
  return str.c_str();
}

///
class INI
{
public:
/// Define
  static int PARSE_FLAGS, SAVE_FLAGS;

  typedef fini_char_t data_t;

  typedef typename std::map<fini_string_t, fini_string_t> keys_t;
  typedef typename std::map<fini_string_t, keys_t*> sections_t;
  typedef typename keys_t::value_type keyspair_t;
  typedef typename sections_t::value_type sectionspair_t;

  enum source_e {SOURCE_FILE, SOURCE_MEMORY};
  enum save_e {SAVE_PRUNE = 1 << 0, SAVE_PADDING_SECTIONS = 1 << 1, SAVE_SPACE_SECTIONS = 1 << 2, SAVE_SPACE_KEYS  = 1 << 3, SAVE_TAB_KEYS  = 1 << 4, SAVE_SEMICOLON_KEYS  = 1 << 5};
  enum parse_e {PARSE_COMMENTS_SLASH = 1 << 0, PARSE_COMMENTS_HASH = 1 << 1, PARSE_COMMENTS_ALL = 1 << 2};

/// Data
   const source_e source;
   const fini_string_t filename;
   //data_t* data;
   //size_t dataSize;

   keys_t* current;
   sections_t sections;

/// Methods
  INI(const INI& from);
  INI(fini_string_t filename, bool doParse, int parseFlags = 0);
  //INI(void* data, size_t dataSize, bool doParse)
  ~INI();
  void clear();
  bool parse(int parseFlags = 0);
  void _parseFile(fini_ifstream_t& file, int parseFlags);
  bool save(fini_string_t filename, int saveFlags = 0);

  keys_t& operator[](fini_string_t section);
  void create(fini_string_t section);
  void remove(fini_string_t section);
  bool select(fini_string_t section, bool noCreate = false);
  fini_string_t get(fini_string_t section, fini_string_t key, fini_string_t def);
  fini_string_t get(fini_string_t key, fini_string_t def);
    template<class T>
  T getAs(fini_string_t section, fini_string_t key, T def = T());
    template<class T>
  T getAs(fini_string_t key, T def = T());
  void set(fini_string_t section, fini_string_t key, fini_string_t value);
  void set(fini_string_t key, fini_string_t value);
};

/// Definition
INI::INI(const INI& from): source(from.source), filename(from.filename) {
  // Deep clone INI
  for(auto i: from.sections) {
    select(i.first);
    for(auto j: *i.second)
      set(j.first, j.second);
  }
}

INI::INI(fini_string_t filename, bool doParse, int parseFlags): source(SOURCE_FILE), filename(filename) {
  this->create("");

  if (doParse)
     parse(parseFlags);
}

INI:: ~INI() {
  clear();
}

void INI::clear() {
  sections.clear();
}

bool INI::parse(int parseFlags) {
  parseFlags = (parseFlags > 0)? parseFlags: PARSE_FLAGS;

  switch(source)
  {
    case SOURCE_FILE: {
      fini_ifstream_t file(filename);

      if (!file.is_open())
        return false;

      _parseFile(file, parseFlags);

      file.close();
      } break;

    case SOURCE_MEMORY:
      /*std::stringstream sstream;
      sstream.rdbuf()->pubsetbuf(data, dataSize);
      parse(sstream);*/
      break;
  }

  return true;
}

int INI::PARSE_FLAGS = 0, INI::SAVE_FLAGS = 0;

void INI::_parseFile(fini_ifstream_t& file, int parseFlags) {
  fini_string_t line;
  fini_string_t section; // Set default section (support for sectionless files)
  size_t i = 0;
  keys_t* current = this->current;

  while(std::getline(file, line)) {
    i++;

    // Parse comments
    if (parseFlags & PARSE_COMMENTS_SLASH || parseFlags & PARSE_COMMENTS_ALL)
      line = line.substr(0, line.find("//"));
    if (parseFlags & PARSE_COMMENTS_HASH || parseFlags & PARSE_COMMENTS_ALL)
      line = line.substr(0, line.find("#"));

    if (trim(line).size() == 0) // Skip empty lines
      continue;

    if ('[' == line.at(0)) { // Section
      section = trim(line, "[] "); // Obtain key value, including contained spaced
      if (section.size() == 0) // If no section value, use default section
        current = this->current;

      if (sections.find(section) != sections.end()) {
        std::cerr << "Error: cpp-feather-ini-parser: Duplicate section '" + section + "':" << i << std::endl;
        throw -1;
      }

      current = new keys_t;
      sections[section] = current;
    } else {
      size_t indexEquals = line.find("=");
      if (indexEquals != fini_string_t::npos) {
        fini_string_t key = line.substr(0, indexEquals), value = line.substr(indexEquals + 1);
        r_trim(key);
        l_trim(value);

        if ((*current).find(key) != (*current).end()) {
          std::cerr << "Error: cpp-feather-ini-parser: Duplicate key '" + key + "':" << i << std::endl;
          throw -1;
        }

        (*current).emplace(key, value);
      }
    }
  }
}

bool INI::save(fini_string_t filename, int saveFlags) {
  saveFlags = (saveFlags > 0)? saveFlags: SAVE_FLAGS;

  fini_ofstream_t file((filename == "")? this->filename: filename, std::ios::trunc);
  if (!file.is_open())
     return false;

  // Save remaining sections
  for(auto i: sections) {
    //if (i.first == "")
    //  continue;
    if (saveFlags & SAVE_PRUNE && i.second->size() == 0)  // No keys/values in section, skip to next
      continue;

    // Write section
    if (i.first != "") {
      if (saveFlags & SAVE_SPACE_SECTIONS)
        file << "[ " << i.first << " ]" << std::endl;
      else
        file << '[' << i.first << ']' << std::endl;
    }

    // Loop through key & values
    for(auto j: *i.second) {
      if (saveFlags & SAVE_PRUNE && j.second == "")
        continue;

      // Write key & value
      if (saveFlags & SAVE_TAB_KEYS && i.first != "")
        file << '\t'; // Insert indent

      if (saveFlags & SAVE_SPACE_KEYS)
        file << j.first << " = " << j.second;
      else
        file << j.first << '=' << j.second;

      if (saveFlags & SAVE_SEMICOLON_KEYS)
        file << ';';

      file << std::endl;
    }

    // New section line
    if (saveFlags & SAVE_PADDING_SECTIONS)
      file << '\n';
  }

  file.close();

  return true;
}

//Provide bracket access to section contents
INI::keys_t& INI::operator[](fini_string_t section) {
  select(section);
  return *current;
}

//Create a new section and select it
void INI::create(fini_string_t section) {
  if (section != "" && sections.find(section) != sections.end()) {
    std::cerr << "Error: cpp-feather-ini-parser: Duplicate section '" << section << "'" << std::endl;
    throw -1;
  }

  current = new keys_t;
  sections[section] = current;
}

//Removes a section including all key/value pairs
void INI::remove(fini_string_t section) {
  if (select(section, true))
    sections.erase(section);

  current = NULL;
}

//Select a section for performing operations
bool INI::select(fini_string_t section, bool noCreate) {
  sections_t::iterator sectionsit = sections.find(section);
  if (sectionsit == sections.end()) {
     if (!noCreate)
       create(section);

     return false;
  }

  current = sectionsit->second;
  return true;
}

fini_string_t INI::get(fini_string_t section, fini_string_t key, fini_string_t def) {
  return get(key, def);
}

fini_string_t INI::get(fini_string_t key, fini_string_t def) {
  auto it = current->find(key);
  if (it == current->end())
     return def;

  return it->second;
}

  template<class T>
T INI::getAs(fini_string_t section, fini_string_t key, T def) {
  return getAs<T>(key, def);
}

  template<class T>
T INI::getAs(fini_string_t key, T def) {
  auto it = current->find(key);
  if (it == current->end())
     return def;

  return convert_to<T>(it->second);
}

void INI::set(fini_string_t section, fini_string_t key, fini_string_t value) {
  if (!select(section))
    create(section);

  set(key, value);
}

void INI::set(fini_string_t key, fini_string_t value) {
  (*current)[key] = value;
}
