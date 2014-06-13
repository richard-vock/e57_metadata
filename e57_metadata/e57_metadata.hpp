#ifndef DURAARK_E57METADATA_HPP_
#define DURAARK_E57METADATA_HPP_

#include "extractor.hpp"

extern "C" {

int __declspec(dllexport) extract(const char input_file[], const char output_file[], const char file_type[]);

int __declspec(dllexport) test(const char input_file[]);

}



#endif // DURAARK_E57METADATA_HPP_