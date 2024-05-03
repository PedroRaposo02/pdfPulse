#pragma once

#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <string>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

void parseXml(const std::string& filepath);
std::string parseXmlString(const std::string& xmlString);

#endif // XML_PARSER_HPP