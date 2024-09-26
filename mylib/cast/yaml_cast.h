﻿//
// Created by HanHaocheng on 2024/6/30.
//

#ifndef MYLIB_SLN_YAML_CONVERTER_H
#define MYLIB_SLN_YAML_CONVERTER_H

// 禁用C4251警告
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#include <yaml-cpp/yaml.h>

// 重新启用刚才禁用的警告
#pragma warning(pop)

#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../base/mylib_def.h"
#include "../exception/exception.h"
#include "string_cast.h"

MYLIB_BEGIN

#define YAML_CAST_TRY_BEG try {
#define YAML_CAST_TRY_END                  \
  }                                        \
  catch (const YAML::ParserException &e) { \
    MYLIB_THROW(e.what());                 \
  }                                        \
  catch (std::exception & e) {             \
    MYLIB_THROW(e.what());                 \
  }                                        \
  catch (...) {                            \
    MYLIB_THROW("cast_error");             \
  }

template<typename Ty>
class YamlCast {
public:
  using cast_type = Ty;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) { return StringCast<Ty>::fromString(yaml); }
  static String toString(const cast_type &ty) { return StringCast<Ty>::toString(ty); }
};

template<typename Ty>
class YamlCast<std::vector<Ty>> {
public:
  using cast_type = std::vector<Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    cast_type res;
    YAML_CAST_TRY_BEG
    YAML::Node node = YAML::Load(yaml);
    for (const auto &iter: node) { res.emplace_back(YamlCast<Ty>::fromString(YAML::Dump(iter))); }
    YAML_CAST_TRY_END
    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    YAML_CAST_TRY_BEG
    for (const auto &ele: ty) {
      node.push_back(YAML::Load(YamlCast<Ty>::toString(ele)));
    }
    YAML_CAST_TRY_END
    return YAML::Dump(node);
  }
};

template<typename Ty>
class YamlCast<std::list<Ty>> {
public:
  using cast_type = std::list<Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    cast_type res;
    YAML_CAST_TRY_BEG
    YAML::Node node = YAML::Load(yaml);
    for (const auto &iter: node) {
      res.emplace_back(YamlCast<Ty>::fromString(YAML::Dump(iter)));
    }
    YAML_CAST_TRY_END
    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    YAML_CAST_TRY_BEG
    for (auto &ele: ty) {
      node.push_back(YamlCast<Ty>::toString(ele));
    }
    YAML_CAST_TRY_END
    return YAML::Dump(node);
  }
};

template<typename Ty>
class YamlCast<std::forward_list<Ty>> {
public:
  using cast_type = std::forward_list<Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    YAML::Node node = YAML::Load(yaml);
    cast_type res;
    for (const auto &iter: node) { res.emplace_front(YamlCast<Ty>::fromString(YAML::Dump(iter))); }
    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    for (const auto &ele: ty) { node.push_back(YamlCast<value_type>::toString(ele)); }
    return YAML::Dump(node);
  }
};

template<typename Ty>
class YamlCast<std::set<Ty>> {
public:
  using cast_type = std::set<Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    YAML::Node node = YAML::Load(yaml);
    cast_type res;
    for (const auto &iter: node) { res.emplace(YamlCast<value_type>::fromString(YAML::Dump(iter))); }
    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    for (const auto &ele: ty) { node.push_back(YamlCast<value_type>::toString(ele)); }
    return YAML::Dump(node);
  }
};

template<typename Ty>
class YamlCast<std::unordered_set<Ty>> {
public:
  using cast_type = std::unordered_set<Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    YAML::Node node = YAML::Load(yaml);
    cast_type res;
    for (const auto &iter: node) { res.emplace(YamlCast<value_type>::fromString(YAML::Dump(iter))); }
    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    for (const auto &ele: ty) { node.push_back(YamlCast<value_type>::toString(ele)); }
    return YAML::Dump(node);
  }
};

template<typename Ty>
class YamlCast<std::map<String, Ty>> {
public:
  using cast_type = std::map<String, Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    YAML::Node node = YAML::Load(yaml);
    cast_type res;
    for (const auto &iter: node) {
      String key = iter.first.IsScalar() ? iter.first.Scalar() : YAML::Dump(iter.first);
      value_type value = YamlCast<value_type>::fromString(YAML::Dump(iter.second));
      res.emplace(key, value);
    }

    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    for (const auto &ele: ty) { node[ele.first] = YamlCast<value_type>::toString(ele.second); }
    return YAML::Dump(node);
  }
};

template<typename Ty>
class YamlCast<std::unordered_map<String, Ty>> {
public:
  using cast_type = std::unordered_map<String, Ty>;
  using value_type = Ty;

  static cast_type fromString(const String &yaml) {
    YAML::Node node = YAML::Load(yaml);
    cast_type res;
    for (const auto &iter: node) {
      String key = iter.first.IsScalar() ? iter.first.Scalar() : YAML::Dump(iter.first);
      value_type value = YamlCast<value_type>::fromString(YAML::Dump(iter.second));
      res.emplace(key, value);
    }
    return res;
  }

  static String toString(const cast_type &ty) {
    YAML::Node node;
    for (const auto &ele: ty) { node[ele.first] = YamlCast<value_type>::toString(ele.second); }
    return Dump(node);
  }
};

MYLIB_END

#endif//MYLIB_SLN_YAML_CONVERTER_H