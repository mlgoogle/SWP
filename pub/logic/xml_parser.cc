//  Copyright (c) 2016-2017 The SWP Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "logic/xml_parser.h"
#include "file/file_util.h"
#include <algorithm>

namespace logic {

XmlParser::XmlParser() {
}

XmlParser::~XmlParser() {

}

base_logic::DictionaryValue* XmlParser::ReadXml(const std::string& file_name) {
  std::string error_str;
  int32 error_code;
  std::string content;
  file::FilePath sfile_name(file_name);
  bool r = file::ReadFileToString(sfile_name, &content);
  if (!r)
    return NULL;
  base_logic::DictionaryValue *value = NULL;

  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, OnConfigStart, OnConfigEnd);

  if (XML_Parse(parser, xml, amt, 1) == XML_STATUS_ERROR) {
    MIG_ERROR(USER_LEVEL, "XML Parser error:%s at line %llu",
              XML_ErrorString(XML_GetErrorCode(parser)),
              XML_GetCurrentLineNumber(parser));
    XML_ParserFree(parser);
    if (xml) {
      delete[] xml;
      xml = NULL;
    }
    return false;
  }

  XML_ParserFree(parser);
  if (xml) {
    delete xml;
    xml = NULL;
  }
  return true;
  /*content.erase(remove(content.begin(),content.end(),'\n'), content.end());
   content.erase(remove(content.begin(),content.end(),'\r'), content.end());
   content = content.substr(42,content.length());
   base_logic::ValueSerializer *engine = base_logic::ValueSerializer::Create(
   base_logic::IMPL_XML,&content);
   if (engine == NULL)
   return NULL;
   base_logic::DictionaryValue *value = (base_logic::DictionaryValue*) engine
   ->Deserialize( &error_code, &error_str);*/
  return value;
}

}
