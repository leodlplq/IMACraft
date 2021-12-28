//
// Created by leodlplq on 22/11/2021.
//

#pragma once
#include "filePath.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <filesystem>

std::string get_file_contents(FilePath filePath);
