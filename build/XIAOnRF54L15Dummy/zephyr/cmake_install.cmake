# Install script for directory: /opt/nordic/ncs/v3.2.4/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/nordic/ncs/toolchains/185bb0e3b6/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/rubensteijn/GitHub/XIAOnRF54L15Dummy/build/XIAOnRF54L15Dummy/zephyr/cmake/reports/cmake_install.cmake")
endif()

