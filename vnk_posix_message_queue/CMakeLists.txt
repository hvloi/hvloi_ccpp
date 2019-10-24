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

# CMAKE DEFINITION FILE

# Required version
cmake_minimum_required(VERSION 3.10.2)

# Project name
project(vinaknowledge_ccpp)

# Includes
include_directories(include)

# Add sources
set(SOURCES src/main.c src/vnk_mq_create.c src/vnk_mq_tumlum.c)

# Excutable files
add_executable(vnkmq ${SOURCES})

# Link library to target
# Find more at: https://cmake.org/cmake/help/latest/command/ \
# target_link_libraries.html#command:target_link_libraries
target_link_libraries(vnkmq rt)
