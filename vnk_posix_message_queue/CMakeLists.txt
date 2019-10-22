#/******************************************************************************
# ******************************************************************************
# **
# **     VINA KNOWLEDGE
# **
# **     Site : https://www.vinaknowledge.com
# **     Email: hvloi@vinaknowledge.com
# **
# **     Copyright © 2019 Vina Knowledge
# **
# *****************************************************************************/

# CMAKE

# Required version
cmake_minimum_required(VERSION 3.10.2)

# Project name
project(vinaknowledge_ccpp)

# Includes
include_directories(include)

# Add source
#set(SOURCES src/main.c src/vnk_mq_create.c src/vnk_mq_tumlum.c)
set(SOURCES src/main.c src/vnk_mq_create.c src/vnk_mq_tumlum.c)

# Add flags
set(CMAKE_CXX_FLAGS "-lrt")
set(C_FLAGS "-lrt")

# Add libs
#set(LIBS "-lrt")

# Add linker
#set(CMAKE_STATIC_LINKER_FLAGS "-lrt")

# Try try
#link_directories(/lib/x86_64-linux-gnu/librt-2.27.so)

# Excutable files
add_executable(vnkmq ${SOURCES})
