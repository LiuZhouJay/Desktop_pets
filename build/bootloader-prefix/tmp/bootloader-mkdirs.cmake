# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Jayzyl/esp/v5.1/esp-idf/components/bootloader/subproject"
  "D:/Code/espidf/Desktoppet/build/bootloader"
  "D:/Code/espidf/Desktoppet/build/bootloader-prefix"
  "D:/Code/espidf/Desktoppet/build/bootloader-prefix/tmp"
  "D:/Code/espidf/Desktoppet/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Code/espidf/Desktoppet/build/bootloader-prefix/src"
  "D:/Code/espidf/Desktoppet/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Code/espidf/Desktoppet/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Code/espidf/Desktoppet/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
